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
/// \file   SigPrepTx.c
///
/// \brief  Tx Frame Processing
///
/// \descr  Output Tx Frame Processing [Cyclic, Event and Time-Out detection]
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <SigPrepTx.h>
#include <SigPrepRx.h>
#include <p_IpduCallback.h>
#include <p_IL_messages.h>
#include <LgmDEHMainAPI.h>
#include <Nvm.h>

//#include <p_NM.h>
#include <NM_priv.h>
#include <ProcessE2E.h>

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#if (CFG_DRV_CAN != CFG_Drv_None)
#define SIGPREP_TX_FRM_CONFIG
#include <SigPrep_Cfg.h>
#undef SIGPREP_TX_FRM_CONFIG

#define SIGPREP_TX_ENUM_FRM_CONFIG
#include <SigPrep_Cfg.h>
#undef SIGPREP_TX_ENUM_FRM_CONFIG
#endif

#define SIGPREPTX_ZERO_VALUE          0u

#define SIGPREPTX_SCALING_65535             0xFFFFU
#define SIGPREPTX_SCALING_32768             0x8000U
#define SIGPREPTX_SCALING_10000             0x2710U
#define SIGPREPTX_SCALING_100               0x0064U

#define SIGPREPTX_TEMP_OFFSET_40            40u
#define SIGPREPTX_DBL_RESOLUTION_5           5
#define SIGPREPTX_DBL_RESOLUTION_10         10

#define SIGPREPTX_TGTPOS_RAD_RESOLUTION_NUMERATOR    10
#define SIGPREPTX_TGTPOS_RAD_RESOLUTION_DENOMINATOR   6

#define SIGPREPTX_TGTPOS_DENOMINATOR  10

#define SIGPREPTX_FAN_STATUS_OFF     0u
#define SIGPREPTX_FAN_STATUS_ON      1u

#define SIGPREPTX_FAN1_INDEX 0u
#define SIGPREPTX_FAN2_INDEX 1u

#define SIGPREPTX_HSS_STATUS_ON  1u

#define SIGPREPTX_DIAGPXLINDEX_INIT {{ RL_LED_01_Feh , RL_LED_02_Feh , RL_LED_03_Feh , RL_LED_04_Feh , RL_LED_05_Feh , RL_LED_06_Feh , RL_LED_07_Feh , RL_LED_08_Feh , RL_LED_09_Feh , RL_LED_10_Feh , RL_LED_11_Feh , RL_LED_12_Feh , RL_LED_13_Feh , RL_LED_14_Feh , RL_LED_15_Feh , RL_LED_16_Feh , RL_LED_17_Feh , RL_LED_18_Feh , RL_LED_19_Feh , RL_LED_20_Feh , RL_LED_21_Feh , RL_LED_22_Feh , RL_LED_23_Feh , RL_LED_24_Feh , RL_LED_25_Feh , RL_LED_26_Feh , RL_LED_27_Feh , RL_LED_28_Feh , RL_LED_29_Feh , RL_LED_30_Feh , RL_LED_31_Feh , RL_LED_32_Feh , RL_LED_33_Feh , RL_LED_34_Feh , RL_LED_35_Feh , RL_LED_36_Feh , RL_LED_37_Feh , RL_LED_38_Feh , RL_LED_39_Feh , RL_LED_40_Feh , RL_LED_41_Feh , RL_LED_42_Feh , RL_LED_43_Feh , RL_LED_44_Feh , RL_LED_45_Feh , RL_LED_46_Feh , RL_LED_47_Feh , RL_LED_48_Feh , RL_LED_49_Feh , RL_LED_50_Feh , RL_LED_51_Feh , RL_LED_52_Feh , RL_LED_53_Feh , RL_LED_54_Feh , RL_LED_55_Feh , RL_LED_56_Feh , RL_LED_57_Feh , RL_LED_58_Feh , RL_LED_59_Feh , RL_LED_60_Feh , RL_LED_61_Feh , RL_LED_62_Feh , RL_LED_63_Feh , RL_LED_64_Feh , RL_LED_65_Feh , RL_LED_66_Feh , RL_LED_67_Feh , RL_LED_68_Feh , RL_LED_69_Feh , RL_LED_70_Feh , RL_LED_71_Feh , RL_LED_72_Feh , RL_LED_73_Feh , RL_LED_74_Feh , RL_LED_75_Feh , RL_LED_76_Feh , RL_LED_77_Feh , RL_LED_78_Feh , RL_LED_79_Feh , RL_LED_80_Feh , RL_LED_81_Feh , RL_LED_82_Feh , RL_LED_83_Feh , RL_LED_84_Feh , RL_LED_85_Feh , RL_LED_86_Feh , RL_LED_87_Feh , RL_LED_88_Feh , RL_LED_89_Feh , RL_LED_90_Feh }, \
                                     { RL_LED_01_PWM , RL_LED_02_PWM , RL_LED_03_PWM , RL_LED_04_PWM , RL_LED_05_PWM , RL_LED_06_PWM , RL_LED_07_PWM , RL_LED_08_PWM , RL_LED_09_PWM , RL_LED_10_PWM , RL_LED_11_PWM , RL_LED_12_PWM , RL_LED_13_PWM , RL_LED_14_PWM , RL_LED_15_PWM , RL_LED_16_PWM , RL_LED_17_PWM , RL_LED_18_PWM , RL_LED_19_PWM , RL_LED_20_PWM , RL_LED_21_PWM , RL_LED_22_PWM , RL_LED_23_PWM , RL_LED_24_PWM , RL_LED_25_PWM , RL_LED_26_PWM , RL_LED_27_PWM , RL_LED_28_PWM , RL_LED_29_PWM , RL_LED_30_PWM , RL_LED_31_PWM , RL_LED_32_PWM , RL_LED_33_PWM , RL_LED_34_PWM , RL_LED_35_PWM , RL_LED_36_PWM , RL_LED_37_PWM , RL_LED_38_PWM , RL_LED_39_PWM , RL_LED_40_PWM , RL_LED_41_PWM , RL_LED_42_PWM , RL_LED_43_PWM , RL_LED_44_PWM , RL_LED_45_PWM , RL_LED_46_PWM , RL_LED_47_PWM , RL_LED_48_PWM , RL_LED_49_PWM , RL_LED_50_PWM , RL_LED_51_PWM , RL_LED_52_PWM , RL_LED_53_PWM , RL_LED_54_PWM , RL_LED_55_PWM , RL_LED_56_PWM , RL_LED_57_PWM , RL_LED_58_PWM , RL_LED_59_PWM , RL_LED_60_PWM , RL_LED_61_PWM , RL_LED_62_PWM , RL_LED_63_PWM , RL_LED_64_PWM , RL_LED_65_PWM , RL_LED_66_PWM , RL_LED_67_PWM , RL_LED_68_PWM , RL_LED_69_PWM , RL_LED_70_PWM , RL_LED_71_PWM , RL_LED_72_PWM , RL_LED_73_PWM , RL_LED_74_PWM , RL_LED_75_PWM , RL_LED_76_PWM , RL_LED_77_PWM , RL_LED_78_PWM , RL_LED_79_PWM , RL_LED_80_PWM , RL_LED_81_PWM , RL_LED_82_PWM , RL_LED_83_PWM , RL_LED_84_PWM , RL_LED_85_PWM , RL_LED_86_PWM , RL_LED_87_PWM , RL_LED_88_PWM , RL_LED_89_PWM , RL_LED_90_PWM } }

#define SIGPREPTX_LUMINDEX_INIT {{RL_CHANNEL_01_LUM, RL_CHANNEL_02_LUM, RL_CHANNEL_03_LUM, RL_CHANNEL_04_LUM, RL_CHANNEL_05_LUM, RL_CHANNEL_06_LUM, RL_CHANNEL_07_LUM, RL_CHANNEL_08_LUM, RL_CHANNEL_09_LUM, RL_CHANNEL_10_LUM, RL_CHANNEL_11_LUM, RL_CHANNEL_12_LUM}}

#define SIGPREPTX_TEMPINDEX_INIT {{RL_CHANNEL_01_TEMP, RL_CHANNEL_02_TEMP, RL_CHANNEL_03_TEMP, RL_CHANNEL_04_TEMP, RL_CHANNEL_05_TEMP, RL_CHANNEL_06_TEMP, RL_CHANNEL_07_TEMP, RL_CHANNEL_08_TEMP, RL_CHANNEL_09_TEMP, RL_CHANNEL_10_TEMP, RL_CHANNEL_11_TEMP, RL_CHANNEL_12_TEMP}}

#define SIGPREPTX_POWERFACTORINDEX_INIT {{RL_CHANNEL_01_POWER_FACT, RL_CHANNEL_02_POWER_FACT, RL_CHANNEL_03_POWER_FACT, RL_CHANNEL_04_POWER_FACT, RL_CHANNEL_05_POWER_FACT, RL_CHANNEL_06_POWER_FACT, RL_CHANNEL_07_POWER_FACT, RL_CHANNEL_08_POWER_FACT, RL_CHANNEL_09_POWER_FACT, RL_CHANNEL_10_POWER_FACT, RL_CHANNEL_11_POWER_FACT, RL_CHANNEL_12_POWER_FACT}}

#define SIGPREPTX_BHSINDEX_INIT {{L_R_BHS_READING, L_F_BHS_READING}}

#define SIGPREPTX_DBLSWIVANGLEINDEX_INIT {{RL_DBL_SWIV_ANGLE_L, RL_DBL_SWIV_ANGLE_R}}

//scaling number (from x->y)
#define SIGPREPTX_SCALING_X_TO_Y_VALUE(x, y, val, type) ((val) == 0U) ? 0U : (type)( ( (uint32)((uint32)(y) * (uint32)(val))   ) / (uint32)(x))
//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------
// Active Tx Status
STATIC_AL           boolean                                       SigPrepTx_boActivateTx     = FALSE;
STATIC_AL           teSigPrep_TxSideFrameState                    SigPrepTx_eEcuSide         = eRightTxFrame;
STATIC_AL CONST_AL  tsSigPrep_TxValidationFrames_PxlPwmErrIndex   SigPrepTx_DiagPxlIndex     = SIGPREPTX_DIAGPXLINDEX_INIT;
STATIC_AL CONST_AL  tsSigPrep_TxValidationFrames_LumLedChnlIndex  SigPrepTx_LumLedChnlIndex  = SIGPREPTX_LUMINDEX_INIT;
STATIC_AL CONST_AL  tsSigPrep_TxValidationFrames_TempIndex        SigPrepTx_TempIndex        = SIGPREPTX_TEMPINDEX_INIT;
STATIC_AL CONST_AL  tsSigPrep_TxValidationFrames_PowerFactorIndex SigPrepTx_PowerFactorIndex = SIGPREPTX_POWERFACTORINDEX_INIT;
STATIC_AL CONST_AL  tsSigPrep_TxValidationFrames_BhsIndex         SigPrepTx_BhsIndex         = SIGPREPTX_BHSINDEX_INIT;
STATIC_AL CONST_AL  tsSigPrep_TxValidationFrames_DblSwivAnglIndex SigPrepTx_DblSwivAnglIndex = SIGPREPTX_DBLSWIVANGLEINDEX_INIT;

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
STATIC_AL boolean SigPrepTx_TimeoutCheck(uint8 ucFrmIdx);
STATIC_AL void    SigPrepTx_FramesTimerInit(void);
STATIC_AL void    SigPrepTx_FramesProcessing(void);
STATIC_AL void    SigPrepTx_ValidationFramesProcessing(void);
STATIC_AL void    SigPrepTx_ValidationFrames_10ms(void);
STATIC_AL void    SigPrepTx_ValidationFrames_100ms(void);
STATIC_AL void    SigPrepTx_ValidationFrames_200ms(void);
STATIC_AL void    SigPrepTx_ValidationFrames_PrepareStepperData(void);
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST) // Applicable for FULL only
STATIC_AL void    SigPrepTx_ValidationFrames_PrepareAngleData(void);
#endif

//-----------------------------------------------------------------------------
// function definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_Init
///
/// \descr  SigPrepTx init function
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrepTx_Init(void)
{
  teRte_MountingSide  eMountingSide = { 0 };

  // Get Mounting Side from IoHwAb
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  SigPrepTx_eEcuSide = (eMountingSide != eMountedLeft) ? eRightTxFrame : eLeftTxFrame;

  // Init timer for all cyclic Tx frames
  SigPrepTx_FramesTimerInit();
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_Cycle0
///
/// \descr  SigPrepTx cyclic main function
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrepTx_Cycle0(void)
{
  // Network On
  if (SigPrepTx_boActivateTx != FALSE)
  {
    SigPrepTx_FramesProcessing();

    // Validation Frames trigger
    SigPrepTx_ValidationFramesProcessing();
  }
  // Network Sleep
  else
  {
    // Init timer for all cyclic Tx frames - avoid time-out callback when network is spleep
    SigPrepTx_FramesTimerInit();
  }
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_CommStackDataRouter
///
/// \descr  Function for routing data from Untrusted Communication Stack on RTE to Trusted Components.
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrepTx_CommStackDataRouter(void)
{
    uint8 u8SleepBSI = (uint8)NM_CAN_b_SleepBSIframe;
    (void)Rte_Write_SigPrep_SleepBSI(&u8SleepBSI);

    /* not needed anymore. SysMon calls directly EEPL, because they are both trusted
    tE2eRawState stData;
    //dummy stData.retStatus[0] = E_EXEC_OK;
    //dummy stData.pte_ChunkStateE2E[0] = EECO_E_P01_OK;
    for (uint8 ucIdx = 0; ucIdx < CONF_D_NB_CHUNKS_PDU1; ucIdx++)
    {
        //stData.retStatus[ucIdx] = EEPL_GetRawState(ucIdx, stData.pte_ChunkStateE2E[ucIdx]);
    }
    (void)Rte_Write_SigPrep_E2EGetRawState(&stData);
    */

    NM_ModeType eNMMode;
    (void)NM_GetMode(&eNMMode);
    (void)Rte_Write_SigPrep_NMMode(&eNMMode);
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_FramesInit
///
/// \descr  Init timer for Side Compatible Tx Frame
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrepTx_FramesTimerInit(void)
{
  uint8 ucFrmIdx = 0u;

  // Init every Tx frame fron Tx frame config table
  for (ucFrmIdx = 0u; ucFrmIdx < countof(asSigPrepCanTxFrameInfoConst); ucFrmIdx++)
  {
    // Check Side Compatibility
    if ((asSigPrepCanTxFrameInfoConst[ucFrmIdx].eFrameSide == SigPrepTx_eEcuSide) && (asSigPrepCanTxFrameInfoConst[ucFrmIdx].ulTimeOut > 0u))
    {
      // Init timer
      asSigPrepCanTxFrameInfoConst[ucFrmIdx].ulTimer = TimerGetTick();
    }
    else
    {
      // Skip, side incompatibility or it is an event frame
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief SigPrepTx_FramesProcessing
///
/// \descr Tx Frames Processing [Cycle, Event and Dynamic objects]
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrepTx_FramesProcessing(void)
{
  uint8 ucFrmIdx = 0u;

  // Init every Tx frame fron Tx frame config table
  for (ucFrmIdx = 0u; ucFrmIdx < countof(asSigPrepCanTxFrameInfoConst); ucFrmIdx++)
  {
    // Check Frame Side Compatibility
    if (asSigPrepCanTxFrameInfoConst[ucFrmIdx].eFrameSide == SigPrepTx_eEcuSide)
    {
      // Run cycle frames
      if (asSigPrepCanTxFrameInfoConst[ucFrmIdx].ulTimeOut > 0u)
      {
        if (asSigPrepCanTxFrameInfoConst[ucFrmIdx].pfCycleCb != NULL_PTR)
        {
          // Cyclic callback
          asSigPrepCanTxFrameInfoConst[ucFrmIdx].pfCycleCb();
        }
        else
        {
          // Null pointer call avoid
        }
        // Tx Time-Out
        // PRQA S 3415 1 // no right hand opperator side effect
        if ((asSigPrepCanTxFrameInfoConst[ucFrmIdx].pfNotAckCb != NULL_PTR) && (SigPrepTx_TimeoutCheck(ucFrmIdx) != FALSE))
        {
          asSigPrepCanTxFrameInfoConst[ucFrmIdx].boMsgConfirmed = FALSE;
          asSigPrepCanTxFrameInfoConst[ucFrmIdx].pfNotAckCb();
        }
        else
        {
          // Skip, timeout callback defined by a NULL_PTR or there isn't time-out in transmission
        }
      }
      // Check if an event has occured and if the trigger call back is valid
      else if ((asSigPrepCanTxFrameInfoConst[ucFrmIdx].boTriggerFrm != FALSE) && (asSigPrepCanTxFrameInfoConst[ucFrmIdx].pfTriggerCb != NULL_PTR))
      {
        // Event occured, therefore call the trigger handling
        asSigPrepCanTxFrameInfoConst[ucFrmIdx].pfTriggerCb();

        // Reset the trigger flag
        asSigPrepCanTxFrameInfoConst[ucFrmIdx].boTriggerFrm = FALSE;
      }
      else
      {
        // Dynamic objects (n.a.) handling or object invalid
      }
    }
    else
    {
      // Skip, frame side mismatching
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_TimeoutCheck
///
/// \descr  Rx Frame Timeout check 
///
/// \param  ucFrmIdx:  frame Index
///
/// \return boolean True, if timeout occured
//-----------------------------------------------------------------------------
STATIC_AL boolean SigPrepTx_TimeoutCheck(uint8 ucFrmIdx)
{
  boolean boRetToStatus = FALSE;

  if ((TIMER_SIGNED)TimerGetTimeSince(asSigPrepCanTxFrameInfoConst[ucFrmIdx].ulTimer) >= (TIMER_SIGNED)UTILTIME_MSEC(asSigPrepCanTxFrameInfoConst[ucFrmIdx].ulTimeOut))
  {
    // Timeout occurred
    // Reset timer
    asSigPrepCanTxFrameInfoConst[ucFrmIdx].ulTimer = TimerGetTick();
    boRetToStatus = TRUE;
  }
  else
  {
    // Keep returning false (no time-out)
  }

  return boRetToStatus;
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ComM_ActivateTxBufer
///
/// \descr This ComM callback activate TxBuffer Processing
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrepTx_ComM_ActivateTxBufer(void)
{
  SigPrepTx_boActivateTx = TRUE;
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ComM_DeactivateTxBuffer
///
/// \descr This ComM callback dezactivate TxBuffer Processing
///
/// \param void
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrepTx_ComM_DeactivateTxBuffer(void)
{
  SigPrepTx_boActivateTx = FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_BEMP_2B7_Sent
///
/// \descr  Handling of 0x2B7 CAN frame successful transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_BEMP_2B7_Sent(void)
{
  // Indicate message reception
  asSigPrepCanTxFrameInfoConst[CANTX_HS6_DYN_BEMP_2B7].boMsgConfirmed = TRUE;
  // Reset timer
  asSigPrepCanTxFrameInfoConst[CANTX_HS6_DYN_BEMP_2B7].ulTimer = TimerGetTick();
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_BEMP_2B7_NotSent
///
/// \descr  Handling of 0x2B7 CAN frame failed transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_BEMP_2B7_NotSent(void)
{
  (void)0;
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_DRVLED_R_297_Sent
///
/// \descr  Handling of 0x297 CAN frame successful transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_DRVLED_R_297_Sent(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // Indicate message reception
  asSigPrepCanTxFrameInfoConst[CANTX_HS6_DAT_DRVLED_R_297].boMsgConfirmed = TRUE;
  // Reset timer
  asSigPrepCanTxFrameInfoConst[CANTX_HS6_DAT_DRVLED_R_297].ulTimer = TimerGetTick();
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_DRVLED_R_297_NotSent
///
/// \descr  Handling of 0x297 CAN frame failed transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_DRVLED_R_297_NotSent(void)
{
  (void)0;
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT2_DRVLED_R_4D7_Sent
///
/// \descr  Handling of 0x4D7 CAN frame successful transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT2_DRVLED_R_4D7_Sent(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // Indicate message reception
  asSigPrepCanTxFrameInfoConst[CANTX_HS6_DAT2_DRVLED_R_4D7].boMsgConfirmed = TRUE;
  // Reset timer
  asSigPrepCanTxFrameInfoConst[CANTX_HS6_DAT2_DRVLED_R_4D7].ulTimer = TimerGetTick();
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT2_DRVLED_R_4D7_NotSent
///
/// \descr  Handling of 0x4D7 CAN frame failed transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT2_DRVLED_R_4D7_NotSent(void)
{
  (void)0;
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_SUPV_DRVLED_Sent
///
/// \descr  Handling of SUPV DRVLED CAN frame successful transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_SUPV_DRVLED_Sent(void)
{
  // Check if the current side is left
  if (SigPrepTx_eEcuSide == eLeftTxFrame)
  {
    // Indicate message reception on left side
    asSigPrepCanTxFrameInfoConst[CANTX_HS6_SUPV_DRVLED_L_5D7].boMsgConfirmed = TRUE;
    // Reset timer
    asSigPrepCanTxFrameInfoConst[CANTX_HS6_SUPV_DRVLED_L_5D7].ulTimer = TimerGetTick();
  }
  else
  {
    // Indicate message reception on right side
    asSigPrepCanTxFrameInfoConst[CANTX_HS6_SUPV_DRVLED_R_5F7].boMsgConfirmed = TRUE;
    // Reset timer
    asSigPrepCanTxFrameInfoConst[CANTX_HS6_SUPV_DRVLED_R_5F7].ulTimer = TimerGetTick();
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_SUPV_DRVLED_NotSent
///
/// \descr  Handling of SUPV DRVLED CAN frame failed transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_SUPV_DRVLED_NotSent(void)
{
  (void)0;
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_EMIS_NEW_JDD_DRVLED_Sent
///
/// \descr  Handling of EMIS NEW JDD DRVLED CAN frame successful transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_EMIS_NEW_JDD_DRVLED_Sent(void)
{
  // Confirm success of the current frame transmission
  DAPI_TransmitAck();
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_EMIS_NEW_JDD_DRVLED_NotSent
///
/// \descr  Handling of EMIS NEW JDD DRVLED CAN frame failed transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_EMIS_NEW_JDD_DRVLED_NotSent(void)
{
  // Confirm failure of the current frame transmission
  DAPI_TransmitNack();
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_VERS_DRVLED_Sent
///
/// \descr  Handling of VERS DRVLED CAN frame successful transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_VERS_DRVLED_Sent(void)
{
  (void)0;
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DIAG_DRVLED_Sent
///
/// \descr  Handling of DIAG DRVLED CAN frame successful transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DIAG_DRVLED_Sent(void)
{
    boolean boSent = TRUE;
    (void)Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent(boSent);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DIAG_DRVLED_NotSent
///
/// \descr  Handling of DIAG DRVLED CAN frame failed transmission
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DIAG_DRVLED_NotSent(void)
{
    boolean boSent = FALSE;
    (void)Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent(boSent);
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ValidationFramesProcessing
///
/// \descr  Validation Frames Processing
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrepTx_ValidationFramesProcessing(void)
{
  // Free running counter to control to cyclicity of the frames
 static uint32 ulCounter = 0u;
  // Check if Instrumented Frames has been activated by Diagnostic Request
  if (NvmBlockInstrumentatedFrames != FALSE)
  {
    // Send validation frames with cycle time of 10 ms
    SigPrepTx_ValidationFrames_10ms();

    if (ulCounter % SIGPREPTX_CYCLETIME_100_MS == SIGPREPTX_ZERO_VALUE)
    {
      // Send validation frames with cycle time of 100 ms
      SigPrepTx_ValidationFrames_100ms();
    }
    else
    {
      // nothing to do
    }

    if (ulCounter % SIGPREPTX_CYCLETIME_200_MS == SIGPREPTX_ZERO_VALUE)
    {
      // Send validation frames with cycle time of 200 ms
      SigPrepTx_ValidationFrames_200ms();
    }
    else
    {
      // nothing to do, no validation frames to be sent
    }
  }
  else
  {
    // nothing to do, validation frames are not activated
  }

  // Increment counter for cyclicity check
  ulCounter++;
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ValidationFrames_10ms
///
/// \descr  Validation Frames Processing for frames with cycle time of 10 ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrepTx_ValidationFrames_10ms(void)
{
  uint8                 aucDefaultValue[1] = { 0u };
  tisHssStatusError     sStatusError;
  uint8                 aucFanStatus[1] = { 0 };
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST) // Applicable for FULL only
  tsRte_LevellingTgtPos sLvlTgtPosMsgRight;
  tsPositionOut         sPositionOutMsgLeft;
  tsRte_SensorRaw       aunSensRawPwm;
  sint16                nPosReq = 0;
  uint16                unBhsReadingTemp = 0u;
  uint8                 aucBhsReading[2] = { 0u };
  uint8                 aucLvlTgPosMsg[2] = { 0u };

  // Inhibit LVL Validation Frames information if ADL option is not available in coding
  boolean               boAdl_Enable = Cod_AvacStp_Enable();

  // Process Body Hight Sensors only on Left Side
  if (SigPrepTx_eEcuSide == eLeftTxFrame)
  {
    // Get Front and Rear Levelling Sensor PWM
    (void)Rte_Read_IoHwAb_GetSens_Raw(&aunSensRawPwm);

    // Receive Target Position for Left side
    (void)Rte_Read_ppsAvacOut(&sPositionOutMsgLeft);

    for (uint8 ucIx = 0u; ucIx < CFG_CntSens; ucIx++)
    {
      if (boAdl_Enable != FALSE)
      {
        unBhsReadingTemp = SIGPREPTX_SCALING_X_TO_Y_VALUE(SIGPREPTX_SCALING_65535, SIGPREPTX_SCALING_10000, aunSensRawPwm.aucSensRaw[ucIx], uint16);
        aucBhsReading[0] = (uint8)unBhsReadingTemp;
        aucBhsReading[1] = (uint8)(unBhsReadingTemp >> 8u);
      }
      else
      {
        // Fill the buffer with dummy data because ADL option is inhibited
        aucBhsReading[0] = 0u;
        aucBhsReading[1] = 0u;
      }

      // Send Body Height Sensor values
      (void)LGM_SendMessage(SigPrepTx_BhsIndex.unBhsIndex[ucIx], aucBhsReading);
    }

    if (boAdl_Enable != FALSE)
    {
      nPosReq = sPositionOutMsgLeft.Position[SigPrepTx_eEcuSide].Ver * SIGPREPTX_TGTPOS_RAD_RESOLUTION_NUMERATOR / SIGPREPTX_TGTPOS_RAD_RESOLUTION_DENOMINATOR;

      aucLvlTgPosMsg[0] = (uint8)nPosReq;
      // PRQA S 4533, 4393 1 // Compiler can do right shift
      aucLvlTgPosMsg[1] = (uint8)(nPosReq >> 8u);
    }
    else
    {
      // Fill the buffer with dummy data because ADL option is inhibited
      aucLvlTgPosMsg[0] = 0u;
      aucLvlTgPosMsg[1] = 0u;
    }

    // Send Calculated Attitude of Right Stepper
    (void)LGM_SendMessage(RL_CALCULATED_ATTITUDE, aucLvlTgPosMsg);
  }
  else
  {
    if (boAdl_Enable != FALSE)
    {
      // Receive Target Position for Right side
      (void)Rte_Read_SigPrep_LevellingTgtPos(&sLvlTgtPosMsgRight);

      // Convert from rad to degree
      nPosReq = (sLvlTgtPosMsgRight.eRCmdSignLvl == eSigneConsigneSiteD_Positive) ? (sint16)((sint16)sLvlTgtPosMsgRight.eRCmdPosLvl.unRCmdPosLvl) :
        -(sint16)((sint16)sLvlTgtPosMsgRight.eRCmdPosLvl.unRCmdPosLvl);
      aucLvlTgPosMsg[0] = (uint8)nPosReq;
      // PRQA S 4533, 4393 1 // Compiler can do right shift
      aucLvlTgPosMsg[1] = (uint8)(nPosReq >> 8u);
    }
    else
    {
      // Fill the buffer with dummy data because ADL option is inhibited
      aucLvlTgPosMsg[0] = 0u;
      aucLvlTgPosMsg[1] = 0u;
    }

    // Send Calculated Attitude of Right Stepper
    (void)LGM_SendMessage(RL_CALCULATED_ATTITUDE, aucLvlTgPosMsg);
  }

#elif defined (CFG_VARIANT_ECO)
  // Trigger CAN frame transmission
  (void)LGM_SendMessage(RL_CALCULATED_ATTITUDE, aucDefaultValue);
#endif

  // Get FAN1 and FAN2 Status Error from CtrlSwi
  (void)Rte_Read_CtrlSwi_StatusErr(&sStatusError);

  // Store FAN1 status
  aucFanStatus[0] = (sStatusError.eStatOn[SIGPREPTX_FAN1_INDEX] == SIGPREPTX_HSS_STATUS_ON) ? SIGPREPTX_FAN_STATUS_ON : SIGPREPTX_FAN_STATUS_OFF;

  // Send FAN1 status
  (void)LGM_SendMessage(RL_HSS_FAN_1, aucFanStatus);

  // Store FAN2 status
  aucFanStatus[0] = (sStatusError.eStatOn[SIGPREPTX_FAN2_INDEX] == SIGPREPTX_HSS_STATUS_ON) ? SIGPREPTX_FAN_STATUS_ON : SIGPREPTX_FAN_STATUS_OFF;

  // Send FAN2 status
  (void)LGM_SendMessage(RL_HSS_FAN_2, aucFanStatus);

  // Get the data from Stepper and prepare it before sending it out
  SigPrepTx_ValidationFrames_PrepareStepperData();
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ValidationFrames_100ms
///
/// \descr  Validation Frames Processing for frames with cycle time of 100 ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrepTx_ValidationFrames_100ms(void)
{
  uint8                   aucLumLedChnl[1] = { 0u };
  uint8                   aucPowerFactor[1] = { 0u };
  tsRte_TgtLedSig0_ASIL   sLedChannel_Target;
  tsRte_PowerFactor       sThermoPowerFactor;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  tsRte_boMtxSegmentFault sMtxDiagPxlErr;
  tsRte_ucActualPxlPWM    sMtxActualPxlPwm;
  uint8                   aucDiagPxlErr[1]   = { 0u };
  uint8                   aucActualPxlPwm[1] = { 0u };

  // Get PWM and Error State of Pixels from CtrlPxl
  (void)Rte_Read_CtrlPxl_ActualPxlError(&sMtxDiagPxlErr);
  (void)Rte_Read_CtrlPxl_ActualPxlPWM(&sMtxActualPxlPwm);

  // Get the data from AdbMxb and prepare it before sending it out
  SigPrepTx_ValidationFrames_PrepareAngleData();

  for (uint8 ucIdx = 0u; ucIdx < SIGPREPTX_MATRIX_MAX_NO_PXL; ucIdx++)
  {
    aucDiagPxlErr[0]   = sMtxDiagPxlErr.aboMtxSegmentFault[ucIdx];
    aucActualPxlPwm[0] = sMtxActualPxlPwm.aucActualPercMtxPWM[ucIdx];

    // Send Diag Pixel Errors
    (void)LGM_SendMessage(SigPrepTx_DiagPxlIndex.unDiagPxlErrIndex[ucIdx], aucDiagPxlErr);
    // Send Actual Pixel PWM
    (void)LGM_SendMessage(SigPrepTx_DiagPxlIndex.unActualPxlPwmIndex[ucIdx], aucActualPxlPwm);
  }
#endif

  // Get PWM (Luminosity) of LED Channels
  (void)Rte_Read_SysMon_TgtLedSig_sVal(&sLedChannel_Target);

  for (uint8 ucIdx = 0u; ucIdx < CFG_LED_CHANNELS_NR; ucIdx++)
  {
    // Convert from 0-32768 scale to 0-100
    aucLumLedChnl[0] = SIGPREPTX_SCALING_X_TO_Y_VALUE(SIGPREPTX_SCALING_32768, SIGPREPTX_SCALING_100, sLedChannel_Target.asTgtVal[ucIdx].unDutyCycle, uint8);
  
    // Send LED Channel PWM
    (void)LGM_SendMessage(SigPrepTx_LumLedChnlIndex.unLumLedChnlIndex[ucIdx], aucLumLedChnl);
  }

  // Get Power Factors from Thermo Module
  (void)Rte_Read_Cpm_SigPrepTx_PowerFactor(&sThermoPowerFactor);

  for (uint8 ucIdx = 0u; ucIdx < SIGPREPTX_THERMOZONES_NR; ucIdx++)
  {
    aucPowerFactor[0] = sThermoPowerFactor.ucPowerFactor[ucIdx];

    // Send Power Factors
    (void)LGM_SendMessage(SigPrepTx_PowerFactorIndex.unPowerFactorIndex[ucIdx], aucPowerFactor);
  }
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ValidationFrames_200ms
///
/// \descr  Validation Frames Processing for frames with cycle time of 200 ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrepTx_ValidationFrames_200ms(void)
{
  uint8                aucTemp[1] = { 0u };
  tsRte_NTCTemperature sThzTemperatures;

  // Read Rsens temperatures 
  (void)Rte_Read_RSens_ThermzoneTemperatures(&sThzTemperatures);

  for (uint8 ucIdx = 0u; ucIdx < SIGPREPTX_THERMOZONES_NR; ucIdx++)
  {
    sThzTemperatures.s16_NTCTemperatureCelsius[ucIdx] = sThzTemperatures.s16_NTCTemperatureCelsius[ucIdx] / SIGPREPTX_TEMP_RESOLUTION;
    // Add -40 offset to temperature of Thermozone
    aucTemp[0] = (uint8)sThzTemperatures.s16_NTCTemperatureCelsius[ucIdx] + (uint8)SIGPREPTX_TEMP_OFFSET_40;

    // Send Thermozone Temperature
    (void)LGM_SendMessage(SigPrepTx_TempIndex.unTempIndex[ucIdx], aucTemp);
  }
}


//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ValidationFrames_PrepareStepperData
///
/// \descr  Validation Frames Processing for Stepper Data
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrepTx_ValidationFrames_PrepareStepperData(void)
{
  uint8                 aucDefaultValue[1] = { 0u };
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST) // Applicable for FULL only
  tsRte_ActStatStp0     sActStatStp0;
  uint8                 aucStepperErrStatus[1] = { 0u };
  uint8                 aucStepperMovement[2] = { 0u };
  sint16                nStepperMovement = 0;

  // Inhibit LVL Validation Frames information if ADL option is not available in coding
  boolean               boAdl_Enable = Cod_AvacStp_Enable();

  if (boAdl_Enable != FALSE)
  {
    // Read RTE port for Stepper data
    (void)Rte_Read_CtrlStp_ActStatStp_sVal_0(&sActStatStp0);
  }
  else
  {
    // Fill the buffer with dummy data because ADL option is inhibited
    sActStatStp0.sLvlValidationFrames.boLvl_Elec_Defect   = 0u;
    sActStatStp0.sLvlValidationFrames.boLvl_Temp_Defect   = 0u;
    sActStatStp0.sLvlValidationFrames.boLvl_StepLoss      = 0u;
    sActStatStp0.sLvlValidationFrames.boLvl_Moving        = 0u;
    sActStatStp0.sLvlValidationFrames.snLvl_Degree_Ctrl   = 0;
    sActStatStp0.sLvlValidationFrames.snLvl_Pos_Feedback  = 0;
  }

  aucStepperErrStatus[0] = (uint8)sActStatStp0.sLvlValidationFrames.boLvl_Elec_Defect;

  // Send Stepper Electrical Error
  (void)LGM_SendMessage(RL_LVL_ELEC_DEFECT, aucStepperErrStatus);

  aucStepperErrStatus[0] = (uint8)sActStatStp0.sLvlValidationFrames.boLvl_Temp_Defect;

  // Send Stepper Temperature Error
  (void)LGM_SendMessage(RL_LVL_TEMP_DEFECT, aucStepperErrStatus);

  aucStepperErrStatus[0] = (uint8)sActStatStp0.sLvlValidationFrames.boLvl_StepLoss;

  // Send Stepper Steploss Error
  (void)LGM_SendMessage(RL_LVL_STEPLOSS, aucStepperErrStatus);

  aucStepperErrStatus[0] = (uint8)sActStatStp0.sLvlValidationFrames.boLvl_Moving;

  // Send Stepper Steploss Error
  (void)LGM_SendMessage(RL_LVL_MOVING, aucStepperErrStatus);

  nStepperMovement = sActStatStp0.sLvlValidationFrames.snLvl_Degree_Ctrl / SIGPREPTX_TGTPOS_DENOMINATOR;
  aucStepperMovement[0] = (uint8)nStepperMovement;
  // PRQA S 4533, 4393 1 // Compiler can do right shift
  aucStepperMovement[1] = (uint8)(nStepperMovement >> 8u);

  // Send Stepper Steploss Error
  (void)LGM_SendMessage(RL_LVL_DEGREE_CONTROLLED, aucStepperMovement);

  nStepperMovement = sActStatStp0.sLvlValidationFrames.snLvl_Pos_Feedback / SIGPREPTX_TGTPOS_DENOMINATOR;
  aucStepperMovement[0] = (uint8)nStepperMovement;
  // PRQA S 4533, 4393 1 // Compiler can do right shift
  aucStepperMovement[1] = (uint8)(nStepperMovement >> 8u);

  // Send Stepper Steploss Error
  (void)LGM_SendMessage(RL_LVL_POS_FEEDBACK, aucStepperMovement);

#elif defined (CFG_VARIANT_ECO)
  // Trigger CAN frame transmission
  (void)LGM_SendMessage(RL_LVL_ELEC_DEFECT, aucDefaultValue);
#endif
}


#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST) // Applicable for FULL only
//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ValidationFrames_PrepareAngleData
///
/// \descr  Validation Frames Processing for Angle Data
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrepTx_ValidationFrames_PrepareAngleData(void)
{
  tsRte_DblOut  sDblSwivelling;
  tAdbOut       sGfhbAngle;
  uint8         aucAngle[2] = { 0u };
  sint16        nAngleTemp  = 0;

  // Get DBL Swivelling Angle
  (void)Rte_Read_Dbl_SwivellingOut(&sDblSwivelling);

  // Get GFHB angle
  (void)Rte_Read_ppsAdb_Out_sVal_0(&sGfhbAngle);

  for (uint8 ucIdx = 0u; ucIdx < SIGPREPTX_HEADLAMP_NR; ucIdx++)
  {
    // Check if DBL option is present in Coding
    if (Cod_Dbl_Enable() != FALSE)
    {
      nAngleTemp = (sDblSwivelling.SwivelAngle[ucIdx] * SIGPREPTX_DBL_RESOLUTION_5) / SIGPREPTX_DBL_RESOLUTION_10;

      aucAngle[0] = (uint8)nAngleTemp;
      // PRQA S 4533, 4393 1 // Compiler can do right shift
      aucAngle[1] = (uint8)(nAngleTemp >> 8u);
    }
    else
    {
      aucAngle[0] = 0u;
      aucAngle[1] = 0u;
    }

    // Send DBL Swiveling Angle
    (void)LGM_SendMessage(SigPrepTx_DblSwivAnglIndex.unDblSwivAnglIndex[ucIdx], aucAngle);
  }

  // Get Edge Left angle based on mounting side
  nAngleTemp = (SigPrepTx_eEcuSide == eLeftTxFrame) ? sGfhbAngle.Channel[eLeftTxFrame].EdgeLeft : sGfhbAngle.Channel[eRightTxFrame].EdgeLeft;

  aucAngle[0] = (uint8)nAngleTemp;
  // PRQA S 4533, 4393 1 // Compiler can do right shift
  aucAngle[1] = (uint8)(nAngleTemp >> 8u);

  // Send GFHB Left Angle
  (void)LGM_SendMessage(RL_GFHB_ANGLE_L, aucAngle);

  // Get Edge Right angle based on mounting side
  nAngleTemp = (SigPrepTx_eEcuSide == eLeftTxFrame) ? sGfhbAngle.Channel[eLeftTxFrame].EdgeRight : sGfhbAngle.Channel[eRightTxFrame].EdgeRight;

  aucAngle[0] = (uint8)nAngleTemp;
  // PRQA S 4533, 4393 1 // Compiler can do right shift
  aucAngle[1] = (uint8)(nAngleTemp >> 8u);

  // Send GFHB Right Angle
  (void)LGM_SendMessage(RL_GFHB_ANGLE_R, aucAngle);
}
#endif



// EOF
