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
/// \file   CddLed_Adapter1.c
///
/// \brief  Default adapter
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
// standard includes
#include <Std_Types.h>
#include <AL_Helper.h>
#include <../Cfg/CddLed_RoutCfg.h>
#include <Crc.h>

#include <CddLed.h>
#include <../Cfg/CddLed_Cfg.h>
#ifndef UNIT_TEST
#include <Rte.h>

#endif

#include <CddLed_Adapter.h>
#include <RteCommonTypes.h>
#include <Bsw/Sys/Load/SysLoad.h>
#ifndef UNIT_TEST
#include <SysMonCheck_Data.h>
#else
#define INTERNALCOM_CRC8_RTE_ERROR_MS                    320u   // 320 ms
#endif

#if (CFG_DEV_HOOK_EN == 1u)
#define CDDLED_ADAPTER_CRC8_RTE_HOOK_KEY       0x5A5AA5A5u
STATIC_AL volatile uint32 CddLed_Adapter_ulTesterHookActivation = 0u;
#endif

// PRQA S 3408 1 // Explicit debug code
STATIC_AL tCddLedStatus CddLed_sStatus;

//=============================================================================
// variables
//=============================================================================
CONST_AL  tNvmPara_CodingArea* CddLed_pCodingArea;
STATIC_AL boolean CddLed_ParaInit = FALSE;

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCddLedInit)
SYS_LOAD_MEAS_VAR_DEC(rpCddLed_Cycle)
#endif

//-----------------------------------------------------------------------------
//=============================================================================
//  Prototypes
//=============================================================================
STATIC_AL boolean reCddLedNewTarget(void);
STATIC_AL void    CddLed_Rte_SendLedState(tCddLedStatus sStatus);
STATIC_AL void    CddLed_Rte_SendTgtLedCrcError_ASIL(boolean boStatus);
STATIC_AL boolean CddLed_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
STATIC_AL boolean CddLed_CodingDataValidation(void);

//-----------------------------------------------------------------------------
/// \brief  CddLed_Rte_SendLedState
///
/// \descr  write LED status on RTE port to SysMon
///
/// \param  sStatus : Led channels status
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddLed_Rte_SendLedState(tCddLedStatus sStatus)
{
  tsRte_LedStates sLedState;
  uint8           ucCrc = 0u;
  uint32          ulSizeOfData = 0u;


  for (uint8_fast ucIdx = 0u; ucIdx < CFG_LED_CHANNELS_NR; ucIdx++)
  {
    // PRQA S 4322 1 // Reviewed on 2022.04.15 Onufriciuc F. and Sarghe V. The enumeration types are compatible.
    sLedState.aLedStates[ucIdx].eLedErrStatus = (teRte_LedErrStatus)sStatus.aStatus[ucIdx].Err;
    sLedState.aLedStates[ucIdx].boVinBoostOk = (sStatus.aStatus[ucIdx].Vin == eCddLed_VinOk) ? TRUE : FALSE;
  }

  // Calculate CRC and sent over Rte port
  ulSizeOfData = sizeof(tsRte_ChLedStates) * CFG_LED_CHANNELS_NR;
  // PRQA S 310 1 // Software Architecture , intended behaviour
  ucCrc = Crc_CalculateCRC8H2F((const uint8*)&sLedState.aLedStates[0u].eLedErrStatus, ulSizeOfData, CRC_SEED_INIT_CRC8H2F_VAL);
  sLedState.ucCrc = ucCrc;

  (void)Rte_Write_CddLed_LedState(&sLedState);
}

//-----------------------------------------------------------------------------
/// \brief  CddLed_Rte_SendTgtLedCrcError_ASIL
///
/// \descr  write TgtLed Crc8 Error status on RTE port to SysMon
///
/// \param  boStatus : Status of Crc8 Error check
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddLed_Rte_SendTgtLedCrcError_ASIL(boolean boStatus)
{
  tsRte_TgtLedSig0_FaultStatus_ASIL  TgtLed_FaultStatus_ASIL;
  uint8                              ucCrc = 0u;
  uint32                             ulSizeOfData = 0u;

  TgtLed_FaultStatus_ASIL.boCrc8ErrorStatus = boStatus;

  // Calculate CRC and sent over Rte port
  ulSizeOfData = sizeof(boolean);
  // PRQA S 310 1 // Software Architecture , intended behaviour
  ucCrc = Crc_CalculateCRC8H2F((const uint8*)&TgtLed_FaultStatus_ASIL.boCrc8ErrorStatus, ulSizeOfData, CRC_SEED_INIT_CRC8H2F_VAL);
  TgtLed_FaultStatus_ASIL.ucCrc = ucCrc;

  (void)Rte_Write_CddLed_TgtLed_FaultStatus_ASIL(&TgtLed_FaultStatus_ASIL);
}

//-----------------------------------------------------------------------------
/// \brief  riCddLedInit
///
/// \descr  Init runnable to be called at MCU startup
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void riCddLedInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCddLedInit)
#endif
  CONST_AL boolean boCodingValidity = CddLed_CodingDataValidation();
  CddLed_Init();

  if (boCodingValidity != FALSE)
  {
    CddLed_ParaInit = TRUE;
    CddLed_SetPara(CddLed_ParaInit);
    CddLed_GetStatus(&CddLed_sStatus);
    CddLed_Rte_SendLedState(CddLed_sStatus);
    (void)Rte_Write_CddLed_Status(&CddLed_sStatus);
  }

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCddLedInit)
#endif
}


//-----------------------------------------------------------------------------
/// \brief  reCddLedNewTarget
///
/// \descr  Function to be called on new target values
///         This shall be done event triggered by writing RTE target value
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean reCddLedNewTarget(void)
{
  STATIC_UT(boolean, boCrcFailure, FALSE);
  STATIC_UT(TIMER,   ulCrcTimer,      0u);
  STATIC_UT_NOINIT(tsRte_TgtLedSig0_ASIL, sASIL_Target_ASIL);
  tsRte_TgtLedSig0_ASIL           sASIL_Target;
  tCddLedTarget                   sCddLedTarget;
  boolean                         boASIL_Target_FaultStatus = FALSE;
  uint8                           ucCrc         = 0u;
  uint32                          ulSizeOfData  = 0u;
  boolean                         boIsTiFuSa = FALSE;

  //read target //TBD
  (void)Rte_Read_SysMon_TgtLedSig_sVal(&sASIL_Target);

  // Calculate Crc 8 bits 0x2F (x8 + x5 +x3 + x2 + x +1) to ASIL relevant RTE messages
  ulSizeOfData = sizeof(tsRte_TgtLedSig0) * CFG_LED_CHANNELS_NR;
  // PRQA S 310 1 // Software Architecture , intended behaviour
  ucCrc = Crc_CalculateCRC8H2F((const uint8*)&sASIL_Target.asTgtVal[0u].unCurrent, ulSizeOfData, CRC_SEED_INIT_CRC8H2F_VAL);

  // Developer test using hook in order to corrupt the CRC8 between Rte ports
#if (CFG_DEV_HOOK_EN == 1u)
  if (CddLed_Adapter_ulTesterHookActivation == CDDLED_ADAPTER_CRC8_RTE_HOOK_KEY)
  {
    sASIL_Target.ucCrc += 1u;
  }
  else
  {
    // nothing to do
  }
#endif

  // If calculated Crc is matching the transmitted one
  if (ucCrc == sASIL_Target.ucCrc)
  {
    // Data can be used by CddLed because the CRC matches with the one sent from SysMon
    sASIL_Target_ASIL = sASIL_Target;

    // Reset Rte CRC8 failure flag
    boCrcFailure = FALSE;

    // Reset the CRC8 Rte Error flag for Target LED ASIL
    boASIL_Target_FaultStatus = FALSE;
  }
  else
  {
    // Crc not equal as the recieved one
    // First time appearance of Rte CRC8 error
    if (boCrcFailure == FALSE)
    {
      // Get time stamp
      ulCrcTimer = TimerGetTick();
      // Set CRC8 Failure flag
      boCrcFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(ulCrcTimer) >= UTILTIME_MSEC(INTERNALCOM_CRC8_RTE_ERROR_MS))
      {
        // Set the CRC8 Rte Error flag for Target LED ASIL
        boASIL_Target_FaultStatus = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
  }

  //send target
  for (uint32 ulIdx = 0u; ulIdx < CFG_LED_CHANNELS_NR; ulIdx++)
  {
    // Need to turn OFF TI channel in case of CRC corrupted
    if (boASIL_Target_FaultStatus != FALSE)
    {
      boIsTiFuSa = SysMonCheck_Data_IsTurnIndicatorFuSa((uint8)ulIdx);

      // Is the channel TI FuSa ?
      if (boIsTiFuSa != FALSE)
      {
        sCddLedTarget.aTarget[ulIdx].unCurrent_mA        = 0u;
        sCddLedTarget.aTarget[ulIdx].unDutyCycle_1_32768 = 0u;
      }
      else
      {
        // Pass the values because the channel is not TI FuSa
        sCddLedTarget.aTarget[ulIdx].unCurrent_mA        = sASIL_Target_ASIL.asTgtVal[ulIdx].unCurrent;
        sCddLedTarget.aTarget[ulIdx].unDutyCycle_1_32768 = sASIL_Target_ASIL.asTgtVal[ulIdx].unDutyCycle;
      }
    }
    else
    {
      // Pass all the values because there is no CRC8 error
      sCddLedTarget.aTarget[ulIdx].unCurrent_mA        = sASIL_Target_ASIL.asTgtVal[ulIdx].unCurrent;
      sCddLedTarget.aTarget[ulIdx].unDutyCycle_1_32768 = sASIL_Target_ASIL.asTgtVal[ulIdx].unDutyCycle;
    }
  }

  CddLed_SetTarget(&sCddLedTarget);

  return boASIL_Target_FaultStatus;
}

//-----------------------------------------------------------------------------
/// \brief  rpCddLed_Cycle
///
/// \descr  Cyclic runnable adapter for CddLed_Cycle at every 5ms
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void rpCddLed_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCddLed_Cycle)
#endif

  tCddLedDriverSettings    DriverSettings;
  tsRte_ChLedSettings      sRte_ChLedSettings;
  boolean                  boTgtLed_ASIL_FaultStatus = FALSE;
  //tCddLedStatus Status;
  CONST_AL boolean boCodingValidity = CddLed_CodingDataValidation();

  //set new target values only when coding is valid
  if (boCodingValidity != FALSE)
  {
    if (CddLed_ParaInit == FALSE)
    {
      CddLed_ParaInit = TRUE;
      CddLed_SetPara(CddLed_ParaInit);
    }


    (void)Rte_Read_CtrlLed_LedSettings_sVal(&sRte_ChLedSettings);
    DriverSettings.ulDisableErrE2E = /*0u;     */sRte_ChLedSettings.ulDisableErrE2E;
    DriverSettings.ulDisableErrOpenLoad = /*0u;     */sRte_ChLedSettings.ulDisableErrOpenLoad;
    DriverSettings.ulDisableErrOverCurrent = /*0u;     */sRte_ChLedSettings.ulDisableErrOverCurrent;
    DriverSettings.ulDisableErrShortToGnd = /*2160u;  */sRte_ChLedSettings.ulDisableErrShortToGnd;
    DriverSettings.ulDisableErrShortToUbat = /*0u;     */sRte_ChLedSettings.ulDisableErrShortToUbat;
    DriverSettings.ulDisableErrSpi = /*0u;     */sRte_ChLedSettings.ulDisableErrSpi;
    DriverSettings.ulDisableErrThermalShutdown = /*0u;     */sRte_ChLedSettings.ulDisableErrThermalShutdown;
    DriverSettings.ulDisableErrUnderVoltage = /*0xFFFu; */sRte_ChLedSettings.ulDisableErrUnderVoltage;
    DriverSettings.ulDisableErrOverVoltage = /*0xFFFu; */sRte_ChLedSettings.ulDisableErrOverVoltage;

    CddLed_DriverSettings(&DriverSettings);
    //set target values
    boTgtLed_ASIL_FaultStatus = reCddLedNewTarget();

    CddLed_Cycle20ms();

    CddLed_GetStatus(&CddLed_sStatus);

    (void)Rte_Write_CddLed_Status(&CddLed_sStatus);

    CddLed_Rte_SendLedState(CddLed_sStatus);
    CddLed_Rte_SendTgtLedCrcError_ASIL(boTgtLed_ASIL_FaultStatus);
  }

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCddLed_Cycle)
#endif
} // PRQA S 5324 1 // Software Architecture

//-----------------------------------------------------------------------------
/// \brief  CddLed_Get_CodingPara
///
/// \descr  this function get coding params via RTE
///
/// \param  *sCodingParam
///
/// \return void
//-----------------------------------------------------------------------------
void CddLed_Get_CodingPara(tsCddLed_CodingParam *sCodingParam)
{
  tsRteCodingParameters *sRteCoding;
  //PRQA S 310 1 //cust needed
  sRteCoding = (tsRteCodingParameters*)sCodingParam;
  //read coding 
  (void)Rte_Read_CodM_CddLed_Para(sRteCoding);
}


//-----------------------------------------------------------------------------
/// \brief  CddLed_CodingDataValidation
///
/// \descr  get and handle coding parameters for CddLed module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
STATIC_AL boolean CddLed_CodingDataValidation(void)
{
  tsCddLed_CodingParam sCodingParameters;

  //get coding data via RTE
  CDDLED_RTE_RE_GET_CODING_DATA(&sCodingParameters)
  //get coding data and return validity of this
  CONST_AL boolean boCodingValidity = CddLed_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

  //return validity of coding
  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  CddLed_ParaFct0
///
/// \descr  this function get coding params and validity of coding data 
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean CddLed_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;
  CddLed_pCodingArea = pData;
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



