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
/// \file   CddStpPrj.h
///
/// \brief  Contains the project specific MCU functionality interfaces of stepper
///
/// \author Wuesteney, Ulrich ALRT/EEG-PM2 * (wu82rt)
///         mailTo:ulrich.wuesteney@al-lighting.com       
///         J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------

#ifndef __CDDSTPPRJ_H__
#define __CDDSTPPRJ_H__


//=============================================================================
// includes
//=============================================================================

//#include <Gpt.h>
#include <UtilMath.h>
#include <UtilUtility.h>

#include <Cfg/CddStp_Cfg.h>
#include <88XX/CddStp88XX.h>            // !
#include "../CddStp/CddStp_Tsp.h"
#include <RteCommonTypes.h>


//=============================================================================
// defines
//=============================================================================

// #define CDDSTP_ITM  // ITM debug support for Lauterbach -> 'ITM_TRACE_D8'
  // e.g.: Ref & Move & OpenLoad
  // ------------------------------------------------------------------
  // E0000064 05             540.250ms -  CddStp88XX_HalStp_eStateHoldCont
  // E0000068 01   18.150us  540.268ms - CddStp88XX_eStateTempNorm
  // ------------------------------------------------------------------
  // E0000060 01    4.642s     5.182s - CddStp88XX_eStateOff
  // E0000064 05    3.163us    5.182s -  CddStp88XX_HalStp_eStateHoldCont
  // E0000064 05   18.863us    5.182s -  CddStp88XX_HalStp_eStateHoldCont
  // E0000060 08   19.874ms    5.202s - CddStp88XX_eStateTestStep
  // E0000064 06    6.263us    5.202s -  CddStp88XX_HalStp_eStateTestStep
  // E0000064 05  115.195ms    5.317s -  CddStp88XX_HalStp_eStateHoldCont
  // ------------------------------------------------------------------
  // E0000060 03    4.903ms    5.322s - CddStp88XX_eStateIdle
  // ------------------------------------------------------------------
  // E0000060 05    9.863ms    5.332s - CddStp88XX_eStateRef1
  // E0000064 01   11.263us    5.332s -  CddStp88XX_HalStp_eStateFirstStep
  // E0000064 03   30.067ms    5.362s -  CddStp88XX_HalStp_eStateStep
  // E0000064 02    1.990s     7.352s -  CddStp88XX_HalStp_eStateLastStep
  // E0000064 04   30.027ms    7.382s -  CddStp88XX_HalStp_eStateHold
  // E0000064 05  526.825us    7.382s -  CddStp88XX_HalStp_eStateHoldCont
  // E0000060 06    9.535ms    7.392s - CddStp88XX_eStateRef2
  // E0000064 01   10.988us    7.392s -  CddStp88XX_HalStp_eStateFirstStep
  // E0000064 03   30.037ms    7.422s -  CddStp88XX_HalStp_eStateStep
  // E0000064 02  120.349ms    7.542s -  CddStp88XX_HalStp_eStateLastStep
  // E0000064 04   30.028ms    7.572s -  CddStp88XX_HalStp_eStateHold
  // E0000064 05  528.069us    7.573s -  CddStp88XX_HalStp_eStateHoldCont
  // E0000060 07    9.373ms    7.582s - CddStp88XX_eStateRefWait
  // ------------------------------------------------------------------
  // E0000060 03   27.169us    7.582s - CddStp88XX_eStateIdle
  // ------------------------------------------------------------------
  // E0000060 04    9.686ms    7.592s - CddStp88XX_eStateMove
  // E0000064 01    7.663us    7.592s -  CddStp88XX_HalStp_eStateFirstStep
  // E0000064 03   30.029ms    7.622s -  CddStp88XX_HalStp_eStateStep
  // E0000064 02  566.834ms    8.189s -  CddStp88XX_HalStp_eStateLastStep
  // E0000064 04    7.040ms    8.196s -  CddStp88XX_HalStp_eStateHold
  // E0000064 05  528.575us    8.196s -  CddStp88XX_HalStp_eStateHoldCont
  // ------------------------------------------------------------------
  // E0000060 03    5.869ms    8.202s - CddStp88XX_eStateIdle
  // ------------------------------------------------------------------
  // E0000060 09    1.600s     9.802s - CddStp88XX_eStateErr
  // E0000060 00    9.758ms    9.812s - CddStp88XX_eStateInit
  // ------------------------------------------------------------------


  // Activate code for simulation interface
  // Comment following define to deactivate the feature.
#define CDDSTP_CFG_SIMULATION


  // RDM-Workaround (wrong Bit-Pos)
  // #define CDDSTP_RDM_WORKAROUND


  // Unit-Tests-Debugging
#ifdef UNIT_TEST
  // #define CDDSTP_UNIT_TEST_DEBUGGING
  #ifdef    CDDSTP_UNIT_TEST_DEBUGGING // && UNIT_TEST
    #include <stdio.h> // debugging: printf("\n*#*#*#*#*#*#*#* JK - Mt_CddStp88XX_xxx *#*#*#*#*#*#*#*\n");
    #define CddStp_UnitTest_Printf(...)  printf(__VA_ARGS__)
  #else
    #define CddStp_UnitTest_Printf(...)  ((void)(0))
  #endif
#else
  #define CddStp_UnitTest_Printf(...)  ((void)(0))
#endif


// Index of supported drivers (generic definition, depends on stepper configuration)
typedef enum
{
  #if (CFG_DRV_STP_LWR == CFG_Drv_Default)
    CddStpPrj_eDrvIxVer     = 0,
  #endif
  #if (CFG_DRV_STP_KL == CFG_Drv_Default)
    CddStpPrj_eDrvIxHor     = 1,
  #endif
  #if (CFG_DRV_STP_GLW == CFG_Drv_Default)
    CddStpPrj_eDrvIxSht     = 2,
  #endif
    CddStpPrj_eDrvCntMax          // count of supported drivers
} CddStp88XX_eDrriverIndex;


// CFG_LNK_PSENSXXXn (XXXn = VER0, VER1, HOR0, HOR1, SHT0, SHT1)
#define CFG_LnkDrv_PsensNone              1U
#define CFG_LnkDrv_PsensLwr               2U   // for onboard steppers only
#define CFG_LnkDrv_PsensKl                3U   // for onboard steppers only
#define CFG_LnkDrv_PsensGlw               4U   // for onboard steppers only
#define CFG_LnkDrv_PsensExt               5U   // for external steppers only

#define CFG_LNK_PSENSVER0                 CFG_LnkDrv_PsensNone
#define CFG_LNK_PSENSHOR0                 CFG_LnkDrv_PsensNone
#define CFG_LNK_PSENSSHT0                 CFG_LnkDrv_PsensNone


//-----------------------------------------------------------------------------------------------
// includes depending on this definitions
//-----------------------------------------------------------------------------------------------
#include <CddStpTypes.h>                // incl. '88XX/CddStp88XX_HalStp.h'
#include <88XX/CddStp88XX.h>
#include <88XX/_CddStp88XX.h>
#include <88XX/CddStp88XX_FctTables.h>
#include <8899/CddStp8899Types.h>

//-----------------------------------------------------------------------------------------------


#define CDDSTP88XX_HALSTP_HSStpsPerHS      (2u)                                    // half step:  count of time steps with different step clock levels while one half step
#define CDDSTP88XX_HALSTP_MSStpsPerHS      (8u)                                    // micro step: count of time steps with different step clock levels while one half step

// --- timer preparations
#ifdef  TSP
#undef  TSP
#endif

#define TSP(x)                              TAUB0##x                                // !search more strings 'TAUB0' for specific changes!

#ifdef  TSH
#undef  TSH
#endif

#define TSH(x)                              TAUB0##x                                // !search more strings 'TAUB0' for specific changes!

//#define TSP_CKS                           0x6420                                  // prescaling TAUB0 - already configured!
#define TSP_MODE                            0xC000                                  // TAUB08/k/g mode
#define TSH_MODE                            0xC000                                  // TAUB08/k/g mode



//=============================================================================
// prototypes
//=============================================================================

uint32 CddStpPrjLwr_CalcRemainingTicks(/*boolean boHsMode, */uint32 ulBufferIndexNow/*, volatile uint16* punDtc*/);


//=============================================================================
// externals
//=============================================================================

extern uint8 CddStp8899_ucDummy; // suppress LINT warnings


//=============================================================================
// variables
//=============================================================================

extern tStpInfo CddStp88XX_HalStp_StpInfoLwr;
extern tStpInfo CddStp88XX_HalStp_StpInfoKl;
extern tStpInfo CddStp88XX_HalStp_StpInfoGlw;


//=============================================================================
// interfaces
//=============================================================================

// calculate by rounding time duration according to stepper timer timebase (input in microseconds)
INLINE uint32 ST_R_USEC(uint32 ulTime);
INLINE uint32 ST_R_USEC(uint32 ulTime) { return ((uint32) ((ulTime * CDDSTP88XX_HALSTP_TimeBaseFreq) / 1024)); }



//CddStpPrj_AddTimerOffset() --------------------------------------------------
INLINE void CddStpPrj_AddTimerOffset(uint32 ulIx, uint32* pulVal)
{
  // timer is reset to 0 after each start: do not add
  (void)ulIx;
  (void)pulVal;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief  Interface function to get CDDSTP module internal bits of steppers
///
/// \descr  Get pointer to constant structure
///         This function is available for onboard steppers
///
/// \param  uint8 ucIx
///
/// \return pointer
///
/* ...? */ INLINE const tCddStp88XXBitsMod* CddStp88XX_GetBitsMod(const uint8 ucIx);
/* ...? */ INLINE const tCddStp_Bits* CddStp88XX_GetBits(const uint8 ucIx);
INLINE const tCddStp_Bits* CddStp_GetBits(const uint8 ucIx)
{
  return CddStp88XX_GetBits(ucIx);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief  Interface function to get CDDSTP attribute configuration of steppers
///
/// \descr  Get pointer to constant structure
///         This function is available for onboard steppers
///
/// \param  uint8 ucIx
///
/// \return pointer
///
INLINE const tCddStp_Attr* CddStp_GetAttr(const uint8 ucIx)
{
  // jk: 'tCddStp88XX_Attr'/'tCddStp_Attr' is ONLY about 'PSenes'
  return CddStp88XX_GetAttr(ucIx);
}

//=============================================================================
// prototypes
//=============================================================================

void      CddStpPrj_SetEventFinishMove(uint8 ucIx);

uint8 returnval(void);
void setval(void);

#endif // __CDDSTPPRJ_H__
