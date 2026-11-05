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
/// \file   SysMonRx.c
///
/// \brief  Rx Frame processing
///
/// \descr  Input Rx Frame processing based on Rx Frame config table
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <SysMonRx.h>
#include <SysMonRx_ASIL.h>
#include <SysMonCheck_Data.h>
#include <SysMonRx_Callbacks.h>
#include <Bsw/WdgM/WdgM.h>

#ifdef UNIT_TEST
#include <_NM_Types.h>
#endif

#if (CFG_DRV_CAN != CFG_Drv_None)
#define SYSMON_RX_FRM_CONFIG
#include <SysMon_Cfg.h>
#undef SYSMON_RX_FRM_CONFIG

#define SYSMON_RX_ENUM_FRM_CONFIG
#include <SysMon_Cfg.h>
#undef SYSMON_RX_ENUM_FRM_CONFIG
#endif



//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------
STATIC_AL boolean                  SysMonRx_boRxInitStatus        = FALSE;
STATIC_AL boolean                  SysMonRx_boCbDeactivateStatus  = TRUE;
STATIC_AL teRte_MountingSide       SysMonRx_eMountingSide         = { 0 };
STATIC_AL uint32                   SysMonRx_ulCycleCounter        = 0u;
STATIC_AL NM_ModeType              SysMonRx_eNMMode               = REVEIL;
STATIC_AL tSysMon_RxCyclicCounters SysMonRx_sRedundencyCounters = {
  {
    { 0u,  SYSMON_0x2AE_TIMEOUT },
    { 0u,  SYSMON_0x34E_TIMEOUT },
    { 0u,  SYSMON_0x36_TIMEOUT  },
    { 0u,  SYSMON_0x432_TIMEOUT },
    { 0u,  SYSMON_0x38D_TIMEOUT }
   }
};


//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_HandleRxFrame        (uint8 ucFrmIdx);
STATIC_AL void SysMonRx_WriteRTE             (void);
STATIC_AL void SysMonRx_UpdateRedundancyCheckCounter(uint8 ucIndx);

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Init
///
/// \descr  Init function of SysMonRx
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void SysMonRx_Init(void)
{
  // Rx Frame Index
  uint8 ucFrmIdx;

  // Initialize Cycle Counter
  SysMonRx_ulCycleCounter = 0u;

  for (uint8 ucIdx = 0u; ucIdx < CANRX_NR_FRAMES; ucIdx++)
  {
    SysMonRx_sRedundencyCounters.sRxCyclicCheck[ucIdx].ulRxCounter = 0u;
  }

  // Initialize SysMon interfaces for Low Beam and Turn Indicator
  SysMonRx_ASIL_InitLowBeamAndTurnIndicatorInterfaces();

  // Read MountingSide RTE port
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&SysMonRx_eMountingSide);

  // Init every Rx frame fron Rx frame config table
  for (ucFrmIdx = 0u; ucFrmIdx < countof(asSysMonCanRxFrameInfoConst); ucFrmIdx++)
  {
    // Call callback with state Init
    if (asSysMonCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback != NULL_PTR)
    {
      asSysMonCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback(eSysMonFrameInit);
    }
    else
    {
      // Avoid NULL ptr call
    }
  }

  // Init Status Flag Set
  SysMonRx_boRxInitStatus = TRUE;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Cycle0
///
/// \descr  Cyclic function
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
void SysMonRx_Cycle0(void)
{
  uint8 ucFrmIdx;

  // Increment Cycle Counter
  if (SysMonRx_boCbDeactivateStatus == FALSE)
  {
	  SysMonRx_ulCycleCounter++;
  }
  else
  {
	  // nothing to do
  }

  // All Rx Frames to be processed
  for (ucFrmIdx = 0u; ucFrmIdx < countof(asSysMonCanRxFrameInfoConst); ucFrmIdx++)
  {
    SysMonRx_HandleRxFrame(ucFrmIdx);
  }

  WdgM_SetLocalCheckPoint(0u);

  // Evaluate Emergency Operation Mode table
  SysMonRx_ASIL_EmergencyOperation();

  // Send LowBeam status to FctR
  SysMonRx_WriteRTE();
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_HandleRxFrame
///
/// \descr  Handle Reception Frame
///
/// \param  ucFrmIdx - Frame Index
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_HandleRxFrame(uint8 ucFrmIdx)
{
  // If SysMonRx is initialized
  if (SysMonRx_boRxInitStatus != FALSE)
  {
    // Check callback address and precheck status
    if (asSysMonCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback != NULL_PTR)
    {
      // Get life phasis from the NM
      (void)Rte_Read_SigPrep_NMMode(&SysMonRx_eNMMode);

      // Check frame timeout
      if ((asSysMonCanRxFrameInfoConst[ucFrmIdx].boMsgTimedOut != FALSE) ||
        ((SysMonRx_sRedundencyCounters.sRxCyclicCheck[ucFrmIdx].ulRxCounter + (uint32)SysMonRx_sRedundencyCounters.sRxCyclicCheck[ucFrmIdx].unTimeoutVal < SysMonRx_ulCycleCounter) && 
          ((SysMonRx_eNMMode == NM_NORMAL) || (SysMonRx_eNMMode == LIMP_HOME_MODE))))
      {
        // Timeout occured - call callback with state TimeOut
        asSysMonCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback(eSysMonFrmTimeOut);
        // Reset message timeout flag
        asSysMonCanRxFrameInfoConst[ucFrmIdx].boMsgTimedOut = FALSE;
      }
      else if (asSysMonCanRxFrameInfoConst[ucFrmIdx].boMsgUpdated != FALSE)
      {
        // Message indication call callback with state Event
        asSysMonCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback(eSysMonFrmEvent);
        asSysMonCanRxFrameInfoConst[ucFrmIdx].boMsgUpdated = FALSE;
      }
      else
      {
        // Avoid NULL ptr call
      }
    }
    else
    {
      // Frame callback is NULL_PTR
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ComM_DisableCallbacks
///
/// \descr  Calback used to deactivate all frame callbacks
///
/// \param -
///
/// \return void
//-----------------------------------------------------------------------------
void  SysMonRx_ComM_DisableCallbacks(void)
{
  // Update Deactivation Status for 38D Alive counter & CRC reset
  SysMonRx_Callbacks_UpdateDeactivationStatus(FALSE);

  SysMonRx_boCbDeactivateStatus = TRUE;
  SysMonRx_Callbacks_ResetSigQty();

  // Reset redundancy counter
  SysMonRx_ulCycleCounter = 0u;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ComM_EnableCallbacks
///
/// \descr  Calback used to activate all frame callbacks
///
/// \param -
///
/// \return void
//-----------------------------------------------------------------------------
void  SysMonRx_ComM_EnableCallbacks(void)
{
  // Update Deactivation Status for 38D Alive counter & CRC reset
  SysMonRx_Callbacks_UpdateDeactivationStatus(TRUE);

  SysMonRx_boCbDeactivateStatus = FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_GetMountingSide
///
/// \descr  Get the value of Headlamp Mounting Side
///
/// \param  -
///
/// \return teRte_MountingSide
//-----------------------------------------------------------------------------
teRte_MountingSide SysMonRx_GetMountingSide(void)
{
  return SysMonRx_eMountingSide;
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DAT_VSM_2AE -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_2AE_Received
///
/// \descr  Handling of 0x2AE CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_DAT_VSM_2AE_Received(void)
void reSysMonRx_HS6_DAT_VSM_2AE_Received(void)
{
  // SysMon Rx enabled
  if (SysMonRx_boCbDeactivateStatus != FALSE)
  {
    // SysMonRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_2AE].boMsgUpdated   = TRUE;
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_2AE].boMsgTimedOut  = FALSE;
    // Update redundancy check Counter
    SysMonRx_UpdateRedundancyCheckCounter(CANRX_HS6_DAT_VSM_2AE);
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_2AE_NotReceived
///
/// \descr  Handling of 0x2AE CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_DAT_VSM_2AE_NotReceived(void)
void reSysMonRx_HS6_DAT_VSM_2AE_NotReceived(void)
{
  // If SysMonRx is enabled
  if (SysMonRx_boCbDeactivateStatus != FALSE)
  {
    // SysMonRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_2AE].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DAT_VSM_34E -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_34E_Received
///
/// \descr  Handling of 0x34E CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_DAT_VSM_34E_Received(void)
void reSysMonRx_HS6_DAT_VSM_34E_Received(void)
{
  // SysMon Rx enabled
  if (SysMonRx_boCbDeactivateStatus != FALSE)
  {
    // SysMonRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_34E].boMsgUpdated   = TRUE;
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_34E].boMsgTimedOut  = FALSE;
    // Update redundancy check Counter
    SysMonRx_UpdateRedundancyCheckCounter(CANRX_HS6_DAT_VSM_34E);

    // toggle Rx Indicator from successful message reception, because it will be used by E2E Profile to check the reception of the message and proceed to check the integrity of that
    APPLI_ui32_Hs6DatVsm34eIndicator = (APPLI_ui32_Hs6DatVsm34eIndicator == EECO_E_HEARTBEAT_STATE_A) ? EECO_E_HEARTBEAT_STATE_B : EECO_E_HEARTBEAT_STATE_A;
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_34E_NotReceived
///
/// \descr  Handling of 0x34E CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_DAT_VSM_34E_NotReceived(void)
void reSysMonRx_HS6_DAT_VSM_34E_NotReceived(void)
{
  // If SysMonRx is enabled
  if (SysMonRx_boCbDeactivateStatus != FALSE)
  {
    // SysMonRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_34E].boMsgTimedOut = TRUE;
  }
}


// ----------------------------------------------------------------------------
// --------------------- HS6_COMMANDES_VSM_036 --------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_COMMANDES_VSM_036_Received
///
/// \descr  Handling of 0x36 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_COMMANDES_VSM_036_Received(void)
void reSysMonRx_HS6_COMMANDES_VSM_036_Received(void)
{
  // Indicate message reception
  asSysMonCanRxFrameInfoConst[CANRX_HS6_COMMANDES_VSM_036].boMsgUpdated   = TRUE;
  asSysMonCanRxFrameInfoConst[CANRX_HS6_COMMANDES_VSM_036].boMsgTimedOut  = FALSE;
  // Update redundancy check Counter
  SysMonRx_UpdateRedundancyCheckCounter(CANRX_HS6_COMMANDES_VSM_036);
}



//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_COMMANDES_VSM_036_NotReceived
///
/// \descr  Handling of 0x36 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_COMMANDES_VSM_036_NotReceived(void)
void reSysMonRx_HS6_COMMANDES_VSM_036_NotReceived(void)
{
  // Indicate message timeout
  asSysMonCanRxFrameInfoConst[CANRX_HS6_COMMANDES_VSM_036].boMsgTimedOut = TRUE;
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DAT_BSI_432 -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_BSI_432_Received
///
/// \descr  Handling of 0x432 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_DAT_BSI_432_Received(void)
void reSysMonRx_HS6_DAT_BSI_432_Received(void)
{
  // If SysMonRx is enabled
  if (SysMonRx_boCbDeactivateStatus != FALSE)
  {
    // SysMonRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DAT_BSI_432].boMsgUpdated   = TRUE;
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DAT_BSI_432].boMsgTimedOut  = FALSE;
    // Update redundancy check Counter
    SysMonRx_UpdateRedundancyCheckCounter(CANRX_HS6_DAT_BSI_432);
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_BSI_432_NotReceived
///
/// \descr  Handling of 0x432 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_DAT_BSI_432_NotReceived(void)
void reSysMonRx_HS6_DAT_BSI_432_NotReceived(void)
{
  // If SysMonRx is enabled
  if (SysMonRx_boCbDeactivateStatus != FALSE)
  {
    // SysMonRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DAT_BSI_432].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DYN_ABR_38D -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_ABR_38D_Received
///
/// \descr  Handling of 0x38D CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_DYN_ABR_38D_Received(void)
void reSysMonRx_HS6_DYN_ABR_38D_Received(void)
{
  // If SysMonRx is enabled
  if (SysMonRx_boCbDeactivateStatus != FALSE)
  {
    // SysMonRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DYN_ABR_38D].boMsgUpdated   = TRUE;
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DYN_ABR_38D].boMsgTimedOut  = FALSE;
    // Update redundancy check Counter
    SysMonRx_UpdateRedundancyCheckCounter(CANRX_HS6_DYN_ABR_38D);
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_ABR_38D_NotReceived
///
/// \descr  Handling of 0x38D CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
//void LGM_HS6_DYN_ABR_38D_NotReceived(void)
void reSysMonRx_HS6_DYN_ABR_38D_NotReceived(void)
{
  // If SysMonRx is enabled
  if (SysMonRx_boCbDeactivateStatus != FALSE)
  {
    // SysMonRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSysMonCanRxFrameInfoConst[CANRX_HS6_DYN_ABR_38D].boMsgTimedOut = TRUE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_WriteRTE
///
/// \descr  RTE write of Low Beam to FctR
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_WriteRTE(void)
{
  teRte_ReqLightState  eLowBeamCmd       = (SysMonRx_ASIL_Get_boEmergencyOperation_FinalLowBeamStatus() != FALSE) ? ReqLighted_On : ReqLighted_Off;
  teRte_ReqLightState  eTurnIndicatorCmd = (SysMonRx_ASIL_Get_boEmergencyOperation_FinalTurnIndicatorStatus() != FALSE) ? ReqLighted_On : ReqLighted_Off;
  boolean              boCrc32OverCoding = FALSE;

  // Get CRC32 over FuSa coding block from CodM
  boCrc32OverCoding = SysMonCheck_Data_GetCrc32IntegrityCheck();

  // Check if CRC32 over FuSa coding area is faled, disable TI
  if (boCrc32OverCoding == FALSE)
  {
    // Disable TI function
    eTurnIndicatorCmd = ReqLighted_Off;
  }
  else
  {
    // nothing to do
  }

  (void)Rte_Write_SysMon_LowBeamCmd_Req(&eLowBeamCmd);
  (void)Rte_Write_SysMon_TurnIndicatorCmd_Req(&eTurnIndicatorCmd);
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_UpdateRedundancyCheckCounter
///
/// \descr  Update redundancy check counter of received message
///
/// \param  ucIndx - index of message in array
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_UpdateRedundancyCheckCounter(uint8 ucIndx)
{
  SysMonRx_sRedundencyCounters.sRxCyclicCheck[ucIndx].ulRxCounter = SysMonRx_ulCycleCounter;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_getNMMode
///
/// \descr  Return the NM Mode of the LGM Stack
///
/// \param  void
///
/// \return NM_ModeType
//-----------------------------------------------------------------------------
NM_ModeType SysMonRx_getNMMode(void)
{
  return SysMonRx_eNMMode;
}


// EOF
