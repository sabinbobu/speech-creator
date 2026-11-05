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
#include <AL_Helper.h>
#include <RSens.h>
#include <RSens_Types.h>

//=============================================================================
// Defines
//=============================================================================
//RSens.c
#define RSENS_INIT_TEMP            -400
#define RSENS_MIN_LIMIT_TEMP       -400
#define RSENS_MAX_LIMIT_TEMP       1500
#define RSENS_NUM_NTC_TEMP_PROFILE 8u
#define RSENS_LMM_CODING_OFFSET    14u
#define RSENS_LED_DRV02            1 
#define RSENS_LED_DRV03            2 
#ifdef CFG_VARIANT_FULL
#define RSENS_NR_LED_DRVS          12u
#else
#define RSENS_NR_LED_DRVS          4u
#endif

//=============================================================================
// Typedefs
//=============================================================================
typedef enum enumDigState
{
  Di_Off = 0,
  Di_OnDelay = 1,
  Di_On = 2,
  Di_OffDelay = 3,
  Di_Sna = 4
}
tieDigState;

typedef struct struct_Digital
{
  unsigned bVal : 1;
  unsigned bPosEdge : 1;
  unsigned bNegEdge : 1;
  unsigned bValid : 1;
  unsigned bValLatched : 1;
}
tisDigital;

//=============================================================================
// Module global variables
//=============================================================================
extern tNvmPara_CodingArea       Coding_Dummy = { 0 };

//=============================================================================
// Global variables (of the module itself)
//=============================================================================
//RSens.c
extern const tNvmPara_CodingArea*       RSens_pCodingArea;
extern uint8                            RSens_aucBinClassesArry[RSENS_LED_BINNING_CLASSES];
extern tRSens_CodingMode                RSens_eCodingMode;
extern tsRsens_InterpolationInfo        RSens_sInterpPoints;
extern tsRte_NTCTemperature             RSens_sNTCTemperatureVal;
extern tsRsens_NTCErrState              Rsens_asNtcThz_ErrState[12];
extern tsRsens_NTCErrState              Rsens_asPCB_ErrState;
extern volatile tsRsens_NTCErrState     Rsens_asRCODBin_ErrState[RSENS_NR_LED_DRVS];
extern boolean                          RSens_boCodingValid;
extern uint16                           RSens_unCodShortGND;
extern uint16                           RSens_unCodShortBAT;
extern uint16                           RSens_unCodOpenLoad;
extern uint16                           RSens_unPCBShortGND;
extern uint16                           RSens_unPCBOpenLoad;
extern tsRteCodingParameters            CodingParameters;
extern  uint16                          Rsens_Binning_Thresholds[CFG_BIN_CLASS_CNT];
extern tasRte_MlcAdcResult              asLmmAdc;
extern tasRte_CtrlPxl_BinEEprom         asEepromBinning;
extern boolean                          RSens_boResistor_Para_Test;
extern boolean                          RSens_aboNTCBinErrors[eMaxNTCBin_Inputs];
extern uint16                           Rsens_Binning_Thresholds_Lmm[CFG_BIN_CLASS_CNT];
extern NtcTables RSens_Data_asnNTCB4000;
extern NtcTables RSens_Data_asnNTCB3650;
extern NtcTables RSens_Data_asnNTCB3380;

// interpolation table for Led NTcs
extern NtcTables* RSens_Data_apsnNTC[];
// interpolation table for LMM Temp
extern NtcTables  RSens_Data_asnLMM;

//=============================================================================
// Module function declarations
//=============================================================================
//ctaaRSens.c
extern void     riRSens_Init();
extern void     rpRSens_Cycle0();

//RSens.c
extern void     RSens_CalculateTemp_Pcb(void);
extern void     RSens_Calculate_Binning(uint8 ucBinIdx, boolean boInit);
extern boolean  Rsens_ParallelResistor_Exists(uint8 ucThermozoneID);
extern void     RSens_CheckErrFlagsNtc_Thzs(void);
extern sint16   RSens_CalcInterpolationTemperatures(uint8 ucThermoZoneID, uint16 unNtcVoltage, NtcTables* pasNtcTableParam);
extern void     RSens_CheckErrFlagsRCODs_LedDrvs(void);
extern void     RSens_CheckErrFlagsPCB(void);
extern void     RSens_OpenLoadHandlingPCB(boolean boErrorFlag);
extern void     RSens_Sh2GndHandlingPCB(boolean boErrorFlag);
extern sint16   Rsens_GetTemperature(uint16 nVoltage, uint16 unVoltage0, uint16 unVoltage1, sint16 snTemperature0, sint16 snTemperature1);
extern void     Rsens_GetInterpolationNTCInputs(uint16 nVoltage, NtcTables* pasNtcTableParam, boolean boParSer);
extern void     RSens_CheckVoltageRange(uint16 ucActualVoltage, uint8 ucThermoZoneID);
extern void     RSens_TempLimitation(sint16* snTemperature);
extern uint8    Rsens_CheckErrorBinning(uint16 unActualBinningVoltage, uint8 ucBinningIdx, uint8 ucCodBinIdx);
extern void     RSens_OpenloadHandlingNtcs(void);
extern void     RSens_Sh2GndHandlingNtcs(void);
extern void     RSens_Sh2VbatHandlingNtcs(void);
extern void     RSens_OpenloadHandlingRCODBin(void);
extern void     RSens_Sh2VbatHandlingRCODBin(void);
extern void     RSens_Sh2GndHandlingRCODBin(void);
extern void     RSens_UpdateNTCBINLMMErrors(void);
extern void     RSens_Update_D409Diag(void);

//=============================================================================
// Function parameter stubs (of the module ifself)
//=============================================================================
//RSens.c
uint8                Rsens_ParallelResistor_Exists_Param1;
sint16*              RSens_TempLimitation_Param1;
uint16               Rsens_CheckErrorBinning_Param1;
uint8                Rsens_CheckErrorBinning_Param2;
uint8                Rsens_CheckErrorBinning_Param3;
uint16               Rsens_GetTemperature_Param1;
uint16               Rsens_GetTemperature_Param2;
uint16               Rsens_GetTemperature_Param3;
sint16               Rsens_GetTemperature_Param4;
sint16               Rsens_GetTemperature_Param5;
tParaFct0_Cmd        RSens_ParaFct0_Param1;
tNvmPara_CodingArea* RSens_ParaFct0_Param2;
uint16               RSens_CheckVoltageRange_Param1;
uint8                RSens_CheckVoltageRange_Param2;
uint16               Rsens_GetInterpolationNTCInputs_Param1;
NtcTables*           Rsens_GetInterpolationNTCInputs_Param2;
boolean              Rsens_GetInterpolationNTCInputs_Param3;
boolean              RSens_Sh2GndHandlingPCB_Param1;
boolean              RSens_OpenLoadHandlingPCB_Param1;
uint8                RSens_CalcInterpolationTemperatures_Param1;
uint16               RSens_CalcInterpolationTemperatures_Param2;
NtcTables*           RSens_CalcInterpolationTemperatures_Param3;
uint8                RSens_Calculate_Binning_Param1;
boolean              RSens_Calculate_Binning_Param2;
uint8                RSens_CalculateTemp_Thzs_Param1;

//RSensRteAccess.c
uint16*              RSens_Rte_Read_PCBNTC_Param1;
uint32               RSens_Rte_Read_ExtNTC_Param1;
uint8                RSens_RteAccess_Write_BinnigClasses_Param1;
tsRte_Binning0*      RSens_RteAccess_Write_BinnigClasses_Param2;

//=============================================================================
// Module function parameter stubs
//=============================================================================


//=============================================================================
// Module function return value stubs
//=============================================================================
boolean        Rsens_ParallelResistor_Exists_RetVal;
uint8          Rsens_CheckErrorBinning_RetVal;
sint16         Rsens_GetTemperature_RetVal;
sint16         RSens_CalcInterpolationTemperatures_RetVal;
uint16         RSens_Rte_Read_ExtNTC_RetVal;
Std_ReturnType RSens_RteAccess_Write_BinnigClasses_RetVal;

//=============================================================================
// Module static variables inside functions
//=============================================================================
uint8                     ucIdx;
tsRte_PcbTemperatureMsg   sPCBTemperatureVal;
boolean                   boLMMBinUpdateStatus[12];

#endif // TEST_2023_08_25_H_
