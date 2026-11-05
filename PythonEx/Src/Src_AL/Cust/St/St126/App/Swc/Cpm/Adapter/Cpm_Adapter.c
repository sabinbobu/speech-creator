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
/// \file  Cpm_Adapter.c
///
/// \brief The software component CPM applies the binning current and duty
///        cycle to the light sources, reduces the light source duty cycle due
///        to thermal and supply voltage influences and requests the fan and
///        CMD activation due to environmental conditions.
///        These functionalities are needed to protect the ECU and head lamp
///        from thermal and electric damage.
///
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================

#include <string.h>
#include "Swc/Cpm/Api/Cpm_Adapter.h"
#include "Swc/Cpm/Api/Cpm_Rte.h"
#include "Swc/Cpm/Gen/Cpm/CPM_Gen.h"
#include "Swc/Cpm/Gen/FanM/FanM_Gen.h"
#include <CodM_Para_Fan.h>
#include <Nvm.h>
#include <_NM_Types.h>


//-----------------------------------------------------------------------------
//  Static variable declarations
//-----------------------------------------------------------------------------

STATIC_AL boolean                 Cpm_aboFanCtrl[2] = { FALSE, FALSE };
STATIC_AL tsCPM_LifePhases        Cpm_eEcuOpMode = { eEcu_StandBy,eEcu_SIG_DISABLED };
STATIC_AL tAppMThermo_CodHelper*  CPM_Data_DriverMap(teCPM_MountingSide ucEcuSide);
STATIC_AL uint8                   Cpm_aucChannelType[CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS];
//-----------------------------------------------------------------------------
//  Function prototypes
//-----------------------------------------------------------------------------
STATIC_AL void             Cpm_Init(void);
STATIC_AL void             Cpm_Cycle20ms(void);
STATIC_AL void             Cpm_CodingValidCycle(void);
STATIC_AL boolean          Cpm_MapParams(void);
STATIC_AL boolean          Cpm_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
STATIC_AL void             CpmThermo_SetPara(void);
STATIC_AL Std_ReturnType   CPM_Read_PhaseVie(tsCPM_LifePhases* eEcuOpMode);
STATIC_AL uint8            Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT(void);
STATIC_AL tiu32Voltage_mV  Cpm_RteAccess_Read_Vbat(void);
STATIC_AL void             Cpm_RteAccess_Write_PwFact_Temp(tsCPM_PowFactTemp* sParam1);
STATIC_AL Std_ReturnType   Cpm_Rte_Read_PcbTemperature(const tsRte_PcbTemperatureMsg *pdata);

//-----------------------------------------------------------------------------
//  Macros
//-----------------------------------------------------------------------------
#define BINCUR2CURMA(cur)         ((uint16)(cur) /** 2u*/)
#define BINDUCY2PER1328(per)      (uint16)(((uint32)(per) << 15u) / 200u)
#define DUCY2PER1328(per)         (uint16)(((uint32)(per) << 15u) / 100u)
#define PER13282DUCY(per)         (uint16)(((uint32)(per) * 100u) >> 15u)
#define MULTDUTYCYCLE(x,y)        (uint16)(((uint32)(x)*(uint32)(y))>> 15u)
#define CODTEMP2MTEMP(deg)        ((((sint32)(deg)) - 40) * 1000)
#define MTEMP2CODTEMP(deg)        (uint8)(((sint32)(deg) / 1000) + 40)
#define DEG2MDEG(deg)             (((sint32)(deg)) * 1000)
#define CODRED2DUCY2PER1328(per)  (uint16)(((uint32)((uint32)(per) * 4u) << 15u) / 1000u)
#define CPM_RSENS2CPMRES(deg)     (((sint32)(deg)) * 100) //Cpm module has resolution 0.001
#define CPM_ZERO_DUTY             0u
#define CPM_ZERO_VOLTAGE          0u

//=============================================================================
// Definitions
//=============================================================================
// compiler switch in case Developer hooks mode is active
#if (CFG_DEV_HOOK_EN == 1u)
// Pattern for inserting manual voltage on ECU NTC
#define CPM_RATE_LIMITER 0x5AA5AAu
STATIC_AL volatile uint32 Cpm_ulTesterHookActivation = 0u;
#endif

//-----------------------------------------------------------------------------
//  Function definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  CPM_Rte_Read_PcbTemperature
///
/// \descr  This function reads the temperature from rsens for pcb
///
/// \param  tsRte_PcbTemperatureMsg
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType Cpm_Rte_Read_PcbTemperature(const tsRte_PcbTemperatureMsg *pdata)
{
  return Rte_Read_RSens_PcbTemperature((tsRte_PcbTemperatureMsg*)pdata);  // PRQA S 311 // Cast is needed 
}

//-----------------------------------------------------------------------------
/// \brief initialisation runnable
///
/// \descr initialisation runnable for Cpm
///        Calling once at start up.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riCpmInit(void)
{
  //ENTER_INIT_RUNNABLE(RIAPPMINIT);
   Cpm_Init();
  //EXIT_INIT_RUNNABLE(RIAPPMINIT);
}

//-----------------------------------------------------------------------------
/// \brief  cyclic runnable
///
/// \descr  cyclic runnable for Cpm
///         Calling cyclicaly every 20 ms.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpCpm20ms(void)
{
  //ENTER_CYCLIC_RUNNABLE(RPAPPM10MS);
  Cpm_Cycle20ms();
  //EXIT_CYCLIC_RUNNABLE(RPAPPM10MS);
}

//-----------------------------------------------------------------------------
/// \func   Cpm_ParaFct0
///
/// \brief  Thermo coding parameters
///
/// \param  eCmd (coding data valid / invalid)
/// \param  pData (pointer to coding data ram copy)
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL boolean Cpm_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  // set pointer to Coding Data
  CPM_pCodingArea = pData;
  boolean boCodingValidity = FALSE;
  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
	  boCodingValidity = TRUE;
	  break;
  case eParaFct0_CodingDataInvalid:
	  boCodingValidity = FALSE;
	  break;
  default:
	  break;
  }
  return boCodingValidity;
}

//-----------------------------------------------------------------------------
/// \brief  Cpm_MapParams
///
/// \descr  Maps the coding parameter in order to acces them in Thermo
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL boolean Cpm_MapParams(void)
{
  tsRteCodingParameters sCodingParameters;
 
  (void)Rte_Read_CodM_AppM_Para(&sCodingParameters);

  const boolean boCodingValidity = Cpm_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  Cpm_Read_PhaseVie
///
/// \descr  Read Ecu operating mode from Rte
///
/// \param  eEcuOpMode - stores Ecu operating mode
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType Cpm_Read_PhaseVie(tsCPM_LifePhases* eEcuOpMode)
{
  Std_ReturnType           ucReturnValue;
  tsRte_SysMon_LifePhases  sLifePhases;

  ucReturnValue = Rte_Read_SysMon_LifePhases(&sLifePhases);

  eEcuOpMode->ePhaseVie = (teCPM_EcuOperationgMode)sLifePhases.ePhaseVie; // PRQA S 4322 // The cust is needed; Rte struct type converted to CPM struct type
  eEcuOpMode->eSigQty = (teCPM_SigQty)sLifePhases.eSigQty; // PRQA S 4322 // The cust is needed; Rte struct type converted to CPM struct type

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  Cpm_RteAccess_Get_ECU_Side
///
/// \descr  this function return ECU side, used for coding data handling
///
/// \param  void
///
/// \return eEcuSide - stores Ecu mounting side
//-----------------------------------------------------------------------------
STATIC_AL teCPM_MountingSide Cpm_RteAccess_Get_ECU_Side(void)
{
  teRte_MountingSide eEcuSide = eMountedUndef;
  teCPM_MountingSide eReturnEcuSide = eCPM_MountedUndef;

  //read ECU side
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eEcuSide);

  switch (eEcuSide)
  {
  case eMountedLeft:
    eReturnEcuSide = eCPM_MountedLeft;
    break;
  case eMountedRight:
    eReturnEcuSide = eCPM_MountedRight;
    break;
  case eMountedUndef:
    eReturnEcuSide = eCPM_MountedRight;
    break;
  default:
    break;
  }

  //return ECU side, cast needed for macro
  return eReturnEcuSide;
}

//-----------------------------------------------------------------------------
/// \brief  Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT
///
/// \descr  this function returns status of ETAT_FEUX_STATIONMENT
///
/// \param  void
///
/// \return eEcuSide - stores Ecu mounting side
//-----------------------------------------------------------------------------
STATIC_AL uint8 Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT(void)
{
  tsRte_SysMonLgtFctsReq dataLgtFctsReq = { 0 };
  teRte_EtatFeuxStationnement eReturnValue = eEtatFeuxStationnement_Deactivated;

  (void)Rte_Read_SysMon_StdLgtFcts_Req(&dataLgtFctsReq);

  if (dataLgtFctsReq.eSigQty == SIG_VALID)
  {
    eReturnValue = dataLgtFctsReq.eEtatFeuxStat;
  }
  return (uint8)eReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief Cpm_RteAccess_Read_Vbat
///
/// \descr Read Vbat voltage Rte call wrapper
///
/// \param  void
///
/// \return unVoltage_mV - batery voltage indirected
//-----------------------------------------------------------------------------
STATIC_AL tiu32Voltage_mV Cpm_RteAccess_Read_Vbat(void)
{
  tiu32Voltage_mV u32Voltage_mV;
  // Rte call for Vbat voltage
  (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(&u32Voltage_mV);

  return u32Voltage_mV;
}

//-----------------------------------------------------------------------------
/// \brief Cpm_RteAccess_Write_PwFact_Temp
///
/// \descr Write power factor and temperature per thermozone
///
/// \param  sParam1 - Derating factors and thermozone temperatures
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Cpm_RteAccess_Write_PwFact_Temp(tsCPM_PowFactTemp* sParam1)
{
  tsRtePowFactTemp sRte_PowFactTemp;

  for (uint8 ucIdx = 0u; ucIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucIdx++)
  {
    sRte_PowFactTemp.snNTCTemperatureCelsius[ucIdx] = sParam1->snNTCTemperatureCelsius[ucIdx];
    sRte_PowFactTemp.ucPowerFactor[ucIdx]           = sParam1->ucPowerFactor[ucIdx];
  }

  // Write power factor and temperature per thermozone
  (void)Rte_Write_Cpm_PowFact_Temp(&sRte_PowFactTemp);
}

//-----------------------------------------------------------------------------
/// \brief initialisation function for CMP
///
/// \descr Cpm_Init() is initializing the RTE outputs, privat variables and
///        coding date.
///        Calling once at start up.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Cpm_Init(void)
{
  const boolean boCodingValidity = Cpm_MapParams();
  // Initialize the commands of the fans with 0
  for (uint8 ucIdx = 0u; ucIdx < CPM_FAN_NR; ucIdx++)
  {
	  Cpm_aboFanCtrl[ucIdx] = 0u;
  }
  if (boCodingValidity != FALSE)
  {
	  CpmThermo_SetPara(); // Set the parameters of the generic algorithm 
  }
}

//-----------------------------------------------------------------------------
/// \brief  cyclic function for Cpm
///
/// \descr  Cpm_Cycle20ms() is monitoring the internal and external
///         temperatures, the supply voltage and vehicle state to reduce the
///         duty cycle of the single channels, request the fan and CMD. Further
///         it evaluate the binning classes, the external takeover and applies
///         the values to the channels.
///         Calling cyclicaly every 20 ms.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Cpm_Cycle20ms(void)
{
  // Read Ecu operation mode
  (void)Cpm_Read_PhaseVie(&Cpm_eEcuOpMode);

  const boolean boCodingValidity = Cpm_MapParams();

  if (boCodingValidity != FALSE)
  {
#if (CFG_DEV_HOOK_EN == 1u)
    // 
    if (Cpm_ulTesterHookActivation == CPM_RATE_LIMITER)
    {
      /* Power factor rising rate limiter for each thermozone is deactivated for testing team for a faster testing*/
      CPM_PARA_aunTzLmtRis = 0;
      CPM_PARA_aunTzLmtFal = 0;
    }
    else
    {//Power factor falling rate limiter for each thermozone
    }

#endif

    //essential cyclic function of AppM
    Cpm_CodingValidCycle();
  }
}

//-----------------------------------------------------------------------------
/// \brief  main functionality for Cpm only called when coding ok
///
/// \descr  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Cpm_CodingValidCycle(void)
{
  uint8                     ucMlcIdx = 0u; // MLC chip index
  uint8                     ucSwIdx = 0u;  // MLC switch index
  boolean                   abFanRequest1[2] = { FALSE, FALSE }, boFanOn_NTCFailue = FALSE, boFanOn_LostCom = FALSE;

  // Inputs for Cpm_Gen
  static tsVoltage          sActVoltage0 = {13000u, TESIGQTY_SIG_SNA}; // Actual supply voltage in mV
  tsTemperature             sEcuTemp0 = { 0 };    // Actual ECU PCB temperature in mC
  tsTemperatureArr14        sIoTemp0 = { { 0 }, { 0 } }; // Input IO temperature
  tsTemperatureArr8         sLmmTemp0; // Input LMM temperature
  tsLsTargetPercArr13       asLsTargetSetting0 = { 0 }; // Target light source current and duty cycle
  tunPercent_1_328          aunExtSwitchSetting0[8][16] = { {0},{0} }; // Target MLC stiches duty cycle
  tsRte_CpmHSS3Duty         sHss3Duty = { 0 };

  // Inputs taken from RTE ports
  tiu32Voltage_mV           unEcuSupply = 0u; // Supply voltage from IoHwaB
  tsRte_PcbTemperatureMsg   sPCBTemperature = { 0 }; // Temperature of PCB from RSens
  tsRte_TgtLedSig0Arr       asLsTargetSetting0_Target; // Target light source and current from ctrlled
  uint16                   *punExTgtPxl;  //  Buffer used to wirte the values in aunExtSwitchSetting0 (logical units-> lmm/switch nr)
#if defined (CFG_VARIANT_FULL ) || defined(UNIT_TEST) 
  tsRte_TgtPxlSig0Arr       sTgtPxlSig0Arr = { 0u }; // Target MLC duty cycle(logical unit)
  tsRte_TgtPxlSig0Arr       aunExtSwitchSettingToPxl; // Derated mlc duty cycle (Logical unit)
#endif

  tsRte_TgtLedSig0          sTgtHss3Sig0;

  tsRte_NTCTemperature      sThzTemperatures;
  // Outputs from Cpm_Gen
  tsLsTargetPercArr13       asLsTargetSetting1 = { 0 }; // Derated light source current and duty cycle
  tunPercent_1_328          aunExtSwitchSetting1[8][16]; // Derated mlc duty cycle from Cpm_Gen (LMM/Switch nr)
  tsCPM_PowFactTemp         sPowerFactorTemp; // Power factor and thermozone per temperature for diagnostic service routine

  tsRteHssTarget            asCpmHssTargetSetting;    // High side switch target settings

  uint8                     ucEtatFeuxStationment = Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT();
  teCPM_MountingSide        ucEcuSide = Cpm_RteAccess_Get_ECU_Side();
  uint8                     ucTempPointIdx;
  tsRte_PowerFactor         ucSavePowerFactor;

  NM_ModeType NMMode;

  // Get life phases from the NM
  (void)NM_GetMode(&NMMode);

  // Read Rsens temperatures 
  (void)Rte_Read_RSens_ThermzoneTemperatures(&sThzTemperatures);

  //read target from CtrlLed
  (void)Rte_Read_CtrlLed_TgtLedSig_sVal(&asLsTargetSetting0_Target);

  (void)Rte_Read_CtrlLed_TgtHssSig_sVal(&sTgtHss3Sig0);
#if defined (CFG_VARIANT_FULL ) || defined(UNIT_TEST) 

  (void)Rte_Read_CtrlLed_Cpm_TgtPxlSig(&sTgtPxlSig0Arr); // from ctrled 

  punExTgtPxl = &aunExtSwitchSetting0[0][0]; // overlap the logical units size 103 over the 8x16 input of alg

  for (uint8_fast ucLogicalUnit = 0u; ucLogicalUnit < CPM_CFG_MAX_NO_OF_LOGICAL_UNIT; ucLogicalUnit++)
  {
    sTgtPxlSig0Arr.unPxl_Int[ucLogicalUnit] >>= 1U;// CPM_SCALING_X_TO_Y_VALUE(CPM_SCALING_65535, CPM_SCALING_32768, sTgtPxlSig0Arr.unPxl_Int[ucLogicalUnit]);
    punExTgtPxl[ucLogicalUnit] = sTgtPxlSig0Arr.unPxl_Int[ucLogicalUnit] >= CPM_PERCENT_VAL ? CPM_PERCENT_VAL : sTgtPxlSig0Arr.unPxl_Int[ucLogicalUnit]; // write in aunExtSwitchSetting0
  }
#endif

  // read ECU supply voltage
  unEcuSupply = Cpm_RteAccess_Read_Vbat();

  //Reading the temperature value from the RTE port
  (void)Cpm_Rte_Read_PcbTemperature(&sPCBTemperature); // pcb temperature from rsens

   // Check if Instrumented Frames has been activated by Diagnostic Request
  if (NvmBlockInstrumentatedFrames != FALSE)
  {
    for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
    {
      if (sThzTemperatures.eSigQty[ucChIdx] == SIG_VALID)
      {
        for (ucTempPointIdx = 4u; ucTempPointIdx > 0u; ucTempPointIdx--)
        {
          if (CPM_RSENS2CPMRES(sThzTemperatures.s16_NTCTemperatureCelsius[ucChIdx]) >= CPM_PARA_alTzTemp[ucTempPointIdx][ucChIdx])
          {
            break;
          }
        }
        ucSavePowerFactor.ucPowerFactor[ucChIdx] = ucTempPointIdx + 1u;
      }
      else
      {
        // In case of NTC failure we set the number of the power factor to 0
        ucSavePowerFactor.ucPowerFactor[ucChIdx] = 0u;
      }
    }
    // Write the applied power factor number from the 5 point table for each thermozone
    (void)Rte_Write_Cpm_SigPrepTx_PowerFactor(&ucSavePowerFactor);
  }
  else
  {
    // do nothing 
  }

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++) {

    if ((CPM_PARA_aucTz2Temp[ucChIdx] <= CPM_MAX_NO_OF_IO_TEMP) && (CPM_PARA_aucTz2Temp[ucChIdx] != 0u))
    {
      
		sIoTemp0.lVal[CPM_PARA_aucTz2Temp[ucChIdx] - 1u] = CPM_RSENS2CPMRES(sThzTemperatures.s16_NTCTemperatureCelsius[ucChIdx]); // mapping the Io temperature

      switch(sThzTemperatures.eSigQty[ucChIdx])
      {
      case SIG_SNA:
        sIoTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - 1u] = TESIGQTY_SIG_SNA;
        break;
      case SIG_VALID:
        sIoTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - 1u] = TESIGQTY_SIG_VALID;
        break;
      case SIG_INIT:
        sIoTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - 1u] = TESIGQTY_SIG_INIT;
        break;
      case SIG_INVALID:
        sIoTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - 1u] = TESIGQTY_SIG_INVALID;
        break;
      case SIG_TIMEOUT:
        sIoTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - 1u] = TESIGQTY_SIG_TIMEOUT;
        break;
      case SIG_DEFAULT:
        sIoTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - 1u] = TESIGQTY_SIG_DEFAULT;
        break;
       case SIG_DISABLED:
        sIoTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - 1u] = TESIGQTY_SIG_DISABLED;
        break;
       default:
        sIoTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - 1u] = TESIGQTY_SIG_SNA;
        break;
    }
    }
    else if ((CPM_PARA_aucTz2Temp[ucChIdx] != 0u))
    {
		sLmmTemp0.lVal[CPM_PARA_aucTz2Temp[ucChIdx] - CPM_FIRST_INDEX_MLC] = CPM_RSENS2CPMRES(sThzTemperatures.s16_NTCTemperatureCelsius[ucChIdx]);//tempRSensMLsTemperature0[ucChIdx + CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS].lVal;
      switch (sThzTemperatures.eSigQty[ucChIdx])
      {
      case SIG_SNA:
        sLmmTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - CPM_FIRST_INDEX_MLC] = TESIGQTY_SIG_SNA;
        break;
      case SIG_VALID:
        sLmmTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - CPM_FIRST_INDEX_MLC] = TESIGQTY_SIG_VALID;
        break;
      case SIG_INIT:
        sLmmTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - CPM_FIRST_INDEX_MLC] = TESIGQTY_SIG_INIT;
        break;
      case SIG_INVALID:
        sLmmTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - CPM_FIRST_INDEX_MLC] = TESIGQTY_SIG_INVALID;
        break;
      case SIG_TIMEOUT:
        sLmmTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - CPM_FIRST_INDEX_MLC] = TESIGQTY_SIG_TIMEOUT;
        break;
      case SIG_DEFAULT:
        sLmmTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - CPM_FIRST_INDEX_MLC] = TESIGQTY_SIG_DEFAULT;
        break;
      case SIG_DISABLED:
        sLmmTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - CPM_FIRST_INDEX_MLC] = TESIGQTY_SIG_DISABLED;
        break;
      default:
        sLmmTemp0.eQty[CPM_PARA_aucTz2Temp[ucChIdx] - CPM_FIRST_INDEX_MLC] = TESIGQTY_SIG_SNA;
        break;
      }
    }
    else
    {
      // increment
    }
  }

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++) 
  {
	  asLsTargetSetting0.unDutyCycle[ucChIdx] = (tunPercent_1_328)asLsTargetSetting0_Target[ucChIdx].unDutyCycle >= CPM_PERCENT_VAL ? CPM_PERCENT_VAL : asLsTargetSetting0_Target[ucChIdx].unDutyCycle;
    asLsTargetSetting0.unCurrent[ucChIdx] = CPM_SCALING_32768;

    // NTC Fault
    if (sThzTemperatures.eSigQty[ucChIdx] == SIG_INVALID)
    {
      boFanOn_NTCFailue = TRUE;
    }
    else
    {
      // do nothing
    }
  }

  asLsTargetSetting0.unDutyCycle[CPM_HSS3_INDEX] = (tunPercent_1_328)sTgtHss3Sig0.unDutyCycle >= CPM_PERCENT_VAL ? CPM_PERCENT_VAL : sTgtHss3Sig0.unDutyCycle;
  asLsTargetSetting0.unCurrent[CPM_HSS3_INDEX] = 0u;

  /* Added temporary qualifier */
  sActVoltage0.lVal = unEcuSupply;

  if (sActVoltage0.eQty == TESIGQTY_SIG_SNA)
  {
    sActVoltage0.eQty = TESIGQTY_SIG_INIT;
  }
  else
  {
    sActVoltage0.eQty = TESIGQTY_SIG_VALID;
  }


  // TO DO: Check resolution for pcb
  sEcuTemp0.lVal = CPM_RSENS2CPMRES(sPCBTemperature.nVal); // TO DO: Check resolution of the pcb which came from RSens
  sEcuTemp0.eQty = TESIGQTY_SIG_VALID;

    //  evaluate the thermal management
    CPM_Gen(aunExtSwitchSetting0, aunExtSwitchSetting1, &asLsTargetSetting0,
      &asLsTargetSetting1, &sActVoltage0, &sEcuTemp0, &sIoTemp0, &sLmmTemp0);

  FanM_Gen(asLsTargetSetting0.unDutyCycle, aunExtSwitchSetting0,
    abFanRequest1, &sIoTemp0, &sLmmTemp0);

  // Allocate light sources
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)(CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS); ucChIdx++)
  {

	  if (Cpm_aucChannelType[ucChIdx] == CPM_CFG_MATRIX_BUCK)
	  {
		  asLsTargetSetting1.unDutyCycle[ucChIdx] = asLsTargetSetting0.unDutyCycle[ucChIdx];
	  }
    // Limit max values
    asLsTargetSetting1.unDutyCycle[ucChIdx] = asLsTargetSetting1.unDutyCycle[ucChIdx] <= DUCY2PER1328(CPM_PWM_MAX_0_100) ? asLsTargetSetting1.unDutyCycle[ucChIdx] : DUCY2PER1328(CPM_PWM_MAX_0_100);
    asLsTargetSetting1.unCurrent[ucChIdx] = asLsTargetSetting1.unCurrent[ucChIdx] <= DUCY2PER1328(CPM_PWM_MAX_0_100) ? asLsTargetSetting1.unCurrent[ucChIdx] : DUCY2PER1328(CPM_PWM_MAX_0_100);
    asLsTargetSetting1.unCurrent[ucChIdx] = (uint16)(((asLsTargetSetting0_Target[ucChIdx].unCurrent * asLsTargetSetting1.unCurrent[ucChIdx])) / (CPM_SCALING_32768));
  }

#if defined (CFG_VARIANT_FULL ) || defined(UNIT_TEST) 
  // Allocate MLC switches
  for (uint8 ucIdx = 0u; ucIdx < CPM_CFG_MAX_NO_OF_LOGICAL_UNIT; ucIdx++)
  {
	  ucMlcIdx = ucIdx / 16u;
	  ucSwIdx = ucIdx % 16u;
    // Limit max values
	  aunExtSwitchSettingToPxl.unPxl_Int[ucIdx] = aunExtSwitchSetting1[ucMlcIdx][ucSwIdx] <= CPM_PERCENT_VAL ? aunExtSwitchSetting1[ucMlcIdx][ucSwIdx] : CPM_PERCENT_VAL;
  }
#endif
  tsRte_TgtLedSig0Arr sTgtLedSig0Arr = { 0 };
  if (((Cpm_eEcuOpMode.ePhaseVie == eEcu_NormalMode) && (Cpm_eEcuOpMode.eSigQty == eEcu_SIG_VALID)) ||
     ((ucEtatFeuxStationment == (uint8)eEtatFeuxStationnement_LeftSide) && (ucEcuSide == eCPM_MountedLeft)) ||
     ((ucEtatFeuxStationment == (uint8)eEtatFeuxStationnement_RightSide) && (ucEcuSide == eCPM_MountedRight)))
  {

	  for (uint8 ucIdx = 0u; ucIdx < CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucIdx++)
	  {
		  sTgtLedSig0Arr[ucIdx].unCurrent = asLsTargetSetting1.unCurrent[ucIdx];
		  sTgtLedSig0Arr[ucIdx].unDutyCycle = asLsTargetSetting1.unDutyCycle[ucIdx];
	  }

    Cpm_aboFanCtrl[0] = abFanRequest1[0];
    Cpm_aboFanCtrl[1] = abFanRequest1[1];
    sHss3Duty.unDutyHSS3 = asLsTargetSetting1.unDutyCycle[CPM_HSS3_INDEX];
  }
  else
  {
#if defined (CFG_VARIANT_FULL ) || defined(UNIT_TEST) 
    for (uint8_fast ucLogicalUnit = 0u; ucLogicalUnit < CPM_CFG_MAX_NO_OF_LOGICAL_UNIT; ucLogicalUnit++)
    {
      aunExtSwitchSettingToPxl.unPxl_Int[ucLogicalUnit] = sTgtPxlSig0Arr.unPxl_Int[ucLogicalUnit];
     
    }
#endif

    for (uint8 ucIdx = 0u; ucIdx < CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucIdx++)
    {
      sTgtLedSig0Arr[ucIdx].unCurrent = asLsTargetSetting0_Target[ucIdx].unCurrent;
      sTgtLedSig0Arr[ucIdx].unDutyCycle = asLsTargetSetting0_Target[ucIdx].unDutyCycle;
    }
    sHss3Duty.unDutyHSS3 = sTgtHss3Sig0.unDutyCycle;
    Cpm_aboFanCtrl[0] = FALSE;
    Cpm_aboFanCtrl[1] = FALSE;
  }

  boFanOn_LostCom = (NMMode == LIMP_HOME_MODE) ? TRUE : FALSE;

  //check if FANS command should be overwritted 
  if ((boFanOn_LostCom != FALSE) || (boFanOn_NTCFailue != FALSE))
  {
    Cpm_aboFanCtrl[0] = TRUE;
    Cpm_aboFanCtrl[1] = TRUE;
  }
  else
  {
    // do nothing
  }

  asCpmHssTargetSetting.aeSetting[0] = Cpm_aboFanCtrl[0];
  asCpmHssTargetSetting.aeSetting[1] = Cpm_aboFanCtrl[1];

  for (uint8 ucIdx = 0u; ucIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucIdx++)
  {
	  sPowerFactorTemp.snNTCTemperatureCelsius[ucIdx] = (sThzTemperatures.s16_NTCTemperatureCelsius[ucIdx])/ 10;
    sPowerFactorTemp.ucPowerFactor[ucIdx] = (uint8)((CPM_DISP_aunTzPowerLimiter[ucIdx] * CPM_PWM_MAX_0_100) / CPM_PERCENT_VAL);
  }

  Cpm_RteAccess_Write_PwFact_Temp(&sPowerFactorTemp);
 
#if defined (CFG_VARIANT_FULL ) || defined(UNIT_TEST) 
  // write derated mlc for ctrlpxl
  (void)Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels(&aunExtSwitchSettingToPxl);
#endif

  (void)Rte_Write_Cpm_CtrlSwi_HSS3Target(&sHss3Duty);

  // write light source and switches target duty cycle for sysmon
  (void)Rte_Write_Cpm_TgtLedSig_sVal(&sTgtLedSig0Arr);
  // write fan request to ctrlswitch
  (void)Rte_Write_CpmHssTarget0_sSetting((const tsRteHssTarget*)&asCpmHssTargetSetting);//to be removed
} // PRQA S 5324, 5310, 5316, 5330, 5336 // Architecture and design, parameter interface for generated code designed as functions, no complexity

//-----------------------------------------------------------------------------
/// \brief  CPMThermo_SetPara
///
/// \descr  Set the configuration parameter for every input parameter for the generic alghoritm for CPM and Fan
///
/// \param  -
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CpmThermo_SetPara(void)
{
  tAppMThermo_CodHelper *pucData;
  tAppMThermo_CodHelper * pAppMThermo_CodHelper;
  uint16  ucCoding_FANM_PARA_unHysteresis;

  const teCPM_MountingSide ucEcuSide = CPM_RTE_RE_GET_ECU_SIDE

  pucData = CPM_Data_DriverMap(ucEcuSide); // take the specific ecu side

   /*Taking the values from the coding*/
  CPM_PARA_aunTzLmtRis = ((sint16)CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_RisingRateLimiter < CPM_MAX_LIMIT_FOR_FALLING_RISING_LIMITER) ? (sint16)CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_RisingRateLimiter * CPM_RATE_LIMITER_RESOLUTION : CPM_100_PERCENT_LIMITER;   //Power factor rising rate limiter for each thermozone 
  CPM_PARA_aunTzLmtFal = ((sint16)CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter < CPM_MAX_LIMIT_FOR_FALLING_RISING_LIMITER) ? (sint16)CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter * CPM_RATE_LIMITER_RESOLUTION : CPM_100_PERCENT_LIMITER; //Power factor falling rate limiter for each thermozone
  
  // Taking the value for Fan hysteresis from coding

  ucCoding_FANM_PARA_unHysteresis = CPM_FANHYSTERESIS_RESOLUTION * CPM_pCodingArea->Fan1.Fans_Hysterezis.ucFanHysterezis;

  //Set negative value for the falling rate limiter
  if (CPM_PARA_aunTzLmtFal > 0)
  {
    CPM_PARA_aunTzLmtFal *= - 1;
  }

    for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
    {
      //Thermozone Temp
      CPM_PARA_alTzTemp[0][ucChIdx] = CODTEMP2MTEMP(CPM_pCodingArea->Thermo1.Thermozones_Temp1.ucTemp1_Thermozones[ucChIdx]);
      CPM_PARA_alTzTemp[1][ucChIdx] = CODTEMP2MTEMP(CPM_pCodingArea->Thermo1.Thermozones_Temp2.ucTemp2_Thermozones[ucChIdx]);
      CPM_PARA_alTzTemp[2][ucChIdx] = CODTEMP2MTEMP(CPM_pCodingArea->Thermo1.Thermozones_Temp3.ucTemp3_Thermozones[ucChIdx]);
      CPM_PARA_alTzTemp[3][ucChIdx] = CODTEMP2MTEMP(CPM_pCodingArea->Thermo1.Thermozones_Temp4.ucTemp4_Thermozones[ucChIdx]);
      CPM_PARA_alTzTemp[4][ucChIdx] = CODTEMP2MTEMP(CPM_pCodingArea->Thermo1.Thermozones_Temp5.ucTemp5_Thermozones[ucChIdx]);

      //Thermozone Power Factor
      CPM_PARA_aunTzPwrFct[0][ucChIdx] = DUCY2PER1328(CPM_pCodingArea->Thermo1.Thermozones_PowerFactor_1.ucPowFact1_Thermozones[ucChIdx]);
      CPM_PARA_aunTzPwrFct[1][ucChIdx] = DUCY2PER1328(CPM_pCodingArea->Thermo1.Thermozones_PowerFactor_2.ucPowFact2_Thermozones[ucChIdx]);
      CPM_PARA_aunTzPwrFct[2][ucChIdx] = DUCY2PER1328(CPM_pCodingArea->Thermo1.Thermozones_PowerFactor_3.ucPowFact3_Thermozones[ucChIdx]);
      CPM_PARA_aunTzPwrFct[3][ucChIdx] = DUCY2PER1328(CPM_pCodingArea->Thermo1.Thermozones_PowerFactor_4.ucPowFact4_Thermozones[ucChIdx]);
      CPM_PARA_aunTzPwrFct[4][ucChIdx] = DUCY2PER1328(CPM_pCodingArea->Thermo1.Thermozones_PowerFactor_5.ucPowFact5_Thermozones[ucChIdx]);
      
      //Thermozone fail safe power factor
      CPM_PARA_aunTzFS[ucChIdx] = DUCY2PER1328(CPM_pCodingArea->Thermo1.Thermozone_BehaviourNtcFaulty.ucFaultyNtc_PowFct_Thermozones[ucChIdx]);

      //Function group 
      CPM_PARA_abTzFctGrp[0][ucChIdx] = CPM_pCodingArea->Thermo1.Thermozones_FunctionGroup_1.ucFctGroup1_State_Thermozones[ucChIdx];
      CPM_PARA_abTzFctGrp[1][ucChIdx] = CPM_pCodingArea->Thermo1.Thermozones_FunctionGroup_2.ucFctGroup2_State_Thermozones[ucChIdx];
      CPM_PARA_abTzFctGrp[2][ucChIdx] = CPM_pCodingArea->Thermo1.Thermozones_FunctionGroup_3.ucFctGroup3_State_Thermozones[ucChIdx];
      CPM_PARA_abTzFctGrp[3][ucChIdx] = CPM_pCodingArea->Thermo1.Thermozones_FunctionGroup_4.ucFctGroup4_State_Thermozones[ucChIdx];

      // Allocate Ntc source for each thermozone
      CPM_PARA_aucTz2Temp[ucChIdx] = CPM_pCodingArea->Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[ucChIdx];
    
      //Coding parameters for FanM_Gen
      FANM_PARA_alFan1TempOff[ucChIdx] = CODTEMP2MTEMP(CPM_pCodingArea->Fan1.FAN1_HT_THRESHOLDS.ucFan1_Actv_Threshold_Termozones[ucChIdx]) - (sint32)ucCoding_FANM_PARA_unHysteresis;
      FANM_PARA_alFan1TempOn[ucChIdx] = CODTEMP2MTEMP(CPM_pCodingArea->Fan1.FAN1_HT_THRESHOLDS.ucFan1_Actv_Threshold_Termozones[ucChIdx]);

#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
      FANM_PARA_alFan2TempOff[ucChIdx] = CODTEMP2MTEMP(CPM_pCodingArea->Fan1.FAN2_HT_THRESHOLDS.ucFan2_Actv_Threshold_Termozones[ucChIdx]) - (sint32)ucCoding_FANM_PARA_unHysteresis;
      FANM_PARA_alFan2TempOn[ucChIdx] = CODTEMP2MTEMP(CPM_pCodingArea->Fan1.FAN2_HT_THRESHOLDS.ucFan2_Actv_Threshold_Termozones[ucChIdx]);
#endif
      FANM_PARA_abFan1FS[ucChIdx] = 0;
      FANM_PARA_abFan2FS[ucChIdx] = 0;
    }

    for (uint8 ucClIdx = 0u; ucClIdx < 5u; ucClIdx++)
    {
      //PCB Temp
      CPM_PARA_alTzTemp[ucClIdx][12] = CODTEMP2MTEMP(CPM_pCodingArea->Thermo1.ThermzonePCB_Temp.aucThermzonePcb_Temps[ucClIdx]);
	    CPM_PARA_aunTzPwrFct[ucClIdx][12] = DUCY2PER1328(CPM_pCodingArea->Thermo1.ThermozonePCB_PowFct.aucThermozonePcb_PowFcts[ucClIdx]);
    
    }

    //Voltage derating
	CPM_PARA_aunLedDeratingPwm[0] = CPM_ZERO_DUTY;	
    CPM_PARA_aunLedDeratingPwm[1] = DUCY2PER1328(CPM_pCodingArea->Led1.LedVoltageDerating.aucLED_VBAT_MAX_DERATING_P1);
    CPM_PARA_aunLedDeratingPwm[2] = DUCY2PER1328(CPM_pCodingArea->Led1.LedVoltageDerating.aucLED_VBAT_MAX_DERATING_P2);
    CPM_PARA_aunLedDeratingPwm[3] = DUCY2PER1328(CPM_pCodingArea->Led1.LedVoltageDerating.aucLED_VBAT_MAX_DERATING_P3);
    CPM_PARA_aunLedDeratingPwm[4] = CPM_PERCENT_VAL;
    CPM_PARA_aulLedDeratingV[0] = CPM_ZERO_VOLTAGE;
    CPM_PARA_aulLedDeratingV[1] = (uint32)CPM_pCodingArea->Led1.LedVoltageDerating.aucLED_VBAT_DERATING_V1 * CPM_MV_RESOLUTION;
    CPM_PARA_aulLedDeratingV[2] = (uint32)CPM_pCodingArea->Led1.LedVoltageDerating.aucLED_VBAT_DERATING_V2 * CPM_MV_RESOLUTION;
    CPM_PARA_aulLedDeratingV[3] = (uint32)CPM_pCodingArea->Led1.LedVoltageDerating.aucLED_VBAT_DERATING_V3 * CPM_MV_RESOLUTION;
    CPM_PARA_aulLedDeratingV[4] = (uint32)CPM_pCodingArea->Led1.LedVoltageDerating.aucLED_VBAT_DERATING_V4 * CPM_MV_RESOLUTION;
    CPM_PARA_ucLedUBatDeratingDelay = CPM_pCodingArea->Led1.LedVoltageDerating.LED_VBAT_DERATING_DELAY;
    CPM_PARA_ucLedUBatDeratingFilter = CPM_pCodingArea->Led1.LedVoltageDerating.LED_VBAT_DERATING_FILTER;

    // Fail safe error for PCB
    CPM_PARA_aunTzFS[CPM_CFG_MAX_NO_OF_THERMOZONES] = DUCY2PER1328(CPM_PWM_MAX_0_100);

    if (pucData != NULL_PTR)
    {
      pAppMThermo_CodHelper = (tAppMThermo_CodHelper*)&pucData[0];

      for (uint8 ucIdx = 0u; ucIdx < CPM_CFG_MAX_NO_OF_LOGICAL_UNIT; ucIdx++)
      {
        uint8 ucLmmId = (uint8)pAppMThermo_CodHelper[ucIdx].Lmms_Unit;
        uint8 ucDriverId = (uint8)pAppMThermo_CodHelper[ucIdx].Drv_Unit;
        uint8 ucThermozone = (uint8)pAppMThermo_CodHelper[ucIdx].ThermZone_Unit;

        // check if thermozone belongs to the valid range
        if ((ucThermozone > CPM_CFG_MAX_NO_OF_THERMOZONES) || (ucThermozone == 0u))
        {
          ucThermozone = 0u;
        }
        
        if (((ucDriverId != 0u) && (ucDriverId <= CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS)) || (ucDriverId == CPM_HSS3_DRVINDEX))
        {
    
          // check for channel type 
			Cpm_aucChannelType[ucDriverId - 1u] = ((ucLmmId != 0u) && (ucLmmId <= CPM_CFG_MAX_NO_OF_MLC)) ? CPM_CFG_MATRIX_BUCK : CPM_CFG_NON_MATRIX_BUCK;
          CPM_PARA_aucLsTarget2Tz[ucDriverId - 1u] = Cpm_aucChannelType[ucDriverId - 1u] == CPM_CFG_MATRIX_BUCK ? CPM_CFG_NON_MATRIX_BUCK : ucThermozone;// (uint8)pAppMThermo_CodHelper[ucIdx].ThermZone_Unit;

        }
#if defined (CFG_VARIANT_FULL ) || defined(UNIT_TEST) 
    
        *(uint8*)(&CPM_PARA_aucExtSwitch2Tz[0][0] + ucIdx) = ucThermozone; // overlap logical units in the 8x16 matrix of alg
#endif
      }
    }

    (void)memcpy(FANM_PARA_aucExtSwitch2Tz, CPM_PARA_aucExtSwitch2Tz, sizeof(FANM_PARA_aucExtSwitch2Tz));
    (void)memcpy(FANM_PARA_aucLsTarget2Tz, CPM_PARA_aucLsTarget2Tz, sizeof(FANM_PARA_aucLsTarget2Tz));
    (void)memcpy(FANM_PARA_aucTz2Temp, CPM_PARA_aucTz2Temp, sizeof(FANM_PARA_aucTz2Temp));
} // PRQA S 5330 // HIS metrics violation - STST3 = 51' exceeds threshold 50

//-----------------------------------------------------------------------------
/// \brief  CPM_Data_DriverMap
///
/// \descr  This function maps the datas from mappinglist sheet for thermo
///
/// \param  uint8
///
/// \return tAppMThermo_CodHelper
//-----------------------------------------------------------------------------
 STATIC_AL tAppMThermo_CodHelper* CPM_Data_DriverMap(teCPM_MountingSide ucEcuSide)
{
   //PRQA S 311,310 2 // cust is needed
	return ((ucEcuSide) == ((teCPM_MountingSide)eCPM_MountedLeft)) ? (tAppMThermo_CodHelper*)&(CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping) : \
		((ucEcuSide) == (eCPM_MountedRight)) ? (tAppMThermo_CodHelper*)&CPM_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping : (tAppMThermo_CodHelper*)NULL_PTR; 
} 
