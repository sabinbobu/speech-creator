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
/// \brief  Unit Test Cases for CtrlLed
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - ctaaCtrlLed.c
//            - CtrlLed.c
//            - CtrlLed_Data.c
//            - CtrlLed_Diag.c
//            - CtrlLed_Rte.c
//==============================================================================

//=============================================================================
// Includes
//=============================================================================

// Standard unit test header
#include <ALUnitTest_UserInterface.h>
#include <stdio.h>
#include <string.h>

// Stub headers
#include "Test_Stubs.h"
#include "Test_Ext.h"

// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
//  Module Test Cases
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  CtrlLed_Rte.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Rte_Get_BinningClass
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Rte_Get_BinningClass 
///                      returns the binning class for the requested LED channel
///                     RTE from RSense module
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input RTE binning ports filled with valid data : Binning Class and quality signal
///
///   - Expectations:
///
/// \output The function returns the binning class associated to the LED channel
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Rte_Get_BinningClass(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
    Rte_Read_RSens_BinningClass_sVal_00_Param1.ucBinning = 0x01;
    Rte_Read_RSens_BinningClass_sVal_00_Param1.eSigQty   = SIG_SNA;
    Rte_Read_RSens_BinningClass_sVal_01_Param1.ucBinning = 0x04;
    Rte_Read_RSens_BinningClass_sVal_01_Param1.eSigQty   = SIG_VALID;
    Rte_Read_RSens_BinningClass_sVal_02_Param1.ucBinning = 0x02;
    Rte_Read_RSens_BinningClass_sVal_02_Param1.eSigQty   = SIG_SNA;
    Rte_Read_RSens_BinningClass_sVal_03_Param1.ucBinning = 0x03;
    Rte_Read_RSens_BinningClass_sVal_03_Param1.eSigQty   = SIG_SNA;
    Rte_Read_RSens_BinningClass_sVal_04_Param1.ucBinning = 0x04;
    Rte_Read_RSens_BinningClass_sVal_04_Param1.eSigQty   = SIG_INIT;
    Rte_Read_RSens_BinningClass_sVal_05_Param1.ucBinning = 0x05;
    Rte_Read_RSens_BinningClass_sVal_05_Param1.eSigQty   = SIG_E2E_CRCERR;
    Rte_Read_RSens_BinningClass_sVal_06_Param1.ucBinning = 0x06;
    Rte_Read_RSens_BinningClass_sVal_06_Param1.eSigQty   = SIG_E2E_TIMEOUT;
    Rte_Read_RSens_BinningClass_sVal_07_Param1.ucBinning = 0x02;
    Rte_Read_RSens_BinningClass_sVal_07_Param1.eSigQty   = SIG_VALID;
    Rte_Read_RSens_BinningClass_sVal_08_Param1.ucBinning = 0x02;
    Rte_Read_RSens_BinningClass_sVal_08_Param1.eSigQty   = SIG_VALID;
    Rte_Read_RSens_BinningClass_sVal_09_Param1.ucBinning = 0x01;
    Rte_Read_RSens_BinningClass_sVal_09_Param1.eSigQty   = SIG_VALID;
    Rte_Read_RSens_BinningClass_sVal_10_Param1.ucBinning = 0x00;
    Rte_Read_RSens_BinningClass_sVal_10_Param1.eSigQty   = SIG_UNAVAILABLE;
    Rte_Read_RSens_BinningClass_sVal_11_Param1.ucBinning = 0x00;
    Rte_Read_RSens_BinningClass_sVal_11_Param1.eSigQty   = SIG_UNAVAILABLE;

         /*   -- INPUT --      |   -- OUTPUT --        */
  struct {uint8 ucInputBinning;  uint8 ucBinningClass;         }  asTestCaseData[]
    = {
         {  0x00,             CTRLLED_CFG_UNKNOWN_UINT8_VALUE   },
         {  0x01,                                        0x04   },
         {  0x02,             CTRLLED_CFG_UNKNOWN_UINT8_VALUE   },
         {  0x03,             CTRLLED_CFG_UNKNOWN_UINT8_VALUE   },
         {  0x04,             CTRLLED_CFG_UNKNOWN_UINT8_VALUE   },
         {  0x05,             CTRLLED_CFG_UNKNOWN_UINT8_VALUE   },
         {  0x06,             CTRLLED_CFG_UNKNOWN_UINT8_VALUE   },
         {  0x07,                                        0x02   },
         {  0x08,                                        0x02   },
         {  0x09,                                        0x01   },
         {  0x10,             CTRLLED_CFG_UNKNOWN_UINT8_VALUE   },
         {  0x11,             CTRLLED_CFG_UNKNOWN_UINT8_VALUE   },
      };

  for (uint8 ucIdx = 0; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
      //Step 2) Assign Input values
      CtrlLed_Rte_Get_BinningClass_Param1   = ucIdx;
      CtrlLed_Rte_ReadTgtBinningVal_Param1  = ucIdx; // is needed for : CtrlLed_Rte_apfnReadTgtBinningClass_sVal_List[CtrlLed_Rte_ReadTgtBinningVal_Param1](&CtrlLed_Rte_ReadTgtBinningVal_Param2);

      //Step 3) Call FUT
      CtrlLed_Rte_Get_BinningClass_RetVal = CtrlLed_Rte_Get_BinningClass(CtrlLed_Rte_Get_BinningClass_Param1);

      //Step 4) Check expected output values
      AL_UNITTEST_CHECK(CtrlLed_Rte_Get_BinningClass_RetVal, asTestCaseData[ucIdx].ucBinningClass, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Read_Vbat
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function stores the battery voltage read via
///                     RTE from IoHwAb module
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1     = 4500u
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount   = 0u
/// \input CtrlLed_RteAccess_Read_Vbat_RetVal               = 0u
///
///   - Expectations:
///
/// \output CtrlLed_RteAccess_Read_Vbat_RetVal             = 4500u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Read_Vbat(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1    = 4500u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
  CtrlLed_RteAccess_Read_Vbat_RetVal              = 0u;

  //Step 3) Call FUT
  CtrlLed_RteAccess_Read_Vbat_RetVal = CtrlLed_RteAccess_Read_Vbat();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Read_Vbat_RetVal,          4500u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Get_EcuSide
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function stores the ECU side read via
///                     RTE from IoHwAb module
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input Mounted side detection via RTE port
///
///   - Expectations:
///
/// \output Mounted Side read and decoded
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Get_EcuSide(void)
{
  //Step 1: Set pre-conditions
  teCtrlLed_EcuSide MtTest = eEcu_Undef;

  struct { teRte_MountingSide eRteSide; uint8 ucHitCount;  uint8 ucRetVal;   teCtrlLed_EcuSide* eMountedSide} asTestCaseData[] 
      =  {  {             eMountedUndef,              1u,            E_OK,                     eEcu_Undef  },
            {              eMountedLeft,              1u,            E_OK,                     eEcu_Left   },
            {             eMountedRight,              1u,            E_OK,                     eEcu_Right  },
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1: Set pre-conditions
    CtrlLed_RteAccess_Get_EcuSide_Param1 = &MtTest;
    //Step 2) Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1    = asTestCaseData[ucIdx].eRteSide;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
    Rte_Read_IoHwAbUser_GetMountingSide_RetVal    = E_OK;

    //Step 3) Call FUT
    CtrlLed_RteAccess_Get_EcuSide_RetVal = CtrlLed_RteAccess_Get_EcuSide(CtrlLed_RteAccess_Get_EcuSide_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_EcuSide_RetVal, asTestCaseData[ucIdx].ucRetVal,           == );
    AL_UNITTEST_CHECK(*CtrlLed_RteAccess_Get_EcuSide_Param1, asTestCaseData[ucIdx].eMountedSide,       == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, asTestCaseData[ucIdx].ucHitCount, == );

  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Get_ECU_Side
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function returns the ECU side received via
///                     RTE from IoHwAb module
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1     = eMountedLeft
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount   = 0u
///
///   - Expectations:
///
/// \output CtrlLed_RteAccess_Get_ECU_Side_RetVal         = eEcu_Left
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Get_ECU_Side(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedLeft;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  CtrlLed_RteAccess_Get_ECU_Side_RetVal = CtrlLed_RteAccess_Get_ECU_Side();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_ECU_Side_RetVal, eEcu_Left, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Get_CodingPara
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function writes the coding parameters 
///                     via RTE from CodM
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input CtrlLed_RteAccess_Get_CodingPara_Param1.eCodingState              = eParaFct0_CodingDataValid
/// \input CtrlLed_RteAccess_Get_CodingPara_Param1.psCodingParameters_Blocks = &Coding_Dummy
/// \input Rte_Read_CodM_CtrlLed_Para_HitCount                                = 0u
///
///   - Expectations:
///
/// \output Rte_Read_CodM_CtrlLed_Para.eCodingState              = eParaFct0_CodingDataValid
/// \output Rte_Read_CodM_CtrlLed_Para_HitCount                  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Get_CodingPara(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_CtrlLed_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CtrlLed_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_CtrlLed_Para_HitCount = 0u;

  //Step 3) Call FUT
  CtrlLed_RteAccess_Get_CodingPara(&CtrlLed_RteAccess_Get_CodingPara_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_CodingPara_Param1.eCodingState, eParaFct0_CodingDataValid, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlLed_Para_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Get_ChannelState
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads the LED channel states received from
///                     SysMon via RTE
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_LedState_Param1.aLedStates[1]   = 5u;
/// \input Rte_Read_SysMon_LedState_Param1.boVinBoostOk[1] = TRUE;
/// \input Rte_Read_SysMon_LedState_HitCount               = 0u
/// \input CtrlLed_RteAccess_Get_ChannelState_Param1       = 1u
///
///   - Expectations:
///
/// \output CtrlLed_RteAccess_Get_ChannelState_Param2.asChannelState[1].ucChannelStatus = 5u
/// \output CtrlLed_RteAccess_Get_ChannelState_Param2.asChannelState[1].boVinOk = TRUE
/// \output Rte_Read_SysMon_LedState_HitCount   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Get_ChannelState(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_LedState_Param1.aLedStates[1]   = 5u;
  Rte_Read_SysMon_LedState_Param1.boVinBoostOk[1] = TRUE;
  Rte_Read_SysMon_LedState_HitCount               = 0u;
  CtrlLed_RteAccess_Get_ChannelState_Param1       = 1u;

  //Step 3) Call FUT
  CtrlLed_RteAccess_Get_ChannelState(CtrlLed_RteAccess_Get_ChannelState_Param1, &CtrlLed_RteAccess_Get_ChannelState_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_ChannelState_Param2.asChannelState[1].ucChannelStatus, 5u, == );
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_ChannelState_Param2.asChannelState[1].boVinOk,       TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LedState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Set_ChannelSettings
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function sets the errors disabled for each LED channel
///                     via RTE
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Each LED error supported is set
///
///   - Expectations:
///
/// \output The disable status is set for each supported LED error
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Set_ChannelSettings(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_RteAccess_Set_ChannelSettings_Param1.ulDisable_ErrE2E             = 0x00;
  CtrlLed_RteAccess_Set_ChannelSettings_Param1.ulDisable_ErrOpenLoad        = 0x00;
  CtrlLed_RteAccess_Set_ChannelSettings_Param1.ulDisable_ErrOverCurrent     = 0x00;
  CtrlLed_RteAccess_Set_ChannelSettings_Param1.ulDisable_ErrOverVoltage     = 0xFFFu;
  CtrlLed_RteAccess_Set_ChannelSettings_Param1.ulDisable_ErrShortToGnd      = 2160;
  CtrlLed_RteAccess_Set_ChannelSettings_Param1.ulDisable_ErrShortToUbat     = 0x00;
  CtrlLed_RteAccess_Set_ChannelSettings_Param1.ulDisable_ErrSpi             = 0x00;
  CtrlLed_RteAccess_Set_ChannelSettings_Param1.ulDisable_ErrThermalShutdown = 0x00;
  CtrlLed_RteAccess_Set_ChannelSettings_Param1.ulDisable_ErrUnderVoltage    = 0xFFFu;
  Rte_Write_CtrlLed_LedSettings_sVal_HitCount = 0u;

  //Step 3) Call FUT
  CtrlLed_RteAccess_Set_ChannelSettings(&CtrlLed_RteAccess_Set_ChannelSettings_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_LedSettings_sVal_Param1.ulDisableErrOverVoltage,   0xFFFu, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_LedSettings_sVal_Param1.ulDisableErrShortToGnd,      2160, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_LedSettings_sVal_Param1.ulDisableErrUnderVoltage,  0xFFFu, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_LedSettings_sVal_HitCount,                             1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Set_IlluminantsStatus
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlLed_RteAccess_Set_IlluminantsStatus 
///                     writes the LED channel Error Status assigned for the requested Illuminant 
///                     (16 configured Illuminants)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input RTE port Rte_Write_CtrlLed_ActLed_sState available
///
///   - Expectations:
///
/// \output The module CtrlLed sends via RTE port the LED error status for the given
///         Illuminant requested by CtrlLed_RteAccess_Set_IlluminantsStatus_Param1
///         and the channel fucntion name
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Set_IlluminantsStatus(void)
{
  //Step 1: Set pre-conditions
  Mt_InternalCodingMapping();
  for(uint8 ucLedIdx = 0u; ucLedIdx < CTRLLED_CFG_NO_ILLUMINANTS; ucLedIdx++) { Rte_Write_CtrlLed_ActLed_sState_Param1.uIlluminantState[ucLedIdx].unRaw = 0x00u; }
  Rte_Write_CtrlLed_ActLed_sState_HitCount       = 0u;

  for (uint8 ucIlIdx = 0u; ucIlIdx < CTRLLED_CFG_NO_ILLUMINANTS; ucIlIdx++)
  { 
    //Step 2) Assign Input values
    CtrlLed_RteAccess_Set_IlluminantsStatus_Param1 = ucIlIdx;

   /* Basic LED channels*/  if (ucIlIdx < 13u )       CtrlLed_RteAccess_Set_IlluminantsStatus_Param2 = (uint8)eLedState_On;
   /* Matrix LED channels*/ else                       CtrlLed_RteAccess_Set_IlluminantsStatus_Param2 = (uint8)eLedState_OpenLoad;
   CtrlLed_RteAccess_Set_IlluminantsStatus_Param3 = FALSE;
   CtrlLed_RteAccess_Set_IlluminantsStatus_Param4 = CtrlLed_sCodingData.ucLedName[ucIlIdx];
   
    //Step 3) Call FUT
    CtrlLed_RteAccess_Set_IlluminantsStatus(CtrlLed_RteAccess_Set_IlluminantsStatus_Param1, CtrlLed_RteAccess_Set_IlluminantsStatus_Param2, CtrlLed_RteAccess_Set_IlluminantsStatus_Param3, CtrlLed_RteAccess_Set_IlluminantsStatus_Param4);


    //Step 4) Check expected output values
    if (ucIlIdx < 13u)  { AL_UNITTEST_CHECK(Rte_Write_CtrlLed_ActLed_sState_Param1.uIlluminantState[CtrlLed_RteAccess_Set_IlluminantsStatus_Param1].unRaw, (uint8)eLedState_On, == ); }
    else                  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_ActLed_sState_Param1.uIlluminantState[CtrlLed_RteAccess_Set_IlluminantsStatus_Param1].unRaw, (uint8)eLedState_OpenLoad, == );
    
    AL_UNITTEST_CHECK(Rte_Write_CtrlLed_ActLed_sState_Param1.boIlluminantStatus[CtrlLed_RteAccess_Set_IlluminantsStatus_Param1], FALSE, == );
  }
 
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_ActLed_sState_HitCount, CTRLLED_CFG_NO_ILLUMINANTS, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Get_MatrixLuErrors
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlLed_RteAccess_Get_MatrixLuErrors 
///                     reads all matrix type errors received via RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input RTE port Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal available
///
///   - Expectations:
///
/// \output The module CtrlLed saves the received matrix errors in the function parameter
///         CtrlLed_RteAccess_Get_MatrixLuErrors_Param2 for each Logical Unit defined
///         by CtrlLed_RteAccess_Get_MatrixLuErrors_Param1
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Get_MatrixLuErrors(void)
{
  //Step 1: Set pre-conditions
  tuCtrlLed_bErr uTest_LedError = { 0 };
  CtrlLed_RteAccess_Get_MatrixLuErrors_Param2 = &uTest_LedError;    /* output parameter is pointer type and must be initialized*/

  //Step 2) Assign Input values
  CtrlLed_RteAccess_Get_MatrixLuErrors_Param1        = 5u;
  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount = 0u;
  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[CtrlLed_RteAccess_Get_MatrixLuErrors_Param1].bErr.bCoruptComm = FALSE;
  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[CtrlLed_RteAccess_Get_MatrixLuErrors_Param1].bErr.bLossComm   = TRUE;
  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[CtrlLed_RteAccess_Get_MatrixLuErrors_Param1].bErr.bPxlFault   = TRUE;
  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[CtrlLed_RteAccess_Get_MatrixLuErrors_Param1].bErr.Reserved    = FALSE;
  
  //Step 3) Call FUT
  CtrlLed_RteAccess_Get_MatrixLuErrors(CtrlLed_RteAccess_Get_MatrixLuErrors_Param1, CtrlLed_RteAccess_Get_MatrixLuErrors_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_MatrixLuErrors_Param2[CtrlLed_RteAccess_Get_MatrixLuErrors_Param1].bErr.bCoruptComm,  FALSE, == );
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_MatrixLuErrors_Param2[CtrlLed_RteAccess_Get_MatrixLuErrors_Param1].bErr.bLossComm,     TRUE, == );
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_MatrixLuErrors_Param2[CtrlLed_RteAccess_Get_MatrixLuErrors_Param1].bErr.bPxlFault,     TRUE, == );
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_MatrixLuErrors_Param2[CtrlLed_RteAccess_Get_MatrixLuErrors_Param1].bErr.Reserved,     FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Get_MatrixVccxErrors
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlLed_RteAccess_Get_MatrixVccxErrors 
///                     reads the matrix supply errors via RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input RTE port Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState available
///
///   - Expectations:
///
/// \output The module CtrlLed saves the received matrix supply errors in the function parameters
///         CtrlLed_RteAccess_Get_MatrixVccxErrors_Param1 the ShortToGnd status and in 
///         CtrlLed_RteAccess_Get_MatrixVccxErrors_Param2 the StortToVbat status
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Get_MatrixVccxErrors(void)
{
  //Step 1: Set pre-conditions
  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boCommError         = FALSE;
  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boPxlError          = FALSE;
  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError   = FALSE;
  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError  = TRUE;
  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_HitCount = 0u;

  //Step 2) Assign Input values
  CtrlLed_RteAccess_Get_MatrixVccxErrors_Param1 = FALSE;
  CtrlLed_RteAccess_Get_MatrixVccxErrors_Param2 = FALSE;

  //Step 3) Call FUT
  CtrlLed_RteAccess_Get_MatrixVccxErrors(&CtrlLed_RteAccess_Get_MatrixVccxErrors_Param1, &CtrlLed_RteAccess_Get_MatrixVccxErrors_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_MatrixVccxErrors_Param1,    FALSE, == );
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_MatrixVccxErrors_Param2,     TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Get_DD01_Diag_Status
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlLed_RteAccess_Get_DD01_Diag_Status 
///                     reads the DIAG DD01 request via RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input RTE port Rte_Read_Diag_DD01_Activation available
///
///   - Expectations:
///
/// \output The module CtrlLed returns the received request
///         CtrlLed_RteAccess_Get_DD01_Diag_Status_RetVal = TRUE
///         Rte_Read_Diag_DD01_Activation_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Get_DD01_Diag_Status(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_RteAccess_Get_DD01_Diag_Status_RetVal = FALSE;
  Rte_Read_Diag_DD01_Activation_Param1          = TRUE;
  Rte_Read_Diag_DD01_Activation_HitCount        = 0u;

  //Step 3) Call FUT
  CtrlLed_RteAccess_Get_DD01_Diag_Status_RetVal = CtrlLed_RteAccess_Get_DD01_Diag_Status();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_DD01_Diag_Status_RetVal, TRUE, ==);
  AL_UNITTEST_CHECK(Rte_Read_Diag_DD01_Activation_HitCount,          1u, ==);

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_VoltageRange
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_RteAccess_VoltageRange 
///                      returns the LED Voltage range received via RTE from SysVolt
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input RTE  ports filled with valid data : voltage range
///
///   - Expectations:
///
/// \output The function returns the voltage state for the recived range
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_VoltageRange(void)
{
  //Step 1: Set pre-conditions
  CtrlLed_RteAccess_VoltageRange_RetVal = 0u;

  struct { uint8 ucRte_LedVoltage;      uint8 ucLedVoltRange;  } asTestCaseData[]
    = { {        SysVolt_eNormal,         CTRLLED_NORMAL_VOLT  },
        {        SysVolt_eLow2,             CTRLLED_LOW2_VOLT  },
        {        SysVolt_eLow1,             CTRLLED_LOW1_VOLT  },
        {        SysVolt_eUnknown,       CTRLLED_UNKNOWN_VOLT  },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount  = 0u;
    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1    = asTestCaseData[ucIdx].ucRte_LedVoltage;

    //Step 3) Call FUT
    CtrlLed_RteAccess_VoltageRange_RetVal = CtrlLed_RteAccess_VoltageRange();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlLed_RteAccess_VoltageRange_RetVal, asTestCaseData[ucIdx].ucLedVoltRange, == );
    AL_UNITTEST_CHECK(Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount, 1u, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Get_MatrixSystemMode
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_RteAccess_Get_MatrixSystemMode 
///                     marks the Matrix as configured if it has gone through its state 
///                     machine initialization and reached LedsConfig, otherwise it 
///                     returns FALSE
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input RTE  ports filled with valid data : matrix current system mode reached from its
///        own state machine
///
///   - Expectations:
///
/// \output The function returns the status of the matrix (TRUE = configured, FALSE = not configured)
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Get_MatrixSystemMode(void)
{
  //Step 1: Set pre-conditions
  Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_RetVal   = 0u;
  CtrlLed_RteAccess_Get_MatrixSystemMode_Param1    = 0u;

  struct { teRte_CddMlc_SystemMode  Rte_eSystemMode;      boolean boMtxConfigured;  } asTestCaseData[]
    = {  {        CddMlc_SystemMode_CfgComm,                                 FALSE  },
         {        CddMlc_SystemMode_CfgLeds,                                  TRUE  },
         {        CddMlc_SystemMode_Normal,                                   TRUE  },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_HitCount  = 0u;
    Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_Param1    = asTestCaseData[ucIdx].Rte_eSystemMode;

    //Step 3) Call FUT
    CtrlLed_RteAccess_Get_MatrixSystemMode(&CtrlLed_RteAccess_Get_MatrixSystemMode_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_MatrixSystemMode_Param1, asTestCaseData[ucIdx].boMtxConfigured, == );
    AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_HitCount,                                 1u, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Rte_ReadTgtBinningVal
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Rte_ReadTgtBinningVal 
///                     handles the  binning class data for the  given LED channel
///                     received via individual RTE ports (for each LED channel)
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input RTE  ports for binning class filled with data( valid/ invalid)
///
///   - Expectations:
///
/// \output The function returns the status and the recieved binning class data
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Rte_ReadTgtBinningVal(void)
{
  //Step 1: Set pre-conditions
  tsRte_Binning0 MtTest = { 0u, SIG_VALID };

  struct { uint8 ucChIdx;       tsRte_Binning0*  psBinningClass;      uint8 ucReturnStatus;   tsRte_Binning0  sBinningData  } asTestCaseData[]
    = { {              2u, Rte_Read_RSens_BinningClass_sVal_02,                       10u,               { 3u,   SIG_INIT } },
        {              2u,                            NULL_PTR,                        0u,               { 5u, SIG_INVALID} },
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    CtrlLed_Rte_apfnReadTgtBinningClass_sVal_List[asTestCaseData[ucIdx].ucChIdx] = asTestCaseData[ucIdx].psBinningClass;
    CtrlLed_Rte_ReadTgtBinningVal_Param1 = asTestCaseData[ucIdx].ucChIdx;
    CtrlLed_Rte_ReadTgtBinningVal_Param2 = &MtTest;
    CtrlLed_Rte_ReadTgtBinningVal_RetVal = 0u;

   if (ucIdx == 0u)
   {
      Rte_Read_RSens_BinningClass_sVal_02_RetVal            = 10u;
      Rte_Read_RSens_BinningClass_sVal_02_Param1.eSigQty    = asTestCaseData[ucIdx].sBinningData.eSigQty;
      Rte_Read_RSens_BinningClass_sVal_02_Param1.ucBinning  = asTestCaseData[ucIdx].sBinningData.ucBinning;
   }

    //Step 3) Call FUT
    CtrlLed_Rte_ReadTgtBinningVal_RetVal = CtrlLed_Rte_ReadTgtBinningVal(CtrlLed_Rte_ReadTgtBinningVal_Param1, CtrlLed_Rte_ReadTgtBinningVal_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlLed_Rte_ReadTgtBinningVal_RetVal, asTestCaseData[ucIdx].ucReturnStatus, == )

    if (ucIdx == 0u)
    {
      AL_UNITTEST_CHECK(CtrlLed_Rte_ReadTgtBinningVal_Param2->eSigQty, asTestCaseData[ucIdx].sBinningData.eSigQty, == );
      AL_UNITTEST_CHECK(CtrlLed_Rte_ReadTgtBinningVal_Param2->ucBinning, asTestCaseData[ucIdx].sBinningData.ucBinning, == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Get_HSS3_Status
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function stores the HSS status erros read via
///                     RTE from CtrlSwi module
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
///  \DT-Info:
///
///   - Inputs:
///       sHss3Status : HSS status received via RTE
///
///   - Expectations:
///       boHssEn : status of activated/deactivated HSS functionality
///       ucError : error status remaped by the module
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Get_HSS3_Status(void)
{

  struct { tsRte_Hss3Status  sHss3Status; boolean boHssEn;  uint8 ucError; } asTestCaseData[]
    = { {                       { 0x00u },              0u,         0xFFu   },
        {  {  TRUE, FALSE, FALSE, FALSE },              0u,            2u   },  //Sh2Gnd
        {  { FALSE,  TRUE, FALSE, FALSE },              0u,            0u   },  //OpenLoad
        {  { FALSE, FALSE,  TRUE, FALSE },              0u,            1u   },  //Sh2Vbat
        {  { FALSE, FALSE, FALSE,  TRUE },              1u,         0xFFu   },  //Hss Enabled
        {  { FALSE, FALSE,  TRUE,  TRUE },              1u,            1u   },  //Hss Enabled
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_CtrlSwi_Hss3StatusErr_Param1 = asTestCaseData[ucIdx].sHss3Status;
    
    //Step 3) Call the FUT
    CtrlLed_RteAccess_Get_HSS3_Status(&CtrlLed_RteAccess_Get_HSS3_Status_Param1, &CtrlLed_RteAccess_Get_HSS3_Status_Param2);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_HSS3_Status_Param1, asTestCaseData[ucIdx].ucError, ==);
    AL_UNITTEST_CHECK(CtrlLed_RteAccess_Get_HSS3_Status_Param2, asTestCaseData[ucIdx].boHssEn, ==);
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_RteAccess_Set_HSS3_Duty
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if the functions sends the duty via RTE
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
///         Rte_Write_CtrlLed_TgtHssSig_sVal_HitCount           = 0u
///         Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unCurrent   = 0u
///         Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unDutyCycle = 0u
///         CtrlLed_RteAccess_Set_HSS3_Duty_Param1              = 32000u
///
///    - Expected test results: 
///        - Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unDutyCycle = 32000u
///        - Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unCurrent   = 0u
///        - Rte_Write_CtrlLed_TgtHssSig_sVal_HitCount           = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_RteAccess_Set_HSS3_Duty(void)
{
  //Step 1) Set pre - conditions
  Rte_Write_CtrlLed_TgtHssSig_sVal_HitCount           = 0u;
  Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unCurrent   = 0u;
  Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unDutyCycle = 0u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlLed_RteAccess_Set_HSS3_Duty_Param1 = 32000u;

  //Step 3) Call the FUT
  CtrlLed_RteAccess_Set_HSS3_Duty(CtrlLed_RteAccess_Set_HSS3_Duty_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unCurrent,       0u, ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unDutyCycle, 32000u, ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtHssSig_sVal_HitCount,               1u, ==);
}

//-----------------------------------------------------------------------------
//  CtrlLed.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Init
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the init function reads the coding data validity and 
///                     sends current and duty for initialization of LEDs
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input Init runnable is called and  coding data filled 
///
///   - Expectations:
///
/// \output In case of invalid coding, PWM and current are 0, otherwise force to be 0 and call 
///         init of animation
/// \output ucAnimationCnt  : animation runnable call count
/// \output ucRTEWriteCnt   : RTE call
/// \output Rte_Write_CtrlLed_TgtLedSig_sVal_Param1[ucLedIdx].unCurrent   = 0u
/// \output Rte_Write_CtrlLed_TgtLedSig_sVal_Param1[ucLedIdx].unDutyCycle = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Init(void)
{
  //Step 1) Set pre-conditions
  CtrlLed_CreateCodingData_FULLVariant();
  Mt_InitializeCodingData(eEcu_Left);

  Anima_Init_HitCount = 0u;                         //no call of Anima_Init because Coding data is invalid
  Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount = 0u;   //no call of CtrlLed cycle

  struct {  tParaFct0_Cmd  eCodingState;  uint8 ucAnimationCnt;    uint8 ucRTEWriteCnt; } asTestCaseData[]
    = {  {  eParaFct0_CodingDataInvalid,                    0u,                     1u  },
         {    eParaFct0_CodingDataValid,                    1u,                     2u  },
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    Rte_Read_CodM_CtrlLed_Para_Param1.eCodingState              = asTestCaseData[ucIdx].eCodingState;

    //Step 3) Call FUT
    CtrlLed_Init();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Anima_Init_HitCount,                        asTestCaseData[ucIdx].ucAnimationCnt, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount,   asTestCaseData[ucIdx].ucRTEWriteCnt, == );

    for (uint8 ucLedIdx = 0u; ucLedIdx < CTRLLED_CFG_LED_CHANNELS_NR - 1u; ucLedIdx++)
    {
      AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_Param1[ucLedIdx].unCurrent,            0u, == );
      AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_Param1[ucLedIdx].unDutyCycle,          0u, == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Cycle0
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls and executes
///                     the cycle function of CtrlLed according to the
///                     defined cycle time = 5ms:
///                      a) even count -> Animation call
///                      a) odd count  -> CtrLed call
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Coding data assigned to CtrlLed is available (correct or not)
///
///   - Expectations:
///
/// \output Animation is called in even cycles and CtrlLed in odd cycles
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Cycle0(void)
{
  //Step 1) Set pre-conditions
  Anima_Cycle10_HitCount = 0u;   //no call of AnimaCycle
  Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount = 0u;   //no call of CtrlLed cycle

  struct { boolean boCodMap_OK;  uint8 ucCycleTime;  uint8 ucAnimationCnt;    uint8 ucCtrlLedCnt; } asTestCaseData[]
    = {  {                FALSE,                0u,                    0u,                    0u  },
         {                 TRUE,                0u,                    1u,                    0u  },
         {                 TRUE,                1u,                    1u,                    0u  },
         {                 TRUE,                2u,                    2u,                    0u  },
         {                 TRUE,                3u,                    2u,                    1u  },
         {                 TRUE,                4u,                    3u,                    1u  },
         {                 TRUE,                5u,                    3u,                    1u  },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    /* no input value, the idea is to ensure the correct timing call*/
    /* ucCycleTime is the time slot of the cycle call of the function  =  "virtual" call*/
    CtrlLed_boCodMap_OK = asTestCaseData[ucIdx].boCodMap_OK;

    //Step 3) Call FUT
    CtrlLed_Cycle0();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Anima_Cycle10_HitCount,                  asTestCaseData[ucIdx].ucAnimationCnt, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount, asTestCaseData[ucIdx].ucCtrlLedCnt, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Buck_Handling
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function remaps illuminants to led channels, applies duty, ramp and gamma
///
///    - Test Design Technique: DT( Decision Table )
///
///   - Preconditions:
///         Coding Initialized and mapped in internal structure
///         Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_Param1 = CddMlc_SystemMode_CfgLeds
///         Anima_Tgt_RetVal.boPriority = FALSE
///         CtrlLed_sInternalHandling.boMtxLightStatus = TRUE
///         sCtrlLed_ErrorHandler.boSwitchOffBuck[0..12] = FALSE
///         CtrlLed_sInternalHandling.boMtxLightIlStatus[0..12] = TRUE
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucLedCh      : LED Channel (buck ID) 
/// \input ucIlIdx      : Illuminant index
/// \input unRTE_TgtInt : RTE input target LED intensity
/// \input unRTE_Ramp   : RTE input ramp time
/// \input boRTE_Fbit   : RTE input F-bit ill. presence
/// \input ucChType     : LED buck channel type (matrix.non-matrix)
///
///   - Expectations:
///
/// \output  unCalculatedDuty    : duty cycle calculated for the given channel
/// \output  unCalculatedCurrent : current calculated for the given channel
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Buck_Handling(void)
{
  //Step 1) Set pre-conditions
  Mt_InternalCodingMapping();
  CtrlLed_CreateCodingData_FULLVariant();

  Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_Param1 = CddMlc_SystemMode_CfgLeds;   //to have matrix initialized
  Anima_Tgt_RetVal.boPriority                    = FALSE;
  CtrlLed_sInternalHandling.boMtxLightStatus     = TRUE;
  Rte_Read_Diag_DD01_Activation_Param1           = FALSE;

  for (uint8   ucIdx = 0u; ucIdx < CTRLLED_CFG_MAX_BUCK_DRV;        ucIdx++){   sCtrlLed_ErrorHandler.boSwitchOffBuck[ucIdx]        = FALSE;  }
  for (uint8 ucIdxIl = 0u; ucIdxIl < CTRLLED_CFG_NO_ILLUMINANTS; ucIdxIl++) { CtrlLed_sInternalHandling.boMtxLightIlStatus[ucIdxIl] = TRUE;   }  // always put 100% if f-bit is not present (errors are not present in this test)

    struct {
    uint8 ucLedCh; uint8 ucIlIdx;    uint16 unRTE_TgtInt; uint16 unRTE_Ramp; boolean boRTE_Fbit;       uint8 ucChType; uint16 unCalculatedDuty; uint16 unCalculatedCurrent;
}asTestCaseData[]
   = {
     {           0u,            0u,                     0u,                0u,      FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,                        0u ,   930u},
     {           1u,            1u,   CTRLLED_SCALING_1000,                0u,      FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,                    32764u ,  1000u},
     {           2u,            2u,                  1001u,                0u,      FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,                    32764u ,   930u},
     {           3u,            3u,   CTRLLED_SCALING_1000,                0u,       TRUE, CTRLLED_CFG_NON_MATRIX_BUCK,                    32764u ,   930u},
     {           7u,            4u,  CTRLLED_SCALING_32768,                0u,      FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,                    32764u ,   210u},
     {           4u,           13u,  CTRLLED_SCALING_65535,                0u,      FALSE,     CTRLLED_CFG_MATRIX_BUCK,                    32768u ,   885u},
     {          11u,           13u,  CTRLLED_SCALING_65535,                0u,      FALSE,     CTRLLED_CFG_MATRIX_BUCK,                    32768u ,   680u},
     {           6u,           14u,  CTRLLED_SCALING_32768,                0u,       TRUE,     CTRLLED_CFG_MATRIX_BUCK,                        0u ,   885u},  //f bit present
     {           5u,           15u,  CTRLLED_SCALING_32768,                0u,       TRUE,     CTRLLED_CFG_MATRIX_BUCK,                        0u ,   680u},  //f bit present
     {          12u,           11u,   CTRLLED_SCALING_1000,                0u,      FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,                    32767u ,     0u},  //HSS3
    };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    Rte_Read_FctR_TgtLed_sVal_Param1.asTgtLedVal[asTestCaseData[ucIdx].ucIlIdx].unTgtIntensity = asTestCaseData[ucIdx].unRTE_TgtInt;
    Rte_Read_FctR_TgtLed_sVal_Param1.asTgtLedVal[asTestCaseData[ucIdx].ucIlIdx].unRampTime     = asTestCaseData[ucIdx].unRTE_Ramp;
    Rte_Read_FctR_TgtLed_sVal_Param1.asTgtLedVal[asTestCaseData[ucIdx].ucIlIdx].boFBit         = asTestCaseData[ucIdx].boRTE_Fbit;
    CtrlLed_sCodingData.aucChannelType[asTestCaseData[ucIdx].ucLedCh]                          = asTestCaseData[ucIdx].ucChType;
    sCtrlLed_ErrorHandler.boSwitchOffBuck[asTestCaseData[ucIdx].ucLedCh] = FALSE;

    //Step 3) Call FUT
    CtrlLed_Buck_Handling();

    //Step 4) Check expected output values
    if (asTestCaseData[ucIdx].ucLedCh != 12u)
    {
      AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_Param1[asTestCaseData[ucIdx].ucLedCh].unDutyCycle, asTestCaseData[ucIdx].unCalculatedDuty, == );
      AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_Param1[asTestCaseData[ucIdx].ucLedCh].unCurrent, asTestCaseData[ucIdx].unCalculatedCurrent, == );
    }
    else
    {
      // special handling for HSS3
      AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unDutyCycle,       asTestCaseData[ucIdx].unCalculatedDuty, == );
      AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtHssSig_sVal_Param1.unCurrent,      asTestCaseData[ucIdx].unCalculatedCurrent, == );
    }
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_MatrixVoltCond
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function checks the input voltage for matrix and increases intensities in LOW1
///        condition and switches OFF for LOW2 condition or LOW1 with no light on the current row
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucVoltRange  : voltage range for matrix
/// \input eMtxRowLight : light distribution active assigned to the current row
///
///   - Expectations:
///
/// \output  eMtxVoltCnd  : action to be taken for matrix intensities based on input voltage
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_MatrixVoltCond(void)
{
  struct {   uint8 ucVoltRange;   uint8 eMtxRowLight;  teCtrlLed_MatrixVoltCnd eMtxVoltCnd; }asTestCaseData[]
    = {  {  CTRLLED_NORMAL_VOLT,                            0x04u,                  CtrlLed_MtxDoNothing },
         {    CTRLLED_LOW1_VOLT,                            0x01u,               CtrlLed_MtxFreeze_Write },
         {    CTRLLED_LOW1_VOLT,                            0x01u,                CtrlLed_MtxFreeze_Skip },
         {    CTRLLED_LOW2_VOLT,                            0x01u,                  CtrlLed_MtxSwitchOff },
         {  CTRLLED_NORMAL_VOLT,                            0x00u,                  CtrlLed_MtxDoNothing },
         {    CTRLLED_LOW1_VOLT,                            0x00u,                  CtrlLed_MtxSwitchOff },
         { CTRLLED_UNKNOWN_VOLT,                            0x00u,                  CtrlLed_MtxDoNothing },
  
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlLed_MatrixVoltCond_Param1                 = asTestCaseData[ucIdx].ucVoltRange;
    CtrlLed_sInternalHandling.ucMatrixRowLightBit = asTestCaseData[ucIdx].eMtxRowLight;

    //Step 3) Call FUT
    CtrlLed_MatrixVoltCond_RetVal = CtrlLed_MatrixVoltCond(CtrlLed_MatrixVoltCond_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlLed_MatrixVoltCond_RetVal,   asTestCaseData[ucIdx].eMtxVoltCnd, == );

  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Matrix_Handling_TestCase1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function handles the matrix intensities, errors and reaction.
///        Check that the function reads the matrix errors via RTE and in case of error free with
///        no animation sequence, it applies the intensities from Pxa and does not 
///        apply gamma correction when no Gamma LUT is assigned
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Coding valid and extracted in internal handling structure
/// \input  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError   = FALSE
/// \input  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError  = FALSE
/// \input  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1                         = { FALSE, FALSE };
/// \input  Rte_Read_AdbPxa_IntensityMatrix_Param1[00..90]   = 45u
/// \input  CtrlLed_sInternalHandling.ucMatrixRowLightBit    = 0x00u
/// \input  CtrlLed_sInternalHandling.boFbitMtx              = FALSE
/// \input  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1     = SysVolt_eLow1
/// \input  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount         = 0u
/// \input  Rte_Read_Diag_DD01_Activation_Param1             = FALSE
/// \input  CtrlLed_sCodingData.sGamma.aucGammaSel[00...103] = 0u
///
/// - Expectations:
///
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[12...59] = 294u
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u
/// \output CtrlLed_sInternalHandling.boMtxLightStatus = FALSE
/// \output CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0b0111
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Matrix_Handling_TestCase1(void)
{
  Mt_InternalCodingMapping();

  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError   = FALSE;
  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError  = FALSE;
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1                         = (tsRte_MtxEeprom_ErrStatus){ FALSE, FALSE };
  Anima_Tgt_RetVal.boPriority = FALSE;  //no animation requested

  for(uint8 ucIdx =0u; ucIdx < 30u; ucIdx++)
  {
    Rte_Read_AdbPxa_IntensityMatrix_Param1.Top[ucIdx]     = 45u;
    Rte_Read_AdbPxa_IntensityMatrix_Param1.Mid[ucIdx]     = 45u;
    Rte_Read_AdbPxa_IntensityMatrix_Param1.Bottom[ucIdx]  = 45u;
  }
  Rte_Read_Diag_DD01_Activation_Param1 = FALSE;
  CtrlLed_sInternalHandling.ucMatrixRowLightBit  = 0x00u;
  CtrlLed_sInternalHandling.boFbitMtx            = FALSE;
  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1   = SysVolt_eLow1;   // go to CtrlLed_MtxSwitchOff
  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount       = 0u;
  for (uint8 ucIdx = 0u; ucIdx < 103u; ucIdx++) { CtrlLed_sCodingData.sGamma.aucGammaSel[ucIdx] = 0u; }  //LUT = 1, no gamma points defined

  //Step 3) Call FUT
  CtrlLed_Matrix_Handling();


  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  for (uint8 ucIdx = 0u; ucIdx < 103u; ucIdx++)
  {
    if (ucIdx >= 12u && ucIdx < 60u)
    {
      AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucIdx], 294u, == );
    }
    else
    {
      AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucIdx], 0u, == );
    }
  }

  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount,               1u, == );
  AL_UNITTEST_CHECK(CtrlLed_sInternalHandling.boMtxLightStatus,          FALSE, == ); 
  AL_UNITTEST_CHECK(CtrlLed_sInternalHandling.ucMatrixRowLightBit,     0b0111u, == );  //all rows are lit up
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Matrix_Handling_TestCase2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function handles the matrix intensities, errors and reaction.
///        Check that the function reads the matrix errors via RTE and in case of error free with
///        animation sequence, it applies the intensities from Animation and does not 
///        apply gamma correction when no Gamma LUT is assigned
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Coding valid and extracted in internal handling structure
/// \input  Anima_Tgt_RetVal.boPriority                     = TRUE
/// \input  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1    = SysVolt_eNormal
/// \input  CtrlLed_sInternalHandling.ucMatrixRowLightBit   = 0x01u
/// \input  Anima_Tgt_RetVal.unTgtAni[0..103]               = 15000u
/// \input  eMtxVoltCnd                                     = CtrlLed_MtxSwitchOff
///
/// - Expectations:
///
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[10u] =      0u
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[12u] =  29999u
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[20u] =  29999u
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[26u] =      0u
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[44u] =      0u
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[48u] =  29999u
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[60u] =      0u
/// \output CtrlLed_sInternalHandling.ucMatrixRowLightBit         = 0b0011u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Matrix_Handling_TestCase2(void)
{
  //Step 1) Set pre - conditions
  Mt_InternalCodingMapping();
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  // animation requested
  Anima_Tgt_RetVal.boPriority = TRUE;
  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1    = SysVolt_eNormal;   // after function is executed, get CtrlLed_MtxSwitchOff 
  CtrlLed_sInternalHandling.ucMatrixRowLightBit   = 0x01u;

  for (uint8 ucIdx = 0u; ucIdx < 103u; ucIdx++) { Anima_Tgt_RetVal.unTgtAni[ucIdx] = 15000u; }
  for (uint8 ucIdx = 0u; ucIdx < 16u; ucIdx++) { CtrlLed_sCodingData.sGamma.aucGammaSel[ucIdx] = 0u; }  // no gamma points defined

  //Step 3) Call FUT
  //call function twice to get transition from  CtrlLed_MtxSwitchOff -> CtrlLed_MtxDoNothing in Normal Voltage behavior & eMtxRowLight = 0x01u
  CtrlLed_Matrix_Handling();
  CtrlLed_Matrix_Handling();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  //intensities scaled from Anima, because after 2nd call, boAnimationStatus = true
   AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[10u],     0u, == );
   AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[12u], 30000u, == );
   AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[20u], 30000u, == );
   AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[26u],     0u, == );
   AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[44u],     0u, == );
   AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[48u], 30000u, == );
   AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[60u],     0u, == );
   AL_UNITTEST_CHECK(CtrlLed_sInternalHandling.ucMatrixRowLightBit,        0b0011u, == );  // Lb Btm and Lb Mid are lit up
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Matrix_Handling_TestCase3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function handles the matrix intensities, errors and reaction.
///        Check that the function reads the matrix errors via RTE when diagnostic routine for controlling
///        pixels is requested, applies the diagnostic intensities and does not apply gamma correction
///        from the assigned Gamma LUT (with 0 gamma points => output =0% duty) because for diagnosis is NOT
///        REQUESTED. 
///        However, intensities will NOT BE UPDATED/ sent via RTE port because the matrix voltage condition 
///        is in low range and to avoid strange behaviour, intensities will be frozen (CtrlLed_MtxFreeze_Skip)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Coding valid and extracted in internal handling structure
/// \input  Anima_Tgt_RetVal.boPriority                   = TRUE
/// \input  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1  = SysVolt_eLow1
/// \input  CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0x04u
/// \input  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount      = 0u
/// \input  Rte_Read_Diag_DD01_Activation_Param1          = TRUE
/// \input  Rte_Read_Diag_DD01_PixelActivation_Param1.ucPixelIntensity[0..103] = 150u
///
/// - Expectations:
///
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount        = 0u
/// \output CtrlLed_sInternalHandling.ucMatrixRowLightBit   = 0b0111u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Matrix_Handling_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Anima_Tgt_RetVal.boPriority                   = TRUE;
  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1  = SysVolt_eLow1;      // to get the state eMtxVoltCnd = CtrlLed_MtxFreeze_Skip
  CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0x04u;  //Hb row
  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount      = 0u;
  Rte_Read_Diag_DD01_Activation_Param1          = TRUE;

  for (uint8 ucIdx = 0u; ucIdx < 103u; ucIdx++) { Rte_Read_Diag_DD01_PixelActivation_Param1.ucPixelIntensity[ucIdx] = 150u;  }
  for (uint8 ucIdx = 0u; ucIdx < 16u; ucIdx++)  { CtrlLed_sCodingData.sGamma.aucGammaSel[ucIdx] = 1u;      }  //LUT = 1,  gamma points defined

  //Step 3) Call FUT
  CtrlLed_Matrix_Handling();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  //CtrlLed_MtxFreeze_Skip, intensities are not sent again, RTE is not envoked  to update intensities
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount,               0u, == );
  AL_UNITTEST_CHECK(CtrlLed_sInternalHandling.ucMatrixRowLightBit,     0b0111u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Matrix_Handling_TestCase4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function handles the matrix intensities but when it finds
///        a logical unit which is not used, checks that no illuminant is assigned
///        and skips processing -> thus, row which is active is no more calculated
///        because it was skipped
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Coding valid and extracted in internal handling structure
/// \input  Anima_Tgt_RetVal.boPriority                   = FALSE
/// \input  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1  = SysVolt_eLow1
/// \input  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount      = 0u
/// \input  CtrlLed_sInternalHandling.boFbitMtx           = FALSE
/// \input  CtrlLed_sCodingData.aucLmmSwitchNo[60]        = 100u
/// \input  CtrlLed_pfCodingData()->aucLuIl[100]          = 0xFFu
///
/// - Expectations:
///
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[0...103] = 0u
/// \output CtrlLed_sInternalHandling.ucMatrixRowLightBit  = 0b0111u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Matrix_Handling_TestCase4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Anima_Tgt_RetVal.boPriority                   = FALSE;
  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1  = SysVolt_eLow1;      // stay in CtrlLed_MtxFreeze_Skip
  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount      = 0u;

  //test the case when no illuminant is assigned on a logical unit (also, logical unit is not used)
  CtrlLed_sInternalHandling.boFbitMtx     = FALSE;
  CtrlLed_sCodingData.aucLmmSwitchNo[60]  = 100u;   //logical unit assigned on pxl segment 60
  CtrlLed_pfCodingData()->aucLuIl[100]    = 0xFFu; // no illuminant assigned on a logical unit not used

  //Step 3) Call FUT
  CtrlLed_Matrix_Handling();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  //intensities are no more sent because the matrix voltage condition has not changed from freeze_skip
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount, 0u,           == );
  AL_UNITTEST_CHECK(CtrlLed_sInternalHandling.ucMatrixRowLightBit, 0b0111u, == );  //all rows are lit up
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Matrix_Handling_TestCase5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function handles the matrix intensities, errors and reaction.
///        Check that the function reads the matrix errors via RTE and in case the voltage
///        operation range is LOW2_VOLT, even if animation is requested, the matrix will be
///        switched off and force intensities to 0%
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Coding valid and extracted in internal handling structure
/// \input  Anima_Tgt_RetVal.boPriority                   = TRUE
/// \input  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1  = SysVolt_eLow2
/// \input  CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0x04u
/// \input  Anima_Tgt_RetVal.unTgtAni[0..103]             = 15000u
///
/// - Expectations:
///
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[0...103] = 0u
/// \output CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0b000u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Matrix_Handling_TestCase5(void)
{
  Anima_Tgt_RetVal.boPriority                   = TRUE;
  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1  = SysVolt_eLow2;    // to get the state eMtxVoltCnd = CtrlLed_MtxSwitchOff
  CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0x04u;  // Hb Row

  for (uint8 ucIdx = 0u; ucIdx < 103u; ucIdx++) { Anima_Tgt_RetVal.unTgtAni[ucIdx] = 15000u; }

  //Step 3) Call FUT
  CtrlLed_Matrix_Handling();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  //in Low2 voltage, switch off matrix
  for (uint8 ucIdx = 0u; ucIdx < 103u; ucIdx++)
  {
      AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucIdx], 0u, == );
  }
  AL_UNITTEST_CHECK(CtrlLed_sInternalHandling.ucMatrixRowLightBit, 0b0000u, == );  //no row is lit up
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Matrix_Handling_TestCase6
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function handles the matrix intensities, errors and reaction.
///        Check that the function reads the matrix errors via RTE when diagnostic routine for controlling
///        pixels is requested, applies the diagnostic intensities and does not apply gamma correction
///        from the assigned Gamma LUT (with 0 gamma points => output =0% duty) because for diagnosis is NOT
///        REQUESTED, and scale intensity to 65535 
///        However, intensities will NOT BE UPDATED/ sent via RTE port because the matrix voltage condition 
///        is in low range and to avoid strange behaviour, intensities will be frozen (CtrlLed_MtxFreeze_Skip)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Coding valid and extracted in internal handling structure
/// \input  Anima_Tgt_RetVal.boPriority                   = TRUE
/// \input  eMtxVoltCnd                                   = CtrlLed_MtxDoNothing;
/// \input  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1  = SysVolt_eLow1
/// \input  CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0x04u
/// \input  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount      = 0u
/// \input  Rte_Read_Diag_DD01_Activation_Param1          = TRUE
/// \input  Rte_Read_Diag_DD01_PixelActivation_Param1.ucPixelIntensity[0..103] = 100u
///
/// - Expectations:
///
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount        = 0u
/// \output CtrlLed_sInternalHandling.ucMatrixRowLightBit   = 0b0111u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Matrix_Handling_TestCase6(void)
{
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Anima_Tgt_RetVal.boPriority                    = TRUE;
    eMtxVoltCnd                                    = CtrlLed_MtxDoNothing;
    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1   = SysVolt_eLow1;      // to get the state eMtxVoltCnd = CtrlLed_MtxFreeze_Skip
    CtrlLed_sInternalHandling.ucMatrixRowLightBit  = 0x04u;  //Hb row
    Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount       = 0u;
    Rte_Read_Diag_DD01_Activation_Param1           = TRUE;
    for (uint8 ucIdx = 0u; ucIdx < 103u; ucIdx++) { Rte_Read_Diag_DD01_PixelActivation_Param1.ucPixelIntensity[ucIdx] = 100u; }
    for (uint8 ucIdx = 0u; ucIdx < 16u; ucIdx++)  { CtrlLed_sCodingData.sGamma.aucGammaSel[ucIdx] = 1u; }  //LUT = 1,  gamma points defined

    //Step 3) Call FUT
    CtrlLed_Matrix_Handling();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    //CtrlLed_MtxFreeze_Skip, intensities are not sent again, RTE is not envoked  to update intensities
    AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount, 0u, == );
    AL_UNITTEST_CHECK(CtrlLed_sInternalHandling.ucMatrixRowLightBit, 0b0111u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Matrix_Handling_TestCase7
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function handles the matrix intensities, errors and reaction.
///        Check that the function reads the matrix errors via RTE when diagnostic routine for controlling
///        pixels is requested, applies the diagnostic intensities and does not apply gamma correction
///        from the assigned Gamma LUT (with 0 gamma points => output =0% duty) because for diagnosis is NOT
///        REQUESTED, and scale intensity to 65535 for animation. 
///        However, intensities will NOT BE UPDATED/ sent via RTE port because the matrix voltage condition 
///        is in low range and to avoid strange behaviour, intensities will be frozen (CtrlLed_MtxFreeze_Skip)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Coding valid and extracted in internal handling structure
/// \input  Anima_Tgt_RetVal.boPriority                   = TRUE
/// \input  eMtxVoltCnd                                   = CtrlLed_MtxDoNothing;
/// \input  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1  = SysVolt_eLow1
/// \input  CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0x04u
/// \input  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount      = 0u
/// \input  Rte_Read_Diag_DD01_Activation_Param1          = TRUE
/// \input  Rte_Read_Diag_DD01_PixelActivation_Param1.ucPixelIntensity[0..103] = CTRLLED_SCALING_32768
///
/// - Expectations:
///
/// \output Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount        = 0u
/// \output CtrlLed_sInternalHandling.ucMatrixRowLightBit   = 0b0111u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Matrix_Handling_TestCase7(void)
{
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Anima_Tgt_RetVal.boPriority                     = TRUE;
    eMtxVoltCnd                                     = CtrlLed_MtxDoNothing;
    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1    = SysVolt_eLow1;      // to get the state eMtxVoltCnd = CtrlLed_MtxFreeze_Skip
    CtrlLed_sInternalHandling.ucMatrixRowLightBit   = 0x04u;  //Hb row
    Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount        = 0u;
    Rte_Read_Diag_DD01_Activation_Param1            = FALSE;
    for (uint8 ucIdx = 0u; ucIdx < 103u; ucIdx++) { Anima_Tgt_RetVal.unTgtAni[ucIdx] = CTRLLED_SCALING_32768; }
    for (uint8 ucIdx = 0u; ucIdx < 16u; ucIdx++)  { CtrlLed_sCodingData.sGamma.aucGammaSel[ucIdx] = 1u; }  //LUT = 1,  gamma points defined

    //Step 3) Call FUT
    CtrlLed_Matrix_Handling();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    //CtrlLed_MtxFreeze_Skip, intensities are not sent again, RTE is not envoked  to update intensities
    AL_UNITTEST_CHECK(Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Matrix_Handling
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function handles the matrix intensities, 
///                     errors and reaction.
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Matrix_Handling(void)
{
  Mt_CtrlLed_Matrix_Handling_TestCase1();
  Mt_CtrlLed_Matrix_Handling_TestCase2();
  Mt_CtrlLed_Matrix_Handling_TestCase3();
  Mt_CtrlLed_Matrix_Handling_TestCase6();
  Mt_CtrlLed_Matrix_Handling_TestCase4();
  Mt_CtrlLed_Matrix_Handling_TestCase5();
  Mt_CtrlLed_Matrix_Handling_TestCase7();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CheckLight
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function checks the input matrix row and target duty cycle
///        and returns the matrix light distribution associated to the matrix row controlled
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucPxlSeg     : pixel segment 
/// \input ucIlforLu    : illuminant for Lu
/// \input ucPxlSegLu   : logical unit associated to the pxl segm
/// \input unDutyCycle : target duty cycle
///
///   - Expectations:
///
/// \output   boKeepMtxOn : decision to keep matrix distribution on/off
/// \output  eMtxRowLight : matrix light distribution associated to the matrix row controlled
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CheckLight(void)
{
  //Step 1) Set pre-conditions
  for (uint8 ucIl = 0u; ucIl < CTRLLED_CFG_NO_ILLUMINANTS; ucIl++) { CtrlLed_sInternalHandling.boMtxLightIlStatus[ucIl] = FALSE; }

  struct { uint8 ucPxlSeg;   uint8 ucIlforLu;  uint8 ucPxlSegLu; uint16 unDutyCycle; uint8 ucMtxFault;  boolean boKeepMtxOn; uint8 eMtxRowLight; }asTestCaseData[]
    = {  {            23u,               15u,               36u,         65535u,                   0u,               TRUE ,              0x04u   },
         {            52u,               14u,               38u,         65535u,                   5u,               FALSE,              0x02u   },
         {            80u,               13u,               51u,         0u,                       0u,               FALSE,              0x00u   },
         {            60u,             0xFFu,             0xFFu,         32768u,                   0u,               FALSE,              0x01u   },
         { CTRLLED_CFG_MAX_NR_OF_PXL,  0xFFu,             0xFFu,         32768u,                   0u,               FALSE,              0x00u   },
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0x00u;

    //Step 2) Assign Input values
    CtrlLed_CheckLight_Param1        = asTestCaseData[ucIdx].ucPxlSeg;
    CtrlLed_CheckLight_Param2        = asTestCaseData[ucIdx].ucIlforLu;
    CtrlLed_CheckLight_Param3        = asTestCaseData[ucIdx].ucPxlSegLu;
    CtrlLed_CheckLight_Param4        = asTestCaseData[ucIdx].unDutyCycle;
    Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[CtrlLed_CheckLight_Param3].ucRaw = asTestCaseData[ucIdx].ucMtxFault;

    //Step 3) Call FUT
    CtrlLed_CheckLight(CtrlLed_CheckLight_Param1, CtrlLed_CheckLight_Param2, CtrlLed_CheckLight_Param3, &CtrlLed_CheckLight_Param4);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlLed_sInternalHandling.boMtxLightIlStatus[CtrlLed_CheckLight_Param2], asTestCaseData[ucIdx].boKeepMtxOn, == );
    AL_UNITTEST_CHECK(CtrlLed_sInternalHandling.ucMatrixRowLightBit,                          asTestCaseData[ucIdx].eMtxRowLight, == );
   // CtrlLed_sInternalHandling.aulPixelAffected
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Handle_MatrixCh
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function switches matrix channel to ON(100% duty) or OFF(0% duty)
///         based on request and matrix system mode
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucIlIdx     : illuminant index
/// \input unDutyCycle : target duty cycle
/// \input eSystemMode : matrix current setting
/// \input boKeepMtxOn : internal setting for matrix channels
///
///   - Expectations:
///
/// \output  unTargetIntensity : target intensity for matrix channels
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Handle_MatrixCh(void)
{
  //Step 1) Set pre-conditions

  struct {  uint8 ucIlIdx;  uint16 unDutyCycle;   teRte_CddMlc_SystemMode eSystemMode;    boolean boKeepMtxOn;   uint16 unTargetIntensity; }asTestCaseData[]
    = {  {            14u,            65535u,              CddMlc_SystemMode_CfgPhases ,               TRUE,       CTRLLED_CHANNEL_OFF   },
         {             6u,                0u,              CddMlc_SystemMode_CfgLeds   ,               TRUE,     CTRLLED_SCALING_32768   },
         {             5u,            65535u,              CddMlc_SystemMode_CfgPhases ,              FALSE,       CTRLLED_CHANNEL_OFF   },
         {            15u,                0u,              CddMlc_SystemMode_Normal    ,              FALSE,       CTRLLED_CHANNEL_OFF   },
         {            13u,            65535u,              CddMlc_SystemMode_Normal    ,               TRUE,     CTRLLED_SCALING_32768   },

  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {

    //Step 2) Assign Input values
    CtrlLed_Handle_MatrixCh_Param1                                               = asTestCaseData[ucIdx].ucIlIdx;
    CtrlLed_Handle_MatrixCh_Param2                                               = asTestCaseData[ucIdx].unDutyCycle;
    Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_Param1                               = asTestCaseData[ucIdx].eSystemMode;
    CtrlLed_sInternalHandling.boMtxLightIlStatus[asTestCaseData[ucIdx].ucIlIdx]  = asTestCaseData[ucIdx].boKeepMtxOn;

    //Step 3) Call FUT
    CtrlLed_Handle_MatrixCh_RetVal = CtrlLed_Handle_MatrixCh(CtrlLed_Handle_MatrixCh_Param1, CtrlLed_Handle_MatrixCh_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlLed_Handle_MatrixCh_RetVal, asTestCaseData[ucIdx].unTargetIntensity, == );

  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CalcRamp_TestCase1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description: This function is testing the case where  if (unTgtRampMs != 0u) is TRUE
///                         and  if (sRampValues[ucIdx].unOldIntensity != unTgtIntensity) is TRUE
///                         Checking if the returned value is the expected one
///
/// - Preconditions:
/// \input      CtrlLed_CalcRamp_Param1                                 = 0u
/// \input      CtrlLed_CalcRamp_Param2                                 = 50u
/// \input      CtrlLed_CalcRamp_Param3                                 = 100u
/// \input      ulTimerGetTimeSince_us[CtrlLed_CalcRamp_Param1]         = 1000u
/// \input      unStartPoint_Int[CtrlLed_CalcRamp_Param1]               = 2u
/// \input      sRampValues[CtrlLed_CalcRamp_Param1].unOldIntensity     = 200u
/// \input      sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping       = 50u
/// \input      sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 150
/// \input      UtilMath_LinearInterpolate_RetVal                       = 10u
///
/// - Expectations: Ramp Values are updated accordingly
/// \output     sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping = 100u
/// \output     sRampValues[CtrlLed_CalcRamp_Param1].unNewRamp    = 100u
/// \output     ulTimerGetTimeSince_us[CtrlLed_CalcRamp_Param1]   = 0u
/// \output     CtrlLed_CalcRamp_RetVal                           = 10u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CalcRamp_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_CalcRamp_Param1 = 0u;//ucIdx
  CtrlLed_CalcRamp_Param2 = 50u;//unTgtIntensity
  CtrlLed_CalcRamp_Param3 = 100u;//unTgtRampMs
  ulTimerGetTimeSince_us[CtrlLed_CalcRamp_Param1] = 1000u;
  unStartPoint_Int[CtrlLed_CalcRamp_Param1]       = 2u;

  sRampValues[CtrlLed_CalcRamp_Param1].unOldIntensity     = 200u;
  sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping       = 50u;
  sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 150u;
  UtilMath_LinearInterpolate_RetVal                       = 10u;

  //Step 3) Call FUT
  CtrlLed_CalcRamp_RetVal = CtrlLed_CalcRamp(CtrlLed_CalcRamp_Param1, CtrlLed_CalcRamp_Param2, CtrlLed_CalcRamp_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping,  100u, == );
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unNewRamp,     100u, == );
  AL_UNITTEST_CHECK(ulTimerGetTimeSince_us[CtrlLed_CalcRamp_Param1],      0u, == );
  AL_UNITTEST_CHECK(CtrlLed_CalcRamp_RetVal,                             10u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CalcRamp_TestCase2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description: This function is testing the case where  if (unTgtRampMs != 0u) is TRUE
///                         and  if (sRampValues[ucIdx].unOldIntensity != unTgtIntensity) is TRUE
///                         and  (boDimInProgress[ucIdx] == TRUE) and
///                         current intensity is less than target intensity, dimming up is performed
///
/// - Preconditions:
///  \input      sRampValues[CtrlLed_CalcRamp_Param1].unOldIntensity     = 20u
///  \input      sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 100u
///  \input      CtrlLed_CalcRamp_Param1                                 = 0u
///  \input      CtrlLed_CalcRamp_Param2                                 = 200u
///  \input      CtrlLed_CalcRamp_Param3                                 = 40u
///  \input      UtilMath_LinearInterpolate_RetVal                       = 80u
///
/// - Expectations: 
///  \output     sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping       = 40u
///  \output     sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 80u
///  \output     sRampValues[CtrlLed_CalcRamp_Param1].unNewRamp          =  4u
///  \output     CtrlLed_CalcRamp_RetVal                                 = 80u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CalcRamp_TestCase2(void)
{
  //Step 1) Set pre-conditions
  sRampValues[CtrlLed_CalcRamp_Param1].unOldIntensity     = 20u;
  sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 100u;

  //Step 2) Assign Input values
  CtrlLed_CalcRamp_Param1 = 0u;//ucIdx
  CtrlLed_CalcRamp_Param2 = 200u;//unTgtIntensity
  CtrlLed_CalcRamp_Param3 = 40u;//unTgtRampMs
  UtilMath_LinearInterpolate_RetVal = 80u;

  //Step 3) Call FUT
  CtrlLed_CalcRamp_RetVal = CtrlLed_CalcRamp(CtrlLed_CalcRamp_Param1, CtrlLed_CalcRamp_Param2, CtrlLed_CalcRamp_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping,       40u, == );
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity, 80u, == );
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unNewRamp,           4u, == );
  AL_UNITTEST_CHECK(CtrlLed_CalcRamp_RetVal,                                 80u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CalcRamp_TestCase3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description: This function is testing the case where  if (unTgtRampMs != 0u) is TRUE
///                         and  if (sRampValues[ucIdx].unOldIntensity != unTgtIntensity) is TRUE
///                         and  (boDimInProgress[ucIdx] == TRUE) 
///                         and  current intensity is greater than target intensity, then
///                         dimming down is performed. Also, negative ramp is not applied !
///
///
/// - Preconditions:
///  \input    CtrlLed_CalcRamp_Param1                                 = 0u
///  \input    CtrlLed_CalcRamp_Param2                                 = 150u
///  \input    CtrlLed_CalcRamp_Param3                                 = 25u
///  \input    sRampValues[CtrlLed_CalcRamp_Param1].unOldIntensity     = 100u
///  \input    sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 250u
///  \input     UtilMath_LinearInterpolate_RetVal                      = -25u
///
/// - Expectations: 
///  \output   sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping       = 25u
///  \output   sRampValues[CtrlLed_CalcRamp_Param1].unNewRamp          =  2u
///  \output   CtrlLed_CalcRamp_RetVal                                 =  0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CalcRamp_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_CalcRamp_Param1 = 0u;//ucIdx
  CtrlLed_CalcRamp_Param2 = 150u;//unTgtIntensity
  CtrlLed_CalcRamp_Param3 = 25u;//unTgtRampMs

  sRampValues[CtrlLed_CalcRamp_Param1].unOldIntensity     = 100u;
  sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 250u;

  UtilMath_LinearInterpolate_RetVal = -25u;   // cover the case when calculated ramp is negative

  //Step 3) Call FUT
  CtrlLed_CalcRamp_RetVal = CtrlLed_CalcRamp(CtrlLed_CalcRamp_Param1, CtrlLed_CalcRamp_Param2, CtrlLed_CalcRamp_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping,25u, == );
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unNewRamp,    2u, == );
  AL_UNITTEST_CHECK(CtrlLed_CalcRamp_RetVal,                            0, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CalcRamp_TestCase4
///
/// \FuSa Relevant: NA
///
/// \Test Case Description: Check that when ramping or intensities were not changed (no
///                         request of new values), the intensity remains unchanged
///
/// - Preconditions:
///  \input     CtrlLed_CalcRamp_Param1                                 = 0u
///  \input     CtrlLed_CalcRamp_Param2                                 = 15u
///  \input     CtrlLed_CalcRamp_Param3                                 = 100u
///  \input     sRampValues[CtrlLed_CalcRamp_Param1].unOldIntensity     = 15u
///  \input     sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping       = 100u
///  \input     sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 15u
///
/// - Expectations: Current intensity remains unchanged if equal with the requested
///  \output    sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 15u
///  \output    CtrlLed_CalcRamp_RetVal  = 15u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CalcRamp_TestCase4(void)
{
  //Step 1) Set pre-conditions

  //Step 2) Assign Input values
  CtrlLed_CalcRamp_Param1                                 = 0u;//ucIdx
  CtrlLed_CalcRamp_Param2                                 = 15u;//unTgtIntensity
  CtrlLed_CalcRamp_Param3                                 = 100u;//unTgtRampMs
  sRampValues[CtrlLed_CalcRamp_Param1].unOldIntensity     = 15u;
  sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping       = 100u;
  sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 15u;


  //Step 3) Call FUT
  CtrlLed_CalcRamp_RetVal = CtrlLed_CalcRamp(CtrlLed_CalcRamp_Param1, \
    CtrlLed_CalcRamp_Param2, \
    CtrlLed_CalcRamp_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity, 15u, == );
  AL_UNITTEST_CHECK(CtrlLed_CalcRamp_RetVal,                                 15u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CalcRamp_TestCase5
///
/// \FuSa Relevant: NA
///
/// \Test Case Description: Check that in case of no dimming requested, the intensities are
///                         and ramping are updated with the given values
///
/// - Preconditions:
///  \input    CtrlLed_CalcRamp_Param1                                 = 0u
///  \input    CtrlLed_CalcRamp_Param2                                 = 100u
///  \input    CtrlLed_CalcRamp_Param3                                 = 0u
///
/// - Expectations: Ramping is not set
///  \output   sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity = 100u
///  \output   sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping       = 0u
///  \output   CtrlLed_CalcRamp_RetVal                                 = 100u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CalcRamp_TestCase5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_CalcRamp_Param1 = 0u;   //ucIdx
  CtrlLed_CalcRamp_Param2 = 100u; //unTgtIntensity
  CtrlLed_CalcRamp_Param3 = 0u;   //unTgtRampMs

  //Step 3) Call FUT
  CtrlLed_CalcRamp_RetVal = CtrlLed_CalcRamp(CtrlLed_CalcRamp_Param1, \
    CtrlLed_CalcRamp_Param2, \
    CtrlLed_CalcRamp_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unCurrentIntensity, 100, == );
  AL_UNITTEST_CHECK(sRampValues[CtrlLed_CalcRamp_Param1].unOldRamping,         0, == );
  AL_UNITTEST_CHECK(CtrlLed_CalcRamp_RetVal,                                 100, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CalcRamp
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test that ramping and intensities are updated correctly
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CalcRamp(void)
{
  Mt_CtrlLed_CalcRamp_TestCase1();
  Mt_CtrlLed_CalcRamp_TestCase2();
  Mt_CtrlLed_CalcRamp_TestCase3();
  Mt_CtrlLed_CalcRamp_TestCase4();
  Mt_CtrlLed_CalcRamp_TestCase5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_GammaCurve_TestCase1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description: Check that gamma is applied on intensities higher than 0
///
/// - Preconditions:
///  \input  CtrlLed_GammaCurve_Param1           = 60u
///  \input  CtrlLed_GammaCurve_Param2           = 100u
///  \input  UtilMath_FastInterpolateU16_RetVal  = 25u
///
/// - Expectations:
///
///  \output  CtrlLed_GammaCurve_RetVal           = 99u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_GammaCurve_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_GammaCurve_Param1           = 60u;
  CtrlLed_GammaCurve_Param2           = 100u;
  UtilMath_FastInterpolateU16_RetVal  = 25u;

  //Step 3) Call FUT
  CtrlLed_GammaCurve_RetVal = CtrlLed_GammaCurve(CtrlLed_GammaCurve_Param1, &CtrlLed_GammaCurve_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_GammaCurve_RetVal, 99u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_GammaCurve_TestCase2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description: Check that gamma is not applied for 0 intensity
///
/// - Preconditions:
///  \input  CtrlLed_GammaCurve_Param1           = 0u
///  \input  CtrlLed_GammaCurve_Param2           = 0u
///
/// - Expectations:
///
///  \output CtrlLed_GammaCurve_RetVal           = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_GammaCurve_TestCase2(void)
{
  //Step 1) Set pre-conditions
 //Step 2) Assign Input values
  CtrlLed_GammaCurve_Param1 = 0;
  CtrlLed_GammaCurve_Param2 = 0;

  //Step 3) Call FUT
  CtrlLed_GammaCurve_RetVal = CtrlLed_GammaCurve(CtrlLed_GammaCurve_Param1, CtrlLed_GammaCurve_Param2);
  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(CtrlLed_GammaCurve_RetVal, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_GammaCurve
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test the conditions when gamma is applied on intensities
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_GammaCurve(void)
{
  Mt_CtrlLed_GammaCurve_TestCase1();
  Mt_CtrlLed_GammaCurve_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CurrentCalculation
///
/// \FuSa Relevant: NA
///
/// \Test Case Description: The function assigns the current from binning class
///
///  \DT-Info:
///
/// - Inputs:
/// \input   ucChIdx : LED channel index
///   
/// - Expectations:
///
/// \output unCurrent : Current will be 0 when Duty = 0, otherwise it is taken from the binning class
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CurrentCalculation(void)
{
  //Step 1) Set pre-conditions
  CtrlLed_CreateCodingData_FULLVariant();
  CtrlLed_CurrentCalculation_RetVal = 0u;

  struct { uint8 ucChIdx;       uint16 unCurrent; } asTestCaseData[]
    = { {             0u,      CtrlLed_pCodingArea->Led1.LedConfigDRV01.DRV01_CURRENT_BINNING_CLASSES[0] },
        {             1u,      CtrlLed_pCodingArea->Led1.LedConfigDRV02.DRV02_CURRENT_BINNING_CLASSES[0] },
        {             2u,      CtrlLed_pCodingArea->Led1.LedConfigDRV03.DRV03_CURRENT_BINNING_CLASSES[0] },
        {             3u,      CtrlLed_pCodingArea->Led1.LedConfigDRV04.DRV04_CURRENT_BINNING_CLASSES[0] },
        {             4u,      CtrlLed_pCodingArea->Led1.LedConfigDRV05.DRV05_CURRENT_BINNING_CLASSES[0] },
        {             5u,      CtrlLed_pCodingArea->Led1.LedConfigDRV06.DRV06_CURRENT_BINNING_CLASSES[0] },
  };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    CtrlLed_CurrentCalculation_Param1            = asTestCaseData[ucIdx].ucChIdx;
    CtrlLed_sCodingData.aunBinningCurrent[asTestCaseData[ucIdx].ucChIdx] = asTestCaseData[ucIdx].unCurrent;

    //Step 3) Call FUT
    CtrlLed_CurrentCalculation_RetVal = CtrlLed_CurrentCalculation(CtrlLed_CurrentCalculation_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlLed_CurrentCalculation_RetVal,            asTestCaseData[ucIdx].unCurrent, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_DutyCalculation
///
/// \FuSa Relevant: NA
///
/// \Test Case Description: Check that the function handles all channels and 
///                         returns a duty cycle based on 
///                         a target intensity and a ramp
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucLedCh      : LED channel 
/// \input ucIlIdx      : Illuminant index
/// \input boDiagEn     : request status of diagnostic service to control LU intensities
/// \input boAnimaPrio  : priority of animation to overtake FctR intensities
/// \input unTgtAni     : intensities from animation sequence
/// \input unRTE_TgtInt : RTE input target LED intensity
/// \input unRTE_Ramp   : RTE input ramp time
/// \input boRTE_Fbit   : RTE input F-bit ill. presence
/// \input ucChType     : LED buck channel type (matrix.non-matrix)
///
///   - Expectations:
///
/// \output  unCalculatedDuty : duty cycle calculated for the given channel
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_DutyCalculation(void)
{
  //Step 1) Set pre - conditions
  CtrlLed_CreateCodingData_FULLVariant();
  Mt_InternalCodingMapping();
  Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_Param1 = CddMlc_SystemMode_CfgLeds; 

  struct { 
      uint8 ucLedCh; uint8 ucIlIdx;  boolean boDiagEn; boolean boAnimaPrio; uint16 unTgtAni;    uint16 unRTE_TgtInt; uint16 unRTE_Ramp; boolean boRTE_Fbit;       uint8 ucChType; uint16 unCalculatedDuty;
  }asTestCaseData[]
 = { {           3u,            3u,             FALSE,               FALSE,              0u,   CTRLLED_SCALING_1000,                0u,       FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,              32764u     },
     {           0u,            0u,              TRUE,                TRUE,          16384u,                     0u,                0u,       FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,                  0u     },
     {           9u,            5u,             FALSE,                TRUE,          16384u,   CTRLLED_SCALING_1000,                0u,       FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,               4124u     },
     {          10u,            6u,             FALSE,                TRUE,              0u,   CTRLLED_SCALING_1000,                0u,       FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,                  0u     },
     {           5u,           13u,             FALSE,                TRUE,          16384u,  CTRLLED_SCALING_65535,             1000u,       FALSE,     CTRLLED_CFG_MATRIX_BUCK,              32768u     },
     {           4u,           12u,             FALSE,               FALSE,          16384u,  CTRLLED_SCALING_32768,                0u,        TRUE,     CTRLLED_CFG_MATRIX_BUCK,                  0u     },
     {           0u,            8u,              TRUE,                TRUE,              0u,   CTRLLED_SCALING_1000,                0u,       FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,                  0u     },
     {           2u,            2u,             FALSE,                TRUE,          16384u,  CTRLLED_SCALING_32768,                0u,       FALSE, CTRLLED_CFG_NON_MATRIX_BUCK,                  0u     },

  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlLed_DutyCalculation_Param1        = asTestCaseData[ucIdx].ucLedCh;
    CtrlLed_DutyCalculation_Param2        = asTestCaseData[ucIdx].ucIlIdx;
    Rte_Read_Diag_DD01_Activation_Param1  = asTestCaseData[ucIdx].boDiagEn;
    Anima_Tgt_RetVal.boPriority           = asTestCaseData[ucIdx].boAnimaPrio;
    if (ucIdx == 1u)      { Anima_Tgt_RetVal.unTgtAni[1u] = asTestCaseData[ucIdx].unTgtAni;    }   //animation requested, LU intensity
    else if (ucIdx == 3)  { Anima_Tgt_RetVal.unTgtAni[2u] = asTestCaseData[ucIdx].unTgtAni;    }  //animation requested, 0% intensity on the LU
    Rte_Read_FctR_TgtLed_sVal_Param1.asTgtLedVal[CtrlLed_DutyCalculation_Param2].unTgtIntensity = asTestCaseData[ucIdx].unRTE_TgtInt;
    Rte_Read_FctR_TgtLed_sVal_Param1.asTgtLedVal[CtrlLed_DutyCalculation_Param2].unRampTime     = asTestCaseData[ucIdx].unRTE_Ramp;
    Rte_Read_FctR_TgtLed_sVal_Param1.asTgtLedVal[CtrlLed_DutyCalculation_Param2].boFBit         = asTestCaseData[ucIdx].boRTE_Fbit;
    Rte_Read_Diag_DD01_PixelActivation_Param1.ucPixelIntensity[CtrlLed_sCodingData.ucLogicalUnitIl[CtrlLed_DutyCalculation_Param2]] =  asTestCaseData[ucIdx].unRTE_TgtInt / 10u;  // diag service sends [%]
    CtrlLed_sCodingData.aucChannelType[CtrlLed_DutyCalculation_Param1]                          = asTestCaseData[ucIdx].ucChType;

    //Step 3) Call the FUT
    CtrlLed_DutyCalculation_RetVal = CtrlLed_DutyCalculation(CtrlLed_DutyCalculation_Param1, CtrlLed_DutyCalculation_Param2);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlLed_DutyCalculation_RetVal, asTestCaseData[ucIdx].unCalculatedDuty, == );   //after gamma applied

  }

}
//-----------------------------------------------------------------------------
//  CtrlLed_Data.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CodingDataValidation
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function returns the status of the
///                        coding parameters
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Coding_State                            = eParaFct0_CodingDataValid
/// \input CtrlLed_CodingDataValidation_RetVal     = FALSE
/// \input Rte_Read_CodM_CtrlLed_Para_HitCount     = 0u
///
/// - Expectations:
///
/// \output CtrlLed_CodingDataValidation_RetVal    = TRUE
/// \output Rte_Read_CodM_CtrlLed_Para_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CodingDataValidation(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Coding_State = eParaFct0_CodingDataValid;
  CtrlLed_CodingDataValidation_RetVal = FALSE;
  Rte_Read_CodM_CtrlLed_Para_HitCount = 0u;

  //Step 3) Call FUT
  CtrlLed_CodingDataValidation_RetVal = CtrlLed_CodingDataValidation();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_CodingDataValidation_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlLed_Para_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_ParaFct0_TestCase1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the coding state and
///                        returns the validity of coding data
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlLed_ParaFct0_Param1     = eParaFct0_CodingDataValid
/// \input CtrlLed_ParaFct0_Param2     = &Coding_Dummy
/// \input CtrlLed_ParaFct0_RetVal     = FALSE
///
/// - Expectations:
///
/// \output CtrlLed_ParaFct0_RetVal    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_ParaFct0_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_ParaFct0_Param1 = eParaFct0_CodingDataValid;
  CtrlLed_ParaFct0_Param2 = &Coding_Dummy;
  CtrlLed_ParaFct0_RetVal = FALSE;

  //Step 3) Call FUT
  CtrlLed_ParaFct0_RetVal = CtrlLed_ParaFct0(CtrlLed_ParaFct0_Param1, CtrlLed_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_ParaFct0_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_ParaFct0_TestCase2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the coding state and
///                        returns the validity of coding data
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlLed_ParaFct0_Param1     = eParaFct0_CodingDataInvalid
/// \input CtrlLed_ParaFct0_Param2     = &Coding_Dummy
/// \input CtrlLed_ParaFct0_RetVal     = FALSE
///
/// - Expectations:
///
/// \output CtrlLed_ParaFct0_RetVal    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_ParaFct0_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
  CtrlLed_ParaFct0_Param2 = &Coding_Dummy;
  CtrlLed_ParaFct0_RetVal = FALSE;

  //Step 3) Call FUT
  CtrlLed_ParaFct0_RetVal = CtrlLed_ParaFct0(CtrlLed_ParaFct0_Param1, CtrlLed_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_ParaFct0_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_ParaFct0_TestCase3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets coding data to invalid
///                        for an undefined command status
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlLed_ParaFct0_Param1     = 3u
/// \input CtrlLed_ParaFct0_Param2     = &Coding_Dummy
/// \input CtrlLed_ParaFct0_RetVal     = FALSE
///
/// - Expectations:
///
/// \output CtrlLed_ParaFct0_RetVal    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_ParaFct0_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_ParaFct0_Param1 = 3u;
  CtrlLed_ParaFct0_Param2 = &Coding_Dummy;
  CtrlLed_ParaFct0_RetVal = FALSE;

  //Step 3) Call FUT
  CtrlLed_ParaFct0_RetVal = CtrlLed_ParaFct0(CtrlLed_ParaFct0_Param1, CtrlLed_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_ParaFct0_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_ParaFct0
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads the coding state and
///                     returns the validity of coding data
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_ParaFct0(void)
{
  Mt_CtrlLed_ParaFct0_TestCase1();
  Mt_CtrlLed_ParaFct0_TestCase2();
  Mt_CtrlLed_ParaFct0_TestCase3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CodMap_TestCase1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets coding data to invalid
///                        for an undefined command status
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlLed_CodMap_Param1     = &sTestInternalCoding
/// \input CtrlLed_CodMap_RetVal     = FALSE
///
/// - Expectations:
///
/// \output CtrlLed_CodMap_RetVal    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CodMap_TestCase1(void)
{
  CtrlLed_CreateCodingData_FULLVariant();

  //Step 1) Set pre-conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };

  //Step 2) Assign Input values
  CtrlLed_CodMap_Param1 = &sTestInternalCoding;
  CtrlLed_CodMap_RetVal = FALSE;

  //Step 3) Call FUT
  CtrlLed_CodMap_RetVal = CtrlLed_CodMap(CtrlLed_CodMap_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_CodMap_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CodMap_TestCase2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets coding data to invalid
///                        for an undefined command status
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlLed_CodMap_Param1     = &sTestInternalCoding
/// \input CtrlLed_Data_apfnDataMap_List[0u] = NULL_PTR
/// \input CtrlLed_Data_apfnDataMap_List[1u] = NULL_PTR
/// \input CtrlLed_Data_apfnDataMap_List[2u] = NULL_PTR
/// \input CtrlLed_Data_apfnDataMap_List[3u] = NULL_PTR
///
/// - Expectations:
///
/// \output CtrlLed_CodMap_RetVal    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CodMap_TestCase2(void)
{
  //Step 1) Set pre-conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };

  //Step 2) Assign Input values
  CtrlLed_CodMap_Param1 = &sTestInternalCoding;
  CtrlLed_Data_apfnDataMap_List[0u] = NULL_PTR;
  CtrlLed_Data_apfnDataMap_List[1u] = NULL_PTR;
  CtrlLed_Data_apfnDataMap_List[2u] = NULL_PTR;
  CtrlLed_Data_apfnDataMap_List[3u] = NULL_PTR;

  //Step 3) Call FUT
  CtrlLed_CodMap_RetVal = CtrlLed_CodMap(CtrlLed_CodMap_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_CodMap_RetVal, FALSE, == );

  //restore valid coding
  CtrlLed_CreateCodingData_FULLVariant();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CodMap
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads the coding state and
///                     returns the validity of coding data
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CodMap(void)
{
  Mt_CtrlLed_CodMap_TestCase1();
  Mt_CtrlLed_CodMap_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_DriverMap_TestCase1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///     - Test subject: Check that the function returns invalid status
///                        for invalid coding data/ undefined
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
///  \input  CtrlLed_Data_DriverMap_Param1 = eEcu_Undef
///  \input  CtrlLed_Data_DriverMap_Param2 =  &sTestInternalCoding
///
///    - Expected test results: 
///  \output  CtrlLed_Data_DriverMap_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_DriverMap_TestCase1(void)
{
  //Step 1) Set pre - conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlLed_Data_DriverMap_Param1 = eEcu_Undef;
  CtrlLed_Data_DriverMap_Param2 = &sTestInternalCoding;
  CtrlLed_Data_DriverMap_RetVal = TRUE;

  //Step 3) Call the FUT
  CtrlLed_Data_DriverMap_RetVal = CtrlLed_Data_DriverMap(CtrlLed_Data_DriverMap_Param1, CtrlLed_Data_DriverMap_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_RetVal, FALSE, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_DriverMap_TestCase2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///     - Test subject: Check that the function stores the buck type based
///           on coding data from Driver Map
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
///  \input : Create coding data
///           CtrlLed_CreateCodingData_FULLVariant();
///           Mt_InitializeCodingData(eEcu_Left);
///  \input  CtrlLed_Data_DriverMap_Param1 = eEcu_Left
///  \input  CtrlLed_Data_DriverMap_Param2 =  &sTestInternalCoding
///
///    - Expected test results: 
///  \output  CtrlLed_Data_DriverMap_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_DriverMap_TestCase2(void)
{
  Mt_InitializeCodingData(eEcu_Left);
  CtrlLed_CreateCodingData_FULLVariant();
  Mt_InternalCodingMapping();

  //Step 1) Set pre - conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlLed_Data_DriverMap_Param1 = eEcu_Left;
  CtrlLed_Data_DriverMap_Param2 = &sTestInternalCoding;
  //Step 3) Call the FUT
  CtrlLed_Data_DriverMap_RetVal = CtrlLed_Data_DriverMap(CtrlLed_Data_DriverMap_Param1, CtrlLed_Data_DriverMap_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[0],  CTRLLED_CFG_NON_MATRIX_BUCK, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[1],  CTRLLED_CFG_NON_MATRIX_BUCK, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[2],  CTRLLED_CFG_NON_MATRIX_BUCK, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[3],  CTRLLED_CFG_NON_MATRIX_BUCK, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[4],  CTRLLED_CFG_MATRIX_BUCK,     == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[5],  CTRLLED_CFG_MATRIX_BUCK,     == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[6],  CTRLLED_CFG_MATRIX_BUCK,     == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[7],  CTRLLED_CFG_NON_MATRIX_BUCK, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[8],  CTRLLED_CFG_NON_MATRIX_BUCK, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[9],  CTRLLED_CFG_NON_MATRIX_BUCK, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[10], CTRLLED_CFG_NON_MATRIX_BUCK, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucChannelType[11], CTRLLED_CFG_MATRIX_BUCK,     == );

  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[0],      0u,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[1],      1u,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[2],      2u,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[3],      3u,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[4],   0xFFu,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[5],   0xFFu,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[6],   0xFFu,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[7],      4u,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[8],      5u,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[9],      6u,      == );
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[10],     7u,      == );


  for (uint8 ucIdx = 60; ucIdx < 103; ucIdx++)
  {
    AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_Param2->aucLuIl[ucIdx], 0xFFu, == );

  }


  /* ------- T2)  Test to force coding invalid   ------- */ 
  //Step 1) Set pre - conditions
  CtrlLed_Force_InvalidCoding = TRUE;
  //Step 3) Call the FUT
  CtrlLed_Data_DriverMap_RetVal = CtrlLed_Data_DriverMap(CtrlLed_Data_DriverMap_Param1, CtrlLed_Data_DriverMap_Param2);
  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_Data_DriverMap_RetVal, FALSE, == );

  //restore value for further tests
  CtrlLed_Force_InvalidCoding = FALSE;
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_DriverMap
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test the coding data interpretation of "Mapping List sheet" at CtrlLed Level
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_DriverMap(void)
{
  Mt_CtrlLed_Data_DriverMap_TestCase1();
  Mt_CtrlLed_Data_DriverMap_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Matrix_TestCase1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function CtrlLed_Data_Matrix does not
///                        distribute coding data in case of undefined
///                        mounted headlamp side
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlLed_Data_Matrix_Param1 = eEcu_Undef
/// \input CtrlLed_Data_Matrix_Param2 = &sTestInternalCoding
///
/// - Expectations:
///
/// \output CtrlLed_Data_Matrix_RetVal    = FALSE
/// \output CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[30u]    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Matrix_TestCase1(void)
{
  //Step 1) Set pre-conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };

  //Step 2) Assign Input values
  CtrlLed_Data_Matrix_Param1               = eEcu_Undef;
  CtrlLed_Data_Matrix_Param2 = &sTestInternalCoding;

  //Step 3) Call FUT
  CtrlLed_Data_Matrix_RetVal = CtrlLed_Data_Matrix(CtrlLed_Data_Matrix_Param1, CtrlLed_Data_Matrix_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_Data_Matrix_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[30u], 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Matrix_TestCase2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function CtrlLed_Data_Matrix reads the corresponding
///                        coding data for the headlamp mounted side and saves in parameter
///                        CtrlPxl_Data_Matrix_Param2 the logical unit associated to 
///                        the segment
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input valid coding data -> call Mt_InitializeCodingData(eEcu_Left);
/// \input CtrlLed_Data_Matrix_Param1 = eEcu_Left
/// \input CtrlLed_Data_Matrix_Param2 = &sTestInternalCoding
///
/// - Expectations:
///
/// \output CtrlLed_Data_Matrix_RetVal    = TRUE
/// \output CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[11u]    = 24u
/// \output CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[48u]    = 46u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Matrix_TestCase2(void)
{
  //Step 1) Set pre-conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };
  Mt_InitializeCodingData(eEcu_Left);

  //Step 2) Assign Input values
  CtrlLed_Data_Matrix_Param1 = eEcu_Left;
  CtrlLed_Data_Matrix_Param2 = &sTestInternalCoding;

  //Step 3) Call FUT
  CtrlLed_Data_Matrix_RetVal = CtrlLed_Data_Matrix(CtrlLed_Data_Matrix_Param1, CtrlLed_Data_Matrix_Param2);
 
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_Data_Matrix_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[11u], 24u, == );  // logical unit associated to segm. 12
  AL_UNITTEST_CHECK(CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[48u], 46u, == );  // logical unit associated to segm. 49
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Matrix_TestCase3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function CtrlLed_Data_Matrix does not continue
///                        to proceed with saving data in case coding value is not valid.
///                        Despite knowing the mounted side and having coding filled with data,
///                        continue to process ONLY if valid values
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input valid coding data -> call Mt_InitializeCodingData(eEcu_Left)
/// \input CtrlLed_Data_Matrix_Param1 = eEcu_Left
/// \input CtrlLed_Data_Matrix_Param2 = &sTestInternalCoding
/// \input CtrlLed_pCodingArea->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[0][19] = CTRLLED_CFG_NR_OF_LOGICAL_UNITS + 1
///
/// - Expectations:
///
/// \output CtrlLed_Data_Matrix_RetVal    = FALSE
/// \output CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[11u]    = 24u
/// \output CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[48u]    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Matrix_TestCase3(void)
{
  //Step 1) Set pre-conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };
  Mt_InitializeCodingData(eEcu_Left);

  //Step 2) Assign Input values
  CtrlLed_Data_Matrix_Param1 = eEcu_Left;
  CtrlLed_Data_Matrix_Param2 = &sTestInternalCoding;

  CtrlLed_pCodingArea->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[0][19] = CTRLLED_CFG_NR_OF_LOGICAL_UNITS + 1; //coding available, but invalid value

  //Step 3) Call FUT
  CtrlLed_Data_Matrix_RetVal = CtrlLed_Data_Matrix(CtrlLed_Data_Matrix_Param1, CtrlLed_Data_Matrix_Param2);
 
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_Data_Matrix_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[11u], 24u, == );  // logical unit associated to segm. 12
  AL_UNITTEST_CHECK(CtrlLed_Data_Matrix_Param2->aucLmmSwitchNo[48u],  0u, == );  // no more data to be saved

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Matrix
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test the coding data interpretation of "Matrix sheet" at CtrlLed Level
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Matrix(void)
{
  Mt_CtrlLed_Data_Matrix_TestCase1();
  Mt_CtrlLed_Data_Matrix_TestCase2();
  Mt_CtrlLed_Data_Matrix_TestCase3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Led1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check that the functions reads the LED1 coding sheet and extracts the
///         binning currents and the LED channel names. 
///         1) Test that the coding current binning is assigned based on the slected 
///         binning class from RTE . 
///         2) Test that the LED channel functionality is assigned based on the
///         information from coding for each channel
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
///         Coding Data filled with valid data
/// \input  Rte_Read_RSens_BinningClass_sVal_01_Param1.ucBinning = 0x04
/// \input  Rte_Read_RSens_BinningClass_sVal_01_Param1.eSigQty = SIG_VALID
/// \input  Rte_Read_RSens_BinningClass_sVal_03_Param1.ucBinning = 0x03
/// \input  Rte_Read_RSens_BinningClass_sVal_03_Param1.eSigQty = SIG_SNA
/// \input  Rte_Read_RSens_BinningClass_sVal_04_Param1.ucBinning = 0x04
/// \input  Rte_Read_RSens_BinningClass_sVal_04_Param1.eSigQty = SIG_INIT
/// \input  Rte_Read_RSens_BinningClass_sVal_07_Param1.ucBinning = 0x02
/// \input  Rte_Read_RSens_BinningClass_sVal_07_Param1.eSigQty = SIG_VALID
/// \input  Rte_Read_RSens_BinningClass_sVal_11_Param1.ucBinning = 0x00
/// \input  Rte_Read_RSens_BinningClass_sVal_11_Param1.eSigQty = SIG_UNAVAILABLE
///
/// \input  CtrlLed_Data_Led1_Param1 = eEcu_Left
/// \input CtrlLed_Data_Led1_Param2 = &sTestInternalCoding
/// \input CtrlLed_Data_Led1_RetVal = FALSE
///
///    - Expected test results: 
/// \output trlLed_Data_Led1_RetVal = TRUE
///
///        - 1) binning class current is selected from coding
/// \output CtrlLed_Data_Led1_Param2->aunBinningCurrent[1u] = 705u
/// \output CtrlLed_Data_Led1_Param2->aunBinningCurrent[3u] = 930u
/// \output CtrlLed_Data_Led1_Param2->aunBinningCurrent[4u] = 885u
/// \output CtrlLed_Data_Led1_Param2->aunBinningCurrent[7u] = 210u
/// \output CtrlLed_Data_Led1_Param2->aunBinningCurrent[11u]= 680u
///
///        - 2) LED channel functionality is assigned based on coding
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[0]  =  2u    /* LB_FUSA */ 
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[1]  =  1u    /* LB - Low Beam */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[2]  =  1u    /* LB - Low Beam */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[3]  = 13u    /* CL - Cornering Light */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[4]  = 14u    /* PXL - matrix channel */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[5]  = 14u    /* PXL - matrix channel */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[6]  = 14u    /* PXL - matrix channel */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[7]  =  4u    /* DRL/POS - Daytime Running Light/ Position Light */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[8]  =  4u    /* DRL/POS - Daytime Running Light/ Position Light */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[9]  =  4u    /* DRL/POS - Daytime Running Light/ Position Light */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[10] =  6u    /* TI - Turn Indicator */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[11] = 14u    /* PXL - matrix channel */
/// \output  CtrlLed_Data_Led1_Param2->ucLedName[12] =  HSS3  /* HSS */
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Led1(void)
{
  //Step 1) Set pre - conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };
  CtrlLed_CreateCodingData_FULLVariant();

  Rte_Read_RSens_BinningClass_sVal_01_Param1.ucBinning = 0x04;
  Rte_Read_RSens_BinningClass_sVal_01_Param1.eSigQty = SIG_VALID;
  Rte_Read_RSens_BinningClass_sVal_03_Param1.ucBinning = 0x03;
  Rte_Read_RSens_BinningClass_sVal_03_Param1.eSigQty = SIG_SNA;
  Rte_Read_RSens_BinningClass_sVal_04_Param1.ucBinning = 0x04;
  Rte_Read_RSens_BinningClass_sVal_04_Param1.eSigQty = SIG_INIT;
  Rte_Read_RSens_BinningClass_sVal_07_Param1.ucBinning = 0x02;
  Rte_Read_RSens_BinningClass_sVal_07_Param1.eSigQty = SIG_VALID;
  Rte_Read_RSens_BinningClass_sVal_11_Param1.ucBinning = 0x00;
  Rte_Read_RSens_BinningClass_sVal_11_Param1.eSigQty = SIG_UNAVAILABLE;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlLed_Data_Led1_Param1 = eEcu_Left;
  CtrlLed_Data_Led1_Param2 = &sTestInternalCoding;
  CtrlLed_Data_Led1_RetVal = FALSE;
  
  //Step 3) Call the FUT
  CtrlLed_Data_Led1_RetVal = CtrlLed_Data_Led1(CtrlLed_Data_Led1_Param1, CtrlLed_Data_Led1_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_RetVal, TRUE, == );

  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->aunBinningCurrent[1u],   705u, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->aunBinningCurrent[3u],   930u,  == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->aunBinningCurrent[4u],   885u,  == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->aunBinningCurrent[7u],   210u,  == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->aunBinningCurrent[11u],  680u,  == );

  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[0],  2u,  == );  /* LB_FUSA */ 
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[1],  1u,  == );  /* LB - Low Beam */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[2],  1u,  == );  /* LB - Low Beam */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[3], 13u,  == );  /* CL - Cornering Light */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[4], 14u,  == );  /* PXL - matrix channel */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[5], 14u,  == );  /* PXL - matrix channel */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[6], 14u,  == );  /* PXL - matrix channel */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[7],  4u,  == );  /* DRL/POS - Daytime Running Light/ Position Light */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[8],  4u,  == );  /* DRL/POS - Daytime Running Light/ Position Light */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[9],  4u,  == );  /* DRL/POS - Daytime Running Light/ Position Light */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[10], 6u,  == );  /* TI - Turn Indicator */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[11],14u,  == );  /* PXL - matrix channel */
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_Param2->ucLedName[12], HSS3,== );  /* HSS */


  /*  ------------ T2) force invalid coding  ------------------------ */
   //Step 1) Set pre - conditions
  CtrlLed_Force_InvalidCoding = TRUE;
  //Step 3) Call the FUT
  CtrlLed_Data_Led1_RetVal = CtrlLed_Data_Led1(CtrlLed_Data_Led1_Param1, CtrlLed_Data_Led1_Param2);
  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_Data_Led1_RetVal, FALSE, == );
  //restore value
  CtrlLed_Force_InvalidCoding = FALSE;
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_LmmX
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function CtrlLed_Data_LmmX reads the corresponding
///                        coding data for the gamma points and saves in parameter
///                        CtrlLed_Data_LmmX_Param2 the gamma points for the LUT from coding
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input valid coding data -> call CtrlLed_CreateCodingData_FULLVariant();
/// \input CtrlLed_Data_LmmX_RetVal   = FALSE
/// \input CtrlLed_Data_LmmX_Param1   = eEcu_Left
/// \input CtCtrlLed_Data_LmmX_Param2 = &Mt_TestInitData
///
/// - Expectations:
///
/// \output CtrlLed_Data_LmmX_RetVal    = TRUE
/// \output CtrlLed_Data_LmmX_Param2->sGamma.aunGamma[0u][6u]  = 3518u
/// \output CtrlLed_Data_LmmX_Param2->sGamma.aunGamma[0u][14u] = 43926u
/// \output CtrlLed_Data_LmmX_Param2->sGamma.aunGamma[1u][11u] = 21340u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_LmmX(void)
{
  //Step 1) Set pre-conditions
  tsCtrlled_CodingData Mt_TestInitData = { 0 };

  //Step 2) Assign Input values
  CtrlLed_Data_LmmX_RetVal = FALSE;
  CtrlLed_Data_LmmX_Param1 = eEcu_Left;
  CtrlLed_Data_LmmX_Param2 = &Mt_TestInitData;
 
  //Step 3) Call FUT
  CtrlLed_Data_LmmX_RetVal = CtrlLed_Data_LmmX(CtrlLed_Data_LmmX_Param1, CtrlLed_Data_LmmX_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_Data_LmmX_RetVal, TRUE, ==);
  AL_UNITTEST_CHECK(CtrlLed_Data_LmmX_Param2->sGamma.aunGamma[0u][6u],   3518u, ==);
  AL_UNITTEST_CHECK(CtrlLed_Data_LmmX_Param2->sGamma.aunGamma[0u][14u], 43926u, ==);
  AL_UNITTEST_CHECK(CtrlLed_Data_LmmX_Param2->sGamma.aunGamma[1u][11u], 21340u, ==);

  /* ----------- T2) Test to force coding invalid  --------------------- */
  //Step 1) Set pre - conditions
  CtrlLed_Force_InvalidCoding = TRUE;
  //Step 3) Call the FUT
  CtrlLed_Data_LmmX_RetVal = CtrlLed_Data_LmmX(CtrlLed_Data_LmmX_Param1, CtrlLed_Data_LmmX_Param2);
  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_Data_LmmX_RetVal, FALSE, == );

  //restore value for further tests
  CtrlLed_Force_InvalidCoding = FALSE;

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Get_UnitGroup_TestCase1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check that for invalid coding parameters for unit groups,
///         the functions does not execute the data decompression logic and 
///         returns coding invalid.
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input   CtrlLed_Data_Get_UnitGroup_Param1 = eEcu_Undef
/// \input   CtrlLed_Data_Get_UnitGroup_Param2 = &Mt_TestInitData
///
///    - Expected test results: 
/// \output   CtrlLed_Data_Get_UnitGroup_RetVal = FALSE
/// \output   CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[1u].ucIlluminantAssigned  = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Get_UnitGroup_TestCase1(void)
{
  //Step 1) Set pre - conditions
  tsCtrlled_CodingData Mt_TestInitData = { 0 };

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlLed_Data_Get_UnitGroup_Param1 = eEcu_Undef;
  CtrlLed_Data_Get_UnitGroup_Param2 = &Mt_TestInitData;

  //Step 3) Call the FUT
  CtrlLed_Data_Get_UnitGroup_RetVal = CtrlLed_Data_Get_UnitGroup(CtrlLed_Data_Get_UnitGroup_Param1, CtrlLed_Data_Get_UnitGroup_Param2);
  
  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[1u].ucIlluminantAssigned,  0u, == );
  
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Get_UnitGroup_TestCase2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check that for a given mounted side and valid coding for unit GROUPS (110-119)
///         the function executes the data decompression logic and 
///         returns unit group number and the associated illuminant 
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input   CtrlLed_Data_Get_UnitGroup_Param1 = eEcu_Left
/// \input   CtrlLed_Data_Get_UnitGroup_Param2 = &Mt_TestInitData
///
///    - Expected test results: 
/// \output   CtrlLed_Data_Get_UnitGroup_RetVal = TRUE
/// \output   CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[0u].ucIlluminantAssigned = 13u
/// \output   CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[1u].ucIlluminantAssigned = 14u
/// \output   CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[9u].ucIlluminantAssigned = 0u
/// \output   CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[0u].ucName =  CTRLLED_CFG_FIRST_UNIT_GROUP
/// \output   CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[1u].ucName =  111u
/// \output   CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[2u].ucName =  112u
/// \output   CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[9u].ucName =  0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Get_UnitGroup_TestCase2(void)
{
  //Step 1) Set pre - conditions
  Mt_InternalCodingMapping();
  tsCtrlled_CodingData Mt_TestInitData = { 0 };
  ucUnitGroupCnt = 0u;      //reset variable

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlLed_Data_Get_UnitGroup_Param1 = eEcu_Left;
  CtrlLed_Data_Get_UnitGroup_Param2 = &Mt_TestInitData;

  //Step 3) Call the FUT
  CtrlLed_Data_Get_UnitGroup_RetVal = CtrlLed_Data_Get_UnitGroup(CtrlLed_Data_Get_UnitGroup_Param1, CtrlLed_Data_Get_UnitGroup_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_RetVal,                                                  TRUE, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[0u].ucIlluminantAssigned,            13u, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[1u].ucIlluminantAssigned,            14u, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[9u].ucIlluminantAssigned,             0u, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[0u].ucName, CTRLLED_CFG_FIRST_UNIT_GROUP, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[1u].ucName,                         111u, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[2u].ucName,                         112u, == );
  AL_UNITTEST_CHECK(CtrlLed_Data_Get_UnitGroup_Param2->asUnitGroups[9u].ucName,                           0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Get_UnitGroup
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test the coding data is decompressed correctly for
///               unit group selection
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Get_UnitGroup(void)
{
  Mt_CtrlLed_Data_Get_UnitGroup_TestCase1();
  Mt_CtrlLed_Data_Get_UnitGroup_TestCase2();
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Process_SingleUnits
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does not handle the coding data 
///                         for invalid inputs
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlLed_Data_Process_SingleUnits_Param4 = &Mt_TestInitData
/// \input CtrlLed_Data_Process_SingleUnits_Param1 = NULL_PTR
///
///   - Expectations:
///
/// \output  CtrlLed_Data_Process_SingleUnits_Param4->aunChannelIlluminant[5u] = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Process_SingleUnits_TestCase1(void)
{
  // T1 ) cover no input
  //Step 1) Set pre - conditions
  tsCtrlled_CodingData Mt_TestInitData = { 0 };
  CtrlLed_Data_Process_SingleUnits_Param4 = &Mt_TestInitData;
  CtrlLed_Data_Process_SingleUnits_Param1 = NULL_PTR;

  //Step 3) Call the FUT
  CtrlLed_Data_Process_SingleUnits(CtrlLed_Data_Process_SingleUnits_Param1, CtrlLed_Data_Process_SingleUnits_Param2, CtrlLed_Data_Process_SingleUnits_Param3, CtrlLed_Data_Process_SingleUnits_Param4);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_Data_Process_SingleUnits_Param4->aunChannelIlluminant[5u], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Process_SingleUnits_TestCase2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function handles the coding data and
///                         saves the LED driver on the bit position for
///                         the single unit groups
///
///        - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucInputData      : Lu (in this case also the driver) assigned to each illuminant 
/// \input ucDrvIdx         : drived index
/// \input ucLuIdx          : logical unit index
/// \input ucIllIdx         : illuminant index
///
///   - Expectations:
///
/// \output  ucChIl         : channel assigned for that illuminant (on bit)\
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Process_SingleUnits_TestCase2(void)
{
  //Step 1) Set pre - conditions
  tsCtrlled_CodingData Mt_TestInitData = { 0 };

  struct {                          uint8 ucInputData[CTRLLED_CFG_NO_ILLUMINANTS];  uint8 ucDrvIdx; uint8 ucLuIdx; uint8 ucIllIdx;  uint32 ucChIl; }asTestCaseData[]
    = {
      { { 1u, 2u, 3u, 4u, 8u, 9u, 10u, 11u, 0u, 0u, 0u, 0u, 0u, 110u, 111u, 112u },           HSS3,           10u,           10u,               0u }, //HSS3 driver, no Ill assigned
      { { 1u, 2u, 3u, 4u, 8u, 9u, 10u, 11u, 0u, 0u, 0u, 0u, 0u, 110u, 111u, 112u },             8u,            7u,            4u,             256u }, // 256 = 1 <<8u (set bit for the led channel)
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlLed_Data_Process_SingleUnits_Param1 = &asTestCaseData[ucIdx].ucInputData[0];
    CtrlLed_Data_Process_SingleUnits_Param2 = asTestCaseData[ucIdx].ucDrvIdx;
    CtrlLed_Data_Process_SingleUnits_Param3 = asTestCaseData[ucIdx].ucLuIdx;
    CtrlLed_Data_Process_SingleUnits_Param4 = &Mt_TestInitData;

    //Step 3) Call the FUT
    CtrlLed_Data_Process_SingleUnits(CtrlLed_Data_Process_SingleUnits_Param1, CtrlLed_Data_Process_SingleUnits_Param2, CtrlLed_Data_Process_SingleUnits_Param3, CtrlLed_Data_Process_SingleUnits_Param4);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlLed_Data_Process_SingleUnits_Param4->aunChannelIlluminant[asTestCaseData[ucIdx].ucIllIdx], asTestCaseData[ucIdx].ucChIl, == );
  }
 }

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_Process_SingleUnits
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test the coding data is decompressed correctly for
///               single unit group selection
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_Process_SingleUnits(void)
{
  Mt_CtrlLed_Data_Process_SingleUnits_TestCase1();
  Mt_CtrlLed_Data_Process_SingleUnits_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Data_AnimaMap
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Check that the function handles the coding data and
///                         maps correctly the logical units used by animation
///
///       - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boUT_ForceInvalid      : instrumentation to force coding NULL_PTR
/// \input ucLuIdx                : logical unit index
///
///   - Expectations:
///
/// \output  ucAnimMap            : animation mapping of logical units
/// \output  boRetCodingStatus    : coding validity
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Data_AnimaMap(void)
{
  //Step 1) Set pre - conditions
  tsCtrlled_CodingData Mt_TestInitData = { 0 };

  struct { boolean boUT_ForceInvalid;   uint8 ucLuIdx; uint8 ucAnimMap;  boolean boRetCodingStatus; } asTestCaseData[]
    =    { {                    TRUE,             15u,           0x00u,                       FALSE },
           {                    FALSE,             6u,           0xFFu,                       TRUE  },
           {                    FALSE,            60u,           0xFFu,                       TRUE  },
           {                    FALSE,            22u,             20u,                       TRUE  },
           {                    FALSE,            46u,             9u,                        TRUE  },
         };
  
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlLed_Data_AnimaMap_Param2 = &Mt_TestInitData;
    CtrlLed_Force_InvalidCoding  = asTestCaseData[ucIdx].boUT_ForceInvalid;

    //Step 3) Call the FUT
    CtrlLed_Data_AnimaMap_RetVal = CtrlLed_Data_AnimaMap(CtrlLed_Data_AnimaMap_Param1, CtrlLed_Data_AnimaMap_Param2);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlLed_Data_AnimaMap_RetVal,                                     asTestCaseData[ucIdx].boRetCodingStatus, == );
    AL_UNITTEST_CHECK(CtrlLed_Data_AnimaMap_Param2->aucAnimaMap[asTestCaseData[ucIdx].ucLuIdx], asTestCaseData[ucIdx].ucAnimMap, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CurrentUpdates_TestCase1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check that for a known LED driver and valid binning class, the binning 
///        current is chosen correctly from the given binning class
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input   CtrlLed_CurrentUpdates_Param1 = 1u
/// \input   CtrlLed_CurrentUpdates_Param2 = 3u
/// \input   CtrlLed_CurrentUpdates_Param3 = &sTestInternalCoding
/// \input   CtrlLed_CurrentUpdates_RetVal = FALSE
///
///    - Expected test results: 
/// \output   CtrlLed_CurrentUpdates_RetVal = TRUE
/// \output   CtrlLed_CurrentUpdates_Param3->aunBinningCurrent[1u] = 705u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CurrentUpdates_TestCase1(void)
{

  //Step 1) Set pre - conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlLed_CurrentUpdates_Param1 = 1u;
  CtrlLed_CurrentUpdates_Param2 = 3u; 
  CtrlLed_CurrentUpdates_Param3 = &sTestInternalCoding;
  CtrlLed_CurrentUpdates_RetVal = FALSE;

  //Step 3) Call the FUT
  CtrlLed_CurrentUpdates_RetVal = CtrlLed_CurrentUpdates(CtrlLed_CurrentUpdates_Param1, CtrlLed_CurrentUpdates_Param2, CtrlLed_CurrentUpdates_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_CurrentUpdates_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(CtrlLed_CurrentUpdates_Param3->aunBinningCurrent[1u], 705u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CurrentUpdates_TestCase2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check that for a known LED driver and invalid binning class, the binning 
///        class 0 is selected and the current from BC0 is stored (system req)
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
/// \input   CtrlLed_CurrentUpdates_Param1 = 4u
/// \input   CtrlLed_CurrentUpdates_Param2 = CTRLLED_CFG_MAX_BINNING_CLASSES
/// \input   CtrlLed_CurrentUpdates_Param3 = &sTestInternalCoding
/// \input   CtrlLed_CurrentUpdates_RetVal = FALSE
///
///    - Expected test results: 
/// \output   CtrlLed_CurrentUpdates_RetVal = TRUE
/// \output   CtrlLed_CurrentUpdates_Param3->aunBinningCurrent[4u] = 885u
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CurrentUpdates_TestCase2(void)
{

  //Step 1) Set pre - conditions
  tsCtrlled_CodingData sTestInternalCoding = { 0 };

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlLed_CurrentUpdates_Param1 = 4u;
  CtrlLed_CurrentUpdates_Param2 = CTRLLED_CFG_MAX_BINNING_CLASSES;
  CtrlLed_CurrentUpdates_Param3 = &sTestInternalCoding;
  CtrlLed_CurrentUpdates_RetVal = FALSE;

  //Step 3) Call the FUT
  CtrlLed_CurrentUpdates_RetVal = CtrlLed_CurrentUpdates(CtrlLed_CurrentUpdates_Param1, CtrlLed_CurrentUpdates_Param2, CtrlLed_CurrentUpdates_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlLed_CurrentUpdates_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(CtrlLed_CurrentUpdates_Param3->aunBinningCurrent[4u], 885u, == );

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_CurrentUpdates
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test that the binning current is correctly chosen  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_CurrentUpdates(void)
{
  Mt_CtrlLed_CurrentUpdates_TestCase1();
  Mt_CtrlLed_CurrentUpdates_TestCase2();
}


//-----------------------------------------------------------------------------
//  CtrlLed_Diag.c
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_ErrorHandler_TestCase1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Diag_ErrorHandler evaluates
///                     the presence of electrical error and sets the DTC status for
///                     the HSS3 channel
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input CtrlLed_Diag_ErrorHandler_Param1      = 0xFFu
/// \input CtrlLed_Diag_ErrorHandler_Param2      = CTRLLED_CFG_MAX_BUCK_DRV - 1u
/// \input CtrlLed_Diag_ErrorHandler_Param3      = 32700u
/// \input CtrlLed_Diag_ErrorHandler_Param4      = 0u
///
///   - Expectations:
///
/// \output  CtrlLed_Diag_ErrorHandler_RetVal.boSwitchOffBuck[12u] =  FALSE
/// \output  CtrlLed_Diag_ErrorHandler_RetVal.sCtrlLed_ChannelSettings.ulDisable_ErrOpenLoad   = CtrlLed_Diag_ErrorHandler_RetVal.sCtrlLed_ChannelSettings.ulDisable_ErrOpenLoad | (1<<12)
/// \output  CtrlLed_Diag_ErrorHandler_RetVal.sCtrlLed_ChannelSettings.ulDisable_ErrShortToGnd = CtrlLed_Diag_ErrorHandler_RetVal.sCtrlLed_ChannelSettings.ulDisable_ErrShortToGnd | (1<<12)
/// \output  CtrlLed_Diag_ErrorHandler_RetVal.ucLedState[CtrlLed_Diag_ErrorHandler_Param2] = CTRLLED_DIAG_STATUS_OK
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_ErrorHandler_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_Diag_ErrorHandler_Param1      = 0xFFu; //no illuminant assigned for HSS
  CtrlLed_Diag_ErrorHandler_Param2      = CTRLLED_CFG_MAX_BUCK_DRV - 1u; //HSS channel
  Rte_Read_CtrlSwi_Hss3StatusErr_Param1 = (tsRte_Hss3Status){ FALSE, FALSE, FALSE, TRUE };  // no error, HSS enabled
  CtrlLed_Diag_ErrorHandler_Param3      = 32700u;
  CtrlLed_Diag_ErrorHandler_Param4      = 170u;

  //to cover CtrlLed_Diag_DisableError_Cmd
  CtrlLed_Diag_DisableError_Cmd_Param2         = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1 = 9000u;
  CtrlLed_sCodingData.aunBinningCurrent[CtrlLed_Diag_ErrorHandler_Param2] = 250u;

  //Step 3) Call FUT
  CtrlLed_Diag_ErrorHandler_RetVal = CtrlLed_Diag_ErrorHandler(CtrlLed_Diag_ErrorHandler_Param1, CtrlLed_Diag_ErrorHandler_Param2, CtrlLed_Diag_ErrorHandler_Param3, CtrlLed_Diag_ErrorHandler_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_Diag_ErrorHandler_RetVal.boSwitchOffBuck[12u], FALSE, ==);
  AL_UNITTEST_CHECK(CtrlLed_Diag_ErrorHandler_RetVal.sCtrlLed_ChannelSettings.ulDisable_ErrOpenLoad,   (CtrlLed_Diag_ErrorHandler_RetVal.sCtrlLed_ChannelSettings.ulDisable_ErrOpenLoad   | 4096), ==);  //4096 = 1<<12
  AL_UNITTEST_CHECK(CtrlLed_Diag_ErrorHandler_RetVal.sCtrlLed_ChannelSettings.ulDisable_ErrShortToGnd, (CtrlLed_Diag_ErrorHandler_RetVal.sCtrlLed_ChannelSettings.ulDisable_ErrShortToGnd | 4096), ==);  //4096 = 1<<12
  AL_UNITTEST_CHECK(CtrlLed_Diag_ErrorHandler_RetVal.ucLedState[CtrlLed_Diag_ErrorHandler_Param2],                     CTRLLED_DIAG_STATUS_OK, ==);

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_ErrorHandler_TestCase2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Diag_ErrorHandler evaluates
///                     the presence of electrical error and sets the DTC status for
///                     the LED channel (matrix channel)
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input CtrlLed_Diag_ErrorHandler_Param1      = 2u
/// \input CtrlLed_Diag_ErrorHandler_Param2      = 5u
/// \input CtrlLed_Diag_ErrorHandler_Param3      = 32700u
/// \input CtrlLed_Diag_ErrorHandler_Param4      = 15000u
/// \input Rte_Read_SysMon_LedState_Param1.aLedStates[5u]   = CTRLLED_DIAG_STATUS_LED_OFF
/// \input Rte_Read_SysMon_LedState_Param1.boVinBoostOk[5u] = TRUE
/// \input Rte_Read_SysMon_LedState_HitCount  = 0u
/// \input CtrlLed_sInternalHandling.uIlluminantError[CtrlLed_Diag_ErrorHandler_Param1].bIlErr.bMtxVccXSB = 1u
///
///   - Expectations:
///
/// \output  CtrlLed_Diag_ErrorHandler_RetVal.boSwitchOffBuck[5u] =  FALSE
/// \output  Rte_Read_SysMon_LedState_HitCount = 1u
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_ErrorHandler_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlLed_Diag_ErrorHandler_Param1 = 2u;
  CtrlLed_Diag_ErrorHandler_Param2 = 5u; // lED ch. 3
  CtrlLed_Diag_ErrorHandler_Param3 = 32700u;
  CtrlLed_Diag_ErrorHandler_Param4 = 15000u;

  Rte_Read_SysMon_LedState_Param1.aLedStates[5u]    = CTRLLED_DIAG_STATUS_LED_OFF;
  Rte_Read_SysMon_LedState_Param1.boVinBoostOk[5u]  = TRUE;
  Rte_Read_SysMon_LedState_HitCount                 = 0u;
  CtrlLed_sInternalHandling.uIlluminantError[CtrlLed_Diag_ErrorHandler_Param1].bIlErr.bMtxVccXSB = 1u;

  //to cover CtrlLed_Diag_DisableError_Cmd
  CtrlLed_Diag_DisableError_Cmd_Param3                                    = 170u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                            = 9500u;
  CtrlLed_sCodingData.aunBinningCurrent[CtrlLed_Diag_ErrorHandler_Param2] = 250u;
  CtrlLed_sCodingData.aucChannelType[CtrlLed_Diag_ErrorHandler_Param2]    = CTRLLED_CFG_MATRIX_BUCK;

  //Step 3) Call FUT
  CtrlLed_Diag_ErrorHandler_RetVal = CtrlLed_Diag_ErrorHandler(CtrlLed_Diag_ErrorHandler_Param1, CtrlLed_Diag_ErrorHandler_Param2, CtrlLed_Diag_ErrorHandler_Param3, CtrlLed_Diag_ErrorHandler_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlLed_Diag_ErrorHandler_RetVal.boSwitchOffBuck[5u], FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LedState_HitCount,                       1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_ErrorHandler
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test that the Led channels are checked for errors 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_ErrorHandler(void)
{
  Mt_CtrlLed_Diag_ErrorHandler_TestCase1();
  Mt_CtrlLed_Diag_ErrorHandler_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_GetMatrixError
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function evaluates the presence of matrix error
///                     received via RTE and sets them in the internal handling
///                     structure
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucRow         : matrix row
/// \input ucPxlLu       : logical unit for the pxl segment
/// \input ucIlofPxl     : Illuminant assigned for the Logical Unit
/// \input ucMtxFault    : matrix error (communication, pxl defect)
/// \input ucSelFault    : matrix fault selected for failure reaction
/// \input ucReaction    : reaction in case of a specific failure
///
///   - Expectations:
///
/// \output  boPxlFault : matrix pixel fault presence
/// \output  boCorrCom  : matrix corrupt communication fault presence
/// \output  boLossComm : matrix loss of communication fault presence
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_GetMatrixError(void)
{

  //Step 1) Set pre - conditions
  struct {            uint8 ucRow;   uint8 ucPxlLu;  uint8 ucIlofPxl;  uint8 ucMtxFault;        uint8 ucSelFault;       uint8 ucReaction;  boolean boPxlFault; boolean boCorrCom; boolean boLossComm;  } asTestCaseData[]
    = {    {    CTRLLED_MTX_ROW_BTM,          13u,           0xFFu,           0x00u,      CTRLLED_SEL_MAX_PXL_ERR,    CTRLLED_DO_NOTHING,                FALSE,             FALSE,               FALSE },
           {    CTRLLED_MTX_ROW_MID,          35u,             14u,           0x03u,       CTRLLED_SEL_CORUPT_COM,     CTRLLED_SWITCH_ON,                FALSE,              TRUE,               TRUE  },
           {    CTRLLED_MTX_ROW_MID,          35u,             14u,           0x02u,       CTRLLED_SEL_CORUPT_COM,    CTRLLED_SWITCH_OFF,                FALSE,              TRUE,               FALSE },
           {    CTRLLED_MTX_ROW_TOP,          40u,             15u,           0x05u,         CTRLLED_SEL_LOSS_COM,    CTRLLED_DO_NOTHING,                 TRUE,             FALSE,               TRUE  },
           {    CTRLLED_MTX_ROW_TOP,          40u,             15u,           0x01u,         CTRLLED_SEL_LOSS_COM,    CTRLLED_SWITCH_OFF,                FALSE,             FALSE,               TRUE  },
           {    CTRLLED_MTX_ROW_BTM,          60u,           0xFFu,           0x04u,     CTRLLED_SEL_PIXEL_DEFECT,     CTRLLED_SWITCH_ON,                 TRUE,             FALSE,               FALSE },
           {    CTRLLED_MTX_ROW_TOP,          44u,             15u,           0x06u,     CTRLLED_SEL_PIXEL_DEFECT,    CTRLLED_SWITCH_OFF,                 TRUE,              TRUE,               FALSE }, //Loss Comm set previously
  };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    CtrlLed_pfInternalHandling()->ucMatrixRowLightBitPrv = 7u; //all matrix rows active

    // reset errors for each test case -> reason: make independent tests
    for (uint8 ucRowSel = 0u; ucRowSel < CTRLLED_MAX_MTX_COL_SEL; ucRowSel++)
    {
      for (uint8 ucErrSel = 0u; ucErrSel < CTRLLED_SEL_MAX_PXL_ERR; ucErrSel++)
      {
        CtrlLed_sInternalHandling.sRowMtxErr[ucRowSel].boErrPresent[ucErrSel] = FALSE;
      }
    }

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlLed_GetMatrixError_Param1 = asTestCaseData[ucIdx].ucRow;
    CtrlLed_GetMatrixError_Param2 = asTestCaseData[ucIdx].ucPxlLu;
    CtrlLed_GetMatrixError_Param3 = asTestCaseData[ucIdx].ucIlofPxl;
    Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[CtrlLed_GetMatrixError_Param2].ucRaw = asTestCaseData[ucIdx].ucMtxFault;
    asReactionPxl_List[asTestCaseData[ucIdx].ucSelFault] = asTestCaseData[ucIdx].ucReaction;

    //Step 3) Call the FUT
    CtrlLed_GetMatrixError_RetVal = CtrlLed_GetMatrixError(CtrlLed_GetMatrixError_Param1, CtrlLed_GetMatrixError_Param2, CtrlLed_GetMatrixError_Param3);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[0], asTestCaseData[ucIdx].boPxlFault,     == );
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[1], asTestCaseData[ucIdx].boCorrCom,      == );
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[2], asTestCaseData[ucIdx].boLossComm,     == );
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].ucIlluminantAssigned, asTestCaseData[ucIdx].ucIlofPxl, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_HandleMatrixDtc
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function evaluates the presence of matrix error
///                     and takes an action for setting/clearing the corresponding DTC
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucMtxPrvLight      : matrix previous light active
/// \input ucMtxActLight      : matrix actual light active
/// \input ucRow              : matrix row
/// \input boRowErr_Act       : actual matrix error on row
/// \input boRowErr_Prv       : previous matrix error on row
/// \input ucIlofPxl          : Illuminant assigned for the pixel segment on that row
///
///   - Expectations:
///
/// \output  boPxlFault : matrix pixel fault presence
/// \output  boCorrCom  : matrix corrupt communication fault presence
/// \output  boLossComm : matrix loss of communication fault presence
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_HandleMatrixDtc(void)
{
  
  struct { uint8 ucMtxPrvLight; uint8 ucMtxActLight;      uint8 ucRow;   boolean boRowErr_Act; boolean boRowErr_Prv; uint8 ucIlofPxl; boolean boPxlFault; boolean boCorrCom; boolean boLossComm; } asTestCaseData[]
    = {    {      0x00u,                0x00u,    CTRLLED_MTX_ROW_BTM,                 FALSE,                FALSE,           0xFFu,               FALSE,             FALSE,               FALSE },
           {      0x04u,                0x04u,    CTRLLED_MTX_ROW_TOP,                 FALSE,                 TRUE,             15u,                TRUE,             FALSE,               TRUE  },  // CTRLLED_SET_DTC 
           {      0x04u,                0x04u,    CTRLLED_MTX_ROW_TOP,                 FALSE,                FALSE,             15u,                TRUE,             FALSE,               TRUE  },
           {      0x04u,                0x02u,    CTRLLED_MTX_ROW_MID,                 FALSE,                 TRUE,             14u,                TRUE,             FALSE,               TRUE  },  // CTRLLED_NO_DTC_ACTION
           {      0x00u,                0x01u,    CTRLLED_MTX_ROW_BTM,                 FALSE,                 TRUE,             13u,               FALSE,             FALSE,              FALSE },   // CTRLLED_RESETSET_DTC
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[0] = asTestCaseData[ucIdx].boPxlFault;
    CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[1] = asTestCaseData[ucIdx].boCorrCom; 
    CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[2] = asTestCaseData[ucIdx].boLossComm;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlLed_pfInternalHandling()->ucMatrixRowLightBitPrv = asTestCaseData[ucIdx].ucMtxPrvLight;
    CtrlLed_pfInternalHandling()->ucMatrixRowLightBit    = asTestCaseData[ucIdx].ucMtxActLight;
    CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boRowErr_Act          = asTestCaseData[ucIdx].boRowErr_Act;
    CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boRowErr_Prv          = asTestCaseData[ucIdx].boRowErr_Prv;
    CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].ucIlluminantAssigned  = asTestCaseData[ucIdx].ucIlofPxl;

    //Step 3) Call the FUT
    CtrlLed_HandleMatrixDtc();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[0], asTestCaseData[ucIdx].boPxlFault , == );
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[1], asTestCaseData[ucIdx].boCorrCom ,  == );
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[2], asTestCaseData[ucIdx].boLossComm , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_SetResetMtxDtc
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function evaluates the presence of matrix error
///                     and takes an action for setting/clearing the corresponding DTC
///                     on the MATRIX ROW ACTIVE. Also, resets the DTC for all rows
///                     when a failure is detected on matix MID (reason: matrix MID
///                     has pixels that are assigne don matrix TOP also)
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucMtxPrvLight      : matrix previous light active
/// \input ucMtxActLight      : matrix actual light active
/// \input ucRow              : matrix row
/// \input boRowErr_Act       : actual matrix error on row
/// \input boRowErr_Prv       : previous matrix error on row
/// \input ucIlofPxl          : Illuminant assigned for the pixel segment on that row
///
///   - Expectations:
///
/// \output  boPxlFault : matrix pixel fault presence
/// \output  boCorrCom  : matrix corrupt communication fault presence
/// \output  boLossComm : matrix loss of communication fault presence
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_SetResetMtxDtc(void)
{
  //Step 1) Set pre - conditions
  Dem_SetEventStatus_Param1 = 0xFFu;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;

  struct { uint8 ucMtxRowLight;          uint8 ucRow;  boolean boDtcStatus;  boolean boPxlFault; boolean boCorrCom; boolean boLossComm;     uint16 ucDtcCode;        uint8 ucDtcStatus; } asTestCaseData[]
    = {    {           0x00u,    CTRLLED_MTX_ROW_BTM,                FALSE,               FALSE,             FALSE,             FALSE ,                0xFFu,   DEM_EVENT_STATUS_PASSED },  // CTRLLED_NO_DTC_ACTION
           {           0x04u,    CTRLLED_MTX_ROW_TOP,                 TRUE,                TRUE,             FALSE,             FALSE ,              HB_1ROW,   DEM_EVENT_STATUS_FAILED },   //       CTRLLED_SET_DTC
           {           0x04u,    CTRLLED_MTX_ROW_TOP,                FALSE,                TRUE,             FALSE,             FALSE ,              HB_1ROW,   DEM_EVENT_STATUS_PASSED },   //  CTRLLED_RESETSET_DTC
           {           0x02u,    CTRLLED_MTX_ROW_MID,                 TRUE,               FALSE,              TRUE,             FALSE ,      LMM_LB_CRPT_COM,   DEM_EVENT_STATUS_FAILED },   //       CTRLLED_SET_DTC
           {           0x02u,    CTRLLED_MTX_ROW_MID,                FALSE,               FALSE,              TRUE,             FALSE ,      LMM_HB_CRPT_COM,   DEM_EVENT_STATUS_PASSED },   // keep with error because it's previous state and it gets reset. DTC is HB because it resets all rows for MID
           {           0x01u,    CTRLLED_MTX_ROW_BTM,                 TRUE,                TRUE,              TRUE,              TRUE ,       LMM_LB_LOS_COM,   DEM_EVENT_STATUS_FAILED },   //       CTRLLED_SET_DTC
           {           0x00u,    CTRLLED_MTX_ROW_BTM,                 TRUE,               FALSE,             FALSE,              TRUE ,       LMM_LB_LOS_COM,   DEM_EVENT_STATUS_FAILED },   //       CTRLLED_SET_DTC
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[0] = asTestCaseData[ucIdx].boPxlFault;
    CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[1] = asTestCaseData[ucIdx].boCorrCom; 
    CtrlLed_pfInternalHandling()->sRowMtxErr[asTestCaseData[ucIdx].ucRow].boErrPresent[2] = asTestCaseData[ucIdx].boLossComm;
    CtrlLed_pfInternalHandling()->ucMatrixRowLightBit = asTestCaseData[ucIdx].ucMtxRowLight;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlLed_SetResetMtxDtc_Param1 = asTestCaseData[ucIdx].boDtcStatus;
    CtrlLed_SetResetMtxDtc_Param2 = asTestCaseData[ucIdx].ucRow;

    //Step 3) Call the FUT
    CtrlLed_SetResetMtxDtc(CtrlLed_SetResetMtxDtc_Param1, CtrlLed_SetResetMtxDtc_Param2);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, asTestCaseData[ucIdx].ucDtcCode, == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, asTestCaseData[ucIdx].ucDtcStatus, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_SetMtxDtc
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function sets the DTC status for the given
///                     matrix error and the correct code
///
///    - Test Design Technique: DT (Decision Table)
///
///  \DT-Info:
///
///   - Inputs:
///       ucRow        : matrix row active
///       ucErr        : matrix error type
///       boHbStatus   : HB distribution ON
///
///   - Expectations:
///       ucDtcStatus       : DTC status
///       ucDtcCode         : DTC code
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_SetMtxDtc(void)
{
  struct { uint8 ucRow;                       uint8 ucErr; boolean boHbStatus;      uint8 ucDtcStatus; ;       uint16 ucDtcCode; } asTestCaseData[]
    = { {  CTRLLED_MTX_ROW_MID,  CTRLLED_SEL_PIXEL_DEFECT,              FALSE,     DEM_EVENT_STATUS_FAILED ,            LB_2ROW  },
        {  CTRLLED_MTX_ROW_MID,      CTRLLED_SEL_LOSS_COM,               TRUE,     DEM_EVENT_STATUS_FAILED ,     LMM_HB_LOS_COM  },
        {  CTRLLED_MTX_ROW_BTM,    CTRLLED_SEL_CORUPT_COM,              FALSE,     DEM_EVENT_STATUS_FAILED ,     LMM_LB_CRPT_COM },
        {  CTRLLED_MTX_ROW_TOP,      CTRLLED_SEL_LOSS_COM,               TRUE,     DEM_EVENT_STATUS_FAILED ,     LMM_HB_LOS_COM  },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    Dem_SetEventStatus_Param1 = 0xFFu;
    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED;

    //Step 2) Assign Input values
    CtrlLed_SetMtxDtc_Param1 = asTestCaseData[ucIdx].ucRow;
    CtrlLed_SetMtxDtc_Param2 = asTestCaseData[ucIdx].ucErr;
    CtrlLed_SetMtxDtc_Param3 = asTestCaseData[ucIdx].boHbStatus;

    //Step 3) Call FUT
    CtrlLed_SetMtxDtc(CtrlLed_SetMtxDtc_Param1, CtrlLed_SetMtxDtc_Param2, CtrlLed_SetMtxDtc_Param3);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, asTestCaseData[ucIdx].ucDtcCode,   == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, asTestCaseData[ucIdx].ucDtcStatus, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_ResetMtxDtc
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function resets the DTC status for the given
///                     matrix error and removes the error from the internal handling
///
///    - Test Design Technique: DT (Decision Table)
///
///  \DT-Info:
///
///   - Inputs:
///       ucRow        : matrix row active
///       ucErr        : matrix error type
///
///   - Expectations:
///       ucDtcStatus        : DTC status
///       boMtxError         : return status for error detection
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_ResetMtxDtc(void)
{
  struct    { uint8 ucRow;                      uint8 ucErr;         uint8 ucDtcStatus;  boolean boError; } asTestCaseData[]
    = {     {  CTRLLED_MTX_ROW_MID,  CTRLLED_SEL_PIXEL_DEFECT,  DEM_EVENT_STATUS_PASSED,          FALSE  },
            {  CTRLLED_MTX_ROW_BTM,    CTRLLED_SEL_CORUPT_COM,  DEM_EVENT_STATUS_PASSED,          FALSE  },
            {  CTRLLED_MTX_ROW_TOP,      CTRLLED_SEL_LOSS_COM,  DEM_EVENT_STATUS_PASSED,          FALSE  },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED;

    //Step 2) Assign Input values
    CtrlLed_ResetMtxDtc_Param1 = asTestCaseData[ucIdx].ucRow;
    CtrlLed_ResetMtxDtc_Param2 = asTestCaseData[ucIdx].ucErr;

    //Step 3) Call FUT
    CtrlLed_ResetMtxDtc(CtrlLed_ResetMtxDtc_Param1, CtrlLed_ResetMtxDtc_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, asTestCaseData[ucIdx].ucDtcStatus, == );
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->sRowMtxErr[CtrlLed_ResetMtxDtc_Param1].boErrPresent[CtrlLed_ResetMtxDtc_Param2], asTestCaseData[ucIdx].boError, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_ChReacBuckErr
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Diag_ChReacBuckErr evaluates
///                     the presence of electrical error and for the reaction for the
///                     error and returns true if reaction is needed, otherwise it return false
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucIlluminant : Illuminant index
/// \input ucChannel    : channel name
/// \input unError      : electrical error
/// \input boNewLghtReq : new light request
///
///   - Expectations:
///
/// \output  boSwitchOff : Reaction status
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_ChReacBuckErr(void)
{
  CtrlLed_CreateCodingData_FULLVariant();
  struct { uint8 ucIlluminant;      uint8 ucChannel;     uint16 unError;                           boolean boNewLghtReq;  boolean boSwitchOff; }asTestCaseData[]
    =    { {               3u,                3u,         CTRLLED_DIAG_STATUS_OK            /*    0u*/,           FALSE,               FALSE   },
           {              10u,                6u,         CTRLLED_DIAG_ERR_ID_UNKNOWN       /* 0x40u*/,           FALSE,               FALSE   }, //special case for unknown LED channel
           {              13u,                4u,         CTRLLED_DIAG_ERR_OVER_CURRENT     /* 0x40u*/,           FALSE,                TRUE   }, //overcurrent error -> switch off
           {              14u,                11u,        CTRLLED_DIAG_ERR_VOLTAGE_LOW      /* 0x08u*/,           FALSE,               FALSE   }, //voltage low -> no reaction
           {              14u,                11u,        CTRLLED_DIAG_ERR_THERM_SHUT_DOWN  /* 0x20u*/,            TRUE,               FALSE   }, //thermal shutdown -> error present prev.  + new Light request to remove error
           {              14u,                11u,        CTRLLED_DIAG_ERR_THERM_SHUT_DOWN  /* 0x20u*/,           FALSE,               FALSE   }, //thermal shutdown -> change reaction to CTRLLED_SWITCH_ON 
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
   CtrlLed_Diag_ChReacBuckErr_Param1 = asTestCaseData[ucIdx].ucIlluminant;
   CtrlLed_Diag_ChReacBuckErr_Param2 = asTestCaseData[ucIdx].ucChannel;  
   CtrlLed_Diag_ChReacBuckErr_Param3 = asTestCaseData[ucIdx].boNewLghtReq;
   CtrlLed_Diag_ChReacBuckErr_Param4 = asTestCaseData[ucIdx].unError;
  
   if (ucIdx == 5u)   // matrix illuminant
   {
     asReaction_List[13u].ucReaction[5u] = CTRLLED_SWITCH_ON;   // 13u- PXL channel (Ill 14), 5u - thermal shutdown error position
   }

   //Step 3) Call FUT
   CtrlLed_Diag_ChReacBuckErr_RetVal = CtrlLed_Diag_ChReacBuckErr(CtrlLed_Diag_ChReacBuckErr_Param1, CtrlLed_Diag_ChReacBuckErr_Param2, CtrlLed_Diag_ChReacBuckErr_Param3, CtrlLed_Diag_ChReacBuckErr_Param4);
  
   //Step 4) Check expected output values
   AL_UNITTEST_CHECK(CtrlLed_Diag_ChReacBuckErr_RetVal, asTestCaseData[ucIdx].boSwitchOff, == );
  
  }

  //restore value to not affect other UT
  CtrlLed_pfInternalHandling()->ucMatrixRowLightBit = 0x00u; 
  asReaction_List[13u].ucReaction[5u] = CTRLLED_SWITCH_OFF;

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_HandleChannelErrors
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_HandleChannelErrors handles
///                     the action of set/reset DTC status based on the error
///                     received which is evaluated considering the previous error
///                     status and the new light request status
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucIl           : Illuminant index
/// \input ucChannel      : LED channel LF assigned 
/// \input ucErrStatus    : diagnosis of LED channel (received error)
/// \input ucMtxErr       : matrix previous error status
/// \input boNewReq       : request of ON-> OFF
/// \input ucForceReset   : UT manipulation to force reset for double check of set/reset DTC conditions
///
///   - Expectations:
///
/// \output  unDtcEvent   : LF associated DTC 
/// \output  ucDtcStatus  : DTC status
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_HandleChannelErrors(void)
{

  //Step 1) Set pre - conditions
  Dem_SetEventStatus_Param1 = 0x1F4u;  // no DTC set
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;
  CtrlLed_pfInternalHandling()->ucMatrixRowLightBit = 0x04u;

  struct { uint8 ucIl;                uint8 ucChannel;               uint8 ucErrStatus; uint8 ucMtxErr; boolean boNewReq;  uint8 ucForceReset; uint16 unDtcEvent;           uint8 ucDtcStatus; }asTestCaseData[]
       = {
           {      14u,  3u /* PXL - matrix channel */,          CTRLLED_DIAG_STATUS_OK,          0x00u,        FALSE,                0x00u,          0x1F4u,     DEM_EVENT_STATUS_PASSED  },  // no channel error 
           {      15u,  5u /* PXL - matrix channel */,          CTRLLED_DIAG_STATUS_OK,          0x00u,        FALSE,                0x00u,          0x1F4u,     DEM_EVENT_STATUS_PASSED  },  // HB illuminant with no channel error , no error on KINK and HB Illuminants
           {      15u,  5u /* PXL - matrix channel */,          CTRLLED_DIAG_STATUS_OK,          0x01u,        FALSE,                0x00u,      HB_OL_LMMx,     DEM_EVENT_STATUS_FAILED  },  // HB illuminant with no channel error , but previous error on KINK Illuminant
           {      3u,   7u /* DRL/POS channel */     ,   CTRLLED_DIAG_ERR_SHORT_TO_BAT,          0x00u,        FALSE,                0x00u,    Drl_E_SC_BAT,     DEM_EVENT_STATUS_FAILED  },  // error on DRL channel  -> CTRLLED_SET_DTC
           {      3u,   7u /* DRL/POS channel */     ,          CTRLLED_DIAG_STATUS_OK,          0x00u,         TRUE,                0x00u,    Drl_E_SC_BAT,     DEM_EVENT_STATUS_PASSED  },  // error recovered on  DRL channel + NL req. -> CTRLLED_RESETSET_DTC  (reset previous state due to New Light request)
           {      4u,   8u /* DRL/POS channel */     ,   CTRLLED_DIAG_ERR_SHORT_TO_BAT,          0x00u,         TRUE,                0x00u,    Drl_E_SC_BAT,     DEM_EVENT_STATUS_FAILED  },  // error on DRL channel  -> CTRLLED_SET_DTC
           {      4u,   8u /* DRL/POS channel */     ,   CTRLLED_DIAG_ERR_SHORT_TO_GND,          0x00u,         TRUE,                0xAAu,    Drl_E_SC_BAT,     DEM_EVENT_STATUS_FAILED  },  // new error on DRL channel, force invalid conditions (Set DTC + Status OK), DTC status remains unchanged
           {      4u,   8u /* DRL/POS channel */     ,   CTRLLED_DIAG_ERR_VOLTAGE_HIGH,          0x00u,         TRUE,                0x55u,    Drl_E_SC_BAT,     DEM_EVENT_STATUS_FAILED  },  // new error on DRL channel, force invalid conditions (Reset DTC + Status ERR), DTC status remains unchanged
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlLed_HandleChannelErrors_Param1 = asTestCaseData[ucIdx].ucIl;
    CtrlLed_HandleChannelErrors_Param2 = asTestCaseData[ucIdx].ucChannel;
    CtrlLed_HandleChannelErrors_Param3 = asTestCaseData[ucIdx].ucErrStatus;
    CtrlLed_HandleChannelErrors_Param4 = asTestCaseData[ucIdx].boNewReq;
    CtrlLed_ForceReset = asTestCaseData[ucIdx].ucForceReset;

    //special handling for customer request
    CtrlLed_pfInternalHandling()->uIlluminantError[CTRLLED_ILLUMINANT_KINK].unRaw = asTestCaseData[ucIdx].ucMtxErr;

    //Step 3) Call the FUT
    CtrlLed_HandleChannelErrors(CtrlLed_HandleChannelErrors_Param1, CtrlLed_HandleChannelErrors_Param2, CtrlLed_HandleChannelErrors_Param3, CtrlLed_HandleChannelErrors_Param4);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, asTestCaseData[ucIdx].unDtcEvent,  == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, asTestCaseData[ucIdx].ucDtcStatus, == );

  }

  //restore value to not influence other test acses
  CtrlLed_pfInternalHandling()->ucMatrixRowLightBit = 0x00u;
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_ReportDtc
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_ReportDtc evaluates
///                     the presence of electrical error and sets or resets the corresponding
///                     DTC for the current matrix/LED channel 
///
///    - Test Design Technique: DT( Decision Table )
///
/// - Preconditions:
///
/// \input DTC action, Channel electrical error and channel function to assign corresponding DTC
/// \input ucDtcAction        : DTC action status
/// \input ucIlluminant       : illuminant index
/// \input ucChannel          : LED channel assigned to the given illuminant
/// \input unTestPrevError    :  error status detected in the previous cycle
/// \input unTestActualError  :  error detected in the current cycle
///
///   - Expectations:
///
/// \output  unDTC       : DTC code to be set
/// \output  ucDTCstatus : DTC status to be set
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_ReportDtc(void)
{
  //Step 1) Set pre-conditions
  Mt_InternalCodingMapping();
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;


  struct {      uint8 ucDtcAction;  uint8 ucIlluminant;       uint8 ucChannel;         uint16 unTestPrevError[CFG_LED_CHANNELS_NR];         uint16 unTestActualError[CFG_LED_CHANNELS_NR];    uint16 unDTC;         uint8 ucDTCstatus;   }asTestCaseData[]
    = {  {   CTRLLED_RESETSET_DTC,                   2u,   3u /*SBL channel */,  { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },             0u,     DEM_EVENT_STATUS_PASSED  }, //unknown LED channel assignment
         {   CTRLLED_RESETSET_DTC,                   2u,   3u /*SBL channel */,  { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },             0u,     DEM_EVENT_STATUS_PASSED  }, // SBL channel
         {        CTRLLED_SET_DTC,                  14u,   6u /*PXL channel */,  { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    { 0u, 0u, 0u, 0u, 0u, 0u, 0x40u, 0u, 0u, 0u, 0u, 0u },  LB_OC_LMMx,     DEM_EVENT_STATUS_FAILED  }, // matrix channel -  0x40 = over current error
         {        CTRLLED_SET_DTC,                  14u,   6u /*PXL channel */,  { 0u, 0u, 0u, 0u, 0u, 0u, 0x10u, 0u, 0u, 0u, 0u, 0u }, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },     LB_OC_LMMx,     DEM_EVENT_STATUS_FAILED  }, // matrix channel -  0x10 = voltage high (DTC_NOT_USED) prev. error
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    CtrlLed_sCodingData.ucLedName[3u] = (ucIdx == 0u) ? 0u/*CTRLLED_CFG_UNKNOWN_UINT8_VALUE*/ : 13u;  /* reset value: CL - Cornering Light */

    //Step 2) Assign Input values
    CtrlLed_ReportDtc_Param1 =  asTestCaseData[ucIdx].ucDtcAction;
    CtrlLed_ReportDtc_Param2 = &asTestCaseData[ucIdx].unTestPrevError[0];
    CtrlLed_ReportDtc_Param3 =  asTestCaseData[ucIdx].ucIlluminant;
    CtrlLed_ReportDtc_Param4 =  asTestCaseData[ucIdx].ucChannel;
    CtrlLed_ReportDtc_Param5 = &asTestCaseData[ucIdx].unTestActualError[0];

    //Step 3) Call FUT
    CtrlLed_ReportDtc(CtrlLed_ReportDtc_Param1, CtrlLed_ReportDtc_Param2, CtrlLed_ReportDtc_Param3, CtrlLed_ReportDtc_Param4, CtrlLed_ReportDtc_Param5);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, asTestCaseData[ucIdx].unDTC,        == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, asTestCaseData[ucIdx].ucDTCstatus,  == );

  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_CountErrorBitPos
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_HandleChannelErrors handles
///                     the action of set/reset DTC status based on the error
///                     received which is evaluated considering the previous error
///                     status and the new light request status
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input unReceivedError    : diagnosis of LED channel (received error)
///
///   - Expectations:
///
/// \output  ucErrorPosition   : error position calculated to set the correct dtc for the detected error
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_CountErrorBitPos(void)
{

  struct {               uint16 unReceivedError;              uint8 ucErrorPosition; }asTestCaseData[]
      =  { {                                0u,     CTRLLED_CFG_UNKNOWN_UINT8_VALUE  },   // no error received
           {  CTRLLED_DIAG_ERR_THERM_SHUT_DOWN,                                  1u  },   // (1010 & 0010 = 0010 != 0u -> count = 1)
           {                            0x1000u,                                 0u  },   // exceed ucBitPos condition -> count will not save bit pos
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
     //Step 1) Set pre - conditions
     //Step 2) Assign all input values to the corresponding input variables identified in the FUT
     CtrlLed_Diag_CountErrorBitPos_Param1 = asTestCaseData[ucIdx].unReceivedError;
     
     //Step 3) Call the FUT
     CtrlLed_Diag_CountErrorBitPos_RetVal = CtrlLed_Diag_CountErrorBitPos(CtrlLed_Diag_CountErrorBitPos_Param1);

     //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
     AL_UNITTEST_CHECK(CtrlLed_Diag_CountErrorBitPos_RetVal, asTestCaseData[ucIdx].ucErrorPosition, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_SetChannelDtc
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Diag_SetChannelDtc evaluates
///                     the presence of electrical error and sets the corresponding
///                     DTC (light function active) for the matrix/LED channel with error
///
///    - Test Design Technique: DT( Decision Table )
///
/// - Preconditions:
///
/// \input ucChannel          : LED channel assigned to the given illuminant
/// \input ucElectricalError  : error detected in the current cycle
/// \input ucMtxRowLight      : controlled matrix row
///
///   - Expectations:
///
/// \output  unDTC       : DTC code to be set
/// \output  ucDTCstatus : DTC status to be set
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_SetChannelDtc(void)
{

 struct { uint8 ucChannel;               uint8 ucElectricalError;     uint8 ucMtxRowLight;          uint16 unDTC;             uint8 ucDTCStatus;   } asTestCaseData[]
    = { {   3u /* DRL/POS channel*/,         6u /* over-current*/,                0x00u,      Drl_E_OV_CURRENT,       DEM_EVENT_STATUS_FAILED   },
        {  13u /* PXL_LB  channel*/,         2u /* short to Vbat*/,               0x04u,             HB_SC_BAT,       DEM_EVENT_STATUS_FAILED   },
        {  13u /* PXL_LB  channel*/,         2u /* short to Vbat*/,               0x02u,        LB_SC_BAT_LMMx,       DEM_EVENT_STATUS_FAILED   },
        {  14u /* PXL_HB  channel*/,         1u /* short to GND */,               0x01u,                    0u,       DEM_EVENT_STATUS_PASSED   },
     };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    Dem_SetEventStatus_Param1 = 0u;
    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;

    //Step 2) Assign Input values
    CtrlLed_Diag_SetChannelDtc_Param1                 = asTestCaseData[ucIdx].ucChannel;
    CtrlLed_Diag_SetChannelDtc_Param2                 = asTestCaseData[ucIdx].ucElectricalError;
    CtrlLed_pfInternalHandling()->ucMatrixRowLightBit = asTestCaseData[ucIdx].ucMtxRowLight;

    //Step 3) Call FUT
    CtrlLed_Diag_SetChannelDtc(CtrlLed_Diag_SetChannelDtc_Param1, CtrlLed_Diag_SetChannelDtc_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, asTestCaseData[ucIdx].unDTC,       == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, asTestCaseData[ucIdx].ucDTCStatus, == );

  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_ResetDtc_TestCase1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Diag_ResetDtc evaluates
///                     the presence of electrical error previously set on a given channel
///                     and resets the DTC status if the errors was healed
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input CtrlLed_Diag_ResetDtc_Param1 = 3u
/// \input CtrlLed_Diag_ResetDtc_Param2 = &unTestInit[0]
/// \input CtrlLed_Diag_ResetDtc_Param3 = 3u
/// \input CtrlLed_Diag_ResetDtc_Param4 = 2u
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_Param1 = 0u
/// \output Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_ResetDtc_TestCase1(void)
{
  //Step 1) Set pre-conditions
  uint16 unTestInit[CFG_LED_CHANNELS_NR] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
  Dem_SetEventStatus_Param1              = 0u;
  Dem_SetEventStatus_Param2              = DEM_EVENT_STATUS_PASSED;

  //Step 2) Assign Input values
  CtrlLed_Diag_ResetDtc_Param1 = 3u;             // Function: DRL/POS channel 
  CtrlLed_Diag_ResetDtc_Param2 = &unTestInit[0]; // no ellectrical errors on LED channels
  CtrlLed_Diag_ResetDtc_Param3 = 3u;             // illuminant 4
  CtrlLed_Diag_ResetDtc_Param4 = 2u;             // LED channel

  //Step 3) Call FUT
  CtrlLed_Diag_ResetDtc(CtrlLed_Diag_ResetDtc_Param1, CtrlLed_Diag_ResetDtc_Param2, CtrlLed_Diag_ResetDtc_Param3, CtrlLed_Diag_ResetDtc_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, 0u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_ResetDtc_TestCase2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Diag_ResetDtc evaluates
///                     the presence of electrical error previously set on a given channel
///                     and sets the DTC status as passed becaue the error was healed 
///                     from previous checking
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input CtrlLed_Diag_ResetDtc_Param1 = 14u
/// \input CtrlLed_Diag_ResetDtc_Param2 = &unTestInit[0]
/// \input CtrlLed_Diag_ResetDtc_Param3 = 3u
/// \input CtrlLed_Diag_ResetDtc_Param4 = 2u
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_Param1 = SPI_Bus2_E_DEFECT
/// \output Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_ResetDtc_TestCase2(void)
{
  //Step 1) Set pre-conditions
  uint16 unTestInit[CFG_LED_CHANNELS_NR] = { 0u, 0u, 0x82u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
  
  //Step 2) Assign Input values
  CtrlLed_Diag_ResetDtc_Param1 = 14u;            // Function: PXL_HB channel   
  CtrlLed_Diag_ResetDtc_Param2 = &unTestInit[0]; // error : SHORT_TO_GND & SPI on LED channel 2
  CtrlLed_Diag_ResetDtc_Param3 = 3u;             // illuminant 4
  CtrlLed_Diag_ResetDtc_Param4 = 2u;             // LED channel

  //Step 3) Call FUT
  CtrlLed_Diag_ResetDtc(CtrlLed_Diag_ResetDtc_Param1, CtrlLed_Diag_ResetDtc_Param2, CtrlLed_Diag_ResetDtc_Param3, CtrlLed_Diag_ResetDtc_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, SPI_Bus2_E_DEFECT, ==);
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, ==);

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_ResetDtc_TestCase3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Diag_ResetDtc evaluates
///                     the presence of electrical error previously set on a given channel.
///                     It checks if the matrix illuminant for LB (KINK Illuminant) has an error 
///                     and KINK row has a failure, then restore DTC for HB illuminant also
///                     Reason: kink row has pixels also distributed on HB row
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input CtrlLed_Diag_ResetDtc_Param1 = CTRLLED_CH_NAME_PXL_LB
/// \input CtrlLed_Diag_ResetDtc_Param2 = &unTestInit[0]
/// \input CtrlLed_Diag_ResetDtc_Param3 = CTRLLED_ILLUMINANT_KINK
/// \input CtrlLed_Diag_ResetDtc_Param4 = 5u
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_Param1 = HB_SC_BAT
/// \output Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_ResetDtc_TestCase3(void)
{
  //Step 1) Set pre-conditions
  uint16 unTestInit[CFG_LED_CHANNELS_NR] = { 0u, 0u, 0u, 0u, 0u, 0x04u, 0u, 0u, 0u, 0u, 0u, 0u }; //;short to Vbat

  CtrlLed_pfInternalHandling()->uIlluminantError[CTRLLED_ILLUMINANT_KINK].unRaw = 0x04u; //short to Vbat
  //Step 2) Assign Input values
  CtrlLed_Diag_ResetDtc_Param1 = CTRLLED_CH_NAME_PXL_LB;            // Function: PXL_LB channel   
  CtrlLed_Diag_ResetDtc_Param2 = &unTestInit[0];                    // error : SHORT_TO_GND & SPI on LED channel 2
  CtrlLed_Diag_ResetDtc_Param3 = CTRLLED_ILLUMINANT_KINK;           // illuminant 15 = LB
  CtrlLed_Diag_ResetDtc_Param4 = 5u;                                // matrix channel

  //Step 3) Call FUT
  CtrlLed_Diag_ResetDtc(CtrlLed_Diag_ResetDtc_Param1, CtrlLed_Diag_ResetDtc_Param2, CtrlLed_Diag_ResetDtc_Param3, CtrlLed_Diag_ResetDtc_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,               HB_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_ResetDtc
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Test that DTC status is reset for healed error
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_ResetDtc(void)
{
  Mt_CtrlLed_Diag_ResetDtc_TestCase1();
  Mt_CtrlLed_Diag_ResetDtc_TestCase2();
  Mt_CtrlLed_Diag_ResetDtc_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_GetHss3DiagStatus
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:   Check that the function stores the diagnosis HSS status 
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
///  \DT-Info:
///
///   - Inputs:
///       sHss3Status : HSS status received via RTE
///
///   - Expectations:
///       ucError : error status remaped by the module
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_GetHss3DiagStatus(void)
{

  //Step 1) Set pre - conditions
  uint8 Mt_DataInit = 0u;
  CtrlLed_GetHss3DiagStatus_Param1 = &Mt_DataInit;

    struct { tsRte_Hss3Status  sHss3Status;                      uint8 ucError;    } asTestCaseData[]
    = {    { { FALSE,  TRUE, FALSE, FALSE },       CTRLLED_DIAG_ERR_OPEN_LOAD      },
           { { FALSE, FALSE,  TRUE, FALSE },       CTRLLED_DIAG_ERR_SHORT_TO_BAT   },
           { {  TRUE, FALSE, FALSE, FALSE },       CTRLLED_DIAG_ERR_SHORT_TO_GND   },
           {                      { 0x00u },       CTRLLED_DIAG_STATUS_LED_OFF     },
           { { FALSE, FALSE, FALSE,  TRUE },       CTRLLED_DIAG_STATUS_OK          },  //Hss Enabled, no error
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_CtrlSwi_Hss3StatusErr_Param1  = asTestCaseData[ucIdx].sHss3Status; 
    
    //Step 3) Call the FUT
    CtrlLed_GetHss3DiagStatus(CtrlLed_GetHss3DiagStatus_Param1);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(*CtrlLed_GetHss3DiagStatus_Param1, asTestCaseData[ucIdx].ucError, ==);
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlLed_Diag_MtxVccx_Eeprom
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function CtrlLed_Diag_MtxVccx_Eeprom receives the 
///                     Vccx Matrix error status and eeprom error status via RTE and 
///                     reports the corresponding DTC status and sets correctly the 
///                     illuminant error status 
///
///    - Test Design Technique: DT (Decision Table)
///
///  \DT-Info:
///
///   - Inputs:
///       boVccxGnd_Fault        : matrix supply Vccx Sh2Gnd error status
///       boVccxBat_Fault        : matrix supply Vccx Sh2Gnd error status
///       sEepromFault           : matrix supply Vccx Sh2Gnd error status
///       ucIlluminant           : illuminant index
///       boMtxIlluminant        : illuminant type (matrix/non-matrix)
///
///   - Expectations:
///       ucDtcStatus        : DTC status
///       unMtxVccXSGbit     : matrix supply Vccx Sh2Gnd error status set on bit on logical unit
///       unMtxVccXSBbit     : matrix supply Vccx Sh2Gnd error status set on bit on logical unit
///       unMtxEEprombit     : matrix eeprom error (no access / wrong checksum)  status set on bit on logical unit
///       boMtxError         : return status for error detection
///
//-----------------------------------------------------------------------------
void Mt_CtrlLed_Diag_MtxVccx_Eeprom(void)
{
  struct { boolean boVccxGnd_Fault;  boolean boVccxBat_Fault;   tsRte_MtxEeprom_ErrStatus sEepromFault;  uint8 ucIlluminant;  boolean boMtxIlluminant;        uint8 ucDtcStatus;   uint16 unMtxVccXSGbit;  uint16 unMtxVccXSBbit; uint16 unMtxEEprombit; boolean boMtxError;  } asTestCaseData[]
    = { {                   FALSE,                     FALSE,                                  {0u, 0u},                  2u,                  FALSE,    DEM_EVENT_STATUS_PASSED,                    0U,                      0u,                    0u,               FALSE },
        {                    TRUE,                     FALSE,                                  {1u, 0u},                 14u,                   TRUE,    DEM_EVENT_STATUS_PASSED,                    1U,                      0u,                    1u,                TRUE },
        {                   FALSE,                     TRUE,                                   {0u, 1u},                 15u,                   TRUE,    DEM_EVENT_STATUS_FAILED,                    0U,                      1u,                    1u,                TRUE },
        {                   FALSE,                     TRUE,                                   {0u, 0u},                 15u,                   TRUE,    DEM_EVENT_STATUS_PASSED,                    0U,                      1u,                    0u,                TRUE },
      };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    // 1) Vccx errors
    CtrlLed_pfInternalHandling()->uIlluminantError[asTestCaseData[ucIdx].ucIlluminant].bIlErr.bMtxVccXSG = FALSE;
    CtrlLed_pfInternalHandling()->uIlluminantError[asTestCaseData[ucIdx].ucIlluminant].bIlErr.bMtxVccXSB = FALSE;
    Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError   = FALSE;
    Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError  = FALSE;
    Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_HitCount                   = 0u;
    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;

    // 2) eeprom errors
    Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFault   = FALSE;
    Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromWrngChksumFault = FALSE;
    CtrlLed_pfInternalHandling()->uIlluminantError[asTestCaseData[ucIdx].ucIlluminant].bIlErr.bMtxEeprom = FALSE;


    //Step 2) Assign Input values
    Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError       = asTestCaseData[ucIdx].boVccxGnd_Fault;
    Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError      = asTestCaseData[ucIdx].boVccxBat_Fault;
    CtrlLed_pfCodingData()->aboIlMtxType[asTestCaseData[ucIdx].ucIlluminant]  = asTestCaseData[ucIdx].boMtxIlluminant;
    Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1                             = asTestCaseData[ucIdx].sEepromFault;

     
    //Step 3) Call FUT
    CtrlLed_Diag_MtxVccx_Eeprom_RetVal = CtrlLed_Diag_MtxVccx_Eeprom();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlLed_Diag_MtxVccx_Eeprom_RetVal,             asTestCaseData[ucIdx].boMtxError,  == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,                      asTestCaseData[ucIdx].ucDtcStatus, == );
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->uIlluminantError[asTestCaseData[ucIdx].ucIlluminant].bIlErr.bMtxVccXSG, asTestCaseData[ucIdx].unMtxVccXSGbit, == );
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->uIlluminantError[asTestCaseData[ucIdx].ucIlluminant].bIlErr.bMtxVccXSB, asTestCaseData[ucIdx].unMtxVccXSBbit, == );
    AL_UNITTEST_CHECK(CtrlLed_pfInternalHandling()->uIlluminantError[asTestCaseData[ucIdx].ucIlluminant].bIlErr.bMtxEeprom, asTestCaseData[ucIdx].unMtxEEprombit, == );

  }
}



//-----------------------------------------------------------------------------
//  ctaaCtrlLed.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCtrlLed_Init
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the initialization runnable calls and executes
///                     the init function of CtrlLed
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Coding data assigned to CtrlLed are valid (eCodingState =  CodingDataValid)
///
///   - Expectations:
///
/// \output RTE read ports are called. Ensure that LED current (0A) and duty (0 PWM) are 
///         sent via RTE in the init phase to keep LEDs OFF
///
//-----------------------------------------------------------------------------
void Mt_riCtrlLed_Init(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_CodM_CtrlLed_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CtrlLed_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_CtrlLed_Para_HitCount                         = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount                = 0u;
  Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount                   = 0u;
  Anima_Init_HitCount = 0u;

  //Step 2) Assign Input values
  Rte_Write_CtrlLed_TgtLedSig_sVal_Param1->unCurrent   = 1500u;   /*request of LED turn ON -> shall not be accepted*/
  Rte_Write_CtrlLed_TgtLedSig_sVal_Param1->unDutyCycle = 4500u;

  //Step 3) Call FUT
  riCtrlLed_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlLed_Para_HitCount,              1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Anima_Init_HitCount,                              1u, == );

  //ensure LEDs are OFF
  for (uint8 ucLedIdx = 0u; ucLedIdx < (CTRLLED_CFG_LED_CHANNELS_NR - 1u); ucLedIdx++)
  {
    AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_Param1[ucLedIdx].unCurrent,    0u, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_Param1[ucLedIdx].unDutyCycle,  0u, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCtrlLed_Cycle0
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls and executes
///                     the cycle function of CtrlLed according to the
///                     defined cycle time = 5ms:
///                      a) even count -> Animation call
///                      a) odd count  -> CtrLed call
///
///    - Test Design Technique: DT (Decision Table)
///
///  \DT-Info:
///
///   - Inputs:
///       ucCycleTime       : time slot of the cycle call of the function
///
///   - Expectations:
///       ucAnimationCnt     : count of animation routine (even cycles)
///       ucCtrlLedCnt       : count of CtrlLed routine   (odd  cycles)
///
//-----------------------------------------------------------------------------
void Mt_rpCtrlLed_Cycle0(void)
{
  //Step 1) Set pre-conditions
  CtrlLed_boCodMap_OK = TRUE;   // as a consequence of Rte_Read_CodM_CtrlLed_Para_Param1.eCodingState  = eParaFct0_CodingDataValid;
  Anima_Cycle10_HitCount                    = 0u;   //no call of AnimaCycle
  Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount = 0u;   //no call of CtrlLed cycle

  struct { uint8 ucCycleTime;  uint8 ucAnimationCnt;    uint8 ucCtrlLedCnt; } asTestCaseData[]
       = { {              0u,                    1u,                    0u  }, 
           {              1u,                    1u,                    1u  },
           {              2u,                    2u,                    1u  },
           {              3u,                    2u,                    1u  },
           {              4u,                    3u,                    1u  },
           {              5u,                    3u,                    2u  },
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    /* no input value, the idea is to ensure the correct timing call*/
    /* ucCycleTime is the time slot of the cycle call of the function  =  "virtual" call*/

    //Step 3) Call FUT
    rpCtrlLed_Cycle0();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Anima_Cycle10_HitCount,                  asTestCaseData[ucIdx].ucAnimationCnt, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount, asTestCaseData[ucIdx].ucCtrlLedCnt, == );
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

  CtrlLed_CreateCodingData_FULLVariant();    // coding data assigned ; pre-condition for all test cases to have the coding structure initialized

  /* CtrlLed_Rte.c*/
  ALUnitTest_AddFunction("Mt_CtrlLed_Rte_Get_BinningClass",                   Mt_CtrlLed_Rte_Get_BinningClass);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Read_Vbat",                    Mt_CtrlLed_RteAccess_Read_Vbat);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Get_EcuSide",                  Mt_CtrlLed_RteAccess_Get_EcuSide);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Get_ECU_Side",                 Mt_CtrlLed_RteAccess_Get_ECU_Side);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Get_CodingPara",               Mt_CtrlLed_RteAccess_Get_CodingPara);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Get_ChannelState",             Mt_CtrlLed_RteAccess_Get_ChannelState);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Set_ChannelSettings",          Mt_CtrlLed_RteAccess_Set_ChannelSettings);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Set_IlluminantsStatus",        Mt_CtrlLed_RteAccess_Set_IlluminantsStatus);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Get_MatrixLuErrors",           Mt_CtrlLed_RteAccess_Get_MatrixLuErrors);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Get_MatrixVccxErrors",         Mt_CtrlLed_RteAccess_Get_MatrixVccxErrors);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Get_DD01_Diag_Status",         Mt_CtrlLed_RteAccess_Get_DD01_Diag_Status);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_VoltageRange",                 Mt_CtrlLed_RteAccess_VoltageRange);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Get_MatrixSystemMode",         Mt_CtrlLed_RteAccess_Get_MatrixSystemMode);
  ALUnitTest_AddFunction("Mt_CtrlLed_Rte_ReadTgtBinningVal",                  Mt_CtrlLed_Rte_ReadTgtBinningVal);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Get_HSS3_Status",              Mt_CtrlLed_RteAccess_Get_HSS3_Status);
  ALUnitTest_AddFunction("Mt_CtrlLed_RteAccess_Set_HSS3_Duty",                Mt_CtrlLed_RteAccess_Set_HSS3_Duty);

  /* CtrlLed.c*/
  ALUnitTest_AddFunction("Mt_CtrlLed_Init",                                   Mt_CtrlLed_Init);
  ALUnitTest_AddFunction("Mt_CtrlLed_Cycle0",                                 Mt_CtrlLed_Cycle0);
  ALUnitTest_AddFunction("Mt_CtrlLed_Buck_Handling",                          Mt_CtrlLed_Buck_Handling);
  ALUnitTest_AddFunction("Mt_CtrlLed_MatrixVoltCond",                         Mt_CtrlLed_MatrixVoltCond);
  ALUnitTest_AddFunction("Mt_CtrlLed_Matrix_Handling",                        Mt_CtrlLed_Matrix_Handling);
  ALUnitTest_AddFunction("Mt_CtrlLed_CheckLight",                             Mt_CtrlLed_CheckLight);
  ALUnitTest_AddFunction("Mt_CtrlLed_Handle_MatrixCh",                        Mt_CtrlLed_Handle_MatrixCh);
  ALUnitTest_AddFunction("Mt_CtrlLed_CalcRamp",                               Mt_CtrlLed_CalcRamp);
  ALUnitTest_AddFunction("Mt_CtrlLed_GammaCurve",                             Mt_CtrlLed_GammaCurve);
  //ALUnitTest_AddFunction("Mt_CtrlLed_CountSetBucks",                         Mt_CtrlLed_CountSetBucks);       /* tested inside Buck_Handling */
  //ALUnitTest_AddFunction("Mt_CtrlLed_GetBuckId",                             Mt_CtrlLed_GetBuckId);           /* tested inside Buck_Handling */
  //ALUnitTest_AddFunction("Mt_CtrlLed_Handle_NonMatrixCh",                    Mt_CtrlLed_Handle_NonMatrixCh);  /* tested inside Buck_Handling */
  ALUnitTest_AddFunction("Mt_CtrlLed_CurrentCalculation",                     Mt_CtrlLed_CurrentCalculation);
  ALUnitTest_AddFunction("Mt_CtrlLed_DutyCalculation",                        Mt_CtrlLed_DutyCalculation);

  /* CtrlLed_Data.c*/
  ALUnitTest_AddFunction("Mt_CtrlLed_CodingDataValidation",                   Mt_CtrlLed_CodingDataValidation);
  ALUnitTest_AddFunction("Mt_CtrlLed_ParaFct0",                               Mt_CtrlLed_ParaFct0);
  ALUnitTest_AddFunction("Mt_CtrlLed_CodMap",                                 Mt_CtrlLed_CodMap);
  ALUnitTest_AddFunction("Mt_CtrlLed_Data_DriverMap",                         Mt_CtrlLed_Data_DriverMap);
  ALUnitTest_AddFunction("Mt_CtrlLed_Data_Matrix",                            Mt_CtrlLed_Data_Matrix);
  ALUnitTest_AddFunction("Mt_CtrlLed_Data_Led1",                              Mt_CtrlLed_Data_Led1);
  ALUnitTest_AddFunction("Mt_CtrlLed_Data_LmmX",                              Mt_CtrlLed_Data_LmmX);
  ALUnitTest_AddFunction("Mt_CtrlLed_Data_Get_UnitGroup",                     Mt_CtrlLed_Data_Get_UnitGroup);
  ALUnitTest_AddFunction("Mt_CtrlLed_Data_Process_SingleUnits",               Mt_CtrlLed_Data_Process_SingleUnits);
  //ALUnitTest_AddFunction("Mt_CtrlLed_Data_Process_MultiUnits",                Mt_CtrlLed_Data_Process_MultiUnits);  /* tested inside CtrlLed_Data_DriverMap*/
  ALUnitTest_AddFunction("Mt_CtrlLed_Data_AnimaMap",                          Mt_CtrlLed_Data_AnimaMap);
  ALUnitTest_AddFunction("Mt_CtrlLed_CurrentUpdates",                         Mt_CtrlLed_CurrentUpdates);

  /* CtrlLed_Diag.c*/
  ALUnitTest_AddFunction("Mt_CtrlLed_Diag_ErrorHandler",                      Mt_CtrlLed_Diag_ErrorHandler);
  ALUnitTest_AddFunction("Mt_CtrlLed_GetMatrixError",                         Mt_CtrlLed_GetMatrixError);
  ALUnitTest_AddFunction("Mt_CtrlLed_HandleMatrixDtc",                        Mt_CtrlLed_HandleMatrixDtc);
  ALUnitTest_AddFunction("Mt_CtrlLed_SetResetMtxDtc",                         Mt_CtrlLed_SetResetMtxDtc);
  ALUnitTest_AddFunction("Mt_CtrlLed_SetMtxDtc",                              Mt_CtrlLed_SetMtxDtc);
  ALUnitTest_AddFunction("Mt_CtrlLed_ResetMtxDtc",                            Mt_CtrlLed_ResetMtxDtc);
  ALUnitTest_AddFunction("Mt_CtrlLed_Diag_ChReacBuckErr",                     Mt_CtrlLed_Diag_ChReacBuckErr);
  ALUnitTest_AddFunction("Mt_CtrlLed_HandleChannelErrors",                    Mt_CtrlLed_HandleChannelErrors);
  ALUnitTest_AddFunction("Mt_CtrlLed_ReportDtc",                              Mt_CtrlLed_ReportDtc);
  ALUnitTest_AddFunction("Mt_CtrlLed_Diag_CountErrorBitPos",                  Mt_CtrlLed_Diag_CountErrorBitPos);
  ALUnitTest_AddFunction("Mt_CtrlLed_Diag_SetChannelDtc",                     Mt_CtrlLed_Diag_SetChannelDtc);
  ALUnitTest_AddFunction("Mt_CtrlLed_Diag_ResetDtc",                          Mt_CtrlLed_Diag_ResetDtc);
  ALUnitTest_AddFunction("Mt_CtrlLed_GetHss3DiagStatus",                      Mt_CtrlLed_GetHss3DiagStatus);
  ALUnitTest_AddFunction("Mt_CtrlLed_Diag_MtxVccx_Eeprom",                    Mt_CtrlLed_Diag_MtxVccx_Eeprom);


  /* ctaaCtrlLed.c*/
  ALUnitTest_AddFunction("Mt_riCtrlLed_Init",                                 Mt_riCtrlLed_Init);
  ALUnitTest_AddFunction("Mt_rpCtrlLed_Cycle0",                               Mt_rpCtrlLed_Cycle0);

}