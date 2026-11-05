// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

//-----------------------------------------------------------------------------
/// \file  CddTle94x1.c
///
/// \brief  SBC Infineon TLE9471/TLE9461 specific complex device driver
///
/// \descr  System Basic Chip
///
/// \author Diana Ursan
/// \e-mail: elena-diana.ursan[at]marelli.com
///
//-----------------------------------------------------------------------------

//=============================================================================
// Standard / system header file includes
//=============================================================================
#include <AL_Helper.h>
#include <CddSpi.h>
#include <CddSbc_Cfg.h>
#include <CddSbc_Types.h>
#include <Util_Time.h>
#include <IoHwAbUser.h>
//=============================================================================
//  Project-specific header file includes
//=============================================================================
#include <CddTle94x1.h>
#include <CddTle94x1_Cfg.h>
#include <CddTle94x1_Regs.h>
#include <CddTle94x1_Com.h>
#include <CddTle94x1_Types.h>
#include <../../St126/Cdd/CddSbc/CddSbc_Cfg.h>

//=============================================================================
// Global variable
//=============================================================================

// macro representing the wait interval to enter in sleep mode
#define CDDTLE94X1_SLEEPTMEOUT_US     50u

#define CDDTLE94X1_SAFTYCNT        20000u

#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
#define CDDTLE94X1_TSD_HOOK_ENBL_VAL 20212022u
STATIC_AL volatile uint32 CddTle94x1_ulTSDHook_Activ_Val = 0u;
#endif

//=============================================================================
// Local variable
//=============================================================================
// Structure to store the Error Flags
STATIC_AL tsCddTle94x1_ErrorState CddTle94x1_sErrorType = { .boInitStatRead = FALSE,
                                                            .boInitCtrlWrite = FALSE,
                                                            .boGoToStop_Failure = FALSE,
                                                            .boGotoStop_SpiFailure = FALSE,
                                                            .boGoToSleep_Failure = FALSE,
                                                            .boGotoSleep_SpiFailure = FALSE,
                                                            .boCyclic_SPI_Communication = FALSE,
                                                            .boCyclic_CanMode = FALSE,
                                                            .boReadWKStat_Failure = FALSE,
                                                            .boReadSUPStat_Failure = FALSE,
                                                            .boScheduleTableFull = FALSE,
                                                            .boCanModeError = FALSE,
                                                            .boCanChannelError = FALSE,
                                                            .boSpiWdgFailure = FALSE,
                                                            .boReadWdgStat_Failure = FALSE,
                                                            .boErrorReset = FALSE,
                                                            .boTSDError = FALSE,
                                                            .boShorttoVBAT = FALSE,
                                                            .boShorttoGND = FALSE };

// Structure to store the SPI Control and Status registers
STATIC_AL volatile tsCddTle94x1_DataMirror CddTle94x1_sDataMirror;

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
// Counter to track the SPI cyclic communication
STATIC_AL uint16 CddTle94x1_unErrorSequenceCounter = 0u;
#endif

#if (CDDSBC_CFG_INIT_OPERATION == STD_ON)
// Variable to store the power on reset information after poweron
STATIC_AL uint8 CddTle94x1_ucSUP_STAT_0_POR = 0u;
// Variable to store the power on reset information after poweron
STATIC_AL uint8 CddTle94x1_ucWK_STAT_0_CANWU = 0u;
// Variable to store the dev status information after poweron
STATIC_AL uint8 CddTle94x1_ucDEV_STAT_DEV_STAT = 0u;
// Variable to store the thermal stutdown status information
STATIC_AL uint8 CddTle94x1_ucTHERMO_STAT_TSD2 = 0u;
// Variable to store the VCC2 pin status
STATIC_AL uint8 CddTle94x1_ucSUP_STAT_0_VCC1_UV = 0u;
#endif

#if (CDDSBC_CFG_WK_INPUT == STD_ON)
// Variable to store wake up status
STATIC_AL uint8 CddTle94x1_ucWK_STAT_0_WK_WU = 0u;
#endif

#if ((CDDSBC_CFG_STORE_RESETREASON == STD_ON) && (CDDSBC_CFG_WATCHDOG == STD_ON))
// Variable to indicate watchdog reset
STATIC_AL boolean CddTle94x1_boStatusWdgReset = FALSE;
#endif

#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
// Variable to store the reset reason
STATIC_AL uint8 CddTle94x1_ucSBCResetReason = 0u;
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
// Variable to indicate the message type
STATIC_AL teCddTle94x1_MsgType CddTle94x1_eDefaultMsg = eBUS_CTRL_0;
#endif

STATIC_AL TIMER CddTle94x1_ulSleepTimeOut = 0u;

//=============================================================================
// Prototypes
//=============================================================================
#if (CDDSBC_CFG_INIT_OPERATION == STD_ON)
STATIC_AL void CddTle94x1_InitSettings(void);
STATIC_AL boolean CddTle94x1_InitStatRead(void);
STATIC_AL boolean CddTle94x1_Save_WK_STAT_0(void);
STATIC_AL boolean CddTle94x1_Save_SUP_STAT_0(void);
#endif

STATIC_AL boolean CddTle94x1_WriteClearReg(uint8 ucAddress, uint16 unDataField);
STATIC_AL uint16 CddTle94x1_ReadReg(uint8 ucAddress);

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
STATIC_AL void CddTle94x1_CbkGetSupState0(uint32 ulData, uint16 unSentVal);
STATIC_AL void CddTle94x1_CbkGetWakeUpStatus(uint32 ulData, uint16 unSentVal);
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
STATIC_AL void CddTle94x1_CbkSetCanMode(uint32 ulData, uint16 unSentVal);
STATIC_AL void CddTle94x1_CbkGetCanMode(uint32 ulData, uint16 unSentVal);
STATIC_AL void CddTle94x1_CbkGetBusState(uint32 ulData, uint16 unSentVal);
STATIC_AL void CddTle94x1_CbkSetPWM(uint32 ulData, uint16 unSentVal);
#endif
STATIC_AL boolean CddTle94x1_ValidateCanMode(uint8 ucCanMode);
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
STATIC_AL void CddTle94x1_ErrorSequenceCounterInc(void);
STATIC_AL void CddTle94x1_ErrorSequenceCounterClear(void);
#endif

#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
STATIC_AL void CddTle94x1_StoreSBCResetReason(void);
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
STATIC_AL void CddTle94x1_SetWdgWithSingleOperation(void);
#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
STATIC_AL void CddTle94x1_CbkSetWDCtrl(uint32 ulData, uint16 unSentVal);
#endif

#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
STATIC_AL void CddTle94x1_GetWatchdogFlag(void);
#endif
#endif

#if (CDDSBC_CFG_VCC2_OPERATION == STD_ON)
STATIC_AL void CddTle94x1_SetVCC2(uint8 ucCmd);
STATIC_AL void CddTle94x1_CbkSetVCC2(uint32 ulData, uint16 unSentVal);
STATIC_AL void CddTle94x1_ReadThermStatReg(void);
STATIC_AL void CddTle94x1_CbkReadThermStatReg(uint32 ulData, uint16 unSentVal);
#endif

//=============================================================================
// Function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_Init
///
/// \descr  Initialize TLE9471 SBC complex device driver by using SPI Transfer Message communication.
///          Preconditions:  CddSpi module should be initialized first
///          1. step:  Read TLE9471 Status Registers (WK_STAT_0 and SUP_STAT_0) and save wake-up reasons for later use.
///          2. step:  Handle the watchdog reset reason
///          3. step:  Write TLE9471 Control Registers to configure SBC.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Init(void)
{
  // Read and debounce TLE9471 Status Registers
  if (CddTle94x1_InitStatRead() != FALSE)
  {
#if (CDDSBC_CFG_WATCHDOG == STD_ON)
    // If the read and save ws successsful hanle the watchdog reset reason
    CddTle94x1_GetWatchdogFlag();
#endif
    // If the read and save was successful write the control registers
    CddTle94x1_InitSettings();
  }
  else
  {
    // do nothing
  }
#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
  CddTle94x1_StoreSBCResetReason();
#endif
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_InitStatRead
///
/// \descr  During the initialization phase wake source signalization flags from WK_STAT_0 need to be saved in order to determin the cause of the wake-up later on.
///         The power on reset flag from SUP_STAT_0 is to be read and saved after in order to detect if it was a power on reset.
//          The function will return FALSE if the read and save was unsuccesful and TRUE if the operation was succesful.
///
/// \param  void
///
/// \return boolean boReturn
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTle94x1_InitStatRead(void)
{
  boolean boReturn = FALSE;

  // Tries to read and save the wake-up and supply status registers
  if ((CddTle94x1_Save_WK_STAT_0() != FALSE) && ((CddTle94x1_Save_SUP_STAT_0() != FALSE))) // PRQA S 3415 // No side effects since both functions return o boolean.
  {
    // Successful read and save
    boReturn = TRUE;
    // Clear the error Flag
    CddTle94x1_sErrorType.boInitStatRead = FALSE;
  }
  else
  {
    // Set the error Flag
    CddTle94x1_sErrorType.boInitStatRead = TRUE;
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_Save_WK_STAT_0
///
/// \descr  During the initialization phase reads the WK_STAT_0 register by calling
///         the CddTle94x1_ReadReg() function and saves the Wake-Up flag of the CAN0.
///
/// \param  void
///
/// \return boolean boReturn
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTle94x1_Save_WK_STAT_0(void)
{
  boolean boReturn = FALSE;

  // read the spi register with the register addresse
  uint16 unReadReg = CddTle94x1_ReadReg(CDDTLE94X1_REGS_WK_STAT_0_ADR);

  // If there were no read errors
  if (unReadReg != CDDTLE94X1_CFG_ERROR)
  {
    // Store the registers content in the memory
    CddTle94x1_sDataMirror.StatRx.WK_STAT_0_Register.uData.ucWord = (uint8)unReadReg;
    CddTle94x1_ucWK_STAT_0_CANWU = CddTle94x1_sDataMirror.StatRx.WK_STAT_0_Register.uData.sBit.bCAN_WU;
    #if (CDDSBC_CFG_WK_INPUT == STD_ON)
    CddTle94x1_ucWK_STAT_0_WK_WU = CddTle94x1_sDataMirror.StatRx.WK_STAT_0_Register.uData.sBit.bWK_WU;
    #endif
    CddTle94x1_sErrorType.boReadWKStat_Failure = FALSE;
    boReturn = TRUE;
  }
  else
  {
    CddTle94x1_sErrorType.boReadWKStat_Failure = TRUE;
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_Save_SUP_STAT_0
///
/// \descr  During the initialization phase reads the SUP_STAT_0 register by
///         calling the CddTle94x1_ReadReg() function and saves the Power On Reset flag.
///
/// \param  void
///
/// \return boolean boReturn
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTle94x1_Save_SUP_STAT_0(void)
{
  boolean boReturn = FALSE;

  uint16 unReadReg = CddTle94x1_ReadReg(CDDTLE94X1_REGS_SUP_STAT_0_ADR);

  // If there were no read errors
  if (unReadReg != CDDTLE94X1_CFG_ERROR)
  {
    // Store the registers content in the memory
    CddTle94x1_sDataMirror.StatRx.SUP_STAT_0_Register.uData.ucWord = (uint8)unReadReg;
    CddTle94x1_ucSUP_STAT_0_POR = CddTle94x1_sDataMirror.StatRx.SUP_STAT_0_Register.uData.sBit.bPOR;
    CddTle94x1_ucSUP_STAT_0_VCC1_UV = CddTle94x1_sDataMirror.StatRx.SUP_STAT_0_Register.uData.sBit.bVCC1_UV;
    CddTle94x1_sErrorType.boReadSUPStat_Failure = FALSE;
    boReturn = TRUE;
  }
  else
  {
    CddTle94x1_sErrorType.boReadSUPStat_Failure = TRUE;
  }

  // Return the status
  return boReturn;
}

#if ((CDDSBC_CFG_WATCHDOG == STD_ON) && (CDDSBC_CFG_STORE_RESETREASON == STD_ON))
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_GetWatchdogFlag
///
/// \descr  During the initialization phase reads the DEV_STAT and THERM_STAT register by calling
///         the CddTle94x1_ReadReg() function and handels the watchdog reset reason.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_GetWatchdogFlag(void)
{
    // read the spi register with the register addresse
    uint16 unReadReg_DEV_STAT = CddTle94x1_ReadReg(CDDTLE94X1_REGS_DEV_STAT_ADR);
    uint16 unReadReg_THERM_STAT = CddTle94x1_ReadReg(CDDTLE94X1_REGS_THERM_STAT_ADR);

    // If there were no read errors
    if ( (unReadReg_DEV_STAT != CDDTLE94X1_CFG_ERROR) && (unReadReg_THERM_STAT != CDDTLE94X1_CFG_ERROR) )
    {
      // If the read was successfull, store the registers content in the memory
      CddTle94x1_sDataMirror.StatRx.DEV_STAT_Register.uData.ucWord = (uint8)unReadReg_DEV_STAT;
      CddTle94x1_ucDEV_STAT_DEV_STAT = CddTle94x1_sDataMirror.StatRx.DEV_STAT_Register.uData.sBit.bDEV_STAT;
      CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord = (uint8)unReadReg_THERM_STAT;
      CddTle94x1_ucTHERMO_STAT_TSD2 = (uint8)CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD2;
      CddTle94x1_sErrorType.boReadWdgStat_Failure = FALSE;
    }
    else
    {
      // Set the error flag because the watchdog status was not successfully read
      CddTle94x1_sErrorType.boReadWdgStat_Failure = TRUE;
    }
    // if the value CddTle94x1_ucDEV_STAT_DEV_STAT is set, CddTle94x1_ucTHERMO_STAT_TSD2 and CddTle94x1_ucSUP_STAT_0_VCC1_UV are not set then watchdog reset is present
    if ( (CddTle94x1_ucDEV_STAT_DEV_STAT == 1u) && (CddTle94x1_ucTHERMO_STAT_TSD2 == 0u) && (CddTle94x1_ucSUP_STAT_0_VCC1_UV == 0u) )
    {
      CddTle94x1_boStatusWdgReset = TRUE;
    }
    else
    {
      CddTle94x1_boStatusWdgReset = FALSE;
    }

}
#endif

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_InitSettings
///
/// \descr  Write initialization configuration data to TLE9471 control registers:
///         clear the flags, clear the bus communication, configure the CAN channel,
///         turn on the charge pump and VCC2 and thermal shutdown monitoring.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_InitSettings(void)
{
  // Clear the power on reset flag in SUP_STAT_0 Register
  CddTle94x1_sDataMirror.StatTx.SUP_STAT_0_Register.uData.ucWord = CDDTLE94X1_CFG_CLEAR_ALL;

  // Clear the Wake-up flag of the CAN0 in WK_STAT_0 Register
  CddTle94x1_sDataMirror.StatTx.WK_STAT_0_Register.uData.ucWord = CDDTLE94X1_CFG_CLEAR_ALL;

  // Clear the bus communication status DEV_STAT Register
  CddTle94x1_sDataMirror.StatTx.DEV_STAT_Register.uData.ucWord = CDDTLE94X1_CFG_CLEAR_ALL;

  // Update the CAN bit in the BUS_CTRL_0 register.
  CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.sBit.bCAN = CDDSBC_CFG_CAN_CHANNEL_0_INIT_CFG;

  // Set the charge pump bit in the HW_CTRL_0 register.CP_EN
  CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_0_Register.uData.sBit.bCP_EN = CDDTLE94X1_CFG_ENABLE;

  // Set SS_MOD_FR in the HW_CTRL_2 regiester.SS_MOD_FR
  CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_2_Register.uData.sBit.bSS_MOD_FR = CDDTLE94X1_CFG_SS_MOD_FR_03;

  // Set the thermal shutdown threshold configuraton bit in the HW_CTRL_3 register.TSD_THR
  CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_3_Register.uData.sBit.bTSD_THR = CDDTLE94X1_CFG_TSD_THR_1;

  // Set the rest Delay Time Selection bit in the HW_CTRL_1 register.RSTN_DEL
  CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_1_Register.uData.sBit.bRSTN_DEL = CDDTLE94X1_CFG_RSTN_DEL_tRD2;

  // Set SBC to enter Restart/Fail-safe mode in case of over voltage in the M_S_CTRL register.bVCC1_OV_RST
  CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC1_OV_RST = CDDTLE94X1_CFG_VCC1_OV_RST_1;

  // Set VCC2_ON to normal mode in the M_S_CTRL register.VCC2_ON
  CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON = CDDTLE94X1_CFG_VCC2_ON1;

#if (CDDSBC_CFG_GPIO == STD_ON)
  //100Hz is a default value for Sbc frequence

  // Set duty cycle in PWM_DC in the PWM_CTRL reigster to 0
  CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.sBit.bPWM_DC = CDDTLE94X1_CFG_PWM_DC_0;

  // Set GPIO with the mode (Low-Side Switch controlled by PWM) in the GPIO_CTRL register.GPIO
  CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.sBit.bGPIO = CDDTLE94X1_CFG_GPIO_110;
#endif

  // Set SBC mode to normal mode in the M_S_CTRL register.MODE
  CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bMODE = CDDTLE94X1_CFG_NORMAL_MODE;

  // Write the data to the registers and check if it was successful or not
  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_SUP_STAT_0_ADR, CddTle94x1_sDataMirror.StatTx.SUP_STAT_0_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.StatRx.SUP_STAT_0_Register.uData.ucWord = CddTle94x1_sDataMirror.StatTx.SUP_STAT_0_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_WK_STAT_0_ADR, CddTle94x1_sDataMirror.StatTx.WK_STAT_0_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.StatRx.WK_STAT_0_Register.uData.ucWord = CddTle94x1_sDataMirror.StatTx.WK_STAT_0_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_DEV_STAT_ADR, CddTle94x1_sDataMirror.StatTx.DEV_STAT_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.StatRx.DEV_STAT_Register.uData.ucWord = CddTle94x1_sDataMirror.StatTx.DEV_STAT_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_BUS_CTRL_0_ADR, CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_HW_CTRL_0_ADR, CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_0_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_0_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_0_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_HW_CTRL_2_ADR, CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_2_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_2_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_2_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_HW_CTRL_3_ADR, CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_3_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_3_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_3_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_HW_CTRL_1_ADR, CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_1_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.HW_CTRL_1_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_1_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

#if (CDDSBC_CFG_GPIO == STD_ON)
    if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_PWM_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_GPIO_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.GPIO_CTRL_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }
#endif

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_M_S_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boInitCtrlWrite = TRUE;
  }

  // prepare for the first SPI-Command in SPI-Cyclic Operation
#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
  CddSbc_InsertDefaultMessage();
#endif

  // PRQA S 5310 1 // compactness and readability
}


#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_StoreSBCResetReason
///
/// \descr  Read MCU register and store the Reset Reason
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_StoreSBCResetReason(void)
{
  if (CddTle94x1_ucSUP_STAT_0_POR == 1u)
  // if the value of CddTle94x1_ucSUP_STAT_0_POR is set then there is a power on reset
  {
    CddTle94x1_ucSBCResetReason = (uint8)ePowerOnResetSBC;
  }
#if (CDDSBC_CFG_WATCHDOG == STD_ON)
  else if (CddTle94x1_boStatusWdgReset != FALSE)
  {
    CddTle94x1_ucSBCResetReason = (uint8)eWatchdogReset;
  }
#endif
  else if (CddTle94x1_ucWK_STAT_0_CANWU == 1u)
  // if the value of CddTle94x1_ucWK_STAT_0_CANWU is set then there is a CAN wake up reset
  {
    CddTle94x1_ucSBCResetReason = (uint8)eCANWakeUpReset;
  }
  #if (CDDSBC_CFG_WK_INPUT == STD_ON)
  else if (CddTle94x1_ucWK_STAT_0_WK_WU == 1u)
  // if the value of CddTle94x1_ucWK_STAT_0_WK_WU is set then there is a Input wake up reset
  {
    CddTle94x1_ucSBCResetReason = (uint8)eInputWakeUpReset;
  }
  #endif
  else
  {
    CddTle94x1_ucSBCResetReason = (uint8)eNoResetSBC;
  }
  //PRQA S 5336 1 // program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_GetResetReason
///
/// \descr  Calls the hardware specific function to get the reset reason
///
/// \param -
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CddTle94x1_GetSBCResetReason(void)
{
  return (uint8)CddTle94x1_ucSBCResetReason;
}

#endif

#if (CDDSBC_CFG_SLEEPMODE == STD_ON)
//-----------------------------------------------------------------------------
/// \brief   CddTle94x1_SetSleepMode
///
/// \descr   Set SBC in Sleep Mode.
///          Because Transfer Message mode is used to communicate over SPI, cyclic operation mode must be stopped, by calling SPI_Stop() before SetSleepMode operation is executed.
///          Before setting the SBC to sleep mode, the wake-up and supply status registers shall to be cleared.
///          Set the VCC2 output to OFF and deactiviate the Charge Pump.
///          Set the CAN module to Wake Capable Mode
///          Write the settings to the control registers and send the SLEEP_MODE command.
///          The following error cases are handled:
///             -The driver is unable to send the commands to the TLE 9471 SBC device therefore sets the
///             GoToSleep_SpiFailure error flag.
///             - The Sleep Mode command was successfully sent but the device is unable to reach
///             Sleep Mode after waiting[MAX_WAITCNT] cycles which corresponds with 0.01[ms]
///             therefore sets  GoToSleep_SpiFailure error flag.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_SetSleepMode(void)
{
  volatile uint16 unIndex;
  uint32_least ulCntProtect = 0u;

  // Clear the Wake-up flag of the CAN0 in WK_STAT_0 Register
  CddTle94x1_sDataMirror.StatTx.WK_STAT_0_Register.uData.ucWord = CDDTLE94X1_CFG_CLEAR_ALL;

  // Clear the power on reset flag in SUP_STAT_0 Register
  CddTle94x1_sDataMirror.StatTx.SUP_STAT_0_Register.uData.ucWord = CDDTLE94X1_CFG_CLEAR_ALL;

  // Deactiviate the Charge Pump in the HW_CTRL_0 register.CP_EN
  CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_0_Register.uData.sBit.bCP_EN = CDDTLE94X1_CFG_DISABLE;

  // set CAN mode to wake capable mode in the BUS_CTRL_0 register.CAN
  CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.sBit.bCAN = CDDTLE94X1_CFG_CAN_WAKE_ON;

#if (CDDSBC_CFG_WK_INPUT == STD_ON)
  CddTle94x1_sDataMirror.CtrlTx.WK_CTRL_1_Register.uData.sBit.bWK_EN = CDDTLE94X1_CFG_ENABLE;
#endif

#if (CDDSBC_CFG_GPIO == STD_ON)
  // Set duty cycle in PWM_DC in the PWM_CTRL reigster to 0
  CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.sBit.bPWM_DC = CDDTLE94X1_CFG_PWM_DC_0;

  //Switch LSS off
  CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.sBit.bGPIO = CDDTLE94X1_CFG_GPIO_100;
#endif

  // Set SBC mode to sleep mode in the M_S_CTRL register.MODE
  CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bMODE = CDDTLE94X1_CFG_SLEEP_MODE;

  // IMPORTANT!!! The order of the commands is important. Don't change it.
  // Write the data to the registers and check if it was successful or not
  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_WK_STAT_0_ADR, CddTle94x1_sDataMirror.StatTx.WK_STAT_0_Register.uData.ucWord) == FALSE)
  {
    // The commands were not sent to the SBC device, the SPI communication failed.
    CddTle94x1_sErrorType.boGotoSleep_SpiFailure = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_SUP_STAT_0_ADR, CddTle94x1_sDataMirror.StatTx.SUP_STAT_0_Register.uData.ucWord) == FALSE)
  {
    // The commands were not sent to the SBC device, the SPI communication failed.
    CddTle94x1_sErrorType.boGotoSleep_SpiFailure = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_HW_CTRL_0_ADR, CddTle94x1_sDataMirror.CtrlTx.HW_CTRL_0_Register.uData.ucWord) == FALSE)
  {
    // The commands were not sent to the SBC device, the SPI communication failed.
    CddTle94x1_sErrorType.boGotoSleep_SpiFailure = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_BUS_CTRL_0_ADR, CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.ucWord) == FALSE)
  {
    // The commands were not sent to the SBC device, the SPI communication failed.
    CddTle94x1_sErrorType.boGotoSleep_SpiFailure = TRUE;
  }

#if (CDDSBC_CFG_WK_INPUT == STD_ON)
  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_WK_CTRL_1_ADR, CddTle94x1_sDataMirror.CtrlTx.WK_CTRL_1_Register.uData.ucWord) == FALSE)
  {
    // The commands were not sent to the SBC device, the SPI communication failed.
    CddTle94x1_sErrorType.boGotoSleep_SpiFailure = TRUE;
  }
#endif

#if (CDDSBC_CFG_GPIO == STD_ON)
  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_PWM_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.ucWord) == FALSE)
  {
    // The commands were not sent to the SBC device, the SPI communication failed.
    CddTle94x1_sErrorType.boGotoSleep_SpiFailure = TRUE;
  }

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_GPIO_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.GPIO_CTRL_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.ucWord;
  }
#endif

  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_M_S_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord) != FALSE)
  {
    // The registers have been updated
    // Wait for 0.01 [ms]
    CddTle94x1_ulSleepTimeOut = TimerGetTick();

    while ((TimerGetTimeSince(CddTle94x1_ulSleepTimeOut) < UTILTIME_USEC(CDDTLE94X1_SLEEPTMEOUT_US)) && (ulCntProtect < CDDTLE94X1_SAFTYCNT))
    {
      // wait 50us
      //increment the counter used for protection against remaining in this while.
      ulCntProtect++;
    }

    // Set the error flag // The Sbc could not reach the sleep mode after x ms // Should not reach this point
    CddTle94x1_sErrorType.boGoToSleep_Failure = TRUE;
  }
  else
  {
    // The commands were not sent to the SBC device, the SPI communication failed.
    CddTle94x1_sErrorType.boGotoSleep_SpiFailure = TRUE;
  }
}// PRQA S 5310 1 // compactness and readability
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
 //-----------------------------------------------------------------------------
 /// \brief  CddTle94x1_SetCanMode
 ///
 /// \descr  Set the specific SBC CAN transceiver to a chosen functional mode
 ///
 /// \param  uint8 ucCanChannel        - SBC CAN transceiver
 ///          uint8 ucCanMode           - CAN transceiver mode
 ///
 /// \return void
 //-----------------------------------------------------------------------------
void CddTle94x1_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode)
{
  if (ucCanChannel == CDDSBC_CFG_CAN_CH0)
  {
    if (CddTle94x1_ValidateCanMode(ucCanMode) != FALSE)
    {
      CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.sBit.bCAN = ucCanMode;

      if (CddSpi_GetState() == CDDSPI_STATE_SINGLE_OPERATION)
      {
        if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_BUS_CTRL_0_ADR, CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.ucWord) != FALSE)
        {
          CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.ucWord;
        }
      }
#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
      else if (CddSpi_GetState() == CDDSPI_STATE_CYCLIC_OPERATION)
      {
        (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_BUS_CTRL_0_ADR, CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.ucWord, CDDTLE94X1_CFG_WRITE_CMD, NULL_PTR);
        (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_BUS_CTRL_0_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, CddTle94x1_CbkSetCanMode);
      }
#endif
      else
      {
        // do nothing
      }
    }
    else
    {
      // do nothing
    }
    CddTle94x1_sErrorType.boCanChannelError = FALSE;
  }
  else
  {
    CddTle94x1_sErrorType.boCanChannelError = TRUE;
  }
}
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_GetCanMode
///
/// \descr  Get the SBC CAN transceiver mode.
///
/// \param  uint8 ucCanChannel        - SBC CAN transceiver
///
/// \return uint8 ucReturn            CAN mode
//-----------------------------------------------------------------------------
uint8 CddTle94x1_GetCanMode(uint8 ucCanChannel)
{
  uint8 ucReturn = 0u;
  uint16 unReadReg = 0u;

  if (ucCanChannel == CDDSBC_CFG_CAN_CH0)
  {
    if (CddSpi_GetState() == CDDSPI_STATE_SINGLE_OPERATION)
    {
      unReadReg = CddTle94x1_ReadReg(CDDTLE94X1_REGS_BUS_CTRL_0_ADR);
      // If there were no read errors
      if (unReadReg != CDDTLE94X1_CFG_ERROR)
      {
        // Store the registers content in the memory
        CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord = (uint8)unReadReg;
      }
    }

    ucReturn = CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.sBit.bCAN;
  }
  else
  {
    // do nothing
  }
  return ucReturn;
}
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_GetCanUV
///
/// \descr  Get the undervoltage bit of CAN bus
///
/// \param  void
///
/// \return uint8 ucReturn
//-----------------------------------------------------------------------------
uint8 CddTle94x1_GetCanUV(void)
{
  uint8 ucReturn = 0u;
  uint16 unReadReg = 0u;

  if (CddSpi_GetState() == CDDSPI_STATE_SINGLE_OPERATION)
  {
    unReadReg = CddTle94x1_ReadReg(CDDTLE94X1_REGS_BUS_STAT_ADR);
    // If there were no read errors
    if (unReadReg != CDDTLE94X1_CFG_ERROR)
    {
      // Store the registers content in the memory
      CddTle94x1_sDataMirror.StatRx.BUS_STAT_Register.uData.ucWord = (uint8)unReadReg;
    }
  }

  ucReturn = CddTle94x1_sDataMirror.StatRx.BUS_STAT_Register.uData.sBit.bVCAN_UV;

  return ucReturn;
}
#endif

#if (CDDSBC_CFG_GPIO == STD_ON)
//-----------------------------------------------------------------------------
 /// \brief  CddTle94x1_SetPWM
 ///
 /// \descr  Set the PWM for the specified duty cyle
 ///
 /// \param  uint16 unPWMDutyCycle
 ///
 /// \return void
 //-----------------------------------------------------------------------------
void CddTle94x1_SetPWM(uint16 unPWMDutyCycle)
{
  if (unPWMDutyCycle == 0u)
  {
    //if duty cycle = 0 then set the PWM to 0 and configure GPIO pin to off
    CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.sBit.bPWM_DC = CDDTLE94X1_CFG_PWM_DC_0;
    CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.sBit.bGPIO = CDDTLE94X1_CFG_GPIO_100;
  }
  else
  {
    //if duty cycle = 100 then set the PWM to 100 and configure GPIO pin to LSS control
    CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.sBit.bPWM_DC = (uint8)((unPWMDutyCycle * 255u) / 10000u);
    CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.sBit.bGPIO = CDDTLE94X1_CFG_GPIO_110;
  }
  // add the write command of the registers updated above
  (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_PWM_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.PWM_CTRL_Register.uData.ucWord, CDDTLE94X1_CFG_WRITE_CMD, NULL_PTR);
  (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_PWM_CTRL_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, CddTle94x1_CbkSetPWM);
  (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_GPIO_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.GPIO_CTRL_Register.uData.ucWord, CDDTLE94X1_CFG_WRITE_CMD, NULL_PTR);
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_CbkSetPWM
///
/// \descr  Updates the value of the Register if the read was successful
///         This callback updates the value of the PWM_CTRL_Register in the memory if the read was succesful
///
/// \param  uint32 ulData - represents the data received during cyclic communication
///         uint16 ucSentVal - Used to store the data we just sent. Used for comparison
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_CbkSetPWM(uint32 ulData, uint16 unSentVal)
{
  // Preprocess the data before checking it
  uint8 ucRxData = (uint8)(ulData >> 8u);
  uint8 ucAddresse = (uint8)(unSentVal & CDDTLE94X1_CFG_ADDRESS_FIELD);

  if (ucAddresse == CDDTLE94X1_REGS_PWM_CTRL_ADR)
  {
    // Update the register
    CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.ucWord = ucRxData;
  }
  else
  {
    // do nothing
  }
}

//-----------------------------------------------------------------------------
/// \briefCddTle94x1_GetPWMVal
///
/// \descr Get the PWM for the specified duty cyle
///
/// \param  -
///
/// \return uint8 - DutyCycle [0..255]
//-----------------------------------------------------------------------------
uint8 CddTle94x1_GetPWM(void)
{
  uint8 ucReturn = 0u;
  uint16 unReadReg = 0u;

  if (CddSpi_GetState() == CDDSPI_STATE_SINGLE_OPERATION)
  {
    unReadReg = CddTle94x1_ReadReg(CDDTLE94X1_REGS_PWM_CTRL_ADR);
    // If there were no read errors
    if (unReadReg != CDDTLE94X1_CFG_ERROR)
    {
      // Store the registers content in the memory
      CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.ucWord = (uint8)unReadReg;
    }
  }

  ucReturn = CddTle94x1_sDataMirror.CtrlRx.PWM_CTRL_Register.uData.ucWord;

  return ucReturn;
}
#endif

#if (CDDSBC_CFG_VCC2_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_SetVCC2
///
/// \descr  Set the corresponding bit in register for activation/deactivation of VCC2
///
/// \param  ucCmd
///         0u - deactivate VCC2
///         1u   activate VCC2
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_SetVCC2(uint8 ucCmd)
{
  if (ucCmd == CDDTLE94X1_CFG_VCC2_DEACTIVATION)
  { //Deactivate VCC2
    CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON = CDDTLE94X1_CFG_VCC2_OFF;
  }
  else
  {
    //Activate VCC2
    CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.sBit.bVCC2_ON = CDDTLE94X1_CFG_VCC2_ON1;
  }

  (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_M_S_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.M_S_CTRL_Register.uData.ucWord, CDDTLE94X1_CFG_WRITE_CMD, NULL_PTR);
  (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_M_S_CTRL_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, CddTle94x1_CbkSetVCC2);
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_CbkSetVCC2
///
/// \descr  Updates the value of the Register if the read was successful
///         This callback updates the value of the M_S_CTRL_Register in the memory if the read was succesful
///
/// \param  uint32 ulData - represents the data received during cyclic communication
///         uint16 ucSentVal - Used to store the data we just sent. Used for comparison
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_CbkSetVCC2(uint32 ulData, uint16 unSentVal)
{
  // Preprocess the data before checking it
  uint8 ucRxData = (uint8)(ulData >> 8u);
  uint8 ucAddresse = (uint8)(unSentVal & CDDTLE94X1_CFG_ADDRESS_FIELD);

  if (ucAddresse == CDDTLE94X1_REGS_M_S_CTRL_ADR)
  {
    // Update the register
    CddTle94x1_sDataMirror.CtrlRx.M_S_CTRL_Register.uData.ucWord = ucRxData;
  }
  else
  {
    // do nothing
  }
}
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_Short_To_VBAT
///
/// \descr  Function that monitors the Short to VBAT and sets the corresponding error flag
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Short_To_VBAT(void)
{
  tiu16Voltage_mV unReadADC_VCCX1 = 0u;
  STATIC_UT(TIMER, ulDebounceStartTime, 0u);
  TIMER ulDebounceStopTime = 0u;
  STATIC_UT(boolean, boTimerInitialized, FALSE);

  unReadADC_VCCX1 = IoHwAbUser_Read_VCCX1();

  if (unReadADC_VCCX1 > CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD)
  {
    // Chekc if this is the first call when vccx2 voltage > 5.82V
    if (boTimerInitialized == FALSE)
    {
      ulDebounceStartTime = TimerGetTick();

      boTimerInitialized = TRUE;
    }
    else
    {
      // nothing to do because the timer was already initiazlied
    }

    ulDebounceStopTime = TimerGetTimeSince(ulDebounceStartTime);

    // wait 500ms to set the error
    if (ulDebounceStopTime >= UTILTIME_MSEC(500u))
    {
      //Short to VBat
      CddTle94x1_sErrorType.boShorttoVBAT = TRUE;
    }
    else
    {
      //do nothing
    }

  }
  else
  {
    //timer was not initialized
    boTimerInitialized = FALSE;
  }

}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_Reset_Short_To_VBAT
///
/// \descr  Function that monitors the Short to VBAT and resets the corresponding error flag
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Reset_Short_To_VBAT(void)
{
  tiu16Voltage_mV unReadADC_VCCX1 = 0u;
  STATIC_UT(TIMER, ulDebounceStartTime, 0u);
  TIMER ulDebounceStopTime = 0u;
  STATIC_UT(boolean, boTimerInitialized, FALSE);

  unReadADC_VCCX1 = IoHwAbUser_Read_VCCX1();

  if ((unReadADC_VCCX1 <= CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD) && (CddTle94x1_sErrorType.boShorttoVBAT == TRUE))
  {
    // Chekc if this is the first call when vccx2 voltage < 5.82V
    if (boTimerInitialized == FALSE)
    {
      ulDebounceStartTime = TimerGetTick();

      boTimerInitialized = TRUE;
    }
    else
    {
      // nothing to do because the timer was already initiazlied
    }

    ulDebounceStopTime = TimerGetTimeSince(ulDebounceStartTime);

    // wait 500ms to reset the error
    if (ulDebounceStopTime >= UTILTIME_MSEC(500u))
    {
      //No Short to VBat
      CddTle94x1_sErrorType.boShorttoVBAT = FALSE;
    }
    else
    {
      //do nothing
    }

  }
  else
  {
    //timer was not initialized
    boTimerInitialized = FALSE;
  }

}
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_Short_To_GND
///
/// \descr   Function that monitors the Short to GND and sets the corresponding error flag
///          It deactivates the VCC2 in case error is present
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Short_To_GND(void)
{
  tiu16Voltage_mV unReadADC_VCCX1 = 0u;
  STATIC_UT(TIMER, ulDebounceStartTime, 0u);
  TIMER ulDebounceStopTime = 0u;
  STATIC_UT(boolean, boTimerInitialized, FALSE);

  unReadADC_VCCX1 = IoHwAbUser_Read_VCCX1();

  if (unReadADC_VCCX1 < CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD)
  {
    // Chekc if this is the first call when vccx2 voltage < 4V
    if (boTimerInitialized == FALSE)
    {
      ulDebounceStartTime = TimerGetTick();

      boTimerInitialized = TRUE;
    }
    else
    {
      // nothing to do because the timer was already initiazlied
    }

    ulDebounceStopTime = TimerGetTimeSince(ulDebounceStartTime);

    // wait 500ms to set the error and deactivate VCC2
    if (ulDebounceStopTime >= UTILTIME_MSEC(500u))
    {
      //Short to GND
      CddTle94x1_sErrorType.boShorttoGND = TRUE;
      //Deactivate VCC2_ON
      CddTle94x1_SetVCC2(CDDTLE94X1_CFG_VCC2_DEACTIVATION);
    }
    else
    {
      //do nothing
    }
  }
  else
  {
    //timer was not initialized
    boTimerInitialized = FALSE;

  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_Reset_Short_To_GND
///
/// \descr   Function that monitors the Short to GND and resets the corresponding error flag
///          It activates the VCC2 in case error is not present anymore
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Reset_Short_To_GND(void)
{
  tiu16Voltage_mV unReadADC_VCCX1 = 0u;
  STATIC_UT(TIMER, ulDebounceStartTime, 0u);
  TIMER ulDebounceStopTime = 0u;
  STATIC_UT(boolean, boTimerInitialized, FALSE);

  unReadADC_VCCX1 = IoHwAbUser_Read_VCCX1();

  if ((unReadADC_VCCX1 >= CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD) && (CddTle94x1_sErrorType.boShorttoGND == TRUE))
  {
    // Chekc if this is the first call when vccx2 voltage > 4V
    if (boTimerInitialized == FALSE)
    {
      ulDebounceStartTime = TimerGetTick();

      boTimerInitialized = TRUE;
    }
    else
    {
      // nothing to do because the timer was already initiazlied
    }

    ulDebounceStopTime = TimerGetTimeSince(ulDebounceStartTime);

    // wait 500ms to reset the error and activate VCC2
    if (ulDebounceStopTime >= UTILTIME_MSEC(500u))
    {
      // No Short to GND
      CddTle94x1_sErrorType.boShorttoGND = FALSE;
      //Activate VCC2_ON
      CddTle94x1_SetVCC2(CDDTLE94X1_CFG_VCC2_ACTIVATION);
    }
    else
    {
      //do nothing
    }
  }
  else
  {
    //timer was not initialized
    boTimerInitialized = FALSE;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_ReadThermStatReg
///
/// \descr  Function to read the specific register for Thermal information.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_ReadThermStatReg(void)
{
  (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_THERM_STAT_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, NULL_PTR);
  (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_THERM_STAT_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, CddTle94x1_CbkReadThermStatReg);
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_CbkReadThermoStatReg
///
/// \descr  Updates the value of the Register if the read was successful
///         This callback updates the value of the M_S_CTRL_Register in the memory if the read was succesful
///
/// \param  uint32 ulData - represents the data received during cyclic communication
///         uint16 ucSentVal - Used to store the data we just sent. Used for comparison
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_CbkReadThermStatReg(uint32 ulData, uint16 unSentVal)
{
  // Preprocess the data before checking it
  uint8 ucRxData = (uint8)(ulData >> 8u);
  uint8 ucAddresse = (uint8)(unSentVal & CDDTLE94X1_CFG_ADDRESS_FIELD);

  if (ucAddresse == CDDTLE94X1_REGS_THERM_STAT_ADR)
  {
    // Update the register
    CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.ucWord = ucRxData;
  }
  else
  {
    // do nothing
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_Thermal_Shutdown
///
/// \descr  Function to check the thermal shutdown information, set the corresponding
///         flag and activate the VCC2 in case of no error.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------

void CddTle94x1_Thermal_Shutdown(void)
{
  uint8 ucThermal_Shutdown = 0u;
  STATIC_UT(TIMER, ulDebounceStartTime, 0u);
  TIMER ulDebounceStopTime = 0u;
  STATIC_UT(boolean, boTimerInitialized, FALSE);

#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
  if (CddTle94x1_ulTSDHook_Activ_Val == CDDTLE94X1_TSD_HOOK_ENBL_VAL)
  {
    ucThermal_Shutdown = 1u;
  }
  else
  {
    //Read and store the Shutdown information
    ucThermal_Shutdown = CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1;
  }
#else
  //Read and store the Shutdown information
  ucThermal_Shutdown = CddTle94x1_sDataMirror.StatRx.THERM_STAT_Register.uData.sBit.bTSD1;
#endif
  

  // if the value of ucThermal_Shutdown is set the thermal shutdown error is present
  if (ucThermal_Shutdown != 0u)
  {
    //Thermal Shutdown Error
    CddTle94x1_sErrorType.boTSDError = TRUE;
#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
    if (CddTle94x1_ulTSDHook_Activ_Val == CDDTLE94X1_TSD_HOOK_ENBL_VAL)
    {
      //Deactivate VCC2 - emulates the real thermal-shutdown behavior
      CddTle94x1_SetVCC2(CDDTLE94X1_CFG_VCC2_DEACTIVATION);
    }
#endif
  }
  else
  {
    
    // Chekc if this is the first call when TSD = 1
    if(CddTle94x1_sErrorType.boTSDError != 0u)
    {
      // Clear TSD error
      CddTle94x1_sErrorType.boTSDError = FALSE;

      // Get Time
      ulDebounceStartTime = TimerGetTick();

      // Set timer initialized
      boTimerInitialized = TRUE;
    }
    else
    {
      // nothing to do because the timer was already initiazlied
    }

    // Timer Initialized
    if (boTimerInitialized != FALSE)
    {
      // Get the time stamp
      ulDebounceStopTime = TimerGetTimeSince(ulDebounceStartTime);

      // wait 5s to activate VCC2 after thermal shut down is not present
      if (ulDebounceStopTime >= UTILTIME_SEC(5u))
      {
        //Activate VCC2_ON
        CddTle94x1_SetVCC2(CDDTLE94X1_CFG_VCC2_ACTIVATION);
        // Reset Timer
        boTimerInitialized = FALSE;
      }
      else
      {
        //do nothing
      }
    }
    else
    {
      // skip timer is not initialized
    }
   
  }
  CddTle94x1_ReadThermStatReg();
}

#endif

#if ((CDDSBC_CFG_CAN_OPERATION == STD_ON) && (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON))
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_CbkGetCanMode
///
/// \descr  Updates the value of the Register if the read was successful
///         This callback updates the value of the BUS_CTRL_0 register in the memory if the read was succesful
///
/// \param  uint32 ulData - represents the data received during cyclic communication
///         uint16 ucSentVal - Used to store the data we just sent. Used for comparison
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_CbkGetCanMode(uint32 ulData, uint16 unSentVal)
{
  // Preprocess the data before checking it
  uint8 ucRxData = (uint8)(ulData >> 8u);
  uint8 ucAddresse = (uint8)(unSentVal & CDDTLE94X1_CFG_ADDRESS_FIELD);

  if (ucAddresse == CDDTLE94X1_REGS_BUS_CTRL_0_ADR)
  {
    // Update the register
    CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord = ucRxData;
  }
  else
  {
    // do nothing
  }
}
#endif

#if ((CDDSBC_CFG_CAN_OPERATION == STD_ON) && (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON))
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_CbkGetBusState
///
/// \descr  Updates the value of the Register if the read was successful
///         This callback updates the value of the BUS_STAT register in the memory if the read was succesful
///
/// \param  uint32 ulData - represents the data received during cyclic communication
///         uint16 ucSentVal - Used to store the data we just sent. Used for comparison
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_CbkGetBusState(uint32 ulData, uint16 unSentVal)
{
  // Preprocess the data before checking it
  uint8 ucRxData = (uint8)(ulData >> 8u);
  uint8 ucAddresse = (uint8)(unSentVal & CDDTLE94X1_CFG_ADDRESS_FIELD);

  if (ucAddresse == CDDTLE94X1_REGS_BUS_STAT_ADR)
  {
    // Update the register
    CddTle94x1_sDataMirror.StatRx.BUS_STAT_Register.uData.ucWord = ucRxData;
  }
  else
  {
    // do nothing
  }
}
#endif

#if ((CDDSBC_CFG_CAN_OPERATION == STD_ON) && (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON))
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_CbkSetCanMode
///
/// \descr  Updates the value of the Register if the write was successful
///         This callback updates the value of the BUS_CTRL_0 register in the memory if the write was succesful
///
/// \param  uint32 ulData - represents the data received during cyclic communication
///         uint16 ucSentVal - Used to store the data we just sent. Used for comparison
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_CbkSetCanMode(uint32 ulData, uint16 unSentVal)
{
  // Preprocess the data before checking it
  uint8 ucRxData = (uint8)(ulData >> 8u);

  (void)unSentVal;

  // If the write wasn't successful
  if (ucRxData != CddTle94x1_sDataMirror.CtrlTx.BUS_CTRL_0_Register.uData.ucWord)
  {
    // Set error flag
    CddTle94x1_sErrorType.boCyclic_CanMode = TRUE;
    CddTle94x1_ErrorSequenceCounterInc();
  }
  else
  {
    CddTle94x1_ErrorSequenceCounterClear();// Reset the error counter
    CddTle94x1_sErrorType.boCyclic_CanMode = FALSE;
    CddTle94x1_sDataMirror.CtrlRx.BUS_CTRL_0_Register.uData.ucWord = ucRxData;
  }
}
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_ValidateCanMode
///
/// \descr  Validate the CAN mode
///         Checks if the received mode is a valid CAN mode
///
/// \param  uint8 ucCanMode - the mode to be validated
///
/// \return boolean boReturn
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTle94x1_ValidateCanMode(uint8 ucCanMode)
{
  boolean boReturn;

  // If the CAN mode is valid return TRUE
  switch (ucCanMode)
  {
  case CDDTLE94X1_CFG_CAN_OFF:
  case CDDTLE94X1_CFG_CAN_WAKE_ON:
  case CDDTLE94X1_CFG_CAN_RECEIVE_ONLY:
  case CDDTLE94X1_CFG_CAN_NORMAL:
  {
    CddTle94x1_sErrorType.boCanModeError = FALSE;
    boReturn = TRUE;
  }
  break;

  default:
  {
    CddTle94x1_sErrorType.boCanModeError = TRUE;
    boReturn = FALSE;
  }
  break;
  }

  return boReturn;
}
#endif

#if ((CDDSBC_CFG_WATCHDOG == STD_ON) && (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON))
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_CbkSetWDCtrl
///
/// \descr  Updates the value of the Register if the read was successful
///         This callback updates the value of the WD_CTRL register in the memory if the read was succesful
///
/// \param  uint32 ulData - represents the data received during cyclic communication
///         uint16 ucSentVal - Used to store the data we just sent. Used for comparison
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_CbkSetWDCtrl(uint32 ulData, uint16 unSentVal)
{
  // Preprocess the data before checking it
  uint8 ucRxData = (uint8)(ulData >> 8u);

  (void)unSentVal;

  // If the write wasn't successful
  if (ucRxData != CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord)
  {
    // Set error flag
    CddTle94x1_sErrorType.boSpiWdgFailure = TRUE;
    CddTle94x1_ErrorSequenceCounterInc();
  }
  else
  {
    CddTle94x1_ErrorSequenceCounterClear();// Reset the error counter
    CddTle94x1_sErrorType.boSpiWdgFailure = FALSE;
    CddTle94x1_sDataMirror.CtrlRx.WD_CTRL_Register.uData.ucWord = ucRxData;
  }
}
#endif

#if ((CDDSBC_CFG_CYCLIC_OPERATION == STD_ON) && (CDDSBC_CFG_WK_INPUT == STD_ON))
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_GetWakeUpStatus
///
/// \descr  Get the WakeUp Pin Status
///
/// \param  void
///
/// \return boolean boReturn
//-----------------------------------------------------------------------------
boolean CddTle94x1_GetWakeUpStatus(void)
{
  boolean boReturn = FALSE;

  boReturn = (boolean)CddTle94x1_sDataMirror.StatRx.WK_LVL_STAT_Register.uData.sBit.bWK_LVL;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_CbkGWakeUpStatus
///
/// \descr  Updates the value of the Register if the read was successful
///         This callback updates the value of the WK_LVL_STAT register in the memory if the read was succesful
///
/// \param  uint32 ulData - represents the data received during cyclic communication
///         uint16 ucSentVal - Used to store the data we just sent. Used for comparison
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_CbkGetWakeUpStatus(uint32 ulData, uint16 unSentVal)
{
  // Preprocess the data before checking it
  uint8 ucRxData = (uint8)(ulData >> 8u);
  uint8 ucAddresse = (uint8)(unSentVal & CDDTLE94X1_CFG_ADDRESS_FIELD);

  if (ucAddresse == CDDTLE94X1_REGS_WK_LVL_STAT_ADR)
  {
    // Update the register
    CddTle94x1_sDataMirror.StatRx.WK_LVL_STAT_Register.uData.ucWord = ucRxData;
  }
  else
  {
    // do nothing
  }
}
#endif

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_WriteClearReg
///
/// \descr  Writes or Clears specific registers using transfer messages
///         During initialization, deinitialization and setting the device into sleep mode this function is used to write and clear specific registers.
///         The CddSpi_TransferMsg will be called for a maximum of CDD_SBC_MAX_WRITE_ATTEMPTS times in case of unsuccessful write.
///         After a successful write CddTle94x1_ReadReg() is called to verify if the data was indeed written to the register.
///         The function return FALSE if the data read from the register is not the one received as a parameter and TRUE if they are equal.
///
/// \param  uint8 ucAddress - the address of the register
///         uint16 unDataField - data to be written into the register
///
/// \return boolean boReturn
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTle94x1_WriteClearReg(uint8 ucAddress, uint16 unDataField)
{
  uint8 ucAddressField, ucIterationIndex = 0u;
  uint16 unTxData, unRxData;
  boolean boReturn = FALSE;

  // Concatenate the address field of the message
  ucAddressField = ucAddress | CDDTLE94X1_CFG_WRITE_CMD;

  // Concatenate the address field of the message with the data field and store the obtained message in the buffer
  unTxData = unDataField;
  unTxData = unTxData << 8u;
  unTxData = unTxData | ucAddressField;

  // Try to send the data to the register for a maximum of 10 times
  while ((CddSpi_TransferMsg((uint8)CDDSPI_DEVICE(SBC), &unTxData) != TRUE) && (ucIterationIndex < CDDSBC_CFG_MAX_WRITE_ATTEMPTS))
  {
    // Increment the error counter
    ucIterationIndex++;
  }

  // If the write command was sent succefully via SPI
  if (ucIterationIndex < CDDSBC_CFG_MAX_WRITE_ATTEMPTS)
  {
    // Read the registers value into the unRxData variable
    unRxData = CddTle94x1_ReadReg(ucAddress);

    // If the data was updated in the register
    if (unRxData == unDataField)
    {
      // Operation succesful => return TRUE
      boReturn = TRUE;
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    // do nothing
  }
  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_ReadReg
///
/// \descr  Reads specific registers using tranfser messages during the initilization
///         During initialization, deinitialization and setting the device into sleep mode this function is used to read specific registers.
///         The function will return the value stored in the register if the Read was succesful and CDDTLE94X1_CFG_ERROR if the process was unsuccesful for a maximum of [MAX_READ_ATTEMPTS] times.
///
/// \param  uint8 ucAddress
///
/// \return uint16 unReturnValue
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddTle94x1_ReadReg(uint8 ucAddress)
{
  uint8  ucIterationCounter = 0u;

  // Concatenate the message to be send in order to read out the values stored in the Sbc's register
  uint16 unSpiTxMsg = (uint16)ucAddress;

  uint16 unReturnValue = (uint16)CDDTLE94X1_CFG_ERROR;

  // Try to send the Msg until is sent succesfuly and the maximum read attemps are not exceeded
  while ((CddSpi_TransferMsg((uint8)CDDSPI_DEVICE(SBC), &unSpiTxMsg) != TRUE) && (ucIterationCounter < CDDSBC_CFG_MAX_READ_ATTEMPTS))
  {
    // Increment the error counter
    ucIterationCounter++;
  }

  // If the read was unsuccesful after MAX_READ_ATTEMP times
  if (ucIterationCounter < CDDSBC_CFG_MAX_READ_ATTEMPTS)
  {
    // Succesful read
    // Store the register's content in the buffer
    const uint16 unSpiRxMsg = (uint8)(unSpiTxMsg >> 8u);

    unReturnValue = unSpiRxMsg;
  }
  else
  {
    // do nothing
  }

  return unReturnValue;
}

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_InsertDefaultMessage
///
/// \descr  Default message will be inserted if there are no messages configured in the queue
///         This default message will check cyclically the SUP_STAT_0.VCC2_UV status register
///         This message will be sent only when the queue is empty and there are no more entries to be processed.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_InsertDefaultMessage(void)
{
  // Read out the Register cyclically
  switch (CddTle94x1_eDefaultMsg)
  {
#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
  case eBUS_CTRL_0:
    //(void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_BUS_CTRL_0_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, NULL_PTR);
    (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_BUS_CTRL_0_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, CddTle94x1_CbkGetCanMode);
    CddTle94x1_eDefaultMsg = eBUS_STAT;
    break;

  case eBUS_STAT:
    //(void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_BUS_STAT_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, NULL_PTR);
    (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_BUS_STAT_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, CddTle94x1_CbkGetBusState);
#if (CDDSBC_CFG_WK_INPUT == STD_ON)
    CddTle94x1_eDefaultMsg = eWK_LVL_STAT;
#else
    CddTle94x1_eDefaultMsg = eSUP_STAT_0;
#endif
    break;
#endif

#if (CDDSBC_CFG_WK_INPUT == STD_ON)
  case eWK_LVL_STAT:
    //(void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_WK_LVL_STAT_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, NULL_PTR);
    (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_WK_LVL_STAT_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, CddTle94x1_CbkGetWakeUpStatus);
    CddTle94x1_eDefaultMsg = eSUP_STAT_0;
    break;
#endif

  case eSUP_STAT_0:
    //(void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_SUP_STAT_0_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, NULL_PTR);
    (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_SUP_STAT_0_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, CddTle94x1_CbkGetSupState0);
#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
    CddTle94x1_eDefaultMsg = eBUS_CTRL_0;
#else
    CddTle94x1_eDefaultMsg = eSUP_STAT_0;
#endif
    break;

  default:
    CddTle94x1_eDefaultMsg = eBUS_STAT;
    break;
  }
}
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_ScheduleTableFull
///
/// \descr  Called by the CddSbc_InsertNewSchedEntry function. Sets the flag
///
/// \param  boolean boStatus - NO_ERROR/ERROR_ON
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_ScheduleTableFull(boolean boStatus)
{
  // Set the flag with the received parameter.
  CddTle94x1_sErrorType.boScheduleTableFull = boStatus;
}
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_CbkGetSupState0
///
/// \descr  Updates the value of the Register if the read was successful
///         This callback updates the value of the SUP_STAT_0_ register in the memory if the read was succesful
///
/// \param  uint32 ulData - represents the data received during cyclic communication
///         uint16 ucSentVal - Used to store the data we just sent. Used for comparison
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_CbkGetSupState0(uint32 ulData, uint16 unSentVal)
{
  // Preprocess the data before checking it
  uint8 ucRxData = (uint8)(ulData >> 8u);
  uint8 ucAddresse = (uint8)(unSentVal & CDDTLE94X1_CFG_ADDRESS_FIELD);

  if (ucAddresse == CDDTLE94X1_REGS_SUP_STAT_0_ADR)
  {
    // Update the register
    CddTle94x1_sDataMirror.StatRx.SUP_STAT_0_Register.uData.ucWord = ucRxData;
  }
  else
  {
    // do nothing
  }
}
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_ErrorSequenceCounterInc
///
/// \descr  Increment the error sequence counter of the SPI
///         In this function the error sequence counter is incremented and if the counter reachs
///         CDDSBC_CFG_MAX_CYCLIC_SEQ_ERRORS, the error flag boCyclic_SPI_Communication is set
///         with ERROR_ON.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_ErrorSequenceCounterInc(void)
{
  if (CddTle94x1_unErrorSequenceCounter < CDDSBC_CFG_MAX_CYCLIC_SEQ_ERRORS)
  {
    // Increment the sequence error counter
    CddTle94x1_unErrorSequenceCounter++;
  }
  else
  {
    // Set the error flag boCyclic_SPI_Communication
    CddTle94x1_sErrorType.boCyclic_SPI_Communication = TRUE;
  }
}
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_ErrorSequenceCounterClear
///
/// \descr  clear the error sequence counter of the SPI
///         This function cleas the error sequence counter and set the error flag
///         boCyclic_SPI_Communication with NO_ERROR
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_ErrorSequenceCounterClear(void)
{
  CddTle94x1_unErrorSequenceCounter = 0;

  // Set the error flag boCyclic_SPI_Communication
  CddTle94x1_sErrorType.boCyclic_SPI_Communication = FALSE;
}
#endif

#if (CDDSBC_CFG_INIT_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_DeInit
///
/// \descr  Denitialize TLE9471 SBC complex device driver
///         This function is a currently dummy function.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_DeInit(void)
{
  (void)CddTle94x1_ucSUP_STAT_0_POR;
  (void)CddTle94x1_ucWK_STAT_0_CANWU;
  (void)CddTle94x1_sErrorType;
}
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_SetWdgWithSingleOperation
///
/// \descr  This function is to set the watchdog with SPI single opeartion
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddTle94x1_SetWdgWithSingleOperation(void)
{
  if (CddTle94x1_WriteClearReg(CDDTLE94X1_REGS_WD_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord) != FALSE)
  {
    CddTle94x1_sDataMirror.CtrlRx.WD_CTRL_Register.uData.ucWord = CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord;
    CddTle94x1_sErrorType.boSpiWdgFailure = FALSE;
  }
  else
  {
    // Write was unsuccessful
    // Set the error Flag
    CddTle94x1_sErrorType.boSpiWdgFailure = TRUE;
  }
}
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_SetWdgWindowModeAnd10ms
///
/// \descr  This function is to set the watchdog with window mode and 10ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_SetWdgWindowModeAnd10ms(void)
{
  // Set Watchdog Timer Periode in the WD_CTRL register.WD_TIMER
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bWD_TIMER = CDDTLE94X1_CFG_WD_TIMER_10ms;

  // Set Watchdog with Window watchdog in the WD_CTRL register.WD_WIN
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bWD_WIN = CDDTLE94X1_CFG_WD_Window;

  // Set Watchdog Checksum in the WD_CTRL register.CHECKSUM
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bCHECKSUM = CDDTLE94X1_CFG_WD_Checksum_1;

  if (CddSpi_GetState() == CDDSPI_STATE_SINGLE_OPERATION)
  {
    CddTle94x1_SetWdgWithSingleOperation();
  }
#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
  else if (CddSpi_GetState() == CDDSPI_STATE_CYCLIC_OPERATION)
  {
    // Set the WD_CTRL register to trigger the watchdog
    (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_WD_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, CDDTLE94X1_CFG_WRITE_CMD, NULL_PTR);
  }
#endif
  else
  {
    // do nothing
  }
}
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_SetWdgTimeoutModeAnd200ms
///
/// \descr  This function is to set the watchdog with timeout mode and 200ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_SetWdgTimeoutModeAnd200ms(void)
{
  // Set Watchdog Timer Periode in the WD_CTRL register.WD_TIMER
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bWD_TIMER = CDDTLE94X1_CFG_WD_TIMER_200ms;

  // Set Watchdog with Window watchdog in the WD_CTRL register.WD_WIN
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bWD_WIN = CDDTLE94X1_CFG_WD_TimeOut;

  // Set Watchdog Checksum in the WD_CTRL register.CHECKSUM
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bCHECKSUM = CDDTLE94X1_CFG_WD_Checksum_1;

  if (CddSpi_GetState() == CDDSPI_STATE_SINGLE_OPERATION)
  {
    CddTle94x1_SetWdgWithSingleOperation();
  }
#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
  else if (CddSpi_GetState() == CDDSPI_STATE_CYCLIC_OPERATION)
  {
    // Set the WD_CTRL register to trigger the watchdog
    (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_WD_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, CDDTLE94X1_CFG_WRITE_CMD, NULL_PTR);
  }
#endif
  else
  {
    // do nothing
  }
}
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddTle94x1_SetWdgWindowModeAnd200ms
///
/// \descr  This function is to set the watchdog with window mode and 200ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_SetWdgWindowModeAnd200ms(void)
{
  // Set Watchdog Timer Periode in the WD_CTRL register.WD_TIMER
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bWD_TIMER = CDDTLE94X1_CFG_WD_TIMER_200ms;

  // Set Watchdog with Window watchdog in the WD_CTRL register.WD_WIN
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bWD_WIN = CDDTLE94X1_CFG_WD_Window;

  // Set Watchdog Checksum in the WD_CTRL register.CHECKSUM
  CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bCHECKSUM = CDDTLE94X1_CFG_WD_Checksum_0;

  if (CddSpi_GetState() == CDDSPI_STATE_SINGLE_OPERATION)
  {
    // Set Watchdog Timer Periode in the WD_CTRL register.WD_TIMER
    CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bWD_TIMER = CDDTLE94X1_CFG_WD_TIMER_200ms;

    // Set Watchdog with Window watchdog in the WD_CTRL register.WD_WIN
    CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bWD_WIN = CDDTLE94X1_CFG_WD_TimeOut;

    // Set Watchdog Checksum in the WD_CTRL register.CHECKSUM
    CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.sBit.bCHECKSUM = CDDTLE94X1_CFG_WD_Checksum_1;
    CddTle94x1_SetWdgWithSingleOperation();
  }
#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
  else if (CddSpi_GetState() == CDDSPI_STATE_CYCLIC_OPERATION)
  {
    // Set the WD_CTRL register to trigger the watchdog
    (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_WD_CTRL_ADR, CddTle94x1_sDataMirror.CtrlTx.WD_CTRL_Register.uData.ucWord, CDDTLE94X1_CFG_WRITE_CMD, NULL_PTR);
    (void)CddSbc_InsertNewSchedEntry(CDDTLE94X1_REGS_WD_CTRL_ADR, CDDTLE94X1_CFG_CLEAR_ALL, CDDTLE94X1_CFG_READ_CMD, CddTle94x1_CbkSetWDCtrl);
  }
#endif
  else
  {
    // do nothing
  }
}
#endif

// EOF
