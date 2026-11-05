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
/// \file   CddStpPrj.c
///
/// \brief  Contains the project specific MCU functionality interfaces of stepper
///
/// \author Wuesteney, Ulrich ALRT/EEG-PM2 * (wu82rt)
///         mailTo:ulrich.wuesteney(at)al-lighting.com       
///         J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL

#include <CddStpIfc.h>

#include <Cfg/Cfg.h>
#include <stddef.h>
#include <string.h>
//#include <interrupt_manager.h>
#include <UtilUtility.h>
#include <../Cdd/CddStp/CddStp_Tsp.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <CddStpPrj.h>
#else // Unit-Tests!
//  #define CFA_CNT_STP_88XX   (4u)
  #include <CddStpPrj.h>
#endif
static volatile uint8 boIntEnb = 0;

//=============================================================================
// constants
//=============================================================================


//=============================================================================
// external functions
//=============================================================================


//=============================================================================
// external variables
//=============================================================================


//=============================================================================
// variables
//=============================================================================


//=============================================================================
// functions
//=============================================================================

//CddStpPrjXxx_GetTshCnt() --------------------------------------------------
// jk-obsolet - currently not used: INLINE uint32 CddStpPrjLwr_GetTshCnt(void)
// jk-obsolet - currently not used: {
// jk-obsolet - currently not used:   // jk-tbd return TSH(CNT10);               // LWR timer help channel 10
// jk-obsolet - currently not used:   return CddStp_Tsp_GetTicks(0); // jk-tbd // UWY: !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! jk please check, whether this is HS time - GetStepCnt()!!!!!!!!!!!!!!!!!!!!!!!!
// jk-obsolet - currently not used: }


uint32 CddStpPrjLwr_CalcRemainingTicks(/*boolean boHsMode, */uint32 ulBufferIndexNow/*, volatile uint16* punDtc*/) // jk-tbd // UWY !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! only for step timer !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
  uint32 ulPulseTime = CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferIndexNow].Val.unHsTime;
  uint32 ulRemainingTicks = 0;
  uint32 ulTspCnt    = CddStp_Tsp_GetTicks(0);                     // actual TSP timer count LWR // UWY: !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! jk please check, whether this is HS time - GetStepCnt()!!!!!!!!!!!!!!!!!!!!!!!!

//if (boHsMode != FALSE){} // parameter not used

//if (boHsMode)                                                     // HS
//{
//}
//else                                                              // us
  {
    ulRemainingTicks = ulPulseTime - ulTspCnt; // UWY: !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! jk please check, whether this is HS time - GetStepCnt()!!!!!!!!!!!!!!!!!!!!!!!!
  }
  return ulRemainingTicks;
}


// ---------------------------------------------------------------------------
///
///  \func     CddStpPrj_SetEventFinishMove
///
///  \brief    Set event FinishMove
///
///  \param    uint8 ucIx
///
///  \return   none
///
///  \descr    Set event flag bit FinishMove and activate event, but not in case of CddStp88XX state StateInit
///
// ---------------------------------------------------------------------------
void CddStpPrj_SetEventFinishMove(uint8 ucIx)
{
  tisTrigger0         Trigger = { 0U /*SIG_SNA*/ };

  if (CddStp88XX_aeState[ucIx] != CddStp88XX_eStateInit)
  {
    CddStp88XX_aEventBits[ucIx].Bit.biFinishMove = 1;    // synchronize CddStp88XX state machine to react immediately in case of first positive slope while reference run

    switch (ucIx)
    {
    #if(CFA_CNT_STP_ONBRD >= 1)
      case (uint8)CddStpPrj_eDrvIxVer:
        (void)Trigger;
        (void)ucIx; // jk-tbd ****************** (void)Rte_Write_StpEvent0_sTrigger_Port(&Trigger); ******************        
        break;
    #endif

    default:
      break;
    }
  }
}


//extern "C" 
// PRQA S 3408 1 // interrupt function handler defined at assembly level 
void LPIT0_Ch0_IRQHandler(void)
{

  CddStp_Tsp_ResetFlag(0u);
  
  // calls state machine
  CddStp88XX_HalStpVer_TimerCb();
  
}

// jk-obsolet // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// jk-obsolet // Interrupt service functions
// jk-obsolet // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// jk-obsolet 
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet ///
// jk-obsolet ///  \func   StpIsrTimer_Ver !!!TSP timer!!!
// jk-obsolet ///
// jk-obsolet ///  \brief  Interrupt service routine timer stepping clock VER
// jk-obsolet ///
// jk-obsolet ///  \descr
// jk-obsolet ///
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet #if(CFA_CNT_STP_ONBRD >= 1)
// jk-obsolet 
// jk-obsolet //Lr06 #define ISR(x) void x##func(void)
// jk-obsolet //Lr06  ISR(StpIsrTimer_Ver)
// jk-obsolet   #if ( TYP_OS == RH850_F1L )
// jk-obsolet   void INTTAUB0I8func(void)
// jk-obsolet   #else
// jk-obsolet     __interrupt void INTTAUB0I8(void)
// jk-obsolet   #endif
// jk-obsolet   {
// jk-obsolet     CddStp88XX_HalStpVer_TimerCb(); // calls 'CddStp88XX_HalStpLwr_StateMachine(CddStp88XX_HalStp_eCmdIsrStp);'
// jk-obsolet   }
// jk-obsolet 
// jk-obsolet #endif
// jk-obsolet 
// jk-obsolet 
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet ///
// jk-obsolet ///  \func   StpIsrTimerHelp_Ver
// jk-obsolet ///
// jk-obsolet ///  \brief  Interrupt service routine timer stepping help VER
// jk-obsolet ///
// jk-obsolet ///  \descr
// jk-obsolet ///
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet #if(CFA_CNT_STP_ONBRD >= 1)
// jk-obsolet 
// jk-obsolet //Lr06 #define ISR(x) void x##func(void)
// jk-obsolet //Lr06  ISR(StpIsrTimerHelp_Ver)
// jk-obsolet   #if ( TYP_OS == RH850_F1L )
// jk-obsolet   void INTTAUB0I10func(void)
// jk-obsolet   #else
// jk-obsolet     __interrupt void INTTAUB0I10(void)
// jk-obsolet   #endif
// jk-obsolet   {
// jk-obsolet     CddStp88XX_HalStpVer_TimerHelpCb();
// jk-obsolet   }
// jk-obsolet 
// jk-obsolet #endif
// jk-obsolet 
// jk-obsolet 
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet ///
// jk-obsolet ///  \func   StpIsrErrn_Ver
// jk-obsolet ///
// jk-obsolet ///  \brief  Interrupt service routine ERRN for Ver DRV70521 error handling
// jk-obsolet ///
// jk-obsolet ///  \descr
// jk-obsolet ///
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet #if(CFA_CNT_STP_ONBRD >= 1)
// jk-obsolet 
// jk-obsolet //Lr06  ISR(StpIsrErrn_Ver)
// jk-obsolet   #if ( TYP_OS == RH850_F1L )
// jk-obsolet       void INTP4func(void)
// jk-obsolet   #else
// jk-obsolet     __interrupt void INTP4(void)
// jk-obsolet   #endif
// jk-obsolet   {
// jk-obsolet     CddStp88XX_HalStpVer_ErrnCb();
// jk-obsolet   }
// jk-obsolet 
// jk-obsolet #endif
// jk-obsolet 
// jk-obsolet 
// jk-obsolet 
// jk-obsolet 
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet ///
// jk-obsolet ///  \func   StpIsrTimerHelp_Hor
// jk-obsolet ///
// jk-obsolet ///  \brief  Interrupt service routine timer stepping help HOR
// jk-obsolet ///
// jk-obsolet ///  \descr
// jk-obsolet ///
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet #if(CFA_CNT_STP_ONBRD >= 1)
// jk-obsolet 
// jk-obsolet //Lr06 #define ISR(x) void x##func(void)
// jk-obsolet //Lr06  ISR(StpIsrTimerHelp_Hor)
// jk-obsolet   #if ( TYP_OS == RH850_F1L )
// jk-obsolet   void INTTAUB0IKfunc(void)
// jk-obsolet   #else
// jk-obsolet     __interrupt void INTTAUB0IK(void)
// jk-obsolet   #endif
// jk-obsolet   {
// jk-obsolet     // CddStp88XX_HalStpHor_TimerHelpCb();
// jk-obsolet   }
// jk-obsolet 
// jk-obsolet #endif
// jk-obsolet 
// jk-obsolet 
// jk-obsolet 
// jk-obsolet 
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet ///
// jk-obsolet ///  \func   StpIsrTimerHelp_Sht
// jk-obsolet ///
// jk-obsolet ///  \brief  Interrupt service routine timer stepping help SHT
// jk-obsolet ///
// jk-obsolet ///  \descr
// jk-obsolet ///
// jk-obsolet // ---------------------------------------------------------------------------
// jk-obsolet #if(CFA_CNT_STP_ONBRD >= 1)
// jk-obsolet 
// jk-obsolet //Lr06 #define ISR(x) void x##func(void)
// jk-obsolet //Lr06  ISR(StpIsrTimerHelp_Ver)
// jk-obsolet   #if ( TYP_OS == RH850_F1L )
// jk-obsolet   void INTTAUB0IGfunc(void)
// jk-obsolet   #else
// jk-obsolet     __interrupt void INTTAUB0IG(void)
// jk-obsolet   #endif
// jk-obsolet   {
// jk-obsolet     // CddStp88XX_HalStpSht_TimerHelpCb();
// jk-obsolet   }
// jk-obsolet 
// jk-obsolet #endif

//EOF
