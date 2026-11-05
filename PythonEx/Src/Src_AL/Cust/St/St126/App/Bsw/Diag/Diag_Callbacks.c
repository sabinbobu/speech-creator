//-----------------------------------------------------------------------------
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
/// \file   Diag_Callbacks.c
///
/// \brief  
///
/// \descr  Diagnostic services
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <_DIAG_types.h>
#include <Diag_ApplCmd_Rdm.h>
#include <Std_Types.h>
#include <AL_Helper.h>
#include <UtilUtility.h>
#include <LgmDEHMainAPI.h>
#include <p_Diag_Services.h>
#include "Diag_Callbacks.h"
#include <Swc/StatM/StatM.h>
#include <LgmDEHConfig_Cfg.h>
#include <IoHwAbUser.h>
#include <LgmEIMMainAPI.h>
#include <ErrCust.h>
#include <ErrCust_RteAccess.h>
#include <Nvm.h>
#include <CtrlSwi.h>
#include <Swc/DiagControl/DiagControl.h>
#include <CddSbc.h>
#include <Mcu.h>
#include <CddEft.h>
#include <SysMonRx_ASIL.h>  // permittied because it is only used to read data
#include <SysMonCheck.h>    // permittied because it is only used to read data
#include <CfgId.h>

#ifdef CFG_VARIANT_FULL
#include <CddMlc_Adapter.h>
#endif

#ifndef UNIT_TEST
#include <Os_SvcUser.h>
#include <Os_MemMap.h>
#else
#include <CddLed.h>
#endif

 //-----------------------------------------------------------------------------
 // Global Variable
 //-----------------------------------------------------------------------------

STATIC_AL uint8 Diag_ucErrorCnt = 0u;
STATIC_AL uint8 Diag_ucPwmSensError = 0u;
STATIC_AL tsRte_StepperRoutineControl       sStepperRoutineControl = { eStpControl_Unknown, eBothActuators, eMovementToZero, FALSE, FALSE, eDID_Invalid, 0, 0u };
STATIC_AL tsRte_DcMotorRoutineControl       Diag_sDcMotorRoutineControl = { eDcmControl_Unknown, eDcmBothActuators, eDcmMovementToZero, FALSE, FALSE, eDcmDID_Invalid, 0u, 0u };
STATIC_AL tsRte_Ld_ActivationRoutineControl Diag_sLd_ActivationRoutineControl;
STATIC_AL boolean Diag_boRoutineFinishedDFB5 = FALSE;
STATIC_AL boolean Diag_boRoutineFinishedDD00 = FALSE;
STATIC_AL boolean Diag_boRoutineFinishedDD03 = FALSE;
STATIC_AL boolean Diag_boControlDTCOff_Stat = FALSE;
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)
STATIC_AL boolean Diag_boRoutineFinishedDD06 = FALSE;
#endif

CONST_AL tNvmPara_CodingArea*  Diag_pCodingArea;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
STATIC_AL boolean Diag_boRoutineFinishedDF17 = FALSE;
STATIC_AL boolean Diag_boRoutineFinishedDD05 = FALSE;
STATIC_AL boolean Diag_boRoutineFinishedDF10 = FALSE;
STATIC_AL boolean Diag_boRoutineFinishedDF11 = FALSE;
STATIC_AL boolean Diag_boRoutineFinishedDF12 = FALSE;
STATIC_AL boolean Diag_boRoutineFinishedDF13 = FALSE;
STATIC_AL boolean Diag_boRoutineFinishedDD04 = FALSE;
STATIC_AL tsRteHssTarget Diag_asCpmHssTargetSetting;
STATIC_AL tsRte_AfsRoutineControl sAfsRoutineControl = { eAfsControl_Unknown, eAfs_Off, FALSE, FALSE };
STATIC_AL boolean Diag_boRoutineFinishedDD01 = FALSE;
STATIC_AL boolean Diag_boDD01_Status;
STATIC_AL tsRte_DIDPixelActivation Diag_boDD01_PixelActivation;
#endif

//Coding parameter
STATIC_AL uint16 Diag_Callbacks_unCodShortGND = 0u;
STATIC_AL uint16 Diag_Callbacks_unCodShortBAT = 0u;
STATIC_AL uint16 Diag_Callbacks_unCodOpenLoad = 0u;

// Structure used for DID F18C month/days number check
STATIC_AL CONST_AL tsDiag_MonthHandle Diag_asMonthsDays[DIAG_DATE_MONTHS_MAX] =
{
     {
          (uint8)1,
          (uint8)31
     },
     {
          (uint8)2,
          (uint8)28
     },
     {
          (uint8)3,
          (uint8)31
     },
     {
          (uint8)4,
          (uint8)30
     },
     {
          (uint8)5,
          (uint8)31
     },
     {
          (uint8)6,
          (uint8)30
     },
     {
          (uint8)7,
          (uint8)31
     },
     {
          (uint8)8,
          (uint8)31
     },
     {
          (uint8)9,
          (uint8)30
     },
     {
          (uint8)10,
          (uint8)31
     },
     {
          (uint8)11,
          (uint8)30
     },
     {
          (uint8)12,
          (uint8)31
     }
};

//-----------------------------------------------------------------------------
// Enums
//-----------------------------------------------------------------------------
typedef enum
{
  eFbhsTooLow,
  eFbhsTooHigh,
  eNotDefined1,
  eNotDefined2,
  eRbhsTooLow,
  eRbhsTooHigh
}SensErrorCodes;

typedef enum
{
  eRoutineInProgress = 0x1,
  eRoutineFinishedOK,
  eRoutineFinishedNOK,
  eRoutineStopped
}RoutineStates;

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

// EMC Label service routine compatibility for older EFT doc versions
#define DIAG_CALLBACKS_EMC_STANDARD_BACKWARD_COMPATIBILITY 1

//Concatenate logzone date by entry index
#define APPDESC_CONCATENATE_DATE_BY_INDEX(x)     (APPDESC_CONCATENATE_DATE(C_BOOT_ZI_Area[x].uData.sLogZoneInfo.ucDownloadedYear,  \
                                                                           C_BOOT_ZI_Area[x].uData.sLogZoneInfo.ucDownloadedMonth, \
                                                                           C_BOOT_ZI_Area[x].uData.sLogZoneInfo.ucDownloadedDay))

#define DIAG_AIMING_MODE_IDX        0x0FU
#define DIAG_ALIGNMENT_MODE_IDX     0x10U

#define DIAG_F18C_ECU_SERIAL_NUMBER_INIT {DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT, DIAG_ASCII_DEFAULT}

#ifdef UNIT_TEST
// MPU-Region5: Application Shared-RAM area
uint32 Diag_Callbacks_UT_ulTest_Buf[200];
#define m_data_shared_start                 (uint32)&Diag_Callbacks_UT_ulTest_Buf[0]
#endif
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// global variables
//-----------------------------------------------------------------------------
//PRQA S 3447 1 // AppDesc_AuthZone' is being declared with external linkage but this declaration is not in a header file.
extern volatile const tuDiag_AuthZoneInfo AppDesc_AuthZone; //authentication zone
//PRQA S 3447 1 // C_BOOT_ZI_Area' is being declared with external linkage but this declaration is not in a header file.
extern tsDiag_LogZoneEntry C_BOOT_ZI_Area[DIAG_LOGZONE_ENTRIES_NR]; //identification zone
 //-----------------------------------------------------------------------------
 // funtion prototypes
 //-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_Read_Number_of_DTC_By_StatusMaskFaultMemory(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_Read_by_MaskFaultMemory(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_Read_DTC_Snapshot_Data_by_DTC_NumberFaultMemory(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_0301_RESET_CPU_LOAD(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_F186_Active_Diag_Session_Data_Identifier(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_C002_SIZE_FOR_MULTI_DID(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_0D00_FACTORY_DATA_PROCESS_BYTE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_0D01_SIZE_OF_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D400_PIXEL_LED_STATUS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D401_FAN1_STATUS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D402_FAN2_STATUS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D404_SCROLLING_CTRL_OUTPUT_STATE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D405_LED_CH_OUTPUT_STATE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D406_LD_STATUS(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D407_NTC_RBIN_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D408_DERATING_FACTOR_AND_TEMP(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D409_CURRENT_BINNING_CLASS(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D410_DIAG_SCROLLING_INPUT_STATE(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D411_INSTRUMENTATED_FRAMES(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D421_RBIN_EEPROM_LMM_DIAGNOSIS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_1100_CPU_LOAD_OF_DEVICE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL uint16      Diag_Callbacks_F18C_Compute_Number_Of_Days_In_Year(void);
LOCAL_INLINE boolean  Diag_Callbacks_F18C_isCharacterSupported(uint8 ucInputVal);
STATIC_AL DIAG_status Diag_Callbacks_FD00_STATISTICS_DATA(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D4C5_LIGHTING_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D4C6_SIGNALLING_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D4C7_TURN_IND_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D4C8_BODY_HIGH_SENSOR_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D4C9_ATTITUDE_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D4CB_LEVELLING_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_D4CD_RGB_LED(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_F080_AUTHENTIFICATION_ZONE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_F0FE_IDENTIFICATION_ZONE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_F08F_EMC_STANDARDIZATION_LABEL(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_FD02_INTERNAL_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_FD03_READ_ACTIVE_ALECS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_FD04_INTERNAL_SW_LABEL(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)
STATIC_AL DIAG_status Diag_Callbacks_DD06_LvlDCMotorPosition(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
#endif

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
STATIC_AL DIAG_status Diag_Callbacks_DD01_PixelActivation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DD04_Fan2Activation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DD05_LvlStepperPosition(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DD07_SetScrollingCtrlOutput(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DF10_LvlReferencingRun(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DF11_LvlStepperControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DF12_LvlStepperControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DF13_LvlStepperControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DF17_AFSControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DF17_AFSControl_AfsControlStartStop(uint8 ucRoutineControl, uint16 unRoutineLength, uint8 const* pucDataIn);
STATIC_AL DIAG_status Diag_Callbacks_DF17_AFSControl_AfsResult(uint8 ucRoutineControl, uint16 unRoutineLength, uint8 const* pucDataIn);
STATIC_AL boolean     Diag_Callbacks_DF17_AFSControl_GetAfsStateAcceptanceStatus(uint8 ucAfsState);
#endif
STATIC_AL DIAG_status Diag_Callbacks_DD00_LdActivation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DD03_Fan1Activation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
STATIC_AL DIAG_status Diag_Callbacks_DFB5_InitAutomativLeveling(uint8* ucResData, uint8 ucDataLen, uint8 ucRoutineControlType, uint16 unLength, UINT8 const* puc_Data);
STATIC_AL DIAG_status Diag_Callbacks_01_CONTROL_DTC_ON(UINT8 ui8_Type, UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_02_CONTROL_DTC_OFF(UINT8 ui8_Type, UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_Write_0D00_FACTORY_DATA_PROCESS_BYTE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_Write_D411_INSTRUMENTATED_FRAMES(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Callbacks_Write_FD00_STATISTICS_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
STATIC_AL DIAG_status Diag_Ld_Control(const boolean boDiagStatus, uint8 const* pucData);
STATIC_AL boolean Diag_PowertrainCheck(void);
STATIC_AL boolean Diag_IntegrationMode(void);
STATIC_AL void Diag_Callbacks_RoutineControl_CheckStartStop(void);
STATIC_AL void Diag_Callbacks_ProgramingSessionAccepted(void);
STATIC_AL boolean Diag_CodingDataValidation(void);
STATIC_AL void    Diag_Get_Coding(tsDiag_CodingParameters *psCodingParam);
STATIC_AL boolean Diag_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
STATIC_AL uint32 Diag_Callback_CheckLastLightReq_Activated(void);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
STATIC_AL boolean     Diag_Callbacks_Check_If_Scrolling_Present(void);
#endif

#if defined UNIT_TEST
/* -------------------------------------------------- --------------------------------------------*/
/* Special UT instrumentation to force convert the raw data into request for default case         */
/* ---------------------------------------------------------------------------------------------- */
STATIC_AL void Diag_Special_UT_Instrumentation_Force_InvalidCoding(UINT8 const** p_ui8_Data);

/* -------------------------------------------------- --------------------------------------------*/
/* Special UT instrumentation to force position for next DTC to keep the current position         */
/* ---------------------------------------------------------------------------------------------- */
STATIC_AL void Diag_Special_UT_Instrumentation_Force_DTCPosition(uint16* unDtcPosition);


#endif


//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  AppDesc_LogZoneLastDataSearch
///
/// \descr  Search in LogZone for last downloaded data by date
///
/// \param  void
///
/// \return Last downloaded data index
//-----------------------------------------------------------------------------
STATIC_AL uint8 AppDesc_LogZoneLastDataSearch(void)
{
  uint8 ucIndex;
  uint8 ucLastDownloadedDataIndex;
  uint32 ulCurrentIndexDate, ulLastStoredIndexDate;

  ucLastDownloadedDataIndex = APPDESC_LOGZONE_ENTRY_MAX_INDEX;

  // Search for last downloaded data by date
  for (ucIndex = 0; ucIndex <= APPDESC_LOGZONE_ENTRY_MAX_INDEX; ucIndex++)
  {
    // Concatenate date from last stored index
    //PRQA S 4434 3 // A non-constant expression of 'essentially signed' type (signed int) is being converted to unsigned type, 'unsigned long' on assignment.
      //PRQA S 1850 2 // The right-hand operand is 'essentially unsigned' (unsigned char) but will be implicitly converted to a signed type (signed int) in this arithmetic operation.
    //PRQA S 1860 1 // The operands of this arithmetic operator are of different 'essential signedness' but will generate a result of type 'signed int'.
    ulLastStoredIndexDate = APPDESC_CONCATENATE_DATE_BY_INDEX(ucLastDownloadedDataIndex);

    // Concatenate date from current index
    //PRQA S 1850 4 // The right-hand operand is 'essentially unsigned' (unsigned char) but will be implicitly converted to a signed type (signed int) in this arithmetic operation.
      //PRQA S 4434 3 // A non-constant expression of 'essentially signed' type (signed int) is being converted to unsigned type, 'unsigned long' on assignment.
    //PRQA S 1850 2 // The right-hand operand is 'essentially unsigned' (unsigned char) but will be implicitly converted to a signed type (signed int) in this arithmetic operation.
     //PRQA S 1860 1 // The operands of this arithmetic operator are of different 'essential signedness' but will generate a result of type 'signed int'.
    ulCurrentIndexDate = APPDESC_CONCATENATE_DATE_BY_INDEX(ucIndex);

    if (ulLastStoredIndexDate > ulCurrentIndexDate)
    {
      // Last downloaded data found
      break;
    }
    else
    {
      // Continue searching with the next element
      ucLastDownloadedDataIndex = ucIndex;
    }
  }

  return ucLastDownloadedDataIndex;
}


//-----------------------------------------------------------------------------
/// \brief Diag_PowertrainCheck
///
/// \descr  Checking if powertrain is activated
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Diag_PowertrainCheck(void)
{
  boolean boPowertrainMode = FALSE;
  tsRte_SysMon_VehicleSpeed sDataSpeedMsg;
  tsRte_SysMon_VehNetState sEtatReseauElec;

  (void)Rte_Read_SysMon_VehicleSpeed(&sDataSpeedMsg);
  (void)Rte_Read_SysMon_VehNetState(&sEtatReseauElec);
  if (sDataSpeedMsg.eVehicleSpeed.unVehicleSpeed <= DIAG_VEHICLE_MOVING)
  {
    if (((sEtatReseauElec.eElectricNetworkState == eTI_NOMINAL) || (sEtatReseauElec.eElectricNetworkState == eTI_DEGRADE) || (sEtatReseauElec.eElectricNetworkState == eTI_DISPO_DEM))
      && (sEtatReseauElec.eVESMainState != VESState_Start))
    {
      boPowertrainMode = FALSE;
    }
  }
  else
  {
    if ((sEtatReseauElec.eElectricNetworkState == eTA_NOMINAL)
      || (sEtatReseauElec.eElectricNetworkState == eTA_DEGRADE)
      || (sEtatReseauElec.eElectricNetworkState == eTA_SECU)
      || (sEtatReseauElec.eElectricNetworkState == eREDEMARRAGE)
      || (sEtatReseauElec.eElectricNetworkState == eDEMARRAGE)
      || (sEtatReseauElec.eVESMainState == VESState_Start))
    {
      boPowertrainMode = TRUE;

    }
  }
  return boPowertrainMode;
}


//-----------------------------------------------------------------------------
/// \brief roDiag_IntegrationMode
///
/// \descr Intergration mode getter runnable
///
/// \param  void
///
/// \return boolean: TRUE - Integration accepted
//-----------------------------------------------------------------------------
boolean roDiag_IntegrationMode(void)
{
  return Diag_IntegrationMode();
}


//-----------------------------------------------------------------------------
/// \brief Diag_IntegrationMode
///
/// \descr
///
/// \param  -
///
/// \return STATIC_AL boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Diag_IntegrationMode(void)
{
  boolean boIntegrationMode = FALSE;
  tsRte_SigPrep_VehicleConfigSig  sDataVehConfig;
  tsRte_SysMon_VehicleSpeed sDataSpeedMsg;
  LEIM_TE_CurrentEIMode E_Ret;
  E_Ret = EAPI_GetCurrentEIMode();

  tsRte_SysMon_VehNetState sData432;
  (void)Rte_Read_SysMon_VehNetState(&sData432);
  (void)Rte_Read_SigPrep_VehicleConfigSig(&sDataVehConfig);
  (void)Rte_Read_SysMon_VehicleSpeed(&sDataSpeedMsg);

  if (E_Ret == LEIM_E_ACTIVE)
  {
    boIntegrationMode = TRUE;
  }
  else
  {
    if (((sData432.eSigQty == SIG_VALID) && (sData432.eVESMainState == VESState_Ignition))
      && ((sDataVehConfig.eSigQty == SIG_VALID) && ((sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Usine) || (sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Client)))
      && ((sDataSpeedMsg.eSigQty == SIG_VALID) && (sDataSpeedMsg.eVehicleSpeed.unVehicleSpeed < DIAG_VEHICLE_MOVING)
        && (sDataSpeedMsg.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoAvailable)))
    {
      boIntegrationMode = TRUE;
    }
    else
    {
      boIntegrationMode = FALSE;
    }
  }

  return boIntegrationMode;
}


//-----------------------------------------------------------------------------
/// \brief APPLI_WriteDataByIdentifier
///
/// \descr  LGM callback for diagnostic subservices for Write Data by Identifier
///
/// \param  -ui16_DID : 
///         -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_WriteDataByIdentifier(UINT16 ui16_DID, UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  if (Diag_PowertrainCheck() == TRUE)
  {
    // Negative response code - 0x22 Conditions not correct
    eReturnCode = CNC;
  }
  else
  {
    switch (ui16_DID)
    {
    case DIAG_0D00_FACTORY_DATA:
      // Diagnostic Subservice 0x2E 0x0D 0x00
      eReturnCode = Diag_Callbacks_Write_0D00_FACTORY_DATA_PROCESS_BYTE(p_ui8_Data, Length);
      break;

    case DIAG_D411_INSTRUMENTATED_FRAMES:
      // Diagnostic Subservice 0x2E 0xD4 0x11
      eReturnCode = Diag_Callbacks_Write_D411_INSTRUMENTATED_FRAMES(p_ui8_Data, Length);
      break;

    case DIAG_FD00_STATISTICS_DATA_IDENTIFIER:
      // Diagnostic Subservice 0x2E 0xFD 0x00
      eReturnCode = Diag_Callbacks_Write_FD00_STATISTICS_DATA(p_ui8_Data, Length);
      break;

    default:
      // Negative response code - 0x31 Request out of range
      eReturnCode = ROOR;
      break;
    }
  }
  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_Write_0D00_FACTORY_DATA_PROCESS_BYTE
///
/// \descr  Diagnostic subservice that writes in NVM factory data process
///
/// \param  UINT16
///         UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_Write_0D00_FACTORY_DATA_PROCESS_BYTE(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8 ucDataLength = 0u;

  tsRte_SysMon_VehNetState sData432;
  (void)Rte_Read_SysMon_VehNetState(&sData432);

  tiu32Voltage_mV u32Voltage_mV;
  // Rte call for Vbat voltage
  (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(&u32Voltage_mV);

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_2BYTES] = { 0u };

  if (Length != DIAG_RESP_1BYTE)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else if (sData432.eVESMainState == VESState_Start)
  {
    // Negative response code - 0x83 engine is running
    eReturnCode = EIR;
  }
  else if (p_ui8_Data[0] > DIAG_MAX_FACTORY_DATA)
  {
    // Negative response code - 0x31 request out of range
    eReturnCode = ROOR;
  }
  else if (u32Voltage_mV < 8000UL)
  {
    eReturnCode = VTL;
  }
  else
  {
    aucResData[0] = DIAG_0D00_DID_1;
    aucResData[1] = DIAG_0D00_DID_2;

    NvmBlockFactoryData = p_ui8_Data[0];

    (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockFactoryDataId, (void*)&NvmBlockFactoryData);

    ucDataLength = DIAG_RESP_2BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }
  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_Write_D411_INSTRUMENTATED_FRAMES
///
/// \descr  Diagnostic subservice that activates/deactivates instrumentated frames
///
/// \param  UINT16
///         UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_Write_D411_INSTRUMENTATED_FRAMES(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8 ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_2BYTES] = { 0u };

  if (Length != DIAG_RESP_1BYTE)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else if (p_ui8_Data[0] > 0x01U)
  {
    // Negative response code - 0x31 Request Out of Range
    eReturnCode = ROOR;
  }
  else
  {
    aucResData[0] = DIAG_D411_DID_1;
    aucResData[1] = DIAG_D411_DID_2;

    NvmBlockInstrumentatedFrames = p_ui8_Data[0];

    (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockInstrumentatedFramesId, (void*)&NvmBlockInstrumentatedFrames);

    ucDataLength = DIAG_RESP_2BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_Write_FD00_STATISTICS_DATA
///
/// \descr  Diagnostic subservice to reset the NvM statistics
///
/// \param  UINT16
///         UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_Write_FD00_STATISTICS_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8 ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_2BYTES] = { 0u };


  if (Length != DIAG_RESP_1BYTE)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = DIAG_FD00_DID_1;
    aucResData[1] = DIAG_FD00_DID_2;
    (void)p_ui8_Data;

    // Write the RTE port with request
    (void)Rte_Write_Diag_ResetStatistics(TRUE);

    ucDataLength = DIAG_RESP_2BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }
  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief APPLI_ReadDataByIdentifier
///
/// \descr  LGM callback for diagnostic subservices for Read Data by Identifier
///
/// \param  -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_ReadDataByIdentifier(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  uint16 unDID = (uint16)((uint16)((uint16)p_ui8_Data[0] << 8u) | (uint16)p_ui8_Data[1]);

  switch (unDID)
  {
  case DIAG_0D00_FACTORY_DATA:
    // Diagnostic Subservice 0x22 0x0D 0x00
    eReturnCode = Diag_Callbacks_0D00_FACTORY_DATA_PROCESS_BYTE(p_ui8_Data, Length);
    break;

  case DIAG_0D01_SIZE_ECU_SERIAL_NUMBER_IDENTIFIER:
    // Diagnostic Subservice 0x22 0x0D 0x01
    eReturnCode = Diag_Callbacks_0D01_SIZE_OF_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(p_ui8_Data, Length);
    break;

  case DIAG_1100_CPU_LOAD_DEVICE:
    // Diagnostic Subservice 0x22 0x11 0x00
    eReturnCode = Diag_Callbacks_1100_CPU_LOAD_OF_DEVICE(p_ui8_Data, Length);
    break;

  case DIAG_C002_SIZE_FOR_MULTI_DID:
    // Diagnostic Subservice 0x22 0xC0 0x02
    eReturnCode = Diag_Callbacks_C002_SIZE_FOR_MULTI_DID(p_ui8_Data, Length);
    break;

  case DIAG_D400_PIXEL_LED_STATUS:
    // Diagnostic Subservice 0x22 0xD4 0x00
    eReturnCode = Diag_Callbacks_D400_PIXEL_LED_STATUS(p_ui8_Data, Length);
    break;

  case DIAG_D401_FAN1_STATUS:
    // Diagnostic Subservice 0x22 0xD4 0x01
    eReturnCode = Diag_Callbacks_D401_FAN1_STATUS(p_ui8_Data, Length);
    break;

  case DIAG_D402_FAN2_STATUS:
    // Diagnostic Subservice 0x22 0xD4 0x02
    eReturnCode = Diag_Callbacks_D402_FAN2_STATUS(p_ui8_Data, Length);
    break;

  case DIAG_D404_SCROLLING_CTRL_OUTPUT_STATE:
    // Diagnostic Subservice 0x22 0xD4 0x04
    eReturnCode = Diag_Callbacks_D404_SCROLLING_CTRL_OUTPUT_STATE(p_ui8_Data, Length);
    break;

  case DIAG_D405_LED_CHANNEL_OUTPUT_STATE:
    // Diagnostic Subservice 0x22 0xD4 0x05
    eReturnCode = Diag_Callbacks_D405_LED_CH_OUTPUT_STATE(p_ui8_Data, Length);
    break;

  case DIAG_D406_LIGHT_DIST_STATUS:
    // Diagnostic Subservice 0x22 0xD4 0x06
    eReturnCode = Diag_Callbacks_D406_LD_STATUS(p_ui8_Data, Length);
    break;

  case DIAG_D407_NTC_RBIN_DATA:
    // Diagnostic Subservice 0x22 0xD4 0x07
    eReturnCode = Diag_Callbacks_D407_NTC_RBIN_DATA(p_ui8_Data, Length);
    break;

  case DIAG_D408_DERATING_FACTOR_AND_TEMP:
    // Diagnostic Subservice 0x22 0xD4 0x08
    eReturnCode = Diag_Callbacks_D408_DERATING_FACTOR_AND_TEMP(p_ui8_Data, Length);
    break;

  case DIAG_D409_CURRENT_BINNING_CLASS:
    // Diagnostic Subservice 0x22 0xD4 0x09
    eReturnCode = Diag_Callbacks_D409_CURRENT_BINNING_CLASS(p_ui8_Data, Length);
    break;

  case DIAG_D410_DIAG_SCROLLING_INPUT_STATE:
    // Diagnostic Subservice 0x22 0xD4 0x10
    eReturnCode = Diag_Callbacks_D410_DIAG_SCROLLING_INPUT_STATE(p_ui8_Data, Length);
    break;

  case DIAG_D411_INSTRUMENTATED_FRAMES:
    // Diagnostic Subservice 0x22 0xD4 0x11
    eReturnCode = Diag_Callbacks_D411_INSTRUMENTATED_FRAMES(p_ui8_Data, Length);
    break;

  case DIAG_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION:
    // Diagnostic Subservice 0x22 0xD4 0x20
    eReturnCode = Diag_Callbacks_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION(p_ui8_Data, Length);
    break;

  case DIAG_D421_RBIN_EEPROM_LMM_DIAGNOSIS:
    // Diagnostic Subservice 0x22 0xD4 0x21
    eReturnCode = Diag_Callbacks_D421_RBIN_EEPROM_LMM_DIAGNOSIS(p_ui8_Data, Length);
    break;

  case DIAG_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS:
    // Diagnostic Subservice 0x22 0xD4 0x22
    eReturnCode = Diag_Callbacks_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS(p_ui8_Data, Length);
    break;

  case DIAG_D4C5_LIGHTING_ENG_DATA:
    // Diagnostic Subservice 0x22 0xD4 0xC5
    eReturnCode = Diag_Callbacks_D4C5_LIGHTING_ENG_DATA(p_ui8_Data, Length);
    break;

  case DIAG_D4C6_SIGNALLING_ENG_DATA:
    // Diagnostic Subservice 0x22 0xD4 0xC6
    eReturnCode = Diag_Callbacks_D4C6_SIGNALLING_ENG_DATA(p_ui8_Data, Length);
    break;

  case DIAG_D4C7_TURN_IND_ENG_DATA:
    // Diagnostic Subservice 0x22 0xD4 0xC7
    eReturnCode = Diag_Callbacks_D4C7_TURN_IND_ENG_DATA(p_ui8_Data, Length);
    break;

  case DIAG_D4C8_BODY_HIGH_SENSOR_ENG_DATA:
    // Diagnostic Subservice 0x22 0xD4 0xC8
    eReturnCode = Diag_Callbacks_D4C8_BODY_HIGH_SENSOR_ENG_DATA(p_ui8_Data, Length);
    break;

  case DIAG_D4C9_ATTITUDE_ENG_DATA:
    // Diagnostic Subservice 0x22 0xD4 0xC9
    eReturnCode = Diag_Callbacks_D4C9_ATTITUDE_ENG_DATA(p_ui8_Data, Length);
    break;

  case DIAG_D4CB_LEVELLING_ENG_DATA:
    // Diagnostic Subservice 0x22 0xD4 0xCB
    eReturnCode = Diag_Callbacks_D4CB_LEVELLING_ENG_DATA(p_ui8_Data, Length);
    break;

  case DIAG_D4CD_RGB_LED:
    // Diagnostic Subservice 0x22 0xD4 0xCD
    eReturnCode = Diag_Callbacks_D4CD_RGB_LED(p_ui8_Data, Length);
    break;

  case DIAG_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES:
    // Diagnostic Subservice 0x22 0xE8 0x88
    eReturnCode = Diag_Callbacks_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES(p_ui8_Data, Length);
    break;

  case DIAG_F080_AUTHENTIFICATION_ZONE:
    // Diagnostic Subservice 0x22 0xF0 0x80
    eReturnCode = Diag_Callbacks_F080_AUTHENTIFICATION_ZONE(p_ui8_Data, Length);
    break;

  case DIAG_F08F_EMC_STANDARDIZATION_LABEL:
    // Diagnostic Subservice 0x22 0xF0 0x8F
    eReturnCode = Diag_Callbacks_F08F_EMC_STANDARDIZATION_LABEL(p_ui8_Data, Length);
    break;

  case DIAG_F0FE_IDENTIFICATION_ZONE:
    // Diagnostic Subservice 0x22 0xF0 0xFE
    eReturnCode = Diag_Callbacks_F0FE_IDENTIFICATION_ZONE(p_ui8_Data, Length);
    break;

  case DIAG_F186_ACTIVE_DIAG_SESSION_IDENTIFIER:
    // Diagnostic Subservice 0x22 0xF1 0x86
    eReturnCode = Diag_Callbacks_F186_Active_Diag_Session_Data_Identifier(p_ui8_Data, Length);
    break;

  case DIAG_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER:
    // Diagnostic Subservice 0x22 0xF1 0x8B
    eReturnCode = Diag_Callbacks_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER(p_ui8_Data, Length);
    break;

  case DIAG_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER:
    // Diagnostic Subservice 0x22 0xF1 0x8C
    eReturnCode = Diag_Callbacks_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(p_ui8_Data, Length);
    break;

  case DIAG_FD00_STATISTICS_DATA_IDENTIFIER:
    // Diagnostic Subservice 0x22 0xFD 0x00
    eReturnCode = Diag_Callbacks_FD00_STATISTICS_DATA(p_ui8_Data, Length);
    break;

  case DIAG_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS:
    // Diagnostic Subservice 0x22 0xFD 0x01
    eReturnCode = Diag_Callbacks_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS(p_ui8_Data, Length);
    break;

  case DIAG_FD02_ECU_SERIAL_NUMBER_DATA_IDENTIFIER:
    // Diagnostic Subservice 0x22 0xFD 0x02
    eReturnCode = Diag_Callbacks_FD02_INTERNAL_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(p_ui8_Data, Length);
    break;

  case DIAG_FD03_READ_ACTIVE_ALECS:
    // Diagnostic Subservice 0x22 0xFD 0x03
    eReturnCode = Diag_Callbacks_FD03_READ_ACTIVE_ALECS(p_ui8_Data, Length);
    break;

  case DIAG_FD04_INTERNAL_SOFTWARE_LABEL:
    // Diagnostic Subservice 0x22 0xFD 0x04
    eReturnCode = Diag_Callbacks_FD04_INTERNAL_SW_LABEL(p_ui8_Data, Length);
    break;

  default:
    // Negative response code - 0x31 Request out of range
    eReturnCode = ROOR;
    break;
  }

  return eReturnCode;
  //PRQA S 5316, 5324, 5330 1 // Multiple function calls needed to handle all RDBI diagnostic services
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_0D00_FACTORY_DATA_PROCESS_BYTE
///
/// \descr  Diagnostic subservice that returns factory data process byte
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_0D00_FACTORY_DATA_PROCESS_BYTE(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = (uint8)NvmBlockFactoryData;
    ucDataLength = DIAG_RESP_3BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);

  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_0D01_SIZE_OF_ECU_SERIAL_NUMBER_DATA_IDENTIFIER
///
/// \descr  Diagnostic subservice that returns size of ecu serial number
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_0D01_SIZE_OF_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = DIAG_SERIAL_NUMBER_DID_F18C_SIZE;
    ucDataLength = DIAG_RESP_3BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_1100_CPU_LOAD_OF_DEVICE
///
/// \descr  Diagnostic subservice that returns cpu load of device
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_1100_CPU_LOAD_OF_DEVICE(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;
  uint8 ucStackUsage = 0u;
  uint8 ucPeakCPU = 0u;
  uint8 ucAvgCPU = 0u;
  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_6BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = DIAG_RESP_3BYTES;
    (void)Rte_Read_OS_CPULoadPeak(&ucPeakCPU);
    (void)Rte_Read_OS_CPULoadAvg(&ucAvgCPU);
    (void)Rte_Read_StatM_StackUsage(&ucStackUsage);
    aucResData[3] = (ucPeakCPU <= 100u) ? (ucPeakCPU * 255u) / 100u : 255u;    // CPU Load peak (0..255)   <==> (1%..100%)
    aucResData[4] = (ucAvgCPU <= 100u) ? (ucAvgCPU * 255u) / 100u : 255u;    // CPU Load peak (0..255)   <==> (1%..100%)
    aucResData[5] = (ucStackUsage <= 100u) ? (ucStackUsage * 255u) / 100u : 255u;    // Stack Load peak (0..255) <==> (1%..100%)
    ucDataLength = DIAG_BUFFER_6BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_FD00_STATISTICS_DATA
///
/// \descr  Diagnostic subservice that returns all statistics Data
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_FD00_STATISTICS_DATA(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  Diag_Length_Type  unDataLength = 0u;

  tstStatistics sStatistics;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[sizeof(tstStatistics) + DIAG_BUFFER_2BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    //read direct from NvM block
    (void)memcpy(&sStatistics, &NvmBlockStatistics.sStatistics, sizeof(tstStatistics));
    //process statistics (convert time statistic data from seconds to hours)
    STATM_S_TO_H(sStatistics.ulEcuOnTime);
    STATM_S_TO_H(sStatistics.ulStepperHoldTime);
    STATM_S_TO_H(sStatistics.ulStepperMoveTime);
    for (uint8 ucI = 0; ucI < STATM_MAX_FAN_NR; ucI++)
    {
      STATM_S_TO_H(sStatistics.ulFanOnTime[ucI]);
    }
    for (uint8 ucI = 0; ucI < STATM_MAX_LED_CHN; ucI++)
    {
      STATM_S_TO_H(sStatistics.ulLedOnTime[ucI]);
    }
    for (uint8 ucI = 0; ucI < STATM_TEMP_CLASSES; ucI++)
    {
      STATM_S_TO_H(sStatistics.ulPCBTempTime[ucI]);
    }
    for (uint8 ucI = 0; ucI < STATM_MAX_TEMP_ZONES; ucI++)
    {
      for (uint8 ucJ = 0; ucJ < STATM_TEMP_CLASSES; ucJ++)
      {
        STATM_S_TO_H(sStatistics.ulTempZoneTime[ucI][ucJ]);
      }
    }
    //copy the processed Statistic values into Diagnostic Response
    (void)memcpy(&aucResData[2], &sStatistics, sizeof(tstStatistics));

    unDataLength = sizeof(aucResData);
    eReturnCode = DIAG_Send_Diag_Response(aucResData, unDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_C002_SIZE_FOR_MULTI_DID
///
/// \descr  Diagnostic subservice that returns the maximum size of the response buffer
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_C002_SIZE_FOR_MULTI_DID(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_4BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = (uint8)(DIAG_BUFFER_MAXSIZE >> DIAG_8BIT_SHIFT);
    aucResData[3] = (uint8)DIAG_BUFFER_MAXSIZE;
    ucDataLength = DIAG_RESP_4BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D400_PIXEL_LED_STATUS
///
/// \descr  Diagnostic subservice that returns pixel led status (pwm and error flag)
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D400_PIXEL_LED_STATUS(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;
#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;
  //read CPM target MLC PWM values on logical units
  uint16 aunPixelIntensities[CFG_LOGICAL_UNITS] = { 0x00u };

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_208BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    tauRte_CtrlPxl_Mtx_bErr auMatrixErrors;
    (void)Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal(&auMatrixErrors);

    //get input MLC PWM intensities (power factor applied)
      //PRQA S 310 1 // Cast needed
    (void)Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels((tsRte_TgtPxlSig0Arr*)aunPixelIntensities);

    for (uint8_fast ucIx = 0u; ucIx < CFG_LOGICAL_UNITS; ucIx++)
    {

      aucResData[DIAG_START_INDEX_2 + ucIx * 2u] = (uint8)DIAG_FIND_PERCENTAGE_PWM(DIAG_DO_SCALLING_FOR_MLC(aunPixelIntensities[ucIx]));

      aucResData[DIAG_START_INDEX_2 + ucIx * 2u + 1u] = auMatrixErrors.auMtxErrorStatus[ucIx].bErr.bPxlFault;

    }
    ucDataLength = DIAG_BUFFER_208BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);

  }
#else
  // Eco variant, return service not supported
  (void)p_ui8_Data;
  (void)Length;

  eReturnCode = SFNS;

#endif

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D401_FAN1_STATUS
///
/// \descr  Diagnostic subservice that returns fan status
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D401_FAN1_STATUS(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{

  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Handle coding data
    CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

    // Check coding validation
    if (boCodingValidity != FALSE)
    {
      // Check if FAN1 is present in Coding
      if (Diag_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled == DIAG_OPTION_ENABLED)
      {
        tisHssStatusError       atStatusError;

        // Get FAN1 Status Error from CtrlSwi
        (void)Rte_Read_CtrlSwi_StatusErr(&atStatusError);

        aucResData[0] = p_ui8_Data[0];
        aucResData[1] = p_ui8_Data[1];

        // Check FAN1 status
        switch (atStatusError.eStatOn[FAN_1])
        {
        case ON:
          // Status On
          aucResData[2] = DIAG_FAN_ON;
          break;
        case OFF:
          // Status Off
          aucResData[2] = DIAG_FAN_OFF;
          break;
        default:
          // Status Unknown
          aucResData[2] = DIAG_FAN_UNKOWN;
          break;
        }

        ucDataLength = DIAG_RESP_3BYTES;
        eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
      }
      else
      {
        // FAN1 is not present, NRC 0x12 Sub Function Not Supported
        eReturnCode = SFNS;
      }
    }
    else
    {
      // Coding is invalid, NRC 0x22 Conditions Not Correct 
      eReturnCode = CNC;
    }
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D402_FAN2_STATUS
///
/// \descr  Diagnostic subservice that returns fan status
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D402_FAN2_STATUS(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Handle coding data
    CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

    // Check coding validation
    if (boCodingValidity != FALSE)
    {
      // Check if FAN2 is present in Coding
      if (Diag_pCodingArea->Fan1.Fans_Presence.ucFan2Enabled == DIAG_OPTION_ENABLED)
      {
        tisHssStatusError       atStatusError;

        // Get FAN2 Status Error from CtrlSwi
        (void)Rte_Read_CtrlSwi_StatusErr(&atStatusError);

        aucResData[0] = p_ui8_Data[0];
        aucResData[1] = p_ui8_Data[1];

        // Check FAN2 status
        switch (atStatusError.eStatOn[FAN_2])
        {
        case ON:
          // Status On
          aucResData[2] = DIAG_FAN_ON;
          break;
        case OFF:
          // Status Off
          aucResData[2] = DIAG_FAN_OFF;
          break;
        default:
          // Status Unknown
          aucResData[2] = DIAG_FAN_UNKOWN;
          break;
        }

        ucDataLength = DIAG_RESP_3BYTES;
        eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
      }
      else
      {
        // FAN2 is not present, NRC 0x12 Sub Function Not Supported
        eReturnCode = SFNS;
      }
    }
    else
    {
      // Coding is invalid, NRC 0x22 Conditions Not Correct 
      eReturnCode = CNC;
    }
  }
#else
  // Eco variant, return service not supported
  (void)Length;
  (void)p_ui8_Data;

  eReturnCode = SFNS;

#endif

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D404_SCROLLING_CTRL_OUTPUT_STATE
///
/// \descr  Diagnostic subservice that returns the scrolling control output state
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D404_SCROLLING_CTRL_OUTPUT_STATE(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  // TI Scrolling is not available yet, return service not supported
  DIAG_status eReturnCode = DIAG_NOK;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)

  // Scrolling Output Value
  teRte_SateliteStatus eScrollingSatellite_Ctrl = eRte_ScrollingSatelite_Off;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Handle coding data
    CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

    // Check coding validation
    if (boCodingValidity != FALSE)
    {
      boolean boIsScrlPresent = Diag_Callbacks_Check_If_Scrolling_Present();

      // Check if Scrolling is present
      if (boIsScrlPresent != FALSE)
      {
        // Read Ti scrolling cmd
        (void)Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite(&eScrollingSatellite_Ctrl);

        // Fill default data
        aucResData[0] = p_ui8_Data[0];
        aucResData[1] = p_ui8_Data[1];

        // Switch last byte of response based on Ti scrolling Cmd
        switch (eScrollingSatellite_Ctrl)
        {
        case eRte_eScrollingSatelite_On_Scrolling_On: aucResData[2] = 0x02u; break;
        case eRte_eScrollingSatelite_On_Scrolling_Off: aucResData[2] = 0x01u; break;
        default: aucResData[2] = 0x00u; break;
        }

        // Set diagnostic response
        ucDataLength = DIAG_RESP_3BYTES;
        eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
      }
      else
      {
        // Scrolling is not present, NRC 0x12 Sub Function Not Supported
        eReturnCode = SFNS;
      }

    }
    else
    {
      // Coding is invalid, NRC 0x22 Conditions Not Correct 
      eReturnCode = CNC;
    }
  }
#else
  (void)p_ui8_Data;
  (void)Length;
  eReturnCode = SFNS;
#endif

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief  Diag_Callbacks_D405_LED_CH_OUTPUT_STATE
///
/// \descr  Diagnostic subservice that returns the LED channel output state
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D405_LED_CH_OUTPUT_STATE(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;
  uint8_fast ucIndex;
  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;
  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_62BYTES] = { 0u };

  tCddLedStatus              sRte_LedStatus;
  tsRte_SysMon_LedStates     sRte_LedStates;
  tsRte_TgtLedSig0Arr        sRte_LedVal;
  tsRte_CtrlLed_ChStatesDiag sCtrlLedErrStateArr = { 0 };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    //positive response
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    //used to read forward voltage
    (void)Rte_Read_CddLed_Status(&sRte_LedStatus);
    //read led state 
    (void)Rte_Read_CtrlLed_ChState(&sCtrlLedErrStateArr);
    //led channel values (pwm and current)
    (void)Rte_Read_Cpm_TgtLedSig_sVal(&sRte_LedVal);
    // Fill in the response buffer with the received values 
    for (ucIndex = 0u; ucIndex < CFG_LED_CHANNELS_NR; ucIndex++)
    {
      aucResData[DIAG_START_INDEX_2 + ucIndex * 5u] = DIAG_FIND_PERCENTAGE_PWM(sRte_LedVal[ucIndex].unDutyCycle);
      aucResData[DIAG_START_INDEX_2 + ucIndex * 5u + 1u] = (uint8)((sCtrlLedErrStateArr.aboChStates[ucIndex] != FALSE) ? 1U : 0U);
      aucResData[DIAG_START_INDEX_2 + ucIndex * 5u + 2u] = (uint8)((sRte_LedVal[ucIndex].unCurrent & 0xFF00u) >> 8u);
      aucResData[DIAG_START_INDEX_2 + ucIndex * 5u + 3u] = (uint8)(sRte_LedVal[ucIndex].unCurrent & 0xFFu);
      aucResData[DIAG_START_INDEX_2 + ucIndex * 5u + 4u] = (uint8)(sRte_LedStatus.aStatus[ucIndex].unVLed / 1000u); //???please update the excel file 
    }
    ucDataLength = DIAG_BUFFER_62BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}

//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D406_LD_STATUS
///
/// \descr  Diagnostic subservice that returns ld status
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D406_LD_STATUS(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  uint32 ulLDraw = 0U;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = 0xFFU;

    ulLDraw = Diag_Callback_CheckLastLightReq_Activated();

    const uint8 ucRemapLight[DIAG_NR_LD] = {
      /*0*/  0x01U, //Tonw
      /*1*/  0x02U, //Pedestrian
      /*2*/  0x03U, //Country
      /*3*/  0x04U, //MotorWay
      /*4*/  0x05U, //LB Boost
      /*5*/  0x07U, //AdvWth_RHD
      /*6*/  0x09U, //FogyRHD
      /*7*/  0x06U, //AdvWth_LHD
      /*8*/  0x08U, //FogyLHD
      /*9*/  0x0AU, //reserved
      /*10*/ 0x0BU, //reserved
      /*11*/ 0x0CU, //reserved
      /*12*/ 0x0DU, //reserved
      /*13*/ 0x0EU, //HB
      /*14*/ 0x0FU, //HBBoost
      /*15*/ 0x10U, //AimingMode
      /*16*/ 0x11U, //AdjMode
      /*17*/ 0x0EU, //HB F2P
      /*18*/ 0x12U, //reserved
      /*19*/ 0x13U, //reserved
      /*20*/ 0x14U, //reserved
      /*21*/ 0x15U, //reserved
      /*22*/ 0x17U, //DRL
      /*23*/ 0x18U, //POS
      /*24*/ 0x19U, //parking light
      /*25*/ 0x1AU, //SBL
      /*26*/ 0x1BU, //CL
      /*27*/ 0x1CU, //fog
      /*28*/ 0x1DU, //SM
      /*29*/ 0x1EU, //TI
      /*30*/ 0x1FU, //TIPOS
      /*31*/ 0x20U, //scrolling
    };

    if (ulLDraw != 0U)
    {
      for (uint8_fast ucIx = 0U; ucIx < DIAG_NR_LD; ucIx++)
      {
        if ((ulLDraw & (uint32)((uint32)1u << ucIx)) != 0u)
        {
          aucResData[2] = ucRemapLight[ucIx];
          break;
        }
      }
    }

    ucDataLength = DIAG_RESP_3BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_Diag_CheckLastLightReq_Activated
///
/// \descr   this function returns last active light reqest 
///
/// \param  void
///
/// \return uint32
//-----------------------------------------------------------------------------
STATIC_AL uint32 Diag_Callback_CheckLastLightReq_Activated(void)
{
  uint32 ulLDraw;
  STATIC_UT(uint32, ulLDrawPrv, 0U);
  STATIC_UT(uint32, ulLDrawDiag, 0U);
  //read current light request
  (void)Rte_Read_FctR_LgtDistStatus(&ulLDraw);

  uint32 ulVal = ulLDraw, ulLastVal = 0U;
  uint8 ucCount = 0u;
  //this algorithm cannot guarantee which was last light request when 2 or more are requested
  if (ulLDrawPrv != ulLDraw)
  {
    //count how many lights are requested simultaneous
    while (ulVal != 0U)
    {
      ulLastVal = ulVal;
      ulVal &= (ulVal - 1U);
      ucCount++;
    }

    // check if more than 1 light are requested
    if (ucCount > 1U)
    {
      ulLDrawDiag = ((ulLDraw ^ ulLDrawPrv) & ulLDraw);
      //in case the results is 0 apply arbitrary answer
      if (ulLDrawDiag == 0U)
      {
        ulLDrawDiag = ulLastVal;
      }
    }
    else
    {
      ulLDrawDiag = ulLastVal;
    }

    ulLDrawPrv = ulLDraw;
  }

  return ulLDrawDiag;
}
//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D407_NTC_RBIN_DATA
///
/// \descr  Diagnostic subservice that returns analog inputs, lmm inputs and PCB temperature
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D407_NTC_RBIN_DATA(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;


  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  uint16 unNTCVoltage = 0u;
  uint16 unLMMVoltage = 0u;
  uint8 ucNtcIndex = 2u;
  uint8 ucLmmIndex = 30u;
  tsRte_PcbTemperatureMsg sTempPCB;


  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_60BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
    tasRte_MlcAdcResult asLmmAdc = { 0u };
    (void)Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal(&asLmmAdc);
#endif

    for (uint8 ucIdx = 0u; ucIdx < DIAG_MAX_NO_OF_EXT_NTCS; ucIdx++)
    {
      unNTCVoltage = IoHwAbUser_GetVoltage_NTCs(ucIdx);
      aucResData[ucNtcIndex] = (uint8)((IoHwAbUser_GetVoltage_NTCs(ucIdx) & 0xFF00u) >> 8u);
      ucNtcIndex++;
      aucResData[ucNtcIndex] = (uint8)(IoHwAbUser_GetVoltage_NTCs(ucIdx) & 0xFFu);
      ucNtcIndex++;

      if (ucIdx < 7u)
      {
#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
        unLMMVoltage = DIAG_ROWADC8BIT_TO_MV(asLmmAdc[ucIdx].ucADC1Value);
#else
        unLMMVoltage = 0u;
#endif
      }
      else
      {
#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
        unLMMVoltage = DIAG_ROWADC8BIT_TO_MV(asLmmAdc[ucIdx % CFG_MLC_Chip_Cnt].ucADC2Value);
#else
        unLMMVoltage = 0u;
#endif
      }
      aucResData[ucLmmIndex] = (uint8)((unLMMVoltage & 0xFF00u) >> 8u);
      ucLmmIndex++;
      aucResData[ucLmmIndex] = (uint8)(unLMMVoltage & 0xFFu);
      ucLmmIndex++;
    }
    (void)Rte_Read_RSens_PcbTemperature(&sTempPCB);
    uint16 unPcbTemp = (uint16)ErrCust_ConvertValueSint2Int(sTempPCB.nVal, 16u) / 10u;
    aucResData[58] = (uint8)((unPcbTemp & 0xFF00u) >> 8u);
    aucResData[59] = (uint8)((unPcbTemp & 0xFFu));
    ucDataLength = DIAG_BUFFER_60BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);

  }

  return eReturnCode;

}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D408_DERATING_FACTOR_AND_TEMP
///
/// \descr  Diagnostic subservice that returns derating factors and temperatures
///         per thermozone (12)
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D408_DERATING_FACTOR_AND_TEMP(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  uint16 unNtcTemperature = 0u;

  tsRtePowFactTemp sPowFactTemp = { 0 };

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_38BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Add 2 bytes DID 0xD408
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    // Read power factor and temperature per thermozone
    (void)Rte_Read_Cpm_PowFact_Temp(&sPowFactTemp);

    for (uint8 ucIdx = 0u; ucIdx < DIAG_NO_OF_THERMO_ZONES; ucIdx++)
    {
      // Add Derating Power factors on bytes 3 to 14
      aucResData[DIAG_START_INDEX_2 + ucIdx] = sPowFactTemp.ucPowerFactor[ucIdx];

      // Convert temperature from signed to unsigned
      unNtcTemperature = (uint16)ErrCust_ConvertValueSint2Int(sPowFactTemp.snNTCTemperatureCelsius[ucIdx], DIAG_LENGTH_TEMP_THERMO);

      // Add Temperatures per Thermozones on bytes 15 to 38
      aucResData[(ucIdx * 2u) + DIAG_OFFSET_INDEX_14] = (uint8)(unNtcTemperature >> DIAG_8BIT_SHIFT);
      aucResData[(ucIdx * 2u) + DIAG_OFFSET_INDEX_14 + 1u] = (uint8)(unNtcTemperature & DIAG_8_BIT_MASK);
    }

    ucDataLength = DIAG_BUFFER_38BYTES;

    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D409_CURRENT_BINNING_CLASS
///
/// \descr  Diagnostic subservice that returns current output and binning class
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D409_CURRENT_BINNING_CLASS(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  uint8 ucIxCurrent = 2u;
  uint8 ucIxBinning = 30u;

  tsRte_D409Binning sBinningData;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[44u] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    //read target from CtrlLed
    (void)Rte_Read_RSens_BinningDataDiag(&sBinningData);

    for (uint8 ucIx = 0u; ucIx < DIAG_MAX_NO_OF_EXT_NTCS; ucIx++)
    {
      aucResData[ucIxCurrent] = (uint8)((sBinningData.aunBinCurrent[ucIx] & 0xFF00u) >> 8u);
      ucIxCurrent++;
      aucResData[ucIxCurrent] = (uint8)(sBinningData.aunBinCurrent[ucIx] & 0xFFu);
      ucIxCurrent++;

      aucResData[ucIxBinning] = sBinningData.aucBinClass[ucIx];
      ucIxBinning++;
    }
    ucDataLength = 44u;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);

  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D410_DIAG_SCROLLING_INPUT_STATE
///
/// \descr  Diagnostic subservice that returns the scrolling input state (pwm)
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D410_DIAG_SCROLLING_INPUT_STATE(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  // TI Scrolling is not available yet, return service not supported
  DIAG_status eReturnCode = DIAG_NOK;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Handle coding data
    CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

    // Check coding validation
    if (boCodingValidity != FALSE)
    {
      boolean boIsScrlPresent = Diag_Callbacks_Check_If_Scrolling_Present();

      // Check if Scrolling is present
      if (boIsScrlPresent != FALSE)
      {
        // Fill default data
        aucResData[0] = p_ui8_Data[0];
        aucResData[1] = p_ui8_Data[1];

        // Get the LSS PWM output
        aucResData[2] = (CddSbc_GetPWM(1u) <= 10000u) ? (uint8)((10000u - CddSbc_GetPWM(1u)) / 100u) : 0u; //formula for PWM output used since output is LSS and logic is reversed, 
                                                                                                           //0 means 100% duty cycle and vice versa

        // Set diagnostic response
        ucDataLength = DIAG_RESP_3BYTES;
        eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
      }
      else
      {
        // Scrolling is not present, NRC 0x12 Sub Function Not Supported
        eReturnCode = SFNS;
      }
    }
    else
    {
      // Coding is invalid, NRC 0x22 Conditions Not Correct 
      eReturnCode = CNC;
    }
  }
#else
  (void)p_ui8_Data;
  (void)Length;
  eReturnCode = SFNS;
#endif

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D411_FACTORY_DATA_PROCESS_BYTE
///
/// \descr  Diagnostic subservice that returns if instrumentated frames are activated
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D411_INSTRUMENTATED_FRAMES(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;
  uint8 ucInstrumentedFrames = 0u;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Read Instrumented Frames status byte
    ucInstrumentedFrames = (uint8)NvmBlockInstrumentatedFrames;

    // Instrumented frames invalid
    if (ucInstrumentedFrames > 1u)
    {
      // Negative response code - 0x31 request out of range
      eReturnCode = ROOR;
    }
    else
    {
      aucResData[0] = p_ui8_Data[0];
      aucResData[1] = p_ui8_Data[1];
      aucResData[2] = ucInstrumentedFrames;
      ucDataLength = DIAG_RESP_3BYTES;
      // Positive response with diagnostic data
      eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
    }
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION
///
/// \descr  Diagnostic subservice that returns the RBIN/NTC failure per light function
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;
  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;
  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_4BYTES] = { 0u };
  // Aftermarket RBIN/NTC Failure data
  tsErrCust_AftermarketRbinNtcFailureData sRbinNtcFailEcuData = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Handle coding data
    CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

    // Check coding validation
    if (boCodingValidity != FALSE)
    {
      // Positive response
      aucResData[0] = p_ui8_Data[0];
      aucResData[1] = p_ui8_Data[1];

      // Capture RBIN/NTC Failure data (0xD420)
      ErrCust_CaptureAftermarketRbinNtcFailureEcuData(&sRbinNtcFailEcuData);

      // Populate byte with Error Per Light Function
      aucResData[DIAG_START_INDEX_2] = sRbinNtcFailEcuData.ucErrPerLightFunc;

      // Set reserved dumy byte
      aucResData[DIAG_START_INDEX_3] = DIAG_RESERVED_BYTE;

      ucDataLength = DIAG_BUFFER_4BYTES;

      eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
    }
    else
    {
      // Coding is invalid, NRC 0x22 Conditions Not Correct 
      eReturnCode = CNC;
    }
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D421_RBIN_EEPROM_LMM_DIAGNOSIS
///
/// \descr  Diagnostic subservice that returns the RBIN and EEPROM LMM diagnosis
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D421_RBIN_EEPROM_LMM_DIAGNOSIS(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status       eReturnCode = DIAG_NOK;
  // Variable used for storing the diagnostic response length
  uint8             ucDataLength = 0u;
  // Variable used for storing the diagnostic response data
  uint8             aucResData[DIAG_BUFFER_7BYTES] = { 0u };
  // Aftermarket RBIN EEPROM LMM data
  tsErrCust_AftermarketRbinEepromLmmData sRbinEepromLmmEcuData = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Handle coding data
    CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

    // Check coding validation
    if (boCodingValidity != FALSE)
    {
       // Positive response
      aucResData[0] = p_ui8_Data[0];
      aucResData[1] = p_ui8_Data[1];

      // Capture RBIN EEPROM LMM data (0xD421)
      ErrCust_CaptureAftermarketRbinEepromLmmEcuData(&sRbinEepromLmmEcuData);

      // Set all the data bytes
      aucResData[DIAG_START_INDEX_2] = sRbinEepromLmmEcuData.ucFirstByte;
      aucResData[DIAG_START_INDEX_3] = sRbinEepromLmmEcuData.ucSecondByte;
      aucResData[DIAG_START_INDEX_4] = sRbinEepromLmmEcuData.ucThirdByte;
      aucResData[DIAG_START_INDEX_5] = sRbinEepromLmmEcuData.ucFourthByte;
      aucResData[DIAG_START_INDEX_6] = sRbinEepromLmmEcuData.ucFifthByte;

      ucDataLength = DIAG_BUFFER_7BYTES;

      eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
    }
    else
    {
      // Coding is invalid, NRC 0x22 Conditions Not Correct 
      eReturnCode = CNC;
    }
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief    Diag_Callbacks_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS
///
/// \descr    Diagnostic subservice that returns the external matrix Eeprom Data
///
/// \param  p_ui8_Data
/// \param  Length
///
/// \return STATIC_AL DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

#if defined CFG_VARIANT_FULL || defined (UNIT_TEST)

  // Variable used for storing the diagnostic response length
  Diag_Length_Type  unDataLength = 0u;

  //variable used to save the eeprom data
  tuNvmPara_EEProm sMtxEEPROMData;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_EXTERNAL_EEPROM_SIZE + DIAG_BUFFER_2BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Handle coding data
    CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

    // Check coding validation
    if (boCodingValidity != FALSE)
    {
      uint8 ucCodingEepromAddress = Diag_pCodingArea->LmmConfig.LMM_Config_Diagnosis.ucEEPROM_ADDRESS;

      // Diagnostic subservice is available only if eeprom is connected
      if ( ((ucCodingEepromAddress != DIAG_MLC_DEV_ADDR_NOT_CONNECTED) ) && (ucCodingEepromAddress == (uint8)CddMlc_GetEEPROMAddressId()))   // PRQA S 3415 //no side effects, intended behavior : if coding is not filled, do not check the other condition
      {
        aucResData[0] = p_ui8_Data[0];
        aucResData[1] = p_ui8_Data[1];

        //read directly the eeprom structure saved in  NvM block and copy it in the Diagnostic Response 
        (void)memcpy(&aucResData[2u], &NvmBlockMatrixEEPromContent.Data[0], DIAG_EXTERNAL_EEPROM_SIZE);

        unDataLength = sizeof(aucResData);

        eReturnCode = DIAG_Send_Diag_Response(aucResData, unDataLength);
      }
      else
      {
        //return Condition Not Correct if EEprom is not used
        eReturnCode = CNC;
      }
    }
    else
    {
      //return Condition Not Correct if coding is invalid
      eReturnCode = CNC;
    }

  }
#else
  (void)Length;
  (void)p_ui8_Data;
  eReturnCode = SFNS;
#endif

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS
///
/// \descr  Diagnostic subservice that returns the diagnosis of the LED channel outputs
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;
  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;
  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_4BYTES] = { 0u };
  // Aftermarket LED Channel Output data
  tsErrCust_AftermarketLedChnlOutData  sLedOutputEcuData = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    //positive response
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    // Capture LED Channel Output data (0xD422)
    ErrCust_CaptureAftermarketLedOutputFailEcuData(&sLedOutputEcuData);

    // Populate the data bytes
    aucResData[DIAG_START_INDEX_2] = sLedOutputEcuData.ucFirstErrorByte;
    aucResData[DIAG_START_INDEX_3] = sLedOutputEcuData.ucSecondErrorByte;

    ucDataLength = DIAG_BUFFER_4BYTES;

    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D4C5_LIGHTING_ENG_DATA
///
/// \descr  Diagnostic subservice that returns lighting functionalities feedback
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D4C5_LIGHTING_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
   DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;
  uint8_fast ucPixel;
  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_4BYTES] = { 0u };

  // Used to store aftermarket LVL ECU data
  tsErrCust_AftermarketLvlEcuData  sLvlECUData;

  tsErrCust_LgtFctState   sLgtFctState;
  tsErrCust_LgtFctStatus  sLgtFctStatus;
  //tsRte_HssStatus         sLgtFanState;
  tisHssStatusError       atStatusError;
  uint8                   ucMatrixBeam_Diag;
  uint8                   ucHighBeam_Diag;
  
  //Fans error status
  boolean aboFan_ErrSts[2u] = { FALSE, FALSE }, boFan_State = FALSE;

  // Read information from ErrCust RTE
  ErrCust_RteAccess_Read_FctR_LgtFctErrState(&sLgtFctState);
  ErrCust_RteAccess_Read_FctR_LgtFctStatus(&sLgtFctStatus);

  /* LDM.SYRS.3838 -  MB_DIAG -> If Matrix beam is not used then return 0b11 else X_GFHB_FAULT
                   -  HB_DIAG -> If Matrix Beam is used     then return 0b00 else HB Diagnosis value*/
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  ucMatrixBeam_Diag = (sLgtFctState.boGfHb_State != FALSE) ? DIAG_D4C5_MB_PRESENT_DEFECT : DIAG_D4C5_MB_NO_DEFECT;
  ucHighBeam_Diag = DIAG_D4C5_HB_STATUS;
#else
  ucMatrixBeam_Diag = DIAG_D4C5_MB_NOT_USED;
  ucHighBeam_Diag = sLgtFctState.boHb_State;
#endif

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    ErrCust_CaptureAftermarketLvlEcuData(&sLvlECUData);

    //get Fans error status
    (void)Rte_Read_CtrlSwi_StatusErr(&atStatusError);

    aboFan_ErrSts[FAN_1] = ((atStatusError.eErrOpenLoad[FAN_1]    == CTRLSWI_CFG_ERR_YES)      ||
                            (atStatusError.eErrShortToVBat[FAN_1] == CTRLSWI_CFG_ERR_YES)      ||
                            (atStatusError.eErrShortToGnd[FAN_1]  == CTRLSWI_CFG_ERR_YES))      ?      TRUE: FALSE;

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
    // get Fan2 status only on FULL
    aboFan_ErrSts[FAN_2] = ((atStatusError.eErrOpenLoad[FAN_2]    == CTRLSWI_CFG_ERR_YES)      ||
                            (atStatusError.eErrShortToVBat[FAN_2] == CTRLSWI_CFG_ERR_YES)      ||
                            (atStatusError.eErrShortToGnd[FAN_2]  == CTRLSWI_CFG_ERR_YES))     ?      TRUE : FALSE;
#elif defined(CFG_VARIANT_ECO)
    //overwrite Fan2 status on ECO
    aboFan_ErrSts[FAN_2] = FALSE;
#endif

    //Fan1 and Fan2 status 
    boFan_State = ((aboFan_ErrSts[FAN_1] != FALSE) || (aboFan_ErrSts[FAN_2] != FALSE)) ? TRUE : FALSE;

    // Fan and Matrix Diag bits need to be added
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = sLvlECUData.ucVoltageTerminal;
    aucResData[3] = ((uint8)sLgtFctStatus.boHb_Status +
      (uint8)(sLgtFctStatus.boLb_Status << DIAG_1BIT_SHIFT) +
      (uint8)(ucHighBeam_Diag << DIAG_2BIT_SHIFT) +
      (uint8)(sLgtFctState.boLb_State << DIAG_3BIT_SHIFT) +
      (uint8)(boFan_State << DIAG_4BIT_SHIFT) +
      (uint8)(ucMatrixBeam_Diag << DIAG_6BIT_SHIFT));

    ucDataLength = DIAG_RESP_4BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D4C6_SIGNALLING_ENG_DATA
///
/// \descr  Diagnostic subservice that returns signalling lighting feedback
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D4C6_SIGNALLING_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  tsErrCust_LgtFctState   sLgtFctState;
  tsErrCust_LgtFctStatus  sLgtFctStatus;

  // Read information from ErrCust RTE
  ErrCust_RteAccess_Read_FctR_LgtFctErrState(&sLgtFctState);
  ErrCust_RteAccess_Read_FctR_LgtFctStatus(&sLgtFctStatus);

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = ((uint8)sLgtFctStatus.boPos_Status +
      (uint8)(sLgtFctStatus.boDrl_Status << DIAG_1BIT_SHIFT) +
      (uint8)(sLgtFctState.boPos_State << DIAG_2BIT_SHIFT) +
      (uint8)(sLgtFctState.boDrl_State << DIAG_3BIT_SHIFT));
    ucDataLength = DIAG_RESP_3BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D4C7_TURN_IND_ENG_DATA
///
/// \descr  Diagnostic subservice that returns turn indicator lighting feedback
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D4C7_TURN_IND_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  tsErrCust_LgtFctStatus  sLgtFctStatus;
  boolean   boLgt_TI_State;

  // Read information from ErrCust RTE
  ErrCust_RteAccess_Read_FctR_LgtFctStatus(&sLgtFctStatus);
  ErrCust_RteAccess_Read_FctR_TI_FctErrState(&boLgt_TI_State);
  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = ((uint8)sLgtFctStatus.boTi_Status +
      (uint8)(boLgt_TI_State << DIAG_1BIT_SHIFT));
    ucDataLength = DIAG_RESP_3BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D4C8_BODY_HIGH_SENSOR_ENG_DATA
///
/// \descr  Diagnostic subservice that returns the body high sensor value and offset
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D4C8_BODY_HIGH_SENSOR_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  (void)Length;
  (void)p_ui8_Data;
  DIAG_status eReturnCode = DIAG_NOK;
  tsRte_SensorRaw                 aunSensRawPwm;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_10BYTES] = { 0u };

  // Variables used to store sensor values
  uint32 ulSensPwmRes[CFG_CntSens];
  uint32 ulDeltaPwm0, ulDeltaPwm1;

  // Variables used to store calibration offset of front/rear left or front/rear body high sensor
  uint32 ulNvmPwmOffset1, ulNvmPwmOffset2, ulNvmPwmOffsetComputed1, ulNvmPwmOffsetComputed2;

  teErrCust_Types_MountingSide eEcuSide; // Variable used to store ECU side
  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(&eEcuSide);

  (void)Rte_Read_IoHwAb_GetSens_Raw(&aunSensRawPwm);

  if (Length != DIAG_RESP_2BYTES)
  {
    eReturnCode = IMLOIF;
  }
  else
  {
    if (eEcuSide != eLeft)
    {
      // Negative response code - 0x12 Sub-function not supported
      eReturnCode = SFNS;
    }
#if defined (CFG_VARIANT_ECO)  || defined (UNIT_TEST)
    else if ((NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN) || (NvmBlockDeltaPwmPara.eASL_Present == eASL_Absent))
#elif defined (CFG_VARIANT_FULL)
    else if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN)
#endif
    {
      // Negative response code - 0x12 Sub-function not supported
      eReturnCode = SFNS;
    }
    else
    {
      for (uint8 ucIx = 0u; ucIx < CFG_CntSens; ucIx++)
      {
        ulSensPwmRes[ucIx] = aunSensRawPwm.aucSensRaw[ucIx];
      }
      ulDeltaPwm0 = (ulSensPwmRes[0] * DIAG_MAX_VALUE_DID_D4C8) / DIAG_RESOLUTION_DID_D4C8;
      ulDeltaPwm1 = (ulSensPwmRes[1] * DIAG_MAX_VALUE_DID_D4C8) / DIAG_RESOLUTION_DID_D4C8;
      ulNvmPwmOffset1 = NvmBlockDeltaPwmPara.unSensOffset_0;
      ulNvmPwmOffset2 = NvmBlockDeltaPwmPara.unSensOffset_1;
      ulNvmPwmOffsetComputed1 = (ulNvmPwmOffset1 * DIAG_MAX_VALUE_DID_D4C8) / DIAG_RESOLUTION_DID_D4C8;
      ulNvmPwmOffsetComputed2 = (ulNvmPwmOffset2 * DIAG_MAX_VALUE_DID_D4C8) / DIAG_RESOLUTION_DID_D4C8;

      aucResData[0] = p_ui8_Data[0];
      aucResData[1] = p_ui8_Data[1];
      aucResData[2] = (uint8)ulDeltaPwm0; // Instantaneous value of front left or front body high sensor
      aucResData[3] = 0xFFu;
      aucResData[4] = (uint8)ulDeltaPwm1; // Instantaneous value of rear left or rear body high sensor
      aucResData[5] = 0xFFu;
      aucResData[6] = (uint8)ulNvmPwmOffsetComputed1; // Calibration offset of front left or front body high sensor
      aucResData[7] = 0xFFu;
      aucResData[8] = (uint8)ulNvmPwmOffsetComputed2; // Calibration offset of rear left or rear body high sensor
      aucResData[9] = 0xFFu;

      ucDataLength = DIAG_RESP_10BYTES;
      eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
    }
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D4C9_ATTITUDE_ENG_DATA
///
/// \descr  Diagnostic subservice that returns the attitude feedback
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D4C9_ATTITUDE_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  (void)Length;
  (void)p_ui8_Data;

#if defined CFG_VARIANT_ECO // Applicable only for ECO version
  // Negative response code - 0x12 Sub-function not supported
  eReturnCode = SFNS;
#else // Applicable only for FULL version

  //tsRte_SigPrep_VehiclePitchAngle  sVehPitchAngle = { 0 };

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_5BYTES] = { 0u };

  teErrCust_Types_MountingSide eEcuSide; // Variable used to store ECU side
  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(&eEcuSide);

  //(void)Rte_Read_SigPrep_VehiclePitchAngle(&sVehPitchAngle);

  // Used to store attitude actual status data
  tsErrCust_AftermarketAttitudeEcuData ActualStatAtt;

  if (Length != DIAG_RESP_2BYTES)
  {
    eReturnCode = IMLOIF;
  }
  else
  {
    if (eEcuSide != eLeft)
    {
      // Negative response code - 0x12 Sub-function not supported
      eReturnCode = SFNS;
    }
    else if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_HLS)
    {
      // Negative response code - 0x12 Sub-function not supported
      eReturnCode = SFNS;
    }
    else
    {
      // Read data from the ErrCust module for the vehicle attitude value
      ErrCust_CaptureAftermarketAttitudeEcuData(&ActualStatAtt);
      uint16 unInstValVehiculeAttitude = (uint16)ErrCust_ConvertValueSint2Int(ActualStatAtt.snInstValVehiculeAttitude, DIAG_LENGTH_ASSIETTE_VEHICULE);
      uint16 unOffsetCalibVehicleAttitude = (uint16)ErrCust_ConvertValueSint2Int(ActualStatAtt.snOffsetCalibVehicleAttitude, DIAG_LENGTH_ASSIETTE_VEHICULE);

      aucResData[0] = p_ui8_Data[0];
      aucResData[1] = p_ui8_Data[1];
      aucResData[2] = (uint8)((uint8)(0x0Fu << DIAG_4BIT_SHIFT) | (uint8)(unOffsetCalibVehicleAttitude >> DIAG_6BIT_SHIFT));
      aucResData[3] = (uint8)((uint8)(unOffsetCalibVehicleAttitude << DIAG_2BIT_SHIFT) | (uint8)(unInstValVehiculeAttitude >> DIAG_8BIT_SHIFT));
      aucResData[4] = (uint8)(unInstValVehiculeAttitude & DIAG_8_BIT_MASK);

      ucDataLength = DIAG_RESP_5BYTES;
      eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
    }
  }
#endif
  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D4CB_LEVELLING_ENG_DATA
///
/// \descr  Diagnostic subservice that returns the stepper levelling feedback
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D4CB_LEVELLING_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST) // Applicable for FULL only

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_4BYTES] = { 0u };

  // Used to store stepper actual status data
  tsErrCust_TypesActStatStp ActualStatStp0;

  uint8 ucStepLoss = 0u, ucElecDef = 0u, ucStpPosDegree = 0u; // used to store diagnostic status

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Read data from the ErrCust module for the stepper actual status
    ErrCust_RteAccess_Read_CtrlStp_ActStatStp(&ActualStatStp0);

    ucStepLoss = ((ActualStatStp0.boStpLossLvl != FALSE) || (ActualStatStp0.boPosDefLvl != FALSE)) ? 1u : 0u; // step loss or position defect
    ucElecDef = ((ActualStatStp0.boElecDefLvl != FALSE) || (ActualStatStp0.boThermDefLvl != FALSE)) ? 1u : 0u; // electrical or thermic defect

    ucStpPosDegree = (ActualStatStp0.cStpPosDegree >= 0) ? (uint8)(sint8)((sint16)ActualStatStp0.cStpPosDegree * 127 / 60) : (uint8)((uint8)ErrCust_ConvertValueSint2Int(((sint32)ActualStatStp0.cStpPosDegree * 128 / 60), DIAG_LENGTH_8BIT));

    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = ucStpPosDegree;
    aucResData[3] = (uint8)((uint8)ActualStatStp0.ucStsAutoLvl +
      (uint8)(0x03u << DIAG_2BIT_SHIFT) +
      (uint8)(ucStepLoss << DIAG_4BIT_SHIFT) +
      (uint8)(ActualStatStp0.boCommDefLvl << DIAG_5BIT_SHIFT) +
      (uint8)(ucElecDef << DIAG_6BIT_SHIFT) +
      (uint8)(ActualStatStp0.boMoveLvlStp << DIAG_7BIT_SHIFT));
    ucDataLength = DIAG_RESP_4BYTES;
    /*#else
        aucResData[0] = p_ui8_Data[0];
        aucResData[1] = p_ui8_Data[1];
        aucResData[2] = 0u;
        aucResData[3] = (uint8)(0x00u +
          (uint8)(0x03u << DIAG_2BIT_SHIFT) +
          (uint8)(0x01u << DIAG_4BIT_SHIFT) +
          (uint8)(0x01u << DIAG_5BIT_SHIFT) +
          (uint8)(0x01u << DIAG_6BIT_SHIFT) +
          (uint8)(0x01u << DIAG_7BIT_SHIFT));
        ucDataLength = DIAG_RESP_4BYTES;
    #endif*/
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

#else//ECO Version
  (void)p_ui8_Data;
  (void)Length;
  // Negative response code - 0x12 Sub-function not supported
  eReturnCode = SFNS;
#endif
  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_D4CD_RGB_LED
///
/// \descr  Diagnostic subservice that returns the rgb feedback.
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_D4CD_RGB_LED(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST) // Applicable for FULL only

  tsRte_Hss3Status  sHss3Status = { 0u };
  uint8             aucResData[DIAG_BUFFER_3BYTES] = { 0u };
  tsDiag_CodingParameters sCodingParam;
  uint8  ucRGBLedStatus = 0u;
  uint8  ucRGBLedDiag = 0u;
  uint8  ucDataLength = 0u;

  // Get coding param
  Diag_Get_Coding(&sCodingParam);

  // If RGB assigned to channel 13
  if ((EFT_DATA_VALID_STATUS != FALSE) && (EFT_ECUVARCFG_HSS3 != 0u) &&
    (sCodingParam.eCodingState != eParaFct0_CodingDataInvalid) && (sCodingParam.psCodingParameters->Led1.LedConfigDRV13.FUSA_DRV13_NAME == 9u))
  {
    // Read Hss3 Status and Errors from Ctrl Switch
    (void)Rte_Read_CtrlSwi_Hss3StatusErr(&sHss3Status);

    if (Length != DIAG_RESP_2BYTES)
    {
      // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
      eReturnCode = IMLOIF;
    }
    else
    {
      // Get the RGB LED status
      ucRGBLedStatus = (uint8)sHss3Status.boHss3_Enabled;

      ucRGBLedDiag = (uint8)(((sHss3Status.boHss3_OpenLoadStatus != FALSE) ||
        (sHss3Status.boHss3_Sh2VbatStatus != FALSE) ||
        (sHss3Status.boHss3_Sh2GndStatus != FALSE)) ? TRUE : FALSE);

      aucResData[0] = p_ui8_Data[0];
      aucResData[1] = p_ui8_Data[1];

      aucResData[DIAG_START_INDEX_2] = (uint8)((ucRGBLedStatus & DIAG_RGB_LED_MASK) |
        (uint8)((ucRGBLedDiag & DIAG_RGB_LED_MASK) << DIAG_1BIT_SHIFT) |
        (uint8)(DIAG_RESERVED_D4CD << DIAG_2BIT_SHIFT));

      ucDataLength = DIAG_BUFFER_3BYTES;

      // Send Diag Response
      eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
    }
  }
  else
  {
    eReturnCode = SFNS;
  }

#else // ECO Version

  (void)Length;
  (void)p_ui8_Data;

  eReturnCode = SFNS;

#endif

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES
///
/// \descr  Diagnostic subservice that returns context groups linked to default codes
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_10BYTES] = { 0u };

  // Used to store aftermarket CONTEXT ECU data
  tsErrCust_AftermarketContextEcuData CtxECUData;

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Capture data from the Errcust module for the Aftermarket Context
    ErrCust_CaptureAftermarketContextEcuData(&CtxECUData);

#if defined(SAMPLE_ECO)
    CtxECUData.ucInstVal_FL_Bhs = NvmBlockDeltaPwmPara.eASL_Present != eASL_Absent ? CtxECUData.ucInstVal_FL_Bhs : 0xFFu;
    CtxECUData.ucInstVal_RL_Bhs = NvmBlockDeltaPwmPara.eASL_Present != eASL_Absent ? CtxECUData.ucInstVal_RL_Bhs : 0xFFu;
#endif

    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = CtxECUData.ucVoltageTerminal;
    aucResData[3] = CtxECUData.ucEtatInfo;
    aucResData[4] = CtxECUData.ucVehicleSpeed;
    aucResData[5] = (uint8)(CtxECUData.ulKilometrage >> 16u);
    aucResData[6] = (uint8)(CtxECUData.ulKilometrage >> 8u);
    aucResData[7] = (uint8)CtxECUData.ulKilometrage;
    aucResData[8] = CtxECUData.ucInstVal_FL_Bhs;
    aucResData[9] = CtxECUData.ucInstVal_RL_Bhs;

    ucDataLength = DIAG_RESP_10BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief  Diag_Callbacks_F080_AUTHENTIFICATION_ZONE
///
/// \descr  Diagnostic subservice that returns the authentification zone information
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_F080_AUTHENTIFICATION_ZONE(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  (void)Length;
  DIAG_status eReturnCode = DIAG_NOK;
  uint8 ucIndex;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_24BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    for (ucIndex = 0u; ucIndex <= DIAG_AUTH_ZONE_LENGTH; ucIndex++)
    {
      aucResData[ucIndex + 2u] = AppDesc_AuthZone.aucInfo[ucIndex];
    }
    ucDataLength = DIAG_BUFFER_24BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief  Diag_Callbacks_F08F_EMC_STANDARDIZATION_LABEL
///
/// \descr  Diagnostic subservice that returns the server information requested by client.
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_F08F_EMC_STANDARDIZATION_LABEL(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{

  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;
  uint8 ucEmcIndx = 0u;

  // ASCI coded
  const uint8* pucEcuAppTxt = NULL_PTR;
  const uint8* pucEcuEmcTxt = NULL_PTR;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_25BYTES] = { 0u };

#if (DIAG_CALLBACKS_EMC_STANDARD_BACKWARD_COMPATIBILITY != 0)

  uint8 ucEftDocVersion = EFT_ECU_EFT_DOC_VERSION;


  const char chFF_Full[12] = "FULL ASC";
  const char chFF_Eco[12] = "ECO ASC";
  const char chEMC[5] = "EMC00";

  if (ucEftDocVersion > 1u)
  {
    // ASCI coded
    pucEcuAppTxt = &EFT_ECU_HWID_APPLICATION(0u);
    pucEcuEmcTxt = &EFT_ECU_HWID_EMC(0u);
  }
  else
  {
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
    //PRQA S 310, 311 1 // This cast is intendeed in order to assure the functionality
    pucEcuAppTxt = (uint8*)&chFF_Full[0];
#else
    //PRQA S 310, 311 1 // This cast is intendeed in order to assure the functionality
    pucEcuAppTxt = (uint8*)&chFF_Eco[0];
#endif
    //PRQA S 310, 311 1 // This cast is intendeed in order to assure the functionality
    pucEcuEmcTxt = (uint8*)&chEMC[0];
  }

#else

  // ASCI coded
  pucEcuAppTxt = &EFT_ECU_HWID_APPLICATION(0u);
  pucEcuEmcTxt = &EFT_ECU_HWID_EMC(0u);

#endif



  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    // PSAC
    aucResData[2] = 0x2Au;

    // DI
    aucResData[3] = (uint8)'L';
    aucResData[4] = (uint8)'D';
    aucResData[5] = (uint8)'M';
    aucResData[6] = 0x00u;
    aucResData[7] = 0x00u;

    // FF
    for (uint8_least ucIx = 0u; ucIx < 12u; ucIx++)
    {
      aucResData[ucIx + 8u] = *(pucEcuAppTxt + ucIx);
    }
    aucResData[20] = 0x00u;
    aucResData[21] = 0x00u;
    aucResData[22] = 0x00u;
    aucResData[23] = 0x00u;

    // EMCI
    // Check if field is encoded as ASCII Number
    if (((*(pucEcuEmcTxt + 3u) >= 0x30u) && (*(pucEcuEmcTxt + 3u) <= 0x39u)) &&
      ((*(pucEcuEmcTxt + 4u) >= 0x30u) && (*(pucEcuEmcTxt + 4u) <= 0x39u)))
    {
      ucEmcIndx = (*(pucEcuEmcTxt + 3u) - 0x30u) * 10u + (*(pucEcuEmcTxt + 4u) - 0x30u);
    }
    else
    {
      ucEmcIndx = 0xFFu;
    }

    aucResData[24] = ucEmcIndx;
    ucDataLength = DIAG_BUFFER_25BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }
  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief  Diag_Callbacks_F0FE_IDENTIFICATION_ZONE
///
/// \descr  Diagnostic subservice that returns the IDENTIFICATION zone information
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_F0FE_IDENTIFICATION_ZONE(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  //(void)Length;
  DIAG_status eReturnCode = DIAG_NOK;
  uint8 ucIndex;
  uint8 ucLastDownloadedDataIndex;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_26BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    for (ucIndex = APPDESC_LOGZONE_ENTRY_MAX_INDEX; ucIndex < APPDESC_MAX_UINT8_VALUE; ucIndex--)
    {
      // Check if PSA Supplier Code is valid
      //PRQA S 1863 1 // The operands of this equality operator are of different 'essential signedness' but will both be promoted to 'signed int' for comparison.
      if (C_BOOT_ZI_Area[ucIndex].uData.sLogZoneInfo.ucSupplierCode != APPDESC_EMPTY_ZONE)
      {
        // Valid data found

        // If LogZone is full, check if data from the begining of LogZone area has been overwritten
        if (ucIndex == APPDESC_LOGZONE_ENTRY_MAX_INDEX)
        {
          // Search for last downloaded data by date
          ucLastDownloadedDataIndex = AppDesc_LogZoneLastDataSearch();
        }
        else
        {
          // Last downloaded data found
          ucLastDownloadedDataIndex = ucIndex;
        }

        break;
      }
      else
      {
        // Continue searching for valid data
      }
    }

    // Fill in the response buffer with the received values 
    for (ucIndex = 0u; ucIndex < DIAG_LOGZONE_LENGTH; ucIndex++)
    {
      aucResData[ucIndex + 2u] = C_BOOT_ZI_Area[ucLastDownloadedDataIndex].uData.aucInfo[ucIndex];
    }

    // Get date from EFT and format it
    uint8 ucEftDay = ECU_EFT_DAY_BCD;
    uint8 ucEftMonth = ECU_EFT_MONTH_BCD;
    uint8 ucEftYear = ECU_EFT_YEAR_BCD;

    // Workaround for issue LDMO-3550
    aucResData[8] = ucEftDay;
    aucResData[9] = ucEftMonth;
    aucResData[10] = ucEftYear;

    ucDataLength = DIAG_BUFFER_26BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_F186_Active_Diag_Session_Data_Identifier
///
/// \descr  Diagnostic subservice that returns the active Diagnostic Session
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_F186_Active_Diag_Session_Data_Identifier(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_3BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];
    aucResData[2] = DIAG_GetActiveSession();
    ucDataLength = DIAG_RESP_3BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER
///
/// \descr  Diagnostic subservice that returns ECU manufacturing date data identifier
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_5BYTES] = { 0u };

  // Check if format/length is correct
  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // If EFT is not available - respond with NRC 0x22
    if (EFT_DATA_VALID_STATUS != FALSE)
    {
      // Get date from EFT and format it
      uint8 ucEftDay = ECU_EFT_DAY_BCD;
      uint8 ucEftMonth = ECU_EFT_MONTH_BCD;
      uint8 ucEftYear = ECU_EFT_YEAR_BCD;

      aucResData[0] = p_ui8_Data[0];
      aucResData[1] = p_ui8_Data[1];
      aucResData[2] = ucEftDay;
      aucResData[3] = ucEftMonth;
      aucResData[4] = ucEftYear;

      ucDataLength = DIAG_RESP_5BYTES;
      eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
    }
    else
    {
      // Negative response code - 0x22 Conditions not correct
      eReturnCode = CNC;
    }
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER
///
/// \descr  Diagnostic subservice that returns ECU serial number
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_17BYTES] = DIAG_F18C_ECU_SERIAL_NUMBER_INIT;

  // Temporary buffer used to get data from EFT
  uint8 ucTempData = 0u;

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // If EFT is not available - respond with NRC 0x22
    if (EFT_DATA_VALID_STATUS != FALSE)
    {
      aucResData[0]  = p_ui8_Data[0];
      aucResData[1]  = p_ui8_Data[1];

      // Byte 0 : contant "T"
      aucResData[2]  = (uint8)'T';

      // Byte 1 : ECU DYN SN Line
      ucTempData = EFT_HWDESC_ECUDYNSN_LINE;

      if (Diag_Callbacks_F18C_isCharacterSupported(ucTempData) != FALSE)
      {
        aucResData[3] = ucTempData;
      }
      else
      {
        // default 0x3F character [?] will be printed
      }

      // Byte 2 : ECU DYN SN EOL
      ucTempData = EFT_HWDESC_ECUDYNSN_EOL;

      if (Diag_Callbacks_F18C_isCharacterSupported(ucTempData) != FALSE)
      {
        aucResData[4] = ucTempData;
      }
      else
      {
        // default 0x3F character [?] will be printed
      }

      // Byte 3-5 : constant "13R" fixed by customer
      aucResData[5]  = (uint8)'1';
      aucResData[6]  = (uint8)'3';
      aucResData[7]  = (uint8)'R';

      // Byte 6-8 : Day of Year (number of days)
      uint16 unNumberOfDays = Diag_Callbacks_F18C_Compute_Number_Of_Days_In_Year();

      if (unNumberOfDays != DIAG_DATE_INVALID_NUMBER_OF_DAYS)
      {
        for (uint8 ucIndex = 0u; ucIndex < DIAG_OFFSET_INDEX_3; ucIndex++)
        {
          uint8 ucDayDigit = (uint8)(unNumberOfDays % 10u);

          unNumberOfDays /= 10u;

          aucResData[DIAG_OFFSET_INDEX_10 - ucIndex] = ucDayDigit + HEX_TO_ASCII_FACTOR;
        }
      }
      else
      {
        // default 0x3F character [?] will be printed
      }

      // Byte 9 : Calendar Year (last digit of the year)
      ucTempData = EFT_MANUFACTURING_DATE_YEAR(DIAG_OFFSET_INDEX_3);

      if (Diag_Callbacks_F18C_isCharacterSupported(ucTempData) != FALSE)
      {
        aucResData[11] = ucTempData;
      }
      else
      {
        // default 0x3F character [?] will be printed
      }

      // Byte 10-14 : Sequence Number (first digit is constant "0", and the remaining four are the ECU DYN SN Counter)
      aucResData[12] = (uint8)'0';

      for (uint8 ucIndex = 0U; ucIndex < DIAG_START_INDEX_4; ucIndex++)
      {
        // Get ECU DYN SN Counter
        ucTempData = EFT_HWDESC_ECUDYNSN_COUNTER(ucIndex);

        if (Diag_Callbacks_F18C_isCharacterSupported(ucTempData) != FALSE)
        {
          aucResData[ucIndex + DIAG_OFFSET_INDEX_13] = ucTempData;
        }
        else
        {
          // default 0x3F character [?] will be printed
        }
      }

      ucDataLength = DIAG_BUFFER_17BYTES;
      eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
    }
    else
    {
      // Negative response code - 0x22 Conditions not correct
      eReturnCode = CNC;
    }
  }

  return eReturnCode;
}

//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_F18C_Compute_Number_Of_Days_In_Year
///
/// \descr  Diagnostic helper function that returns number of days in year
///
/// \param  void
///
/// \return unNumberOfDaysInYear
//-----------------------------------------------------------------------------
STATIC_AL uint16 Diag_Callbacks_F18C_Compute_Number_Of_Days_In_Year(void)
{
  uint16  unNumberOfDaysInYear = 0u;
  uint8   ucMonthIdx           = 0u;
  uint8   ucNbOfDays           = 0u;
  boolean boisDateInvalid      = FALSE;
  boolean boMonthFound         = FALSE;
  boolean boLeapYear           = FALSE;

  // Get date from EFT and format it
  CONST_AL uint8 ucEftDay   = ECU_EFT_DAY_DEC;
  CONST_AL uint8 ucEftMonth = ECU_EFT_MONTH_DEC;
  CONST_AL uint8 ucEftYear  = ECU_EFT_YEAR_DEC;

  // Check date validity only if the characters are supported
  if ((Diag_Callbacks_F18C_isCharacterSupported(EFT_MANUFACTURING_DATE_DAY(0)) != FALSE) &&
      (Diag_Callbacks_F18C_isCharacterSupported(EFT_MANUFACTURING_DATE_DAY(1)) != FALSE) &&  //PRQA S 3415 // program architecture and readability
      (Diag_Callbacks_F18C_isCharacterSupported(EFT_MANUFACTURING_DATE_MONTH(0)) != FALSE) &&  //PRQA S 3415 // program architecture and readability
      (Diag_Callbacks_F18C_isCharacterSupported(EFT_MANUFACTURING_DATE_MONTH(1)) != FALSE) &&  //PRQA S 3415 // program architecture and readability
      (Diag_Callbacks_F18C_isCharacterSupported(EFT_MANUFACTURING_DATE_YEAR(2)) != FALSE) &&  //PRQA S 3415 // program architecture and readability
      (Diag_Callbacks_F18C_isCharacterSupported(EFT_MANUFACTURING_DATE_YEAR(3)) != FALSE))  //PRQA S 3415 // program architecture and readability
  {
    // Check if the manufacturing date from EFT is valid
    if ((ucEftMonth >= DIAG_DATE_MONTHS_MIN) && (ucEftMonth <= DIAG_DATE_MONTHS_MAX))
    {
      // If the year and month are valid, check the day

      // Check for the number of days of the month
      for (uint8 ucLoopIdx = 0; (ucLoopIdx < DIAG_DATE_MONTHS_MAX) && (boMonthFound == FALSE); ucLoopIdx++)
      {
        if (Diag_asMonthsDays[ucLoopIdx].ucMonth == ucEftMonth)
        {
          // The month was identified
          boMonthFound = TRUE;
          ucMonthIdx = ucLoopIdx;
        }
        else
        {
          // nothing to do
        }
      }

      // If the month is February, check for leap year
      if ((ucEftYear % DIAG_DATE_LEAP_YEAR) == 0u)
      {
        // Leap year found
        boLeapYear = TRUE;

        if (Diag_asMonthsDays[ucMonthIdx].ucMonth == DIAG_DATE_FEBRUARY)
        {
          // Leap year and month if February
          ucNbOfDays = Diag_asMonthsDays[ucMonthIdx].ucNbOfDays + 1u;
        }
        else
        {
          // Month is not February
          ucNbOfDays = Diag_asMonthsDays[ucMonthIdx].ucNbOfDays;
        }
      }
      else
      {
        // Not a leap year
        ucNbOfDays = Diag_asMonthsDays[ucMonthIdx].ucNbOfDays;
      }

      // Compare the day with the maximum number of days in this month
      if ((ucEftDay <= ucNbOfDays) && (ucEftDay > 0u))
      {
        // nothing to do
      }
      else
      {
        // Day is invalid, thus date is invalid
        boisDateInvalid = TRUE;
      }
    }
    else
    {
      // Month is invalid, thus date is invalid
      boisDateInvalid = TRUE;
    }
  }
  else
  {
    // Invalid characters detected, thus date is invalid
    boisDateInvalid = TRUE;
  }

  // Compute number of days in a year based on date validity
  if (boisDateInvalid == FALSE)
  {
    // Add all the days from the months below the month set in EFT
    for (uint8 ucIndex = 0u; ucIndex < ucEftMonth - 1u; ucIndex++)
    {
      unNumberOfDaysInYear += Diag_asMonthsDays[ucIndex].ucNbOfDays;
    }

    // Add the remaining number of days from the month that is set in EFT
    unNumberOfDaysInYear += ucEftDay;

    // Add an extra day if it is a leap year and the date is after 29'th of February
    if ((boLeapYear != FALSE) && (ucEftMonth > DIAG_DATE_FEBRUARY))
    {
      unNumberOfDaysInYear += 1u;
    }
    else
    {
      // nothing to do, it is not a leap year
    }
  }
  else
  {
    unNumberOfDaysInYear = DIAG_DATE_INVALID_NUMBER_OF_DAYS;
  }

  return unNumberOfDaysInYear;
} //PRQA S 5310 1 // STPTH exceeded due to program architecture and readability

//-----------------------------------------------------------------------------
/// \brief  Diag_Callbacks_F18C_isCharacterSupported
///
/// \descr  Checks if a character is supported according to REQ-0047934 A
///
/// \param  ucInputVal: EFT data
///
/// \return boolean: TRUE: characters is supported
///                  FALSE: character is not supported
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean Diag_Callbacks_F18C_isCharacterSupported(uint8 ucInputVal)
{
  return (((ucInputVal >= DIAG_ASCII_LOWER_LIMIT) && (ucInputVal <= DIAG_ASCII_UPPER_LIMIT)) &&
          (ucInputVal != DIAG_ASCII_NOT_SUPPORTED_CHARACTER_1) &&
          (ucInputVal != DIAG_ASCII_NOT_SUPPORTED_CHARACTER_2) &&
          (ucInputVal != DIAG_ASCII_NOT_SUPPORTED_CHARACTER_3) &&
          (ucInputVal != DIAG_ASCII_NOT_SUPPORTED_CHARACTER_4) &&
          (ucInputVal != DIAG_ASCII_NOT_SUPPORTED_CHARACTER_5)) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_FD02_INTERNAL_ECU_SERIAL_NUMBER_DATA_IDENTIFIER
///
/// \descr  Diagnostic subservice that returns internal ECU serial number
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_FD02_INTERNAL_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(UINT8 const * p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_27BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    // Get ECR number
    for (uint8 ucIndex = 2U; ucIndex < DIAG_CALLBACKS_ECRNUMBER_BYTE_NR; ucIndex++)
    {
      aucResData[ucIndex] = EFT_HWDESC_ECRNUMBER(ucIndex - 2u);
    }

    for (uint8 ucIndex = 0U; ucIndex < DIAG_START_INDEX_4; ucIndex++)
    {
      // Get Manufacturing Date Year
      aucResData[ucIndex + DIAG_OFFSET_INDEX_13] = EFT_MANUFACTURING_DATE_YEAR(ucIndex);
      // Get ECU DYN SN Counter
      aucResData[ucIndex + DIAG_OFFSET_INDEX_23] = EFT_HWDESC_ECUDYNSN_COUNTER(ucIndex);
    }

    for (uint8 ucIndex = 0U; ucIndex < DIAG_START_INDEX_2; ucIndex++)
    {
      // Get Manufacturing Date Month
      aucResData[ucIndex + DIAG_OFFSET_INDEX_17] = EFT_MANUFACTURING_DATE_MONTH(ucIndex);
      // Get Manufacturing Date Day
      aucResData[ucIndex + DIAG_OFFSET_INDEX_19] = EFT_MANUFACTURING_DATE_DAY(ucIndex);
    }

    // Get ECU DYN SN Line and EOL
    aucResData[DIAG_OFFSET_INDEX_21] = EFT_HWDESC_ECUDYNSN_LINE;
    aucResData[DIAG_OFFSET_INDEX_22] = EFT_HWDESC_ECUDYNSN_EOL;

    ucDataLength = DIAG_BUFFER_27BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}

//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_FD03_READ_ACTIVE_ALECS
///
/// \descr  Diagnostic subservice that returns the active ALECs
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_FD03_READ_ACTIVE_ALECS(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint16 unDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_512BYTES] = { 0u };

  // Counter for active ALECs
  uint8  ucAlecCounter = 0u;

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0u] = p_ui8_Data[0u];
    aucResData[1u] = p_ui8_Data[1u];

    // Check DEM event id status
    for (uint16 unDemConfigIndex = 0U; unDemConfigIndex < DEM_CONFIG_ENTRY_MAX; unDemConfigIndex++)
    {
      // For internal AL Read service check only the value of the first bit from status (1 - Passed, 0 -Failed)
      if (((NvmBlockDemData.aucStatus[unDemConfigIndex] & 1U) ^ DEM_STATUS_TEST_FAILED) == 0U)
      {
        // Build the answer with active DEM event id
        aucResData[DIAG_OFFSET_INDEX_3 + (ucAlecCounter * 2u)]      = HIBYTE(unDemConfigIndex + 1u);
        aucResData[DIAG_OFFSET_INDEX_3 + (ucAlecCounter * 2u) + 1u] = LOBYTE(unDemConfigIndex + 1u);

        // Prepare the index for the next active dem event id(ALEC);
        ucAlecCounter++;
      }
      else
      {
        // nothing to do, DEM event id is not active
      }
    }

    // Return on the 3'rd byte of the response the number of active ALECs
    aucResData[DIAG_OFFSET_INDEX_2] = ucAlecCounter;

    // Length of response is : 2 bytes (0xFD 0x03) + 1 byte Nr of AlECs (zz) + 2 bytes for each Active ALEC (yy)
    unDataLength = DIAG_BUFFER_3BYTES + ((uint16)ucAlecCounter * 2u);

    eReturnCode = DIAG_Send_Diag_Response(aucResData, unDataLength);
  }

  return eReturnCode;
}

//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_FD04_INTERNAL_SW_LABEL
///
/// \descr  Diagnostic subservice that returns the internal Software Label
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_FD04_INTERNAL_SW_LABEL(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;

  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_29BYTES] = { 0u };

  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = p_ui8_Data[0];
    aucResData[1] = p_ui8_Data[1];

    // Get SW Label
    for (uint8 ucIndex = 0U; ucIndex < DIAG_SOFTWARE_LABEL_LENGTH; ucIndex++)
    {
      // Get SW Label character by character
      aucResData[ucIndex + DIAG_OFFSET_INDEX_2] = (uint8)CfgId_CfgInfoConfigData.CfgId_strVersion[ucIndex];
    }

    ucDataLength = DIAG_BUFFER_29BYTES;
    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }

  return eReturnCode;
}

//-----------------------------------------------------------------------------
/// \brief APPLI_TesterPresent
///
/// \descr  LGM callback for diagnostic service for Tester Present
///
/// \param -
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_TesterPresent(void)
{
  return DIAG_OK;
}


//-----------------------------------------------------------------------------
/// \brief APPLI_SecurityAccess
///
/// \descr  LGM callback for diagnostic subservices for Security Access
///
/// \param  -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_SecurityAccess(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  (void)p_ui8_Data;
  (void)Length;

  return SFNS;
}


//-----------------------------------------------------------------------------
/// \brief APPLI_RoutineControl
///
/// \descr  LGM callback for diagnostic subservices for Routine Control
///
/// \param  -ui8_RoutineControlType:
///         -ui16_RoutineIdentifier:
///         -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_RoutineControl(UINT8 ui8_RoutineControlType, UINT16 ui16_RoutineIdentifier, UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;
  uint8  ucResData[DIAG_BUFFER_3BYTES] = { 0 };
  uint8  ucDataLen = 3u;
  uint8  ucDataLenAl = 5u;
  uint8 ucActiveSession = 0u;
  // Mounting side
  teRte_MountingSide eMountingSide = { 0 };

  if (Diag_PowertrainCheck() == TRUE)
  {
    // Negative response code - 0x22 Conditions not correct
    eReturnCode = CNC;
  }
  else
  {
    ucActiveSession = DIAG_GetActiveSession();

    // Read Mounting side
    (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

    switch (ui16_RoutineIdentifier)
    {
    case DIAG_F001_AL_RDM:
      if (ucActiveSession != DIAG_60_AL_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        if (ui8_RoutineControlType == 0x01u)
        {
          ucResData[0] = 0x01u;
          ucResData[1] = 0xF0u;
          ucResData[2] = 0x01u;
          eReturnCode = DIAG_Send_Diag_Response(ucResData, ucDataLen);
        }
        else
        {
          // Negative response code - 0x22 Conditions Not Correct
          eReturnCode = CNC;
        }
      }
      break;

    case DIAG_DD00_LD_ACTIVATION:
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DD00_LdActivation(ui8_RoutineControlType, Length, p_ui8_Data);
      }
      break;

    case DIAG_DD01_PIXEL_ACTIVATION:
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DD01_PixelActivation(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // Pixel Activation is not applicable on ECO version
      eReturnCode = SFNS;
#endif
      break;

    case DIAG_DD03_FAN1_ACTIVATION:
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DD03_Fan1Activation(ui8_RoutineControlType, Length, p_ui8_Data);
      }
      break;

    case DIAG_DD04_FAN2_ACTIVATION:
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DD04_Fan2Activation(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // FAN2 Activation is not applicable on ECO version
      eReturnCode = SFNS;
#endif
      break;

    case DIAG_DD05_STEPPER_POSITION:
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DD05_LvlStepperPosition(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // Set Stepper Position is not applicable on ECO version
      eReturnCode = SFNS;
#endif
      break;

    case DIAG_DD06_DCMOTOR_POSITION:
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DD06_LvlDCMotorPosition(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // DC Motor Position is not applicable on FULL version
      eReturnCode = SFNS;
#endif
      break;

    case DIAG_DD07_SET_SCROLLING_CTRL_OUTPUT:
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DD07_SetScrollingCtrlOutput(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // Set Scrolling Output Control is not applicable on ECO version
      eReturnCode = SFNS;
#endif
      break;

    case DIAG_DF10_REFERENCING_RUN:
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DF10_LvlReferencingRun(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // Referencing Run is not applicable on ECO version
      eReturnCode = SFNS;
#endif
      break;

    case DIAG_DF11_STEPPER_CONTROL:
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
      if ((ucActiveSession != DIAG_03_EXTENDED_SESSION) && (eMountingSide != eMountedRight))
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DF11_LvlStepperControl(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // DF11 Stepper Control is not applicable on ECO version
      eReturnCode = SFNS;
#endif
      break;

    case DIAG_DF12_STEPPER_CONTROL:
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
      if ((ucActiveSession != DIAG_03_EXTENDED_SESSION) && (eMountingSide != eMountedRight))
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DF12_LvlStepperControl(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // DF12 Stepper Control is not applicable on ECO version
      eReturnCode = SFNS;
#endif
      break;

    case DIAG_DF13_STEPPER_CONTROL:
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
      if ((ucActiveSession != DIAG_03_EXTENDED_SESSION) && (eMountingSide != eMountedRight))
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DF13_LvlStepperControl(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // DF13 Stepper Control is not applicable on ECO version
      eReturnCode = SFNS;
#endif
      break;
#if 0 // [2025/04/22 SARGHE, Vlad] Removed DF17 because it is no longer requested
    case DIAG_DF17_AFS_CONTROL:
#if defined (CFG_VARIANT_FULL) 
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        // Afs control
        eReturnCode = Diag_Callbacks_DF17_AFSControl(ui8_RoutineControlType, Length, p_ui8_Data);
      }
#else
      // AFS Control is not applicable on ECO version
      eReturnCode = SFNS;
#endif
      break;
#endif

    case DIAG_DFB5_INIT_AUTOMATIC_LEVELING:
      if ((ucActiveSession != DIAG_03_EXTENDED_SESSION) && (eMountingSide != eMountedRight))
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_DFB5_InitAutomativLeveling(&ucResData[0], ucDataLenAl, ui8_RoutineControlType, Length, p_ui8_Data);
      }
      break;

    case DIAG_FF00_ERASE_MEMORY:
      if (ucActiveSession != DIAG_02_PROGRAMMING_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        // nothing to do
      }
      break;

    case DIAG_FF04_CHECK_MEMORY:
      if (ucActiveSession != DIAG_02_PROGRAMMING_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        // nothing to do
      }
      break;
    case DIAG_0301_RESET_CPU_LOAD:
      if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
      {
        eReturnCode = SNSIAS;
      }
      else
      {
        eReturnCode = Diag_Callbacks_0301_RESET_CPU_LOAD(ui8_RoutineControlType, Length, p_ui8_Data);
      }
      break;
    default:
      // Negative response code - 0x31 Request out of range
      eReturnCode = ROOR;
      break;
    }
  }
  return eReturnCode;
  //PRQA S 5316, 5324, 5330 1 // Multiple function calls needed to handle all WDBI diagnostic services
}


#if 0 // [2025/04/22 SARGHE, Vlad] Removed DF17 because it is no longer requested
//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DF17_AFSControl
///
/// \descr Adaptive Frontligt System Control Routine
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DF17_AFSControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Response data
  uint8 aucResponseDF17[DIAG_AFS_CONTROL_RES_LENGTH] = { 0u, 0u, 0u, 0u };
  // Invalid length flag
  boolean boInvalidlength = FALSE;

  // Request of low beam
  teRte_ReqLightState     eLowBeamReq = ReqLighted_Off;
  // State of Emergency Operation Mode activation
  boolean                 boLbEmergeOpMode = FALSE;
  // LowBeam State
  SysMon_EnumLowBeamState eLowBeamState = SysMon_LowBeam_Valid_State;

  // Read RTE Low Beam Request
  (void)Rte_Read_SysMon_LowBeamCmd_Req(&eLowBeamReq);

  // Get Low Beam Emergency Operation state
  boLbEmergeOpMode = Rte_Call_Get_LB_EmergencyOperationMode;

  // Get Low Beam State value
  eLowBeamState = Rte_Call_Get_LowBeamState;

  // Check if low beam has valid request or is activated by emergency operation mode
  if (((eLowBeamReq != ReqLighted_Off) && (eLowBeamState != SysMon_LowBeam_Invalid_State)) ||
    ((eLowBeamReq != ReqLighted_Off) && (boLbEmergeOpMode != FALSE)))
  {
    // Return condition not correct for diagnostic routine request
    eReturnCode = CNC;
  }
  else
  {
    // Start or stop routine control
    if ((ucRoutineControlType == DIAG_AFS_CONTROL_START) || (ucRoutineControlType == DIAG_AFS_CONTROL_STOP))
    {
      // Start Afs / Stop Afs
      eReturnCode = Diag_Callbacks_DF17_AFSControl_AfsControlStartStop(ucRoutineControlType, unLength, p_ui8_Data);
    }
    // Afs return Result
    else if (DIAG_AFS_CONTROL_RESULT)
    {
      // Routine Result
      eReturnCode = Diag_Callbacks_DF17_AFSControl_AfsResult(ucRoutineControlType, unLength, NULL_PTR);
    }
    else
    {
      // Return condition not correct for diagnostic routine request
      eReturnCode = CNC;
    }
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DF17_AFSControl_GetAfsStateAcceptanceStatus
///
/// \descr
///
/// \param  eAfsState - Afs State requested
///
/// \return boolean - Afs Searching State
//-----------------------------------------------------------------------------
STATIC_AL boolean Diag_Callbacks_DF17_AFSControl_GetAfsStateAcceptanceStatus(uint8 ucAfsState)
{
  // Left and Right Afs Accepted states
  const teRte_AfsStateRoutineControlRequest aeAfs_LeftAcceptedStates[] = { eAfs_Off, eAfs_Town, eAfs_Pedestrian, eAfs_Country, eAfs_Motorway, eAfs_Boost, eAfs_Bad_Weather_L, eAfs_Fog_L, eAfs_Sequence_L };
  const teRte_AfsStateRoutineControlRequest aeAfs_RightAcceptedStates[] = { eAfs_Off, eAfs_Town, eAfs_Pedestrian, eAfs_Country, eAfs_Motorway, eAfs_Boost, eAfs_Bad_Weather_R, eAfs_Fog_R, eAfs_Sequence_R };

  // Starting pointer for Afs states
  const teRte_AfsStateRoutineControlRequest* peAfs_AcceptedState = NULL_PTR;

  // Afs Searching Status
  boolean boAfsStateAccepted = FALSE;

  // Index for Afs State array
  uint8_least ucIndx = 0u;

  // Mounting side
  teRte_MountingSide eMountingSide = { eMountedUndef };

  // Read Mounting side
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  switch (eMountingSide)
  {
  case eMountedLeft:
    // Take the left Afs states start address
    peAfs_AcceptedState = &aeAfs_LeftAcceptedStates[0];
    break;
  case eMountedRight:
    // Take the right Afs states start address
    peAfs_AcceptedState = &aeAfs_RightAcceptedStates[0];
    break;
  default:
    // keep NULL_PTR
    break;
  }

  // Check Invlaid ptr
  if (peAfs_AcceptedState != NULL_PTR)
  {
    // Check all Afs states
    for (ucIndx = 0u; ucIndx < DIAG_AFS_STATES_NR_ALLOWED; ucIndx++)
    {
      // State Found
      if (ucAfsState == (uint8)peAfs_AcceptedState[ucIndx])
      {
        // Return status true
        boAfsStateAccepted = TRUE;
        break;
      }
      else
      {
        // keep searching
      }
    }
  }

  // Return searching status
  return boAfsStateAccepted;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DF17_AFSControl_AfsControlStartStop
///
/// \descr
///
/// \param  ucRoutineControl
/// \param  ucRoutineLength
/// \param  pucDataIn
/// \param  pucDataOut
///
/// \return pucData
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DF17_AFSControl_AfsControlStartStop(uint8 ucRoutineControl, uint16 unRoutineLength, uint8 const* pucDataIn)
{
  // Afs Request status
  boolean boAfsRequestStatus = TRUE;

  DIAG_status eReturnCode = DIAG_NOK;
  // Response data
  uint8 aucResponseDF17[DIAG_AFS_CONTROL_RES_LENGTH] = { 0u, 0u, 0u, 0u };
  // Set request status on true
  sAfsRoutineControl.boRequestStatus = TRUE;
  // Clear the acknowledge status
  sAfsRoutineControl.boRequestAckStatus = FALSE;

  // switch the routine control
  switch (ucRoutineControl)
  {
    // Afs start
  case DIAG_AFS_CONTROL_START:
    // Afs start
    sAfsRoutineControl.eAfsControl = eAfsControl_Start;
    // check the request length (1 byte)
    if (unRoutineLength == 1u)
    {
      boAfsRequestStatus = Diag_Callbacks_DF17_AFSControl_GetAfsStateAcceptanceStatus(pucDataIn[0]);

      if (boAfsRequestStatus != FALSE)
      {
        // check the first byte
        switch (pucDataIn[0])
        {
          // Convert the raw data into request
        case 1u: sAfsRoutineControl.eAfsRequest = eAfs_Off; break;
        case 2u: sAfsRoutineControl.eAfsRequest = eAfs_Town; break;
        case 3u: sAfsRoutineControl.eAfsRequest = eAfs_Pedestrian; break;
        case 4u: sAfsRoutineControl.eAfsRequest = eAfs_Country; break;
        case 5u: sAfsRoutineControl.eAfsRequest = eAfs_Motorway; break;
        case 6u: sAfsRoutineControl.eAfsRequest = eAfs_Boost; break;
        case 7u: sAfsRoutineControl.eAfsRequest = eAfs_Bad_Weather_L; break;
        case 8u: sAfsRoutineControl.eAfsRequest = eAfs_Bad_Weather_R; break;
        case 9u: sAfsRoutineControl.eAfsRequest = eAfs_Fog_L; break;
        case 10u: sAfsRoutineControl.eAfsRequest = eAfs_Fog_R; break;
        case 11u: sAfsRoutineControl.eAfsRequest = eAfs_Sequence_L; break;
        case 12u: sAfsRoutineControl.eAfsRequest = eAfs_Sequence_L; break;
        default: sAfsRoutineControl.eAfsRequest = eAfs_Off; break;
        }

        // Write the RTE port with request
        (void)Rte_Write_Diag_RoutineControl(&sAfsRoutineControl);

        // Set response data
        aucResponseDF17[0] = ucRoutineControl;
        aucResponseDF17[1] = DIAG_AFS_CONTROL_RES_BYTE_1;
        aucResponseDF17[2] = DIAG_AFS_CONTROL_RES_BYTE_2;
        aucResponseDF17[3] = (uint8)eRoutineFinishedOK;;
        Diag_boRoutineFinishedDF17 = TRUE;

        // Call diag response function
        eReturnCode = DIAG_Send_Diag_Response(aucResponseDF17, DIAG_AFS_CONTROL_RES_LENGTH);
      }
      else
      {
        eReturnCode = RSE;
      }
    }
    else
    {
      // Return invalid data length for diagnostic routine request
      eReturnCode = IMLOIF;
    }
    break;
    // Afs stop
  default:
    if (Diag_boRoutineFinishedDF17 == TRUE)
    {
      // check the request length (0 byte)
      if (unRoutineLength == 0u)
      {
        // Afs stop
        sAfsRoutineControl.eAfsControl = eAfsControl_Stop;

        // Write the RTE port with request
        (void)Rte_Write_Diag_RoutineControl(&sAfsRoutineControl);

        // Set response data
        aucResponseDF17[0] = ucRoutineControl;
        aucResponseDF17[1] = DIAG_AFS_CONTROL_RES_BYTE_1;
        aucResponseDF17[2] = DIAG_AFS_CONTROL_RES_BYTE_2;
        aucResponseDF17[3] = (uint8)eRoutineStopped;
        Diag_boRoutineFinishedDF17 = FALSE;

        // Call diag response function
        eReturnCode = DIAG_Send_Diag_Response(aucResponseDF17, DIAG_AFS_CONTROL_RES_LENGTH);
      }
      else
      {
        // Return invalid data length for diagnostic routine request
        eReturnCode = IMLOIF;
      }
    }
    else
    {
      eReturnCode = RSE;
    }
    break;
  }

  return eReturnCode;

  //PRQA S 5316 2 // STCYC exceeded due to reuse of existing code
  //PRQA S 5330 1 // STST3 exceeded due to reuse of existing code
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DF17_AFSControl_AfsResult
///
/// \descr
///
/// \param  ucRoutineControl
/// \param  ucRoutineLength
/// \param  pucDataIn
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DF17_AFSControl_AfsResult(uint8 ucRoutineControl, uint16 unRoutineLength, uint8 const* pucDataIn)
{
  DIAG_status eReturnCode = DIAG_NOK;
  // Response data
  uint8 aucResponseDF17[DIAG_AFS_CONTROL_RES_LENGTH] = { 0u, 0u, 0u, 0u };

  (void)pucDataIn;

  // read Diagnostic Routine Control Rte Port
  (void)Rte_Read_Diag_RoutineControl(&sAfsRoutineControl);

  if (Diag_boRoutineFinishedDF17 == TRUE)
  {
    // Request length valid
    if (unRoutineLength == 0u)
    {
      // Afs rountine ongoing
      if (sAfsRoutineControl.boRequestAckStatus != FALSE)
      {
        // Set response data
        aucResponseDF17[0] = ucRoutineControl;
        aucResponseDF17[1] = DIAG_AFS_CONTROL_RES_BYTE_1;
        aucResponseDF17[2] = DIAG_AFS_CONTROL_RES_BYTE_2;
        aucResponseDF17[3] = (uint8)eRoutineInProgress;

        // Call diag response function
        eReturnCode = DIAG_Send_Diag_Response(aucResponseDF17, DIAG_AFS_CONTROL_RES_LENGTH);
      }
      // Afs rountine stoped
      else
      {
        // Set response data
        aucResponseDF17[0] = ucRoutineControl;
        aucResponseDF17[1] = DIAG_AFS_CONTROL_RES_BYTE_1;
        aucResponseDF17[2] = DIAG_AFS_CONTROL_RES_BYTE_2;
        aucResponseDF17[3] = (uint8)eRoutineFinishedOK;

        // Call diag response function
        eReturnCode = DIAG_Send_Diag_Response(aucResponseDF17, DIAG_AFS_CONTROL_RES_LENGTH);
      }
    }
    else
    {
      // Return invalid data length for diagnostic routine request
      eReturnCode = IMLOIF;
    }
  }
  else
  {
    eReturnCode = RSE;
  }

  return eReturnCode;
}
#endif


#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DD06_LvlDCMotorPosition
///
/// \descr Levelling DC Motor controls - Set DC Motor Position
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DD06_LvlDCMotorPosition(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Response data
  uint8 aucResponseDD06[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };

  // Invalid length flag
  boolean boInvalidlength = FALSE;

  // DC Motor position request
  uint8 ucPosRequest = 0u;

  static boolean boRoutineStoppedOK = FALSE;

  // Handle coding data
  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  // Check coding validation
  if (boCodingValidity != FALSE)
  {
    // Check if DC Motor is present in Coding
    if (Diag_pCodingArea->AvacStp.DCMotorData.ucAsl_Enable == DIAG_OPTION_ENABLED)
    {
      switch (ucRoutineControlType)
      {
      case DIAG_ROUTINE_CONTROL_TYPE_START:
        // reset flag
        boRoutineStoppedOK = FALSE;

        // Set request status on true
        Diag_sDcMotorRoutineControl.boRequestStatus = TRUE;
        // Clear the acknowledge status
        Diag_sDcMotorRoutineControl.boRequestAckStatus = FALSE;

        Diag_sDcMotorRoutineControl.eDcmDID = eDD06;

        Diag_sDcMotorRoutineControl.eDcmControl = eDcmControl_Start;

        // check the request length (1 byte)
        if (unLength == DIAG_RESP_1BYTE)
        {
          // Get position
          ucPosRequest = p_ui8_Data[0];
          // Limit between 20% and 80% of Vbat
          ucPosRequest = max(DIAG_DCM_MIN_LEVEL, ucPosRequest);
          ucPosRequest = min(ucPosRequest, DIAG_DCM_MAX_LEVEL);

          Diag_sDcMotorRoutineControl.ucPosRequest = ucPosRequest;

          // Write the RTE port with request
          (void)Rte_Write_Dcm_RoutineControl(&Diag_sDcMotorRoutineControl);

          // Set response data
          aucResponseDD06[0] = ucRoutineControlType;
          aucResponseDD06[1] = DIAG_DD06_ID_1;
          aucResponseDD06[2] = DIAG_DD06_ID_2;
          aucResponseDD06[3] = (uint8)eRoutineFinishedOK;;

          Diag_boRoutineFinishedDD06 = TRUE;

          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD06, DIAG_RESP_4BYTES);
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_STOP:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDD06 == TRUE)
          {
            // Set request status on true
            Diag_sDcMotorRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            Diag_sDcMotorRoutineControl.boRequestAckStatus = FALSE;
            // Dcm stop
            Diag_sDcMotorRoutineControl.eDcmControl = eDcmControl_Stop;

            // Write the RTE port with request
            (void)Rte_Write_Dcm_RoutineControl(&Diag_sDcMotorRoutineControl);

            // Set response data
            aucResponseDD06[0] = ucRoutineControlType;
            aucResponseDD06[1] = DIAG_DD06_ID_1;
            aucResponseDD06[2] = DIAG_DD06_ID_2;
            aucResponseDD06[3] = (uint8)eRoutineStopped;
            Diag_boRoutineFinishedDD06 = FALSE;
            boRoutineStoppedOK = TRUE;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD06, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
            boRoutineStoppedOK = FALSE;
          }
        }
        else
        {
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (boRoutineStoppedOK != FALSE)
          {
            // Set response data
            aucResponseDD06[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDD06[1] = DIAG_DD06_ID_1;
            aucResponseDD06[2] = DIAG_DD06_ID_2;
            aucResponseDD06[3] = (uint8)eRoutineStopped;
            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD06, DIAG_RESP_4BYTES);
          }
          else if (Diag_boRoutineFinishedDD06 == TRUE)
          {
            // read Diagnostic Routine Control Rte Port
            (void)Rte_Read_Dcm_RoutineControl(&Diag_sDcMotorRoutineControl);

            // Dcm routine ongoing
            if (Diag_sDcMotorRoutineControl.boRequestAckStatus != FALSE)
            {
              // Set response data
              aucResponseDD06[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDD06[1] = DIAG_DD06_ID_1;
              aucResponseDD06[2] = DIAG_DD06_ID_2;
              aucResponseDD06[3] = (uint8)eRoutineInProgress;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDD06, DIAG_RESP_4BYTES);
            }
            // Dcm routine stopped
            else
            {
              // Set response data
              aucResponseDD06[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDD06[1] = DIAG_DD06_ID_1;
              aucResponseDD06[2] = DIAG_DD06_ID_2;
              aucResponseDD06[3] = (uint8)eRoutineFinishedOK;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDD06, DIAG_RESP_4BYTES);
            }
          }
          else
          {
            eReturnCode = RSE;
          }
        }
        else
        {
          eReturnCode = IMLOIF;
        }
        break;
      default:
        // Sub function not supported
        eReturnCode = SFNS;
        break;
      }
    }
    else
    {
      // Sub function not supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }
  return eReturnCode;
  //PRQA S 5330, 5336 1 // STST3 exceeded due to program architecture and readability
}
#endif


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DD03_Fan1Activation
///
/// \descr Activation left fan
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DD03_Fan1Activation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  (void)p_ui8_Data;

  DIAG_status eReturnCode = DIAG_NOK;
  static boolean boRoutineStoppedOK = FALSE;

  // Response data
  uint8 aucResponseDD03[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };

  // Handle coding data
  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  // Check coding validation
  if (boCodingValidity != FALSE)
  {
    // Check if FAN1 is present in Coding
#if defined (SAMPLE_FULL)
    if (Diag_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled == DIAG_OPTION_ENABLED)
#else
    if ((Diag_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled == DIAG_OPTION_ENABLED) && (Diag_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME != DIAG_HSS_SM) && (Diag_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME != DIAG_HSS_DRL))
#endif
    {
      switch (ucRoutineControlType)
      {
      case DIAG_ROUTINE_CONTROL_TYPE_START:
        //Length Ok
        if (unLength == DIAG_RESP_0BYTE)
        {
          // reset flag
          boRoutineStoppedOK = FALSE;
          //Activation of FAN1
          roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start(DIAG_FAN1, TRUE);
          // Set response data
          aucResponseDD03[0] = ucRoutineControlType;
          aucResponseDD03[1] = DIAG_DD03_ID_1;
          aucResponseDD03[2] = DIAG_DD03_ID_2;
          aucResponseDD03[3] = (uint8)eRoutineFinishedOK;
          Diag_boRoutineFinishedDD03 = TRUE;
          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD03, DIAG_RESP_4BYTES);
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_STOP:
        //Length Ok
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDD03 == TRUE)
          {
            //Deactivation of FAN1
            roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(DIAG_FAN1);
            // Set response data
            aucResponseDD03[0] = ucRoutineControlType;
            aucResponseDD03[1] = DIAG_DD03_ID_1;
            aucResponseDD03[2] = DIAG_DD03_ID_2;
            aucResponseDD03[3] = (uint8)eRoutineStopped;
            Diag_boRoutineFinishedDD03 = FALSE;
            boRoutineStoppedOK = TRUE;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD03, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
            boRoutineStoppedOK = FALSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
        //Length Ok
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDD03 == TRUE)
          {
            // Set response data
            aucResponseDD03[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDD03[1] = DIAG_DD03_ID_1;
            aucResponseDD03[2] = DIAG_DD03_ID_2;
            aucResponseDD03[3] = (uint8)eRoutineFinishedOK;
            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD03, DIAG_RESP_4BYTES);
          }
          // fan routine stopped
          else if (boRoutineStoppedOK != FALSE)
          {
            // Set response data
            aucResponseDD03[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDD03[1] = DIAG_DD03_ID_1;
            aucResponseDD03[2] = DIAG_DD03_ID_2;
            aucResponseDD03[3] = (uint8)eRoutineStopped;
            // call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD03, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      default:
        // Sub function not supported
        eReturnCode = SFNS;
        break;
      }
    }
    else
    {
      // FAN1 is not present, NRC 0x12 Sub Function Not Supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }

  return eReturnCode;
} // PRQA S 5336 1 // STMIF exceeded due to reuse of existing code


//-----------------------------------------------------------------------------
/// \brief Diag_Ld_Control
///
/// \descr light distribution control
///
/// \param  boDiagStatus - diagnostic service status
/// \param  pucData - Data in
///
/// \return void
//-----------------------------------------------------------------------------      
STATIC_AL DIAG_status Diag_Ld_Control(const boolean boDiagStatus, uint8 const* pucData)
{
  DIAG_status ucRet = DIAG_OK;
  teRte_SateliteStatus eSateliteStatus;
  boolean boScrollingTakeOver_Status;
  //check for diag activation
  if (boDiagStatus != FALSE)
  {
    //range check
    if ((pucData[0] >= DIAG_LD_CTRL_MIN_RANGE_BYTE0 && pucData[0] <= DIAG_LD_CTRL_MAX_RANGE_BYTE0) && (pucData[1] >= DIAG_LD_CTRL_MIN_RANGE_BYTE1 && pucData[1] <= DIAG_LD_CTRL_MAX_RANGE_BYTE1))
    {
      //save diagnostic light distribution request status
      Diag_sLd_ActivationRoutineControl.boRequestStatus = boDiagStatus;

      //commands for light distributions
      CONST_AL uint8 aucLd_Cmd_Table[] = {
        /*0 (undefined) */
        /*1 (Low Beam LD1 - Town Light(class V))  */ 0U,    /*0 biLB_TownLight             */
        /*2 (Low Beam LD2 - Pedestrian)           */ 1U,    /*1 biLB_Pedestrian            */
        /*3 (Low Beam LD3 - Country(class C))     */ 2U,    /*2 biLB_CountryLight          */
        /*4 (Low Beam LD4 - Motorway Light)       */ 3U,    /*3 biLB_MotorwayLight         */
        /*5 (Low Beam LD5 - Low Beam Boost)       */ 4U,    /*4 biLB_Boost                 */
        /*6 (Low Beam LD6 - Bad Weather LHD)      */ 7U,    /*5 biLB_AdverseWeather_RHD    */
        /*7 (Low Beam LD7 - Bad WeatherRHD)       */ 5U,    /*6 biFoggyWeather_RHD         */
        /*8 (Low Beam LD8 - Foggy Weather LHD)    */ 8U,    /*7 biLB_AdverseWeather_LHD    */
        /*9 (Low Beam LD9 - Foggy Weather RHD)    */ 6U,    /*8 biFoggyWeather_LHD         */
        /*A  (Low Beam LD10 - Reserved)           */ 9U,    /*9 biLB_Reserved              */
        /*B  (Low Beam LD11 - Reserved)           */ 10U,   /*10 biLB_Reserved             */
        /*C  (Low Beam LD12 - Reserved)           */ 11U,   /*11 biLB_Reserved             */
        /*D  (Low Beam LD13 - Reserved)           */ 12U,   /*12 biLB_Reserved             */
        /*E  (High Beam LD1 - High Beam)          */ 13U,   /*13 biHB_HighBeam             */
        /*F  (High Beam LD2 - High Beam Boost)    */ 14U,   /*14 biHB_Boost                */
        /*10 (High Beam LD3 - Aiming Mode)        */ 15U,   /*15 biHB_AimingMode           */
        /*11 (High Beam LD4 - Alignment Mode)     */ 16U,   /*16 biHB_AdjustementMode      */
        /*12 (High Beam LD5 - Reserved)           */ 17U,   /*17 biHB_FlashToPass          */
        /*13 (High Beam LD6 - Reserved)           */ 18U,   /*18 biHB_Reserved2            */
        /*14 (High Beam LD7 - Reserved)           */ 19U,   /*19 biHB_Reserved2            */
        /*15 (High Beam LD8 - Reserved)           */ 20U,   /*20 biHB_Reserved2            */
        /*16 (High Beam LD9 - Reserved)           */ 21U,   /*21 biHB_Reserved2            */
        /*17 (Daytime Running Light DRL)          */ 22U,   /*22 biDRL_DaytimeRunningLight */
        /*18 (Position Light)                     */ 23U,   /*23 biPOS_PositionLight       */
        /*19 (Parking Light)                      */ 24U,   /*24 biPKL_ParkingLight        */
        /*1A (Static Bending Light(SBL))          */ 25U,   /*25 biSBL_StaticBendingLight  */
        /*1B (Cornering Light(CL))                */ 26U,   /*26 biCL_CorneringLight       */
        /*1C (Fog Light)                          */ 27U,   /*27 biFL_FogLight             */
        /*1D (Side Marker)                        */ 28U,   /*28 biSM_SideMarker           */
        /*1E (Turn Indicator)                     */ 29U,   /*29 biTI_TurnIndicator        */
        /*1F (Turn Indicator PO)                  */ 30U,   /*30 biTI_TICmdPOS             */
        /*20 (Turn Indicator PO with Blink)       */ 31U    /*31 biTI_TIReqPOS             */
      };

      // Activate light request based on diagnostic data request
      Diag_sLd_ActivationRoutineControl.uTgtLgtFct.ulRaw = ((uint32)1U << aucLd_Cmd_Table[pucData[1] - 1U]);
      if (Diag_sLd_ActivationRoutineControl.uTgtLgtFct.Bits.biTI_TiReqPos != 0U)
      {
        boScrollingTakeOver_Status = TRUE;
        (void)Rte_Write_Diag_TiScrollingTakeOver(&boScrollingTakeOver_Status);

        eSateliteStatus = eRte_eScrollingSatelite_On_Scrolling_On;

        (void)Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(&eSateliteStatus);
      }
      else
      {
        (void)Rte_Read_Diag_TiScrollingTakeOver(&boScrollingTakeOver_Status);
        if (boScrollingTakeOver_Status != FALSE)
        {
          boScrollingTakeOver_Status = FALSE;
          (void)Rte_Write_Diag_TiScrollingTakeOver(&boScrollingTakeOver_Status);

          eSateliteStatus = eRte_ScrollingSatelite_Off;

          (void)Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(&eSateliteStatus);
        }
      }
    }
    else
    {
      //invalid range
      ucRet = ROOR;
    }
  }
  else
  {
    (void)*pucData;
    Diag_sLd_ActivationRoutineControl.boRequestStatus = boDiagStatus;
    //reset all bits
    Diag_sLd_ActivationRoutineControl.uTgtLgtFct.ulRaw = 0x0U;

    (void)Rte_Read_Diag_TiScrollingTakeOver(&boScrollingTakeOver_Status);
    if (boScrollingTakeOver_Status != FALSE)
    {
      boScrollingTakeOver_Status = FALSE;
      (void)Rte_Write_Diag_TiScrollingTakeOver(&boScrollingTakeOver_Status);

      eSateliteStatus = eRte_ScrollingSatelite_Off;

      (void)Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(&eSateliteStatus);
    }
  }

  //write rte port
  (void)Rte_Write_Diag_LdActivationRoutineControl(&Diag_sLd_ActivationRoutineControl);
  //return value
  return ucRet;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DD00_LdActivation
///
/// \descr Activation ld
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DD00_LdActivation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  (void)unLength;
  DIAG_status eReturnCode = DIAG_NOK;

  // Response data
  uint8 aucResponseDD00[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };

  static boolean boRoutineStoppedOK = FALSE;

  // Request of low beam
  teRte_ReqLightState     eLowBeamReq = ReqLighted_Off;
  // State of Emergency Operation Mode activation
  boolean                 boLbEmergeOpMode = FALSE;
  // Speed State 
  SysMon_EnumSpeedState   eSpeedState = SysMon_Speed_0_State;
  // Turn Indicator State 
  SysMon_EnumTurnIndicatorState eTurnIndicatorState = SysMon_TurnIndicator_Invalid_State;
  // LowBeam State
  SysMon_EnumLowBeamState       eLowBeamState = SysMon_LowBeam_Valid_State;
  // Turn Indicator Command Value
  boolean                       boTiCmdVal = FALSE;
  // Activation/Deactivation multiplexer for Start Routine
  boolean                       boStartMultiplexer = FALSE;

  // Read RTE Low Beam Request
  (void)Rte_Read_SysMon_LowBeamCmd_Req(&eLowBeamReq);

  // Get Low Beam Emergency Operation state
  boLbEmergeOpMode = Rte_Call_Get_LB_EmergencyOperationMode;

  // Get Speed State value
  eSpeedState = Rte_Call_Get_SpeedState;

  // Get TurnIndicator State value
  eTurnIndicatorState = Rte_Call_Get_TurnIndicatorState;

  // Get Low Beam State value
  eLowBeamState = Rte_Call_Get_LowBeamState;

  // Get TI Command Value
  boTiCmdVal = Rte_Call_Get_TICmdValue;


  // Check if TI and LB are ON and give NRC
  if (((((eLowBeamReq != ReqLighted_Off) && (eLowBeamState != SysMon_LowBeam_Invalid_State)) ||
    ((eLowBeamReq != ReqLighted_Off) && (boLbEmergeOpMode != FALSE))) &&
    ((p_ui8_Data[1] >= LOWBEAM_TOWN_LIGHT) && (p_ui8_Data[1] <= LOWBEAM_FOGGY_WEATHER))) ||
    (((eSpeedState != SysMon_Speed_0_State) ||
    ((boTiCmdVal == FALSE) && (eTurnIndicatorState != SysMon_TurnIndicator_Invalid_State)) ||
      (eTurnIndicatorState != SysMon_TurnIndicator_Valid_State)) &&
      ((p_ui8_Data[1] >= TURNINDICATOR_TI) && (p_ui8_Data[1] <= TURNINDICATOR_TI_BLINK))))
  {
    // Negative response 0x22 Conditions Not Correct
    eReturnCode = CNC;
  }
  else
  {
    switch (ucRoutineControlType)
    {
    case DIAG_ROUTINE_CONTROL_TYPE_START:

      if ((unLength == DIAG_RESP_2BYTES) || (unLength == DIAG_RESP_1BYTE))
      {
        // Check Activation/Deactivation Request
        switch (p_ui8_Data[0])
        {
        case DIAG_LD_CTRL_ACTIVATION:
          // Activation Request Received, select light distribution control
          eReturnCode = Diag_Ld_Control(TRUE, p_ui8_Data);
          break;
        case DIAG_LD_CTRL_DEACTIVATION:
          // Deactivation Request Received, turn off all light distributions
          eReturnCode = Diag_Ld_Control(FALSE, p_ui8_Data);
          break;
        default:
          //invalid range
          eReturnCode = ROOR;
          break;
        }

        //check diag status
        if (eReturnCode != ROOR)
        {
          // reset flag
          boRoutineStoppedOK = FALSE;
          // Set response data
          aucResponseDD00[0] = ucRoutineControlType;
          aucResponseDD00[1] = DIAG_DD00_ID_1;
          aucResponseDD00[2] = DIAG_DD00_ID_2;
          aucResponseDD00[3] = (uint8)eRoutineFinishedOK;
          Diag_boRoutineFinishedDD00 = TRUE;
          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD00, DIAG_RESP_4BYTES);
        }
      }
      else
      {
        // Return invalid data length for diagnostic routine request
        eReturnCode = IMLOIF;
      }
      break;
    case DIAG_ROUTINE_CONTROL_TYPE_STOP:

      if (unLength == DIAG_RESP_0BYTE)
      {
        if (Diag_boRoutineFinishedDD00 == TRUE)
        {
          //light distribution control
          (void)Diag_Ld_Control(FALSE, p_ui8_Data);
          // Set response data
          aucResponseDD00[0] = ucRoutineControlType;
          aucResponseDD00[1] = DIAG_DD00_ID_1;
          aucResponseDD00[2] = DIAG_DD00_ID_2;
          aucResponseDD00[3] = (uint8)eRoutineStopped;
          Diag_boRoutineFinishedDD00 = FALSE;
          boRoutineStoppedOK = TRUE;

          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD00, DIAG_RESP_4BYTES);
        }
        else
        {
          eReturnCode = RSE;
          boRoutineStoppedOK = FALSE;
        }
      }
      else
      {
        // Return invalid data length for diagnostic routine request
        eReturnCode = IMLOIF;
      }
      break;
    case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:

      if (unLength == DIAG_RESP_0BYTE)
      {
        if (Diag_boRoutineFinishedDD00 == TRUE)
        {
          // Set response data
          aucResponseDD00[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
          aucResponseDD00[1] = DIAG_DD00_ID_1;
          aucResponseDD00[2] = DIAG_DD00_ID_2;
          aucResponseDD00[3] = (uint8)eRoutineFinishedOK;
          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD00, DIAG_RESP_4BYTES);
        }
        // routine stopped
        else if (boRoutineStoppedOK != FALSE)
        {
          // Set response data
          aucResponseDD00[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
          aucResponseDD00[1] = DIAG_DD00_ID_1;
          aucResponseDD00[2] = DIAG_DD00_ID_2;
          aucResponseDD00[3] = (uint8)eRoutineStopped;
          // call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD00, DIAG_RESP_4BYTES);
        }
        else
        {
          eReturnCode = RSE;
        }
      }
      else
      {
        // Return invalid data length for diagnostic routine request
        eReturnCode = IMLOIF;
      }
      break;
    default:
      // Sub function not supported
      eReturnCode = SFNS;
      break;
    }
  }

  return eReturnCode;
} // PRQA S 5324, 5330, 5336 1 // STCAL exceeded due to reuse of existing code


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_0301_RESET_CPU_LOAD
///
/// \descr CPU laod reset
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_0301_RESET_CPU_LOAD(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data) //PRQA S 3206 1 // architecture, parameter not used
{
  (void)p_ui8_Data;

  DIAG_status eReturnCode = DIAG_NOK;
  // Response data
  uint8 aucResponse0301[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };
  static boolean boRoutine0301_Start_Status = FALSE;

  switch (ucRoutineControlType)
  {
  case DIAG_ROUTINE_CONTROL_TYPE_START:

    if (unLength == DIAG_RESP_2BYTES)
    {
      (void)Rte_Write_StatM_StackUsage(0u);
      (void)Rte_Write_OS_CPULoadPeak(0u);

      if ((p_ui8_Data[0] > 1u) || (p_ui8_Data[1] != 1u))
      {
        // Request error - procesor ID invalid or sequence error
        eReturnCode = RSE;
      }
      else
      {
        boRoutine0301_Start_Status = TRUE;
        switch (p_ui8_Data[0])
        {
        case 0u: (void)Rte_Write_OS_CPULoadPeak(0u); break;
        default: (void)Rte_Write_StatM_StackUsage(0u); break;
        }
        // Set response data
        aucResponse0301[0] = ucRoutineControlType;
        aucResponse0301[1] = DIAG_0301_ID_1;
        aucResponse0301[2] = DIAG_0301_ID_2;
        aucResponse0301[3] = (uint8)eRoutineFinishedOK;

        // Call diag response function
        eReturnCode = DIAG_Send_Diag_Response(aucResponse0301, DIAG_RESP_4BYTES);
      }
    }
    else
    {
      // Return invalid data length for diagnostic routine request
      eReturnCode = IMLOIF;
    }

    break;
  case DIAG_ROUTINE_CONTROL_TYPE_STOP:
    // Stop sub-function not suported
    eReturnCode = SFNS;
    break;
  case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
    if (unLength == DIAG_RESP_0BYTE)
    {
      if (boRoutine0301_Start_Status != FALSE)
      {
        // Reset the Routine Start Status
        boRoutine0301_Start_Status = FALSE;
        // Set response data
        aucResponse0301[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
        aucResponse0301[1] = DIAG_0301_ID_1;
        aucResponse0301[2] = DIAG_0301_ID_2;
        aucResponse0301[3] = (uint8)eRoutineFinishedOK;
        // Call diag response function
        eReturnCode = DIAG_Send_Diag_Response(aucResponse0301, DIAG_RESP_4BYTES);
      }
      else
      {
        // Sequence error
        eReturnCode = RSE;
      }
    }
    else
    {
      // Return invalid data length for diagnostic routine request
      eReturnCode = IMLOIF;
    }
    break;
  default:
    // Sub function not supported
    eReturnCode = SFNS;
    break;
  }

  return eReturnCode;
} // PRQA S 5330 1 // STCAL exceeded due to reuse of existing code


#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DD01_PixelActivation
///
/// \descr Activation of pixel
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DD01_PixelActivation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Response data
  uint8                           aucResponseDD01[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };
  boolean                         boCheckMaxPwm = FALSE;
  static boolean                  boRoutineStoppedOK = FALSE;
  tsRte_SigPrep_VehicleConfigSig  sDataVehConfig = { 0 };

  // Get Vehicle Configuration Mode
  (void)Rte_Read_SigPrep_VehicleConfigSig(&sDataVehConfig);

  // Routine is not allowed to be executed in Customer Mode
  if ((sDataVehConfig.eSigQty == SIG_VALID) && (sDataVehConfig.eVehicleCfg != eModeConfigVehicle_Client))
  {
    switch (ucRoutineControlType)
    {
    case DIAG_ROUTINE_CONTROL_TYPE_START:

      if (unLength == DIAG_RESP_103BYTES)
      {
        // Check if the value is out of range 0..100% PWM
        for (uint8_fast ucIx = 0u; ucIx < CFG_LOGICAL_UNITS; ucIx++)
        {
          if (p_ui8_Data[ucIx] > DIAG_MAX_PWM_100)
          {
            boCheckMaxPwm = TRUE;
            // Break out of for loops because there is one pixel intensity over 100%
            break;
          }
          else
          {
            Diag_boDD01_PixelActivation.ucPixelIntensity[ucIx] = p_ui8_Data[ucIx];
          }
        }

        // If PWM Range check has exceeded , give Conditions Not Correct
        if (boCheckMaxPwm != FALSE)
        {
          // Return Conditions not correct
          eReturnCode = CNC;
        }
        else
        {
          // Set Diagnostic Activation Status to True
          Diag_boDD01_Status = TRUE;
          (void)Rte_Write_Diag_DD01_Activation(&Diag_boDD01_Status);

          // Write Pixel Intensties to Rte port
          (void)Rte_Write_Diag_DD01_PixelActivation(&Diag_boDD01_PixelActivation);

          // reset flag
          boRoutineStoppedOK = FALSE;
          // Set response data
          aucResponseDD01[0] = ucRoutineControlType;
          aucResponseDD01[1] = DIAG_DD01_ID_1;
          aucResponseDD01[2] = DIAG_DD01_ID_2;
          aucResponseDD01[3] = (uint8)eRoutineFinishedOK;
          Diag_boRoutineFinishedDD01 = TRUE;

          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD01, DIAG_RESP_4BYTES);
        }
      }
      else
      {
        // Return invalid data length for diagnostic routine request
        eReturnCode = IMLOIF;
      }

      break;
    case DIAG_ROUTINE_CONTROL_TYPE_STOP:
      if (unLength == DIAG_RESP_0BYTE)
      {
        if (Diag_boRoutineFinishedDD01 == TRUE)
        {
          Diag_boDD01_Status = FALSE;
          (void)Rte_Write_Diag_DD01_Activation(&Diag_boDD01_Status);
          for (uint8_fast ucIx = 0u; ucIx < CFG_LOGICAL_UNITS; ucIx++)
          {
            Diag_boDD01_PixelActivation.ucPixelIntensity[ucIx] = 0U;
          }

          (void)Rte_Write_Diag_DD01_PixelActivation(&Diag_boDD01_PixelActivation);
          // Set response data
          aucResponseDD01[0] = ucRoutineControlType;
          aucResponseDD01[1] = DIAG_DD01_ID_1;
          aucResponseDD01[2] = DIAG_DD01_ID_2;
          aucResponseDD01[3] = (uint8)eRoutineStopped;
          Diag_boRoutineFinishedDD01 = FALSE;
          boRoutineStoppedOK = TRUE;

          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD01, DIAG_RESP_4BYTES);
        }
        else
        {
          eReturnCode = RSE;
          boRoutineStoppedOK = FALSE;
        }
      }
      else
      {
        // Return invalid data length for diagnostic routine request
        eReturnCode = IMLOIF;
      }
      break;
    case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
      if (unLength == DIAG_RESP_0BYTE)
      {
        if (Diag_boRoutineFinishedDD01 == TRUE)
        {
          // Set response data
          aucResponseDD01[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
          aucResponseDD01[1] = DIAG_DD01_ID_1;
          aucResponseDD01[2] = DIAG_DD01_ID_2;
          aucResponseDD01[3] = (uint8)eRoutineFinishedOK;
          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD01, DIAG_RESP_4BYTES);
        }
        // Fan routine stopped
        else if (boRoutineStoppedOK != FALSE)
        {
          // Set response data
          aucResponseDD01[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
          aucResponseDD01[1] = DIAG_DD01_ID_1;
          aucResponseDD01[2] = DIAG_DD01_ID_2;
          aucResponseDD01[3] = (uint8)eRoutineStopped;
          // call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD01, DIAG_RESP_4BYTES);
        }
        else
        {
          eReturnCode = RSE;
        }
      }
      else
      {
        // Return invalid data length for diagnostic routine request
        eReturnCode = IMLOIF;
      }
      break;
    default:
      // Sub function not supported
      eReturnCode = SFNS;
      break;
    }
  }
  else
  {
    // Conditions not correct
    eReturnCode = CNC;
  }

  return eReturnCode;
} // PRQA S 5330, 5336 1 // STCAL exceeded due to reuse of existing code


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DD04_Fan2Activation
///
/// \descr Activation right fan
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DD04_Fan2Activation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  (void)p_ui8_Data;
  DIAG_status eReturnCode = DIAG_NOK;

  static boolean boRoutineStoppedOK = FALSE;

  // Response data
  uint8 aucResponseDD04[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };

  // Handle coding data
  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  // Check coding validation
  if (boCodingValidity != FALSE)
  {
    // Check if FAN2 is present in Coding
    if (Diag_pCodingArea->Fan1.Fans_Presence.ucFan2Enabled == DIAG_OPTION_ENABLED)
    {
      switch (ucRoutineControlType)
      {
      case DIAG_ROUTINE_CONTROL_TYPE_START:

        if (unLength == DIAG_RESP_0BYTE)
        {
          // reset flag
          boRoutineStoppedOK = FALSE;
          //Activation of FAN2
          roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start(DIAG_FAN2, TRUE);
          // Set response data
          aucResponseDD04[0] = ucRoutineControlType;
          aucResponseDD04[1] = DIAG_DD04_ID_1;
          aucResponseDD04[2] = DIAG_DD04_ID_2;
          aucResponseDD04[3] = (uint8)eRoutineFinishedOK;
          Diag_boRoutineFinishedDD04 = TRUE;

          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDD04, DIAG_RESP_4BYTES);
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }

        break;
      case DIAG_ROUTINE_CONTROL_TYPE_STOP:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDD04 == TRUE)
          {
            //Deactivation of FAN2
            roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(DIAG_FAN2);
            // Set response data
            aucResponseDD04[0] = ucRoutineControlType;
            aucResponseDD04[1] = DIAG_DD04_ID_1;
            aucResponseDD04[2] = DIAG_DD04_ID_2;
            aucResponseDD04[3] = (uint8)eRoutineStopped;
            Diag_boRoutineFinishedDD04 = FALSE;
            boRoutineStoppedOK = TRUE;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD04, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
            boRoutineStoppedOK = FALSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDD04 == TRUE)
          {
            // Set response data
            aucResponseDD04[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDD04[1] = DIAG_DD04_ID_1;
            aucResponseDD04[2] = DIAG_DD04_ID_2;
            aucResponseDD04[3] = (uint8)eRoutineFinishedOK;
            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD04, DIAG_RESP_4BYTES);
          }
          // Fan routine stopped
          else if (boRoutineStoppedOK != FALSE)
          {
            // Set response data
            aucResponseDD04[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDD04[1] = DIAG_DD04_ID_1;
            aucResponseDD04[2] = DIAG_DD04_ID_2;
            aucResponseDD04[3] = (uint8)eRoutineStopped;
            // call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD04, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      default:
        // Sub function not supported
        eReturnCode = SFNS;
        break;
      }
    }
    else
    {
      // FAN2 is not present, NRC 0x12 Sub Function Not Supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }

  return eReturnCode;
}  // PRQA S 5336 1 // STMIF exceeded due to reuse of existing code


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DD05_LvlStepperPosition
///
/// \descr Levelling stepper controls - Set Stepper Position 
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DD05_LvlStepperPosition(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Response data
  uint8 aucResponseDD05[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };

  // Invalid length flag
  boolean boInvalidlength = FALSE;

  tsRte_CddStpActual sStpDrvData = { 0 };

  // Stepper position request
  sint16 snPosRequest = 0;
  uint16 unPosRequest = 0u;

  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  static boolean boRoutineStoppedOK = FALSE;

  if (boCodingValidity != FALSE)
  {
    // Check if ADL option is present in Coding for FULL version
    if (Diag_pCodingArea->AvacStp.Modus.ucAvacStp_Enable == DIAG_OPTION_ENABLED)
    {
      switch (ucRoutineControlType)
      {
      case DIAG_ROUTINE_CONTROL_TYPE_START:
        if (unLength == DIAG_RESP_2BYTES)
        {
          // read stepper driver information
          (void)Rte_Read_ppCddStpActual0_sStpActualValues(&sStpDrvData);

          // reset flag
          boRoutineStoppedOK = FALSE;

          // check if stepper is referenced
          if (sStpDrvData.sLwrActual.sStatusError.boIsRef != FALSE)
          {
            // Set request status on true
            sStepperRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            sStepperRoutineControl.boRequestAckStatus = FALSE;

            sStepperRoutineControl.eStpDID = eDD05;

            sStepperRoutineControl.eStpControl = eStpControl_Start;

            // Get position
            unPosRequest = (uint16)((uint16)p_ui8_Data[0] << DIAG_8BIT_SHIFT) + (uint16)p_ui8_Data[1];
            snPosRequest = (sint16)ErrCust_ConvertValueInt2Sint(unPosRequest, DIAG_LENGTH_STP_POS);

            sStepperRoutineControl.snPosRequest = snPosRequest;

            // Write the RTE port with request
            (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

            // Set response data
            aucResponseDD05[0] = ucRoutineControlType;
            aucResponseDD05[1] = DIAG_DD05_ID_1;
            aucResponseDD05[2] = DIAG_DD05_ID_2;
            aucResponseDD05[3] = (uint8)eRoutineFinishedOK;;

            Diag_boRoutineFinishedDD05 = TRUE;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD05, DIAG_RESP_4BYTES);
          }
          else
          {
            // Conditions not correct
            eReturnCode = CNC;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_STOP:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDD05 == TRUE)
          {
            // Set request status on true
            sStepperRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            sStepperRoutineControl.boRequestAckStatus = FALSE;
            // Stp stop
            sStepperRoutineControl.eStpControl = eStpControl_Stop;

            // Write the RTE port with request
            (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

            // Set response data
            aucResponseDD05[0] = ucRoutineControlType;
            aucResponseDD05[1] = DIAG_DD05_ID_1;
            aucResponseDD05[2] = DIAG_DD05_ID_2;
            aucResponseDD05[3] = (uint8)eRoutineStopped;
            Diag_boRoutineFinishedDD05 = FALSE;
            boRoutineStoppedOK = TRUE;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD05, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
            boRoutineStoppedOK = FALSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (boRoutineStoppedOK != FALSE)
          {
            // Set response data
            aucResponseDD05[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDD05[1] = DIAG_DD05_ID_1;
            aucResponseDD05[2] = DIAG_DD05_ID_2;
            aucResponseDD05[3] = (uint8)eRoutineStopped;
            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD05, DIAG_RESP_4BYTES);
          }
          else if (Diag_boRoutineFinishedDD05 == TRUE)
          {
            // read Diagnostic Routine Control Rte Port
            (void)Rte_Read_Stp_RoutineControl(&sStepperRoutineControl);

            // Stp rountine ongoing
            if (sStepperRoutineControl.boRequestAckStatus != FALSE)
            {
              // Set response data
              aucResponseDD05[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDD05[1] = DIAG_DD05_ID_1;
              aucResponseDD05[2] = DIAG_DD05_ID_2;
              aucResponseDD05[3] = (uint8)eRoutineInProgress;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDD05, DIAG_RESP_4BYTES);
            }
            // Stp routine stopped
            else
            {
              // Set response data
              aucResponseDD05[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDD05[1] = DIAG_DD05_ID_1;
              aucResponseDD05[2] = DIAG_DD05_ID_2;
              aucResponseDD05[3] = (uint8)eRoutineFinishedOK;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDD05, DIAG_RESP_4BYTES);
            }
          }
          else
          {
            eReturnCode = RSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      default:
        // Sub function not supported
        eReturnCode = SFNS;
        break;
      }
    }
    else
    {
      // ADL is not present, NRC 0x12 Sub Function Not Supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }

  return eReturnCode;
  //PRQA S 5330, 5336 1 // STST3 exceeded due to program architecture and readability
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DD07_SetScrollingCtrlOutput
///
/// \descr Scrolling Ctrl Output - Set Turn Indicator Scrolling Output (pwm)
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DD07_SetScrollingCtrlOutput(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  // TI Scrolling is not available yet, return service not supported
  DIAG_status eReturnCode = DIAG_NOK;

  STATIC_UT(tScrollingPresent_Stat, sScrollingSatelite_Start_Status, { FALSE });
  STATIC_UT(uint8, ucRoutineState, DIAG_CALLBACKS_ROUTINE_NA);
  STATIC_UT(tScrollingPresent_Stat, sScrollingSatelite_StatPrev, { FALSE });
  boolean boScrollingTakeOver_Status = FALSE;
  uint8 aucResponseDD07[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };
  teRte_ScrollingTgt eScrollingSatellite_Ctrl = eRte_eScrollingTgt_Off;

  // Handle coding data
  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  // Check coding validation
  if (boCodingValidity != FALSE)
  {
    boolean boIsScrlPresent = Diag_Callbacks_Check_If_Scrolling_Present();

    // Check if Scrolling is present
    if (boIsScrlPresent != FALSE)
    {
      // switch for routine type
      switch (ucRoutineControlType)
      {
      case DIAG_ROUTINE_CONTROL_TYPE_START:
        if (unLength == DIAG_RESP_1BYTE)
        {
          if (ucRoutineState != DIAG_CALLBACKS_ROUTINE_START)
          {
            // Start sequence
            ucRoutineState = DIAG_CALLBACKS_ROUTINE_START;

            (void)Rte_Read_CddSwi_ScrollingOn_Stat(&sScrollingSatelite_Start_Status);
            sScrollingSatelite_StatPrev = sScrollingSatelite_Start_Status;

            // Set Satelite global status
            if (sScrollingSatelite_Start_Status.boScrollingTIPresent_Stat == FALSE)
            {
              sScrollingSatelite_StatPrev.boScrollingTIPresent_Stat = TRUE;
              (void)Rte_Write_CddSwi_ScrollingOn_Stat(&sScrollingSatelite_StatPrev);
            }

            boScrollingTakeOver_Status = TRUE;
            (void)Rte_Write_Diag_TiScrollingTakeOver(&boScrollingTakeOver_Status);

            switch (p_ui8_Data[0])
            {
            case 1u: eScrollingSatellite_Ctrl = eRte_eScrollingTgt_On_Scrolling_Off; break;
            case 2u: eScrollingSatellite_Ctrl = eRte_eScrollingTgt_On_Scrolling_On; break;
            default: eScrollingSatellite_Ctrl = eRte_eScrollingTgt_Off; break;
            }

            (void)Rte_Write_Diag_Scrolling_TgtValue(&eScrollingSatellite_Ctrl);


            aucResponseDD07[0] = ucRoutineControlType;
            aucResponseDD07[1] = DIAG_DD07_ID_1;
            aucResponseDD07[2] = DIAG_DD07_ID_2;
            aucResponseDD07[3] = (uint8)eRoutineInProgress;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD07, DIAG_RESP_4BYTES);
          }
          else
          {
            // Start sequence error (present)
            eReturnCode = RSE;
          }
        }
        else
        {
          // Start sequence error (present)
          eReturnCode = IMLOIF;
        }

        break;
      case DIAG_ROUTINE_CONTROL_TYPE_STOP:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if ((ucRoutineState == DIAG_CALLBACKS_ROUTINE_START) || (ucRoutineState == DIAG_CALLBACKS_ROUTINE_RESULT))
          {
            // Stop sequence
            ucRoutineState = DIAG_CALLBACKS_ROUTINE_STOP;

            // Clear Satelite global status
            if (sScrollingSatelite_Start_Status.boScrollingTIPresent_Stat == FALSE)
            {
              sScrollingSatelite_StatPrev.boScrollingTIPresent_Stat = FALSE;
              (void)Rte_Write_CddSwi_ScrollingOn_Stat(&sScrollingSatelite_StatPrev);
            }

            boScrollingTakeOver_Status = FALSE;
            (void)Rte_Write_Diag_TiScrollingTakeOver(&boScrollingTakeOver_Status);

            eScrollingSatellite_Ctrl = eRte_eScrollingTgt_Off;

            (void)Rte_Write_Diag_Scrolling_TgtValue(&eScrollingSatellite_Ctrl);

            aucResponseDD07[0] = ucRoutineControlType;
            aucResponseDD07[1] = DIAG_DD07_ID_1;
            aucResponseDD07[2] = DIAG_DD07_ID_2;
            aucResponseDD07[3] = (uint8)eRoutineStopped;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD07, DIAG_RESP_4BYTES);
          }
          else
          {
            // Start sequence error (present)
            eReturnCode = RSE;
          }
        }
        else
        {
          // Start sequence error (present)
          eReturnCode = IMLOIF;
        }

        break;
      case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (ucRoutineState == DIAG_CALLBACKS_ROUTINE_NA)
          {
            //Sequence error
            eReturnCode = RSE;
          }
          else
          {
            aucResponseDD07[0] = ucRoutineControlType;
            aucResponseDD07[1] = DIAG_DD07_ID_1;
            aucResponseDD07[2] = DIAG_DD07_ID_2;
            switch (ucRoutineState)
            {
            case DIAG_CALLBACKS_ROUTINE_START:  aucResponseDD07[3] = (uint8)eRoutineInProgress; break;
            case DIAG_CALLBACKS_ROUTINE_STOP:   aucResponseDD07[3] = (uint8)eRoutineStopped; break;
            default:                            aucResponseDD07[3] = (uint8)eRoutineFinishedNOK; break;
            }

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDD07, DIAG_RESP_4BYTES);
          }
        }
        else
        {
          // Start sequence error (present)
          eReturnCode = IMLOIF;
        }
        break;
      default:
        // Sub function not supported
        eReturnCode = SFNS;
        break;
      }
    }
    else
    {
      // Scrolling is not present, NRC 0x12 Sub Function Not Supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }

  return eReturnCode;
}  //PRQA S 5316, 5330, 5336  1 // Complexity of Routine control for Ti scrolling is accepted and documented


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DF10_LvlReferencingRun
///
/// \descr Levelling stepper controls - Referencing run
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DF10_LvlReferencingRun(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  (void)p_ui8_Data;
  DIAG_status eReturnCode = DIAG_NOK;

  // Response data
  uint8 aucResponseDF10[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };

  static boolean boRoutineStoppedOK = FALSE;

  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  if (boCodingValidity != FALSE)
  {
    // Check if ADL option is present in Coding for FULL version
    if (Diag_pCodingArea->AvacStp.Modus.ucAvacStp_Enable == DIAG_OPTION_ENABLED)
    {
      switch (ucRoutineControlType)
      {
      case DIAG_ROUTINE_CONTROL_TYPE_START:

        if (unLength == DIAG_RESP_0BYTE)
        {
          // reset flag
          boRoutineStoppedOK = FALSE;

          // Set request status on true
          sStepperRoutineControl.boRequestStatus = TRUE;
          // Clear the acknowledge status
          sStepperRoutineControl.boRequestAckStatus = FALSE;

          sStepperRoutineControl.eStpDID = eDF10;

          sStepperRoutineControl.eStpControl = eStpControl_Start;

          // Write the RTE port with request
          (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

          // Set response data
          aucResponseDF10[0] = ucRoutineControlType;
          aucResponseDF10[1] = DIAG_DF10_ID_1;
          aucResponseDF10[2] = DIAG_DF10_ID_2;
          aucResponseDF10[3] = (uint8)eRoutineFinishedOK;

          Diag_boRoutineFinishedDF10 = TRUE;

          // Call diag response function
          eReturnCode = DIAG_Send_Diag_Response(aucResponseDF10, DIAG_RESP_4BYTES);
        }
        else
        {
          eReturnCode = IMLOIF;
        }

        break;
      case DIAG_ROUTINE_CONTROL_TYPE_STOP:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDF10 == TRUE)
          {
            // Set request status on true
            sStepperRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            sStepperRoutineControl.boRequestAckStatus = FALSE;
            // Stp stop
            sStepperRoutineControl.eStpControl = eStpControl_Stop;

            // Write the RTE port with request
            (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

            // Set response data
            aucResponseDF10[0] = ucRoutineControlType;
            aucResponseDF10[1] = DIAG_DF10_ID_1;
            aucResponseDF10[2] = DIAG_DF10_ID_2;
            aucResponseDF10[3] = (uint8)eRoutineStopped;
            Diag_boRoutineFinishedDF10 = FALSE;
            boRoutineStoppedOK = TRUE;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDF10, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
            boRoutineStoppedOK = FALSE;
          }
        }
        else
        {
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (boRoutineStoppedOK != FALSE)
          {
            // Set response data
            aucResponseDF10[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDF10[1] = DIAG_DF10_ID_1;
            aucResponseDF10[2] = DIAG_DF10_ID_2;
            aucResponseDF10[3] = (uint8)eRoutineStopped;
            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDF10, DIAG_RESP_4BYTES);
          }
          else if (Diag_boRoutineFinishedDF10 == TRUE)
          {
            // read Diagnostic Routine Control Rte Port
            (void)Rte_Read_Stp_RoutineControl(&sStepperRoutineControl);

            // Stp rountine ongoing
            if (sStepperRoutineControl.boRequestAckStatus != FALSE)
            {
              // Set response data
              aucResponseDF10[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDF10[1] = DIAG_DF10_ID_1;
              aucResponseDF10[2] = DIAG_DF10_ID_2;
              aucResponseDF10[3] = (uint8)eRoutineInProgress;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF10, DIAG_RESP_4BYTES);
            }
            // Stp routine stopped
            else
            {
              // Set response data
              aucResponseDF10[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDF10[1] = DIAG_DF10_ID_1;
              aucResponseDF10[2] = DIAG_DF10_ID_2;
              aucResponseDF10[3] = (uint8)eRoutineFinishedOK;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF10, DIAG_RESP_4BYTES);
            }
          }
          else
          {
            eReturnCode = RSE;
          }
        }
        else
        {
          eReturnCode = IMLOIF;
        }
        break;
      default:
        // Sub function not supported
        eReturnCode = SFNS;
        break;
      }
    }
    else
    {
      // ADL is not present, NRC 0x12 Sub Function Not Supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }

  return eReturnCode;
  //PRQA S 5330, 5336 1// STST3 exceeded due to program architecture and readability
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DF11_LvlStepperControl
///
/// \descr Levelling stepper controls of right headlamp
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DF11_LvlStepperControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  DIAG_status eReturnCode = DIAG_NOK;

  tsRte_SigPrep_VehicleConfigSig  sDataVehConfig;
  // Response data
  uint8 aucResponseDF11[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };
  // Mounting side
  teRte_MountingSide eMountingSide = { 0 };
  // STP Request status
  boolean boStpRequestStatus = TRUE;
  // Invalid length flag
  boolean boInvalidlength = FALSE;
  static boolean boRoutineStoppedOK = FALSE;

  tsRte_CddStpActual sStpDrvData = { 0 };

  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  // Read Mounting side
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  if (boCodingValidity != FALSE)
  {
    // Check if ADL option is present in Coding for FULL version
    if (Diag_pCodingArea->AvacStp.Modus.ucAvacStp_Enable == DIAG_OPTION_ENABLED)
    {
      // switch mounting side
      switch (eMountingSide)
      {
      case eMountedLeft:
        // check the request validity based on headlamp left side
        if ((p_ui8_Data[0] != (uint8)eMovementToTop) && (p_ui8_Data[0] != (uint8)eMovementToBottom) && (p_ui8_Data[0] != (uint8)eMovementToZero) && (p_ui8_Data[0] != (uint8)eSequence1) && (p_ui8_Data[0] != (uint8)eSequence2))
        {
          // Invalid data request
          boStpRequestStatus = FALSE;
        }
        break;
      case eMountedRight:
        // Invalid data request
        boStpRequestStatus = FALSE;
        break;
      default:
        // Invalid data request
        boStpRequestStatus = FALSE;
        break;
      }

      switch (ucRoutineControlType)
      {
      case DIAG_ROUTINE_CONTROL_TYPE_START:
        // reset flag
        boRoutineStoppedOK = FALSE;

        if (eMountingSide == eMountedLeft)
        {
          (void)Rte_Read_SigPrep_VehicleConfigSig(&sDataVehConfig);
          (void)Rte_Read_ppCddStpActual0_sStpActualValues(&sStpDrvData);
          // check if stepper is referenced and data request is valid
          // REQ-0543709 C , GEN-LDM-TS-MAINT-1258
          // Updated based on customer bug LDMO-4096
          if ((boStpRequestStatus != FALSE)
            && (sStpDrvData.sLwrActual.sStatusError.boIsRef != FALSE)
            && ((sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Usine)
              || (sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Client)
              || (sDataVehConfig.eVehicleCfg == eModeConfigVehicle_AfterMarket)))
          {
            // Set request status on true
            sStepperRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            sStepperRoutineControl.boRequestAckStatus = FALSE;
            // Set actuator side
            sStepperRoutineControl.eStpSide = eRightActuator; // DF11 moves only right stepper

            sStepperRoutineControl.eStpDID = eDF11;

            sStepperRoutineControl.eStpControl = eStpControl_Start;

            sStepperRoutineControl.ucStartSequence ^= 1u; // toggle start flag so we reset sequence index used in CtrlStp
            // check the request length (1 byte)
            if (unLength == DIAG_RESP_1BYTE)
            {
#if defined UNIT_TEST
              /* -------------------------------------------------- --------------------------------------------*/
              /* Special UT instrumentation to force convert the raw data into request for default case         */
              /* ---------------------------------------------------------------------------------------------- */
              Diag_Special_UT_Instrumentation_Force_InvalidCoding(p_ui8_Data);
#endif
              // check the first byte
              switch (p_ui8_Data[0])
              {
                // Convert the raw data into request
              case 0x11u: sStepperRoutineControl.eStpRequest = eMovementToTop; break;
              case 0x12u: sStepperRoutineControl.eStpRequest = eMovementToBottom; break;
              case 0x13u: sStepperRoutineControl.eStpRequest = eMovementToZero; break;
              case 0x14u: sStepperRoutineControl.eStpRequest = eSequence1; break;
              case 0x15u: sStepperRoutineControl.eStpRequest = eSequence2; break;
              default: break;
              }

              // Write the RTE port with request
              (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

              // Set response data
              aucResponseDF11[0] = ucRoutineControlType;
              aucResponseDF11[1] = DIAG_DF11_ID_1;
              aucResponseDF11[2] = DIAG_DF11_ID_2;
              aucResponseDF11[3] = (uint8)eRoutineFinishedOK;;

              Diag_boRoutineFinishedDF11 = TRUE;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF11, DIAG_RESP_4BYTES);
            }
            else
            {
              // Return invalid data length for diagnostic routine request
              eReturnCode = IMLOIF;
            }
          }
          else
          {
            // Conditions not correct
            eReturnCode = CNC;
          }
        }
        else
        {
          eReturnCode = SFNS;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_STOP:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDF11 == TRUE)
          {
            // Set request status on true
            sStepperRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            sStepperRoutineControl.boRequestAckStatus = FALSE;
            // Stp stop
            sStepperRoutineControl.eStpControl = eStpControl_Stop;

            // Write the RTE port with request
            (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

            // Set response data
            aucResponseDF11[0] = ucRoutineControlType;
            aucResponseDF11[1] = DIAG_DF11_ID_1;
            aucResponseDF11[2] = DIAG_DF11_ID_2;
            aucResponseDF11[3] = (uint8)eRoutineStopped;
            Diag_boRoutineFinishedDF11 = FALSE;
            boRoutineStoppedOK = TRUE;
            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDF11, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
            boRoutineStoppedOK = FALSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (boRoutineStoppedOK != FALSE)
          {
            // Set response data
            aucResponseDF11[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDF11[1] = DIAG_DF11_ID_1;
            aucResponseDF11[2] = DIAG_DF11_ID_2;
            aucResponseDF11[3] = (uint8)eRoutineStopped;
            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDF11, DIAG_RESP_4BYTES);
          }
          else if (Diag_boRoutineFinishedDF11 == TRUE)
          {
            // read Diagnostic Routine Control Rte Port
            (void)Rte_Read_Stp_RoutineControl(&sStepperRoutineControl);

            // Stp rountine ongoing
            if (sStepperRoutineControl.boRequestAckStatus != FALSE)
            {
              // Set response data
              aucResponseDF11[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDF11[1] = DIAG_DF11_ID_1;
              aucResponseDF11[2] = DIAG_DF11_ID_2;
              aucResponseDF11[3] = (uint8)eRoutineInProgress;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF11, DIAG_RESP_4BYTES);
            }
            // Stp routine stopped
            else
            {
              // Set response data
              aucResponseDF11[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDF11[1] = DIAG_DF11_ID_1;
              aucResponseDF11[2] = DIAG_DF11_ID_2;
              aucResponseDF11[3] = (uint8)eRoutineFinishedOK;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF11, DIAG_RESP_4BYTES);
            }
          }
          else
          {
            eReturnCode = RSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF; 
        }
        break;
      default:
        // Sub function not supported
        eReturnCode = SFNS;
        break;
      }
    }
    else
    {
      // ADL is not present, NRC 0x12 Sub Function Not Supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }

  return eReturnCode;
  //PRQA S 5330 2 // STST3 exceeded due to program architecture and readability
  //PRQA S 5316, 5324, 5336 1 // STCYC exceeded due to program architecture and readability
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DF12_LvlStepperControl
///
/// \descr Levelling stepper controls of left headlamp
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DF12_LvlStepperControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  DIAG_status eReturnCode = DIAG_NOK;

  tsRte_SigPrep_VehicleConfigSig  sDataVehConfig;
  // Response data
  uint8 aucResponseDF12[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };
  // Mounting side
  teRte_MountingSide eMountingSide = { 0 };
  // STP Request status
  boolean boStpRequestStatus = TRUE;
  // Invalid length flag
  boolean boInvalidlength = FALSE;
  static boolean boRoutineStoppedOK = FALSE;

  tsRte_CddStpActual sStpDrvData = { 0 };

  // Handle coding data
  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  // Read Mounting side
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  if (boCodingValidity != FALSE)
  {
    // Check if ADL option is present in Coding for FULL version
    if (Diag_pCodingArea->AvacStp.Modus.ucAvacStp_Enable == DIAG_OPTION_ENABLED)
    {
      // switch mounting side
      switch (eMountingSide)
      {
      case eMountedLeft:
        // check the request validity based on headlamp left side
        if ((p_ui8_Data[0] != (uint8)eMovementToTop) && (p_ui8_Data[0] != (uint8)eMovementToBottom) && (p_ui8_Data[0] != (uint8)eMovementToZero) && (p_ui8_Data[0] != (uint8)eSequence1) && (p_ui8_Data[0] != (uint8)eSequence2))
        {
          // Invalid data request
          boStpRequestStatus = FALSE;
        }
        break;
      case eMountedRight:
        // Invalid data request
        boStpRequestStatus = FALSE;
        break;
      default:
        // Invalid data request
        boStpRequestStatus = FALSE;
        break;
      }

      switch (ucRoutineControlType)
      {
      case DIAG_ROUTINE_CONTROL_TYPE_START:
        // reset flag
        boRoutineStoppedOK = FALSE;

        if (eMountingSide == eMountedLeft)
        {
          (void)Rte_Read_SigPrep_VehicleConfigSig(&sDataVehConfig);
          (void)Rte_Read_ppCddStpActual0_sStpActualValues(&sStpDrvData);
          // check if stepper is referenced and data request is valid
          // REQ-0543709 C , GEN-LDM-TS-MAINT-1258
          // Updated based on customer bug LDMO-4096
          if ((boStpRequestStatus != FALSE)
            && (sStpDrvData.sLwrActual.sStatusError.boIsRef != FALSE)
            && ((sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Usine)
              || (sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Client)
              || (sDataVehConfig.eVehicleCfg == eModeConfigVehicle_AfterMarket)))
          {
            // Set request status on true
            sStepperRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            sStepperRoutineControl.boRequestAckStatus = FALSE;
            // Set actuator side
            sStepperRoutineControl.eStpSide = eLeftActuator; // DF12 moves only left stepper

            sStepperRoutineControl.eStpDID = eDF12;

            sStepperRoutineControl.ucStartSequence ^= 1u; // toggle start flag so we reset sequence index used in CtrlStp

            sStepperRoutineControl.eStpControl = eStpControl_Start;
            // check the request length (1 byte)
            if (unLength == DIAG_RESP_1BYTE)
            {
#if defined UNIT_TEST
              /* -------------------------------------------------- --------------------------------------------*/
              /* Special UT instrumentation to force convert the raw data into request for default case         */
              /* ---------------------------------------------------------------------------------------------- */
              Diag_Special_UT_Instrumentation_Force_InvalidCoding(p_ui8_Data);
#endif

              // check the first byte
              switch (p_ui8_Data[0])
              {
                // Convert the raw data into request
              case 0x11u: sStepperRoutineControl.eStpRequest = eMovementToTop; break;
              case 0x12u: sStepperRoutineControl.eStpRequest = eMovementToBottom; break;
              case 0x13u: sStepperRoutineControl.eStpRequest = eMovementToZero; break;
              case 0x14u: sStepperRoutineControl.eStpRequest = eSequence1; break;
              case 0x15u: sStepperRoutineControl.eStpRequest = eSequence2; break;
              default: break;
              }

              // Write the RTE port with request
              (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

              // Set response data
              aucResponseDF12[0] = ucRoutineControlType;
              aucResponseDF12[1] = DIAG_DF12_ID_1;
              aucResponseDF12[2] = DIAG_DF12_ID_2;
              aucResponseDF12[3] = (uint8)eRoutineFinishedOK;
              Diag_boRoutineFinishedDF12 = TRUE;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF12, DIAG_RESP_4BYTES);
            }
            else
            {
              // Return invalid data length for diagnostic routine request
              eReturnCode = IMLOIF;
            }
          }
          else
          {
            // Conditions not correct
            eReturnCode = CNC;
          }
        }
        else
        {
          eReturnCode = SFNS;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_STOP:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDF12 == TRUE)
          {
            // Set request status on true
            sStepperRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            sStepperRoutineControl.boRequestAckStatus = FALSE;

            // Stp stop
            sStepperRoutineControl.eStpControl = eStpControl_Stop;

            // Write the RTE port with request
            (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

            // Set response data
            aucResponseDF12[0] = ucRoutineControlType;
            aucResponseDF12[1] = DIAG_DF12_ID_1;
            aucResponseDF12[2] = DIAG_DF12_ID_2;
            aucResponseDF12[3] = (uint8)eRoutineStopped;
            Diag_boRoutineFinishedDF12 = FALSE;
            boRoutineStoppedOK = TRUE;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDF12, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
            boRoutineStoppedOK = FALSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF; 
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (boRoutineStoppedOK != FALSE)
          {
            // Set response data
            aucResponseDF12[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDF12[1] = DIAG_DF12_ID_1;
            aucResponseDF12[2] = DIAG_DF12_ID_2;
            aucResponseDF12[3] = (uint8)eRoutineStopped;
            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDF12, DIAG_RESP_4BYTES);
          }
          else if (Diag_boRoutineFinishedDF12 == TRUE)
          {
            // read Diagnostic Routine Control Rte Port
            (void)Rte_Read_Stp_RoutineControl(&sStepperRoutineControl);

            // Stp rountine ongoing
            if (sStepperRoutineControl.boRequestAckStatus != FALSE)
            {
              // Set response data
              aucResponseDF12[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDF12[1] = DIAG_DF12_ID_1;
              aucResponseDF12[2] = DIAG_DF12_ID_2;
              aucResponseDF12[3] = (uint8)eRoutineInProgress;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF12, DIAG_RESP_4BYTES);
            }
            // Stp routine stopped
            else
            {
              // Set response data
              aucResponseDF12[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDF12[1] = DIAG_DF12_ID_1;
              aucResponseDF12[2] = DIAG_DF12_ID_2;
              aucResponseDF12[3] = (uint8)eRoutineFinishedOK;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF12, DIAG_RESP_4BYTES);
            }
          }
          else
          {
            eReturnCode = RSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      default:
        // Sub function not supported
        eReturnCode = SFNS;
        break;
      }
    }
    else
    {
      // ADL is not present, NRC 0x12 Sub Function Not Supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }
 

  return eReturnCode;
  //PRQA S 5310 3 // STPTH exceeded due to program architecture and readability
  //PRQA S 5330 2 // STST3 exceeded due to program architecture and readability
  //PRQA S 5316, 5324, 5336 1 // STCYC exceeded due to program architecture and readability
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DF13_LvlStepperControl
///
/// \descr Levelling stepper controls of left and right headlamps
///
/// \param  ucRoutineControlType - Routin Control Type
/// \param  unLength - Routine length
/// \param  p_ui8_Data - Data in
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DF13_LvlStepperControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data)
{
  DIAG_status eReturnCode = DIAG_NOK;

  tsRte_SigPrep_VehicleConfigSig  sDataVehConfig;
  // Response data
  uint8 aucResponseDF13[DIAG_BUFFER_4BYTES] = { 0u, 0u, 0u, 0u };
  // Mounting side
  teRte_MountingSide eMountingSide = { 0 };
  // STP Request status
  boolean boStpRequestStatus = TRUE;
  // Invalid length flag
  boolean boInvalidlength = FALSE;
  static boolean boRoutineStoppedOK = FALSE;

  tsRte_CddStpActual sStpDrvData = { 0 };

  // Handle coding data
  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  // Read Mounting side
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);
  
  if (boCodingValidity != FALSE)
  {
    // Check if ADL option is present in Coding for FULL version
    if (Diag_pCodingArea->AvacStp.Modus.ucAvacStp_Enable == DIAG_OPTION_ENABLED)
    {
      // switch mounting side
      switch (eMountingSide)
      {
      case eMountedLeft:
        // check the request validity based on headlamp left side
        if ((p_ui8_Data[0] != (uint8)eMovementToTop) && (p_ui8_Data[0] != (uint8)eMovementToBottom) && (p_ui8_Data[0] != (uint8)eMovementToZero) && (p_ui8_Data[0] != (uint8)eSequence1) && (p_ui8_Data[0] != (uint8)eSequence2))
        {
          // Invalid data request
          boStpRequestStatus = FALSE;
        }
        break;
      case eMountedRight:
        // Invalid data request
        boStpRequestStatus = FALSE;
        break;
      default:
        // Invalid data request
        boStpRequestStatus = FALSE;
        break;
      }

      switch (ucRoutineControlType)
      {
      case DIAG_ROUTINE_CONTROL_TYPE_START:
        // reset flag
        boRoutineStoppedOK = FALSE;

        if (eMountingSide == eMountedLeft)
        {
          (void)Rte_Read_SigPrep_VehicleConfigSig(&sDataVehConfig);
          (void)Rte_Read_ppCddStpActual0_sStpActualValues(&sStpDrvData);
          // check if stepper is referenced and data request is valid
          // REQ-0543709 C , GEN-LDM-TS-MAINT-1258
          // Updated based on customer bug LDMO-4096
          if ((boStpRequestStatus != FALSE)
            && (sStpDrvData.sLwrActual.sStatusError.boIsRef != FALSE)
            && ((sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Usine)
              || (sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Client)
              || (sDataVehConfig.eVehicleCfg == eModeConfigVehicle_AfterMarket)))
          {
            // Set request status on true
            sStepperRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            sStepperRoutineControl.boRequestAckStatus = FALSE;
            // Set actuator side
            sStepperRoutineControl.eStpSide = eBothActuators; // DF13 moves both steppers

            sStepperRoutineControl.eStpDID = eDF13;

            sStepperRoutineControl.ucStartSequence ^= 1u; // toggle start flag so we reset sequence index used in CtrlStp

            sStepperRoutineControl.eStpControl = eStpControl_Start;
            // check the request length (1 byte)
            if (unLength == DIAG_RESP_1BYTE)
            {
#if defined UNIT_TEST
              /* -------------------------------------------------- --------------------------------------------*/
              /* Special UT instrumentation to force convert the raw data into request for default case         */
              /* ---------------------------------------------------------------------------------------------- */
              Diag_Special_UT_Instrumentation_Force_InvalidCoding(p_ui8_Data);
#endif

              // check the first byte
              switch (p_ui8_Data[0])
              {
                // Convert the raw data into request
              case 0x11u: sStepperRoutineControl.eStpRequest = eMovementToTop; break;
              case 0x12u: sStepperRoutineControl.eStpRequest = eMovementToBottom; break;
              case 0x13u: sStepperRoutineControl.eStpRequest = eMovementToZero; break;
              case 0x14u: sStepperRoutineControl.eStpRequest = eSequence1; break;
              case 0x15u: sStepperRoutineControl.eStpRequest = eSequence2; break;
              default: break;
              }

              // Write the RTE port with request
              (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

              // Set response data
              aucResponseDF13[0] = ucRoutineControlType;
              aucResponseDF13[1] = DIAG_DF13_ID_1;
              aucResponseDF13[2] = DIAG_DF13_ID_2;
              aucResponseDF13[3] = (uint8)eRoutineFinishedOK;
              Diag_boRoutineFinishedDF13 = TRUE;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF13, DIAG_RESP_4BYTES);
            }
            else
            {
              // Return invalid data length for diagnostic routine request
              eReturnCode = IMLOIF;
            }
          }
          else
          {
            // Conditions not correct
            eReturnCode = CNC;
          }
        }
        else
        {
          eReturnCode = SFNS;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_STOP:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (Diag_boRoutineFinishedDF13 == TRUE)
          {
            // Set request status on true
            sStepperRoutineControl.boRequestStatus = TRUE;
            // Clear the acknowledge status
            sStepperRoutineControl.boRequestAckStatus = FALSE;

            // Stp stop
            sStepperRoutineControl.eStpControl = eStpControl_Stop;

            // Write the RTE port with request
            (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);

            // Set response data
            aucResponseDF13[0] = ucRoutineControlType;
            aucResponseDF13[1] = DIAG_DF13_ID_1;
            aucResponseDF13[2] = DIAG_DF13_ID_2;
            aucResponseDF13[3] = (uint8)eRoutineStopped;
            Diag_boRoutineFinishedDF13 = FALSE;
            boRoutineStoppedOK = TRUE;

            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDF13, DIAG_RESP_4BYTES);
          }
          else
          {
            eReturnCode = RSE;
            boRoutineStoppedOK = FALSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
        if (unLength == DIAG_RESP_0BYTE)
        {
          if (boRoutineStoppedOK != FALSE)
          {
            // Set response data
            aucResponseDF13[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
            aucResponseDF13[1] = DIAG_DF13_ID_1;
            aucResponseDF13[2] = DIAG_DF13_ID_2;
            aucResponseDF13[3] = (uint8)eRoutineStopped;
            // Call diag response function
            eReturnCode = DIAG_Send_Diag_Response(aucResponseDF13, DIAG_RESP_4BYTES);
          }
          else if (Diag_boRoutineFinishedDF13 == TRUE)
          {
            // read Diagnostic Routine Control Rte Port
            (void)Rte_Read_Stp_RoutineControl(&sStepperRoutineControl);

            // Stp rountine ongoing
            if (sStepperRoutineControl.boRequestAckStatus != FALSE)
            {
              // Set response data
              aucResponseDF13[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDF13[1] = DIAG_DF13_ID_1;
              aucResponseDF13[2] = DIAG_DF13_ID_2;
              aucResponseDF13[3] = (uint8)eRoutineInProgress;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF13, DIAG_RESP_4BYTES);
            }
            // Stp routine stopped
            else
            {
              // Set response data
              aucResponseDF13[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              aucResponseDF13[1] = DIAG_DF13_ID_1;
              aucResponseDF13[2] = DIAG_DF13_ID_2;
              aucResponseDF13[3] = (uint8)eRoutineFinishedOK;

              // Call diag response function
              eReturnCode = DIAG_Send_Diag_Response(aucResponseDF13, DIAG_RESP_4BYTES);
            }
          }
          else
          {
            eReturnCode = RSE;
          }
        }
        else
        {
          // Return invalid data length for diagnostic routine request
          eReturnCode = IMLOIF;
        }
        break;
      default:
        // Sub function not supported
        eReturnCode = SFNS;
        break;
      }
    }
    else
    {
      // ADL is not present, NRC 0x12 Sub Function Not Supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }

  return eReturnCode;
  //PRQA S 5310 3 // STPTH exceeded due to program architecture and readability
  //PRQA S 5330 2 // STST3 exceeded due to program architecture and readability
  //PRQA S 5316, 5324, 5336 1 // STCYC exceeded due to program architecture and readability
}
#endif

//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_DFB5_InitAutomativLeveling
///
/// \descr  Routine Control for initialization of automatic levelling
///
/// \param  -ucResData
///         -ucDataLen
///         -ucRoutineControlType
///         -unLength
///         -puc_Data
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_DFB5_InitAutomativLeveling(uint8* ucResData, uint8 ucDataLen, uint8 ucRoutineControlType, uint16 unLength, UINT8 const* puc_Data)
{
  DIAG_status eReturnCode = DIAG_NOK;
  sint32 slDeltaPwm0, slDeltaPwm1;
  uint16 aunSensPwmRes[CFG_CntSens];
  (void)puc_Data;
  // Mounting side
  teRte_MountingSide eMountingSide = { 0 };

  // Read Mounting side
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  tsRte_SigPrep_VehicleConfigSig  sDataVehConfig;
  tsRte_SensorRaw                 aunSensRawPwm;

  // Handle coding data
  CONST_AL boolean boCodingValidity = Diag_CodingDataValidation();

  // Check coding validation
  if (boCodingValidity != FALSE)
  {
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
    // Check if ADL option is present in Coding for FULL version
    if (Diag_pCodingArea->AvacStp.Modus.ucAvacStp_Enable == DIAG_OPTION_ENABLED)
#else 
    // Check if ASL option is present in Coding for ECO version
    if (Diag_pCodingArea->AvacStp.DCMotorData.ucAsl_Enable == DIAG_OPTION_ENABLED)
#endif
    {
        switch (ucRoutineControlType)
        {
        case DIAG_ROUTINE_CONTROL_TYPE_START:
          if (unLength == DIAG_RESP_0BYTE)
          {
            if (eMountingSide == eMountedLeft)
            {
              Diag_ucPwmSensError = 0u;
              Diag_ucErrorCnt = 0u;

              ucResData[0] = DIAG_ROUTINE_CONTROL_TYPE_START;
              ucResData[1] = DIAG_DFB5_ID_1;
              ucResData[2] = DIAG_DFB5_ID_2;

              (void)Rte_Read_SigPrep_VehicleConfigSig(&sDataVehConfig);
              (void)Rte_Read_IoHwAb_GetSens_Raw(&aunSensRawPwm);

              for (uint8 ucIx = 0u; ucIx < CFG_CntSens; ucIx++)
              {
                aunSensPwmRes[ucIx] = aunSensRawPwm.aucSensRaw[ucIx];
              }

              // REQ-0543703 C; GEN-LDM-TS-MAINT-1253
              // Updated based on customer bug LDMO-3355
              if ((sDataVehConfig.eSigQty == SIG_VALID)
                && ((sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Usine)
                  || (sDataVehConfig.eVehicleCfg == eModeConfigVehicle_Client)
                  || (sDataVehConfig.eVehicleCfg == eModeConfigVehicle_AfterMarket)))
              {

                tsRte_SigPrep_VehiclePitchAngle sDataVehPitchAngle = { 0 };
                tPitch0 sPitchAngle = { 0 };
                tsPositionOut  sAvacPosOut = { 0 };
#if defined(SAMPLE_ECO)
                tPositionOut sPositionOutMsg;

                //receive bb messages
                (void)Rte_Read_ppsAvacStat1Out_Port(&sPositionOutMsg);
#endif
                (void)Rte_Read_SigPrep_VehiclePitchAngle(&sDataVehPitchAngle);
                (void)Rte_Read_Pitch_Angle(&sPitchAngle);
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
                (void)Rte_Read_ppsAvacOut(&sAvacPosOut);
                if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN) // check if CAN configuration for frame 350 is valid
                {
                  if (sDataVehPitchAngle.eSigQty == SIG_VALID)
                  {
                    NvmBlockDeltaPwmPara.snVehicleAttitude = sDataVehPitchAngle.eAssietteVehicule.nVehiclePitchAngle; // write vehicle attitude
                    NvmBlockDeltaPwmPara.eZeroLevProgInput = eInput_CAN;
                    NvmBlockDeltaPwmPara.ucZeroLevProg |= 0xFFu;
                    (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara); // NvM_Write cannot fail (according to Michael Ordnung)
                  }
                  else
                  {
                    Diag_ucErrorCnt++;
                  }
                }
                else if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_HLS) // check if BHS sensors are connected/valid
                {
#endif
                  if ((aunSensPwmRes[0] == 0u) || (aunSensPwmRes[0] == 0XFFFFu))
                  {
                    //check error on 1st sensor
                    Diag_ucErrorCnt++;

                    if (aunSensPwmRes[0] == 0u)
                    {
                      //rear sensor too low
                      Diag_ucPwmSensError = (uint8)eFbhsTooLow;
                    }
                    if (aunSensPwmRes[0] == 0xFFFFu)
                    {
                      // rear sensor too high
                      Diag_ucPwmSensError = (uint8)eFbhsTooHigh;
                    }
                  }
                  else if ((aunSensPwmRes[1] == 0u) || (aunSensPwmRes[1] == 0XFFFFu))
                  {
                    //check error on 2nd sensor
                    Diag_ucErrorCnt++;

                    //check error on 1st sensor
                    if (aunSensPwmRes[1] == 0u)
                    {
                      //front sensor too low
                      Diag_ucPwmSensError = (uint8)eRbhsTooLow;
                    }
                    if (aunSensPwmRes[1] == 0xFFFFu)
                    {
                      // front sensor too high
                      Diag_ucPwmSensError = (uint8)eRbhsTooHigh;
                    }
                  }
                  else
                  {
                    slDeltaPwm0 = (DIAG_PWM_BALANCING_ANGLE - (sint32)aunSensPwmRes[0]);
                    slDeltaPwm1 = (DIAG_PWM_BALANCING_ANGLE - (sint32)aunSensPwmRes[1]);

                    if (slDeltaPwm0 >= 0)
                    {
                      NvmBlockDeltaPwmPara.slDeltaPwm_0 = slDeltaPwm0;
                      NvmBlockDeltaPwmPara.unSensOffset_0 = aunSensPwmRes[0];
                      NvmBlockDeltaPwmPara.ucZeroLevProg |= 0x0Fu;
                      // prod 00028157 ALTIS 9111438 BEMP responds a NRC78... 
                      //(void)_UaCustApp_NvMWriteWrapper(NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);		// save value of sDeltaPwm to NV memory
                    }
                    else
                    {
                      slDeltaPwm0 = (DIAG_ADJ_ANGLE_DEGREE + slDeltaPwm0); // 80 degree = 52428
                      NvmBlockDeltaPwmPara.slDeltaPwm_0 = slDeltaPwm0;
                      NvmBlockDeltaPwmPara.unSensOffset_0 = aunSensPwmRes[0];
                      NvmBlockDeltaPwmPara.ucZeroLevProg |= 0x0Fu;
                      // prod00028157	ALTIS 9111438 BEMP responds a NRC78...
                      //(void)_UaCustApp_NvMWriteWrapper(NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);   // save value of sDeltaPwm to NV memory
                    }

                    if (slDeltaPwm1 >= 0)
                    {
                      NvmBlockDeltaPwmPara.slDeltaPwm_1 = slDeltaPwm1;
                      NvmBlockDeltaPwmPara.unSensOffset_1 = aunSensPwmRes[1];
                      NvmBlockDeltaPwmPara.ucZeroLevProg |= (uint8)(0xF0);
                      // prod00028157	ALTIS 9111438 BEMP responds a NRC78...
                      //(void)_UaCustApp_NvMWriteWrapper(NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);   // save value of sDeltaPwm to NV memory
                    }
                    else
                    {
                      slDeltaPwm1 = (DIAG_ADJ_ANGLE_DEGREE + slDeltaPwm1); // 80 degree = 52428
                      NvmBlockDeltaPwmPara.slDeltaPwm_1 = slDeltaPwm1;
                      NvmBlockDeltaPwmPara.unSensOffset_1 = aunSensPwmRes[1];
                      NvmBlockDeltaPwmPara.ucZeroLevProg |= (uint8)(0xF0);
                      // prod00028157	ALTIS 9111438 BEMP responds a NRC78...
                      //(void)_UaCustApp_NvMWriteWrapper(NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);   // save value of sDeltaPwm to NV memory
                    }
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
                    NvmBlockDeltaPwmPara.snVehicleAttitude = sAvacPosOut.Position[0].Ver; // write calculated vehicle attitude
#else
                    NvmBlockDeltaPwmPara.snVehicleAttitude = sPositionOutMsg.Position[0].Ver; // write calculated vehicle attitude
#endif
                    NvmBlockDeltaPwmPara.eZeroLevProgInput = eInput_HLS;

                    (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara); // NvM_Write cannot fail (according to Michael Ordnung)
                  }
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
                }
                else
                {
                  Diag_ucErrorCnt++;
                }
#endif
                if (Diag_ucErrorCnt == 0u)  // error not present on any of the sensor
                {

                  ucResData[3] = (uint8)eRoutineFinishedOK;
                  ucDataLen = 4u;

                }
                else
                {
                  ucResData[3] = (uint8)eRoutineFinishedNOK;
                  ucResData[4] = Diag_ucPwmSensError;
                  ucDataLen = 5u;

                }

                Diag_boRoutineFinishedDFB5 = TRUE;
                eReturnCode = DIAG_Send_Diag_Response(ucResData, ucDataLen);
              }
              else
              {
                eReturnCode = CNC;
              }
            }
            else
            {
              eReturnCode = SFNS;
            }

          }
          else
          {
            eReturnCode = IMLOIF;
          }
          break;
        case DIAG_ROUTINE_CONTROL_TYPE_STOP:
          if (unLength == DIAG_RESP_0BYTE)
          {
            if (Diag_boRoutineFinishedDFB5 == FALSE)
            {
              eReturnCode = RSE;
            }
            else
            {
              ucResData[0] = DIAG_ROUTINE_CONTROL_TYPE_STOP;
              ucResData[1] = DIAG_DFB5_ID_1;
              ucResData[2] = DIAG_DFB5_ID_2;
              ucResData[3] = (uint8)eRoutineStopped;
              ucDataLen = 4u;
              Diag_boRoutineFinishedDFB5 = FALSE;
              eReturnCode = DIAG_Send_Diag_Response(ucResData, ucDataLen);
            }
          }
          else
          {
            eReturnCode = IMLOIF;
          }
          break;
        case DIAG_ROUTINE_CONTROL_TYPE_RESULTS:
          if (unLength == DIAG_RESP_0BYTE)
          {
            if (Diag_boRoutineFinishedDFB5 == TRUE)
            {
              ucResData[0] = DIAG_ROUTINE_CONTROL_TYPE_RESULTS;
              ucResData[1] = DIAG_DFB5_ID_1;
              ucResData[2] = DIAG_DFB5_ID_2;
              if (Diag_ucErrorCnt == 0u)  // error not present on any of the sensor
              {

                ucResData[3] = (uint8)eRoutineFinishedOK;  //   routine in progress
                ucDataLen = 4u;  // no of response byte
              }
              else
              {
                ucResData[3] = (uint8)eRoutineFinishedNOK;
                ucResData[4] = Diag_ucPwmSensError;
                ucDataLen = 5u;
              }

              eReturnCode = DIAG_Send_Diag_Response(ucResData, ucDataLen);
            }
            else
            {
              eReturnCode = RSE;
            }
          }
          else
          {
            eReturnCode = IMLOIF;
          }
          break;
        default:
          // Sub function not supported
          eReturnCode = SFNS;
          break;
        }
    }
    else
    {
      // ASL is not present, NRC 0x12 Sub Function Not Supported
      eReturnCode = SFNS;
    }
  }
  else
  {
    // Coding is invalid, NRC 0x22 Conditions Not Correct 
    eReturnCode = CNC;
  }
  /* User service processing finished. */

  return eReturnCode;
  //PRQA S 5310, 5316, 5324, 5330, 5336 1 // exceeded due to reuse of existing code
}


//-----------------------------------------------------------------------------
/// \brief APPLI_ReadDTCInformation
///
/// \descr  LGM callback for diagnostic subservices for Read DTC Information
///
/// \param  -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_ReadDTCInformation(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_OK;

  switch (p_ui8_Data[0u])
  {
  case DIAG_01_READ_NR_OF_DTC_BY_MASK:
    // Diagnostic Subservice 0x19 0x01
    eReturnCode = Diag_Callbacks_Read_Number_of_DTC_By_StatusMaskFaultMemory(p_ui8_Data, Length);
    break;

  case DIAG_02_READ_DTC_BY_MASK:
    // Diagnostic Subservice 0x19 0x02
    eReturnCode = Diag_Callbacks_Read_by_MaskFaultMemory(p_ui8_Data, Length);
    break;

  case DIAG_04_READ_DTC_SNAPSHOT_DATA:
    // Diagnostic Subservice 0x19 0x04
    eReturnCode = Diag_Callbacks_Read_DTC_Snapshot_Data_by_DTC_NumberFaultMemory(p_ui8_Data, Length);
    break;

  default:
    // Negative response code - 0x12 Subfunction not suported
    eReturnCode = SFNS;
    break;
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief APPLI_ECUReset
///
/// \descr  LGM callback for diagnostic subservices for ECU Reset
///
/// \param  -ui8_ResetType:
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_ECUReset(UINT8 ui8_ResetType)
{
  DIAG_status eReturnCode = DIAG_OK;
  UINT8 ucActiveSession = 0u;
  // Request of low beam
  teRte_ReqLightState     eLowBeamReq = ReqLighted_Off;

  uint8  ucResData[DIAG_BUFFER_1BYTE];
  uint8  ucDataLen = DIAG_RESP_1BYTE;

  // Read RTE Low Beam Request
  (void)Rte_Read_SysMon_LowBeamCmd_Req(&eLowBeamReq);

  // FctR_RteAccess_Read_LgtFctStatus(FctR_LgtFctStatus);
  ucActiveSession = DIAG_GetActiveSession();

  if (Diag_PowertrainCheck() == TRUE)
  {
    // Negative response code - 0x22 Condition not correct
    eReturnCode = CNC;
  }
  else if (eLowBeamReq == ReqLighted_On)
  {
    // Negative response code - 0x22 Condition not correct
    eReturnCode = CNC;
  }
  else if (ucActiveSession != DIAG_03_EXTENDED_SESSION)
  {
    eReturnCode = SNSIAS;
  }
  else
  {
    switch (ui8_ResetType)
    {
    case 0x03U:
    {
      boolean boReset = TRUE;
      ucResData[0] = 0x03u;

      //Positive response 51 03
      eReturnCode = DIAG_Send_Diag_Response(ucResData, ucDataLen);

      //set the reset flag
      //EcuM_DiagResetRequest();
      (void)Rte_Write_Diag_DiagResetRequest(&boReset);
    }
    break;
    case 0x02U:
    {
      uint8 ucReq;
      ucResData[0] = 0x02u;
      //Positive response 51 02
      eReturnCode = DIAG_Send_Diag_Response(ucResData, ucDataLen);

      //EcuM_ReleaseRUN(DIAG_01_EcuMUser);
      ucReq = DIAG_01_EcuMUser;
      (void)Rte_Write_ElecInt_ReleaseRUN(&ucReq);

      //EcuM_RequestPOST_RUN(DIAG_02_EcuMUser);
      ucReq = DIAG_02_EcuMUser;
      (void)Rte_Write_Diag_RequestPOST_RUN(&ucReq);
    }
    break;
    default:
    {
      // Negative response code - 0x12 SubFunction Not Supported
      eReturnCode = SFNS;
    }
    break;
    }
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief APPLI_DiagnosticSessionControl
///
/// \descr  LGM callback for diagnostic subservices for Diagnostic Session Control
///
/// \param  -ui8_Session:
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_DiagnosticSessionControl(UINT8 ui8_Session)
{
  DIAG_status eReturnCode = DIAG_NOK;
  tsRte_SysMon_VehNetState sData432;

  switch (ui8_Session)
  {
  case DIAG_01_DEFAULT_SESSION:
    Diag_Callbacks_RoutineControl_CheckStartStop();
    if (Diag_boControlDTCOff_Stat != FALSE)
    {
      Rte_Call_Diag_ControlDTCSetting(TRUE, (void)ulDTC);
      Diag_boControlDTCOff_Stat = FALSE;
    }
    eReturnCode = DIAG_OK;
    break;

  case DIAG_02_PROGRAMMING_SESSION:
    (void)Rte_Read_SysMon_VehNetState(&sData432);
    if (sData432.eVESMainState == VESState_Start)
    {
      // Negative response code - 0x83 engine is running
      eReturnCode = EIR;
    }
    else
    {
      if (Diag_IntegrationMode() != TRUE)
      {
        // Negative response code - 0x12 conditions not correct
        eReturnCode = RCRRP;
        DiagControl_ProgrammingSesion_Request();
      }
      else
      {
        Diag_Callbacks_ProgramingSessionAccepted();
      }
    }
    break;

  case DIAG_03_EXTENDED_SESSION:
    Diag_Callbacks_RoutineControl_CheckStartStop();
    eReturnCode = DIAG_OK;
    break;

  case DIAG_50_SUPPLIER_SESSION:
    eReturnCode = DIAG_OK;
    break;

  case DIAG_60_AL_SESSION:
    eReturnCode = DIAG_OK;
    break;

  default:
    // Negative response code - 0x12 Sub function not supported
    eReturnCode = SFNS;
    break;
  }
  return eReturnCode;
  //PRQA S 5310, 5316, 5324, 5330 1 // exceeded due to reuse of existing code
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_RoutineControl_CheckStartStop
///
/// \descr  Check if the RoutineControl has already been started,
///         if yes, request stop routine; if no, request start routine
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Diag_Callbacks_RoutineControl_CheckStartStop(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)

#if 0 // [2025/04/22 SARGHE, Vlad] Removed DF17 because it is no longer requested
  if (Diag_boRoutineFinishedDF17 == TRUE)
  {
    // Afs stop
    sAfsRoutineControl.eAfsControl = eAfsControl_Stop;
    Diag_boRoutineFinishedDF17 = FALSE;

    // Write the RTE port with request
    (void)Rte_Write_Diag_RoutineControl(&sAfsRoutineControl);
  }
  else
  {
    //do ntohing
  }
#endif

  if (Diag_boRoutineFinishedDD01 == TRUE)
  {
    Diag_boRoutineFinishedDD01 = FALSE;
    Diag_boDD01_Status = FALSE;

    (void)Rte_Write_Diag_DD01_Activation(&Diag_boDD01_Status);

    for (uint8_fast ucIx = 0u; ucIx < CFG_LOGICAL_UNITS; ucIx++)
    {
      Diag_boDD01_PixelActivation.ucPixelIntensity[ucIx] = 0;
    }

    (void)Rte_Write_Diag_DD01_PixelActivation(&Diag_boDD01_PixelActivation);
  }
  else
  {
    //do nothing
  }
  if ((Diag_boRoutineFinishedDF11 == TRUE) || (Diag_boRoutineFinishedDF12 == TRUE) || (Diag_boRoutineFinishedDF13 == TRUE) || (Diag_boRoutineFinishedDD05 == TRUE) || (Diag_boRoutineFinishedDF10 == TRUE))
  {
    Diag_boRoutineFinishedDF11 = FALSE;
    Diag_boRoutineFinishedDF12 = FALSE;
    Diag_boRoutineFinishedDF13 = FALSE;
    Diag_boRoutineFinishedDD05 = FALSE;
    Diag_boRoutineFinishedDF10 = FALSE;
    // Set request status on true
    sStepperRoutineControl.boRequestStatus = TRUE;
    // Clear the acknowledge status
    sStepperRoutineControl.boRequestAckStatus = FALSE;
    // Stp stop
    sStepperRoutineControl.eStpControl = eStpControl_Stop;
    // Write the RTE port with request
    (void)Rte_Write_Stp_RoutineControl(&sStepperRoutineControl);
  }
  else
  {
    //do nothing
  }

  if (Diag_boRoutineFinishedDD04 == TRUE)
  {
    Diag_boRoutineFinishedDD04 = FALSE;
    // FAN2 deactivation
    roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(DIAG_FAN2);
  }
  else
  {
    //do nothing
  }
#else
  if (Diag_boRoutineFinishedDD06 == TRUE)
  {
    Diag_boRoutineFinishedDD06 = FALSE;

    // Set request status on true
    Diag_sDcMotorRoutineControl.boRequestStatus = TRUE;
    // Clear the acknowledge status
    Diag_sDcMotorRoutineControl.boRequestAckStatus = FALSE;
    // Stp stop
    Diag_sDcMotorRoutineControl.eDcmControl = eDcmControl_Stop;
    // Write the RTE port with request
    (void)Rte_Write_Dcm_RoutineControl(&Diag_sDcMotorRoutineControl);
  }
  else
  {
    //do nothing
  }
#endif
  if (Diag_boRoutineFinishedDD00 == TRUE)
  {
    Diag_boRoutineFinishedDD00 = FALSE;
    Diag_sLd_ActivationRoutineControl.boRequestStatus = FALSE;
    //reset all bits
    Diag_sLd_ActivationRoutineControl.uTgtLgtFct.ulRaw = 0x0U;
    (void)Rte_Write_Diag_LdActivationRoutineControl(&Diag_sLd_ActivationRoutineControl);
  }
  else
  {
    //do nothing
  }
  if (Diag_boRoutineFinishedDFB5 == TRUE)
  {
    Diag_boRoutineFinishedDFB5 = FALSE;
  }
  else
  {
    //do nothing
  }
  if (Diag_boRoutineFinishedDD03 == TRUE)
  {
    Diag_boRoutineFinishedDD03 = FALSE;
    // FAN1 deactivation
    roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(DIAG_FAN1);
  }
  else
  {
    //do nothing
  }
  //PRQA S 5310 1 // exceeded due to reuse of existing code
}


//-----------------------------------------------------------------------------
/// \brief APPLI_ClearDiagnosticInformation
///
/// \descr  LGM callback for diagnostic service for Clear Diagnostic Information
///
/// \param  -ui32_Group:
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_ClearDiagnosticInformation(UINT32 ui32_Group)
{
  DIAG_status eReturnCode = DIAG_NOK;
  // Local variable which shows if recevied parameter via CAN is supported or not
  boolean boDtcNotSupported;
  // Variable used for storing the diagnostic response data
  uint8  aucReqData[DIAG_BUFFER_3BYTES];
  uint8  ucResData = 0u;
  uint8  ucDataLen = 0u;
  boolean boClearDtcProcessStat = FALSE;

  // Speed info
  tsRte_SysMon_VehicleSpeed sDataSpeedMsg;
  // Life Phase
  tsRte_SysMon_LifePhases  sLifePhases;

  // Read RTE ports
  (void)Rte_Read_SysMon_VehicleSpeed(&sDataSpeedMsg);
  (void)Rte_Read_SysMon_LifePhases(&sLifePhases);

  // Speed available and Speed <= 5kph or Speed available but invalid (speed == 0xFFFF)
  // Life phase normal
  if ((((sDataSpeedMsg.eSigQty == SIG_VALID) && (sDataSpeedMsg.eVehicleSpeed.unVehicleSpeed <= DIAG_VEHICLE_MOVING)) ||
    ((sDataSpeedMsg.eSigQty == SIG_INVALID) && (sDataSpeedMsg.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoAvailable))) &&
    (sLifePhases.eSigQty == SIG_VALID) && (sLifePhases.ePhaseVie == eNormalMode))
  {
    // Process clear dtc
    boClearDtcProcessStat = TRUE;
  }
  else
  {
    // keep boClearDtcProcessStat = FALSE;
  }

  // Clear DTC process
  if (boClearDtcProcessStat != FALSE)
  {
    // Clear dtc code mounting
    aucReqData[0] = (uint8)ui32_Group;
    aucReqData[1] = (uint8)(ui32_Group >> 8u);
    aucReqData[2] = (uint8)(ui32_Group >> 16u);


    // Clear the memory according with received dtc code
    boDtcNotSupported = ErrCust_ClearMemory((uint8*)(&aucReqData[0]));

    if (boDtcNotSupported != FALSE)
    {
      // Return request out of range
      eReturnCode = ROOR;
    }
    else
    {
      // Set ClrDtc for DEH entries clear and DEH defect frame emission stop
      DAPI_ClearDTCInfo();
      Deh_ClearAndInitDehLogTab();

      // Diagnostic return
      eReturnCode = DIAG_Send_Diag_Response(&ucResData, ucDataLen);
    }
  }
  else
  {
    // Negative response code - 0x22 Condition not correct
    eReturnCode = CNC;
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief APPLI_ControlDTCSetting
///
/// \descr  LGM callback for diagnostic subservices for Read Data by Identifier
///
/// \param  -ui8_Type : 
///         -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_ControlDTCSetting(UINT8 ui8_Type, UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Local variable which keeps the Dtc index
  uint8 ucErrIx;

  // Local variable which show if both DTC and DTCSnapshotRecordNumber have valid values
  boolean boValidParams = FALSE;

  if (Diag_PowertrainCheck() == TRUE)
  {
    // Negative response code - 0x2 Conditions not correct
    eReturnCode = CNC;
  }
  else
  {
    // Take the Dtc code from request
// PRQA S 4397 1 //An expression which is the result of a ~ or << operation has not been cast to its essential type -> it is intended and the behavior is as expected
    uint32 ulDTC = UTIL_MAKELONG(UTIL_MAKEWORD(p_ui8_Data[2], p_ui8_Data[1]), UTIL_MAKEWORD(p_ui8_Data[0], 0x00));

    if (ulDTC == 0xFFFFFFu)
    {
      // Marked that the parameters are valid
      boValidParams = TRUE;
    }
    else
    {
      // Find the given DTC
      for (ucErrIx = 0u; ucErrIx < ERRCUST_NUMBER_OF_DTCS; ucErrIx++)
      {
        if (ErrCust_ulGetDtcCode(ucErrIx) == ulDTC)
        {
          // Marked that the parameters are valid
          boValidParams = TRUE;
          break;
        }
      }
    }
    if (Length != DIAG_RESP_3BYTES)
    {
      // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
      eReturnCode = IMLOIF;
    }
    else if (boValidParams == FALSE)
    {
      // Params are invalid
      eReturnCode = ROOR;
    }
    else
    {
      switch (ui8_Type)
      {
      case DIAG_01_CONTROL_DTC_SETTING_ON:
        eReturnCode = Diag_Callbacks_01_CONTROL_DTC_ON(ui8_Type, p_ui8_Data, Length);
        break;

      case DIAG_01_CONTROL_DTC_SETTING_OFF:
        eReturnCode = Diag_Callbacks_02_CONTROL_DTC_OFF(ui8_Type, p_ui8_Data, Length);
        break;

      default:
        // Negative response code - 0x12 Subfunction not suported
        eReturnCode = SFNS;
        break;
      }
    }
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_01_CONTROL_DTC_ON
///
/// \descr  Diagnostic subservice that restart recording of local errors
///
/// \param  UINT8
///         UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_01_CONTROL_DTC_ON(UINT8 ui8_Type, UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  (void)p_ui8_Data;
  (void)Length;
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;
  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_1BYTE] = { 0u };

  // dtc control on
  Diag_boControlDTCOff_Stat = FALSE;

  aucResData[0] = ui8_Type;
  Rte_Call_Diag_ControlDTCSetting(TRUE, ulDTC);
  ucDataLength = DIAG_RESP_1BYTE;
  eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_02_CONTROL_DTC_OFF
///
/// \descr  Diagnostic subservice that stop recording of local errors
///
/// \param  UINT8
///         UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_02_CONTROL_DTC_OFF(UINT8 ui8_Type, UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  (void)p_ui8_Data;
  (void)Length;
  DIAG_status eReturnCode = DIAG_NOK;
  // Variable used for storing the diagnostic response length
  uint8  ucDataLength = 0u;
  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_1BYTE] = { 0u };

  // dtc control off
  Diag_boControlDTCOff_Stat = TRUE;

  aucResData[0] = ui8_Type;
  Rte_Call_Diag_ControlDTCSetting(FALSE, ulDTC);
  ucDataLength = DIAG_RESP_1BYTE;
  eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief APPLI_ReadMemoryByAddress
///
/// \descr  LGM callback for diagnostic service for Read Memory by Address
///
/// \param  -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_ReadMemoryByAddress(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_OK;
  // Process the user service ID: 0x23
  UINT8 ucRdmResultCode = ApplCmd_Rdm_ReadMemByAddr(p_ui8_Data, Length);

  // PRQA S 4442 1 //Enum Cast under control, return was tested and documented
  eReturnCode = ucRdmResultCode;

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief APPLI_WriteMemoryByAddress
///
/// \descr  LGM callback for diagnostic service for Write Memory by Address
///
/// \param  -p_ui8_Data: received data from diag command
///         -Length: length of received data from diag command
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status APPLI_WriteMemoryByAddress(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_OK;
  // Process the user service ID: 0x3D
  UINT8 ucRdmResultCode = ApplCmd_Rdm_WriteMemByAddr(p_ui8_Data, Length);

  // PRQA S 4442 1 //Enum Cast under control, return was tested and documented
  eReturnCode = ucRdmResultCode;

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_Read_Number_of_DTC_By_StatusMaskFaultMemory
///
/// \descr  Diagnostic subservice that returns the numbers of DTC that match
///         a logical OR with the mask given.
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_Read_Number_of_DTC_By_StatusMaskFaultMemory(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the number of active DTCs
  uint16 unDtcCount = 0u;
  // Variable for storing the diagnosti subservice
  uint8  ucDiagSubService = p_ui8_Data[0];
  // Variable for storing the received mask from request
  uint8  ucMask = p_ui8_Data[1];
  // Variable used for storing the diagnostic response length
  uint8 ucDataLength = DIAG_RESP_5BYTES;
  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_5BYTES] = { 0u };

  // Check data length
  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    aucResData[0] = ucDiagSubService;
    aucResData[1] = ucMask;
    // DTC coded is using standard ISO 15031-6
    aucResData[2] = 0u;

    // Get DTC count
    unDtcCount = ErrCust_ucGetErrorCount(ucMask);

    aucResData[3] = HIBYTE(unDtcCount);
    aucResData[4] = LOBYTE(unDtcCount);

    eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
  }
  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_Read_by_MaskFaultMemory
///
/// \descr  Diagnostic subservice that returns a list of DTCs that match
///         a logical OR with the mask given.
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_Read_by_MaskFaultMemory(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Variable used for storing the number of active DTCs
  uint16 unDtcCount;
  // Variable used for calling ErrCust_SetAvailableDtc function 'unDtcCount' times in order to take the available DTC
  uint8 ucIdx;
  // Variable used for indicating the current position where to store the DTC code
  uint16 unDtcPosition;
  // Variable for storing the received mask from request
  uint8 ucDTCStatusMask;
  // Variable for storing the diagnosti subservice
  uint8 ucDiagSubService = p_ui8_Data[0];
  // Variable used for storing the diagnostic response length
  uint16 unDataLength = 0u;
  // Variable used for storing the diagnostic response data
  uint8  aucResData[DIAG_BUFFER_512BYTES] = { 0u };

  // Check data length
  if (Length != DIAG_RESP_2BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else
  {
    // Reset the position to 2 (position 0 is diag subservice and position 1 is ucDTCStatusMask)
    unDtcPosition = 2u;
    // Take the DTC status mask from the request
    ucDTCStatusMask = p_ui8_Data[1];
    // Set the receved diag subservice on the response buffer
    aucResData[0] = ucDiagSubService;
    // Set the receved mask on the response buffer
    aucResData[1] = ucDTCStatusMask;

    // Get the number of active DTCs
    unDtcCount = ErrCust_ucGetErrorCount(ucDTCStatusMask);

    // Reset the Dtc Index
    ErrCust_ResetDtcIndex();

    for (ucIdx = 0u; ucIdx < unDtcCount; ucIdx++)
    {
      // Get the available DTC in pMsgContext->resData[unDtcPosition]
      ErrCust_SetAvailableDtc(&aucResData[unDtcPosition], ucDTCStatusMask);
#if defined (UNIT_TEST)
      /* -------------------------------------------------- --------------------------------------------*/
      /* Special UT instrumentation to force position for next DTC to keep the current position         */
      /* ---------------------------------------------------------------------------------------------- */
      Diag_Special_UT_Instrumentation_Force_DTCPosition(&unDtcPosition);
#endif
      //Increment by 4 in order to prepare the position for the next DTC: 3 bytes for DTC and 1 byte for status Of DTC
      unDtcPosition = (unDtcPosition < DIAG_BUFFER_512BYTES - 4u) ? unDtcPosition + 4u : unDtcPosition;
    }

    //The length is always last DTC position
    unDataLength = unDtcPosition;

    eReturnCode = DIAG_Send_Diag_Response(aucResData, unDataLength);
  }

  return eReturnCode;
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_Read_DTC_Snapshot_Data_by_DTC_NumberFaultMemory
///
/// \descr  Diagnostic subservice that returns the extended snapshot data for a
///         certain DTC that is received by diagnostic request.
///
/// \param  UINT8 const*
///         Diag_Length_Type
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
STATIC_AL DIAG_status Diag_Callbacks_Read_DTC_Snapshot_Data_by_DTC_NumberFaultMemory(UINT8 const* p_ui8_Data, Diag_Length_Type Length)
{
  DIAG_status eReturnCode = DIAG_NOK;

  // Local variable which keeps the Dtc index
  uint8 ucErrIx;

  // Variable for storing the diagnosti subservice
  uint8 ucDiagSubService = p_ui8_Data[0];
  // Variable used for storing the diagnostic response length
  uint8 ucDataLength = 0u;
  // Variable used for storing the diagnostic response data
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  uint8  aucResData[DIAG_BUFFER_41BYTES] = { 0u };
#else
  uint8  aucResData[DIAG_BUFFER_32BYTES] = { 0u };
#endif
  // Check data length
  if (Length != DIAG_RESP_5BYTES)
  {
    // Negative response code - 0x13 Incorrect Message Length Or Invalid Format
    eReturnCode = IMLOIF;
  }
  else if (p_ui8_Data[4] != DIAG_LAST_BYTE_DTC_SPNASHOT)
  {
    eReturnCode = ROOR;
  }
  else
  {
    // Take the Dtc code from request
// PRQA S 4397 1 //An expression which is the result of a ~ or << operation has not been cast to its essential type -> it is intended and the behavior is as expected
    uint32 ulDTC = UTIL_MAKELONG((uint16)UTIL_MAKEWORD(p_ui8_Data[3], p_ui8_Data[2]), (uint16)UTIL_MAKEWORD(p_ui8_Data[1], (uint8)0x00u));
    // Local Variable which keeps the freeze frame index of the current Dtc
    uint8 ucErrFreezeFrameIx;
    // Local variable which show if both DTC and DTCSnapshotRecordNumber have valid values
    boolean boValidParams = FALSE;
    // Local variable which keeps the type of snapshot reading
    uint8 ucDTCSnapshotRecordNumber = p_ui8_Data[4];

    uint8 ucInstLVLpos = 0u;

    // Find the given DTC
    for (ucErrIx = 0u; ucErrIx < ERRCUST_NUMBER_OF_DTCS; ucErrIx++)
    {
      if (ErrCust_ulGetDtcCode(ucErrIx) == ulDTC)
      {
        // Marked that the parameters are valid
        boValidParams = TRUE;

        // Given error found, assemble answer with dtc code and its current status
        aucResData[0] = ucDiagSubService;                                                  // Byte  2  Sub Service ID 0x04
        aucResData[1] = p_ui8_Data[1];                                                     // Byte  3  DTC
        aucResData[2] = p_ui8_Data[2];                                                     // Byte  4  DTC
        aucResData[3] = p_ui8_Data[3];                                                     // Byte  5  DTC
        aucResData[4] = ErrCust_ucGetStatusOfDTC(ucErrIx);                                 // Byte  6  DTC Status

        // Set the length in case Snapshot data for the current dtc was not saved yet
        ucDataLength = DIAG_LENGTH_SNAPSHOT_NOT_AVAILABLE;

        // Take the corresponding freeze frame index of the current Dtc
        ucErrFreezeFrameIx = NvmBlockErrCustPs.aucErrFreezeFrameIndex[ucErrIx];

        ucInstLVLpos = (NvmBlockFreezeFrameDataPs.ascINSTANT_LVL_POS[ucErrFreezeFrameIx] >= 0) ? (uint8)(sint8)((sint16)NvmBlockFreezeFrameDataPs.ascINSTANT_LVL_POS[ucErrFreezeFrameIx] * 127 / 60) : (uint8)((uint8)ErrCust_ConvertValueSint2Int(((sint32)NvmBlockFreezeFrameDataPs.ascINSTANT_LVL_POS[ucErrFreezeFrameIx] * 128 / 60), DIAG_LENGTH_8BIT));

        uint16 unOffsetCalibVehicleAttitude = (uint16)ErrCust_ConvertValueSint2Int(NvmBlockFreezeFrameDataPs.asnOFFSET_CALIB_VEHICLE_ATTITUDE[ucErrFreezeFrameIx], DIAG_LENGTH_ASSIETTE_VEHICULE);
        uint16 unInstValVehiculeAttitude = (uint16)ErrCust_ConvertValueSint2Int(NvmBlockFreezeFrameDataPs.asnINST_VAL_VEHICULE_ATTITUDE[ucErrFreezeFrameIx], DIAG_LENGTH_ASSIETTE_VEHICULE);

        // Check if snapshot available for the current DTC
        if ((ucErrFreezeFrameIx != ERRCUST_DTC_AVAILABLE_FOR_FFD) && (ucErrFreezeFrameIx <= ERRCUST_FREEZE_FRAME_DATA_ENTRIES))
        {
          aucResData[5] = DIAG_ALL_DATA_RECORD_NUMBER;                                                         // Byte  7  Report all stored DTCSnapshot (context) data records at once 
          aucResData[6] = DIAG_AFTERMARKET_DATA_IDS_NR;                                                        // Byte  8  Number of Identifiers
          aucResData[7] = DIAG_DID_D4XX_HIGH_BYTE;                                                             // Byte  9  Identifier high byte, AfterMarket Data's RBIN/NTC Failure per light function  [0xD420]
          aucResData[8] = DIAG_DID_D420_LOW_BYTE;                                                              // Byte 10  Identifier low byte, AfterMarket Data's RBIN/NTC Failure per light function   [0xD420]
          aucResData[9] = NvmBlockFreezeFrameDataPs.aucRbinNtcErrPerLightFunc[ucErrFreezeFrameIx];             // Byte 11  Bit 0: [Data] RBIN NTC Failure per light function: LB_Diag                    [0xD420]
                                                                                                               // Byte 11  Bit 1: [Data] RBIN NTC Failure per light function: HB_Diag                    [0xD420]
                                                                                                               // Byte 11  Bit 2: [Data] RBIN NTC Failure per light function: DRL_POS_Diag               [0xD420]
                                                                                                               // Byte 11  Bit 3: [Data] RBIN NTC Failure per light function: TI_Diag                    [0xD420]
                                                                                                               // Byte 11  Bit 4: [Data] RBIN NTC Failure per light function: SM_Diag                    [0xD420]
                                                                                                               // Byte 11  Bit 5: [Data] RBIN NTC Failure per light function: RGB_Diag                   [0xD420]
                                                                                                               // Byte 11  Bit 6: [Data] RBIN NTC Failure per light function: Fog_Light_Diag             [0xD420]
                                                                                                               // Byte 11  Bit 7: [Data] RBIN NTC Failure per light function: Cornering_Light_Diag       [0xD420]
          aucResData[10] = DIAG_RESERVED_BYTE;                                                                 // Byte 12  Reserved byte                                                                 [0xD420]
          aucResData[11] = DIAG_DID_D4XX_HIGH_BYTE;                                                            // Byte 13  Identifier high byte, AfterMarket Data's RBIN EEPROM LMM Diagnosis  [0xD421]
          aucResData[12] = DIAG_DID_D421_LOW_BYTE;                                                             // Byte 14  Identifier low byte, AfterMarket Data's RBIN EEPROM LMM Diagnosis   [0xD421]
          aucResData[13] = NvmBlockFreezeFrameDataPs.aucRbinEepromLmmFirstByte[ucErrFreezeFrameIx];            // Byte 15  Bits 0-7: [Data] RBIN/NTC DIAG 8-1                                  [0xD421]
          aucResData[14] = NvmBlockFreezeFrameDataPs.aucRbinEepromLmmSecondByte[ucErrFreezeFrameIx];           // Byte 16  Bits 0-1: [Data] EEPROM DIAG 2-1                                    [0xD421]
                                                                                                               // Byte 16  Bits 2-7: [Data] RBIN/NTC DIAG 14-9                                 [0xD421]
          aucResData[15] = NvmBlockFreezeFrameDataPs.aucRbinEepromLmmThirdByte[ucErrFreezeFrameIx];            // Byte 17  Bits 0-7: [Data] EEPROM DIAG 10-3                                   [0xD421]
          aucResData[16] = NvmBlockFreezeFrameDataPs.aucRbinEepromLmmFourthByte[ucErrFreezeFrameIx];           // Byte 18  Bits 0-5: [Data] LMM DIAG 6-1                                       [0xD421]
                                                                                                               // Byte 18  Bits 6-7: [Data] EEPROM DIAG 12-11                                  [0xD421]
          aucResData[17] = NvmBlockFreezeFrameDataPs.aucRbinEepromLmmFifthByte[ucErrFreezeFrameIx];            // Byte 19  Bits 0-6: reserved                                                  [0xD421]
                                                                                                               // Byte 19  Bit 7: [Data] LMM DIAG 7                                            [0xD421]
          aucResData[18] = DIAG_DID_D4XX_HIGH_BYTE;                                                            // Byte 20  Identifier high byte, AfterMarket Data's LED Channel Output Diagnosis  [0xD422]
          aucResData[19] = DIAG_DID_D422_LOW_BYTE;                                                             // Byte 21  Identifier low byte, AfterMarket Data's LED Channel Output Diagnosis   [0xD422]
          aucResData[20] = NvmBlockFreezeFrameDataPs.aucLedChnlOutFirstByte[ucErrFreezeFrameIx];               // Byte 22  Bits 0-7: [Data] LED Channel Output Diag 8-1                           [0xD422]
          aucResData[21] = NvmBlockFreezeFrameDataPs.aucLedChnlOutSecondByte[ucErrFreezeFrameIx];              // Byte 23  Bits 0-3: reserved                                                     [0xD422]
                                                                                                               // Byte 23  Bits 4-7: [Data] LED Channel Output Diag 12-9                          [0xD422]
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
          aucResData[22] = DIAG_DID_D4XX_HIGH_BYTE;                                                                                                    // Byte 24  Identifier high byte, AfterMarket Data's ATTITUDE_ECU  [0xD4C9]
          aucResData[23] = DIAG_DID_D4C9_LOW_BYTE;                                                                                                     // Byte 25  Identifier low byte, AfterMarket Data's ATTITUDE_ECU   [0xD4C9]
          aucResData[24] = (uint8)((uint8)(0x0Fu << DIAG_4BIT_SHIFT) | (uint8)(unOffsetCalibVehicleAttitude >> DIAG_6BIT_SHIFT));                      // Byte 26  Calibration offset of vehicle attitude from network    [0xD4C9]
          aucResData[25] = (uint8)((uint8)(unOffsetCalibVehicleAttitude << DIAG_4BIT_SHIFT) | (uint8)(unInstValVehiculeAttitude >> DIAG_8BIT_SHIFT));  // Byte 27  Calibration offset of vehicle attitude from network    [0xD4C9]
          aucResData[26] = (uint8)(unInstValVehiculeAttitude & DIAG_8_BIT_MASK);                                                                       // Byte 28  Instantaneous value of vehicle attitude from network   [0xD4C9]
          aucResData[27] = DIAG_DID_D4XX_HIGH_BYTE;                                                            // Byte 29  Identifier high byte, AfterMarket Data's LVL_ECU                            [0xD4CB]
          aucResData[28] = DIAG_DID_D4CB_LOW_BYTE;                                                             // Byte 30  Identifier low byte, AfterMarket Data's LVL_ECU                             [0xD4CB]
          aucResData[29] = ucInstLVLpos;                                                                       // Byte 31  Instantaneous angular levelling position                                    [0xD4CB]
          aucResData[30] = NvmBlockFreezeFrameDataPs.aucLVL_INFO[ucErrFreezeFrameIx];                          // Byte 32  Bits 0-1 [Data] Status of automatic levelling                               [0xD4CB]
                                                                                                               // Byte 32  Bits 2-3: reserved                                                          [0xD4CB]
                                                                                                               // Byte 32  Bit 4: [Data] Step loss, position or direction defect of levelling stepper  [0xD4CB]
                                                                                                               // Byte 32  Bit 5: [Data] Communication or time out defect of levelling stepper         [0xD4CB]
                                                                                                               // Byte 32  Bit 6: [Data] Electrical or thermic defect of levelling stepper             [0xD4CB]
                                                                                                               // Byte 32  Bit 7: [Data] Levelling stepper in motion                                   [0xD4CB]
          aucResData[31] = DIAG_DID_E888_HIGH_BYTE;                                                            // Byte 33  Identifier high byte, AfterMarket Data's CONTEXT_ECU  [0xE888]
          aucResData[32] = DIAG_DID_E888_LOW_BYTE;                                                             // Byte 34  Identifier low byte, AfterMarket Data's CONTEXT_ECU   [0xE888]
          aucResData[33] = NvmBlockFreezeFrameDataPs.aucVOLTAGE_TERMINAL_DTC[ucErrFreezeFrameIx];              // Byte 35  Voltage terminal value                                [0xE888]
          aucResData[34] = NvmBlockFreezeFrameDataPs.aucETAT_INFO_DTC[ucErrFreezeFrameIx];                     // Byte 36  Bits 0-3: [Data] ETAT_RESEAU_ELEC state               [0xE888]
                                                                                                               // Byte 36  Bits 4-5: [Data] ETAT_PRINCIP_SEV state               [0xE888]
                                                                                                               // Byte 36  Bits 6-7: reserved                                    [0xE888]
          aucResData[35] = NvmBlockFreezeFrameDataPs.VEHICLE_SPEED_DTC[ucErrFreezeFrameIx];                    // Byte 37  Vehicle speed value                                   [0xE888]
          aucResData[36] = (uint8)(NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC[ucErrFreezeFrameIx] >> 16u);      // Byte 38  Kilometrage value HIGHBYTE                            [0xE888]
          aucResData[37] = (uint8)(NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC[ucErrFreezeFrameIx] >> 8u);       // Byte 39  Kilometrage value MIDBYTE                             [0xE888]
          aucResData[38] = (uint8)NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC[ucErrFreezeFrameIx];               // Byte 40  Kilometrage value LOWBYTE                             [0xE888]
          aucResData[39] = NvmBlockFreezeFrameDataPs.INST_VAL_FL_BODY_HIGH_SENSOR_DTC[ucErrFreezeFrameIx];     // Byte 41  Instantaneous value of Front Left BHS                 [0xE888]
          aucResData[40] = NvmBlockFreezeFrameDataPs.INST_VAL_RL_BODY_HIGH_SENSOR_DTC[ucErrFreezeFrameIx];     // Byte 42  Instantaneous value of Rear Left BHS                  [0xE888]
#else
          aucResData[22] = DIAG_DID_E888_HIGH_BYTE;                                                            // Byte 24  Identifier high byte, AfterMarket Data's CONTEXT_ECU  [0xE888]
          aucResData[23] = DIAG_DID_E888_LOW_BYTE;                                                             // Byte 25  Identifier low byte, AfterMarket Data's CONTEXT_ECU   [0xE888]
          aucResData[24] = NvmBlockFreezeFrameDataPs.aucVOLTAGE_TERMINAL_DTC[ucErrFreezeFrameIx];              // Byte 26  Voltage terminal value                                [0xE888]
          aucResData[25] = NvmBlockFreezeFrameDataPs.aucETAT_INFO_DTC[ucErrFreezeFrameIx];                     // Byte 27  Bits 0-3: [Data] ETAT_RESEAU_ELEC state               [0xE888]
                                                                                                               // Byte 27  Bits 4-5: [Data] ETAT_PRINCIP_SEV state               [0xE888]
                                                                                                               // Byte 27  Bits 6-7 reserved                                     [0xE888]
          aucResData[26] = NvmBlockFreezeFrameDataPs.VEHICLE_SPEED_DTC[ucErrFreezeFrameIx];                    // Byte 28  Vehicle speed value                                   [0xE888]
          aucResData[27] = (uint8)(NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC[ucErrFreezeFrameIx] >> 16u);      // Byte 29  Kilometrage value HIGHBYTE                            [0xE888]
          aucResData[28] = (uint8)(NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC[ucErrFreezeFrameIx] >> 8u);       // Byte 30  Kilometrage value MIDBYTE                             [0xE888]
          aucResData[29] = (uint8)NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC[ucErrFreezeFrameIx];               // Byte 31  Kilometrage value LOWBYTE                             [0xE888]
          aucResData[30] = NvmBlockFreezeFrameDataPs.INST_VAL_FL_BODY_HIGH_SENSOR_DTC[ucErrFreezeFrameIx];     // Byte 32  Instantaneous value of Front Left BHS                 [0xE888]
          aucResData[31] = NvmBlockFreezeFrameDataPs.INST_VAL_RL_BODY_HIGH_SENSOR_DTC[ucErrFreezeFrameIx];     // Byte 33  Instantaneous value of Rear Left BHS                  [0xE888]
#endif
          // Set the length of the response data; 41 for FULL and 32 for ECO
          ucDataLength = DIAG_DTC_SNAPSHOT_LENGTH;
        }
        else
        {
          // Freeze Frame data for the current DTC were not stored, therefore nothing to do
        }

        // Dtc was found, therefore the search can be finished
        break;
      }
      else
      {
        // DTC or DTCSnapshotRecordNumber are invalid, therefore nothing to do
      }
    }

    // Check if DTC and DTCSnapshotRecordNumber are valid
    if (boValidParams == FALSE)
    {
      // Params are invalid
      eReturnCode = ROOR;
    }
    else
    {
      // Params are valid
      eReturnCode = DIAG_Send_Diag_Response(aucResData, ucDataLength);
    }
  }

  return eReturnCode;
} // PRQA S 5330, 5336 1 // Multiple lines needed to handle processing of diagnostic buffer


//-----------------------------------------------------------------------------
/// \brief  APPLI_RemoveAllDTC
///
/// \descr  LGM Callback in order to remove all DTCs from NvM
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void APPLI_RemoveAllDTC(void)
{
  // Local array which keeps the value for erase all DTCs
  uint8 aucClearAllDtcs[ERRCUST_DTC_CODE_SIZE] = { 0xFFu, 0xFFu, 0xFFu };

  // Clear DTCs
  (void)ErrCust_ClearMemory(&aucClearAllDtcs[0u]);
}


//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_ProgramingSessionAccepted
///
/// \descr Programing Session Actions (sha data update + MCU reset)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Diag_Callbacks_ProgramingSessionAccepted(void)
{
#if (DIAG_APPLCMD_PRIVILEGE_MODE_SWITCH_SUPPORT == STD_ON)

  boolean boIsMcuPrivilege = TRUE;

  ApplCmd_Rdm_GetMcuPrivilegeStatus();

  if (ApplCmd_Rdm_ulMcuPrivStatus == 0u)
  {
    ApplCmd_Rdm_PrivilegeSwitch();
    boIsMcuPrivilege = FALSE;
  }
  else
  {
    // MCU is in Privilege already
  }

#endif 
  //PRQA S 306  4 // Cast between a pointer to object and an integral type.
  //PRQA S 1840 3 // The left-hand operand is constant, 'essentially signed' (signed int) and non-negative but will be implicitly converted to an unsigned type (unsigned int) in this arithmetic operation.
  (*(UINT32*)((uint32)m_data_shared_start + 0x80u)) = (UINT32)0xCA11B007U; //FBL MAGIC FLAG
  (*(UINT32*)((uint32)m_data_shared_start + 0x84u)) = (UINT32)0x1234u;     //Appl Seed
  (*(UINT32*)((uint32)m_data_shared_start + 0x88u)) = (UINT32)LGM_FALSE;   //BOOT_b_AppliDSCsuppressPosRspMsgIndicationBit

  Mcu_PerformReset();

#if (DIAG_APPLCMD_PRIVILEGE_MODE_SWITCH_SUPPORT == STD_ON)

  // Switch back to user mode
  if (boIsMcuPrivilege == FALSE)
  {
    ApplCmd_Rdm_UserSwitch();
  }

#endif 
}


//-----------------------------------------------------------------------------
/// \brief roDiag_Callbacks_ProgramingSessionAccepted
///
/// \descr Programing session accepted runable
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void roDiag_Callbacks_ProgramingSessionAccepted(void)
{
  Diag_Callbacks_ProgramingSessionAccepted();
}


//-----------------------------------------------------------------------------
/// \brief roDiag_Callbacks_NRC_Response
///
/// \descr Negative response runable
///
/// \param  ucCode - NRC code
///
/// \return void
//-----------------------------------------------------------------------------
void roDiag_Callbacks_NRC_Response(uint8 ucCode)
{
  // PRQA S 4342 2 // Casting is OK, NRC code conversion 
  (void)DIAG_Send_Diag_Error((DIAG_status)ucCode);
}


//-----------------------------------------------------------------------------
/// \brief  Diag_CodingDataValidation
///
/// \descr  get and handle coding parameters for Diag module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
STATIC_AL boolean Diag_CodingDataValidation(void)
{
  tsDiag_CodingParameters sCodingParameters;

  //get coding data via RTE
  Diag_Get_Coding(&sCodingParameters);

  //get coding data and return validity of this
  CONST_AL boolean boCodingValidity = Diag_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters);

  //return validity of coding
  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  Diag_Get_Coding
///
/// \descr  Read Coding Data via RTE
///
/// \param  *psCodingParam - pointer to commands and coding data
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Diag_Get_Coding(tsDiag_CodingParameters *psCodingParam)
{
  tsRteCodingParameters sRteCodingParameters;

  (void)Rte_Read_CodM_AppM_Para(&sRteCodingParameters);

  //PRQA S 310 1 // Cast needed
  psCodingParam->eCodingState = sRteCodingParameters.eCodingState;
  psCodingParam->psCodingParameters = sRteCodingParameters.psCodingParameters_Blocks;
}


//-----------------------------------------------------------------------------
/// \brief  Diag_ParaFct0
///
/// \descr  this function get coding params and validity of coding data 
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean Diag_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;

  // Get coding data based on command received
  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
    boCodingValidity = TRUE;
    Diag_pCodingArea = pData;
    break;
  case eParaFct0_CodingDataInvalid:
    boCodingValidity = FALSE;
    break;
  default:
    break;
  }
  // Return coding validity
  return boCodingValidity;
}



#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)

//-----------------------------------------------------------------------------
/// \brief Diag_Callbacks_Check_If_Scrolling_Present
///
/// \descr  Diagnostic subservice that returns if scrolling is present
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Diag_Callbacks_Check_If_Scrolling_Present(void)
{
  boolean boScrlFuncPresent = FALSE;

  for (uint8 ucIdx = 0u; ucIdx < DIAG_NO_OF_LED_CHANNELS; ucIdx++)
  {
    if ((Diag_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[ucIdx] == DIAG_LF_DRL_POS_SCRL)
      || (Diag_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[ucIdx] == DIAG_LF_TI_SCRL))
    {
      // Scrolling functionality is present
      boScrlFuncPresent = TRUE;
      break;
    }
    else
    {
      // nothing to do
    }
  }

  return boScrlFuncPresent;
}
#endif


#ifdef UNIT_TEST
//-----------------------------------------------------------------------------
/// \brief Diag_Special_UT_Instrumentation_Force_InvalidCoding
///
/// \descr Special UT instrumentation handler (simulates uninitialized coding)
///
/// \param  UINT8 const** p_ui8_Data
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Diag_Special_UT_Instrumentation_Force_InvalidCoding(UINT8 const** p_ui8_Data)
{
  STATIC_UT(boolean, Diag_Force_InvalidCoding, FALSE);

  if (Diag_Force_InvalidCoding == TRUE)
  {
    *p_ui8_Data = 0x16u;
    Diag_Force_InvalidCoding = FALSE;
  }
  else
  {
    // skip the UT instrumentation
  }

}

//-----------------------------------------------------------------------------
/// \brief Diag_Special_UT_Instrumentation_Force_DTCPosition
///
/// \descr Special UT instrumentation handler (simulate position for the next DTC)
///
/// \param  uint16* unDtcPosition
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Diag_Special_UT_Instrumentation_Force_DTCPosition(uint16* unDtcPosition)
{
  STATIC_UT(boolean, Diag_Force_DTCPosition, FALSE);

  if (Diag_Force_DTCPosition == TRUE)
  {
    *unDtcPosition = DIAG_BUFFER_512BYTES;
    Diag_Force_DTCPosition = FALSE;
  }
  else
  {
    *unDtcPosition = 2u;
  }

}
#endif
// EOF
