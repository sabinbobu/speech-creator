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
/// \file   SigPrepRx.c
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
#include <SigPrepRx.h>


#if (CFG_DRV_CAN != CFG_Drv_None)
#define SIGPREP_RX_FRM_CONFIG
#include <SigPrep_Cfg.h>
#undef SIGPREP_RX_FRM_CONFIG

#define SIGPREP_RX_ENUM_FRM_CONFIG
#include <SigPrep_Cfg.h>
#undef SIGPREP_RX_ENUM_FRM_CONFIG
#endif

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------
STATIC_AL boolean                   SigPrepRx_boRxInitStatus        = FALSE;
STATIC_AL boolean                   SigPrepRx_boCbDeactivateStatus  = TRUE;
STATIC_AL teRte_MountingSide        SigPrepRx_eMountingSide         = { 0 };
STATIC_AL uint16                    SigPrep_Data_unCONFIG_TIME      = 0u;
CONST_AL  tNvmPara_CodingArea*      SigPrep_Data_pCodingArea        = NULL_PTR;
STATIC_AL tsSigPrep_Coding_Options  SigPrep_Coding_Options          = { FALSE };

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
STATIC_AL void     SigPrepRx_HandleRxFrame       (uint8 ucFrmIdx);
STATIC_AL boolean  SigPrep_CodingDataValidation  (void);
STATIC_AL boolean  SigPrep_Data_ParaFct0         (tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
STATIC_AL void     SigPrep_SetCodingData         (boolean boIsCodingDataValid);

//-----------------------------------------------------------------------------
// Interface functions
//-----------------------------------------------------------------------------
uint16   SigPrepRx_GetConfigTime(void)     { return SigPrep_Data_unCONFIG_TIME;                    }
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
boolean  Cod_Dbl_Enable(void)              { return SigPrep_Coding_Options.boDbl_Enable;           }
boolean  Cod_GFHB_Enable(void)             { return SigPrep_Coding_Options.boGFHB_Enable;          }
boolean  Cod_CurtainEffect_Enable(void)    { return SigPrep_Coding_Options.boCurtainEffect_Enable; }
boolean  Cod_TSAG_Enable(void)             { return SigPrep_Coding_Options.boTSAG_Enable;          }
boolean  Cod_Motorway_Enable(void)         { return SigPrep_Coding_Options.boMotorway_Enable;      }
boolean  Cod_CurvatureMode(void)           { return SigPrep_Coding_Options.boCurvatureMode;        }
boolean  Cod_AvacStp_Enable(void)          { return SigPrep_Coding_Options.boAvacStp_Enable;       }
#endif // (CFG_VARIANT_FULL) || defined(UNIT_TEST)
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)
// Check if ASL option is present in Coding for ECO version
boolean  Cod_Asl_Enable(void)              { return SigPrep_Coding_Options.boAsl_Enable;           }
#endif // (CFG_VARIANT_ECO) || (UNIT_TEST)


//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_Init
///
/// \descr  Init function of SigPrepRx
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrepRx_Init(void)
{
  // Rx Frame Index
  uint8 ucFrmIdx;
  // Precheck status
  boolean boFrmPrecheckStat;
  // Coding validity check
  CONST_AL boolean boCodingValidity = SigPrep_CodingDataValidation();

  // Load the coding parameters
  SigPrep_SetCodingData(boCodingValidity);

  // Read MountingSide RTE port
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&SigPrepRx_eMountingSide);

  // Init every Rx frame fron Rx frame config table
  for (ucFrmIdx = 0u; ucFrmIdx < countof(asSigPrepCanRxFrameInfoConst); ucFrmIdx++)
  {
    // Supose precheck status to be true
    boFrmPrecheckStat = TRUE;

    // Prechecking frame (Side compatibility)
    // PRQA S 3415  1 // Side effect not present in this case
    if ((asSigPrepCanRxFrameInfoConst[ucFrmIdx].pfPreCheckCb != NULL_PTR) && (asSigPrepCanRxFrameInfoConst[ucFrmIdx].pfPreCheckCb() == FALSE))
    {
      // Set precheck status to false
      boFrmPrecheckStat = FALSE;
    }
    else
    {
      // Keep precheck status true
    }

    // Frame precheck pass
    if (boFrmPrecheckStat != FALSE)
    {
      // Call callback with state Init
      if (asSigPrepCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback != NULL_PTR)
      {
        asSigPrepCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback(eFrameInit);
      }
      else
      {
        // Avoid NULL ptr call
      }
    }
    else
    {
      // Do nothing
    }
  }

  // Init Status Flag Set
  SigPrepRx_boRxInitStatus = TRUE;
}



//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_Cycle0
///
/// \descr  Cyclic function
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
void SigPrepRx_Cycle0(void)
{
  uint8 ucFrmIdx;

  // All Rx Frames to be processed
  for (ucFrmIdx = 0u; ucFrmIdx < countof(asSigPrepCanRxFrameInfoConst); ucFrmIdx++)
  {
    SigPrepRx_HandleRxFrame(ucFrmIdx);
  }
}



//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_HandleRxFrame
///
/// \descr  Handle Reception Frame
///
/// \param  ucFrmIdx - Frame Index
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void SigPrepRx_HandleRxFrame(uint8 ucFrmIdx)
{
  // Rx Frame Precheck status
  boolean boFrmPrecheckStat;

  // If SigPrepRx is initialized
  if (SigPrepRx_boRxInitStatus != FALSE)
  {
    // Supose precheck to be true
    boFrmPrecheckStat = TRUE;

    // Prechecking Rx Frame (Side compatibility)
    // PRQA S 3415  1 // Side effect not present in this case
    if ((asSigPrepCanRxFrameInfoConst[ucFrmIdx].pfPreCheckCb != NULL_PTR) && (asSigPrepCanRxFrameInfoConst[ucFrmIdx].pfPreCheckCb() == FALSE))
    {
      // Set precheck status to false
      boFrmPrecheckStat = FALSE;
    }
    else
    {
      // Do nothing
    }
    // Check callback address and precheck status
    if ((boFrmPrecheckStat != FALSE) && (asSigPrepCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback != NULL_PTR))
    {
      // Check frame timeout
      if (asSigPrepCanRxFrameInfoConst[ucFrmIdx].boMsgTimedOut != FALSE)
      {
        // Timeout occured - call callback with state TimeOut
        asSigPrepCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback(eFrmTimeOut);
        // Reset message timeout flag
        asSigPrepCanRxFrameInfoConst[ucFrmIdx].boMsgTimedOut = FALSE;
      }
      else if (asSigPrepCanRxFrameInfoConst[ucFrmIdx].boMsgUpdated != FALSE)
      {
        // Message indication call callback with state Event
        asSigPrepCanRxFrameInfoConst[ucFrmIdx].pfFrmCallback(eFrmEvent);
        asSigPrepCanRxFrameInfoConst[ucFrmIdx].boMsgUpdated = FALSE;
      }
      else
      {
        // Avoid NULL ptr call
      }
    }
    else
    {
      // Precheck failed or frame callback is NULL_PTR
    }
  }
  else
  {
    // nothing to do
  }
}



//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_ComM_DisableCallbacks
///
/// \descr  Calback used to deactivate all frame callbacks
///
/// \param -
///
/// \return void
//-----------------------------------------------------------------------------
void  SigPrepRx_ComM_DisableCallbacks(void)
{
  SigPrepRx_boCbDeactivateStatus = TRUE;
}



//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_ComM_EnableCallbacks
///
/// \descr  Calback used to activate all frame callbacks
///
/// \param -
///
/// \return void
//-----------------------------------------------------------------------------
void  SigPrepRx_ComM_EnableCallbacks(void)
{
  SigPrepRx_boCbDeactivateStatus = FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_GetMountingSide
///
/// \descr  Get the value of Headlamp Mounting Side
///
/// \param  -
///
/// \return teRte_MountingSide
//-----------------------------------------------------------------------------
teRte_MountingSide SigPrepRx_GetMountingSide(void)
{
  return SigPrepRx_eMountingSide;
}



// ----------------------------------------------------------------------------
// ----------------------- HS6_ACQ_NEW_JDD_55F --------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_ACQ_NEW_JDD_55F_Received
///
/// \descr  Handling of 0x55F CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_ACQ_NEW_JDD_55F_Received(void)
{
  // Indicate message reception
  asSigPrepCanRxFrameInfoConst[CANRX_HS6_ACQ_NEW_JDD_55F].boMsgUpdated  = TRUE;
  asSigPrepCanRxFrameInfoConst[CANRX_HS6_ACQ_NEW_JDD_55F].boMsgTimedOut = FALSE;
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DAT_VSM_36E -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_36E_Received
///
/// \descr  Handling of 0x36E CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_36E_Received(void)
{
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_36E].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_36E].boMsgTimedOut = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_36E_NotReceived
///
/// \descr  Handling of 0x36E CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_36E_NotReceived(void)
{
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_36E].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DAT_VSM_3AE -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_3AE_Received
///
/// \descr  Handling of 0x3AE CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_3AE_Received(void)
{
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_3AE].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_3AE].boMsgTimedOut = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_3AE_NotReceived
///
/// \descr  Handling of 0x3AE CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_3AE_NotReceived(void)
{
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_3AE].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DAT_VSM_54D -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_54D_Received
///
/// \descr  Handling of 0x54D CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_54D_Received(void)
{
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_54D].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_54D].boMsgTimedOut = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_54D_NotReceived
///
/// \descr  Handling of 0x54D CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_54D_NotReceived(void)
{
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_54D].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// ---------------------- HS6_DAT4_V2_BSI_552 ---------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT4_V2_BSI_552_Received
///
/// \descr  Handling of 0x552 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT4_V2_BSI_552_Received(void)
{
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT4_V2_BSI_552].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT4_V2_BSI_552].boMsgTimedOut = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT4_V2_BSI_552_NotReceived
///
/// \descr  Handling of 0x552 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT4_V2_BSI_552_NotReceived(void)
{
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT4_V2_BSI_552].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// ----------------------- HS6_DYN3_CMM_468 -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN3_CMM_468_Received
///
/// \descr  Handling of 0x468 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN3_CMM_468_Received(void)
{
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN3_CMM_468].boMsgUpdated   = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN3_CMM_468].boMsgTimedOut  = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN3_CMM_468_NotReceived
///
/// \descr  Handling of 0x468 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN3_CMM_468_NotReceived(void)
{
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN3_CMM_468].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// ------------------- HS6_INTE_ELECTRON_BSI_092 ------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_INTE_ELECTRON_BSI_092_Received
///
/// \descr  Handling of 0x92 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_INTE_ELECTRON_BSI_092_Received(void)
{
  // Indicate message reception
  asSigPrepCanRxFrameInfoConst[CANRX_HS6_INTE_ELECTRON_BSI_092].boMsgUpdated  = TRUE;
  asSigPrepCanRxFrameInfoConst[CANRX_HS6_INTE_ELECTRON_BSI_092].boMsgTimedOut = FALSE;
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DYN2_FRE_3CD ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN2_FRE_3CD_Received
///
/// \descr  Handling of 0x3CD CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN2_FRE_3CD_Received(void)
{
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN2_FRE_3CD].boMsgUpdated   = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN2_FRE_3CD].boMsgTimedOut  = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN2_FRE_3CD_NotReceived
///
/// \descr  Handling of 0x3CD CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN2_FRE_3CD_NotReceived(void)
{
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN2_FRE_3CD].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// --------------------- HS6_DAT2_DRVLED_R_4D7 --------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT2_DRVLED_R_4D7_Received
///
/// \descr  Handling of 0x4D7 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT2_DRVLED_R_4D7_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT2_DRVLED_R_4D7_RX].boMsgUpdated   = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT2_DRVLED_R_4D7_RX].boMsgTimedOut  = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT2_DRVLED_R_4D7_NotReceived
///
/// \descr  Handling of 0x4D7 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT2_DRVLED_R_4D7_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT2_DRVLED_R_4D7_RX].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DYN_BEMP_2B7 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_BEMP_2B7_Received
///
/// \descr  Handling of 0x2B7 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_BEMP_2B7_Received(void)
{
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_BEMP_2B7_RX].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_BEMP_2B7_RX].boMsgTimedOut = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_BEMP_2B7_NotReceived
///
/// \descr  Handling of 0x2B7 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_BEMP_2B7_NotReceived(void)
{
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_BEMP_2B7_RX].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_257 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_257_Received
///
/// \descr  Handling of 0x257 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_257_Received(void)
{
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_257].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_257].boMsgTimedOut = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_257_NotReceived
///
/// \descr  Handling of 0x257 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_257_NotReceived(void)
{
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_257].boMsgTimedOut = TRUE;
  }
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DAT_CSS_350 -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_CSS_350_Received
///
/// \descr  Handling of 0x350 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_CSS_350_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_CSS_350].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_CSS_350].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_CSS_350_NotReceived
///
/// \descr  Handling of 0x350 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_CSS_350_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_CSS_350].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// --------------------- HS6_DAT_DRVLED_R_297 ---------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_DRVLED_R_297_Received
///
/// \descr  Handling of 0x297 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_DRVLED_R_297_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_DRVLED_R_297_RX].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_DRVLED_R_297_RX].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_DRVLED_R_297_NotReceived
///
/// \descr  Handling of 0x297 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_DRVLED_R_297_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_DRVLED_R_297_RX].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DYN_VSM_28E -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_28E_Received
///
/// \descr  Handling of 0x28E CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_28E_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_28E].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_28E].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_28E_NotReceived
///
/// \descr  Handling of 0x28E CAN failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_28E_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_28E].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DAT_VSM_32E -----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_32E_Received
///
/// \descr  Handling of 0x32E CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_32E_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_32E].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_32E].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_32E_NotReceived
///
/// \descr  Handling of 0x32E CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_32E_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
}
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT_VSM_32E].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------ HS6_DAT7_BSI_612 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT7_BSI_612_Received
///
/// \descr  Handling of 0x612 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT7_BSI_612_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT7_BSI_612].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT7_BSI_612].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT7_BSI_612_NotReceived
///
/// \descr  Handling of 0x612 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT7_BSI_612_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
}
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DAT7_BSI_612].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_0AB ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0AB_Received
///
/// \descr  Handling of 0xAB CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0AB_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0AB].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0AB].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0AB_NotReceived
///
/// \descr  Handling of 0xAB CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0AB_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0AB].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_0C3 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0C3_Received
///
/// \descr  Handling of 0xC3 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0C3_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0C3].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0C3].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0C3_NotReceived
///
/// \descr  Handling of 0xC3 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0C3_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0C3].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_0CB ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0CB_Received
///
/// \descr  Handling of 0xCB CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0CB_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0CB].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0CB].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0CB_NotReceived
///
/// \descr  Handling of 0xCB CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0CB_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0CB].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_0E3 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0E3_Received
///
/// \descr  Handling of 0xE3 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0E3_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0E3].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0E3].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0E3_NotReceived
///
/// \descr  Handling of 0xE3 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0E3_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0E3].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_0EB ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0EB_Received
///
/// \descr  Handling of 0xEB CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0EB_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0EB].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0EB].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_0EB_NotReceived
///
/// \descr  Handling of 0xEB CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_0EB_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_0EB].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_103 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_103_Received
///
/// \descr  Handling of 0x103 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_103_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_103].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_103].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_103_NotReceived
///
/// \descr  Handling of 0x103 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_103_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_103].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_10B ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_10B_Received
///
/// \descr  Handling of 0x10B CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_10B_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_10B].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_10B].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_10B_NotReceived
///
/// \descr  Handling of 0x10B CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_10B_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_10B].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_123 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_123_Received
///
/// \descr  Handling of 0x123 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_123_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_123].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_123].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_123_NotReceived
///
/// \descr  Handling of 0x123 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_123_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_123].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_12B ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_12B_Received
///
/// \descr  Handling of 0x12B CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_12B_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_12B].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_12B].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_12B_NotReceived
///
/// \descr  Handling of 0x12B CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_12B_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_12B].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_143 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_143_Received
///
/// \descr  Handling of 0x143 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_143_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_143].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_143].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_143_NotReceived
///
/// \descr  Handling of 0x143 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_143_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_143].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_14B ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_14B_Received
///
/// \descr  Handling of 0x14B CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_14B_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_14B].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_14B].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_14B_NotReceived
///
/// \descr  Handling of 0x14B CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_14B_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_14B].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_163 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_163_Received
///
/// \descr  Handling of 0x163 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_163_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_163].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_163].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_163_NotReceived
///
/// \descr  Handling of 0x163 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_163_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_163].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_16B ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_16B_Received
///
/// \descr  Handling of 0x16B CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_16B_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_16B].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_16B].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_16B_NotReceived
///
/// \descr  Handling of 0x16B CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_16B_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_16B].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_183 ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_183_Received
///
/// \descr  Handling of 0x183 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_183_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_183].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_183].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_183_NotReceived
///
/// \descr  Handling of 0x183 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_183_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_183].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_18B ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_18B_Received
///
/// \descr  Handling of 0x18B CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_18B_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_18B].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_18B].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_18B_NotReceived
///
/// \descr  Handling of 0x18B CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_18B_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_18B].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}



// ----------------------------------------------------------------------------
// ------------------------- HS6_DYN_VSM_1AB ----------------------------------
// ----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_1AB_Received
///
/// \descr  Handling of 0x1AB CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_1AB_Received(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_1AB].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_1AB].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_VSM_1AB_NotReceived
///
/// \descr  Handling of 0x1AB CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_VSM_1AB_NotReceived(void)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DYN_VSM_1AB].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_ECO)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DIAG_DRVLED_R_477_Received
///
/// \descr  Handling of 0x477 CAN frame successful reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DIAG_DRVLED_R_477_Received(void)
{
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST) // Applicable only for ECO version
  // SigPrep Rx enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message reception
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DIAG_DRVLED_R_477_RX].boMsgUpdated  = TRUE;
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DIAG_DRVLED_R_477_RX].boMsgTimedOut = FALSE;
  }
#elif defined (CFG_VARIANT_FULL)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DIAG_DRVLED_R_477_NotReceived
///
/// \descr  Handling of 0x477 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DIAG_DRVLED_R_477_NotReceived(void)
{
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST) // Applicable only for ECO version
  // If SigPrepRx is enabled
  if (SigPrepRx_boCbDeactivateStatus != FALSE)
  {
    // SigPrepRx is not enabled, do nothing
  }
  else
  {
    // Indicate message timeout
    asSigPrepCanRxFrameInfoConst[CANRX_HS6_DIAG_DRVLED_R_477_RX].boMsgTimedOut = TRUE;
  }
#elif defined (CFG_VARIANT_FULL)
  (void)0U; // Nothing to do
#endif
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_2AE_Received
///
/// \descr  LGM notification callback for 0x2AE CAN frame reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_2AE_Received(void)
{
  tHS6_DAT_VSM_2AE stData;
  
  stData.ucWarningMode             = *WARNING_MODE;
  stData.ucEtatClignotants         = *ETAT_CLIGNOTANTS;
  stData.ucLeftTurnIndicatorCmd    = *CTRL_TI_L_F_S;
  stData.ucRightTurnIndicatorCmd   = *CTRL_TI_R_F_S;
  stData.ucTurnIndicatorScrolling  = *SCROLLING_TI;

  (void)Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received(&stData);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_2AE_NotReceived
///
/// \descr  LGM notification callback for 0x2AE CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_2AE_NotReceived(void)
{
  boolean boReceived = FALSE;

  (void)Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived(boReceived);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_34E_Received
///
/// \descr  LGM notification callback for 0x34E CAN frame reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_34E_Received(void)
{
  tHS6_DAT_VSM_34E stData;

  stData.ucFrontFogBeamCmd[0]         = *CTRL_FL_L_F;
  stData.ucFrontFogBeamCmd[1]         = *CTRL_FL_R_F;
  stData.ucAfsModeCmd                 = *CTRL_AFS;
  stData.ucGfhbCmd                    = *GFHB_CMD;
  stData.ucLowBeamBoostAllowed        = *LOW_BEAM_BOOST_ALLOWED;
  stData.ucPedestrianAllowed          = *PEDESTRIAN_ALLOWED;
  stData.ucAimingModeActivation       = *AIMING_MODE_ACTIVATION;
  stData.ucMotorwayDetection          = *MOTORWAY_DETECTION;
  stData.ucDayTimeRunningLightCmd[0]  = *CTRL_DRL_L;
  stData.ucDayTimeRunningLightCmd[1]  = *CTRL_DRL_R;
  stData.ucLowBeamCmd[0]              = *CTRL_LB_L;
  stData.ucLowBeamCmd[1]              = *CTRL_LB_R;
  stData.ucHighBeamCmd[0]             = *CTRL_HB_L;
  stData.ucHighBeamCmd[1]             = *CTRL_HB_R;
  stData.ucSideMarkerCmd[0]           = *CTRL_S_M_L_F;
  stData.ucSideMarkerCmd[1]           = *CTRL_S_M_R_F;
  stData.ucFrontPositionCmd[0]        = *CTRL_PL_L_F;
  stData.ucFrontPositionCmd[1]        = *CTRL_PL_R_F;
  stData.ucHeadlampFlashBeamCmd       = *CTRL_HB_FLASH;
  stData.ucEtatFeuxStationnement      = *ETAT_FEUX_STATIONNEMENT;
  stData.ucConfigVhl                  = *CONFIG_VHL;

  (void)Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received(&stData);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_34E_NotReceived
///
/// \descr  LGM notification callback for 0x34E CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_34E_NotReceived(void)
{
  boolean boReceived = FALSE;

  (void)Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived(boReceived);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_COMMANDES_VSM_036_Received
///
/// \descr  LGM notification callback for 0x36 CAN frame reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_COMMANDES_VSM_036_Received(void)
{
  tHS6_COMMANDES_VSM_036 stData;

  stData.ucPhaseVie       = *PHASE_VIE;
  stData.ucInterdMemoDef  = *INTERD_MEMO_DEF;
  stData.ucDemEffacDef    = *DEM_EFFAC_DEF;
  stData.ucDiagMux        = *DIAG_MUX_ON_BODY;

  (void)Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received(&stData);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_COMMANDES_VSM_036_NotReceived
///
/// \descr  LGM notification callback for 0x36 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_COMMANDES_VSM_036_NotReceived(void)
{
  boolean boReceived = FALSE;

  (void)Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived(boReceived);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_BSI_432_Received
///
/// \descr  LGM notification callback for 0x432 CAN frame reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_BSI_432_Received(void)
{
  tHS6_DAT_BSI_432 stData;

  stData.ucVESMainState          = *ETAT_PRINCIP_SEV;
  stData.ucElectricNetworkState  = *ETAT_RESEAU_ELEC;

  (void)Rte_Write_SigPrep_HS6_DAT_BSI_432_Received(&stData);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_BSI_432_NotReceived
///
/// \descr  LGM notification callback for 0x432 CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_BSI_432_NotReceived(void)
{
  boolean boReceived = FALSE;

  (void)Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived(boReceived);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_ABR_38D_Received
///
/// \descr  LGM notification callback for 0x38D CAN frame reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_ABR_38D_Received(void)
{
  tHS6_DYN_ABR_38D stData;

  stData.unVehicleSpeed          = (uint16)((uint16)(*VITESSE_VEHICULE_ROUES) + (uint16)((uint16)(*(VITESSE_VEHICULE_ROUES + 1U)) << 8U));
  stData.ucVehicleSpeedDispo     = *VVH_INDISP;
  stData.ucChksumTrmeDynUcFrein  = *CHKSUM_TRME_DYN_UC_FREIN;
  stData.ucCptProcess4B38D       = *CPT_PROCESS_4B_38D;

  for (uint8 ucI = 0U; ucI < 8U; ucI++)
  {
    stData.aucCHKSUM[ucI] = *(OVERALL_DAT_ABR_38D_CHKSUM + ucI);
  }

  (void)Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received(&stData);
}


//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_ABR_38D_NotReceived
///
/// \descr  LGM notification callback for 0x38D CAN frame failed reception
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_ABR_38D_NotReceived(void)
{
  boolean boReceived = FALSE;

  (void)Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived(boReceived);
}


//-----------------------------------------------------------------------------
/// \brief  SigPrep_CodingDataValidation
///
/// \descr  Get and handle coding parameters for SigPrep module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
STATIC_AL boolean SigPrep_CodingDataValidation(void)
{
  tsRteCodingParameters sCodingParameters;
  // Get coding data via RTE
  (void)Rte_Read_CodM_SigPrep_Para(&sCodingParameters);
  // Get coding data and return it's validity
  CONST_AL boolean boCodingValidity = SigPrep_Data_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);
  // Return validity of coding
  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  SigPrep_Data_ParaFct0
///
/// \descr  This function gets coding params and validity of coding data 
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean SigPrep_Data_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;

  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
    boCodingValidity = TRUE;
    SigPrep_Data_pCodingArea = pData;
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
/// \brief  SigPrep_SetCodingData
///
/// \descr  Load the coding data in case the coding is valid
///
/// \param  boIsCodingDataValid
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_SetCodingData(boolean boIsCodingDataValid)
{
  // If coding data is valid
  if (boIsCodingDataValid != FALSE)
  {
    // Get CONFIG_TIME parameter from coding
    SigPrep_Data_unCONFIG_TIME                     = SigPrep_Data_pCodingArea->Led1.BasicFunctions.unCONFIG_TIME;

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
    // Check if DBL option is present in Coding
    SigPrep_Coding_Options.boDbl_Enable            = (SigPrep_Data_pCodingArea->Sys.Configurability.ucDbl_Enable != 0u) ? TRUE : FALSE;
    // Check if GFHB option is present in Coding
    SigPrep_Coding_Options.boGFHB_Enable           =  (SigPrep_Data_pCodingArea->Sys.Configurability.ucGFHB_Enable != 0u) ? TRUE : FALSE;
    // Check if Curtain Effect option is present in Coding
    SigPrep_Coding_Options.boCurtainEffect_Enable  = (SigPrep_Data_pCodingArea->Sys.Configurability.ucCurtainEffect_Enable != 0u) ? TRUE : FALSE;
    // Check if TSAG option is present in Coding
    SigPrep_Coding_Options.boTSAG_Enable           = (SigPrep_Data_pCodingArea->Sys.Configurability.ucTSAG_Enable != 0u) ? TRUE : FALSE;
    // Check if Motoray option is present in Coding
    SigPrep_Coding_Options.boMotorway_Enable       = (SigPrep_Data_pCodingArea->Sys.Configurability.ucMotorway_Enable != 0u) ? TRUE : FALSE;
    // Check if Curvature option is present in Coding
    SigPrep_Coding_Options.boCurvatureMode         = (SigPrep_Data_pCodingArea->Dbl.DisableFuncs.ucCurvatureMode != 0u) ? TRUE : FALSE;
    // Check if ADL option is present in Coding for FULL version
    SigPrep_Coding_Options.boAvacStp_Enable        = (SigPrep_Data_pCodingArea->AvacStp.Modus.ucAvacStp_Enable != 0u) ? TRUE : FALSE;
#endif // (CFG_VARIANT_FULL) || defined(UNIT_TEST)
#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)
    // Check if ASL option is present in Coding for ECO version
    SigPrep_Coding_Options.boAsl_Enable            = (SigPrep_Data_pCodingArea->AvacStp.DCMotorData.ucAsl_Enable != 0u) ? TRUE : FALSE;
#endif // (CFG_VARIANT_ECO) || (UNIT_TEST)
  }
  else
  {
    // nothing to do, functionalities are inhibited because the coding is corrupted
    // coding data is corrupted, set a default value of 2 seconds
    SigPrep_Data_unCONFIG_TIME = SIGPREP_CONFIG_TIME_DEFAULT;
  }
}



// EOF
