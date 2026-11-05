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
/// \file   CddTps92520_Types.h
///
/// \brief  Types specific description for TPS92520
///
/// \author OTT, Peter ALDE-RT/EES6
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS92520_TYPES_2021_01_21_H_
#define CDD_TPS92520_TYPES_2021_01_21_H_

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
#include <../Cfg/CddTps92520_Cfg.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
// SYSCFG1 register coonfiguration
#define CDDTPS92520_Cfg_CH1INTPWM       0u   // Internal PWM generator not used
#define CDDTPS92520_Cfg_CH2INTPWM       0u   // Internal PWM generator not used
#define CDDTPS92520_Cfg_PWMPH           1u   // 0 deg phase shift for internal PWMs

// SYSCFG2 register coonfiguration
#define CDDTPS92520_Cfg_IFT             0u   // IFT Fault Timer 3.6ms
#define CDDTPS92520_Cfg_CH1TSFL         0u   // Channel auto-restart by thermal shutdown
#define CDDTPS92520_Cfg_CH2TSFL         0u   // Channel auto-restart by thermal shutdown

// Communication watchdog timer (CMWTAP) register configuration
#define CDDTPS92520_Cfg_CMWTAP          8u   // Communication watchdog period 1,67s (typcial)

// Thermal warning limit (TWLMT) register configuration
#define CDDTPS92520_Cfg_TWLMT         147u   // Thermal warning limit : Tj = 0,7168°C * 147d * 4 - 271,51°C = 150°C

// Internal PWM clock divider (PWMDIV) register configuration
#define CDDTPS92520_Cfg_PWMDIV          5u   // Internal PWM-Frequency = 439Hz

// Buck ON-time and frequency for CHxTON register configuration
#define CDDTPS92520_Cfg_CHxTON_LoFreq   6u   // Buck frequency  400kHz: for normal operation
#define CDDTPS92520_Cfg_CHxTON_HiFreq  22u   // Buck frequency 1200kHz: for initialization and low PWM

// Limp home configuration register 1
#define CDDTPS92520_Cfg_LHEXTIADJ       1u   // Internal LHxIADJ register used as CHxIADJ setting in Limp home
#define CDDTPS92520_Cfg_LH1INTPM        1u   // Limp home LED current duty cycle controlled by internal PWM
#define CDDTPS92520_Cfg_LH2INTPM        1u   // Limp home LED current duty cycle controlled by internal PWM
#define CDDTPS92520_Cfg_LHPWMPH         1u   // 0 deg phase shift for internal PWMs

// IADJ scaling
#define CDDTPS92520_CHxIADJ_Max      1023u   // represented by 10bit
#define CDDTPS92520_DutyCycle_0         0u   // detection of duty cycle 0
#define CDDTPS92520_CHxIADJL_CHxIADJ_BIT_MASK (uint16) 0x03  // Bit mask for CHxIADJ[1:0]

// driver organization
#define CDDTPS92520_NbOfChannel         2u   // Number of channel by TPS92520 device
#define CDDTPS92520_CFG_NO_OF_CHANNELS  (CDDTPS92520_Cfg_NbOfDevices * CDDTPS92520_NbOfChannel)

// averaging of ADC values
#define CDDTPS92520_AdcSamples          4u  // do averaging of 4 ADC values

// SYSCFG1 ENABLE bit
#define CDDTPS92520_CH_x_ENABLE         1u
#define CDDTPS92520_CH_x_DISABLE        0u

// for exit of STANDALONE mode
#define CDDTPS92520_RESET            0xC3u


//=============================================================================
// TPS92520 SPI addresses
//=============================================================================
#define CDDTPS92520_AddrSYSCFG1     (uint16)0x00u
#define CDDTPS92520_AddrSYSCFG2     (uint16)0x01u
#define CDDTPS92520_AddrCMWTAP      (uint16)0x02u
#define CDDTPS92520_AddrSTATUS1     (uint16)0x03u
#define CDDTPS92520_AddrSTATUS2     (uint16)0x04u
#define CDDTPS92520_AddrSTATUS3     (uint16)0x05u
#define CDDTPS92520_AddrTWLMT       (uint16)0x06u
#define CDDTPS92520_AddrSLEEP       (uint16)0x07u
#define CDDTPS92520_AddrCH1IADJL    (uint16)0x08u
#define CDDTPS92520_AddrCH1IADJH    (uint16)0x09u
#define CDDTPS92520_AddrCH2IADJL    (uint16)0x0Au
#define CDDTPS92520_AddrCH2IADJH    (uint16)0x0Bu
#define CDDTPS92520_AddrPWMDIV      (uint16)0x0Cu
#define CDDTPS92520_AddrCH1PWML     (uint16)0x0Du
#define CDDTPS92520_AddrCH1PWMH     (uint16)0x0Eu
#define CDDTPS92520_AddrCH2PWML     (uint16)0x0Fu
#define CDDTPS92520_AddrCH2PWMH     (uint16)0x10u
#define CDDTPS92520_AddrCH1TON      (uint16)0x11u
#define CDDTPS92520_AddrCH2TON      (uint16)0x12u
#define CDDTPS92520_AddrCH1VIN      (uint16)0x13u
#define CDDTPS92520_AddrCH1VLED     (uint16)0x14u
#define CDDTPS92520_AddrCH1VLEDON   (uint16)0x15u
#define CDDTPS92520_AddrCH1VLEDOFF  (uint16)0x16u
#define CDDTPS92520_AddrCH2VIN      (uint16)0x17u
#define CDDTPS92520_AddrCH2VLED     (uint16)0x18u
#define CDDTPS92520_AddrCH2VLEDON   (uint16)0x19u
#define CDDTPS92520_AddrCH2VLEDOFF  (uint16)0x1Au
#define CDDTPS92520_AddrTEMPL       (uint16)0x1Bu
#define CDDTPS92520_AddrTEMPH       (uint16)0x1Cu
#define CDDTPS92520_AddrV5D         (uint16)0x1Du
#define CDDTPS92520_AddrLHCFG1      (uint16)0x1Eu
#define CDDTPS92520_AddrLHCFG2      (uint16)0x1Fu
#define CDDTPS92520_AddrLHIL        (uint16)0x20u
#define CDDTPS92520_AddrLHIH        (uint16)0x21u
#define CDDTPS92520_AddrLHIFILTL    (uint16)0x22u
#define CDDTPS92520_AddrLHIFILTH    (uint16)0x23u
#define CDDTPS92520_AddrLH1IADJL    (uint16)0x24u
#define CDDTPS92520_AddrLH1IADJH    (uint16)0x25u
#define CDDTPS92520_AddrLH2IADJL    (uint16)0x26u
#define CDDTPS92520_AddrLH2IADJH    (uint16)0x27u
#define CDDTPS92520_AddrLHCH1PWML   (uint16)0x28u
#define CDDTPS92520_AddrLHCH1PWMH   (uint16)0x29u
#define CDDTPS92520_AddrLHCH2PWML   (uint16)0x2Au
#define CDDTPS92520_AddrLHCH2PWMH   (uint16)0x2Bu
#define CDDTPS92520_AddrLH1TON      (uint16)0x2Cu
#define CDDTPS92520_AddrLH2TON      (uint16)0x2Du
#define CDDTPS92520_AddrRESET       (uint16)0x2Eu

#define CDDTPS92520_ShiftAddrReg(Addr)  ((uint16) (Addr << 9u)) // Shift address register to bit position 9

#define CDDTPS92520_AddrSYSCFG1_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrSYSCFG1)
#define CDDTPS92520_AddrSYSCFG2_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrSYSCFG2)
#define CDDTPS92520_AddrCMWTAP_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCMWTAP)
#define CDDTPS92520_AddrSTATUS1_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrSTATUS1)
#define CDDTPS92520_AddrSTATUS2_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrSTATUS2)
#define CDDTPS92520_AddrSTATUS3_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrSTATUS3)
#define CDDTPS92520_AddrTWLMT_Tx      CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrTWLMT)
#define CDDTPS92520_AddrSLEEP_Tx      CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrSLEEP)
#define CDDTPS92520_AddrCH1IADJL_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH1IADJL)
#define CDDTPS92520_AddrCH1IADJH_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH1IADJH)
#define CDDTPS92520_AddrCH2IADJL_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH2IADJL)
#define CDDTPS92520_AddrCH2IADJH_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH2IADJH)
#define CDDTPS92520_AddrPWMDIV_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrPWMDIV)
#define CDDTPS92520_AddrCH1PWML_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH1PWML)
#define CDDTPS92520_AddrCH1PWMH_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH1PWMH)
#define CDDTPS92520_AddrCH2PWML_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH2PWML)
#define CDDTPS92520_AddrCH2PWMH_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH2PWMH)
#define CDDTPS92520_AddrCH1TON_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH1TON)
#define CDDTPS92520_AddrCH2TON_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH2TON)
#define CDDTPS92520_AddrCH1VIN_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH1VIN)
#define CDDTPS92520_AddrCH1VLED_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH1VLED)
#define CDDTPS92520_AddrCH1VLEDON_Tx  CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH1VLEDON)
#define CDDTPS92520_AddrCH1VLEDOFF_Tx CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH1VLEDOFF)
#define CDDTPS92520_AddrCH2VIN_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH2VIN)
#define CDDTPS92520_AddrCH2VLED_Tx    CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH2VLED)
#define CDDTPS92520_AddrCH2VLEDON_Tx  CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH2VLEDON)
#define CDDTPS92520_AddrCH2VLEDOFF_Tx CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrCH2VLEDOFF)
#define CDDTPS92520_AddrTEMPL_Tx      CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrTEMPL)
#define CDDTPS92520_AddrTEMPH_Tx      CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrTEMPH)
#define CDDTPS92520_AddrV5D_Tx        CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrV5D)
#define CDDTPS92520_AddrLHCFG1_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHCFG1)
#define CDDTPS92520_AddrLHCFG2_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHCFG2)
#define CDDTPS92520_AddrLHIL_Tx       CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHIL)
#define CDDTPS92520_AddrLHIH_Tx       CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHIH)
#define CDDTPS92520_AddrLHIFILTL_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHIFILTL)
#define CDDTPS92520_AddrLHIFILTH_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHIFILTH)
#define CDDTPS92520_AddrLH1IADJL_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLH1IADJL)
#define CDDTPS92520_AddrLH1IADJH_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLH1IADJH)
#define CDDTPS92520_AddrLH2IADJL_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLH2IADJL)
#define CDDTPS92520_AddrLH2IADJH_Tx   CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLH2IADJH)
#define CDDTPS92520_AddrLHCH1PWML_Tx  CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHCH1PWML)
#define CDDTPS92520_AddrLHCH1PWMH_Tx  CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHCH1PWMH)
#define CDDTPS92520_AddrLHCH2PWML_Tx  CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHCH2PWML)
#define CDDTPS92520_AddrLHCH2PWMH_Tx  CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLHCH2PWMH)
#define CDDTPS92520_AddrLH1TON_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLH1TON)
#define CDDTPS92520_AddrLH2TON_Tx     CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrLH2TON)
#define CDDTPS92520_AddrRESET_Tx      CDDTPS92520_ShiftAddrReg(CDDTPS92520_AddrRESET)

#define CDDTPS92520_ReadCmdBit_Tx     0x0000u // MSB (bit position 15) set to '0'
#define CDDTPS92520_WriteCmdBit_Tx    0x8000u // MSB (bit position 15) set to '1'

#define CDDTPS92520_SpiErrorMask      0xC000U  // these 2 bits have to be checked for SPI errors
#define CDDTPS92520_SpiRxExpected     0x4000U  // this is the expected value


//=============================================================================
// Type definition for Configuration and control registers
//=============================================================================
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)

// ADDR 0x00 - Register SYSCFG1
typedef struct tCddTps92520_Bit_SYSCFG1
{
  uint16 biCH1EN     : 1 ;
  uint16 biCH1INTPWM : 1 ;
  uint16 biCH2EN     : 1 ;
  uint16 biCH2INTPWM : 1 ;
  uint16 biCMWEN     : 1 ;
  uint16 biLHSW      : 1 ;
  uint16 u1PWMPH     : 1 ;
  uint16 biFPINRST   : 1 ;
}tCddTps92520_Bit_SYSCFG1;

// ADDR 0x01 - Register SYSCFG2
typedef struct tCddTps92520_Bit_SYSCFG2
{
  uint16 biCH1LSILIMFL : 1 ;
  uint16 biCH1HSILIMFL : 1 ;
  uint16 biCH1TSFL     : 1 ;
  uint16 biCH2LSILIMFL : 1 ;
  uint16 biCH2HSILIMFL : 1 ;
  uint16 biCH2TSFL     : 1 ;
  uint16 bi2IFT        : 2 ;
}tCddTps92520_Bit_SYSCFG2;

// ADDR 0x02 - Register CMWTAP
typedef struct tCddTps92520_Bit_CMWTAP
{
  uint16 bi4CMWTAP    : 4 ;
  uint16 bi4RESERVED  : 4 ;
}tCddTps92520_Bit_CMWTAP;

// ADDR 0x06 - Register TWLMT
typedef struct tCddTps92520_Byte_TWLMT
{
  uint8 biTWLMT;
}tCddTps92520_Byte_TWLMT;

// ADDR 0x07 - Register SLEEP
typedef struct tCddTps92520_Bit_SLEEP
{
  uint16 bi2SLEEP     : 2 ;
  uint16 bi6RESERVED  : 6 ;
}tCddTps92520_Bit_SLEEP;

// ADDR 0x08 - Register CH1IADJL
// ADDR 0x0A - Register CH2IADJL
typedef struct tCddTps92520_Bit_CHxIADJL
{
  uint16 bi2CHxIADJ   : 2 ;
  uint16 bi6RESERVED  : 6 ;
}tCddTps92520_Bit_CHxIADJL;

// ADDR 0x09 - Register CH1IADJH
// ADDR 0x0B - Register CH2IADJH
typedef struct tCddTps92520_Byte_CHxIADJH
{
  uint8 ucCHxIADJ;
}tCddTps92520_Byte_CHxIADJH;

// ADDR 0x0C - Register PWMDIV
typedef struct tCddTps92520_Bit_PWMDIV
{
  uint16 bi3PWMDIV   : 3 ;
  uint16 bi5RESERVED : 5 ;
}tCddTps92520_Bit_PWMDIV;

// ADDR 0x0D - Register CH1PWML
// ADDR 0x0F - Register CH2PWML
typedef struct tCddTps92520_Byte_CHxPWML
{
  uint8 ucCHxPWM;
}tCddTps92520_Byte_CHxPWML;

// ADDR 0x0E - Register CH1PWMH
// ADDR 0x10 - Register CH2PWMH
typedef struct tCddTps92520_Bit_CHxPWMH
{
  uint16 bi2CHxPWM    : 2 ;
  uint16 bi6RESERVED  : 6 ;
}tCddTps92520_Bit_CHxPWMH;

// ADDR 0x11 - Register CH1TON
// ADDR 0x12 - Register CH2TON
typedef struct tCddTps92520_Bit_CHxTON
{
  uint16 bi6CHxTON    : 6 ;
  uint16 bi2RESERVED  : 2 ;
}tCddTps92520_Bit_CHxTON;

// ADDR 0x1E - Register LHCFG1
typedef struct tCddTps92520_Bit_LHCFG1
{
  uint16 biLH1EN     : 1 ;
  uint16 biLH1INTPWM : 1 ;
  uint16 biLH1100D   : 1 ;
  uint16 biLH2EN     : 1 ;
  uint16 biLH2INTPWM : 1 ;
  uint16 biLH2100D   : 1 ;
  uint16 biLHEXTIADJ : 1 ;
  uint16 u1LHPWMPH   : 1 ;
}tCddTps92520_Bit_LHCFG1;

// ADDR 0x1F - Register LHCFG2
typedef struct tCddTps92520_Bit_LHCFG2
{
  uint16 biLH1LSILIMFL : 1 ;
  uint16 biLH1HSILIMFL : 1 ;
  uint16 biLH1TSFL     : 1 ;
  uint16 biLH2LSILIMFL : 1 ;
  uint16 biLH2HSILIMFL : 1 ;
  uint16 biLH2TSFL     : 1 ;
  uint16 bi2LHIFT      : 2 ;
}tCddTps92520_Bit_LHCFG2;

// ADDR 0x24 - Register LH1IADJL
// ADDR 0x26 - Register LH2IADJL
typedef struct tCddTps92520_Bit_LHxIADJL
{
  uint16 bi2LHxIADJ   : 2 ;
  uint16 bi6RESERVED  : 6 ;
}tCddTps92520_Bit_LHxIADJL;

// ADDR 0x25 - Register LH1IADJH
// ADDR 0x27 - Register LH2IADJH
typedef struct tCddTps92520_Byte_LHxIADJH
{
  uint8 ucLHxIADJ;
}tCddTps92520_Byte_LHxIADJH;

// ADDR 0x28 - Register LHCH1PWML
// ADDR 0x2A - Register LHCH2PWML
typedef struct tCddTps92520_Byte_LHCHxPWML
{
  uint8 ucLHxPWM;
}tCddTps92520_Byte_LHCHxPWML;

// ADDR 0x29 - Register LHCH1PWMH
// ADDR 0x2B - Register LHCH2PWMH
typedef struct tCddTps92520_Bit_LHCHxPWMH
{
  uint16 bi2LHxPWM    : 2 ;
  uint16 bi6RESERVED  : 6 ;
}tCddTps92520_Bit_LHCHxPWMH;

// ADDR 0x2C - Register LH1TON
// ADDR 0x2D - Register LH2TON
typedef struct tCddTps92520_Bit_LHxTON
{
  uint16 bi6LHxTON    : 6 ;
  uint16 bi2RESERVED  : 2 ;
}tCddTps92520_Bit_LHxTON;

// ADDR 0x2E - Register RESET
typedef struct tCddTps92520_Byte_RESET
{
  uint8 ucRESET;
}tCddTps92520_Byte_RESET;

//=============================================================================
// Type definition for Status registers
//=============================================================================

// ADDR 0x03 - Register STATUS1
typedef struct tCddTps92520_Bit_STATUS1
{
  uint16 biCH1COMPOV : 1 ;
  uint16 biCH1SHORT  : 1 ;
  uint16 biCH1HSILIM : 1 ;
  uint16 biCH1LSILIM : 1 ;
  uint16 biCH2COMPOV : 1 ;
  uint16 biCH2SHORT  : 1 ;
  uint16 biCH2HSILIM : 1 ;
  uint16 biCH2LSILIM : 1 ;
}tCddTps92520_Bit_STATUS1;

// ADDR 0x04 - Register STATUS2
typedef struct tCddTps92520_Bit_STATUS2
{
  uint16 biCH1TOFFMIN  : 1 ;
  uint16 biCH1BSTUV    : 1 ;
  uint16 biCH1TP       : 1 ;
  uint16 biCH2TOFFMIN  : 1 ;
  uint16 biCH2BSTUV    : 1 ;
  uint16 biCH2TP       : 1 ;
  uint16 bi2RESERVED   : 2 ;
}tCddTps92520_Bit_STATUS2;

// ADDR 0x05 - Register STATUS3
typedef struct tCddTps92520_Bit_STATUS3
{
  uint16 biCH1STATUS  : 1 ;
  uint16 biCH2STATUS  : 1 ;
  uint16 biPC         : 1 ;
  uint16 biTW         : 1 ;
  uint16 bi2CMWTO     : 2 ;
  uint16 biV5AUV      : 1 ;
  uint16 u1STANDALONE : 1 ;
}tCddTps92520_Bit_STATUS3;

// ADDR 0x13 - Register CH1VIN
// ADDR 0x17 - Register CH2VIN
typedef struct tCddTps92520_Byte_CHxVIN
{
  uint8 ucCHxVIN;
}tCddTps92520_Byte_CHxVIN;

// ADDR 0x14 - Register CH1VLED
// ADDR 0x18 - Register CH2VLED
typedef struct tCddTps92520_Byte_CHxVLED
{
  uint8 ucCHxVLED;
}tCddTps92520_Byte_CHxVLED;

// ADDR 0x15 - Register CH1VLEDON
// ADDR 0x19 - Register CH1VLEDON
typedef struct tCddTps92520_Byte_CHxVLEDON
{
  uint8 ucCHxVLEDON;
}tCddTps92520_Byte_CHxVLEDON;

// ADDR 0x16 - Register CH1VLEDOFF
// ADDR 0x1A - Register CH2VLEDOFF
typedef struct tCddTps92520_Byte_CHxVLEDOFF
{
  uint8 ucCHxVLEDOFF;
}tCddTps92520_Byte_CHxVLEDOFF;

// ADDR 0x1B - Register TEMPL
typedef struct tCddTps92520_Bit_TEMPL
{
  uint16 bi2TEMP      : 2 ;
  uint16 bi6RESERVED  : 6 ;
}tCddTps92520_Bit_TEMPL;

// ADDR 0x1C - Register TEMPH
typedef struct tCddTps92520_Byte_TEMPH
{
  uint8 ucTEMP;
}tCddTps92520_Byte_TEMPH;

// ADDR 0x1D - Register V5D
typedef struct tCddTps92520_Byte_V5D
{
  uint8 ucV5D;
}tCddTps92520_Byte_V5D;

// ADDR 0x20 - Register LHIL
typedef struct tCddTps92520_Bit_LHIL
{
  uint16 bi2LHI       : 2 ;
  uint16 bi6RESERVED  : 6 ;
}tCddTps92520_Bit_LHIL;

// ADDR 0x21 - Register LHIH
typedef struct tCddTps92520_Byte_LHIH
{
  uint8 ucLHI;
}tCddTps92520_Byte_LHIH;

// ADDR 0x22 - Register LHIFILTL
typedef struct tCddTps92520_Bit_LHIFILTL
{
  uint16 u2LHIFILT  : 2;
  uint16 u6RESERVED : 6;
}tCddTps92520_Bit_LHIFILTL;

// ADDR 0x23 - Register LHIFILTH
typedef struct tCddTps92520_Byte_LHIFILTH
{
  uint8 ucLHIFILT;
}tCddTps92520_Byte_LHIFILTH;

#else

#error CPU_BYTE_ORDER == HIGH_BYTE_FIRST not supported

#endif //(CPU_BYTE_ORDER == LOW_BYTE_FIRST)

// R/W registers
typedef union tCddTps92520_SYSCFG1   { tCddTps92520_Bit_SYSCFG1    Bit;                                     uint16 unRaw;  } tCddTps92520_SYSCFG1;
typedef union tCddTps92520_SYSCFG2   { tCddTps92520_Bit_SYSCFG2    Bit;                                     uint16 unRaw;  } tCddTps92520_SYSCFG2;
typedef union tCddTps92520_CMWTAP    { tCddTps92520_Bit_CMWTAP     Bit;                                     uint16 unRaw;  } tCddTps92520_CMWTAP;
typedef union tCddTps92520_TWLMT     {                                   tCddTps92520_Byte_TWLMT     Byte;  uint16 unRaw;  } tCddTps92520_TWLMT;
typedef union tCddTps92520_SLEEP     { tCddTps92520_Bit_SLEEP      Bit;                                     uint16 unRaw;  } tCddTps92520_SLEEP;
typedef union tCddTps92520_CHxIADJL  { tCddTps92520_Bit_CHxIADJL   Bit;                                     uint16 unRaw;  } tCddTps92520_CHxIADJL;
typedef union tCddTps92520_CHxIADJH  {                                   tCddTps92520_Byte_CHxIADJH  Byte;  uint16 unRaw;  } tCddTps92520_CHxIADJH;
typedef union tCddTps92520_PWMDIV    { tCddTps92520_Bit_PWMDIV     Bit;                                     uint16 unRaw;  } tCddTps92520_PWMDIV;
typedef union tCddTps92520_CHxPWML   {                                   tCddTps92520_Byte_CHxPWML   Byte;  uint16 unRaw;  } tCddTps92520_CHxPWML;
typedef union tCddTps92520_CHxPWMH   { tCddTps92520_Bit_CHxPWMH    Bit;                                     uint16 unRaw;  } tCddTps92520_CHxPWMH;
typedef union tCddTps92520_CHxTON    { tCddTps92520_Bit_CHxTON     Bit;                                     uint16 unRaw;  } tCddTps92520_CHxTON;
typedef union tCddTps92520_LHCFG1    { tCddTps92520_Bit_LHCFG1     Bit;                                     uint16 unRaw;  } tCddTps92520_LHCFG1;
typedef union tCddTps92520_LHCFG2    { tCddTps92520_Bit_LHCFG2     Bit;                                     uint16 unRaw;  } tCddTps92520_LHCFG2;
typedef union tCddTps92520_LHxIADJL  { tCddTps92520_Bit_LHxIADJL   Bit;                                     uint16 unRaw;  } tCddTps92520_LHxIADJL;
typedef union tCddTps92520_LHxIADJH  {                                   tCddTps92520_Byte_LHxIADJH  Byte;  uint16 unRaw;  } tCddTps92520_LHxIADJH;
typedef union tCddTps92520_LHCHxPWML {                                   tCddTps92520_Byte_LHCHxPWML Byte;  uint16 unRaw;  } tCddTps92520_LHCHxPWML;
typedef union tCddTps92520_LHCHxPWMH { tCddTps92520_Bit_LHCHxPWMH  Bit;                                     uint16 unRaw;  } tCddTps92520_LHCHxPWMH;
typedef union tCddTps92520_LHxTON    { tCddTps92520_Bit_LHxTON     Bit;                                     uint16 unRaw;  } tCddTps92520_LHxTON;

// RC (Read and Clear) registers
typedef union tCddTps92520_STATUS1   { tCddTps92520_Bit_STATUS1    Bit;                                     uint16 unRaw;  } tCddTps92520_STATUS1;
typedef union tCddTps92520_STATUS2   { tCddTps92520_Bit_STATUS2    Bit;                                     uint16 unRaw;  } tCddTps92520_STATUS2;
typedef union tCddTps92520_STATUS3   { tCddTps92520_Bit_STATUS3    Bit;                                     uint16 unRaw;  } tCddTps92520_STATUS3;

// R (Read only) registers
typedef union tCddTps92520_CHxVIN    {                                   tCddTps92520_Byte_CHxVIN      Byte; uint16 unRaw;  } tCddTps92520_CHxVIN;
typedef union tCddTps92520_CHxVLED   {                                   tCddTps92520_Byte_CHxVLED     Byte; uint16 unRaw;  } tCddTps92520_CHxVLED;
typedef union tCddTps92520_CHxVLEDON {                                   tCddTps92520_Byte_CHxVLEDON   Byte; uint16 unRaw;  } tCddTps92520_CHxVLEDON;
typedef union tCddTps92520_CHxVLEDOFF{                                   tCddTps92520_Byte_CHxVLEDOFF  Byte; uint16 unRaw;  } tCddTps92520_CHxVLEDOFF;
typedef union tCddTps92520_TEMPL     { tCddTps92520_Bit_TEMPL      Bit;                                      uint16 unRaw;  } tCddTps92520_TEMPL;
typedef union tCddTps92520_TEMPH     {                                   tCddTps92520_Byte_TEMPH       Byte; uint16 unRaw;  } tCddTps92520_TEMPH;
typedef union tCddTps92520_V5D       {                                   tCddTps92520_Byte_V5D         Byte; uint16 unRaw;  } tCddTps92520_V5D;
typedef union tCddTps92520_LHIL      { tCddTps92520_Bit_LHIL       Bit;                                      uint16 unRaw;  } tCddTps92520_LHIL;
typedef union tCddTps92520_LHIH      {                                   tCddTps92520_Byte_LHIH        Byte; uint16 unRaw;  } tCddTps92520_LHIH;
typedef union tCddTps92520_LHIFILTL  { tCddTps92520_Bit_LHIFILTL   Bit;                                      uint16 unRaw;  } tCddTps92520_LHIFILTL;
typedef union tCddTps92520_LHIFILTH  {                                   tCddTps92520_Byte_LHIFILTH    Byte; uint16 unRaw;  } tCddTps92520_LHIFILTH;

// W (write only) register
typedef union tCddTps92520_RESET     {                                   tCddTps92520_Byte_RESET       Byte; uint16 unRaw;  } tCddTps92520_RESET;


#endif // CDD_TPS92520_TYPES_2021_01_21_H_
