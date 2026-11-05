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
/// \file  CddStp8899Com.c
///
/// \brief  Handling of Stepper-Communication via SPI - Texas Instruments TI-DRV8899
///
/// \descr  Handling of Stepper-Communication via SPI incl. Data-Mirror- & Error-Handling
///
///         Stat-Reg-'B' - Basic-Status - comes each time 'automatically' - 1      |  1          |  UVLO  |  CPUV  |  OCP  |  STL  |  TF  |  OL
///         Stat-Reg-0   - Fault-Status                                   - FAULT  |  SPI_ERROR  |  UVLO  |  CPUV  |  OCP  |  STL  |  TF  |  OL
///         Stat-Reg-1   - Diag-Status-1                                  - OCP_LS2_B | OCP_HS2_B | OCP_LS1_B | OCP_HS1_B | OCP_LS2_A | OCP_HS2_A | OCP_LS1_A | OCP_HS1_A
///         Stat-Reg-2   - Diag-Status-2                                  - UTW  |  OTW  |  OTS  |  STL_LRN_OK  |  STALL  |  RSVD  |  OL_B  |  OL_A
///
///         Ctrl-Reg-1  -  TRQ_DAC [3:0]  |  RSVD  |  SLEW_RATE [1:0]
///         Ctrl-Reg-2  -  DIS_OUT  |  RSVD  |  TOFF [1:0]  |  DECAY [2:0]
///         Ctrl-Reg-3  -  DIR  |  STEP  |  SPI_DIR  |  SPI_STEP  |  MICROSTEP_MODE [3:0]
///         Ctrl-Reg-4  -  CLR_FLT  |  LOCK [2:0]  |  EN_OL  |  OCP_MODE  |  OTSD_MODE  |  TW_REP  - e.g. EN_OL: 0x31=0011.0001 | 0x39=0011.1001
///         Ctrl-Reg-5  -  RSVD [1:0]  |  STL_LRN  |  EN_STL  |  STL_REP  |  OL_TIME [1:0]  |  EN_SR_BLANK
///         Ctrl-Reg-6  -  STALL_TH [7:0]
///         Ctrl-Reg-7  -  TRQ_COUNT [7:0]
///         Ctrl-Reg-8  -  RSVD  |  REV_ID [3:0]
///
///         New Error-Debouncing
///           SPI-Error and OpenLoad-Error are LATCHED errors  ->  in order to have any debouncing the Error-Bit has to be 'cleared': Ctrl-Reg-4 'CLR_FLT'
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Ott, Peter ALRT/EEG-PM2 (otp2rt)
///         mailTo:peter.ott(at)al-lighting.com
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------

#include <Std_Types.h>
#include <AL_Helper.h>

#include <UtilBase_Atomic.h>

#include <RteCommonTypes.h>

#include <Cfg/CddStp_Cfg.h>

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
  #include <CddStpPrj.h>
  #include <CddStpData.h>
#else // Unit-Tests!
  uint32 CddStp_UnitTestHelper_ul1;
  uint32 CddStp_UnitTestHelper_ul2;
  boolean CddStp_UnitTestHelper_bo1;
  boolean CddStp_UnitTestHelper_bo2;

  #define CFA_CNT_STP_88XX   (4u)
  #include <CddStpPrj.h>
  #include <CddStpData.h>
#endif

#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
  #include <CddStp_Simulation.h>
#endif // CDDSTP_CFG_SIMULATION

#include <8899/CddStp8899Cfg.h>
#include <88XX/CddStp88XX_HalStp.h>
#include <8899/CddStp8899Com.h>


//=============================================================================
// defines
//=============================================================================

// reserved register-values
#define RSVD_0               (0u)


// #define CDDSTP_DEBUGGING_VARS
#ifdef CDDSTP_DEBUGGING_VARS
  volatile uint16 aaa_CddStp__SpiRx_1;
  volatile uint8  aaa_CddStp__SpiRx_2;
  volatile uint8  aaa_CddStp__SpiRx_3;
  volatile uint8  aaa_CddStp__SpiRx_4_OL_Cntr;
  volatile uint8  aaa_CddStp__SpiRx_4v_OL_Cntr;
  volatile uint8  aaa_CddStp__SpiRx_5_SC_Cntr;
  volatile uint8  aaa_CddStp__SpiRx_5v_SC_Cntr;
#endif //CDDSTP_DEBUGGING_VARS


//=============================================================================
// Mirror of TI-Drv8899 registers (initialization values)
//=============================================================================
// ctrl-register format and initialization values
#define LOW_BYTE_FIRST 1
#define CPU_BYTE_ORDER LOW_BYTE_FIRST
#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    #define TI8899_REG01     {{ CDDSTP88xx_default_SLEW_RATE, RSVD_0, CDDSTP88xx_default_TRQ_DAC }}
    #define TI8899_REG02     {{ CDDSTP88xx_default_DECAY, CDDSTP88xx_default_TOFF, RSVD_0, CDDSTP88xx_default_DIS_OUT }}
    #define TI8899_REG03     {{ CDDSTP88xx_default_MICROSTEP_MODE, CDDSTP88xx_default_SPI_STEP, CDDSTP88xx_default_SPI_DIR, CDDSTP88xx_default_STEP, CDDSTP88xx_default_DIR }}
    #define TI8899_REG04     {{ CDDSTP88xx_default_TW_REP, CDDSTP88xx_default_OTSD_MODE, CDDSTP88xx_default_OCP_MODE, CDDSTP88xx_default_EN_OL, CDDSTP88xx_default_LOCK, CDDSTP88xx_default_CLR_FLT }}
    #define TI8899_REG05     {{ RSVD_0 }} // RSVD
    #define TI8899_REG06     {{ RSVD_0 }} // RSVD - reserved but somehow about step-speed
    #define TI8899_REG07     {{ RSVD_0 }} // RSVD
#else
  #error Unsupported version
#endif

  #if(CFA_CNT_STP_88XX   == 1)
    #define INIT_TI8899(x)    { x }
  #elif(CFA_CNT_STP_88XX == 2)
    #define INIT_TI8899(x)    { x, x }
  #elif(CFA_CNT_STP_88XX == 3)
    #define INIT_TI8899(x)    { x, x, x }
  #elif(CFA_CNT_STP_88XX == 4)
    #define INIT_TI8899(x)    { x, x, x, x }
  #else
    #error Unsupported number of stepper
  #endif

  #if(CFA_CNT_STP_88XX == 4)

    #define DRV8899_DATAMIRROR_INIT        \
      {                                    \
        {   /* CtrlTx */                   \
        INIT_TI8899(TI8899_REG01),         /* aCReg1  {{ SLEW_RATE, RSVD_0, TRQ_DAC }}*/                         \
        INIT_TI8899(TI8899_REG02),         /* aCReg2  {{ DECAY, TOFF, RSVD_0, DIS_OUT }}*/                       \
        INIT_TI8899(TI8899_REG03),         /* aCReg3  {{ MICROSTEP_MODE, SPI_STEP, SPI_DIR, STEP, DIR }}*/       \
        INIT_TI8899(TI8899_REG04)          /* aCReg4  {{ TW_REP, OTSD_MODE, OCP_MODE, EN_OL, LOCK, CLR_FLT }}*/  \
        }                                  \
                                           \
                                           \
        /* Usually: CtrlRx and StatRx and StatvRx intentionally not initialized explicitely */ \
                                           \
        , { {{{0}}}, {{{0}}}, {{{0}}}, {{{0}}} }, { {{{0}}}, {{{0}}}, {{{0}}}, {{{0}}} }, { {{{0}}}, {{{0}}}, {{{0}}}, {{{0}}} } \
      }

  #else
    //#error Number of stepper not supported
  #endif

  // Addr.-Byte:
  // B7: 0
  // B6: write=0, read=1
  // 5 bits of Reg.-Adr.: B5...B1 | e.g. 3=0000.0010=CtrlReg '1'
  // B0: don't care
  #define DRV88XX_Addr(x)              ((uint8) (((x) & 0x1F) << (1u)))    // left-shift by '1' of B4...B0 to B5...B1
  #define DRV88XX_Addr_R(x)            ((uint8) (DRV88XX_Addr(x) | 0x40))  // add '1' in B6
  #define DRV88XX_Addr_W(x)            ((uint8) (DRV88XX_Addr(x)))         // yet no extra handling


  // Registers ------------------------------------------------------------------

  typedef enum teCddStp_TI8899_RegAddr
  {
    CddStp_TI8899_RegAddr_FAULT_Status  = 0x00,
    CddStp_TI8899_RegAddr_DIAG_Status_1 = 0x01,
    CddStp_TI8899_RegAddr_DIAG_Status_2 = 0x02,
    CddStp_TI8899_RegAddr_CTRL1         = 0x03,
    CddStp_TI8899_RegAddr_CTRL2         = 0x04,
    CddStp_TI8899_RegAddr_CTRL3         = 0x05,
    CddStp_TI8899_RegAddr_CTRL4         = 0x06,
    CddStp_TI8899_RegAddr_CTRL5         = 0x07, // RSVD
    CddStp_TI8899_RegAddr_CTRL6         = 0x08, // RSVD - reserved but somehow about step-speed
    CddStp_TI8899_RegAddr_CTRL7         = 0x09  // RSVD
  } teCddStp_TI8899_RegAddr;

  #define DRV88XX_SReg_FLT             CddStp_TI8899_RegAddr_FAULT_Status  // = 0x00
  #define DRV88XX_SReg_D1              CddStp_TI8899_RegAddr_DIAG_Status_1 // = 0x01
  #define DRV88XX_SReg_D2              CddStp_TI8899_RegAddr_DIAG_Status_2 // = 0x02
  #define DRV88XX_CREG01               CddStp_TI8899_RegAddr_CTRL1         // = 0x03
  #define DRV88XX_CREG02               CddStp_TI8899_RegAddr_CTRL2         // = 0x04
  #define DRV88XX_CREG03               CddStp_TI8899_RegAddr_CTRL3         // = 0x05
  #define DRV88XX_CREG04               CddStp_TI8899_RegAddr_CTRL4         // = 0x06
  #define DRV88XX_CREG05               CddStp_TI8899_RegAddr_CTRL5         // = 0x07 - 8899: RSVD
  #define DRV88XX_CREG06               CddStp_TI8899_RegAddr_CTRL6         // = 0x08 - 8899: RSVD - reserved but somehow about step-speed
  #define DRV88XX_CREG07               CddStp_TI8899_RegAddr_CTRL7         // = 0x09 - 8899: RSVD

  // read ----------------------------------------------------------
  #define DRV88XX_arSReg_FLT           DRV88XX_Addr_R(DRV88XX_SReg_FLT)
  #define DRV88XX_arSReg_D1            DRV88XX_Addr_R(DRV88XX_SReg_D1)
  #define DRV88XX_arSReg_D2            DRV88XX_Addr_R(DRV88XX_SReg_D2)
  #define DRV88XX_arCREG01             DRV88XX_Addr_R(DRV88XX_CREG01)
  #define DRV88XX_arCREG02             DRV88XX_Addr_R(DRV88XX_CREG02)
  #define DRV88XX_arCREG03             DRV88XX_Addr_R(DRV88XX_CREG03)
  #define DRV88XX_arCREG04             DRV88XX_Addr_R(DRV88XX_CREG04)
  #define DRV88XX_arCREG05             DRV88XX_Addr_R(DRV88XX_CREG05)
  #define DRV88XX_arCREG06             DRV88XX_Addr_R(DRV88XX_CREG06)
  #define DRV88XX_arCREG07             DRV88XX_Addr_R(DRV88XX_CREG07)

  // write -------------------------------------------------------
  #define DRV88XX_awCREG01             DRV88XX_Addr_W(DRV88XX_CREG01)
  #define DRV88XX_awCREG02             DRV88XX_Addr_W(DRV88XX_CREG02)
  #define DRV88XX_awCREG03             DRV88XX_Addr_W(DRV88XX_CREG03)
  #define DRV88XX_awCREG04             DRV88XX_Addr_W(DRV88XX_CREG04)
  #define DRV88XX_awCREG05             DRV88XX_Addr_W(DRV88XX_CREG05)
  #define DRV88XX_awCREG06             DRV88XX_Addr_W(DRV88XX_CREG06)
  #define DRV88XX_awCREG07             DRV88XX_Addr_W(DRV88XX_CREG07)

  #define ST_ACTION_NONE               (0u)
  #define ST_ACTION_TRIM_CALC          (1u)
  #define ST_ACTION_CHECK_START        (2u)
  #define ST_ACTION_CHECK_REG06        (3u)
  #define ST_ACTION_CHECK_REG07        (4u)

  

#define tCddSpiL2Channel uint8

// DRV 8899 commands
// TI: read/write ... S. 37 !!
// addr-Byte: 0 | R/W |  A4 | A3 | A2 | A1 | A0 | x
// R/W: 1=read, 0=write
// Example: Read e.g. SR1: '0100010'

// SPI address for reading
#define  DRV8899_rSR0_                                         0x40u  // 'real'-Adr 0
#define  DRV8899_rSR1_                                         0x42u  // 'real'-Adr 1
#define  DRV8899_rSR2_                                         0x44u  // 'real'-Adr 2
#define  DRV8899_rCR1_                                         0x46u  // 'real'-Adr 3
#define  DRV8899_rCR2_                                         0x48u  // 'real'-Adr 4
#define  DRV8899_rCR3_                                         0x4Au  // 'real'-Adr 5
#define  DRV8899_rCR4_                                         0x4Cu  // 'real'-Adr 6

// SPI address for writing (no writing for Status-Reg)
#define  DRV8899_wCR1_                                         0x06u  // 'real'-Adr 3
#define  DRV8899_wCR2_                                         0x08u  // 'real'-Adr 4
#define  DRV8899_wCR3_                                         0x0Au  // 'real'-Adr 5
#define  DRV8899_wCR4_                                         0x0Cu  // 'real'-Adr 6
  
#define  DRV8899_Nop__                                         0x00u


// defines used in schedule table entries
#define    ST_CTRL_TX_CR1   &CddStp8899Com_DataMirror.CtrlTx.aCReg1[0].ucRaw
#define    ST_CTRL_TX_CR2   &CddStp8899Com_DataMirror.CtrlTx.aCReg2[0].ucRaw
#define    ST_CTRL_TX_CR3   &CddStp8899Com_DataMirror.CtrlTx.aCReg3[0].ucRaw
#define    ST_CTRL_TX_CR4   &CddStp8899Com_DataMirror.CtrlTx.aCReg4[0].ucRaw
#define    ST_CTRL_TX_ZERO  CddStp8899Com_ucZero

#define    ST_CTRL_RX_CR1   &CddStp8899Com_DataMirror.CtrlRx.aCReg1[0].ucRaw
#define    ST_CTRL_RX_CR2   &CddStp8899Com_DataMirror.CtrlRx.aCReg2[0].ucRaw
#define    ST_CTRL_RX_CR3   &CddStp8899Com_DataMirror.CtrlRx.aCReg3[0].ucRaw
#define    ST_CTRL_RX_CR4   &CddStp8899Com_DataMirror.CtrlRx.aCReg4[0].ucRaw

#define    ST_STAT_RX_SRB   &CddStp8899Com_DataMirror.StatRx.aSRegBasic[0].ucRaw   // Basic-Status - comes each time 'automatically' - 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL
#define    ST_STAT_RX_SR0   &CddStp8899Com_DataMirror.StatRx.aSRegFault[0].ucRaw     // Fault-Status                                   - FAULT | SPI_ERROR | UVLO | CPUV | OCP | RSVD | TF | OL
#define    ST_STAT_RX_SR1   &CddStp8899Com_DataMirror.StatRx.aSRegDiag1[0].ucRaw   // Diag-Status-1                                  - OCP_LS2_B | OCP_HS2_B | OCP_LS1_B | OCP_HS1_B | OCP_LS2_A | OCP_HS2_A | OCP_LS1_A | OCP_HS1_A
#define    ST_STAT_RX_SR2   &CddStp8899Com_DataMirror.StatRx.aSRegDiag2[0].ucRaw   // Diag-Status-2                                  - UTW | OTW | OTS | RSVD | OL_B | OL_A



// jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd
//  * SPI-Entprellung
//  * SPI-Rx-Verification ...: 'CddStp8899Com_CheckSpiComSt0'
//  * MOTEN anpassen
//  * HCM\8899\CddStp8899Types.h anpassen & Bits anlegen
// jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd - jk-tbd


#define  CDDSTP8899_CHECKDRVDEFECT_MAX       (83u)  // 1 s = 1000 ms = 83 * 12 ms in case of cyclic ST0 has 12 entries: after 12 ms it is restarted
 
#define  CDDSTP8899_VBATSDrvDefect         (5500u)  // [mV] VBATS < 2.5 V but 5.5 V because of 2 ms SysVolt average - DRV88XX specific
#define  CDDSTP8899_RegValVBATSDD          (0xFFu)  // control and status register value in case of VBATS < 2.5 V: SPI does not work and data is set by pull up resistances
#define  CDDSTP8899_SRBValVBATSDD          (0x3Fu)  // Basic       status register value in case of VBATS < 2.5 V: SPI does not work and data is set by pull up resistances

#define  CDDSTP8899_ENABLE_DEBUG           STD_OFF

//=============================================================================
// local types
//=============================================================================

// SPI schedule table entry
typedef struct
{
  uint8        ucNextEntry;       // index of next schedule table entry
  uint8        ucAddr;            // SPI address (combination of low and high nibble)
  const uint8* pucCtrlTx;         // SPI control register data for transmission       - offset related to 1st address of stuct 
  uint8*       pucRxDataByte;     // SPI control/status register data 1 for reception - offset related to 1st address of stuct
  uint8*       pucRxDummy;        // SPI status register data 2 for reception - use instead of this:  'uint8* pucStatusBasic = ST_STAT_RX_SRB'
} tCddStp8899Com_SpiSchedTable;


//=============================================================================
// local function prototypes
//=============================================================================

STATIC_AL void   CddStp8899Com_SpiRx(uint16 unIx, uint16 unData);
STATIC_AL uint16 CddStp8899Com_SpiTx(uint16 unIx);

STATIC_AL   boolean CddStp8899Com_CheckSpiComSt0     (tCddSpiL2Channel SpiL2Channel);

#if (CDDSTP8899_ENABLE_DEBUG == STD_ON)
STATIC_AL void    CddStp8899Com_DEBUG_Check_EnOl_DisOut(void);
#endif


#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
// check simulation
STATIC_AL void CddStp8899Com_Simulation_HandleSpiRxStatusBits(tCddSpiL2Channel SpiL2Channel,     const boolean *pboSim_DriverDefect
                                            , const boolean *pboSim_UVLO_UnderVoltageLockout,    const boolean *pboSim_CPUV_ChargePumpUndervoltage
                                            , const boolean *pboSim_OCP_OverCurrentProtection,   const boolean *pboSim_OL_OpenLoad
                                          /*, const boolean *pboSim_TF_ThermalFault*/,           const boolean *pboSim_OTW_OverThermalWarning
                                            , const boolean *pboSim_OTS_OverTemperatureShutdown, const boolean *pboSim_UTW_UnderTemperatureWarning);
#endif // CDDSTP_CFG_SIMULATION


//=============================================================================
// variables
//=============================================================================
// usage of global definitions is allowed for inline function access only

// mirror of DRV8899 registers
tCddStp8899Com_DataMirror CddStp8899Com_DataMirror            = DRV8899_DATAMIRROR_INIT;

#if(CFA_CNT_STP_88XX == 4)

  uint8                   CddStp8899Com_aucStReqSingle          [CFA_CNT_STP_88XX] = { 0, 0, 0, 0 };   // each bit represents a requested schedule table
  uint8                   CddStp8899Com_aucStReqOnceMore        [CFA_CNT_STP_88XX] = { 0, 0, 0, 0 };   // each bit represents a requested schedule table

  STATIC_AL uint8         CddStp8899Com_aucActSchedTable        [CFA_CNT_STP_88XX] = { (uint8)CddStp8899Com_eSt0, (uint8)CddStp8899Com_eSt0, (uint8)CddStp8899Com_eSt0, (uint8)CddStp8899Com_eSt0 };                      // number of actual schedule table CddStp8899Com_eSt3
  STATIC_AL uint8         CddStp8899Com_aucSchedState           [CFA_CNT_STP_88XX] = { CDDSTP8899_SpiSt_StartIx0, CDDSTP8899_SpiSt_StartIx0, CDDSTP8899_SpiSt_StartIx0, CDDSTP8899_SpiSt_StartIx0 };  // index to         schedule table CddStp8899Com_eSt3

  // CddStp8899Com_aulRxNotification[] is used to handle RX notification functions
  STATIC_AL uint32        CddStp8899Com_aulRxNotification       [CFA_CNT_STP_88XX] = { 0, 0, 0, 0 };
  STATIC_AL uint8         CddStp8899Com_aucTrqDac_LastTx        [CFA_CNT_STP_88XX] = { 0, 0, 0, 0 };
  STATIC_AL uint8         CddStp8899Com_aucTrqDac_PrevTx        [CFA_CNT_STP_88XX] = { 0, 0, 0, 0 };

  STATIC_AL uint16        CddStp8899Com_aunTxData               [CFA_CNT_STP_88XX];    // filled in fct '...SpiRx' and used in fct '...SpiTx'
  STATIC_AL boolean       CddStp8899Com_DoClearFaultBit         [CFA_CNT_STP_88XX];    // usually 'CLR_FLT' in CReg4 is '0' - only on request do WRITE ONCE a '1'
  STATIC_AL uint8         CddStp8899Com_aucDebouncingCtr_OL     [CFA_CNT_STP_88XX];
  STATIC_AL uint8         CddStp8899Com_aucDebouncingCtr_OCP    [CFA_CNT_STP_88XX];
  STATIC_AL uint8         CddStp8899Com_aucDebouncingCtr_SPI    [CFA_CNT_STP_88XX];    // handled inside of section: 'SPI somehow NOT valid'

  STATIC_AL const uint8   CddStp8899Com_ucZero                  [CFA_CNT_STP_88XX] = INIT_TI8899(0); // { 0, 0, 0, 0 };

#else
 // #error Unsupported number of stepper
#endif

STATIC_AL uint8           CddStp8899Com_aucCheckDrvDefectCnt    [CFA_CNT_STP_88XX];

// DEBUG
#define UNTANGLE
#ifdef UNTANGLE
  #define UNTANGLE_INCR(x)               (x++);                // PRQA S 3410  // warning - QAC(Prio7) Msg: 3410(Macro parameter not enclosed in ().) Depth: 0 Ref: MISRA C:2012 Rule-20.7
  #define UNTANGLE_INCR_IF_NZ(x, y)      {if(x>0) {y++;}}      // PRQA S 3410  // warning - QAC(Prio7) Msg: 3410(Macro parameter not enclosed in ().) Depth: 0 Ref: MISRA C:2012 Rule-20.7
  #define UNTANGLE_RESET(x)              (x = 0);              // PRQA S 3410  // warning - QAC(Prio7) Msg: 3410(Macro parameter not enclosed in ().) Depth: 0 Ref: MISRA C:2012 Rule-20.7
  #define UNTANGLE_MAX(x, y)             (x = UTIL_MAX(x,y));  // PRQA S 3410  // warning - QAC(Prio7) Msg: 3410(Macro parameter not enclosed in ().) Depth: 0 Ref: MISRA C:2012 Rule-20.7
  typedef struct { uint32 ulRead; uint32 ulWrite; }   tCddStp8899Com_DEBUG_StlLrn_Cntr;
  STATIC_AL volatile tCddStp8899Com_DEBUG_StlLrn_Cntr  CddStp8899Com_DEBUG_StlLrn_Cntr[6+1];             // 2x Ctrl-Reg (of totally '8') are only 'READ'
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_StlLrn_Cntr__Cr5LastData;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_SpiOkCounter;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Rst;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Max;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Incr;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_OCP_Rst;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_OCP_Max;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_OCP_Incr;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_SPI_Rst;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_SPI_Max;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_SPI_Incr;
  STATIC_AL volatile uint8                             CddStp8899Com_ucDEBUG_DebouncingCtr_SpiFaultClear;
  STATIC_AL volatile uint32                            CddStp8899Com_ulDEBUG_DebouncingCtr_ClrFlt_Sent;
  STATIC_AL volatile uint32                            CddStp8899Com_ulDEBUG_SpiCheckCounter;            // count of fct-call 'CddStp8899Com_CheckSpiComSt0'
  STATIC_AL volatile uint32                            CddStp8899Com_ulDEBUG_SpiNOkCounter;              // count of all 'SPI not valid due to 'Rx' == 0xFF  (or SPI-HW-Error 'Bit.u1SPI_ERROR')  (or due to 'Error-Simulation')
  STATIC_AL volatile uint32                            CddStp8899Com_ulDEBUG_NotVrfyCounter;             // count of all 'CtrlTx != CtrlRx of 'TRQ_DAC''
  STATIC_AL volatile uint32                            CddStp8899Com_ulDEBUG_DrvDfctCounter;
  STATIC_AL volatile tCddStp8899Com_StatReg_Basic      CddStp8899Com___DEBUG_1stErrBit_Basic;
  STATIC_AL volatile tCddStp8899Com_StatReg_Fault      CddStp8899Com___DEBUG_1stErrBit_Fault;
#else
  #define UNTANGLE_INCR(x)
  #define UNTANGLE_INCR_IF_NZ(x, y)
  #define UNTANGLE_RESET(x)
  #define UNTANGLE_MAX(x, y)
#endif
  

// SPI schedule table
// one line represents one SPI transmit/receive sequence
// Attention !! This table must match the CDDSTP8899_SpiSt_...-List in CddStp8899Com.h !!

// tCddStp8899Com_SpiSchedTable:  uint8 ucNextEntry;  |  uint8 ucAddr;  |  const uint8* pucCtrlTx;  |  uint8* pucRxDataByte;  |  uint8* pucRxDummy;

STATIC_AL CONST_AL tCddStp8899Com_SpiSchedTable CddStp8899Com_SpiSchedTable[CDDSTP8899_SpiSt_IxMax + 1u] =
{
  //  ucNextEntry               | ucAddr                         | pucCtrlTx                     | pucRxDataByte                           | pucRxDummy - use instead of this:  'uint8* pucStatusBasic = ST_STAT_RX_SRB'
  //  idx of nxt schdlTbl-Entry | SPI addr                       | SPI ctrl-reg-data for transm. | SPI ctrl/state-reg data 1 for reception | SPI ctrl/state-reg data 2 for reception
  //  next                        TX: SPI register address (Cmd)   TX: control reg.                RX: ctrl/stat r.                          RX: status reg.       table
  //  state                                                        data byte                       data byte 1                               data byte 2           index

  // jk-tbd: use 'DRV88XX_awCREG01' instead of 'DRV8899_wCR1_'  &  use 'ST_CTRL_TX_REG01' instead of 'ST_CTRL_TX_CR1' etc

  // table 0 = CddStp8899Com_eSt0 (CDDSTP8899_SpiSt_ReadWriteAll
{  1u,                         DRV8899_wCR1_,                   ST_CTRL_TX_CR1,                ST_STAT_RX_SR2,                            ST_STAT_RX_SRB }, //  0 = CDDSTP8899_SpiSt_StartIx0
{  2u,                         DRV8899_wCR2_,                   ST_CTRL_TX_CR2,                ST_CTRL_RX_CR1,                            ST_STAT_RX_SRB }, //  1
{  3u,                         DRV8899_wCR1_,                   ST_CTRL_TX_CR1,                ST_CTRL_RX_CR2,                            ST_STAT_RX_SRB }, //  2
{  4u,                         DRV8899_wCR3_,                   ST_CTRL_TX_CR3,                ST_CTRL_RX_CR1,                            ST_STAT_RX_SRB }, //  3
{  5u,                         DRV8899_wCR1_,                   ST_CTRL_TX_CR1,                ST_CTRL_RX_CR3,                            ST_STAT_RX_SRB }, //  4
{  6u,                         DRV8899_wCR4_,                   ST_CTRL_TX_CR4,                ST_CTRL_RX_CR1,                            ST_STAT_RX_SRB }, //  5
{  7u,                         DRV8899_wCR1_,                   ST_CTRL_TX_CR1,                ST_CTRL_RX_CR4,                            ST_STAT_RX_SRB }, //  6
{  8u,                         DRV8899_rSR0_,                   ST_CTRL_TX_ZERO,               ST_CTRL_RX_CR1,                            ST_STAT_RX_SRB }, //  7
{  9u,                         DRV8899_wCR1_,                   ST_CTRL_TX_CR1,                ST_STAT_RX_SR0,                            ST_STAT_RX_SRB }, //  8
{ 10u,                         DRV8899_rSR1_,                   ST_CTRL_TX_ZERO,               ST_CTRL_RX_CR1,                            ST_STAT_RX_SRB }, //  9
{ 11u,                         DRV8899_wCR1_,                   ST_CTRL_TX_CR1,                ST_STAT_RX_SR1,                            ST_STAT_RX_SRB }, // 10
{  0u,                         DRV8899_rSR2_,                   ST_CTRL_TX_ZERO,               ST_CTRL_RX_CR1,                            ST_STAT_RX_SRB }  // 11 = CDDSTP8899_SpiSt_EndIx0
};                                                                                              


static const uint8 CddStp8899Com_aucStStart[CddStp8899Com_eStMax] = 
{ 
  CDDSTP8899_SpiSt_StartIx0 /*, 
  CDDSTP8899_SpiSt_StartIx1, 
  CDDSTP8899_SpiSt_StartIx2, 
  CDDSTP8899_SpiSt_StartIx3 */
};


typedef boolean (*tFctCheckSpiComPtr)(tCddSpiL2Channel SpiL2Channel);


static const tFctCheckSpiComPtr CddStp8899Com_aucStCheckSpiComFct[CddStp8899Com_eStMax] = 
{ 
  CddStp8899Com_CheckSpiComSt0 /*, 
  CddStp8899Com_CheckSpiComSt1, 
  CddStp8899Com_CheckSpiComSt2, 
  CddStp8899Com_CheckSpiComSt3 */
};


//=============================================================================
// Public functions  implementation
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  get Status-Register-Basic contents from RAM mirror (verified)
///
/// \descr  verified status register content is returned
///
/// \param  uint8  ucIx     stepper index 
///         uint8* pucSRegBsc pointer to status register Basic content (verified)
///
/// \return boolean 
//-----------------------------------------------------------------------------
boolean CddStp8899Com_GetSRegBsc(uint8 ucIx, uint8* pucSRegBsc)
{
  boolean boReturn = TRUE;

  *pucSRegBsc = CddStp8899Com_DataMirror.StatvRx.aSRegBasic[ucIx].ucRaw;

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  get Status-Register-FAULT contents from RAM mirror (verified)
///
/// \descr  verified status register content is returned
///
/// \param  uint8  ucIx     stepper index 
///         uint8* pucSRegFlt pointer to status register FAULT content (verified)
///
/// \return boolean 
//-----------------------------------------------------------------------------
boolean CddStp8899Com_GetSRegFlt(uint8 ucIx, uint8* pucSRegFlt)
{
  boolean boReturn = TRUE;

  *pucSRegFlt = CddStp8899Com_DataMirror.StatvRx.aSRegFault[ucIx].ucRaw;

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  get Status-Register-Diag-1 contents
///
/// \descr  verified status register content is returned
///
/// \param  uint8  ucIx     stepper index 
///         uint8* pucSRegDiag1 pointer to status register Diag1 content (verified)
///
/// \return boolean 
//-----------------------------------------------------------------------------
boolean CddStp8899Com_GetSRegDiag1(uint8 ucIx, uint8* pucSRegDiag1)
{
  boolean boReturn = TRUE;

  *pucSRegDiag1 = CddStp8899Com_DataMirror.StatvRx.aSRegDiag1[ucIx].ucRaw;

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  get Status-Register-Diag-2 contents
///
/// \descr  verified status register content is returned
///
/// \param  uint8  ucIx     stepper index 
///         uint8* pucSRegDiag2 pointer to status register Diag2 content (verified)
///
/// \return boolean 
//-----------------------------------------------------------------------------
boolean CddStp8899Com_GetSRegDiag2(uint8 ucIx, uint8* pucSRegDiag2)
{
  boolean boReturn = TRUE;

  *pucSRegDiag2 = CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[ucIx].ucRaw;

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  get Status-Register-Diag-1 & -2 contents
///
/// \descr  verified status register content is returned
///
/// \param  uint8  ucIx     stepper index 
///         uint8* pucSRegDiag2 pointer to status register Diag1 content (verified)
///         uint8* pucSRegDiag2 pointer to status register Diag2 content (verified)
///
/// \return boolean 
//-----------------------------------------------------------------------------
boolean CddStp8899Com_GetSRegDiag12(uint8 ucIx, uint8* pucSRegDiag1, uint8* pucSRegDiag2)
{
  boolean boReturn = TRUE;

  *pucSRegDiag1 = CddStp8899Com_DataMirror.StatvRx.aSRegDiag1[ucIx].ucRaw;
  *pucSRegDiag2 = CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[ucIx].ucRaw;

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  get SR1, SR2, SR6, SR7A, SR8A contents from RAM mirror (verified)
///
/// \descr  verified status register contents are returned
///
/// \param  uint8  ucIx     stepper index 
///         uint8* aSRegFault    pointer to status register FAULT  content (verified)
///         uint8* pucSRegDiag2  pointer to status register Diag-2 content (verified)
///
/// \return boolean 
//-----------------------------------------------------------------------------
boolean CddStp8899Com_GetSRegFltDiag2(uint8 ucIx, uint8* pucSRegFlt, uint8* pucSRegDiag2)
{
  // usually called with var 'CddStp88XX_aSRegXXX' like 'CddStp88XX_aSRegBasic[idx]', 'CddStp88XX_aSRegFault[idx]', 'CddStp88XX_aSRegDiag1[idx]', 'CddStp88XX_aSRegDiag2[idx]

  boolean boReturn = TRUE;

  *pucSRegFlt   = CddStp8899Com_DataMirror.StatvRx.aSRegFault[ucIx].ucRaw;
  *pucSRegDiag2 = CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[ucIx].ucRaw;

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  get SR1, SR2, SR6, SR7A, SR8A contents from RAM mirror (verified)
///
/// \descr  verified status register contents are returned
///
/// \param  uint8  ucIx     stepper index 
///         uint8* aSRegBasic    pointer to status register Basic  content (verified)
///         uint8* aSRegFault    pointer to status register FAULT  content (verified)
///         uint8* pucSRegDiag1  pointer to status register Diag-1 content (verified)
///         uint8* pucSRegDiag2  pointer to status register Diag-2 content (verified)
///
/// \return boolean 
//-----------------------------------------------------------------------------
boolean CddStp8899Com_GetSRegBscFltDiag12(uint8 ucIx, uint8* pucSRegBsc, uint8* pucSRegFlt, uint8* pucSRegDiag1, uint8* pucSRegDiag2)
{
  // usually called with var 'CddStp88XX_aSRegXXX' like 'CddStp88XX_aSRegBasic[idx]', 'CddStp88XX_aSRegFault[idx]', 'CddStp88XX_aSRegDiag1[idx]', 'CddStp88XX_aSRegDiag2[idx]

  boolean boReturn = TRUE;

  *pucSRegBsc   = CddStp8899Com_DataMirror.StatvRx.aSRegBasic[ucIx].ucRaw; // jk-tbd ... Basic-Status - comes each time 'automatically'
  *pucSRegFlt   = CddStp8899Com_DataMirror.StatvRx.aSRegFault[ucIx].ucRaw;
  *pucSRegDiag1 = CddStp8899Com_DataMirror.StatvRx.aSRegDiag1[ucIx].ucRaw;
  *pucSRegDiag2 = CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[ucIx].ucRaw;

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  check SPI communication for schedule table 0 as write verify of control registers 1 and 2 and read control registers 1 and 2
///
/// \descr  check communication by comparison of TX and RX data of CR1, CR2 registers
///         Usually called via 'CddStp8899Com_aucStCheckSpiComFct'
///
/// \param  tCddSpiL2Channel SpiL2Channel 
///
/// \return boolean boVerifyOk 
//-----------------------------------------------------------------------------
STATIC_AL boolean CddStp8899Com_CheckSpiComSt0(tCddSpiL2Channel SpiL2Channel)
{
  boolean boVerifyOk = FALSE;
  boolean boSpiValid = FALSE;

  boolean boSim_DriverDefect = FALSE;
  boolean boSim_SPI_ERROR_SpiProtocolError = FALSE;
  boolean boSim_UVLO_UnderVoltageLockout = FALSE;
  boolean boSim_CPUV_ChargePumpUndervoltage = FALSE;
  boolean boSim_OCP_OverCurrentProtection = FALSE;
  boolean boSim_OL_OpenLoad = FALSE;
//boolean boSim_TF_ThermalFault = FALSE;
  boolean boSim_OTW_OverThermalWarning = FALSE;
  boolean boSim_OTS_OverTemperatureShutdown = FALSE;
  boolean boSim_UTW_UnderTemperatureWarning = FALSE;

#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
  // check simulation
  CddStp_Simulation_HandleSpiRxStatusBits(&boSim_DriverDefect, &boSim_SPI_ERROR_SpiProtocolError , &boSim_UVLO_UnderVoltageLockout
                                                             , &boSim_CPUV_ChargePumpUndervoltage, &boSim_OCP_OverCurrentProtection
                                                             , &boSim_OL_OpenLoad
                                                           /*, &boSim_TF_ThermalFault*/          , &boSim_OTW_OverThermalWarning
                                                             , &boSim_OTS_OverTemperatureShutdown, &boSim_UTW_UnderTemperatureWarning);
#endif

#ifdef JK_TBD
  /* jk-tbd */ if (0);
#endif
  // New code:
  //  * There is only ONE Schedule-Table (ST)
  //  * Explicit reading of Ctrl-Registers is NEVER done
  //  * Rx of Ctrl-Regs is always the 'previous' value (tx=5 -> rx=?, tx=5 -> rx=5, tx=5 -> rx=5, tx=8 -> rx=5, tx=3 -> rx=8, tx=y -> rx=3, ...)
  //  * Daisy-Chain: Rx= SB3.SB2.SB1.Hdr1.Hdr2.R3.R2.R1  (SB=Status-Byte, Hdr=Header, R=register (Ctrl:'previous', Status:'current'))
  //  * Single-Dvc:  Rx= SB1.R1  (SB=Status-Byte, R=register (Ctrl:'previous', Status:'current'))
  //  * Check: SB (='All-Time' Status-Byte): Bit 6 & 7 always '1' (this is NOT the FALUT-Status or any Diag-Status)
  //  * Check: Some bits in Ctrl-Regs are always fixed and so these bits are checkable
  //  * Check: If Daisy-Chain: Rx-Hdr has to be Tx-Hdr

  {
    // FLMT-4524
    // New: Do this NOT with CURRENT values but do this with LAST VALID values
    //
    // Diag: Get raw content of 'all' TI-HW-Registers
    // use NEW behaviour: see below const aucValStp arrayStpRegValues = { // 'Rte_Type.h': 'typedef uint8 aucValStp[7];'
    // use NEW behaviour: see below                                       // CddStp8899Com_DataMirror.StatRx.aSRegBasic[0].ucRaw,
    // use NEW behaviour: see below                                          CddStp8899Com_DataMirror.StatRx.aSRegFault[0].ucRaw,
    // use NEW behaviour: see below                                          CddStp8899Com_DataMirror.StatRx.aSRegDiag1[0].ucRaw,
    // use NEW behaviour: see below                                          CddStp8899Com_DataMirror.StatRx.aSRegDiag2[0].ucRaw,
    // use NEW behaviour: see below                                          CddStp8899Com_DataMirror.CtrlRx.aCReg1[0].ucRaw,
    // use NEW behaviour: see below                                          CddStp8899Com_DataMirror.CtrlRx.aCReg2[0].ucRaw,
    // use NEW behaviour: see below                                          CddStp8899Com_DataMirror.CtrlRx.aCReg3[0].ucRaw,
    // use NEW behaviour: see below                                          CddStp8899Com_DataMirror.CtrlRx.aCReg4[0].ucRaw
    // use NEW behaviour: see below                                     };
    // use NEW behaviour: see below (void)Rte_Write_ppCddStpStpRegData0_aucValStp(arrayStpRegValues); // Rte_Write_ctacCddStp_ppCddStpStpRegData0_aucValStp
  }

  // schedule table 0 reads status registers Basic, Fault, Diag1, Diag2 - SPI valid check:
  if (   (CddStp8899Com_DataMirror.StatRx.aSRegBasic[SpiL2Channel].ucRaw != CDDSTP8899_SRBValVBATSDD)
      && (CddStp8899Com_DataMirror.StatRx.aSRegFault[SpiL2Channel].ucRaw != CDDSTP8899_RegValVBATSDD)
      && (CddStp8899Com_DataMirror.StatRx.aSRegDiag1[SpiL2Channel].ucRaw != CDDSTP8899_RegValVBATSDD)
      && (CddStp8899Com_DataMirror.StatRx.aSRegDiag2[SpiL2Channel].ucRaw != CDDSTP8899_RegValVBATSDD)
      && (boSim_SPI_ERROR_SpiProtocolError == FALSE))
  {
    boSpiValid = CddStp8899Com_DataMirror.StatRx.aSRegFault[SpiL2Channel].Bit.u1SPI_ERROR != FALSE ? FALSE : TRUE; // inverse logic
  }

#if (CFG_DEV_HOOK_EN == 1u)
  if (CddStp_ulTesterHookActivation == CDDSTP_SPI_ERR_HOOK_KEY)
  {
    boSpiValid = FALSE;
    CddStp88XX_aStpCtrl[SpiL2Channel].Bit.On = 1u;
    CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] = CDDSTP8899_CHECKDRVDEFECT_MAX;
  }
  else if (CddStp_ulTesterHookActivation == CDDSTP_RESET_HOOK_KEY)
  {
    boSpiValid = TRUE;
    CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] = 0u;
  }
  else
  {
    // nothing to do
  }
#endif

  // schedule table 0 reads status registers Basic, Fault, Diag1, Diag2 - SPI valid check:
  if (boSpiValid != FALSE)
  {
    CddStp88XX_aStpState[SpiL2Channel].Bit.SpiValid = 1;                                            // set SPI valid bit (driver is not in Sleep mode)

    // checks has been OK, copy now the raw SPI values into the verified status registers data mirror which is accessed from tasks by CddStp8899Com_GetSRegXxx1()
    CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].ucRaw = CddStp8899Com_DataMirror.StatRx.aSRegBasic[SpiL2Channel].ucRaw;    // copy verified status register value from raw SPI value
    CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].ucRaw = CddStp8899Com_DataMirror.StatRx.aSRegFault[SpiL2Channel].ucRaw;    // copy verified status register value from raw SPI value
    CddStp8899Com_DataMirror.StatvRx.aSRegDiag1[SpiL2Channel].ucRaw = CddStp8899Com_DataMirror.StatRx.aSRegDiag1[SpiL2Channel].ucRaw;    // copy verified status register value from raw SPI value
    CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[SpiL2Channel].ucRaw = CddStp8899Com_DataMirror.StatRx.aSRegDiag2[SpiL2Channel].ucRaw;    // copy verified status register value from raw SPI value


    // incr & check any 'latched'-OL-Error in fct 'CddStp88XX_HalStpLwr_IncOLCnt_'
    // New debouncing of Open-Load-Error
    if (CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1OL == 1u) // HW-OL-Bit active?
    {
      static volatile uint8 CddStp8899Com_DEBUG_MaxErr_OL = 18u; //  100; // 'Cold'-Stp: 0x2A: 1v5, 0x29: 1v15, 0x28=40: 1v200 (7xTX) (9..18V) (OL_Max=0x40), 0x20=32 (6xTX) (9..18V) (OL_Max=0x35), 0x12=18 (4xTX)(OL_Max=0x25)(9..18V)
      if (CddStp8899Com_aucDebouncingCtr_OL[SpiL2Channel] < CddStp8899Com_DEBUG_MaxErr_OL) // N.b.: Reset-Cmd (in CReg4) is sent only every 6ms  ->  in order to debounce only twice it takes around 12ms
      {
        CddStp8899Com_aucDebouncingCtr_OL[SpiL2Channel]++;
        UNTANGLE_MAX(CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Max, CddStp8899Com_aucDebouncingCtr_OL[SpiL2Channel]);  // PRQA S 400  // warning - QAC(Prio7) Msg: 400([U] 'CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Max' is modified more than once between sequence points - evaluation order unspecified.) Depth: 0 Ref: MISRA C:2012 Rule-1.3, Rule-13.2; REFERENCE - ISO:C90-6.3 Expressions

        CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1OL = 0; // reset Status-Reg-Basic
        CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1OL = 0; // reset Status-Reg-Fault

        if (CddStp8899Com_DoClearFaultBit[SpiL2Channel] == FALSE) // not already set?
        {
          UNTANGLE_INCR(CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Incr);  // this var will be reset if OL-Error is gone
          // reset any latched fault ('Bit.u1SPI_ERROR' or 'Bit.u1OL'): 'CLR_FLT'
          CddStp8899Com_DoClearFaultBit[SpiL2Channel] = TRUE; // this var wiil be reset if 'CReg4.CLR_FLT' is 'really' sent via SPI-TX
        }
      }
    }
    else // no OL-Error
    {
      UNTANGLE_INCR_IF_NZ(CddStp8899Com_aucDebouncingCtr_OL[SpiL2Channel], CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Rst);  // PRQA S 1862  //  warning - QAC(Prio7) Msg: 1862(The operands of this relational operator are of different 'essential signedness' but will both be promoted to 'signed int' for comparison.) Depth: 0 Ref: MISRA C:2012 Rule-10.4
      UNTANGLE_RESET(CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Incr);
      CddStp8899Com_aucDebouncingCtr_OL[SpiL2Channel] = 0; // reset
    }


    // New debouncing of Over-Current-Protection-Error
    if (CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1OCP == 1u) // HW-OCP-Bit active?
    {
      static volatile uint8 CddStp8899Com_DEBUG_MaxErr_OCP = 18u; //  ->  max=23 & 4xTX (CANoe-SC-Macro with 20ms -> max=30)
      if (CddStp8899Com_aucDebouncingCtr_OCP[SpiL2Channel] < CddStp8899Com_DEBUG_MaxErr_OCP) // N.b.: Reset-Cmd (in CReg4) is sent only every 6ms  ->  in order to debounce only twice it takes around 12ms
      {
        CddStp8899Com_aucDebouncingCtr_OCP[SpiL2Channel]++;
        UNTANGLE_MAX(CddStp8899Com_ucDEBUG_DebouncingCtr_OCP_Max, CddStp8899Com_aucDebouncingCtr_OCP[SpiL2Channel]);  // PRQA S 400  // warning - QAC(Prio7) Msg: 400([U] 'CddStp8899Com_ucDEBUG_DebouncingCtr_OL_Max' is modified more than once between sequence points - evaluation order unspecified.) Depth: 0 Ref: MISRA C:2012 Rule-1.3, Rule-13.2; REFERENCE - ISO:C90-6.3 Expressions

        CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1OCP = 0; // reset Status-Reg-Basic
        CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1OCP = 0; // reset Status-Reg-Fault

        if (CddStp8899Com_DoClearFaultBit[SpiL2Channel] == FALSE) // not already set?
        {
          UNTANGLE_INCR(CddStp8899Com_ucDEBUG_DebouncingCtr_OCP_Incr);  // this var will be reset if OCP-Error is gone
          // reset any latched fault ('Bit.u1SPI_ERROR' or 'Bit.u1OL' or 'Bit.u1OCP'): 'CLR_FLT'
          CddStp8899Com_DoClearFaultBit[SpiL2Channel] = TRUE; // this var wiil be reset if 'CReg4.CLR_FLT' is 'really' sent via SPI-TX
        }
      }
    }
    else // no OCP-Error
    {
      UNTANGLE_INCR_IF_NZ(CddStp8899Com_aucDebouncingCtr_OCP[SpiL2Channel], CddStp8899Com_ucDEBUG_DebouncingCtr_OCP_Rst);  // PRQA S 1862  //  warning - QAC(Prio7) Msg: 1862(The operands of this relational operator are of different 'essential signedness' but will both be promoted to 'signed int' for comparison.) Depth: 0 Ref: MISRA C:2012 Rule-10.4
      UNTANGLE_RESET(CddStp8899Com_ucDEBUG_DebouncingCtr_OCP_Incr);
      CddStp8899Com_aucDebouncingCtr_OCP[SpiL2Channel] = 0; // reset
    }
    // FLMT-4524
    // Do this NOT with CURRENT values but do this with LAST VALID values
    //
    // Diag: Get raw content of 'all' TI-HW-Registers
    // *** jk-tbd ***  do this EACH time?  *** jk-tbd ***
    //const aucValStp arrayStpRegValues[] = { // 'Rte_Type.h': 'typedef uint8 aucValStp[12];'
    //                                          CddStp8899Com_DataMirror.StatRx.aSRegBasic[0].ucRaw,
    //                                          CddStp8899Com_DataMirror.StatRx.aSRegFault[0].ucRaw,
    //                                          CddStp8899Com_DataMirror.StatRx.aSRegDiag1[0].ucRaw,
    //                                          CddStp8899Com_DataMirror.StatRx.aSRegDiag2[0].ucRaw,
    //                                          CddStp8899Com_DataMirror.CtrlRx.aCReg1[0].ucRaw,
    //                                          CddStp8899Com_DataMirror.CtrlRx.aCReg2[0].ucRaw,
    //                                          CddStp8899Com_DataMirror.CtrlRx.aCReg3[0].ucRaw,
    //                                          CddStp8899Com_DataMirror.CtrlRx.aCReg4[0].ucRaw,
    //                                          0, // CReg5
    //                                          0, // CReg6
    //                                          0, // CReg7
    //                                          0  // CReg8
    //                                    };
    // NOT here but a little bit below: (void)Rte_Write_ppCddStpStpRegData0_aucValStp(arrayStpRegValues); // Rte_Write_ctacCddStp_ppCddStpStpRegData0_aucValStp

#ifdef CDDSTP_DEBUGGING_VARS
    if (CddStp8899Com_DataMirror.StatRx.aSRegBasic[0].Bit.u1OL   != FALSE) aaa_CddStp__SpiRx_4_OL_Cntr++;
    if (CddStp8899Com_DataMirror.StatvRx.aSRegBasic[0].Bit.u1OL  != FALSE) aaa_CddStp__SpiRx_4v_OL_Cntr++;
    if (CddStp8899Com_DataMirror.StatRx.aSRegBasic[0].Bit.u1OCP  != FALSE) aaa_CddStp__SpiRx_5_SC_Cntr++;
    if (CddStp8899Com_DataMirror.StatvRx.aSRegBasic[0].Bit.u1OCP != FALSE) aaa_CddStp__SpiRx_5v_SC_Cntr++;
#endif // CDDSTP_DEBUGGING_VARS

#if (CFG_DEV_HOOK_EN == 1u)
    switch (CddStp_ulTesterHookActivation)
    {
    case CDDSTP_OTS_HOOK_KEY: CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[0].Bit.u1OTS = 1u; break;
    case CDDSTP_OTW_HOOK_KEY: CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[0].Bit.u1OTW = 1u; break;
    case CDDSTP_OCP_HOOK_KEY: CddStp8899Com_DataMirror.StatvRx.aSRegBasic[0].Bit.u1OCP = 1u;
                              CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1OCP = 1u;
                              break;
    case CDDSTP_RESET_HOOK_KEY: 
      CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[0].Bit.u1OTS = 0u;
      CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[0].Bit.u1OTW = 0u;
      CddStp8899Com_DataMirror.StatvRx.aSRegBasic[0].Bit.u1OCP = 0u;
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1OCP = 0u;
      break;
    default: break;
    }
#endif

#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
    // simulation
    CddStp8899Com_Simulation_HandleSpiRxStatusBits(SpiL2Channel, &boSim_DriverDefect
                                                               , &boSim_UVLO_UnderVoltageLockout ,   &boSim_CPUV_ChargePumpUndervoltage
                                                               , &boSim_OCP_OverCurrentProtection ,  &boSim_OL_OpenLoad
                                                             /*, &boSim_TF_ThermalFault*/,           &boSim_OTW_OverThermalWarning
                                                               , &boSim_OTS_OverTemperatureShutdown, &boSim_UTW_UnderTemperatureWarning);
#endif // CDDSTP_CFG_SIMULATION

#ifdef JK_TBD
    if (0); // jk-tbd: Check this 'if' with 'MOTEN': Does it still work?  ... probably NOT ;(
#endif
    // schedule table 0 writes and reads control registers 1 and 2
    // PRQA S 4397 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4397(An expression which is the result of a ~ or << operation has not been cast to its essential type.) Depth: 0 Ref: MISRA C:2012 Rule-10.7
// jk-orig:     if (   (CddStp8899Com_DataMirror.CtrlRx.aCReg1[SpiL2Channel].ucRaw & ~CDDSTP8899_old_Mask_MOTEN) == (CddStp8899Com_DataMirror.CtrlTx.aCReg1[SpiL2Channel].ucRaw & ~CDDSTP8899_old_Mask_MOTEN) // do not check CReg1 MOTEN bit to avoid ErrDrvDefect before UV/ErrOL/SC/Therm is detected in case of UV or error before switching driver on because of DRV8899 automatically clears MOTEN bit in this case
// jk-not-good: if (   (CddStp8899Com_DataMirror.CtrlRx.aCReg2[SpiL2Channel].Bit.u1DIS_OUT == CddStp8899Com_DataMirror.CtrlTx.aCReg2[SpiL2Channel].Bit.u1DIS_OUT) // do not check CReg1 MOTEN bit to avoid ErrDrvDefect before UV/ErrOL/SC/Therm is detected in case of UV or error before switching driver on because of DRV8899 automatically clears MOTEN bit in this case
    if    (CddStp8899Com_DataMirror.CtrlRx.aCReg1[SpiL2Channel].Bit.u4TRQ_DAC == CddStp8899Com_DataMirror.CtrlTx.aCReg1[SpiL2Channel].Bit.u4TRQ_DAC) // do not check CReg1 MOTEN bit to avoid ErrDrvDefect before UV/ErrOL/SC/Therm is detected in case of UV or error before switching driver on because of DRV8899 automatically clears MOTEN bit in this case
//O     && (CddStp8899Com_DataMirror.CtrlRx.aCReg2[SpiL2Channel].ucRaw                           ==  CddStp8899Com_DataMirror.CtrlTx.aCReg2[SpiL2Channel].ucRaw))
        //O - verify of CReg2 is not necessary because of CReg1 is checked and read of CReg2 is in next cycle to save one line in schedule table 0
    {
      CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] = 0;
      boVerifyOk = TRUE;
      Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_DRIVER_SPI, DEM_EVENT_STATUS_PASSED); // clear Stp SPI Bus DTC

      // FLMT-4524
      // Do this ONLY with LAST VALID values
      //(void)Rte_Write_ppCddStpStpRegData0_aucValStp(arrayStpRegValues); // Rte_Write_ctacCddStp_ppCddStpStpRegData0_aucValStp
    } // end of 'if (DataMirror.CtrlRx.TRQ_DAC == DataMirror.CtrlTx.TRQ_DAC)'

    else // not verified - occures also because after each change of Tx the first Rx is the old Tx date
    {
      uint16 unDIAG_VBAT;                                                                           // Vbat [mV]

      (void)IoHwAb_User_GetAdc_DIAG_VBAT(&unDIAG_VBAT);                                             // get DIAG_VBAT value

      if (   (unDIAG_VBAT >= CDDSTP8899_VBATSDrvDefect)                                             // voltage VBATS not too low and provokes no DRV88XX specific SPI communication error ErrDrvDefect?
          && (CddStp88XX_aStpCtrl[SpiL2Channel].Bit.On == 1u)                                       // DRV8899 driver not in sleep mode?
#ifdef JK_TBD
            if (0); // jk-tbd: Check this 'two conditions: Does this work?  ... probably NOT ;(
#endif
          && (CddStp8899Com_DataMirror.CtrlRx.aCReg1[SpiL2Channel].ucRaw != CDDSTP8899_RegValVBATSDD)                              // register value not set by pull up resistances
          && (CddStp8899Com_DataMirror.CtrlRx.aCReg2[SpiL2Channel].ucRaw != CDDSTP8899_RegValVBATSDD))                             // register value not set by pull up resistances
      {
        CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel]++; 
      }
      else                                                                                         // voltage VBATS too low        // Kl15 off               // LED6.1 specific: Kl15 off and Led switch on supports uC but not stepper drivers!
      {
        CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] = 0;                                      // restart counting SPI errors  // for next Kl15 not off  // LED6.1 specific: Kl15 off and Led switch on supports uC but not stepper drivers!
      }

      if (CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] >= CDDSTP8899_CHECKDRVDEFECT_MAX)
      {
        CddStp88XX_aStpState[SpiL2Channel].Bit.ErrDrvDefect = 1;                                   // set DRV8899 driver defect error bit
        CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] = CDDSTP8899_CHECKDRVDEFECT_MAX;          // avoid overflow - because of it is sent cyclic in schedule table 0
      }
      else                                                                                         // try next verify CDDSTP8899_CHECKDRVDEFECT_MAX
      {
        // MISRA
      }
    } // end of 'if (DataMirror.CtrlRx.TRQ_DAC == DataMirror.CtrlTx.TRQ_DAC)   -   else   // i.e.: NOT verified - occures also because after each change of Tx the first Rx is the old Tx date'
  } // end of 'if (boSpiValid != FALSE)'

  else // SPI not valid due to all 'Rx' == 0xFF
  {
    CddStp88XX_aStpState[SpiL2Channel].Bit.SpiValid = 0;                                           // SPI not valid (driver is in Sleep mode)

    CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].ucRaw = 0u; // reset due to sleep-mode
    CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].ucRaw = 0u; // reset due to sleep-mode
    CddStp8899Com_DataMirror.StatvRx.aSRegDiag1[SpiL2Channel].ucRaw = 0u; // reset due to sleep-mode
    CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[SpiL2Channel].ucRaw = 0u; // reset due to sleep-mode

    if (CddStp88XX_aStpCtrl[SpiL2Channel].Bit.On == 1u)                                            // DRV8899 driver not in sleep mode?
    {
      CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel]++; 
      if (CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] >= CDDSTP8899_CHECKDRVDEFECT_MAX)
      {
        CddStp88XX_aStpState[SpiL2Channel].Bit.ErrDrvDefect = 1;                                   // set DRV8899 driver defect error bit
        Rte_Call_DemPrj_ReportErrorStatus((uint16)STP_DRIVER_SPI, DEM_EVENT_STATUS_FAILED);        // set Stp SPI Bus DTC
        CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] = CDDSTP8899_CHECKDRVDEFECT_MAX;          // avoid overflow - because of it is sent cyclic in schedule table 0
      }
      else                                                                                         // try next verify CDDSTP8899_CHECKDRVDEFECT_MAX
      {
        // MISRA
      }
    }
    else                                                                                           // try next verify CDDSTP8899_CHECKDRVDEFECT_MAX
    {
      // MISRA
    }
  }

// RDM-Workaround?!
#ifdef CDDSTP_RDM_WORKAROUND
  CddStp_RDM_DataMirror_SRegBasic_OL        = CddStp8899Com_DataMirror.StatvRx.aSRegBasic[0].Bit.u1OL ;   // Indicates open-load condition.
  CddStp_RDM_DataMirror_SRegBasic_TF        = CddStp8899Com_DataMirror.StatvRx.aSRegBasic[0].Bit.u1TF ;   // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
  CddStp_RDM_DataMirror_SRegBasic_OCP       = CddStp8899Com_DataMirror.StatvRx.aSRegBasic[0].Bit.u1OCP ;  // Indicates overcurrent fault condition.
  CddStp_RDM_DataMirror_SRegBasic_CPUV      = CddStp8899Com_DataMirror.StatvRx.aSRegBasic[0].Bit.u1CPUV ; // Indicates charge pump undervoltage fault condition. Latched high after power-up, remains set until it is cleared through the CLR_FLT bit or an nSLEEP reset pulse.
  CddStp_RDM_DataMirror_SRegBasic_UVLO      = CddStp8899Com_DataMirror.StatvRx.aSRegBasic[0].Bit.u1UVLO ; // Indicates an undervoltage lockout  fault condition. Latched high after power-up, remains set until it is cleared through the CLR_FLT bit or an nSLEEP reset pulse.
  

  if ((CddStp_RDM_DataMirror_SRegFault_OL == 0) && (CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1OL != 0)) CddStp_RDM_DataMirror_SRegFault_OL_Cntr++; // changed to 'active'?
  CddStp_RDM_DataMirror_SRegFault_OL        = CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1OL ;   // Indicates open-load condition.
  CddStp_RDM_DataMirror_SRegFault_TF        = CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1TF ;   // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
  CddStp_RDM_DataMirror_SRegFault_OCP       = CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1OCP ;  // Indicates overcurrent fault condition.
  CddStp_RDM_DataMirror_SRegFault_CPUV      = CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1CPUV ; // Indicates charge pump undervoltage fault condition. Latched high after power-up, remains set until it is cleared through the CLR_FLT bit or an nSLEEP reset pulse.
  CddStp_RDM_DataMirror_SRegFault_UVLO      = CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1UVLO ; // Indicates an undervoltage lockout  fault condition. Latched high after power-up, remains set until it is cleared through the CLR_FLT bit or an nSLEEP reset pulse.
  CddStp_RDM_DataMirror_SRegFault_SPI_ERROR = CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1SPI_ERROR; // Indicates SPI protocol errors, such as more SCLK pulses than are required or SCLK is absent even though nSCS is low. Becomes high in fault and the nFAULT pin is driven low.
  CddStp_RDM_DataMirror_SRegFault_FAULT     = CddStp8899Com_DataMirror.StatvRx.aSRegFault[0].Bit.u1FAULT;     // When nFAULT pin is at 1, FAULT bit is 0. When nFAULT pin is at 0, FAULT bit is 1.

  CddStp_RDM_DataMirror_SRegDiag2_OTS       = CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[0].Bit.u1OTS; // Indicates overtemperature shutdown
  CddStp_RDM_DataMirror_SRegDiag2_OTW       = CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[0].Bit.u1OTW; // Indicates overtemperature warning.
  CddStp_RDM_DataMirror_SRegDiag2_UTW       = CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[0].Bit.u1UTW; // Indicates undertemperature warning.

  CddStp_RDM_StpState_SpiValid              = CddStp88XX_aStpState[0].Bit.SpiValid;     // set SPI valid bit (driver is not in Sleep mode)
  CddStp_RDM_StpState_ErrDrvDefect          = CddStp88XX_aStpState[0].Bit.ErrDrvDefect; // set DRV8899 driver defect error bit
#endif
  // PRQA S 4558 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 4558(An expression of 'essentially unsigned' type (unsigned char) is being used as the left-hand operand of this logical operator (&&).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
  return (boVerifyOk && boSpiValid) ? TRUE : FALSE;
  //PRQA S 5316 3 // STCYC is exceeded due to program architecture and readibility
  //PRQA S 5310 2 // STPTH is exceeded due to an active developer hook needed to simulate a behavior. If the hook is disabled from configuration, there is no HIS metric violation
  //PRQA S 5330 1 // STST3 is exceeded due to an active developer hook needed to simulate a behavior. If the hook is disabled from configuration, there is no HIS metric violation
}

//-----------------------------------------------------------------------------
/// \brief  CddStp8899Com_SetFaultClr
///
/// \descr
///
/// \param  ucChannelIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp8899Com_SetFaultClr(uint8 ucChannelIdx)
{
  CddStp8899Com_DoClearFaultBit[ucChannelIdx] = TRUE;
}


#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
//-----------------------------------------------------------------------------
/// \brief  CddStp8899Com_Simulation_HandleSpiRxStatusBits
///
/// \descr
///
/// \param  SpiL2Channel
/// \param  pboSim_DriverDefect
/// \param  pboSim_UVLO_UnderVoltageLockout
/// \param  pboSim_CPUV_ChargePumpUndervoltage
/// \param  pboSim_OCP_OverCurrentProtection
/// \param  pboSim_OL_OpenLoad
/// \param  pboSim_OTW_OverThermalWarning
/// \param  pboSim_OTS_OverTemperatureShutdown
/// \param  pboSim_UTW_UnderTemperatureWarning
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddStp8899Com_Simulation_HandleSpiRxStatusBits(tCddSpiL2Channel SpiL2Channel,     const boolean *pboSim_DriverDefect
                                            , const boolean *pboSim_UVLO_UnderVoltageLockout,    const boolean *pboSim_CPUV_ChargePumpUndervoltage
                                            , const boolean *pboSim_OCP_OverCurrentProtection,   const boolean *pboSim_OL_OpenLoad
                                          /*, const boolean *pboSim_TF_ThermalFault*/,           const boolean *pboSim_OTW_OverThermalWarning
                                            , const boolean *pboSim_OTS_OverTemperatureShutdown, const boolean *pboSim_UTW_UnderTemperatureWarning)
{
  // check simulation
  if (CddStp_Simulation_IsSimActive() != FALSE)
  {
    // check simulation
    if (*pboSim_DriverDefect != FALSE)
    {
      CddStp88XX_aStpState[SpiL2Channel].Bit.ErrDrvDefect = 1; // set DRV8899 driver defect error bit

   // CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit....: not available
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1FAULT = TRUE;
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1OCP   = TRUE; // tbd-jk: WORKAROUND in order to simulate an error
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1OL    = TRUE; // tbd-jk: WORKAROUND in order to simulate an error
    }
    else
    {
      // no need to reset: Variable 'CddStp8899Com_DataMirror' is set each time of SPI-RX
    }

    if (*pboSim_UVLO_UnderVoltageLockout != FALSE)
    {
      CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1UVLO = TRUE;
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1UVLO = TRUE;
    }
    else
    {
      // no need to reset: Variable 'CddStp8899Com_DataMirror' is set each time of SPI-RX
    }

    if (*pboSim_CPUV_ChargePumpUndervoltage != FALSE)
    {
      CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1CPUV = TRUE;
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1CPUV = TRUE;
    }
    else
    {
      // no need to reset: Variable 'CddStp8899Com_DataMirror' is set each time of SPI-RX
    }

    if (*pboSim_OCP_OverCurrentProtection != FALSE)
    {
      CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1OCP = TRUE;
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1OCP = TRUE;
    }
    else
    {
      // no need to reset: Variable 'CddStp8899Com_DataMirror' is set each time of SPI-RX
    }

    if (*pboSim_OL_OpenLoad != FALSE)
    {
      CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1OL = TRUE;
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1OL = TRUE;
    }
    else
    {
      // no need to reset: Variable 'CddStp8899Com_DataMirror' is set each time of SPI-RX
    }

    // 'TF': Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
    // 'TF' is set in 'OTS' or 'OTW' or 'UTW' if (*pboSim_TF_ThermalFault != FALSE)
    // 'TF' is set in 'OTS' or 'OTW' or 'UTW' {
    // 'TF' is set in 'OTS' or 'OTW' or 'UTW'   CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1TF = TRUE;
    // 'TF' is set in 'OTS' or 'OTW' or 'UTW'   CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1TF = TRUE;  // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
    // 'TF' is set in 'OTS' or 'OTW' or 'UTW'   CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[SpiL2Channel].Bit.u1OTS = TRUE; // Indicates overtemperature shutdown
    // 'TF' is set in 'OTS' or 'OTW' or 'UTW' }
    // 'TF' is set in 'OTS' or 'OTW' or 'UTW' else
    // 'TF' is set in 'OTS' or 'OTW' or 'UTW' {
    // 'TF' is set in 'OTS' or 'OTW' or 'UTW' }

    if (*pboSim_OTS_OverTemperatureShutdown != FALSE)
    {
      CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1TF  = TRUE;
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1TF  = TRUE;  // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
      CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[SpiL2Channel].Bit.u1OTS = TRUE; // Indicates overtemperature shutdown
    }
    else
    {
      // no need to reset: Variable 'CddStp8899Com_DataMirror' is set each time of SPI-RX
    }

    if (*pboSim_OTW_OverThermalWarning != FALSE)
    {
      CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1TF  = TRUE;
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1TF  = TRUE;  // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
      CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[SpiL2Channel].Bit.u1OTW = TRUE; // Indicates overtemperature warning
    }
    else
    {
      // no need to reset: Variable 'CddStp8899Com_DataMirror' is set each time of SPI-RX
    }

    if (*pboSim_UTW_UnderTemperatureWarning != FALSE)
    {
      CddStp8899Com_DataMirror.StatvRx.aSRegBasic[SpiL2Channel].Bit.u1TF  = TRUE;
      CddStp8899Com_DataMirror.StatvRx.aSRegFault[SpiL2Channel].Bit.u1TF  = TRUE;  // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
      CddStp8899Com_DataMirror.StatvRx.aSRegDiag2[SpiL2Channel].Bit.u1UTW = TRUE; // Indicates undertemperature warning
    }
    else
    {
      // no need to reset: Variable 'CddStp8899Com_DataMirror' is set each time of SPI-RX
    }
  } // end of 'if (CddStp_Simulation_IsSimActive() != FALSE)'

  else // no simulation is active
  {
    // no simulation is active ->  no changes are done
  }

  // PRQA S 5310, 5328 1 // program architecture and readability - intentionally no modification of existing code -  warning - QAC(Prio2) Msg: 5310(HIS metrics violation: 'CddStp8899Com_Simulation_HandleSpiRxStatusBits() : STPTH = 129' exceeds threshold 80 for Number of paths (STPTH).)  |  warning - QAC(Prio2) Msg : 5328(HIS metrics violation : 'CddStp8899Com_Simulation_HandleSpiRxStatusBits() : STPAR = 8' exceeds threshold 5 for Number of function parameters(STPAR).)
}
#endif // CDDSTP_CFG_SIMULATION


/*
//-----------------------------------------------------------------------------
/// \brief  check SPI communication for schedule table 1 as write verify of control registers 3...7 and read control registers 3...7
///
/// \descr  check communication by comparison of TX and RX data of CR3...7 registers
///
/// \param  tCddSpiL2Channel SpiL2Channel 
///
/// \return boolean boVerifyOk 
//-----------------------------------------------------------------------------
static boolean CddStp8899Com_CheckSpiComSt1(tCddSpiL2Channel SpiL2Channel)
{
  boolean boVerifyOk = FALSE;
  uint16 unSpiCheckDrvDefectCReg1, unSpiCheckDrvDefectCReg2, unSpiCheckDrvDefectCReg3, unSpiCheckDrvDefectCReg4;

  unSpiCheckDrvDefectCReg1  = CddStp8899Com_DataMirror.CtrlRx.aCReg1 [SpiL2Channel];          // control register 1  RX
  unSpiCheckDrvDefectCReg2  = CddStp8899Com_DataMirror.CtrlRx.aCReg2 [SpiL2Channel];          // control register 2  RX
  unSpiCheckDrvDefectCReg3  = CddStp8899Com_DataMirror.CtrlRx.aCReg3 [SpiL2Channel];          // control register 3  RX
  unSpiCheckDrvDefectCReg4  = CddStp8899Com_DataMirror.CtrlRx.aCReg4 [SpiL2Channel];          // control register 4  RX

  // schedule table 1 writes and reads control registers 3, 4, 5, 6, 7
  if (   ( unSpiCheckDrvDefectCReg1  == CddStp8899Com_DataMirror.CtrlTx.aCReg1 [SpiL2Channel])
      && ( unSpiCheckDrvDefectCReg2  == CddStp8899Com_DataMirror.CtrlTx.aCReg2 [SpiL2Channel])
      && ( unSpiCheckDrvDefectCReg3  == CddStp8899Com_DataMirror.CtrlTx.aCReg3 [SpiL2Channel])
      && ( unSpiCheckDrvDefectCReg4  == CddStp8899Com_DataMirror.CtrlTx.aCReg4 [SpiL2Channel]))
  {
    CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] = 0;
    boVerifyOk = TRUE;
  }
  else // not verified
  {
    uint16 unDIAG_VBAT;                                                                       // Vbat [mV]

    (void)IoHwAb_User_GetAdc_DIAG_VBAT(&unDIAG_VBAT);                                         // get DIAG_VBAT value
    if (   (unDIAG_VBAT >= CDDSTP8899_VBATSDrvDefect)                                        // voltage VBATS not too low and provokes no DRV88XX specific SPI communication error ErrDrvDefect?
        && (unSpiCheckDrvDefectCReg1  != CDDSTP8899_RegValVBATSDD)                           // register value not set by pull up resistances
        && (unSpiCheckDrvDefectCReg2  != CDDSTP8899_RegValVBATSDD)                           // register value not set by pull up resistances
        && (unSpiCheckDrvDefectCReg3  != CDDSTP8899_RegValVBATSDD)                           // register value not set by pull up resistances
        && (unSpiCheckDrvDefectCReg4  != CDDSTP8899_RegValVBATSDD))                          // register value not set by pull up resistances
    {
      CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel]++;
    }
    else                                                                                      // voltage VBATS too low        // Kl15 off               // LED6.1 specific: Kl15 off and Led switch on supports uC but not stepper drivers!
    {
      CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] = 0;                                     // restart counting SPI errors  // for next Kl15 not off  // LED6.1 specific: Kl15 off and Led switch on supports uC but not stepper drivers!
    }
    if (CddStp8899Com_aucCheckDrvDefectCnt[SpiL2Channel] >= CDDSTP8899_CHECKDRVDEFECT_MAX)
    {
      CddStp88XX_aStpState[SpiL2Channel].Bit.ErrDrvDefect = 1;                               // set DRV8899 driver defect error bit
    }
    else                                                                                      // try next verify CDDSTP8899_CHECKDRVDEFECT_MAX
    {
      CddStp8899Com_StReqSingle(SpiL2Channel, CDDSTP8899_SpiSt_WriteCr34A67_ReadCr34A67);   // send once more
    }
  }
  return boVerifyOk;
}
*/


//-----------------------------------------------------------------------------
/// \brief  Called after reception of a SPI frame
///
/// \descr  The function reads the content of SPI Rx data provided by SPI and store data in CddStp-DataMirror.
///         CB-Handling config by .\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddSpi\Cfg\CddSpi_Cfg.h
///         SPI-EFT-Handling: 'CddSpi_GetStpConfig'
///
/// \param  unIx index of stepper (up to SW-A340 = HW-B2: 3 stp)
/// \param  ulData  : SPI Rx data (only 16 LSB valid)
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_SpiRx(uint16 unIx, uint32 ulData)
{
  if (unIx < CFA_CNT_STP_88XX)
  {
    CddStp8899Com_SpiRx(unIx, (uint16)ulData);
  }
}


//-----------------------------------------------------------------------------
/// \brief  Called between reception of SPI telegram and
///         transmission of next SPI telegram
///
/// \descr  This function gets raw SPI RX data and stores the contents
///         in CddStp8899Com_DataMirror. Then the function determines the
///         next SPI telegram. Now the contents of the CddStp8899Com_DataMirror
///         are read to start data transmission.
///
/// \param  uint16      unIx:        index to DRV8899 chip
///         uint16      unData:      16 bit raw RX data
///
/// \return -
//-----------------------------------------------------------------------------
STATIC_AL void CddStp8899Com_SpiRx(uint16 unIx, uint16 unData) // currently called by obsolet fct 'CddStp8899_SpiRx'
{
  //
  // 1st of all:
  // Check EFT for num of 'installed' (not just 'coded') steppers
  // If there is only ONE stepper, NO 'Daisy-Chain'-Handling is used
  //
#if defined (UNIT_TEST)
  extern uint8 ucNumOfSteppers_EFT;
#else
  uint8 ucNumOfSteppers_EFT = 1;// CddStp88XX_GetNumOfSteppers_EFT();
#endif
  if (ucNumOfSteppers_EFT == 0u) // maybe param yet not loaded
  {
    return;
  }

  // at least ONE HW-Stepper-Chip is available
  else
  {
    uint8  ucSchedStateOld;
    uint8  ucLoByte_, ucHiByte_;

    // orig.: const  tCddStp8899Com_SpiSchedTable* pTabEntry;
    static volatile const tCddStp8899Com_SpiSchedTable* pTabEntry;

    // jk-tbd: // static volatile tCddStp8899Com_StatReg_Basic aRegBsc_lastError [CDDSTP_8899_CNT]; // 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL                                                     -  Basic-Status-Registers - comes each time one each SPI-Response: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1
    // jk-tbd: static volatile uint8 aRegBsc_lastError [4]; // 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL                                                     -  Basic-Status-Registers - comes each time one each SPI-Response: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1

    /////  __DI();            // call from interrupt level is not possible (no counter)!
    /////  osDisableGlobal(); // call from interrupt level is not possible (no counter)!
    //Lr06  SuspendAllInterrupts();
    // jk-tbd-HW-02   uint32 ulDisableIntKey;
    // jk-tbd-HW-02   ulDisableIntKey = __DIR();

    // calculate pointer to actual schedule table entry
    pTabEntry = &CddStp8899Com_SpiSchedTable[CddStp8899Com_aucSchedState[unIx]];

    // only ONE HW-Stepper-Chip
    if (ucNumOfSteppers_EFT == 1u) // no daisy-chain
    {
      // TX: A1 D1  ->  Adr & Data
      // RX: S1 R1  ->  Status & Report
      //     |  |
      //     |  |--> 8 Bytes
      //     |-----> 8 Bytes
      //
      // ECU-TX:
      //   the sdi input data word is 16 bits long and consists of the following format:
      //    * 1 read or write bit, w (bit 14)
      //    * 5 address bits, a (bits 13 through 9)
      //    * 8 data bits, d (bits 7 through 0)
      //   
      //   sdi input data word format
      //   b15 b14 b13 b12 b11 b10 b9 b8 b7 b6 b5 b4 b3 b2 b1 b0
      //     0  w0  a4  a3  a2  a1 a0 x  d7 d6 d5 d4 d3 d2 d1 d0       -> mosi: a1 d1
      //
      // ECU-RX
      //   the sdo output-data word is 16 bits long and the first 8 bits make up the status register (s1). 
      //   the report word (r1) is the content of the register being accessed.
      //   for a write command (w0 = 0), the response word on the sdo pin is the data currently in the register being written to.
      //   for a read  command (w0 = 1), the response word is the data currently in the register being read.
      //   
      //   sdo output data word format
      //   b15 b14 b13  b12  b11 b10  b9 b8 b7 b6 b5 b4 b3 b2 b1 b0
      //     1   1 uvlo cpuv ocp rsvd tf ol d7 d6 d5 d4 d3 d2 d1 d0    -> miso: s1 r1
      //     |   |  |    |    |   |   |  |
      //     1   1  0    0  . 0   0   0  0 = 0xC0

      // only ONE stepper -> 'unIx' is always '0'
      if (unIx == 0u)
      {
        uint8* pucStatusBasic = ST_STAT_RX_SRB; // Basic-Status-Registers: 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL -  comes EACH time in each SPI-Response
        pucStatusBasic[0] = (uint8)((0x3F00u & unData) >> 8u);  // e.g. 0xC123 -> take '0x01' - do NOT take the top two bits because they are always '1' in this response

        pTabEntry->pucRxDataByte[0] = (uint8)(0x00FFu & unData); // e.g. 0xC123 -> take '0x23' - requested register: either 'previous' Ctrl-Register or current State-Register

#ifdef CDDSTP_DEBUGGING_VARS
        aaa_CddStp__SpiRx_1 = unData;
        aaa_CddStp__SpiRx_2 = pucStatusBasic[0];
        aaa_CddStp__SpiRx_3 = pTabEntry->pucRxDataByte[0];
#endif // CDDSTP_DEBUGGING_VARS
      }

      else
      {
         // MISRA
      }
    } // end of 'if (ucNumOfSteppers_EFT == 1u)' // no daisy-chain

    // 3 HW-Stepper-Chips
    else if (ucNumOfSteppers_EFT == 3u) // 'old' HW B2 and older
    {
      // 3-Stepper-Handling via Daisy-Chain:
      //
      // TI - DRV8899:
      // Send-Data: Hdr1 Hdr2 RegAdr3 RegAdr2 RegAdr1 Dt3 Dt2 Dt1
      // Response-Data: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1
      // StatX?: Basic Status-Reg. - comes each time automatically
      // Hdr1: 1.0.n5...n0 - n=count of daisy-chain-members = '3'
      //
      // Req./Tx:
      //    -> word-0: Hdr1 Hdr2
      //    -> word-1:           RegAdr3 RegAdr2
      //    -> word-2:                           RegAdr1 Dt3
      //    -> word-3:                                       Dt2 Dt1
      // e.g.:         0x83 0x80   0x0C 0x0C   0x0C 0xE0   0xE0 0xE0
      // N.b.:
      // In SPI-Buffer 'mixed': Hdr2 Hdr1 | A2 A3 | D3 A1 | D1 D2
      //
      // Resp./Rx:
      // -> word-0: StatBsc3 StatBsc2
      // -> word-1:                   StatBsc1 Hdr1
      // -> word-2:                                 Hdr2 RegData3
      // -> word-3:                                               RegData2 RegData1
      //
      // jk-TI-Daisy-Chain-Handling *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
      // input: =3,2,1,0,   3,2,1,0,    3,2,1,0,    ....
      // needed: 0,1,2,3,   0,1,2,3, ...

      if (unIx == 3u)
      {
        // Response-Data: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1
        // unIx=0,1,2,3:  -----0-----,-----1----,----2----,----3----
        // relevant:      ^^^^^^^^^^^
        // ->  unIx-0 = Stat3 & Stat2 (= 2x Basic-Status-Register - comes EACH time 'automatically'!!)
        // jk-orig pucStatusBasic[2] = (uint8)((0x00003F00U & ulData) >> 8);  // store RX data Stp-3 - do NOT take the top two bytes because they are always '1' in this response
        // jk-orig pucStatusBasic[1] = (uint8) (0x0000003FU & ulData);        // store RX data Stp-2 - do NOT take the top two bytes because they are always '1' in this response
        /*static volatile*/ uint8* pucStatusBasic = ST_STAT_RX_SRB;
        pucStatusBasic[2] = (uint8)((0x3F00U & unData) >> 8u);  // store RX data Stp-3 - do NOT take the top two bytes because they are always '1' in this response
        pucStatusBasic[1] = (uint8)((0x003FU & unData));        // store RX data Stp-2 - do NOT take the top two bytes because they are always '1' in this response

        // Basic-Status-Registers - comes each time one each SPI-Response: StsBsc3 StsBsc2 StsBsc1 Hdr1 Hdr2 Reg3 Reg2 Reg1
        // 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL (any error: 0011.1011=0x3B)
        // PRQA S 1861, 2214, 4542 2 // program architecture and readability - intentionally no modification of existing code -  warning - QAC(Prio7) Msg: 1861(The operands of this bitwise operator are of different 'essential signedness' but will generate a result of type 'signed int'.) Depth: 0 Ref: MISRA C:2012 Rule-10.4 | warning - QAC(Prio7) Msg : 4542(A non - negative constant expression of 'essentially signed' type(signed char) is being used as the right - hand operand of this bitwise operator (&).) Depth : 0 Ref : MISRA C : 2012 Rule - 10.1 |  warning - QAC(Prio7) Msg : 2214(Body of control statement is on the same line and is not enclosed within braces.) Depth : 0 Ref : MISRA C : 2012 Rule - 15.6
        // jk-tbd: if ((pucStatusBasic[2] & 0x3Bu) > 0u) aRegBsc_lastError[2]/*.ucRaw*/ = pucStatusBasic[2];
        // jk-tbd: if ((pucStatusBasic[1] & 0x3Bu) > 0u) aRegBsc_lastError[1]/*.ucRaw*/ = pucStatusBasic[1];
      }

      else if (unIx == 2u)
      {
        // Response-Data: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1
        // unIx=0,1,2,3:  -----0-----,-----1----,----2----,----3----
        // relevant:                  ^^^^^^^^^^
        // ->  unIx-1 = Stat1 & Hdr1
        // jk-orig pucStatusBasic[0] = (uint8)((0x00003F00U & ulData) >> 8);  // store RX data Stp-1 - do NOT take the top two bytes because they are always '1' in this response
        uint8* pucStatusBasic = ST_STAT_RX_SRB;
        pucStatusBasic[0] = (uint8)((0x3F00U & unData) >> 8u);  // store RX data Stp-1 - do NOT take the top two bytes because they are always '1' in this response

        // Basic-Status-Registers - comes each time one each SPI-Response: StsBsc3 StsBsc2 StsBsc1 Hdr1 Hdr2 Reg3 Reg2 Reg1
        // 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL
        // PRQA S 1861, 2214, 4542 1 // program architecture and readability - intentionally no modification of existing code -  warning - QAC(Prio7) Msg: 1861(The operands of this bitwise operator are of different 'essential signedness' but will generate a result of type 'signed int'.) Depth: 0 Ref: MISRA C:2012 Rule-10.4 | warning - QAC(Prio7) Msg : 4542(A non - negative constant expression of 'essentially signed' type(signed char) is being used as the right - hand operand of this bitwise operator (&).) Depth : 0 Ref : MISRA C : 2012 Rule - 10.1 |  warning - QAC(Prio7) Msg : 2214(Body of control statement is on the same line and is not enclosed within braces.) Depth : 0 Ref : MISRA C : 2012 Rule - 15.6
        // jk-tbd: if ((pucStatusBasic[0] & 0x3Bu) > 0u) aRegBsc_lastError[0]/*.ucRaw*/ = pucStatusBasic[0];
      }

      else if (unIx == 1u)
      {
        // Response-Data: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1
        // unIx=0,1,2,3:  -----0-----,-----1----,----2----,----3----
        // relevant:                             ^^^^^^^^^
        // ->  unIx-2 = Hdr2 & Reg3
        // jk-orig pTabEntry->pucRx[2] = (uint8)(ulData); // store RX data Stp-3
        pTabEntry->pucRxDataByte[2] = (uint8)(unData); // store RX Stp-3 in data 1  -  e.g. 'ST_CTRL_RX_CR3'
      }

      else if (unIx == 0u)
      {
        // Response-Data: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1
        // unIx=0,1,2,3:  -----0-----,-----1----,----2----,----3----
        // relevant:                                       ^^^^^^^^^
        // ->  unIx-3 = Reg2 Reg1
        // jk-orig pTabEntry->pucRx[1] = (uint8)(ulData >> 8); // store RX data Stp-2
        // jk-orig pTabEntry->pucRx[0] = (uint8)(ulData);      // store RX data Stp-1
        pTabEntry->pucRxDataByte[1] = (uint8)(unData >> 8u); // store RX Stp-2 in data 1  -  e.g. 'ST_CTRL_RX_CR3'
        pTabEntry->pucRxDataByte[0] = (uint8)(unData);      // store RX Stp-1 in data 1  -  e.g. 'ST_CTRL_RX_CR3'
      }

      else
      {
        // MISRA
      }
    } // end of 'else if (ucNumOfSteppers_EFT == 3u)' // 'old' HW B2 and older

    else // ucNumOfSteppers_EFT
    {
      // num of HW-Stepper-Chips is not supported
    }

    // jk-TI-Daisy-Chain-Handling *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#

    #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
    #else // Unit-Tests!
    if (unIx > 3) // some kind of error - should never happen in real code
    {
      unIx = 0;
    }
    #endif

    // note: at first call unData contains dummy data
    // jk-orig pTabEntry->pucRxDataByte1[unIx] = UTIL_HIBYTE(unData);  // store RX data 1
    // jk-orig pTabEntry->pucRxDataByte2[unIx] = UTIL_LOBYTE(unData);  // store RX data 2    -    pucRxDummy - use instead of this:  'uint8* pucStatusBasic = ST_STAT_RX_SRB'

    // jk: new position (moved some lines UP)
    ucLoByte_ = pTabEntry->pucCtrlTx[unIx]; // get data for transmission
    ucHiByte_ = pTabEntry->ucAddr;

    // Ctrl-Reg-1  -  TRQ_DAC [3:0]  |  RSVD  |  SLEW_RATE [1:0]
    // Ctrl-Reg-2  -  DIS_OUT  |  RSVD  |  TOFF [1:0]  |  DECAY [2:0]
    // Ctrl-Reg-3  -  DIR  |  STEP  |  SPI_DIR  |  SPI_STEP  |  MICROSTEP_MODE [3:0]
    // Ctrl-Reg-4  -  CLR_FLT  |  LOCK [2:0]  |  EN_OL  |  OCP_MODE  |  OTSD_MODE  |  TW_REP  - e.g. EN_OL: 0x31=0011.0001 | 0x39=0011.1001
    // Ctrl-Reg-5  -  RSVD [1:0]  |  STL_LRN  |  EN_STL  |  STL_REP  |  OL_TIME [1:0]  |  EN_SR_BLANK
    // Ctrl-Reg-6  -  STALL_TH [7:0]
    // Ctrl-Reg-7  -  TRQ_COUNT [7:0]
    // Ctrl-Reg-8  -  RSVD  |  REV_ID [3:0]

    // write-request to Ctrl-Reg-1'?
    if (ucHiByte_ == DRV8899_wCR1_) // TRQ_DAC [3:0]  |  RSVD  |  SLEW_RATE [1:0]
    {
      STATIC_UT_NOINIT(uint8, ucDlyCntr);
      // check if anything has changed -> do ONLY write on CHANGE
      if (CddStp8899Com_DataMirror.CtrlTx.aCReg1[0].ucRaw != CddStp8899Com_DataMirror.CtrlRx.aCReg1[0].ucRaw)
      {
        // is this the 1st round after change? - do not write this time
        if (ucDlyCntr < 1u)
        {
          ucDlyCntr++;
          ucHiByte_ = DRV8899_rCR1_;
        }
        // else: counter is at least '1' -> do write once again
      }
      else // Tx and Rx are the same - no need to write the same content once again
      {
        ucDlyCntr = 0;
        ucHiByte_ = DRV8899_rCR1_;
      }
    }

    // write-request to Ctrl-Reg-2'?
    if (ucHiByte_ == DRV8899_wCR2_) // DIS_OUT  |  RSVD  |  TOFF [1:0]  |  DECAY [2:0]
    {
      // check if anything has changed -> do ONLY write on CHANGE
      if (CddStp8899Com_DataMirror.CtrlTx.aCReg2[0].ucRaw == CddStp8899Com_DataMirror.CtrlRx.aCReg2[0].ucRaw)
      {
        ucHiByte_ = DRV8899_rCR2_;
      }
    }

    // write-request to Ctrl-Reg-3'?
    if (ucHiByte_ == DRV8899_wCR3_) // DIR  |  STEP  |  SPI_DIR  |  SPI_STEP  |  MICROSTEP_MODE [3:0]
    {
      // check if anything has changed -> do ONLY write on CHANGE
      if (CddStp8899Com_DataMirror.CtrlTx.aCReg3[0].ucRaw == CddStp8899Com_DataMirror.CtrlRx.aCReg3[0].ucRaw)
      {
        ucHiByte_ = DRV8899_rCR3_;
      }
    }

    // write-request to Ctrl-Reg-4 with containing bit 'CLR_FLT'?
    if (ucHiByte_ == DRV8899_wCR4_) // CLR_FLT  |  LOCK [2:0]  |  EN_OL  |  OCP_MODE  |  OTSD_MODE  |  TW_REP  - e.g. EN_OL: 0x31=0011.0001 | 0x39=0011.1001
    {
      // usually 'CLR_FLT' in CReg4 is '0' - only on request do WRITE ONCE a '1'
#if defined (UNIT_TEST)
      extern boolean bResult;
#else
      boolean bResult = FALSE;// CddStp_Simulation_PreEvalStallDtctn_GetWriteClrFltOnce(); // flag will we resetted internally at once
#endif
      if (bResult == TRUE)
      {
        ucLoByte_ |= (uint8)(1u << CDDSTP88xx_BitPos_CLR_FLT); // CLR_FLT
      }

      // check if anything has changed -> do ONLY write on CHANGE
      else
      {
        if (CddStp8899Com_DataMirror.CtrlTx.aCReg4[0].ucRaw == CddStp8899Com_DataMirror.CtrlRx.aCReg4[0].ucRaw)
        {
          ucHiByte_ = DRV8899_rCR4_;
        }
      }
    }
#if (CDDSTP8899_ENABLE_DEBUG == STD_ON)
    // CddStp8899Com_Debug__OlErrorProblem
    CddStp8899Com_DEBUG_Check_EnOl_DisOut();
#endif

    // Important:
    //
    // 7.4.2 Disable Mode (nSLEEP = 1, DRVOFF = 1)
    //    The DRVOFF pin is           used to enable or disable the half bridges in the device. When the DRVOFF pin is high, the output drivers are disabled in the Hi-Z state.
    //    The DIS_OUT bit can also be used to           disable the output drivers.             When the DIS_OUT bit is '1', the output drivers are disabled in the Hi-Z state. DIS_OUT is OR'ed with DRVOFF pin.
    //
    //    'DRVOFF pin'  ==  'Rte_Call_ppIoHwAbUserSetLwrDrvOff0_IoHwAbUser_SetLwrDrvOff(xy)'  ==  'IoHwAbUser_SetLwrDrvOff(xy)'  ==  'IoHwAb_SetDo_0_2(xy)'  ==  'IoHwAb_SetDo(DioConf_DioChannel_DioChannel_0_2_ST_DRVOFF , xy)'
    //    'nSleep pin'  ==  'Rte_Call_ppIoHwAbUserSetLwrSleep0_IoHwAbUser_SetLwrSleep(xy)'    ==  'IoHwAbUser_SetLwrSleep(xy)'   ==  'IoHwAb_SetDo_0_1(xy)'  ==  'IoHwAb_SetDo(DioConf_DioChannel_DioChannel_0_1_ST_SLEEP  , xy)'
    //
    // Only in fct 'CddStp88XX_CtrlFct0'
    //    CddStp_eCtrlFct0_ModeOn:  'RTE_..._SetLwrDrvOff(FALSE)  &  'RTE_..._SetLwrSleep(TRUE)'   &  CddStp88xx__LwrSleepAndDisable = FALSE
    //    CddStp_eCtrlFct0_ModeOff: 'RTE_..._SetLwrDrvOff(TRUE)   &  'RTE_..._SetLwrSleep(FALSE)'  &  CddStp88xx__LwrSleepAndDisable = TRUE
    //
    // CTRL2 - DIS_OUT
    //    Write '1' to Hi-Z all outputs. Write '0' to enable all outputs.
    //    OR'ed with DRVOFF pin.
    //    To prevent false OL detection, ensure OL fault detection is disabled
    //       by writing '0' to EN_OL bit, before making the outputs Hi-Z by writing '1' to DIS_OUT.
    //
    // The default value of the DIS_OUT bit in CTRL2 register is different in DRV8889A-Q1: '1'
    //
    // Used var for handling of bit 'EN_OL':
    //    'CddStp8899Com_DataMirror.CtrlTx.aCReg4[0].Bit.u1EN_OL'  ==  'CddStp88XX_aBitsMod[CFG_Stp_IdxVer].Bit.biDisOLDetect'
    //
    //
    // I.e.:
    // BEFORE set bit 'EN_OL' to '1' (Ctrl-4)
    //   the TI-HW should be 'ENABLED' via 'nSleep'-Pin & 'DrvOff'-Pin & 'DIS_OUT'-Bit
    //
    // write-request to Ctrl-Reg-4 with containing bit 'EN_OL' & 'CLR_FLT'?
    if (   (ucHiByte_ == DRV8899_wCR4_)  // CLR_FLT  |  LOCK [2:0]  |  EN_OL  |  OCP_MODE  |  OTSD_MODE  |  TW_REP  - e.g. EN_OL: 0x31=0011.0001 | 0x39=0011.1001
        || (ucHiByte_ == DRV8899_rCR4_)) // new in FLM3: Do NOR write all the time
    {
      // HW is switched off  ->  do NOT enable OL-Detection
      if (CddStp88xx__LwrSleepAndDisable == TRUE)
      {
        ucLoByte_ &= (uint8)~CDDSTP88xx_Mask_EN_OL; // CDDSTP88xx_Mask_EN_OL = 0x08u = 0000.1000  ->  1111.0111
        ucHiByte_ = DRV8899_wCR4_;
      }

      // usually 'CLR_FLT' in CReg4 is '0' - only on request do WRITE ONCE a '1' e.g. reset 'Stall' or reset 'Fault-Bit' (Error-Debouncing)
      if (CddStp8899Com_DoClearFaultBit[unIx] == TRUE)
      {
        UNTANGLE_INCR(CddStp8899Com_ulDEBUG_DebouncingCtr_ClrFlt_Sent);  // this var will never be reset

        CddStp8899Com_DoClearFaultBit[unIx] = FALSE; // reset at once
        ucLoByte_ |= (uint8)(1u << CDDSTP88xx_BitPos_CLR_FLT); // reset latched fault (e.g. SPI or OL, ...
        ucHiByte_ = DRV8899_wCR4_;
      }
    }

    if (ucHiByte_ == DRV8899_wCR1_) // next SPI-TX: Ctrl-Reg-1 with 'TRQ_DAC'
    {
      // remember values in order to compare them later with 'RX'
      if (CddStp8899Com_aucTrqDac_LastTx[unIx] != CddStp8899Com_DataMirror.CtrlTx.aCReg1[unIx].Bit.u4TRQ_DAC) // changed?
      {
        CddStp8899Com_aucTrqDac_PrevTx[unIx] = CddStp8899Com_aucTrqDac_LastTx[unIx];
      }
      CddStp8899Com_aucTrqDac_LastTx[unIx] = CddStp8899Com_DataMirror.CtrlTx.aCReg1[unIx].Bit.u4TRQ_DAC;
    }


    // check RX-Data for errors via e.g. fct 'CddStp8899Com_CheckSpiComSt0'
    // N.b.
    //  previously: Check only once after a WHOLE Schedule-Table (ST) was done (8...50 entries & more)
    //  new:        Check EACH received data via SPI-TX
    (void)CddStp8899Com_aucStCheckSpiComFct[0]((uint8)unIx); // '0': currently the one and only 1st entry in list  -  return (boVerifyOk && !boSpiProblem)


    // store schedule state for RX notification usage
    ucSchedStateOld = CddStp8899Com_aucSchedState[unIx];

    // check whether a new write CReg0/1&2 for the actual schedule table had been requested
    // PRQA S 1861, 4542 2 // program architecture and readability - intentionally no modification of existing code -  warning - QAC(Prio7) Msg: 1861(The operands of this bitwise operator are of different 'essential signedness' but will generate a result of type 'signed int'.) Depth: 0 Ref: MISRA C:2012 Rule-10.4 | warning - QAC(Prio7) Msg : 4542(A non - negative constant expression of 'essentially signed' type(signed char) is being used as the right - hand operand of this bitwise operator (&).) Depth : 0 Ref : MISRA C : 2012 Rule - 10.1 |  warning - QAC(Prio7) Msg : 2214(Body of control statement is on the same line and is not enclosed within braces.) Depth : 0 Ref : MISRA C : 2012 Rule - 15.6
    if      (    ( CddStp8899Com_aucActSchedTable[unIx] == (uint8)CddStp8899Com_eSt0 )                    // CddStp8899Com_eSt0='0'
             &&  ((CddStp8899Com_aucStReqOnceMore[unIx] &  CDDSTP8899_SpiSt_Bit0) != 0u))        // CDDSTP8899_SpiSt_Bit0='1'
    {
      CddStp8899Com_aucStReqOnceMore [unIx] = 0;                                                 // delete all bits
  //  CddStp8899Com_aucActSchedTable[unIx] = CddStp8899Com_eSt0;                                   // abort actual work and restart St0
      CddStp8899Com_aucSchedState[unIx] = CddStp8899Com_aucStStart[CddStp8899Com_aucActSchedTable[unIx]];
    }
  // jk-tbd   else if (    ( CddStp8899Com_aucActSchedTable[unIx] == CddStp8899Com_eSt1 )                    // St1 for write CReg3&4&5&6&7?
  // jk-tbd            &&  ((CddStp8899Com_aucStReqOnceMore[unIx] &  CDDSTP8899_SpiSt_Bit1) != 0))
  // jk-tbd   {
  // jk-tbd     CddStp8899Com_aucStReqOnceMore [unIx] = 0;                                                 // delete other bits
  // jk-tbd //  CddStp8899Com_aucActSchedTable[unIx] = CddStp8899Com_eSt1;                                   // abort actual work and restart St1
  // jk-tbd     CddStp8899Com_aucSchedState[unIx] = CddStp8899Com_aucStStart[CddStp8899Com_aucActSchedTable[unIx]];
  // jk-tbd   }
    else // standard
    {
      CddStp8899Com_aucStReqOnceMore [unIx] = 0;                                                 // delete other bits because of the schedule tables has not been active

      // switch to next schedule table entry
      CddStp8899Com_aucSchedState[unIx] = pTabEntry->ucNextEntry;

      if (CddStp8899Com_aucSchedState[unIx] == 0u)                                                // actual table finished
      {
        boolean boSpiCheckResult = FALSE;
        const uint16 unSpiCheckIdx = CddStp8899Com_aucActSchedTable[unIx];

        // mark actual table finished
        // tbd-jk
        // check 'tmp_workaround'
        UtilClearVarBitAtomicU8_(unSpiCheckIdx, &CddStp8899Com_aucStReqSingle[unIx]); /// tbd-jk
        // tbd-jk

        // check via e.g. fct 'CddStp8899Com_CheckSpiComSt0'
        // N.b.
        //  previously: Check only once after a WHOLE Schedule-Table (ST) was done (8...50 entries & more)
        //  new:        Check EACH received data via SPI-TX
        // jk: outdated boSpiCheckResult = CddStp8899Com_aucStCheckSpiComFct[unSpiCheckIdx]((uint8)unIx); // return (boVerifyOk && !boSpiProblem)
        boSpiCheckResult = TRUE; // i.e.: (boVerifyOk && !boSpiProblem)

        #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
        #else // Unit-Tests!
          boSpiCheckResult = CddStp_UnitTestHelper_bo1;
        #endif

        // check via e.g. fct 'CddStp8899Com_CheckSpiComSt0'
        // PRQA S 3344, 4559 2 // program architecture and readability - intentionally no modification of existing code -  warning - QAC(Prio7) Msg: 3344(Controlling expression is not an 'essentially Boolean' expression.) Depth: 0 Ref: MISRA C:2012 Rule-14.4 | warning - QAC(Prio7) Msg: 4559(An expression of 'essentially unsigned' type (unsigned char) is being used as the first operand of this conditional operator (?).) Depth: 0 Ref: MISRA C:2012 Rule-10.1
        if (boSpiCheckResult ? TRUE : FALSE)  // verify Rx schedule 0/1 write data by comparing with Tx data and Rx schedule 2/3 read data parity check
        {
          // store bit mask for RX notification usage - only in case of verify OK
          CddStp8899Com_aulRxNotification[unIx] |= (((uint32) 1) << ucSchedStateOld);
        }
        else
        {
          // MISRA
        }

        #ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
        #else // Unit-Tests!
        if (CddStp_UnitTestHelper_bo1 == TRUE) // no easy way to get this state
        {
          CddStp8899Com_aucStReqSingle[unIx] = CDDSTP8899_SpiSt_Bit0;
        }
        #endif

        // check for next schedule table request
        // PRQA S 1861, 4542 1 // program architecture and readability - intentionally no modification of existing code -  warning - QAC(Prio7) Msg: 1861(The operands of this bitwise operator are of different 'essential signedness' but will generate a result of type 'signed int'.) Depth: 0 Ref: MISRA C:2012 Rule-10.4 | warning - QAC(Prio7) Msg : 4542(A non - negative constant expression of 'essentially signed' type(signed char) is being used as the right - hand operand of this bitwise operator (&).) Depth : 0 Ref : MISRA C : 2012 Rule - 10.1 |  warning - QAC(Prio7) Msg : 2214(Body of control statement is on the same line and is not enclosed within braces.) Depth : 0 Ref : MISRA C : 2012 Rule - 15.6
        if      ((CddStp8899Com_aucStReqSingle[unIx] & CDDSTP8899_SpiSt_Bit0) != 0u)             // - CddSpi special: CReg1, CReg2 sending in schedule table 0 is cyclic, but this special handling speeds up the sending started by code (tasks, ISRs) -> highest priority (current amplitude)
        {
          CddStp8899Com_aucActSchedTable[unIx] = (uint8)CddStp8899Com_eSt0;
        }
  // jk-tbd-Cyclic       else if ((CddStp8899Com_aucStReqSingle[unIx] & CDDSTP8899_SpiSt_Bit1) != 0)
  // jk-tbd-Cyclic       {
  // jk-tbd-Cyclic         CddStp8899Com_aucActSchedTable[unIx] = CddStp8899Com_eSt1;
  // jk-tbd-Cyclic       }
  // jk-tbd-Cyclic       else if ((CddStp8899Com_aucStReqSingle[unIx] & CDDSTP8899_SpiSt_Bit2) != 0)
  // jk-tbd-Cyclic       {
  // jk-tbd-Cyclic         CddStp8899Com_aucActSchedTable[unIx] = CddStp8899Com_eSt2;
  // jk-tbd-Cyclic       }
  // jk-tbd-Cyclic       else if ((CddStp8899Com_aucStReqSingle[unIx] & CDDSTP8899_SpiSt_Bit3) != 0)
  // jk-tbd-Cyclic       {
  // jk-tbd-Cyclic         CddStp8899Com_aucActSchedTable[unIx] = CddStp8899Com_eSt3;
  // jk-tbd-Cyclic       }
        else
        {
          CddStp8899Com_aucActSchedTable[unIx] = (uint8)CddStp8899Com_eSt0;                               // default table
        }
      
        CddStp8899Com_aucSchedState[unIx] = CddStp8899Com_aucStStart[CddStp8899Com_aucActSchedTable[unIx]];
      }

      // calculate new pointer because index to schedule table has changed
      pTabEntry = &CddStp8899Com_SpiSchedTable[CddStp8899Com_aucSchedState[unIx]];
    }

    // old position (moved some line up) ucLoByte_ = pTabEntry->pucCtrlTx[unIx]; // get data for transmission
    // old position (moved some line up) ucHiByte_ = pTabEntry->ucAddr;

  /////  __EI();           // call from interrupt level is not possible (no counter)!
  /////  osEnableGlobal(); // call from interrupt level is not possible (no counter)!
  //Lr06  ResumeAllInterrupts();
  // jk-tbd-HW-02   __RIR(ulDisableIntKey);

    // PRQA S 4397 1 // program architecture and readability - intentionally no modification of existing code -  warning - QAC(Prio7) Msg: 4397(An expression which is the result of a ~ or << operation has not been cast to its essential type.) Depth: 0 Ref: MISRA C:2012 Rule-10.7
    CddStp8899Com_aunTxData[unIx] =  UTIL_MAKEWORD(ucLoByte_, ucHiByte_); // low=data, high=addr
  } // end of 'else' // at least ONE HW-Stepper-Chip is available

  // PRQA S 5310, 5330, 5316, 5336 1 // // program architecture and readability - intentionally no modification of existing code - HIS metrics violation
}


//-----------------------------------------------------------------------------
/// \brief  Called before transmission of SPI telegram
///
/// \descr  The function reads the content of CddStp-DataMirror
///         CB-Handling config by .\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddSpi\Cfg\CddSpi_Cfg.h
///         SPI-EFT-Handling: 'CddSpi_GetStpConfig'
///
/// \param  unIx index of stepper (up to SW-A340 = HW-B2: 3 stp)
///
/// \return uint32  : Tx data (16 LSB are valid)
//-----------------------------------------------------------------------------
uint32 CddStp_SpiTx(uint16 unIx)
{
  uint32 ulResult = 0;
  if (unIx < CFA_CNT_STP_88XX)
  {
    ulResult = CddStp8899Com_SpiTx(unIx);
  }
  return ulResult;
}


//-----------------------------------------------------------------------------
/// \brief  Called between reception of SPI telegram and
///         transmission of next SPI telegram
///
/// \descr  This function sets raw SPI TX data.
///
/// \param  uint16 unIx: index to DRV8899 chip
///
/// \return uint16 16 bit raw TX data
//-----------------------------------------------------------------------------
STATIC_AL uint16 CddStp8899Com_SpiTx(uint16 unIx)
{
  uint16 unRetValue = 0u;

  //
  // 1st of all:
  // Check EFT for num of 'installed' (not just 'coded') steppers
  // If there is only ONE stepper, NO 'Daisy-Chain'-Handling is used
  //
#if defined (UNIT_TEST)
  extern uint8 ucNumOfSteppers_EFT;
#else
  uint8 ucNumOfSteppers_EFT = 1;// CddStp88XX_GetNumOfSteppers_EFT();
#endif
  if (ucNumOfSteppers_EFT == 0u) // maybe param yet not loaded
  {
    unRetValue = 0u;
  }

  // at least ONE HW-Stepper-Chip is available
  else
  {
    // HCM: return CddStp8899Com_aunTxData[unIx]; // low=data, high=addr
    //
    // now:
    // pTabEntry = &CddStp8899Com_SpiSchedTable[CddStp8899Com_aucSchedState[unIx]];
    // CddStp8899Com_aunTxData[unIx] = MAKEWORD(pTabEntry->pucCtrlTx[unIx], pTabEntry->ucAddr); // low=data, high=addr


    static volatile uint16 unData = 0xEFEF;
    unData = 0;

    // only ONE HW-Stepper-Chip
    if (ucNumOfSteppers_EFT == 1u) // no daisy-chain
    {
      // the sdi input data word is 16 bits long and consists of the following format:
      //  * 1 read or write bit, w (bit 14)
      //  * 5 address bits, a (bits 13 through 9)
      //  * 8 data bits, d (bits 7 through 0)
      // the sdo output-data word is 16 bits long and the first 8 bits make up the status register (s1). 
      // the report word (r1) is the content of the register being accessed.
      // for a write command (w0 = 0), the response word on the sdo pin is the data currently in the register being written to.
      // for a read  command (w0 = 1), the response word is the data currently in the register being read.
      //
      // sdi input data word format
      // b15 b14 b13 b12 b11 b10 b9 b8 b7 b6 b5 b4 b3 b2 b1 b0
      //   0  w0  a4  a3  a2  a1 a0 x  d7 d6 d5 d4 d3 d2 d1 d0       -> mosi: a1 d1
      //
      // sdo output data word format
      // b15 b14 b13  b12  b11 b10  b9 b8 b7 b6 b5 b4 b3 b2 b1 b0
      //   1   1 uvlo cpuv ocp rsvd tf ol d7 d6 d5 d4 d3 d2 d1 d0    -> miso: s1 r1

      // *#*#*#*#*#*#*#*#*# TBD *#*#*#*#*#*#*#*#*#
        static volatile uint8 ucRegAdr;
        static volatile uint8 ucData;
        ucRegAdr = UTIL_HIBYTE(CddStp8899Com_aunTxData[0]); // low=data, high=addr
        ucData   = UTIL_LOBYTE(CddStp8899Com_aunTxData[0]); // low=data, high=addr  |  idx=0,1,2  ->  Reg1,Reg2,Reg3  ->  idx-2 = data3

#if 0
        // Debug-Counter
        if (ucRegAdr == DRV8899_wCR1_)
        {
          CddStp8899Com_DEBUG_StlLrn_Cntr[1].ulWrite++;
        }
        if (ucRegAdr == DRV8899_rCR1_)
        {
          CddStp8899Com_DEBUG_StlLrn_Cntr[1].ulRead++;
        }
        if (ucRegAdr == DRV8899_wCR2_)
        {
          CddStp8899Com_DEBUG_StlLrn_Cntr[2].ulWrite++;
        }
        if (ucRegAdr == DRV8899_rCR2_)
        {
          CddStp8899Com_DEBUG_StlLrn_Cntr[2].ulRead++;
        }
        if (ucRegAdr == DRV8899_wCR3_)
        {
          CddStp8899Com_DEBUG_StlLrn_Cntr[3].ulWrite++;
        }
        if (ucRegAdr == DRV8899_rCR3_)
        {
          CddStp8899Com_DEBUG_StlLrn_Cntr[3].ulRead++;
        }
        if (ucRegAdr == DRV8899_wCR4_)
        {
          CddStp8899Com_DEBUG_StlLrn_Cntr[4].ulWrite++;
        }
        if (ucRegAdr == DRV8899_rCR4_)
        {
          CddStp8899Com_DEBUG_StlLrn_Cntr[4].ulRead++;
        }
#endif

        unData = ((uint16)((uint16)ucRegAdr << 8u) | (uint16)ucData); // RegAdrStp DataStp
      // *#*#*#*#*#*#*#*#*# TBD *#*#*#*#*#*#*#*#*#
    }

    // 3 HW-Stepper-Chips
    else if (ucNumOfSteppers_EFT == 3u) // 'old' HW B2 and older
    {
      // 3-Stepper-Handling via Daisy-Chain:


      // Send-Data: Hdr1 Hdr2 RegAdr3 RegAdr2 RegAdr1 Dt3 Dt2 Dt1
      // Hdr1: 1.0.n5...n0       - n=count of daisy-chain-members = '3' -> 0x83
      // Hdr2: 1.0.Clr.x.x.x.x.x - Clr='global fault clear'=0     -> 0x80
      //
      // Response-Data: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1
      //
      // Tx:
      //    -> unIx=0: Hdr1 Hdr2
      //    -> unIx=1:           RegAdr3 RegAdr2
      //    -> unIx=2:                           RegAdr1 Dt3
      //    -> unIx=3:                                       Dt2 Dt1
      //
      // e.g.:         0x83 0x80   0x0C 0x0C   0x0C 0xE0   0xE0 0xE0
      //
      // N.b.:
      // In SPI-Buffer: Hdr2 Hdr1 | A2 A3 | D3 A1 | D1 D2
      //

      // jk-tbd // do not send/receive until basic settings are done
      // jk-tbd if (CddStp__DiagReq__bo_EnableSPI == FALSE)
      // jk-tbd {
      // jk-tbd   return 0u;
      // jk-tbd }

      // input: =3,2,1,0,   3,2,1,0,    3,2,1,0,    ....
      // needed: 0,1,2,3,   0,1,2,3, ...

      if (unIx == 3u)
      {
        // data: Hdr1 Hdr2 RegAdr3 RegAdr2 RegAdr1 Dt3 Dt2 Dt1
        // Hdr1: 1.0.n5...n0       - n=count of daisy-chain-members = '3'
        // Hdr2: 1.0.Clr.x.x.x.x.x - Clr='global fault clear'=0     -> 0x80
        static volatile uint8 ucHdr1 = 0x83; // Header-H1: 1000.0011 = 0x83
        static volatile uint8 ucHdr2 = 0x80; // Header-H2: 1000.0000 = 0x80

        unData = ((uint16)((uint16)ucHdr1 << 8u) | (uint16)ucHdr2); // Hdr1 Hdr2
      }

      else if (unIx == 2u)
      {
        // data: Hdr1 Hdr2 RegAdr3 RegAdr2 RegAdr1 Dt3 Dt2 Dt1
        // jk-orig uint8 ucRegAdr2 = pTabEntry->ucRegAddrMODIFIED;
        // jk-orig uint8 ucRegAdr3 = pTabEntry->ucRegAddrMODIFIED;
        static volatile uint8 ucRegAdr2;
        static volatile uint8 ucRegAdr3;
        /*uint8*/ ucRegAdr2 = UTIL_HIBYTE(CddStp8899Com_aunTxData[unIx]); // low=data, high=addr
        /*uint8*/ ucRegAdr3 = UTIL_HIBYTE(CddStp8899Com_aunTxData[unIx]); // low=data, high=addr

        unData = ((uint16)((uint16)ucRegAdr3 << 8u) | (uint16)ucRegAdr2); // RegAdrStp3 RegAdrStp2
      }

      else if (unIx == 1u)
      {
        // data: Hdr1 Hdr2 RegAdr3 RegAdr2 RegAdr1 Dt3 Dt2 Dt1
        // jk-orig uint8 ucRegAdr1 = pTabEntry->ucRegAddrMODIFIED;
        // jk-orig uint8 ucData3   = pTabEntry->pucTx[2]; // idx=0,1,2  ->  Reg1,Reg2,Reg3  ->  idx-2 = data3
        static volatile uint8 ucRegAdr1;
        static volatile uint8 ucData3  ;
        /*uint8*/ ucRegAdr1 = UTIL_HIBYTE(CddStp8899Com_aunTxData[unIx]); // low=data, high=addr
        /*uint8*/ ucData3   = UTIL_LOBYTE(CddStp8899Com_aunTxData[2]);    // low=data, high=addr  |  idx=0,1,2  ->  Reg1,Reg2,Reg3  ->  idx-2 = data3

        unData = ((uint16)((uint16)ucRegAdr1 << 8u) | (uint16)ucData3); // RegAdrStp1 DataStp3
      }

      else if (unIx == 0u)
      {
        // data: Hdr1 Hdr2 RegAdr3 RegAdr2 RegAdr1 Dt3 Dt2 Dt1
        // jk-orig uint8 ucData1 = pTabEntry->pucTx[0]; // idx=0,1,2  ->  Data1,Data2,Data3  ->  idx-0 = data1
        // jk-orig uint8 ucData2 = pTabEntry->pucTx[1]; // idx=0,1,2  ->  Data1,Data2,Data3  ->  idx-1 = data2
        static volatile uint8 ucData1;
        static volatile uint8 ucData2;
        /*uint8*/ ucData1 = UTIL_LOBYTE(CddStp8899Com_aunTxData[0]); // low=data, high=addr  |  idx=0,1,2  ->  Data1,Data2,Data3  ->  idx-0 = data1
        /*uint8*/ ucData2 = UTIL_LOBYTE(CddStp8899Com_aunTxData[1]); // low=data, high=addr  |  idx=0,1,2  ->  Data1,Data2,Data3  ->  idx-1 = data2

        unData = ((uint16)((uint16)ucData2 << 8u) | (uint16)ucData1); // DataStp2 DataStp1
      }

      else
      {
        // MISRA
      }
    } // end of 'if (ucNumOfSteppers_EFT == 1u)    else if (ucNumOfSteppers_EFT == 3u) ...'

    else // ucNumOfSteppers_EFT
    {
      // num of HW-Stepper-Chips is not supported
    }

    // jk-orig if(unIx == (CFA_CNT_STP_88XX - 1u))  // is last instance? (e.g. unIx=2 -> 2 == 4-1=3)
    // jk-orig {
    // jk-orig   // switch to next schedule table entry for next transmission
    // jk-orig   CddStp88X9_ucSchedIx_Tx = pTabEntry->ucNextEntry;
    // jk-orig }

    // get SPI register address and contents of control register for next SPI frame
    // update parity bit according to control register data
    unRetValue = unData; //  CddStp88X9_ConcatTxData(pTabEntry->unAddr, pTabEntry->punTx[unIx]);
  } // end of 'if (ucNumOfSteppers_EFT == 0u) ... else ...'

  return unRetValue;

  // PRQA S 5336, 5310, 5316 1 // // program architecture and readability - intentionally no modification of existing code - HIS metrics violation
}

typedef struct
{
  boolean bState_EnOl;
  boolean bState_DisOut;
  // tbd: CddStp88XX_aBitsMod[CFG_Stp_IdxVer].Bit.biDisOLDetect
  // tbd: CddStp88XX_HalStp_BitsLwr.Bit.biMotEn
  uint8   ucSpiOkCounter;
  tFTimer ftTime;
  uint8   ucNextEntry;       // index of next schedule table entry
  uint8   ucAddr;            // SPI address (combination of low and high nibble) - e.g. 'DRV8899_wCR3_'
} tCddStp8899Com_DebugOlErrorProblem;

#define cDebugSize  10u
static volatile tCddStp8899Com_DebugOlErrorProblem CddStp8899Com_Debug__OlErrorProblem[cDebugSize];
static volatile uint8   CddStp8899Com_Debug__ucIdx = 0;
static volatile boolean CddStp8899Com_Debug__bSomeKindOfError = FALSE;

#if (CDDSTP8899_ENABLE_DEBUG == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddStp8899Com_DEBUG_Check_EnOl_DisOut
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddStp8899Com_DEBUG_Check_EnOl_DisOut(void)
{
  static volatile boolean CddStp8899Com_Debug__bStateOld_EnOl          = FALSE;
  static volatile boolean CddStp8899Com_Debug__bStateOld_DisOut        = FALSE;
  static volatile uint8   CddStp8899Com_Debug__ucStateOld_SpiOkCounter = 0;

  // PRQA S 3415 2 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 3415(Right hand operand of '&&' or '||' is an expression with possible side effects.) Depth: 0 Ref: MISRA C:2012 Rule-13.5; REFERENCE - ISO:C90-5,1,2,3 Program Execution
  if (   (CddStp8899Com_Debug__bStateOld_EnOl         != CddStp8899Com_DataMirror.CtrlTx.aCReg4[0].Bit.u1EN_OL)    // changed?
      || (CddStp8899Com_Debug__bStateOld_DisOut       != CddStp8899Com_DataMirror.CtrlTx.aCReg2[0].Bit.u1DIS_OUT)  // changed?
      || (CddStp8899Com_Debug__ucStateOld_SpiOkCounter > CddStp8899Com_ucDEBUG_SpiOkCounter)                   // reset to '0'?
    )
  {
    CddStp8899Com_Debug__OlErrorProblem[CddStp8899Com_Debug__ucIdx].bState_EnOl = CddStp8899Com_DataMirror.CtrlTx.aCReg4[0].Bit.u1EN_OL;        // set via fct 'CddStp88XX_HalStpLwr_SendCReg4' | 'CddStp8899Com_SetCReg4'
    CddStp8899Com_Debug__OlErrorProblem[CddStp8899Com_Debug__ucIdx].bState_DisOut = CddStp8899Com_DataMirror.CtrlTx.aCReg2[0].Bit.u1DIS_OUT;      // requested via fct 'CddStp8899Com_GetCRegRxMotEn'
    CddStp8899Com_Debug__OlErrorProblem[CddStp8899Com_Debug__ucIdx].ucSpiOkCounter = CddStp8899Com_ucDEBUG_SpiOkCounter;
    CddStp8899Com_Debug__OlErrorProblem[CddStp8899Com_Debug__ucIdx].ucAddr = CddStp8899Com_SpiSchedTable[CddStp8899Com_aucSchedState[0]].ucAddr;      // e.g. 'DRV8899_wCR1_' = 0x06 = 'real'-Adr 3)
    CddStp8899Com_Debug__OlErrorProblem[CddStp8899Com_Debug__ucIdx].ucNextEntry = CddStp8899Com_SpiSchedTable[CddStp8899Com_aucSchedState[0]].ucNextEntry; // index of next schedule table entry
    CddStp8899Com_Debug__OlErrorProblem[CddStp8899Com_Debug__ucIdx].ftTime = TimerGetTick();

    // PRQA S 400 1 // program architecture and readability - intentionally no modification of existing code - warning - QAC(Prio7) Msg: 400([U] 'CddStp8899Com_Debug__ucIdx' is modified more than once between sequence points - evaluation order unspecified.) Depth: 0 Ref: MISRA C:2012 Rule-1.3, Rule-13.2; REFERENCE - ISO:C90-6.3 Expressions
    CddStp8899Com_Debug__ucIdx = (CddStp8899Com_Debug__ucIdx + 1u) % cDebugSize;
  }

  CddStp8899Com_Debug__bStateOld_EnOl = CddStp8899Com_DataMirror.CtrlTx.aCReg4[0].Bit.u1EN_OL; // depends on 'CddStp88__LwrDisableOlDetection', too
  CddStp8899Com_Debug__bStateOld_DisOut = CddStp8899Com_DataMirror.CtrlTx.aCReg2[0].Bit.u1DIS_OUT;
  CddStp8899Com_Debug__ucStateOld_SpiOkCounter = CddStp8899Com_ucDEBUG_SpiOkCounter;

  if ((CddStp88XX_aeState[0] == CddStp88XX_eStateErr) || (CddStp88XX_aStpState[0].Bit.ErrDrvDefect == 1u)) // '9'  OR  SPI-Error reported by Stp-Drv-HW (previously called 'ErrDrvDefect': driver defect error)
  {
    CddStp8899Com_Debug__bSomeKindOfError = TRUE;
  }
  else
  {
    CddStp8899Com_Debug__bSomeKindOfError = FALSE;
  }
}
#endif
//EOF
