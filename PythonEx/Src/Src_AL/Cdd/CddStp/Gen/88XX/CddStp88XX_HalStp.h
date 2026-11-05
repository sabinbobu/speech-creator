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
/// \file  CddStp88XX_HalStp.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------

#ifndef __CDDSTP88XX_HALSTP_H__
#define __CDDSTP88XX_HALSTP_H__


#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <CodM_Para/CodM_Para_System.h>
#else // Unit-Tests!
  #include <CodM_Para/CodM_Para_System.h>
#endif

#include <Cfg/CddStp_Cfg.h>
#include <8899/CddStp8899Com.h>
#include <88xx/_CddStp88XX.h>






  //-----------------------------------------------------------------------------
  /// \file  _CddStp88XX_HalStp.h
  ///
  /// \brief  Definitions of CddStp88XX_HalStp state machine
  ///
  /// \descr  
  ///
  ///         Additional information can be found in the design description (Link:
  ///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
  ///
  /// \author Wuesteney, Ulrich ALRT/EEG4 * (wu82rt)
  ///         J. Kling ALRT-EES6 (f84304b)
  //-----------------------------------------------------------------------------

//#ifndef ___CDDSTP88XX_HALSTP_H__
//#define ___CDDSTP88XX_HALSTP_H__

  // ---------------------------------------------------------------------------
  // states and flags

  typedef enum
  {
    CddStp88XX_HalStp_eStateInit          = 0,  // must be 0 (init. value)
    CddStp88XX_HalStp_eStateFirstStep,   // 1
    CddStp88XX_HalStp_eStateLastStep,    // 2
    CddStp88XX_HalStp_eStateStep,        // 3
    CddStp88XX_HalStp_eStateHold,        // 4
    CddStp88XX_HalStp_eStateHoldCont,    // 5
    CddStp88XX_HalStp_eStateTestStep,    // 6
    CddStp88XX_HalStp_eMaxStates         // 7 // numbers of states = end of states for state machine table
  } tStateHalStp;


  //---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  // Definitions for table state machine(s)

  // Command parameters of state machine call
  typedef enum
  {
    CddStp88XX_HalStp_eCmdInit,
    CddStp88XX_HalStp_eCmdStartStp,
    CddStp88XX_HalStp_eCmdIsrStp
  }
  tCommandHalStp;


  // Transition function pointer
  typedef uint32 (*ptTransitionFctPtrHalStp)(tCommandHalStp);
  
  
  // Transition function informations
  typedef struct
  {
    const tStateHalStp             eNewState;
    const ptTransitionFctPtrHalStp ptTransitionFct;
  } tTransitionHalStp;
  
  
/*  // Simple StateMachine
  typedef struct
  {
    const uint8                    ucCount;
    const tTransitionHalStp *const pTransition;
  } tStateMachineHalStp;
*/

  typedef void (*tStateFctPtrHalStp)(tAction);

  typedef struct
  {
    const uint8              ucCount;
    const tTransitionHalStp  *const pTransition;
    const tStateFctPtrHalStp pStateFct;
  } tStateMachineHalStpSF;
  //---------------------------------------------------------------------------

// #endif // ___CDDSTP88XX_HALSTP_H__


















  // ---------------------------------------------------------------------------
  // constant definitions
  // ---------------------------------------------------------------------------
//DaVinciCfg  #define TSP_CKS0                    0x4444                        // prescaler CK3 = 2^4 = 16 (1.0 MHz tick) - TAUJ0O1 TSP (STP LWR, KL, GLW) logical and to change only clock CK1 - initial TAUJ0O1 register value is 0xFFFF //DaVinciCfg
//DaVinciCfg                                                                    // prescaler CK3 = 2^4 = 16 (1.0 MHz tick) - TAUJ0O3 GPT FastTimer (FTIMER) logical and to change only clock CK0 - initial TAUJ0O3 register value is 0xFFFF //DaVinciCfg
//DaVinciCfg                                                                    // prescaler CK3 = 2^4 = 16 (1.0 MHz tick) - TAUJ0O0 GPT ChargePumpTimer    logical and to change only clock CK0 - initial TAUJ0O0 register value is 0xFFFF //DaVinciCfg
//DaVinciCfg                                                                    // prescaler CK3 = 2^4 = 16 (1.0 MHz tick) - TAUJ0O2 FanTimer               logical and to change only clock CK0 - initial TAUJ0O2 register value is 0xFFFF //DaVinciCfg
//DaVinciCfg  #define TSP_CKS                     TSP_CKS0
  #define CDDSTP88XX_HALSTP_TimeBaseFreq         ((1000ul * 1024ul) / 1000ul)   // 1000 kHz - scaled by 1024

  // definition of half stepping info buffer
  #define CDDSTP88XX_HALSTP_HsInfoBufLen         (64u)
 
  // definition of status register no error data
//#define CDDSTP88XX_HALSTP_SREG_NOERR           (0x00u)                       // no error data for even parity DRV8899 1st silicon
  #define CDDSTP88XX_HALSTP_SREG_NOERR           (0x80u)                       // no error data for odd  parity DRV8899 2nd silicon
  

  // ---------------------------------------------------------------------------------------------------
  // definition of half step info: interface between CddStp and HalStp
  //
  // R R S L F P D A I I I I I I I I T T T T T T T T T T T T T T T T
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // | | | | | | | | | | | | | | | | +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-- T: halfstep time in microseconds
  // | | | | | | | | | | | | | | | |
  // | | | | | | | | +-+-+-+-+-+-+-+---------------------------------- I: index of dynamic table (used in CddStpDyn only)
  // | | | | | | | |
  // | | | | | | | +-------------------------------------------------- A: above resonance frequency area (used in CddStpDyn only)
  // | | | | | | +---------------------------------------------------- D: direction, 0=positive, 1=negative
  // | | | | | +------------------------------------------------------ P: pause (no step)
  // | | | | +-------------------------------------------------------- F: first step of current movement
  // | | | +---------------------------------------------------------- L: last step of current movement
  // | | +------------------------------------------------------------ S: set for current movement
  // +-+-------------------------------------------------------------- R: reserved
  // ---------------------------------------------------------------------------------------------------
  typedef struct
  {
    uint32  biHsTime       : 16;  // duration of 1 half step [microseconds]
    uint32  biDynTableIx   :  8;  // used only if CddStp uses a table for step dynamic calculation, not relevant for HalStp
    uint32  biAboveResF1   :  1;  // used only in CddStpDyn: actual stepper frequency above resonance frequency area 1
    uint32  biAboveResF2   :  1;  // used only in CddStpDyn: actual stepper frequency above resonance frequency area 2
    uint32  biDirection    :  1;  // 0=positive, 1=negative
    uint32  biPause        :  1;  // pause (no step)
    uint32  biFirstStep    :  1;  // first step of current movement
    uint32  biLastStep     :  1;  // last  step of current movement
    uint32  biSet          :  1;  // set entry, bit is cleared after entry is used
    uint32  biReserved     :  1;  // if no flag is set: end of table reached
  }tHsInfoBit;

  typedef struct
  {
    uint16  unHsTime;       // direct access to bit field
    uint8   ucDynTableIx;   // direct access to bit field
    uint8   ucDummy;        // not used: access by bit field
  }tHsInfoVal;

  typedef union
  {
    tHsInfoBit    Bit;
    tHsInfoVal    Val;
    uint32        ulRaw;
  }tHsInfo;

  // stepping buffer
  typedef struct
  {
    sint32   lActPos;
    uint32  ulHsInfoBufIx;
    tHsInfo HsInfoBuf[CDDSTP88XX_HALSTP_HsInfoBufLen];
  }tStpInfo;

  // HalStp bits - interrupt level
  typedef struct
  {
    uint8   biDirection         : 1; //  0: direction
    uint16  biReserved3         : 3; //  5: reserved
  }tHSBitsInt;

  typedef union
  {
    tHSBitsInt Bit;     ///< bit signal access
    uint8      ucRaw;   ///< raw signal access
  } tHalStpBitsInt;

  #define DEBUG_BUFFERSIZE 64

  typedef struct
  {
    uint16  unTime;
    uint8   ucBufIx;
    uint8   ucBits;
    uint16  unHsTime;
    sint16  nActPos;
  }
  tDebugChronoBufferRead;

  typedef struct
  {
    uint16  unTime;
    uint8   ucBufIx1;
    uint8   ucBufIx2;
    sint16  nStepsToDo;
    uint16  unRemainingTime;
  }
  tDebugChronoBufferWrite;

  typedef union
  {
    tDebugChronoBufferRead   Read;
    tDebugChronoBufferWrite  Write;
  }
  tDebugChronoBuffer;


  // SPI communication types
  typedef enum
  {
    CDDSTP88XX_HALSTP_eSpiSendCyclic   = 0, // SPI communication triggered by cyclic mainTask event     (call from CAT1-ISR is possible)
    CDDSTP88XX_HALSTP_eSpiSendEvent    = 1, // SPI communication triggered by event handled in mainTask (call from CAT1-ISR is not possible)
    CDDSTP88XX_HALSTP_eSpiSendDirect   = 2  // SPI communication direct by AUTOSAR MCAL module Spi      (call from CAT1-ISR is not possible)
  } eCddStp88XX_HalStpSpiSendType;


  // Numbers of DRV8899 registers
  typedef enum
  {
    CddStp88XX_HalStp_eCReg1    = 0,  // Control register 1  (index of TX/RX buffer: CDDSTP8899_CReg1Ix  !CDDSTP8899_Dummy)
    CddStp88XX_HalStp_eCReg2    = 1,  // Control register 2  (index of TX/RX buffer: CDDSTP8899_CReg2Ix  !CDDSTP8899_Dummy)
    CddStp88XX_HalStp_eCReg3    = 2,  // Control register 3  (index of TX/RX buffer: CDDSTP8899_CReg3Ix  !CDDSTP8899_Dummy)
    CddStp88XX_HalStp_eCReg4    = 3,  // Control register 4  (index of TX/RX buffer: CDDSTP8899_CReg4Ix  !CDDSTP8899_Dummy)
// jk-obsolet    CddStp88XX_HalStp_eCReg5    = ,  // Control register 5  (index of TX/RX buffer: CDDSTP8899_CReg5Ix  !CDDSTP8899_Dummy)
// jk-obsolet    CddStp88XX_HalStp_eCReg6    = ,  // Control register 6  (index of TX/RX buffer: CDDSTP8899_CReg6Ix  !CDDSTP8899_Dummy)
// jk-obsolet    CddStp88XX_HalStp_eCReg7    = ,  // Control register 7  (index of TX/RX buffer: CDDSTP8899_CReg7Ix  !CDDSTP8899_Dummy)
// jk-obsolet    CddStp88XX_HalStp_eCReg7A   = ,  // Control register 7A (index of TX/RX buffer: CDDSTP8899_CReg7Ix  !CDDSTP8899_Dummy)
    CddStp88XX_HalStp_eSRegAllTime = 4,  // Status  register 1  (index of TX/RX buffer: CDDSTP8899_SReg1Ix  !CDDSTP8899_Dummy)
    CddStp88XX_HalStp_eSRegFAULT   = 5,  // Status  register 2  (index of TX/RX buffer: CDDSTP8899_SReg2Ix  !CDDSTP8899_Dummy)
    CddStp88XX_HalStp_eSRegDiag1   = 6, // Status  register 3  (index of TX/RX buffer: CDDSTP8899_SReg3Ix  !CDDSTP8899_Dummy)
    CddStp88XX_HalStp_eSRegDiag2   = 7, // Status  register 4  (index of TX/RX buffer: CDDSTP8899_SReg4Ix  !CDDSTP8899_Dummy)
    CddStp88XX_HalStp_eRegMax      = 8, // count of registers
    CddStp88XX_HalStp_eRegBSize    = 9  // size of buffer with register values (see index of TX/RX buffer:   CDDSTP8899_Dummy)
  } eCddStp88XX_HalStpRegisters;


  void                       CddStp88XX_HalStpVer_TimerCb(void);
  void                       CddStp88XX_HalStpVer_TimerHelpCb(void);
  void                       CddStp88XX_HalStpVer_ErrnCb(void); 


//  -----------------------------------------------------------------------------------------------
//  stepper configuration


#if ((CFG_DRV_STP_LWR == CFG_Drv_Default) || (CFG_DRV_STP_KL == CFG_Drv_Default) || (CFG_DRV_STP_GLW == CFG_Drv_Default))

    typedef void             (*tFct_Void_Void)                                (void);
    typedef void             (*tFct_Void_Bool)                                (boolean);
    typedef void             (*tFct_Void_Bool_Bool)                           (boolean, boolean);
    typedef boolean          (*tFct_Bool_Void)                                (void);
    typedef boolean          (*tFct_Bool_Bool)                                (boolean);
    typedef boolean          (*tFct_Bool_Bool_Uint8)                          (boolean, uint8);
    typedef sint32           (*tFct_Int32_Void)                               (void);
    typedef uint8            (*tFct_Uint8_Void)                               (void);
    typedef uint32           (*tFct_Uint32_pInt32_pUint32)                    (sint32*, uint32*);
    typedef void             (*tFct_Void_Uint8)                               (uint8);
    typedef void             (*tFct_Void_Uint8_Uint8_Uint8)                   (uint8, uint8, uint8);
    typedef volatile uint8*  (*tFct_VolatileUint8_Void)                       (void);
    typedef tStpInfo*        (*tFct_ptStpInfo_Void)                           (void);
    typedef void             (*tFct_Void_ConstInt32)                          (const sint32);
    typedef void             (*tFct_Void_ConsteHalStpRegisters_ConstUint16)   (const eCddStp88XX_HalStpRegisters, const uint16);
    typedef void             (*tFct_Void_ConsteHalStpRegisters_ConstBool)     (const eCddStp88XX_HalStpRegisters, const boolean);
    typedef uint32           (*tFct_Uint32_Void)                              (void);

    typedef struct
    {
      const tFct_Bool_Bool                                pSpiSendCReg0;   // DRV70521 specific
      const tFct_Bool_Bool                                pSpiSendCReg1;   // DRV88XX specific
      const tFct_Bool_Bool                                pSpiSendCReg2;   // DRV88XX specific
      const tFct_Bool_Bool                                pSpiSendCReg3;   // DRV8899 specific
      const tFct_Bool_Bool                                pSpiSendCReg4;   // DRV8899 specific
// jk-obsolet       const tFct_Bool_Bool                  pSpiSendCReg6;   // DRV8899 specific
// jk-obsolet       const tFct_Bool_Bool                  pSpiSendCReg7;   // DRV8899 specific
      const tFct_Bool_Void                                pSpiSendCRegAll; // DRV88XX specific
      //  keine CddStp88XX_HalStpLwr_SendSRegX()-Funktionen, da sowieso immer alle StatusRegister gelesen werden
   // const tFct_Bool_Void                                pSpiSendSReg0;   // DRV70521 specific
      const tFct_Bool_Void                                pIsDriverReset;  // DRV88XX specific
      const tFct_Void_Void                                pClrDriverReset; // DRV88XX specific
      const tFct_Void_Void                                pSetDriverReset; // DRV88XX specific
      
      const tFct_ptStpInfo_Void                           pGetStpInfo;
      const tFct_Uint32_pInt32_pUint32                    pGetWriteIx;

      const tFct_Void_ConstInt32                          pSetActPos;
      const tFct_Void_ConstInt32                          pIncActPos;
      const tFct_Int32_Void                               pGetActPos;
      const tFct_Uint8_Void                               pGetPhaseCounter; // DRV88XX specific

      const tFct_Bool_Void                                pIsFinishMove;
      
      const tFct_Void_Bool_Bool                           pHandleMotEn;
      const tFct_Void_Uint8_Uint8_Uint8                   pHandleCurAmplt;
      const tFct_Uint8_Void                               pGetCurAmplt;

      const tFct_Void_Void                                pStartStp;
      const tFct_Void_Bool                                pResetStp;
      const tFct_Void_Bool                                pStopStp;
      
      const tFct_Bool_Void                                pGetPsensPort;
      
      const tFct_Uint32_Void                              pGetErrVolt;   // DRV88XX specific
      const tFct_Void_Void                                pResetErrVolt; // DRV88XX specific
      
      const tFct_Bool_Bool                                pSetTestStep;
      const tFct_Bool_Void                                pIsTestStepDone;
      const tFct_Void_Void                                pResetTestStepCnt;
      
      const tFct_Void_Void                                pClrOLCnt;
      const tFct_Bool_Void                                pIncOLCnt;
      const tFct_Bool_Void                                pIsOLCntMax;
      
      const tFct_Void_Void                                pClrSCCnt;
      const tFct_Bool_Void                                pIncSCCnt;
      const tFct_Bool_Void                                pIsSCCntMax;
      
      const tFct_Uint32_Void                              pGetHsCnt;
      const tFct_Void_Uint8                               pSetCARunRefCnt;
      const tFct_Uint32_Void                              pGetIrunTime;

      const tFct_Bool_Bool                                pInit;

      const tFct_Bool_Bool_Uint8                          pSetHsMode;
      const tFct_Bool_Void                                pGetHsMode;
    }
    tCddStp88XX_HalStpFct;

    // ---------------------------------------------------------------------------
    // external variable declarations
    // ---------------------------------------------------------------------------
//  extern tHalStpBitsInt               CddStp88XX_HalStp_BitsIntLwr;
//  extern tHalStpBitsInt               CddStp88XX_HalStp_BitsIntKl;
//  extern tHalStpBitsInt               CddStp88XX_HalStp_BitsIntGlw;
    extern const tCddStp88XX_HalStpFct  CddStp88XX_HalStpFct[];
    extern /* orig: 'uint8' */ tCddStp8899Com_StatReg_Basic CddStp8899_aSRegBasic[];  // Basic-Status - comes each time 'automatically'  - 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL
    extern /* orig: 'uint8' */ tCddStp8899Com_StatReg_Fault CddStp8899_aSRegFault[];  // Fault-Status                                    - FAULT | SPI_ERROR | UVLO | CPUV | OCP | RSVD | TF | OL
    extern /* orig: 'uint8' */ tCddStp8899Com_StatReg_Diag1 CddStp8899_aSRegDiag1[];  // Diag-Status-1                                   - OCP_LS2_B | OCP_HS2_B | OCP_LS1_B | OCP_HS1_B | OCP_LS2_A | OCP_HS2_A | OCP_LS1_A | OCP_HS1_A
    extern /* orig: 'uint8' */ tCddStp8899Com_StatReg_Diag2 CddStp8899_aSRegDiag2[];  // Diag-Status-2                                   - UTW | OTW | OTS | RSVD | OL_B | OL_A
   
  #endif

  void             CddStp88XX_HalStp_Init(void);
  void             CddStp88XX_HalStp_Deinit(void);
// jk-not-used  void             CddStp88XX_HalStp_TSPCfgCtrlRegInit(void);
// jk-not-used  uint16           CddStp88XX_HalStp_GetTimerCnt(void);


#endif // __CDDSTP88XX_HALSTP_H__

// EOF
