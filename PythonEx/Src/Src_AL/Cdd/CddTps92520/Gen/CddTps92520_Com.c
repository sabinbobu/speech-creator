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
/// \file   CddTps92520_Com.c
///
/// \brief  Code for TPS92520 SPI communication
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
// standard includes
#include <Std_Types.h>
#include <AL_Helper.h>

// module API (include path)
#include <CddTps92520.h>
#include <CddTps92520_Cb.h>

// module includes (relative to API)
#include <../Cfg/CddTps92520_Cfg.h>
#include <../Cfg/CddTps92520_RoutCfg.h>
#include <../Gen/CddTps92520_Com.h>
#include <../Gen/CddTps92520_Types.h>
#include <../Gen/CddTps92520_Sched.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#if (CDDTPS92520_Cfg_NbOfDevices == 1)
  #define CDDTPS92520_INIT(x) { x }
#elif (CDDTPS92520_Cfg_NbOfDevices == 2)
  #define CDDTPS92520_INIT(x) { x, x }
#elif (CDDTPS92520_Cfg_NbOfDevices == 3)
  #define CDDTPS92520_INIT(x) { x, x, x }
#elif (CDDTPS92520_Cfg_NbOfDevices == 4)
  #define CDDTPS92520_INIT(x) { x, x, x, x }
#elif (CDDTPS92520_Cfg_NbOfDevices == 5)
  #define CDDTPS92520_INIT(x) { x, x, x, x, x }
#elif (CDDTPS92520_Cfg_NbOfDevices == 6)
  #define CDDTPS92520_INIT(x) { x, x, x, x, x, x }
#elif (CDDTPS92520_Cfg_NbOfDevices == 7)
  #define CDDTPS92520_INIT(x) { x, x, x, x, x, x, x }
#endif //(CDDTPS92520_Cfg_NbOfDevices = nb of TPS92520 configured)

#define TPS92520_unDummyZeroReg   {.unRaw=0u}

#define CDDTPS92520_SYSCFG1_Init  {.Bit={.biCH1EN=0u, .biCH1INTPWM=CDDTPS92520_Cfg_CH1INTPWM, .biCH2EN=0u, .biCH2INTPWM=CDDTPS92520_Cfg_CH2INTPWM, .biCMWEN=0u, .biLHSW=0u, .u1PWMPH=CDDTPS92520_Cfg_PWMPH, .biFPINRST=0u}}
#define CDDTPS92520_SYSCFG2_Init  {.Bit={.biCH1LSILIMFL=0u, .biCH1HSILIMFL=0u, .biCH1TSFL=CDDTPS92520_Cfg_CH1TSFL, .biCH2LSILIMFL=0u, .biCH2HSILIMFL=0u, .biCH2TSFL=CDDTPS92520_Cfg_CH2TSFL, .bi2IFT=CDDTPS92520_Cfg_IFT}}
#define CDDTPS92520_CMWTAP_Init   {.Bit={.bi4CMWTAP=CDDTPS92520_Cfg_CMWTAP, .bi4RESERVED=0u}}
#define CDDTPS92520_TWLMT_Init    {.Byte={(uint8)CDDTPS92520_Cfg_TWLMT}}
#define CDDTPS92520_SLEEP_Init    {.Bit={.bi2SLEEP=0u}}
#define CDDTPS92520_PWMDIV_Init   {.Bit={.bi3PWMDIV=CDDTPS92520_Cfg_PWMDIV}}
#define CDDTPS92520_CH1TON_Init   {.Bit={.bi6CHxTON=CDDTPS92520_Cfg_CHxTON_HiFreq}}
#define CDDTPS92520_CH2TON_Init   {.Bit={.bi6CHxTON=CDDTPS92520_Cfg_CHxTON_HiFreq}}
#define CDDTPS92520_LHCFG1_Init   {.Bit={.biLH1EN=0u, .biLH1INTPWM=CDDTPS92520_Cfg_LH1INTPM, .biLH1100D=0u, .biLH2EN=0u, .biLH2INTPWM=CDDTPS92520_Cfg_LH2INTPM,  .biLH2100D=0, .biLHEXTIADJ=CDDTPS92520_Cfg_LHEXTIADJ, .u1LHPWMPH=CDDTPS92520_Cfg_LHPWMPH}}
#define CDDTPS92520_RESET_Init    {.Byte={CDDTPS92520_RESET}}

// Initialization values of Data Mirror of TPS92520 registers
#define CDDTPS92520_DataMirror_Init                                                                            \
{                                                                                                              \
  { /* CtrlTx */                                                                                               \
      CDDTPS92520_INIT(CDDTPS92520_SYSCFG1_Init),                                                              \
      CDDTPS92520_INIT(CDDTPS92520_SYSCFG2_Init),                                                              \
      CDDTPS92520_INIT(CDDTPS92520_CMWTAP_Init),                                                               \
      CDDTPS92520_INIT(CDDTPS92520_TWLMT_Init),                                                                \
      CDDTPS92520_INIT(CDDTPS92520_SLEEP_Init),                                                                \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxIADJL  */ \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxIADJH  */ \
      CDDTPS92520_INIT(CDDTPS92520_PWMDIV_Init),                                                               \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxPWML   */ \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxPWMH   */ \
    { CDDTPS92520_INIT(CDDTPS92520_CH1TON_Init), CDDTPS92520_INIT(CDDTPS92520_CH2TON_Init) }, /* aCHxTON    */ \
      CDDTPS92520_INIT(CDDTPS92520_LHCFG1_Init),                                                               \
      CDDTPS92520_INIT(CDDTPS92520_RESET_Init)                                                                 \
  },                                                                                                           \
  { /*CtrlRx */                                                                                                \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxIADJL  */ \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxIADH   */ \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxPWML   */ \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxPWMH   */ \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxTON    */ \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg)                                                                \
  },                                                                                                           \
  { /* StatRx */                                                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxVIN    */ \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxVLED   */ \
    { CDDTPS92520_INIT(TPS92520_unDummyZeroReg), CDDTPS92520_INIT(TPS92520_unDummyZeroReg) }, /* aCHxVLEDON */ \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg),                                                               \
      CDDTPS92520_INIT(TPS92520_unDummyZeroReg)                                                                \
  }                                                                                                            \
}


#define CDDTPS92520_SYSCFG1_Tx    &CddTps92520_DataMirror.CtrlTx.aSYSCFG1[0].unRaw
#define CDDTPS92520_SYSCFG2_Tx    &CddTps92520_DataMirror.CtrlTx.aSYSCFG2[0].unRaw
#define CDDTPS92520_CMWTAP_Tx     &CddTps92520_DataMirror.CtrlTx.aCMWTAP[0].unRaw
#define CDDTPS92520_TWLMT_Tx      &CddTps92520_DataMirror.CtrlTx.aTWLMT[0].unRaw
#define CDDTPS92520_SLEEP_Tx      &CddTps92520_DataMirror.CtrlTx.aSLEEP[0].unRaw
#define CDDTPS92520_CH1IADJL_Tx   &CddTps92520_DataMirror.CtrlTx.aCHxIADJL[0][0].unRaw
#define CDDTPS92520_CH2IADJL_Tx   &CddTps92520_DataMirror.CtrlTx.aCHxIADJL[1][0].unRaw
#define CDDTPS92520_CH1IADJH_Tx   &CddTps92520_DataMirror.CtrlTx.aCHxIADJH[0][0].unRaw
#define CDDTPS92520_CH2IADJH_Tx   &CddTps92520_DataMirror.CtrlTx.aCHxIADJH[1][0].unRaw
#define CDDTPS92520_PMWDIV_Tx     &CddTps92520_DataMirror.CtrlTx.aPWMDIV[0].unRaw
#define CDDTPS92520_CH1PWML_Tx    &CddTps92520_DataMirror.CtrlTx.aCHxPWML[0][0].unRaw
#define CDDTPS92520_CH2PWML_Tx    &CddTps92520_DataMirror.CtrlTx.aCHxPWML[1][0].unRaw
#define CDDTPS92520_CH1PWMH_Tx    &CddTps92520_DataMirror.CtrlTx.aCHxPWMH[0][0].unRaw
#define CDDTPS92520_CH2PWMH_Tx    &CddTps92520_DataMirror.CtrlTx.aCHxPWMH[1][0].unRaw
#define CDDTPS92520_CH1TON_Tx     &CddTps92520_DataMirror.CtrlTx.aCHxTON[0][0].unRaw
#define CDDTPS92520_CH2TON_Tx     &CddTps92520_DataMirror.CtrlTx.aCHxTON[1][0].unRaw
#define CDDTPS92520_LHCFG1_Tx     &CddTps92520_DataMirror.CtrlTx.aLHCFG1[0].unRaw
#define CDDTPS92520_RESET_Tx      &CddTps92520_DataMirror.CtrlTx.aRESET[0].unRaw

#define CDDTPS92520_SYSCFG1_Rx    &CddTps92520_DataMirror.CtrlRx.aSYSCFG1[0].unRaw
#define CDDTPS92520_SYSCFG2_Rx    &CddTps92520_DataMirror.CtrlRx.aSYSCFG2[0].unRaw
#define CDDTPS92520_CMWTAP_Rx     &CddTps92520_DataMirror.CtrlRx.aCMWTAP[0].unRaw
#define CDDTPS92520_TWLMT_Rx      &CddTps92520_DataMirror.CtrlRx.aTWLMT[0].unRaw
#define CDDTPS92520_SLEEP_Rx      &CddTps92520_DataMirror.CtrlRx.aSLEEP[0].unRaw
#define CDDTPS92520_CH1IADJL_Rx   &CddTps92520_DataMirror.CtrlRx.aCHxIADJL[0][0].unRaw
#define CDDTPS92520_CH1IADJH_Rx   &CddTps92520_DataMirror.CtrlRx.aCHxIADJH[0][0].unRaw
#define CDDTPS92520_CH2IADJL_Rx   &CddTps92520_DataMirror.CtrlRx.aCHxIADJL[1][0].unRaw
#define CDDTPS92520_CH2IADJH_Rx   &CddTps92520_DataMirror.CtrlRx.aCHxIADJH[1][0].unRaw
#define CDDTPS92520_PMWDIV_Rx     &CddTps92520_DataMirror.CtrlRx.aPWMDIV[0].unRaw
#define CDDTPS92520_CH1PWML_Rx    &CddTps92520_DataMirror.CtrlRx.aCHxPWML[0][0].unRaw
#define CDDTPS92520_CH2PWML_Rx    &CddTps92520_DataMirror.CtrlRx.aCHxPWML[1][0].unRaw
#define CDDTPS92520_CH1PWMH_Rx    &CddTps92520_DataMirror.CtrlRx.aCHxPWMH[0][0].unRaw
#define CDDTPS92520_CH2PWMH_Rx    &CddTps92520_DataMirror.CtrlRx.aCHxPWMH[1][0].unRaw
#define CDDTPS92520_CH1TON_Rx     &CddTps92520_DataMirror.CtrlRx.aCHxTON[0][0].unRaw
#define CDDTPS92520_CH2TON_Rx     &CddTps92520_DataMirror.CtrlRx.aCHxTON[1][0].unRaw
#define CDDTPS92520_LHCFG1_Rx     &CddTps92520_DataMirror.CtrlRx.aLHCFG1[0].unRaw
#define CDDTPS92520_STATUS1_Rx    &CddTps92520_DataMirror.StatRx.aSTATUS1[0].unRaw
#define CDDTPS92520_STATUS2_Rx    &CddTps92520_DataMirror.StatRx.aSTATUS2[0].unRaw
#define CDDTPS92520_STATUS3_Rx    &CddTps92520_DataMirror.StatRx.aSTATUS3[0].unRaw
#define CDDTPS92520_CH1VIN_Rx     &CddTps92520_DataMirror.StatRx.aCHxVIN[0][0].unRaw
#define CDDTPS92520_CH1VLED_Rx    &CddTps92520_DataMirror.StatRx.aCHxVLED[0][0].unRaw
#define CDDTPS92520_CH1VLEDON_Rx  &CddTps92520_DataMirror.StatRx.aCHxVLEDON[0][0].unRaw
#define CDDTPS92520_CH2VIN_Rx     &CddTps92520_DataMirror.StatRx.aCHxVIN[1][0].unRaw
#define CDDTPS92520_CH2VLED_Rx    &CddTps92520_DataMirror.StatRx.aCHxVLED[1][0].unRaw
#define CDDTPS92520_CH2VLEDON_Rx  &CddTps92520_DataMirror.StatRx.aCHxVLEDON[1][0].unRaw
#define CDDTPS92520_TEMPL_Rx      &CddTps92520_DataMirror.StatRx.aTEMPL[0].unRaw
#define CDDTPS92520_TEMPH_Rx      &CddTps92520_DataMirror.StatRx.aTEMPH[0].unRaw
#define CDDTPS92520_V5D_Rx        &CddTps92520_DataMirror.StatRx.aV5D[0].unRaw

#define CDDTPS92520_Zero_Tx       &CddTps92520_aunZero[0]
#define CDDTPS92520_Dummy_Rx      &CddTps92520_aunDummy[0]


//-----------------------------------------------------------------------------
// Local types
//-----------------------------------------------------------------------------
// SPI schedule table entry datatype
typedef struct tCddTps92520_SpiSchedTable
{
  sint8         cNextEntry;   // offset to next schedule table entry
  uint8         ucAction;     // index of action function done after Rx --> TODO change as function pointer ?
  uint16        unCmd;        // Read/Write Command to send
  uint16        unAddr;       // SPI address (combination of low and high nibble)
  const uint16* punTx;        // SPI control register data for transmission - offset related to 1st address of stuct 
  uint16*       punRx;        // SPI status register data for reception     - offset related to 1st address of stuct
} tCddTps92520_SpiSchedTable;


//-----------------------------------------------------------------------------
// Start definitions of initialized 16 bit variables
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_VAR_INIT_16
#include <../Cfg/CddTps92520_MemMap.h>

STATIC_AL uint16 CddTps92520_unSchedIx       = 0u;  // Index for pointer to schedule table
STATIC_AL uint16 CddTps92520_unFirstDev      = 0u;  // Index of first device
STATIC_AL uint16 CddTps92520_unAvrgVinIdx    = 0u;  // Index for VIN averaging
STATIC_AL uint16 CddTps92520_unAvrgVledIdx   = 0u;  // Index for VLED averaging
STATIC_AL uint16 CddTps92520_unAvrgVledOnIdx = 0u;  // Index for VLEDON averaging

#define ctadCddLed_STOP_SEC_VAR_INIT_16
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized 16 bit variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_VAR_INIT_UNSPECIFIED
#include <../Cfg/CddTps92520_MemMap.h>

STATIC_AL tCddTps92520_DataMirror CddTps92520_DataMirror                   = CDDTPS92520_DataMirror_Init;  // mirror of TPS92520 registers
STATIC_AL boolean CddTps92520_boSpiErrorLatch[CDDTPS92520_Cfg_NbOfDevices * 2u] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };      // SPI error latch per chip
STATIC_AL CONST_AL uint16 CddTps92520_aunOddParityLUT[256] = { 0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,
                                              0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,
                                              0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,
                                              0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,
                                              0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,
                                              0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,
                                              0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,
                                              0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,
                                              0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,
                                              0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,
                                              0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,
                                              0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,
                                              0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,
                                              0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,
                                              0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,
                                              0x0100,0x0000,0x0000,0x0100,0x0000,0x0100,0x0100,0x0000,0x0000,0x0100,0x0100,0x0000,0x0100,0x0000,0x0000,0x0100 };

#define ctadCddLed_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of non initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddTps92520_MemMap.h>

STATIC_AL uint16  CddTps92520_aunDummy    [CDDTPS92520_Cfg_NbOfDevices];                             // for dummy recieve Spi Frames
STATIC_AL uint8   CddTps92520_aucCHxVIN   [CDDTPS92520_AdcSamples][CDDTPS92520_CFG_NO_OF_CHANNELS];  // for averaging VIN values
STATIC_AL uint8   CddTps92520_aucCHxVLED  [CDDTPS92520_AdcSamples][CDDTPS92520_CFG_NO_OF_CHANNELS];  // for averaging VLED values
STATIC_AL uint8   CddTps92520_aucCHxVLEDON[CDDTPS92520_AdcSamples][CDDTPS92520_CFG_NO_OF_CHANNELS];  // for averaging VLEDON values

#define ctadCddLed_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of non initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of const structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_CONST_ROM_UNSPECIFIED
#include <../Cfg/CddTps92520_MemMap.h>

STATIC_AL CONST_AL uint16                     CddTps92520_aunZero       [CDDTPS92520_Cfg_NbOfDevices]      = { 0u };
STATIC_AL CONST_AL tCddTps92520_SpiSchedTable aCddTps92520_SpiSchedTable[CDDTPS92520_Cfg_SpiSchedTableLen] = CDDTPS92520_Cfg_SpiSchedTable_Init;

#define ctadCddLed_STOP_SEC_CONST_ROM_UNSPECIFIED
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of const structures and unions or arrays variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>


//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
STATIC_AL uint16  CddTps92520_CalcAndAddParity(const uint16 unCmd, const uint16 unAddr, const uint16 unData);
STATIC_AL boolean CddTps92520_CheckSpiValid   (const uint16 unRawData);
STATIC_AL boolean CddTps92520_StAction        (const uint8 ucAction);


//-----------------------------------------------------------------------------
// Function definitions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  check for SPI error
///
/// \descr  SPE bit (bit 15) shall be "0" and bit 14 always "1", all others means error
///
/// \param  uint16 unRawData
///
/// \return boolean: TRUE  - data valid
///                  FALSE - data invalid
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTps92520_CheckSpiValid(const uint16 unRawData)
{
  return ((unRawData & CDDTPS92520_SpiErrorMask) == CDDTPS92520_SpiRxExpected) ? TRUE : FALSE; 
}


//-----------------------------------------------------------------------------
/// \brief  get content of status register STATUS1
///
/// \descr
///
/// \param  ulChnIdx : channel index
/// \param  pSTATUS1 : content of status register STATUS1
///
/// \return boolean: TRUE - data are valid
///                  FALSE - data shall be discard
//-----------------------------------------------------------------------------
boolean CddTps92520_GetSTATUS1(const uint32 ulChnIdx, tCddTps92520_STATUS1* pSTATUS1)
{
  const uint32 ulDevice = ulChnIdx / CDDTPS92520_NbOfChannel;

  if ((ulDevice < CDDTPS92520_Cfg_NbOfDevices) &&  (pSTATUS1 != NULL_PTR))
  {
    *pSTATUS1 = CddTps92520_DataMirror.StatRx.aSTATUS1[ulDevice];
  }

  return CddTps92520_CheckSpiValid(CddTps92520_DataMirror.StatRx.aSTATUS1[ulDevice].unRaw);  // return SPI error status
}


//-----------------------------------------------------------------------------
/// \brief  get content of status register STATUS2
///
/// \descr
///
/// \param  ulChnIdx : channel index
/// \param  pSTATUS2 : content of status register STATUS2
///
/// \return boolean: TRUE - data are valid
///                  FALSE - data shall be discard
//-----------------------------------------------------------------------------
boolean CddTps92520_GetSTATUS2(const uint32 ulChnIdx, tCddTps92520_STATUS2* pSTATUS2)
{
  const uint32 ulDevice = ulChnIdx / CDDTPS92520_NbOfChannel;

  if ((ulDevice < CDDTPS92520_Cfg_NbOfDevices) && (pSTATUS2 != NULL_PTR))
  {
    *pSTATUS2 = CddTps92520_DataMirror.StatRx.aSTATUS2[ulDevice];
  }

  return CddTps92520_CheckSpiValid(CddTps92520_DataMirror.StatRx.aSTATUS2[ulDevice].unRaw);  // return SPI error status
}


//-----------------------------------------------------------------------------
/// \brief  Get content of status register STATUS3
///
/// \descr
///
/// \param  ulChnIdx : channel index
/// \param  pSTATUS3 : content of status register STATUS3
///
/// \return boolean: TRUE - data are valid
///                  FALSE - data shall be discard
//-----------------------------------------------------------------------------
boolean CddTps92520_GetSTATUS3(const uint32 ulChnIdx, tCddTps92520_STATUS3* pSTATUS3)
{
  const uint32 ulDevice = ulChnIdx / CDDTPS92520_NbOfChannel;

  if ((ulDevice < CDDTPS92520_Cfg_NbOfDevices) && (pSTATUS3 != NULL_PTR))
  {
    *pSTATUS3 = CddTps92520_DataMirror.StatRx.aSTATUS3[ulDevice];
  }

  return CddTps92520_CheckSpiValid(CddTps92520_DataMirror.StatRx.aSTATUS3[ulDevice].unRaw);  // return SPI error status
}


//-----------------------------------------------------------------------------
/// \brief  Get the CHxVIN measurement
///
/// \descr  Calculate average of 4 samples (average of CH1VIN and CH2VIN)
///
/// \param  ulChnIdx
///
/// \return uint32 raw voltage value multiplied by number of samples
//-----------------------------------------------------------------------------
uint32 CddTps92520_GetCHxVIN(const uint32 ulChnIdx)
{
  uint32 ulResult = 0u;
  
  for (uint32 ul = 0u; ul < CDDTPS92520_AdcSamples; ul++)
  {
    ulResult += CddTps92520_aucCHxVIN[ul][ulChnIdx];
  }

  return ulResult;
}


//-----------------------------------------------------------------------------
/// \brief  Get the CHxVLED measurement
///
/// \descr  Calculate average of 4 samples
///
/// \param  ulChnIdx
///
/// \return uint32 raw voltage value multiplied by number of samples
//-----------------------------------------------------------------------------
uint32 CddTps92520_GetCHxVLED(const uint32 ulChnIdx)
{
  uint32 ulResult = 0u;
  
  for (uint32 ul = 0u; ul < CDDTPS92520_AdcSamples; ul++)
  {
    ulResult += CddTps92520_aucCHxVLED[ul][ulChnIdx];
  }

  return ulResult;
}


//-----------------------------------------------------------------------------
/// \brief  Get the CHxVLEDON measurement
///
/// \descr  Calculate average of 4 samples
///
/// \param  ulChnIdx
///
/// \return uint32 raw voltage value multiplied by number of samples
//-----------------------------------------------------------------------------
uint32 CddTps92520_GetCHxVLEDON(const uint32 ulChnIdx)
{
  uint32 ulResult = 0u;
  
  for (uint32 ul = 0u; ul < CDDTPS92520_AdcSamples; ul++)
  {
    ulResult += CddTps92520_aucCHxVLEDON[ul][ulChnIdx];
  }

  return ulResult;
}


//-----------------------------------------------------------------------------
/// \brief  Read the CHxIADJL register (LSB)
///
/// \descr  Read the CHxIADJL 2 bits LSBs
///
/// \param  ulChnIdx : Channel index
/// \param  CHxIADJL*: 2 bits LSBs of 10 bits DAC analog current command
///
/// \return boolean: TRUE  - data are valid
///                  FALSE - data shall be discarded
//-----------------------------------------------------------------------------
boolean CddTps92520_GetCHxIADJL(const uint32 ulChnIdx, uint8* pucCHxIADJL)
{
  const uint32 ulDevice  = ulChnIdx / CDDTPS92520_NbOfChannel;
  const uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;

  if ((ulDevice < CDDTPS92520_Cfg_NbOfDevices) && (pucCHxIADJL != NULL_PTR))
  {
    *pucCHxIADJL = CddTps92520_DataMirror.CtrlRx.aCHxIADJL[ulChannel][ulDevice].Bit.bi2CHxIADJ;
  }

  return CddTps92520_CheckSpiValid(CddTps92520_DataMirror.CtrlRx.aCHxIADJL[ulChannel][ulDevice].unRaw);  // return SPI error status
}


//-----------------------------------------------------------------------------
/// \brief  Read the CHxIADJH register (MSB)
///
/// \descr  Read the CHxIADJH 8 bits MSBs
///
/// \param  ulChnIdx   : Channel index
/// \param  ucCHxIADJH*: 8 bits MSBs of 10 bits DAC analog current command
///
/// \return boolean: TRUE  - data are valid
///                  FALSE - data shall be discarded
//-----------------------------------------------------------------------------
boolean CddTps92520_GetCHxIADJH(const uint32 ulChnIdx, uint8* pucCHxIADJH)
{
  const uint32 ulDevice  = ulChnIdx / CDDTPS92520_NbOfChannel;
  const uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;

  if ((ulDevice < CDDTPS92520_Cfg_NbOfDevices) && (pucCHxIADJH != NULL_PTR))
  {
    *pucCHxIADJH = CddTps92520_DataMirror.CtrlRx.aCHxIADJH[ulChannel][ulDevice].Byte.ucCHxIADJ;
  }

  return CddTps92520_CheckSpiValid(CddTps92520_DataMirror.CtrlRx.aCHxIADJH[ulChannel][ulDevice].unRaw);  // return SPI error status
}


//-----------------------------------------------------------------------------
/// \brief  Set the CHxIADJL Analog current command (LSB)
///
/// \descr  Set the CHxIADJL 2 bits LSBs
///
/// \param  ulChnIdx : Channel index
/// \param  CHxIADJL : 2 bits LSBs of 10 bits DAC analog current command
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps92520_SetCHxIADJL(const uint32 ulChnIdx, const tCddTps92520_CHxIADJL CHxIADJL)
{
  const uint32 ulDevice  = ulChnIdx / CDDTPS92520_NbOfChannel;
  const uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;

  CddTps92520_DataMirror.CtrlTx.aCHxIADJL[ulChannel][ulDevice] = CHxIADJL;
}


//-----------------------------------------------------------------------------
/// \brief  Set the CHxIADJH Analog current command (MSB)
///
/// \descr  Set the CHxIADJH 8 bits MSBs
///
/// \param  ulChnIdx  : Channel index
/// \param  ucCHxIADJH: 8 bits MSBs of 10 bits DAC analog current command
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps92520_SetCHxIADJH(const uint32 ulChnIdx, const uint8 ucCHxIDJH)
{
  const uint32 ulDevice  = ulChnIdx / CDDTPS92520_NbOfChannel;
  const uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;

  CddTps92520_DataMirror.CtrlTx.aCHxIADJH[ulChannel][ulDevice].Byte.ucCHxIADJ = ucCHxIDJH;
}


//-----------------------------------------------------------------------------
/// \brief  Set the CHxTON register (buck frequency)
///
/// \descr  Set the 6 bit CHxTON register
///
/// \param  ulChIdx : Channel index
/// \param  ucCHxTON: target value
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps92520_SetCHxTON(const uint32 ulChnIdx, const uint8 ucCHxTON)
{
  const uint32 ulDevice  = ulChnIdx / CDDTPS92520_NbOfChannel;
  const uint32 ulChannel = ulChnIdx % CDDTPS92520_NbOfChannel;

  CddTps92520_DataMirror.CtrlTx.aCHxTON[ulChannel][ulDevice].Bit.bi6CHxTON = ucCHxTON;
}


//-----------------------------------------------------------------------------
/// \brief  Enable / Disable buck by CHxEN bit in SYSCFG1 register
///
/// \descr  
///
/// \param  ulChIdx   : Channel index
/// \param  boEn      : Enable / Disable
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps92520_EnableChannel(const uint32 ulChIdx, const boolean boEn)
{
  uint32 ulDeviceIdx = ulChIdx / CDDTPS92520_NbOfChannel;  // Get TPS92520 device index
  uint32 ulDeviceCh  = ulChIdx % CDDTPS92520_NbOfChannel;  // Get Channel index 0 or 1 of the device

  uint16 unEnable = (boEn != FALSE) ? CDDTPS92520_CH_x_ENABLE : CDDTPS92520_CH_x_DISABLE;

  if (ulDeviceCh == 0u)  // 1st channel
  {
    CddTps92520_DataMirror.CtrlTx.aSYSCFG1[ulDeviceIdx].Bit.biCH1EN = unEnable;
  }
  else  // (ulDeviceCh == CDDLED92520_CH_2_INDEX)
  {
    CddTps92520_DataMirror.CtrlTx.aSYSCFG1[ulDeviceIdx].Bit.biCH2EN = unEnable;
  }
}


//-----------------------------------------------------------------------------
/// \brief  Perfom specific actions synchronuously to SPI schedule table
///
/// \descr  Perform specific actions at the end of Spi_Rx reception before
///         switching next entry in schedule table.
///
///         not planned but prepared for future use
///
/// \param  ucAction
///
/// \return boolean:  TRUE: schedule table must be restarted
///                   FALSE: schedule table can continue with the next entry.
//-----------------------------------------------------------------------------
STATIC_AL boolean CddTps92520_StAction(const uint8 ucAction)
{
  boolean boRestart = FALSE;

  switch (ucAction)
  {
    case CDDTPS92520_ST_GETVIN:    // store VIN values (average of VIN1 and VIN2)
      CddTps92520_unAvrgVinIdx = (CddTps92520_unAvrgVinIdx >= (CDDTPS92520_AdcSamples - 1u)) ? 0u : CddTps92520_unAvrgVinIdx + 1u;

      for (uint32 ulDevice = 0u; ulDevice < CDDTPS92520_Cfg_NbOfDevices; ulDevice++)
      {
        if (CddTps92520_CheckSpiValid(CddTps92520_DataMirror.StatRx.aCHxVIN[0u][ulDevice].unRaw) != FALSE)  // ignore values for SPI errors (check CH1VIN only)
        {
          uint8 ucVin1 = CddTps92520_DataMirror.StatRx.aCHxVIN[0u][ulDevice].Byte.ucCHxVIN;
          uint8 ucVin2 = CddTps92520_DataMirror.StatRx.aCHxVIN[1u][ulDevice].Byte.ucCHxVIN;
          uint8 ucVin  = (uint8)(((uint32)ucVin1 + (uint32)ucVin2) / 2u);

          CddTps92520_aucCHxVIN[CddTps92520_unAvrgVinIdx][ulDevice * CDDTPS92520_NbOfChannel     ] = ucVin;
          CddTps92520_aucCHxVIN[CddTps92520_unAvrgVinIdx][ulDevice * CDDTPS92520_NbOfChannel + 1u] = ucVin;
        }
      }
      break;

    case CDDTPS92520_ST_GETVLED:    // store VLED values
      CddTps92520_unAvrgVledIdx = (CddTps92520_unAvrgVledIdx >= (CDDTPS92520_AdcSamples - 1u)) ? 0u : CddTps92520_unAvrgVledIdx + 1u;

      for (uint32 ulDevice = 0u; ulDevice < CDDTPS92520_Cfg_NbOfDevices; ulDevice++)
      {
        if (CddTps92520_CheckSpiValid(CddTps92520_DataMirror.StatRx.aCHxVLED[0u][ulDevice].unRaw) != FALSE)  // ignore values for SPI errors (check CH1VLED only)
        {
          CddTps92520_aucCHxVLED[CddTps92520_unAvrgVledIdx][ulDevice * CDDTPS92520_NbOfChannel     ] = CddTps92520_DataMirror.StatRx.aCHxVLED[0u][ulDevice].Byte.ucCHxVLED;
          CddTps92520_aucCHxVLED[CddTps92520_unAvrgVledIdx][ulDevice * CDDTPS92520_NbOfChannel + 1u] = CddTps92520_DataMirror.StatRx.aCHxVLED[1u][ulDevice].Byte.ucCHxVLED;
        }
      }
      break;

    case CDDTPS92520_ST_GETVLEDON:    // store VLEDON values
      CddTps92520_unAvrgVledOnIdx = (CddTps92520_unAvrgVledOnIdx >= (CDDTPS92520_AdcSamples - 1u)) ? 0u : CddTps92520_unAvrgVledOnIdx + 1u;

      for (uint32 ulDevice = 0u; ulDevice < CDDTPS92520_Cfg_NbOfDevices; ulDevice++)
      {
        if (CddTps92520_CheckSpiValid(CddTps92520_DataMirror.StatRx.aCHxVLEDON[0u][ulDevice].unRaw) != FALSE)  // ignore values for SPI errors (check CH1VLEDON only)
        {
          CddTps92520_aucCHxVLEDON[CddTps92520_unAvrgVledOnIdx][ulDevice * CDDTPS92520_NbOfChannel     ] = CddTps92520_DataMirror.StatRx.aCHxVLEDON[0u][ulDevice].Byte.ucCHxVLEDON;
          CddTps92520_aucCHxVLEDON[CddTps92520_unAvrgVledOnIdx][ulDevice * CDDTPS92520_NbOfChannel + 1u] = CddTps92520_DataMirror.StatRx.aCHxVLEDON[1u][ulDevice].Byte.ucCHxVLEDON;
        }
      }
      break;

    default:  //Do nothing
      break;
  }

  return boRestart;
}


//-----------------------------------------------------------------------------
/// \brief  Calculate odd parity bit based on 15 bits (Cmd, Addr, Data) and 
///         add it to bit position 8
///
/// \descr  Concatenate Command bit, Address register and Data
///         Calculate parity bit based on Cmd, Addr and data
///         Add parity bit in order to have an odd parity on SPI Tx frame
///
/// \param  unCmd   : Read or Write command bit shifted at the bit15
/// \param  unAddr  : Register address shifted at the bit position 9
/// \param  unData  : Data shifted at the bit position 0
///
/// \return uint16  : complete SPI command frame (Cmd, Addr, Parity Bit, Data)
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddTps92520_CalcAndAddParity(const uint16 unCmd, const uint16 unAddr, const uint16 unData)
{
  uint16 unCmdAddrData = (unCmd | unAddr | unData);  // Concat Command bit, address register and Data
  uint16 unResult = 0u;
  uint16 unParityWord = 0u;

  //for (uint32 ul = 0u; ul < CDDTPS92520_NbOfBit_SPIFrame; ul++)
  //{
  //  unResult ^= (unCmdAddrData >> ul);
  //}
  
  //if ((unResult & 0x01u) == 0u)  // if an even number of bits '1' has been counted
  //{
  //  unParityWord = CDDTPS92520_ParityBit;
  //}
  
  // optimized original code from above by using LUT
  unResult = (unCmdAddrData >> 8u) ^ (unCmdAddrData & 0x00FFu);
  unParityWord = CddTps92520_aunOddParityLUT[unResult];

  return unCmdAddrData | unParityWord;
}


//-----------------------------------------------------------------------------
/// \brief  Called before transmission of SPI telegram
///
/// \descr  The function reads the content of CddTps92520_DataMirror
///         and adds the odd parity bit.
///
/// \param  unDevIdx : index of TP92520 chip
///
/// \return uint32   : Tx data (16 LSB are valid)
//-----------------------------------------------------------------------------
uint32 CddTps92520_SpiTx(const uint16 unDevIdx)
{
  uint32  ulTxData = 0u;

  // calculate pointer to actual schedule table entry
  const tCddTps92520_SpiSchedTable* pTabEntry = &aCddTps92520_SpiSchedTable[CddTps92520_unSchedIx];

  // get SPI command (read or write), register address and contents of control register for next SPI frame
  // update parity bit according to control register data
  ulTxData = CddTps92520_CalcAndAddParity(pTabEntry->unCmd, pTabEntry->unAddr, pTabEntry->punTx[unDevIdx]);

  return ulTxData;
}


//-----------------------------------------------------------------------------
/// \brief  Called after reception of a SPI frame
///
/// \descr  The function reads the content of SPI Rx data provided by SPI and
 ///        store data in CddTps92520_DataMirror.
///
/// \param  unDevIdx : Device index
/// \param  ulData   : SPI Rx data (only 16 LSB valid)
///
/// \return void
//-----------------------------------------------------------------------------
void CddTps92520_SpiRx(const uint16 unDevIdx, const uint32 ulData)
{
  sint32 lSchedIx;

  // calculate pointer to actual schedule table entry
  const  tCddTps92520_SpiSchedTable* pTabEntry = &aCddTps92520_SpiSchedTable[CddTps92520_unSchedIx];

  if (CddTps92520_CheckSpiValid((uint16)ulData) == FALSE)
  {
    // SPI error detected
    CddTps92520_boSpiErrorLatch[unDevIdx * 2u] = TRUE;  // latching mechanism, a counter is not used in order to avoid extra max saturation 
    CddTps92520_boSpiErrorLatch[unDevIdx * 2u + 1u] = TRUE;  // latching mechanism, a counter is not used in order to avoid extra max saturation 
  }

  pTabEntry->punRx[unDevIdx] = (uint16)ulData;     // store RX data (only 16 LSB are relevant)

  if(unDevIdx == CddTps92520_unFirstDev)  // is last instance. Spi Tx callbacks called from 6,5,.. 0
  {
    // set index to next schedule table entry
    lSchedIx = (sint32)CddTps92520_unSchedIx + pTabEntry->cNextEntry;
    CddTps92520_unSchedIx = (uint16)lSchedIx;

    // calculate pointer to actual schedule table entry (read next TX entry to check action)
    pTabEntry = &aCddTps92520_SpiSchedTable[CddTps92520_unSchedIx];

    if (pTabEntry->ucAction != CDDTPS92520_NO_ACT)
    {
      boolean boSchTableRestart = CddTps92520_StAction(pTabEntry->ucAction);

      // restart support for future use
      (void)boSchTableRestart;
//    if (boSchTableRestart != FALSE)
//    {
//      CddTps92520_unSchedIx = 0u;
//    }
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  CddTps92520_SpiGetConfig
///
/// \descr  Provides device population footprint to CddSpi
///         to handle transmissions with bucks
///         Additionally check for nindex of first device
///
/// \param  punData: Data pointer to provide footprint
///
/// \return boolean
///           TRUE : Footprint data valid
///           FALSE: Footprint data invalid
///
//-----------------------------------------------------------------------------
boolean CddTps92520_SpiGetConfig(uint16* punData)
{
  boolean boRetVal = FALSE;
  *punData         = 0u;

  if (CDDTPS92520_EftDataValid() != FALSE)  // end of line data available
  {
    uint16 unDevice = CDDTPS92520_Cfg_NbOfDevices;

    while (unDevice > 0u)
    {
      unDevice--;

      if (CDDTPS92520_ECUVARCFG_ucDrvType(unDevice) != 0u)
      {
        *punData |= (uint16)((uint32)1u << unDevice);  // needed for SPI driver
        CddTps92520_unFirstDev = unDevice;             // do this until first device is found
      }
    }

    boRetVal = TRUE;
  }

  return boRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  CddTps92520_GetSpiError
///
/// \descr  Provides SPI Error status using a latch mechanism
///         After read, the error is cleared
///
/// \param  ulChnIdx: Channel index
///
/// \return boolean
///           TRUE : SPI error occurred from the last call
///           FALSE: SPI error did NOT occurred from the last call
///
//-----------------------------------------------------------------------------
boolean CddTps92520_GetSpiError(const uint32 ulChnIdx)
{
  boolean boRetVal    = CddTps92520_boSpiErrorLatch[ulChnIdx];  // get latched value

  CddTps92520_boSpiErrorLatch[ulChnIdx] = FALSE; // reset latch

  return boRetVal;
}

#define ctadCddLed_STOP_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------
