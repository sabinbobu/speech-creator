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
/// \file  CddStp8899Com.h
///
/// \brief  Handling the SPI-Communication with TI-Stepper-Drviver-Chip
///         Register-Handling of TI-Stepper-Drviver-Chip
///
/// \descr  Handling the SPI-Communication to TI-Stepper-Drviver-Chip
///         Register-Handling of TI-Stepper-Drviver-Chip
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
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Ott, Peter ALRT/EEG-PM2 (otp2rt)
///         mailTo:peter.ott@al-lighting.com       
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------

#ifndef __CDDSTP8899COM_H__
#define __CDDSTP8899COM_H__


//=============================================================================
// includes
//=============================================================================

#include <../Cdd/CddStp/Cfg/CddStp_Cfg.h>
#include <CddStp88XX.h>


//=============================================================================
// defines
//=============================================================================

//#define CFA_CNT_STP_88XX   (4u)
#define CFG_Stp_IdxVer     (0u)   // Index  of Vertical   Stepper

//-----------------------------------------------------------------------------
// TI-DRV8899 initialization data
//-----------------------------------------------------------------------------
// Bit-Access mybe via 'https://bytes.com/topic/c/answers/216333-binary-constant-macros'

// ctrl-register format and initialization values
#define LOW_BYTE_FIRST 1
#define CPU_BYTE_ORDER LOW_BYTE_FIRST
#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)


  // Schedule tables (currently only ONE)
  typedef enum
  {
    CddStp8899Com_eSt0                                              = 0,  // CDDSTP8899_SpiSt_WriteCr12_ReadCr12
  //CddStp8899Com_eSt1                                              = 1,  // CDDSTP8899_SpiSt_WriteCr34A67_ReadCr34A67
  //CddStp8899Com_eSt2                                              = 2,  // CDDSTP8899_SpiSt_ReadSr12367A8A
  //CddStp8899Com_eSt3                                              = 3,  // CDDSTP8899_SpiSt_ReadSr3
    CddStp8899Com_eStMax                                            = 1   // count of schedule tables
  } eCDDSTPScheduleTables;

  // Attention !! This list must match the ROM schedule table order !!
  #define CDDSTP8899_SpiSt_readWriteAll                          CddStp8899Com_eSt0
//#define CDDSTP8899_SpiSt_WriteCr34A67_ReadCr34A67              CddStp8899Com_eSt1
//#define CDDSTP8899_SpiSt_ReadSr12367A8A                        CddStp8899Com_eSt2
//#define CDDSTP8899_SpiSt_ReadSr3                               CddStp8899Com_eSt3

  #define CDDSTP8899_SpiSt_IxMax                                 11u  // size of SPI-Schedule-Table

  #define CDDSTP8899_SpiSt_StartIx0                              0
//#define CDDSTP8899_SpiSt_StartIx1                              2
//#define CDDSTP8899_SpiSt_StartIx2                              8
//#define CDDSTP8899_SpiSt_StartIx3                              13

  #define CDDSTP8899_SpiSt_Bit0                                  0x01
// jk-tbd-Cyclic  #define CDDSTP8899_SpiSt_Bit1                  0x02
// jk-tbd-Cyclic  #define CDDSTP8899_SpiSt_Bit2                  0x04
// jk-tbd-Cyclic  #define CDDSTP8899_SpiSt_Bit3                  0x08

  #define CDDSTP8899_SpiSt_EndIx0                                11
  #define CDDSTP8899_SpiSt_RxNotifyIx0                           0x00000002  // bit number CDDSTP8899_SpiSt_EndIx0
//#define CDDSTP8899_SpiSt_EndIx1                                7
//#define CDDSTP8899_SpiSt_RxNotifyIx1                           0x00000080  // bit number CDDSTP8899_SpiSt_EndIx1
//#define CDDSTP8899_SpiSt_EndIx2                                12
//#define CDDSTP8899_SpiSt_RxNotifyIx2                           0x00001000  // bit number CDDSTP8899_SpiSt_EndIx2
//#define CDDSTP8899_SpiSt_EndIx3                                14
//#define CDDSTP8899_SpiSt_RxNotifyIx3                           0x00004000  // bit number CDDSTP8899_SpiSt_EndIx3


//-----------------------------------------------------------------------------
// Data-Mirror of DRV8899 registers
//-----------------------------------------------------------------------------

    // 7x Control-Registers
    // CTRL1-Register
    typedef struct
    {
        uint8  u2SLEW_RATE          : 2 ; // Blanking-Time (S.27) 00b=10V/us ... 11b=105V/us
        uint8  u2RSVD               : 2 ; // Reserved
        uint8  u4TRQ_DAC            : 4 ; // Torque-DAC (S.17) 0000b=100% ... 1111b=6.25%
    } tCddStp8899Com_Bit_CtrlReg_01;

    // CTRL2-Register
    typedef struct
    {
        uint8  u3DECAY              : 3 ; // (S.19)
        uint8  u2TOFF               : 2 ; // 00b=7us ... 11b=32us
        uint8  u2RSVD               : 2 ; // Reserved
        uint8  u1DIS_OUT            : 1 ; // Write '1' to Hi-Z all outputs. OR'ed with DRVOFF pin. Ensure OL fault detection is disabled by writing '0' to EN_OL bit, before making the outputs Hi-Z by writing '1' to DIS_OUT.
    } tCddStp8899Com_Bit_CtrlReg_02;

    // CTRL3-Register
    typedef struct
    {
        uint8  u4MICROSTEP_MODE     : 4 ; // 0000b = Full step (2-phase excitation) with 100% current ... 1010b = 1/256 step (1011b to 1111b = Reserved)
        uint8  u1SPI_STEP           : 1 ; // 0b = Outputs follow input pin for STEP | 1b = Outputs follow SPI registers STEP
        uint8  u1SPI_DIR            : 1 ; // 0b = Outputs follow input pin for DIR  | 1b = Outputs follow SPI registers DIR
        uint8  u1STEP               : 1 ; // Step input. Logic '1' causes the indexer to advance one step, when SPI_STEP = 1.
        uint8  u1DIR                : 1 ; // Direction input. Logic '1' sets the direction of stepping, when SPI_DIR = 1.
    } tCddStp8899Com_Bit_CtrlReg_03;

    // CTRL4-Register
    typedef struct
    {
        uint8  u1TW_REP             : 1 ; // 0b = Over- or undertemp. warning is not reported on the nFAULT line | 1b = Overtemperature or undertemperature warning is reported on the nFAULT line
        uint8  u1OTSD_MODE          : 1 ; // 0b = Overtemperature condition will cause latched fault             | 1b = Overtemperature condition will cause automatic recovery fault
        uint8  u1OCP_MODE           : 1 ; // 0b = Overcurrent condition causes a latched fault                   | 1b = Overcurrent condition causes an automatic retrying fault
        uint8  u1EN_OL              : 1 ; // Write '1' to enable open load detection  -  Ensure OL fault detection is disabled by writing '0' to EN_OL bit, before making the outputs Hi-Z by writing '1' to DIS_OUT.
        uint8  u3LOCK               : 3 ; // Write 110b to lock the settings by ignoring further register writes except to these bits and address 0x06h bit 7 (CLR_FLT). Writing any sequence other than 110b has no effect when unlocked. Write 011b to this register to unlock all registers. Writing any sequence other than 011b has no effect when locked.
        uint8  u1CLR_FLT            : 1 ; // Write '1' to this bit to clear all latched fault bits. This bit automatically resets after being written.
    } tCddStp8899Com_Bit_CtrlReg_04;

    // CTRL5...7-Register
    typedef struct
    {
        uint8  u8RSVD               : 8 ; // completly RESERVED
    } tCddStp8899Com_Bit_CtrlReg_RSVD;

    
     // Basic-Status-Registers - comes each time one each SPI-Response: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1
    typedef struct
    { 
        uint8  u1OL                 : 1 ; // Indicates open-load condition.
        uint8  u1TF                 : 1 ; // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
        uint8  u1RSVD               : 1 ; // Reserved
        uint8  u1OCP                : 1 ; // Indicates overcurrent fault condition.
        uint8  u1CPUV               : 1 ; // Indicates charge pump undervoltage fault condition. Latched high after power-up, remains set until it is cleared through the CLR_FLT bit or an nSLEEP reset pulse.
        uint8  u1UVLO               : 1 ; // Indicates an undervoltage lockout  fault condition. Latched high after power-up, remains set until it is cleared through the CLR_FLT bit or an nSLEEP reset pulse.
        uint8  u2Always1            : 2 ; // Always '1'
    } tCddStp8899Com_Bit_StatReg_Basic;


    // 3x Status-Registers
    // FAULT-Status-Register
    typedef struct
    { 
        uint8  u1OL                 : 1 ; // Indicates open-load condition.
        uint8  u1TF                 : 1 ; // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
        uint8  u1RSVD               : 1 ; // Reserved
        uint8  u1OCP                : 1 ; // Indicates overcurrent fault condition.
        uint8  u1CPUV               : 1 ; // Indicates charge pump undervoltage fault condition. Latched high after power-up, remains set until it is cleared through the CLR_FLT bit or an nSLEEP reset pulse.
        uint8  u1UVLO               : 1 ; // Indicates an undervoltage lockout  fault condition. Latched high after power-up, remains set until it is cleared through the CLR_FLT bit or an nSLEEP reset pulse.
        uint8  u1SPI_ERROR          : 1 ; // Indicates SPI protocol errors, such as more SCLK pulses than are required or SCLK is absent even though nSCS is low. Becomes high in fault and the nFAULT pin is driven low.
        uint8  u1FAULT              : 1 ; // When nFAULT pin is at 1, FAULT bit is 0. When nFAULT pin is at 0, FAULT bit is 1.
    } tCddStp8899Com_Bit_StatReg_Fault;

    // DIAG-Status-1-Register
    typedef struct
    {
        uint8  u1OCP_HS1_A          : 1 ; // Indicates overcurrent fault on the high-side FET of half bridge 1 in AOUT
        uint8  u1OCP_LS1_A          : 1 ; // Indicates overcurrent fault on the low-side  FET of half bridge 1 in AOUT
        uint8  u1OCP_HS2_A          : 1 ; // Indicates overcurrent fault on the high-side FET of half bridge 2 in AOUT
        uint8  u1OCP_LS2_A          : 1 ; // Indicates overcurrent fault on the low-side  FET of half bridge 2 in AOUT
        uint8  u1OCP_HS1_B          : 1 ; // Indicates overcurrent fault on the high-side FET of half bridge 1 in BOUT
        uint8  u1OCP_LS1_B          : 1 ; // Indicates overcurrent fault on the low-side  FET of half bridge 1 in BOUT
        uint8  u1OCP_HS2_B          : 1 ; // Indicates overcurrent fault on the high-side FET of half bridge 2 in BOUT
        uint8  u1OCP_LS2_B          : 1 ; // Indicates overcurrent fault on the low-side  FET of half bridge 2 in BOUT
    } tCddStp8899Com_Bit_StatReg_Diag1;

    // DIAG-Status-2-Register
    typedef struct
    {
        uint8  u1OL_A               : 1 ; // Indicates open-load detection on AOUT
        uint8  u1OL_B               : 1 ; // Indicates open-load detection on BOUT
        uint8  u3RSVD               : 3 ; // Reserved
        uint8  u1OTS                : 1 ; // Indicates overtemperature shutdown
        uint8  u1OTW                : 1 ; // Indicates overtemperature warning
        uint8  u1UTW                : 1 ; // Indicates undertemperature warning
    } tCddStp8899Com_Bit_StatReg_Diag2;

#else
    #error Big Endian not supported
#endif


  // R/W registers 
  // use bit representation for initializing
  // easy human-reading
  typedef union { tCddStp8899Com_Bit_CtrlReg_01 Bit; uint8 ucRaw; } tCddStp8899Com_CReg1; // TRQ_DAC [3:0]  |  RSVD  |  SLEW_RATE [1:0]
  typedef union { tCddStp8899Com_Bit_CtrlReg_02 Bit; uint8 ucRaw; } tCddStp8899Com_CReg2; // DIS_OUT  |  RSVD  |  TOFF [1:0]  |  DECAY [2:0]
  typedef union { tCddStp8899Com_Bit_CtrlReg_03 Bit; uint8 ucRaw; } tCddStp8899Com_CReg3; // DIR  |  STEP  |  SPI_DIR  |  SPI_STEP  |  MICROSTEP_MODE [3:0]
  typedef union { tCddStp8899Com_Bit_CtrlReg_04 Bit; uint8 ucRaw; } tCddStp8899Com_CReg4; // CLR_FLT  |  LOCK [2:0]  |  EN_OL  |  OCP_MODE  |  OTSD_MODE  |  TW_REP


  // read only registers
  // use raw representation for initializing (set all bits to to 0)
  typedef union { tCddStp8899Com_Bit_StatReg_Basic Bit; uint8 ucRaw; } tCddStp8899Com_StatReg_Basic; // 1  |  1  |  UVLO  |  CPUV  |  OCP  |  RSVD  |  TF  |  OL                                                    // = Basic-Status-Registers - comes each time one each SPI-Response: Stat3 Stat2 Stat1 Hdr1 Hdr2 Reg3 Reg2 Reg1
  typedef union { tCddStp8899Com_Bit_StatReg_Fault Bit; uint8 ucRaw; } tCddStp8899Com_StatReg_Fault; // FAULT  |  SPI_ERROR  |  UVLO  |  CPUV  |  OCP  |  RSVD  |  TF  |  OL                                        // = 'FAULT Status'
  typedef union { tCddStp8899Com_Bit_StatReg_Diag1 Bit; uint8 ucRaw; } tCddStp8899Com_StatReg_Diag1; // OCP_LS2_B  |  OCP_HS2_B  |  OCP_LS1_B  |  OCP_HS1_B  |  OCP_LS2_A  |  OCP_HS2_A  |  OCP_LS1_A  |  OCP_HS1_A // = 'DIAG Status 1'
  typedef union { tCddStp8899Com_Bit_StatReg_Diag2 Bit; uint8 ucRaw; } tCddStp8899Com_StatReg_Diag2; // UTW  |  OTW  |  OTS  |  RSVD  |  OL_B  |  OL_A                                                          // = 'DIAG Status 2'


  // all Ctrl-Registers
  typedef struct
  {
    tCddStp8899Com_CReg1    aCReg1[CFA_CNT_STP_88XX];     // control register 1  -  TRQ_DAC [3:0]  |  RSVD  |  SLEW_RATE [1:0]
    tCddStp8899Com_CReg2    aCReg2[CFA_CNT_STP_88XX];     // control register 2  -  DIS_OUT  |  RSVD  |  TOFF [1:0]  |  DECAY [2:0]
    tCddStp8899Com_CReg3    aCReg3[CFA_CNT_STP_88XX];     // control register 3  -  DIR  |  STEP  |  SPI_DIR  |  SPI_STEP  |  MICROSTEP_MODE [3:0]
    tCddStp8899Com_CReg4    aCReg4[CFA_CNT_STP_88XX];     // control register 4  -  CLR_FLT  |  LOCK [2:0]  |  EN_OL  |  OCP_MODE  |  OTSD_MODE  |  TW_REP  }tCddStp8899Com_CtrlData;
//  tCddStp8899Com_CRegRSVD   aReg05[CFA_CNT_STP_88XX];     // currently completly RESERVED
//  tCddStp8899Com_CRegRSVD   aReg06[CFA_CNT_STP_88XX];     // currently completly RESERVED - reserved but somehow about step-speed
//  tCddStp8899Com_CRegRSVD   aReg07[CFA_CNT_STP_88XX];     // currently completly RESERVED
  } tCddStp8899Com_CtrlData;


  // all State-Registers
  typedef struct
  {
    // jk-update uint8    uint8   aucSRegBasic[CFA_CNT_STP_88XX];     // status register 'B' - Basic-Status - comes each time 'automatically' - 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL
    // ...
    tCddStp8899Com_StatReg_Basic  aSRegBasic[CFA_CNT_STP_88XX];       // status register 'B' - Basic-Status - comes each time 'automatically' - 1 | 1 | UVLO | CPUV | OCP | RSVD | TF | OL
    tCddStp8899Com_StatReg_Fault  aSRegFault[CFA_CNT_STP_88XX];       // status register  0  - Fault-Status                                   - FAULT | SPI_ERROR | UVLO | CPUV | OCP | RSVD | TF | OL
    tCddStp8899Com_StatReg_Diag1  aSRegDiag1[CFA_CNT_STP_88XX];       // status register  1  - Diag-Status-1                                  - OCP_LS2_B | OCP_HS2_B | OCP_LS1_B | OCP_HS1_B | OCP_LS2_A | OCP_HS2_A | OCP_LS1_A | OCP_HS1_A
    tCddStp8899Com_StatReg_Diag2  aSRegDiag2[CFA_CNT_STP_88XX];       // status register  2  - Diag-Status-2                                  - UTW | OTW | OTS | RSVD | OL_B | OL_A
  }tCddStp8899Com_StatData;

  // complete Data-Mirror
  typedef struct
  {
    tCddStp8899Com_CtrlData  CtrlTx;
    tCddStp8899Com_CtrlData  CtrlRx;
    tCddStp8899Com_StatData  StatRx;              // raw      status register values directly after SPI read
    tCddStp8899Com_StatData  StatvRx;             // verified status register values          after checks (DrvDefect (parity), DriverReset)
  } tCddStp8899Com_DataMirror;


  //=============================================================================
  // inline functions
  //=============================================================================

  // global definitions used for inline function access
  extern tCddStp8899Com_DataMirror   CddStp8899Com_DataMirror;
  extern uint8                       CddStp8899Com_aucStReqSingle  [CFA_CNT_STP_88XX];
  extern uint8                       CddStp8899Com_aucStReqOnceMore[CFA_CNT_STP_88XX];
  extern boolean                     CddStp88xx__LwrSleepAndDisable; // HW-Pins of 'Sleep' and 'Disable' are 'active'

  //lint -e528 Symbol 'xxx' not referenced, usage of static inline

  // check if schedule table has finished
  INLINE boolean CddStp8899Com_CheckStReady(uint8 ucIx, uint32 ulSt)
  {
    return ((CddStp8899Com_aucStReqSingle[ucIx] & (uint8) ((uint32) 1u << ulSt)) != 0) ? FALSE : TRUE;
  }

  // initiate start of schedule table
  INLINE void  CddStp8899Com_StReqSingle(uint8 ucIx, uint32 ulSt)
  {
    if (CddStp8899Com_CheckStReady(ucIx, ulSt) != FALSE)                  // abort and restart schedule table if it is active in CddStp8899Com_SpiRxTx()
    {
      CddStp8899Com_aucStReqOnceMore[ucIx] |= (uint8) ((uint32) 1u << ulSt); // this code line is already atomar (checked by GHS MULTI assembly view with actual compiler options)
    }
    // always
    CddStp8899Com_aucStReqSingle  [ucIx] |= (uint8) ((uint32) 1u << ulSt);   // this code line is already atomar (checked by GHS MULTI assembly view with actual compiler options)
  }

  INLINE void  CddStp8899Com_SetCReg1 (uint8 ucIx, uint8 uc) { CddStp8899Com_DataMirror.CtrlTx.aCReg1 [ucIx].ucRaw = uc; }
  INLINE void  CddStp8899Com_SetCReg2 (uint8 ucIx, uint8 uc) { CddStp8899Com_DataMirror.CtrlTx.aCReg2 [ucIx].ucRaw = uc; }
  INLINE void  CddStp8899Com_SetCReg3 (uint8 ucIx, uint8 uc) { CddStp8899Com_DataMirror.CtrlTx.aCReg3 [ucIx].ucRaw = uc; }
  INLINE void  CddStp8899Com_SetCReg4 (uint8 ucIx, uint8 uc) { CddStp8899Com_DataMirror.CtrlTx.aCReg4 [ucIx].ucRaw = uc; }

  INLINE boolean CddStp8899Com_GetCRegRxMotEn(const uint8 ucIx) 
  {
    // jk-orig: return ((CddStp8899Com_DataMirror_.CtrlRx.aCReg2[ucIx] & CDDSTP8899_old_Mask_MOTEN) != 0) ? TRUE : FALSE; // Ctrl-Reg2: u1DIS_OUT

    uint16 ucMotEn = 0;

    // jk-ok: unMotEn = CddStp8899Com_DataMirror.CtrlRx.aCReg2[ucIx].ucRaw & 0x0080; // TI: take only bit '7' = 'DIS_OUT'
              ucMotEn = CddStp8899Com_DataMirror.CtrlRx.aCReg2[ucIx].Bit.u1DIS_OUT;  // N.b.: var is yet NOT 'ready'!
    // jk-ok: unMotEn = unMotEn ^ 0x0080; // XOR: toggle bit '7' DIS_OUT' (MotEn=Motor-Enable <-> DIS_OUT=Disable Output)
              ucMotEn = (ucMotEn == 0u) ? 1u : 0u; // swap:  MotEn = Motor-Enable  <->  DisOut = Disable Output

    return (ucMotEn != 0u) ? TRUE : FALSE;
  }


//=============================================================================
// Interfaces
//=============================================================================

  void   CddStp_SpiRx(uint16 unIx, uint32 ulData);
  uint32 CddStp_SpiTx(uint16 unIx);
  void CddStp8899Com_SetFaultClr(uint8 ucChannelIdx);

  //=============================================================================
  // function prototypes
  //=============================================================================

/* jk-tbd */ typedef uint16        tCddSpiData;       // customize this type to your requirements
/* jk-tbd */ typedef sint8         tCddSpiL1Index;
/* jk-tbd */ typedef uint8         tCddSpiL2Channel;  // up to 255 channels (spi devices)
/* jk-tbd */ typedef uint8         tCddSpiL2Single;
/* jk-tbd */ typedef tCddSpiData   (*tCddSpiRxTxFct)(tCddSpiL2Channel SpiL2Channel, tCddSpiData SpiData);

  boolean     CddStp8899Com_GetSRegBsc          (uint8 ucIx, uint8* pucSRegBsc);
  boolean     CddStp8899Com_GetSRegFlt          (uint8 ucIx, uint8* pucSRegFlt);
  boolean     CddStp8899Com_GetSRegDiag1        (uint8 ucIx, uint8* pucSRegDiag1);
  boolean     CddStp8899Com_GetSRegDiag2        (uint8 ucIx, uint8* pucSRegDiag2);
  boolean     CddStp8899Com_GetSRegDiag12       (uint8 ucIx, uint8* pucSRegDiag1, uint8* pucSRegDiag2);
  boolean     CddStp8899Com_GetSRegFltDiag2     (uint8 ucIx, uint8* pucSRegFlt  , uint8* pucSRegDiag2);
  boolean     CddStp8899Com_GetSRegBscFltDiag12 (uint8 ucIx, uint8* pucSRegBsc  , uint8* pucSRegFlt, uint8* pucSRegDiag1, uint8* pucSRegDiag2);

//boolean     CddStp8899Com_StartRxNotificationCr134A67  (uint8 ucIx);
//boolean     CddStp8899Com_StartRxNotificationSr12367A8A(uint8 ucIx);
//boolean     CddStp8899Com_StartRxNotificationSr3       (uint8 ucIx);
  
//boolean     CddStp8899Com_CheckRxNotificationCr134A67  (uint8 ucIx);
//boolean     CddStp8899Com_CheckRxNotificationSr12367A8A(uint8 ucIx);
//boolean     CddStp8899Com_CheckRxNotificationSr3       (uint8 ucIx);

#endif // __CDDSTP8899COM_H__

// EOF
