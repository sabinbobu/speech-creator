//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work. 
// This work shall not be copied, reproduced, used, modified, transferred 
// or its information shall not be disclosed without the prior written 
// authorization of Marelli Automotive Lighting Reutlingen GmbH. 
//*****************************************************************************

//-----------------------------------------------------------------------------
/// \file Rte_Cfg.c
/// 
/// \brief Configuration of the RTE. 
///
/// \descr 
///
/// \author ALRteGenerator version 0.28 from Dec 09 2021
/// 
//-----------------------------------------------------------------------------

// *****************************************************************************
// includes
// *****************************************************************************
#include "stdint.h"
#include "Os_Types.h"
#include "Rte.h"
#include "RteCommonTypes.h"
#include "Rte_Cfg.h"
#include "Rte_Sct.h"
#include "UtilUtility.h"

#define RTE_CFG_C_ID 1252364596

#if RTE_CFG_C_ID != RTE_CFG_H_ID
#error "Generation-ID mismatch between Rte_Cfg.c and Rte_Cfg.h"
#endif
#if RTE_CFG_C_ID != RTE_SCT_H_ID
#error "Generation-ID mismatch between Rte_Cfg.c and Rte_Sct.h"
#endif

// *****************************************************************************
// constants
// *****************************************************************************
const RteRunnableInit_t RTE_RunnableInit[] = 
{
  { riCodM_Init, eRteSafety_Untrusted }, 
  { riSysMon_Init, eRteSafety_Trusted }, 
  { riSchM_Func_NonTrusted_Init, eRteSafety_Untrusted }, 
  { riSchM_Func_Trusted_Init, eRteSafety_Trusted }, 
  { riCpmInit, eRteSafety_Untrusted }, 
  { riSysVoltInit, eRteSafety_Untrusted }, 
  { riStatM_Init, eRteSafety_Untrusted }, 
  { riRSens_Init, eRteSafety_Untrusted }, 
  { riDiagControl_Init, eRteSafety_Untrusted }, 
  { riFctRInit, eRteSafety_Untrusted }, 
  { riCtrlLed_Init, eRteSafety_Untrusted }, 
  { riCtrlSwiInit, eRteSafety_Untrusted }, 
  { riCddLedInit, eRteSafety_Trusted }, 
  { riCddBoostInit, eRteSafety_Trusted }, 
  { riCddSpiInit, eRteSafety_Trusted }, 
  { riCddSbc_Init, eRteSafety_Trusted }, 
  { riCddEftInit, eRteSafety_Untrusted }, 
  { riCddSwi_Init, eRteSafety_Untrusted }, 
  { riAvacStat1_Init, eRteSafety_Untrusted }, 
  { riCddDcm_Init, eRteSafety_Untrusted }, 
  { riPitch_Init, eRteSafety_Untrusted }, 
  { riCtrlDcm_Init, eRteSafety_Untrusted }
};

const uint8_t RTE_RunnableInitCount = UTIL_COUNTOF(RTE_RunnableInit);

const RteThreadCyclic_t RTE_ThreadCyclic[RTECYC_RunnableCount] =
{
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCodM_Cycle0 }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rcSysMon_Cycle1ms }, 
  { eRteThread_U_HL, eRteThreadFlag_U_HL_rpSchM_Func_NonTrusted_Cycle }, 
  { eRteThread_U_LL, eRteThreadFlag_U_LL_rcMemoryProc }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpSchM_Func_Trusted_Cycle }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCpm20ms }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpSysVolt_Cycle }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rcStatM_Cycle10ms }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpRSens_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpDiagControl_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpFctR_Cycle }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCtrlLed_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCtrlSwiCycle0 }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddLed_Cycle }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddBoost_Cycle }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddSpi_Cycle }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddSbc_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCddSwi_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpAvacStat1_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCddDcm_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpPitch_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCtrlDcm_Cycle }
};

const CYCLIC_TABLE_TYPE  RTE_CyclicTable[] =
{
  /*   0 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rcStatM_Cycle10ms) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*   1 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*   2 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpAvacStat1_Cycle0) | CYCLIC(RTECYC_rpCddDcm_Cycle0) | CYCLIC(RTECYC_rpPitch_Cycle0), 
  /*   3 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*   4 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCtrlDcm_Cycle), 
  /*   5 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*   6 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*   7 */  CYCLIC(RTECYC_rpCodM_Cycle0) | CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*   8 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*   9 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  10 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  11 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  12 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  13 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  14 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  15 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  16 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  17 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  18 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  19 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  20 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  21 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  22 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpAvacStat1_Cycle0) | CYCLIC(RTECYC_rpCddDcm_Cycle0) | CYCLIC(RTECYC_rpPitch_Cycle0), 
  /*  23 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  24 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCtrlDcm_Cycle), 
  /*  25 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  26 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  27 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  28 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  29 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  30 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  31 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  32 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  33 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  34 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  35 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  36 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  37 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  38 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  39 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  40 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  41 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  42 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpAvacStat1_Cycle0) | CYCLIC(RTECYC_rpCddDcm_Cycle0) | CYCLIC(RTECYC_rpPitch_Cycle0), 
  /*  43 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  44 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCtrlDcm_Cycle), 
  /*  45 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  46 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  47 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  48 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  49 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  50 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  51 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  52 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  53 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  54 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  55 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  56 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  57 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  58 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  59 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  60 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  61 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  62 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpAvacStat1_Cycle0) | CYCLIC(RTECYC_rpCddDcm_Cycle0) | CYCLIC(RTECYC_rpPitch_Cycle0), 
  /*  63 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  64 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCtrlDcm_Cycle), 
  /*  65 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  66 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  67 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  68 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  69 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  70 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  71 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  72 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  73 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  74 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  75 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  76 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  77 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  78 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  79 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  80 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  81 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  82 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpAvacStat1_Cycle0) | CYCLIC(RTECYC_rpCddDcm_Cycle0) | CYCLIC(RTECYC_rpPitch_Cycle0), 
  /*  83 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  84 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCtrlDcm_Cycle), 
  /*  85 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  86 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  87 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  88 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  89 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  90 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  91 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  92 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  93 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  94 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  95 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  96 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  97 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddDcm_Cycle0), 
  /*  98 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  99 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle)
};

const uint8_t RTE_CyclicTableCount = countof(RTE_CyclicTable);

const pRunnable_t RTE_Runnable_T_HH_func[eRteThreadFlag_T_HH_Count] =
{
  reSysMonRx_HS6_DAT_VSM_2AE_Received, 
  reSysMonRx_HS6_DAT_VSM_2AE_NotReceived, 
  reSysMonRx_HS6_DAT_VSM_34E_Received, 
  reSysMonRx_HS6_DAT_VSM_34E_NotReceived, 
  reSysMonRx_HS6_COMMANDES_VSM_036_Received, 
  reSysMonRx_HS6_COMMANDES_VSM_036_NotReceived, 
  reSysMonRx_HS6_DAT_BSI_432_Received, 
  reSysMonRx_HS6_DAT_BSI_432_NotReceived, 
  reSysMonRx_HS6_DYN_ABR_38D_Received, 
  reSysMonRx_HS6_DYN_ABR_38D_NotReceived, 
  reSysMonRx_EnableCallbacks, 
  reSysMonTx_HS6_DIAG_DRVLED_Sent, 
  reSysMonTx_HS6_DIAG_DRVLED_NotSent, 
  reSysMonTx_ActivateTxBufer, 
  reEcuM_RequestRUN, 
  reEcuM_ReleaseRUN, 
  reEcuM_ReleasePOST_RUN, 
  reEcuM_RequestPOST_RUN, 
  reEcuM_DiagResetRequest
};

const pRunnable_t RTE_Runnable_T_HL_func[eRteThreadFlag_T_HL_Count] =
{
  rcSysMon_Cycle1ms, 
  rpSchM_Func_Trusted_Cycle, 
  rpCddLed_Cycle, 
  rpCddBoost_Cycle, 
  rpCddSpi_Cycle, 
  rpCddSbc_Cycle0
};

const pRunnable_t RTE_Runnable_U_HH_func[eRteThreadFlag_U_HH_Count] =
{
  reSigPrepRx_LifePhases, 
  reSigPrepRx_SetDiagMux, 
  reSigPrepTx_SendFrame457, 
  reSigPrepTx_SendFrame477, 
  reStatM_Deinit, 
  reStatM_ResetStatistics
};

const pRunnable_t RTE_Runnable_U_HL_func[eRteThreadFlag_U_HL_Count] =
{
  rpSchM_Func_NonTrusted_Cycle
};

const pRunnable_t RTE_Runnable_U_LH_func[eRteThreadFlag_U_LH_Count] =
{
  rpCodM_Cycle0, 
  rpCpm20ms, 
  rpSysVolt_Cycle, 
  rcStatM_Cycle10ms, 
  rpRSens_Cycle0, 
  rpDiagControl_Cycle0, 
  rpFctR_Cycle, 
  rpCtrlLed_Cycle0, 
  rpCtrlSwiCycle0, 
  rpCddSwi_Cycle0, 
  rpAvacStat1_Cycle0, 
  rpCddDcm_Cycle0, 
  rpPitch_Cycle0, 
  rpCtrlDcm_Cycle
};

const pRunnable_t RTE_Runnable_U_LL_func[eRteThreadFlag_U_LL_Count] =
{
  rcMemoryProc
};


// *****************************************************************************
// vars
// *****************************************************************************
__attribute__((section(".bss.RtePortSR_T")))
static struct
{
  uint8              SysMon_E2Eexec;
  tsRte_SysMonLgtFctsReq SysMon_StdLgtFcts_Req;
  teRte_ReqLightState SysMon_LowBeamCmd_Req;
  teRte_ReqLightState SysMon_TurnIndicatorCmd_Req;
  tsRte_SysMonLgtTiReq SysMon_StdLgtTi_Req;
  tsRte_SysMon_VehicleSpeed SysMon_VehicleSpeed;
  tsRte_SysMon_VehNetState SysMon_VehNetState;
  tsRte_SysMon_LifePhases SysMon_LifePhases;
  TE_Bool            SysMon_SetDiagMux;
  tSysMon_SendFrame457 SysMon_SendFrame457;
  tSysMon_SendFrame477 SysMon_SendFrame477;
  tsRte_TgtLedSig0_ASIL SysMon_TgtLedSig_sVal;
  tsRte_SysMon_LedStates SysMon_LedState;
  teRte_MountingSide IoHwAbUser_GetMountingSide;
  tiu32Voltage_mV    IoHwAb_User_GetAdc_DIAG_VBAT;
  tsRte_SensorBalance IoHwAb_GetSens_Balanced;
  tsRte_SensorRaw    IoHwAb_GetSens_Raw;
  tiu16Voltage_mV    IoHwAb_GetPCB;
  tsRte_Voltage_mV   IoHwAb_GetVoltage_NTCs;
  tiu16Voltage_mV    IoHwAb_VCCX1Voltage;
  uint32             MPU_ErrorCounter;
  boolean            EcuM_Deinit;
  tsRte_LedStates    CddLed_LedState;
  tCddLedStatus      CddLed_Status;
  tsRte_TgtLedSig0_FaultStatus_ASIL CddLed_TgtLed_FaultStatus_ASIL;
  tsRte_BoostState   CddBoost_BoostState;
  tCddBoostStatus    CddBoost_BoostStatus;
}RtePortSR_T;

__attribute__((section(".bss.RtePortSR_U")))
static struct
{
  tsRteCodingParameters CodM_FctR_Para;
  tsRteCodingParameters CodM_AppM_Para;
  tsRteCodingParameters CodM_CtrlLed_Para;
  tsRteCodingParameters CodM_Rsens_Para;
  tsRteCodingParameters CodM_CtrlFan_Para;
  tsRteCodingParameters CodM_SysVolt_Para;
  tsRteCodingParameters CodM_CddLed_Para;
  tsRteCodingParameters CodM_CddSwi_Para;
  tsRteCodingParameters CodM_CddBoost_Para;
  tsRteCodingParameters CodM_SigPrep_Para;
  tsRteCodingParameters CodM_SysMon_Para;
  tsRteCodingParameters CodM_Anima_Para;
  tsRteCodingParameters CodM_Pitch_Para;
  tsRteCodingParameters CodM_IoHwAbUser_Para;
  tsRteCodingParameters CodM_Err_Para;
  tsRte_Ld_ActivationRoutineControl Diag_LdActivationRoutineControl;
  boolean            Diag_DiagResetRequest;
  uint8              Diag_RequestPOST_RUN;
  tsRte_DcMotorRoutineControl Dcm_RoutineControl;
  tsRte_SigPrep_YawSpeed SigPrep_YawSpeed;
  tsRte_SigPrep_ElecSupState SigPrep_ElecSupState;
  tsRte_SigPrep_VehicleConfigSig SigPrep_VehicleConfigSig;
  tsRte_SigPrep_DynamicSigs SigPrep_DynamicSigs;
  tsRte_SigPrep_VehiclePitchAngle SigPrep_VehiclePitchAngle;
  tsRte_SigPrepNsoTrig SigPrep_NsoTrigger_Port;
  tsRte_AnimationReq SigPrep_AnimationReq;
  tsRte_VehTimeCntr  SigPrep_VehTimeCntr;
  tsRte_OdometerTotal SigPrep_OdometerTotal;
  tsRte_ElecIntegra  SigPrep_ElecIntegra;
  tsRte_DcmDiagStatusR SigPrep_DcmDiagStatusR;
  tsRte_LevellingTgtPos SigPrep_LevellingTgtPos;
  tHS6_DAT_VSM_2AE   SigPrep_HS6_DAT_VSM_2AE_Received;
  boolean            SigPrep_HS6_DAT_VSM_2AE_NotReceived;
  tHS6_DAT_VSM_34E   SigPrep_HS6_DAT_VSM_34E_Received;
  boolean            SigPrep_HS6_DAT_VSM_34E_NotReceived;
  tHS6_COMMANDES_VSM_036 SigPrep_HS6_COMMANDES_VSM_036_Received;
  boolean            SigPrep_HS6_COMMANDES_VSM_036_NotReceived;
  tHS6_DAT_BSI_432   SigPrep_HS6_DAT_BSI_432_Received;
  boolean            SigPrep_HS6_DAT_BSI_432_NotReceived;
  tHS6_DYN_ABR_38D   SigPrep_HS6_DYN_ABR_38D_Received;
  boolean            SigPrep_HS6_DYN_ABR_38D_NotReceived;
  uint8              SigPrep_SleepBSI;
  NM_ModeType        SigPrep_NMMode;
  boolean            SigPrep_HS6_DIAG_DRVLED_Sent;
  boolean            SigPrep_HS6_DIAG_DRVLED_NotSent;
  boolean            DEM_UV_NotifyStatus;
  boolean            DEM_OV_NotifyStatus;
  boolean            DEM_350Lost_NotifyStatus;
  uint8              ElecInt_RequestRUN;
  uint8              ElecInt_ReleaseRUN;
  uint8              ElecInt_ReleasePOST_RUN;
  boolean            ElecInt_EnableCallbacks;
  boolean            ElecInt_ActivateTxBufer;
  boolean            Diag_ResetStatistics;
  uint8              OS_CPULoadAvg;
  uint8              OS_CPULoadPeak;
  boolean            Diag_TiScrollingTakeOver;
  tsRte_TgtLedSig0Arr Cpm_TgtLedSig_sVal;
  tsRteHssTarget     CpmHssTarget0_sSetting;
  tsRte_PowerFactor  Cpm_SigPrepTx_PowerFactor;
  tsRtePowFactTemp   Cpm_PowFact_Temp;
  tsRte_CpmHSS3Duty  Cpm_CtrlSwi_HSS3Target;
  teRte_SysVolt_Results SysVolt_FanVoltRng0_sVoltRng;
  teRte_SysVolt_Results SysVolt_LedVoltRng0_sVoltRng;
  uint8              StatM_StackUsage;
  tsRte_PcbTemperatureMsg RSens_PcbTemperature;
  tsRte_NTCTemperature RSens_ThermzoneTemperatures;
  tsRte_Binning0     RSens_BinningClass_sVal_00;
  tsRte_Binning0     RSens_BinningClass_sVal_01;
  tsRte_Binning0     RSens_BinningClass_sVal_02;
  tsRte_Binning0     RSens_BinningClass_sVal_03;
  tsRteNTCBinInData  RSens_NTC_BIN_Input_Errors;
  tsRte_D409Binning  RSens_BinningDataDiag;
  tsRte_TgtLedVal0Arr FctR_TgtLed_sVal;
  tsRte_LgtFctState  FctR_LgtFctState;
  tsRte_LgtFctStatus FctR_LgtFctStatus;
  teRte_WarningMode  FctR_TiWarningMode;
  boolean            FctR_TiFailureStatus;
  uint32             FctR_LgtDistStatus;
  tsRte_TgtLedSig0Arr CtrlLed_TgtLedSig_sVal;
  tsRte_TgtLedSig0   CtrlLed_TgtHssSig_sVal;
  tsRte_ChLedSettings CtrlLed_LedSettings_sVal;
  tsRte_LedErrStateArr CtrlLed_ActLed_sState;
  tsRte_ucBinningSelect CtrlLed_BinningClass;
  tsRte_LedChFbit    CtrlLed_LedChFbit;
  tsRte_CtrlLed_ChStatesDiag CtrlLed_ChState;
  tRteSwitchTgtVal   CtrlSwi_TgtValue_Fan1;
  tRteSwitchTgtVal   CtrlSwi_TgtValue_Fan2;
  tRteSwitchTgtVal   CtrlSwi_TgtValue_SMRGB;
  tisHssStatusError  CtrlSwi_StatusErr;
  teRte_SateliteStatus CtrlSwi_TgtValue_ScrollingSatelite;
  tsRte_Hss3Status   CtrlSwi_Hss3StatusErr;
  tsRte_HssStatus    CddSwi_SwitchStatus;
  tPositionOut       ppsAvacStat1Out_Port;
  teRte_DcmSpeedMode AvacStat1_SpeedMode;
  tDcmPosMsg         DcmPos0_Port;
  tDcmStateMsg       DcmState0_Port;
  tsRte_DcmStatusError CddDcm_ErrorStatus;
  tSensRaw0          Pitch_SensRaw;
  tPitch0            Pitch_Angle;
  teRte_HlsSensorState Pitch_PlausState;
  tsRte_LevellingTgtPos CtrlDcm_MasterCommand;
  tsRte_CtrlDcmTarget ppCtrlDcmTarget0_DcmTargetValues;
  tsRte_CtrlDcmStatusParams CtrlDcm_StatusParameters_Port;
  tsRte_Hs6_Diag_Drvled_L_457 DrvLedDiag;
  tsRte_Hs6_Diag_Drvled_R_477 DrvLedDiagR;
}RtePortSR_U;

// *****************************************************************************
// Rte_PortSR Functions
// *****************************************************************************

// *** CodM_FctR_Para ***
Std_ReturnType Rte_Write_CodM_FctR_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_FctR_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_FctR_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_FctR_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_FctR_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_FctR_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_AppM_Para ***
Std_ReturnType Rte_Write_CodM_AppM_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CodM_AppM_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_AppM_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_AppM_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CodM_AppM_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_AppM_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_CtrlLed_Para ***
Std_ReturnType Rte_Write_CodM_CtrlLed_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_CtrlLed_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_CtrlLed_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_CtrlLed_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_CtrlLed_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_CtrlLed_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_Rsens_Para ***
Std_ReturnType Rte_Write_CodM_Rsens_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_Rsens_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_Rsens_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_Rsens_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_Rsens_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_Rsens_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_CtrlFan_Para ***
Std_ReturnType Rte_Write_CodM_CtrlFan_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_CtrlFan_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_CtrlFan_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_CtrlFan_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_CtrlFan_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_CtrlFan_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_SysVolt_Para ***
Std_ReturnType Rte_Write_CodM_SysVolt_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_SysVolt_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_SysVolt_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_SysVolt_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_SysVolt_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_SysVolt_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_CddLed_Para ***
Std_ReturnType Rte_Write_CodM_CddLed_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CodM_CddLed_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_CddLed_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_CddLed_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CodM_CddLed_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_CddLed_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_CddSwi_Para ***
Std_ReturnType Rte_Write_CodM_CddSwi_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_CddSwi_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_CddSwi_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_CddSwi_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_CddSwi_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_CddSwi_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_CddBoost_Para ***
Std_ReturnType Rte_Write_CodM_CddBoost_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CodM_CddBoost_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_CddBoost_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_CddBoost_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CodM_CddBoost_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_CddBoost_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_SigPrep_Para ***
Std_ReturnType Rte_Write_CodM_SigPrep_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CodM_SigPrep_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_SigPrep_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_SigPrep_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CodM_SigPrep_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_SigPrep_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_SysMon_Para ***
Std_ReturnType Rte_Write_CodM_SysMon_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CodM_SysMon_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_SysMon_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_SysMon_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CodM_SysMon_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_SysMon_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_Anima_Para ***
Std_ReturnType Rte_Write_CodM_Anima_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_Anima_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_Anima_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_Anima_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_Anima_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_Anima_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_Pitch_Para ***
Std_ReturnType Rte_Write_CodM_Pitch_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_Pitch_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_Pitch_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_Pitch_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_Pitch_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_Pitch_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_IoHwAbUser_Para ***
Std_ReturnType Rte_Write_CodM_IoHwAbUser_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CodM_IoHwAbUser_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_IoHwAbUser_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_IoHwAbUser_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CodM_IoHwAbUser_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_IoHwAbUser_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_Err_Para ***
Std_ReturnType Rte_Write_CodM_Err_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CodM_Err_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_Err_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_Err_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CodM_Err_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_Err_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_E2Eexec ***
Std_ReturnType Rte_Write_SysMon_E2Eexec(const uint8* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_E2Eexec, ppara1, sizeof(uint8));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_E2Eexec);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_E2Eexec(uint8* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_E2Eexec, sizeof(uint8));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_E2Eexec) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_StdLgtFcts_Req ***
Std_ReturnType Rte_Write_SysMon_StdLgtFcts_Req(const tsRte_SysMonLgtFctsReq* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_StdLgtFcts_Req, ppara1, sizeof(tsRte_SysMonLgtFctsReq));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_StdLgtFcts_Req);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_StdLgtFcts_Req, sizeof(tsRte_SysMonLgtFctsReq));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_StdLgtFcts_Req) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_LowBeamCmd_Req ***
Std_ReturnType Rte_Write_SysMon_LowBeamCmd_Req(const teRte_ReqLightState* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_LowBeamCmd_Req, ppara1, sizeof(teRte_ReqLightState));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_LowBeamCmd_Req);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_LowBeamCmd_Req, sizeof(teRte_ReqLightState));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_LowBeamCmd_Req) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_TurnIndicatorCmd_Req ***
Std_ReturnType Rte_Write_SysMon_TurnIndicatorCmd_Req(const teRte_ReqLightState* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.SysMon_TurnIndicatorCmd_Req, ppara1, sizeof(teRte_ReqLightState));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_TurnIndicatorCmd_Req);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_TurnIndicatorCmd_Req(teRte_ReqLightState* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.SysMon_TurnIndicatorCmd_Req, sizeof(teRte_ReqLightState));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_TurnIndicatorCmd_Req) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_StdLgtTi_Req ***
Std_ReturnType Rte_Write_SysMon_StdLgtTi_Req(const tsRte_SysMonLgtTiReq* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_StdLgtTi_Req, ppara1, sizeof(tsRte_SysMonLgtTiReq));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_StdLgtTi_Req);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_StdLgtTi_Req(tsRte_SysMonLgtTiReq* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_StdLgtTi_Req, sizeof(tsRte_SysMonLgtTiReq));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_StdLgtTi_Req) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_VehicleSpeed ***
Std_ReturnType Rte_Write_SysMon_VehicleSpeed(const tsRte_SysMon_VehicleSpeed* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_VehicleSpeed, ppara1, sizeof(tsRte_SysMon_VehicleSpeed));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_VehicleSpeed);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_VehicleSpeed, sizeof(tsRte_SysMon_VehicleSpeed));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_VehicleSpeed) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_VehNetState ***
Std_ReturnType Rte_Write_SysMon_VehNetState(const tsRte_SysMon_VehNetState* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_VehNetState, ppara1, sizeof(tsRte_SysMon_VehNetState));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_VehNetState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_VehNetState, sizeof(tsRte_SysMon_VehNetState));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_VehNetState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_LifePhases ***
Std_ReturnType Rte_Write_SysMon_LifePhases(const tsRte_SysMon_LifePhases* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_LifePhases, ppara1, sizeof(tsRte_SysMon_LifePhases));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_LifePhases);

  Rte_PortSR_Trigger(eRteThread_U_HH, eRteThreadFlag_U_HH_reSigPrepRx_LifePhases);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_LifePhases, sizeof(tsRte_SysMon_LifePhases));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_LifePhases) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_SetDiagMux ***
Std_ReturnType Rte_Write_SysMon_SetDiagMux(TE_Bool para1)
{
  RtePortSR_T.SysMon_SetDiagMux = para1;

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_SetDiagMux);

  Rte_PortSR_Trigger(eRteThread_U_HH, eRteThreadFlag_U_HH_reSigPrepRx_SetDiagMux);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_SetDiagMux(TE_Bool* ppara1)
{
  *ppara1 = RtePortSR_T.SysMon_SetDiagMux;

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_SetDiagMux) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

TE_Bool Rte_DRead_SysMon_SetDiagMux(void)
{
  return RtePortSR_T.SysMon_SetDiagMux;
}

// *** SysMon_SendFrame457 ***
Std_ReturnType Rte_Write_SysMon_SendFrame457(const tSysMon_SendFrame457* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.SysMon_SendFrame457, ppara1, sizeof(tSysMon_SendFrame457));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_SendFrame457);

  Rte_PortSR_Trigger(eRteThread_U_HH, eRteThreadFlag_U_HH_reSigPrepTx_SendFrame457);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_SendFrame457(tSysMon_SendFrame457* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.SysMon_SendFrame457, sizeof(tSysMon_SendFrame457));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_SendFrame457) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_SendFrame477 ***
Std_ReturnType Rte_Write_SysMon_SendFrame477(const tSysMon_SendFrame477* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.SysMon_SendFrame477, ppara1, sizeof(tSysMon_SendFrame477));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_SendFrame477);

  Rte_PortSR_Trigger(eRteThread_U_HH, eRteThreadFlag_U_HH_reSigPrepTx_SendFrame477);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_SendFrame477(tSysMon_SendFrame477* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.SysMon_SendFrame477, sizeof(tSysMon_SendFrame477));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_SendFrame477) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_TgtLedSig_sVal ***
Std_ReturnType Rte_Write_SysMon_TgtLedSig_sVal(const tsRte_TgtLedSig0_ASIL* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.SysMon_TgtLedSig_sVal, ppara1, sizeof(tsRte_TgtLedSig0_ASIL));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_TgtLedSig_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_TgtLedSig_sVal(tsRte_TgtLedSig0_ASIL* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.SysMon_TgtLedSig_sVal, sizeof(tsRte_TgtLedSig0_ASIL));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_TgtLedSig_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_LedState ***
Std_ReturnType Rte_Write_SysMon_LedState(const tsRte_SysMon_LedStates* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.SysMon_LedState, ppara1, sizeof(tsRte_SysMon_LedStates));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_LedState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_LedState(tsRte_SysMon_LedStates* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.SysMon_LedState, sizeof(tsRte_SysMon_LedStates));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_LedState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Diag_LdActivationRoutineControl ***
Std_ReturnType Rte_Write_Diag_LdActivationRoutineControl(const tsRte_Ld_ActivationRoutineControl* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Diag_LdActivationRoutineControl, ppara1, sizeof(tsRte_Ld_ActivationRoutineControl));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Diag_LdActivationRoutineControl);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Diag_LdActivationRoutineControl(tsRte_Ld_ActivationRoutineControl* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Diag_LdActivationRoutineControl, sizeof(tsRte_Ld_ActivationRoutineControl));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Diag_LdActivationRoutineControl) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Diag_DiagResetRequest ***
Std_ReturnType Rte_Write_Diag_DiagResetRequest(const boolean* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Diag_DiagResetRequest, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Diag_DiagResetRequest);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reEcuM_DiagResetRequest);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Diag_DiagResetRequest(boolean* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Diag_DiagResetRequest, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Diag_DiagResetRequest) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Diag_RequestPOST_RUN ***
Std_ReturnType Rte_Write_Diag_RequestPOST_RUN(const uint8* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Diag_RequestPOST_RUN, ppara1, sizeof(uint8));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Diag_RequestPOST_RUN);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reEcuM_RequestPOST_RUN);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Diag_RequestPOST_RUN(uint8* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Diag_RequestPOST_RUN, sizeof(uint8));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Diag_RequestPOST_RUN) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Dcm_RoutineControl ***
Std_ReturnType Rte_Write_Dcm_RoutineControl(const tsRte_DcMotorRoutineControl* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Dcm_RoutineControl, ppara1, sizeof(tsRte_DcMotorRoutineControl));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Dcm_RoutineControl);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Dcm_RoutineControl, sizeof(tsRte_DcMotorRoutineControl));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Dcm_RoutineControl) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_YawSpeed ***
Std_ReturnType Rte_Write_SigPrep_YawSpeed(const tsRte_SigPrep_YawSpeed* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_YawSpeed, ppara1, sizeof(tsRte_SigPrep_YawSpeed));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_YawSpeed);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_YawSpeed(tsRte_SigPrep_YawSpeed* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_YawSpeed, sizeof(tsRte_SigPrep_YawSpeed));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_YawSpeed) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ElecSupState ***
Std_ReturnType Rte_Write_SigPrep_ElecSupState(const tsRte_SigPrep_ElecSupState* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrep_ElecSupState, ppara1, sizeof(tsRte_SigPrep_ElecSupState));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ElecSupState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrep_ElecSupState, sizeof(tsRte_SigPrep_ElecSupState));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ElecSupState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_VehicleConfigSig ***
Std_ReturnType Rte_Write_SigPrep_VehicleConfigSig(const tsRte_SigPrep_VehicleConfigSig* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrep_VehicleConfigSig, ppara1, sizeof(tsRte_SigPrep_VehicleConfigSig));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_VehicleConfigSig);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrep_VehicleConfigSig, sizeof(tsRte_SigPrep_VehicleConfigSig));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_VehicleConfigSig) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_DynamicSigs ***
Std_ReturnType Rte_Write_SigPrep_DynamicSigs(const tsRte_SigPrep_DynamicSigs* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_DynamicSigs, ppara1, sizeof(tsRte_SigPrep_DynamicSigs));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_DynamicSigs);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_DynamicSigs, sizeof(tsRte_SigPrep_DynamicSigs));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_DynamicSigs) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_VehiclePitchAngle ***
Std_ReturnType Rte_Write_SigPrep_VehiclePitchAngle(const tsRte_SigPrep_VehiclePitchAngle* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_VehiclePitchAngle, ppara1, sizeof(tsRte_SigPrep_VehiclePitchAngle));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_VehiclePitchAngle);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_VehiclePitchAngle, sizeof(tsRte_SigPrep_VehiclePitchAngle));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_VehiclePitchAngle) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_NsoTrigger_Port ***
Std_ReturnType Rte_Write_SigPrep_NsoTrigger_Port(const tsRte_SigPrepNsoTrig* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_NsoTrigger_Port, ppara1, sizeof(tsRte_SigPrepNsoTrig));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_NsoTrigger_Port);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_NsoTrigger_Port(tsRte_SigPrepNsoTrig* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_NsoTrigger_Port, sizeof(tsRte_SigPrepNsoTrig));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_NsoTrigger_Port) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_AnimationReq ***
Std_ReturnType Rte_Write_SigPrep_AnimationReq(const tsRte_AnimationReq* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_AnimationReq, ppara1, sizeof(tsRte_AnimationReq));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_AnimationReq);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_AnimationReq(tsRte_AnimationReq* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_AnimationReq, sizeof(tsRte_AnimationReq));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_AnimationReq) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_VehTimeCntr ***
Std_ReturnType Rte_Write_SigPrep_VehTimeCntr(const tsRte_VehTimeCntr* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_VehTimeCntr, ppara1, sizeof(tsRte_VehTimeCntr));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_VehTimeCntr);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_VehTimeCntr(tsRte_VehTimeCntr* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_VehTimeCntr, sizeof(tsRte_VehTimeCntr));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_VehTimeCntr) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_OdometerTotal ***
Std_ReturnType Rte_Write_SigPrep_OdometerTotal(const tsRte_OdometerTotal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_OdometerTotal, ppara1, sizeof(tsRte_OdometerTotal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_OdometerTotal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_OdometerTotal(tsRte_OdometerTotal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_OdometerTotal, sizeof(tsRte_OdometerTotal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_OdometerTotal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ElecIntegra ***
Std_ReturnType Rte_Write_SigPrep_ElecIntegra(const tsRte_ElecIntegra* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ElecIntegra, ppara1, sizeof(tsRte_ElecIntegra));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ElecIntegra);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ElecIntegra(tsRte_ElecIntegra* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ElecIntegra, sizeof(tsRte_ElecIntegra));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ElecIntegra) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_DcmDiagStatusR ***
Std_ReturnType Rte_Write_SigPrep_DcmDiagStatusR(const tsRte_DcmDiagStatusR* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_DcmDiagStatusR, ppara1, sizeof(tsRte_DcmDiagStatusR));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_DcmDiagStatusR);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_DcmDiagStatusR(tsRte_DcmDiagStatusR* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_DcmDiagStatusR, sizeof(tsRte_DcmDiagStatusR));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_DcmDiagStatusR) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_LevellingTgtPos ***
Std_ReturnType Rte_Write_SigPrep_LevellingTgtPos(const tsRte_LevellingTgtPos* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_LevellingTgtPos, ppara1, sizeof(tsRte_LevellingTgtPos));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_LevellingTgtPos);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_LevellingTgtPos(tsRte_LevellingTgtPos* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_LevellingTgtPos, sizeof(tsRte_LevellingTgtPos));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_LevellingTgtPos) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_HS6_DAT_VSM_2AE_Received ***
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_VSM_2AE_Received(const tHS6_DAT_VSM_2AE* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrep_HS6_DAT_VSM_2AE_Received, ppara1, sizeof(tHS6_DAT_VSM_2AE));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_VSM_2AE_Received);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_VSM_2AE_Received);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received(tHS6_DAT_VSM_2AE* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrep_HS6_DAT_VSM_2AE_Received, sizeof(tHS6_DAT_VSM_2AE));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_VSM_2AE_Received) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_HS6_DAT_VSM_2AE_NotReceived ***
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_VSM_2AE_NotReceived(boolean para1)
{
  RtePortSR_U.SigPrep_HS6_DAT_VSM_2AE_NotReceived = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_VSM_2AE_NotReceived);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_VSM_2AE_NotReceived);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_2AE_NotReceived(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.SigPrep_HS6_DAT_VSM_2AE_NotReceived;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_VSM_2AE_NotReceived) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_SigPrep_HS6_DAT_VSM_2AE_NotReceived(void)
{
  return RtePortSR_U.SigPrep_HS6_DAT_VSM_2AE_NotReceived;
}

// *** SigPrep_HS6_DAT_VSM_34E_Received ***
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_VSM_34E_Received(const tHS6_DAT_VSM_34E* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrep_HS6_DAT_VSM_34E_Received, ppara1, sizeof(tHS6_DAT_VSM_34E));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_VSM_34E_Received);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_VSM_34E_Received);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received(tHS6_DAT_VSM_34E* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrep_HS6_DAT_VSM_34E_Received, sizeof(tHS6_DAT_VSM_34E));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_VSM_34E_Received) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_HS6_DAT_VSM_34E_NotReceived ***
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_VSM_34E_NotReceived(boolean para1)
{
  RtePortSR_U.SigPrep_HS6_DAT_VSM_34E_NotReceived = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_VSM_34E_NotReceived);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_VSM_34E_NotReceived);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_34E_NotReceived(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.SigPrep_HS6_DAT_VSM_34E_NotReceived;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_VSM_34E_NotReceived) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_SigPrep_HS6_DAT_VSM_34E_NotReceived(void)
{
  return RtePortSR_U.SigPrep_HS6_DAT_VSM_34E_NotReceived;
}

// *** SigPrep_HS6_COMMANDES_VSM_036_Received ***
Std_ReturnType Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_Received(const tHS6_COMMANDES_VSM_036* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrep_HS6_COMMANDES_VSM_036_Received, ppara1, sizeof(tHS6_COMMANDES_VSM_036));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_COMMANDES_VSM_036_Received);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_COMMANDES_VSM_036_Received);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received(tHS6_COMMANDES_VSM_036* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrep_HS6_COMMANDES_VSM_036_Received, sizeof(tHS6_COMMANDES_VSM_036));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_COMMANDES_VSM_036_Received) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_HS6_COMMANDES_VSM_036_NotReceived ***
Std_ReturnType Rte_Write_SigPrep_HS6_COMMANDES_VSM_036_NotReceived(boolean para1)
{
  RtePortSR_U.SigPrep_HS6_COMMANDES_VSM_036_NotReceived = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_COMMANDES_VSM_036_NotReceived);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_COMMANDES_VSM_036_NotReceived);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_NotReceived(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.SigPrep_HS6_COMMANDES_VSM_036_NotReceived;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_COMMANDES_VSM_036_NotReceived) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_SigPrep_HS6_COMMANDES_VSM_036_NotReceived(void)
{
  return RtePortSR_U.SigPrep_HS6_COMMANDES_VSM_036_NotReceived;
}

// *** SigPrep_HS6_DAT_BSI_432_Received ***
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_BSI_432_Received(const tHS6_DAT_BSI_432* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrep_HS6_DAT_BSI_432_Received, ppara1, sizeof(tHS6_DAT_BSI_432));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_BSI_432_Received);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_BSI_432_Received);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DAT_BSI_432_Received(tHS6_DAT_BSI_432* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrep_HS6_DAT_BSI_432_Received, sizeof(tHS6_DAT_BSI_432));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_BSI_432_Received) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_HS6_DAT_BSI_432_NotReceived ***
Std_ReturnType Rte_Write_SigPrep_HS6_DAT_BSI_432_NotReceived(boolean para1)
{
  RtePortSR_U.SigPrep_HS6_DAT_BSI_432_NotReceived = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_BSI_432_NotReceived);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_DAT_BSI_432_NotReceived);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DAT_BSI_432_NotReceived(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.SigPrep_HS6_DAT_BSI_432_NotReceived;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DAT_BSI_432_NotReceived) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_SigPrep_HS6_DAT_BSI_432_NotReceived(void)
{
  return RtePortSR_U.SigPrep_HS6_DAT_BSI_432_NotReceived;
}

// *** SigPrep_HS6_DYN_ABR_38D_Received ***
Std_ReturnType Rte_Write_SigPrep_HS6_DYN_ABR_38D_Received(const tHS6_DYN_ABR_38D* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrep_HS6_DYN_ABR_38D_Received, ppara1, sizeof(tHS6_DYN_ABR_38D));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DYN_ABR_38D_Received);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_DYN_ABR_38D_Received);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received(tHS6_DYN_ABR_38D* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrep_HS6_DYN_ABR_38D_Received, sizeof(tHS6_DYN_ABR_38D));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DYN_ABR_38D_Received) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_HS6_DYN_ABR_38D_NotReceived ***
Std_ReturnType Rte_Write_SigPrep_HS6_DYN_ABR_38D_NotReceived(boolean para1)
{
  RtePortSR_U.SigPrep_HS6_DYN_ABR_38D_NotReceived = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DYN_ABR_38D_NotReceived);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_HS6_DYN_ABR_38D_NotReceived);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DYN_ABR_38D_NotReceived(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.SigPrep_HS6_DYN_ABR_38D_NotReceived;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DYN_ABR_38D_NotReceived) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_SigPrep_HS6_DYN_ABR_38D_NotReceived(void)
{
  return RtePortSR_U.SigPrep_HS6_DYN_ABR_38D_NotReceived;
}

// *** SigPrep_SleepBSI ***
Std_ReturnType Rte_Write_SigPrep_SleepBSI(const uint8* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrep_SleepBSI, ppara1, sizeof(uint8));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_SleepBSI);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_SleepBSI(uint8* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrep_SleepBSI, sizeof(uint8));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_SleepBSI) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_NMMode ***
Std_ReturnType Rte_Write_SigPrep_NMMode(const NM_ModeType* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrep_NMMode, ppara1, sizeof(NM_ModeType));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_NMMode);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_NMMode(NM_ModeType* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrep_NMMode, sizeof(NM_ModeType));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_NMMode) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_HS6_DIAG_DRVLED_Sent ***
Std_ReturnType Rte_Write_SigPrep_HS6_DIAG_DRVLED_Sent(boolean para1)
{
  RtePortSR_U.SigPrep_HS6_DIAG_DRVLED_Sent = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DIAG_DRVLED_Sent);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonTx_HS6_DIAG_DRVLED_Sent);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DIAG_DRVLED_Sent(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.SigPrep_HS6_DIAG_DRVLED_Sent;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DIAG_DRVLED_Sent) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_SigPrep_HS6_DIAG_DRVLED_Sent(void)
{
  return RtePortSR_U.SigPrep_HS6_DIAG_DRVLED_Sent;
}

// *** SigPrep_HS6_DIAG_DRVLED_NotSent ***
Std_ReturnType Rte_Write_SigPrep_HS6_DIAG_DRVLED_NotSent(boolean para1)
{
  RtePortSR_U.SigPrep_HS6_DIAG_DRVLED_NotSent = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DIAG_DRVLED_NotSent);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonTx_HS6_DIAG_DRVLED_NotSent);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_HS6_DIAG_DRVLED_NotSent(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.SigPrep_HS6_DIAG_DRVLED_NotSent;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_HS6_DIAG_DRVLED_NotSent) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_SigPrep_HS6_DIAG_DRVLED_NotSent(void)
{
  return RtePortSR_U.SigPrep_HS6_DIAG_DRVLED_NotSent;
}

// *** DEM_UV_NotifyStatus ***
Std_ReturnType Rte_Write_DEM_UV_NotifyStatus(const boolean* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.DEM_UV_NotifyStatus, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_DEM_UV_NotifyStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_DEM_UV_NotifyStatus(boolean* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.DEM_UV_NotifyStatus, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_DEM_UV_NotifyStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** DEM_OV_NotifyStatus ***
Std_ReturnType Rte_Write_DEM_OV_NotifyStatus(const boolean* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.DEM_OV_NotifyStatus, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_DEM_OV_NotifyStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_DEM_OV_NotifyStatus(boolean* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.DEM_OV_NotifyStatus, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_DEM_OV_NotifyStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** DEM_350Lost_NotifyStatus ***
Std_ReturnType Rte_Write_DEM_350Lost_NotifyStatus(const boolean* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.DEM_350Lost_NotifyStatus, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_DEM_350Lost_NotifyStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_DEM_350Lost_NotifyStatus(boolean* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.DEM_350Lost_NotifyStatus, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_DEM_350Lost_NotifyStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ElecInt_RequestRUN ***
Std_ReturnType Rte_Write_ElecInt_RequestRUN(const uint8* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.ElecInt_RequestRUN, ppara1, sizeof(uint8));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ElecInt_RequestRUN);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reEcuM_RequestRUN);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ElecInt_RequestRUN(uint8* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.ElecInt_RequestRUN, sizeof(uint8));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ElecInt_RequestRUN) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ElecInt_ReleaseRUN ***
Std_ReturnType Rte_Write_ElecInt_ReleaseRUN(const uint8* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.ElecInt_ReleaseRUN, ppara1, sizeof(uint8));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ElecInt_ReleaseRUN);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reEcuM_ReleaseRUN);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ElecInt_ReleaseRUN(uint8* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.ElecInt_ReleaseRUN, sizeof(uint8));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ElecInt_ReleaseRUN) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ElecInt_ReleasePOST_RUN ***
Std_ReturnType Rte_Write_ElecInt_ReleasePOST_RUN(const uint8* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.ElecInt_ReleasePOST_RUN, ppara1, sizeof(uint8));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ElecInt_ReleasePOST_RUN);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reEcuM_ReleasePOST_RUN);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ElecInt_ReleasePOST_RUN(uint8* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.ElecInt_ReleasePOST_RUN, sizeof(uint8));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ElecInt_ReleasePOST_RUN) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ElecInt_EnableCallbacks ***
Std_ReturnType Rte_Write_ElecInt_EnableCallbacks(boolean para1)
{
  RtePortSR_U.ElecInt_EnableCallbacks = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ElecInt_EnableCallbacks);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonRx_EnableCallbacks);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ElecInt_EnableCallbacks(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.ElecInt_EnableCallbacks;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ElecInt_EnableCallbacks) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_ElecInt_EnableCallbacks(void)
{
  return RtePortSR_U.ElecInt_EnableCallbacks;
}

// *** ElecInt_ActivateTxBufer ***
Std_ReturnType Rte_Write_ElecInt_ActivateTxBufer(boolean para1)
{
  RtePortSR_U.ElecInt_ActivateTxBufer = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ElecInt_ActivateTxBufer);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reSysMonTx_ActivateTxBufer);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ElecInt_ActivateTxBufer(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.ElecInt_ActivateTxBufer;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ElecInt_ActivateTxBufer) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_ElecInt_ActivateTxBufer(void)
{
  return RtePortSR_U.ElecInt_ActivateTxBufer;
}

// *** Diag_ResetStatistics ***
Std_ReturnType Rte_Write_Diag_ResetStatistics(boolean para1)
{
  RtePortSR_U.Diag_ResetStatistics = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Diag_ResetStatistics);

  Rte_PortSR_Trigger(eRteThread_U_HH, eRteThreadFlag_U_HH_reStatM_ResetStatistics);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Diag_ResetStatistics(boolean* ppara1)
{
  *ppara1 = RtePortSR_U.Diag_ResetStatistics;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Diag_ResetStatistics) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_Diag_ResetStatistics(void)
{
  return RtePortSR_U.Diag_ResetStatistics;
}

// *** OS_CPULoadAvg ***
Std_ReturnType Rte_Write_OS_CPULoadAvg(uint8 para1)
{
  RtePortSR_U.OS_CPULoadAvg = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_OS_CPULoadAvg);


  return RTE_E_OK;
}

Std_ReturnType Rte_Read_OS_CPULoadAvg(uint8* ppara1)
{
  *ppara1 = RtePortSR_U.OS_CPULoadAvg;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_OS_CPULoadAvg) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

uint8 Rte_DRead_OS_CPULoadAvg(void)
{
  return RtePortSR_U.OS_CPULoadAvg;
}

// *** OS_CPULoadPeak ***
Std_ReturnType Rte_Write_OS_CPULoadPeak(uint8 para1)
{
  RtePortSR_U.OS_CPULoadPeak = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_OS_CPULoadPeak);


  return RTE_E_OK;
}

Std_ReturnType Rte_Read_OS_CPULoadPeak(uint8* ppara1)
{
  *ppara1 = RtePortSR_U.OS_CPULoadPeak;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_OS_CPULoadPeak) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

uint8 Rte_DRead_OS_CPULoadPeak(void)
{
  return RtePortSR_U.OS_CPULoadPeak;
}

// *** Diag_TiScrollingTakeOver ***
Std_ReturnType Rte_Write_Diag_TiScrollingTakeOver(const boolean* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Diag_TiScrollingTakeOver, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Diag_TiScrollingTakeOver);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Diag_TiScrollingTakeOver(boolean* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Diag_TiScrollingTakeOver, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Diag_TiScrollingTakeOver) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** IoHwAbUser_GetMountingSide ***
Std_ReturnType Rte_Write_IoHwAbUser_GetMountingSide(const teRte_MountingSide* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.IoHwAbUser_GetMountingSide, ppara1, sizeof(teRte_MountingSide));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_IoHwAbUser_GetMountingSide);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.IoHwAbUser_GetMountingSide, sizeof(teRte_MountingSide));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_IoHwAbUser_GetMountingSide) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** IoHwAb_User_GetAdc_DIAG_VBAT ***
Std_ReturnType Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT(const tiu32Voltage_mV* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.IoHwAb_User_GetAdc_DIAG_VBAT, ppara1, sizeof(tiu32Voltage_mV));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_IoHwAb_User_GetAdc_DIAG_VBAT);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.IoHwAb_User_GetAdc_DIAG_VBAT, sizeof(tiu32Voltage_mV));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_IoHwAb_User_GetAdc_DIAG_VBAT) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** IoHwAb_GetSens_Balanced ***
Std_ReturnType Rte_Write_IoHwAb_GetSens_Balanced(const tsRte_SensorBalance* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.IoHwAb_GetSens_Balanced, ppara1, sizeof(tsRte_SensorBalance));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_IoHwAb_GetSens_Balanced);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_IoHwAb_GetSens_Balanced(tsRte_SensorBalance* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.IoHwAb_GetSens_Balanced, sizeof(tsRte_SensorBalance));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_IoHwAb_GetSens_Balanced) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** IoHwAb_GetSens_Raw ***
Std_ReturnType Rte_Write_IoHwAb_GetSens_Raw(const tsRte_SensorRaw* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.IoHwAb_GetSens_Raw, ppara1, sizeof(tsRte_SensorRaw));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_IoHwAb_GetSens_Raw);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.IoHwAb_GetSens_Raw, sizeof(tsRte_SensorRaw));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_IoHwAb_GetSens_Raw) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** IoHwAb_GetPCB ***
Std_ReturnType Rte_Write_IoHwAb_GetPCB(const tiu16Voltage_mV* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.IoHwAb_GetPCB, ppara1, sizeof(tiu16Voltage_mV));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_IoHwAb_GetPCB);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_IoHwAb_GetPCB(tiu16Voltage_mV* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.IoHwAb_GetPCB, sizeof(tiu16Voltage_mV));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_IoHwAb_GetPCB) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** IoHwAb_GetVoltage_NTCs ***
Std_ReturnType Rte_Write_IoHwAb_GetVoltage_NTCs(const tsRte_Voltage_mV* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.IoHwAb_GetVoltage_NTCs, ppara1, sizeof(tsRte_Voltage_mV));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_IoHwAb_GetVoltage_NTCs);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_IoHwAb_GetVoltage_NTCs(tsRte_Voltage_mV* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.IoHwAb_GetVoltage_NTCs, sizeof(tsRte_Voltage_mV));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_IoHwAb_GetVoltage_NTCs) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** IoHwAb_VCCX1Voltage ***
Std_ReturnType Rte_Write_IoHwAb_VCCX1Voltage(const tiu16Voltage_mV* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.IoHwAb_VCCX1Voltage, ppara1, sizeof(tiu16Voltage_mV));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_IoHwAb_VCCX1Voltage);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_IoHwAb_VCCX1Voltage(tiu16Voltage_mV* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.IoHwAb_VCCX1Voltage, sizeof(tiu16Voltage_mV));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_IoHwAb_VCCX1Voltage) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** MPU_ErrorCounter ***
Std_ReturnType Rte_Write_MPU_ErrorCounter(const uint32* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.MPU_ErrorCounter, ppara1, sizeof(uint32));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_MPU_ErrorCounter);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_MPU_ErrorCounter(uint32* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.MPU_ErrorCounter, sizeof(uint32));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_MPU_ErrorCounter) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** EcuM_Deinit ***
Std_ReturnType Rte_Write_EcuM_Deinit(boolean para1)
{
  RtePortSR_T.EcuM_Deinit = para1;

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_EcuM_Deinit);

  Rte_PortSR_Trigger(eRteThread_U_HH, eRteThreadFlag_U_HH_reStatM_Deinit);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_EcuM_Deinit(boolean* ppara1)
{
  *ppara1 = RtePortSR_T.EcuM_Deinit;

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_EcuM_Deinit) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

boolean Rte_DRead_EcuM_Deinit(void)
{
  return RtePortSR_T.EcuM_Deinit;
}

// *** Cpm_TgtLedSig_sVal ***
Std_ReturnType Rte_Write_Cpm_TgtLedSig_sVal(const tsRte_TgtLedSig0Arr* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Cpm_TgtLedSig_sVal, ppara1, sizeof(tsRte_TgtLedSig0Arr));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Cpm_TgtLedSig_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Cpm_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Cpm_TgtLedSig_sVal, sizeof(tsRte_TgtLedSig0Arr));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Cpm_TgtLedSig_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CpmHssTarget0_sSetting ***
Std_ReturnType Rte_Write_CpmHssTarget0_sSetting(const tsRteHssTarget* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CpmHssTarget0_sSetting, ppara1, sizeof(tsRteHssTarget));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CpmHssTarget0_sSetting);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CpmHssTarget0_sSetting(tsRteHssTarget* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CpmHssTarget0_sSetting, sizeof(tsRteHssTarget));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CpmHssTarget0_sSetting) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Cpm_SigPrepTx_PowerFactor ***
Std_ReturnType Rte_Write_Cpm_SigPrepTx_PowerFactor(const tsRte_PowerFactor* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Cpm_SigPrepTx_PowerFactor, ppara1, sizeof(tsRte_PowerFactor));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Cpm_SigPrepTx_PowerFactor);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Cpm_SigPrepTx_PowerFactor(tsRte_PowerFactor* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Cpm_SigPrepTx_PowerFactor, sizeof(tsRte_PowerFactor));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Cpm_SigPrepTx_PowerFactor) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Cpm_PowFact_Temp ***
Std_ReturnType Rte_Write_Cpm_PowFact_Temp(const tsRtePowFactTemp* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Cpm_PowFact_Temp, ppara1, sizeof(tsRtePowFactTemp));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Cpm_PowFact_Temp);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Cpm_PowFact_Temp(tsRtePowFactTemp* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Cpm_PowFact_Temp, sizeof(tsRtePowFactTemp));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Cpm_PowFact_Temp) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Cpm_CtrlSwi_HSS3Target ***
Std_ReturnType Rte_Write_Cpm_CtrlSwi_HSS3Target(const tsRte_CpmHSS3Duty* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Cpm_CtrlSwi_HSS3Target, ppara1, sizeof(tsRte_CpmHSS3Duty));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Cpm_CtrlSwi_HSS3Target);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Cpm_CtrlSwi_HSS3Target(tsRte_CpmHSS3Duty* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Cpm_CtrlSwi_HSS3Target, sizeof(tsRte_CpmHSS3Duty));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Cpm_CtrlSwi_HSS3Target) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysVolt_FanVoltRng0_sVoltRng ***
Std_ReturnType Rte_Write_SysVolt_FanVoltRng0_sVoltRng(const teRte_SysVolt_Results* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SysVolt_FanVoltRng0_sVoltRng, ppara1, sizeof(teRte_SysVolt_Results));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SysVolt_FanVoltRng0_sVoltRng);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysVolt_FanVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SysVolt_FanVoltRng0_sVoltRng, sizeof(teRte_SysVolt_Results));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SysVolt_FanVoltRng0_sVoltRng) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysVolt_LedVoltRng0_sVoltRng ***
Std_ReturnType Rte_Write_SysVolt_LedVoltRng0_sVoltRng(const teRte_SysVolt_Results* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SysVolt_LedVoltRng0_sVoltRng, ppara1, sizeof(teRte_SysVolt_Results));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SysVolt_LedVoltRng0_sVoltRng);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysVolt_LedVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SysVolt_LedVoltRng0_sVoltRng, sizeof(teRte_SysVolt_Results));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SysVolt_LedVoltRng0_sVoltRng) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** StatM_StackUsage ***
Std_ReturnType Rte_Write_StatM_StackUsage(uint8 para1)
{
  RtePortSR_U.StatM_StackUsage = para1;

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_StatM_StackUsage);


  return RTE_E_OK;
}

Std_ReturnType Rte_Read_StatM_StackUsage(uint8* ppara1)
{
  *ppara1 = RtePortSR_U.StatM_StackUsage;

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_StatM_StackUsage) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

uint8 Rte_DRead_StatM_StackUsage(void)
{
  return RtePortSR_U.StatM_StackUsage;
}

// *** RSens_PcbTemperature ***
Std_ReturnType Rte_Write_RSens_PcbTemperature(const tsRte_PcbTemperatureMsg* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.RSens_PcbTemperature, ppara1, sizeof(tsRte_PcbTemperatureMsg));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_PcbTemperature);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_PcbTemperature(tsRte_PcbTemperatureMsg* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.RSens_PcbTemperature, sizeof(tsRte_PcbTemperatureMsg));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_PcbTemperature) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_ThermzoneTemperatures ***
Std_ReturnType Rte_Write_RSens_ThermzoneTemperatures(const tsRte_NTCTemperature* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_ThermzoneTemperatures, ppara1, sizeof(tsRte_NTCTemperature));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_ThermzoneTemperatures);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_ThermzoneTemperatures, sizeof(tsRte_NTCTemperature));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_ThermzoneTemperatures) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_00 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_00(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_00, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_00);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_00(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_00, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_00) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_01 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_01(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_01, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_01);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_01(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_01, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_01) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_02 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_02(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_02, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_02);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_02(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_02, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_02) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_03 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_03(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_03, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_03);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_03(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_03, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_03) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_NTC_BIN_Input_Errors ***
Std_ReturnType Rte_Write_RSens_NTC_BIN_Input_Errors(const tsRteNTCBinInData* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_NTC_BIN_Input_Errors, ppara1, sizeof(tsRteNTCBinInData));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_NTC_BIN_Input_Errors);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_NTC_BIN_Input_Errors(tsRteNTCBinInData* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_NTC_BIN_Input_Errors, sizeof(tsRteNTCBinInData));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_NTC_BIN_Input_Errors) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningDataDiag ***
Std_ReturnType Rte_Write_RSens_BinningDataDiag(const tsRte_D409Binning* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningDataDiag, ppara1, sizeof(tsRte_D409Binning));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningDataDiag);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningDataDiag(tsRte_D409Binning* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningDataDiag, sizeof(tsRte_D409Binning));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningDataDiag) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** FctR_TgtLed_sVal ***
Std_ReturnType Rte_Write_FctR_TgtLed_sVal(const tsRte_TgtLedVal0Arr* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.FctR_TgtLed_sVal, ppara1, sizeof(tsRte_TgtLedVal0Arr));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_TgtLed_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_TgtLed_sVal(tsRte_TgtLedVal0Arr* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.FctR_TgtLed_sVal, sizeof(tsRte_TgtLedVal0Arr));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_TgtLed_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** FctR_LgtFctState ***
Std_ReturnType Rte_Write_FctR_LgtFctState(const tsRte_LgtFctState* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.FctR_LgtFctState, ppara1, sizeof(tsRte_LgtFctState));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_LgtFctState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_LgtFctState(tsRte_LgtFctState* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.FctR_LgtFctState, sizeof(tsRte_LgtFctState));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_LgtFctState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** FctR_LgtFctStatus ***
Std_ReturnType Rte_Write_FctR_LgtFctStatus(const tsRte_LgtFctStatus* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.FctR_LgtFctStatus, ppara1, sizeof(tsRte_LgtFctStatus));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_LgtFctStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_LgtFctStatus(tsRte_LgtFctStatus* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.FctR_LgtFctStatus, sizeof(tsRte_LgtFctStatus));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_LgtFctStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** FctR_TiWarningMode ***
Std_ReturnType Rte_Write_FctR_TiWarningMode(const teRte_WarningMode* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.FctR_TiWarningMode, ppara1, sizeof(teRte_WarningMode));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_TiWarningMode);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_TiWarningMode(teRte_WarningMode* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.FctR_TiWarningMode, sizeof(teRte_WarningMode));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_TiWarningMode) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** FctR_TiFailureStatus ***
Std_ReturnType Rte_Write_FctR_TiFailureStatus(const boolean* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.FctR_TiFailureStatus, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_TiFailureStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_TiFailureStatus(boolean* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.FctR_TiFailureStatus, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_TiFailureStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** FctR_LgtDistStatus ***
Std_ReturnType Rte_Write_FctR_LgtDistStatus(const uint32* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.FctR_LgtDistStatus, ppara1, sizeof(uint32));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_LgtDistStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_LgtDistStatus(uint32* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.FctR_LgtDistStatus, sizeof(uint32));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_LgtDistStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlLed_TgtLedSig_sVal ***
Std_ReturnType Rte_Write_CtrlLed_TgtLedSig_sVal(const tsRte_TgtLedSig0Arr* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlLed_TgtLedSig_sVal, ppara1, sizeof(tsRte_TgtLedSig0Arr));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlLed_TgtLedSig_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlLed_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlLed_TgtLedSig_sVal, sizeof(tsRte_TgtLedSig0Arr));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlLed_TgtLedSig_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlLed_TgtHssSig_sVal ***
Std_ReturnType Rte_Write_CtrlLed_TgtHssSig_sVal(const tsRte_TgtLedSig0* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlLed_TgtHssSig_sVal, ppara1, sizeof(tsRte_TgtLedSig0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlLed_TgtHssSig_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlLed_TgtHssSig_sVal(tsRte_TgtLedSig0* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlLed_TgtHssSig_sVal, sizeof(tsRte_TgtLedSig0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlLed_TgtHssSig_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlLed_LedSettings_sVal ***
Std_ReturnType Rte_Write_CtrlLed_LedSettings_sVal(const tsRte_ChLedSettings* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlLed_LedSettings_sVal, ppara1, sizeof(tsRte_ChLedSettings));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlLed_LedSettings_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlLed_LedSettings_sVal(tsRte_ChLedSettings* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlLed_LedSettings_sVal, sizeof(tsRte_ChLedSettings));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlLed_LedSettings_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlLed_ActLed_sState ***
Std_ReturnType Rte_Write_CtrlLed_ActLed_sState(const tsRte_LedErrStateArr* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlLed_ActLed_sState, ppara1, sizeof(tsRte_LedErrStateArr));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlLed_ActLed_sState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlLed_ActLed_sState(tsRte_LedErrStateArr* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlLed_ActLed_sState, sizeof(tsRte_LedErrStateArr));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlLed_ActLed_sState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlLed_BinningClass ***
Std_ReturnType Rte_Write_CtrlLed_BinningClass(const tsRte_ucBinningSelect* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlLed_BinningClass, ppara1, sizeof(tsRte_ucBinningSelect));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlLed_BinningClass);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlLed_BinningClass(tsRte_ucBinningSelect* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlLed_BinningClass, sizeof(tsRte_ucBinningSelect));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlLed_BinningClass) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlLed_LedChFbit ***
Std_ReturnType Rte_Write_CtrlLed_LedChFbit(const tsRte_LedChFbit* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlLed_LedChFbit, ppara1, sizeof(tsRte_LedChFbit));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlLed_LedChFbit);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlLed_LedChFbit(tsRte_LedChFbit* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlLed_LedChFbit, sizeof(tsRte_LedChFbit));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlLed_LedChFbit) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlLed_ChState ***
Std_ReturnType Rte_Write_CtrlLed_ChState(const tsRte_CtrlLed_ChStatesDiag* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlLed_ChState, ppara1, sizeof(tsRte_CtrlLed_ChStatesDiag));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlLed_ChState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlLed_ChState(tsRte_CtrlLed_ChStatesDiag* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlLed_ChState, sizeof(tsRte_CtrlLed_ChStatesDiag));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlLed_ChState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlSwi_TgtValue_Fan1 ***
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_Fan1(const tRteSwitchTgtVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlSwi_TgtValue_Fan1, ppara1, sizeof(tRteSwitchTgtVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlSwi_TgtValue_Fan1);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlSwi_TgtValue_Fan1(tRteSwitchTgtVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlSwi_TgtValue_Fan1, sizeof(tRteSwitchTgtVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlSwi_TgtValue_Fan1) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlSwi_TgtValue_Fan2 ***
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_Fan2(const tRteSwitchTgtVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlSwi_TgtValue_Fan2, ppara1, sizeof(tRteSwitchTgtVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlSwi_TgtValue_Fan2);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlSwi_TgtValue_Fan2(tRteSwitchTgtVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlSwi_TgtValue_Fan2, sizeof(tRteSwitchTgtVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlSwi_TgtValue_Fan2) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlSwi_TgtValue_SMRGB ***
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_SMRGB(const tRteSwitchTgtVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlSwi_TgtValue_SMRGB, ppara1, sizeof(tRteSwitchTgtVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlSwi_TgtValue_SMRGB);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlSwi_TgtValue_SMRGB(tRteSwitchTgtVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlSwi_TgtValue_SMRGB, sizeof(tRteSwitchTgtVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlSwi_TgtValue_SMRGB) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlSwi_StatusErr ***
Std_ReturnType Rte_Write_CtrlSwi_StatusErr(const tisHssStatusError* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlSwi_StatusErr, ppara1, sizeof(tisHssStatusError));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlSwi_StatusErr);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlSwi_StatusErr(tisHssStatusError* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlSwi_StatusErr, sizeof(tisHssStatusError));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlSwi_StatusErr) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlSwi_TgtValue_ScrollingSatelite ***
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(const teRte_SateliteStatus* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlSwi_TgtValue_ScrollingSatelite, ppara1, sizeof(teRte_SateliteStatus));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlSwi_TgtValue_ScrollingSatelite);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite(teRte_SateliteStatus* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlSwi_TgtValue_ScrollingSatelite, sizeof(teRte_SateliteStatus));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlSwi_TgtValue_ScrollingSatelite) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlSwi_Hss3StatusErr ***
Std_ReturnType Rte_Write_CtrlSwi_Hss3StatusErr(const tsRte_Hss3Status* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlSwi_Hss3StatusErr, ppara1, sizeof(tsRte_Hss3Status));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlSwi_Hss3StatusErr);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlSwi_Hss3StatusErr(tsRte_Hss3Status* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlSwi_Hss3StatusErr, sizeof(tsRte_Hss3Status));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlSwi_Hss3StatusErr) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CddLed_LedState ***
Std_ReturnType Rte_Write_CddLed_LedState(const tsRte_LedStates* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.CddLed_LedState, ppara1, sizeof(tsRte_LedStates));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CddLed_LedState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CddLed_LedState(tsRte_LedStates* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.CddLed_LedState, sizeof(tsRte_LedStates));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CddLed_LedState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CddLed_Status ***
Std_ReturnType Rte_Write_CddLed_Status(const tCddLedStatus* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.CddLed_Status, ppara1, sizeof(tCddLedStatus));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CddLed_Status);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CddLed_Status(tCddLedStatus* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.CddLed_Status, sizeof(tCddLedStatus));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CddLed_Status) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CddLed_TgtLed_FaultStatus_ASIL ***
Std_ReturnType Rte_Write_CddLed_TgtLed_FaultStatus_ASIL(const tsRte_TgtLedSig0_FaultStatus_ASIL* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.CddLed_TgtLed_FaultStatus_ASIL, ppara1, sizeof(tsRte_TgtLedSig0_FaultStatus_ASIL));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CddLed_TgtLed_FaultStatus_ASIL);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CddLed_TgtLed_FaultStatus_ASIL(tsRte_TgtLedSig0_FaultStatus_ASIL* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.CddLed_TgtLed_FaultStatus_ASIL, sizeof(tsRte_TgtLedSig0_FaultStatus_ASIL));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CddLed_TgtLed_FaultStatus_ASIL) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CddBoost_BoostState ***
Std_ReturnType Rte_Write_CddBoost_BoostState(const tsRte_BoostState* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.CddBoost_BoostState, ppara1, sizeof(tsRte_BoostState));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CddBoost_BoostState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CddBoost_BoostState(tsRte_BoostState* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.CddBoost_BoostState, sizeof(tsRte_BoostState));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CddBoost_BoostState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CddBoost_BoostStatus ***
Std_ReturnType Rte_Write_CddBoost_BoostStatus(const tCddBoostStatus* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.CddBoost_BoostStatus, ppara1, sizeof(tCddBoostStatus));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CddBoost_BoostStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CddBoost_BoostStatus(tCddBoostStatus* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.CddBoost_BoostStatus, sizeof(tCddBoostStatus));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CddBoost_BoostStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CddSwi_SwitchStatus ***
Std_ReturnType Rte_Write_CddSwi_SwitchStatus(const tsRte_HssStatus* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CddSwi_SwitchStatus, ppara1, sizeof(tsRte_HssStatus));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CddSwi_SwitchStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CddSwi_SwitchStatus(tsRte_HssStatus* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CddSwi_SwitchStatus, sizeof(tsRte_HssStatus));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CddSwi_SwitchStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppsAvacStat1Out_Port ***
Std_ReturnType Rte_Write_ppsAvacStat1Out_Port(const tPositionOut* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.ppsAvacStat1Out_Port, ppara1, sizeof(tPositionOut));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppsAvacStat1Out_Port);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppsAvacStat1Out_Port(tPositionOut* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.ppsAvacStat1Out_Port, sizeof(tPositionOut));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppsAvacStat1Out_Port) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** AvacStat1_SpeedMode ***
Std_ReturnType Rte_Write_AvacStat1_SpeedMode(const teRte_DcmSpeedMode* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.AvacStat1_SpeedMode, ppara1, sizeof(teRte_DcmSpeedMode));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_AvacStat1_SpeedMode);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_AvacStat1_SpeedMode(teRte_DcmSpeedMode* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.AvacStat1_SpeedMode, sizeof(teRte_DcmSpeedMode));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_AvacStat1_SpeedMode) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** DcmPos0_Port ***
Std_ReturnType Rte_Write_DcmPos0_Port(const tDcmPosMsg* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.DcmPos0_Port, ppara1, sizeof(tDcmPosMsg));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_DcmPos0_Port);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_DcmPos0_Port(tDcmPosMsg* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.DcmPos0_Port, sizeof(tDcmPosMsg));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_DcmPos0_Port) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** DcmState0_Port ***
Std_ReturnType Rte_Write_DcmState0_Port(const tDcmStateMsg* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.DcmState0_Port, ppara1, sizeof(tDcmStateMsg));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_DcmState0_Port);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_DcmState0_Port(tDcmStateMsg* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.DcmState0_Port, sizeof(tDcmStateMsg));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_DcmState0_Port) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CddDcm_ErrorStatus ***
Std_ReturnType Rte_Write_CddDcm_ErrorStatus(const tsRte_DcmStatusError* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CddDcm_ErrorStatus, ppara1, sizeof(tsRte_DcmStatusError));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CddDcm_ErrorStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CddDcm_ErrorStatus(tsRte_DcmStatusError* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CddDcm_ErrorStatus, sizeof(tsRte_DcmStatusError));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CddDcm_ErrorStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Pitch_SensRaw ***
Std_ReturnType Rte_Write_Pitch_SensRaw(const tSensRaw0* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Pitch_SensRaw, ppara1, sizeof(tSensRaw0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Pitch_SensRaw);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Pitch_SensRaw(tSensRaw0* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Pitch_SensRaw, sizeof(tSensRaw0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Pitch_SensRaw) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Pitch_Angle ***
Std_ReturnType Rte_Write_Pitch_Angle(const tPitch0* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Pitch_Angle, ppara1, sizeof(tPitch0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Pitch_Angle);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Pitch_Angle(tPitch0* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Pitch_Angle, sizeof(tPitch0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Pitch_Angle) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Pitch_PlausState ***
Std_ReturnType Rte_Write_Pitch_PlausState(const teRte_HlsSensorState* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Pitch_PlausState, ppara1, sizeof(teRte_HlsSensorState));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Pitch_PlausState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Pitch_PlausState(teRte_HlsSensorState* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Pitch_PlausState, sizeof(teRte_HlsSensorState));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Pitch_PlausState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlDcm_MasterCommand ***
Std_ReturnType Rte_Write_CtrlDcm_MasterCommand(const tsRte_LevellingTgtPos* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlDcm_MasterCommand, ppara1, sizeof(tsRte_LevellingTgtPos));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlDcm_MasterCommand);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlDcm_MasterCommand(tsRte_LevellingTgtPos* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlDcm_MasterCommand, sizeof(tsRte_LevellingTgtPos));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlDcm_MasterCommand) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppCtrlDcmTarget0_DcmTargetValues ***
Std_ReturnType Rte_Write_ppCtrlDcmTarget0_DcmTargetValues(const tsRte_CtrlDcmTarget* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.ppCtrlDcmTarget0_DcmTargetValues, ppara1, sizeof(tsRte_CtrlDcmTarget));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppCtrlDcmTarget0_DcmTargetValues);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppCtrlDcmTarget0_DcmTargetValues(tsRte_CtrlDcmTarget* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.ppCtrlDcmTarget0_DcmTargetValues, sizeof(tsRte_CtrlDcmTarget));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppCtrlDcmTarget0_DcmTargetValues) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlDcm_StatusParameters_Port ***
Std_ReturnType Rte_Write_CtrlDcm_StatusParameters_Port(const tsRte_CtrlDcmStatusParams* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlDcm_StatusParameters_Port, ppara1, sizeof(tsRte_CtrlDcmStatusParams));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlDcm_StatusParameters_Port);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlDcm_StatusParameters_Port(tsRte_CtrlDcmStatusParams* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlDcm_StatusParameters_Port, sizeof(tsRte_CtrlDcmStatusParams));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlDcm_StatusParameters_Port) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** DrvLedDiag ***
Std_ReturnType Rte_Write_DrvLedDiag(const tsRte_Hs6_Diag_Drvled_L_457* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.DrvLedDiag, ppara1, sizeof(tsRte_Hs6_Diag_Drvled_L_457));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_DrvLedDiag);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.DrvLedDiag, sizeof(tsRte_Hs6_Diag_Drvled_L_457));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_DrvLedDiag) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** DrvLedDiagR ***
Std_ReturnType Rte_Write_DrvLedDiagR(const tsRte_Hs6_Diag_Drvled_R_477* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.DrvLedDiagR, ppara1, sizeof(tsRte_Hs6_Diag_Drvled_R_477));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_DrvLedDiagR);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.DrvLedDiagR, sizeof(tsRte_Hs6_Diag_Drvled_R_477));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_DrvLedDiagR) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

