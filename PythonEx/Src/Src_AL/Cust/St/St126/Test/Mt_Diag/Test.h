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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <Diag_Callbacks.h>
#include <Cfg/CfgId.h>
#include <CfgId_Type.h>


//=============================================================================
// Typedefs
//=============================================================================
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

typedef struct
{

} DescMsgContext;

CfgId_CfgInfoType CfgId_CfgInfoConfigData;

typedef DescMsgContext MsgContextType;
typedef void* (*tpfnGetVirtData)(uint32* pulSize);


//=============================================================================
// Defines
//=============================================================================
/* Supplier Code */
#define SUPPLIER_CODE_0                         (uint8)0x00
#define SUPPLIER_CODE_1                         CFG_ULP_CAL_SUPPLIER

#define NUMBER_OF_ASSOCIATED_PARAMETERS_0       (uint8)0x00

#define SUPPLIER_IDENT_MANUFACT_DATE_0          (uint8)0x01
#define SUPPLIER_IDENT_MANUFACT_DATE_1          (uint8)0x01
#define SUPPLIER_IDENT_MANUFACT_DATE_2          (uint8)0x01

#define SUPPLIER_IDENT_SITE_CODE_0              (uint8)0xFE

#define SUPPLIER_IDENT_SIGNATURE_CODE_0         (uint8)0x00
#define SUPPLIER_IDENT_SIGNATURE_CODE_1         (uint8)0x00
#define SUPPLIER_IDENT_SIGNATURE_CODE_2         (uint8)0x00

#define SUPPLIER_IDENT_NUMBER_CODE_0            (uint8)0xFE
#define SUPPLIER_IDENT_MARKING_0                (uint8)0x5C

#define SUPPLIER_IDENT_CRC_0                    (uint8)0x51
#define SUPPLIER_IDENT_CRC_1                    (uint8)0x8A

#define RDM_ROM_BEGIN       0x00000000U
#define RDM_ROM_END         0x000FFFFFU

#define RDM_RAM_BEGIN       0x1FFF0000U
#define RDM_RAM_END         0x2000EFFFU

#define RDM_REG_BEGIN       0x400FF000U
#define RDM_REG_END         0x400FF000U

#define DIAG_D406_MAX_MAIN_LIGHTS   4U
#define DIAG_D406_LB_MAIN_LIGHTS    0x00001FFFU
#define DIAG_D406_HB_MAIN_LIGHTS    0x003FE000U
#define DIAG_D406_OTHER_MAIN_LIGHT  0x1FC00000U
#define DIAG_D406_TI_MAIN_LIGHT     0xE0000000U
#define DIAG_AIMING_MODE_IDX        0x0FU
#define DIAG_ALIGNMENT_MODE_IDX     0x10U


//=============================================================================
// Module global variables
//=============================================================================
tScrollingPresent_Stat sScrollingSatelite_Start_Status;
tScrollingPresent_Stat sScrollingSatelite_StatPrev;
uint32 ulLDrawPrv;
uint32 ulLDrawDiag;

uint8 ucRoutineState;
boolean boScrollingSatelite_Start_Status;
extern uint16 Diag_Callbacks_unCodShortGND;
extern uint16 Diag_Callbacks_unCodShortBAT;
extern uint16 Diag_Callbacks_unCodOpenLoad;
extern tsRte_Ld_ActivationRoutineControl Diag_sLd_ActivationRoutineControl;

extern boolean Diag_boRoutineFinishedDF17;
extern boolean Diag_boRoutineFinishedDD05;
extern boolean Diag_boRoutineFinishedDF10;
extern boolean Diag_boRoutineFinishedDF11;
extern boolean Diag_boRoutineFinishedDF12;
extern boolean Diag_boRoutineFinishedDF13;
extern boolean Diag_boRoutineFinishedDD04;
extern tsRteHssTarget Diag_asCpmHssTargetSetting;
extern tsRte_AfsRoutineControl sAfsRoutineControl;
extern boolean Diag_boRoutineFinishedDD01;
extern boolean Diag_boDD01_Status;
extern tsRte_DIDPixelActivation Diag_boDD01_PixelActivation;

extern boolean Diag_boRoutineFinishedDFB5;
extern boolean Diag_boRoutineFinishedDD00;
extern boolean Diag_boRoutineFinishedDD03;

extern boolean Diag_boRoutineFinishedDD06;

extern uint8 Diag_ucErrorCnt;
extern uint8 Diag_ucPwmSensError;

extern uint32 ApplCmd_Rdm_ulMcuPrivStatus;
CONST_AL tEftData EftData =
{
  // ------------------------------------------------------------------
  // Eft_Crc
  // ------------------------------------------------------------------
    {
      { 1234u },                // Eft_Crc32
      { 1u, 255u, 255u, 255u }  // Eft_DocVers
    },
  // ------------------------------------------------------------------


  // ------------------------------------------------------------------
  // Eft_Calib
  // ------------------------------------------------------------------
    { // union
    {
      { { 'C', 'A', 'L', 'I' } },      // Eft_Calib_Text
      { 255u, 255u, 255u, 255u },      // Eft_Calib_Type

      CDDTPS92520_Eft_Calib_Default,   // TPS92520 calibration
      CDDNCV78702_Eft_Calib_Default    // NCV78702 calibration
    }
    },


  // ------------------------------------------------------------------
  // Eft_HwDesc
  // ------------------------------------------------------------------
    { // union
    {
      { { 'H', 'W', 'I', 'D' } },  // Eft_HwDesc_Text
      { 255u, 255u, 255u, 255u },  // Eft_HwDesc_Type
    }
    },


  // ------------------------------------------------------------------
  // Eft_EcuVarCfg
  // ------------------------------------------------------------------
    { // union
    {
      { { 'V', 'C', 'F', 'G' } },                         // Eft_EcuVarCfg_Text
      { 255u, 255u, 1u, 255u },                           // Eft_EcuVarCfg_Type
      CDDTPS92520_Eft_EcuVarCfg_Default,                  // TPS92520 configuration
      CDDNCV78702_Eft_EcuVarCfg_Default,                  // NCV78702 configuration
      { 0x3FFFu, 0xFFFFu },                               // NTC
      { 216u, 9661u },                                    // ADC IN
      { { 2u, 255u }, { 0u, 255u } },                     // STP
      { 0u, 255u },                                       // DC OUT
      { 3u, 255u },                                       // EXT SUPPLY 2
      { 0u, 255u },                                       // EXT SUPPLY 3
      { 0u, 255u },                                       // SWITCH ARRAY
      { { 1u, 255u }, { 2u, 255u },                       // HSS
        { 3u, 255u }, { 0u, 255u } },                     // HSS
      { 1u, 255u },                                       // CAN2
      { 0u, 255u },                                       // CAN3
      { 0u, 255u },                                       // LIN
      { 2u, 255u },                                       // GPIO SBC
      { 0u, 255u },                                       // WK SENSE
      { { 1u, 255u }, { 1u, 255u },                       // IN
        { 3u, 255u }, { 1u, 255u } },                     // IN
      {
        5000u ,                                           // ADC FACTOR PCB TEMP
      { 6273u, 6273u, 6273u, 6273u, 6273u, 6273u, 6273u,  // ADC FACTOR NTC
        6273u, 6273u, 6273u, 6273u, 6273u, 6273u, 6273u },// ADC FACTOR NTC
        24643u,                                           // ADC FACTOR Vbat
        24643u,                                           // ADC FACTOR LrDetect
        5000u,                                            // ADC FACTOR HssSense_1_2
        5000u,                                            // ADC FACTOR HssSense_3
        0u,                                               // ADC FACTOR PosSensor
      { 6273u,  6273u,  0u },                             // ADC FACTOR Vccx
      { 0u, 0u, 0u, 0u },                                 // ADC FACTOR In
        24643u,                                           // ADC FACTOR OutFct
        0u                                                // ADC FACTOR Vboost
      }
    }
    }
};

/* BootLoader authentication zone */
tuDiag_AuthZoneInfo AppDesc_AuthZone __attribute__((section(".AuthZone"), used)) =
{
 .sAuthZoneInfo.aucFunctPlanNb            = CFG_FUNCTPLANNB,
 .sAuthZoneInfo.aucPsaSupplierCode        = {SUPPLIER_CODE_0, SUPPLIER_CODE_1},
 .sAuthZoneInfo.aucFunctProdNb            = CFG_FUNCTPRODNB,
 .sAuthZoneInfo.ucSwEvolutionIndex_MSB    = CFG_SOFT_VERSION,
 .sAuthZoneInfo.ucSwEvolutionIndex_LSB    = CFG_SOFT_EDITION,
 .sAuthZoneInfo.aucReserved               = {0xFF, 0xFF},
 .sAuthZoneInfo.ucDiagFrameEvolutionIndex = CFG_SOFT_EVOLUTION_INDEX,
 .sAuthZoneInfo.ucFaultsParamNr           = NUMBER_OF_ASSOCIATED_PARAMETERS_0,
 .sAuthZoneInfo.aucReserved2              = CFG_APPLI_TYPE
};


tsDiag_LogZoneEntry C_BOOT_ZI_Area[DIAG_LOGZONE_ENTRIES_NR] __attribute__((section(".LOG_ZONE"), used)) =
{ //PRQA S 693 2 // special memory mapping mechanism
  /* Initialization of the first ZI record */
  /* 00 */		(uint8)0xFF, /* Reserved */
  /* 01 */		(uint8)0xFF, /* Reserved */
  /* 02 */		(uint8)0x00, /* Reserved */
  /* 03 */		(uint8)0x00, /* Reserved */
  /* 04 */		(uint8)CFG_ULP_CAL_SUPPLIER, /* Supplier */
  /* 05 */		(uint8)CFG_ULP_CAL_SYSTEM, /* System */
  /* 06 */		(uint8)SUPPLIER_IDENT_MANUFACT_DATE_0, /* Manufacturing date0 */
  /* 07 */		(uint8)SUPPLIER_IDENT_MANUFACT_DATE_1, /*Manufacturing date1*/
  /* 08 */		(uint8)SUPPLIER_IDENT_MANUFACT_DATE_2, /*Manufacturing date2 */
  /* 09 */		(uint8)CFG_ULP_CAL_APPLICATION, /* Application */
  /* 10 */		(uint8)CFG_ULP_CAL_SOFTWARE_VERSION, /* Version */
  /* 11 */		HIBYTE(CFG_ULP_CAL_SOFTWARE_EDITION), /* Edition0 */
  /* 12 */		LOBYTE(CFG_ULP_CAL_SOFTWARE_EDITION), /* Edition1 */
  /* 13 */		(uint8)JENKINS_BUILD_DAY, /* Programming date0 */
  /* 14 */		(uint8)JENKINS_BUILD_MONTH, /* Programming date1 */
  /* 15 */		(uint8)JENKINS_BUILD_YEAR, /* Programming date2 */
  /* 16 */		(uint8)SUPPLIER_IDENT_SITE_CODE_0, /* Site */
  /* 17 */		(uint8)SUPPLIER_IDENT_SIGNATURE_CODE_0, /* Signature0 */
  /* 18 */		(uint8)SUPPLIER_IDENT_SIGNATURE_CODE_1, /* Signature1 */
  /* 19 */		(uint8)SUPPLIER_IDENT_SIGNATURE_CODE_2, /* Signature2 */
  /* 20 */		(uint8)SUPPLIER_IDENT_NUMBER_CODE_0, /* Number */
  /* 21 */		(uint8)CFG_ULP_CAL_FILE_NUMBER_1, /* ref: Software0 */
  /* 22 */		(uint8)CFG_ULP_CAL_FILE_NUMBER_2, /* ref: Software1 */
  /* 23 */		(uint8)CFG_ULP_CAL_FILE_NUMBER_3, /* ref: Software2 */
  /* 24 */		(uint8)0xFF, /* reserved 21 bytes : 0 */
  /* 25 */		(uint8)0xFF,
  /* 26 */		(uint8)0xFF,
  /* 27 */		(uint8)0xFF,
  /* 28 */		(uint8)0xFF,
  /* 29 */		(uint8)0xFF,
  /* 30 */		(uint8)0xFF,
  /* 31 */		(uint8)0xFF,
  /* 32 */		(uint8)0xFF,
  /* 33 */		(uint8)0xFF,
  /* 34 */		(uint8)0xFF,
  /* 35 */		(uint8)0xFF,
  /* 36 */		(uint8)0xFF,
  /* 37 */		(uint8)0xFF,
  /* 38 */		(uint8)0xFF,
  /* 39 */		(uint8)0xFF,
  /* 40 */		(uint8)0xFF,
  /* 41 */		(uint8)0xFF,
  /* 42 */		(uint8)0xFF,
  /* 43 */		(uint8)0xFF,
  /* 44 */		(uint8)0xFF, /* reserved 21 bytes : 20 */
  /* 45 */		(uint8)SUPPLIER_IDENT_MARKING_0, /* Marking of the recording */
  /* 46 */		(uint8)SUPPLIER_IDENT_CRC_0, /* CRC HISTO0 */
  /* 47 */		(uint8)SUPPLIER_IDENT_CRC_1, /* CRC HISTO1 */
}; // PRQA S 686 1 // only first 48 bytes are of interes

extern tNvmPara_CodingArea*  Diag_pCodingArea;

//static variable used for coding instrumentation
boolean Diag_Force_InvalidCoding;
boolean Diag_Force_DTCPosition;
boolean Diag_Force_LightReq;

//=============================================================================
// Global variable stubs ( registers, global variables from other modules which are referenced in the module )
//=============================================================================
extern uint32 Diag_Callbacks_UT_ulTest_Buf[];

//=============================================================================
// Module function declarations
//=============================================================================
//Diag_Callbacks.c
extern  DIAG_status     Diag_Callbacks_Read_Number_of_DTC_By_StatusMaskFaultMemory(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_Read_by_MaskFaultMemory(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_Read_DTC_Snapshot_Data_by_DTC_NumberFaultMemory(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_0301_RESET_CPU_LOAD(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_F186_Active_Diag_Session_Data_Identifier(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_C002_SIZE_FOR_MULTI_DID(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_0D00_FACTORY_DATA_PROCESS_BYTE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_0D01_SIZE_OF_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D400_PIXEL_LED_STATUS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D401_FAN1_STATUS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D402_FAN2_STATUS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D404_SCROLLING_CTRL_OUTPUT_STATE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D405_LED_CH_OUTPUT_STATE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D406_LD_STATUS(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D407_NTC_RBIN_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D408_DERATING_FACTOR_AND_TEMP(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D409_CURRENT_BINNING_CLASS(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D410_DIAG_SCROLLING_INPUT_STATE(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D411_INSTRUMENTATED_FRAMES(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D421_RBIN_EEPROM_LMM_DIAGNOSIS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_1100_CPU_LOAD_OF_DEVICE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D4C5_LIGHTING_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_FD00_STATISTICS_DATA(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_FD02_INTERNAL_ECU_SERIAL_NUMBER_DATA_IDENTIFIER(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_FD03_READ_ACTIVE_ALECS(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_FD04_INTERNAL_SW_LABEL(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D4C6_SIGNALLING_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D4C7_TURN_IND_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D4C8_BODY_HIGH_SENSOR_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D4C9_ATTITUDE_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D4CB_LEVELLING_ENG_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_D4CD_RGB_LED(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_F080_AUTHENTIFICATION_ZONE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_F0FE_IDENTIFICATION_ZONE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_F08F_EMC_STANDARDIZATION_LABEL(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_DD06_LvlDCMotorPosition(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DD01_PixelActivation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DD04_Fan2Activation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DD05_LvlStepperPosition(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DD07_SetScrollingCtrlOutput(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DF10_LvlReferencingRun(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DF11_LvlStepperControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DF12_LvlStepperControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DF13_LvlStepperControl(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DD00_LdActivation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DD03_Fan1Activation(uint8 ucRoutineControlType, uint16 unLength, UINT8 const* p_ui8_Data);
extern  DIAG_status     Diag_Callbacks_DFB5_InitAutomativLeveling(uint8* ucResData, uint8 ucDataLen, uint8 ucRoutineControlType, uint16 unLength, UINT8 const* puc_Data);
extern  DIAG_status     Diag_Callbacks_01_CONTROL_DTC_ON(UINT8 ui8_Type, UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_02_CONTROL_DTC_OFF(UINT8 ui8_Type, UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_Write_0D00_FACTORY_DATA_PROCESS_BYTE(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_Write_FD00_STATISTICS_DATA(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Callbacks_Write_D411_INSTRUMENTATED_FRAMES(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern  DIAG_status     Diag_Ld_Control(const boolean boDiagStatus, uint8 const* pucData);
extern  boolean         Diag_PowertrainCheck(void);
extern  boolean         Diag_IntegrationMode(void);
extern  void            Diag_Callbacks_RoutineControl_CheckStartStop(void);
extern  void            Diag_Callbacks_ProgramingSessionAccepted(void);
extern  boolean         Diag_CodingDataValidation(void);
extern  void            Diag_Get_Coding(tsDiag_CodingParameters *psCodingParam);
extern  boolean         Diag_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
extern  DIAG_status     Diag_Callbacks_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS(UINT8 const * p_ui8_Data, Diag_Length_Type Length);
extern  uint32          Diag_Callback_CheckLastLightReq_Activated(void);
extern  boolean         Diag_Callbacks_Check_If_Scrolling_Present(void);

// Diag_ApplCmd_Rdm.c
extern uint8            ApplCmd_Rdm_ReadMemByAddr(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern uint8            ApplCmd_Rdm_WriteMemByAddr(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
extern uint8            ApplCmd_Rdm_StartSession(MsgContextType *const pMsgContext);
extern uint8            ApplCmd_Rdm_SecurityAccess(MsgContextType *const pMsgContext);
extern void*            Diag_GetVirtData_OsSystemCounter(uint32* pulSize);
extern void             ApplCmd_Rdm_PrivilegeUpdate(void);
extern void             ApplCmd_Rdm_GetMcuPrivilegeStatus(void);
extern void             ApplCmd_Rdm_PrivilegeSwitch(void);
extern void             ApplCmd_Rdm_UserSwitch(void);


//=============================================================================
// Module function parameter stubs
//=============================================================================
UINT16                    APPLI_WriteDataByIdentifier_Param1;
UINT8                     APPLI_WriteDataByIdentifier_Param2[100];
Diag_Length_Type          APPLI_WriteDataByIdentifier_Param3;
UINT8                     Diag_Callbacks_Write_0D00_FACTORY_DATA_PROCESS_BYTE_Param1[100];
Diag_Length_Type          Diag_Callbacks_Write_0D00_FACTORY_DATA_PROCESS_BYTE_Param2;
UINT8                     Diag_Callbacks_Write_D411_INSTRUMENTATED_FRAMES_Param1[100];
Diag_Length_Type          Diag_Callbacks_Write_D411_INSTRUMENTATED_FRAMES_Param2;
UINT8                     Diag_Callbacks_Write_FD00_STATISTICS_DATA_Param1[100];
Diag_Length_Type          Diag_Callbacks_Write_FD00_STATISTICS_DATA_Param2;
UINT8                     Diag_Callbacks_0D00_FACTORY_DATA_PROCESS_BYTE_Param1[100];
Diag_Length_Type          Diag_Callbacks_0D00_FACTORY_DATA_PROCESS_BYTE_Param2;
UINT8                     Diag_Callbacks_0D01_SIZE_OF_ECU_SERIAL_NUMBER_DATA_IDENTIFIER_Param1[100];
Diag_Length_Type          Diag_Callbacks_0D01_SIZE_OF_ECU_SERIAL_NUMBER_DATA_IDENTIFIER_Param2;
UINT8                     Diag_Callbacks_C002_SIZE_FOR_MULTI_DID_Param1[100];
Diag_Length_Type          Diag_Callbacks_C002_SIZE_FOR_MULTI_DID_Param2;
UINT8                     Diag_Callbacks_1100_CPU_LOAD_OF_DEVICE_Param1[100];
Diag_Length_Type          Diag_Callbacks_1100_CPU_LOAD_OF_DEVICE_Param2;
UINT8                     Diag_Callbacks_D404_SCROLLING_CTRL_OUTPUT_STATE_Param1[100];
Diag_Length_Type          Diag_Callbacks_D404_SCROLLING_CTRL_OUTPUT_STATE_Param2;
UINT8                     Diag_Callbacks_D406_LD_STATUS_Param1[100];
Diag_Length_Type          Diag_Callbacks_D406_LD_STATUS_Param2;
UINT8                     Diag_Callbacks_D401_FAN1_STATUS_Param1[100];
Diag_Length_Type          Diag_Callbacks_D401_FAN1_STATUS_Param2;
UINT8                     Diag_Callbacks_D402_FAN2_STATUS_Param1[100];
Diag_Length_Type          Diag_Callbacks_D402_FAN2_STATUS_Param2;
UINT8                     Diag_Callbacks_D407_NTC_RBIN_DATA_Param1[100];
Diag_Length_Type          Diag_Callbacks_D407_NTC_RBIN_DATA_Param2;
UINT8                     Diag_Callbacks_D408_DERATING_FACTOR_AND_TEMP_Param1[100];
Diag_Length_Type          Diag_Callbacks_D408_DERATING_FACTOR_AND_TEMP_Param2;
UINT8                     Diag_Callbacks_D410_DIAG_SCROLLING_INPUT_STATE_Param1[100];
Diag_Length_Type          Diag_Callbacks_D410_DIAG_SCROLLING_INPUT_STATE_Param2;
UINT8                     Diag_Callbacks_D411_INSTRUMENTATED_FRAMES_Param1[100];
Diag_Length_Type          Diag_Callbacks_D411_INSTRUMENTATED_FRAMES_Param2;
UINT8                     Diag_Callbacks_D4C6_SIGNALLING_ENG_DATA_Param1[100];
Diag_Length_Type          Diag_Callbacks_D4C6_SIGNALLING_ENG_DATA_Param2;
UINT8                     Diag_Callbacks_D4C7_TURN_IND_ENG_DATA_Param1[100];
Diag_Length_Type          Diag_Callbacks_D4C7_TURN_IND_ENG_DATA_Param2;
UINT8                     Diag_Callbacks_Read_Number_of_DTC_By_StatusMaskFaultMemory_Param1[100];
Diag_Length_Type          Diag_Callbacks_Read_Number_of_DTC_By_StatusMaskFaultMemory_Param2;
tParaFct0_Cmd             Diag_ParaFct0_Param1;
tNvmPara_CodingArea       Diag_ParaFct0_Param2;
uint8                     roDiag_Callbacks_NRC_Response_Param1;
uint8                     roDiag_Callbacks_ProgramingSessionAccepted_Param1;
UINT8                     Diag_Callbacks_02_CONTROL_DTC_OFF_Param1;
UINT8                     Diag_Callbacks_02_CONTROL_DTC_OFF_Param2[100];
Diag_Length_Type          Diag_Callbacks_02_CONTROL_DTC_OFF_Param3;
UINT8                     Diag_Callbacks_01_CONTROL_DTC_ON_Param1;
UINT8                     Diag_Callbacks_01_CONTROL_DTC_ON_Param2[100];
Diag_Length_Type          Diag_Callbacks_01_CONTROL_DTC_ON_Param3;
UINT8                     APPLI_ReadDataByIdentifier_Param1[100];
Diag_Length_Type          APPLI_ReadDataByIdentifier_Param2;
UINT8                     APPLI_ControlDTCSetting_Param1;
UINT8                     APPLI_ControlDTCSetting_Param2[3];
Diag_Length_Type          APPLI_ControlDTCSetting_Param3;
UINT8                     Diag_Callbacks_FD00_STATISTICS_DATA_Param1[100];
Diag_Length_Type          Diag_Callbacks_FD00_STATISTICS_DATA_Param2;
UINT8                     Diag_Callbacks_FD02_INTERNAL_ECU_SERIAL_NUMBER_DATA_IDENTIFIER_Param1[100];
Diag_Length_Type          Diag_Callbacks_FD02_INTERNAL_ECU_SERIAL_NUMBER_DATA_IDENTIFIER_Param2;
UINT8                     Diag_Callbacks_FD03_READ_ACTIVE_ALECS_Param1[100];
Diag_Length_Type          Diag_Callbacks_FD03_READ_ACTIVE_ALECS_Param2;
UINT8                     Diag_Callbacks_FD04_INTERNAL_SW_LABEL_Param1[100];
Diag_Length_Type          Diag_Callbacks_FD04_INTERNAL_SW_LABEL_Param2;
UINT8                     Diag_Callbacks_D400_PIXEL_LED_STATUS_Param1[100];
Diag_Length_Type          Diag_Callbacks_D400_PIXEL_LED_STATUS_Param2;
UINT8                     Diag_Callbacks_D405_LED_CH_OUTPUT_STATE_Param1[100];
Diag_Length_Type          Diag_Callbacks_D405_LED_CH_OUTPUT_STATE_Param2;
UINT8                     Diag_Callbacks_D409_CURRENT_BINNING_CLASS_Param1[100];
Diag_Length_Type          Diag_Callbacks_D409_CURRENT_BINNING_CLASS_Param2;
UINT8                     Diag_Callbacks_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS_Param1[100];
Diag_Length_Type          Diag_Callbacks_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS_Param2;
UINT8                     Diag_Callbacks_D4C5_LIGHTING_ENG_DATA_Param1[100];
Diag_Length_Type          Diag_Callbacks_D4C5_LIGHTING_ENG_DATA_Param2;
UINT8                     Diag_Callbacks_D4C8_BODY_HIGH_SENSOR_ENG_DATA_Param1[100];
Diag_Length_Type          Diag_Callbacks_D4C8_BODY_HIGH_SENSOR_ENG_DATA_Param2;
UINT8                     Diag_Callbacks_D4C9_ATTITUDE_ENG_DATA_Param1[100];
Diag_Length_Type          Diag_Callbacks_D4CB_LEVELLING_ENG_DATA_Param2;
UINT8                     Diag_Callbacks_D4CB_LEVELLING_ENG_DATA_Param1[100];
Diag_Length_Type          Diag_Callbacks_D4C9_ATTITUDE_ENG_DATA_Param2;
UINT8                     Diag_Callbacks_D4CD_RGB_LED_Param1[100];
Diag_Length_Type          Diag_Callbacks_D4CD_RGB_LED_Param2;
UINT8                     Diag_Callbacks_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES_Param1[100];
Diag_Length_Type          Diag_Callbacks_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES_Param2;
UINT8                     Diag_Callbacks_F080_AUTHENTIFICATION_ZONE_Param1[100];
Diag_Length_Type          Diag_Callbacks_F080_AUTHENTIFICATION_ZONE_Param2;
UINT8                     Diag_Callbacks_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION_Param1[100];
Diag_Length_Type          Diag_Callbacks_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION_Param2;
UINT8                     Diag_Callbacks_F08F_EMC_STANDARDIZATION_LABEL_Param1[100];
Diag_Length_Type          Diag_Callbacks_F08F_EMC_STANDARDIZATION_LABEL_Param2;
UINT8                     Diag_Callbacks_F186_Active_Diag_Session_Data_Identifier_Param1[100];
Diag_Length_Type          Diag_Callbacks_F186_Active_Diag_Session_Data_Identifier_Param2;
UINT8                     Diag_Callbacks_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER_Param1[100];
Diag_Length_Type          Diag_Callbacks_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER_Param2;
UINT8                     Diag_Callbacks_D421_RBIN_EEPROM_LMM_DIAGNOSIS_Param1[100];
Diag_Length_Type          Diag_Callbacks_D421_RBIN_EEPROM_LMM_DIAGNOSIS_Param2;
UINT8                     Diag_Callbacks_F0FE_IDENTIFICATION_ZONE_Param1[100];
Diag_Length_Type          Diag_Callbacks_F0FE_IDENTIFICATION_ZONE_Param2;
UINT8                     Diag_Callbacks_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER_Param1[100];
Diag_Length_Type          Diag_Callbacks_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER_Param2;
UINT8                     APPLI_SecurityAccess_Param1[100];
Diag_Length_Type          APPLI_SecurityAccess_Param2;
UINT8                     APPLI_RoutineControl_Param3[100];
Diag_Length_Type          APPLI_RoutineControl_Param4;
UINT8                     APPLI_ReadDTCInformation_Param1[100];
Diag_Length_Type          APPLI_ReadDTCInformation_Param2;
UINT8                     APPLI_RoutineControl_Param1;
UINT16                    APPLI_RoutineControl_Param2;
uint8                     Diag_Callbacks_DD00_LdActivation_Param1;
uint16                    Diag_Callbacks_DD00_LdActivation_Param2;
UINT8                     Diag_Callbacks_DD00_LdActivation_Param3[100];
uint8                     Diag_Callbacks_0301_RESET_CPU_LOAD_Param1;
uint16                    Diag_Callbacks_0301_RESET_CPU_LOAD_Param2;
UINT8                     Diag_Callbacks_0301_RESET_CPU_LOAD_Param3[100];
uint8                     Diag_Callbacks_DD01_PixelActivation_Param1;
uint16                    Diag_Callbacks_DD01_PixelActivation_Param2;
UINT8                     Diag_Callbacks_DD01_PixelActivation_Param3[100];
uint8                     Diag_Callbacks_DD04_Fan2Activation_Param1;
uint16                    Diag_Callbacks_DD04_Fan2Activation_Param2;
UINT8                     Diag_Callbacks_DD04_Fan2Activation_Param3[100];
uint8                     Diag_Callbacks_DD05_LvlStepperPosition_Param1;
uint16                    Diag_Callbacks_DD05_LvlStepperPosition_Param2;
UINT8                     Diag_Callbacks_DD05_LvlStepperPosition_Param3[100];
uint8                     Diag_Callbacks_DD07_SetScrollingCtrlOutput_Param1;
uint16                    Diag_Callbacks_DD07_SetScrollingCtrlOutput_Param2;
UINT8                     Diag_Callbacks_DD07_SetScrollingCtrlOutput_Param3[100];
uint8                     Diag_Callbacks_DF11_LvlStepperControl_Param1;
uint16                    Diag_Callbacks_DF11_LvlStepperControl_Param2;
UINT8                     Diag_Callbacks_DF11_LvlStepperControl_Param3[100];
uint8                     Diag_Callbacks_DF10_LvlReferencingRun_Param1;
uint16                    Diag_Callbacks_DF10_LvlReferencingRun_Param2;
UINT8                     Diag_Callbacks_DF10_LvlReferencingRun_Param3[100];
uint8                     Diag_Callbacks_DF13_LvlStepperControl_Param1;
uint16                    Diag_Callbacks_DF13_LvlStepperControl_Param2;
UINT8                     Diag_Callbacks_DF13_LvlStepperControl_Param3[100];
uint8                     Diag_Callbacks_DD06_LvlDCMotorPosition_Param1;
uint16                    Diag_Callbacks_DD06_LvlDCMotorPosition_Param2;
UINT8                     Diag_Callbacks_DD06_LvlDCMotorPosition_Param3[100];
uint8                     Diag_Callbacks_DF12_LvlStepperControl_Param1;
uint16                    Diag_Callbacks_DF12_LvlStepperControl_Param2;
UINT8                     Diag_Callbacks_DF12_LvlStepperControl_Param3[100];
uint8                     Diag_Callbacks_DD03_Fan1Activation_Param1;
uint16                    Diag_Callbacks_DD03_Fan1Activation_Param2;
uint8                     Diag_Callbacks_DD03_Fan1Activation_Param3[100];
UINT32                    APPLI_ClearDiagnosticInformation_Param1;
UINT8                     APPLI_ECUReset_Param1;
tsDiag_CodingParameters   Diag_Get_Coding_Param1;
UINT8                     APPLI_ReadMemoryByAddress_Param1[100];
Diag_Length_Type          APPLI_ReadMemoryByAddress_Param2;
uint8                     Diag_Callbacks_DF17_AFSControl_GetAfsStateAcceptanceStatus_Param1;
boolean                   Diag_Ld_Control_Param1;
uint8                     Diag_Ld_Control_Param2[100];
UINT8                     Diag_Callbacks_Read_DTC_Snapshot_Data_by_DTC_NumberFaultMemory_Param1[100];
Diag_Length_Type          Diag_Callbacks_Read_DTC_Snapshot_Data_by_DTC_NumberFaultMemory_Param2;
UINT8                     Diag_Callbacks_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS_Param1[100];
Diag_Length_Type          Diag_Callbacks_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS_Param2;
UINT8                     Diag_Callbacks_Read_by_MaskFaultMemory_Param1[100];
Diag_Length_Type          Diag_Callbacks_Read_by_MaskFaultMemory_Param2;
UINT8                     APPLI_DiagnosticSessionControl_Param1;
uint32                    Diag_GetVirtData_OsSystemCounter_Param1;
MsgContextType            ApplCmd_Rdm_SecurityAccess_Param1[100];
MsgContextType            ApplCmd_Rdm_StartSession_Param1[100];
uint8                     DiagR_CalcSrcAddressForVirtID_Param1[100];
tpfnGetVirtData           DiagR_CalcSrcAddressForVirtID_Param2[100];
uint32                    DiagR_CalcSrcAddressForVirtID_Param3;
uint32                    DiagR_CalcSrcAddressForVirtID_Param4;
uint8                     DiagR_CalcSrcAddressForVirtID_Param5;
uint8                     Diag_Callbacks_DFB5_InitAutomativLeveling_Param1[100];
uint8                     Diag_Callbacks_DFB5_InitAutomativLeveling_Param2;
uint8                     Diag_Callbacks_DFB5_InitAutomativLeveling_Param3;
uint16                    Diag_Callbacks_DFB5_InitAutomativLeveling_Param4;
UINT8                     Diag_Callbacks_DFB5_InitAutomativLeveling_Param5[100];
UINT8                     ApplCmd_Rdm_ReadMemByAddr_Param1[1];
Diag_Length_Type          ApplCmd_Rdm_ReadMemByAddr_Param2;
UINT8                     ApplCmd_Rdm_WriteMemByAddr_Param1[20];
Diag_Length_Type          ApplCmd_Rdm_WriteMemByAddr_Param2;
UINT8                     APPLI_WriteMemoryByAddress_Param1[100];
Diag_Length_Type          APPLI_WriteMemoryByAddress_Param2;


//=============================================================================
// Module function return value stubs
//=============================================================================
//Diag_Callbacks.c
uint8             AppDesc_LogZoneLastDataSearch_RetVal;
boolean           Diag_PowertrainCheck_RetVal;
boolean           Diag_IntegrationMode_RetVal;
boolean           roDiag_IntegrationMode_RetVal;
DIAG_status       APPLI_WriteDataByIdentifier_RetVal;
DIAG_status       Diag_Callbacks_Write_0D00_FACTORY_DATA_PROCESS_BYTE_RetVal;
DIAG_status       Diag_Callbacks_Write_D411_INSTRUMENTATED_FRAMES_RetVal;
DIAG_status       Diag_Callbacks_Write_FD00_STATISTICS_DATA_RetVal;
DIAG_status       Diag_Callbacks_0D00_FACTORY_DATA_PROCESS_BYTE_RetVal;
DIAG_status       Diag_Callbacks_0D01_SIZE_OF_ECU_SERIAL_NUMBER_DATA_IDENTIFIER_RetVal;
DIAG_status       Diag_Callbacks_C002_SIZE_FOR_MULTI_DID_RetVal;
DIAG_status       Diag_Callbacks_1100_CPU_LOAD_OF_DEVICE_RetVal;
DIAG_status       Diag_Callbacks_D404_SCROLLING_CTRL_OUTPUT_STATE_RetVal;
DIAG_status       Diag_Callbacks_D406_LD_STATUS_RetVal;
DIAG_status       Diag_Callbacks_D401_FAN1_STATUS_RetVal;
DIAG_status       Diag_Callbacks_D402_FAN2_STATUS_RetVal;
DIAG_status       Diag_Callbacks_D407_NTC_RBIN_DATA_RetVal;
DIAG_status       Diag_Callbacks_D408_DERATING_FACTOR_AND_TEMP_RetVal;
DIAG_status       Diag_Callbacks_D410_DIAG_SCROLLING_INPUT_STATE_RetVal;
DIAG_status       Diag_Callbacks_D411_INSTRUMENTATED_FRAMES_RetVal;
DIAG_status       Diag_Callbacks_D4C6_SIGNALLING_ENG_DATA_RetVal;
DIAG_status       Diag_Callbacks_D4C7_TURN_IND_ENG_DATA_RetVal;
boolean           Diag_ParaFct0_RetVal;
Diag_Length_Type  Diag_Callbacks_Read_Number_of_DTC_By_StatusMaskFaultMemory_RetVal;
DIAG_status       Diag_Callbacks_02_CONTROL_DTC_OFF_RetVal;
DIAG_status       Diag_Callbacks_01_CONTROL_DTC_ON_RetVal;
DIAG_status       APPLI_ControlDTCSetting_RetVal;
DIAG_status       APPLI_ClearDiagnosticInformation_RetVal;
DIAG_status       APPLI_ECUReset_RetVal;
DIAG_status       APPLI_ReadDataByIdentifier_RetVal;
DIAG_status       Diag_Callbacks_FD00_STATISTICS_DATA_RetVal;
DIAG_status       Diag_Callbacks_FD02_INTERNAL_ECU_SERIAL_NUMBER_DATA_IDENTIFIER_RetVal;
DIAG_status       Diag_Callbacks_FD03_READ_ACTIVE_ALECS_RetVal;
DIAG_status       Diag_Callbacks_FD04_INTERNAL_SW_LABEL_RetVal;
DIAG_status       Diag_Callbacks_D400_PIXEL_LED_STATUS_RetVal;
DIAG_status       Diag_Callbacks_D405_LED_CH_OUTPUT_STATE_RetVal;
DIAG_status       Diag_Callbacks_D409_CURRENT_BINNING_CLASS_RetVal;
DIAG_status       Diag_Callbacks_D422_LED_CHANNEL_OUTPUT_DIAGNOSIS_RetVal;
DIAG_status       Diag_Callbacks_D4C5_LIGHTING_ENG_DATA_RetVal;
DIAG_status       Diag_Callbacks_D4C8_BODY_HIGH_SENSOR_ENG_DATA_RetVal;
DIAG_status       Diag_Callbacks_D4C9_ATTITUDE_ENG_DATA_RetVal;
DIAG_status       Diag_Callbacks_D4CB_LEVELLING_ENG_DATA_RetVal;
DIAG_status       Diag_Callbacks_D4CD_RGB_LED_RetVal;
DIAG_status       Diag_Callbacks_E888_CONTEXT_GROUPS_LINKED_TO_DEFAULT_CODES_RetVal;
DIAG_status       Diag_Callbacks_D420_RBIN_NTC_FAILIURE_PER_LIGHT_FUNCTION_RetVal;
DIAG_status       Diag_Callbacks_F080_AUTHENTIFICATION_ZONE_RetVal;
DIAG_status       Diag_Callbacks_F08F_EMC_STANDARDIZATION_LABEL_RetVal;
DIAG_status       Diag_Callbacks_F186_Active_Diag_Session_Data_Identifier_RetVal;
DIAG_status       Diag_Callbacks_F18B_ECU_MANUFACTURING_DATE_DATA_IDENTIFIER_RetVal;
DIAG_status       Diag_Callbacks_D421_RBIN_EEPROM_LMM_DIAGNOSIS_RetVal;
DIAG_status       Diag_Callbacks_F0FE_IDENTIFICATION_ZONE_RetVal;
DIAG_status       Diag_Callbacks_F18C_ECU_SERIAL_NUMBER_DATA_IDENTIFIER_RetVal;
DIAG_status       APPLI_TesterPresent_RetVal;
DIAG_status       APPLI_SecurityAccess_RetVal;
DIAG_status       APPLI_RoutineControl_RetVal;
DIAG_status       Diag_Callbacks_DD00_LdActivation_RetVal;
DIAG_status       Diag_Callbacks_0301_RESET_CPU_LOAD_RetVal;
DIAG_status       Diag_Callbacks_DD01_PixelActivation_RetVal;
DIAG_status       Diag_Callbacks_DD04_Fan2Activation_RetVal;
DIAG_status       Diag_Callbacks_DD05_LvlStepperPosition_RetVal;
DIAG_status       Diag_Callbacks_DD07_SetScrollingCtrlOutput_RetVal;
DIAG_status       Diag_Callbacks_DF10_LvlReferencingRun_RetVal;
DIAG_status       APPLI_ReadMemoryByAddress_RetVal;
DIAG_status       Diag_Ld_Control_RetVal;
DIAG_status       Diag_Callbacks_DF11_LvlStepperControl_RetVal;
DIAG_status       Diag_Callbacks_Read_DTC_Snapshot_Data_by_DTC_NumberFaultMemory_RetVal;
DIAG_status       Diag_Callbacks_DF13_LvlStepperControl_RetVal;
DIAG_status       Diag_Callbacks_DD06_LvlDCMotorPosition_RetVal;
DIAG_status       Diag_Callbacks_DD03_Fan1Activation_RetVal;
DIAG_status       Diag_Callbacks_Read_by_MaskFaultMemory_RetVal;
DIAG_status       APPLI_DiagnosticSessionControl_RetVal;
DIAG_status       APPLI_ReadDTCInformation_RetVal;
DIAG_status       Diag_Callbacks_DF12_LvlStepperControl_RetVal;
DIAG_status       Diag_Callbacks_DFB5_InitAutomativLeveling_RetVal;
DIAG_status       APPLI_WriteMemoryByAddress_RetVal;
DIAG_status       Diag_Callbacks_FD01_READ_EEPROM_STRUCTURE_DIAGNOSIS_RetVal;
boolean           Diag_Callbacks_Check_If_Scrolling_Present_RetVal;
boolean           Diag_CodingDataValidation_RetVal;
void*             Diag_GetVirtData_OsSystemCounter_RetVal;
uint8             ApplCmd_Rdm_StartSession_RetVal;
uint8             ApplCmd_Rdm_SecurityAccess_RetVal;
uint8             DiagR_CalcSrcAddressForVirtID_RetVal;
uint8             ApplCmd_Rdm_ReadMemByAddr_RetVal;
uint8             ApplCmd_Rdm_WriteMemByAddr_RetVal;
uint32            Diag_Callback_CheckLastLightReq_Activated_RetVal;


#endif // TEST_2023_08_25_H_
