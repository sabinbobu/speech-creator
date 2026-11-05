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
/// \file  ErrCust.c
///
/// \brief  DTC handling
///
/// \descr  
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <UtilUtility.h>
#include <Nvm.h>
#include <ErrCust.h>
//#include <EcuM.h>
//#include <Bsw/IoHwAb/IoHwAbUser.h>
#include "ErrCust_RteAccess.h"

#ifndef UNIT_TEST
#include <Rte.h>
#else 
#include <RteCommonTypes.h>
#endif // UNIT_TEST

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------
// DTCAgingCounter is set to maximum value
#define ERRCUST_DTC_AGING_COUNTER_MAX             40u
// Confiugartion for clearing all group of DTCs
#define ERRCUST_ALL_GROUP_OF_DTCS                 0xFFFFFFu
// This the youngest age for freeze frame data, it means that the corresponding Dtc is the last one which occured
#define ERRCUST_YOUNGEST_AGE_FFD                  1u

//Lower limit for stp angle(degree)
#define ERRCUST_MIN_ACCEPTED_ANGLE                -120
//Upper limit for stp angle(degree)
#define ERRCUST_MAX_ACCEPTED_ANGLE                120
//Stp Angle resolution (0.05 degree)  
#define ERRCUST_ANNGLE_REZ                        5
//Voltage Rezolution (from mv to 0.1 V Rezolution) 
#define ERRCUST_01_VOLTAGE_REZOLUTION             100u 
//Maximum Accepted Voltage(V in 0.1 Rezolution)
#define ERRCUST_MAX_ACCEPTED_VOLTAGE_V            255u
//Maximum Accepted Voltage(mV)
#define ERRCUST_MAX_ACCEPTED_VOLTAGE_MV           ERRCUST_MAX_ACCEPTED_VOLTAGE_V * ERRCUST_01_VOLTAGE_REZOLUTION

// Vehicle Speed Resolution (from km/h to 0.01 km/h Resolution) 
#define ERRCUST_SPEED_RESOLUTION                  100u 
// Maximum Accepted Vehicle Speed(km/h)
#define ERRCUST_MAX_ACCEPTED_VOLTAGE_KMPH         255u
//Maximum Accepted Voltage(mV)
#define ERRCUST_MAX_ACCEPTED_SPEED_KMPH           ERRCUST_MAX_ACCEPTED_VOLTAGE_KMPH * ERRCUST_SPEED_RESOLUTION

#define ERRCUST_32_BIT_MASK                       0xFFFFFFFFu    // 32 Bit Mask

// Instantaneous value of front/rear left or front/rear body high sensor
#define ERRCUST_MAX_VALUE_DID_D4C8            (250u)
#define ERRCUST_RESOLUTION_DID_D4C8           (65536u)

// Flags for setting the status when a dtc test failed
#define ERRCUST_TEST_FAILED_SET_FLAGS                                    (ERRCUST_STATUS_TEST_FAILED | ERRCUST_STATUS_TEST_FAILED_THIS_CYCLE | ERRCUST_STATUS_TEST_FAILED_SINCE_CLEAR | ERRCUST_STATUS_PENDING_DTC | ERRCUST_STATUS_CONFIRMED_DTC)
// Flags for clearing the status when a dtc test failed
#define ERRCUST_TEST_FAILED_CLEAR_FLAGS                                  (ERRCUST_STATUS_TEST_PASSED | ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR | ERRCUST_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE)
// Flags for setting the status when a dtc test failed for nvm block
#define ERRCUST_TEST_FAILED_SET_FLAGS_NVM                                (ERRCUST_STATUS_TEST_FAILED_THIS_CYCLE | ERRCUST_STATUS_TEST_FAILED_SINCE_CLEAR)
// Flags for setting the status when a dtc test passed
#define ERRCUST_TEST_PASSED_CLEAR_FLAGS                                  (ERRCUST_STATUS_TEST_FAILED | ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR | ERRCUST_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE)

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
//STATIC_AL void ErrCust_ClearErrCustAndDemEventIds(uint8 ucPsError, uint32 ulDTCCode);
STATIC_AL void                   ErrCust_ClearAllErrCustAndDemEventIds(void);
STATIC_AL void                   ErrCust_MapDtc(teErrCust_IxPsError* peRefList);
STATIC_AL void                   ErrCust_CaptureFreezeFrameData(uint8 ucPsError);
STATIC_AL teErrCust_Types_Clear  ErrCust_ucGetClearMemoryType(uint32 ulDtcCode);
STATIC_AL void                   ErrCust_ClearFreezeFrameData(uint8 ucFreezeFrameIdx);
STATIC_AL uint8                  ErrCust_EvaluateVehicleSpeed(tsRte_SysMon_VehicleSpeed sInputSig);
STATIC_AL boolean                ErrCust_CodingDataValidation(void);
STATIC_AL boolean                ErrCust_Data_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
STATIC_AL uint8                  ErrCust_Get_NTC(uint8_fast ucIdx);
STATIC_AL Std_ReturnType         ErrCust_ReadNtcVal(tsRte_NTCTemperature* sNtcVal);
STATIC_AL uint8                  ErrCust_Get_BinningClass(uint8_fast ucIdx);
STATIC_AL Std_ReturnType         ErrCust_ReadTgtBinningVal(uint8_fast ucIdx, tsRte_Binning0* sTgtBinningVal);
STATIC_AL uint8                  ErrCust_GetNTCBinningErrorPerChannel(uint8_fast ucIdx, tsErrCust_RbinFailLightFunc sRBINNTCFail);

#ifdef UNIT_TEST
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_00(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_01(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_02(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_03(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_04(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_05(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_06(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_07(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_08(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_09(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_10(tsRte_Binning0* ppara1);
extern Std_ReturnType Rte_Read_RSens_BinningClass_sVal_11(tsRte_Binning0* ppara1);
#endif

// Array of function pointers to read Binning Class value
STATIC_AL Std_ReturnType(*ErrCust_apfnReadTgtBinningClass_sVal_List[ERRCUST_NO_OF_LED_CHANNELS]) (tsRte_Binning0* psTgtBinningVal) =
{
  Rte_Read_RSens_BinningClass_sVal_00,
  Rte_Read_RSens_BinningClass_sVal_01,
  Rte_Read_RSens_BinningClass_sVal_02,
  Rte_Read_RSens_BinningClass_sVal_03,
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  Rte_Read_RSens_BinningClass_sVal_04,
  Rte_Read_RSens_BinningClass_sVal_05,
  Rte_Read_RSens_BinningClass_sVal_06,
  Rte_Read_RSens_BinningClass_sVal_07,
  Rte_Read_RSens_BinningClass_sVal_08,
  Rte_Read_RSens_BinningClass_sVal_09,
  Rte_Read_RSens_BinningClass_sVal_10,
  Rte_Read_RSens_BinningClass_sVal_11,
#endif
};

//-----------------------------------------------------------------------------
// Static Variables
//-----------------------------------------------------------------------------
// Global array which contains at each index(ALEC ID) the corresponding DTC code
STATIC_AL teErrCust_IxPsError ErrCust_aPsRefList[DEM_MAX_EVENT_ID + 1u];

// A global array for keeping the actual Ps error status
STATIC_AL uint8 ErrCust_aucStatus[ERRCUST_NUMBER_OF_DTCS];

// Global flag which indicate which headlamp is used
STATIC_AL boolean ErrCust_boLeft = FALSE;

// Global variable which is used to read DTCs
STATIC_AL uint8 ErrCust_ucDtcIndex = 0u;

// Global variables which are used to do a new NvM Write
STATIC_AL boolean ErrCust_boNvmDirtyErrCust         = FALSE;
STATIC_AL boolean ErrCust_boNvmDirtyFreezeFrameData = FALSE;

// Pointer to coding area
CONST_AL  tNvmPara_CodingArea* ErrCust_pCodingArea       = NULL_PTR;
STATIC_AL boolean              ErrCust_boCodingValidity  = FALSE;


// build the ErrCust_PsDtcs table
//lint -e451 Header file 'xxx.h' repeatedly included but does not have a standard include guard
#define ERRCUST_CONFIG_DEF
#include "ErrCust_Cfg.h"
#undef  ERRCUST_CONFIG_DEF
//lint +e451 Header file 'xxx.h' repeatedly included but does not have a standard include guard


//-----------------------------------------------------------------------------
/// \brief  ErrCust_MapDtc
///
/// \descr  Map each DEM event id(ALEC ID) to the coresponding DTC code
///         There is a relationship: 1(DTC) to many(ALEC)
///
/// \param   peRefList
///
/// \return  void 
//-----------------------------------------------------------------------------

STATIC_AL void ErrCust_MapDtc(teErrCust_IxPsError* peRefList)
{
  // Init all errors to 0
  for (uint16 unIdx = 0u; unIdx < DEM_MAX_EVENT_ID + 1u; unIdx++)
  {
    peRefList[unIdx] = ERRCUST_IxPsError_NONE;
  }

  //Map customer errors to DEM event IDs here
  //lint -e451 Header file 'xxx.h' repeatedly included but does not have a standard include guard
#define ERRCUST_CONFIG_ASSIGN
#include "ErrCust_Cfg.h"
#undef  ERRCUST_CONFIG_ASSIGN
//lint +e451 Header file 'xxx.h' repeatedly included but does not have a standard include guard
//PRQA S 5330, 5344 1//STST3 = 232 exceeds threshold 50 for Number of statements in function -> there is no possibility to decrease number of statements, STXLN = 232' Number of Executable Lines >200 -> there is no possibility to decrease number of executable lines
}

//-----------------------------------------------------------------------------
/// \brief  ErrCust_Init
///
/// \descr  Initialisation of Ps error status at system boot
///
/// \param   void
///
/// \return  void 
//-----------------------------------------------------------------------------
void ErrCust_Init(void)
{
  // HeadLamp side
  teRte_MountingSide eMountingSide = { 0 };

  // Map each ALEC ID to the corresponding DTC code
  ErrCust_MapDtc((teErrCust_IxPsError*)(&ErrCust_aPsRefList[0]));

  // Read MountingSide RTE port
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  // Detect which headlamp is used
  ErrCust_boLeft = (eMountingSide == eMountedLeft) ? TRUE : FALSE;

  for (uint8 ucDtcIdx = 0u; ucDtcIdx < ERRCUST_NUMBER_OF_DTCS; ucDtcIdx++)
  {
    //At the beginning of a new opeartion cycle the status of each DTC is 'testNoCompletedThisCycle'
    ErrCust_aucStatus[ucDtcIdx] = ERRCUST_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE;

    // process NVM
    if (( (NvmBlockErrCustPs.aucErrStatus[ucDtcIdx] & ERRCUST_STATUS_TEST_FAILED_THIS_CYCLE) == 0u ) && (NvmBlockErrCustPs.aucAgingCounter[ucDtcIdx] > 0u))
    {
      // The DTC Aging Counter decrements after completing an operation cycle in which test did not fail and if aging counter hasn't reached 0 yet
      NvmBlockErrCustPs.aucAgingCounter[ucDtcIdx]--;

      // Store logged Ps error data in NvM
      ErrCust_boNvmDirtyErrCust = TRUE;
    }
    else
    {
      //Aging counter is 0 or the DTC test passed in the last operation cycle
    }

    //Check if there has passed 40 operation cycle with the DTC test passed
    if ( NvmBlockErrCustPs.aucAgingCounter[ucDtcIdx] > 0u)
    {
      //It has not passed 40 operation cycle in which the DTC test passed, therefore the DTC status can be confirmed, all information linked to DTC has to be stored in Nvm yet
      ErrCust_aucStatus[ucDtcIdx] |= ERRCUST_STATUS_CONFIRMED_DTC;

      //Check if the DTC test failed in the last operation cycle
      if ( (NvmBlockErrCustPs.aucErrStatus[ucDtcIdx] & ERRCUST_STATUS_TEST_FAILED_THIS_CYCLE) != 0u)
      {
        //The DTC test failed in the last operation cycle, therefore 'ERRCUST_STATUS_PENDING_DTC' is needed to be set
        ErrCust_aucStatus[ucDtcIdx] = ErrCust_aucStatus[ucDtcIdx] | ERRCUST_STATUS_PENDING_DTC;

        //The DTC test failed in the last operation cycle, this is the beginning of a new operation cycle(initialization phase), therefore reset the bit beacuse the test hasn't failed at this point
        NvmBlockErrCustPs.aucErrStatus[ucDtcIdx] = NvmBlockErrCustPs.aucErrStatus[ucDtcIdx] & (uint8)(~ERRCUST_STATUS_TEST_FAILED_THIS_CYCLE);

        // Store logged Ps error data in NvM
        ErrCust_boNvmDirtyErrCust = TRUE;
      }
      else
      {
        //The DTC test passed in the last operation cycle, therefore nothing to do
      }
    }
    else
    {
      //Aging counter reaches the 0 value, therefore nothing to do
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureFreezeFrameData
///
/// \descr  Stores the actual captured freeze frame data and environmental conditions
///
/// \param   ucPsError - DTC index
///
/// \return  void 
//-----------------------------------------------------------------------------
STATIC_AL void ErrCust_CaptureFreezeFrameData(uint8 ucPsError)
{
  // Aftermarket RBIN/NTC Failure data
  tsErrCust_AftermarketRbinNtcFailureData  sRbinNtcFailEcuData = { 0u };
  // Aftermarket RBIN EEPROM LMM data
  tsErrCust_AftermarketRbinEepromLmmData   sRbinEepromLmmEcuData = { 0u };
  // Aftermarket LED Channel Output data
  tsErrCust_AftermarketLedChnlOutData      sLedOutputEcuData = { 0u };
  // Aftermarket ATTITUDE ECU data
  tsErrCust_AftermarketAttitudeEcuData     sAttitudeEcuData = { 0 };
  // Aftermarket LVL ECU data
  tsErrCust_AftermarketLvlEcuData          sLvlEcuData = { 0u };
  // Aftermarket CONTEXT ECU data
  tsErrCust_AftermarketContextEcuData      sContextEcuData = { 0u };
  // Variables used as indexes
  uint8 ucFreezeFrmIdx = 0u;
  uint8 ucDtcIdx = 0u;
  uint8 ucIdx = 0u;
  // Local variable which is used to signalize that an available place for storing a FFD was found
  boolean boAvailable = FALSE;

  // Search for the postion for the new FFD to be stored
  for (ucIdx = 0u; ucIdx < ERRCUST_FREEZE_FRAME_DATA_ENTRIES; ucIdx++)
  {
    // Check if current entry is available for storage
    if ((NvmBlockFreezeFrameDataPs.aucAge[ucIdx] == ERRCUST_MIN_AGE) && (boAvailable == FALSE))
    {
      // Signalize that current value for 'ucIdx' is available for storing FFD
      boAvailable = TRUE;
      // Save the current value of 'ucIdx'
      ucFreezeFrmIdx = ucIdx;
    }
    // Check if its age has the maximum possible value (10) for 'ucIdx'
    else if( (NvmBlockFreezeFrameDataPs.aucAge[ucIdx] == ERRCUST_MAX_AGE) && (boAvailable == FALSE))
    {
      // Get the dtc index corresponding with current freeze frame index
      ucDtcIdx = NvmBlockFreezeFrameDataPs.aucDtcId[ucIdx];
      // From FFD structure mark Dtc as available
      NvmBlockFreezeFrameDataPs.aucDtcId[ucIdx] = ERRCUST_DTC_AVAILABLE_FOR_FFD;
      // The oldest DTC was found, therefore this is marked as available
      NvmBlockErrCustPs.aucErrFreezeFrameIndex[ucDtcIdx] = ERRCUST_DTC_AVAILABLE_FOR_FFD;
      
      // Signalize that current value for 'ucIdx' is available for storing FFD
      boAvailable = TRUE;
      // Oldest freeze frame idx with age of 10 found, save the current value of 'ucIdx'
      ucFreezeFrmIdx = ucIdx;
    }
    // Check if the age is ready to be increased
    else if(NvmBlockFreezeFrameDataPs.aucAge[ucIdx] != ERRCUST_MIN_AGE)
    {
      // Increase the age 
      NvmBlockFreezeFrameDataPs.aucAge[ucIdx]++;
    }
    else
    {
      // In all other cases there is no action to be performed
    }
  }

  // Link the freeze frame data with the id of the current Dtc
  NvmBlockFreezeFrameDataPs.aucDtcId[ucFreezeFrmIdx] = ucPsError;
  // Set the age of the actual entry to 1 (the youngest one) for the current freeze frame
  NvmBlockFreezeFrameDataPs.aucAge[ucFreezeFrmIdx] = ERRCUST_YOUNGEST_AGE_FFD;

  // Set the index of the new FFD entry for the current Dtc
  NvmBlockErrCustPs.aucErrFreezeFrameIndex[ucPsError] = ucFreezeFrmIdx;

  // Store logged Ps error data in NvM
  ErrCust_boNvmDirtyErrCust = TRUE;

  // Capture RBIN/NTC Failure data (0xD420)
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData(&sRbinNtcFailEcuData);
  // Capture RBIN EEPROM LMM data (0xD421)
  ErrCust_CaptureAftermarketRbinEepromLmmEcuData(&sRbinEepromLmmEcuData);
  // Capture LED Channel Output data (0xD422)
  ErrCust_CaptureAftermarketLedOutputFailEcuData(&sLedOutputEcuData);
  // Capture ATTITUDE ECU data (0xD4C9)
  ErrCust_CaptureAftermarketAttitudeEcuData(&sAttitudeEcuData);
  // Capture LVL ECU data (0xD4CB)
  ErrCust_CaptureAftermarketLvlEcuData(&sLvlEcuData);
  // Capture CONTEXT ECU data (0xE88)
  ErrCust_CaptureAftermarketContextEcuData(&sContextEcuData);

  // Fill NvmBlockFreezeFrameDataPs
  NvmBlockFreezeFrameDataPs.aucRbinNtcErrPerLightFunc         [ucFreezeFrmIdx]  = sRbinNtcFailEcuData.ucErrPerLightFunc;
  NvmBlockFreezeFrameDataPs.aucRbinEepromLmmFirstByte         [ucFreezeFrmIdx]  = sRbinEepromLmmEcuData.ucFirstByte;
  NvmBlockFreezeFrameDataPs.aucRbinEepromLmmSecondByte        [ucFreezeFrmIdx]  = sRbinEepromLmmEcuData.ucSecondByte;
  NvmBlockFreezeFrameDataPs.aucRbinEepromLmmThirdByte         [ucFreezeFrmIdx]  = sRbinEepromLmmEcuData.ucThirdByte;
  NvmBlockFreezeFrameDataPs.aucRbinEepromLmmFourthByte        [ucFreezeFrmIdx]  = sRbinEepromLmmEcuData.ucFourthByte;
  NvmBlockFreezeFrameDataPs.aucRbinEepromLmmFifthByte         [ucFreezeFrmIdx]  = sRbinEepromLmmEcuData.ucFifthByte;
  NvmBlockFreezeFrameDataPs.aucLedChnlOutFirstByte            [ucFreezeFrmIdx]  = sLedOutputEcuData.ucFirstErrorByte;
  NvmBlockFreezeFrameDataPs.aucLedChnlOutSecondByte           [ucFreezeFrmIdx]  = sLedOutputEcuData.ucSecondErrorByte;
  NvmBlockFreezeFrameDataPs.asnOFFSET_CALIB_VEHICLE_ATTITUDE  [ucFreezeFrmIdx]  = sAttitudeEcuData.snOffsetCalibVehicleAttitude;
  NvmBlockFreezeFrameDataPs.asnINST_VAL_VEHICULE_ATTITUDE     [ucFreezeFrmIdx]  = sAttitudeEcuData.snInstValVehiculeAttitude;
  NvmBlockFreezeFrameDataPs.ascINSTANT_LVL_POS                [ucFreezeFrmIdx]  = sLvlEcuData.scInstantLvlPos;
  NvmBlockFreezeFrameDataPs.aucLVL_INFO                       [ucFreezeFrmIdx]  = sLvlEcuData.ucLvlInfo;
  NvmBlockFreezeFrameDataPs.aucVOLTAGE_TERMINAL_DTC           [ucFreezeFrmIdx]  = sContextEcuData.ucVoltageTerminal;
  NvmBlockFreezeFrameDataPs.aucETAT_INFO_DTC                  [ucFreezeFrmIdx]  = sContextEcuData.ucEtatInfo;
  NvmBlockFreezeFrameDataPs.VEHICLE_SPEED_DTC                 [ucFreezeFrmIdx]  = sContextEcuData.ucVehicleSpeed;
  NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC                   [ucFreezeFrmIdx]  = sContextEcuData.ulKilometrage;
  NvmBlockFreezeFrameDataPs.INST_VAL_FL_BODY_HIGH_SENSOR_DTC  [ucFreezeFrmIdx]  = sContextEcuData.ucInstVal_FL_Bhs;
  NvmBlockFreezeFrameDataPs.INST_VAL_RL_BODY_HIGH_SENSOR_DTC  [ucFreezeFrmIdx]  = sContextEcuData.ucInstVal_RL_Bhs;

  // Store freeze frame information
  ErrCust_boNvmDirtyFreezeFrameData = TRUE;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketRbinNtcFailureEcuData
///
/// \descr  Stores aftermarket RBIN NTC Failure ECU data
///
/// \param   psOutputData   buffer to store data
///
/// \return  void 
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketRbinNtcFailureEcuData(tsErrCust_AftermarketRbinNtcFailureData* psOutputData)
{
  // Structure used for RBIN/NTC failure per light function
  tsErrCust_RbinFailLightFunc sRBIN_NTCFailLightFunc = { 0u };
  // Variable used to store ECU side
  teErrCust_Types_MountingSide eEcuSide;
  // Variable used to get RBIN/NTC error per light function
  uint8 ucErrPerLightFunc = 0u;
  // Pointers used to access logical units
  uint8 *pucLUnit_Hl = NULL_PTR, *pucLUnit_Hl_LR = NULL_PTR;

  // Check coding validity
  if (ErrCust_boCodingValidity != FALSE)
  {
    // Get Ecu Side
    ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(&eEcuSide);

    // Check ECU Side
    if (eEcuSide == eLeft)
    {
      // Take the Maping List Calibration Address (LEFT)
      //PRQA S 310, 311 1 // Cast under control
      pucLUnit_Hl_LR = (uint8*)&ErrCust_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping;

    }
    else
    {
      // Take the Maping List Calibration Address (right)
      //PRQA S 310, 311 1 // Cast under control
      pucLUnit_Hl_LR = (uint8*)&ErrCust_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping;
    }

    // Get RBIN/NTC error
    for (uint8 ucIdx = 0u; ucIdx < ERRCUST_NO_OF_LED_CHANNELS; ucIdx++)
    {
      // Init address
      pucLUnit_Hl = pucLUnit_Hl_LR;
      // Check all logical unit
      for (uint8_least ucLogicalUnit = 0u; ucLogicalUnit < ERRCUST_LU_NR; ucLogicalUnit++)
      {
        // Check the LED driver assigned to be available and equal with index under test
        if ((((*pucLUnit_Hl >> 0u) & 0x0Fu) != 0u) && ((((*pucLUnit_Hl >> 0u) & 0x0Fu) - 1u) == ucIdx))
        {
          // Check error on thermozone assigned + availability
          // PRQA S 3415 2 // No potential of side effect. Behavior wanted - function call skiping in case of first condition fail
          // PRQA S 4391 1 // Cast under control
          if ((((*(pucLUnit_Hl + 1u) >> 4u) & 0x0Fu) != 0u) && (ErrCust_Get_NTC(((uint8_fast)((*(pucLUnit_Hl + 1u) >> 4u) & 0x0Fu) - 1u)) != 0u))
          {
            // Thermozones mapping to LED channel is in error
            sRBIN_NTCFailLightFunc.aucNtcError[ucIdx] = TRUE;
            break;
          }
        }
        // Next Logical Unit from Maping List
        pucLUnit_Hl += 3u;
      }

      sRBIN_NTCFailLightFunc.aucRbinError[ucIdx]    = ErrCust_Get_BinningClass(ucIdx);
      sRBIN_NTCFailLightFunc.aucChannelName[ucIdx]  = ErrCust_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[ucIdx];
    }

    for (uint8 ucIdx = 0u; ucIdx < 8u; ucIdx++)
    {
      // Calculate RBIN error per light function
      ucErrPerLightFunc = ErrCust_GetNTCBinningErrorPerChannel(ucIdx, sRBIN_NTCFailLightFunc);
      // Set each bit of the RBIN DIAG per light function
      psOutputData->ucErrPerLightFunc |= (uint8)(ucErrPerLightFunc << ucIdx);
    }
  }
  else
  {
    // Coding is not valid
    psOutputData->ucErrPerLightFunc = 0u;
  }
} // PRQA S 5336 1 // Program Architecture


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketRbinEepromLmmEcuData
///
/// \descr  Stores aftermarket RBIN EEPROM LMM diagnosis ECU data
///
/// \param   psOutputData   buffer to store data
///
/// \return  void 
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketRbinEepromLmmEcuData(tsErrCust_AftermarketRbinEepromLmmData* psOutputData)
{
  // Data used for RBIN_NTCs 1-14, LMMs 1-7, EEPROM 1-12
  boolean aboNtcBinData[ERRCUST_MAX_NTCBIN_INPUTS] = { 0u };

  (void)Rte_Read_RSens_NTC_BIN_Input_Errors((tsRteNTCBinInData*)&aboNtcBinData);   // PRQA S 310 

  // Set RBIN/NTC DIAG 1-8
  for (uint8 ucIdx = 0u; ucIdx < 8u; ucIdx++)
  {
    psOutputData->ucFirstByte += (uint8)(aboNtcBinData[ucIdx] << (ERRCUST_7BIT_SHIFT - ucIdx));
  }

  // Set RBIN/NTC DIAG 9-14
  for (uint8 ucIdx = 8u; ucIdx < 14u; ucIdx++)
  {
    psOutputData->ucSecondByte += (uint8)(aboNtcBinData[ucIdx] << (ERRCUST_15BIT_SHIFT - ucIdx));
  }

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  // Set EEPROM DIAG 1-2 and 11-12
  for (uint8 ucBinIdx = 0u; ucBinIdx < 2u; ucBinIdx++)
  {
    psOutputData->ucSecondByte += (uint8)((aboNtcBinData[ERRCUST_EEPROM_NTCBIN_START + ucBinIdx]) << (ERRCUST_1BIT_SHIFT - ucBinIdx));

    psOutputData->ucFourthByte += (uint8)((aboNtcBinData[ERRCUST_EEPROM_NTCBIN_START + ERRCUST_OFFSET_INDEX_10 + ucBinIdx]) << (ERRCUST_7BIT_SHIFT - ucBinIdx));
  }

  // Set EEPROM DIAG 3-10
  for (uint8 ucBinIdx = ERRCUST_START_INDEX_2; ucBinIdx < ERRCUST_OFFSET_INDEX_10; ucBinIdx++)
  {
    psOutputData->ucThirdByte += (uint8)((aboNtcBinData[ERRCUST_EEPROM_NTCBIN_START + ucBinIdx]) << (ERRCUST_9BIT_SHIFT - ucBinIdx));
  }

  // Set LMM DIAG 1-6
  for (uint8 ucLmmIndx = 0; ucLmmIndx < ERRCUST_OFFSET_INDEX_6; ucLmmIndx++)
  {
    psOutputData->ucFourthByte += (uint8)((aboNtcBinData[ERRCUST_LMM_NTCBIN_START + ucLmmIndx]) << (ERRCUST_5BIT_SHIFT - ucLmmIndx));
  }

  // Set LMM DIAG 7
  psOutputData->ucFifthByte += (uint8)((aboNtcBinData[ERRCUST_LMM_NTCBIN_START + ERRCUST_OFFSET_INDEX_6]) << ERRCUST_7BIT_SHIFT);

#else
  // On ECO there is no EEPROM Binning Class
  psOutputData->ucThirdByte  = 0u;
  // On ECO there is no LMM 
  psOutputData->ucFourthByte = 0u;
#endif
  // Add reserved value 0x7F to the last byte
  psOutputData->ucFifthByte += ERRCUST_RESERVED_D421;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketLedOutputFailEcuData
///
/// \descr  Stores aftermarket LED Channel Output Failure ECU data
///
/// \param   psOutputData   buffer to store data
///
/// \return  void 
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketLedOutputFailEcuData(tsErrCust_AftermarketLedChnlOutData* psOutputData)
{
  tsRte_CtrlLed_ChStatesDiag sCtrlLedErrStateArr = { 0 };

  (void)Rte_Read_CtrlLed_ChState(&sCtrlLedErrStateArr);

  // Populate first byte
  for (uint8 ucIdx = 0u; ucIdx < 8u; ucIdx++)
  {
    psOutputData->ucFirstErrorByte += (uint8)(sCtrlLedErrStateArr.aboChStates[ucIdx] << (ERRCUST_7BIT_SHIFT - ucIdx));
  }

  // First 4 bits of second byte are reserved
  psOutputData->ucSecondErrorByte = ERRCUST_RESERVED_D422;

  // Populate second byte
  for (uint8 ucIdx = 8u; ucIdx < CFG_LED_CHANNELS_NR; ucIdx++)
  {
    psOutputData->ucSecondErrorByte += (uint8)(sCtrlLedErrStateArr.aboChStates[ucIdx] << (ERRCUST_15BIT_SHIFT - ucIdx));
  }
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_Get_NTC
///
/// \descr  This function return NTC status for each thermozone index
///
/// \param  ucIdx         - index of thermozone
///
/// \return uint8 (ntc error)
//-----------------------------------------------------------------------------
STATIC_AL uint8 ErrCust_Get_NTC(uint8_fast ucIdx)
{
  // Ntc state
  tsRte_NTCTemperature sNtcVal;
  // Ntc error
  uint8 ucNtcErr = 0u;

  // Read NTC error state assigne to a thermozone
  (void)ErrCust_ReadNtcVal(&sNtcVal);

  // Check signal qty
  ucNtcErr = (uint8)((sNtcVal.eSigQty[ucIdx] != SIG_VALID) ? TRUE : FALSE);

  // Return binning class error state
  return ucNtcErr;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ReadNtcVal
///
/// \descr  This function calls the RTE for thermozone states
///
/// \param sNtcVal - pointer to the data structure with target NTC thermo value
///         
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType ErrCust_ReadNtcVal(tsRte_NTCTemperature* sNtcVal)
{
  // Error value
  Std_ReturnType ucReturnValue = 0u;

  // Read Thermzones state
  ucReturnValue = Rte_Read_RSens_ThermzoneTemperatures(sNtcVal);

  return ucReturnValue;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_Get_BinningClass
///
/// \descr  This function return binning class for each led channel
///
/// \param  ucIdx - index of led channel
///
/// \return uint8 (binning class)
//-----------------------------------------------------------------------------
STATIC_AL uint8 ErrCust_Get_BinningClass(uint8_fast ucIdx)
{
  tsRte_Binning0 sBinning;
  uint8 ucBinningClassErr = 0u;

  // Read power factor for each channel
  (void)ErrCust_ReadTgtBinningVal(ucIdx, &sBinning);

  // Check signal qty
  ucBinningClassErr = (uint8)(((sBinning.eSigQty != SIG_VALID) || (sBinning.ucBinning == (uint8)eBinningClassErr)) ? TRUE : FALSE);

  // Return binning class error state
  return ucBinningClassErr;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ReadTgtBinningVal
///
/// \descr  This function calls an array of function pointers for each led channel
///
/// \param  ucIdx         - index of led channel
///         sTgtBinningVal - pointer to the data structure with target binning value
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType ErrCust_ReadTgtBinningVal(uint8_fast ucIdx, tsRte_Binning0* sTgtBinningVal)
{
  Std_ReturnType ucReturnValue = 0u;

  // check against null ptr
  if (ErrCust_apfnReadTgtBinningClass_sVal_List[ucIdx] != NULL_PTR)
  {
    // Read binning classes
    ucReturnValue = ErrCust_apfnReadTgtBinningClass_sVal_List[ucIdx](sTgtBinningVal);
  }

  return ucReturnValue;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_GetNTCBinningErrorPerChannel
///
/// \descr  This function return binning class and NTC errorS per light function
///
/// \param  ucIdx         - index of led channel
/// \param  sRBINNTCFail  - structure with channel name and RBIN, NTC error
///
/// \return uint8 (binning class)
//-----------------------------------------------------------------------------
STATIC_AL uint8 ErrCust_GetNTCBinningErrorPerChannel(uint8_fast ucIdx, tsErrCust_RbinFailLightFunc sRBINNTCFail)
{
  uint8 ucNTC_BinningClassError = 0u;

  for (uint8 ucChnIdx = 0u; ucChnIdx <= ERRCUST_NO_OF_LED_CHANNELS; ucChnIdx++)
  {
    switch (ucIdx)
    {
        // Check RBIN/NTC error for Low Beam light function
      case ERRCUST_LIGHT_FUNCTION_LB:
        if (((sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_LB) ||
             (sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_LB_FuSa) ||
             (sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_LB_BOOST) ||
             (sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_PXL) ||
             (sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_MXB)) &&
            ((sRBINNTCFail.aucRbinError[ucChnIdx] == (uint8)TRUE) || (sRBINNTCFail.aucNtcError[ucChnIdx] == (uint8)TRUE)))
        {
          ucNTC_BinningClassError |= (uint8)TRUE;
        }
        else
        {
          // nothing to do
        }

        break;
        // Check RBIN/NTC error for High Beam light function
      case ERRCUST_LIGHT_FUNCTION_HB:
        if (((sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_HB) ||
            (sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_HB_BOOST) ||
            (sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_PXL) ||
            (sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_MXB)) &&
           ((sRBINNTCFail.aucRbinError[ucChnIdx] == (uint8)TRUE) || (sRBINNTCFail.aucNtcError[ucChnIdx] == (uint8)TRUE)))
        {
          ucNTC_BinningClassError |= (uint8)TRUE;
        }
        else
        {
          // nothing to do
        }

        break;
        // Check RBIN/NTC error for DayTime Running Light function
      case ERRCUST_LIGHT_FUNCTION_DRL_POS:
        if (((sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_DRL_POS) ||
             (sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_DRL_POS_SCRL)) &&
            ((sRBINNTCFail.aucRbinError[ucChnIdx] == (uint8)TRUE) || (sRBINNTCFail.aucNtcError[ucChnIdx] == (uint8)TRUE)))
        {
          ucNTC_BinningClassError |= (uint8)TRUE;
        }
        else
        {
          // nothing to do
        }

        break;
        // Check RBIN/NTC error for Turn Indicator light function
      case ERRCUST_LIGHT_FUNCTION_TI:
        if (((sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_TI) ||
             (sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_TI_SCRL)) &&
            ((sRBINNTCFail.aucRbinError[ucChnIdx] == (uint8)TRUE) || (sRBINNTCFail.aucNtcError[ucChnIdx] == (uint8)TRUE)))
        {
          ucNTC_BinningClassError |= (uint8)TRUE;
        }
        else
        {
          // nothing to do
        }

        break;
        // Check RBIN/NTC error for Side Marker light function
      case ERRCUST_LIGHT_FUNCTION_SM:
        if ((sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_SM) &&
            ((sRBINNTCFail.aucRbinError[ucChnIdx] == (uint8)TRUE) || (sRBINNTCFail.aucNtcError[ucChnIdx] == (uint8)TRUE)))
        {
          ucNTC_BinningClassError |= (uint8)TRUE;
        }
        else
        {
          // nothing to do
        }

        break;
        // Check RBIN/NTC error for RGB light function
      case ERRCUST_LIGHT_FUNCTION_RGB:
        if ((sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_RGB) &&
            ((sRBINNTCFail.aucRbinError[ucChnIdx] == (uint8)TRUE) || (sRBINNTCFail.aucNtcError[ucChnIdx] == (uint8)TRUE)))
        {
          ucNTC_BinningClassError |= (uint8)TRUE;
        }
        else
        {
          // nothing to do
        }

        break;
        // Check RBIN/NTC error for Fog light function
      case ERRCUST_LIGHT_FUNCTION_FOG:
        if ((sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_FOG) &&
            ((sRBINNTCFail.aucRbinError[ucChnIdx] == (uint8)TRUE) || (sRBINNTCFail.aucNtcError[ucChnIdx] == (uint8)TRUE)))
        {
          ucNTC_BinningClassError |= (uint8)TRUE;
        }
        else
        {
          // nothing to do
        }

        break;
        // Check RBIN/NTC error for Cornering light function
      case ERRCUST_LIGHT_FUNCTION_CORNERING:
        if ((sRBINNTCFail.aucChannelName[ucChnIdx] == ERRCUST_LF_CL) &&
            ((sRBINNTCFail.aucRbinError[ucChnIdx] == (uint8)TRUE) || (sRBINNTCFail.aucNtcError[ucChnIdx] == (uint8)TRUE)))
        {
          ucNTC_BinningClassError |= (uint8)TRUE;
        }
        else
        {
          // nothing to do
        }

        break;

      default:
        // nothing to do
        break;
    }
  }

  // Return binning class error
  return ucNTC_BinningClassError;
} // PRQA S 5316 1 // STCYC = 18' exceeds threshold 15 for Cyclomatic complexity (STCYC)


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketAttitudeEcuData
///
/// \descr  Stores aftermarket ATTITUDE ECU data
///
/// \param   psOutputData   buffer to store data  
///
/// \return  void 
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketAttitudeEcuData(tsErrCust_AftermarketAttitudeEcuData* psOutputData)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // Strucure used for freezing Attitude data to Ram
  tsErrCust_FreezeAttFrameDataRamStruct sFreezeAttFrameDataRam;
  // Structure used for storing Attitude value
  tsRte_SigPrep_VehiclePitchAngle sVehPitchAngle;

 // Get attitude values, the internal vehicle pitch angle is 0.01 degrees (to be checked, AVAC is reading with that resolution). 
  (void)Rte_Read_SigPrep_VehiclePitchAngle(&sVehPitchAngle);

  // Store stepper info, Diag type is +-10 deg = +511/-512 =====> 1 LSB = 10/512 = 0.019 = 0.02
  sFreezeAttFrameDataRam.snOffsetCalibVehicle_Attitude = NvmBlockDeltaPwmPara.snVehicleAttitude / 2; // change to correct format
  if (sVehPitchAngle.eSigQty == SIG_VALID)
  {
    sFreezeAttFrameDataRam.snInstValVehicule_Attitude = sVehPitchAngle.eAssietteVehicule.nVehiclePitchAngle /2; // change to correct format
  }
  else
  {
    // Update the maximum valid position value (511 * 6 / 20 = 153)
    sFreezeAttFrameDataRam.snInstValVehicule_Attitude = 0x99;
  }
  

  // Write output data
  psOutputData->snOffsetCalibVehicleAttitude  = sFreezeAttFrameDataRam.snOffsetCalibVehicle_Attitude;
  psOutputData->snInstValVehiculeAttitude     = sFreezeAttFrameDataRam.snInstValVehicule_Attitude;
#else
    (void)psOutputData;
#endif

}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketLvlEcuData
///
/// \descr  Stores aftermarket LVL ECU data
///
/// \param   psOutputData   buffer to store data  
///
/// \return  void 
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketLvlEcuData(tsErrCust_AftermarketLvlEcuData* psOutputData)
{
  // Strucure used for freezing Stp data to Ram
  tsErrCust_FreezeStpFrameDataRamStruct sFreezeStpFrameDataRam;

  tsErrCust_TypesActStatStp sActStatStp;
  sint8                     scConvertedRezForAngle;
  tiu32Voltage_mV           ulVoltage_mV = 15000u;

  // Read RTE wrapper port for Stp data
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp(&sActStatStp);

  (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(&ulVoltage_mV);

  // Store voltage supply
  sFreezeStpFrameDataRam.ucCl15 = (ulVoltage_mV > ERRCUST_MAX_ACCEPTED_VOLTAGE_MV) ? (uint8)(ERRCUST_MAX_ACCEPTED_VOLTAGE_V) : (uint8)(ulVoltage_mV / ERRCUST_01_VOLTAGE_REZOLUTION);

  // Store stepper info
  sFreezeStpFrameDataRam.bStsAutoLvl      = sActStatStp.ucStsAutoLvl;
  sFreezeStpFrameDataRam.bStpLossLvl = ((sActStatStp.boStpLossLvl != FALSE) || (sActStatStp.boPosDefLvl != FALSE)) ? 1u : 0u; // step loss or position defect;
  sFreezeStpFrameDataRam.bCommDefLvl = sActStatStp.boCommDefLvl;
  sFreezeStpFrameDataRam.bElecDefLvl = ((sActStatStp.boElecDefLvl != FALSE) || (sActStatStp.boThermDefLvl != FALSE)) ? 1u : 0u; // electrical or thermic defect
  sFreezeStpFrameDataRam.bMoveLvlStp      = sActStatStp.boMoveLvlStp;
  sFreezeStpFrameDataRam.scInstantLvl_Pos = sActStatStp.cStpPosDegree;

  // Write output data
  psOutputData->ucVoltageTerminal = sFreezeStpFrameDataRam.ucCl15;
  psOutputData->scInstantLvlPos   = sFreezeStpFrameDataRam.scInstantLvl_Pos;
  psOutputData->ucLvlInfo         = ((uint8)(sFreezeStpFrameDataRam.bStsAutoLvl                      )   +
                                     (uint8)(0x03u                              << ERRCUST_2BIT_SHIFT)   +
                                     (uint8)(sFreezeStpFrameDataRam.bStpLossLvl << ERRCUST_4BIT_SHIFT)   +
                                     (uint8)(sFreezeStpFrameDataRam.bCommDefLvl << ERRCUST_5BIT_SHIFT)   +
                                     (uint8)(sFreezeStpFrameDataRam.bElecDefLvl << ERRCUST_6BIT_SHIFT)   +
                                     (uint8)(sFreezeStpFrameDataRam.bMoveLvlStp << ERRCUST_7BIT_SHIFT));
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketContextEcuData
///
/// \descr  Stores aftermarket CONTEXT ECU data
///
/// \param   psOutputData   buffer to store data
///
/// \return  void 
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketContextEcuData(tsErrCust_AftermarketContextEcuData* psOutputData)
{
  // Strucure used for freezing Context data to Ram
  tsErrCust_FreezeCtxFrameDataRamStruct sFreezeCtxFrameDataRam;

  tiu32Voltage_mV             ulVoltage_mV  = 15000u;
  tsRte_SysMon_VehNetState    sNetworkState = { 0 };
  tsRte_SysMon_VehicleSpeed   sSpeedState   = { 0 };
  tsRte_OdometerTotal         sKilometrage  = { 0 };
  tsRte_SensorRaw             aunSensRawPwm;
  uint8                       ucVehicleSpeed = 0u;

  (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(&ulVoltage_mV);
  (void)Rte_Read_SysMon_VehNetState(&sNetworkState);
  (void)Rte_Read_SysMon_VehicleSpeed(&sSpeedState);
  (void)Rte_Read_SigPrep_OdometerTotal(&sKilometrage);
  (void)Rte_Read_IoHwAb_GetSens_Raw(&aunSensRawPwm);

  // Evaluate vehicle speed based on value and Signal Quality factor // LDMO-3327
  ucVehicleSpeed = ErrCust_EvaluateVehicleSpeed(sSpeedState);

  // Store voltage supply
  sFreezeCtxFrameDataRam.ucCl15           = (ulVoltage_mV > ERRCUST_MAX_ACCEPTED_VOLTAGE_MV) ? (uint8)(ERRCUST_MAX_ACCEPTED_VOLTAGE_V) : (uint8)(ulVoltage_mV / ERRCUST_01_VOLTAGE_REZOLUTION);
  sFreezeCtxFrameDataRam.bEtatReseauElec  = (uint8)sNetworkState.eElectricNetworkState;
  sFreezeCtxFrameDataRam.bEtatPrincipSev  = (uint8)sNetworkState.eVESMainState;
  sFreezeCtxFrameDataRam.ucVehicleSpeed   = ucVehicleSpeed;
  sFreezeCtxFrameDataRam.ulKilometrage    = (uint32)(sKilometrage.eOdometerTotal.ulOdometerTotal / 10u);
  sFreezeCtxFrameDataRam.ucInstValFlBhs   = (uint8)(((uint32)aunSensRawPwm.aucSensRaw[0u] * ERRCUST_MAX_VALUE_DID_D4C8) / ERRCUST_RESOLUTION_DID_D4C8);
  sFreezeCtxFrameDataRam.ucInstValRlBhs   = (uint8)(((uint32)aunSensRawPwm.aucSensRaw[1u] * ERRCUST_MAX_VALUE_DID_D4C8) / ERRCUST_RESOLUTION_DID_D4C8);

  // Write output data
  psOutputData->ucVoltageTerminal = (uint8)sFreezeCtxFrameDataRam.ucCl15;

  psOutputData->ucEtatInfo = ((uint8)(sFreezeCtxFrameDataRam.bEtatReseauElec                      )    +
                              (uint8)(sFreezeCtxFrameDataRam.bEtatPrincipSev << ERRCUST_4BIT_SHIFT));

  psOutputData->ucVehicleSpeed    = (uint8)sFreezeCtxFrameDataRam.ucVehicleSpeed;
  psOutputData->ulKilometrage     = (uint32)sFreezeCtxFrameDataRam.ulKilometrage;
  psOutputData->ucInstVal_FL_Bhs  = (uint8)sFreezeCtxFrameDataRam.ucInstValFlBhs;
  psOutputData->ucInstVal_RL_Bhs  = (uint8)sFreezeCtxFrameDataRam.ucInstValRlBhs;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ErrHandling
///
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
/// \param   unAlecId, ucAlecStatus
///
/// \return  void 
//-----------------------------------------------------------------------------
void ErrCust_ErrHandling(uint16 unAlecId, uint8 ucAlecStatus)
{
  // Local buffer used for clearing
  uint8 aucClearDtc[ERRCUST_DTC_CODE_SIZE] = { 0u };
  // Dtc index
  uint8 ucActualPsError;

  // Get (index of) Ps error for this (index of) AL error code
  ucActualPsError = (uint8)ErrCust_aPsRefList[unAlecId];


  // Check if it is a mapped cust error type (Ps)
  if (ucActualPsError != (uint8)ERRCUST_IxPsError_NONE)
  {
    //Check if the DTC test failed
    if ((ucAlecStatus & DEM_STATUS_TEST_FAILED) != 0u)
    {
      // Check if update is necessary
      if ((ErrCust_aucStatus[ucActualPsError] & ERRCUST_STATUS_TEST_FAILED) == 0u)
      {
        // Set all the corresponding status flags when a dtc test failed
        ErrCust_aucStatus[ucActualPsError] = ErrCust_aucStatus[ucActualPsError] | ERRCUST_TEST_FAILED_SET_FLAGS;

        // Clear all the corresponding status flags when a dtc test failed
        ErrCust_aucStatus[ucActualPsError] = ErrCust_aucStatus[ucActualPsError] & (uint8)(~ERRCUST_TEST_FAILED_CLEAR_FLAGS);


        // process NVM
        NvmBlockErrCustPs.aucErrStatus[ucActualPsError] = NvmBlockErrCustPs.aucErrStatus[ucActualPsError] | ERRCUST_TEST_FAILED_SET_FLAGS_NVM;

        NvmBlockErrCustPs.aucErrStatus[ucActualPsError] = NvmBlockErrCustPs.aucErrStatus[ucActualPsError] & (uint8)(~ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR);

        // Check if this the first occurrence of the current DTC
        if ((NvmBlockErrCustPs.aucAgingCounter[ucActualPsError] == 0u) && (NvmBlockErrCustPs.aucErrFreezeFrameIndex[ucActualPsError] == ERRCUST_DTC_AVAILABLE_FOR_FFD) )
        {
          ErrCust_CaptureFreezeFrameData(ucActualPsError);
        }
        else
        {
          // Freeze Frame Data are capture only at the first appeareance
        }

        NvmBlockErrCustPs.aucAgingCounter[ucActualPsError] = ERRCUST_DTC_AGING_COUNTER_MAX;

        // Store logged Ps error data in NvM
        ErrCust_boNvmDirtyErrCust = TRUE;
      }
      else
      {
        // Nothing to do beacuse the status is unchanged
      }
    }
    //Check if the DTC test passed
    else if ((ucAlecStatus & DEM_STATUS_TEST_PASSED) != 0u)
    {
      //Check if update is necessary
      if ((ErrCust_aucStatus[ucActualPsError] & ERRCUST_STATUS_TEST_PASSED) == 0u)
      {
        // DTC shall be cleared only if all mapped ALECs are passed, if at least one ALEC is failed than de DTC shall not be cleared
        for (uint16 unIdxAlec = ((ErrCust_boLeft == TRUE) ? (1u) : (0u)); unIdxAlec < (DEM_MAX_EVENT_ID + 1u); unIdxAlec += 2u)
        {
          // Check if alec test passed or failed  
          //PRQA S 3415 1 //The right hand operand of a logical && operator is only evaluated if the left hand operand evaluates to 1 ("true"). - IT IS INTENDED, no side efect
          if ((ucActualPsError == (uint8)ErrCust_aPsRefList[unIdxAlec]) && (Dem_boEventPassed(unIdxAlec - 1u) == FALSE))
          {
            // test failed for unAlecId which is link to eActualIxPsError, therefore it's not necessary to go further
            return;
          }
          else
          {
            // test passed for unAlecId, go to the next alec
          }
        }

        ErrCust_aucStatus[ucActualPsError] = ErrCust_aucStatus[ucActualPsError] | ERRCUST_STATUS_TEST_PASSED;

        ErrCust_aucStatus[ucActualPsError] = ErrCust_aucStatus[ucActualPsError] & (uint8)(~ERRCUST_TEST_PASSED_CLEAR_FLAGS);

        if (NvmBlockErrCustPs.aucAgingCounter[ucActualPsError] == ERRCUST_DTC_AGING_COUNTER_MAX - 1u)
        {

          //This is the 2nd operation cycle since the DTC test passed, therefore 'pending' bit can be reseted
          ErrCust_aucStatus[ucActualPsError] = ErrCust_aucStatus[ucActualPsError] & (uint8)(~ERRCUST_STATUS_PENDING_DTC);
        }
        else if (NvmBlockErrCustPs.aucAgingCounter[ucActualPsError] == 0u)
        {
          //The DTC test passed in the last 40  operation cycle
          //If the bit 2 (pendingDTC) and the bit 3 (confirmedDTC) of statusOfDTC are set to 0 since more 40 operation cycles consecutives 
          //then the calculator clears automatically the whole information linked to DTC and reinitialize the status of DTC.
          //When the counter (DTC Aging Counter) reaches the value 0, the calculator must clear automatically all information linked to DTC(DTCsnapshotrecord, counter, status)

          ErrCust_aucStatus[ucActualPsError] = ErrCust_aucStatus[ucActualPsError] & (uint8)(~ERRCUST_STATUS_CONFIRMED_DTC);

          //Fill the buffer with the DTC code in order to clear the 
          aucClearDtc[0] = ERRCUST_GET_DTC_HIGH_BYTE(ucActualPsError);
          aucClearDtc[1] = ERRCUST_GET_DTC_MIDDLE_BYTE(ucActualPsError);
          aucClearDtc[2] = ERRCUST_GET_DTC_LOW_BYTE(ucActualPsError);
          (void)ErrCust_ClearMemory(&aucClearDtc[0]);
        }
        else
        {
          //This can be the first opearation cycle the DTC test passed or DTC test failed at least one time
        }

        //Process NVM
        if ((NvmBlockErrCustPs.aucErrStatus[ucActualPsError] & ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR) != 0u)
        {

          // In the previous operation cycle the DTC test has not completed since clear, but now the test is done, therefore reset the bit
          NvmBlockErrCustPs.aucErrStatus[ucActualPsError] = NvmBlockErrCustPs.aucErrStatus[ucActualPsError] & (uint8)(~ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR);

          // Store logged Ps error data in NvM
          ErrCust_boNvmDirtyErrCust = TRUE;
        }
        else
        {
          //Test was completed in the previous operation cycle, bit is already reseted, therefore nothing to do
        }

        // process NVM
        if ((NvmBlockErrCustPs.aucErrStatus[ucActualPsError] & ERRCUST_STATUS_TEST_FAILED_SINCE_CLEAR) != 0u)
        {

          //In the previous operation cycle the DTC test failed since clear, but now the DTC test hasn't failed yet, therefore reset the bit
          NvmBlockErrCustPs.aucErrStatus[ucActualPsError] = NvmBlockErrCustPs.aucErrStatus[ucActualPsError] & (uint8)(~ERRCUST_STATUS_TEST_FAILED_SINCE_CLEAR);

          // Store logged Ps error data in NvM
          ErrCust_boNvmDirtyErrCust = TRUE;
        }
        else
        {
          // The DTC test passed in the previous operation cycle, bit is already reseted, therefore nothing to do
        }
      }
      else
      {
        // The DTC status test hasn't changed since last test, therefore nothing to do
      }
    }
    else
    {
      // There are only two variants: DTC test failed or DTC test passed, therefore nothing to do
    }
  }
  else
  {
    // Mapping error, nothing to do
  }
//PRQA S 5336 1// STMIF = 6' exceeds threshold 4 for Number nesting of control structures -> there is no possibility to decrease the number of STMIF
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ucGetClearMemoryType
///
/// \descr  This function returns clear type according to the value of the parameter
///
/// \param   uint32 ulDtcCode: All Groups of DTCs, a group of DTCs, a single DTC
///
/// \return  uint8 ucClearType 
//-----------------------------------------------------------------------------
STATIC_AL teErrCust_Types_Clear ErrCust_ucGetClearMemoryType(uint32 ulDtcCode)
{
  //Variable which store the clearType
  teErrCust_Types_Clear eClearType = eErrCust_ClearNotSupported;
  // Dtc index
  uint8 ucErrIx;

  //Check if there is request for clearing all DTCs
  if (ulDtcCode == ERRCUST_ALL_GROUP_OF_DTCS)
  {
    //Clear all DTCs
    eClearType = eErrCust_ClearAllDtcs;
  }
  //Check if there is a request for clearing a certain group of DTCs
  else if ((ulDtcCode == ERRCUST_GRP_P) || (ulDtcCode == ERRCUST_GRP_C) || (ulDtcCode == ERRCUST_GRP_B) || (ulDtcCode == ERRCUST_GRP_U))
  {
    //Clear the group of DTCs INDICATING by ulClearDtcCode
    eClearType = eErrCust_ClearGroupOfDtcs;
  }
  //Any other case means that there is a request for clearing a single DTC
  else
  {
    // Find the given DTC
    for (ucErrIx = 0u; ucErrIx < ERRCUST_NUMBER_OF_DTCS; ucErrIx++)
    {
      if (ErrCust_aPsDtcs[ucErrIx].ulDtc == ulDtcCode)
      {
        // Set the clear type to single DTC
        eClearType = eErrCust_ClearSingleDtc;
        // After the dtc is found break the search
        break;
      }
      else
      {
        // Dtc not found, therefore nothing to set, clear type is the one from initialization phase: eErrCust_ClearNotSupported
      }
    }
  }

  return eClearType;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ClearMemory
///
/// \descr  This function clear both Customer errors from Nvm and RAM and also correponding DemEventIds errors(ALEC ID) from Nvm and RAM according to DTC code received over the CAN via pointer parameter
///
/// \param   pucDtcCode - contains Dtc code or Group of dtc for clearing
///
/// \return  boDtcSupported: FALSE - pucDtcCode contains values which are supported, TRUE otherwise 
//-----------------------------------------------------------------------------
boolean ErrCust_ClearMemory(uint8* pucDtcCode)
{
  // Variable for keeping the DTC code or group of DTCs
  uint32 ulClearDtcCode;
  // Variable used for browsing the dtc table
  uint8 ucErrIx;
  // Variable which show the type of clearing
  teErrCust_Types_Clear eConfigClearType;
  // Local variable which shows if receved parameter(Dtc) is supported or not
  boolean boDtcNotSupported = FALSE;

  // Build the DTC code
  // PRQA S 4397 1//An expression which is the result of a ~ or << operation has not been cast to its essential type -> it is intended and the behavior is as expected
  ulClearDtcCode = UTIL_MAKELONG(UTIL_MAKEWORD(pucDtcCode[2], pucDtcCode[1]), UTIL_MAKEWORD(pucDtcCode[0], 0x00));

  // Get the Clear Type
  eConfigClearType = ErrCust_ucGetClearMemoryType(ulClearDtcCode);

  switch (eConfigClearType)
  {
     case eErrCust_ClearAllDtcs: 
         // Clear Cust Ps error code and corresponding DemEventId err from Nvm and RAM for all DTC code: uErrIx 
         ErrCust_ClearAllErrCustAndDemEventIds();

       break;

     case eErrCust_ClearGroupOfDtcs:
       // based on ticket LDMO-1558 and the CANdela file it was decided only clear all grups to be supported
       //// Go through each dtc
       //for (ucErrIx = 0u; ucErrIx < ERRCUST_NUMBER_OF_DTCS; ucErrIx++)
       //{
       //  // Check if the current dtc code is part of DTC group received over the CAN
       //  if ((ErrCust_aPsDtcs[ucErrIx].ulDtc | ulClearDtcCode) == ErrCust_aPsDtcs[ucErrIx].ulDtc)
       //  {
       //    // Clear Cust Ps error code and corresponding DemEventId err from Nvm and RAM for the current DTC code(uErrIx) which is part of DTC group received over the CAN - ulClearDtcCode
       //    ErrCust_ClearErrCustAndDemEventIds(ucErrIx, ulClearDtcCode);
       //  }
       //  else
       //  {
       //    // The current DTC is not part of the DTC group receved over the CAN, therefore nothing to do
       //  }
       //}
       boDtcNotSupported = TRUE;
       break;

     case eErrCust_ClearSingleDtc:
       // code commented with regard to issue LDMO-1558
       //for (ucErrIx = 0u; ucErrIx < ERRCUST_NUMBER_OF_DTCS; ucErrIx++)
       //{
       //  // Check if the current DTC is the one received over the CAN
       //  if (ErrCust_aPsDtcs[ucErrIx].ulDtc == ulClearDtcCode)
       //  {
       //    // Clear Cust Ps error code and corresponding DemEventId err from Nvm and RAM for the current DTC code(uErrIx) which was received over the CAN - ulClearDtcCode
       //    ErrCust_ClearErrCustAndDemEventIds(ucErrIx, ulClearDtcCode);
       //
       //    // Break the loop beacuse there is no other DTC like this one
       //    break;
       //  }
       //  else
       //  {
       //    // The current DTC is not the one received over the CAN, therefore nothing to do
       //  }
       //}
       boDtcNotSupported = TRUE;
       break;
     default:
       // eConfigClearType == eErrCust_ClearNotSupported; DTC or group of DTCs not supported, therefore mark the flag
       boDtcNotSupported = TRUE;
       break;
  }

  return boDtcNotSupported;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ucGetStatusOfDTC
///
/// \descr  This function return the current status of the DTC given as parameter
///
/// \param   teErrCust_IxPsError ActualIxPsError
///
/// \return  void 
//-----------------------------------------------------------------------------
uint8 ErrCust_ucGetStatusOfDTC(uint8 ucDtcIndex)
{
  // Variable for storing the current status of DTC
  uint8 ucStatusOfDTC;
  
  // Get the status
  ucStatusOfDTC = (ErrCust_aucStatus[ucDtcIndex] & 0x4Fu) |
                           (NvmBlockErrCustPs.aucErrStatus[ucDtcIndex] & (ERRCUST_STATUS_TEST_FAILED_SINCE_CLEAR | ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR));

  return ucStatusOfDTC;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_SetAvailableDtc
///
/// \descr    This function fill the buffer received as parameter with the first available DTC code that match the ucDTCStatusMask
///
/// \param    uint8* pucBuf - bufer for storing the DTC code
///           uint8 ucDTCStatusMask
///
/// \return   void 
//-----------------------------------------------------------------------------

void ErrCust_SetAvailableDtc(uint8* pucBuf, uint8 ucDTCStatusMask)
{
  // Variable for storing status for each DTC
  uint8 ucStatusOfDTC;
  // Flag which indicate via: False - dtc not found, TRUE - dtc is already found
  boolean boDtcFound;
  // It is assumed that the dtc was not found
  boDtcFound = FALSE;

  //Go through the DTC table as long as the DTC index hasn't reached the max value or the DTC was not found
  while ((ErrCust_ucDtcIndex < ERRCUST_NUMBER_OF_DTCS) && (boDtcFound == FALSE))
  {

    //Get the status of the current DTC
    ucStatusOfDTC = ErrCust_ucGetStatusOfDTC(ErrCust_ucDtcIndex);

     /*The server shall perform a logical AND-ing operation between the mask defined in the client request (DTCStatusMask) 
      and the status associated with each DTC supported by the server(StatusOfDTC) and
      shall return all DTCs for which the result of the AND - ing operation is non - zero. (DTCStatusMask & StatusOfDTC != 0)*/
    if ((ucStatusOfDTC & ucDTCStatusMask) != 0u)
    {
      //Take the high byte
      pucBuf[0] = ERRCUST_GET_DTC_HIGH_BYTE(ErrCust_ucDtcIndex);
      //Take the low byte
      pucBuf[1] = ERRCUST_GET_DTC_MIDDLE_BYTE(ErrCust_ucDtcIndex);
      //Take the dtc type: B, C, P or U
      pucBuf[2] = ERRCUST_GET_DTC_LOW_BYTE(ErrCust_ucDtcIndex);
      //Take the current status of DTC
      pucBuf[3] = ucStatusOfDTC;

      //Mark that a dtc was found, this is a finished condition for while loop
      boDtcFound = TRUE;
    }
    else
    {
      //No match of ucDTCStatusMask found for the current DTC, therefore nothing to do
    }

    //Increment index for next dtc
    ErrCust_ucDtcIndex++;
  }
}


//-----------------------------------------------------------------------------
/// \brief   ErrCust_ucGetErrorCount
///
/// \descr   This function returns the number of logged custom error entries - DTCs
///
/// \param   ucDTCStatusMask: mask for status errors
///
/// \return  ucDTCCount 
//-----------------------------------------------------------------------------
uint8 ErrCust_ucGetErrorCount(uint8 ucDTCStatusMask)
{
  // Counter for active DTCs
  uint8 ucDTCCount = 0u;
  // Varible used for getting the status for each Ps Error
  uint8 ucStatusOfDTC;

  for (uint8 ucDtcIdx = 0u; ucDtcIdx < ERRCUST_NUMBER_OF_DTCS; ucDtcIdx++)
  {
    // Get the status of the current DTC
    ucStatusOfDTC = ErrCust_ucGetStatusOfDTC(ucDtcIdx);

    // Check if actual status is matching with receveid status
    if ((ucStatusOfDTC & ucDTCStatusMask) != 0u)
    {
      // Increment error counter for the DTC which match with DTCStatusMask
      ucDTCCount++;
    }
    else
    {
      // The status do not correspond with the status mask received over CAN, therefore nothing to do
    }
  }

  return ucDTCCount;
}


//-----------------------------------------------------------------------------
/// \brief   ErrCust_ulGetDtcCode
///
/// \descr   This function returns the DTC code corresponding with the given DTC index
///
/// \param   ucDtcIndex
///
/// \return  dtc code 
//-----------------------------------------------------------------------------
uint32 ErrCust_ulGetDtcCode(uint8 ucDtcIndex)
{
  // Return the DTC code in ps format
  return (ErrCust_aPsDtcs[ucDtcIndex].ulDtc);
}

/* code commented with regard to issue LDMO-1558
//-----------------------------------------------------------------------------
/// \brief  ErrCust_ClearErrCustAndDemEventIds
///
/// \descr  This function clear RAM tables(ErrCust_aucStatus and Dem_astEventStatus), and NvmBlockTable (NvmBlockErrCustPs and NvmBlockDemData) according to value of the first parameter
///
/// \param   ePsError, ulDTCCode
///
/// \return  void 
//-----------------------------------------------------------------------------
STATIC_AL void ErrCust_ClearErrCustAndDemEventIds(uint8 ucPsError, uint32 ulDTCCode)
{
  // Variable for browsing ErrCust_aPsRefList table
  uint16 unAlecId;
  // Variable for storing the freeze frame data index of the current Dtc
  uint8 ucFFDIdx;

  // Get freeze frame index for the current Dtc
  ucFFDIdx = NvmBlockErrCustPs.aucErrFreezeFrameIndex[ucPsError];

  ErrCust_aucStatus[ucPsError] = ERRCUST_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE;

  NvmBlockErrCustPs.aucAgingCounter[ucPsError] = 0u;
  NvmBlockErrCustPs.aucErrStatus[ucPsError] = ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR;
  NvmBlockErrCustPs.aucErrFreezeFrameIndex[ucPsError] = ERRCUST_DTC_AVAILABLE_FOR_FFD;

  // Store logged Ps error data in NvM
  ErrCust_boNvmDirtyErrCust = TRUE;

  // Check if for the current DTC entry in FFD was used; This Check make sense only for clearing ALL DTCs
  if (ucFFDIdx < ERRCUST_FREEZE_FRAME_DATA_ENTRIES)
  {
    ErrCust_ClearFreezeFrameData(ucFFDIdx);
  }
  else
  {
    // FFD entry not used, therefore nothing to    
  }


  // Check if there is a request to clear all DTCs
  if (ulDTCCode == ERRCUST_ALL_GROUP_OF_DTCS)
  {
    //Dem_astEventStatus and NvmBlockDemData are cleared for All Alecs 
    Dem_ClearAlec(TRUE, 0u);
  }
  else
  {

    // Go through all Alec ids
    for (unAlecId = 1u; unAlecId <= DEM_MAX_EVENT_ID; unAlecId++)
    {
      // Check if the current DemEventId is correponding to PsErrCode received as parameter
      if (ucPsError == (uint8)ErrCust_aPsRefList[unAlecId])
      {
        // Clear info correponding to the found dem event id (Alec)
        Dem_ClearAlec(FALSE, unAlecId - 1u);
      }
      else
      {
        // Nothing to do, check the next ucPsError
      }
    }
  }
}
*/

//-----------------------------------------------------------------------------
/// \brief  ErrCust_ClearAllErrCustAndDemEventIds
///
/// \descr  This function clear RAM tables(ErrCust_aucStatus and Dem_astEventStatus), and NvmBlockTable (NvmBlockErrCustPs and NvmBlockDemData) according to value of the first parameter
///
/// \param   ePsError, ulDTCCode
///
/// \return  void 
//-----------------------------------------------------------------------------
STATIC_AL void ErrCust_ClearAllErrCustAndDemEventIds(void)
{
  // Variable for browsing ErrCust_aPsRefList table
  uint16 unAlecId;
  // Variable for storing the freeze frame data index of the current Dtc
  uint8 ucPsError,ucFFDIdx;

//clear all DTCs
  for (ucPsError = 0u; ucPsError < ERRCUST_NUMBER_OF_DTCS; ucPsError++)
  {
    ErrCust_aucStatus[ucPsError] = ERRCUST_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE;

    NvmBlockErrCustPs.aucAgingCounter[ucPsError] = 0u;
    NvmBlockErrCustPs.aucErrStatus[ucPsError] = ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR;
    NvmBlockErrCustPs.aucErrFreezeFrameIndex[ucPsError] = ERRCUST_DTC_AVAILABLE_FOR_FFD;
  }
  // Store logged Ps error data in NvM
  ErrCust_boNvmDirtyErrCust = TRUE;

//Clear all freeze frames
  for (ucFFDIdx = 0; ucFFDIdx < ERRCUST_FREEZE_FRAME_DATA_ENTRIES; ucFFDIdx++)
  {
    ErrCust_ClearFreezeFrameData(ucFFDIdx);
  }

    //Dem_astEventStatus and NvmBlockDemData are cleared for All Alecs 
    Dem_ClearAlec(TRUE, 0u);

}

//-----------------------------------------------------------------------------
/// \brief ErrCust_ResetDtcIndex
///
/// \descr This function is used by diagnosis in order to reset Dtc index right before reading the available DTCs
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_ResetDtcIndex(void)
{
  // Reset DTC index
  ErrCust_ucDtcIndex = 0u;
}


//-----------------------------------------------------------------------------
/// \brief ErrCust_ClearFreezeFrameData
///
/// \descr This function clear freeze frame data corresponding to 'ucFreezeFrameIdx' parameter
///        from table ErrCust_ClearFreezeFrameData which is linked with dtc indicated by aucDtcId field from the same table
///
/// \param  ucFreezeFrameIdx
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void ErrCust_ClearFreezeFrameData(uint8 ucFreezeFrameIdx)
{
  // Index variable
  uint8 ucIdx;

  for (ucIdx = 0u; ucIdx < ERRCUST_FREEZE_FRAME_DATA_ENTRIES; ucIdx++)
  {
    if ( (NvmBlockFreezeFrameDataPs.aucAge[ucIdx] > NvmBlockFreezeFrameDataPs.aucAge[ucFreezeFrameIdx]) && 
         (NvmBlockFreezeFrameDataPs.aucDtcId[ucIdx] != ERRCUST_DTC_AVAILABLE_FOR_FFD) )
    {
      // Decrease the age for all DTCs which have an age bigger than the age of freeze frame data which will be cleared; Also a valid dtc id is required
      NvmBlockFreezeFrameDataPs.aucAge[ucIdx]--;
    }
    else
    {
      // In all other cases there is nothing to decrease
    }
  }

  // Set the age to min in order to signalize that Dtc snapshot data is availabale for storage for this Dtc
  NvmBlockFreezeFrameDataPs.aucAge[ucFreezeFrameIdx] = ERRCUST_MIN_AGE;
  // Set dtc field from FFD structure as available
  NvmBlockFreezeFrameDataPs.aucDtcId[ucFreezeFrameIdx] = ERRCUST_DTC_AVAILABLE_FOR_FFD;

  // Reset all fields of freeze frame data structure
  NvmBlockFreezeFrameDataPs.asnOFFSET_CALIB_VEHICLE_ATTITUDE  [ucFreezeFrameIdx]  = 0;
  NvmBlockFreezeFrameDataPs.asnINST_VAL_VEHICULE_ATTITUDE     [ucFreezeFrameIdx]  = 0;
  NvmBlockFreezeFrameDataPs.ascINSTANT_LVL_POS                [ucFreezeFrameIdx]  = 0;
  NvmBlockFreezeFrameDataPs.aucLVL_INFO                       [ucFreezeFrameIdx]  = 0u;
  NvmBlockFreezeFrameDataPs.aucVOLTAGE_TERMINAL_DTC           [ucFreezeFrameIdx]  = 0u;
  NvmBlockFreezeFrameDataPs.aucETAT_INFO_DTC                  [ucFreezeFrameIdx]  = 0u;
  NvmBlockFreezeFrameDataPs.VEHICLE_SPEED_DTC                 [ucFreezeFrameIdx]  = 0u;
  NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC                   [ucFreezeFrameIdx]  = 0u;
  NvmBlockFreezeFrameDataPs.INST_VAL_FL_BODY_HIGH_SENSOR_DTC  [ucFreezeFrameIdx]  = 0u;
  NvmBlockFreezeFrameDataPs.INST_VAL_RL_BODY_HIGH_SENSOR_DTC  [ucFreezeFrameIdx]  = 0u;

  // Store freeze frame information
  ErrCust_boNvmDirtyFreezeFrameData = TRUE;
}


//-----------------------------------------------------------------------------
/// \brief ErrCust_GetActualErrorIndex
///
/// \descr Get actual error dtc index based on Alec Index input
///
/// \param  unAlecId: Alec Id
///
/// \return uint8: Error Dtc Index
//-----------------------------------------------------------------------------
uint8 ErrCust_GetActualErrorIndex(uint16 unAlecId)
{
  return ((uint8)ErrCust_aPsRefList[unAlecId]);
}


//-----------------------------------------------------------------------------
/// \brief ErrCust_Cycle0
///
/// \descr ErrCust cyclic main function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_Cycle0(void)
{
  // update NVM
  STATIC_AL TIMER ulNvmLastRetry = 0u;

  // Flag used to read the coding only once
  STATIC_UT(boolean, boCodingReady, FALSE);

  if (boCodingReady == FALSE)
  {
    // Coding validity check
    ErrCust_boCodingValidity = ErrCust_CodingDataValidation();

    // Set the flag that indicates the coding has been read
    boCodingReady = TRUE;
  }
  else
  {
    // nothing to do, coding has already been read
  }

  if (TimerGetTimeSince(ulNvmLastRetry) >= FT_MSEC(300U)) {
    // retry every 300 ms
    if (ErrCust_boNvmDirtyErrCust != FALSE) {
      ErrCust_boNvmDirtyErrCust = NvM_WriteBlock((NvM_BlockIdType)NvmBlockErrCustPsId, NULL_PTR) != E_OK ? TRUE : FALSE;
    }

    if (ErrCust_boNvmDirtyFreezeFrameData != FALSE) {
      ErrCust_boNvmDirtyFreezeFrameData = NvM_WriteBlock((NvM_BlockIdType)NvmBlockFreezeFrameDataPsId, NULL_PTR) != E_OK ? TRUE : FALSE;
    }

    ulNvmLastRetry = TimerGetTick();
  }
}


/// ---------------------------------------------------------------------------
/// \func     ErrCust_ConvertValueSint2Int
///
/// \brief    Convert signed values into unsigned values 
///
/// \param    slInValue     - Input signed Value
///           ucbitLength   - Signal Length in bits
///
/// \return   uint32 - value unsigned
/// ---------------------------------------------------------------------------
uint32 ErrCust_ConvertValueSint2Int(sint32 slInValue, uint8 ucbitLength)
{
  uint32 ulValue = 0u;

  if (slInValue >= 0)
  {
    ulValue = (uint32)slInValue;
  }
  else
  {
    // PRQA S 4397, 1891  1 // All forms of bit operations on single-bit bitfields allowed for efficiency
    ulValue = (1u << (ucbitLength - 1u)) | ((uint32)slInValue & ((1u << ucbitLength) - 1u));
  }

  return ulValue;
}


/// ---------------------------------------------------------------------------
/// \func     ErrCust_ConvertValueInt2Sint
///
/// \brief    Convert unsigned values into signed values 
///
/// \param    ulInValue     - Input Unsigned Value
///           ucbitLength   - Signal Length in bits
///
/// \return   sint32 - value signed
/// ---------------------------------------------------------------------------
sint32 ErrCust_ConvertValueInt2Sint(uint32 ulInValue, uint8 ucbitLength)
{
  sint32 slValue = (sint32)ulInValue;
  uint32 ulBitToCheck = ((uint32)slValue) >> (ucbitLength - 1u);

  // PRQA S 1843 1 // The Right-hand signed operand is located in macro bellow from UtilMath.h
  if ((ulBitToCheck & 1u) != 0u)
  {
    // PRQA S 4532, 4394  1 // All forms of bit operations on single-bit bitfields allowed for efficiency
    slValue = slValue | (sint32)(ERRCUST_32_BIT_MASK << ucbitLength);
  }
  else
  {
    // Keep positive value
  }

  return slValue;
}


//-----------------------------------------------------------------------------
/// \brief   ErrCust_GetStatusOfDtc
///
/// \descr   This function returns the status of a DTC code corresponding with the given DTC index
///
/// \param   ucDtcIndex
///
/// \return  dtc code 
//-----------------------------------------------------------------------------
uint8 ErrCust_GetStatusOfDtc(uint8 ucDtcIndex)
{
  // Return the DTC code in ps format
  return (ErrCust_aucStatus[ucDtcIndex]);
}


//-----------------------------------------------------------------------------
/// \brief   ErrCust_EvaluateVehicleSpeed
///
/// \descr   This function returns the vehicle speed after evaluating it's signal
///          quality factor and it's value (to avoid overflow)
///
/// \param   sInputSig        - input signal received on CAN
///
/// \return  ucVehicleSpeed   - Vehicle Speed after evaluation
//-----------------------------------------------------------------------------
STATIC_AL uint8 ErrCust_EvaluateVehicleSpeed(tsRte_SysMon_VehicleSpeed sInputSig)
{
  uint8 ucVehicleSpeed = 0u;

  if (((sInputSig.eSigQty == SIG_INVALID) || (sInputSig.eSigQty == SIG_TIMEOUT) ||
       (sInputSig.eSigQty == SIG_E2E_CRCERR) || (sInputSig.eSigQty == SIG_E2E_ALIVEERR)) ||
      (sInputSig.eVehicleSpeed.unVehicleSpeed > ERRCUST_MAX_ACCEPTED_SPEED_KMPH))
  {
    // Latch the value to the maximum accepted value (255 km/h)
    ucVehicleSpeed = (uint8)ERRCUST_MAX_ACCEPTED_VOLTAGE_KMPH;
  }
  else
  {
    ucVehicleSpeed = (uint8)(sInputSig.eVehicleSpeed.unVehicleSpeed / ERRCUST_SPEED_RESOLUTION);
  }

  return ucVehicleSpeed;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CodingDataValidation
///
/// \descr  Get and handle coding parameters for ErrCust module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
STATIC_AL boolean ErrCust_CodingDataValidation(void)
{
  tsRteCodingParameters sCodingParameters;
  // Get coding data via RTE
  (void)Rte_Read_CodM_Err_Para(&sCodingParameters);
  // Get coding data and return it's validity
  CONST_AL boolean boCodingValidity = ErrCust_Data_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);
  // Return validity of coding
  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_Data_ParaFct0
///
/// \descr  This function gets coding params and validity of coding data 
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean ErrCust_Data_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;

  switch (eCmd)
  {
    case eParaFct0_CodingDataValid:
      boCodingValidity = TRUE;
      ErrCust_pCodingArea = pData;
      break;
    case eParaFct0_CodingDataInvalid:
      boCodingValidity = FALSE;
      break;
    default:
      break;
  }

  return boCodingValidity;
}



//EOF
