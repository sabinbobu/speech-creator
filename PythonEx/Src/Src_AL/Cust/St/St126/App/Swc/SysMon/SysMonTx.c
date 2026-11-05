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
/// \file   SysMonTx.c
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
#include <SysMonTx.h>
//#include <p_IpduCallback.h>

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#if (CFG_DRV_CAN != CFG_Drv_None)
#define SYSMON_TX_FRM_CONFIG
#include <SysMon_Cfg.h>
#undef SYSMON_TX_FRM_CONFIG

#define SYSMON_TX_ENUM_FRM_CONFIG
#include <SysMon_Cfg.h>
#undef SYSMON_TX_ENUM_FRM_CONFIG
#endif

//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------
// Active Tx Status
STATIC_AL boolean                    SysMonTx_boActivateTx  = FALSE;
STATIC_AL teSysMon_TxSideFrameState  SysMonTx_eEcuSide      = eSysMonRightTxFrame;

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonTx_TimeoutCheck(uint8 ucFrmIdx);
STATIC_AL void    SysMonTx_FramesTimerInit(void);
STATIC_AL void    SysMonTx_FramesProcessing(void);

//-----------------------------------------------------------------------------
// function definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  SysMonTx_Init
///
/// \descr  SysMonTx init function
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void SysMonTx_Init(void)
{
  teRte_MountingSide          eMountingSide = { 0 };

  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  SysMonTx_eEcuSide = (eMountingSide != eMountedLeft) ? eSysMonRightTxFrame : eSysMonLeftTxFrame;

  // Init timer for all cyclic Tx frames
  SysMonTx_FramesTimerInit();
}


//-----------------------------------------------------------------------------
/// \brief  SysMonTx_Cycle0
///
/// \descr  SysMonTx cyclic main function
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
void SysMonTx_Cycle0(void)
{
  // Network On
  if (SysMonTx_boActivateTx != FALSE)
  {
    SysMonTx_FramesProcessing();
  }
  // Network Sleep
  else
  {
    // Init timer for all cyclic Tx frames - avoid time-out callback when network is spleep
    SysMonTx_FramesTimerInit();
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonTx_FramesInit
///
/// \descr  Init timer for Side Compatible Tx Frame
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonTx_FramesTimerInit(void)
{
  uint8 ucFrmIdx = 0u;

  // Init every Tx frame fron Tx frame config table
  for (ucFrmIdx = 0u; ucFrmIdx < countof(asSysMonCanTxFrameInfoConst); ucFrmIdx++)
  {
    // Check Side Compatibility
    if ((asSysMonCanTxFrameInfoConst[ucFrmIdx].eFrameSide == SysMonTx_eEcuSide) && (asSysMonCanTxFrameInfoConst[ucFrmIdx].ulTimeOut > 0u))
    {
      // Init timer
      asSysMonCanTxFrameInfoConst[ucFrmIdx].ulTimer = TimerGetTick();
    }
    else
    {
      // Skip, side incompatibility or it is an event frame
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief SysMonTx_FramesProcessing
///
/// \descr Tx Frames Processing [Cycle, Event and Dynamic objects]
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonTx_FramesProcessing(void)
{
  uint8 ucFrmIdx = 0u;

  // Init every Tx frame fron Tx frame config table
  for (ucFrmIdx = 0u; ucFrmIdx < countof(asSysMonCanTxFrameInfoConst); ucFrmIdx++)
  {
    // Check Frame Side Compatibility
    if (asSysMonCanTxFrameInfoConst[ucFrmIdx].eFrameSide == SysMonTx_eEcuSide)
    {
      // Run cycle frames
      if (asSysMonCanTxFrameInfoConst[ucFrmIdx].ulTimeOut > 0u)
      {
        if (asSysMonCanTxFrameInfoConst[ucFrmIdx].pfCycleCb != NULL_PTR)
        {
          // Cyclic callback
          asSysMonCanTxFrameInfoConst[ucFrmIdx].pfCycleCb();
        }
        else
        {
          // Null pointer call avoid
        }
        // Tx Time-Out
        // PRQA S 3415 1 // no right hand opperator side effect
        if ((asSysMonCanTxFrameInfoConst[ucFrmIdx].pfNotAckCb != NULL_PTR) && (SysMonTx_TimeoutCheck(ucFrmIdx) != FALSE))
        {
          asSysMonCanTxFrameInfoConst[ucFrmIdx].boMsgConfirmed = FALSE;
          asSysMonCanTxFrameInfoConst[ucFrmIdx].pfNotAckCb();
        }
        else
        {
          // Skip, timeout callback defined by a NULL_PTR or there isn't time-out in transmission
        }
      }
      else
      {
        // Nothing to do
      }
    }
    else
    {
      // Skip, frame side mismatching
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonTx_TimeoutCheck
///
/// \descr  Rx Frame Timeout check 
///
/// \param  ucFrmIdx:  frame Index
///
/// \return boolean True, if timeout occured
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonTx_TimeoutCheck(uint8 ucFrmIdx)
{
  boolean boRetToStatus = FALSE;

  if ((TIMER_SIGNED)TimerGetTimeSince(asSysMonCanTxFrameInfoConst[ucFrmIdx].ulTimer) >= (TIMER_SIGNED)UTILTIME_MSEC(asSysMonCanTxFrameInfoConst[ucFrmIdx].ulTimeOut))
  {
    // Timeout occurred
    // Reset timer
    asSysMonCanTxFrameInfoConst[ucFrmIdx].ulTimer = TimerGetTick();
    boRetToStatus = TRUE;
  }
  else
  {
    // Keep returning false (no time-out)
  }

  return boRetToStatus;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonTx_ComM_ActivateTxBufer
///
/// \descr This ComM callback activate TxBuffer Processing
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void SysMonTx_ComM_ActivateTxBufer(void)
{
  SysMonTx_boActivateTx = TRUE;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonTx_ComM_DeactivateTxBuffer
///
/// \descr This ComM callback dezactivate TxBuffer Processing
///
/// \param void
///
/// \return void 
//-----------------------------------------------------------------------------
void SysMonTx_ComM_DeactivateTxBuffer(void)
{
  SysMonTx_boActivateTx = FALSE;
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
//void LGM_HS6_DIAG_DRVLED_Sent(void)
void reSysMonTx_HS6_DIAG_DRVLED_Sent(void)
{
  // Check if the current side is left
  if (SysMonTx_eEcuSide == eSysMonLeftTxFrame)
  {
    // Indicate message reception on left side
    asSysMonCanTxFrameInfoConst[CANTX_HS6_DIAG_DRVLED_L_457].boMsgConfirmed = TRUE;
    // Reset timer
    asSysMonCanTxFrameInfoConst[CANTX_HS6_DIAG_DRVLED_L_457].ulTimer = TimerGetTick();
  }
  else
  {
    // Indicate message reception on right side
    asSysMonCanTxFrameInfoConst[CANTX_HS6_DIAG_DRVLED_R_477].boMsgConfirmed = TRUE;
    // Reset timer
    asSysMonCanTxFrameInfoConst[CANTX_HS6_DIAG_DRVLED_R_477].ulTimer = TimerGetTick();
  }
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
//void LGM_HS6_DIAG_DRVLED_NotSent(void)
void reSysMonTx_HS6_DIAG_DRVLED_NotSent(void)
{
  (void)0;
}

// EOF
