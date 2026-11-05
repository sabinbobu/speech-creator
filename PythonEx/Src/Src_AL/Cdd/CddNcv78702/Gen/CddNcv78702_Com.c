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
/// \file   CddNcv78702_Com.c
///
/// \brief
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
#include <CddNcv78702.h>
#include <CddNcv78702_Cb.h>
#include <CddNcv78702_Eft.h>

// module includes (relative to API)
#include <../Cfg/CddNcv78702_Cfg.h>
#include <../Cfg/CddNcv78702_RoutCfg.h>
#include <../Gen/CddNcv78702_Types.h>
#include <../Gen/CddNcv78702_Com.h>
#include <../Gen/CddNcv78702_Sched.h>


//-----------------------------------------------------------------------------
// Defines and Typedef
//-----------------------------------------------------------------------------
#define CDDNCV78702_InitZeroReg  {.unRaw=0x0000u}
#define CDDNCV78702_Reg0x01_Init {.Bit={ .biBOOST_SKCL=CDDNCV78702_Cfg_BOOST_SKCL,                \
                                          .biBOOST_OTA_GAIN=CDDNCV78702_Cfg_BOOST_OTA_GAIN,        \
                                          .biVDRIVE_VSETPOINT=CDDNCV78702_Cfg_VDRIVE_VSETPOINT,    \
                                          .biVBOOST_VGATE_THR=CDDNCV78702_Cfg_VBOOST_VGATE_THR,    \
                                          .biBOOST_DIV3_DIV2=CDDNCV78702_BOOST_DIV3_DIV2_reserved, \
                                          .biUNUSED=0u}}
#define CDDNCV78702_Reg0x02_Init {.Bit={.biBOOST_VLIMTH1=CDDNCV78702_Cfg_BOOST_VLIMTH1, .biBOOST_VLIMTH2=CDDNCV78702_Cfg_BOOST_VLIMTH2, .biBOOST_VLIMTH3=CDDNCV78702_BOOST_VLIMTH3_reserved, .biBOOST_SLPCTRL=CDDNCV78702_Cfg_BOOST_SLPCTLR, .biZero=0u, .biUNUSED=0u}}
#define CDDNCV78702_Reg0x03_Init {.Bit={ .biBOOST_OVERVOLTSD_THR=CDDNCV78702_Cfg_BOOST_OVERVOLTSD_THR,  \
                                          .biBOOST_SRCINV=CDDNCV78702_Cfg_BOOST_SRCINV,                  \
                                          .biBOOST_MULTI_PHASE_MD=CDDNCV78702_Cfg_BOOST_MULTI_PHASE_MD,  \
                                          .biUNUSED=0u}}
#define CDDNCV78702_Reg0x04_Init {.Bit={ .biBOOST_VSETPOINT=CDDNCV78702_BOOST_VSETPOINT_Init,  \
                                          .biFSO_BST_FREQ=CDDNCV78702_Cfg_FSO_BST_FREQ,         \
                                          .biUNUSED=0u}}
#define CDDNCV78702_Reg0x05_Init {.Bit={ .biBOOST1_EN=CDDNCV78702_BOOSTx_EN_Disable,    \
                                          .biBOOST2_EN=CDDNCV78702_BOOSTx_EN_Disable,    \
                                          .biBOOST3_EN=CDDNCV78702_BOOST3_EN_reserved,   \
                                          .biFSO_MD=CDDNCV78702_Cfg_FSO_MD,              \
                                          .biADC_TEMP_THR=CDDNCV78702_Cfg_ADC_TEMP_THR,  \
                                          .biTSD_AUT_RCVR_EN=CDDNCV78702_Cfg_TSD_AUT_RCVR_EN,  \
                                          .biUNUSED=0u}}
#define CDDNCV78702_Reg0x06_Init {.Bit={ .biVDD_ENA=CDDNCV78702_Cfg_VDD_ENA, \
                                          .biFSO_ENABLE_SEL=CDDNCV78702_Cfg_FSO_ENABLE_SEL,  \
                                          .biVBOOST_TOFF_SET=CDDNCV78702_Cfg_VBOOST_TOFF_SET,  \
                                          .biVBOOST_TON_SET=CDDNCV78702_Cfg_VBOOST_TON_SET,  \
                                          .biBOOST_OV_REACT=CDDNCV78702_Cfg_BOOST_OV_REACT,  \
                                          .biUNUSED=0u}}
#define CDDNCV78702_Reg0x07_Init {.Bit={.biP_DISTRIBUTION1=CDDNCV78702_Cfg_P_DISTRIBUTION1, .biP_DISTRIBUTION2=CDDNCV78702_Cfg_P_DISTRIBUTION2, .biUNUSED=0u}}
#define CDDNCV78702_Reg0x08_Init {.Bit={.biP_DISTRIBUTION3=CDDNCV78702_P_DISTRIBUTION3_Reserved, .biVDRIVE_UV_THR=CDDNCV78702_Cfg_VDRIVE_UV_THR, .biZero=0u, .biUNUSED=0u}}

#define CDDNCV78702_DataMirror_Init  \
{                                     \
  { /* CtrlTx */                      \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_Reg0x01_Init,        \
    CDDNCV78702_Reg0x02_Init,        \
    CDDNCV78702_Reg0x03_Init,        \
    CDDNCV78702_Reg0x04_Init,        \
    CDDNCV78702_Reg0x05_Init,        \
    CDDNCV78702_Reg0x06_Init,        \
    CDDNCV78702_Reg0x07_Init,        \
    CDDNCV78702_Reg0x08_Init,        \
    CDDNCV78702_InitZeroReg          \
  },                                  \
  { /* CtrlRx */                      \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg          \
                                      \
  },                                  \
  { /* StatRx */                      \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg,         \
    CDDNCV78702_InitZeroReg          \
  }                                   \
}

#define CDDNCV78702_Reg0x00_Tx &CddNcv78702_DataMirror.CtrlTx.Reg0x00.unRaw
#define CDDNCV78702_Reg0x01_Tx &CddNcv78702_DataMirror.CtrlTx.Reg0x01.unRaw
#define CDDNCV78702_Reg0x02_Tx &CddNcv78702_DataMirror.CtrlTx.Reg0x02.unRaw
#define CDDNCV78702_Reg0x03_Tx &CddNcv78702_DataMirror.CtrlTx.Reg0x03.unRaw
#define CDDNCV78702_Reg0x04_Tx &CddNcv78702_DataMirror.CtrlTx.Reg0x04.unRaw
#define CDDNCV78702_Reg0x05_Tx &CddNcv78702_DataMirror.CtrlTx.Reg0x05.unRaw
#define CDDNCV78702_Reg0x06_Tx &CddNcv78702_DataMirror.CtrlTx.Reg0x06.unRaw
#define CDDNCV78702_Reg0x07_Tx &CddNcv78702_DataMirror.CtrlTx.Reg0x07.unRaw
#define CDDNCV78702_Reg0x08_Tx &CddNcv78702_DataMirror.CtrlTx.Reg0x08.unRaw

#define CDDNCV78702_Reg0x01_Rx &CddNcv78702_DataMirror.CtrlRx.Reg0x01.unRaw
#define CDDNCV78702_Reg0x02_Rx &CddNcv78702_DataMirror.CtrlRx.Reg0x02.unRaw
#define CDDNCV78702_Reg0x03_Rx &CddNcv78702_DataMirror.CtrlRx.Reg0x03.unRaw
#define CDDNCV78702_Reg0x04_Rx &CddNcv78702_DataMirror.CtrlRx.Reg0x04.unRaw
#define CDDNCV78702_Reg0x05_Rx &CddNcv78702_DataMirror.CtrlRx.Reg0x05.unRaw
#define CDDNCV78702_Reg0x06_Rx &CddNcv78702_DataMirror.CtrlRx.Reg0x06.unRaw
#define CDDNCV78702_Reg0x07_Rx &CddNcv78702_DataMirror.CtrlRx.Reg0x07.unRaw
#define CDDNCV78702_Reg0x08_Rx &CddNcv78702_DataMirror.CtrlRx.Reg0x08.unRaw
#define CDDNCV78702_Reg0x0A_Rx &CddNcv78702_DataMirror.StatRx.Reg0x0A.unRaw
#define CDDNCV78702_Reg0x0B_Rx &CddNcv78702_DataMirror.StatRx.Reg0x0B.unRaw
#define CDDNCV78702_Reg0x0D_Rx &CddNcv78702_DataMirror.StatRx.Reg0x0D.unRaw

#define CDDNCV78702_Zero_Tx  &CddNcv78702_aunZero
#define CDDNCV78702_Dummy_Rx &CddNcv78702_aunDummy

#define CDDNCV78702_BSTSYNC_DUTY_50  0x4000u

#define CDDNCV78702_RestartCntInit    5u  // check 5 times until doing RESET or RESTART


// SPI schedule table entry datatype
typedef struct tCddNcv78702_SpiSchedTable
{
  sint8         cNextEntry;   // offset to next schedule table entry
  uint8         ucAction;     // index of action function done after Rx --> TODO change as function pointer ?
  uint16        unCmd;        // Read/Write Command to send
  uint16        unAddr;       // SPI address (combination of low and high nibble)
  const uint16* punTx;        // SPI control register data for transmission     - offset related to 1st address of stuct
  uint16*       punRx;        // SPI status register data for reception         - offset related to 1st address of stuct
} tCddNcv78702_SpiSchedTable;


//-----------------------------------------------------------------------------
// Start definitions of initialized boolean variables
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_VAR_INIT_BOOLEAN
#include <../Cfg/CddNcv78702_MemMap.h>

STATIC_AL boolean CddNcv78702_boSpiValid_Reg0x0A = TRUE;

#define ctadCddBoost_STOP_SEC_VAR_INIT_BOOLEAN
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized boolean variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of initialized 16 bit variables
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_VAR_INIT_16
#include <../Cfg/CddNcv78702_MemMap.h>

STATIC_AL uint16 CddNcv78702_unSchedIx    = 0u;  // pointer to schedule table
STATIC_AL uint16 CddNcv78702_aunDummy     = 0u;  // for dummy recieve Spi Frames
STATIC_AL uint16 CddLed78702_unRestartCnt = CDDNCV78702_RestartCntInit;  // debounce timer for restart

#define ctadCddBoost_STOP_SEC_VAR_INIT_16
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized 16 bit variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_VAR_INIT_UNSPECIFIED
#include <../Cfg/CddNcv78702_MemMap.h>

STATIC_AL tCddNcv78702_DataMirror CddNcv78702_DataMirror = CDDNCV78702_DataMirror_Init;
STATIC_AL CONST_AL uint16 CddNcv78702_aunOddParityLUT[256] = { 0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,
                                              0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,
                                              0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,
                                              0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,
                                              0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,
                                              0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,
                                              0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,
                                              0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,
                                              0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,
                                              0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,
                                              0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,
                                              0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,
                                              0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,
                                              0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,
                                              0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,
                                              0x0200,0x0000,0x0000,0x0200,0x0000,0x0200,0x0200,0x0000,0x0000,0x0200,0x0200,0x0000,0x0200,0x0000,0x0000,0x0200 };

#define ctadCddBoost_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of 16 bit const
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_CONST_ROM_16BIT
#include <../Cfg/CddNcv78702_MemMap.h>

STATIC_AL CONST_AL uint16 CddNcv78702_aunZero = 0;

#define ctadCddBoost_STOP_SEC_CONST_ROM_16BIT
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of 16 bit const
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of const structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_CONST_ROM_UNSPECIFIED
#include <../Cfg/CddNcv78702_MemMap.h>

STATIC_AL CONST_AL tCddNcv78702_SpiSchedTable aCddNcv78702_SpiSchedTable[CDDNCV78702_Cfg_SpiSchedTableLen] = CDDNCV78702_Cfg_SpiSchedTable_Init;

#define ctadCddBoost_STOP_SEC_CONST_ROM_UNSPECIFIED
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of const structures and unions or arrays variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>


//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
STATIC_AL uint16  CddNcv78702_CalculateAndAddOddParityBit(const uint16 unCmd, const uint16 unAddr, const uint16 unData);
STATIC_AL boolean CddNcv78702_StAction(const uint8 ucAction);
STATIC_AL uint16  CddNcv78702_CalcParity10(const uint16 unInput);


//-----------------------------------------------------------------------------
// Function definitions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  Calculate parity
///
/// \descr  
///
/// \param  unInput
///
/// \return uint16 parity ( 0=even, 1=odd)
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddNcv78702_CalcParity10(const uint16 unInput)
{
  uint16 unResult = 0u;

  for (uint32 ul = 0u; ul < 10u; ul++)
  {
    unResult ^= (unInput >> ul);
  }

  return unResult & 0x01u;
}

#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief  CddNcv78702_SetBoostOverVoltageThr
///
/// \descr  
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddNcv78702_SetBoostOverVoltageThr(void)
{
  CddNcv78702_DataMirror.CtrlTx.Reg0x03.Bit.biBOOST_OVERVOLTSD_THR = ((CDDNCV78702_ECUVARCFG_ucVariant(0) == 3u) ? CDDNCV78702_Cfg_60V_BOOST_OVERVOLTSD_THR : CDDNCV78702_Cfg_BOOST_OVERVOLTSD_THR);
}
#endif


//-----------------------------------------------------------------------------
/// \brief  Set the Booster Voltage Setpoint
///
/// \descr  Set the Booster voltage setpoint sent via SPI.
///
/// \param  ucBoostVsetpoint
///
/// \return void
//-----------------------------------------------------------------------------
void CddNcv78702_SetBoostVsetpoint(const uint8 ucBoostVsetpoint)
{
  CddNcv78702_DataMirror.CtrlTx.Reg0x04.Bit.biBOOST_VSETPOINT = ucBoostVsetpoint;
}


//-----------------------------------------------------------------------------
/// \brief  Indicate RESET state
///
/// \descr
///
/// \param  uint32 ulIdx (for future use)
///
/// \return boolean: TRUE  - driver in RESET state
///                  FALSE - else
//-----------------------------------------------------------------------------
boolean CddNcv78702_IsReset(const uint32 ulIdx)
{
  (void) ulIdx;

  return (CddNcv78702_unSchedIx < CDDNCV78702_Cfg_SpiSchedTableCycStart) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  Get content of status register Reg0x0A (STATUS1)
///
/// \descr
///
/// \param  pReg0x0A : content of status register pReg0x0A
///
/// \return boolean: TRUE  - data are valid
///                  FALSE - data shall be discard
//-----------------------------------------------------------------------------
boolean CddNcv78702_GetReg0x0A(tCddNcv78702_Reg0x0A* pReg0x0A)
{
  if (pReg0x0A != NULL_PTR)
  {
    *pReg0x0A = CddNcv78702_DataMirror.StatRx.Reg0x0A;
  }

  return CddNcv78702_boSpiValid_Reg0x0A;  // return SPI error status
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
STATIC_AL uint16 CddNcv78702_CalculateAndAddOddParityBit(const uint16 unCmd, const uint16 unAddr, const uint16 unData)
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
  //  unParityWord = (unCmd == CDDNCV78702_ReadCmd) ? CDDNCV78702_ParityBitReadFrame : CDDNCV78702_ParityBitWriteFrame;
  //}
  
  // optimized original code from above by using LUT
  unResult = (unCmdAddrData >> 8u) ^ (unCmdAddrData & 0x00FFu);
  unParityWord = CddNcv78702_aunOddParityLUT[unResult];

  if(unCmd == CDDNCV78702_WriteCmd)
  {
    unParityWord <<= 1u;
  }

  return unCmdAddrData | unParityWord;
}


//-----------------------------------------------------------------------------
/// \brief  Action executed synchronously with schedule Table
///
/// \descr
///
/// \param  ucAction
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddNcv78702_StAction(const uint8 ucAction)
{
  boolean boRestart = FALSE;
  boolean boBoostStatus;

  switch (ucAction)
  {
    case CDDNCV78702_ST_ACT_DIS_BOOST:
      CddNcv78702_SetBoostEnableGpio(FALSE);
      break;

    case CDDNCV78702_ST_ACT_BSTSYNC_50:
      //Enable booster bits
      //TODO CddLed check EFT param to set enable booster bits
      if (CDDNCV78702_ECUVARCFG_ucBoostCfg(0) == CDDNCV78702_EFT_BoosterDual)
      {
        CddNcv78702_DataMirror.CtrlTx.Reg0x05.Bit.biBOOST1_EN = 1u;
        CddNcv78702_DataMirror.CtrlTx.Reg0x05.Bit.biBOOST2_EN = 1u;
      }
      else if (CDDNCV78702_ECUVARCFG_ucBoostCfg(0) == CDDNCV78702_EFT_BoosterSingle)
      {
        CddNcv78702_DataMirror.CtrlTx.Reg0x05.Bit.biBOOST1_EN = 1u;
      }
      else
      {
        //Do nothing. Enable bits pre init with 0
      }
      CddNcv78702_SetBoostBstSyncDuty(CDDNCV78702_BSTSYNC_DUTY_50);
      break;

    case CDDNCV78702_ST_ACT_EN_BOOST:
      CddNcv78702_SetBoostEnableGpio(TRUE);
      break;

    case CDDNCV78702_ST_CHECK_START:
      if (CDDNCV78702_EftDataValid() == FALSE) //PRQA S 2742 1 // CddEft not yet enabled
      {
        boRestart = TRUE; // Loop in SPI schedule table index 0..2
      }
      break;

    case CDDNCV78702_ST_CHECK_STATUS:
      {
        boolean boSpiErr = CddNcv78702_DataMirror.StatRx.Reg0x0A.Frame.biSPIERR;                   // SPI Error bit in receive frame
        uint16  unParity = CddNcv78702_CalcParity10(CddNcv78702_DataMirror.StatRx.Reg0x0A.unRaw);  // Parity bit in data frame

        CddNcv78702_boSpiValid_Reg0x0A = ((boSpiErr != FALSE) || (unParity == 0u)) ? FALSE : TRUE;

        if (CddNcv78702_boSpiValid_Reg0x0A == FALSE)  // any doubt about signal quality: SPI error bit set or MISO continously low or high
        {
          CddLed78702_unRestartCnt = CDDNCV78702_RestartCntInit;        // reset validation counter
        }
        else
        {
          boolean boRestartNeed = FALSE;
          boBoostStatus = (CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biBOOST1_STATUS == 0u) ? FALSE : TRUE; // FALSE = BOOST_OV or VDRIVE_UV

          if (CDDNCV78702_ECUVARCFG_ucBoostCfg(0) == CDDNCV78702_EFT_BoosterDual)
          {
            if (CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biBOOST2_STATUS == 0u)  // BOOST_OV or VDRIVE_UV
            {
              boBoostStatus = FALSE;  // OR Boost1_Status and Boost2_Status for dual booster
            }
          }

          if (CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biHWR == 1u)    // RESET
          {
            boRestartNeed = TRUE;  // restart needed after validation
          }

          if ( (CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biHWR == 1u)  // RESET
            || ((boBoostStatus == FALSE) && (CddNcv78702_DataMirror.StatRx.Reg0x0A.Bit.biBOOST_OV == 0u)) )  // not BOOST_OV --> VDRIVE_UV
          {
            if (CddLed78702_unRestartCnt == 0u)                         // validated
            {
              CddNcv78702_SetBoostEnableGpio(FALSE);
              boRestart = boRestartNeed;                                // restart schedule table in case of HWR
            }
            else
            {
              CddLed78702_unRestartCnt--;                               // validation in progress
            }
          }
          else
          {
            CddLed78702_unRestartCnt = CDDNCV78702_RestartCntInit;      // reset validation counter
          }
        }
      }
      break;
    default:  //Do nothing
      break;
  }

  return boRestart;
}


//-----------------------------------------------------------------------------
/// \brief  Called after reception of a SPI frame
///
/// \descr  The function reads the content of SPI Rx data provided by SPI and
///         store data in CddNcv78702_DataMirror.
///
/// \param  unIx
/// \param  ulData  : SPI Rx data (only 16 LSB valid)
///
/// \return void
//-----------------------------------------------------------------------------
void CddNcv78702_SpiRx(const uint16 unIx, const uint32 ulData)
{
  sint32 lSchedIx;
  boolean boSchTableRestart = FALSE;

  // calculate pointer to actual schedule table entry
  const  tCddNcv78702_SpiSchedTable* pTabEntry = &aCddNcv78702_SpiSchedTable[CddNcv78702_unSchedIx];

  pTabEntry->punRx[unIx] = (uint16) ulData;  // store RX data (only 16 LSB are relevant)

  // set index to next schedule table entry
  lSchedIx = (sint32)CddNcv78702_unSchedIx + pTabEntry->cNextEntry;
  CddNcv78702_unSchedIx = (uint16)lSchedIx;

  // calculate pointer to actual schedule table entry (read next TX entry to check action)
  pTabEntry = &aCddNcv78702_SpiSchedTable[CddNcv78702_unSchedIx];

  if (pTabEntry->ucAction != CDDNCV78702_ST_NO_ACT)
  {
    boSchTableRestart = CddNcv78702_StAction(pTabEntry->ucAction);
    if (boSchTableRestart != FALSE)
    {
      CddNcv78702_unSchedIx = 0u;
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  Called before transmission of SPI telegram
///
/// \descr  The function reads the content of CddNcv78702_DataMirror
///         and adds the odd parity bit.
///
/// \param  unIx
///
/// \return uint32  : Tx data (16 LSB are valid)
//-----------------------------------------------------------------------------
uint32 CddNcv78702_SpiTx(const uint16 unIx)
{
  // calculate pointer to actual schedule table entry
  const tCddNcv78702_SpiSchedTable* pSchedEntry = &aCddNcv78702_SpiSchedTable[CddNcv78702_unSchedIx];

  (void)unIx;

  // get SPI command (read or write), register address and contents of control register for next SPI frame
  // update parity bit according to control register data
  return (uint32) CddNcv78702_CalculateAndAddOddParityBit(pSchedEntry->unCmd, pSchedEntry->unAddr, *(pSchedEntry->punTx));
}


//-----------------------------------------------------------------------------
/// \brief  Called before SBC sleep
///
/// \descr  The function disables the booster
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddNcv78702_SetBoostSleep(void)
{
  uint16 unCmdAddrData = CddNcv78702_CalculateAndAddOddParityBit(CDDNCV78702_WriteCmd, CDDNCV78702_WriteReg0x06Addr, 0u);
  (void)CDDNCV78702_TransferMsg((uint8)CDDSPI_DEVICE(BOOST), &unCmdAddrData);
}


#define ctadCddBoost_STOP_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------

