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

#define RTE_CFG_C_ID 64464413

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
  { riCtrlPxl_Init, eRteSafety_Untrusted }, 
  { riCtrlStpInit, eRteSafety_Untrusted }, 
  { riAvac_Init, eRteSafety_Untrusted }, 
  { riPitch_Init, eRteSafety_Untrusted }, 
  { riDbl_Init, eRteSafety_Untrusted }, 
  { riMxb_Init, eRteSafety_Untrusted }, 
  { riAdbPxa3_Init, eRteSafety_Untrusted }, 
  { riCddLedInit, eRteSafety_Trusted }, 
  { riCddBoostInit, eRteSafety_Trusted }, 
  { riCddSpiInit, eRteSafety_Trusted }, 
  { riCddSbc_Init, eRteSafety_Trusted }, 
  { riCddEftInit, eRteSafety_Untrusted }, 
  { riCddUartInit, eRteSafety_Trusted }, 
  { riCddMlc_Init, eRteSafety_Trusted }, 
  { riCddStpInit, eRteSafety_Untrusted }, 
  { riCddSwi_Init, eRteSafety_Untrusted }
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
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCtrlPxl_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCtrlStp_Cycle }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpAvac_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpPitch_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpDbl_Cycle }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpMxb_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpAdbPxa3_Cycle0 }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddLed_Cycle }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddBoost_Cycle }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddSpi_Cycle }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddSbc_Cycle0 }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddUart_Cycle }, 
  { eRteThread_T_HL, eRteThreadFlag_T_HL_rpCddMlc_Cycle0 }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCddStp_Cycle }, 
  { eRteThread_U_LH, eRteThreadFlag_U_LH_rpCddSwi_Cycle0 }
};

const CYCLIC_TABLE_TYPE  RTE_CyclicTable[] =
{
  /*   0 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rcStatM_Cycle10ms) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*   1 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*   2 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpPitch_Cycle0) | CYCLIC(RTECYC_rpDbl_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*   3 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*   4 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCtrlStp_Cycle) | CYCLIC(RTECYC_rpAvac_Cycle0) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*   5 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*   6 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*   7 */  CYCLIC(RTECYC_rpCodM_Cycle0) | CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*   8 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*   9 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  10 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*  11 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  12 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  13 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*  14 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  15 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  16 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  17 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  18 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  19 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  20 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*  21 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  22 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpPitch_Cycle0) | CYCLIC(RTECYC_rpDbl_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  23 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*  24 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCtrlStp_Cycle) | CYCLIC(RTECYC_rpAvac_Cycle0) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  25 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  26 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  27 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  28 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  29 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  30 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*  31 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  32 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  33 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*  34 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  35 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  36 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  37 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  38 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  39 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  40 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*  41 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  42 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpPitch_Cycle0) | CYCLIC(RTECYC_rpDbl_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  43 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*  44 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCtrlStp_Cycle) | CYCLIC(RTECYC_rpAvac_Cycle0) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  45 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  46 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  47 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  48 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  49 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  50 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*  51 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  52 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  53 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*  54 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  55 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  56 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  57 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  58 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  59 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  60 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*  61 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  62 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpPitch_Cycle0) | CYCLIC(RTECYC_rpDbl_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  63 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*  64 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCtrlStp_Cycle) | CYCLIC(RTECYC_rpAvac_Cycle0) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  65 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  66 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  67 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  68 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  69 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  70 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*  71 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  72 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  73 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*  74 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  75 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  76 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  77 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  78 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  79 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  80 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpSysVolt_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*  81 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  82 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpPitch_Cycle0) | CYCLIC(RTECYC_rpDbl_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  83 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpRSens_Cycle0) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*  84 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCpm20ms) | CYCLIC(RTECYC_rpCtrlStp_Cycle) | CYCLIC(RTECYC_rpAvac_Cycle0) | CYCLIC(RTECYC_rpCddLed_Cycle) | CYCLIC(RTECYC_rpCddBoost_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  85 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSbc_Cycle0) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  86 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  87 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpDiagControl_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  88 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  89 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpFctR_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  90 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle) | CYCLIC(RTECYC_rpCddMlc_Cycle0), 
  /*  91 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlPxl_Cycle0) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  92 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  93 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddStp_Cycle), 
  /*  94 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  95 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rcMemoryProc) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlSwiCycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddSwi_Cycle0), 
  /*  96 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpMxb_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
  /*  97 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCddSpi_Cycle), 
  /*  98 */  CYCLIC(RTECYC_rcSysMon_Cycle1ms) | CYCLIC(RTECYC_rpSchM_Func_NonTrusted_Cycle) | CYCLIC(RTECYC_rpSchM_Func_Trusted_Cycle) | CYCLIC(RTECYC_rpCtrlLed_Cycle0) | CYCLIC(RTECYC_rpAdbPxa3_Cycle0) | CYCLIC(RTECYC_rpCddSpi_Cycle) | CYCLIC(RTECYC_rpCddUart_Cycle), 
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
  reIoHwAbUser_GetLssDiagnostic, 
  reEcuM_RequestRUN, 
  reEcuM_ReleaseRUN, 
  reEcuM_ReleasePOST_RUN, 
  reEcuM_RequestPOST_RUN, 
  reEcuM_DiagResetRequest, 
  reCddSbc_SetLssPwm, 
  reCddMlcEE_Read, 
  reCddMlcEE_Write, 
  reCddMlcEE_CbkInit
};

const pRunnable_t RTE_Runnable_T_HL_func[eRteThreadFlag_T_HL_Count] =
{
  rcSysMon_Cycle1ms, 
  rpSchM_Func_Trusted_Cycle, 
  rpCddLed_Cycle, 
  rpCddBoost_Cycle, 
  rpCddSpi_Cycle, 
  rpCddSbc_Cycle0, 
  rpCddUart_Cycle, 
  rpCddMlc_Cycle0
};

const pRunnable_t RTE_Runnable_U_HH_func[eRteThreadFlag_U_HH_Count] =
{
  reSigPrepRx_LifePhases, 
  reSigPrepRx_SetDiagMux, 
  reSigPrepTx_SendFrame457, 
  reSigPrepTx_SendFrame477, 
  reNvm_WritePxlData, 
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
  rpCtrlPxl_Cycle0, 
  rpCtrlStp_Cycle, 
  rpAvac_Cycle0, 
  rpPitch_Cycle0, 
  rpDbl_Cycle, 
  rpMxb_Cycle0, 
  rpAdbPxa3_Cycle0, 
  rpCddStp_Cycle, 
  rpCddSwi_Cycle0
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
  tsRte_SysMonLgtFctsReq SysMon_StdLgtFcts_Req;
  teRte_ReqLightState SysMon_LowBeamCmd_Req;
  teRte_ReqLightState SysMon_TurnIndicatorCmd_Req;
  tsRte_SysMonAfsSignals SysMon_Afs_Signals;
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
  teRte_VccxLineState IoHwAbUser_VccxLineState;
  uint32             MPU_ErrorCounter;
  boolean            EcuM_Deinit;
  tsRte_LedStates    CddLed_LedState;
  tCddLedStatus      CddLed_Status;
  tsRte_TgtLedSig0_FaultStatus_ASIL CddLed_TgtLed_FaultStatus_ASIL;
  tsRte_BoostState   CddBoost_BoostState;
  tCddBoostStatus    CddBoost_BoostStatus;
  tsRte_CddMlcComStatus CtrlPxl_CddMlc_ComStatus_sVal;
  tasRte_MlcLedStatus CtrlPxl_CddMlc_LedStatus_aVal;
  tasRte_MlcAdcResult CtrlPxl_CddMlc_AdcResult_aVal;
  tsRte_MlcComErrorStatus CtrlPxl_CddMlc_CrcError_sVal;
  teRte_CddMlc_SystemMode CtrlPxl_CddMlc_SystemMode_eVal;
}RtePortSR_T;

__attribute__((section(".bss.RtePortSR_U")))
static struct
{
  tsRteCodingParameters CodM_FctR_Para;
  tsRteCodingParameters CodM_Adb_Pxa_Para;
  tsRteCodingParameters CodM_Adb_Mxb_Para;
  tsRteCodingParameters CodM_CddMlc_Para;
  tsRteCodingParameters CodM_Dbl_Para;
  tsRteCodingParameters CodM_AppM_Para;
  tsRteCodingParameters CodM_Pitch_Para;
  tsRteCodingParameters CodM_CtrlLed_Para;
  tsRteCodingParameters CodM_CtrlPxl_Para;
  tsRteCodingParameters CodM_Rsens_Para;
  tsRteCodingParameters CodM_CtrlFan_Para;
  tsRteCodingParameters CodM_CtrlStp_Para;
  tsRteCodingParameters CodM_SysVolt_Para;
  tsRteCodingParameters CodM_CddStp_Para;
  tsRteCodingParameters CodM_CddLed_Para;
  tsRteCodingParameters CodM_CddBoost_Para;
  tsRteCodingParameters CodM_CddSwi_Para;
  tsRteCodingParameters CodM_SigPrep_Para;
  tsRteCodingParameters CodM_SysMon_Para;
  tsRteCodingParameters CodM_Anima_Para;
  tsRteCodingParameters CodM_Err_Para;
  tsRte_AfsRoutineControl Diag_RoutineControl;
  tsRte_Ld_ActivationRoutineControl Diag_LdActivationRoutineControl;
  boolean            Diag_DD01_Activation;
  tsRte_DIDPixelActivation Diag_DD01_PixelActivation;
  tsRte_StepperRoutineControl Stp_RoutineControl;
  boolean            Diag_DiagResetRequest;
  uint8              Diag_RequestPOST_RUN;
  teRte_ScrollingTgt Diag_Scrolling_TgtValue;
  tsRte_SigPrepLgtClSblReq SigPrep_StdLgtClSbl_Req;
  tsRte_SigPrep_PerceiveSigGroup1_sVal SigPrep_PerceiveSigGroup1_sVal_00;
  tsRte_SigPrep_PerceiveSigGroup1_sVal SigPrep_PerceiveSigGroup1_sVal_01;
  tsRte_SigPrep_PerceiveSigGroup1_sVal SigPrep_PerceiveSigGroup1_sVal_02;
  tsRte_SigPrep_ClusterSigGroup1_sVal SigPrep_ClusterSigGroup1_sVal_00;
  tsRte_SigPrep_ClusterSigGroup1_sVal SigPrep_ClusterSigGroup1_sVal_01;
  tsRte_SigPrep_ClusterSigGroup1_sVal SigPrep_ClusterSigGroup1_sVal_02;
  tsRte_SigPrep_ClusterSigGroup1_sVal SigPrep_ClusterSigGroup1_sVal_03;
  tsRte_SigPrep_ClusterSigGroup1_sVal SigPrep_ClusterSigGroup1_sVal_04;
  tsRte_SigPrep_PerceiveSigGroup2_sVal SigPrep_PerceiveSigGroup2_sVal_00;
  tsRte_SigPrep_PerceiveSigGroup2_sVal SigPrep_PerceiveSigGroup2_sVal_01;
  tsRte_SigPrep_PerceiveSigGroup2_sVal SigPrep_PerceiveSigGroup2_sVal_02;
  tsRte_SigPrep_ClusterSigGroup2_sVal SigPrep_ClusterSigGroup2_sVal_00;
  tsRte_SigPrep_ClusterSigGroup2_sVal SigPrep_ClusterSigGroup2_sVal_01;
  tsRte_SigPrep_ClusterSigGroup2_sVal SigPrep_ClusterSigGroup2_sVal_02;
  tsRte_SigPrep_ClusterSigGroup2_sVal SigPrep_ClusterSigGroup2_sVal_03;
  tsRte_SigPrep_ClusterSigGroup2_sVal SigPrep_ClusterSigGroup2_sVal_04;
  tsRte_SigPrep_YawSpeed SigPrep_YawSpeed;
  tsRte_SigPrep_VehPathCurvature SigPrep_VehPathCurvature;
  tsRte_SigPrep_EnvCondition SigPrep_EnvCondition;
  tsRte_SigPrep_ElecSupState SigPrep_ElecSupState;
  tsRte_SigPrep_VehicleConfigSig SigPrep_VehicleConfigSig;
  tsRte_SigPrep_DynamicSigs SigPrep_DynamicSigs;
  tsRte_SigPrep_SteeringWheelAngle SigPrep_SteeringWheelAngle;
  tsRte_SigPrep_VehiclePitchAngle SigPrep_VehiclePitchAngle;
  tsRte_AnimationReq SigPrep_AnimationReq;
  tsRte_VehTimeCntr  SigPrep_VehTimeCntr;
  tsRte_OdometerTotal SigPrep_OdometerTotal;
  tsRte_ElecIntegra  SigPrep_ElecIntegra;
  tsRte_LevellingFeedback SigPrep_LevellingFeedback;
  tsRte_LevellingDiagStatus SigPrep_LevellingDiagStatus;
  tsRte_LevellingTgtPos SigPrep_LevellingTgtPos;
  tsRte_BendingBeamFault_OtherHL SigPrepRx_Dbl_LeftStatus;
  tsRte_BendingBeamFault_OtherHL SigPrepRx_Dbl_RightStatus;
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
  tsRte_TgtPxlSig0Arr Cpm_CtrlPxl_DeratedMtxPixels;
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
  tsRte_Binning0     RSens_BinningClass_sVal_04;
  tsRte_Binning0     RSens_BinningClass_sVal_05;
  tsRte_Binning0     RSens_BinningClass_sVal_06;
  tsRte_Binning0     RSens_BinningClass_sVal_07;
  tsRte_Binning0     RSens_BinningClass_sVal_08;
  tsRte_Binning0     RSens_BinningClass_sVal_09;
  tsRte_Binning0     RSens_BinningClass_sVal_10;
  tsRte_Binning0     RSens_BinningClass_sVal_11;
  tsRteNTCBinInData  RSens_NTC_BIN_Input_Errors;
  tsRte_D409Binning  RSens_BinningDataDiag;
  teRte_AfsModeSig_sVal FctR_AfsModeSig_sVal;
  teRte_GfHb_Cmd     FctR_GfHbCmd;
  tsRte_TgtLedVal0Arr FctR_TgtLed_sVal;
  tsRte_AfsDblCmd    FctR_AfsDblCmd;
  tsRte_LgtFctState  FctR_LgtFctState;
  tsRte_LgtFctStatus FctR_LgtFctStatus;
  teRte_WarningMode  FctR_TiWarningMode;
  boolean            FctR_TiFailureStatus;
  uint32             FctR_LgtDistStatus;
  boolean            FctR_PXALightDistr_Fbit;
  tsRte_TgtLedSig0Arr CtrlLed_TgtLedSig_sVal;
  tsRte_TgtLedSig0   CtrlLed_TgtHssSig_sVal;
  tsRte_ChLedSettings CtrlLed_LedSettings_sVal;
  tsRte_TgtPxlSig0Arr CtrlLed_Cpm_TgtPxlSig;
  tsRte_LedErrStateArr CtrlLed_ActLed_sState;
  tsRte_ucBinningSelect CtrlLed_BinningClass;
  tsRte_LedChFbit    CtrlLed_LedChFbit;
  tsRte_CtrlLed_ChStatesDiag CtrlLed_ChState;
  tsRte_TgtAniArrScr AnimaScrollingActivation;
  tRteSwitchTgtVal   CtrlSwi_TgtValue_Fan1;
  tRteSwitchTgtVal   CtrlSwi_TgtValue_Fan2;
  tRteSwitchTgtVal   CtrlSwi_TgtValue_SMRGB;
  teRte_SateliteStatus CtrlSwi_TgtValue_ScrollingSatelite;
  tisHssStatusError  CtrlSwi_StatusErr;
  tsRte_Hss3Status   CtrlSwi_Hss3StatusErr;
  tsRte_TgtMtxPixels_sVal CtrlPxl_TgtMtxPixels_sVal;
  tsRte_MatrixFaultStates CtrlPxl_CtrLed_MatrixFault_sState;
  tauRte_CtrlPxl_Mtx_bErr CtrlPxl_CtrlLed_Matrix_bErr_aVal;
  tsRte_MtxEeprom_ErrStatus CtrlPxl_MtxEeprom_ErrorStatus;
  tasRte_CtrlPxl_BinEEprom CtrlPxl_CtrlLed_EepromBinningClass_aVal;
  uint8              CtrlPxl_CddMlc_SysCtrlCommand;
  boolean            CtrlPxl_CddMlc_ReinitMatrix;
  tsRte_ucActualPxlPWM CtrlPxl_ActualPxlPWM;
  tsRte_boMtxSegmentFault CtrlPxl_ActualPxlError;
  tsRte_MatrixEE0peration CtrlPxl_MatrixEE_DataRead;
  tsRte_MatrixEE0peration CtrlPxl_MatrixEE_DataWrite;
  tsRte_MatrixEE0CbkFn CtrlPxl_MatrixEE_CbkInitData;
  tsRte_NvMBlock     CtrlPxl_Nvm_WriteData;
  tsRte_CtrlStpTarget ppCtrlStpTarget0_StpTargetValues;
  tsRte_Hs6_Diag_Drvled_L_457 DrvLedDiag;
  tsRte_LevellingTgtPos CtrlStp_MasterCommand;
  tsRte_LevellingDiagStatus CtrlStp_SlaveDiagStatus;
  tsRte_LevellingFeedback CtrlStp_SlaveFeedback;
  tsRte_ActStatStp0  CtrlStp_ActStatStp_sVal_0;
  tsRte_CtrlStpValidation CtrlStp_Validation_Port;
  tsPositionOut      ppsAvacOut;
  tPitch0            Pitch_Angle;
  teRte_HlsSensorState Pitch_PlausState;
  tsRte_DblOut       Dbl_SwivellingOut;
  tsRte_AfsDblDriveSituation AfsDbl_DblDriveSit;
  tsRte_SwiRateLimMsg AfsDbl_SwiRateLimMsg;
  tsRte_BendingBeamFault_OtherHL Dbl_SigPrepTx_RightStatus;
  tsRte_BendingBeamFault_OtherHL Dbl_SigPrepTx_LeftStatus;
  tsRte_Hs6_Diag_Drvled_BendingBeamFault Dbl_SysMonTx_FullStatus;
  teRte_DblSubMode   Dbl_Mode;
  tAdbOut            ppsAdb_Out_sVal_0;
  tAdbOut            ppsAdb_Out_sVal_1;
  tAdbOut            ppsAdb_Out_sVal_2;
  tAdbOut            ppsAdb_Out_sVal_3;
  tAdbOut            ppsAdb_Out_sVal_4;
  tAdbStatus         Adb_StatusOut;
  boolean            AdbMxb_Gfhb_Diag;
  tsRte_PxaIntensityMatrix AdbPxa_IntensityMatrix;
  tsRte_CddStpActual ppCddStpActual0_sStpActualValues;
  tsRte_HssStatus    CddSwi_SwitchStatus;
  tScrollingPresent_Stat CddSwi_ScrollingOn_Stat;
  uint16             CddSwi_SetLssPwm_Req;
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

// *** CodM_Adb_Pxa_Para ***
Std_ReturnType Rte_Write_CodM_Adb_Pxa_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_Adb_Pxa_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_Adb_Pxa_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_Adb_Pxa_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_Adb_Pxa_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_Adb_Pxa_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_Adb_Mxb_Para ***
Std_ReturnType Rte_Write_CodM_Adb_Mxb_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_Adb_Mxb_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_Adb_Mxb_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_Adb_Mxb_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_Adb_Mxb_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_Adb_Mxb_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_CddMlc_Para ***
Std_ReturnType Rte_Write_CodM_CddMlc_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CodM_CddMlc_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_CddMlc_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_CddMlc_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CodM_CddMlc_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_CddMlc_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CodM_Dbl_Para ***
Std_ReturnType Rte_Write_CodM_Dbl_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_Dbl_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_Dbl_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_Dbl_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_Dbl_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_Dbl_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** CodM_CtrlPxl_Para ***
Std_ReturnType Rte_Write_CodM_CtrlPxl_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_CtrlPxl_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_CtrlPxl_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_CtrlPxl_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_CtrlPxl_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_CtrlPxl_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** CodM_CtrlStp_Para ***
Std_ReturnType Rte_Write_CodM_CtrlStp_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_CtrlStp_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_CtrlStp_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_CtrlStp_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_CtrlStp_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_CtrlStp_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** CodM_CddStp_Para ***
Std_ReturnType Rte_Write_CodM_CddStp_Para(const tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CodM_CddStp_Para, ppara1, sizeof(tsRteCodingParameters));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CodM_CddStp_Para);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CodM_CddStp_Para(tsRteCodingParameters* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CodM_CddStp_Para, sizeof(tsRteCodingParameters));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CodM_CddStp_Para) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_TurnIndicatorCmd_Req, ppara1, sizeof(teRte_ReqLightState));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_TurnIndicatorCmd_Req);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_TurnIndicatorCmd_Req(teRte_ReqLightState* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_TurnIndicatorCmd_Req, sizeof(teRte_ReqLightState));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_TurnIndicatorCmd_Req) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SysMon_Afs_Signals ***
Std_ReturnType Rte_Write_SysMon_Afs_Signals(const tsRte_SysMonAfsSignals* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_Afs_Signals, ppara1, sizeof(tsRte_SysMonAfsSignals));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_Afs_Signals);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_Afs_Signals(tsRte_SysMonAfsSignals* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_Afs_Signals, sizeof(tsRte_SysMonAfsSignals));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_Afs_Signals) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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
  Rte_PortSR_Copy(&RtePortSR_T.SysMon_LedState, ppara1, sizeof(tsRte_SysMon_LedStates));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_SysMon_LedState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SysMon_LedState(tsRte_SysMon_LedStates* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_T.SysMon_LedState, sizeof(tsRte_SysMon_LedStates));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_SysMon_LedState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Diag_RoutineControl ***
Std_ReturnType Rte_Write_Diag_RoutineControl(const tsRte_AfsRoutineControl* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Diag_RoutineControl, ppara1, sizeof(tsRte_AfsRoutineControl));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Diag_RoutineControl);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Diag_RoutineControl(tsRte_AfsRoutineControl* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Diag_RoutineControl, sizeof(tsRte_AfsRoutineControl));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Diag_RoutineControl) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** Diag_DD01_Activation ***
Std_ReturnType Rte_Write_Diag_DD01_Activation(const boolean* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Diag_DD01_Activation, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Diag_DD01_Activation);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Diag_DD01_Activation(boolean* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Diag_DD01_Activation, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Diag_DD01_Activation) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Diag_DD01_PixelActivation ***
Std_ReturnType Rte_Write_Diag_DD01_PixelActivation(const tsRte_DIDPixelActivation* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Diag_DD01_PixelActivation, ppara1, sizeof(tsRte_DIDPixelActivation));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Diag_DD01_PixelActivation);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Diag_DD01_PixelActivation(tsRte_DIDPixelActivation* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Diag_DD01_PixelActivation, sizeof(tsRte_DIDPixelActivation));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Diag_DD01_PixelActivation) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Stp_RoutineControl ***
Std_ReturnType Rte_Write_Stp_RoutineControl(const tsRte_StepperRoutineControl* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Stp_RoutineControl, ppara1, sizeof(tsRte_StepperRoutineControl));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Stp_RoutineControl);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Stp_RoutineControl(tsRte_StepperRoutineControl* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Stp_RoutineControl, sizeof(tsRte_StepperRoutineControl));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Stp_RoutineControl) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** Diag_Scrolling_TgtValue ***
Std_ReturnType Rte_Write_Diag_Scrolling_TgtValue(const teRte_ScrollingTgt* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Diag_Scrolling_TgtValue, ppara1, sizeof(teRte_ScrollingTgt));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Diag_Scrolling_TgtValue);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Diag_Scrolling_TgtValue(teRte_ScrollingTgt* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Diag_Scrolling_TgtValue, sizeof(teRte_ScrollingTgt));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Diag_Scrolling_TgtValue) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_StdLgtClSbl_Req ***
Std_ReturnType Rte_Write_SigPrep_StdLgtClSbl_Req(const tsRte_SigPrepLgtClSblReq* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_StdLgtClSbl_Req, ppara1, sizeof(tsRte_SigPrepLgtClSblReq));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_StdLgtClSbl_Req);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_StdLgtClSbl_Req(tsRte_SigPrepLgtClSblReq* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_StdLgtClSbl_Req, sizeof(tsRte_SigPrepLgtClSblReq));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_StdLgtClSbl_Req) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_PerceiveSigGroup1_sVal_00 ***
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00(const tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_PerceiveSigGroup1_sVal_00, ppara1, sizeof(tsRte_SigPrep_PerceiveSigGroup1_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup1_sVal_00);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00(tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_PerceiveSigGroup1_sVal_00, sizeof(tsRte_SigPrep_PerceiveSigGroup1_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup1_sVal_00) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_PerceiveSigGroup1_sVal_01 ***
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01(const tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_PerceiveSigGroup1_sVal_01, ppara1, sizeof(tsRte_SigPrep_PerceiveSigGroup1_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup1_sVal_01);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01(tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_PerceiveSigGroup1_sVal_01, sizeof(tsRte_SigPrep_PerceiveSigGroup1_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup1_sVal_01) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_PerceiveSigGroup1_sVal_02 ***
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02(const tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_PerceiveSigGroup1_sVal_02, ppara1, sizeof(tsRte_SigPrep_PerceiveSigGroup1_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup1_sVal_02);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02(tsRte_SigPrep_PerceiveSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_PerceiveSigGroup1_sVal_02, sizeof(tsRte_SigPrep_PerceiveSigGroup1_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup1_sVal_02) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup1_sVal_00 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_00(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_00, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_00);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_00(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_00, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_00) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup1_sVal_01 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_01(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_01, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_01);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_01(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_01, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_01) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup1_sVal_02 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_02(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_02, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_02);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_02(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_02, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_02) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup1_sVal_03 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_03(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_03, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_03);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_03(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_03, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_03) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup1_sVal_04 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup1_sVal_04(const tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_04, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_04);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup1_sVal_04(tsRte_SigPrep_ClusterSigGroup1_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup1_sVal_04, sizeof(tsRte_SigPrep_ClusterSigGroup1_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup1_sVal_04) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_PerceiveSigGroup2_sVal_00 ***
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00(const tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_PerceiveSigGroup2_sVal_00, ppara1, sizeof(tsRte_SigPrep_PerceiveSigGroup2_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup2_sVal_00);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00(tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_PerceiveSigGroup2_sVal_00, sizeof(tsRte_SigPrep_PerceiveSigGroup2_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup2_sVal_00) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_PerceiveSigGroup2_sVal_01 ***
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01(const tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_PerceiveSigGroup2_sVal_01, ppara1, sizeof(tsRte_SigPrep_PerceiveSigGroup2_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup2_sVal_01);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01(tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_PerceiveSigGroup2_sVal_01, sizeof(tsRte_SigPrep_PerceiveSigGroup2_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup2_sVal_01) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_PerceiveSigGroup2_sVal_02 ***
Std_ReturnType Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02(const tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_PerceiveSigGroup2_sVal_02, ppara1, sizeof(tsRte_SigPrep_PerceiveSigGroup2_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup2_sVal_02);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02(tsRte_SigPrep_PerceiveSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_PerceiveSigGroup2_sVal_02, sizeof(tsRte_SigPrep_PerceiveSigGroup2_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_PerceiveSigGroup2_sVal_02) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup2_sVal_00 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_00(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_00, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_00);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_00(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_00, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_00) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup2_sVal_01 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_01(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_01, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_01);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_01(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_01, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_01) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup2_sVal_02 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_02(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_02, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_02);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_02(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_02, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_02) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup2_sVal_03 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_03(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_03, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_03);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_03(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_03, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_03) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_ClusterSigGroup2_sVal_04 ***
Std_ReturnType Rte_Write_SigPrep_ClusterSigGroup2_sVal_04(const tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_04, ppara1, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_04);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_ClusterSigGroup2_sVal_04(tsRte_SigPrep_ClusterSigGroup2_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_ClusterSigGroup2_sVal_04, sizeof(tsRte_SigPrep_ClusterSigGroup2_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_ClusterSigGroup2_sVal_04) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** SigPrep_VehPathCurvature ***
Std_ReturnType Rte_Write_SigPrep_VehPathCurvature(const tsRte_SigPrep_VehPathCurvature* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_VehPathCurvature, ppara1, sizeof(tsRte_SigPrep_VehPathCurvature));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_VehPathCurvature);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_VehPathCurvature(tsRte_SigPrep_VehPathCurvature* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_VehPathCurvature, sizeof(tsRte_SigPrep_VehPathCurvature));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_VehPathCurvature) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_EnvCondition ***
Std_ReturnType Rte_Write_SigPrep_EnvCondition(const tsRte_SigPrep_EnvCondition* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_EnvCondition, ppara1, sizeof(tsRte_SigPrep_EnvCondition));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_EnvCondition);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_EnvCondition(tsRte_SigPrep_EnvCondition* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_EnvCondition, sizeof(tsRte_SigPrep_EnvCondition));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_EnvCondition) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** SigPrep_SteeringWheelAngle ***
Std_ReturnType Rte_Write_SigPrep_SteeringWheelAngle(const tsRte_SigPrep_SteeringWheelAngle* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_SteeringWheelAngle, ppara1, sizeof(tsRte_SigPrep_SteeringWheelAngle));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_SteeringWheelAngle);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_SteeringWheelAngle(tsRte_SigPrep_SteeringWheelAngle* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_SteeringWheelAngle, sizeof(tsRte_SigPrep_SteeringWheelAngle));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_SteeringWheelAngle) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** SigPrep_LevellingFeedback ***
Std_ReturnType Rte_Write_SigPrep_LevellingFeedback(const tsRte_LevellingFeedback* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_LevellingFeedback, ppara1, sizeof(tsRte_LevellingFeedback));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_LevellingFeedback);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_LevellingFeedback(tsRte_LevellingFeedback* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_LevellingFeedback, sizeof(tsRte_LevellingFeedback));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_LevellingFeedback) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrep_LevellingDiagStatus ***
Std_ReturnType Rte_Write_SigPrep_LevellingDiagStatus(const tsRte_LevellingDiagStatus* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.SigPrep_LevellingDiagStatus, ppara1, sizeof(tsRte_LevellingDiagStatus));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrep_LevellingDiagStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrep_LevellingDiagStatus(tsRte_LevellingDiagStatus* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.SigPrep_LevellingDiagStatus, sizeof(tsRte_LevellingDiagStatus));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrep_LevellingDiagStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** SigPrepRx_Dbl_LeftStatus ***
Std_ReturnType Rte_Write_SigPrepRx_Dbl_LeftStatus(const tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrepRx_Dbl_LeftStatus, ppara1, sizeof(tsRte_BendingBeamFault_OtherHL));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrepRx_Dbl_LeftStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrepRx_Dbl_LeftStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrepRx_Dbl_LeftStatus, sizeof(tsRte_BendingBeamFault_OtherHL));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrepRx_Dbl_LeftStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** SigPrepRx_Dbl_RightStatus ***
Std_ReturnType Rte_Write_SigPrepRx_Dbl_RightStatus(const tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.SigPrepRx_Dbl_RightStatus, ppara1, sizeof(tsRte_BendingBeamFault_OtherHL));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_SigPrepRx_Dbl_RightStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_SigPrepRx_Dbl_RightStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.SigPrepRx_Dbl_RightStatus, sizeof(tsRte_BendingBeamFault_OtherHL));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_SigPrepRx_Dbl_RightStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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
  Rte_PortSR_CopyThread(&RtePortSR_U.DEM_350Lost_NotifyStatus, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_DEM_350Lost_NotifyStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_DEM_350Lost_NotifyStatus(boolean* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.DEM_350Lost_NotifyStatus, sizeof(boolean));

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

// *** IoHwAbUser_VccxLineState ***
Std_ReturnType Rte_Write_IoHwAbUser_VccxLineState(const teRte_VccxLineState* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.IoHwAbUser_VccxLineState, ppara1, sizeof(teRte_VccxLineState));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_IoHwAbUser_VccxLineState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_IoHwAbUser_VccxLineState(teRte_VccxLineState* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.IoHwAbUser_VccxLineState, sizeof(teRte_VccxLineState));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_IoHwAbUser_VccxLineState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** Cpm_CtrlPxl_DeratedMtxPixels ***
Std_ReturnType Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels(const tsRte_TgtPxlSig0Arr* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Cpm_CtrlPxl_DeratedMtxPixels, ppara1, sizeof(tsRte_TgtPxlSig0Arr));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Cpm_CtrlPxl_DeratedMtxPixels);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels(tsRte_TgtPxlSig0Arr* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Cpm_CtrlPxl_DeratedMtxPixels, sizeof(tsRte_TgtPxlSig0Arr));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Cpm_CtrlPxl_DeratedMtxPixels) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** RSens_BinningClass_sVal_04 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_04(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_04, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_04);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_04(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_04, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_04) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_05 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_05(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_05, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_05);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_05(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_05, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_05) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_06 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_06(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_06, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_06);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_06(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_06, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_06) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_07 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_07(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_07, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_07);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_07(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_07, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_07) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_08 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_08(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_08, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_08);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_08(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_08, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_08) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_09 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_09(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_09, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_09);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_09(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_09, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_09) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_10 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_10(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_10, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_10);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_10(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_10, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_10) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** RSens_BinningClass_sVal_11 ***
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_11(const tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.RSens_BinningClass_sVal_11, ppara1, sizeof(tsRte_Binning0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_11);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_RSens_BinningClass_sVal_11(tsRte_Binning0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.RSens_BinningClass_sVal_11, sizeof(tsRte_Binning0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_RSens_BinningClass_sVal_11) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** FctR_AfsModeSig_sVal ***
Std_ReturnType Rte_Write_FctR_AfsModeSig_sVal(const teRte_AfsModeSig_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.FctR_AfsModeSig_sVal, ppara1, sizeof(teRte_AfsModeSig_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_AfsModeSig_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_AfsModeSig_sVal(teRte_AfsModeSig_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.FctR_AfsModeSig_sVal, sizeof(teRte_AfsModeSig_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_AfsModeSig_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** FctR_GfHbCmd ***
Std_ReturnType Rte_Write_FctR_GfHbCmd(const teRte_GfHb_Cmd* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.FctR_GfHbCmd, ppara1, sizeof(teRte_GfHb_Cmd));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_GfHbCmd);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_GfHbCmd(teRte_GfHb_Cmd* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.FctR_GfHbCmd, sizeof(teRte_GfHb_Cmd));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_GfHbCmd) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** FctR_AfsDblCmd ***
Std_ReturnType Rte_Write_FctR_AfsDblCmd(const tsRte_AfsDblCmd* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.FctR_AfsDblCmd, ppara1, sizeof(tsRte_AfsDblCmd));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_AfsDblCmd);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_AfsDblCmd(tsRte_AfsDblCmd* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.FctR_AfsDblCmd, sizeof(tsRte_AfsDblCmd));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_AfsDblCmd) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** FctR_PXALightDistr_Fbit ***
Std_ReturnType Rte_Write_FctR_PXALightDistr_Fbit(const boolean* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.FctR_PXALightDistr_Fbit, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_FctR_PXALightDistr_Fbit);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_FctR_PXALightDistr_Fbit(boolean* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.FctR_PXALightDistr_Fbit, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_FctR_PXALightDistr_Fbit) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** CtrlLed_Cpm_TgtPxlSig ***
Std_ReturnType Rte_Write_CtrlLed_Cpm_TgtPxlSig(const tsRte_TgtPxlSig0Arr* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlLed_Cpm_TgtPxlSig, ppara1, sizeof(tsRte_TgtPxlSig0Arr));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlLed_Cpm_TgtPxlSig);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlLed_Cpm_TgtPxlSig(tsRte_TgtPxlSig0Arr* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlLed_Cpm_TgtPxlSig, sizeof(tsRte_TgtPxlSig0Arr));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlLed_Cpm_TgtPxlSig) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** AnimaScrollingActivation ***
Std_ReturnType Rte_Write_AnimaScrollingActivation(const tsRte_TgtAniArrScr* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.AnimaScrollingActivation, ppara1, sizeof(tsRte_TgtAniArrScr));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_AnimaScrollingActivation);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_AnimaScrollingActivation(tsRte_TgtAniArrScr* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.AnimaScrollingActivation, sizeof(tsRte_TgtAniArrScr));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_AnimaScrollingActivation) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** CtrlPxl_TgtMtxPixels_sVal ***
Std_ReturnType Rte_Write_CtrlPxl_TgtMtxPixels_sVal(const tsRte_TgtMtxPixels_sVal* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlPxl_TgtMtxPixels_sVal, ppara1, sizeof(tsRte_TgtMtxPixels_sVal));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_TgtMtxPixels_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_TgtMtxPixels_sVal(tsRte_TgtMtxPixels_sVal* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlPxl_TgtMtxPixels_sVal, sizeof(tsRte_TgtMtxPixels_sVal));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_TgtMtxPixels_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_CtrLed_MatrixFault_sState ***
Std_ReturnType Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState(const tsRte_MatrixFaultStates* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlPxl_CtrLed_MatrixFault_sState, ppara1, sizeof(tsRte_MatrixFaultStates));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_CtrLed_MatrixFault_sState);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState(tsRte_MatrixFaultStates* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlPxl_CtrLed_MatrixFault_sState, sizeof(tsRte_MatrixFaultStates));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_CtrLed_MatrixFault_sState) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_CtrlLed_Matrix_bErr_aVal ***
Std_ReturnType Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal(const tauRte_CtrlPxl_Mtx_bErr* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlPxl_CtrlLed_Matrix_bErr_aVal, ppara1, sizeof(tauRte_CtrlPxl_Mtx_bErr));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_CtrlLed_Matrix_bErr_aVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal(tauRte_CtrlPxl_Mtx_bErr* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlPxl_CtrlLed_Matrix_bErr_aVal, sizeof(tauRte_CtrlPxl_Mtx_bErr));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_CtrlLed_Matrix_bErr_aVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_MtxEeprom_ErrorStatus ***
Std_ReturnType Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus(const tsRte_MtxEeprom_ErrStatus* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlPxl_MtxEeprom_ErrorStatus, ppara1, sizeof(tsRte_MtxEeprom_ErrStatus));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_MtxEeprom_ErrorStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus(tsRte_MtxEeprom_ErrStatus* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlPxl_MtxEeprom_ErrorStatus, sizeof(tsRte_MtxEeprom_ErrStatus));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_MtxEeprom_ErrorStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_CtrlLed_EepromBinningClass_aVal ***
Std_ReturnType Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal(const tasRte_CtrlPxl_BinEEprom* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlPxl_CtrlLed_EepromBinningClass_aVal, ppara1, sizeof(tasRte_CtrlPxl_BinEEprom));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_CtrlLed_EepromBinningClass_aVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal(tasRte_CtrlPxl_BinEEprom* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlPxl_CtrlLed_EepromBinningClass_aVal, sizeof(tasRte_CtrlPxl_BinEEprom));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_CtrlLed_EepromBinningClass_aVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_CddMlc_SysCtrlCommand ***
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand(const uint8* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlPxl_CddMlc_SysCtrlCommand, ppara1, sizeof(uint8));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_CddMlc_SysCtrlCommand);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CddMlc_SysCtrlCommand(uint8* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlPxl_CddMlc_SysCtrlCommand, sizeof(uint8));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_CddMlc_SysCtrlCommand) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_CddMlc_ReinitMatrix ***
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_ReinitMatrix(const boolean* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlPxl_CddMlc_ReinitMatrix, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_CddMlc_ReinitMatrix);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CddMlc_ReinitMatrix(boolean* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlPxl_CddMlc_ReinitMatrix, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_CddMlc_ReinitMatrix) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_ActualPxlPWM ***
Std_ReturnType Rte_Write_CtrlPxl_ActualPxlPWM(const tsRte_ucActualPxlPWM* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlPxl_ActualPxlPWM, ppara1, sizeof(tsRte_ucActualPxlPWM));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_ActualPxlPWM);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_ActualPxlPWM(tsRte_ucActualPxlPWM* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlPxl_ActualPxlPWM, sizeof(tsRte_ucActualPxlPWM));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_ActualPxlPWM) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_ActualPxlError ***
Std_ReturnType Rte_Write_CtrlPxl_ActualPxlError(const tsRte_boMtxSegmentFault* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlPxl_ActualPxlError, ppara1, sizeof(tsRte_boMtxSegmentFault));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_ActualPxlError);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_ActualPxlError(tsRte_boMtxSegmentFault* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlPxl_ActualPxlError, sizeof(tsRte_boMtxSegmentFault));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_ActualPxlError) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_MatrixEE_DataRead ***
Std_ReturnType Rte_Write_CtrlPxl_MatrixEE_DataRead(const tsRte_MatrixEE0peration* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlPxl_MatrixEE_DataRead, ppara1, sizeof(tsRte_MatrixEE0peration));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_MatrixEE_DataRead);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reCddMlcEE_Read);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_MatrixEE_DataRead(tsRte_MatrixEE0peration* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlPxl_MatrixEE_DataRead, sizeof(tsRte_MatrixEE0peration));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_MatrixEE_DataRead) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_MatrixEE_DataWrite ***
Std_ReturnType Rte_Write_CtrlPxl_MatrixEE_DataWrite(const tsRte_MatrixEE0peration* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlPxl_MatrixEE_DataWrite, ppara1, sizeof(tsRte_MatrixEE0peration));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_MatrixEE_DataWrite);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reCddMlcEE_Write);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_MatrixEE_DataWrite(tsRte_MatrixEE0peration* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlPxl_MatrixEE_DataWrite, sizeof(tsRte_MatrixEE0peration));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_MatrixEE_DataWrite) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_MatrixEE_CbkInitData ***
Std_ReturnType Rte_Write_CtrlPxl_MatrixEE_CbkInitData(const tsRte_MatrixEE0CbkFn* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlPxl_MatrixEE_CbkInitData, ppara1, sizeof(tsRte_MatrixEE0CbkFn));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_MatrixEE_CbkInitData);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reCddMlcEE_CbkInit);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_MatrixEE_CbkInitData(tsRte_MatrixEE0CbkFn* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlPxl_MatrixEE_CbkInitData, sizeof(tsRte_MatrixEE0CbkFn));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_MatrixEE_CbkInitData) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_Nvm_WriteData ***
Std_ReturnType Rte_Write_CtrlPxl_Nvm_WriteData(const tsRte_NvMBlock* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlPxl_Nvm_WriteData, ppara1, sizeof(tsRte_NvMBlock));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlPxl_Nvm_WriteData);

  Rte_PortSR_Trigger(eRteThread_U_HH, eRteThreadFlag_U_HH_reNvm_WritePxlData);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_Nvm_WriteData(tsRte_NvMBlock* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlPxl_Nvm_WriteData, sizeof(tsRte_NvMBlock));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlPxl_Nvm_WriteData) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppCtrlStpTarget0_StpTargetValues ***
Std_ReturnType Rte_Write_ppCtrlStpTarget0_StpTargetValues(const tsRte_CtrlStpTarget* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.ppCtrlStpTarget0_StpTargetValues, ppara1, sizeof(tsRte_CtrlStpTarget));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppCtrlStpTarget0_StpTargetValues);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppCtrlStpTarget0_StpTargetValues(tsRte_CtrlStpTarget* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.ppCtrlStpTarget0_StpTargetValues, sizeof(tsRte_CtrlStpTarget));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppCtrlStpTarget0_StpTargetValues) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** CtrlStp_MasterCommand ***
Std_ReturnType Rte_Write_CtrlStp_MasterCommand(const tsRte_LevellingTgtPos* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlStp_MasterCommand, ppara1, sizeof(tsRte_LevellingTgtPos));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlStp_MasterCommand);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlStp_MasterCommand(tsRte_LevellingTgtPos* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlStp_MasterCommand, sizeof(tsRte_LevellingTgtPos));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlStp_MasterCommand) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlStp_SlaveDiagStatus ***
Std_ReturnType Rte_Write_CtrlStp_SlaveDiagStatus(const tsRte_LevellingDiagStatus* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlStp_SlaveDiagStatus, ppara1, sizeof(tsRte_LevellingDiagStatus));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlStp_SlaveDiagStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlStp_SlaveDiagStatus(tsRte_LevellingDiagStatus* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlStp_SlaveDiagStatus, sizeof(tsRte_LevellingDiagStatus));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlStp_SlaveDiagStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlStp_SlaveFeedback ***
Std_ReturnType Rte_Write_CtrlStp_SlaveFeedback(const tsRte_LevellingFeedback* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlStp_SlaveFeedback, ppara1, sizeof(tsRte_LevellingFeedback));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlStp_SlaveFeedback);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlStp_SlaveFeedback(tsRte_LevellingFeedback* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlStp_SlaveFeedback, sizeof(tsRte_LevellingFeedback));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlStp_SlaveFeedback) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlStp_ActStatStp_sVal_0 ***
Std_ReturnType Rte_Write_CtrlStp_ActStatStp_sVal_0(const tsRte_ActStatStp0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CtrlStp_ActStatStp_sVal_0, ppara1, sizeof(tsRte_ActStatStp0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlStp_ActStatStp_sVal_0);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlStp_ActStatStp_sVal_0(tsRte_ActStatStp0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CtrlStp_ActStatStp_sVal_0, sizeof(tsRte_ActStatStp0));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlStp_ActStatStp_sVal_0) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlStp_Validation_Port ***
Std_ReturnType Rte_Write_CtrlStp_Validation_Port(const tsRte_CtrlStpValidation* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.CtrlStp_Validation_Port, ppara1, sizeof(tsRte_CtrlStpValidation));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CtrlStp_Validation_Port);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlStp_Validation_Port(tsRte_CtrlStpValidation* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.CtrlStp_Validation_Port, sizeof(tsRte_CtrlStpValidation));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CtrlStp_Validation_Port) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppsAvacOut ***
Std_ReturnType Rte_Write_ppsAvacOut(const tsPositionOut* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.ppsAvacOut, ppara1, sizeof(tsPositionOut));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppsAvacOut);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppsAvacOut(tsPositionOut* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.ppsAvacOut, sizeof(tsPositionOut));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppsAvacOut) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Pitch_Angle ***
Std_ReturnType Rte_Write_Pitch_Angle(const tPitch0* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Pitch_Angle, ppara1, sizeof(tPitch0));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Pitch_Angle);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Pitch_Angle(tPitch0* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Pitch_Angle, sizeof(tPitch0));

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

// *** Dbl_SwivellingOut ***
Std_ReturnType Rte_Write_Dbl_SwivellingOut(const tsRte_DblOut* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Dbl_SwivellingOut, ppara1, sizeof(tsRte_DblOut));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Dbl_SwivellingOut);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Dbl_SwivellingOut(tsRte_DblOut* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Dbl_SwivellingOut, sizeof(tsRte_DblOut));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Dbl_SwivellingOut) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** AfsDbl_DblDriveSit ***
Std_ReturnType Rte_Write_AfsDbl_DblDriveSit(const tsRte_AfsDblDriveSituation* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.AfsDbl_DblDriveSit, ppara1, sizeof(tsRte_AfsDblDriveSituation));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_AfsDbl_DblDriveSit);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_AfsDbl_DblDriveSit(tsRte_AfsDblDriveSituation* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.AfsDbl_DblDriveSit, sizeof(tsRte_AfsDblDriveSituation));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_AfsDbl_DblDriveSit) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** AfsDbl_SwiRateLimMsg ***
Std_ReturnType Rte_Write_AfsDbl_SwiRateLimMsg(const tsRte_SwiRateLimMsg* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.AfsDbl_SwiRateLimMsg, ppara1, sizeof(tsRte_SwiRateLimMsg));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_AfsDbl_SwiRateLimMsg);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_AfsDbl_SwiRateLimMsg(tsRte_SwiRateLimMsg* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.AfsDbl_SwiRateLimMsg, sizeof(tsRte_SwiRateLimMsg));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_AfsDbl_SwiRateLimMsg) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Dbl_SigPrepTx_RightStatus ***
Std_ReturnType Rte_Write_Dbl_SigPrepTx_RightStatus(const tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Dbl_SigPrepTx_RightStatus, ppara1, sizeof(tsRte_BendingBeamFault_OtherHL));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Dbl_SigPrepTx_RightStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Dbl_SigPrepTx_RightStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Dbl_SigPrepTx_RightStatus, sizeof(tsRte_BendingBeamFault_OtherHL));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Dbl_SigPrepTx_RightStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Dbl_SigPrepTx_LeftStatus ***
Std_ReturnType Rte_Write_Dbl_SigPrepTx_LeftStatus(const tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Dbl_SigPrepTx_LeftStatus, ppara1, sizeof(tsRte_BendingBeamFault_OtherHL));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Dbl_SigPrepTx_LeftStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Dbl_SigPrepTx_LeftStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Dbl_SigPrepTx_LeftStatus, sizeof(tsRte_BendingBeamFault_OtherHL));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Dbl_SigPrepTx_LeftStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Dbl_SysMonTx_FullStatus ***
Std_ReturnType Rte_Write_Dbl_SysMonTx_FullStatus(const tsRte_Hs6_Diag_Drvled_BendingBeamFault* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.Dbl_SysMonTx_FullStatus, ppara1, sizeof(tsRte_Hs6_Diag_Drvled_BendingBeamFault));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Dbl_SysMonTx_FullStatus);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Dbl_SysMonTx_FullStatus(tsRte_Hs6_Diag_Drvled_BendingBeamFault* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.Dbl_SysMonTx_FullStatus, sizeof(tsRte_Hs6_Diag_Drvled_BendingBeamFault));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Dbl_SysMonTx_FullStatus) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Dbl_Mode ***
Std_ReturnType Rte_Write_Dbl_Mode(const teRte_DblSubMode* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Dbl_Mode, ppara1, sizeof(teRte_DblSubMode));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Dbl_Mode);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Dbl_Mode(teRte_DblSubMode* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Dbl_Mode, sizeof(teRte_DblSubMode));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Dbl_Mode) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppsAdb_Out_sVal_0 ***
Std_ReturnType Rte_Write_ppsAdb_Out_sVal_0(const tAdbOut* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.ppsAdb_Out_sVal_0, ppara1, sizeof(tAdbOut));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_0);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppsAdb_Out_sVal_0(tAdbOut* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.ppsAdb_Out_sVal_0, sizeof(tAdbOut));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_0) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppsAdb_Out_sVal_1 ***
Std_ReturnType Rte_Write_ppsAdb_Out_sVal_1(const tAdbOut* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.ppsAdb_Out_sVal_1, ppara1, sizeof(tAdbOut));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_1);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppsAdb_Out_sVal_1(tAdbOut* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.ppsAdb_Out_sVal_1, sizeof(tAdbOut));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_1) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppsAdb_Out_sVal_2 ***
Std_ReturnType Rte_Write_ppsAdb_Out_sVal_2(const tAdbOut* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.ppsAdb_Out_sVal_2, ppara1, sizeof(tAdbOut));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_2);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppsAdb_Out_sVal_2(tAdbOut* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.ppsAdb_Out_sVal_2, sizeof(tAdbOut));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_2) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppsAdb_Out_sVal_3 ***
Std_ReturnType Rte_Write_ppsAdb_Out_sVal_3(const tAdbOut* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.ppsAdb_Out_sVal_3, ppara1, sizeof(tAdbOut));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_3);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppsAdb_Out_sVal_3(tAdbOut* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.ppsAdb_Out_sVal_3, sizeof(tAdbOut));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_3) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppsAdb_Out_sVal_4 ***
Std_ReturnType Rte_Write_ppsAdb_Out_sVal_4(const tAdbOut* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.ppsAdb_Out_sVal_4, ppara1, sizeof(tAdbOut));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_4);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppsAdb_Out_sVal_4(tAdbOut* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.ppsAdb_Out_sVal_4, sizeof(tAdbOut));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppsAdb_Out_sVal_4) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** Adb_StatusOut ***
Std_ReturnType Rte_Write_Adb_StatusOut(const tAdbStatus* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.Adb_StatusOut, ppara1, sizeof(tAdbStatus));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_Adb_StatusOut);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_Adb_StatusOut(tAdbStatus* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.Adb_StatusOut, sizeof(tAdbStatus));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_Adb_StatusOut) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** AdbMxb_Gfhb_Diag ***
Std_ReturnType Rte_Write_AdbMxb_Gfhb_Diag(const boolean* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.AdbMxb_Gfhb_Diag, ppara1, sizeof(boolean));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_AdbMxb_Gfhb_Diag);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_AdbMxb_Gfhb_Diag(boolean* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.AdbMxb_Gfhb_Diag, sizeof(boolean));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_AdbMxb_Gfhb_Diag) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** AdbPxa_IntensityMatrix ***
Std_ReturnType Rte_Write_AdbPxa_IntensityMatrix(const tsRte_PxaIntensityMatrix* ppara1)
{
  Rte_PortSR_Copy(&RtePortSR_U.AdbPxa_IntensityMatrix, ppara1, sizeof(tsRte_PxaIntensityMatrix));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_AdbPxa_IntensityMatrix);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_AdbPxa_IntensityMatrix(tsRte_PxaIntensityMatrix* ppara1)
{
  Rte_PortSR_Copy(ppara1, &RtePortSR_U.AdbPxa_IntensityMatrix, sizeof(tsRte_PxaIntensityMatrix));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_AdbPxa_IntensityMatrix) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** CtrlPxl_CddMlc_ComStatus_sVal ***
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal(const tsRte_CddMlcComStatus* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.CtrlPxl_CddMlc_ComStatus_sVal, ppara1, sizeof(tsRte_CddMlcComStatus));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_ComStatus_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal(tsRte_CddMlcComStatus* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.CtrlPxl_CddMlc_ComStatus_sVal, sizeof(tsRte_CddMlcComStatus));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_ComStatus_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_CddMlc_LedStatus_aVal ***
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal(const tasRte_MlcLedStatus* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.CtrlPxl_CddMlc_LedStatus_aVal, ppara1, sizeof(tasRte_MlcLedStatus));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_LedStatus_aVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal(tasRte_MlcLedStatus* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.CtrlPxl_CddMlc_LedStatus_aVal, sizeof(tasRte_MlcLedStatus));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_LedStatus_aVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_CddMlc_AdcResult_aVal ***
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal(const tasRte_MlcAdcResult* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.CtrlPxl_CddMlc_AdcResult_aVal, ppara1, sizeof(tasRte_MlcAdcResult));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_AdcResult_aVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal(tasRte_MlcAdcResult* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.CtrlPxl_CddMlc_AdcResult_aVal, sizeof(tasRte_MlcAdcResult));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_AdcResult_aVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_CddMlc_CrcError_sVal ***
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_CrcError_sVal(const tsRte_MlcComErrorStatus* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.CtrlPxl_CddMlc_CrcError_sVal, ppara1, sizeof(tsRte_MlcComErrorStatus));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_CrcError_sVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CddMlc_CrcError_sVal(tsRte_MlcComErrorStatus* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.CtrlPxl_CddMlc_CrcError_sVal, sizeof(tsRte_MlcComErrorStatus));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_CrcError_sVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CtrlPxl_CddMlc_SystemMode_eVal ***
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal(const teRte_CddMlc_SystemMode* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_T.CtrlPxl_CddMlc_SystemMode_eVal, ppara1, sizeof(teRte_CddMlc_SystemMode));

  Rte_PortSR_SetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_SystemMode_eVal);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal(teRte_CddMlc_SystemMode* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_T.CtrlPxl_CddMlc_SystemMode_eVal, sizeof(teRte_CddMlc_SystemMode));

  return Rte_PortSR_GetInitFlag_T(eRtePortSR_T_CtrlPxl_CddMlc_SystemMode_eVal) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** ppCddStpActual0_sStpActualValues ***
Std_ReturnType Rte_Write_ppCddStpActual0_sStpActualValues(const tsRte_CddStpActual* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.ppCddStpActual0_sStpActualValues, ppara1, sizeof(tsRte_CddStpActual));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_ppCddStpActual0_sStpActualValues);

  return RTE_E_OK;
}

Std_ReturnType Rte_Read_ppCddStpActual0_sStpActualValues(tsRte_CddStpActual* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.ppCddStpActual0_sStpActualValues, sizeof(tsRte_CddStpActual));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_ppCddStpActual0_sStpActualValues) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
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

// *** CddSwi_ScrollingOn_Stat ***
Std_ReturnType Rte_Write_CddSwi_ScrollingOn_Stat(const tScrollingPresent_Stat* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CddSwi_ScrollingOn_Stat, ppara1, sizeof(tScrollingPresent_Stat));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CddSwi_ScrollingOn_Stat);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reIoHwAbUser_GetLssDiagnostic);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CddSwi_ScrollingOn_Stat(tScrollingPresent_Stat* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CddSwi_ScrollingOn_Stat, sizeof(tScrollingPresent_Stat));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CddSwi_ScrollingOn_Stat) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

// *** CddSwi_SetLssPwm_Req ***
Std_ReturnType Rte_Write_CddSwi_SetLssPwm_Req(const uint16* ppara1)
{
  Rte_PortSR_CopyThread(&RtePortSR_U.CddSwi_SetLssPwm_Req, ppara1, sizeof(uint16));

  Rte_PortSR_SetInitFlag_U(eRtePortSR_U_CddSwi_SetLssPwm_Req);

  Rte_PortSR_Trigger(eRteThread_T_HH, eRteThreadFlag_T_HH_reCddSbc_SetLssPwm);
  return RTE_E_OK;
}

Std_ReturnType Rte_Read_CddSwi_SetLssPwm_Req(uint16* ppara1)
{
  Rte_PortSR_CopyThread(ppara1, &RtePortSR_U.CddSwi_SetLssPwm_Req, sizeof(uint16));

  return Rte_PortSR_GetInitFlag_U(eRtePortSR_U_CddSwi_SetLssPwm_Req) ? RTE_E_OK : RTE_E_NEVER_RECEIVED;
}

