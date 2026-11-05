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
/// \file  RSens.c
///
/// \brief
///
/// \descr
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Cretu Vlad
///         mailTo:vladutioan.cretu[at]uc.marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "RSens.h"
#include "RSensRteAccess.h"

#include <Cfg/Cfg.h>
#include <Dem.h>

#ifndef UNIT_TEST
#include <Rte.h>
#endif

#include <UtilUtility.h>
#include <UtilDebounce.h>
#include <UtilMath.h>
#include <RteCommonTypes.h>
//=============================================================================
// definitions
//=============================================================================
// Error temperature for the led channels NTCs (0-3: LB, TI, DRL/POS, SBL) with 0.1 resolution
#define RSENS_ERROR_TEMP       1500
#define RSENS_INIT_TEMP        -400
#define RSENS_ERROR_ABSENT       0u
#define RSENS_NO_NTC_ERROR       1u
#define RSENS_PXLGR_INDEX        16u
#define RSENS_ERR_VFILTER        50u

#define RSENS_MIN_LIMIT_TEMP  -400
#define RSENS_MAX_LIMIT_TEMP  1500
#define RSENS_MIN_LIMIT_TEMP_PCB -500


#define RSENS_NTC_PCB_INDEX         4u    //  ECU_PCB INDEX
#define RSENS_NTC_SAT_INDEX         5u    //  MATRIX PCB INDEX    
#define RSENS_PCB_NTC_SC_GND        500u   //  threshold needed for shrt2gnd detection for the internal NTC
#define RSENS_SAT_NTC_SC_GND        196u   //  threshold needed for shrt2gnd detection for the SAT NTC (mV)
#define RSENS_PCB_NTC_SC_GND_TIMER  50    //  error counter used for shrt2gnd detection for the internal NTC


#define RSENS_TEMPERATURE_OFFSET    40u
#define RSENS_TEMPERATURE_SCALING   10u
#define RSENS_ERROR_SCALING         10u

//masks needed to manage ALEC and error setting
#define RSENS_SC_GND_MASK           0x02u
#define RSENS_SC_VBAT_MASK          0x04u
#define RSENS_OL_MASK               0x08u
#define RSENS_OVTEMP_MASK           0x10u
#define RSENS_ERRORSET_MASK         0xFFu

#define RSENS_NTCBIN_TOTAL          CFG_CntNtcTotal + CFG_BinningCnt
#define RSENS_TI_BINNING_INDEX      1u
#define RSENS_POS_DRL_BINNING_INDEX 2u
#define RSENS_REQUEST_FAN_ON        100u
#define RSENS_REQUEST_FAN_OFF       0u

#define RSENS_ALEC_NA               0u
#define RSENS_NUM_LMM_TEMP_PROFILE      8u
#define RSENS_NTC_TYPE_1                       0u
#define RSENS_NTC_TYPE_2                       1u
#define RSENS_NTC_TYPE_3                       2u
#define RSENS_LMM_TYPE_4                       3u

#define RSENS_NUM_NTC_TEMP_PROFILE             8u

#define RSENS_THZ_NTC_TYPE1                    1u
#define RSENS_THZ_NTC_TYPE2                    2u
#define RSENS_THZ_NTC_TYPE3                    3u
#define RSENS_THZ_LMMTYPE                      4u
#define RSENS_LMM_CODING_OFFSET                14u
#define RSENS_EEPROM_CODING_OFFSET             21u

// Rsens led_drvs channels
#define RSENS_LED_DRV01          0 
#define RSENS_LED_DRV02          1 
#define RSENS_LED_DRV03          2 
#define RSENS_LED_DRV04          3 
#define RSENS_LED_DRV05          4 
#define RSENS_LED_DRV06          5 
#define RSENS_LED_DRV07          6 
#define RSENS_LED_DRV08          7 
#define RSENS_LED_DRV09          8 
#define RSENS_LED_DRV10          9 
#define RSENS_LED_DRV11          10
#define RSENS_LED_DRV12          11

#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
#define RSENS_NR_LED_DRVS    12u
#else
#define RSENS_NR_LED_DRVS    4u
#endif

#define RSENS_SH2GND_PCB             0
#define RSENS_OP_PCB                 1
#define RSENS_SH2VB_PCB              2
#define RSENS_NR_PCB_ERROR           3

#define RSENS_REF_VOLTAGE                2560
#define RSENS_MAX_ADC_VAL                255 //8 bits

#define RSENS_REF_VOLTAGE_UNSIGNED               2560u
#define RSENS_MAX_ADC_VAL_UNSIGNED               255u //8 bits

// Conv formula for the mlc reg values
#define RSENS_ROWADC8BIT_TO_MV(x) ((x) * RSENS_REF_VOLTAGE) / RSENS_MAX_ADC_VAL

// Conv formula for the mlc reg values
#define RSENS_ROWADC8BIT_TO_MV_UNSIGNED(x) ((x) * RSENS_REF_VOLTAGE_UNSIGNED) / RSENS_MAX_ADC_VAL_UNSIGNED

#if (CFG_DEV_HOOK_EN == 1u)
// Pattern for inserting manual voltage on ECU NTC
#define RSENS_MANUAL_VOLTAGE_PATTERN 0x5AA5u
#endif

#define RSENS_INIT_LMM_BIN_VALUES \
        { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }

//=============================================================================
// variables
//=============================================================================
STATIC_AL const tNvmPara_CodingArea*  RSens_pCodingArea;
STATIC_AL uint8                       RSens_aucBinClassesArry[RSENS_LED_BINNING_CLASSES];
STATIC_AL tRsens_ErrorFlags           RSens_tNTCBINFlag[RSENS_NTCBIN_TOTAL];
STATIC_AL tRSens_CodingMode           RSens_eCodingMode = RSENS_CODINGMODE_VALID;
STATIC_AL tsRsens_InterpolationInfo   RSens_sInterpPoints = { 0 };
STATIC_AL tsRsens_InterpolationInfo   RSens_sInterpLmmPoints = { 0 };
STATIC_AL NtcTables                   *pasNtcTable = NULL_PTR;
STATIC_AL tsRte_NTCTemperature        RSens_sNTCTemperatureVal;
STATIC_AL tsRsens_NTCErrState         Rsens_asNtcThz_ErrState[12];
STATIC_AL tsRsens_NTCErrState         Rsens_asPCB_ErrState;
STATIC_AL TIMER                       Rsens_tiDebounceControlNtc[3][12];
STATIC_AL TIMER                       Rsens_tiDebounceControlPCB[RSENS_NR_PCB_ERROR];
STATIC_AL volatile tsRsens_NTCErrState         Rsens_asRCODBin_ErrState[RSENS_NR_LED_DRVS];
STATIC_AL uint16                       Rsens_ucCalculateBin_Semaphore = 0u;
STATIC_AL boolean                      RSens_boCodingValid = FALSE;
STATIC_AL tsRte_D409Binning            RSens_sBinningData;


// compiler switch in case Developer hooks mode is active
#if (CFG_DEV_HOOK_EN == 1u)
// Manual hook for ECU NTC
STATIC_AL volatile uint32 Rsens_udManualVoltageSet = 0;
//Variable used for inserting voltage needed for a specific temperature 
STATIC_AL volatile sint32 Rsens_udTestVoltageValue = 0;
#endif

//Coding parameter
STATIC_AL uint16 RSens_unCodShortGND;
STATIC_AL uint16 RSens_unCodShortBAT;
STATIC_AL uint16 RSens_unCodOpenLoad;


//Coding parameter
STATIC_AL uint16 RSens_unPCBShortGND;
STATIC_AL uint16 RSens_unPCBOpenLoad;


STATIC_AL sint16 RSens_nCodOverTemp;
STATIC_AL uint8  RSens_ucCodErrCnt;

//Error counter
STATIC_AL uint8  RSens_ucNTCBINErrOLCnt[RSENS_NTCBIN_TOTAL];
STATIC_AL uint8  RSens_ucNTCBINErrOverTempCnt;
STATIC_AL tsRteCodingParameters CodingParameters;

//Threshold for binning selection in descendig order
///============================================================================
// V(BinClass_Adc)/V(Rcod) = R2/R1+R2 = 82.5k/(82.5k + 21k) = 1/1.254 = 0.797
// Binning Class Voltage return function  (RSens_Rte_Read_Bin)
///============================================================================
// Typical binning resistor voltage value (at ECU pin) are:
// Binning 5: 2.788 V
// Binning 4: 2.354 V
// Binning 3: 1.929 V
// Binning 2: 1.585 V
// Binning 1: 1.267 V
// Binning 0: 1.018 V
// Calculate thresholds for binning resistor is midle point between 2 typicall binning resistor voltage values (1143 = (1.267 + 1.018) / 2 for Binning 0)

STATIC_AL CONST_AL uint16 Rsens_Binning_Thresholds[CFG_BIN_CLASS_CNT] = { 1143u, 1426u, 1757u, 2142u, 2571u, /*3413u*/ 3925u };
// According TCI info:
// Class 0: R = 1.0K ADC2: 001x xxxx
// Class 1: R = 2.2K ADC2: 010x xxxx
// Class 2: R = 3.3K ADC2: 011x xxxx
// Class 3: R = 5.6K ADC2: 100x xxxx
// Class 4: R = 10.0K ADC2: 101x xxxx
// Class 5: R = 21.0K ADC2: 110x xxxx
// Invalid: R = ??? ADC2: 000x xxxx/ 111x xxxx
STATIC_AL CONST_AL uint16 Rsense_unInvalidLmmVoltage_Low   = 320u;   // ( 0..31 )
STATIC_AL CONST_AL uint16 Rsense_unInvalidLmmVoltage_High  = 2230u;  // ( 224 .. 254)
STATIC_AL CONST_AL uint16 Rsense_unInvalidLmmVoltage_Max   = 2540u;  // 255 (MAXIMUM ADC value on 8 bit -> 2550mV - 10mV (1 bit))
STATIC_AL CONST_AL uint16 Rsens_Binning_Thresholds_Lmm[CFG_BIN_CLASS_CNT] = { 630u, 960u, 1270u, 1590u, 1910u, 2239u };
STATIC_AL CONST_AL uint8  Rsens_Binning_Classes[CFG_BIN_CLASS_CNT] = { (uint8)eBinningClass0, (uint8)eBinningClass1, (uint8)eBinningClass2, (uint8)eBinningClass3, (uint8)eBinningClass4, (uint8)eBinningClass5 };

// Allocated NTCs
STATIC_AL boolean RSens_abAllocatedNtcs[CFG_CntNtcExt];

STATIC_AL boolean RSens_aboNTCBinErrors[eMaxNTCBin_Inputs] = { 0u };

//Error debounce timers for all NTCs except the NTC_PCB (SC_GND/SHT2VBAT)
STATIC_AL tUtilDebounceControl RSens_sNTC_ErrorDebounce_Timers[CFG_CntNtcExt];

////Interpolation table used to calculate the PCB temperature 
////voltage in mV, temperature resolution is 0.1
STATIC_AL const tLinearPoint RSens_asPCB_voltage_temp[] =
{
  { 189,  1500 },
  { 300,  1300 },
  { 383,  1200 },
  { 492,  1100 },
  { 635,  1000 },
  { 822,   900 },
  { 2184,  500 },
  { 4378,    0 },
  { 4976, -400 }
};

#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
// Lmm
 STATIC_AL tasRte_MlcAdcResult asLmmAdc = { 0u };
 STATIC_AL tasRte_CtrlPxl_BinEEprom asEepromBinning = { 0u };
#endif

#if defined (UNIT_TEST)
 STATIC_AL boolean RSens_boResistor_Para_Test = FALSE;
#endif


//=============================================================================
// function prototypes
//=============================================================================

STATIC_AL void RSens_CalculateTemp_Thzs(void);
STATIC_AL void RSens_CalculateTemp_Pcb(void);
STATIC_AL void RSens_Calculate_Binning(uint8 ucBinIdx, boolean boInit);
STATIC_AL boolean Rsens_ParallelResistor_Exists(uint8 ucThermozoneID);
// Checks Errors for ntcs which are assigned to a thermozone
STATIC_AL void RSens_CheckErrFlagsNtc_Thzs(void);
STATIC_AL sint16 RSens_CalcInterpolationTemperatures(uint8 ucThermoZoneID, uint16 unNtcVoltage, NtcTables *pasNtcTableParam);
// Check error for RCODS which are assigned to LED_DRVs
STATIC_AL void RSens_CheckErrFlagsRCODs_LedDrvs(void);
// Checks Errors for pcb
STATIC_AL void RSens_CheckErrFlagsPCB(void);

STATIC_AL void RSens_OpenLoadHandlingPCB(boolean boErrorFlag);
STATIC_AL void RSens_Sh2GndHandlingPCB(boolean boErrorFlag);
STATIC_AL void RSens_UpdateNTCBINLMMErrors(void);

STATIC_AL sint16                      Rsens_GetTemperature(uint16 nVoltage, uint16 unVoltage0, uint16 unVoltage1, sint16 snTemperature0, sint16 snTemperature1);
STATIC_AL void                        Rsens_GetInterpolationNTCInputs(uint16 nVoltage, NtcTables *pasNtcTableParam, boolean boParSer);
STATIC_AL void                        RSens_CheckVoltageRange(uint16 ucActualVoltage, uint8 ucThermoZoneID);
STATIC_AL void                        RSens_TempLimitation(sint16 *snTemperature);
STATIC_AL uint8                       Rsens_CheckErrorBinning(uint16 unActualBinningVoltage, uint8 ucBinningIdx, uint8 ucCodBinIdx);

STATIC_AL void                        RSens_OpenloadHandlingNtcs(void);
STATIC_AL void                        RSens_Sh2GndHandlingNtcs(void);
STATIC_AL void                        RSens_Sh2VbatHandlingNtcs(void);

STATIC_AL void                        RSens_OpenloadHandlingRCODBin(void);
STATIC_AL void                        RSens_Sh2VbatHandlingRCODBin(void);
STATIC_AL void                        RSens_Sh2GndHandlingRCODBin(void);

STATIC_AL void                        RSens_Update_D409Diag(void);

//-----------------------------------------------------------------------------
/// \brief  Returns presence of parrallel resistor
///
/// \descr  Function that return the presence of a parallel resistor for external NTCs
///         return TRUE by default for binning resistors and FALSE by default for the 
///         internal NTC
/// \param  uc_VResistorIndex
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Rsens_ParallelResistor_Exists(uint8 ucThermozoneID)
{
  (void)ucThermozoneID;

  // set presence of parallel resistor as TRUE by default
  boolean boResistorPresent = TRUE;

#if defined (UNIT_TEST)
  // Unit Test Hook
  boResistorPresent = RSens_boResistor_Para_Test;
#endif

  return boResistorPresent;
}

//-----------------------------------------------------------------------------
/// \brief  Coding data notification
///
/// \descr  Function is called when coding data are available
///
/// \param  ulCmd
/// \param  ucIx
/// \param  pData
///
/// \return void
//-----------------------------------------------------------------------------
void  RSens_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
{
  RSens_pCodingArea = pData;

  if (eCmd == eParaFct0_CodingDataValid)
  {
    RSens_eCodingMode = RSENS_CODINGMODE_VALID;
  }
  else
  {
    RSens_eCodingMode = RSENS_CODINGMODE_INVALID;
  }
}
//-----------------------------------------------------------------------------
/// \brief  initialization of RSens
///
/// \descr
///
/// \param  -
///
/// \return void8
//-----------------------------------------------------------------------------
void RSens_Init(void)
{
  uint8             ucNTCIdx;
  uint8             ucBINIdx;

  // Read the coding params in order to see the binning assigned to the led drv
  (void)Rte_Read_CodM_Rsens_Para(&CodingParameters);

  RSens_boCodingValid = (CodingParameters.eCodingState == eParaFct0_CodingDataValid) ? TRUE : FALSE;

  if (RSens_boCodingValid != FALSE)
  {
    // Error thresholds for PCB
    RSens_unPCBShortGND = CodingParameters.psCodingParameters_Blocks->Thermo1.PCBNtc_ErrThresh.unPcbNtc_Sh2GndThreshold;
    RSens_unPCBOpenLoad = CodingParameters.psCodingParameters_Blocks->Thermo1.PCBNtc_ErrThresh.unPcbNtc_OpenLoad;

    //Error thresholds for external NTC
    RSens_unCodShortGND = CodingParameters.psCodingParameters_Blocks->Thermo1.ExtNTCsErrThresh_DebFilter.unNtc_Sh2GndThreshold;
    RSens_unCodShortBAT = CodingParameters.psCodingParameters_Blocks->Thermo1.ExtNTCsErrThresh_DebFilter.unNtc_Sh2Vbat;
    RSens_unCodOpenLoad = CodingParameters.psCodingParameters_Blocks->Thermo1.ExtNTCsErrThresh_DebFilter.unNtc_OpenLoad;

    // Assign the binning resistor from coding
    RSens_aucBinClassesArry[RSENS_LED_DRV01] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV01.DRV01_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV02] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV02.DRV02_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV03] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV03.DRV03_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV04] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV04.DRV04_ALLOCATED_RCOD;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
    RSens_aucBinClassesArry[RSENS_LED_DRV05] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV05.DRV05_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV06] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV06.DRV06_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV07] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV07.DRV07_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV08] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV08.DRV08_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV09] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV09.DRV09_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV10] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV10.DRV10_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV11] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV11.DRV11_ALLOCATED_RCOD;
    RSens_aucBinClassesArry[RSENS_LED_DRV12] = CodingParameters.psCodingParameters_Blocks->Led1.LedConfigDRV12.DRV12_ALLOCATED_RCOD;
#endif

    if (RSens_eCodingMode == RSENS_CODINGMODE_VALID)
    {

      for (ucBINIdx = 0; ucBINIdx < RSENS_LED_BINNING_CLASSES; ucBINIdx++)
      {
        RSens_Calculate_Binning(ucBINIdx, TRUE);
      }

    }
    else
    {
      //do nothing
    }

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
    for (uint8_fast ucIdx = 0u; ucIdx < LMMROW; ucIdx++)
    {
      // Take the lmm temp nodes from coding and transform them into mv
      RSens_Data_asnLMM[ucIdx][LMMCOL - 1u] = RSENS_ROWADC8BIT_TO_MV((sint16)CodingParameters.psCodingParameters_Blocks->LmmConfig.LMM_Config_Diagnosis.ucLTMP_LMM_NODES[ucIdx]);
    }
#endif
    //for D409 diag service
    for(uint8_fast ucIOIdx = 0U; ucIOIdx < CFG_NTC_BIN_CNT; ucIOIdx++)
    {
      RSens_sBinningData.aucBinClass[ucIOIdx] = 0xFFU;
      RSens_sBinningData.aunBinCurrent[ucIOIdx] = 0xFFFFU;
    }
  }
  else
  {
    // LDM Shall stay uncoded
  }
}



//-----------------------------------------------------------------------------
/// \brief Cycle runable to calculate external and pcb temparature
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void RSens_Cycle0(void)
{
  STATIC_UT(uint8, ucRsensProc_Cnt, 0u);

  uint8_fast ucLedDrvIdx;

  if (RSens_boCodingValid != FALSE)
  {
    for (ucLedDrvIdx = 0u; ucLedDrvIdx < RSENS_LED_BINNING_CLASSES; ucLedDrvIdx++)
    {
      RSens_Calculate_Binning((uint8)ucLedDrvIdx, FALSE);
    }

    RSens_CalculateTemp_Thzs();
    RSens_CalculateTemp_Pcb();
  }
  else
  {
    // LDM stays uncoded
  }

  RSens_UpdateNTCBINLMMErrors();
  RSens_CheckErrFlagsNtc_Thzs();
  RSens_CheckErrFlagsRCODs_LedDrvs();
  RSens_CheckErrFlagsPCB();
  RSens_Update_D409Diag();
}//PRQA S 5324 //function is maintainable and well structured 

//-----------------------------------------------------------------------------
/// \brief RSens_CalculateTemp_Thzs
///
/// \descr Interface which reads out all the ntcs soruces and types and the calculates the temperatures
///
/// \param  ucThermoZoneID
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void RSens_CalculateTemp_Thzs(void)
{
  uint16  unNtcVoltage;
  boolean boThermozoneValid = FALSE;
  boolean boThermzoneNotused = FALSE;
  uint8   ucNTCVal = 0u;
  uint8 ucNtcSourceLocal = 0u;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
  uint16 ucLmmAdcVal[CFG_MLC_Chip_Cnt] = { 0u };
#endif
  sint16 snThzLimitTemp[12u] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  for (uint8_least ucThermoZoneID = 0u; ucThermoZoneID < RSENS_THERMOZONE_COUNTER; ucThermoZoneID++)
  {
    ucNtcSourceLocal = CodingParameters.psCodingParameters_Blocks->Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[ucThermoZoneID];
    if (ucNtcSourceLocal != 0u)
    {
      ucNTCVal = ucNtcSourceLocal - 1u;
      boThermzoneNotused = FALSE;
    }
    else
    {
      boThermzoneNotused = TRUE;
    }

    if (boThermzoneNotused == FALSE)
    {
      // CHANGE THE MAPPING FOR THE NTC TYPE
      uint8 ucNTC_Bc_Type = CodingParameters.psCodingParameters_Blocks->Thermo1.NTC_Types.ucNtcType_Thermozones[ucThermoZoneID];
      // Check NTC Type
      switch (ucNTC_Bc_Type)
      {
      case RSENS_THZ_NTC_TYPE1:
        pasNtcTable = RSens_Data_apsnNTC[RSENS_NTC_TYPE_1];
        // Read the voltage at external NTCs - !!! This port has to be read when the update on IoHwAb is done.
        unNtcVoltage = RSens_Rte_Read_ExtNTC(ucNTCVal);
         RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID] = RSens_CalcInterpolationTemperatures((uint8)ucThermoZoneID, unNtcVoltage, pasNtcTable);
        RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_VALID;
        break;
      case RSENS_THZ_NTC_TYPE2:
        pasNtcTable = RSens_Data_apsnNTC[RSENS_NTC_TYPE_2];
        // Read the voltage at external NTCs - !!! This port has to be read when the update on IoHwAb is done.
        unNtcVoltage = RSens_Rte_Read_ExtNTC(ucNTCVal);
        RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID] = RSens_CalcInterpolationTemperatures((uint8)ucThermoZoneID, unNtcVoltage, pasNtcTable);
        RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_VALID;
        break;
      case RSENS_THZ_NTC_TYPE3:
        pasNtcTable = RSens_Data_apsnNTC[RSENS_NTC_TYPE_3];
        // Read the voltage at external NTCs - !!! This port has to be read when the update on IoHwAb is done.
        unNtcVoltage = RSens_Rte_Read_ExtNTC(ucNTCVal);
        RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID] = RSens_CalcInterpolationTemperatures((uint8)ucThermoZoneID, unNtcVoltage, pasNtcTable); // 1000u
        RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_VALID;

        break;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
      case RSENS_THZ_LMMTYPE:
        pasNtcTable = RSens_Data_apsnNTC[RSENS_LMM_TYPE_4];
        // Read the Lmmm reg value for the Lmm NTC
         (void)Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal(&asLmmAdc);

        // Check if SigQty is invalid
        if (asLmmAdc[ucNTCVal - RSENS_LMM_CODING_OFFSET].eQlty == CDD_MLC_QLTY_VALID)
        {
          // Take all the adc values for all the mlc chips
          ucLmmAdcVal[ucNTCVal - RSENS_LMM_CODING_OFFSET] = (uint16)asLmmAdc[ucNTCVal - RSENS_LMM_CODING_OFFSET].ucADC1Value;
          // Convert all the adc values for all the mlc chips
          unNtcVoltage = RSENS_ROWADC8BIT_TO_MV_UNSIGNED(ucLmmAdcVal[ucNTCVal - RSENS_LMM_CODING_OFFSET]);
          // Calculate the temperature
          RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID] = RSens_CalcInterpolationTemperatures((uint8)ucThermoZoneID, unNtcVoltage, pasNtcTable);
          RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_VALID;
        }
        else
        {
          // Put the highest temperature & sigqty invalid
          RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID] = 1500; //0.1% resolution
          RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_SNA;
        }

        break;
#endif
      default:
        RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID] = RSENS_INIT_TEMP;
        RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_VALID;
        break;
      }
      // Check errors functions
      RSens_CheckVoltageRange(unNtcVoltage, (uint8)ucThermoZoneID);
    }
    else
    {
      RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID] = RSENS_INIT_TEMP;
      RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_SNA;
    }

    // Hardcoded until errors are implemented
    RSens_sNTCTemperatureVal.eErrTypeA[ucThermoZoneID] = (uint8)E_TYPE_PASSED; //TBD

      // min/max temperature limitation
    RSens_TempLimitation(&RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID]);
  }
  
  
  (void)Rte_Write_RSens_ThermzoneTemperatures(&RSens_sNTCTemperatureVal);

}

//-----------------------------------------------------------------------------
/// \brief RSens_CheckVoltageRange
/// 
/// \descr Checks the voltage range to set the corresponding error flag for DTC setting/desetting
///
/// \param  ucActualVoltage - actual voltage for specific NTC
///         ucThermoZoneID - thermozone index
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void RSens_CheckVoltageRange(uint16 ucActualVoltage, uint8 ucThermoZoneID)
{
  // Check errors functions
  if (ucActualVoltage < RSens_unCodShortGND)
  {
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boSh2Gnd   = TRUE;
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boSh2Vbat = FALSE;
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boOpenload = FALSE;
    RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_INVALID;
  }
  else if (ucActualVoltage > RSens_unCodShortBAT)
  {
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boSh2Vbat  = TRUE;
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boOpenload = FALSE;
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boSh2Gnd = FALSE;
    RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_INVALID;
  }
  else if ((ucActualVoltage > RSens_unCodOpenLoad) && (ucActualVoltage < RSens_unCodShortBAT))
  {
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boOpenload = TRUE;
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boSh2Gnd = FALSE;
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boSh2Vbat = FALSE;
    RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_INVALID;
  }
  else
  {
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boOpenload = FALSE;
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boSh2Gnd = FALSE;
    Rsens_asNtcThz_ErrState[ucThermoZoneID].boSh2Vbat = FALSE;
    RSens_sNTCTemperatureVal.eSigQty[ucThermoZoneID] = SIG_VALID;
  }
}

//-----------------------------------------------------------------------------
/// \brief RSens_TempLimitation
/// 
/// \descr Checks if the temperature is between the correct range, if not limit it
///
/// \param  snTemperature - actual temperature value for the current thermozone
///
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void RSens_TempLimitation(sint16 *snTemperature)
{
  // min/max temperature limitation
  if (*snTemperature < RSENS_MIN_LIMIT_TEMP)
  {
    *snTemperature = RSENS_MIN_LIMIT_TEMP;
  }
  else if (*snTemperature > RSENS_MAX_LIMIT_TEMP)
  {
    *snTemperature = RSENS_MAX_LIMIT_TEMP;
  }
  else
  {
    //do nothing
  }
}

//-----------------------------------------------------------------------------
/// \brief RSens_CalcInterpolationTemperatures
/// 
/// \descr Checks if paralel resistor exists and then calculates the temperatures based on the interpolation 
//         between the voltage and the temperatures.
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL sint16 RSens_CalcInterpolationTemperatures(uint8 ucThermoZoneID, uint16 unNtcVoltage, NtcTables *pasNtcTableParam)
{
  tsRte_NTCTemperature sNTCTemperatureVal;

  sint16 snThzTemperatures[12];

  // Check if parallel resistors exists
  if (Rsens_ParallelResistor_Exists(ucThermoZoneID) != FALSE)
  {
    // Parallel resistor exists
    Rsens_GetInterpolationNTCInputs(unNtcVoltage, pasNtcTableParam, TRUE);
  }
  else
  {
    // Serial resistor exists
    Rsens_GetInterpolationNTCInputs(unNtcVoltage, pasNtcTableParam, FALSE);
  }

  // Calc temperatures
  sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID] = Rsens_GetTemperature(unNtcVoltage, (uint16)RSens_sInterpPoints.snVoltage0, (uint16)RSens_sInterpPoints.snVoltage1, RSens_sInterpPoints.snTemp0 * 10, RSens_sInterpPoints.snTemp1 * 10);
  
  snThzTemperatures[ucThermoZoneID]                            = sNTCTemperatureVal.s16_NTCTemperatureCelsius[ucThermoZoneID];

  // Return the calculated temperature
  return snThzTemperatures[ucThermoZoneID];
}
//-----------------------------------------------------------------------------
/// \brief Function that calculates the temperature of the PCB
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void RSens_CalculateTemp_Pcb(void)
{
  // calculate PCB temperature
  uint16 lNtcPcbVoltage;
  sint16 nPcbTemp;
  STATIC_UT(tsRte_PcbTemperatureMsg, sPCBTemperatureVal, { 0 });
  teRSens_SigQty eErrTypeA;

  // compiler switch in case Developer hooks mode is active
#if (CFG_DEV_HOOK_EN == 1u)
  //Rsens_udManualVoltageSet -> When this variable is equal with the voltage pattern the testers can introduce wanted voltage values for testing purposes.
  //                                  -> Otherwise the voltage is taken from IoHwAb module.
  if (Rsens_udManualVoltageSet == RSENS_MANUAL_VOLTAGE_PATTERN)
  {
    lNtcPcbVoltage = (uint16)Rsens_udTestVoltageValue;
  }
  else
  {
    (void)RSens_Rte_Read_PCBNTC(&lNtcPcbVoltage);
  }
#else
  (void)RSens_Rte_Read_PCBNTC(&lNtcPcbVoltage);
#endif

  // Check errors functions
  if (lNtcPcbVoltage <= RSens_unPCBShortGND)
  {
    Rsens_asPCB_ErrState.boSh2Gnd = TRUE;
    Rsens_asPCB_ErrState.boSh2Vbat = FALSE;
    Rsens_asPCB_ErrState.boOpenload = FALSE;
    eErrTypeA = eRSENS_SIG_INVALID;
  }
  else if (lNtcPcbVoltage > RSens_unPCBOpenLoad)
  {
    Rsens_asPCB_ErrState.boOpenload = TRUE;
    Rsens_asPCB_ErrState.boSh2Gnd = FALSE;
    Rsens_asPCB_ErrState.boSh2Vbat = FALSE;
    eErrTypeA = eRSENS_SIG_INVALID;
  }
  else
  {
    Rsens_asPCB_ErrState.boOpenload = FALSE;
    Rsens_asPCB_ErrState.boSh2Gnd = FALSE;
    Rsens_asPCB_ErrState.boSh2Vbat = FALSE;
    eErrTypeA = eRSENS_SIG_VALID;
  }


  if (eErrTypeA == eRSENS_SIG_VALID)
  {
    // No Error
    nPcbTemp = (sint16)UtilMath_LinearInterpolate(RSens_asPCB_voltage_temp, (sint32)countof(RSens_asPCB_voltage_temp), (sint16)lNtcPcbVoltage);

    sPCBTemperatureVal.nVal = nPcbTemp;
    sPCBTemperatureVal.eQty = SIG_VALID;

    // min/max temperature limitation
    if (sPCBTemperatureVal.nVal < RSENS_MIN_LIMIT_TEMP)
    {
      sPCBTemperatureVal.nVal = RSENS_MIN_LIMIT_TEMP;
    }
    else if (sPCBTemperatureVal.nVal > RSENS_MAX_LIMIT_TEMP)
    {
      sPCBTemperatureVal.nVal = RSENS_MAX_LIMIT_TEMP;
    }
    else
    {
      //do nothing
    }

  }
  else
  {
    // Error present
    sPCBTemperatureVal.nVal = RSENS_ERROR_TEMP;
    sPCBTemperatureVal.eQty = SIG_INVALID;
  }

 (void)RSens_Rte_Write_PcbTemperature(&sPCBTemperatureVal);

}
//-----------------------------------------------------------------------------
/// \brief Function that clasifies the binnig resistors into binning classes
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void RSens_Calculate_Binning(uint8 ucBinIdx, boolean boInit)
{
  tsRte_Binning0     sBinningClass;
  uint16             unBinningVoltage;
  uint8              ucCodBinIndx = 0u;
  uint8              ucErrtype;
  uint8              ucBinningClassIdx;

  STATIC_UT(boolean, boLMMBinUpdateStatus[12], RSENS_INIT_LMM_BIN_VALUES);
  boolean boUpdateBinning = FALSE;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
  tsRte_MtxEeprom_ErrStatus sMtxEepromStatus = { FALSE, FALSE };
#endif
  sBinningClass.eSigQty = SIG_SNA;
  sBinningClass.ucBinning = 0U;

  ucCodBinIndx = RSens_aucBinClassesArry[ucBinIdx] - 1u;

  if (boInit != FALSE)
  {
    // Read the voltage for the led_drvs
    if (ucCodBinIndx < RSENS_LMM_CODING_OFFSET)
    {
      //Voltage is read from IoHwAb
      unBinningVoltage = RSens_Rte_Read_ExtNTC(ucCodBinIndx);
      boUpdateBinning = TRUE;
    }
    else
    {
      // skip
    }
  }
  else
  {
    if ((boLMMBinUpdateStatus[ucBinIdx] == FALSE) && (ucCodBinIndx != RSENS_EEPROM_CODING_OFFSET) && (ucCodBinIndx >= RSENS_LMM_CODING_OFFSET))
    {
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)

      // Read the MLC Voltage
      (void)Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal(&asLmmAdc);

      if (asLmmAdc[ucCodBinIndx - RSENS_LMM_CODING_OFFSET].eQlty == CDD_MLC_QLTY_VALID)
      {
        // Take all the adc values for all the mlc chips
        // Convert all the adc values for all the mlc chips
        unBinningVoltage = RSENS_ROWADC8BIT_TO_MV_UNSIGNED(asLmmAdc[ucCodBinIndx - RSENS_LMM_CODING_OFFSET].ucADC2Value);
        boLMMBinUpdateStatus[ucBinIdx] = TRUE;
      }
      else
      {
        // do nothing
        unBinningVoltage = 0xFFFFu;
      }

      boUpdateBinning = TRUE;
#endif
    }
    else if((boLMMBinUpdateStatus[ucBinIdx] == FALSE) && (ucCodBinIndx == RSENS_EEPROM_CODING_OFFSET))
    {
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)

      // EEPROM - TBD
      (void)Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus(&sMtxEepromStatus);

      if ( (sMtxEepromStatus.boEepromNoAccessFault != FALSE) || (sMtxEepromStatus.boEepromWrngChksumFault != FALSE) )
      {
        //eeprom error, do not read data
        unBinningVoltage = 0xFFFFu;
      }
      else
      {
        //no eeprom error -> read RTE port with binning values

        (void)Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal(&asEepromBinning);

        // Init Voltage - Error
        unBinningVoltage = 0x0u;

        if ((asEepromBinning[ucBinIdx].ucBinning <= (uint8)eBinningClass5) && (asEepromBinning[ucBinIdx].eSigQty == SIG_VALID))
        {
          unBinningVoltage = (Rsens_Binning_Thresholds[asEepromBinning[ucBinIdx].ucBinning] > 0u) ? Rsens_Binning_Thresholds[asEepromBinning[ucBinIdx].ucBinning] - 1u : 0u;
        }
        else
        {
          // Kep searching
        }

        boLMMBinUpdateStatus[ucBinIdx] = TRUE;
        boUpdateBinning = TRUE;
      }
#endif
    }
    else
    {
      // skip
    }
  }

  if (boUpdateBinning != FALSE)
  {

    // Check errors functions
    ucErrtype = Rsens_CheckErrorBinning(unBinningVoltage, ucBinIdx, ucCodBinIndx);

    // No error
    if (ucErrtype == (uint8)E_TYPE_PASSED)
    {
      for (ucBinningClassIdx = 0u; ucBinningClassIdx < CFG_BIN_CLASS_CNT; ucBinningClassIdx++)
      {
        // Based on the RCOD selector, get the valid binning thresholds (LMM or EXTIN)
        uint16 unBinningValThreshold = ((ucCodBinIndx != RSENS_EEPROM_CODING_OFFSET) && (ucCodBinIndx >= RSENS_LMM_CODING_OFFSET)) ? Rsens_Binning_Thresholds_Lmm[ucBinningClassIdx] : Rsens_Binning_Thresholds[ucBinningClassIdx];
        //check voltage against binning class thresholds starting with the greatest threshold
        if ((unBinningVoltage < unBinningValThreshold))
        {
          //if voltage is greater than the threshold assign the corespunding class
          sBinningClass.ucBinning = Rsens_Binning_Classes[ucBinningClassIdx];
          break;
        }
      }
      sBinningClass.eSigQty = SIG_VALID;
    }
    else
    {
      sBinningClass.ucBinning = (uint8)eBinningClassErr;
      sBinningClass.eSigQty = SIG_INVALID;
    }


    (void)RSens_RteAccess_Write_BinnigClasses(ucBinIdx, &sBinningClass);
  }
} //PRQA S 5336 // architecture and readability

//-----------------------------------------------------------------------------
/// \brief Rsens_CheckErrorBinning
///
/// \descr Function that check voltage range for binning classes, set the specific error flag and return the error status
///
/// \param  uint16 - actual binning voltage
///         uint16 - binning index
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 Rsens_CheckErrorBinning(uint16 unActualBinningVoltage,uint8 ucBinningIdx, uint8 ucCodBinIdx)
{
  uint8              ucErrtype;

  // Select the error thresholds based on Rcod (LMM or External input)
  uint16 unShToGndVal  = ((ucCodBinIdx != RSENS_EEPROM_CODING_OFFSET) && (ucCodBinIdx >= RSENS_LMM_CODING_OFFSET)) ? Rsense_unInvalidLmmVoltage_Low  : RSens_unCodShortGND;
  uint16 unShToVbatVal = ((ucCodBinIdx != RSENS_EEPROM_CODING_OFFSET) && (ucCodBinIdx >= RSENS_LMM_CODING_OFFSET)) ? Rsense_unInvalidLmmVoltage_Max  : RSens_unCodShortBAT;
  uint16 unOLVal       = ((ucCodBinIdx != RSENS_EEPROM_CODING_OFFSET) && (ucCodBinIdx >= RSENS_LMM_CODING_OFFSET)) ? Rsense_unInvalidLmmVoltage_High : RSens_unCodOpenLoad;

  // Check errors functions
  if (unActualBinningVoltage < unShToGndVal)
  {
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Gnd = TRUE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Vbat = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boOpenload = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].eSigQty = eRSENS_SIG_INVALID;
    ucErrtype = (uint8)E_TYPE_SNA;
  }
  else if ((unActualBinningVoltage > unShToVbatVal) && (unActualBinningVoltage != (uint16)0xFFFF))
  {
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Vbat = TRUE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boOpenload = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Gnd = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].eSigQty = eRSENS_SIG_INVALID;
    ucErrtype = (uint8)E_TYPE_SNA;
  }
  else if ((unActualBinningVoltage > unOLVal) && (unActualBinningVoltage < unShToVbatVal))
  {
    Rsens_asRCODBin_ErrState[ucBinningIdx].boOpenload = TRUE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Gnd = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Vbat = FALSE; 
    Rsens_asRCODBin_ErrState[ucBinningIdx].eSigQty = eRSENS_SIG_INVALID;
    ucErrtype = (uint8)E_TYPE_SNA;
  }
  else if (unActualBinningVoltage == (uint16)0xFFFF)
  {
    // no error voltage ok
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Gnd = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Vbat = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boOpenload = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].eSigQty = eRSENS_SIG_VALID;
    ucErrtype = (uint8)E_TYPE_SNA;
  }
  else
  {
    // no error voltage ok
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Gnd = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boSh2Vbat = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].boOpenload = FALSE;
    Rsens_asRCODBin_ErrState[ucBinningIdx].eSigQty = eRSENS_SIG_VALID;
    ucErrtype = (uint8)E_TYPE_PASSED;
  }
  return ucErrtype;
}




//-----------------------------------------------------------------------------
/// \brief Rsens_GetTemperature
///
/// \descr
///
/// \param  nVoltage
/// \param  unVoltage0
/// \param  unVoltage1
/// \param  snTemperature0
/// \param  snTemperature1
///
/// \return STATIC_AL sint16
//-----------------------------------------------------------------------------
STATIC_AL sint16 Rsens_GetTemperature(uint16 nVoltage, uint16 unVoltage0, uint16 unVoltage1, sint16 snTemperature0, sint16 snTemperature1)
{
  return (snTemperature0 + ((snTemperature1 - snTemperature0) * (sint16)((sint16)nVoltage - (sint16)unVoltage0)) / (sint16)((sint16)unVoltage1 - (sint16)unVoltage0));
}

//-----------------------------------------------------------------------------
/// \brief Rsens_GetInterpolationNTCInputs
///
/// \descr
///
/// \param  psInterpPoints
/// \param  
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void Rsens_GetInterpolationNTCInputs(uint16 nVoltage, NtcTables *pasNtcTableParam, boolean boParSer)
{
  // Paralel resitor present/not present
  uint8 ucColumnSelector = (boParSer != FALSE) ? 1u : 2u;
  uint8 ucIdx = 0u;

  for (ucIdx = 0u; ucIdx < RSENS_NUM_NTC_TEMP_PROFILE; ucIdx++)
  {
    if ((sint16)nVoltage > (*(pasNtcTableParam))[ucIdx][ucColumnSelector] )
    {
      if (ucIdx == 0u)
      {
        RSens_sInterpPoints.snTemp0    = -40;
        RSens_sInterpPoints.snVoltage0 = 5000;
        RSens_sInterpPoints.snTemp1    = (*(pasNtcTableParam))[ucIdx][0u];
        RSens_sInterpPoints.snVoltage1 = (*(pasNtcTableParam))[ucIdx][ucColumnSelector];
      }
      else
      {
        RSens_sInterpPoints.snTemp0    =  (*(pasNtcTableParam))[ucIdx - 1u][0u];
        RSens_sInterpPoints.snVoltage0 =  (*(pasNtcTableParam))[ucIdx - 1u][ucColumnSelector];
        RSens_sInterpPoints.snTemp1    =  (*(pasNtcTableParam))[ucIdx     ][0u];
        RSens_sInterpPoints.snVoltage1 =  (*(pasNtcTableParam))[ucIdx     ][ucColumnSelector];
      }
      break;
    }
  }

  if (ucIdx == RSENS_NUM_NTC_TEMP_PROFILE)
  {
    RSens_sInterpPoints.snTemp0    = (*(pasNtcTableParam))[RSENS_NUM_NTC_TEMP_PROFILE - 1u][0u];               
  //  //(*pasNtcTable)[RSENS_NUM_TEMP_PROFILE - 1u][0u];                
  //  //*(*(pasNtcTable + RSENS_NUM_TEMP_PROFILE - 1u) + 0u);
    RSens_sInterpPoints.snVoltage0 = (*(pasNtcTableParam))[RSENS_NUM_NTC_TEMP_PROFILE - 1u][ucColumnSelector]; 
  //  //(*pasNtcTable)[RSENS_NUM_TEMP_PROFILE - 1u][ucColumnSelector];  
  //  //*(*(pasNtcTable + RSENS_NUM_TEMP_PROFILE - 1u) + ucColumnSelector);
    RSens_sInterpPoints.snTemp1    = 150;
    RSens_sInterpPoints.snVoltage1 = 0;
  }
  else
  {
    // Skip
  }
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void RSens_CheckErrFlagsNtc_Thzs(void) 
{
  STATIC_UT(uint8, ucIdx, 0u);

  if (ucIdx == 1u)
  {
    RSens_Sh2GndHandlingNtcs();
  }
  else  if (ucIdx == 3u)
  {
    RSens_Sh2VbatHandlingNtcs();
  }
  else if (ucIdx == 5u)
  {
    RSens_OpenloadHandlingNtcs();
  }
  else
  {
  }

  ucIdx = (ucIdx == 6u) ? 0u : (ucIdx + 1u);
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void RSens_Sh2GndHandlingNtcs(void)
{
  uint8_fast ucThzIdx;
  // Check all the thz ios
  for (ucThzIdx = 0u; ucThzIdx < 12u; ucThzIdx++)
  {
    if (Rsens_asNtcThz_ErrState[ucThzIdx].boSh2Gnd != FALSE)
    {
      Rte_Call_DemPrj_ReportErrorStatus((uint16)NTCs_SC_GND, DEM_EVENT_STATUS_FAILED);
      break;
    }
  }

  // After all the indexes are checked if theres no error reset it
  if (ucThzIdx == 12u)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)NTCs_SC_GND, DEM_EVENT_STATUS_PASSED);
  }

}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void RSens_Sh2VbatHandlingNtcs(void)
{
  uint8_fast ucThzIdx;
  // Check all the thz ios
  for (ucThzIdx = 0u; ucThzIdx < 12u; ucThzIdx++)
  {
    if (Rsens_asNtcThz_ErrState[ucThzIdx].boSh2Vbat != FALSE)
    {
      Rte_Call_DemPrj_ReportErrorStatus((uint16)NTCs_SC_BAT, DEM_EVENT_STATUS_FAILED);
      break;
    }
  }

  if (ucThzIdx == 12u)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)NTCs_SC_BAT, DEM_EVENT_STATUS_PASSED);
  }

}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void RSens_OpenloadHandlingNtcs(void)
{
  uint8_fast ucThzIdx;
  // Check all the thz ios
  for (ucThzIdx = 0u; ucThzIdx < 12u; ucThzIdx++)
  {
    if (Rsens_asNtcThz_ErrState[ucThzIdx].boOpenload != FALSE)
    {
      Rte_Call_DemPrj_ReportErrorStatus((uint16)NTCs_OL, DEM_EVENT_STATUS_FAILED);
      break;
    }
  }

  if (ucThzIdx == 12u)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)NTCs_OL, DEM_EVENT_STATUS_PASSED);
  }
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void RSens_CheckErrFlagsPCB(void)
{
  //check the error flag for short to ground for the PCB and set / deset the corresponding DTC
  RSens_Sh2GndHandlingPCB(Rsens_asPCB_ErrState.boSh2Gnd);
  //check the error flag for open load for the PCB and set / deset the corresponding DTC
  RSens_OpenLoadHandlingPCB(Rsens_asPCB_ErrState.boOpenload); 
}

//-----------------------------------------------------------------------------
/// \brief RSens_CheckErrorFlags_PCB
///
/// \descr The funcion is checking the error flag for short to ground for 
///        the PCB and set/deset the corresponding DTC
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void RSens_Sh2GndHandlingPCB(boolean boErrorFlag)
{
  switch (boErrorFlag)
  {
  case TRUE:
    Rte_Call_DemPrj_ReportErrorStatus((uint16)NTC_PCB_E_SC_GND, DEM_EVENT_STATUS_FAILED);
    break;
  case FALSE:
    Rte_Call_DemPrj_ReportErrorStatus((uint16)NTC_PCB_E_SC_GND, DEM_EVENT_STATUS_PASSED);
    break;
  default:
     Rte_Call_DemPrj_ReportErrorStatus((uint16)NTC_PCB_E_SC_GND, DEM_EVENT_STATUS_FAILED);
     break;
  }
}

//-----------------------------------------------------------------------------
/// \brief RSens_CheckErrorFlags_PCB
///
/// \descr The funcion is checking the error flag for open load for 
///        the PCB and set/deset the corresponding DTC
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void RSens_OpenLoadHandlingPCB(boolean boErrorFlag)
{
  switch (boErrorFlag)
  {
  case TRUE:
    Rte_Call_DemPrj_ReportErrorStatus((uint16)NTC_PCB_E_OPENLOAD, DEM_EVENT_STATUS_FAILED);
    break;
  case FALSE:
    Rte_Call_DemPrj_ReportErrorStatus((uint16)NTC_PCB_E_OPENLOAD, DEM_EVENT_STATUS_PASSED);
    break;
  default:
    Rte_Call_DemPrj_ReportErrorStatus((uint16)NTC_PCB_E_OPENLOAD, DEM_EVENT_STATUS_FAILED);
    break;
  }
}



//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void RSens_CheckErrFlagsRCODs_LedDrvs(void)
{
  //static uint8 ucIdx = 0u;
  STATIC_UT(uint8, ucIdx, 0u);

  if (ucIdx == 0u)
  {
    RSens_Sh2GndHandlingRCODBin();
  }
  else  if (ucIdx == 2u)
  {
    RSens_Sh2VbatHandlingRCODBin();
  }
  else if (ucIdx == 4u)
  {
    RSens_OpenloadHandlingRCODBin();
  }
  else
  {
  }

  ucIdx = (ucIdx == 6u) ? 0u : (ucIdx + 1u);
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void RSens_Sh2GndHandlingRCODBin(void)
{
  uint8_fast ucLedDrvIdx = 0u;

  // Check all the thz ios
  for (ucLedDrvIdx = 0u; ucLedDrvIdx < (uint8_fast)RSENS_NR_LED_DRVS; ucLedDrvIdx++)
  {
    if (Rsens_asRCODBin_ErrState[ucLedDrvIdx].boSh2Gnd != FALSE)
    {
      Rte_Call_DemPrj_ReportErrorStatus((uint16)RCODs_SC_GND, DEM_EVENT_STATUS_FAILED);
      break;
    }
  }

  // After all the indexes are checked if theres no error reset it
  if (ucLedDrvIdx == RSENS_NR_LED_DRVS)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)RCODs_SC_GND, DEM_EVENT_STATUS_PASSED);
  }

}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void RSens_Sh2VbatHandlingRCODBin(void)
{
  uint8_fast ucLedDrvIdx = 0u;

  // Check all the thz ios
  for (ucLedDrvIdx = 0u; ucLedDrvIdx < RSENS_NR_LED_DRVS; ucLedDrvIdx++)
  {
    if (Rsens_asRCODBin_ErrState[ucLedDrvIdx].boSh2Vbat != FALSE)
    {
      Rte_Call_DemPrj_ReportErrorStatus((uint16)RCODs_SC_BAT, DEM_EVENT_STATUS_FAILED);
      break;
    }
  }

  if (ucLedDrvIdx == RSENS_NR_LED_DRVS)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)RCODs_SC_BAT, DEM_EVENT_STATUS_PASSED);
  }

}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void RSens_OpenloadHandlingRCODBin(void)
{
  uint8_fast ucLedDrvIdx = 0u;
  // Check all the thz ios
  for (ucLedDrvIdx = 0u; ucLedDrvIdx < RSENS_NR_LED_DRVS; ucLedDrvIdx++)
  {
    if (Rsens_asRCODBin_ErrState[ucLedDrvIdx].boOpenload != FALSE)
    {
      Rte_Call_DemPrj_ReportErrorStatus((uint16)RCODs_OL, DEM_EVENT_STATUS_FAILED);
      break;
    }
  }

  if (ucLedDrvIdx == RSENS_NR_LED_DRVS)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)RCODs_OL, DEM_EVENT_STATUS_PASSED);
  }
}

//-----------------------------------------------------------------------------
/// \brief  RSens_UpdateNTCBINLMMErrors
///
/// \descr  The function gathers the binning and ntc errors for all NTC source type
///         which are sent to the diagnosis 
///
/// \param  -
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void RSens_UpdateNTCBINLMMErrors(void)
{
  uint8 ucNtcSourceLocal = 0u;
  uint8 ucCodBinIndx = 0u;

  // Check NTCs
  // Check Thermozones errors
  for (uint8 ucThermozonesId = 0u; ucThermozonesId < 12u; ucThermozonesId++)
  {
    ucNtcSourceLocal = CodingParameters.psCodingParameters_Blocks->Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[ucThermozonesId] - 1u;

    if ((RSens_sNTCTemperatureVal.eSigQty[ucThermozonesId] == SIG_INVALID) && (RSens_aboNTCBinErrors[ucNtcSourceLocal] == FALSE))
    {
      RSens_aboNTCBinErrors[ucNtcSourceLocal] = TRUE;
    }
    else if((RSens_sNTCTemperatureVal.eSigQty[ucThermozonesId] == SIG_VALID) && (RSens_aboNTCBinErrors[ucNtcSourceLocal] != FALSE))
    {
      RSens_aboNTCBinErrors[ucNtcSourceLocal] = FALSE;
    }
    else
    {
      //
    }
  }

  // Check Binnings
  for (uint8 ucLedId = 0u; ucLedId < RSENS_LED_BINNING_CLASSES; ucLedId++)
  {
    ucCodBinIndx = (RSens_aucBinClassesArry[ucLedId]  == 22u) ? (RSens_aucBinClassesArry[ucLedId] - 1u) + ucLedId : (RSens_aucBinClassesArry[ucLedId] - 1u);

    if ((Rsens_asRCODBin_ErrState[ucLedId].eSigQty == eRSENS_SIG_INVALID) && (RSens_aboNTCBinErrors[ucCodBinIndx] == FALSE))
    {
      RSens_aboNTCBinErrors[ucCodBinIndx] = TRUE;
    }
    else if ((Rsens_asRCODBin_ErrState[ucLedId].eSigQty == eRSENS_SIG_VALID) && (RSens_aboNTCBinErrors[ucCodBinIndx] != FALSE))
    {
      {
        RSens_aboNTCBinErrors[ucCodBinIndx] = FALSE;
      }
    }
    else
    {
      //
    }
  }

  (void)Rte_Write_RSens_NTC_BIN_Input_Errors((tsRteNTCBinInData*)&RSens_aboNTCBinErrors);  // PRQA S 310 // cast intended
}

//-----------------------------------------------------------------------------
/// \brief  RSens_Update_D409Diag
///
/// \descr The function gets the binning classes and currents for each LED channels, 
///        then maps for D409 the led channel values assigned to the analog input sources. 
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void RSens_Update_D409Diag(void)
{
  uint8 ucCodBinIndx = 0xFFU;
  uint8_fast ucLedCh;
  tsRte_ucBinningSelect sBinningSelect;
  tsRte_TgtLedSig0Arr asLsTargetSetting0_Target;
  //get binning class for each LED channel
  (void)Rte_Read_CtrlLed_BinningClass(&sBinningSelect);
  //get binning current for each LED channel
  (void)Rte_Read_CtrlLed_TgtLedSig_sVal(&asLsTargetSetting0_Target);

  //map for D409 the Led channel values assigned to the analog input sources 
  for (ucLedCh = 0u; ucLedCh < RSENS_NR_LED_DRVS; ucLedCh++)
  {
    ucCodBinIndx = RSens_aucBinClassesArry[ucLedCh] - 1u;
    //range check for analog inputs
    if (ucCodBinIndx < CFG_NTC_BIN_CNT)
    {
      RSens_sBinningData.aucBinClass[ucCodBinIndx] = sBinningSelect.aucBinningSelect[ucLedCh];
      RSens_sBinningData.aunBinCurrent[ucCodBinIndx] = asLsTargetSetting0_Target[ucLedCh].unCurrent;
    }
  }

  (void)Rte_Write_RSens_BinningDataDiag(&RSens_sBinningData);
}
// EOF
