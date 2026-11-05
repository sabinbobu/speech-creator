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
/// \file  CddTpsGen2_Types.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN2_TYPES_2024_01_30_H_
#define CDD_TPS_GEN2_TYPES_2024_01_30_H_

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
#include <CddTpsGen2_Cfg.h> //TODO GEN3 take from _Cod.h


//=============================================================================
// Type definition for control and data structures
//=============================================================================


//=============================================================================
// Defines
//=============================================================================
//Length of message format
#define CDDTPSGEN2_N_HEADER_BYTES    3u

//Number of bytes transferred
#define CDDTPSGEN2_N_01_BYTE         1u
#define CDDTPSGEN2_N_02_BYTES        2u
#define CDDTPSGEN2_N_03_BYTES        3u
#define CDDTPSGEN2_N_04_BYTES        4u
#define CDDTPSGEN2_N_12_BYTES        12u
#define CDDTPSGEN2_N_16_BYTES        16u
#define CDDTPSGEN2_N_32_BYTES        32u

//Length of CRC
#define CDDTPSGEN2_N_CRC_BYTES       2u

//Reception acknowledge
#define CDDTPSGEN2_N_ACK             1u

#define CDDTPSGEN2_DUMMY_BYTE        1u
#define CDDTPSGEN2_MAX_WRITE_CMD_LENGTH    (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_32_BYTES  + CDDTPSGEN2_N_CRC_BYTES +  CDDTPSGEN2_N_ACK)
#define CDDTPSGEN2_MAX_READ_CMD_LENGTH     (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_CRC_BYTES + CDDTPSGEN2_N_32_BYTES  +  CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_MAX_CMD_LENGTH          (CDDTPSGEN2_MAX_READ_CMD_LENGTH + CDDTPSGEN2_DUMMY_BYTE)

//frame intialization bytes for write commands
#define CDDTPSGEN2_WRITE_01_BYTES    0x87u
#define CDDTPSGEN2_WRITE_02_BYTES    0x99u
#define CDDTPSGEN2_WRITE_03_BYTES    0x1Eu
#define CDDTPSGEN2_WRITE_04_BYTES    0xAAu
#define CDDTPSGEN2_WRITE_12_BYTES    0x2Du
#define CDDTPSGEN2_WRITE_16_BYTES    0x33u
#define CDDTPSGEN2_WRITE_32_BYTES    0xB4u

//frame intialization bytes for read commands
#define CDDTPSGEN2_READ_01_BYTES     0x4Bu
#define CDDTPSGEN2_READ_02_BYTES     0xCCu
#define CDDTPSGEN2_READ_03_BYTES     0xD2u
#define CDDTPSGEN2_READ_04_BYTES     0x55u
#define CDDTPSGEN2_READ_12_BYTES     0xE1u
#define CDDTPSGEN2_READ_16_BYTES     0x66u
#define CDDTPSGEN2_READ_32_BYTES     0x78u

//acknowledgement byte expected from Mlc chip
#define CDDTPSGEN2_ACK_BYTE          0x7Fu  

//Definitions for enable/disable Mlc features
#define CDDTPSGEN2_FEATURE_ON        1u     // active feature
#define CDDTPSGEN2_FEATURE_OFF       0u     // inactive feature

// definition of I2C Master Control Register bits
#define CDDTPSGEN2_I2CCTRL_NOADR     (uint8)(0x01U << 3U) // the 3th bit No Byte Address
#define CDDTPSGEN2_I2CCTRL_START     (uint8)(0x01U << 2U) // the 2th bit Start I2C operation
#define CDDTPSGEN2_I2CCTRL_RD        (uint8)(0x01U << 1U) // the 1th bit Specify I2C transaction: 0-write or 1-read
#define CDDTPSGEN2_I2CCTRL_RST       (uint8)(0x01U << 0U) // the 0th bit Reset I2C StateMachine and FIFO is flushed

// definition of I2C Status Register bits
#define CDDTPSGEN2_I2CSTAT_RFE       (uint8)(0x01U << 7u) // the 7th bit Receive FIFO Empty
#define CDDTPSGEN2_I2CSTAT_RFF       (uint8)(0x01U << 6u) // the 6th bit Receive FIFO Full
#define CDDTPSGEN2_I2CSTAT_BUSYERR   (uint8)(0x01U << 5u) // the 5th bit Busy Error
#define CDDTPSGEN2_I2CSTAT_SLANACK   (uint8)(0x01U << 4u) // the 2th bit Slave Address Not Acknowledged Error
#define CDDTPSGEN2_I2CSTAT_ADRNACK   (uint8)(0x01U << 3u) // the 3th bit Byte Address Not Acknowledged Error
#define CDDTPSGEN2_I2CSTAT_DATNACK   (uint8)(0x01U << 2u) // the 4th bit Write Data Not Acknowledged Error
#define CDDTPSGEN2_I2CSTAT_SDALOW    (uint8)(0x01U << 1u) // the 1th bit SDA Stuck Low Error
#define CDDTPSGEN2_I2CSTAT_BUSY      (uint8)(0x01U << 0u) // the 0th bit I2C Controller Busy

#define CDDTPSGEN2_I2C_RD_STATUS_VALID   ((uint8)CDDTPSGEN2_I2CSTAT_BUSYERR | (uint8)CDDTPSGEN2_I2CSTAT_ADRNACK | (uint8)CDDTPSGEN2_I2CSTAT_SDALOW )
#define CDDTPSGEN2_I2C_WR_STATUS_VALID   ((uint8)CDDTPSGEN2_I2CSTAT_BUSYERR | (uint8)CDDTPSGEN2_I2CSTAT_ADRNACK | (uint8)CDDTPSGEN2_I2CSTAT_SDALOW | (uint8)CDDTPSGEN2_I2CSTAT_DATNACK)

// definition of SYSCFG bits
#define CDDTPSGEN2_SEPTR   (uint8)(0x01U << 7U) // the 7th bit indicates separate Rx/Tx
#define CDDTPSGEN2_I2CEN   (uint8)(0x01U << 6U) // the 6th bit enables I2C
#define CDDTPSGEN2_ACKEN   (uint8)(0x01U << 5U) // the 5th bit enables the Ack response
#define CDDTPSGEN2_PSON    (uint8)(0x01U << 4U) // the 4th bit indicates the phase shift LED on
#define CDDTPSGEN2_CMWEN   (uint8)(0x01U << 3U) // the 3th bit enables the communications watchdog
#define CDDTPSGEN2_SYNCOEN (uint8)(0x01U << 2U) // the 2th bit enables the sync output
#define CDDTPSGEN2_SYNCPEN (uint8)(0x01U << 1U) // the 1th bit enables the pulse output
#define CDDTPSGEN2_PWR     (uint8)(0x01U << 0U) // the 0th bit indicates a power cycle

// definition of SLEWRATE bit pos
#define CDDTPSGEN2_SLEW_12_10 (6u)
#define CDDTPSGEN2_SLEW_09_07 (4u)
#define CDDTPSGEN2_SLEW_06_04 (2u)
#define CDDTPSGEN2_SLEW_03_01 (0u)

// definition of OVLMT bit pos
#define CDDTPSGEN2_OVLMT_12_10 (6u)
#define CDDTPSGEN2_OVLMT_09_07 (4u)
#define CDDTPSGEN2_OVLMT_06_04 (2u)
#define CDDTPSGEN2_OVLMT_03_01 (0u)

#define CDDTPSGEN2_SET_SLEWRATE_REG(slewRate)    ((uint8)(slewRate<<CDDTPSGEN2_SLEW_12_10)|(uint8)(slewRate<<CDDTPSGEN2_SLEW_09_07)|(uint8)(slewRate<<CDDTPSGEN2_SLEW_06_04)|(uint8)(slewRate<<CDDTPSGEN2_SLEW_03_01))
#define CDDTPSGEN2_SET_OVLMT_REG(overVoltLimit)  ((uint8)(overVoltLimit<<CDDTPSGEN2_OVLMT_12_10)|(uint8)(overVoltLimit<<CDDTPSGEN2_OVLMT_09_07)|(uint8)(overVoltLimit<<CDDTPSGEN2_OVLMT_06_04)|(uint8)(overVoltLimit<<CDDTPSGEN2_OVLMT_03_01))
// PWM Synchronization Type
#define CDDTPSGEN2_SYNC_HW_EXTERNAL_PIN    0u  // Exclusive Hardware - MCU External pin
#define CDDTPSGEN2_SYNC_HW_MASTER_SLAVE    1u  // Master Slave Topology Synchronization
#define CDDTPSGEN2_SYNC_SW_BROADCAST_CMD   2u  // Exclusive Sofware - Broadcast SSYNC Command

// PHASE registers computation
#define CDDTPSGEN2_PHASE_MAX          1023u    // Maximum value for PHASE shift register

#define CDDTPSGEN2_PHASE_DIV12        12u             // PHASE shift division for 12 leds in series
#define CDDTPSGEN2_PHASE_DIV9         9u              // PHASE shift division for 9 leds in series  
#define CDDTPSGEN2_PHASE_DIV6         6u              // PHASE shift division for 6 leds in series  
#define CDDTPSGEN2_PHASE_DIV3         3u              // PHASE shift division for 3 leds in series    


#define CDDTPSGEN2_PHASE_LOW10_MASK    0x03u           // Mask for lower bits1-0 of PHASE Register 
#define CDDTPSGEN2_WIDTH_LOW10_MASK    0x03u           // Mask for lower bits1-0 of WIDTH Register


// Configuration for one set (1,2,3,4,5,6,7,8,9,10,11,12) of twelve LEDs segments in series.
#define CDDTPSGEN2_CFG_1STRING_OF_12LEDS { \
    ( 0u ), \
    ( CDDTPSGEN2_PHASE_MAX * 1u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX * 2u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX * 3u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX * 4u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX * 5u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX * 6u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX * 7u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX * 8u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX * 9u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX *10u / CDDTPSGEN2_PHASE_DIV12), \
    ( CDDTPSGEN2_PHASE_MAX *11u / CDDTPSGEN2_PHASE_DIV12)  \
}


// Configuration for two strings (1,2,3,10,11,12 and 4,5,6,7,8,9) of six LEDs segments in series.
#define CDDTPSGEN2_CFG_2STRINGS_OF_6LEDS { \
    ( 0u), \
    ( CDDTPSGEN2_PHASE_MAX * 1u / CDDTPSGEN2_PHASE_DIV6), \
    ( CDDTPSGEN2_PHASE_MAX * 2u / CDDTPSGEN2_PHASE_DIV6), \
    ( 0u),  \
    ( CDDTPSGEN2_PHASE_MAX * 1u / CDDTPSGEN2_PHASE_DIV6), \
    ( CDDTPSGEN2_PHASE_MAX * 2u / CDDTPSGEN2_PHASE_DIV6), \
    ( CDDTPSGEN2_PHASE_MAX * 3u / CDDTPSGEN2_PHASE_DIV6), \
    ( CDDTPSGEN2_PHASE_MAX * 4u / CDDTPSGEN2_PHASE_DIV6), \
    ( CDDTPSGEN2_PHASE_MAX * 5u / CDDTPSGEN2_PHASE_DIV6), \
    ( CDDTPSGEN2_PHASE_MAX * 3u / CDDTPSGEN2_PHASE_DIV6), \
    ( CDDTPSGEN2_PHASE_MAX * 4u / CDDTPSGEN2_PHASE_DIV6), \
    ( CDDTPSGEN2_PHASE_MAX * 5u / CDDTPSGEN2_PHASE_DIV6)  \
}

// Configuration for two strings (1,2,3 and 4,5,6,7,8,9,10,11,12) of 3 and 9 LEDs segments in series.
#define CDD_LMM_CFG_2STRINGS_OF_3LEDS_AND_9LEDS { \
    ( 0u), \
    ( CDDTPSGEN2_PHASE_MAX * 1u / CDDTPSGEN2_PHASE_DIV3), \
    ( CDDTPSGEN2_PHASE_MAX * 2u / CDDTPSGEN2_PHASE_DIV3), \
    ( 0u),  \
    ( CDDTPSGEN2_PHASE_MAX * 1u / CDDTPSGEN2_PHASE_DIV9), \
    ( CDDTPSGEN2_PHASE_MAX * 2u / CDDTPSGEN2_PHASE_DIV9), \
    ( CDDTPSGEN2_PHASE_MAX * 3u / CDDTPSGEN2_PHASE_DIV9), \
    ( CDDTPSGEN2_PHASE_MAX * 4u / CDDTPSGEN2_PHASE_DIV9), \
    ( CDDTPSGEN2_PHASE_MAX * 5u / CDDTPSGEN2_PHASE_DIV9), \
    ( CDDTPSGEN2_PHASE_MAX * 6u / CDDTPSGEN2_PHASE_DIV9), \
    ( CDDTPSGEN2_PHASE_MAX * 7u / CDDTPSGEN2_PHASE_DIV9), \
    ( CDDTPSGEN2_PHASE_MAX * 8u / CDDTPSGEN2_PHASE_DIV9)  \
}



// Default Configuration for PHASE shift values - no phase shifts
#define CDDTPSGEN2_CFG_NO_PHASE_SHIFTING { \
    (0u), \
    (0u), \
    (0u), \
    (0u), \
    (0u), \
    (0u), \
    (0u), \
    (0u), \
    (0u), \
    (0u), \
    (0u), \
    (0u)  \
}


//=============================================================================
// Defines for Registers Addresses
//=============================================================================
//   MPHASE registers
#define CDDTPSGEN2_AddrMPHASE01L      0x00
#define CDDTPSGEN2_AddrMPHASE02L      0x01
#define CDDTPSGEN2_AddrMPHASE03L      0x02
#define CDDTPSGEN2_AddrMPHASE03_01H   0x03
#define CDDTPSGEN2_AddrMPHASE04L      0x04
#define CDDTPSGEN2_AddrMPHASE05L      0x05
#define CDDTPSGEN2_AddrMPHASE06L      0x06
#define CDDTPSGEN2_AddrMPHASE06_04H   0x07
#define CDDTPSGEN2_AddrMPHASE07L      0x08
#define CDDTPSGEN2_AddrMPHASE08L      0x09
#define CDDTPSGEN2_AddrMPHASE09L      0x0A
#define CDDTPSGEN2_AddrMPHASE09_07H   0x0B
#define CDDTPSGEN2_AddrMPHASE10L      0x0C
#define CDDTPSGEN2_AddrMPHASE11L      0x0D
#define CDDTPSGEN2_AddrMPHASE12L      0x0E
#define CDDTPSGEN2_AddrMPHASE12_10H   0x0F

//   MWIDTH registers
#define CDDTPSGEN2_AddrMWIDTH01L      0x10
#define CDDTPSGEN2_AddrMWIDTH02L      0x11
#define CDDTPSGEN2_AddrMWIDTH03L      0x12
#define CDDTPSGEN2_AddrMWIDTH03_01H   0x13
#define CDDTPSGEN2_AddrMWIDTH04L      0x14
#define CDDTPSGEN2_AddrMWIDTH05L      0x15
#define CDDTPSGEN2_AddrMWIDTH06L      0x16
#define CDDTPSGEN2_AddrMWIDTH06_04H   0x17
#define CDDTPSGEN2_AddrMWIDTH07L      0x18
#define CDDTPSGEN2_AddrMWIDTH08L      0x19
#define CDDTPSGEN2_AddrMWIDTH09L      0x1A
#define CDDTPSGEN2_AddrMWIDTH09_07H   0x1B
#define CDDTPSGEN2_AddrMWIDTH10L      0x1C
#define CDDTPSGEN2_AddrMWIDTH11L      0x1D
#define CDDTPSGEN2_AddrMWIDTH12L      0x1E
#define CDDTPSGEN2_AddrMWIDTH12_10H   0x1F

//   LPHASE registers
#define CDDTPSGEN2_AddrLPHASE01H      0x20
#define CDDTPSGEN2_AddrLPHASE02H      0x21
#define CDDTPSGEN2_AddrLPHASE03H      0x22
#define CDDTPSGEN2_AddrLPHASE04H      0x23
#define CDDTPSGEN2_AddrLPHASE05H      0x24
#define CDDTPSGEN2_AddrLPHASE06H      0x25
#define CDDTPSGEN2_AddrLPHASE07H      0x26
#define CDDTPSGEN2_AddrLPHASE08H      0x27
#define CDDTPSGEN2_AddrLPHASE09H      0x28
#define CDDTPSGEN2_AddrLPHASE10H      0x29
#define CDDTPSGEN2_AddrLPHASE11H      0x2A
#define CDDTPSGEN2_AddrLPHASE12H      0x2B
#define CDDTPSGEN2_AddrLPHASE03_01L   0x2C
#define CDDTPSGEN2_AddrLPHASE06_04L   0x2D
#define CDDTPSGEN2_AddrLPHASE09_07L   0x2E
#define CDDTPSGEN2_AddrLPHASE12_10L   0x2F

//   LWIDTH registers
#define CDDTPSGEN2_AddrLWIDTH01H      0x30
#define CDDTPSGEN2_AddrLWIDTH02H      0x31
#define CDDTPSGEN2_AddrLWIDTH03H      0x32
#define CDDTPSGEN2_AddrLWIDTH04H      0x33
#define CDDTPSGEN2_AddrLWIDTH05H      0x34
#define CDDTPSGEN2_AddrLWIDTH06H      0x35
#define CDDTPSGEN2_AddrLWIDTH07H      0x36
#define CDDTPSGEN2_AddrLWIDTH08H      0x37
#define CDDTPSGEN2_AddrLWIDTH09H      0x38
#define CDDTPSGEN2_AddrLWIDTH10H      0x39
#define CDDTPSGEN2_AddrLWIDTH11H      0x3A
#define CDDTPSGEN2_AddrLWIDTH12H      0x3B
#define CDDTPSGEN2_AddrLWIDTH03_01L   0x3C
#define CDDTPSGEN2_AddrLWIDTH06_04L   0x3D
#define CDDTPSGEN2_AddrLWIDTH09_07L   0x3E
#define CDDTPSGEN2_AddrLWIDTH12_10L   0x3F

// DPHASE and DWIDTH registers
#define CDDTPSGEN2_AddrDPHASE01L      0x40
#define CDDTPSGEN2_AddrDPHASE01H      0x41
#define CDDTPSGEN2_AddrDWIDTH01L      0x42
#define CDDTPSGEN2_AddrDWIDTH01H      0x43
#define CDDTPSGEN2_AddrDPHASE02L      0x44
#define CDDTPSGEN2_AddrDPHASE02H      0x45
#define CDDTPSGEN2_AddrDWIDTH02L      0x46
#define CDDTPSGEN2_AddrDWIDTH02H      0x47
#define CDDTPSGEN2_AddrDPHASE03L      0x48
#define CDDTPSGEN2_AddrDPHASE03H      0x49
#define CDDTPSGEN2_AddrDWIDTH03L      0x4A
#define CDDTPSGEN2_AddrDWIDTH03H      0x4B
#define CDDTPSGEN2_AddrDPHASE04L      0x4C
#define CDDTPSGEN2_AddrDPHASE04H      0x4D
#define CDDTPSGEN2_AddrDWIDTH04L      0x4E
#define CDDTPSGEN2_AddrDWIDTH04H      0x4F
#define CDDTPSGEN2_AddrDPHASE05L      0x50
#define CDDTPSGEN2_AddrDPHASE05H      0x51
#define CDDTPSGEN2_AddrDWIDTH05L      0x52
#define CDDTPSGEN2_AddrDWIDTH05H      0x53
#define CDDTPSGEN2_AddrDPHASE06L      0x54
#define CDDTPSGEN2_AddrDPHASE06H      0x55
#define CDDTPSGEN2_AddrDWIDTH06L      0x56
#define CDDTPSGEN2_AddrDWIDTH06H      0x57
#define CDDTPSGEN2_AddrDPHASE07L      0x58
#define CDDTPSGEN2_AddrDPHASE07H      0x59
#define CDDTPSGEN2_AddrDWIDTH07L      0x5A
#define CDDTPSGEN2_AddrDWIDTH07H      0x5B
#define CDDTPSGEN2_AddrDPHASE08L      0x5C
#define CDDTPSGEN2_AddrDPHASE08H      0x5D
#define CDDTPSGEN2_AddrDWIDTH08L      0x5E
#define CDDTPSGEN2_AddrDWIDTH08H      0x5F
#define CDDTPSGEN2_AddrDPHASE09L      0x60
#define CDDTPSGEN2_AddrDPHASE09H      0x61
#define CDDTPSGEN2_AddrDWIDTH09L      0x62
#define CDDTPSGEN2_AddrDWIDTH09H      0x63
#define CDDTPSGEN2_AddrDPHASE10L      0x64
#define CDDTPSGEN2_AddrDPHASE10H      0x65
#define CDDTPSGEN2_AddrDWIDTH10L      0x66
#define CDDTPSGEN2_AddrDWIDTH10H      0x67
#define CDDTPSGEN2_AddrDPHASE11L      0x68
#define CDDTPSGEN2_AddrDPHASE11H      0x69
#define CDDTPSGEN2_AddrDWIDTH11L      0x6A
#define CDDTPSGEN2_AddrDWIDTH11H      0x6B
#define CDDTPSGEN2_AddrDPHASE12L      0x6C
#define CDDTPSGEN2_AddrDPHASE12H      0x6D
#define CDDTPSGEN2_AddrDWIDTH12L      0x6E
#define CDDTPSGEN2_AddrDWIDTH12H      0x6F

#define CDDTPSGEN2_AddrSLEWRATE       0x70  // slew rate register
#define CDDTPSGEN2_AddrOVLMT          0x71  // overvoltage limit register
#define CDDTPSGEN2_AddrPARLED         0x72  // parallel LED string register

// default pulse width registers
#define CDDTPSGEN2_AddrDEFWIDTH02_01  0x73
#define CDDTPSGEN2_AddrDEFWIDTH04_03  0x74
#define CDDTPSGEN2_AddrDEFWIDTH06_05  0x75
#define CDDTPSGEN2_AddrDEFWIDTH08_07  0x76
#define CDDTPSGEN2_AddrDEFWIDTH10_09  0x77
#define CDDTPSGEN2_AddrDEFWIDTH12_11  0x78

#define CDDTPSGEN2_AddrSYSCFG         0x80 // system configuration register
#define CDDTPSGEN2_AddrCMWTAP         0x81 // communications watchdog timer tap point register
#define CDDTPSGEN2_AddrPWMTICK        0x82 // PWM tick period register
#define CDDTPSGEN2_AddrADCID          0x83 // ADC ID register
#define CDDTPSGEN2_AddrSOFTSYNC       0x84 // soft sync register

//   I2C registers
#define CDDTPSGEN2_AddrI2CTICK        0x90 // tick period register
#define CDDTPSGEN2_AddrI2CSLA         0x91 // slave address register
#define CDDTPSGEN2_AddrI2CRLEN        0x92 // read length register
#define CDDTPSGEN2_AddrI2CADR         0x93 // byte address register
#define CDDTPSGEN2_AddrI2CCTRL        0x94 // master control register
#define CDDTPSGEN2_AddrI2CDAT         0x95 // data register
#define CDDTPSGEN2_AddrI2CSTAT        0x96 // status register
#define CDDTPSGEN2_AddrI2CBMON        0x97 // bus monitor register

//  ADC registers
#define CDDTPSGEN2_AddrADC1           0xA0
#define CDDTPSGEN2_AddrADC2           0xA1

// Fault and CRC error registers
#define CDDTPSGEN2_AddrFAULTL         0xB0
#define CDDTPSGEN2_AddrFAULTH         0xB1
#define CDDTPSGEN2_AddrCERRCNT        0xB0

#define CDDTPSGEN2_AddrICID           0xFF // IC identification register for matrix manager family

//=============================================================================
// type definitions
//=============================================================================

typedef enum {
  SLOW_RATE = 0,
  MEDIUM_RATE = 1,
  FAST_RATE = 2,
  FAST_RATE_DEFAULT = 3
}tCddTpsGen2_SlewRate;

typedef enum {
  VTH_O1 = 0u,
  VTH_O2 = 1u,
  VTH_O3_DEFAULT = 2u,
  VTH_O3 = 3u
}tCddTpsGen2_OverVoltageLimit;


typedef enum {
  CDDTPSGEN2_PARLED_NONE = 0,             //S1=LED1-3 S2=LED4-6 S3=LED7-9 S4=LED10-12
  CDDTPSGEN2_PARLED_S1_P_S2 = 1,          //S1=LED1-3 S2=LED1-3 S3=LED7-9 S4=LED10-12
  CDDTPSGEN2_PARLED_S1_P_S2___S3_P_P4 = 2,//S1=LED1-3 S2=LED1-3 S3=LED7-9 S4=LED7-9
  CDDTPSGEN2_PARLED_S1_P_S2_P_S3_P_S4 = 3 //S1=LED1-3 S2=LED1-3 S3=LED1-3 S4=LED1-3
}tCddTpsGen2_ParalelLed;

typedef enum {  // Tap Point (Bit Number)
  CDDTPSGEN2_CMWTAP_BIT16 = 0,         //2^16 Clock Cycles
  CDDTPSGEN2_CMWTAP_BIT17 = 1,         //2^17 Clock Cycles
  CDDTPSGEN2_CMWTAP_BIT18 = 2,         //2^18 Clock Cycles
  CDDTPSGEN2_CMWTAP_BIT19 = 3,         //2^19 Clock Cycles
  CDDTPSGEN2_CMWTAP_BIT20 = 4,         //2^20 Clock Cycles
  CDDTPSGEN2_CMWTAP_BIT21_DEFAULT = 5, //2^21 Clock Cycles
  CDDTPSGEN2_CMWTAP_BIT22 = 6,         //2^22 Clock Cycles
  CDDTPSGEN2_CMWTAP_BIT23 = 7          //2^23 Clock Cycles
}tCddTpsGen2_ComWatchdogTimerTap;

typedef enum {  // Default Widths (4 bit resolution) at Communication Watchdog Timeout
  CDDTPSGEN2_DEF_WIDTH_00p00 = 0,      //  0.00%
  CDDTPSGEN2_DEF_WIDTH_06p25 = 1,      //  6.25%
  CDDTPSGEN2_DEF_WIDTH_12p50 = 2,      // 12.50%
  CDDTPSGEN2_DEF_WIDTH_18p75 = 3,      // 18.75%
  CDDTPSGEN2_DEF_WIDTH_25p00 = 4,      // 25.00%
  CDDTPSGEN2_DEF_WIDTH_31p25 = 5,      // 31.25%
  CDDTPSGEN2_DEF_WIDTH_37p50 = 6,      // 37.50%
  CDDTPSGEN2_DEF_WIDTH_43p75 = 7,      // 43.75%
  CDDTPSGEN2_DEF_WIDTH_50p00 = 8,      // 50.00%
  CDDTPSGEN2_DEF_WIDTH_56p25 = 9,      // 56.25%
  CDDTPSGEN2_DEF_WIDTH_62p50 = 10,     // 62.50%
  CDDTPSGEN2_DEF_WIDTH_68p75 = 11,     // 68.75%
  CDDTPSGEN2_DEF_WIDTH_75p00 = 12,     // 75.00%
  CDDTPSGEN2_DEF_WIDTH_81p25 = 13,     // 81.25%
  CDDTPSGEN2_DEF_WIDTH_87p50 = 14,     // 87.50%
  CDDTPSGEN2_DEF_WIDTH_100p0 = 15      //100.00%
}tCddTpsGen2_DefaultWidth;

// Two System Clock frequencies are supported
typedef enum {
  CDDTPSGEN2_CLK_FREQ_8MHz = 8u,   // 8Mhz
  CDDTPSGEN2_CLK_FREQ_16MHz = 16u  // 16MHz
} tCddTpsGen2_ClkFreq;

// table of the division factors for PWM tick
typedef enum {
  CDDTPSGEN2_CLK8_PWM_100HZ = 62u, // DIV1 = 1, DIV2 = 78, f ~ 100Hz,
  CDDTPSGEN2_CLK8_PWM_200HZ = 35U, // DIV1 = 1, DIV2 = 39, f ~ 200Hz,
  CDDTPSGEN2_CLK8_PWM_300HZ = 22U, // DIV1 = 1, DIV2 = 26, f ~ 300Hz,
  CDDTPSGEN2_CLK8_PWM_400HZ = 16U, // DIV1 = 1, DIV2 = 20, f ~ 400Hz,
  CDDTPSGEN2_CLK8_PWM_500HZ = 12U, // DIV1 = 1, DIV2 = 16, f ~ 500Hz, 
  CDDTPSGEN2_CLK8_PWM_600HZ = 9U,  // DIV1 = 1, DIV2 = 13, f ~ 600Hz
  CDDTPSGEN2_CLK8_PWM_700HZ = 7U,  // DIV1 = 1, DIV2 = 11, f ~ 700Hz,
  CDDTPSGEN2_CLK8_PWM_800HZ = 6U   // DIV1 = 1, DIV2 = 10, f ~ 800Hz,
} tCddTpsGen2_PwmFreq_SYSCLK8;

typedef enum {
  CDDTPSGEN2_CLK16_PWM_200HZ = 62U, // DIV1 = 1, DIV2 = 80, f ~ 200Hz,
  CDDTPSGEN2_CLK16_PWM_300HZ = 48U, // DIV1 = 1, DIV2 = 53, f ~ 300Hz,
  CDDTPSGEN2_CLK16_PWM_400HZ = 36U, // DIV1 = 1, DIV2 = 40, f ~ 400Hz,
  CDDTPSGEN2_CLK16_PWM_500HZ = 28U, // DIV1 = 1, DIV2 = 32, f ~ 500Hz, 
  CDDTPSGEN2_CLK16_PWM_600HZ = 23U, // DIV1 = 1, DIV2 = 27, f ~ 600Hz
  CDDTPSGEN2_CLK16_PWM_700HZ = 19U, // DIV1 = 1, DIV2 = 23, f ~ 700Hz,
  CDDTPSGEN2_CLK16_PWM_800HZ = 16U  // DIV1 = 1, DIV2 = 20, f ~ 800Hz,
} tCddTpsGen2_PwmFreq_SYSCLK16;


typedef enum {
  CDDTPSGEN2_ADCID_DEVID_MAPPING = 0u, // Up to  8 TPS92662 Devices on the Bus - Address range 0-7
  CDDTPSGEN2_ADCID_2BIT_MAPPING = 1u,  // Up to 16 TPS92662 Devices on the Bus - Address range 0-15 
  CDDTPSGEN2_ADCID_3BIT_MAPPING = 2u   // Up to 31 TPS92662 Devices on the Bus - Address range 0-30
}tCddTpsGen2_AdcId;

typedef enum {
  CDDTPSGEN2_DEV_ID00 = 0x20u,  // device with address  0
  CDDTPSGEN2_DEV_ID01 = 0x61u,  // device with address  1
  CDDTPSGEN2_DEV_ID02 = 0xE2u,  // device with address  2
  CDDTPSGEN2_DEV_ID03 = 0xA3u,  // device with address  3
  CDDTPSGEN2_DEV_ID04 = 0x64u,  // device with address  4
  CDDTPSGEN2_DEV_ID05 = 0x25u,  // device with address  5
  CDDTPSGEN2_DEV_ID06 = 0xA6u,  // device with address  6
  CDDTPSGEN2_DEV_ID07 = 0xE7u,  // device with address  7
  CDDTPSGEN2_DEV_ID08 = 0xA8u,  // device with address  8
  CDDTPSGEN2_DEV_ID09 = 0xE9u,  // device with address  9
  CDDTPSGEN2_DEV_ID10 = 0x6Au,  // device with address 10
  CDDTPSGEN2_DEV_ID11 = 0x2Bu,  // device with address 11
  CDDTPSGEN2_DEV_ID12 = 0xECu,  // device with address 12
  CDDTPSGEN2_DEV_ID13 = 0xADu,  // device with address 13
  CDDTPSGEN2_DEV_ID14 = 0x2Eu,  // device with address 14
  CDDTPSGEN2_DEV_ID15 = 0x6Fu,  // device with address 15
  CDDTPSGEN2_DEV_ID16 = 0xF0u,  // device with address 16
  CDDTPSGEN2_DEV_ID17 = 0xB1u,  // device with address 17
  CDDTPSGEN2_DEV_ID18 = 0x32u,  // device with address 18
  CDDTPSGEN2_DEV_ID19 = 0x73u,  // device with address 19
  CDDTPSGEN2_DEV_ID20 = 0xB4u,  // device with address 20
  CDDTPSGEN2_DEV_ID21 = 0xF5u,  // device with address 21
  CDDTPSGEN2_DEV_ID22 = 0x76u,  // device with address 22
  CDDTPSGEN2_DEV_ID23 = 0x37u,  // device with address 23
  CDDTPSGEN2_DEV_ID24 = 0x78u,  // device with address 24
  CDDTPSGEN2_DEV_ID25 = 0x39u,  // device with address 25
  CDDTPSGEN2_DEV_ID26 = 0xBAu,  // device with address 26
  CDDTPSGEN2_DEV_ID27 = 0xFBu,  // device with address 27
  CDDTPSGEN2_DEV_ID28 = 0x3Cu,  // device with address 28
  CDDTPSGEN2_DEV_ID29 = 0x7Du,  // device with address 29
  CDDTPSGEN2_DEV_ID30 = 0xFEu,  // device with address 30
  CDDTPSGEN2_BROADCAST = 0xBFu   // device with address 31
} CddTpsGen2_ucDevIdArray;


typedef enum {
  CDDTPSGEN2_I2C_CLK8_DIV20 = 0u,           // f_SCL = 400 kHz 
  CDDTPSGEN2_I2C_CLK8_DIV24 = 1u,           // f_SCL = 333 kHz 
  CDDTPSGEN2_I2C_CLK8_DIV28 = 2u,           // f_SCL = 286 kHz 
  CDDTPSGEN2_I2C_CLK8_DIV32 = 3u,           // f_SCL = 250 kHz 
  CDDTPSGEN2_I2C_CLK8_DIV36 = 4u,           // f_SCL = 222 kHz 
  CDDTPSGEN2_I2C_CLK8_DIV40_DEFAULT = 5u,   // f_SCL = 200 kHz 
  CDDTPSGEN2_I2C_CLK8_DIV80 = 6u,           // f_SCL = 100 kHz 
  CDDTPSGEN2_I2C_CLK8_DIV160 = 7u           // f_SCL =  50 kHz 	
} tCddTpsGen2_I2CTick_SYSCLK8;

typedef enum {
  CDDTPSGEN2_I2C_CLK16_DIV40_DEFAULT = 5u,   // f_SCL = 400 kHz 
  CDDTPSGEN2_I2C_CLK16_DIV80 = 6u,           // f_SCL = 200 kHz 
  CDDTPSGEN2_I2C_CLK16_DIV160 = 7u           // f_SCL = 100 kHz 	
} tCddTpsGen2_I2CTick_SYSCLK16;

//=============================================================================
// Type definition for Configuration and control registers
//=============================================================================

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)

//=============================================================================
// Type definition for LED PWM Phase - Shift and Width Registers
//=============================================================================

// ADDR 0x00
typedef struct tsCddTpsGen2_Bit_RegMPHASE01L
{
  uint8 biPHASE01 : 8;
}tsCddTpsGen2_Bit_RegMPHASE01L;

// ADDR 0x01
typedef struct tsCddTpsGen2_Bit_RegMPHASE02L
{
  uint8 biPHASE02 : 8;
}tsCddTpsGen2_Bit_RegMPHASE02L;

// ADDR 0x02
typedef struct tsCddTpsGen2_Bit_RegMPHASE03L
{
  uint8 biPHASE03 : 8;
}tsCddTpsGen2_Bit_RegMPHASE03L;

// ADDR 0x03
typedef struct tsCddTpsGen2_Bit_RegMPHASE03_01H
{
  uint8 biPHASE01 : 2;
  uint8 biPHASE02 : 2;
  uint8 biPHASE03 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegMPHASE03_01H;

// ADDR 0x04
typedef struct tsCddTpsGen2_Bit_RegMPHASE04L
{
  uint8 biPHASE04 : 8;
}tsCddTpsGen2_Bit_RegMPHASE04L;

// ADDR 0x05
typedef struct tsCddTpsGen2_Bit_RegMPHASE05L
{
  uint8 biPHASE05 : 8;
}tsCddTpsGen2_Bit_RegMPHASE05L;

// ADDR 0x06
typedef struct tsCddTpsGen2_Bit_RegMPHASE06L
{
  uint8 biPHASE06 : 8;
}tsCddTpsGen2_Bit_RegMPHASE06L;

// ADDR 0x07
typedef struct tsCddTpsGen2_Bit_RegMPHASE06_04H
{
  uint8 biPHASE04 : 2;
  uint8 biPHASE05 : 2;
  uint8 biPHASE06 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegMPHASE06_04H;

// ADDR 0x08
typedef struct tsCddTpsGen2_Bit_RegMPHASE07L
{
  uint8 biPHASE07 : 8;
}tsCddTpsGen2_Bit_RegMPHASE07L;

// ADDR 0x09
typedef struct tsCddTpsGen2_Bit_RegMPHASE08L
{
  uint8 biPHASE08 : 8;
}tsCddTpsGen2_Bit_RegMPHASE08L;

// ADDR 0x0A
typedef struct tsCddTpsGen2_Bit_RegMPHASE09L
{
  uint8 biPHASE09 : 8;
}tsCddTpsGen2_Bit_RegMPHASE09L;

// ADDR 0x0B
typedef struct tsCddTpsGen2_Bit_RegMPHASE09_07H
{
  uint8 biPHASE07 : 2;
  uint8 biPHASE08 : 2;
  uint8 biPHASE09 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegMPHASE09_07H;

// ADDR 0x0C
typedef struct tsCddTpsGen2_Bit_RegMPHASE10L
{
  uint8 biPHASE10 : 8;
}tsCddTpsGen2_Bit_RegMPHASE10L;

// ADDR 0x0D
typedef struct tsCddTpsGen2_Bit_RegMPHASE11L
{
  uint8 biPHASE11 : 8;
}tsCddTpsGen2_Bit_RegMPHASE11L;

// ADDR 0x0E
typedef struct tsCddTpsGen2_Bit_RegMPHASE12L
{
  uint8 biPHASE12 : 8;
}tsCddTpsGen2_Bit_RegMPHASE12L;

// ADDR 0x0F
typedef struct tsCddTpsGen2_Bit_RegMPHASE12_10H
{
  uint8 biPHASE10 : 2;
  uint8 biPHASE11 : 2;
  uint8 biPHASE12 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegMPHASE12_10H;

// ADDR 0x10
typedef struct tsCddTpsGen2_Bit_RegMWIDTH01L
{
  uint8 biWIDTH01 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH01L;

// ADDR 0x11
typedef struct tsCddTpsGen2_Bit_RegMWIDTH02L
{
  uint8 biWIDTH02 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH02L;

// ADDR 0x12
typedef struct tsCddTpsGen2_Bit_RegMWIDTH03L
{
  uint8 biWIDTH03 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH03L;

// ADDR 0x13
typedef struct tsCddTpsGen2_Bit_RegMWIDTH03_01H
{
  uint8 biWIDTH01 : 2;
  uint8 biWIDTH02 : 2;
  uint8 biWIDTH03 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegMWIDTH03_01H;

// ADDR 0x14
typedef struct tsCddTpsGen2_Bit_RegMWIDTH04L
{
  uint8 biWIDTH04 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH04L;

// ADDR 0x15
typedef struct tsCddTpsGen2_Bit_RegMWIDTH05L
{
  uint8 biWIDTH05 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH05L;

// ADDR 0x16
typedef struct tsCddTpsGen2_Bit_RegMWIDTH06L
{
  uint8 biWIDTH06 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH06L;

// ADDR 0x17
typedef struct tCdTps92662A_Bit_RegMWIDTH06_04H
{
  uint8 biWIDTH04 : 2;
  uint8 biWIDTH05 : 2;
  uint8 biWIDTH06 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegMWIDTH06_04H;

// ADDR 0x18
typedef struct tsCddTpsGen2_Bit_RegMWIDTH07L
{
  uint8 biWIDTH07 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH07L;

// ADDR 0x19
typedef struct tsCddTpsGen2_Bit_RegMWIDTH08L
{
  uint8 biWIDTH08 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH08L;

// ADDR 0x1A
typedef struct tsCddTpsGen2_Bit_RegMWIDTH09L
{
  uint8 biWIDTH09 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH09L;

// ADDR 0x1B
typedef struct tsCddTpsGen2_Bit_RegMWIDTH09_07H
{
  uint8 biWIDTH07 : 2;
  uint8 biWIDTH08 : 2;
  uint8 biWIDTH09 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegMWIDTH09_07H;

// ADDR 0x1C
typedef struct tsCddTpsGen2_Bit_RegMWIDTH10L
{
  uint8 biWIDTH10 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH10L;

// ADDR 0x1D
typedef struct tsCddTpsGen2_Bit_RegMWIDTH11L
{
  uint8 biWIDTH11 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH11L;

// ADDR 0x1E
typedef struct tsCddTpsGen2_Bit_RegMWIDTH12L
{
  uint8 biWIDTH12 : 8;
}tsCddTpsGen2_Bit_RegMWIDTH12L;

// ADDR 0x1F
typedef struct tsCddTpsGen2_Bit_RegMWIDTH12_10H
{
  uint8 biWIDTH10 : 2;
  uint8 biWIDTH11 : 2;
  uint8 biWIDTH12 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegMWIDTH12_10H;

// ADDR 0x20
typedef struct tsCddTpsGen2_Bit_RegLPHASE01H
{
  uint8 biPHASE01 : 8;
}tsCddTpsGen2_Bit_RegLPHASE01H;

// ADDR 0x21
typedef struct tsCddTpsGen2_Bit_RegLPHASE02H
{
  uint8 biPHASE02 : 8;
}tsCddTpsGen2_Bit_RegLPHASE02H;

// ADDR 0x22
typedef struct tsCddTpsGen2_Bit_RegLPHASE03H
{
  uint8 biPHASE03 : 8;
}tsCddTpsGen2_Bit_RegLPHASE03H;

// ADDR 0x23
typedef struct tsCddTpsGen2_Bit_RegLPHASE04H
{
  uint8 biPHASE04 : 8;
}tsCddTpsGen2_Bit_RegLPHASE04H;

// ADDR 0x24
typedef struct tsCddTpsGen2_Bit_RegLPHASE05H
{
  uint8 biPHASE05 : 8;
}tsCddTpsGen2_Bit_RegLPHASE05H;

// ADDR 0x25
typedef struct tsCddTpsGen2_Bit_RegLPHASE06H
{
  uint8 biPHASE06 : 8;
}tsCddTpsGen2_Bit_RegLPHASE06H;

// ADDR 0x26
typedef struct tsCddTpsGen2_Bit_RegLPHASE07H
{
  uint8 biPHASE07 : 8;
}tsCddTpsGen2_Bit_RegLPHASE07H;

// ADDR 0x27
typedef struct tsCddTpsGen2_Bit_RegLPHASE08H
{
  uint8 biPHASE08 : 8;
}tsCddTpsGen2_Bit_RegLPHASE08H;

// ADDR 0x28
typedef struct tsCddTpsGen2_Bit_RegLPHASE09H
{
  uint8 biPHASE09 : 8;
}tsCddTpsGen2_Bit_RegLPHASE09H;

// ADDR 0x29
typedef struct tsCddTpsGen2_Bit_RegLPHASE10H
{
  uint8 biPHASE10 : 8;
}tsCddTpsGen2_Bit_RegLPHASE10H;

// ADDR 0x2A
typedef struct tsCddTpsGen2_Bit_RegLPHASE11H
{
  uint8 biPHASE11 : 8;
}tsCddTpsGen2_Bit_RegLPHASE11H;

// ADDR 0x2B
typedef struct tsCddTpsGen2_Bit_RegLPHASE12H
{
  uint8 biPHASE12 : 8;
}tsCddTpsGen2_Bit_RegLPHASE12H;

// ADDR 0x2C
typedef struct tsCddTpsGen2_Bit_RegLPHASE03_01L
{
  uint8 biPHASE01 : 2;
  uint8 biPHASE02 : 2;
  uint8 biPHASE03 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegLPHASE03_01L;

// ADDR 0x2D
typedef struct tsCddTpsGen2_Bit_RegLPHASE06_04L
{
  uint8 biPHASE04 : 2;
  uint8 biPHASE05 : 2;
  uint8 biPHASE06 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegLPHASE06_04L;

// ADDR 0x2E
typedef struct tsCddTpsGen2_Bit_RegLPHASE09_07L
{
  uint8 biPHASE07 : 2;
  uint8 biPHASE08 : 2;
  uint8 biPHASE09 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegLPHASE09_07L;

// ADDR 0x2F
typedef struct tsCddTpsGen2_Bit_RegLPHASE12_10L
{
  uint8 biPHASE10 : 2;
  uint8 biPHASE11 : 2;
  uint8 biPHASE12 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegLPHASE12_10L;

// ADDR 0x30
typedef struct tsCddTpsGen2_Bit_RegLWIDTH01H
{
  uint8 biWIDTH01 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH01H;

// ADDR 0x31
typedef struct tsCddTpsGen2_Bit_RegLWIDTH02H
{
  uint8 biWIDTH02 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH02H;

// ADDR 0x32
typedef struct tsCddTpsGen2_Bit_RegLWIDTH03H
{
  uint8 biWIDTH03 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH03H;

// ADDR 0x33
typedef struct tsCddTpsGen2_Bit_RegLWIDTH04H
{
  uint8 biWIDTH04 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH04H;

// ADDR 0x34
typedef struct tsCddTpsGen2_Bit_RegLWIDTH05H
{
  uint8 biWIDTH05 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH05H;

// ADDR 0x35
typedef struct tsCddTpsGen2_Bit_RegLWIDTH06H
{
  uint8 biWIDTH06 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH06H;

// ADDR 0x36
typedef struct tsCddTpsGen2_Bit_RegLWIDTH07H
{
  uint8 biWIDTH07 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH07H;

// ADDR 0x37
typedef struct tsCddTpsGen2_Bit_RegLWIDTH08H
{
  uint8 biWIDTH08 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH08H;

// ADDR 0x38
typedef struct tsCddTpsGen2_Bit_RegLWIDTH09H
{
  uint8 biWIDTH09 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH09H;

// ADDR 0x39
typedef struct tsCddTpsGen2_Bit_RegLWIDTH10H
{
  uint8 biWIDTH10 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH10H;

// ADDR 0x3A
typedef struct tsCddTpsGen2_Bit_RegLWIDTH11H
{
  uint8 biWIDTH11 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH11H;

// ADDR 0x3B
typedef struct tsCddTpsGen2_Bit_RegLWIDTH12H
{
  uint8 biWIDTH12 : 8;
}tsCddTpsGen2_Bit_RegLWIDTH12H;

// ADDR 0x3C
typedef struct tsCddTpsGen2_Bit_RegLWIDTH03_01L
{
  uint8 biWIDTH01 : 2;
  uint8 biWIDTH02 : 2;
  uint8 biWIDTH03 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegLWIDTH03_01L;

// ADDR 0x3D
typedef struct tsCddTpsGen2_Bit_RegLWIDTH06_04L
{
  uint8 biWIDTH04 : 2;
  uint8 biWIDTH05 : 2;
  uint8 biWIDTH06 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegLWIDTH06_04L;

// ADDR 0x3E
typedef struct tsCddTpsGen2_Bit_RegLWIDTH09_07L
{
  uint8 biWIDTH07 : 2;
  uint8 biWIDTH08 : 2;
  uint8 biWIDTH09 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegLWIDTH09_07L;

// ADDR 0x3F
typedef struct tsCddTpsGen2_Bit_RegLWIDTH12_10L
{
  uint8 biWIDTH10 : 2;
  uint8 biWIDTH11 : 2;
  uint8 biWIDTH12 : 2;
  uint8 biUNUSED  : 2;
}tsCddTpsGen2_Bit_RegLWIDTH12_10L;

// ADDR 0x40
typedef struct tsCddTpsGen2_Bit_RegDPHASE01L
{
  uint8 biPHASE01 : 8;
}tsCddTpsGen2_Bit_RegDPHASE01L;

// ADDR 0x41
typedef struct tsCddTpsGen2_Bit_RegDPHASE01H
{
  uint8 biPHASE01 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE01H;

// ADDR 0x42
typedef struct tsCddTpsGen2_Bit_RegDWIDTH01L
{
  uint8 biWIDTH01 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH01L;

// ADDR 0x43
typedef struct tsCddTpsGen2_Bit_RegDWIDTH01H
{
  uint8 biWIDTH01 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH01H;

// ADDR 0x44
typedef struct tsCddTpsGen2_Bit_RegDPHASE02L
{
  uint8 biPHASE02 : 8;
}tsCddTpsGen2_Bit_RegDPHASE02L;

// ADDR 0x45
typedef struct tsCddTpsGen2_Bit_RegDPHASE02H
{
  uint8 biPHASE02 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE02H;

// ADDR 0x46
typedef struct tsCddTpsGen2_Bit_RegDWIDTH02L
{
  uint8 biWIDTH02 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH02L;

// ADDR 0x47
typedef struct tsCddTpsGen2_Bit_RegDWIDTH02H
{
  uint8 biWIDTH02 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH02H;

// ADDR 0x48
typedef struct tsCddTpsGen2_Bit_RegDPHASE03L
{
  uint8 biPHASE03 : 8;
}tsCddTpsGen2_Bit_RegDPHASE03L;

// ADDR 0x49
typedef struct tsCddTpsGen2_Bit_RegDPHASE03H
{
  uint8 biPHASE03 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE03H;

// ADDR 0x4A
typedef struct tsCddTpsGen2_Bit_RegDWIDTH03L
{
  uint8 biWIDTH03 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH03L;

// ADDR 0x4B
typedef struct tsCddTpsGen2_Bit_RegDWIDTH03H
{
  uint8 biWIDTH03 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH03H;

// ADDR 0x4C
typedef struct tsCddTpsGen2_Bit_RegDPHASE04L
{
  uint8 biPHASE04 : 8;
}tsCddTpsGen2_Bit_RegDPHASE04L;

// ADDR 0x4D
typedef struct tsCddTpsGen2_Bit_RegDPHASE04H
{
  uint8 biPHASE04 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE04H;

// ADDR 0x4E
typedef struct tsCddTpsGen2_Bit_RegDWIDTH04L
{
  uint8 biWIDTH04 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH04L;

// ADDR 0x4F
typedef struct tsCddTpsGen2_Bit_RegDWIDTH04H
{
  uint8 biWIDTH04 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH04H;

// ADDR 0x50
typedef struct tsCddTpsGen2_Bit_RegDPHASE05L
{
  uint8 biPHASE05 : 8;
}tsCddTpsGen2_Bit_RegDPHASE05L;

// ADDR 0x51
typedef struct tsCddTpsGen2_Bit_RegDPHASE05H
{
  uint8 biPHASE05 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE05H;

// ADDR 0x52
typedef struct tsCddTpsGen2_Bit_RegDWIDTH05L
{
  uint8 biWIDTH05 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH05L;

// ADDR 0x53
typedef struct tsCddTpsGen2_Bit_RegDWIDTH05H
{
  uint8 biWIDTH05 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH05H;

// ADDR 0x54
typedef struct tsCddTpsGen2_Bit_RegDPHASE06L
{
  uint8 biPHASE06 : 8;
}tsCddTpsGen2_Bit_RegDPHASE06L;

// ADDR 0x55
typedef struct tsCddTpsGen2_Bit_RegDPHASE06H
{
  uint8 biPHASE06 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE06H;

// ADDR 0x56
typedef struct tsCddTpsGen2_Bit_RegDWIDTH06L
{
  uint8 biWIDTH06 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH06L;

// ADDR 0x57
typedef struct tsCddTpsGen2_Bit_RegDWIDTH06H
{
  uint8 biWIDTH06 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH06H;

// ADDR 0x58
typedef struct tsCddTpsGen2_Bit_RegDPHASE07L
{
  uint8 biPHASE07 : 8;
}tsCddTpsGen2_Bit_RegDPHASE07L;

// ADDR 0x59
typedef struct tsCddTpsGen2_Bit_RegDPHASE07H
{
  uint8 biPHASE07 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE07H;

// ADDR 0x5A
typedef struct tsCddTpsGen2_Bit_RegDWIDTH07L
{
  uint8 biWIDTH07 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH07L;

// ADDR 0x5B
typedef struct tsCddTpsGen2_Bit_RegDWIDTH07H
{
  uint8 biWIDTH07 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH07H;

// ADDR 0x5C
typedef struct tsCddTpsGen2_Bit_RegDPHASE08L
{
  uint8 biPHASE08 : 8;
}tsCddTpsGen2_Bit_RegDPHASE08L;

// ADDR 0x5D
typedef struct tsCddTpsGen2_Bit_RegDPHASE08H
{
  uint8 biPHASE08 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE08H;

// ADDR 0x5E
typedef struct tsCddTpsGen2_Bit_RegDWIDTH08L
{
  uint8 biWIDTH08 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH08L;

// ADDR 0x5F
typedef struct tsCddTpsGen2_Bit_RegDWIDTH08H
{
  uint8 biWIDTH08 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH08H;

// ADDR 0x60
typedef struct tsCddTpsGen2_Bit_RegDPHASE09L
{
  uint8 biPHASE09 : 8;
}tsCddTpsGen2_Bit_RegDPHASE09L;

// ADDR 0x61
typedef struct tsCddTpsGen2_Bit_RegDPHASE09H
{
  uint8 biPHASE09 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE09H;

// ADDR 0x62
typedef struct tsCddTpsGen2_Bit_RegDWIDTH09L
{
  uint8 biWIDTH09 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH09L;

// ADDR 0x63
typedef struct tsCddTpsGen2_Bit_RegDWIDTH09H
{
  uint8 biWIDTH09 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH09H;

// ADDR 0x64
typedef struct tsCddTpsGen2_Bit_RegDPHASE10L
{
  uint8 biPHASE10 : 8;
}tsCddTpsGen2_Bit_RegDPHASE10L;

// ADDR 0x65
typedef struct tsCddTpsGen2_Bit_RegDPHASE10H
{
  uint8 biPHASE10 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE10H;

// ADDR 0x66
typedef struct tsCddTpsGen2_Bit_RegDWIDTH10L
{
  uint8 biWIDTH10 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH10L;

// ADDR 0x67
typedef struct tsCddTpsGen2_Bit_RegDWIDTH10H
{
  uint8 biWIDTH10 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH10H;

// ADDR 0x68
typedef struct tsCddTpsGen2_Bit_RegDPHASE11L
{
  uint8 biPHASE11 : 8;
}tsCddTpsGen2_Bit_RegDPHASE11L;

// ADDR 0x69
typedef struct tsCddTpsGen2_Bit_RegDPHASE11H
{
  uint8 biPHASE11 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE11H;

// ADDR 0x6A
typedef struct tsCddTpsGen2_Bit_RegDWIDTH11L
{
  uint8 biWIDTH11 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH11L;

// ADDR 0x6B
typedef struct tsCddTpsGen2_Bit_RegDWIDTH11H
{
  uint8 biWIDTH11 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH11H;

// ADDR 0x6C
typedef struct tsCddTpsGen2_Bit_RegDPHASE12L
{
  uint8 biPHASE12 : 8;
}tsCddTpsGen2_Bit_RegDPHASE12L;

// ADDR 0x6D
typedef struct tsCddTpsGen2_Bit_RegDPHASE12H
{
  uint8 biPHASE12 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDPHASE12H;

// ADDR 0x6E
typedef struct tsCddTpsGen2_Bit_RegDWIDTH12L
{
  uint8 biWIDTH12 : 8;
}tsCddTpsGen2_Bit_RegDWIDTH12L;

// ADDR 0x6F
typedef struct tsCddTpsGen2_Bit_RegDWIDTH12H
{
  uint8 biWIDTH12 : 2;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegDWIDTH12H;

//=============================================================================
// Type definition for Slew Rate Registers
//=============================================================================

// ADDR 0x70
typedef struct tsCddTpsGen2_Bit_RegSLEWRATE
{
  uint8 biSLEW_03_01 : 2;
  uint8 biSLEW_06_04 : 2;
  uint8 biSLEW_09_07 : 2;
  uint8 biSLEW_12_10 : 2;
}tsCddTpsGen2_Bit_RegSLEWRATE;

//=============================================================================
// Type definition for Over Voltage Limit Registers
//=============================================================================

// ADDR 0x71
typedef struct tsCddTpsGen2_Bit_RegOVLMT
{
  uint8 biOVLMT_03_01 : 2;
  uint8 biOVLMT_06_04 : 2;
  uint8 biOVLMT_09_07 : 2;
  uint8 biOVLMT_12_10 : 2;
}tsCddTpsGen2_Bit_RegOVLMT;

//=============================================================================
// Type definition for Parallel Led String Registers
//=============================================================================

// ADDR 0x72
typedef struct tsCddTpsGen2_Bit_RegPARLED
{
  uint8 biPARLED : 2;
  uint8 biUNUSED : 6;
}tsCddTpsGen2_Bit_RegPARLED;

//=============================================================================
// Type definition for Default Pulse Width Registers
//=============================================================================

// ADDR 0x73
typedef struct tsCddTpsGen2_Bit_RegDEFWIDTH02_01
{
  uint8 biDEFWIDTH01 : 4;
  uint8 biDEFWIDTH02 : 4;
}tsCddTpsGen2_Bit_RegDEFWIDTH02_01;

// ADDR 0x74
typedef struct tsCddTpsGen2_Bit_RegDEFWIDTH04_03
{
  uint8 biDEFWIDTH03 : 4;
  uint8 biDEFWIDTH04 : 4;
}tsCddTpsGen2_Bit_RegDEFWIDTH04_03;

// ADDR 0x75
typedef struct tsCddTpsGen2_Bit_RegDEFWIDTH06_05
{
  uint8 biDEFWIDTH05 : 4;
  uint8 biDEFWIDTH06 : 4;
}tsCddTpsGen2_Bit_RegDEFWIDTH06_05;

// ADDR 0x76
typedef struct tsCddTpsGen2_Bit_RegDEFWIDTH08_07
{
  uint8 biDEFWIDTH07 : 4;
  uint8 biDEFWIDTH08 : 4;
}tsCddTpsGen2_Bit_RegDEFWIDTH08_07;

// ADDR 0x77
typedef struct tsCddTpsGen2_Bit_RegDEFWIDTH10_09
{
  uint8 biDEFWIDTH09 : 4;
  uint8 biDEFWIDTH10 : 4;
}tsCddTpsGen2_Bit_RegDEFWIDTH10_09;

// ADDR 0x78
typedef struct tsCddTpsGen2_Bit_RegDEFWIDTH12_11
{
  uint8 biDEFWIDTH11 : 4;
  uint8 biDEFWIDTH12 : 4;
}tsCddTpsGen2_Bit_RegDEFWIDTH12_11;

//=============================================================================
// Type definition for System Configuration Register
//=============================================================================

// ADDR 0x80
typedef struct tsCddTpsGen2_Bit_RegSYSCFG
{
  uint8 biPWR     : 1;
  uint8 biSYNCPEN : 1;
  uint8 biSYNCOEN : 1;
  uint8 biCMWEN   : 1;
  uint8 biPSON    : 1;
  uint8 biACKEN   : 1;
  uint8 biI2CEN   : 1;
  uint8 biSEPTR   : 1;
}tsCddTpsGen2_Bit_RegSYSCFG;

//=============================================================================
// Type definition for Communications Watchdog Timer Tap Point Register
//=============================================================================

// ADDR 0x81
typedef struct tsCddTpsGen2_Bit_RegCMWTAP
{
  uint8 biCMWTAP  : 3;
  uint8 biUNUSED  : 5;
}tsCddTpsGen2_Bit_RegCMWTAP;

//=============================================================================
// Type definition for PWM Tick Period Register
//=============================================================================

// ADDR 0x82
typedef struct tsCddTpsGen2_Bit_RegPWMTICK
{
  uint8 biPTCNT  : 6;
  uint8 biPTBASE : 2;
}tsCddTpsGen2_Bit_RegPWMTICK;

//=============================================================================
// Type definition for ADC ID Register
//=============================================================================

// ADDR 0x83
typedef struct tsCddTpsGen2_Bit_RegADCID
{
  uint8 biADCID  : 2;
  uint8 biUNUSED : 6;
}tsCddTpsGen2_Bit_RegADCID;

//=============================================================================
// Type definition for SOFTSYNC Register
//=============================================================================

// ADDR 0x84
typedef struct tsCddTpsGen2_Bit_RegSOFTSYNC
{
  uint8 biSSYNC  : 1;
  uint8 biUNUSED : 7;
}tsCddTpsGen2_Bit_RegSOFTSYNC;

//=============================================================================
// Type definition for I2C Tick Period Register
//=============================================================================

// ADDR 0x90
typedef struct tsCddTpsGen2_Bit_RegI2CTICK
{
  uint8 biI2CTICK : 3;
  uint8 biUNUSED  : 5;
}tsCddTpsGen2_Bit_RegI2CTICK;

//=============================================================================
// Type definition for I2C Slave Address Register
//=============================================================================

// ADDR 0x91
typedef struct tsCddTpsGen2_Bit_RegI2CSLA
{
  uint8 biUNUSED  : 1;
  uint8 biSA      : 7;
}tsCddTpsGen2_Bit_RegI2CSLA;

//=============================================================================
// Type definition for I2C Read Length Register
//=============================================================================

// ADDR 0x92
typedef struct tsCddTpsGen2_Bit_RegI2CRLEN
{
  uint8 biI2CRLEN : 8;
}tsCddTpsGen2_Bit_RegI2CRLEN;

//=============================================================================
// Type definition for I2C Byte Address Register
//=============================================================================

// ADDR 0x93
typedef struct tsCddTpsGen2_Bit_RegI2CADR
{
  uint8 biI2CADR : 8;
}tsCddTpsGen2_Bit_RegI2CADR;

//=============================================================================
// Type definition for I2C Master Control Register
//=============================================================================

// ADDR 0x94
typedef struct tsCddTpsGen2_Bit_RegI2CCTRL
{
  uint8 biRST     : 1;
  uint8 biRD      : 1;
  uint8 biSTART   : 1;
  uint8 biNOADR   : 1;
  uint8 biUNUSED  : 4;
}tsCddTpsGen2_Bit_RegI2CCTRL;

//=============================================================================
// Type definition for I2C Data Register
//=============================================================================

// ADDR 0x95
typedef struct tsCddTpsGen2_Bit_RegI2CDAT
{
  uint8 biI2CDAT : 8;
}tsCddTpsGen2_Bit_RegI2CDAT;

//=============================================================================
// Type definition for I2C Status Register
//=============================================================================

// ADDR 0x96
typedef struct tsCddTpsGen2_Bit_RegI2CSTAT
{
  uint8 biBUSY      : 1;
  uint8 biSDALOW    : 1;
  uint8 biDATNACK   : 1;
  uint8 biADRNACK   : 1;
  uint8 biSLANACK   : 1;
  uint8 biBUSYERR   : 1;
  uint8 biRFF       : 1;
  uint8 biRFE       : 1;
}tsCddTpsGen2_Bit_RegI2CSTAT;

//=============================================================================
// Type definition for I2C Bus Monitor Register
//=============================================================================

// ADDR 0x97
typedef struct tsCddTpsGen2_Bit_RegI2CBMON
{
  uint8 biSCL     : 1;
  uint8 biSDA     : 1;
  uint8 biUNUSED  : 6;
}tsCddTpsGen2_Bit_RegI2CBMON;

//=============================================================================
// Type definition for ADC Registers
//=============================================================================

// ADDR 0xA0
typedef struct tsCddTpsGen2_Bit_RegADC1
{
  uint8 biADC1     : 8;
}tsCddTpsGen2_Bit_RegADC1;

// ADDR 0xA1
typedef struct tsCddTpsGen2_Bit_RegADC2
{
  uint8 biADC2     : 8;
}tsCddTpsGen2_Bit_RegADC2;

//=============================================================================
// Type definition for Fault and CRC Error Count Registers
//=============================================================================

// ADDR 0xB0
typedef struct tsCddTpsGen2_Bit_RegFAULTL
{
  uint8 biFAULT     : 8;
}tsCddTpsGen2_Bit_RegFAULTL;

// ADDR 0xB1
typedef struct tsCddTpsGen2_Bit_RegFAULTH
{
  uint8 biFAULT     : 4;
  uint8 biUNUSED    : 4;
}tsCddTpsGen2_Bit_RegFAULTH;

// ADDR 0xB2
typedef struct tsCddTpsGen2_Bit_RegCERRCNT
{
  uint8 biCERRCNT   : 8;
}tsCddTpsGen2_Bit_RegCERRCNT;

//=============================================================================
// Type definition for IC Identification Register
//=============================================================================

// ADDR 0xFF
typedef struct tsCddTpsGen2_Bit_RegICID
{
  uint8 biICID     : 8;
}tsCddTpsGen2_Bit_RegICID;


#else
#error CPU_BYTE_ORDER == HIGH_BYTE_FIRST not supported
#endif  //(CPU_BYTE_ORDER == LOW_BYTE_FIRST)


// R/W Registers
typedef union tuCddTpsGen2_RegMPHASE01L      { tsCddTpsGen2_Bit_RegMPHASE01L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE01L;
typedef union tuCddTpsGen2_RegMPHASE02L      { tsCddTpsGen2_Bit_RegMPHASE02L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE02L;
typedef union tuCddTpsGen2_RegMPHASE03L      { tsCddTpsGen2_Bit_RegMPHASE03L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE03L;
typedef union tuCddTpsGen2_RegMPHASE03_01H   { tsCddTpsGen2_Bit_RegMPHASE03_01H   Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE03_01H;
typedef union tuCddTpsGen2_RegMPHASE04L      { tsCddTpsGen2_Bit_RegMPHASE04L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE04L;
typedef union tuCddTpsGen2_RegMPHASE05L      { tsCddTpsGen2_Bit_RegMPHASE05L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE05L;
typedef union tuCddTpsGen2_RegMPHASE06L      { tsCddTpsGen2_Bit_RegMPHASE06L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE06L;
typedef union tuCddTpsGen2_RegMPHASE06_04H   { tsCddTpsGen2_Bit_RegMPHASE06_04H   Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE06_04H;
typedef union tuCddTpsGen2_RegMPHASE07L      { tsCddTpsGen2_Bit_RegMPHASE07L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE07L;
typedef union tuCddTpsGen2_RegMPHASE08L      { tsCddTpsGen2_Bit_RegMPHASE08L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE08L;
typedef union tuCddTpsGen2_RegMPHASE09L      { tsCddTpsGen2_Bit_RegMPHASE09L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE09L;
typedef union tuCddTpsGen2_RegMPHASE09_07H   { tsCddTpsGen2_Bit_RegMPHASE09_07H   Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE09_07H;
typedef union tuCddTpsGen2_RegMPHASE10L      { tsCddTpsGen2_Bit_RegMPHASE10L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE10L;
typedef union tuCddTpsGen2_RegMPHASE11L      { tsCddTpsGen2_Bit_RegMPHASE11L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE11L;
typedef union tuCddTpsGen2_RegMPHASE12L      { tsCddTpsGen2_Bit_RegMPHASE12L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE12L;
typedef union tuCddTpsGen2_RegMPHASE12_10H   { tsCddTpsGen2_Bit_RegMPHASE12_10H   Bit; uint8 ucRaw; } tuCddTpsGen2_RegMPHASE12_10H;
typedef union tuCddTpsGen2_RegMWIDTH01L      { tsCddTpsGen2_Bit_RegMWIDTH01L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH01L;
typedef union tuCddTpsGen2_RegMWIDTH02L      { tsCddTpsGen2_Bit_RegMWIDTH02L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH02L;
typedef union tuCddTpsGen2_RegMWIDTH03L      { tsCddTpsGen2_Bit_RegMWIDTH03L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH03L;
typedef union tuCddTpsGen2_RegMWIDTH03_01H   { tsCddTpsGen2_Bit_RegMWIDTH03_01H   Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH03_01H;
typedef union tuCddTpsGen2_RegMWIDTH04L      { tsCddTpsGen2_Bit_RegMWIDTH04L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH04L;
typedef union tuCddTpsGen2_RegMWIDTH05L      { tsCddTpsGen2_Bit_RegMWIDTH05L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH05L;
typedef union tuCddTpsGen2_RegMWIDTH06L      { tsCddTpsGen2_Bit_RegMWIDTH06L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH06L;
typedef union tuCddTpsGen2_RegMWIDTH06_04H   { tsCddTpsGen2_Bit_RegMWIDTH06_04H   Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH06_04H;
typedef union tuCddTpsGen2_RegMWIDTH07L      { tsCddTpsGen2_Bit_RegMWIDTH07L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH07L;
typedef union tuCddTpsGen2_RegMWIDTH08L      { tsCddTpsGen2_Bit_RegMWIDTH08L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH08L;
typedef union tuCddTpsGen2_RegMWIDTH09L      { tsCddTpsGen2_Bit_RegMWIDTH09L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH09L;
typedef union tuCddTpsGen2_RegMWIDTH09_07H   { tsCddTpsGen2_Bit_RegMWIDTH09_07H   Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH09_07H;
typedef union tuCddTpsGen2_RegMWIDTH10L      { tsCddTpsGen2_Bit_RegMWIDTH10L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH10L;
typedef union tuCddTpsGen2_RegMWIDTH11L      { tsCddTpsGen2_Bit_RegMWIDTH11L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH11L;
typedef union tuCddTpsGen2_RegMWIDTH12L      { tsCddTpsGen2_Bit_RegMWIDTH12L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH12L;
typedef union tuCddTpsGen2_RegMWIDTH12_10H   { tsCddTpsGen2_Bit_RegMWIDTH12_10H   Bit; uint8 ucRaw; } tuCddTpsGen2_RegMWIDTH12_10H;
typedef union tuCddTpsGen2_RegLPHASE01H      { tsCddTpsGen2_Bit_RegLPHASE01H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE01H;
typedef union tuCddTpsGen2_RegLPHASE02H      { tsCddTpsGen2_Bit_RegLPHASE02H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE02H;
typedef union tuCddTpsGen2_RegLPHASE03H      { tsCddTpsGen2_Bit_RegLPHASE03H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE03H;
typedef union tuCddTpsGen2_RegLPHASE04H      { tsCddTpsGen2_Bit_RegLPHASE04H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE04H;
typedef union tuCddTpsGen2_RegLPHASE05H      { tsCddTpsGen2_Bit_RegLPHASE05H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE05H;
typedef union tuCddTpsGen2_RegLPHASE06H      { tsCddTpsGen2_Bit_RegLPHASE06H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE06H;
typedef union tuCddTpsGen2_RegLPHASE07H      { tsCddTpsGen2_Bit_RegLPHASE07H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE07H;
typedef union tuCddTpsGen2_RegLPHASE08H      { tsCddTpsGen2_Bit_RegLPHASE08H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE08H;
typedef union tuCddTpsGen2_RegLPHASE09H      { tsCddTpsGen2_Bit_RegLPHASE09H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE09H;
typedef union tuCddTpsGen2_RegLPHASE10H      { tsCddTpsGen2_Bit_RegLPHASE10H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE10H;
typedef union tuCddTpsGen2_RegLPHASE11H      { tsCddTpsGen2_Bit_RegLPHASE11H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE11H;
typedef union tuCddTpsGen2_RegLPHASE12H      { tsCddTpsGen2_Bit_RegLPHASE12H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE12H;
typedef union tuCddTpsGen2_RegLPHASE03_01L   { tsCddTpsGen2_Bit_RegLPHASE03_01L   Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE03_01L;
typedef union tuCddTpsGen2_RegLPHASE06_04L   { tsCddTpsGen2_Bit_RegLPHASE06_04L   Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE06_04L;
typedef union tuCddTpsGen2_RegLPHASE09_07L   { tsCddTpsGen2_Bit_RegLPHASE09_07L   Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE09_07L;
typedef union tuCddTpsGen2_RegLPHASE12_10L   { tsCddTpsGen2_Bit_RegLPHASE12_10L   Bit; uint8 ucRaw; } tuCddTpsGen2_RegLPHASE12_10L;
typedef union tuCddTpsGen2_RegLWIDTH01H      { tsCddTpsGen2_Bit_RegLWIDTH01H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH01H;
typedef union tuCddTpsGen2_RegLWIDTH02H      { tsCddTpsGen2_Bit_RegLWIDTH02H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH02H;
typedef union tuCddTpsGen2_RegLWIDTH03H      { tsCddTpsGen2_Bit_RegLWIDTH03H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH03H;
typedef union tuCddTpsGen2_RegLWIDTH04H      { tsCddTpsGen2_Bit_RegLWIDTH04H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH04H;
typedef union tuCddTpsGen2_RegLWIDTH05H      { tsCddTpsGen2_Bit_RegLWIDTH05H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH05H;
typedef union tuCddTpsGen2_RegLWIDTH06H      { tsCddTpsGen2_Bit_RegLWIDTH06H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH06H;
typedef union tuCddTpsGen2_RegLWIDTH07H      { tsCddTpsGen2_Bit_RegLWIDTH07H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH07H;
typedef union tuCddTpsGen2_RegLWIDTH08H      { tsCddTpsGen2_Bit_RegLWIDTH08H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH08H;
typedef union tuCddTpsGen2_RegLWIDTH09H      { tsCddTpsGen2_Bit_RegLWIDTH09H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH09H;
typedef union tuCddTpsGen2_RegLWIDTH10H      { tsCddTpsGen2_Bit_RegLWIDTH10H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH10H;
typedef union tuCddTpsGen2_RegLWIDTH11H      { tsCddTpsGen2_Bit_RegLWIDTH11H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH11H;
typedef union tuCddTpsGen2_RegLWIDTH12H      { tsCddTpsGen2_Bit_RegLWIDTH12H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH12H;
typedef union tuCddTpsGen2_RegLWIDTH03_01L   { tsCddTpsGen2_Bit_RegLWIDTH03_01L   Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH03_01L;
typedef union tuCddTpsGen2_RegLWIDTH06_04L   { tsCddTpsGen2_Bit_RegLWIDTH06_04L   Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH06_04L;
typedef union tuCddTpsGen2_RegLWIDTH09_07L   { tsCddTpsGen2_Bit_RegLWIDTH09_07L   Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH09_07L;
typedef union tuCddTpsGen2_RegLWIDTH12_10L   { tsCddTpsGen2_Bit_RegLWIDTH12_10L   Bit; uint8 ucRaw; } tuCddTpsGen2_RegLWIDTH12_10L;
typedef union tuCddTpsGen2_RegDPHASE01L      { tsCddTpsGen2_Bit_RegDPHASE01L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE01L;
typedef union tuCddTpsGen2_RegDPHASE01H      { tsCddTpsGen2_Bit_RegDPHASE01H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE01H;
typedef union tuCddTpsGen2_RegDWIDTH01L      { tsCddTpsGen2_Bit_RegDWIDTH01L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH01L;
typedef union tuCddTpsGen2_RegDWIDTH01H      { tsCddTpsGen2_Bit_RegDWIDTH01H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH01H;
typedef union tuCddTpsGen2_RegDPHASE02L      { tsCddTpsGen2_Bit_RegDPHASE02L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE02L;
typedef union tuCddTpsGen2_RegDPHASE02H      { tsCddTpsGen2_Bit_RegDPHASE02H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE02H;
typedef union tuCddTpsGen2_RegDWIDTH02L      { tsCddTpsGen2_Bit_RegDWIDTH02L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH02L;
typedef union tuCddTpsGen2_RegDWIDTH02H      { tsCddTpsGen2_Bit_RegDWIDTH02H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH02H;
typedef union tuCddTpsGen2_RegDPHASE03L      { tsCddTpsGen2_Bit_RegDPHASE03L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE03L;
typedef union tuCddTpsGen2_RegDPHASE03H      { tsCddTpsGen2_Bit_RegDPHASE03H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE03H;
typedef union tuCddTpsGen2_RegDWIDTH03L      { tsCddTpsGen2_Bit_RegDWIDTH03L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH03L;
typedef union tuCddTpsGen2_RegDWIDTH03H      { tsCddTpsGen2_Bit_RegDWIDTH03H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH03H;
typedef union tuCddTpsGen2_RegDPHASE04L      { tsCddTpsGen2_Bit_RegDPHASE04L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE04L;
typedef union tuCddTpsGen2_RegDPHASE04H      { tsCddTpsGen2_Bit_RegDPHASE04H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE04H;
typedef union tuCddTpsGen2_RegDWIDTH04L      { tsCddTpsGen2_Bit_RegDWIDTH04L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH04L;
typedef union tuCddTpsGen2_RegDWIDTH04H      { tsCddTpsGen2_Bit_RegDWIDTH04H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH04H;
typedef union tuCddTpsGen2_RegDPHASE05L      { tsCddTpsGen2_Bit_RegDPHASE05L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE05L;
typedef union tuCddTpsGen2_RegDPHASE05H      { tsCddTpsGen2_Bit_RegDPHASE05H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE05H;
typedef union tuCddTpsGen2_RegDWIDTH05L      { tsCddTpsGen2_Bit_RegDWIDTH05L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH05L;
typedef union tuCddTpsGen2_RegDWIDTH05H      { tsCddTpsGen2_Bit_RegDWIDTH05H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH05H;
typedef union tuCddTpsGen2_RegDPHASE06L      { tsCddTpsGen2_Bit_RegDPHASE06L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE06L;
typedef union tuCddTpsGen2_RegDPHASE06H      { tsCddTpsGen2_Bit_RegDPHASE06H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE06H;
typedef union tuCddTpsGen2_RegDWIDTH06L      { tsCddTpsGen2_Bit_RegDWIDTH06L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH06L;
typedef union tuCddTpsGen2_RegDWIDTH06H      { tsCddTpsGen2_Bit_RegDWIDTH06H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH06H;
typedef union tuCddTpsGen2_RegDPHASE07L      { tsCddTpsGen2_Bit_RegDPHASE07L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE07L;
typedef union tuCddTpsGen2_RegDPHASE07H      { tsCddTpsGen2_Bit_RegDPHASE07H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE07H;
typedef union tuCddTpsGen2_RegDWIDTH07L      { tsCddTpsGen2_Bit_RegDWIDTH07L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH07L;
typedef union tuCddTpsGen2_RegDWIDTH07H      { tsCddTpsGen2_Bit_RegDWIDTH07H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH07H;
typedef union tuCddTpsGen2_RegDPHASE08L      { tsCddTpsGen2_Bit_RegDPHASE08L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE08L;
typedef union tuCddTpsGen2_RegDPHASE08H      { tsCddTpsGen2_Bit_RegDPHASE08H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE08H;
typedef union tuCddTpsGen2_RegDWIDTH08L      { tsCddTpsGen2_Bit_RegDWIDTH08L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH08L;
typedef union tuCddTpsGen2_RegDWIDTH08H      { tsCddTpsGen2_Bit_RegDWIDTH08H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH08H;
typedef union tuCddTpsGen2_RegDPHASE09L      { tsCddTpsGen2_Bit_RegDPHASE09L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE09L;
typedef union tuCddTpsGen2_RegDPHASE09H      { tsCddTpsGen2_Bit_RegDPHASE09H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE09H;
typedef union tuCddTpsGen2_RegDWIDTH09L      { tsCddTpsGen2_Bit_RegDWIDTH09L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH09L;
typedef union tuCddTpsGen2_RegDWIDTH09H      { tsCddTpsGen2_Bit_RegDWIDTH09H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH09H;
typedef union tuCddTpsGen2_RegDPHASE10L      { tsCddTpsGen2_Bit_RegDPHASE10L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE10L;
typedef union tuCddTpsGen2_RegDPHASE10H      { tsCddTpsGen2_Bit_RegDPHASE10H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE10H;
typedef union tuCddTpsGen2_RegDWIDTH10L      { tsCddTpsGen2_Bit_RegDWIDTH10L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH10L;
typedef union tuCddTpsGen2_RegDWIDTH10H      { tsCddTpsGen2_Bit_RegDWIDTH10H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH10H;
typedef union tuCddTpsGen2_RegDPHASE11L      { tsCddTpsGen2_Bit_RegDPHASE11L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE11L;
typedef union tuCddTpsGen2_RegDPHASE11H      { tsCddTpsGen2_Bit_RegDPHASE11H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE11H;
typedef union tuCddTpsGen2_RegDWIDTH11L      { tsCddTpsGen2_Bit_RegDWIDTH11L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH11L;
typedef union tuCddTpsGen2_RegDWIDTH11H      { tsCddTpsGen2_Bit_RegDWIDTH11H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH11H;
typedef union tuCddTpsGen2_RegDPHASE12L      { tsCddTpsGen2_Bit_RegDPHASE12L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE12L;
typedef union tuCddTpsGen2_RegDPHASE12H      { tsCddTpsGen2_Bit_RegDPHASE12H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDPHASE12H;
typedef union tuCddTpsGen2_RegDWIDTH12L      { tsCddTpsGen2_Bit_RegDWIDTH12L      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH12L;
typedef union tuCddTpsGen2_RegDWIDTH12H      { tsCddTpsGen2_Bit_RegDWIDTH12H      Bit; uint8 ucRaw; } tuCddTpsGen2_RegDWIDTH12H;
typedef union tuCddTpsGen2_RegSLEWRATE       { tsCddTpsGen2_Bit_RegSLEWRATE       Bit; uint8 ucRaw; } tuCddTpsGen2_RegSLEWRATE;
typedef union tuCddTpsGen2_RegOVLMT          { tsCddTpsGen2_Bit_RegOVLMT          Bit; uint8 ucRaw; } tuCddTpsGen2_RegOVLMT;
typedef union tuCddTpsGen2_RegPARLED         { tsCddTpsGen2_Bit_RegPARLED         Bit; uint8 ucRaw; } tuCddTpsGen2_RegPARLED;
typedef union tuCddTpsGen2_RegDEFWIDTH02_01  { tsCddTpsGen2_Bit_RegDEFWIDTH02_01  Bit; uint8 ucRaw; } tuCddTpsGen2_RegDEFWIDTH02_01;
typedef union tuCddTpsGen2_RegDEFWIDTH04_03  { tsCddTpsGen2_Bit_RegDEFWIDTH04_03  Bit; uint8 ucRaw; } tuCddTpsGen2_RegDEFWIDTH04_03;
typedef union tuCddTpsGen2_RegDEFWIDTH06_05  { tsCddTpsGen2_Bit_RegDEFWIDTH06_05  Bit; uint8 ucRaw; } tuCddTpsGen2_RegDEFWIDTH06_05;
typedef union tuCddTpsGen2_RegDEFWIDTH08_07  { tsCddTpsGen2_Bit_RegDEFWIDTH08_07  Bit; uint8 ucRaw; } tuCddTpsGen2_RegDEFWIDTH08_07;
typedef union tuCddTpsGen2_RegDEFWIDTH10_09  { tsCddTpsGen2_Bit_RegDEFWIDTH10_09  Bit; uint8 ucRaw; } tuCddTpsGen2_RegDEFWIDTH10_09;
typedef union tuCddTpsGen2_RegDEFWIDTH12_11  { tsCddTpsGen2_Bit_RegDEFWIDTH12_11  Bit; uint8 ucRaw; } tuCddTpsGen2_RegDEFWIDTH12_11;
typedef union tuCddTpsGen2_RegSYSCFG         { tsCddTpsGen2_Bit_RegSYSCFG         Bit; uint8 ucRaw; } tuCddTpsGen2_RegSYSCFG;
typedef union tuCddTpsGen2_RegCMWTAP         { tsCddTpsGen2_Bit_RegCMWTAP         Bit; uint8 ucRaw; } tuCddTpsGen2_RegCMWTAP;
typedef union tuCddTpsGen2_RegPWMTICK        { tsCddTpsGen2_Bit_RegPWMTICK        Bit; uint8 ucRaw; } tuCddTpsGen2_RegPWMTICK;
typedef union tuCddTpsGen2_RegADCID          { tsCddTpsGen2_Bit_RegADCID          Bit; uint8 ucRaw; } tuCddTpsGen2_RegADCID;
//SOFTSYNC register
typedef union tuCddTpsGen2_RegI2CTICK        { tsCddTpsGen2_Bit_RegI2CTICK        Bit; uint8 ucRaw; } tuCddTpsGen2_RegI2CTICK;
typedef union tuCddTpsGen2_RegI2CSLA         { tsCddTpsGen2_Bit_RegI2CSLA         Bit; uint8 ucRaw; } tuCddTpsGen2_RegI2CSLA;
typedef union tuCddTpsGen2_RegI2CRLEN        { tsCddTpsGen2_Bit_RegI2CRLEN        Bit; uint8 ucRaw; } tuCddTpsGen2_RegI2CRLEN;
typedef union tuCddTpsGen2_RegI2CADR         { tsCddTpsGen2_Bit_RegI2CADR         Bit; uint8 ucRaw; } tuCddTpsGen2_RegI2CADR;
//I2CCTRL register
typedef union tuCddTpsGen2_RegI2CDAT         { tsCddTpsGen2_Bit_RegI2CDAT         Bit; uint8 ucRaw; } tuCddTpsGen2_RegI2CDAT;
//I2CSTAT & I2CBMON registers
//ADC1    & ADC2    registers
typedef union tuCddTpsGen2_RegFAULTL         { tsCddTpsGen2_Bit_RegFAULTL         Bit; uint8 ucRaw; } tuCddTpsGen2_RegFAULTL;
typedef union tuCddTpsGen2_RegFAULTH         { tsCddTpsGen2_Bit_RegFAULTH         Bit; uint8 ucRaw; } tuCddTpsGen2_RegFAULTH;
typedef union tuCddTpsGen2_RegCERRCNT        { tsCddTpsGen2_Bit_RegCERRCNT        Bit; uint8 ucRaw; } tuCddTpsGen2_RegCERRCNT;
//ICID              register


// W Registers
typedef union tuCddTpsGen2_RegSOFTSYNC       { tsCddTpsGen2_Bit_RegSOFTSYNC       Bit; uint8 ucRaw; } tuCddTpsGen2_RegSOFTSYNC;
typedef union tuCddTpsGen2_RegI2CCTRL        { tsCddTpsGen2_Bit_RegI2CCTRL        Bit; uint8 ucRaw; } tuCddTpsGen2_RegI2CCTRL;

// R Registers
typedef union tuCddTpsGen2_RegI2CSTAT        { tsCddTpsGen2_Bit_RegI2CSTAT        Bit; uint8 ucRaw; } tuCddTpsGen2_RegI2CSTAT;
typedef union tuCddTpsGen2_RegI2CBMON        { tsCddTpsGen2_Bit_RegI2CBMON        Bit; uint8 ucRaw; } tuCddTpsGen2_RegI2CBMON;
typedef union tuCddTpsGen2_RegADC1           { tsCddTpsGen2_Bit_RegADC1           Bit; uint8 ucRaw; } tuCddTpsGen2_RegADC1;
typedef union tuCddTpsGen2_RegADC2           { tsCddTpsGen2_Bit_RegADC2           Bit; uint8 ucRaw; } tuCddTpsGen2_RegADC2;
typedef union tuCddTpsGen2_RegICID           { tsCddTpsGen2_Bit_RegICID           Bit; uint8 ucRaw; } tuCddTpsGen2_RegICID;



// group registers
typedef struct tsCddTpsGen2_MPHASEReg
{
  tuCddTpsGen2_RegMPHASE01L       RegMPHASE01L;
  tuCddTpsGen2_RegMPHASE02L       RegMPHASE02L;
  tuCddTpsGen2_RegMPHASE03L       RegMPHASE03L;
  tuCddTpsGen2_RegMPHASE03_01H    RegMPHASE03_01H;
  tuCddTpsGen2_RegMPHASE04L       RegMPHASE04L;
  tuCddTpsGen2_RegMPHASE05L       RegMPHASE05L;
  tuCddTpsGen2_RegMPHASE06L       RegMPHASE06L;
  tuCddTpsGen2_RegMPHASE06_04H    RegMPHASE06_04H;
  tuCddTpsGen2_RegMPHASE07L       RegMPHASE07L;
  tuCddTpsGen2_RegMPHASE08L       RegMPHASE08L;
  tuCddTpsGen2_RegMPHASE09L       RegMPHASE09L;
  tuCddTpsGen2_RegMPHASE09_07H    RegMPHASE09_07H;
  tuCddTpsGen2_RegMPHASE10L       RegMPHASE10L;
  tuCddTpsGen2_RegMPHASE11L       RegMPHASE11L;
  tuCddTpsGen2_RegMPHASE12L       RegMPHASE12L;
  tuCddTpsGen2_RegMPHASE12_10H    RegMPHASE12_10H;
}tsCddTpsGen2_MPHASEReg;

typedef union tuCddTpsGen2_MPHASEReg
{
  tsCddTpsGen2_MPHASEReg          MPHASERegs;
  uint8                             ucByte[16];
}tuCddTpsGen2_MPHASEReg;

typedef struct tsCddTpsGen2_MWIDTHReg
{
  tuCddTpsGen2_RegMWIDTH01L       RegMWIDTH01L;
  tuCddTpsGen2_RegMWIDTH02L       RegMWIDTH02L;
  tuCddTpsGen2_RegMWIDTH03L       RegMWIDTH03L;
  tuCddTpsGen2_RegMWIDTH03_01H    RegMWIDTH03_01H;
  tuCddTpsGen2_RegMWIDTH04L       RegMWIDTH04L;
  tuCddTpsGen2_RegMWIDTH05L       RegMWIDTH05L;
  tuCddTpsGen2_RegMWIDTH06L       RegMWIDTH06L;
  tuCddTpsGen2_RegMWIDTH06_04H    RegMWIDTH06_04H;
  tuCddTpsGen2_RegMWIDTH07L       RegMWIDTH07L;
  tuCddTpsGen2_RegMWIDTH08L       RegMWIDTH08L;
  tuCddTpsGen2_RegMWIDTH09L       RegMWIDTH09L;
  tuCddTpsGen2_RegMWIDTH09_07H    RegMWIDTH09_07H;
  tuCddTpsGen2_RegMWIDTH10L       RegMWIDTH10L;
  tuCddTpsGen2_RegMWIDTH11L       RegMWIDTH11L;
  tuCddTpsGen2_RegMWIDTH12L       RegMWIDTH12L;
  tuCddTpsGen2_RegMWIDTH12_10H    RegMWIDTH12_10H;
}tsCddTpsGen2_MWIDTHReg;

typedef union tuCddTpsGen2_MWIDTHReg
{
  tsCddTpsGen2_MWIDTHReg          MWIDTHRegs;
  uint8                             ucByte[16];
}tuCddTpsGen2_MWIDTHReg;

typedef struct tsCddTpsGen2_LPHASEReg
{
  tuCddTpsGen2_RegLPHASE01H       RegLPHASE01H;
  tuCddTpsGen2_RegLPHASE02H       RegLPHASE02H;
  tuCddTpsGen2_RegLPHASE03H       RegLPHASE03H;
  tuCddTpsGen2_RegLPHASE04H       RegLPHASE04H;
  tuCddTpsGen2_RegLPHASE05H       RegLPHASE05H;
  tuCddTpsGen2_RegLPHASE06H       RegLPHASE06H;
  tuCddTpsGen2_RegLPHASE07H       RegLPHASE07H;
  tuCddTpsGen2_RegLPHASE08H       RegLPHASE08H;
  tuCddTpsGen2_RegLPHASE09H       RegLPHASE09H;
  tuCddTpsGen2_RegLPHASE10H       RegLPHASE10H;
  tuCddTpsGen2_RegLPHASE11H       RegLPHASE11H;
  tuCddTpsGen2_RegLPHASE12H       RegLPHASE12H;
  tuCddTpsGen2_RegLPHASE03_01L    RegLPHASE03_01L;
  tuCddTpsGen2_RegLPHASE06_04L    RegLPHASE06_04L;
  tuCddTpsGen2_RegLPHASE09_07L    RegLPHASE09_07L;
  tuCddTpsGen2_RegLPHASE12_10L    RegLPHASE12_10L;
}tsCddTpsGen2_LPHASEReg;

typedef struct tsCddTpsGen2_LWIDTHReg
{
  tuCddTpsGen2_RegLWIDTH01H       RegLWIDTH01H;
  tuCddTpsGen2_RegLWIDTH02H       RegLWIDTH02H;
  tuCddTpsGen2_RegLWIDTH03H       RegLWIDTH03H;
  tuCddTpsGen2_RegLWIDTH04H       RegLWIDTH04H;
  tuCddTpsGen2_RegLWIDTH05H       RegLWIDTH05H;
  tuCddTpsGen2_RegLWIDTH06H       RegLWIDTH06H;
  tuCddTpsGen2_RegLWIDTH07H       RegLWIDTH07H;
  tuCddTpsGen2_RegLWIDTH08H       RegLWIDTH08H;
  tuCddTpsGen2_RegLWIDTH09H       RegLWIDTH09H;
  tuCddTpsGen2_RegLWIDTH10H       RegLWIDTH10H;
  tuCddTpsGen2_RegLWIDTH11H       RegLWIDTH11H;
  tuCddTpsGen2_RegLWIDTH12H       RegLWIDTH12H;
  tuCddTpsGen2_RegLWIDTH03_01L    RegLWIDTH03_01L;
  tuCddTpsGen2_RegLWIDTH06_04L    RegLWIDTH06_04L;
  tuCddTpsGen2_RegLWIDTH09_07L    RegLWIDTH09_07L;
  tuCddTpsGen2_RegLWIDTH12_10L    RegLWIDTH12_10L;
}tsCddTpsGen2_LWIDTHReg;


typedef struct tsCddTpsGen2_DiscreteLED_PHASE_WIDTHReg {
  tuCddTpsGen2_RegDPHASE01L      RegDPHASE01L;
  tuCddTpsGen2_RegDPHASE01H      RegDPHASE01H;
  tuCddTpsGen2_RegDWIDTH01L      RegDWIDTH01L;
  tuCddTpsGen2_RegDWIDTH01H      RegDWIDTH01H;
  tuCddTpsGen2_RegDPHASE02L      RegDPHASE02L;
  tuCddTpsGen2_RegDPHASE02H      RegDPHASE02H;
  tuCddTpsGen2_RegDWIDTH02L      RegDWIDTH02L;
  tuCddTpsGen2_RegDWIDTH02H      RegDWIDTH02H;
  tuCddTpsGen2_RegDPHASE03L      RegDPHASE03L;
  tuCddTpsGen2_RegDPHASE03H      RegDPHASE03H;
  tuCddTpsGen2_RegDWIDTH03L      RegDWIDTH03L;
  tuCddTpsGen2_RegDWIDTH03H      RegDWIDTH03H;
  tuCddTpsGen2_RegDPHASE04L      RegDPHASE04L;
  tuCddTpsGen2_RegDPHASE04H      RegDPHASE04H;
  tuCddTpsGen2_RegDWIDTH04L      RegDWIDTH04L;
  tuCddTpsGen2_RegDWIDTH04H      RegDWIDTH04H;
  tuCddTpsGen2_RegDPHASE05L      RegDPHASE05L;
  tuCddTpsGen2_RegDPHASE05H      RegDPHASE05H;
  tuCddTpsGen2_RegDWIDTH05L      RegDWIDTH05L;
  tuCddTpsGen2_RegDWIDTH05H      RegDWIDTH05H;
  tuCddTpsGen2_RegDPHASE06L      RegDPHASE06L;
  tuCddTpsGen2_RegDPHASE06H      RegDPHASE06H;
  tuCddTpsGen2_RegDWIDTH06L      RegDWIDTH06L;
  tuCddTpsGen2_RegDWIDTH06H      RegDWIDTH06H;
  tuCddTpsGen2_RegDPHASE07L      RegDPHASE07L;
  tuCddTpsGen2_RegDPHASE07H      RegDPHASE07H;
  tuCddTpsGen2_RegDWIDTH07L      RegDWIDTH07L;
  tuCddTpsGen2_RegDWIDTH07H      RegDWIDTH07H;
  tuCddTpsGen2_RegDPHASE08L      RegDPHASE08L;
  tuCddTpsGen2_RegDPHASE08H      RegDPHASE08H;
  tuCddTpsGen2_RegDWIDTH08L      RegDWIDTH08L;
  tuCddTpsGen2_RegDWIDTH08H      RegDWIDTH08H;
  tuCddTpsGen2_RegDPHASE09L      RegDPHASE09L;
  tuCddTpsGen2_RegDPHASE09H      RegDPHASE09H;
  tuCddTpsGen2_RegDWIDTH09L      RegDWIDTH09L;
  tuCddTpsGen2_RegDWIDTH09H      RegDWIDTH09H;
  tuCddTpsGen2_RegDPHASE10L      RegDPHASE10L;
  tuCddTpsGen2_RegDPHASE10H      RegDPHASE10H;
  tuCddTpsGen2_RegDWIDTH10L      RegDWIDTH10L;
  tuCddTpsGen2_RegDWIDTH10H      RegDWIDTH10H;
  tuCddTpsGen2_RegDPHASE11L      RegDPHASE11L;
  tuCddTpsGen2_RegDPHASE11H      RegDPHASE11H;
  tuCddTpsGen2_RegDWIDTH11L      RegDWIDTH11L;
  tuCddTpsGen2_RegDWIDTH11H      RegDWIDTH11H;
  tuCddTpsGen2_RegDPHASE12L      RegDPHASE12L;
  tuCddTpsGen2_RegDPHASE12H      RegDPHASE12H;
  tuCddTpsGen2_RegDWIDTH12L      RegDWIDTH12L;
  tuCddTpsGen2_RegDWIDTH12H      RegDWIDTH12H;
}tsCddTpsGen2_DiscreteLED_PHASE_WIDTHReg;

typedef struct tsCddTpsGen2_LEDPhaseWidthReg
{
  tsCddTpsGen2_MPHASEReg                   RegMPHASE;
  tsCddTpsGen2_MWIDTHReg                   RegMWIDTH;
  tsCddTpsGen2_LPHASEReg                   RegLPHASE;
  tsCddTpsGen2_LWIDTHReg                   RegLWIDTH;
  tsCddTpsGen2_DiscreteLED_PHASE_WIDTHReg  RegDiscreteLED_PHASE_WIDTH;
}tsCddTpsGen2_LEDPhaseWidthReg;

typedef union tuCddTpsGen2_DefWIDTHReg {
  tsCddTpsGen2_Bit_RegDEFWIDTH02_01  sRegDEFWIDTH02_01[6];
  uint8  ucByte[6];
}tuCddTpsGen2_DefWIDTHReg;

typedef struct tsCddTpsGen2_LedSubStringCfgReg
{
  tuCddTpsGen2_RegSLEWRATE       uRegSLEWRATE;
  tuCddTpsGen2_RegOVLMT          uRegOVLMT;
  tuCddTpsGen2_RegPARLED         uRegPARLED;
  tuCddTpsGen2_DefWIDTHReg       uRegDEFWIDTHS;
  uint8 ucReserved[3];          /* Note: needed to fill remaining 3bytes from 12Byte command*/
}tsCddTpsGen2_LedSubStringCfgReg;


typedef struct tsCddTpsGen2_I2CSeqCfg
{
  tuCddTpsGen2_RegI2CSLA   RegI2CSLA;  // 1 byte
  tuCddTpsGen2_RegI2CRLEN  RegI2CRLEN; // 1 byte
  tuCddTpsGen2_RegI2CADR   RegI2CADR;  // 1 byte
  tuCddTpsGen2_RegI2CCTRL  RegI2CCTRL; // 1 byte
}tsCddTpsGen2_I2CSeqCfg;

typedef union tuCddTpsGen2_RegI2CSeqCfg
{
  tsCddTpsGen2_I2CSeqCfg  sI2CSeqCfg;
  uint8                   ucByte[4];
}tuCddTpsGen2_RegI2CSeqCfg;

typedef struct tsCddTpsGen2_I2CStatusReg
{
  tuCddTpsGen2_RegI2CSTAT  RegI2CSTAT;
  tuCddTpsGen2_RegI2CBMON  RegI2CBMON;
}tsCddTpsGen2_I2CStatusReg;

typedef union tuCddTpsGen2_I2CStatusReg
{
  tsCddTpsGen2_I2CStatusReg  I2CStatusReg;
  uint8                        ucByte[2];
}tuCddTpsGen2_I2CStatusReg;

typedef struct tsCddTpsGen2_SystemCfgReg
{
  tuCddTpsGen2_RegSYSCFG   RegSYSCFG;
  tuCddTpsGen2_RegCMWTAP   RegCMWTAP;
  tuCddTpsGen2_RegPWMTICK  RegPWMTICK;
}tsCddTpsGen2_SystemCfgReg;


typedef struct tsCddTpsGen2_FaultCtrlReg
{
  tuCddTpsGen2_RegFAULTL   RegFAULTL;
  tuCddTpsGen2_RegFAULTH   RegFAULTH;
  tuCddTpsGen2_RegCERRCNT  RegCERRCNT;
}tsCddTpsGen2_FaultCtrlReg;


typedef union tuCddTpsGen2_StringCfg    { tsCddTpsGen2_LedSubStringCfgReg    sStringCfg; uint8 ucByte[12]; }tuCddTpsGen2_StringCfg;
typedef union tuCddTpsGen2_SystemCfgReg { tsCddTpsGen2_SystemCfgReg          sSysReg;    uint8 ucByte[3];  }tuCddTpsGen2_SystemCfgReg;
typedef union tuCddTpsGen2_FaultCtrlReg { tsCddTpsGen2_FaultCtrlReg          sFaultReg;  uint8 ucByte[3];  }tuCddTpsGen2_FaultCtrlReg;

typedef struct tsCddTpsGen2_IdentificationReg
{
  tuCddTpsGen2_RegICID RegICID;
}tsCddTpsGen2_IdentificationReg;

typedef void(*tCddTpsGen2_I2C_pFnct)(void);          // I2C Callback Function Definition

typedef enum
{                                             //-I2C Communication States-
  CddTpsGen2_I2C_NotInit = 0,                      // Not Initialized
  CddTpsGen2_I2C_Preinit,                          // Initialization Process
  CddTpsGen2_I2C_Init,                             // Initialization Process
  CddTpsGen2_I2C_Idle,                             // Idle - No operation performed
  CddTpsGen2_I2C_Read_Start,                       // Read process started
  CddTpsGen2_I2C_Read_Status,                      // Evaluate reading status
  CddTpsGen2_I2C_Read_Data,                        // Receive data bytes from FIFO
  CddTpsGen2_I2C_Write_Data,                       // Send data byte for writing 
  CddTpsGen2_I2C_Write_Start,                      // Write proccess started
  CddTpsGen2_I2C_Write_Status,                     // Evaluate writing status
  CddTpsGen2_I2C_ControlReset,                     // Reset I2C state machine and the receive FIFO is flushed
  CddTpsGen2_I2C_Length                            // Number of I2C states
}tCddTpsGen2_I2C_eState;

typedef enum {
  CddTpsGen2_I2C_Rejected = 0,                       // Operation rejected due to faulty I2C, invalid buffer pointer, adress or length,
  CddTpsGen2_I2C_Failed,                             // Operation failure due to I2C status error flags or timeout threshold reached,
  CddTpsGen2_I2C_Pending,                            // Operation ongoing - not finished yet,
  CddTpsGen2_I2C_Completed                           // Operation succesfully completed.
} tCddTpsGen2_I2C_eStatus;                           // EEPROM operation status


#endif // CDD_TPS92662A_TYPES_2023_09_06_H
