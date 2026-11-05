//
// To-Be-Done
// search for: 
//     * jk-tbd
//     * jk-tbd-HW
//     * jk-obsolet    -> original HCM-Code not needed any longer
//     * jk-orig       -> original/previous HCM-Code
//

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
/// \file  CddStp8899_HalStp.c
///
/// \brief  LWR stepping clock generation
///
/// \descr  Generation of stepping clocks at pins of the Texas Instruments TI-DRV8899 LWR
///         by use of three timer compare registers.
///         One compare match interrupt is used of LWR.
///         The ISR functions work with state machines.
///
///         HAL-Stp - States and possible State-Transitions
///           * Init       ->  HoldCont
///           * FirstStep  ->  LastStep or Step
///           * LastStep   ->  StepHold
///           * Step       ->  LastStep
///           * Hold       ->  HoldCont
///           * HoldCont   ->  TestStep or FirstStep
///           * TestStep   ->  HoldCont
///
///         Timer:
///          CddStp_Tsp_Start(0, count);   // Stepper-Timer: HW-Pin-Toggling With u-Steps
///          Gpt_StartTimer(  0, count);   // Help-Timer:    IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'
///
///
///         Due to problems with LWR-DMA the HCM-Implementation ('70516'!) uses no DMA (previous used DMA-Code was with '70514' -> '70514' is 'clumsy' for FLM3 but used as base)
///         
///         This files is based on '70514': Bad, because DMA ist used
///         '70516' would have been better because it is based on Help-Timer (IRQ etc.)
///
///         70514: LWR with DMA           - this whole code below  -> clumsy
///         70516: Problems with LWR-DMA  - therefore no DMA       -> better Code (including 'CddStp705XX_HalStpLwr_GetIrunTimeEd' & 'CddStp705XX_HalStp_ulIrunTimeLwrEd')
///
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL

#include <Util_Time.h>

#include <CddSpi.h>

#include <UtilBase_Atomic.h>

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <../../Cust/St/St126/Cdd/CddStp/CddStpPrj.h>
#include <../App/Bsw/IoHwAb/IoHwAbUser.h>
#include <interrupt_manager.h>
  #include <CddStpData.h>
#else // Unit-Tests!
  #define CFG_Drv_None             1U
  #define CFG_Drv_Default          2U
  #define CFG_DRV_STP_LWR          CFG_Drv_Default
  #define CFG_DRV_STP_KL           CFG_Drv_None
  #define CFG_DRV_STP_GLW          CFG_Drv_None
  #define CFA_CNT_STP_88XX         (4u)
  #define CFG_Stp_IdxVer           (0u)   // Index  of Vertical   Stepper

  uint32 CddStp_UnitTestHelper_ul1;
  uint32 CddStp_UnitTestHelper_ul2;
  boolean CddStp_UnitTestHelper_bo1;
  boolean CddStp_UnitTestHelper_bo2;

  #include <CddStpPrj.h>
  #include <CddStpData.h>
#endif

#include <8899/CddStp8899Cfg.h>
#include <8899/CddStp8899Types.h>
#include <88XX/CddStp88XX_FctTables.h>
#include <88XX/CddStp88XX_HalStp.h>


// ---------------------------------------------------------------------------
// preprocessor definitions
// ---------------------------------------------------------------------------

#define CDDSTP88XX_HALSTP_TestStepCntMax         (6u)                          // count of test steps (see buffer test step initialisation)
#define CDDSTP88XX_HALSTP_TestStepSr3ReadMax     (7u)                          // count of test step 1

#define CDDSTP88XX_HALSTP_SCCntMax               (1u)                          // SC counter: max. count of sequenced set of DRV88XX OverCurrent error bits (SC)    !=1 because DRV88XX (!) stops stepper motor! -> counter is used as flag
#define CDDSTP88XX_HALSTP_OLCntMaxHS             (2u)                          // OL counter: max. count of sequenced set of DRV88XX OL error bit in half step mode  >1 because DRV88XX not stops stepper motor //HS
#define CDDSTP88XX_HALSTP_OLCntMaxMS             (2u)                          // OL counter: max. count of sequenced set of DRV88XX OL error bit in half micro mode >1 because DRV88XX not stops stepper motor //HS

#define CDDSTP88XX_HALSTP_MaxTimerVal            (0x3FFFFFFFu)                 // maximal timer CDR value

#define CDDSTP88XX_HALSTP_ErrVoltDefault         (13000u)                      // default value of the voltage stored in Err-ISR [mV]
#define CDDSTP88XX_STEPPERIDX                    (0u)                          // index of stepper motor


#if ((CFG_DRV_STP_LWR == CFG_Drv_Default) || (CFG_DRV_STP_KL == CFG_Drv_Default) || (CFG_DRV_STP_GLW == CFG_Drv_Default))

  // ---------------------------------------------------------------------------
  // preprocessor definitions
  // ---------------------------------------------------------------------------
  // --- Status registers 0, 1, 2 bit 0 and 1 should be zero (AMIS requirement)
  #define CDDSTP88XX_HALSTP_SPI_SR0_2Bit0_1_MSK (0x03)

  #define CDDSTP88XX_HALSTP_SPI_SOM_MAX       (5u)                             // max. count for sending same SPI register once more  = 6 in case of CReg0...2;  = 12 in case of SReg1...8A because of 32 bit SPI (2 * (2 * 8 Bit))

  #define CDDSTP88XX_HALSTP_HIWORD            (16u)                            // bit shift count to create high word (16 bit)

  #define CDDSTP88XX_HALSTP_RT_MIN            ST_R_USEC(1000u)                 //  1000 us              minimum remaining ticks

//#define TSPIN_FREQUENCY                      (500000u)

  #define TSP_IOC4DELAY                        (1u)                             // minimum compare match delay
  #define CDDSTP88XX_HALSTP_INIT              (ST_R_USEC(1500u))               //  1500 us init               count
  #define CDDSTP88XX_HALSTP_HOLD              (ST_R_USEC(500u))                //   500 us hold               count
//#define CDDSTP88XX_HALSTP_PULSE             (ST_R_USEC(150u))                //   150 us pulse (min. 2 us)  count - consider TSP_IOC4DELAY!
  #define CDDSTP88XX_HALSTP_TESTSTEP          (ST_R_USEC(20000u))              //  TestSteps 0, 1:            (20 ms * 2) = 40 ms > ( (32 ms) - DRV88XX recommended to check OpenCoil + (40 ms)
  #define CDDSTP88XX_HALSTP_TESTSTEPSPI       (ST_R_USEC(15000u))              //  TestSteps 2, 3, 4, 5, 6:   (15 ms * (CDDSTP88XX_HALSTP_TestStepSr3ReadMax - 2)) = 75 wait time for SPI read of SReg3 (note: wait till maximal schedule table requirements for other registers are done!)

  // HalStp bits - task level
  // PRQA S 635 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 635([E] Bit-fields in this struct/union have been declared with types other than int, signed int or unsigned int.) Depth: 0 Ref: MISRA C:2012 Rule-1.2, Rule-6.1; REFERENCE - ISO:C90-6.5.2.1 Structure and Union Specifiers - Semantics
  typedef struct
  {
    uint16  biInit              : 1; //  0: HalStp is initialized
    uint16  biTestStep          : 1; //  1: test step
    uint16  biTestStepDone      : 1; //  2: test step done
    uint16  biStopStpPZ         : 1; //  3: stop stepper profile zero (not motor enable !MotEn) - stored in case of stop while movement
    uint16  biStopStp           : 1; //  4: stop stepper
    uint16  biHsMode            : 1; //  5: half step mode
    uint16  biReserved          : 2; //  6: reserved
    uint16  biMotEn             : 1; //  8: motor enable                                                       // only used for DRV88XX
    uint16  biDriverReset       : 1; //  9: driver reset       - detected by missing SPI communication         // only used for DRV88XX
// orig.: uint16  biReserved6   : 6; // 10: reserved
    uint16  biTbdClrTiFaultBits : 1; // 10: CTRL4 Bit7: CLR_FLT - Write '1' to this bit to clear all latched fault bits. This bit automatically resets after being written.
//  uint16  biReserved5         : 5; // 11: reserved
    uint16  biTbdEnOlDtctn      : 1; // 11: Enable Open-Load-Detection
    uint16  biReserved4         : 4; // 12: reserved
  }tHSBits;

  typedef union
  {
    tHSBits Bit;     ///< bit signal access
    uint16  unRaw;   ///< raw signal access
  } tHalStpBits;


  #if(CFG_DRV_STP_LWR == CFG_Drv_Default)



  // /*jk-moved-from-h-inline*/ CddStpPrj_TSPInit() --------------------------------------------------
  STATIC_AL uint32 CddStp8899_HalStp_AvoidMisraWarning;
  STATIC_AL void CddStpPrj_TSPInit(void)
  {
    // jk-tbd: Do we need this fct?

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
    // jk-obsolet: avoid MISRA-/QAC-Warnings
    CddStp8899_HalStp_AvoidMisraWarning++;
    if (CddStp8899_HalStp_AvoidMisraWarning > 5u)
    {
      CddStp8899_HalStp_AvoidMisraWarning--;
    }
#else // Unit-Tests!
    extern boolean CddStp_UnitTest__TspIsIni;
    extern boolean CddStp_UnitTest__TspIsRunning;
    CddStp_UnitTest__TspIsIni = TRUE;
    CddStp_UnitTest__TspIsRunning = FALSE;
#endif
  }


  // /*jk-moved-from-h-inline*/ CddStpPrj_TSPDeinit() --------------------------------------------------
  STATIC_AL void CddStpPrj_TSPDeinit(void)
  {
    // jk-tbd: Do we need this fct?

    // TSP configuration timer outputs LWR, KL and GLW
// jk-obsolet #if (CFG_DRV_STP_LWR == CFG_Drv_Default)
// jk-obsolet #pragma diag_suppress 1626 /* GHS warning 1626-D: concatenation with "TAUB0" in macro "MCU_B16" does not create a valid token */
// jk-obsolet     // jk-tbd-HW-01     MCU_BIT(TSP(TT), 8) = 1;   // stop timer LWR - channel 8
// jk-obsolet #endif

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
    // jk-obsolet: avoid MISRA-/QAC-Warnings
    CddStp8899_HalStp_AvoidMisraWarning++;
    if (CddStp8899_HalStp_AvoidMisraWarning > 5u)
    {
      CddStp8899_HalStp_AvoidMisraWarning--;
    }
#else // Unit-Tests!
    extern boolean CddStp_UnitTest__TspIsIni;
    extern boolean CddStp_UnitTest__TspIsRunning;
    CddStp_UnitTest__TspIsIni = FALSE;
    CddStp_UnitTest__TspIsRunning = FALSE;
#endif
  }


  // /*jk-moved-from-h-inline*/ CddStpPrjXxx_StartHelp() --------------------------------------------------
  STATIC_AL void CddStpPrjLwr_GPT_StartHelp(uint32 ulCount)
  {
    // Due to problems with LWR-DMA the HCM-Implementation ('70516'!) uses no DMA (previous used DMA-Code was with '70514' -> '70514' is 'clumsy' for FLM3 but used as base)
    //
    // Timer:
    //  CddStp_Tsp_Start(0, count);   // Stepper-Timer: HW-Pin-Toggling With u-Steps
    //  Gpt_StartTimer(  0, count);   // Help-Timer:    IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'

    CddStp_Tsp_StopHelpTmr(0); // just to be sure
    CddStp_Tsp_StartHelpTimer(0, ulCount); // IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'
  }


  STATIC_AL volatile uint32 CddStp8899_HalStp__DUMMY__TimerCount_GPT;
  STATIC_AL volatile uint32 CddStp8899_HalStp__DUMMY__TimerCount_TSP;
  // /*jk-moved-from-h-inline*/ CddStpPrjLwr_BothTimers_Prepare() --------------------------------------------------
  STATIC_AL void CddStpPrjLwr_BothTimers_Prepare(uint32 ulTimerCount_GPT, uint32 ulTimerCount_TSP)
  {
    // jk-tbd!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    CddStp8899_HalStp__DUMMY__TimerCount_GPT = ulTimerCount_GPT;
    CddStp8899_HalStp__DUMMY__TimerCount_TSP = ulTimerCount_TSP;

    CddStp_Tsp_Stop(0); // just to be sure
    CddStp_Tsp_StopHelpTmr(0);   // just to be sure
  }


  // /*jk-moved-from-h-inline*/ CddStpPrjLwr_BothTimers_Start() --------------------------------------------------
  STATIC_AL void CddStpPrjLwr_BothTimers_Start(void)
  {
  
    /* Disable the global interrupt */
    DISABLE_INTERRUPTS();
    // Timer:
    //  CddStp_Tsp_Start(0, count);   // Stepper-Timer: HW-Pin-Toggling With u-Steps
    //  Gpt_StartTimer(  0, count);   // Help-Timer:    IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'

    CddStp_Tsp_StartHelpTimer(  0u,         CddStp8899_HalStp__DUMMY__TimerCount_GPT);   // IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'
    CddStp_Tsp_Start(0u, (uint16)CddStp8899_HalStp__DUMMY__TimerCount_TSP);   // Stepper-Timer with u-Steps

                                                          // reset!
    CddStp8899_HalStp__DUMMY__TimerCount_GPT = 0u;
    CddStp8899_HalStp__DUMMY__TimerCount_TSP = 0u;

    /* Enable the global interrupt*/
    ENABLE_INTERRUPTS();

  }


  // /*jk-moved-from-h-inline*/ CddStpPrjXxx_ForceTimerLow() --------------------------------------------------
  STATIC_AL void CddStpPrjLwr_TSP_ForceTimerLow(void)
  {
    CddStp_Tsp_Stop(CDDSTP88XX_STEPPERIDX); // =Step-Clock-Timer (without IRQ)
  }


  // /*jk-moved-from-h-inline*/ CddStpPrjXxx_GetTshCnt() --------------------------------------------------
  STATIC_AL uint32 CddStpPrjLwr_GPT_GetRemainingCnt(void) // UWY
  {
    return CddStp_Tsp_GetTicks(CDDSTP88XX_STEPPERIDX); // UWY
  }




  
    STATIC_AL void             CddStp88XX_HalStpLwr_SetActPos_         (const sint32 ln);
    STATIC_AL void             CddStp88XX_HalStpLwr_IncActPos_         (const sint32 ln);
    STATIC_AL sint32           CddStp88XX_HalStpLwr_GetActPos_         (void);
    STATIC_AL uint8            CddStp88XX_HalStpLwr_GetPhaseCounter_   (void);
    STATIC_AL tStpInfo*        CddStp88XX_HalStpLwr_GetStpInfo_        (void);
    STATIC_AL void             CddStp88XX_HalStpLwr_HandleMotEn_       (boolean boMotEn, boolean boSendCReg12);
    STATIC_AL void             CddStp88XX_HalStpLwr_StopStp_           (boolean boMotEn);

    STATIC_AL boolean          CddStp88XX_HalStpLwr_SpiSendCReg0       (boolean boSend); // Dummy
    STATIC_AL boolean          CddStp88XX_HalStpLwr_SpiSendCReg1       (boolean boSend);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_SpiSendCReg2       (boolean boSend);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_SpiSendCReg3       (boolean boSend);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_SpiSendCReg4       (boolean boSend);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_SpiSendCRegAll     (void);
//  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
//  STATIC_AL boolean          CddStp88XX_HalStpLwr_SpiSendSReg0       (void); // Dummy
    STATIC_AL boolean          CddStp88XX_HalStpLwr_IsDriverReset      (void); // DRV88XX specific
    STATIC_AL void             CddStp88XX_HalStpLwr_ClrDriverReset     (void); // DRV88XX specific
    STATIC_AL void             CddStp88XX_HalStpLwr_SetDriverReset     (void); // DRV88XX specific

    STATIC_AL tStpInfo*        CddStp88XX_HalStpLwr_GetStpInfo         (void);
    STATIC_AL uint32           CddStp88XX_HalStpLwr_GetWriteIx         (sint32* plActPos, uint32* pulRemainingTicks);

    STATIC_AL void             CddStp88XX_HalStpLwr_SetActPos          (const sint32 ln);
    STATIC_AL void             CddStp88XX_HalStpLwr_IncActPos          (const sint32 ln);
    STATIC_AL sint32           CddStp88XX_HalStpLwr_GetActPos          (void);
    STATIC_AL uint8            CddStp88XX_HalStpLwr_GetPhaseCounter    (void);

    STATIC_AL boolean          CddStp88XX_HalStpLwr_IsFinishMove       (void);

    STATIC_AL void             CddStp88XX_HalStpLwr_HandleMotEn        (boolean boMotEn, boolean boSendCReg12);
    STATIC_AL void             CddStp88XX_HalStpLwr_HandleCurAmplt     (uint8 ucCurAmpltState, uint8 ucCurAmpltHold, uint8 ucCurAmpltRun);
    STATIC_AL uint8            CddStp88XX_HalStpLwr_GetCurAmplt        (void);

    STATIC_AL void             CddStp88XX_HalStpLwr_StartStp           (void);
    STATIC_AL void             CddStp88XX_HalStpLwr_ResetStp           (boolean boMotEn);
    STATIC_AL void             CddStp88XX_HalStpLwr_StopStp            (boolean boMotEn);

    STATIC_AL boolean          CddStp88XX_HalStpLwr_GetPsensPort       (void);

    STATIC_AL uint32           CddStp88XX_HalStpLwr_GetErrVolt         (void);
    STATIC_AL void             CddStp88XX_HalStpLwr_ResetErrVolt       (void);

    STATIC_AL boolean          CddStp88XX_HalStpLwr_SetTestStep        (boolean boResetTestStepDone);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_IsTestStepDone     (void);
    STATIC_AL void             CddStp88XX_HalStpLwr_ResetTestStepCnt   (void);

    STATIC_AL void             CddStp88XX_HalStpLwr_ClrOLCnt           (void);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_IncOLCnt           (void);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_IsOLCntMax         (void);

    STATIC_AL void             CddStp88XX_HalStpLwr_ClrSCCnt           (void);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_IncSCCnt           (void);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_IsSCCntMax         (void);

    STATIC_AL uint32           CddStp88XX_HalStpLwr_GetHsCnt           (void);
    STATIC_AL void             CddStp88XX_HalStpLwr_SetCARunRefCnt     (uint8 ucCntVal);
    STATIC_AL uint32           CddStp88XX_HalStpLwr_GetIrunTime        (void);
    
    STATIC_AL boolean          CddStp88XX_HalStpLwr_Init               (boolean boInit);

    STATIC_AL boolean          CddStp88XX_HalStpLwr_SetHsMode          (boolean boHsMode, uint8 ucCurAmpltRun);
    STATIC_AL boolean          CddStp88XX_HalStpLwr_GetHsMode          (void);

  #endif



  #define CDDSTP88XX_HALSTP_FCT_LIST_LWR     \
  {                                          \
    CddStp88XX_HalStpLwr_SpiSendCReg0,       \
    CddStp88XX_HalStpLwr_SpiSendCReg1,       \
    CddStp88XX_HalStpLwr_SpiSendCReg2,       \
    CddStp88XX_HalStpLwr_SpiSendCReg3,       \
    CddStp88XX_HalStpLwr_SpiSendCReg4,       \
    CddStp88XX_HalStpLwr_SpiSendCRegAll,     \
/*  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden */ \
/*  CddStp88XX_HalStpLwr_SpiSendSReg0,   */  \
    CddStp88XX_HalStpLwr_IsDriverReset,      \
    CddStp88XX_HalStpLwr_ClrDriverReset,     \
    CddStp88XX_HalStpLwr_SetDriverReset,     \
                                             \
    CddStp88XX_HalStpLwr_GetStpInfo,         \
    CddStp88XX_HalStpLwr_GetWriteIx,         \
                                             \
    CddStp88XX_HalStpLwr_SetActPos,          \
    CddStp88XX_HalStpLwr_IncActPos,          \
    CddStp88XX_HalStpLwr_GetActPos,          \
    CddStp88XX_HalStpLwr_GetPhaseCounter,    \
                                             \
    CddStp88XX_HalStpLwr_IsFinishMove,       \
                                             \
    CddStp88XX_HalStpLwr_HandleMotEn,        \
    CddStp88XX_HalStpLwr_HandleCurAmplt,     \
    CddStp88XX_HalStpLwr_GetCurAmplt,        \
                                             \
    CddStp88XX_HalStpLwr_StartStp,           \
    CddStp88XX_HalStpLwr_ResetStp,           \
    CddStp88XX_HalStpLwr_StopStp,            \
                                             \
    CddStp88XX_HalStpLwr_GetPsensPort,       \
                                             \
    CddStp88XX_HalStpLwr_GetErrVolt,         \
    CddStp88XX_HalStpLwr_ResetErrVolt,       \
                                             \
    CddStp88XX_HalStpLwr_SetTestStep,        \
    CddStp88XX_HalStpLwr_IsTestStepDone,     \
    CddStp88XX_HalStpLwr_ResetTestStepCnt,   \
                                             \
    CddStp88XX_HalStpLwr_ClrOLCnt,           \
    CddStp88XX_HalStpLwr_IncOLCnt,           \
    CddStp88XX_HalStpLwr_IsOLCntMax,         \
                                             \
    CddStp88XX_HalStpLwr_ClrSCCnt,           \
    CddStp88XX_HalStpLwr_IncSCCnt,           \
    CddStp88XX_HalStpLwr_IsSCCntMax,         \
                                             \
    CddStp88XX_HalStpLwr_GetHsCnt,           \
    CddStp88XX_HalStpLwr_SetCARunRefCnt,     \
    CddStp88XX_HalStpLwr_GetIrunTime,        \
                                             \
    CddStp88XX_HalStpLwr_Init,               \
                                             \
    CddStp88XX_HalStpLwr_SetHsMode,          \
    CddStp88XX_HalStpLwr_GetHsMode           \
  }

#endif


// ---------------------------------------------------------------------------
// const
// ---------------------------------------------------------------------------
#if (CFG_DRV_STP_GLW == CFG_Drv_Default)
  #error Unsupported kind of stepper (1)

#elif (CFG_DRV_STP_KL == CFG_Drv_Default)
  #error Unsupported kind of stepper (2)
#elif (CFG_DRV_STP_LWR == CFG_Drv_Default)

  // jk-orig:  const tCddStp88XX_HalStpFct CddStp88XX_HalStpFct[] = { CDDSTP88XX_HALSTP_FCT_LIST_LWR };
  #if(CFA_CNT_STP_88XX == 4)
    const tCddStp88XX_HalStpFct CddStp88XX_HalStpFct[] = { CDDSTP88XX_HALSTP_FCT_LIST_LWR, CDDSTP88XX_HALSTP_FCT_LIST_LWR, CDDSTP88XX_HALSTP_FCT_LIST_LWR, CDDSTP88XX_HALSTP_FCT_LIST_LWR };
  #else
    //#error Unsupported number of stepper
    const tCddStp88XX_HalStpFct CddStp88XX_HalStpFct[] = { CDDSTP88XX_HALSTP_FCT_LIST_LWR };
  #endif

#else
#error Unsupported kind of stepper (3)
#endif


// ---------------------------------------------------------------------------
// vars
// ---------------------------------------------------------------------------

    STATIC_AL uint8 CddStp88XX_HalStp_aucSPI_TX[CFA_CNT_STP_88XX][CddStp88XX_HalStp_eRegBSize]; // SPI TX buffer which contents raw register values to transmit

#if (CFG_DRV_STP_LWR == CFG_Drv_Default)

  STATIC_AL tStateHalStp            CddStp88XX_HalStp_eStateLwr;  // = CddStp88XX_HalStp_eStateInit, anyway init to 0 in start up code.
  STATIC_AL tHsInfo                 CddStp88XX_HalStp_HSInfoBufSaveLwr;
  STATIC_AL uint32                  CddStp88XX_HalStp_ulHsCntLwr;
  STATIC_AL uint32                  CddStp88XX_HalStp_ulSet0Lwr;  // debug only, should never be incremented!
//STATIC_AL uint8                   CddStp88XX_HalStp_ucCARunRefCntLwr;
  STATIC_AL uint32                  CddStp88XX_HalStp_ulIrunTimeLwr;
  STATIC_AL uint8                   CddStp88XX_HalStp_ucPhaseCounterLwr;
  STATIC_AL uint8                   CddStp88XX_HalStp_ucStepModeLwr;
// jk-obsolet: No HS-Mode...:       CddStp88XX_HalStp_ucStepModeOldLwr;
  STATIC_AL uint8                   CddStp88XX_HalStp_ucCurAmpltLwr;
  STATIC_AL uint8                   CddStp88XX_HalStp_ucCurAmpltOldLwr;
//STATIC_AL uint8                   CddStp88XX_HalStp_ucCurAmpltHoldLwr;
//STATIC_AL uint8                   CddStp88XX_HalStp_ucCurAmpltRunLwr;
//STATIC_AL tCurAmpltStateCddStp88XX  CddStp88XX_HalStp_eCurAmpltStateLwr;

  tStpInfo                          CddStp88XX_HalStp_StpInfoLwr;

  STATIC_AL uint16                  CddStp88XX_HalStp_unErrVoltLwr;

  STATIC_AL uint8                   CddStp88XX_HalStp_ucOLCntLwr;
  STATIC_AL uint8                   CddStp88XX_HalStp_ucSCCntLwr;

  STATIC_AL uint32                  CddStp88XX_HalStp_ulTestStepCntLwr;
// jk-obsolet: currently not used:  CddStp88XX_HalStp_ucTestStepSr3ReadNotOkCntLwr;

  STATIC_AL tHalStpBits             CddStp88XX_HalStp_BitsLwr;
  STATIC_AL tHalStpBitsInt          CddStp88XX_HalStp_BitsIntLwr;

  #if(CFG_OPT_STATISTIC & CFG_Statistic_ExtendedStpLwr)
  STATIC_AL TIMER                   CddStp88XX_HalStp_MovementTimestampLwr;
  STATIC_AL uint8                   CddStp88XX_HalStp_ucCycleHsCntLwr;
  STATIC_AL uint8                   CddStp88XX_HalStp_aucCyclesLwr[8];
  #endif

#endif


// ---------------------------------------------------------------------------
// local prototypes
// ---------------------------------------------------------------------------

// ok: STATIC_AL void   CddStp8899_HalStp_SetDIR(boolean b) { IoHwAb_SetDo(DioConf_DioChannel_DioChannel_0_0_ST_DIR_LWR, b); } // jk-tbd: 'Rte_Call_ppIoHwAbUserSetDirLwr0_IoHwAbUser_SetDirLwr' / 'ppIoHwAbUserSetDirLwr0'
  STATIC_AL void CddStp8899_HalStp_SetDIR(boolean boDir) { (void)IoHwAbUser_SetDirLwr(boDir); } // jk-tbd: 'Rte_Call_ppIoHwAbUserSetDirLwr0_IoHwAbUser_SetDirLwr' / 'ppIoHwAbUserSetDirLwr0'

#if ((CFG_DRV_STP_LWR == CFG_Drv_Default) || (CFG_DRV_STP_KL == CFG_Drv_Default) || (CFG_DRV_STP_GLW == CFG_Drv_Default))

STATIC_AL void                    CddStp88XX_HalStp_InitBuffer                      (tStpInfo* pStpInfo);

  #if (CFG_DRV_STP_LWR == CFG_Drv_Default)

STATIC_AL void           CddStp88XX_HalStpLwr_EmptyBuffer                  (void);
STATIC_AL boolean        CddStp88XX_HalStpLwr_SendCReg1                    (boolean boSend);
STATIC_AL boolean        CddStp88XX_HalStpLwr_SendCReg2                    (boolean boSend);
STATIC_AL boolean        CddStp88XX_HalStpLwr_SendCReg3                    (boolean boSend);
STATIC_AL boolean        CddStp88XX_HalStpLwr_SendCReg4                    (boolean boSend);
STATIC_AL boolean        CddStp88XX_HalStpLwr_SendCRegAll                  (void);
//  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
//  STATIC_AL inline boolean        CddStp88XX_HalStpLwr_SendSReg1                    (void);
STATIC_AL boolean               CddStp88XX_HalStpLwr_DRV88XXCRegInit             (void);
STATIC_AL boolean               CddStp88XX_HalStpLwr_DRV88XXCRegDeinit           (void);
STATIC_AL void           CddStp88XX_HalStpLwr_ClrSCCnt_                    (void);
STATIC_AL boolean        CddStp88XX_HalStpLwr_IncSCCnt_                    (void);
STATIC_AL boolean        CddStp88XX_HalStpLwr_IsSCCntMax_                  (void);
STATIC_AL uint16         CddStp88XX_HalStpLwr_GetErrVolt_                  (void);
STATIC_AL void           CddStp88XX_HalStpLwr_ResetErrVolt_                (void);
STATIC_AL boolean        CddStp88XX_HalStpLwr_IsStateHoldCont_             (void);
STATIC_AL boolean        CddStp88XX_HalStpLwr_IsStateTestStep_             (void);
STATIC_AL uint32         CddStp88XX_HalStpLwr_CalcCount                    (const uint32 ulCount);
STATIC_AL void           CddStp88XX_HalStpLwr_StepReload                   (const uint32 ulCount);

STATIC_AL void           CddStp88XX_HalStpLwr_HandleCurAmplt_              (tCurAmpltStateCddStp88XX eCurAmpltState, uint8 ucCurAmpltHold, uint8 ucCurAmpltRun);
STATIC_AL void           CddStp88XX_HalStpLwr_HandleInc                    (boolean boIncCntActPos, boolean boIncBufIx);
STATIC_AL boolean        CddStp88XX_HalStpLwr_HandleDir                    (void); // dir stepper (currently: SPI - future: HW-Pin)
STATIC_AL boolean        CddStp88XX_HalStpLwr_GetPause                     (void);
STATIC_AL void           CddStp88XX_HalStpLwr_HandleTestStep               (void);
STATIC_AL void           CddStp88XX_HalStpLwr_HandleCommonStep             (const tStateHalStp eState);

STATIC_AL void           CddStp88XX_HalStpLwr_StateMachine                 (const tCommandHalStp eCmd);
STATIC_AL uint32                CddStp88XX_HalStpLwr_TransitionInitHoldCont       (const tCommandHalStp eCmd);
STATIC_AL uint32                CddStp88XX_HalStpLwr_TransitionTestStepHoldCont   (const tCommandHalStp eCmd);
STATIC_AL uint32                CddStp88XX_HalStpLwr_Transition2LastStep          (const tCommandHalStp eCmd);
STATIC_AL uint32                CddStp88XX_HalStpLwr_Transition2Step              (const tCommandHalStp eCmd);
STATIC_AL uint32                CddStp88XX_HalStpLwr_TransitionStepHold           (const tCommandHalStp eCmd);
STATIC_AL uint32                CddStp88XX_HalStpLwr_TransitionHoldHoldCont       (const tCommandHalStp eCmd);
STATIC_AL uint32                CddStp88XX_HalStpLwr_Transition2FirstStep         (const tCommandHalStp eCmd);
STATIC_AL uint32                CddStp88XX_HalStpLwr_Transition2TestStep          (const tCommandHalStp eCmd);

STATIC_AL void                  CddStp88XX_HalStpLwr_InitStateFct                 (tAction Action);
STATIC_AL void                  CddStp88XX_HalStpLwr_FirstStepStateFct            (tAction Action);
STATIC_AL void                  CddStp88XX_HalStpLwr_LastStepStateFct             (tAction Action);
STATIC_AL void                  CddStp88XX_HalStpLwr_StepStateFct                 (tAction Action);
STATIC_AL void                  CddStp88XX_HalStpLwr_HoldStateFct                 (tAction Action);
STATIC_AL void                  CddStp88XX_HalStpLwr_HoldContStateFct             (tAction Action);
STATIC_AL void                  CddStp88XX_HalStpLwr_TestStepStateFct             (tAction Action);

STATIC_AL void           CddStp88XX_HalStpLwr_ClrOLCnt_                    (void);
STATIC_AL boolean        CddStp88XX_HalStpLwr_IncOLCnt_                    (void);
STATIC_AL boolean        CddStp88XX_HalStpLwr_IsOLCntMax_                  (void);

STATIC_AL boolean        CddStp88XX_HalStpLwr_SetHsMode_                   (boolean boHsMode, uint8 ucCurAmpltRun);

  #endif

#endif


#if ((CFG_DRV_STP_LWR == CFG_Drv_Default) || (CFG_DRV_STP_KL == CFG_Drv_Default) || (CFG_DRV_STP_GLW == CFG_Drv_Default))

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // LWR, KL and GLW common functions
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // ---------------------------------------------------------------------------
  ///
  ///  \func   CddStp88XX_HalStp_InitBuffer
  ///
  ///  \brief  Initialisation of stepping buffer
  ///
  ///  \param  tStpInfo *pStpInfo
  ///
  ///  \return none
  ///
  ///  \descr
  ///
  // ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HalStp_InitBuffer(tStpInfo* pStpInfo)
  {
    // Initialisation with zero
    //HalStp..._SetActPos(0); , reset actual position
    // PRQA S 316, 4464 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio5) Msg: 316([I] Cast from a pointer to void to a pointer to object type.) Depth: 0 Ref: MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
    UtilMemClr((uint8*)(void*)pStpInfo, (uint8_least)sizeof(tStpInfo));
  }


  #if (CFG_DRV_STP_LWR == CFG_Drv_Default)

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Optional debug buffer functions
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // LWR specific functions
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetHsCnt
    ///
    ///  \brief  Get half step count to count LWR steps and clear it internal
    ///
    ///  \param  none
    ///
    ///  \return uint32
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_HalStpLwr_GetHsCnt(void)
    {
      uint32 ulReturn = CddStp88XX_HalStp_ulHsCntLwr;

      CddStp88XX_HalStp_ulHsCntLwr = 0;               // reset after read
      return ulReturn;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SetCARunRefCnt
    ///
    ///  \brief  Set half step count LWR of run current of next 12 HS to reference current for bump reference run
    ///
    ///  \param  uint8 ucCntVal
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HalStpLwr_SetCARunRefCnt(uint8 ucCntVal)
    {
      // (void)ucCntVal;
      if (ucCntVal == 0u){} //Misra QAC
//    CddStp88XX_HalStp_ucCARunRefCntLwr = ucCntVal;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetIrunTime
    ///
    ///  \brief  Get time of LWR motor running (moving) phase and clear it internal
    ///
    ///  \param  none
    ///
    ///  \return uint32
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_HalStpLwr_GetIrunTime(void)
    {
      uint32 ulReturn = CDDSTP_TICKS_TO_US(CddStp88XX_HalStp_ulIrunTimeLwr) / 1000u; // [ms]

      CddStp88XX_HalStp_ulIrunTimeLwr = 0;               // reset after read
      return ulReturn;

// jk-orig-70516
// jk-orig-70516       uint32 ulReturn;
// jk-orig-70516 
// jk-orig-70516 ///// __DI();             // call from interrupt level is not possible (no counter)!
// jk-orig-70516 ///// osDisableGlobal();  // call from interrupt level is not possible (no counter)!
// jk-orig-70516 //PLI_GM22      SuspendAllInterrupts(); // warning - QAC(Prio7) Msg: 635([E] Bit-fields in this struct/union have been declared with types other than int, signed int or unsigned int.) Depth: 0 Ref: MISRA C:2012 Rule-1.2, Rule-6.1; REFERENCE - ISO:C90-6.5.2.1 Structure and Union Specifiers - Semantics (definition in Vector code osek is wrong)!
// jk-orig-70516       uint32 ulDisableIntKey;
// jk-orig-70516       ulDisableIntKey = __DIR();
// jk-orig-70516 
// jk-orig-70516       ulReturn = CDDSTP_TICKS_TO_US(CddStp705XX_HalStp_ulIrunTimeLwr);
// jk-orig-70516 
// jk-orig-70516       CddStp705XX_HalStp_ulIrunTimeLwr = 0;               // reset after read
// jk-orig-70516       
// jk-orig-70516 ///// __EI();            // call from interrupt level is not possible (no counter)!
// jk-orig-70516 ///// osEnableGlobal();  // call from interrupt level is not possible (no counter)!
// jk-orig-70516 //PLI_GM22      ResumeAllInterrupts(); // PRQA S 3417 1 // program architecture and readability - intentionally no modification of existing code (definition in Vector code osek is wrong)!
// jk-orig-70516       __RIR(ulDisableIntKey);
// jk-orig-70516 
// jk-orig-70516       return ulReturn;
    }


// jk-orig-70516     // ---------------------------------------------------------------------------
// jk-orig-70516     ///
// jk-orig-70516     ///  \func   CddStp705XX_HalStpLwr_GetIrunTimeEd
// jk-orig-70516     ///
// jk-orig-70516     ///  \brief  Get time of LWR motor running (moving) phase and clear it internal - for (check of) stepper moving endurance time.
// jk-orig-70516     ///
// jk-orig-70516     ///  \param  none
// jk-orig-70516     ///
// jk-orig-70516     ///  \return uint32
// jk-orig-70516     ///
// jk-orig-70516     ///  \descr
// jk-orig-70516     ///
// jk-orig-70516     // ---------------------------------------------------------------------------
// jk-orig-70516     STATIC_AL uint32 CddStp705XX_HalStpLwr_GetIrunTimeEd(void)
// jk-orig-70516     {
// jk-orig-70516       uint32 ulReturn;
// jk-orig-70516 
// jk-orig-70516 ///// __DI();             // call from interrupt level is not possible (no counter)!
// jk-orig-70516 ///// osDisableGlobal();  // call from interrupt level is not possible (no counter)!
// jk-orig-70516 //PLI_GM22      SuspendAllInterrupts(); // PRQA S 3417 1 // program architecture and readability - intentionally no modification of existing code (definition in Vector code osek is wrong)!
// jk-orig-70516       uint32 ulDisableIntKey;
// jk-orig-70516       ulDisableIntKey = __DIR();
// jk-orig-70516 
// jk-orig-70516       ulReturn = CDDSTP_TICKS_TO_US(CddStp705XX_HalStp_ulIrunTimeLwrEd);
// jk-orig-70516 
// jk-orig-70516       CddStp705XX_HalStp_ulIrunTimeLwrEd = 0;             // reset after read
// jk-orig-70516       
// jk-orig-70516 ///// __EI();            // call from interrupt level is not possible (no counter)!
// jk-orig-70516 ///// osEnableGlobal();  // call from interrupt level is not possible (no counter)!
// jk-orig-70516 //PLI_GM22      ResumeAllInterrupts(); // PRQA S 3417 1 // program architecture and readability - intentionally no modification of existing code (definition in Vector code osek is wrong)!
// jk-orig-70516       __RIR(ulDisableIntKey);
// jk-orig-70516 
// jk-orig-70516       return ulReturn;
// jk-orig-70516     }





    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_Init
    ///
    ///  \brief  Init stepper driver
    ///
    ///  \param  boolean boInit = TRUE:   init
    ///                         = FALSE:  deinit
    ///
    ///  \return boolean  = TRUE:   OK
    ///                   = FALSE:  not OK
    ///
    ///  \descr  Depending on boInit the interrupts are enabled or disabled.
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_Init(boolean boInit)
    {
      if (boInit != FALSE) // init?
      {
        // LWR
        CddStp88XX_HalStp_eStateLwr = CddStp88XX_HalStp_eStateInit;
        CddStp88XX_HalStp_HSInfoBufSaveLwr.ulRaw = 0;
//      CddStp88XX_HalStp_ulHsCntLwr = 0;                      // reset step counter (not compatible to Afs2)
        #if(CFG_OPT_STATISTIC & CFG_Statistic_ExtendedStpLwr)
          CddStp88XX_HalStp_ucCycleHsCntLwr = 0;
        #endif
        CddStp88XX_HalStp_ucPhaseCounterLwr = 0;
        CddStp88XX_HalStp_ucCurAmpltLwr    = CddStp88XX_aucCurAmpltHoldTemp[CFG_Stp_IdxVer][CddStp_eTempState_NormTemp];
        CddStp88XX_HalStp_ucCurAmpltOldLwr = CddStp88XX_aucCurAmpltHoldTemp[CFG_Stp_IdxVer][CddStp_eTempState_NormTemp];

        CddStp88XX_HalStp_ucOLCntLwr = 0;
        CddStp88XX_HalStp_ucSCCntLwr = 0;

        CddStp88XX_HalStp_ulTestStepCntLwr = 0;
        // jk-obsolet: currently not used: CddStp88XX_HalStp_ucTestStepSr3ReadNotOkCntLwr = 0;

        CddStp88XX_HalStp_BitsLwr.unRaw = 0;
        CddStp88XX_HalStp_BitsLwr.Bit.biInit = 1;  // now ERRN ISR starts reading all status registers by SPI and CddStp88XX_HalStpLwr_HandleCurAmplt_() sends CReg0 values by SPI
        CddStp88XX_HalStp_BitsIntLwr.ucRaw = 0;

        CddStp88XX_HalStpLwr_ResetErrVolt_();

        CddStp88XX_HalStp_InitBuffer(&CddStp88XX_HalStp_StpInfoLwr);
        CddStp88XX_HalStpLwr_StateMachine(CddStp88XX_HalStp_eCmdInit);
      }
      else        // deinit
      {
        CddStp88XX_HalStp_eStateLwr = CddStp88XX_HalStp_eStateInit;
      }

      return TRUE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SetHsMode_
    ///
    ///  \brief  Returns half step mode
    ///
    ///  \param  boolean boHsMode = TRUE:   half step mode
    ///                           = FALSE:  micro step mode
    ///          uint8 ucCurAmpltRun (not compatible to Afs2)
    ///
    ///  \return boolean  = TRUE:   OK
    ///                   = FALSE:  not OK
    ///
    ///  \descr  The driver is not initialised by SPI (important for call in HalInit()).
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_SetHsMode_(boolean boHsMode, uint8 ucCurAmpltRun)
    {
      CddStp88XX_HalStp_BitsLwr.Bit.biHsMode = boHsMode;

      if (boHsMode != FALSE)
      {
        uint8 ucCurAmpltRun_NT              = CddStp88XX_aucCurAmpltRunTemp[CFG_Stp_IdxVer] [CddStp_eTempState_NormTemp];
        
        CddStp88XX_HalStp_ucStepModeLwr    = CDDSTP8899_StepModeHS;
        (void)CddStp88XX_HalStp_ucStepModeLwr; // jk-tbd!!

        // jk-obsolet: No HS-Mode CddStp88XX_HalStp_ucStepModeOldLwr = CDDSTP8899_StepModeHS;

        // like at initialisation: new normal current amplitude without temperature dependency (values for normal temperature are used)
        CddStp88XX_HalStpLwr_HandleCurAmplt_(CDDSTP88XX_eCurAmpltStateNoChange, CDDSTP88XX_eCurAmpltNoChange, ucCurAmpltRun_NT);
//      CddStp88XX_HalStpLwr_HandleCurAmplt_(CDDSTP88XX_eCurAmpltStateNoChange, CDDSTP88XX_eCurAmpltNoChange, CDDSTP88XX_CurAmpltRunNC_NTVer); //HSNC not compensated   //TBD
//HSNC  CddStp88XX_HalStpLwr_HandleCurAmplt_(CDDSTP88XX_eCurAmpltStateNoChange, CDDSTP88XX_eCurAmpltNoChange, CDDSTP88XX_CurAmpltRunHS_NTVer); //HS       compensated   //TBD
      }

      else
      {
        CddStp88XX_HalStp_ucStepModeLwr = CDDSTP8899_StepModeMS;
        // jk-obsolet: No HS-Mode CddStp88XX_HalStp_ucStepModeOldLwr = CDDSTP8899_StepModeMS;

        // like at initialisation: new normal current amplitude without temperature dependency (values for normal temperature are used)
        CddStp88XX_HalStpLwr_HandleCurAmplt_(CDDSTP88XX_eCurAmpltStateNoChange, CDDSTP88XX_eCurAmpltNoChange, ucCurAmpltRun); // us
      }

      CddStp88XX_HalStp_InitBuffer(&CddStp88XX_HalStp_StpInfoLwr);

      return TRUE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SetHsMode
    ///
    ///  \brief  Returns half step mode
    ///
    ///  \param  boolean boHsMode = TRUE:   half step mode
    ///                           = FALSE:  micro step mode
    ///          uint8 ucCurAmpltRun (not compatible to Afs2)
    ///
    ///  \return boolean  = TRUE:   OK
    ///                   = FALSE:  not OK
    ///
    ///  \descr  Additional the driver is initialised by SPI.
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_SetHsMode(boolean boHsMode, uint8 ucCurAmpltRun)
    {
      boolean boSetHsMode = CddStp88XX_HalStpLwr_SetHsMode_(boHsMode, ucCurAmpltRun);
      boolean boRegInit   = CddStp88XX_HalStpLwr_DRV88XXCRegInit();

      #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
      #else // Unit-Tests!
        // all the 'real' results are fixed so use this way to do full coverage
        boSetHsMode = CddStp_UnitTestHelper_bo1;
        boRegInit   = CddStp_UnitTestHelper_bo2;
      #endif

      // jk-orig return (   (boSetHsMode != TRUE)  && (boRegInit == TRUE));
                 return (   (boSetHsMode == FALSE) && (boRegInit != FALSE)) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetHsMode
    ///
    ///  \brief  Returns half step mode
    ///
    ///  \param  none
    ///
    ///  \return boolean  = TRUE:   half step mode
    ///                   = FALSE:  micro step mode
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_GetHsMode(void)
    {
      return (CddStp88XX_HalStp_BitsLwr.Bit.biHsMode == 1u) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SetTestStep
    ///
    ///  \brief  Set test step flag LWR and call state machine
    ///
    ///  \param  boolean boResetTestStepDone
    ///          = TRUE:   reset biTestStepDone
    ///          = FALSE:  do not reset biTestStepDone
    ///
    ///  \return boolean  = TRUE:   biTestStep flag is set because of the actual state is 'CddStp88XX_HalStp_eStateHoldCont'
    ///                   = FALSE:  biTestStep flag is not set because of the actual state is not 'CddStp88XX_HalStp_eStateHoldCont'
    ///
    ///  \descr  After setting test step flag the state machine switches to TestStep state
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_SetTestStep(boolean boResetTestStepDone)
    {
      boolean boReturn = FALSE;

      if (boResetTestStepDone != FALSE)
      {
        CddStp88XX_HalStp_BitsLwr.Bit.biTestStepDone = 0;
      }

      if (   (CddStp88XX_HalStpLwr_IsStateHoldCont_() != FALSE) )// avoid asynchronous call of state machine
//          && (CddStp88XX_HalStp_ulTestStepCntLwr == 0u)) // NEW LDM specific: this condition is removed as the test step will not be done once per cycle due to the OL retry mechanism
                                                           // (old) only once after CddStp88XX_HalStpLwr_Init() and not while test steps
      {
        CddStp88XX_HalStp_BitsLwr.Bit.biTestStep = 1;

        CddStp88XX_HalStpLwr_StateMachine(CddStp88XX_HalStp_eCmdStartStp);

        boReturn = TRUE;
      }
      return (boReturn != FALSE) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_IsTestStepDone
    ///
    ///  \brief  Get test step done flag LWR
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr  Possibility to get test step done flag.
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_IsTestStepDone(void)
    {
      return (CddStp88XX_HalStp_BitsLwr.Bit.biTestStepDone == 1u) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_ResetTestStepCnt
    ///
    ///  \brief  Reset test step counter LWR
    ///
    ///  \param  none
    ///
    ///  \return none
    ///
    ///  \descr  Possibility to reset test step counter without use of CddStp88XX_HalStpLwr_Init().
    ///
    // ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HalStpLwr_ResetTestStepCnt(void)
    {
      CddStp88XX_HalStp_ulTestStepCntLwr = 0;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_DRV88XXCRegInit
    ///
    ///  \brief  Initialisation of DRV88XX LWR control registers
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr  Initialisation of DRV88XX LWR control registers:
    ///          - include CSN pin handling
    ///          - Control register 1
    ///          - Control register 2
    ///          - Control register 3
    ///          - Control register 4
    ///          - Control register 5
    ///          - Control register 6
    ///          - Control register 7
    ///          - Status register 1
    ///          - Status register 2
    ///          - Status register 3
    ///          - Status register 4
    ///          - Status register 5
    ///          - Status register 6
    ///          - Status register 7
    ///          - Status register 8
    ///          - Status register 7A
    ///          - Status register 8A
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_DRV88XXCRegInit(void)
    {
      CddStp88XX_HalStpLwr_HandleMotEn_(TRUE, TRUE);   // boMotEn = TRUE to enable driver (handle difference, because function is called several times!), boSendCReg12 = FALSE, but TRUE would be OK also, because of all CRegs are sent - see explicitly in next return line: // UWY manipulate send always CReg1 and CReg2 (cyclic)
      return CddStp88XX_HalStpLwr_SpiSendCRegAll();    // send SPI commands triggered by cyclic mainTask event     (call from ISR is possible)
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_DRV88XXCRegDeinit
    ///
    ///  \brief  Disable DRV88XX LWR control registers
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr  Disable DRV88XX LWR control registers:
    ///          - include CSN pin handling
    ///          - Control register 1
    ///          - Control register 2
    ///          - Control register 3
    ///          - Control register 4
    ///          - Control register 5
    ///          - Control register 6
    ///          - Control register 7
    ///          - Status register 1
    ///          - Status register 2
    ///          - Status register 3
    ///          - Status register 4
    ///          - Status register 5
    ///          - Status register 6
    ///          - Status register 7
    ///          - Status register 8
    ///          - Status register 7A
    ///          - Status register 8A
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_DRV88XXCRegDeinit(void)
    {
      CddStp88XX_HalStpLwr_HandleMotEn_(FALSE, TRUE); // boMotEn = FALSE to disable driver (handle difference, because function is called several times!), boSendCReg12 = FALSE, but TRUE would be OK also, because of all CRegs are sent - see explicitly in next return line: // UWY manipulate send always CReg1 and CReg2 (cyclic)
      return CddStp88XX_HalStpLwr_SpiSendCRegAll();    // send SPI commands triggered by event handled in mainTask (call from ISR is not possible)
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendCReg0
    ///
    ///  \brief  Dummy
    ///
    ///  \param  boolean boSend
    ///
    ///  \return boolean FALSE
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendCReg0(boolean boSend)
    {
      (void)boSend;
      return FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendCReg1
    ///
    ///  \brief  Send control register 1 to LWR DRV88XX
    ///
    ///  \param  boolean boSend
    ///
    ///  \return boolean
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendCReg1(boolean boSend)
    {
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      return CddStp88XX_HalStpLwr_SendCReg1(boSend);
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendCReg2
    ///
    ///  \brief  Send control register 2 to LWR DRV88XX
    ///
    ///  \param  boolean boSend
    ///
    ///  \return boolean
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendCReg2(boolean boSend)
    {
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      return CddStp88XX_HalStpLwr_SendCReg2(boSend);
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendCReg3
    ///
    ///  \brief  Send control register 3 to LWR DRV88XX
    ///
    ///  \param  boolean boSend
    ///
    ///  \return boolean
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendCReg3(boolean boSend)
    {
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      return CddStp88XX_HalStpLwr_SendCReg3(boSend);
    }




    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendCReg4 
    ///
    ///  \brief  Send control register 4 to LWR DRV88XX
    ///
    ///  \param  boolean boSend
    ///
    ///  \return boolean
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendCReg4(boolean boSend)
    {
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      return CddStp88XX_HalStpLwr_SendCReg4(boSend);
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendCRegAll
    ///
    ///  \brief  Send all control registers to LWR DRV88XX
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendCRegAll(void)
    {
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      return CddStp88XX_HalStpLwr_SendCRegAll();
    }


    // keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //    X=0,1,3,4,5,6,7,8,7A,8A,All
    /*
    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg0
    ///
    ///  \brief  Dummy
    ///
    ///  \param  none
    ///
    ///  \return boolean FALSE
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg0(void)
    //{
    //  return FALSE;
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg1
    ///
    ///  \brief  Send status register 1 to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 1 to read.
    ///
    // ---------------------------------------------------------------------------
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg1(void)
    //{
    //  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //  return CddStp88XX_HalStpLwr_SendSReg1();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg2
    ///
    ///  \brief  Send status register 2 to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 2 to read.
    ///
    // ---------------------------------------------------------------------------
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg2(void)
    //{
    //  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //  return CddStp88XX_HalStpLwr_SendSReg2();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg3
    ///
    ///  \brief  Send status register 3 to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 3 to read.
    ///
    // ---------------------------------------------------------------------------
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg3(void)
    //{
    //  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //  return CddStp88XX_HalStpLwr_SendSReg3();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg4
    ///
    ///  \brief  Send status register 4 to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 4 to read.
    ///
    // ---------------------------------------------------------------------------
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg4(void)
    //{
    //  return CddStp88XX_HalStpLwr_SendSReg4();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg5
    ///
    ///  \brief  Send status register 5 to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 5 to read.
    ///
    // ---------------------------------------------------------------------------
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg5(void)
    //{
    //  return CddStp88XX_HalStpLwr_SendSReg5();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg6
    ///
    ///  \brief  Send status register 6 to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 6 to read.
    ///
    // ---------------------------------------------------------------------------
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg6(void)
    //{
    //  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //  return CddStp88XX_HalStpLwr_SendSReg6();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg7
    ///
    ///  \brief  Send status register 7 to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 7 to read.
    ///
    // ---------------------------------------------------------------------------
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg7(void)
    //{
    //  return CddStp88XX_HalStpLwr_SendSReg7();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg8
    ///
    ///  \brief  Send status register 8 to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 8 to read.
    ///
    // ---------------------------------------------------------------------------
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg8(void)
    //{
    //  return CddStp88XX_HalStpLwr_SendSReg8();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg7A
    ///
    ///  \brief  Send status register 7A to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 7A to read.
    ///
    // ---------------------------------------------------------------------------
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg7A(void)
    //{
    //  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //  return CddStp88XX_HalStpLwr_SendSReg7A();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSReg8A
    ///
    ///  \brief  Send status register 8A to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status register 8A to read.
    ///
    // ---------------------------------------------------------------------------
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSReg8A(void)
    //{
    //  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //  return CddStp88XX_HalStpLwr_SendSReg8A();
    //}


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SpiSendSRegAll
    ///
    ///  \brief  Send all status registers to LWR DRV88XX.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr Send LWR DRV88XX status registers to read.
    ///
    // ---------------------------------------------------------------------------
    //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //STATIC_AL boolean CddStp88XX_HalStpLwr_SpiSendSRegAll(void)
    //{
    //  //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
    //  return CddStp88XX_HalStpLwr_SendSRegAll();
    //}
*/


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_IsDriverReset
    ///
    ///  \brief  Get whether LWR driver reset is detected (DRV88XX specific).
    ///
    ///  \param  none
    ///
    ///  \return boolean state 'driver reset'
    ///
    ///  \descr  Only call from task level (loop!)
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_IsDriverReset(void)
    {
      return (CddStp88XX_HalStp_BitsLwr.Bit.biDriverReset == 1u) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_ClrDriverReset
    ///
    ///  \brief  Clear LWR driver reset flag biDriverReset directly (DRV88XX specific).
    ///
    ///  \param  none
    ///
    ///  \return none
    ///
    ///  \descr  Only call from task level (loop!)
    ///
    // ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HalStpLwr_ClrDriverReset(void)
    {
      CddStp88XX_HalStp_BitsLwr.Bit.biDriverReset = 0; // clear driver reset
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SetDriverReset
    ///
    ///  \brief  Set LWR driver reset flag biDriverReset directly (DRV88XX specific).
    ///
    ///  \param  none
    ///
    ///  \return none
    ///
    ///  \descr  Only call from task level (loop!)
    ///
    // ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HalStpLwr_SetDriverReset(void)
    {
      CddStp88XX_HalStp_BitsLwr.Bit.biDriverReset = 1; // set driver reset
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_ClrOLCnt_
    ///
    ///  \brief  Clear OpenLoad counter LWR.
    ///
    ///  \param  none
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HalStpLwr_ClrOLCnt_(void)
    {
      CddStp88XX_HalStp_ucOLCntLwr = 0;
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
STATIC_AL void CddStp88XX_HalStpLwr_ClrOLCnt(void)
    {
      CddStp88XX_HalStpLwr_ClrOLCnt_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_IncOLCnt_
    ///
    ///  \brief  Increment OpenLoad counter LWR.
    ///
    ///  \param  none
    ///
    ///  \return boolean TRUE if openload error bit in register 1 is set (to clear it later)
    ///
    ///  \descr  Increments OL counter and clears it if no OL error is detected.
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_IncOLCnt_(void)
    {
      boolean boReturn;
      
      // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
      // get Status-Register-FAULT contents from RAM mirror (verified)
    //(void)CddStp8899Com_GetSRegFlt(CFG_Stp_IdxVer, &CddStp8899_aSRegFault[CFG_Stp_IdxVer].ucRaw);
      (void)CddStp8899Com_GetSRegBsc(CFG_Stp_IdxVer, &CddStp8899_aSRegBasic[CFG_Stp_IdxVer].ucRaw);

    //if (CddStp8899_aSRegFault[CFG_Stp_IdxVer].Bit.u1OL != 0x00u)  // only used openload error bit set?
      if (CddStp8899_aSRegBasic[CFG_Stp_IdxVer].Bit.u1OL != 0x00u)  // only used openload error bit set?
      {
        CddStp88XX_HalStp_ucOLCntLwr++;

        if (CddStp88XX_HalStpLwr_IsOLCntMax_() != FALSE)
        {
          CddStpPrj_SetEventFinishMove(CFG_Stp_IdxVer);
        }

        boReturn = TRUE;
      }
      else
      {
        CddStp88XX_HalStpLwr_ClrOLCnt_();
        boReturn = FALSE;
      }
      return (boReturn != FALSE) ? TRUE : FALSE;
    }


    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
    STATIC_AL boolean CddStp88XX_HalStpLwr_IncOLCnt(void)
    {
      return CddStp88XX_HalStpLwr_IncOLCnt_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_IsOLCntMax_
    ///
    ///  \brief  Get OpenLoad counter LWR.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_IsOLCntMax_(void)
    {
      boolean boReturn;

      if (CddStp88XX_HalStp_BitsLwr.Bit.biHsMode == 1u)
      {
        boReturn = (CddStp88XX_HalStp_ucOLCntLwr >= CDDSTP88XX_HALSTP_OLCntMaxHS) ? TRUE : FALSE;                //TBD
      }
      else
      {
//!!    boReturn = (boolean) (CddStp88XX_HalStp_ucOLCntLwr >= CDDSTP88XX_HALSTP_OLCntMaxMS);
        boReturn =           (CddStp88XX_HalStp_ucOLCntLwr >= CddStp88XX_aucOLCntMax[CFG_Stp_IdxVer]) ? TRUE : FALSE;
        if (   (boReturn             != FALSE)           // TRUE?
            && (Cod_LwrTestOlIgnor() != FALSE))          // ignore OL error of driver? // PRQA S 3415 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 3415(Right hand operand of '&&' or '||' is an expression with possible side effects.) Depth: 0 Ref: MISRA C:2012 Rule-13.5; REFERENCE - ISO:C90-5,1,2,3 Program Execution
        {
          //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
          //(void)CddStp88XX_HalStpLwr_SpiSendSRegAll();  // read all the status registers to clear the error bit
          boReturn = FALSE;
        }
      }
      return (boReturn);
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
STATIC_AL boolean CddStp88XX_HalStpLwr_IsOLCntMax(void)
    {
      return CddStp88XX_HalStpLwr_IsOLCntMax_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_ClrSCCnt_
    ///
    ///  \brief  Clear ShortedCoil counter LWR.
    ///
    ///  \param  none
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HalStpLwr_ClrSCCnt_(void)
    {
      CddStp88XX_HalStp_ucSCCntLwr = 0;
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
STATIC_AL void CddStp88XX_HalStpLwr_ClrSCCnt(void)
    {
      CddStp88XX_HalStpLwr_ClrSCCnt_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_IncSCCnt_
    ///
    ///  \brief  Increment ShortedCoil counter LWR.
    ///
    ///  \param  none
    ///
    ///  \return boolean TRUE if overcurrent error bit in register 1 is set (to clear it later)
    ///
    ///  \descr  Increments SC counter and clears it if no SC error is detected.
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_IncSCCnt_(void)
    {
      boolean boReturn;

      // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
      // get Status-Register-FAULT contents from RAM mirror (verified)
    //(void)CddStp8899Com_GetSRegFlt(CFG_Stp_IdxVer, &CddStp8899_aSRegFault[CFG_Stp_IdxVer].ucRaw);
      (void)CddStp8899Com_GetSRegBsc(CFG_Stp_IdxVer, &CddStp8899_aSRegBasic[CFG_Stp_IdxVer].ucRaw);

    //if (CddStp8899_aSRegFault[CFG_Stp_IdxVer].Bit.u1OCP != 0x00u)  // only used overcurrent error bit set?
      if (CddStp8899_aSRegBasic[CFG_Stp_IdxVer].Bit.u1OCP != 0x00u)  // only used overcurrent error bit set?
      {
        CddStp88XX_HalStp_ucSCCntLwr++;

        if (CddStp88XX_HalStpLwr_IsSCCntMax_() != FALSE)
        {
          CddStpPrj_SetEventFinishMove(CFG_Stp_IdxVer);
        }

        boReturn = TRUE;
      }
      else
      {
        CddStp88XX_HalStpLwr_ClrSCCnt_();
        boReturn = FALSE;
      }
      return (boReturn != FALSE) ? TRUE : FALSE;
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
STATIC_AL boolean CddStp88XX_HalStpLwr_IncSCCnt(void)
    {
      return CddStp88XX_HalStpLwr_IncSCCnt_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_IsSCCntMax_
    ///
    ///  \brief  Get ShortedCoil counter LWR.
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_IsSCCntMax_(void)
    {
//8899! SC or OL are detected sometimes as OL orSC!      return (boolean)(CddStp88XX_HalStp_ucSCCntLwr >= CDDSTP88XX_HALSTP_SCCntMax);
      boolean boReturn;                                                                                                 //8899! SC or OL are detected sometimes as OL orSC!

      boReturn = (CddStp88XX_HalStp_ucSCCntLwr/*!OL*/ >= CddStp88XX_aucOLCntMax[CFG_Stp_IdxVer]) ? TRUE : FALSE;        //8899! SC or OL are detected sometimes as OL orSC!
      if (   (boReturn             != FALSE)              // TRUE?                                                      //8899! SC or OL are detected sometimes as OL orSC!
          && (Cod_LwrTestOlIgnor() != FALSE))             // ignore OL error of driver?          // SC also!            //8899! SC or OL are detected sometimes as OL orSC! // PRQA S 3415 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 3415(Right hand operand of '&&' or '||' is an expression with possible side effects.) Depth: 0 Ref: MISRA C:2012 Rule-13.5; REFERENCE - ISO:C90-5,1,2,3 Program Execution
      {                                                                                                                 //8899! SC or OL are detected sometimes as OL orSC!
        //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
        //(void)CddStp88XX_HalStpLwr_SpiSendSRegAll();   // read all the status registers to clear the error bit        //8899! SC or OL are detected sometimes as OL orSC!
        boReturn = FALSE;                                                                                               //8899! SC or OL are detected sometimes as OL orSC!
      }                                                                                                                 //8899! SC or OL are detected sometimes as OL orSC!
      return (boReturn);                                                                                                //8899! SC or OL are detected sometimes as OL orSC!
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
STATIC_AL boolean CddStp88XX_HalStpLwr_IsSCCntMax(void)
    {
      return CddStp88XX_HalStpLwr_IsSCCntMax_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetPsensPort
    ///
    ///  \brief  Get boolean value of input port LWR position sensor 'Psens'
    ///
    ///  \param  none
    ///
    ///  \return boolean boPsensValue: level value of position sensor
    ///          - TRUE:  position sensor is switched on
    ///          - FALSE: position sensor is switched off
    ///
    ///  \descr  interface function for other modules
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_GetPsensPort(void)
    {
      boolean boReturn = FALSE;
  
      #if ( CFG_LNK_PSENSVER0 == CFG_LnkDrv_PsensLwr )
      {
        (void)IoHwAb_User_GetDio_PS_DIG_LWR(&boReturn);
      }
      #endif      
      return boReturn;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetErrVolt_
    ///
    ///  \brief  Get actual driver error voltage of LWR
    ///
    ///  \param  none
    ///
    ///  \return uint16
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL uint16 CddStp88XX_HalStpLwr_GetErrVolt_(void)
    {
      return (CddStp88XX_HalStp_unErrVoltLwr);
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
STATIC_AL uint32 CddStp88XX_HalStpLwr_GetErrVolt(void)
    {
      return CddStp88XX_HalStpLwr_GetErrVolt_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_ResetErrVolt_
    ///
    ///  \brief  Reset ErrISR voltage of LWR
    ///
    ///  \param  none
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL void CddStp88XX_HalStpLwr_ResetErrVolt_(void)
    {
      CddStp88XX_HalStp_unErrVoltLwr = CDDSTP88XX_HALSTP_ErrVoltDefault;
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
STATIC_AL void CddStp88XX_HalStpLwr_ResetErrVolt(void)
    {
      CddStp88XX_HalStpLwr_ResetErrVolt_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_IsStateHoldCont_
    ///
    ///  \brief  Interface to check LWR for state 'CddStp88XX_HalStp_eStateHoldCont'
    ///
    ///  \param  none
    ///
    ///  \return boolean HalStp_boStateLwr
    ///          = TRUE  if  CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateHoldCont
    ///          = FALSE if  CddStp88XX_HalStp_eStateLwr != CddStp88XX_HalStp_eStateHoldCont
    ///
    ///  \descr  Interface to get boolean information
    ///          whether the LWR state machine is in state 'CddStp88XX_HalStp_eStateHoldCont'.
    ///          Used global variables:
    ///          - CddStp88XX_HalStp_eStateLwr
    ///
    // ---------------------------------------------------------------------------
STATIC_AL boolean CddStp88XX_HalStpLwr_IsStateHoldCont_(void)
    {
      return (CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateHoldCont) ? TRUE : FALSE;
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
STATIC_AL boolean CddStp88XX_HalStpLwr_IsFinishMove(void)
    {
      return CddStp88XX_HalStpLwr_IsStateHoldCont_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_IsStateTestStep_
    ///
    ///  \brief  Interface to check LWR for state 'CddStp88XX_HalStp_eStateTestStep'
    ///
    ///  \param  none
    ///
    ///  \return boolean HalStp_boStateLwr
    ///          = TRUE  if  CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateTestStep
    ///          = FALSE if  CddStp88XX_HalStp_eStateLwr != CddStp88XX_HalStp_eStateTestStep
    ///
    ///  \descr  Interface to get boolean information
    ///          whether the LWR state machine is in state 'CddStp88XX_HalStp_eStateTestStep'.
    ///          Used global variables:
    ///          - CddStp88XX_HalStp_eStateLwr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL boolean CddStp88XX_HalStpLwr_IsStateTestStep_(void)
    {
      return (CddStp88XX_HalStp_eStateLwr == CddStp88XX_HalStp_eStateTestStep) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetWriteIx
    ///
    ///  \brief  Get stepping buffer index of LWR which can be overwritten for next steps and the according position
    ///
    ///  \param  sint32* plActPos: pointer to actual position
    ///          This variable is incremented or decremented according the direction bit
    ///          of the entry which contains the information.
    ///          uint32* pulRemainingTicks: pointer to remaining ticks till next buffer entry is used
    ///
    ///  \return uint32 ulBufIx: index of stepping buffer which can be overwritten
    ///
    ///  \descr  Call from task level - CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx is changed in interrupt level, but this is checked, therefore disable INTs is not neccessary!
    ///
    // ---------------------------------------------------------------------------
STATIC_AL uint32 CddStp88XX_HalStpLwr_GetWriteIx(sint32* plActPos, uint32* pulRemainingTicks)
    {
      uint32 ulBufferIndex = 0;
      uint32 ulBufferIndexAct;
      uint32 ulBufferIndexSav = CDDSTP88XX_HALSTP_HsInfoBufLen;      // not valid index as initial value to force first run in while loop
      uint32 ulBufferIndexNow;

///// __DI();               // call from interrupt level is not possible (no counter)!
///// osDisableGlobal();    // call from interrupt level is not possible (no counter)!
//!   SuspendAllInterrupts();

      ulBufferIndexAct = CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx;

// jk-orig 70514  while (   (unDtc != CddStpPrjLwr_GetDmaCount())      // actual DMA transfer count LWR - different to actual value?
// jk-orig 70514         || (ulBufferIndexSav != ulBufferIndexAct))    // no INT has incremented buffer index?
// jk-orig 70514  {
      // 'modified' 70516:
      while (ulBufferIndexSav != ulBufferIndexAct)    // no INT has incremented buffer index?
      {
        ulBufferIndex    = ulBufferIndexAct;
        ulBufferIndexSav = ulBufferIndexAct;
        ulBufferIndexNow = ulBufferIndexAct;
        *plActPos = CddStp88XX_HalStp_StpInfoLwr.lActPos;
        *pulRemainingTicks = 0;                            // reset time till next buffer entry is used

        if (   (CddStp88XX_HalStp_eStateLwr != CddStp88XX_HalStp_eStateHold)                // moving?
            && (CddStp88XX_HalStp_eStateLwr != CddStp88XX_HalStp_eStateHoldCont)
            && (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferIndexAct].Bit.biSet == 1u))  // is actual entry a new entry?
        {
          uint32 ulRemainingTicks;

          ulBufferIndexNow--; // this entry is now active
          ulBufferIndexNow %= CDDSTP88XX_HALSTP_HsInfoBufLen;
//T       //T Tsh hepler timer is always active: in case of pause and in case of stepping:
//T       if (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferIndexNow].Bit.biPause == 1u)   // Pause bit set in now active actual entry? - causes no position increment/decrement while stepping
          {
#if defined (UNIT_TEST)
            ulRemainingTicks = CddStp_UnitTestHelper_ul1;
#else
            ulRemainingTicks = CddStpPrjLwr_GPT_GetRemainingCnt();                           // actual help(!!!) timer remaining count LWR
#endif
          }
//T       else                                                                              // real step (no Pause bit set in now active actual entry)
//T       {
//T         ulRemainingTicks = CddStpPrjLwr_CalcRemainingTicks(/*((CddStp705XX_HalStp_BitsLwr.Bit.biHsMode == 1) ? TRUE : FALSE), */ulBufferIndexNow/*, ulBufferIndexNow, &unDtc*/);
//T       }

          if (ulRemainingTicks > CDDSTP88XX_HALSTP_MaxTimerVal)                            // the actual CNT value is greater than last CDR value -> step follows immediately (see CddStpDynTables.h: first table entry)
          {
            ulRemainingTicks = 0;
          }
          *pulRemainingTicks = ulRemainingTicks;                                           // save rest time

          // check remaining time
          if (ulRemainingTicks < CDDSTP88XX_HALSTP_RT_MIN)                                 // are the remaining ticks of actual step too less?
          { //  do not overwrite actual entry -> use next entry:
            if (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferIndexAct].Bit.biPause == 0u) // Pause bit not set in actual entry? - causes position increment/decrement while stepping
            {
              if (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferIndexAct].Bit.biDirection == CDDSTP8899_DirPos)
              {
                (*plActPos)++;
              }
              else
              {
                (*plActPos)--;
              }
            }

            *pulRemainingTicks += CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferIndexAct].Val.unHsTime; // add to rest time the time of actual buffer entry

            ulBufferIndex++; // get not actual index
            ulBufferIndex %= CDDSTP88XX_HALSTP_HsInfoBufLen;
          }
        }
        else                                                                                // not moving or moving but actual entry is not new calculated
        {
          // jk-orig 70514 unDtc = CddStpPrjLwr_GetDmaCount();                                               // actual DMA transfer count LWR - equal to actual value (no DMA transfer)
          // 'modified' 70516:
          // nothing to do
        }
        ulBufferIndexAct = CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx;
      }
///// __EI();            // call from interrupt level is not possible (no counter)!
///// osEnableGlobal();  // call from interrupt level is not possible (no counter)!
//!   ResumeAllInterrupts();

      return ulBufferIndex;

      // PRQA S 5336 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5336(HIS metrics violation: 'CddStp88XX_HalStpLwr_GetWriteIx() : STMIF = 5' exceeds threshold 4 for Number nesting of control structures (STMIF).) Depth: 0 Ref: 
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SetActPos_
    ///
    ///  \brief  Set actual position of LWR
    ///
    ///  \param  const sint32 ln
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_SetActPos_(const sint32 ln)
    {
///// __DI();             // call from interrupt level is not possible (no counter)!
///// osDisableGlobal();  // call from interrupt level is not possible (no counter)!
//Lr06      SuspendAllInterrupts();
// jk-tbd-HW-02       uint32 ulDisableIntKey;
// jk-tbd-HW-02       ulDisableIntKey = __DIR();
      
      CddStp88XX_HalStp_StpInfoLwr.lActPos = ln;
      
///// __EI();            // call from interrupt level is not possible (no counter)!
///// osEnableGlobal();  // call from interrupt level is not possible (no counter)!
//Lr06      ResumeAllInterrupts();
// jk-tbd-HW-02       __RIR(ulDisableIntKey);
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
    STATIC_AL void CddStp88XX_HalStpLwr_SetActPos(const sint32 ln)
    {
      CddStp88XX_HalStpLwr_SetActPos_(ln);
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_IncActPos_
    ///
    ///  \brief  Increment actual position of LWR
    ///
    ///  \param  const sint32 ln
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_IncActPos_(const sint32 ln)
    {
///// __DI();             // call from interrupt level is not possible (no counter)!
///// osDisableGlobal();  // call from interrupt level is not possible (no counter)!
//Lr06      SuspendAllInterrupts();
// jk-tbd-HW-02       uint32 ulDisableIntKey;
// jk-tbd-HW-02       ulDisableIntKey = __DIR();

      CddStp88XX_HalStp_StpInfoLwr.lActPos += ln;

///// __EI();            // call from interrupt level is not possible (no counter)!
///// osEnableGlobal();  // call from interrupt level is not possible (no counter)!
//Lr06      ResumeAllInterrupts();
// jk-tbd-HW-02       __RIR(ulDisableIntKey);
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
    STATIC_AL void CddStp88XX_HalStpLwr_IncActPos(const sint32 ln)
    {
      CddStp88XX_HalStpLwr_IncActPos_(ln);
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetActPos_
    ///
    ///  \brief  Get actual position of LWR
    ///
    ///  \param  none
    ///
    ///  \return sint32
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL sint32 CddStp88XX_HalStpLwr_GetActPos_(void)
    {
      return (CddStp88XX_HalStp_StpInfoLwr.lActPos);
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
    STATIC_AL sint32 CddStp88XX_HalStpLwr_GetActPos(void)
    {
      return CddStp88XX_HalStpLwr_GetActPos_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetPhaseCounter_
    ///
    ///  \brief  Get phase counter of LWR
    ///
    ///  \param  none
    ///
    ///  \return uint8
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint8 CddStp88XX_HalStpLwr_GetPhaseCounter_(void)
    {
      return (CddStp88XX_HalStp_ucPhaseCounterLwr);
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
    STATIC_AL uint8 CddStp88XX_HalStpLwr_GetPhaseCounter(void)
    {
      return CddStp88XX_HalStpLwr_GetPhaseCounter_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetStpInfo_
    ///
    ///  \brief  Get stepper information of LWR
    ///
    ///  \param  none
    ///
    ///  \return tStpInfo*
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL tStpInfo* CddStp88XX_HalStpLwr_GetStpInfo_(void)
    {
      return (&CddStp88XX_HalStp_StpInfoLwr);
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
    STATIC_AL tStpInfo* CddStp88XX_HalStpLwr_GetStpInfo(void)
    {
      return CddStp88XX_HalStpLwr_GetStpInfo_();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_HandleMotEn_
    ///
    ///  \brief  Handle Enable Motor actions and global variables
    ///
    ///  \param  boolean boMotEn
    ///          boolean boSendCReg12 -  // UWY manipulate send always CReg1 and CReg2 (cyclic)
    ///
    ///  \return none
    ///
    ///  \descr  function of ISR timer stepping clock LWR.
    ///          to handle MotEn and current actions and global variables.
    ///          CddStp88XX_HalStp_BitsLwr.Bit.biMotEn - is changed by this routine!
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_HandleMotEn_(boolean boMotEn, boolean boSendCReg12)
    {
      boolean boMotEn_ = (CddStp88XX_HalStp_BitsLwr.Bit.biMotEn == 1u) ? TRUE : FALSE;
      
      // changed?
      if (boMotEn != boMotEn_)
      {
        CddStp88XX_HalStp_BitsLwr.Bit.biMotEn = ((boMotEn != FALSE) ? 1u : 0u);

        // jk-tbd: set 'EN_OL', too (...:'Cod_LwrTestOlIgnor')
        CddStp88XX_HalStp_BitsLwr.Bit.biTbdEnOlDtctn = CddStp88XX_HalStp_BitsLwr.Bit.biMotEn; // En-/Dis-able Open-Load-Detection due to 'MOTEN'/'DISOUT' - Ctrl-Reg '4'

        if (boSendCReg12 != FALSE)                         // UWY manipulate send always CReg1 and CReg2 (cyclic)
        {
          (void)CddStp88XX_HalStpLwr_SpiSendCReg2(TRUE);   // send MotorEnable (bit MotEn) by SPI
          (void)CddStp88XX_HalStpLwr_SpiSendCReg1(TRUE);   // send also TRQ_DAC (current by SPI) // UWY - DRV8899 has two registers for MotEn and current
          (void)CddStp88XX_HalStpLwr_SpiSendCReg4(TRUE);   // send also EN_OL (Open-Load-Detection by SPI)
        }
      }
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
    STATIC_AL void CddStp88XX_HalStpLwr_HandleMotEn(boolean boMotEn, boolean boSendCReg12)
    {
      CddStp88XX_HalStpLwr_HandleMotEn_(boMotEn, boSendCReg12);
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_StartStp
    ///
    ///  \brief  Start stepping interrupt state machine of LWR
    ///
    ///  \param  none
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_StartStp(void)
    {
      CddStp88XX_HalStp_BitsLwr.Bit.biStopStpPZ = 0;
      CddStp88XX_HalStp_BitsLwr.Bit.biStopStp = 0;

      if (CddStp88XX_HalStpLwr_IsStateHoldCont_() != FALSE) // avoid asynchronous call of state machine
      {
        uint32 ulBufferLastIndex = CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx - 1u; // 64-er buffer
        
        ulBufferLastIndex %= CDDSTP88XX_HALSTP_HsInfoBufLen; // falls ins negative gerutscht
        
        // in case of wrong result of CddStp88XX_HalStpXxx_GetWriteIx() the hanging CddStp88XX_HalStp state machine 
        // can be reset for correct CddStpDyn calculation by setting biLastStep bit of last entry (condition for biFirstStep):
        CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferLastIndex].Bit.biLastStep = 1;
        CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferLastIndex].Bit.biPause = 1;    // additional change for safer work
        CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferLastIndex].Bit.biSet = 0;      // additional change for safer work

        if (CddStp88XX_HalStp_BitsLwr.Bit.biMotEn == 0u)     // not motor enable?
        {
          CddStp88XX_HalStpLwr_HandleMotEn_(TRUE, TRUE);    // motor enable, send SPI commands asynchronous
        }

        CddStp88XX_HalStpLwr_StateMachine(CddStp88XX_HalStp_eCmdStartStp);
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_ResetStp
    ///
    ///  \brief  Reset state machine of LWR
    ///
    ///  \param  boolean boMotEn
    ///          = TRUE:   set motor enable
    ///          = FALSE:  set motor disable
    ///
    ///  \return none
    ///
    ///  \descr  Reset state machine and stepping buffer of LWR:
    ///          - disable stepping interrupt
    ///          - set stepping clock output to low level
    ///          - reset phase counter
    ///          - reset stepping buffer
    ///          - reset stepping buffer index
    ///          - reset state machine
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_ResetStp(boolean boMotEn)
    {
      CddStp88XX_HalStp_eStateLwr = CddStp88XX_HalStp_eStateHoldCont; // avoid pending stop stepper command in StopStp() before call of StopStp_()! Therefore here once more: reset state machine (!not CddStp88XX_HalStp_eStateInit!)
      CddStp88XX_HalStpLwr_StopStp(boMotEn);
//    CddStp88XX_HalStp_ulHsCntLwr = 0;                                // reset step counter (not compatible to Afs2)
      #if(CFG_OPT_STATISTIC & CFG_Statistic_ExtendedStpLwr)
        CddStp88XX_HalStp_ucCycleHsCntLwr = 0;                         // reset cycle step counter for SysCn
      #endif
      CddStp88XX_HalStp_ucPhaseCounterLwr = 0;                         // reset phase counter

      { // see CddStp88XX_HalStpLwr_StartStp() which can also called asynchronous from task level: prepare CddStpDyn conditions to start of a motion
        uint32 ulBufferLastIndex = CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx - 1u; 

        ulBufferLastIndex %= CDDSTP88XX_HALSTP_HsInfoBufLen;

        // in case of wrong result of CddStp88XX_HalStpXxx_GetWriteIx() the hanging CddStp88XX_HalStp state machine 
        // can be reset for correct CddStpDyn calculation by setting biLastStep bit of last entry (condition for biFirstStep):
        CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferLastIndex].Bit.biLastStep = 1;
        CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferLastIndex].Bit.biPause = 1;    // additional change for safer work
        CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[ulBufferLastIndex].Bit.biSet = 0;      // additional change for safer work
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_StopStp_
    ///
    ///  \brief  Stop state machine of LWR
    ///
    ///  \param  boolean boMotEn
    ///          = TRUE:   set motor enable
    ///          = FALSE:  set motor disable
    ///
    ///  \return none
    ///
    ///  \descr  Stop state machine of LWR:
    ///          - disable stepping interrupt
    ///          - set stepping clock output to low level
    ///          - reset stepping buffer
    ///          - reset stepping buffer index
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_StopStp_(boolean boMotEn)
    {
      boolean boDir;

      CddStp88XX_HalStpLwr_HandleCurAmplt_(CDDSTP88XX_eCurAmpltStateHold, CDDSTP88XX_eCurAmpltNoChange, CDDSTP88XX_eCurAmpltNoChange);
      CddStpPrjLwr_TSP_ForceTimerLow();                                              // yet: only 'CddStp_Tsp_Stop(0)' - but it only works in CAT2-ISR StpTimer0Notification() - CddStp88XX_HalStpVer_TimerCb()
      CddStp88XX_HalStpLwr_EmptyBuffer();                                            // reset stepping buffer and buffer index
      CddStp88XX_HalStp_eStateLwr = CddStp88XX_HalStp_eStateHoldCont;                // reset state machine (!not CddStp88XX_HalStp_eStateInit!)
      boDir = CDDSTP8899_DirPos;                                                     // reset direction

      #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
      #else // Unit-Tests!
        boDir = CddStp_UnitTestHelper_bo1;
      #endif

      CddStp88XX_HalStp_BitsIntLwr.Bit.biDirection = ((boDir != FALSE) ? 1u : 0u);   // dir stepper (...:'HW-Pin')
      if (CddStp88XX_GetBits(CFG_Stp_IdxVer)->Bit.biRichtung == 1u)                  // direction inverted?
      {
        boDir = (boDir == FALSE) ? TRUE : FALSE;                                                              // invert
      }
      (void)CddStp8899_HalStp_SetDIR(boDir);                                         // update port Dio_DIR_LWR
      CddStp88XX_HalStpLwr_HandleMotEn_(boMotEn, TRUE);                              // send register in CddStp88XX_HalStpLwr_SendCRegAll() // UWY manipulate send always CReg1 and CReg2 (cyclic)
      (void)CddStp88XX_HalStpLwr_SpiSendCRegAll();                                   // send CReg1 to send new boMotEn content but also CReg2...7 because of DRV property: clear the content of CRegs in case of undervoltage.
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_StopStp
    ///
    ///  \brief  Stop state machine of LWR by respecting half steps
    ///
    ///  \param  boolean boMotEn
    ///          = TRUE:   enable motor
    ///          = FALSE:  disable motor
    ///
    ///  \return none
    ///
    ///  \descr  Stop state machine of LWR by respecting half steps (finish timer after whole HS):
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_StopStp(boolean boMotEn)
    {
      boolean boIsStateHoldCont = CddStp88XX_HalStpLwr_IsStateHoldCont_();
      boolean boIsStateTestStep = CddStp88XX_HalStpLwr_IsStateTestStep_(); 
      
      if (   (boIsStateHoldCont != FALSE)                               // avoid asynchronous call of state machine
          || (boIsStateTestStep != FALSE) )
      {
        CddStp88XX_HalStpLwr_StopStp_(boMotEn);
      }
      else // finish timer after whole HS
      {
        CddStp88XX_HalStp_BitsLwr.Bit.biStopStpPZ = (boMotEn == FALSE) ? TRUE : FALSE; // !boMotEn; // not motor enable
        CddStp88XX_HalStp_BitsLwr.Bit.biStopStp = 1;
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_EmptyBuffer
    ///
    ///  \brief  Reset LWR buffer variables [actual stepping position,] stepping buffer and buffer index
    ///
    ///  \param  none
    ///
    ///  \return none
    ///
    ///  \descr  Reset following LWR stepping buffer variables:
    ///          - reset stepping buffer
    ///          - reset stepping buffer index
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_EmptyBuffer(void)
    {
      // reset stepping buffer
      // PRQA S 316, 4464 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio5) Msg: 316([I] Cast from a pointer to void to a pointer to object type.) Depth: 0 Ref: MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
      UtilMemClr((uint8*)(void*)CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf, ((uint8_least)sizeof(tHsInfo) * CDDSTP88XX_HALSTP_HsInfoBufLen));
      CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx = 0;    // reset stepping buffer index
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SendCReg1
    ///
    ///  \brief  Send the actual register value to control register number 1 of LWR DRV88XX
    ///
    ///  \param  boolean boSend
    ///
    ///  \return boolean
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL boolean CddStp88XX_HalStpLwr_SendCReg1(boolean boSend)
    {
      // **********  8899 **********
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      // alle xxx_SendCRegX in der Form nicht notwendig sondern dort jeweils NUR den MIRROR setzen
      // **********  8899 **********
      //
      boolean boReturn = FALSE;

      // ------------ DRV8899 LWR: Control register 1 ------------
      CddStp88XX_HalStp_aucSPI_TX[CFG_Stp_IdxVer][CddStp88XX_HalStp_eCReg1] = (uint8)  (                      // SPI buffer index 0
                               ((uint8) (CDDSTP88xx_default_SLEW_RATE      << CDDSTP88xx_BitPos_SLEW_RATE))
                             | ((uint8) (CddStp88XX_HalStp_ucCurAmpltLwr   << CDDSTP88xx_BitPos_TRQ_DAC))     // (Torque-DAC (S.17): 0000b = 100% ... 1111b = 6.25%)
                            );
      CddStp8899Com_SetCReg1(CFG_Stp_IdxVer, CddStp88XX_HalStp_aucSPI_TX[CFG_Stp_IdxVer][CddStp88XX_HalStp_eCReg1]);
      if (boSend != FALSE)
      {
//      CddStp8899Com_StReqSingle(CFG_Stp_IdxVer, CDDSTP8899_SpiSt_WriteCr12_ReadCr12); // - not used because of it is sent cyclic in schedule table 0
        boReturn = TRUE;
      }

      #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
      #else // Unit-Tests!
        boReturn = CddStp_UnitTestHelper_bo1; 
      #endif

      return (boReturn != FALSE) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SendCReg2
    ///
    ///  \brief  Send the actual register value to control register number 2 of LWR DRV88XX
    ///
    ///  \param  boolean boSend
    ///
    ///  \return boolean
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL boolean CddStp88XX_HalStpLwr_SendCReg2(boolean boSend)
    {
      // **********  jk-tbd  8899 **********
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      // alle xxx_SendCRegX in der Form nicht notwendig sondern dort jeweils NUR den MIRROR setzen
      // **********  jk-tbd  8899 **********
      //
      // jk-tbd    die var 'CddStp88XX_HalStp_ucCurAmpltLwr' bleibt erhalten!!!
      //
      boolean boReturn = FALSE;
      uint16 unDisOut = 0;

      // jk-ok: unDisOut = CddStp88XX_HalStp_BitsLwr.unRaw & 0x0080u; // take only this bit '7' DIS_OUT
                unDisOut = CddStp88XX_HalStp_BitsLwr.Bit.biMotEn; // N.b.: var is yet NOT 'ready'!
      // jk-ok: unDisOut = unDisOut ^ 0x0080u; // XOR: toggle bit '7' DIS_OUT (MotEn=Motor-Enable <-> DisOut=Disable Output)
                unDisOut = (unDisOut == 0u) ? 1u : 0u; // swap:  MotEn = Motor-Enable  <->  DisOut = Disable Output

      // ------------ DRV8899 LWR: Control register 2 ------------
      CddStp88XX_HalStp_aucSPI_TX[CFG_Stp_IdxVer][CddStp88XX_HalStp_eCReg2] = (uint8)  (                      // SPI buffer index 1
                               ((uint8) (CDDSTP88xx_default_DECAY      << CDDSTP88xx_BitPos_DECAY))
                             | ((uint8) (CDDSTP88xx_default_TOFF       << CDDSTP88xx_BitPos_TOFF))
                             | ((uint8) (unDisOut                      << CDDSTP88xx_BitPos_DIS_OUT))
                            );
      CddStp8899Com_SetCReg2(CFG_Stp_IdxVer, CddStp88XX_HalStp_aucSPI_TX[CFG_Stp_IdxVer][CddStp88XX_HalStp_eCReg2]);
      if (boSend != FALSE)
      {
//      CddStp8899Com_StReqSingle(CFG_Stp_IdxVer, CDDSTP8899_SpiSt_WriteCr12_ReadCr12); // - not used because of it is sent cyclic in schedule table 0
        boReturn = TRUE;
      }

      #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
      #else // Unit-Tests!
        boReturn = CddStp_UnitTestHelper_bo1; 
      #endif

      return (boReturn != FALSE) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SendCReg3
    ///
    ///  \brief  Send the actual register value to control register number 3 of LWR DRV88XX
    ///
    ///  \param  boolean boSend
    ///
    ///  \return boolean
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL boolean CddStp88XX_HalStpLwr_SendCReg3(boolean boSend)
    {
      // **********  8899 **********
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      // alle xxx_SendCRegX in der Form nicht notwendig sondern dort jeweils NUR den MIRROR setzen
      // **********  8899 **********
      //
      boolean boReturn = FALSE;

      // ------------ DRV8899 LWR: Control register 3 ------------
      CddStp88XX_HalStp_aucSPI_TX[CFG_Stp_IdxVer][CddStp88XX_HalStp_eCReg3] = (uint8)  (                          // SPI buffer index 2
                         //tbd ((uint8) CddStp88XX_HalStp_ucStepModeLwr      << CDDSTP88xx_BitPos_MICROSTEP_MODE)
                               ((uint8) (CDDSTP88xx_default_MICROSTEP_MODE   << CDDSTP88xx_BitPos_MICROSTEP_MODE))
                             | ((uint8) (CDDSTP88xx_default_SPI_STEP         << CDDSTP88xx_BitPos_SPI_STEP))      // not used
                             | ((uint8) (CDDSTP88xx_default_SPI_DIR          << CDDSTP88xx_BitPos_SPI_DIR))       // currently: 0 due to HW-Pin
                             | ((uint8) (CDDSTP88xx_default_STEP             << CDDSTP88xx_BitPos_STEP))          // not used
                             | ((uint8) (CDDSTP88xx_default_DIR              << CDDSTP88xx_BitPos_DIR))           // currently: 0 due to HW-Pin
                            );
      CddStp8899Com_SetCReg3(CFG_Stp_IdxVer, CddStp88XX_HalStp_aucSPI_TX[CFG_Stp_IdxVer][CddStp88XX_HalStp_eCReg3]);
      if (boSend != FALSE)
      {
        /*jk-tbd - Not Needed Any Longer*/ // CddStp8899Com_StReqSingle(CFG_Stp_IdxVer, CDDSTP8899_SpiSt_WriteCr34A67_ReadCr34A67);
        boReturn = TRUE;
      }

      #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
      #else // Unit-Tests!
        boReturn = CddStp_UnitTestHelper_bo1; 
      #endif

      return (boReturn != FALSE) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SendCReg4
    ///
    ///  \brief  Send the actual register value to control register number 4 of LWR DRV88XX
    ///
    ///  \param  boolean boSend
    ///
    ///  \return boolean
    ///
    ///  \descr 
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL boolean CddStp88XX_HalStpLwr_SendCReg4(boolean boSend)
    {
      // **********  8899 **********
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      // alle xxx_SendCRegX in der Form nicht notwendig sondern dort jeweils NUR den MIRROR setzen
      // **********  8899 **********
      //
      boolean boReturn = FALSE;

      // jk-tbd ??? uint8 ucEnOl = CddStp88XX_HalStp_BitsLwr.Bit.biTbdEnOlDtctn == 0u ? 0u : 1u; // -> 'Cod_LwrTestOlIgnor' / 'biMotEn'
      // biDisOLDetect
      //    OL: NICHT Anhalten/Abschalten!!  -- danach: LATCH LOESCHEN!!
      //    Pruefen: Ist die Unterdrueckung der OL-Erkennung WAEHREND der Verstellung (move & ref) notwendig
      //    biMotEn / biTbdEnOlDtctn / EnOl
      uint8 ucEnOl = ((CddStp88XX_aBitsMod[CFG_Stp_IdxVer].Bit.biDisOLDetect != FALSE) || 
                      (CddStp88XX_boIgnoreOLDetection != FALSE)) ? FALSE : TRUE; // Disable OL-Detection during Moving (no Pseudo-Errors - similar to HCM)
					  
	  // jk-new
      // PRQA S 4558 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (||).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
      if (   ((CddStp88XX_HalStp_BitsLwr.Bit.biMotEn                 == 0u) ? TRUE : FALSE)  // e.g. 'MotEn'=0  ->  'DisOut'=1
          || ((CddStp88XX_aBitsMod[CFG_Stp_IdxVer].Bit.biDisOLDetect != 0u) ? TRUE : FALSE)
         )
      {
        ucEnOl = FALSE;
      }

      uint8 ucTbdClrTiFaultBits = CddStp88XX_HalStp_BitsLwr.Bit.biTbdClrTiFaultBits;
      // NOT here: CddStp88XX_HalStp_BitsLwr.Bit.biTbdClrTiFaultBits = 0; // reset: do clear the TI-Fault-Bits only ONCE
 
       // ------------ DRV8899 LWR: Control register 4 ------------
       CddStp88XX_HalStp_aucSPI_TX[CFG_Stp_IdxVer][CddStp88XX_HalStp_eCReg4] = (uint8) (                         // SPI buffer index 3 = Ctrl-Reg '4'
                                ((uint8) (CDDSTP88xx_default_TW_REP     << CDDSTP88xx_BitPos_TW_REP))    // '1' - 1b = Over- or undertemp. warning is reported on the nFAULT line | 0b = Over- or undertemp. warning is not reported on the nFAULT line
                              | ((uint8) (CDDSTP88xx_default_OTSD_MODE  << CDDSTP88xx_BitPos_OTSD_MODE)) // '0' - 0b = Overtemperature condition will cause latched fault | 1b = Overtemperature condition will cause automatic recovery fault
                              | ((uint8) (CDDSTP88xx_default_OCP_MODE   << CDDSTP88xx_BitPos_OCP_MODE))  // '0' - 0b = Overcurrent condition causes a latched fault | 1b = Overcurrent condition causes an automatic retrying fault
                              | ((uint8) (ucEnOl                        << CDDSTP88xx_BitPos_EN_OL))     // 'x' - Write '1' to enable open load detection (... 'u1EN_OL'!) ('Cod_LwrTestOlIgnor') ('DIS_OUT' = 'Hi-Z all outputs': Ensure OL fault detection is disabled before making the outputs Hi-Z)
                              | ((uint8) (CDDSTP88xx_default_LOCK       << CDDSTP88xx_BitPos_LOCK))      // '3' - Write 110b to lock the settings by ignoring further register writes except to these bits and address 0x06h bit 7 (CLR_FLT). Writing any sequence other than 110b has no effect when unlocked. Write 011b to this register to unlock all registers. Writing any sequence other than 011b has no effect when locked.
                              | ((uint8) (ucTbdClrTiFaultBits           << CDDSTP88xx_BitPos_CLR_FLT))   // 'x' - Write '1' to this bit to clear all latched fault bits. This bit automatically resets after being written.
                              );
       CddStp8899Com_SetCReg4(CFG_Stp_IdxVer, CddStp88XX_HalStp_aucSPI_TX[CFG_Stp_IdxVer][CddStp88XX_HalStp_eCReg4]);
       if (boSend != FALSE)
       {
         /*jk-tbd - Not Needed Any Longer*/ // CddStp8899Com_StReqSingle(CFG_Stp_IdxVer, CDDSTP8899_SpiSt_WriteCr34A67_ReadCr34A67);
         boReturn = TRUE;
       }

      #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
      #else // Unit-Tests!
        boReturn = CddStp_UnitTestHelper_bo1; 
      #endif

      return (boReturn != FALSE) ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_SendCRegAll
    ///
    ///  \brief  Send all DRV88XX LWR control registers with values which depend on actual variables
    ///
    ///  \param  none
    ///
    ///  \return boolean
    ///
    ///  \descr  All DRV88XX LWR control registers with values which depend on actual variables are sent:
    ///          - include CSN pin handling
    ///          - Control register 0
    ///          - Control register 1
    ///          - Control register 2
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL boolean CddStp88XX_HalStpLwr_SendCRegAll(void)
    {
      // **********  8899 **********
      // in den CddStp88XX_HalStpLwr_SendCRegX()-Funktionen werden nur noch in die TX-Mirror-Variablen die aktuellen Steuervariablen einmaskiert 
      // alle xxx_SendCRegX in der Form nicht notwendig sondern dort jeweils NUR den MIRROR setzen
      // **********  8899 **********
      //
      boolean boReturn = FALSE;

      // PRQA S 4404, 4558, 3415 13 // program architecture and readability - intentionally no modification of existing code
      //                            warning - QAC(Prio7) Msg: 4404(An expression of 'essentially Boolean' type (_Bool) is being converted to unsigned type, 'unsigned char' on assignment.) Depth: 0 Ref: MISRA C:2012 Rule-10.3
      //                            warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type(unsigned char) is being used as the left - hand operand of this logical operator ( || ).) Depth : 0 Ref : MISRA C : 2012 Rule - 10.1
      //                            warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type(unsigned char) is being used as the right - hand operand of this logical operator ( || ).) Depth : 0 Ref : MISRA C : 2012 Rule - 10.1
      //                            warning - QAC(Prio7) Msg: 3415(Right hand operand of '&&' or '||' is an expression with possible side effects.) Depth : 0 Ref : MISRA C : 2012 Rule - 13.5; REFERENCE - ISO:C90 - 5, 1, 2, 3 Program Execution

      // ------------ DRV88XX LWR: Control register 1 ------------
      boReturn = boReturn || CddStp88XX_HalStpLwr_SendCReg1(FALSE);   // copy value but do not send - is done at last CReg7: SendCReg7(TRUE)
      // ------------ DRV88XX LWR: Control register 2 ------------
      boReturn = boReturn || CddStp88XX_HalStpLwr_SendCReg2(FALSE);   // copy value but do not send - is done at last CReg7: SendCReg7(TRUE)
      // ------------ DRV88XX LWR: Control register 3 ------------
      boReturn = boReturn || CddStp88XX_HalStpLwr_SendCReg3(FALSE);   // copy value but do not send - is done at last CReg7: SendCReg7(TRUE)
      // ------------ DRV88XX LWR: Control register 4 ------------
      boReturn = boReturn || CddStp88XX_HalStpLwr_SendCReg4(FALSE);  // copy value but do not send - is done at last CReg7: SendCReg7(TRUE)

      #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
      #else // Unit-Tests!
        boReturn = CddStp_UnitTestHelper_bo1; 
      #endif

      return boReturn;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_CalcCount
    ///
    ///  \brief  Calculate next LWR step count value to load in CDR
    ///
    ///  \param  const uint32 ulCount: data of CDR register
    ///
    ///  \return uint32 ulCdrVal calculated CDR timer register value
    ///
    ///  \descr  Calculate of the LWR count value to load in CDR for the next step.
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint32 CddStp88XX_HalStpLwr_CalcCount(const uint32 ulCount)
    {
      return (ulCount - TSP_IOC4DELAY);
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_StepReload
    ///
    ///  \brief  Set LWR compare register for stepping clock port
    ///
    ///  \param  const uint32 ulCount: data of CDR register
    ///          e.g. CDDSTP88XX_HALSTP_INIT, CDDSTP88XX_HALSTP_HOLD, ulCount, CDDSTP88XX_HALSTP_TESTSTEPSPI, CDDSTP88XX_HALSTP_TESTSTEPPULSE
    ///
    ///  \return none
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_StepReload(const uint32 ulCount)
    {
      uint32 ulCdrVal = CddStp88XX_HalStpLwr_CalcCount(ulCount); // inside: return (ulCount - TSP_IOC4DELAY);

      CddStpPrj_AddTimerOffset(CFG_Stp_IdxVer, &ulCdrVal); // inside: none/obsolet

      // jk-tbd: NOT this timer! CddStpPrjLwr_StartTsp( ulCdrVal);  // -> CB: 'CddStp88XX_HalStpVer_TimerCb'
                                 CddStpPrjLwr_GPT_StartHelp(ulCdrVal);  // -> Gpt_StartTimer(0, ulCount) -> IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'

      // prepare HW-Debugging via Pin-Toggling: HSS-1: X0-Sample - Pin X4006-4
      // IoHwAb_SetDo(DioConf_DioChannel_DioChannel_HSS_1, STD_HIGH); // Pin: #define DioConf_DioChannel_DioChannel_HSS_1 88U  |  TEST!!!!!!!!!!!!!!!!
    }


    //-----------------------------------------------------------------------------
    /// \brief  StpTimer0Notification
    ///
    /// \descr  IRQ and callback at the end due to ' Gpt_StartTimer(0, ulCount);'
    ///
    ///         2 different timers for LWR-Stepclock:
    ///          CddStp_Tsp_Start(0, count);   // Stepper-Timer: HW-Pin-Toggling With u-Steps
    ///          Gpt_StartTimer(  0, count);   // Help-Timer:    IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'
    ///
    /// \param  -
    ///
    /// \return StpTimer0Notification
    //-----------------------------------------------------------------------------
    
    //void StpTimer0Notification(void)
    //{
    //  // LWR
    //  CddStp88XX_HalStpVer_TimerCb();
    //}

    // jk-obsolet void StpTimer1Notification(void) { /* AHL - obsolet */ }
    // jk-obsolet void StpTimer2Notification(void) { /* LLR - obsolet */ }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_HandleCurAmplt_
    ///
    ///  \brief  Handle CurAmplt actions and global variables
    ///
    ///  \param  tCurAmpltStateCddStp88XX eCurAmpltState CDDSTP88XX_eCurAmpltStateHold:      hold current
    ///                                                   CDDSTP88XX_eCurAmpltStateNorm:      norm current
    ///                                                   CDDSTP88XX_eCurAmpltStateNoChange:  no change of current state
    ///          uint8 ucCurAmpltHold
    ///          uint8 ucCurAmpltRun
    ///
    ///  \return none
    ///
    ///  \descr  function of ISR timer stepping clock LWR.
    ///          to handle CurAmplt actions and global variables.
    ///          uint8 CddStp88XX_HalStp_ucCurAmpltLwr - is changed by this routine!
    ///          uint8 CddStp88XX_HalStp_ucCurAmpltOldLwr - is changed by this routine!
    ///          tCurAmpltStateCddStp88XX CddStp88XX_HalStp_eCurAmpltStateLwr - is changed by this routine!
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_HandleCurAmplt_(tCurAmpltStateCddStp88XX eCurAmpltState, uint8 ucCurAmpltHold, uint8 ucCurAmpltRun)
    {
      STATIC_AL uint8                     CddStp88XX_HalStp_ucCurAmpltHoldLwr; // = CddStp88XX_aucCurAmpltHoldTemp[CFG_Stp_IdxVer] [CddStp_eTempState_NormTemp];
      STATIC_AL uint8                     CddStp88XX_HalStp_ucCurAmpltRunLwr;  //  = CddStp88XX_aucCurAmpltRunTemp[CFG_Stp_IdxVer] [CddStp_eTempState_NormTemp];
      STATIC_AL tCurAmpltStateCddStp88XX  CddStp88XX_HalStp_eCurAmpltStateLwr;
      
      if (eCurAmpltState < CDDSTP88XX_eCurAmpltStateNoChange)   // change current amplitude state
      {
        CddStp88XX_HalStp_eCurAmpltStateLwr = eCurAmpltState;
      }

      if (ucCurAmpltHold < CDDSTP88XX_eCurAmpltNoChange)   // change hold current amplitude
      {
        CddStp88XX_HalStp_ucCurAmpltHoldLwr = ucCurAmpltHold;
      }

      if (ucCurAmpltRun < CDDSTP88XX_eCurAmpltNoChange)   // change norm current amplitude
      {
        CddStp88XX_HalStp_ucCurAmpltRunLwr = ucCurAmpltRun;
      }

      #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
      #else // Unit-Tests!
        // all the 'real' results are fixed so use this way to do full coverage
        CddStp88XX_HalStp_eCurAmpltStateLwr = (CddStp_UnitTestHelper_bo1 != FALSE) ? CddStp_UnitTestHelper_ul1 : CddStp88XX_HalStp_eCurAmpltStateLwr;
      #endif

      switch (CddStp88XX_HalStp_eCurAmpltStateLwr)
      {
      case CDDSTP88XX_eCurAmpltStateHold:
        CddStp88XX_HalStp_ucCurAmpltLwr = CddStp88XX_HalStp_ucCurAmpltHoldLwr;
        break;

      case CDDSTP88XX_eCurAmpltStateNorm:
        CddStp88XX_HalStp_ucCurAmpltLwr = CddStp88XX_HalStp_ucCurAmpltRunLwr;
        break;

      case CDDSTP88XX_eCurAmpltStateNoChange:
      default:
        break;
      }

      if (CddStp88XX_HalStp_ucCurAmpltLwr != CddStp88XX_HalStp_ucCurAmpltOldLwr)
      {
        CddStp88XX_HalStp_ucCurAmpltOldLwr = CddStp88XX_HalStp_ucCurAmpltLwr;
        if (CddStp88XX_HalStp_BitsLwr.Bit.biInit == 1u)                   // HalStp is initialized? - now CddStp88XX_HalStpLwr_HandleCurAmplt_() sends CReg1 values by SPI
        {
          (void)CddStp88XX_HalStpLwr_SpiSendCReg1(TRUE);                 // send CURrent amplitude by SPI
        }
      }
    }

    // interface function for other modules CddStp88XX_HalStpXxx_Yyy() over pointer access CddStp88XX_HalStpFct[Index of Xxx].pYyy():
    STATIC_AL void CddStp88XX_HalStpLwr_HandleCurAmplt(uint8 ucCurAmpltState, uint8 ucCurAmpltHold, uint8 ucCurAmpltRun)
    {
      // PRQA S 4342 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio5) Msg: 4342(An expression of 'essentially unsigned' type (unsigned char) is being cast to enum type 'tCurAmpltStateCddStp88XX'.) Depth: 0 Ref: MISRA C:2012 Rule-10.5
      CddStp88XX_HalStpLwr_HandleCurAmplt_((tCurAmpltStateCddStp88XX)ucCurAmpltState, ucCurAmpltHold, ucCurAmpltRun);
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_GetCurAmplt
    ///
    ///  \brief  Get current amplitude CurAmplt
    ///
    ///  \param  none
    ///
    ///  \return uint8 CddStp88XX_HalStp_ucCurAmpltLwr
    ///
    ///  \descr  Get actual current amplitude state of LWR!
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint8 CddStp88XX_HalStpLwr_GetCurAmplt(void)
    {
      return CddStp88XX_HalStp_ucCurAmpltLwr;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_HandleInc
    ///
    ///  \brief  Handle increment actions and global variables of LWR
    ///
    ///  \param  boolean boIncCntActPos          TRUE:  increment system step counter, phase counter and actual position
    ///                                          FALSE: no increment system step counter, phase counter and actual position
    ///          boolean boIncBufIx              TRUE:  increment buffer index
    ///                                          FALSE: no increment buffer index
    ///
    ///  \return none
    ///
    ///  \descr  function of ISR timer stepping clock LWR
    ///          to handle increment actions and global variables.
    ///          uint32 CddStp88XX_HalStp_ulHsCntLwr               - is changed by this routine!
    ///          uint8 CddStp88XX_HalStp_ucCycleHsCntLwr           - is changed by this routine!
    ///          uint8 CddStp88XX_HalStp_ucPhaseCounterLwr         - is changed by this routine!
    ///          sint32 CddStp88XX_HalStp_StpInfoLwr.lActPos       - is changed by this routine!
    ///          uint32 CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx - is changed by this routine!
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_HandleInc(boolean boIncCntActPos, boolean boIncBufIx)
    {
      // increment system step counter, phase counter and actual position
      if (boIncCntActPos != FALSE)
      {
        CddStp88XX_HalStp_ulHsCntLwr++;
        
        // handling of reference current for bump reference run
//      if (CddStp88XX_HalStp_ucCARunRefCntLwr != 0)
//      {
//        CddStp88XX_HalStp_ucCARunRefCntLwr--;
//        if (CddStp88XX_HalStp_ucCARunRefCntLwr == 0u)
//        {
//          CddStp88XX_HalStpLwr_HandleCurAmplt(CDDSTP88XX_eCurAmpltStateNoChange, CddStp88XX_aucCurAmpltHoldTemp[CFG_Stp_IdxVer][CddStp88XX_aeTemp[CFG_Stp_IdxVer]], CddStp88XX_aucCurAmpltRunTemp[CFG_Stp_IdxVer][CddStp88XX_aeTemp[CFG_Stp_IdxVer]]); // decrease normal current from reference amplitude back to run amplitude
//        }
//      }
        
        #if(CFG_OPT_STATISTIC & CFG_Statistic_ExtendedStpLwr)
          if (CddStp88XX_HalStp_ucCycleHsCntLwr < 0xFF)
          {
            CddStp88XX_HalStp_ucCycleHsCntLwr++;
          }
        #endif

        // for actual step: calculate phase counter and increment/decrement actual position
// jk-orig  if (CddStp88XX_HalStp_BitsIntLwr.Bit.biDirection == (sint8)CDDSTP8899_DirPos)
        if     (CddStp88XX_HalStp_BitsIntLwr.Bit.biDirection ==        CDDSTP8899_DirPos)
        {
          CddStp88XX_HalStp_ucPhaseCounterLwr = (uint8)(CddStp88XX_HalStp_ucPhaseCounterLwr + CDDSTP8899_IncPhaseHS);
          CddStp88XX_HalStp_StpInfoLwr.lActPos++;
        }
        else
        {
          CddStp88XX_HalStp_ucPhaseCounterLwr = (uint8)(CddStp88XX_HalStp_ucPhaseCounterLwr - CDDSTP8899_IncPhaseHS);
          CddStp88XX_HalStp_StpInfoLwr.lActPos--;
        }
      }

      // increment buffer index
      if (boIncBufIx != FALSE)
      {
        CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx++;
        CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx %= CDDSTP88XX_HALSTP_HsInfoBufLen;
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func     CddStp88XX_HalStpLwr_HandleDir
    ///
    ///  \brief    Handle direction of LWR
    ///
    ///  \param    none
    ///
    ///  \return   boolean TRUE:  change of direction detected
    ///                 FALSE: no change of direction detected
    ///
    ///  \descr    Detect change of direction and set output pin.
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL boolean CddStp88XX_HalStpLwr_HandleDir(void)
    {
      // currently:SPI - future: HW-Pin

      boolean boReturn = FALSE;
      boolean boDir;

      boDir = CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].Bit.biDirection;

      // change of direction
      if (CddStp88XX_HalStp_BitsIntLwr.Bit.biDirection != boDir)
      {
        #if(CFG_OPT_STATISTIC & CFG_Statistic_ExtendedStpLwr)
          if (CddStp88XX_HalStp_ucCycleHsCntLwr != 0)                  // first change of direction?
          {
            CddStp88XX_HalStp_aucCyclesLwr[(uint8)(UTIL_PRIOR_8(CddStp88XX_HalStp_ucCycleHsCntLwr)) & 0x07]++;
            CddStp88XX_HalStp_ucCycleHsCntLwr = 0;
          }
        #endif

        boReturn = TRUE;

        CddStp88XX_HalStp_BitsIntLwr.Bit.biDirection = boDir;          // save direction if changed
        if (CddStp88XX_GetBits(CFG_Stp_IdxVer)->Bit.biRichtung == 1u)   // direction inverted?
        {
          boDir = (boDir == FALSE) ? TRUE : FALSE; // !boDir;                                               // invert
        }
        (void)CddStp8899_HalStp_SetDIR( boDir);                       // update port Dio_DIR_LWR
      }
      return (boReturn != FALSE) ? TRUE : FALSE;;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func     CddStp88XX_HalStpLwr_GetPause
    ///
    ///  \brief    Get pause bit of stepper buffer of LWR (no step)
    ///
    ///  \param    none
    ///
    ///  \return   boolean TRUE:  pause bit set
    ///                 FALSE: pause bit cleared
    ///
    ///  \descr    Get stepper buffer information bit 'Pause' of actual entry.
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL boolean CddStp88XX_HalStpLwr_GetPause(void)
    {
      return (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].Bit.biPause == 1u) ? TRUE : FALSE;;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_HandleTestStep
    ///
    ///  \brief  Handle test steps of LWR
    ///
    ///  \param  none
    ///
    ///  \return none
    ///
    ///  \descr  Special handling of test steps:
    ///          1. TestStep reads SReg3 micro step position (MSP)
    ///          2. If lowest MSP bit is zero:
    ///             Save StepMode and switch to StepMode 1/32 micro step and
    ///             create a next step clock (NXT)
    ///          3. TestStep reads SReg3 micro step position (MSP)
    ///          4. If lowest MSP bit is zero: error
    ///             If lowest MSP bit is set: switch back to saved StepMode
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_HandleTestStep(void)
    {
       /*jk-tbd*/ //CddStp88XX_HalStp_ulTestStepCntLwr = 7;/* jk-tbd */

       // jk-obsolet (void)CddStp8899Com_GetSReg3(CFG_Stp_IdxVer, &CddStp8899_aSReg3[CFG_Stp_IdxVer]);
 
 //!   SuspendAllInterrupts();
 
       switch (CddStp88XX_HalStp_ulTestStepCntLwr)
       {
         case 0u:
         {
           // jk-obsolet: no MSP-Pos-Check uint8 ucMspMask = (CddStp88XX_HalStp_BitsLwr.Bit.biHsMode == 1) ? CDDSTP8899_MSPMask_TS_HS : CDDSTP8899_MSPMask_TS_MS;
           
           {
              // Step-Mode: Half-Step or Micro-Step
              // jk-obsolet: No HS-Mode CddStp88XX_HalStp_ucStepModeOldLwr = CddStp88XX_HalStp_ucStepModeLwr;
              CddStp88XX_HalStp_ucStepModeLwr    = (CddStp88XX_HalStp_BitsLwr.Bit.biHsMode == 1u) ? CDDSTP8899_StepModeTS_HS : CDDSTP8899_StepModeTS_MS;

              // Timer:
              //  CddStp_Tsp_Start(0, count);   // Stepper-Timer: HW-Pin-Toggling With u-Steps
              //  Gpt_StartTimer(  0, count);   // Help-Timer:    IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'
              //
              // both timers: 1.: GPT (=Help-Timer with IRQ) & 2.: TSP (=Step-Clock-Timer)
              CddStpPrjLwr_BothTimers_Prepare(CDDSTP88XX_HALSTP_TESTSTEP,      CDDSTP88XX_HALSTP_TESTSTEP); // test step pulse time (CDDSTP88XX_HALSTP_TESTSTEP / 2) ms
              CddStpPrjLwr_BothTimers_Start(); // both timers: GPT (=Help-Timer with IRQ) & TSP (=Step-Clock-Timer)

              CddStp88XX_HalStp_ulTestStepCntLwr++; // forward to next 'case'
           }
           break;
         }

         case 1u:
           // jk-obsolet: No HS-Mode CddStp88XX_HalStp_ucStepModeLwr = CddStp88XX_HalStp_ucStepModeOldLwr;
           // ------------ DRV88XX LWR: Control register 3 ------------
           (void)CddStp88XX_HalStpLwr_SpiSendCReg3(TRUE);                                     // send StepMode by SPI
 
           CddStpPrjLwr_TSP_ForceTimerLow(); // yet: only 'CddStp_Tsp_Stop(0)' - TSP = Step-Clock-Timer
           CddStp88XX_HalStpLwr_StepReload(CDDSTP88XX_HALSTP_TESTSTEP);
           CddStp88XX_HalStp_ulTestStepCntLwr++; // forward to next 'case'
           break;
 
         // case '2'...'6': ISR/Callback: 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb' (due to 'StepReload' -> CddStpPrjLwr_GPT_StartHelp(ulCdrVal) -> Gpt_StartTimer(0, ulCount) )
         case 2u:
         case 3u:
         case 4u:
         case 5u:
         case 6u:

          // Timer:
           CddStpPrjLwr_TSP_ForceTimerLow(); // yet: only 'CddStp_Tsp_Stop(0)'
           CddStp88XX_HalStpLwr_StepReload(CDDSTP88XX_HALSTP_TESTSTEPSPI);                      // wait to detect SC or OL
           CddStp88XX_HalStp_ulTestStepCntLwr++; // forward to next 'case' i.e.:  5 & 6 & 7
           break;
 
         default:
         {
           // wrong definition of CDDSTP88XX_HALSTP_TestStepCntMax!
           CddStp88XX_HalStp_ulTestStepCntLwr++; // forward to next 'case'
           break;
         }
       }
 
 //!   ResumeAllInterrupts();
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_HandleCommonStep
    ///
    ///  \brief  Handle common code of the step states of LWR
    ///
    ///  \param  tStateHalStp
    ///
    ///  \return none
    ///
    ///  \descr  State function of ISR timer stepping clock LWR to handle common code of the step states
    ///          - CddStp88XX_HalStp_eStateFirstStep uses only help timer
    ///          - CddStp88XX_HalStp_eStateLastStep  uses only help timer
    ///          - CddStp88XX_HalStp_eStateStep      uses step timer.
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_HandleCommonStep(const tStateHalStp eState)
    {
      uint32 ulCount;
      boolean boIncCntActPos = FALSE;
      boolean boSet = FALSE;

      (void)eState;

      // check whether entry is set new and get time count
      if (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].Bit.biSet == 1u) // buffer entry set with new value?
      {
        boSet = TRUE;
        CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].Bit.biSet = 0;    // actual buffer entry is used

        CddStp88XX_HalStp_HSInfoBufSaveLwr.ulRaw = CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].ulRaw; // save last value
      }
      else // the entry is not calculated by CddStpDyn
      {
        CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].ulRaw = CddStp88XX_HalStp_HSInfoBufSaveLwr.ulRaw; // copy all information to avoid use of old setting
        CddStp88XX_HalStp_ulSet0Lwr++;                             // debug only, should never be incremented!
        (void)CddStp88XX_HalStp_ulSet0Lwr;                         // debug only, suppress LINT warning
      }
      ulCount = CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].Val.unHsTime; // rising slope of stepping clock: step time (X)
      
//BugFixRunCurrentEnsurement      if (eState == CddStp88XX_HalStp_eStateFirstStep)             // first Step
      {
        CddStp88XX_HalStpLwr_HandleCurAmplt_(CDDSTP88XX_eCurAmpltStateNorm, CDDSTP88XX_eCurAmpltNoChange, CDDSTP88XX_eCurAmpltNoChange);
      }

      // Pause bei: Vorbestromung, Umkehrung, Nachbestromung
      if (CddStp88XX_HalStpLwr_GetPause() != FALSE)                // first step with pause, last step or pause (no step)? -----------------------------------------------
      {
        // jk-workaround due to SPI-Delay instead of HW-Pin
        (void)CddStp88XX_HalStpLwr_HandleDir();                    // direction - currently:SPI - future: HW-Pin

        CddStpPrjLwr_TSP_ForceTimerLow();                          // yet: only 'CddStp_Tsp_Stop(0)'
//        SuspendAllInterrupts();
          /* Disable the global interrupt */
        DISABLE_INTERRUPTS();
        CddStp88XX_HalStpLwr_StepReload(ulCount - 50U);                  // and use CNT timer register value for CalcCount()
//        ResumeAllInterrupts();
            /* Enable the global interrupt*/
        ENABLE_INTERRUPTS();
//Check HalPort_DeactivateChkMse(); //Check
      }
      else                                                          // Step(s) --------------------------------------------------------------------------------------------
      {
//Check HalPort_ActivateChkMse(); //Check
        // start stepping by triggering step timer which handles the timer CDR register for creating pulse(s)
        (void)CddStp88XX_HalStpLwr_HandleDir();                    // direction - currently:SPI - future: HW-Pin
        boIncCntActPos = TRUE; 
        // jk: langsam: ca 10ms each HS = 10.000us  ->  TSP: 10k & Help-Timer: 10k/8 + ca. 15us   - in 10ms ein HS = in 10ms 8 uS
        //     schnell: ca 1ms  each HS
        //

        CddStpPrjLwr_BothTimers_Prepare((ulCount-30U), (ulCount/4u)); // TSP: check: HS oder uStepU
        CddStpPrjLwr_BothTimers_Start();

        //
      }

      CddStp88XX_HalStp_ulIrunTimeLwr += ulCount;              // add all Irun times by condition [tick] - note: before overflow StatM has to call CddStp88XX_HalStpLwr_GetIrunTime()
      CddStp88XX_HalStpLwr_HandleInc(boIncCntActPos, boSet);

      // PRQA S 5324 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio2) Msg: 5324(HIS metrics violation: 'CddStp88XX_HalStpLwr_HandleCommonStep() : STCAL = 8' exceeds threshold 7 for Number of Distinct Function Calls (STCAL).) Depth: 0 Ref: 
    }


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // LWR StateMachine transition functions
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ---------------------------------------------------------------------------
    ///
    ///  \func     CddStp88XX_HalStpLwr_TransitionInitHoldCont
    ///
    ///  \brief    LWR transition function from StateInit to StateHoldCont
    ///
    ///  \param    const tCommandHalStp eCmd
    ///
    ///  \return   uint32
    ///            = TRUE:  condition is valid
    ///            = FALSE: condition is not valid
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint32 CddStp88XX_HalStpLwr_TransitionInitHoldCont(const tCommandHalStp eCmd)
    {
      (void)eCmd;
      return TRUE;
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func     CddStp88XX_HalStpLwr_TransitionTestStepHoldCont
    ///
    ///  \brief    LWR transition function from StateTestStep to StateHoldCont
    ///
    ///  \param    const tCommandHalStp eCmd
    ///
    ///  \return   uint32
    ///            = TRUE:  condition is valid
    ///            = FALSE: condition is not valid
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint32 CddStp88XX_HalStpLwr_TransitionTestStepHoldCont(const tCommandHalStp eCmd)
    {
      boolean boIsSCCntMax;
      boolean boIsOLCntMax;

      (void)eCmd;

      // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
      // get Status-Register-FAULT contents from RAM mirror (verified)
      (void)CddStp8899Com_GetSRegDiag12(CFG_Stp_IdxVer, &CddStp8899_aSRegDiag1[CFG_Stp_IdxVer].ucRaw, &CddStp8899_aSRegDiag2[CFG_Stp_IdxVer].ucRaw);

      boIsSCCntMax = CddStp88XX_HalStpLwr_IsSCCntMax_();                                               // maximal value of overcurrent counter
      boIsOLCntMax = CddStp88XX_HalStpLwr_IsOLCntMax_();                                               // maximal value of openload counter

      return (   (boIsSCCntMax != FALSE)                                                   // maximal value of overcurrent counter
              || (boIsOLCntMax != FALSE)                                                   // maximal value of openload counter
              || ((CddStp8899_aSRegDiag2[CFG_Stp_IdxVer].Bit.u1OTS) != 0u)                 // DRV88XX ('over') thermal shutdown error bit - i.e.: TSD detected?
              || (CddStp88XX_HalStp_ulTestStepCntLwr > CDDSTP88XX_HALSTP_TestStepCntMax))  // extra test step
               ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    /// \func     CddStp88XX_HalStpLwr_Transition2LastStep
    ///
    /// \brief    LWR transition function to StateLastStep
    ///
    /// \param    const tCommandHalStp eCmd
    ///
    /// \return   uint32
    ///           = TRUE:  condition is valid
    ///           = FALSE: condition is not valid
    ///
    /// \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint32 CddStp88XX_HalStpLwr_Transition2LastStep(const tCommandHalStp eCmd)
    {
      (void)eCmd;
      return (   (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].Bit.biSet == 1u) // buffer entry set with new value?
              && (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].Bit.biLastStep == 1u))
               ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    /// \func     CddStp88XX_HalStpLwr_Transition2Step
    ///
    /// \brief    LWR transition function to StateStep
    ///
    /// \param    const tCommandHalStp eCmd
    ///
    /// \return   uint32
    ///           = TRUE:  condition is valid
    ///           = FALSE: condition is not valid
    ///
    /// \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint32 CddStp88XX_HalStpLwr_Transition2Step(const tCommandHalStp eCmd)
    {
      (void)eCmd;
      return TRUE;
    }


    // ---------------------------------------------------------------------------
    ///
    /// \func     CddStp88XX_HalStpLwr_TransitionStepHold
    ///
    /// \brief    LWR transition function from StateStep to StateHold
    ///
    /// \param    const tCommandHalStp eCmd
    ///
    /// \return   uint32
    ///           = TRUE:  condition is valid
    ///           = FALSE: condition is not valid
    ///
    /// \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint32 CddStp88XX_HalStpLwr_TransitionStepHold(const tCommandHalStp eCmd)
    {
      (void)eCmd;
      return TRUE;
    }


    // ---------------------------------------------------------------------------
    ///
    /// \func     CddStp88XX_HalStpLwr_TransitionHoldHoldCont
    ///
    /// \brief    LWR transition function from StateHold to StateHoldCont
    ///
    /// \param    const tCommandHalStp eCmd
    ///
    /// \return   uint32
    ///           = TRUE:  condition is valid
    ///           = FALSE: condition is not valid
    ///
    /// \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint32 CddStp88XX_HalStpLwr_TransitionHoldHoldCont(const tCommandHalStp eCmd)
    {
      (void)eCmd;
      return TRUE;
    }


    // ---------------------------------------------------------------------------
    ///
    /// \func     CddStp88XX_HalStpLwr_Transition2FirstStep
    ///
    /// \brief    LWR transition function to StateFirstStep
    ///
    /// \param    const tCommandHalStp eCmd
    ///
    /// \return   uint32
    ///           = TRUE:  condition is valid
    ///           = FALSE: condition is not valid
    ///
    /// \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint32 CddStp88XX_HalStpLwr_Transition2FirstStep(const tCommandHalStp eCmd)
    {
      (void)eCmd;
      // Check start stepping: bit set in actual (first) entry and bit first step
      return (   (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].Bit.biSet == 1u) // buffer entry set with new value
              && (CddStp88XX_HalStp_StpInfoLwr.HsInfoBuf[CddStp88XX_HalStp_StpInfoLwr.ulHsInfoBufIx].Bit.biFirstStep == 1u))
               ? TRUE : FALSE;
    }


    // ---------------------------------------------------------------------------
    ///
    /// \func     CddStp88XX_HalStpLwr_Transition2TestStep
    ///
    /// \brief    LWR transition function to StateTestStep
    ///
    /// \param    const tCommandHalStp eCmd
    ///
    /// \return   uint32
    ///           = TRUE:  condition is valid
    ///           = FALSE: condition is not valid
    ///
    /// \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL uint32 CddStp88XX_HalStpLwr_Transition2TestStep(const tCommandHalStp eCmd)
    {
      (void)eCmd;
      return (CddStp88XX_HalStp_BitsLwr.Bit.biTestStep == 1u) ? TRUE : FALSE;; // SysVolt is available if runnables are working
    }


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // LWR StateMachine state functions
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_InitStateFct
    ///
    ///  \brief  State function of ISR timer stepping clock LWR to handle state CddStp88XX_HalStp_eStateInit
    ///
    ///  \param  tAction Action
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_InitStateFct(tAction Action)
    {
      switch (Action)
      {
        case ActEntry: // perform entry action
        {
          // empty - this entry action is never reached because InitState is first state!
          break;
        }
  /*  // ActDo is not used in this state function
        case ActDo:    // perform do activity
        {
          // empty
          break;
        }
  */  // ActDo is not used in this state function
        case ActExit:  // perform exit action
        {
          CddStpPrjLwr_TSP_ForceTimerLow();       // yet: only 'CddStp_Tsp_Stop(0)'
          CddStp88XX_HalStpLwr_StepReload(CDDSTP88XX_HALSTP_INIT);

          (void)CddStp88XX_HalStpLwr_DRV88XXCRegInit();

  //      CddStp88XX_HalStp_ucPhaseCounterLwr = 0;             // init phase counter because of initial stepping clock impulse (generates a uStep) but after sending initial DRV88XX register 0 value.
          break;
        }
        default:
        {
          // This is not a valid action, must be an error.
          // Assert(....);
          break;
        }
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_FirstStepStateFct
    ///
    ///  \brief  State function of ISR timer stepping clock LWR to handle state CddStp88XX_HalStp_eStateFirstStep
    ///
    ///  \param  tAction Action
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_FirstStepStateFct(tAction Action)
    {
      switch (Action)
      {
        case ActEntry: // perform entry action
        {
          #if(CFG_OPT_STATISTIC & CFG_Statistic_ExtendedStpLwr)
            CddStp88XX_HalStp_MovementTimestampLwr = TimerStart(0);
            CddStp88XX_HalStp_ucCycleHsCntLwr = 0;
          #endif

          CddStp88XX_HalStpLwr_HandleCommonStep(CddStp88XX_HalStp_eStateFirstStep);
          break;
        }
  /*  // ActDo is not used in this state function
        case ActDo:    // perform do activity
        {
          // empty
          break;
        }
  */  // ActDo is not used in this state function
        case ActExit:  // perform exit action
        {
          // empty
          break;
        }
        default:
        {
          // This is not a valid action, must be an error.
          // Assert(....);
          break;
        }
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_LastStepStateFct
    ///
    ///  \brief  State function of ISR timer stepping clock LWR to handle state CddStp88XX_HalStp_eStateLastStep
    ///
    ///  \param  tAction Action
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_LastStepStateFct(tAction Action)
    {
      switch (Action)
      {
        case ActEntry: // perform entry action
        {
          #if(CFG_OPT_STATISTIC & CFG_Statistic_ExtendedStpLwr)
            if (CddStp88XX_HalStp_ucCycleHsCntLwr != 0)    // theoretical case: after change of direction only a last step?
            {
              CddStp88XX_HalStp_aucCyclesLwr[(uint8)(UTIL_PRIOR_8(CddStp88XX_HalStp_ucCycleHsCntLwr)) & 0x07]++;
            }
          #endif

          CddStp88XX_HalStpLwr_HandleCommonStep(CddStp88XX_HalStp_eStateLastStep);
          break;
        }
  /*  // ActDo is not used in this state function
        case ActDo:    // perform do activity
        {
          // empty
          break;
        }
  */  // ActDo is not used in this state function
        case ActExit:  // perform exit action
        {
          // empty
          break;
        }
        default:
        {
          // This is not a valid action, must be an error.
          // Assert(....);
          break;
        }
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_StepStateFct
    ///
    ///  \brief  State function of ISR timer stepping clock LWR to handle state CddStp88XX_HalStp_eStateStep
    ///
    ///  \param  tAction Action
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_StepStateFct(tAction Action)
    {
      switch (Action)
      {
        case ActEntry: // perform entry action
        case ActDo:    // perform do activity
        {
          CddStp88XX_HalStpLwr_HandleCommonStep(CddStp88XX_HalStp_eStateStep);
          break;
        }
        case ActExit:  // perform exit action
        {
          // empty
          break;
        }
        default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
        {
          // This is not a valid action, must be an error.
          // Assert(....);
          break;
        }
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_HoldStateFct
    ///
    ///  \brief  State function of ISR timer stepping clock LWR to handle state CddStp88XX_HalStp_eStateHold
    ///
    ///  \param  tAction Action
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_HoldStateFct(tAction Action)
    {
      switch (Action)
      {
        case ActEntry: // perform entry action
        {
          CddStp88XX_HalStpLwr_HandleCurAmplt_(CDDSTP88XX_eCurAmpltStateHold, CDDSTP88XX_eCurAmpltNoChange, CDDSTP88XX_eCurAmpltNoChange);

          CddStpPrjLwr_TSP_ForceTimerLow();     // yet: only 'CddStp_Tsp_Stop(0)'
          CddStp88XX_HalStpLwr_StepReload(CDDSTP88XX_HALSTP_HOLD);
          break;
        }
  /*  // ActDo is not used in this state function
        case ActDo:    // perform do activity
        {
          // empty
          break;
        }
  */  // ActDo is not used in this state function
        case ActExit:  // perform exit action
        {
          // empty
          break;
        }
        default:
        {
          // This is not a valid action, must be an error.
          // Assert(....);
          break;
        }
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_HoldContStateFct
    ///
    ///  \brief  State function of ISR timer stepping clock LWR to handle state CddStp88XX_HalStp_eStateHoldCont
    ///
    ///  \param  tAction Action
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_HoldContStateFct(tAction Action)
    {
      switch (Action)
      {
        case ActEntry: // perform entry action
        {
          CddStpPrj_SetEventFinishMove(CFG_Stp_IdxVer);

// jk-TEST CddStp88XX_HalStpLwr_TestStepStateFct(ActEntry);/* jk-tbd */
// jk-TEST CddStp88XX_HalStpLwr_TestStepStateFct(ActExit);/* jk-tbd */
          break;
        }
  /*  // ActDo is not used in this state function
        case ActDo:    // perform do activity
        {
          // empty
          break;
        }
  */  // ActDo is not used in this state function
        case ActExit:  // perform exit action
        {
          // empty
          break;
        }
        default:
        {
          // This is not a valid action, must be an error.
          // Assert(....);
          break;
        }
      }
    }


    // ---------------------------------------------------------------------------
    ///
    ///  \func   CddStp88XX_HalStpLwr_TestStepStateFct
    ///
    ///  \brief  State function of ISR timer stepping clock LWR to handle state CddStp88XX_HalStp_eStateInit
    ///
    ///  \param  tAction Action
    ///
    ///  \return none
    ///
    ///  \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_TestStepStateFct(tAction Action)
    {
      switch (Action)
      {
        case ActEntry: // perform entry action
        case ActDo:    // perform do activity
        {
          CddStp88XX_HalStpLwr_HandleTestStep();
          break;
        }
        case ActExit:  // perform exit action
        {
          boolean boIsSCCntMax = CddStp88XX_HalStpLwr_IsSCCntMax_();  // maximal value of overcurrent counter
          boolean boIsOLCntMax = CddStp88XX_HalStpLwr_IsOLCntMax_();  // maximal value of openload counter
          
          CddStp88XX_HalStpLwr_HandleCurAmplt_(CDDSTP88XX_eCurAmpltStateHold, CDDSTP88XX_eCurAmpltNoChange, CDDSTP88XX_eCurAmpltNoChange);
//Check   HalPort_ActivateChkMse(); //Check

          // after this case ActExit code the case ActEntry code of CddStp88XX_HalStpLwr_HoldContStateFct() is called -> disable timer interrupt
          CddStp88XX_HalStp_BitsLwr.Bit.biTestStep = 0;
          CddStp88XX_HalStp_BitsLwr.Bit.biTestStepDone = 1;

          if ( !(   (boIsSCCntMax != FALSE)                            // not: maximal value of overcurrent counter
                 || (boIsOLCntMax != FALSE)))                          // not: maximal value of openload counter
          {
            (void)CddStp88XX_HalStpLwr_DRV88XXCRegInit();
          }

          CddStpPrjLwr_TSP_ForceTimerLow();   // yet: only 'CddStp_Tsp_Stop(0)'
          break;
        }
        default:         // switch of enum variable: against MISRA warning - QAC(Prio2) Msg: 2018(This switch default label is unreachable.) Depth: 0 Ref: 
        {
          // This is not a valid action, must be an error.
          // Assert(....);
          break;
        }
      }
    }


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // LWR StateMachine transition function tables
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ---------------------------------------------------------------------------
    // Transition function table for LWR state CddStp88XX_HalStp_eStateInit
    // ---------------------------------------------------------------------------
    STATIC_AL const tTransitionHalStp CddStp88XX_HalStp_TransitionInitLwr[] =
    {
      //  new state                             transition function
      { CddStp88XX_HalStp_eStateHoldCont,      CddStp88XX_HalStpLwr_TransitionInitHoldCont }
    };


    // ---------------------------------------------------------------------------
    // Transition function table for LWR state CddStp88XX_HalStp_eStateFirstStep
    // ---------------------------------------------------------------------------
    STATIC_AL const tTransitionHalStp CddStp88XX_HalStp_TransitionFirstStepLwr[] =
    {
      //  new state                             transition function
      { CddStp88XX_HalStp_eStateLastStep,      CddStp88XX_HalStpLwr_Transition2LastStep    }, // first condition!
      { CddStp88XX_HalStp_eStateStep,          CddStp88XX_HalStpLwr_Transition2Step        }
    };


    // ---------------------------------------------------------------------------
    // Transition function table for LWR state CddStp88XX_HalStp_eStateLastStep
    // ---------------------------------------------------------------------------
    STATIC_AL const tTransitionHalStp CddStp88XX_HalStp_TransitionLastStepLwr[] =
    {
      //  new state                             transition function
      { CddStp88XX_HalStp_eStateHold,          CddStp88XX_HalStpLwr_TransitionStepHold     }
    };


    // ---------------------------------------------------------------------------
    // Transition function table for LWR state CddStp88XX_HalStp_eStateStep
    // ---------------------------------------------------------------------------
    STATIC_AL const tTransitionHalStp CddStp88XX_HalStp_TransitionStepLwr[] =
    {
      //  new state                             transition function
      { CddStp88XX_HalStp_eStateLastStep,      CddStp88XX_HalStpLwr_Transition2LastStep    } // first condition!
    };


    // ---------------------------------------------------------------------------
    // Transition function table for LWR state CddStp88XX_HalStp_eStateHold
    // ---------------------------------------------------------------------------
    STATIC_AL const tTransitionHalStp CddStp88XX_HalStp_TransitionHoldLwr[] =
    {
      //  new state                             transition function
      { CddStp88XX_HalStp_eStateHoldCont,      CddStp88XX_HalStpLwr_TransitionHoldHoldCont }
    };


    // ---------------------------------------------------------------------------
    // Transition function table for LWR state CddStp88XX_HalStp_eStateHoldCont
    // ---------------------------------------------------------------------------
    STATIC_AL const tTransitionHalStp CddStp88XX_HalStp_TransitionHoldContLwr[] =
    {
      //  new state                             transition function
      { CddStp88XX_HalStp_eStateTestStep,      CddStp88XX_HalStpLwr_Transition2TestStep    }, // first condition to avoid loss of start of state TestStep!
      { CddStp88XX_HalStp_eStateFirstStep,     CddStp88XX_HalStpLwr_Transition2FirstStep   }
    };


    // ---------------------------------------------------------------------------
    // Transition function table for LWR state CddStp88XX_HalStp_eStateTestStep
    // ---------------------------------------------------------------------------
    STATIC_AL const tTransitionHalStp CddStp88XX_HalStp_TransitionTestStepLwr[] =
    {
      //  new state                             transition function
      { CddStp88XX_HalStp_eStateHoldCont,      CddStp88XX_HalStpLwr_TransitionTestStepHoldCont }
    };


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // LWR StateMachine table and function
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ---------------------------------------------------------------------------
    // State machine table for LWR HAL stepper
    // ---------------------------------------------------------------------------
    STATIC_AL const tStateMachineHalStpSF HalStp_StateMachineLwr[CddStp88XX_HalStp_eMaxStates] =
    { //   state name                                transition count                                      transition table                            state function
      { /* CddStp88XX_HalStp_eStateInit,        */  UTIL_COUNTOF(CddStp88XX_HalStp_TransitionInitLwr),        CddStp88XX_HalStp_TransitionInitLwr,       CddStp88XX_HalStpLwr_InitStateFct      },
      { /* CddStp88XX_HalStp_eStateFirstStep,   */  UTIL_COUNTOF(CddStp88XX_HalStp_TransitionFirstStepLwr),   CddStp88XX_HalStp_TransitionFirstStepLwr,  CddStp88XX_HalStpLwr_FirstStepStateFct },
      { /* CddStp88XX_HalStp_eStateLastStep,    */  UTIL_COUNTOF(CddStp88XX_HalStp_TransitionLastStepLwr),    CddStp88XX_HalStp_TransitionLastStepLwr,   CddStp88XX_HalStpLwr_LastStepStateFct  },
      { /* CddStp88XX_HalStp_eStateStep,        */  UTIL_COUNTOF(CddStp88XX_HalStp_TransitionStepLwr),        CddStp88XX_HalStp_TransitionStepLwr,       CddStp88XX_HalStpLwr_StepStateFct      },
      { /* CddStp88XX_HalStp_eStateHold,        */  UTIL_COUNTOF(CddStp88XX_HalStp_TransitionHoldLwr),        CddStp88XX_HalStp_TransitionHoldLwr,       CddStp88XX_HalStpLwr_HoldStateFct      },
      { /* CddStp88XX_HalStp_eStateHoldCont,    */  UTIL_COUNTOF(CddStp88XX_HalStp_TransitionHoldContLwr),    CddStp88XX_HalStp_TransitionHoldContLwr,   CddStp88XX_HalStpLwr_HoldContStateFct  },
      { /* CddStp88XX_HalStp_eStateTestStep,    */  UTIL_COUNTOF(CddStp88XX_HalStp_TransitionTestStepLwr),    CddStp88XX_HalStp_TransitionTestStepLwr,   CddStp88XX_HalStpLwr_TestStepStateFct  },
    };


    // ---------------------------------------------------------------------------
    ///
    /// \func     CddStp88XX_HalStpLwr_StateMachine
    ///
    /// \brief    LWR HAL stepper state machine
    ///
    /// \param    const tCommandHalStp eCmd: One of CddStp88XX_HalStp_eCmdInit, CddStp88XX_HalStp_eCmdStartStp, CddStp88XX_HalStp_eCmdIsrStp
    ///
    /// \return   none
    ///
    /// \descr
    ///
    // ---------------------------------------------------------------------------
    STATIC_AL void CddStp88XX_HalStpLwr_StateMachine(const tCommandHalStp eCmd)
    {
//O   tStateCddStp88XX eStateBegin = CddStp88XX_HalStp_eStateLwr;
//    STATIC_AL tStateHalStp CddStp88XX_HalStp_eStateLwr = CddStp88XX_HalStp_eStateInit;
      STATIC_AL tStateHalStp        eOldState = CddStp88XX_HalStp_eMaxStates; // force tracking in case of first state

      // Save current state of the machine state
      eOldState = CddStp88XX_HalStp_eStateLwr;

      // Execute state machine
      {
        boolean                  boBreak              = FALSE;
//O     tStateCddStp88XX         eNewState_           = eStateBegin;
        const tStateFctPtrHalStp pOldStateFct         = HalStp_StateMachineLwr[CddStp88XX_HalStp_eStateLwr].pStateFct;
        const tTransitionHalStp *pTransition_         = HalStp_StateMachineLwr[CddStp88XX_HalStp_eStateLwr].pTransition;
        const tTransitionHalStp *const pTransitionEnd = &pTransition_[HalStp_StateMachineLwr[CddStp88XX_HalStp_eStateLwr].ucCount];

        for ( ; ( (pTransition_ < pTransitionEnd) && (FALSE == boBreak) ); pTransition_++ )
        {
          // Check transition condition
          if ( pTransition_->ptTransitionFct(eCmd) != FALSE) // via e.g. ISR 'INTTAUB0I8func' & fct 'CddStp88XX_HalStpVer_TimerCb'/'CddStp88XX_HalStpVer_TimerCb': eCmd='CddStp88XX_HalStp_eCmdIsrStp'
          {
            // Ok, transition condition complied, get the the new state
            const tStateHalStp eNewState_ = pTransition_->eNewState; //O

            #ifdef CDDSTP_ITM
              // N.b.: '_channel_' (=index) has to be 1...30  (1...x1E)
              // 24+1 = 'E0000064'
              ITM_TRACE_D8(24+1, (uint8)eNewState_); // CddStp88XX_HalStp_eStateInit = 0,  CddStp88XX_HalStp_eStateFirstStep = 1,  CddStp88XX_HalStp_eStateLastStep = 2,  CddStp88XX_HalStp_eStateStep = 3,  CddStp88XX_HalStp_eStateHold = 4,  CddStp88XX_HalStp_eStateHoldCont = 5,  CddStp88XX_HalStp_eStateTestStep = 6
            #endif

            // Call actual state exit action
// state functions always exist in this state machine            if ( pOldStateFct != (tStateFctPtrHalStp)0 )
            {
              pOldStateFct(ActExit);
            }

            // Call new state entry action
// state functions always exist in this state machine            if ( HalStp_StateMachineLwr[eNewState_].pStateFct != (tStateFctPtrHalStp)0 )
            {
              HalStp_StateMachineLwr[eNewState_].pStateFct(ActEntry);
            }

            // Assign the new state to the state variable
            CddStp88XX_HalStp_eStateLwr = eNewState_;

            // Leave the for loop
            boBreak = TRUE;
          }
        }

        if (eOldState == CddStp88XX_HalStp_eStateLwr)
        {
          // Call ActDo activity if state was not changed
// state functions always exist in this state machine            if ( pOldStateFct != (tStateFctPtrHalStp)0 )
          {
            pOldStateFct(ActDo);
          }
        }

        // common code ...

      }
    }

  #endif  // (CFG_DRV_STP_LWR == CFG_Drv_Default)

#endif  // ((CFG_DRV_STP_LWR == CFG_Drv_Default) || (CFG_DRV_STP_KL == CFG_Drv_Default) || (CFG_DRV_STP_GLW == CFG_Drv_Default))


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// (De)Init functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
///
///  \func   CddStp88XX_HalStp_Init
///
///  \brief  Initialisation of stepping ports
///
///  \param  none
///
///  \return none
///
///  \descr  Initialisation of stepping ports,
///                            stepping communication ports of SPI channel (CSIG4),
///                            timer configuration and
///                            timer control registers.
///
// ---------------------------------------------------------------------------
void CddStp88XX_HalStp_Init(void)
{
///// __DI();             // call from interrupt level is not possible (no counter)!
///// osDisableGlobal();  // call from interrupt level is not possible (no counter)!
//!   SuspendAllInterrupts();

  #if ((CFG_DRV_STP_LWR == CFG_Drv_Default) || (CFG_DRV_STP_KL == CFG_Drv_Default) || (CFG_DRV_STP_GLW == CFG_Drv_Default))

    CddStpPrj_TSPInit();              // TSP initialisation

//A!CddStpPrj_PsensPortInit();        // input position sensor

  #endif

///// __EI();            // call from interrupt level is not possible (no counter)!
///// osEnableGlobal();  // call from interrupt level is not possible (no counter)!
//!   ResumeAllInterrupts();
}


// ---------------------------------------------------------------------------
///
///  \func   CddStp88XX_HalStp_Deinit
///
///  \brief  Disable stepping ports
///
///  \param  none
///
///  \return none
///
///  \descr  Disable stepping ports,
///                  stepping communication ports of SPI channel (CSIG4),
///                  stepping timer
///
///  \todo  Add code to disable the stepper ports.
///
// ---------------------------------------------------------------------------
void CddStp88XX_HalStp_Deinit(void)
{
  #if ((CFG_DRV_STP_LWR == CFG_Drv_Default) || (CFG_DRV_STP_KL == CFG_Drv_Default) || (CFG_DRV_STP_GLW == CFG_Drv_Default))

    // disable stepping interrupts
    #if (CFG_DRV_STP_LWR == CFG_Drv_Default)
      CddStp88XX_HalStpLwr_ResetStp(FALSE); // not enable motor, send SPI commands synchronous
      CddStp88XX_HalStpLwr_SetActPos(0);                                       // reset actual position

      (void)CddStp88XX_HalStpLwr_DRV88XXCRegDeinit();
    #endif

    #if (CFG_DRV_STP_KL == CFG_Drv_Default)
    #endif
    
    #if (CFG_DRV_STP_GLW == CFG_Drv_Default)
    #endif

//A!CddStpPrj_PsensPortDeinit();             // input position sensor

    CddStpPrj_TSPDeinit();                   // stop stepping timer

  #endif
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Callback functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------
///
///  \func   CddStp88XX_HalStpVer_TimerCb !!!TSP timer!!!
///
///  \brief  Callback function timer stepping clock Ver (by ISR 'INTTAUB0I8func')
///
///  \descr  callback (to IRQ) at the end of ' Gpt_StartTimer(0, ulCount);'
///
///          2 different timers for LWR-Stepclock:
///           CddStp_Tsp_Start(0, count);   // Stepper-Timer: HW-Pin-Toggling With u-Steps
///           Gpt_StartTimer(  0, count);   // Help-Timer:    IRQ at the end: callback 'StpTimer0Notification' -> 'CddStp88XX_HalStpVer_TimerCb'
///
// ---------------------------------------------------------------------------
void CddStp88XX_HalStpVer_TimerCb(void)
{
  #if (CFG_DRV_STP_LWR == CFG_Drv_Default)

//  STP_RUNTIME_START(CddStp88XX_HalStpVer_TimerCb);

    // stop PWM works only in CAT2-ISR StpTimer0Notification() - CddStp88XX_HalStpVer_TimerCb()
    if (CddStp88XX_HalStp_BitsLwr.Bit.biStopStp == 1u) // no stop in a us position
    {
      CddStp88XX_HalStp_BitsLwr.Bit.biStopStp = 0;
      
      // PRQA S 4304, 4558 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio5) Msg: 4304(An expression of 'essentially Boolean' type (_Bool) is being cast to unsigned type 'unsigned char'.) Depth: 0 Ref: MISRA C:2012 Rule-10.5  |  warning - QAC(Prio7) Msg : 4558(An expression of 'essentially unsigned' type(unsigned char) is being used as the  operand of this logical operator (!).) Depth : 0 Ref : MISRA C : 2012 Rule - 10.1
      CddStp88XX_HalStpLwr_StopStp_((boolean)(!(CddStp88XX_HalStp_BitsLwr.Bit.biStopStpPZ))); // not motor enable
      
      CddStp88XX_HalStp_BitsLwr.Bit.biStopStpPZ = 0;
    }
    else
    {
      CddStp88XX_HalStpLwr_StateMachine(CddStp88XX_HalStp_eCmdIsrStp);
    }

//  STP_RUNTIME_STOP(CddStp88XX_HalStpVer_TimerCb);

  #endif
}


// ---------------------------------------------------------------------------
///
///  \func   CddStp88XX_HalStpVer_TimerHelpCb
///
///  \brief  Callback function timer stepping help Ver (by ISR 'INTTAUB0I10func')
///
///  \descr
///
// ---------------------------------------------------------------------------
void CddStp88XX_HalStpVer_TimerHelpCb(void)
{
  #if (CFG_DRV_STP_LWR == CFG_Drv_Default)

//  STP_RUNTIME_START(CddStp88XX_HalStpVer_TimerCb);

//  STP_RUNTIME_STOP(CddStp88XX_HalStpVer_TimerCb);

  #endif
  return;
}


// ---------------------------------------------------------------------------
///
///  \func   CddStp88XX_HalStpVer_ErrnCb
///
///  \brief  ISR-Callback function ERRN for Ver DRV88XX error handling
///
///  \descr
///
// ---------------------------------------------------------------------------
void CddStp88XX_HalStpVer_ErrnCb(void)
{
  uint8 ucDummy = 0u;
  (void)(ucDummy);
  #if (CFG_DRV_STP_LWR == CFG_Drv_Default)
          
    uint16 unErrVolt;
     
//  STP_RUNTIME_START(CddStp88XX_HalStpVer_ErrnCb);
 
    IoHwAb_User_GetAdc_DIAG_VBAT(&unErrVolt);  //TODO                                                          // save the voltage to detect pseudo SC or OL errors - Note: UV3 and TW provoke also ERRN-ISR of driver -> voltage is saved and status registers are read also
 
    // update internal Data-Mirror ('CddStp8899_aSRegXXX') of necessary HW-Status-Registers ('CddStp8899Com_DataMirror.StatvRx.aSRegXXX')
    // get Status-Register-FAULT contents from RAM mirror (verified)
    (void)CddStp8899Com_GetSRegDiag12(CFG_Stp_IdxVer, &CddStp8899_aSRegDiag1[CFG_Stp_IdxVer].ucRaw, &CddStp8899_aSRegDiag2[CFG_Stp_IdxVer].ucRaw);
 
    uint16 unSpgLo1 = Cod_StpSpannungLo1();             // 'CddStp_tCodingAreaSys.STP_SPANNUNG_LO1' e.g.  '96'  -  [0.1 V]    Spannungsschwelle fur die Reaktivierung des Motors nach Unterspannung
    uint16 unSpgHi1 = Cod_StpSpannungHi1();             // 'CddStp_tCodingAreaSys.STP_SPANNUNG_HI1' e.g. '187'  -  [0.1 V]    Spannungsschwelle fur die Reaktivierung des Motors nach Ueberspannung

    if (   (   (CddStp88XX_HalStp_BitsLwr.Bit.biInit == 1u)                                                     // HalStp is initialized? - now ERRN ISR starts reading all status registers by SPI
            && (!(   ( CddStp8899_aSRegDiag1[CFG_Stp_IdxVer].ucRaw != 0x00u)                                    // not: error from before?
                  || ( CddStp8899_aSRegDiag2[CFG_Stp_IdxVer].ucRaw != 0x00u))))
        || (   (CddStp88XX_aBits[CFG_Stp_IdxVer].Bit.biTransitionErrDone == 1u)                                 // check of error bits is done in CddStp88XX_TransitionErr() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_TransitionErr()
            && (unErrVolt > (unSpgLo1 * 100u))                                                                  // error voltage in specified range?
            && (unErrVolt < (unSpgHi1 * 100u)))
       )
    {
      CddStp88XX_aBits[CFG_Stp_IdxVer].Bit.biTransitionErrDone = 0;                                            // not: check of error bits is done in CddStp88XX_TransitionErr() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb() and in CddStp88XX_TransitionErr()
 
      CddStp88XX_HalStp_unErrVoltLwr = unErrVolt;                                                              // save the voltage to detect pseudo SC or OL errors - Note: CPfail and TW provoke also ERRN-ISR of driver -> voltage is saved and status registers are read also
    }

    CddStpPrj_SetEventFinishMove(CFG_Stp_IdxVer); // ?? Set event flag bit FinishMove and activate event, but not in case of CddStp88XX state StateInit
          
//  STP_RUNTIME_STOP(CddStp88XX_HalStpVer_ErrnCb);
          
  #endif
}

//EOF
