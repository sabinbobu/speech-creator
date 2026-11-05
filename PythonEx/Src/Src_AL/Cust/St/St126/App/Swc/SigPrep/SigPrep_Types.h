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
/// \file   SigPrep_Types.h
///
/// \brief  Data Types Definition
///
/// \descr  Types definitions for SigPrep module is defined here
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SIG_PREP_TYPES_H__
#define __SIG_PREP_TYPES_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Util_Time.h> 
#include <RteCommonTypes.h>
#include <AL_Helper.h>
#include <Cfg/Cfg.h>
#include <UtilUtility.h>
#include <Std_Types.h>
#include <p_IL.h>
#include <p_IL_messages.h>
#include <p_IpduCallback.h>

#ifndef UNIT_TEST
#include <Rte.h>
#endif // UNIT_TEST

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

// Timing for validation frames
#define SIGPREPTX_CYCLETIME_100_MS        10u
#define SIGPREPTX_CYCLETIME_200_MS        20u

#define SIGPREPTX_MATRIX_MAX_NO_PXL       90u

#define SIGPREPTX_THERMOZONES_NR          12u
#define SIGPREPTX_LED_CHANNELS_NR         12u
#define SIGPREPTX_TEMP_RESOLUTION         10

#define SIGPREPTX_HEADLAMP_NR             2u

#define SIGPREPRX_ZERO_VALUE              0u

#define SIGPREP_CONFIG_TIME_DEFAULT        (uint16)2000    // default value for CONFIG_TIME
//-----------------------------------------------------------------------------
// Handles of receive objects
//-----------------------------------------------------------------------------
#define CANRX_HS6_ACQ_NEW_JDD_55F          (uint8)0
#define CANRX_HS6_DAT_VSM_36E              (uint8)1
#define CANRX_HS6_DAT_VSM_3AE              (uint8)2
#define CANRX_HS6_DAT_VSM_54D              (uint8)3
#define CANRX_HS6_DAT4_V2_BSI_552          (uint8)4
#define CANRX_HS6_DYN3_CMM_468             (uint8)5
#define CANRX_HS6_INTE_ELECTRON_BSI_092    (uint8)6
#define CANRX_HS6_DYN_VSM_257              (uint8)7
#define CANRX_HS6_DYN_BEMP_2B7_RX          (uint8)8
#define CANRX_HS6_DYN2_FRE_3CD             (uint8)9
#if defined (CFG_VARIANT_ECO) || (UNIT_TEST)
#define CANRX_HS6_DIAG_DRVLED_R_477_RX     (uint8)10
#endif
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
#define CANRX_HS6_DAT2_DRVLED_R_4D7_RX     (uint8)10
#define CANRX_HS6_DAT_CSS_350              (uint8)11
#define CANRX_HS6_DAT_DRVLED_R_297_RX      (uint8)12
#define CANRX_HS6_DYN_VSM_28E              (uint8)13
#define CANRX_HS6_DAT_VSM_32E              (uint8)14
#define CANRX_HS6_DAT7_BSI_612             (uint8)15
#define CANRX_HS6_DYN_VSM_0AB              (uint8)16
#define CANRX_HS6_DYN_VSM_0C3              (uint8)17
#define CANRX_HS6_DYN_VSM_0CB              (uint8)18
#define CANRX_HS6_DYN_VSM_0E3              (uint8)19
#define CANRX_HS6_DYN_VSM_0EB              (uint8)20
#define CANRX_HS6_DYN_VSM_103              (uint8)21
#define CANRX_HS6_DYN_VSM_10B              (uint8)22
#define CANRX_HS6_DYN_VSM_123              (uint8)23
#define CANRX_HS6_DYN_VSM_12B              (uint8)24
#define CANRX_HS6_DYN_VSM_143              (uint8)25
#define CANRX_HS6_DYN_VSM_14B              (uint8)26
#define CANRX_HS6_DYN_VSM_163              (uint8)27
#define CANRX_HS6_DYN_VSM_16B              (uint8)28
#define CANRX_HS6_DYN_VSM_183              (uint8)29
#define CANRX_HS6_DYN_VSM_18B              (uint8)30
#define CANRX_HS6_DYN_VSM_1AB              (uint8)31
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)


//-----------------------------------------------------------------------------
// Handles of send objects
//-----------------------------------------------------------------------------
#define CANTX_HS6_SUPV_DRVLED_L_5D7        (uint8)0
#define CANTX_HS6_SUPV_DRVLED_R_5F7        (uint8)1
#define CANTX_HS6_DYN_BEMP_2B7             (uint8)2
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
#define CANTX_HS6_DAT2_DRVLED_R_4D7        (uint8)3
#define CANTX_HS6_DAT_DRVLED_R_297         (uint8)4
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

//-----------------------------------------------------------------------------
// typedef
//-----------------------------------------------------------------------------
// Bsi Acknowledge status received on 0x55f frame Id
typedef struct
{
  boolean boBsiAckStatus;       // Bsi acknowledge status (0x97 Acknowledge Ok)
}tsSigPrep_BsiJddAck;

// Tx Frame Side State
typedef enum
{
  eLeftTxFrame = 0,
  eRightTxFrame
}teSigPrep_TxSideFrameState;

// SigPrepRx Event Callback State
typedef enum
{
  eFrameInit = 0,
  eFrmTimeOut,
  eFrmEvent,
  eFrmCrcErr,
  eFrmAliveErr
}teSigPrep_RxFrameState;

// SigPrep Rx frame handle data struct
typedef struct
{
  boolean(*CONST_AL pfPreCheckCb)(void);
  boolean           boMsgUpdated;
  boolean           boMsgTimedOut;
  void(*CONST_AL pfFrmCallback)(teSigPrep_RxFrameState eSigPrepRxState);
}tsSigPrep_RxFrameInfoConst;


// SigPrep Tx frame handle data struct
typedef struct
{
  CONST_AL teSigPrep_TxSideFrameState eFrameSide;
  boolean                             boMsgConfirmed;
  boolean                             boTriggerFrm;
  CONST_AL uint32                     ulTimeOut;
  TIMER                               ulTimer;
  void(*CONST_AL pfCycleCb)  (void);
  void(*CONST_AL pfTriggerCb)(void);
  void(*CONST_AL pfNotAckCb) (void);
}tsSigPrep_TxFrameInfoConst;

// SigPrepRx strcture to handle invalid data and DTC setting for CVM frames
typedef struct tsSigPrep_ClusterSigGroup1_InvalidData
{
  Dem_EventListId_EnumType  eDemEventId;
}tsSigPrep_ClusterSigGroup1_InvalidData;

// Structure used for validation frames PWM and Pixel Errors Buffer Index
typedef struct tsSigPrep_TxValidationFrames_PxlPwmErrIndex
{
  uint16  unDiagPxlErrIndex[SIGPREPTX_MATRIX_MAX_NO_PXL];
  uint16  unActualPxlPwmIndex[SIGPREPTX_MATRIX_MAX_NO_PXL];
}tsSigPrep_TxValidationFrames_PxlPwmErrIndex;

// Structure used for validation frames Luminosity LED Channel Index
typedef struct tsSigPrep_TxValidationFrames_LumLedChnlIndex
{
  uint16  unLumLedChnlIndex[SIGPREPTX_LED_CHANNELS_NR];
}tsSigPrep_TxValidationFrames_LumLedChnlIndex;

// Structure used for validation frames Temperature Thermozone Index
typedef struct tsSigPrep_TxValidationFrames_TempIndex
{
  uint16  unTempIndex[SIGPREPTX_THERMOZONES_NR];
}tsSigPrep_TxValidationFrames_TempIndex;

// Structure used for validation frames Thermozone Power Factor Index
typedef struct tsSigPrep_TxValidationFrames_PowerFactorIndex
{
  uint16  unPowerFactorIndex[SIGPREPTX_THERMOZONES_NR];
}tsSigPrep_TxValidationFrames_PowerFactorIndex;

// Structure used for validation frames Body Hight Index
typedef struct tsSigPrep_TxValidationFrames_BhsIndex
{
  uint16  unBhsIndex[CFG_CntSens];
}tsSigPrep_TxValidationFrames_BhsIndex;

// Structure used for validation frames DBL Swiveling Angle Index
typedef struct tsSigPrep_TxValidationFrames_DblSwivAnglIndex
{
  uint16  unDblSwivAnglIndex[SIGPREPTX_HEADLAMP_NR];
}tsSigPrep_TxValidationFrames_DblSwivAnglIndex;

// Structure used for Coding Data
typedef struct 
{
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
  boolean  boDbl_Enable;
  boolean  boGFHB_Enable;
  boolean  boCurtainEffect_Enable;
  boolean  boTSAG_Enable;
  boolean  boMotorway_Enable;
  boolean  boCurvatureMode;
  boolean  boAvacStp_Enable;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
#if defined (CFG_VARIANT_ECO) || (UNIT_TEST)
  // Check if ASL option is present in Coding for ECO version
  boolean  boAsl_Enable;
#endif // (CFG_VARIANT_ECO) || (UNIT_TEST)
}tsSigPrep_Coding_Options;
#endif // __SIG_PREP_RX_TYPES_H__

// EOF
