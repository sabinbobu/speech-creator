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
/// \file  CddNcv78702_Cfg.h
///
/// \brief  Configuration of CddNcv78702 module
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_NCV78702_CFG_2021_03_25_H_
#define CDD_NCV78702_CFG_2021_03_25_H_

#include <Cfg/Cfg.h>
//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
// number of NCV78702 devices
#define CDDNCV78702_Cfg_NbOfDevices               1u

#if defined (CFG_VARIANT_ECO)
  //80V transistor
  #define CDDNCV78702_Cfg_VboostMin             36000u  // LDM.SYRS.32454
  #define CDDNCV78702_Cfg_VboostMax             63000u  // LDM.SYRS.32454
  #define CDDNCV78702_Cfg_BOOST_VSETPOINT_Min      66u  // LDM.SYRS.32456
  #define CDDNCV78702_Cfg_BOOST_VSETPOINT_Max     113u  // LDM.SYRS.32456
  //60V transistor
  #define CDDNCV78702_Cfg_60V_VboostMin             36000u  // LDM.SYRS.32454
  #define CDDNCV78702_Cfg_60V_VboostMax             49000u  // LDM.SYRS.32454
  #define CDDNCV78702_Cfg_60V_BOOST_VSETPOINT_Min      83u  // LDM.SYRS.32456
  #define CDDNCV78702_Cfg_60V_BOOST_VSETPOINT_Max     112u  // LDM.SYRS.32456
#else // CFG_VARIANT_FULL
  #define CDDNCV78702_Cfg_VboostMin             36000u  // LDM.SYRS.2605
  #define CDDNCV78702_Cfg_VboostMax             49000u  // LDM.SYRS.2605
  #define CDDNCV78702_Cfg_BOOST_VSETPOINT_Min      83u  // LDM.SYRS.2607
  #define CDDNCV78702_Cfg_BOOST_VSETPOINT_Max     112u  // LDM.SYRS.2607
#endif


//-----------------------------------------------------------------------------
// EFT default values
//-----------------------------------------------------------------------------
// values needed for projects without calibration data
#define CDDNCV78702_Eft_Calib_Default \
{ { 0xFFFFu, -1, 0xFFFFFFFFu } }

#if defined (CFG_VARIANT_ECO)
  #define CDDNCV78702_Eft_EcuVarCfg_Default \
  { { 1u, 2u, 546u, 0, 255u, 255u } }
#else
  #define CDDNCV78702_Eft_EcuVarCfg_Default \
  { { 2u, 1u, 432u, 0, 255u, 255u } }
#endif


//-----------------------------------------------------------------------------
// Register settings
//-----------------------------------------------------------------------------
#if defined (CFG_VARIANT_ECO)
  #define CDDNCV78702_Cfg_BOOST_OTA_GAIN             2u  // LDM.SYRS.32447
  #define CDDNCV78702_Cfg_VDRIVE_VSETPOINT           7u  // LDM.SYRS.32447
  #define CDDNCV78702_Cfg_VBOOST_VGATE_THR           0u  // LDM.SYRS.32447
  #define CDDNCV78702_Cfg_BOOST_VLIMTH1              3u  // LDM.SYRS.32448
  #define CDDNCV78702_Cfg_BOOST_VLIMTH2              0u  // LDM.SYRS.32448
  #define CDDNCV78702_Cfg_BOOST_SLPCTLR              7u  // LDM.SYRS.32448
  #define CDDNCV78702_Cfg_60V_BOOST_OVERVOLTSD_THR   92u  // LDM.SYRS.32449
  #define CDDNCV78702_Cfg_BOOST_OVERVOLTSD_THR       115u  // LDM.SYRS.32449
  #define CDDNCV78702_Cfg_P_DISTRIBUTION1            1u  // LDM.SYRS.32451
  #define CDDNCV78702_Cfg_P_DISTRIBUTION2            0u  // LDM.SYRS.32451
#else // CFG_VARIANT_FULL
  #define CDDNCV78702_Cfg_BOOST_OTA_GAIN          1u  // LDM.SYRS.2581
  #define CDDNCV78702_Cfg_VDRIVE_VSETPOINT        7u  // LDM.SYRS.2581
  #define CDDNCV78702_Cfg_VBOOST_VGATE_THR        1u  // LDM.SYRS.2581
  #define CDDNCV78702_Cfg_BOOST_VLIMTH1           1u  // LDM.SYRS.2582
  #define CDDNCV78702_Cfg_BOOST_VLIMTH2           1u  // LDM.SYRS.2582
  #define CDDNCV78702_Cfg_BOOST_SLPCTLR           6u  // LDM.SYRS.2582
  #define CDDNCV78702_Cfg_BOOST_OVERVOLTSD_THR  113u  // LDM.SYRS.2584
  #define CDDNCV78702_Cfg_P_DISTRIBUTION1         8u  // LDM.SYRS.2591
  #define CDDNCV78702_Cfg_P_DISTRIBUTION2         8u  // LDM.SYRS.2591
#endif

// LDM common
#define CDDNCV78702_Cfg_BOOST_SKCL              0u  // LDM.SYRS.2581/32447
#define CDDNCV78702_Cfg_BOOST_SRCINV            0u  // LDM.SYRS.2584
#define CDDNCV78702_Cfg_BOOST_MULTI_PHASE_MD    1u  // LDM.SYRS.2584
#define CDDNCV78702_Cfg_FSO_BST_FREQ            2u  // LDM.SYRS.2586
#define CDDNCV78702_Cfg_TSD_AUT_RCVR_EN         1u  // LDM.SYRS.2588
#define CDDNCV78702_Cfg_ADC_TEMP_THR            4u  // LDM.SYRS.2588
#define CDDNCV78702_Cfg_FSO_MD                  0u  // LDM.SYRS.2588
#define CDDNCV78702_Cfg_VDD_ENA                 1u  // LDM.SYRS.2590
#define CDDNCV78702_Cfg_FSO_ENABLE_SEL          1u  // LDM.SYRS.2590
#define CDDNCV78702_Cfg_BOOST_OV_REACT          1u  // LDM.SYRS.2590
#define CDDNCV78702_Cfg_VBOOST_TON_SET          0u  // LDM.SYRS.2590
#define CDDNCV78702_Cfg_VBOOST_TOFF_SET         0u  // LDM.SYRS.2590
#define CDDNCV78702_Cfg_VDRIVE_UV_THR           1u  // LDM.SYRS.2592


#endif // CDD_NCV78702_CFG_2021_03_25_H_
