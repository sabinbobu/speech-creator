//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddTpsGen3_Types.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN3_TYPES_2024_02_05_H
#define CDD_TPS_GEN3_TYPES_2024_02_05_H

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>

//=============================================================================
// Type definition for control and data structures
//=============================================================================


//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// TPS92664 Communication Protocol
//=============================================================================

//Length of message format
#define CDDTPSGEN3_N_HEADER_BYTES    3u

//Number of bytes transferred
#define CDDTPSGEN3_N_01_BYTE         1u
#define CDDTPSGEN3_N_02_BYTES        2u
#define CDDTPSGEN3_N_03_BYTES        3u
#define CDDTPSGEN3_N_04_BYTES        4u
#define CDDTPSGEN3_N_12_BYTES        12u
#define CDDTPSGEN3_N_16_BYTES        16u
#define CDDTPSGEN3_N_32_BYTES        32u

// Extended Protocol Transfer
#define CDDTPSGEN3_N_05_BYTES        5u
#define CDDTPSGEN3_N_08_BYTES        8u
#define CDDTPSGEN3_N_20_BYTES        20u

//Length of CRC
#define CDDTPSGEN3_N_CRC_BYTES       2u

//Reception acknowledge
#define CDDTPSGEN3_N_ACK             1u

#define CDDTPSGEN3_DUMMY_BYTE        1u
#define CDDTPSGEN3_MAX_WRITE_CMD_LENGTH    (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_32_BYTES  + CDDTPSGEN3_N_CRC_BYTES +  CDDTPSGEN3_N_ACK)
#define CDDTPSGEN3_MAX_READ_CMD_LENGTH     (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_CRC_BYTES + CDDTPSGEN3_N_32_BYTES  +  CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_MAX_CMD_LENGTH          (CDDTPSGEN3_MAX_READ_CMD_LENGTH + CDDTPSGEN3_DUMMY_BYTE)

/*--------------------------------------------
  Frame Initialization Byte
  INIT byte to identify the transaction
----------------------------------------------*/

// frame INIT bytes for write commands
#define CDDTPSGEN3_WRITE_01_BYTES    0x87u
#define CDDTPSGEN3_WRITE_02_BYTES    0x99u
#define CDDTPSGEN3_WRITE_03_BYTES    0x1Eu
#define CDDTPSGEN3_WRITE_04_BYTES    0xAAu
#define CDDTPSGEN3_WRITE_12_BYTES    0x2Du
#define CDDTPSGEN3_WRITE_16_BYTES    0x33u
#define CDDTPSGEN3_WRITE_32_BYTES    0xB4u

// frame INIT bytes for write commands in Extended Protocol Transfer
#define CDDTPSGEN3_WRITE_05_BYTES    0xADu
#define CDDTPSGEN3_WRITE_08_BYTES    0x13u
#define CDDTPSGEN3_WRITE_20_BYTES    0xB5u

// frame INIT bytes for read commands
#define CDDTPSGEN3_READ_01_BYTES     0x4Bu
#define CDDTPSGEN3_READ_02_BYTES     0xCCu
#define CDDTPSGEN3_READ_03_BYTES     0xD2u
#define CDDTPSGEN3_READ_04_BYTES     0x55u
#define CDDTPSGEN3_READ_12_BYTES     0xE1u
#define CDDTPSGEN3_READ_16_BYTES     0x66u
#define CDDTPSGEN3_READ_32_BYTES     0x78u

// frame INIT bytes for read commands in Extended Protocol Transfer
#define CDDTPSGEN3_READ_05_BYTES     0xE5u
#define CDDTPSGEN3_READ_08_BYTES     0x26u
#define CDDTPSGEN3_READ_20_BYTES     0x7Au

//acknowledgement byte expected from Mlc chip
#define CDDTPSGEN3_ACK_BYTE          0x7Fu  

//Definitions for enable/disable Mlc features
#define CDDTPSGEN3_FEATURE_ON        1u     // active feature
#define CDDTPSGEN3_FEATURE_OFF       0u     // inactive feature

/*--------------------------------------------------------------------
   Definition of MTPCFG bits :
   CLKDIV2 | EN_VDD_OV | FS_PIN | STANDALONE | MTPDEFWIDTH[1:0] | MTPPHASE[1:0]
---------------------------------------------------------------------*/

#define CDDTPSGEN3_CLKDIV2        (0x01U << 7U) // the 7th bit divides system clock by two for 500kpbs (0 = Do not divide system clock by two for 1000kbps)
#define CDDTPSGEN3_EN_VDD_OV      (0x00U << 6U) // the 6th bit enables VDD OV comparison
#define CDDTPSGEN3_FS_PIN         (0x01U << 5U) // the 5th bit writes "1" to FS_PIN to exit failsafe
#define CDDTPSGEN3_STANDALONE     (0x00U << 4U) // the 4th bit indicates normal mode (an MCU is required to communciate with and control the IC)
#define CDDTPSGEN3_MTPDEFWIDTH_1  (0x01U << 3U) // the 3th bit configures the bit length of DEFWIDTH reg in MTP (11 = Pre-initialize DEFWIDTH registers with 8-bit values stored in MTP)
#define CDDTPSGEN3_MTPDEFWIDTH_0  (0x01U << 2U) // the 2th bit configures the bit length of DEFWIDTH reg in MTP (11 = Pre-initialize DEFWIDTH registers with 8-bit values stored in MTP)
#define CDDTPSGEN3_MTPPHASE_1     (0x00U << 1U) // the 1th bit configures the bit length of PHASE reg in MTP (00 = set PHASE to equally 16 spaced values)
#define CDDTPSGEN3_MTPPHASE_0     (0x00U << 0U) // the 0th bit configures the bit length of PHASE reg in MTP (00 = set PHASE to equally 16 spaced values)

/*--------------------------------------------------------------------
   Definition of SYSCFG bits :
   SEPTR | LEDADCEN | ACKEN | PSON | CMWEN | CSGAIN | CHPMP_SS | CSEN
---------------------------------------------------------------------*/

#define CDDTPSGEN3_SEPTR      (0x01U << 7U) // the 7th bit indicates separate Rx/Tx
#define CDDTPSGEN3_LEDADCEN   (0x01U << 6U) // the 6th bit enables ADC measurement of LED voltages
#define CDDTPSGEN3_ACKEN      (0x01U << 5U) // the 5th bit enables the Ack response
#define CDDTPSGEN3_PSON       (0x01U << 4U) // the 4th bit indicates the phase shift LED on
#define CDDTPSGEN3_CMWEN      (0x01U << 3U) // the 3th bit enables the communication watchdog timer
#define CDDTPSGEN3_CSGAIN     (0x00U << 2U) // the 2th bit enables the current sense gain
#define CDDTPSGEN3_CHPMP_SS   (0x01U << 1U) // the 1th bit enables the charge pump spread spectrum
#define CDDTPSGEN3_CSEN       (0x00U << 0U) // the 0th bit enables ADC measurement of the current sense


/*--------------------------------------------------------------------
   Definition of STATUS bits :
   PWM_ERR | CHPMP_ERR | VLED_ERR | LIMP_HOME | TRIM_ERR | TW | MTP_ERR | PWR
---------------------------------------------------------------------*/

#define CDDTPSGEN3_PWM_ERR     (0x01U << 7U) // the 7th bit indicates a PWM error (PWM_MISCOUNT registers can be read in order to diagnose which channel(s) had duty cycle errors )
#define CDDTPSGEN3_CHPMP_ERR   (0x01U << 6U) // the 6th bit indicates a charge pump error
#define CDDTPSGEN3_VLED_ERR    (0x01U << 5U) // the 5th bit indicates an LED Voltage error (the ADC readings were outside of LEDONTH / LEDOFFTH limits)
#define CDDTPSGEN3_LIMP_HOME   (0x01U << 4U) // the 4th bit indicates that the limp home mode is active (CMW timer expired)
#define CDDTPSGEN3_TRIM_ERR    (0x01U << 3U) // the 3th bit indicates a trim error (CRC doesn't match with the expected one)
#define CDDTPSGEN3_TW          (0x01U << 2U) // the 2th bit indicates a thermal warning
#define CDDTPSGEN3_MTP_ERR     (0x01U << 1U) // the 1th bit indicates a MTP error
#define CDDTPSGEN3_PWR         (0x01U << 0U) // the 0th bit indicates a power cycle

/*--------------------------------------------------------------------
   Definition of SLEWRATE bit pos :
   SLEWL  : Reserved [1:0] | SLEWL_08_05[2:0] | SLEWL_04_01 [2:0]
   SLEWH  : Reserved [1:0] | SLEWL_16_13[2:0] | SLEWL_12_09 [2:0]
---------------------------------------------------------------------*/

#define CDDTPSGEN3_SLEWL_08_05 (3u)
#define CDDTPSGEN3_SLEWL_04_01 (0u)

#define CDDTPSGEN3_SLEWH_16_13 (3u)
#define CDDTPSGEN3_SLEWH_12_09 (0u)

/*--------------------------------------------------------------------
   Definition of OVLMT (Over Voltage)  bit pos :
   OVLMT = 18V (fixed, not programmable)
---------------------------------------------------------------------*/

#define CDDTPSGEN3_SET_SLEWRATE_REGL(slewRateL)    ((uint8)(slewRateL<<CDDTPSGEN3_SLEWL_08_05)|(uint8)(slewRateL<<CDDTPSGEN3_SLEWL_04_01))
#define CDDTPSGEN3_SET_SLEWRATE_REGH(slewRateH)    ((uint8)(slewRateH<<CDDTPSGEN3_SLEWH_16_13)|(uint8)(slewRateH<<CDDTPSGEN3_SLEWH_12_09))


// PWM Synchronization Type
#define CDDTPSGEN3_SYNC_HW_EXTERNAL_PIN    0u  // Exclusive Hardware - MCU External pin
#define CDDTPSGEN3_SYNC_HW_MASTER_SLAVE    1u  // Master Slave Topology Synchronization
#define CDDTPSGEN3_SYNC_SW_BROADCAST_CMD   2u  // Exclusive Sofware - Broadcast SSYNC Command

// PHASE registers computation
#define CDDTPSGEN3_PHASE_MAX               1023u   // Maximum value for PHASE shift register

#define CDDTPSGEN3_PHASE_DIV16             16u             // PHASE shift division for 16 leds in series
#define CDDTPSGEN3_PHASE_DIV12             12u             // PHASE shift division for 12 leds in series
#define CDDTPSGEN3_PHASE_DIV6              6u              // PHASE shift division for 6 leds in series  


// Configuration for one set (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16) of sixteen LEDs segments in series.
#define CDDTPSGEN3_CFG_1STRING_OF_16LEDS { \
    ( 0u ), \
    ( CDDTPSGEN3_PHASE_MAX * 1u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX * 2u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX * 3u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX * 4u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX * 5u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX * 6u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX * 7u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX * 8u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX * 9u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX *10u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX *11u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX *12u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX *13u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX *14u / CDDTPSGEN3_PHASE_DIV16), \
    ( CDDTPSGEN3_PHASE_MAX *15u / CDDTPSGEN3_PHASE_DIV16)  \
}


// Default Configuration for PHASE shift values - no phase shifts
#define CDDTPSGEN3_CFG_NO_PHASE_SHIFTING { \
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
    (0u), \
    (0u), \
    (0u), \
    (0u), \
    (0u)  \
}



//=============================================================================
// Defines for Registers Addresses
//=============================================================================

//=============================================================================
// REGISTER DEFINITIONS
//
// TPS92664 Volatile Register Map
//
//=============================================================================

//   MTP Config, Slew rate config
#define CDDTPSGEN3_AddrMTPCFG              0x00 // MTP memory configuration, system clock frequency, VDD overvoltage
#define CDDTPSGEN3_AddrOUTCTRL             0x01 // parallel switch configuration, driver health check, TX output, SYNC output and LVDS CLK output
#define CDDTPSGEN3_AddrTWLMT               0x02 // sets the die temperature
#define CDDTPSGEN3_AddrSLEWL               0x03
#define CDDTPSGEN3_AddrSLEWH               0x04

//   DEFWIDTH registers
#define CDDTPSGEN3_AddrDEFWIDTH01          0x05
#define CDDTPSGEN3_AddrDEFWIDTH02          0x06
#define CDDTPSGEN3_AddrDEFWIDTH03          0x07
#define CDDTPSGEN3_AddrDEFWIDTH04          0x08
#define CDDTPSGEN3_AddrDEFWIDTH05          0x09
#define CDDTPSGEN3_AddrDEFWIDTH06          0x0A
#define CDDTPSGEN3_AddrDEFWIDTH07          0x0B
#define CDDTPSGEN3_AddrDEFWIDTH08          0x0C
#define CDDTPSGEN3_AddrDEFWIDTH09          0x0D
#define CDDTPSGEN3_AddrDEFWIDTH10          0x0E
#define CDDTPSGEN3_AddrDEFWIDTH11          0x0F
#define CDDTPSGEN3_AddrDEFWIDTH12          0x10
#define CDDTPSGEN3_AddrDEFWIDTH13          0x11
#define CDDTPSGEN3_AddrDEFWIDTH14          0x12
#define CDDTPSGEN3_AddrDEFWIDTH15          0x13
#define CDDTPSGEN3_AddrDEFWIDTH16          0x14

//   PHASE registers
#define CDDTPSGEN3_AddrPHASE01H            0x15
#define CDDTPSGEN3_AddrPHASE02H            0x16
#define CDDTPSGEN3_AddrPHASE03H            0x17
#define CDDTPSGEN3_AddrPHASE04H            0x18
#define CDDTPSGEN3_AddrPHASE05H            0x19
#define CDDTPSGEN3_AddrPHASE06H            0x1A
#define CDDTPSGEN3_AddrPHASE07H            0x1B
#define CDDTPSGEN3_AddrPHASE08H            0x1C
#define CDDTPSGEN3_AddrPHASE09H            0x1D
#define CDDTPSGEN3_AddrPHASE10H            0x1E
#define CDDTPSGEN3_AddrPHASE11H            0x1F
#define CDDTPSGEN3_AddrPHASE12H            0x20
#define CDDTPSGEN3_AddrPHASE13H            0x21
#define CDDTPSGEN3_AddrPHASE14H            0x22
#define CDDTPSGEN3_AddrPHASE15H            0x23
#define CDDTPSGEN3_AddrPHASE16H            0x24

//   PHASE L registers
#define CDDTPSGEN3_AddrPHASE04_01L         0x25
#define CDDTPSGEN3_AddrPHASE08_05L         0x26
#define CDDTPSGEN3_AddrPHASE12_09L         0x27
#define CDDTPSGEN3_AddrPHASE16_13L         0x28

//   WIDTH registers
#define CDDTPSGEN3_AddrWIDTH01H            0x29
#define CDDTPSGEN3_AddrWIDTH02H            0x2A
#define CDDTPSGEN3_AddrWIDTH03H            0x2B
#define CDDTPSGEN3_AddrWIDTH04H            0x2C
#define CDDTPSGEN3_AddrWIDTH05H            0x2D
#define CDDTPSGEN3_AddrWIDTH06H            0x2E
#define CDDTPSGEN3_AddrWIDTH07H            0x2F
#define CDDTPSGEN3_AddrWIDTH08H            0x30
#define CDDTPSGEN3_AddrWIDTH09H            0x31
#define CDDTPSGEN3_AddrWIDTH10H            0x32
#define CDDTPSGEN3_AddrWIDTH11H            0x33
#define CDDTPSGEN3_AddrWIDTH12H            0x34
#define CDDTPSGEN3_AddrWIDTH13H            0x35
#define CDDTPSGEN3_AddrWIDTH14H            0x36
#define CDDTPSGEN3_AddrWIDTH15H            0x37
#define CDDTPSGEN3_AddrWIDTH16H            0x38

//   WIDTH L registers
#define CDDTPSGEN3_AddrWIDTH04_01L         0x39
#define CDDTPSGEN3_AddrWIDTH08_05L         0x3A
#define CDDTPSGEN3_AddrWIDTH12_09L         0x3B
#define CDDTPSGEN3_AddrWIDTH16_13L         0x3C

//   BANK PHASE registers
#define CDDTPSGEN3_AddrBANK_PHASE01L       0x3D
#define CDDTPSGEN3_AddrBANK_PHASE02L       0x3E
#define CDDTPSGEN3_AddrBANK_PHASE03L       0x3F
#define CDDTPSGEN3_AddrBANK_PHASE04L       0x40
#define CDDTPSGEN3_AddrBANK_PHASE04_01H    0x41
#define CDDTPSGEN3_AddrBANK_PHASE05L       0x42
#define CDDTPSGEN3_AddrBANK_PHASE06L       0x43
#define CDDTPSGEN3_AddrBANK_PHASE07L       0x44
#define CDDTPSGEN3_AddrBANK_PHASE08L       0x45
#define CDDTPSGEN3_AddrBANK_PHASE08_05H    0x46
#define CDDTPSGEN3_AddrBANK_PHASE09L       0x47
#define CDDTPSGEN3_AddrBANK_PHASE10L       0x48
#define CDDTPSGEN3_AddrBANK_PHASE11L       0x49
#define CDDTPSGEN3_AddrBANK_PHASE12L       0x4A
#define CDDTPSGEN3_AddrBANK_PHASE12_09H    0x4B
#define CDDTPSGEN3_AddrBANK_PHASE13L       0x4C
#define CDDTPSGEN3_AddrBANK_PHASE14L       0x4D
#define CDDTPSGEN3_AddrBANK_PHASE15L       0x4E
#define CDDTPSGEN3_AddrBANK_PHASE16L       0x4F
#define CDDTPSGEN3_AddrBANK_PHASE16_13H    0x50

//   BANK WIDTH  registers
#define CDDTPSGEN3_AddrBANK_WIDTH01L       0x51
#define CDDTPSGEN3_AddrBANK_WIDTH02L       0x52
#define CDDTPSGEN3_AddrBANK_WIDTH03L       0x53
#define CDDTPSGEN3_AddrBANK_WIDTH04L       0x54
#define CDDTPSGEN3_AddrBANK_WIDTH04_01H    0x55
#define CDDTPSGEN3_AddrBANK_WIDTH05L       0x56
#define CDDTPSGEN3_AddrBANK_WIDTH06L       0x57
#define CDDTPSGEN3_AddrBANK_WIDTH07L       0x58
#define CDDTPSGEN3_AddrBANK_WIDTH08L       0x59
#define CDDTPSGEN3_AddrBANK_WIDTH08_05H    0x5A
#define CDDTPSGEN3_AddrBANK_WIDTH09L       0x5B
#define CDDTPSGEN3_AddrBANK_WIDTH10L       0x5C
#define CDDTPSGEN3_AddrBANK_WIDTH11L       0x5D
#define CDDTPSGEN3_AddrBANK_WIDTH12L       0x5E
#define CDDTPSGEN3_AddrBANK_WIDTH12_09H    0x5F
#define CDDTPSGEN3_AddrBANK_WIDTH13L       0x60
#define CDDTPSGEN3_AddrBANK_WIDTH14L       0x61
#define CDDTPSGEN3_AddrBANK_WIDTH15L       0x62
#define CDDTPSGEN3_AddrBANK_WIDTH16L       0x63
#define CDDTPSGEN3_AddrBANK_WIDTH16_13H    0x64

/* Reserved Memory (11 bytes)  between 0x65 - 0x6F */

// LEDONTH registers
#define CDDTPSGEN3_AddrLEDONTH01           0x70
#define CDDTPSGEN3_AddrLEDONTH02           0x71
#define CDDTPSGEN3_AddrLEDONTH03           0x72
#define CDDTPSGEN3_AddrLEDONTH04           0x73
#define CDDTPSGEN3_AddrLEDONTH05           0x74
#define CDDTPSGEN3_AddrLEDONTH06           0x75
#define CDDTPSGEN3_AddrLEDONTH07           0x76
#define CDDTPSGEN3_AddrLEDONTH08           0x77
#define CDDTPSGEN3_AddrLEDONTH09           0x78
#define CDDTPSGEN3_AddrLEDONTH10           0x79
#define CDDTPSGEN3_AddrLEDONTH11           0x7A
#define CDDTPSGEN3_AddrLEDONTH12           0x7B
#define CDDTPSGEN3_AddrLEDONTH13           0x7C
#define CDDTPSGEN3_AddrLEDONTH14           0x7D
#define CDDTPSGEN3_AddrLEDONTH15           0x7E
#define CDDTPSGEN3_AddrLEDONTH16           0x7F

//   Control registers
#define CDDTPSGEN3_AddrSYSCFG              0x80 // system configuration register
#define CDDTPSGEN3_AddrCMWTAP              0x81 // communications watchdog timer tap point register
#define CDDTPSGEN3_AddrPWMTICK             0x82 // PWM tick period register
#define CDDTPSGEN3_AddrADCID               0x83 // ADC ID register
#define CDDTPSGEN3_AddrCLK_SYNC            0x84 // clock sync register
#define CDDTPSGEN3_AddrSTATUS              0x85
#define CDDTPSGEN3_AddrFLT_OPEN_OR_DRVL    0x86
#define CDDTPSGEN3_AddrFLT_OPEN_OR_DRVH    0x87
#define CDDTPSGEN3_AddrFAULT_SHORTL        0x88
#define CDDTPSGEN3_AddrFAULT_SHORTH        0x89
#define CDDTPSGEN3_AddrFAULT_RESFETL       0x8A
#define CDDTPSGEN3_AddrFAULT_RESFETH       0x8B
#define CDDTPSGEN3_AddrCERRCNT             0x8C
#define CDDTPSGEN3_AddrADC1                0x8D
#define CDDTPSGEN3_AddrADC2                0x8E
#define CDDTPSGEN3_AddrDIETEMP             0x8F
#define CDDTPSGEN3_AddrCS                  0x90

//   VLEDON registers
#define CDDTPSGEN3_AddrVLEDON01            0x91
#define CDDTPSGEN3_AddrVLEDON02            0x92
#define CDDTPSGEN3_AddrVLEDON03            0x93
#define CDDTPSGEN3_AddrVLEDON04            0x94
#define CDDTPSGEN3_AddrVLEDON05            0x95
#define CDDTPSGEN3_AddrVLEDON06            0x96
#define CDDTPSGEN3_AddrVLEDON07            0x97
#define CDDTPSGEN3_AddrVLEDON08            0x98
#define CDDTPSGEN3_AddrVLEDON09            0x99
#define CDDTPSGEN3_AddrVLEDON10            0x9A
#define CDDTPSGEN3_AddrVLEDON11            0x9B
#define CDDTPSGEN3_AddrVLEDON12            0x9C
#define CDDTPSGEN3_AddrVLEDON13            0x9D
#define CDDTPSGEN3_AddrVLEDON14            0x9E
#define CDDTPSGEN3_AddrVLEDON15            0x9F
#define CDDTPSGEN3_AddrVLEDON16            0xA0

// VLEDOFF registers
#define CDDTPSGEN3_AddrVLEDOFF01           0xA1
#define CDDTPSGEN3_AddrVLEDOFF02           0xA2
#define CDDTPSGEN3_AddrVLEDOFF03           0xA3
#define CDDTPSGEN3_AddrVLEDOFF04           0xA4
#define CDDTPSGEN3_AddrVLEDOFF05           0xA5
#define CDDTPSGEN3_AddrVLEDOFF06           0xA6
#define CDDTPSGEN3_AddrVLEDOFF07           0xA7
#define CDDTPSGEN3_AddrVLEDOFF08           0xA8
#define CDDTPSGEN3_AddrVLEDOFF09           0xA9
#define CDDTPSGEN3_AddrVLEDOFF10           0xAA
#define CDDTPSGEN3_AddrVLEDOFF11           0xAB
#define CDDTPSGEN3_AddrVLEDOFF12           0xAC
#define CDDTPSGEN3_AddrVLEDOFF13           0xAD
#define CDDTPSGEN3_AddrVLEDOFF14           0xAE
#define CDDTPSGEN3_AddrVLEDOFF15           0xAF
#define CDDTPSGEN3_AddrVLEDOFF16           0xB0

#define CDDTPSGEN3_AddrPWM_MISCOUNTL       0xB1
#define CDDTPSGEN3_AddrPWM_MISCOUNTH       0xB2

/* Reserved Memory (63 bytes)  between 0xB3 - 0xF2 */

//   Device Lot Information Registers
#define CDDTPSGEN3_AddrLOTINFO1            0xF7
#define CDDTPSGEN3_AddrLOTINFO2            0xF8
#define CDDTPSGEN3_AddrLOTINFO3            0xF9
#define CDDTPSGEN3_AddrLOTINFO4            0xFA

//   MTP Programming registers
#define CDDTPSGEN3_AddrMTP_PROG1           0xFB
#define CDDTPSGEN3_AddrMTP_PROG2           0xFC
#define CDDTPSGEN3_AddrMTP_PROG3           0xFD
#define CDDTPSGEN3_AddrMTP_PROG4           0xFE
#define CDDTPSGEN3_AddrICID                0xFF  // IC identification register

//=============================================================================
// type definitions
//=============================================================================

typedef enum {
  SLOWER_SLEWRATE                 = 0,  // 0.05V/us
  SLOW_SLEWRATE                   = 1,  // 0.1V/us
  MEDIUM_SLEWRATE                 = 2,  // 0.2V/us
  FAST_SLEWRATE                   = 3,  // 0.4V/us
  SATURATED_SLEW_RATE_DEFAULT     = 4   // 0.8V/us - slewrate saturated for values >=4 : 100, 101, 110, 111
}teCddTpsGen3_SlewRate;


typedef enum {
  CDDTPSGEN3_PARLED_NONE = 0,                 //S1=LED1-4 S2=LED5-8 S3=LED9-12 S4=LED13-16
  CDDTPSGEN3_PARLED_S1_P_S2 = 1,              //S1=LED1-4 S2=LED1-4 S3=LED9-12 S4=LED13-16
  CDDTPSGEN3_PARLED_S1_P_S2___S3_P_P4 = 2,    //S1=LED1-4 S2=LED1-4 S3=LED9-12 S4=LED9-12
  CDDTPSGEN3_PARLED_S1_P_S2_P_S3_P_S4 = 3     //S1=LED1-4 S2=LED1-4 S3=LED1-4  S4=LED1-4
}teCddTpsGen3_ParalelLed;

typedef enum {  // Tap Point (Bit Number)
  CDDTPSGEN3_CMWTAP_BIT16 = 0,                //2^16 Clock Cycles
  CDDTPSGEN3_CMWTAP_BIT17 = 1,                //2^17 Clock Cycles
  CDDTPSGEN3_CMWTAP_BIT18 = 2,                //2^18 Clock Cycles
  CDDTPSGEN3_CMWTAP_BIT19 = 3,                //2^19 Clock Cycles
  CDDTPSGEN3_CMWTAP_BIT20 = 4,                //2^20 Clock Cycles
  CDDTPSGEN3_CMWTAP_BIT21_DEFAULT = 5,        //2^21 Clock Cycles
  CDDTPSGEN3_CMWTAP_BIT22 = 6,                //2^22 Clock Cycles
  CDDTPSGEN3_CMWTAP_BIT23 = 7                 //2^23 Clock Cycles
}teCddTpsGen3_ComWatchdogTimerTap;

typedef enum {  // Default Widths (4 bit resolution) at Communication Watchdog Timeout
  CDDTPSGEN3_DEF_WIDTH_00p00 = 0,      //  0.00%
  CDDTPSGEN3_DEF_WIDTH_06p25 = 1,      //  6.25%
  CDDTPSGEN3_DEF_WIDTH_12p50 = 2,      // 12.50%
  CDDTPSGEN3_DEF_WIDTH_18p75 = 3,      // 18.75%
  CDDTPSGEN3_DEF_WIDTH_25p00 = 4,      // 25.00%
  CDDTPSGEN3_DEF_WIDTH_31p25 = 5,      // 31.25%
  CDDTPSGEN3_DEF_WIDTH_37p50 = 6,      // 37.50%
  CDDTPSGEN3_DEF_WIDTH_43p75 = 7,      // 43.75%
  CDDTPSGEN3_DEF_WIDTH_50p00 = 8,      // 50.00%
  CDDTPSGEN3_DEF_WIDTH_56p25 = 9,      // 56.25%
  CDDTPSGEN3_DEF_WIDTH_62p50 = 10,     // 62.50%
  CDDTPSGEN3_DEF_WIDTH_68p75 = 11,     // 68.75%
  CDDTPSGEN3_DEF_WIDTH_75p00 = 12,     // 75.00%
  CDDTPSGEN3_DEF_WIDTH_81p25 = 13,     // 81.25%
  CDDTPSGEN3_DEF_WIDTH_87p50 = 14,     // 87.50%
  CDDTPSGEN3_DEF_WIDTH_100p0 = 15      //100.00%
}teCddTpsGen3_DefaultWidth;

// Two System Clock frequencies are supported
typedef enum {
  CDDTPSGEN3_CLK_FREQ_8MHz  = 8u,   // 8Mhz
  CDDTPSGEN3_CLK_FREQ_16MHz = 16u  // 16MHz
} teCddTpsGen3_ClkFreq;

// table of the division factors for PWM tick
typedef enum {
  CDDTPSGEN3_CLK8_PWM_100HZ = 62U, // DIV1 = 1, DIV2 = 78, f ~ 100Hz,
  CDDTPSGEN3_CLK8_PWM_200HZ = 35U, // DIV1 = 1, DIV2 = 39, f ~ 200Hz,
  CDDTPSGEN3_CLK8_PWM_300HZ = 22U, // DIV1 = 1, DIV2 = 26, f ~ 300Hz,
  CDDTPSGEN3_CLK8_PWM_400HZ = 16U, // DIV1 = 1, DIV2 = 20, f ~ 400Hz,
  CDDTPSGEN3_CLK8_PWM_500HZ = 12U, // DIV1 = 1, DIV2 = 16, f ~ 500Hz, 
  CDDTPSGEN3_CLK8_PWM_600HZ = 9U,  // DIV1 = 1, DIV2 = 13, f ~ 600Hz
  CDDTPSGEN3_CLK8_PWM_700HZ = 7U,  // DIV1 = 1, DIV2 = 11, f ~ 700Hz,
  CDDTPSGEN3_CLK8_PWM_800HZ = 6U   // DIV1 = 1, DIV2 = 10, f ~ 800Hz,
} teCddTpsGen3_PwmFreq_SYSCLK8;

typedef enum {
  CDDTPSGEN3_CLK16_PWM_200HZ = 62U, // DIV1 = 1, DIV2 = 80, f ~ 200Hz,
  CDDTPSGEN3_CLK16_PWM_300HZ = 48U, // DIV1 = 1, DIV2 = 53, f ~ 300Hz,
  CDDTPSGEN3_CLK16_PWM_400HZ = 36U, // DIV1 = 1, DIV2 = 40, f ~ 400Hz,
  CDDTPSGEN3_CLK16_PWM_500HZ = 28U, // DIV1 = 1, DIV2 = 32, f ~ 500Hz, 
  CDDTPSGEN3_CLK16_PWM_600HZ = 23U, // DIV1 = 1, DIV2 = 27, f ~ 600Hz
  CDDTPSGEN3_CLK16_PWM_700HZ = 19U, // DIV1 = 1, DIV2 = 23, f ~ 700Hz,
  CDDTPSGEN3_CLK16_PWM_800HZ = 16U  // DIV1 = 1, DIV2 = 20, f ~ 800Hz,
} tCddTpsGen3_PwmFreq_SYSCLK16;

/*--------------------------------------------------------------------
     Obsolete for 664 family : ADCID register is incorporated to 
     provide backwards compatibility with legacy matrix manger devices. 
     There is no requirement to enable ADC conversion of the ADDR0 / 1
---------------------------------------------------------------------*/
typedef enum {
  CDDTPSGEN3_ADCID_DEVID_MAPPING = 0u,  // Up to  8 TPS92662 Devices on the Bus - Address range 0-7
  CDDTPSGEN3_ADCID_2BIT_MAPPING  = 1u,  // Up to 16 TPS92662 Devices on the Bus - Address range 0-15 
  CDDTPSGEN3_ADCID_3BIT_MAPPING  = 2u   // Up to 31 TPS92662 Devices on the Bus - Address range 0-30
}teCddTpsGen3_AdcId;   // obsolete for 664 family : ADCID register is incorporated to provide backwards compatibility with legacy matrix manger devices. There
                           //is no requirement to enable ADC conversion of the ADDR0 / 1


typedef enum {
  CDDTPSGEN3_DEV_ID00 = 0x20u,  // device with address  0
  CDDTPSGEN3_DEV_ID01 = 0x61u,  // device with address  1
  CDDTPSGEN3_DEV_ID02 = 0xE2u,  // device with address  2
  CDDTPSGEN3_DEV_ID03 = 0xA3u,  // device with address  3
  CDDTPSGEN3_DEV_ID04 = 0x64u,  // device with address  4
  CDDTPSGEN3_DEV_ID05 = 0x25u,  // device with address  5
  CDDTPSGEN3_DEV_ID06 = 0xA6u,  // device with address  6
  CDDTPSGEN3_DEV_ID07 = 0xE7u,  // device with address  7
  CDDTPSGEN3_DEV_ID08 = 0xA8u,  // device with address  8
  CDDTPSGEN3_DEV_ID09 = 0xE9u,  // device with address  9
  CDDTPSGEN3_DEV_ID10 = 0x6Au,  // device with address 10
  CDDTPSGEN3_DEV_ID11 = 0x2Bu,  // device with address 11
  CDDTPSGEN3_DEV_ID12 = 0xECu,  // device with address 12
  CDDTPSGEN3_DEV_ID13 = 0xADu,  // device with address 13
  CDDTPSGEN3_DEV_ID14 = 0x2Eu,  // device with address 14
  CDDTPSGEN3_DEV_ID15 = 0x6Fu,  // device with address 15
  CDDTPSGEN3_DEV_ID16 = 0xF0u,  // device with address 16
  CDDTPSGEN3_DEV_ID17 = 0xB1u,  // device with address 17
  CDDTPSGEN3_DEV_ID18 = 0x32u,  // device with address 18
  CDDTPSGEN3_DEV_ID19 = 0x73u,  // device with address 19
  CDDTPSGEN3_DEV_ID20 = 0xB4u,  // device with address 20
  CDDTPSGEN3_DEV_ID21 = 0xF5u,  // device with address 21
  CDDTPSGEN3_DEV_ID22 = 0x76u,  // device with address 22
  CDDTPSGEN3_DEV_ID23 = 0x37u,  // device with address 23
  CDDTPSGEN3_DEV_ID24 = 0x78u,  // device with address 24
  CDDTPSGEN3_DEV_ID25 = 0x39u,  // device with address 25
  CDDTPSGEN3_DEV_ID26 = 0xBAu,  // device with address 26
  CDDTPSGEN3_DEV_ID27 = 0xFBu,  // device with address 27
  CDDTPSGEN3_DEV_ID28 = 0x3Cu,  // device with address 28
  CDDTPSGEN3_DEV_ID29 = 0x7Du,  // device with address 29
  CDDTPSGEN3_DEV_ID30 = 0xFEu,  // device with address 30
  CDDTPSGEN3_BROADCAST = 0xBFu   // device with address 31
} teCddTpsGen3_DEVIDByte_WithParity;

//=============================================================================
// Type definition for Configuration and control registers
//=============================================================================


#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)

//=============================================================================
// Type definition for Configuration and control registers
//=============================================================================

// ADDR 0x00
typedef struct tsCddTpsGen3_Bit_RegMTPCFG
{
  uint8 biMTPPHASE    : 2;
  uint8 biMTPDEFWIDTH : 2;
  uint8 biSTANDALONE  : 1;
  uint8 biFS_PIN      : 1;
  uint8 biEN_VDD_OV   : 1;
  uint8 biCLKDIV2     : 1;
}tsCddTpsGen3_Bit_RegMTPCFG;

// ADDR 0x01
typedef struct tsCddTpsGen3_Bit_RegOUTCTRL
{
  uint8 biLVDS_TX     : 1;
  uint8 biSYNCPEN     : 1;
  uint8 biSYNCOEN     : 1;
  uint8 biSTRENGTH    : 2;
  uint8 biPARLED      : 2;
  uint8 biDRV_CHK     : 1;
}tsCddTpsGen3_Bit_RegOUTCTRL;


//=============================================================================
// Type definition for Thermal Limit and Slew Rate Registers
//=============================================================================

// ADDR 0x02
typedef struct tsCddTpsGen3_Bit_RegTWLMT
{
  uint8 biTWLMT       : 8;
}tsCddTpsGen3_Bit_RegTWLMT;

// ADDR 0x03
typedef struct tsCddTpsGen3_Bit_RegSLEWL
{
  uint8 biSLEW_04_01  : 3;
  uint8 biSLEW_08_05  : 3;
  uint8 biUNUSED      : 2;
}tsCddTpsGen3_Bit_RegSLEWL;

// ADDR 0x04
typedef struct tsCddTpsGen3_Bit_RegSLEWH
{
  uint8 biSLEW_12_09  : 3;
  uint8 biSLEW_16_13  : 3;
  uint8 biUNUSED      : 2;
}tsCddTpsGen3_Bit_RegSLEWH;


//=============================================================================
// Type definition for Default Pulse Width Registers
//=============================================================================

// ADDR 0x05
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH01
{
  uint8 biDEFWIDTH01  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH01;

// ADDR 0x06
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH02
{
  uint8 biDEFWIDTH02  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH02;

// ADDR 0x07
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH03
{
  uint8 biDEFWIDTH03  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH03;

// ADDR 0x08
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH04
{
  uint8 biDEFWIDTH04  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH04;

// ADDR 0x09
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH05
{
  uint8 biDEFWIDTH05  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH05;

// ADDR 0x0A
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH06
{
  uint8 biDEFWIDTH06  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH06;

// ADDR 0x0B
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH07
{
  uint8 biDEFWIDTH07  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH07;

// ADDR 0x0C
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH08
{
  uint8 biDEFWIDTH08  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH08;

// ADDR 0x0D
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH09
{
  uint8 biDEFWIDTH09  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH09;

// ADDR 0x0E
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH10
{
  uint8 biDEFWIDTH10  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH10;

// ADDR 0x0F
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH11
{
  uint8 biDEFWIDTH11  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH11;

// ADDR 0x10
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH12
{
  uint8 biDEFWIDTH12  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH12;

// ADDR 0x11
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH13
{
  uint8 biDEFWIDTH13  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH13;

// ADDR 0x12
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH14
{
  uint8 biDEFWIDTH14  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH14;

// ADDR 0x13
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH15
{
  uint8 biDEFWIDTH15  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH15;

// ADDR 0x14
typedef struct tsCddTpsGen3_Bit_RegDEFWIDTH16
{
  uint8 biDEFWIDTH16  : 8;
}tsCddTpsGen3_Bit_RegDEFWIDTH16;

//=============================================================================
// Type definition for LED PWM Phase - Shift and Width Registers
//=============================================================================

// ADDR 0x15
typedef struct tsCddTpsGen3_Bit_RegPHASE01H
{
  uint8 biPHASE01 : 8;
}tsCddTpsGen3_Bit_RegPHASE01H;

// ADDR 0x16
typedef struct tsCddTpsGen3_Bit_RegPHASE02H
{
  uint8 biPHASE02 : 8;
}tsCddTpsGen3_Bit_RegPHASE02H;

// ADDR 0x17
typedef struct tsCddTpsGen3_Bit_RegPHASE03H
{
  uint8 biPHASE03 : 8;
}tsCddTpsGen3_Bit_RegPHASE03H;

// ADDR 0x18
typedef struct tsCddTpsGen3_Bit_RegPHASE04H
{
  uint8 biPHASE04 : 8;
}tsCddTpsGen3_Bit_RegPHASE04H;

// ADDR 0x19
typedef struct tsCddTpsGen3_Bit_RegPHASE05H
{
  uint8 biPHASE05 : 8;
}tsCddTpsGen3_Bit_RegPHASE05H;

// ADDR 0x1A
typedef struct tsCddTpsGen3_Bit_RegPHASE06H
{
  uint8 biPHASE06 : 8;
}tsCddTpsGen3_Bit_RegPHASE06H;

// ADDR 0x1B
typedef struct tsCddTpsGen3_Bit_RegPHASE07H
{
  uint8 biPHASE07 : 8;
}tsCddTpsGen3_Bit_RegPHASE07H;

// ADDR 0x1C
typedef struct tsCddTpsGen3_Bit_RegPHASE08H
{
  uint8 biPHASE08 : 8;
}tsCddTpsGen3_Bit_RegPHASE08H;

// ADDR 0x1D
typedef struct tsCddTpsGen3_Bit_RegPHASE09H
{
  uint8 biPHASE09 : 8;
}tsCddTpsGen3_Bit_RegPHASE09H;

// ADDR 0x1E
typedef struct tsCddTpsGen3_Bit_RegPHASE10H
{
  uint8 biPHASE10 : 8;
}tsCddTpsGen3_Bit_RegPHASE10H;

// ADDR 0x1F
typedef struct tsCddTpsGen3_Bit_RegPHASE11H
{
  uint8 biPHASE11 : 8;
}tsCddTpsGen3_Bit_RegPHASE11H;

// ADDR 0x20
typedef struct tsCddTpsGen3_Bit_RegPHASE12H
{
  uint8 biPHASE12 : 8;
}tsCddTpsGen3_Bit_RegPHASE12H;

// ADDR 0x21
typedef struct tsCddTpsGen3_Bit_RegPHASE13H
{
  uint8 biPHASE13 : 8;
}tsCddTpsGen3_Bit_RegPHASE13H;

// ADDR 0x22
typedef struct tsCddTpsGen3_Bit_RegPHASE14H
{
  uint8 biPHASE14 : 8;
}tsCddTpsGen3_Bit_RegPHASE14H;

// ADDR 0x23
typedef struct tsCddTpsGen3_Bit_RegPHASE15H
{
  uint8 biPHASE15 : 8;
}tsCddTpsGen3_Bit_RegPHASE15H;

// ADDR 0x24
typedef struct tsCddTpsGen3_Bit_RegPHASE16H
{
  uint8 biPHASE16 : 8;
}tsCddTpsGen3_Bit_RegPHASE16H;

// ADDR 0x25
typedef struct tsCddTpsGen3_Bit_RegPHASE04_01L
{
  uint8 biPHASE01 : 2;
  uint8 biPHASE02 : 2;
  uint8 biPHASE03 : 2;
  uint8 biPHASE04 : 2;
}tsCddTpsGen3_Bit_RegPHASE04_01L;

// ADDR 0x26
typedef struct tsCddTpsGen3_Bit_RegPHASE08_05L
{
  uint8 biPHASE05 : 2;
  uint8 biPHASE06 : 2;
  uint8 biPHASE07 : 2;
  uint8 biPHASE08 : 2;
}tsCddTpsGen3_Bit_RegPHASE08_05L;

// ADDR 0x27
typedef struct tsCddTpsGen3_Bit_RegPHASE12_09L
{
  uint8 biPHASE09 : 2;
  uint8 biPHASE10 : 2;
  uint8 biPHASE11 : 2;
  uint8 biPHASE12 : 2;
}tsCddTpsGen3_Bit_RegPHASE12_09L;

// ADDR 0x28
typedef struct tsCddTpsGen3_Bit_RegPHASE16_13L
{
  uint8 biPHASE13 : 2;
  uint8 biPHASE14 : 2;
  uint8 biPHASE15 : 2;
  uint8 biPHASE16 : 2;
}tsCddTpsGen3_Bit_RegPHASE16_13L;

// ADDR 0x29
typedef struct tsCddTpsGen3_Bit_RegWIDTH01H
{
  uint8 biWIDTH01 : 8;
}tsCddTpsGen3_Bit_RegWIDTH01H;

// ADDR 0x2A
typedef struct tsCddTpsGen3_Bit_RegWIDTH02H
{
  uint8 biWIDTH02 : 8;
}tsCddTpsGen3_Bit_RegWIDTH02H;

// ADDR 0x2B
typedef struct tsCddTpsGen3_Bit_RegWIDTH03H
{
  uint8 biWIDTH03 : 8;
}tsCddTpsGen3_Bit_RegWIDTH03H;

// ADDR 0x2C
typedef struct tsCddTpsGen3_Bit_RegWIDTH04H
{
  uint8 biWIDTH04 : 8;
}tsCddTpsGen3_Bit_RegWIDTH04H;

// ADDR 0x2D
typedef struct tsCddTpsGen3_Bit_RegWIDTH05H
{
  uint8 biWIDTH05 : 8;
}tsCddTpsGen3_Bit_RegWIDTH05H;

// ADDR 0x2E
typedef struct tsCddTpsGen3_Bit_RegWIDTH06H
{
  uint8 biWIDTH06 : 8;
}tsCddTpsGen3_Bit_RegWIDTH06H;

// ADDR 0x2F
typedef struct tsCddTpsGen3_Bit_RegWIDTH07H
{
  uint8 biWIDTH07 : 8;
}tsCddTpsGen3_Bit_RegWIDTH07H;

// ADDR 0x30
typedef struct tsCddTpsGen3_Bit_RegWIDTH08H
{
  uint8 biWIDTH08 : 8;
}tsCddTpsGen3_Bit_RegWIDTH08H;

// ADDR 0x31
typedef struct tsCddTpsGen3_Bit_RegWIDTH09H
{
  uint8 biWIDTH09 : 8;
}tsCddTpsGen3_Bit_RegWIDTH09H;

// ADDR 0x32
typedef struct tsCddTpsGen3_Bit_RegWIDTH10H
{
  uint8 biWIDTH10 : 8;
}tsCddTpsGen3_Bit_RegWIDTH10H;

// ADDR 0x33
typedef struct tsCddTpsGen3_Bit_RegWIDTH11H
{
  uint8 biWIDTH11 : 8;
}tsCddTpsGen3_Bit_RegWIDTH11H;

// ADDR 0x34
typedef struct tsCddTpsGen3_Bit_RegWIDTH12H
{
  uint8 biWIDTH12 : 8;
}tsCddTpsGen3_Bit_RegWIDTH12H;

// ADDR 0x35
typedef struct tsCddTpsGen3_Bit_RegWIDTH13H
{
  uint8 biWIDTH13 : 8;
}tsCddTpsGen3_Bit_RegWIDTH13H;

// ADDR 0x36
typedef struct tsCddTpsGen3_Bit_RegWIDTH14H
{
  uint8 biWIDTH14 : 8;
}tsCddTpsGen3_Bit_RegWIDTH14H;

// ADDR 0x37
typedef struct tsCddTpsGen3_Bit_RegWIDTH15H
{
  uint8 biWIDTH15 : 8;
}tsCddTpsGen3_Bit_RegWIDTH15H;

// ADDR 0x38
typedef struct tsCddTpsGen3_Bit_RegWIDTH16H
{
  uint8 biWIDTH16 : 8;
}tsCddTpsGen3_Bit_RegWIDTH16H;

// ADDR 0x39
typedef struct tsCddTpsGen3_Bit_RegWIDTH04_01L
{
  uint8 biWIDTH01 : 2;
  uint8 biWIDTH02 : 2;
  uint8 biWIDTH03 : 2;
  uint8 biWIDTH04 : 2;
}tsCddTpsGen3_Bit_RegWIDTH04_01L;

// ADDR 0x3A
typedef struct tsCddTpsGen3_Bit_RegWIDTH08_05L
{
  uint8 biWIDTH05 : 2;
  uint8 biWIDTH06 : 2;
  uint8 biWIDTH07 : 2;
  uint8 biWIDTH08 : 2;
}tsCddTpsGen3_Bit_RegWIDTH08_05L;

// ADDR 0x3B
typedef struct tsCddTpsGen3_Bit_RegWIDTH12_09L
{
  uint8 biWIDTH09 : 2;
  uint8 biWIDTH10 : 2;
  uint8 biWIDTH11 : 2;
  uint8 biWIDTH12 : 2;
}tsCddTpsGen3_Bit_RegWIDTH12_09L;

// ADDR 0x3C
typedef struct tsCddTpsGen3_Bit_RegWIDTH16_13L
{
  uint8 biWIDTH13 : 2;
  uint8 biWIDTH14 : 2;
  uint8 biWIDTH15 : 2;
  uint8 biWIDTH16 : 2;
}tsCddTpsGen3_Bit_RegWIDTH16_13L;

//=============================================================================
// Type definition for BANK (GROUP) LED PWM Phase - Shift and Width Registers
//=============================================================================

// ADDR 0x3D
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE01L
{
  uint8 biBANK_PHASE01 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE01L;

// ADDR 0x3E
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE02L
{
  uint8 biBANK_PHASE02 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE02L;

// ADDR 0x3F
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE03L
{
  uint8 biBANK_PHASE03 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE03L;

// ADDR 0x40
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE04L
{
  uint8 biBANK_PHASE04 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE04L;

// ADDR 0x41
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE04_01H
{
  uint8 biBANK_PHASE01 : 2;
  uint8 biBANK_PHASE02 : 2;
  uint8 biBANK_PHASE03 : 2;
  uint8 biBANK_PHASE04 : 2;
}tsCddTpsGen3_Bit_RegBANK_PHASE04_01H;

// ADDR 0x42
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE05L
{
  uint8 biBANK_PHASE05 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE05L;

// ADDR 0x43
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE06L
{
  uint8 biBANK_PHASE06 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE06L;

// ADDR 0x44
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE07L
{
  uint8 biBANK_PHASE07 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE07L;

// ADDR 0x45
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE08L
{
  uint8 biBANK_PHASE08 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE08L;

// ADDR 0x46
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE08_05H
{
  uint8 biBANK_PHASE05 : 2;
  uint8 biBANK_PHASE06 : 2;
  uint8 biBANK_PHASE07 : 2;
  uint8 biBANK_PHASE08 : 2;
}tsCddTpsGen3_Bit_RegBANK_PHASE08_05H;

// ADDR 0x47
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE09L
{
  uint8 biBANK_PHASE09 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE09L;

// ADDR 0x48
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE10L
{
  uint8 biBANK_PHASE10 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE10L;

// ADDR 0x49
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE11L
{
  uint8 biBANK_PHASE11 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE11L;

// ADDR 0x4A
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE12L
{
  uint8 biBANK_PHASE12 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE12L;

// ADDR 0x4B
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE12_09H
{
  uint8 biBANK_PHASE09 : 2;
  uint8 biBANK_PHASE10 : 2;
  uint8 biBANK_PHASE11 : 2;
  uint8 biBANK_PHASE12 : 2;
}tsCddTpsGen3_Bit_RegBANK_PHASE12_09H;

// ADDR 0x4C
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE13L
{
  uint8 biBANK_PHASE13 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE13L;

// ADDR 0x4D
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE14L
{
  uint8 biBANK_PHASE14 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE14L;

// ADDR 0x4E
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE15L
{
  uint8 biBANK_PHASE15 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE15L;

// ADDR 0x4F
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE16L
{
  uint8 biBANK_PHASE16 : 8;
}tsCddTpsGen3_Bit_RegBANK_PHASE16L;

// ADDR 0x50
typedef struct tsCddTpsGen3_Bit_RegBANK_PHASE16_13H
{
  uint8 biBANK_PHASE13 : 2;
  uint8 biBANK_PHASE14 : 2;
  uint8 biBANK_PHASE15 : 2;
  uint8 biBANK_PHASE16 : 2;
}tsCddTpsGen3_Bit_RegBANK_PHASE16_13H;

// ADDR 0x51
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH01L
{
  uint8 biBANK_WIDTH01 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH01L;

// ADDR 0x52
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH02L
{
  uint8 biBANK_WIDTH02 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH02L;

// ADDR 0x53
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH03L
{
  uint8 biBANK_WIDTH03 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH03L;

// ADDR 0x54
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH04L
{
  uint8 biBANK_WIDTH04 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH04L;

// ADDR 0x55
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH04_01H
{
  uint8 biBANK_WIDTH01 : 2;
  uint8 biBANK_WIDTH02 : 2;
  uint8 biBANK_WIDTH03 : 2;
  uint8 biBANK_WIDTH04 : 2;
}tsCddTpsGen3_Bit_RegBANK_WIDTH04_01H;

// ADDR 0x56
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH05L
{
  uint8 biBANK_WIDTH05 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH05L;

// ADDR 0x57
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH06L
{
  uint8 biBANK_WIDTH06 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH06L;

// ADDR 0x58
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH07L
{
  uint8 biBANK_WIDTH07 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH07L;

// ADDR 0x59
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH08L
{
  uint8 biBANK_WIDTH08 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH08L;

// ADDR 0x5A
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH08_05H
{
  uint8 biBANK_WIDTH05 : 2;
  uint8 biBANK_WIDTH06 : 2;
  uint8 biBANK_WIDTH07 : 2;
  uint8 biBANK_WIDTH08 : 2;
}tsCddTpsGen3_Bit_RegBANK_WIDTH08_05H;

// ADDR 0x5B
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH09L
{
  uint8 biBANK_WIDTH09 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH09L;

// ADDR 0x5C
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH10L
{
  uint8 biBANK_WIDTH10 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH10L;

// ADDR 0x5D
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH11L
{
  uint8 biBANK_WIDTH11 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH11L;

// ADDR 0x5E
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH12L
{
  uint8 biBANK_WIDTH12 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH12L;

// ADDR 0x5F
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH12_09H
{
  uint8 biBANK_WIDTH09 : 2;
  uint8 biBANK_WIDTH10 : 2;
  uint8 biBANK_WIDTH11 : 2;
  uint8 biBANK_WIDTH12 : 2;
}tsCddTpsGen3_Bit_RegBANK_WIDTH12_09H;

// ADDR 0x60
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH13L
{
  uint8 biBANK_WIDTH13 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH13L;

// ADDR 0x61
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH14L
{
  uint8 biBANK_WIDTH14 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH14L;

// ADDR 0x62
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH15L
{
  uint8 biBANK_WIDTH15 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH15L;

// ADDR 0x63
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH16L
{
  uint8 biBANK_WIDTH16 : 8;
}tsCddTpsGen3_Bit_RegBANK_WIDTH16L;

// ADDR 0x64
typedef struct tsCddTpsGen3_Bit_RegBANK_WIDTH16_13H
{
  uint8 biBANK_WIDTH13 : 2;
  uint8 biBANK_WIDTH14 : 2;
  uint8 biBANK_WIDTH15 : 2;
  uint8 biBANK_WIDTH16 : 2;
}tsCddTpsGen3_Bit_RegBANK_WIDTH16_13H;

//=============================================================================
// Type definition for RESERVED MEMORY AREA (0x68 - 0x6F)
//=============================================================================

// ADDR 0x68 - 0x6F
typedef struct tsCddTpsGen3_RegRESERVED_0x6F_0x68
{
  uint8 aucUNUSED_0x6F_0x68[11];
}tsCddTpsGen3_RegRESERVED_0x6F_0x68;

//=============================================================================
// Type definition for LEDON Treshold Registers
//=============================================================================

// ADDR 0x70
typedef struct tsCddTpsGen3_Bit_RegLEDONTH01
{
  uint8 biLEDONTH01L : 3;
  uint8 biLEDONTH01H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH01;

// ADDR 0x71
typedef struct tsCddTpsGen3_Bit_RegLEDONTH02
{
  uint8 biLEDONTH02L : 3;
  uint8 biLEDONTH02H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH02;

// ADDR 0x72
typedef struct tsCddTpsGen3_Bit_RegLEDONTH03
{
  uint8 biLEDONTH03L : 3;
  uint8 biLEDONTH03H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH03;

// ADDR 0x73
typedef struct tsCddTpsGen3_Bit_RegLEDONTH04
{
  uint8 biLEDONTH04L : 3;
  uint8 biLEDONTH04H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH04;

// ADDR 0x74
typedef struct tsCddTpsGen3_Bit_RegLEDONTH05
{
  uint8 biLEDONTH05L : 3;
  uint8 biLEDONTH05H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH05;

// ADDR 0x75
typedef struct tsCddTpsGen3_Bit_RegLEDONTH06
{
  uint8 biLEDONTH06L : 3;
  uint8 biLEDONTH06H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH06;

// ADDR 0x76
typedef struct tsCddTpsGen3_Bit_RegLEDNTH07
{
  uint8 biLEDONTH07L : 3;
  uint8 biLEDONTH07H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH07;

// ADDR 0x77
typedef struct tsCddTpsGen3_Bit_RegLEDONTH08
{
  uint8 biLEDONTH08L : 3;
  uint8 biLEDONTH08H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH08;

// ADDR 0x78
typedef struct tsCddTpsGen3_Bit_RegLEDONTH09
{
  uint8 biLEDONTH09L : 3;
  uint8 biLEDONTH09H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH09;

// ADDR 0x79
typedef struct tsCddTpsGen3_Bit_RegLEDONTH10
{
  uint8 biLEDONTH10L : 3;
  uint8 biLEDONTH10H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH10;

// ADDR 0x7A
typedef struct tsCddTpsGen3_Bit_RegLEDONTH11
{
  uint8 biLEDONTH11L : 3;
  uint8 biLEDONTH11H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH11;

// ADDR 0x7B
typedef struct tsCddTpsGen3_Bit_RegLEDONTH12
{
  uint8 biLEDONTH12L : 3;
  uint8 biLEDONTH12H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH12;

// ADDR 0x7C
typedef struct tsCddTpsGen3_Bit_RegLEDONTH13
{
  uint8 biLEDONTH13L : 3;
  uint8 biLEDONTH13H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH13;

// ADDR 0x7D
typedef struct tsCddTpsGen3_Bit_RegLEDONTH14
{
  uint8 biLEDONTH14L : 3;
  uint8 biLEDONTH14H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH14;

// ADDR 0x7E
typedef struct tsCddTpsGen3_Bit_RegLEDONTH15
{
  uint8 biLEDONTH15L : 3;
  uint8 biLEDONTH15H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH15;

// ADDR 0x7F
typedef struct tsCddTpsGen3_Bit_RegLEDONTH16
{
  uint8 biLEDONTH16L : 3;
  uint8 biLEDONTH16H : 5;
}tsCddTpsGen3_Bit_RegLEDONTH16;

//=============================================================================
// Type definition for System Configuration Register
//=============================================================================

// ADDR 0x80
typedef struct tsCddTpsGen3_Bit_RegSYSCFG
{
  uint8 biCSEN      : 1;
  uint8 biCHPMP_SS  : 1;
  uint8 biCSGAIN    : 1;
  uint8 biCMWEN     : 1;
  uint8 biPSON      : 1;
  uint8 biACKEN     : 1;
  uint8 biLEDADCEN  : 1;
  uint8 biSEPTR     : 1;
}tsCddTpsGen3_Bit_RegSYSCFG;

//=============================================================================
// Type definition for Communications Watchdog Timer Tap Point Register
//=============================================================================

// ADDR 0x81
typedef struct tsCddTpsGen3_Bit_RegCMWTAP
{
  uint8 biCMWTAP : 3;
  uint8 biUNUSED : 5;
}tsCddTpsGen3_Bit_RegCMWTAP;

//=============================================================================
// Type definition for PWM Tick Period Register
//=============================================================================

// ADDR 0x82
typedef struct tsCddTpsGen3_Bit_RegPWMTICK
{
  uint8 biPTCNT  : 6;
  uint8 biPTBASE : 2;
}tsCddTpsGen3_Bit_RegPWMTICK;

//=============================================================================
// Type definition for ADC ID Register
//=============================================================================

// ADDR 0x83
typedef struct tsCddTpsGen3_Bit_RegADCID
{
  uint8 biUNUSED : 8;
}tsCddTpsGen3_Bit_RegADCID;

//=============================================================================
// Type definition for CLOCK and SYNCHRONIZATION Register
//=============================================================================

// ADDR 0x84
typedef struct tsCddTpsGen3_Bit_RegCLK_SYNC
{
  uint8 biSSYNC       : 1;
  uint8 biCLK_IS_EXT  : 1;
  uint8 biVDD_OV_FLT  : 1;
  uint8 biUNUSED      : 5;
}tsCddTpsGen3_Bit_RegCLK_SYNC;

//=============================================================================
// Type definition for STATUS Register
//=============================================================================

// ADDR 0x85
typedef struct tsCddTpsGen3_Bit_RegSTATUS
{
  uint8 biPWR       : 1;
  uint8 biMTP_ERR   : 1;
  uint8 biTW        : 1;
  uint8 biTRIM_ERR  : 1;
  uint8 biLIMP_HOME : 1;
  uint8 biVLED_ERR  : 1;
  uint8 biCHPMP_ERR : 1;
  uint8 biPWM_ERR   : 1;
}tsCddTpsGen3_Bit_RegSTATUS;

//=============================================================================
// Type definition for ELECTRICAL FAULTS Registers
//=============================================================================

// ADDR 0x86
typedef struct tsCddTpsGen3_Bit_RegFLT_OPEN_OR_DRVL
{
  uint8 biFLT_OPEN_OR_DRV : 8;
}tsCddTpsGen3_Bit_RegFLT_OPEN_OR_DRVL;

// ADDR 0x87
typedef struct tsCddTpsGen3_Bit_RegFLT_OPEN_OR_DRVH
{
  uint8 biFLT_OPEN_OR_DRV : 8;
}tsCddTpsGen3_Bit_RegFLT_OPEN_OR_DRVH;

// ADDR 0x88
typedef struct tsCddTpsGen3_Bit_RegFAULT_SHORTL
{
  uint8 biFAULT_SHORT : 8;
}tsCddTpsGen3_Bit_RegFAULT_SHORTL;

// ADDR 0x89
typedef struct tsCddTpsGen3_Bit_RegFAULT_SHORTH
{
  uint8 biFAULT_SHORT : 8;
}tsCddTpsGen3_Bit_RegFAULT_SHORTH;

// ADDR 0x8A
typedef struct tsCddTpsGen3_Bit_RegFAULT_RESFETL
{
  uint8 biFAULT_RESFET : 8;
}tsCddTpsGen3_Bit_RegFAULT_RESFETL;

// ADDR 0x8B
typedef struct tsCddTpsGen3_Bit_RegFAULT_RESFETH
{
  uint8 biFAULT_RESFET : 8;
}tsCddTpsGen3_Bit_RegFAULT_RESFETH;

//=============================================================================
// Type definition for CRC ERROR COUNT Registers
//=============================================================================

// ADDR 0x8C
typedef struct tsCddTpsGen3_Bit_RegCERRCNT
{
  uint8 biCERRCNT : 8;
}tsCddTpsGen3_Bit_RegCERRCNT;

//=============================================================================
// Type definition for Non-LED ADC Input Registers: ADC1, ADC2, DIETEMP, CS
// (Current Sense)
//=============================================================================

// ADDR 0x8D
typedef struct tsCddTpsGen3_Bit_RegADC1
{
  uint8 biADC1 : 8;
}tsCddTpsGen3_Bit_RegADC1;

// ADDR 0x8E
typedef struct tsCddTpsGen3_Bit_RegADC2
{
  uint8 biADC2 : 8;
}tsCddTpsGen3_Bit_RegADC2;

// ADDR 0x8F
typedef struct tsCddTpsGen3_Bit_RegDIETEMP
{
  uint8 biDIETEMP : 8;
}tsCddTpsGen3_Bit_RegDIETEMP;

// ADDR 0x90
typedef struct tsCddTpsGen3_Bit_RegCS
{
  uint8 biCS : 8;
}tsCddTpsGen3_Bit_RegCS;

//=============================================================================
// Type definition for LED ADC  Registers
//=============================================================================

// ADDR 0x91
typedef struct tsCddTpsGen3_Bit_RegVLEDON01
{
  uint8 biVLEDON01 : 8;
}tsCddTpsGen3_Bit_RegVLEDON01;

// ADDR 0x92
typedef struct tsCddTpsGen3_Bit_RegVLEDON02
{
  uint8 biVLEDON02 : 8;
}tsCddTpsGen3_Bit_RegVLEDON02;

// ADDR 0x93
typedef struct tsCddTpsGen3_Bit_RegVLEDON03
{
  uint8 biVLEDON03 : 8;
}tsCddTpsGen3_Bit_RegVLEDON03;

// ADDR 0x94
typedef struct tsCddTpsGen3_Bit_RegVLEDON04
{
  uint8 biVLEDON04 : 8;
}tsCddTpsGen3_Bit_RegVLEDON04;

// ADDR 0x95
typedef struct tsCddTpsGen3_Bit_RegVLEDON05
{
  uint8 biVLEDON05 : 8;
}tsCddTpsGen3_Bit_RegVLEDON05;

// ADDR 0x96
typedef struct tsCddTpsGen3_Bit_RegVLEDON06
{
  uint8 biVLEDON06 : 8;
}tsCddTpsGen3_Bit_RegVLEDON06;

// ADDR 0x97
typedef struct tsCddTpsGen3_Bit_RegVLEDON07
{
  uint8 biVLEDON07 : 8;
}tsCddTpsGen3_Bit_RegVLEDON07;

// ADDR 0x98
typedef struct tsCddTpsGen3_Bit_RegVLEDON08
{
  uint8 biVLEDON08 : 8;
}tsCddTpsGen3_Bit_RegVLEDON08;

// ADDR 0x99
typedef struct tsCddTpsGen3_Bit_RegVLEDON09
{
  uint8 biVLEDON09 : 8;
}tsCddTpsGen3_Bit_RegVLEDON09;

// ADDR 0x9A
typedef struct tsCddTpsGen3_Bit_RegVLEDON10
{
  uint8 biVLEDON10 : 8;
}tsCddTpsGen3_Bit_RegVLEDON10;

// ADDR 0x9B
typedef struct tsCddTpsGen3_Bit_RegVLEDON11
{
  uint8 biVLEDON11 : 8;
}tsCddTpsGen3_Bit_RegVLEDON11;

// ADDR 0x9C
typedef struct tsCddTpsGen3_Bit_RegVLEDON12
{
  uint8 biVLEDON12 : 8;
}tsCddTpsGen3_Bit_RegVLEDON12;

// ADDR 0x9D
typedef struct tsCddTpsGen3_Bit_RegVLEDON13
{
  uint8 biVLEDON13 : 8;
}tsCddTpsGen3_Bit_RegVLEDON13;

// ADDR 0x9E
typedef struct tsCddTpsGen3_Bit_RegVLEDON14
{
  uint8 biVLEDON14 : 8;
}tsCddTpsGen3_Bit_RegVLEDON14;

// ADDR 0x9F
typedef struct tsCddTpsGen3_Bit_RegVLEDON15
{
  uint8 biVLEDON15 : 8;
}tsCddTpsGen3_Bit_RegVLEDON15;

// ADDR 0xA0
typedef struct tsCddTpsGen3_Bit_RegVLEDON16
{
  uint8 biVLEDON16 : 8;
}tsCddTpsGen3_Bit_RegVLEDON16;

// ADDR 0xA1
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF01
{
  uint8 biVLEDOFF01 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF01;

// ADDR 0xA2
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF02
{
  uint8 biVLEDOFF02 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF02;

// ADDR 0xA3
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF03
{
  uint8 biVLEDOFF03 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF03;

// ADDR 0xA4
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF04
{
  uint8 biVLEDOFF04 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF04;

// ADDR 0xA5
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF05
{
  uint8 biVLEDOFF05 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF05;

// ADDR 0xA6
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF06
{
  uint8 biVLEDOFF06 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF06;

// ADDR 0xA7
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF07
{
  uint8 biVLEDOFF07 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF07;

// ADDR 0xA8
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF08
{
  uint8 biVLEDOFF08 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF08;

// ADDR 0xA9
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF09
{
  uint8 biVLEDOFF09 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF09;

// ADDR 0xAA
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF10
{
  uint8 biVLEDOFF10 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF10;

// ADDR 0xAB
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF11
{
  uint8 biVLEDOFF11 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF11;

// ADDR 0xAC
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF12
{
  uint8 biVLEDOFF12 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF12;

// ADDR 0xAD
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF13
{
  uint8 biVLEDOFF13 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF13;

// ADDR 0xAE
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF14
{
  uint8 biVLEDOFF14 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF14;

// ADDR 0xAF
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF15
{
  uint8 biVLEDOFF15 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF15;

// ADDR 0xB0
typedef struct tsCddTpsGen3_Bit_RegVLEDOFF16
{
  uint8 biVLEDOFF16 : 8;
}tsCddTpsGen3_Bit_RegVLEDOFF16;

//=============================================================================
// Type definition for PWM MISCOUNT Registers
//=============================================================================

// ADDR 0xB1
typedef struct tsCddTpsGen3_Bit_RegPWM_MISCOUNTL
{
  uint8 biPWM_MISCOUNT : 8;
}tsCddTpsGen3_Bit_RegPWM_MISCOUNTL;

// ADDR 0xB2
typedef struct tsCddTpsGen3_Bit_RegPWM_MISCOUNTH
{
  uint8 biPWM_MISCOUNT : 8;
}tsCddTpsGen3_Bit_RegPWM_MISCOUNTH;

//=============================================================================
// Type definition for RESERVED MEMORY AREA (0xB3 - 0xF6)
//=============================================================================

// ADDR 0xB3 - 0xF6
typedef struct tsCddTpsGen3_RegRESERVED_0xF6_0xB3
{
  uint8 aucUNUSED_0xF6_0xB3[69];
}tsCddTpsGen3_RegRESERVED_0xF6_0xB3;

//=============================================================================
// Type definition for LOT INFORMATION Registers
//=============================================================================

// ADDR 0xF7
typedef struct tsCddTpsGen3_Bit_RegLOTINFO1
{
  uint8 biLOTINFO : 8;
}tsCddTpsGen3_Bit_RegLOTINFO1;

// ADDR 0xF8
typedef struct tsCddTpsGen3_Bit_RegLOTINFO2
{
  uint8 biLOTINFO : 8;
}tsCddTpsGen3_Bit_RegLOTINFO2;

// ADDR 0xF9
typedef struct tsCddTpsGen3_Bit_RegLOTINFO3
{
  uint8 biLOTINFO : 8;
}tsCddTpsGen3_Bit_RegLOTINFO3;

// ADDR 0xFA
typedef struct tsCddTpsGen3_Bit_RegLOTINFO4
{
  uint8 biLOTINFO : 8;
}tsCddTpsGen3_Bit_RegLOTINFO4;

//=============================================================================
// Type definition for MTP (Multi-Time Programmable Memory) PROGRAMMING Registers
//=============================================================================

// ADDR 0xFB
typedef struct tsCddTpsGen3_Bit_RegMTP_PROG1
{
  uint8 biMTP_PROG : 8;
}tsCddTpsGen3_Bit_RegMTP_PROG1;

// ADDR 0xFC
typedef struct tsCddTpsGen3_Bit_RegMTP_PROG2
{
  uint8 biMTP_PROG : 8;
}tsCddTpsGen3_Bit_RegMTP_PROG2;

// ADDR 0xFD
typedef struct tsCddTpsGen3_Bit_RegMTP_PROG3
{
  uint8 biMTP_PROG : 8;
}tsCddTpsGen3_Bit_RegMTP_PROG3;

// ADDR 0xFE
typedef struct tsCddTpsGen3_Bit_RegMTP_PROG4
{
  uint8 biMTP_PROG : 8;
}tsCddTpsGen3_Bit_RegMTP_PROG4;

//=============================================================================
// Type definition for IC Identification Register
//=============================================================================

// ADDR 0xFF
typedef struct tsCddTpsGen3_Bit_RegICID
{
  uint8 biICID : 8;
}tsCddTpsGen3_Bit_RegICID;

#else
#error CPU_BYTE_ORDER == HIGH_BYTE_FIRST not supported
#endif  //(CPU_BYTE_ORDER == LOW_BYTE_FIRST)


// R/W Registers
typedef union tuCddTpsGen3_RegMTPCFG            { tsCddTpsGen3_Bit_RegMTPCFG              Bit; uint8 ucRaw; } tuCddTpsGen3_RegMTPCFG;
typedef union tuCddTpsGen3_RegOUTCTRL           { tsCddTpsGen3_Bit_RegOUTCTRL             Bit; uint8 ucRaw; } tuCddTpsGen3_RegOUTCTRL;
typedef union tuCddTpsGen3_RegTWLMT             { tsCddTpsGen3_Bit_RegTWLMT               Bit; uint8 ucRaw; } tuCddTpsGen3_RegTWLMT;
typedef union tuCddTpsGen3_RegSLEWL             { tsCddTpsGen3_Bit_RegSLEWL               Bit; uint8 ucRaw; } tuCddTpsGen3_RegSLEWL;
typedef union tuCddTpsGen3_RegSLEWH             { tsCddTpsGen3_Bit_RegSLEWH               Bit; uint8 ucRaw; } tuCddTpsGen3_RegSLEWH;
typedef union tuCddTpsGen3_RegDEFWIDTH01        { tsCddTpsGen3_Bit_RegDEFWIDTH01          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH01;
typedef union tuCddTpsGen3_RegDEFWIDTH02        { tsCddTpsGen3_Bit_RegDEFWIDTH02          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH02;
typedef union tuCddTpsGen3_RegDEFWIDTH03        { tsCddTpsGen3_Bit_RegDEFWIDTH03          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH03;
typedef union tuCddTpsGen3_RegDEFWIDTH04        { tsCddTpsGen3_Bit_RegDEFWIDTH04          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH04;
typedef union tuCddTpsGen3_RegDEFWIDTH05        { tsCddTpsGen3_Bit_RegDEFWIDTH05          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH05;
typedef union tuCddTpsGen3_RegDEFWIDTH06        { tsCddTpsGen3_Bit_RegDEFWIDTH06          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH06;
typedef union tuCddTpsGen3_RegDEFWIDTH07        { tsCddTpsGen3_Bit_RegDEFWIDTH07          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH07;
typedef union tuCddTpsGen3_RegDEFWIDTH08        { tsCddTpsGen3_Bit_RegDEFWIDTH08          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH08;
typedef union tuCddTpsGen3_RegDEFWIDTH09        { tsCddTpsGen3_Bit_RegDEFWIDTH09          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH09;
typedef union tuCddTpsGen3_RegDEFWIDTH10        { tsCddTpsGen3_Bit_RegDEFWIDTH10          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH10;
typedef union tuCddTpsGen3_RegDEFWIDTH11        { tsCddTpsGen3_Bit_RegDEFWIDTH11          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH11;
typedef union tuCddTpsGen3_RegDEFWIDTH12        { tsCddTpsGen3_Bit_RegDEFWIDTH12          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH12;
typedef union tuCddTpsGen3_RegDEFWIDTH13        { tsCddTpsGen3_Bit_RegDEFWIDTH13          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH13;
typedef union tuCddTpsGen3_RegDEFWIDTH14        { tsCddTpsGen3_Bit_RegDEFWIDTH14          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH14;
typedef union tuCddTpsGen3_RegDEFWIDTH15        { tsCddTpsGen3_Bit_RegDEFWIDTH15          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH15;
typedef union tuCddTpsGen3_RegDEFWIDTH16        { tsCddTpsGen3_Bit_RegDEFWIDTH16          Bit; uint8 ucRaw; } tuCddTpsGen3_RegDEFWIDTH16;
typedef union tuCddTpsGen3_RegPHASE01H          { tsCddTpsGen3_Bit_RegPHASE01H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE01H;
typedef union tuCddTpsGen3_RegPHASE02H          { tsCddTpsGen3_Bit_RegPHASE02H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE02H;
typedef union tuCddTpsGen3_RegPHASE03H          { tsCddTpsGen3_Bit_RegPHASE03H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE03H;
typedef union tuCddTpsGen3_RegPHASE04H          { tsCddTpsGen3_Bit_RegPHASE04H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE04H;
typedef union tuCddTpsGen3_RegPHASE05H          { tsCddTpsGen3_Bit_RegPHASE05H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE05H;
typedef union tuCddTpsGen3_RegPHASE06H          { tsCddTpsGen3_Bit_RegPHASE06H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE06H;
typedef union tuCddTpsGen3_RegPHASE07H          { tsCddTpsGen3_Bit_RegPHASE07H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE07H;
typedef union tuCddTpsGen3_RegPHASE08H          { tsCddTpsGen3_Bit_RegPHASE08H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE08H;
typedef union tuCddTpsGen3_RegPHASE09H          { tsCddTpsGen3_Bit_RegPHASE09H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE09H;
typedef union tuCddTpsGen3_RegPHASE10H          { tsCddTpsGen3_Bit_RegPHASE10H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE10H;
typedef union tuCddTpsGen3_RegPHASE11H          { tsCddTpsGen3_Bit_RegPHASE11H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE11H;
typedef union tuCddTpsGen3_RegPHASE12H          { tsCddTpsGen3_Bit_RegPHASE12H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE12H;
typedef union tuCddTpsGen3_RegPHASE13H          { tsCddTpsGen3_Bit_RegPHASE13H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE13H;
typedef union tuCddTpsGen3_RegPHASE14H          { tsCddTpsGen3_Bit_RegPHASE14H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE14H;
typedef union tuCddTpsGen3_RegPHASE15H          { tsCddTpsGen3_Bit_RegPHASE15H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE15H;
typedef union tuCddTpsGen3_RegPHASE16H          { tsCddTpsGen3_Bit_RegPHASE16H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE16H;
typedef union tuCddTpsGen3_RegPHASE04_01L       { tsCddTpsGen3_Bit_RegPHASE04_01L         Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE04_01L;
typedef union tuCddTpsGen3_RegPHASE08_05L       { tsCddTpsGen3_Bit_RegPHASE08_05L         Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE08_05L;
typedef union tuCddTpsGen3_RegPHASE12_09L       { tsCddTpsGen3_Bit_RegPHASE12_09L         Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE12_09L;
typedef union tuCddTpsGen3_RegPHASE16_13L       { tsCddTpsGen3_Bit_RegPHASE16_13L         Bit; uint8 ucRaw; } tuCddTpsGen3_RegPHASE16_13L;
typedef union tuCddTpsGen3_RegWIDTH01H          { tsCddTpsGen3_Bit_RegWIDTH01H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH01H;
typedef union tuCddTpsGen3_RegWIDTH02H          { tsCddTpsGen3_Bit_RegWIDTH02H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH02H;
typedef union tuCddTpsGen3_RegWIDTH03H          { tsCddTpsGen3_Bit_RegWIDTH03H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH03H;
typedef union tuCddTpsGen3_RegWIDTH04H          { tsCddTpsGen3_Bit_RegWIDTH04H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH04H;
typedef union tuCddTpsGen3_RegWIDTH05H          { tsCddTpsGen3_Bit_RegWIDTH05H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH05H;
typedef union tuCddTpsGen3_RegWIDTH06H          { tsCddTpsGen3_Bit_RegWIDTH06H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH06H;
typedef union tuCddTpsGen3_RegWIDTH07H          { tsCddTpsGen3_Bit_RegWIDTH07H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH07H;
typedef union tuCddTpsGen3_RegWIDTH08H          { tsCddTpsGen3_Bit_RegWIDTH08H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH08H;
typedef union tuCddTpsGen3_RegWIDTH09H          { tsCddTpsGen3_Bit_RegWIDTH09H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH09H;
typedef union tuCddTpsGen3_RegWIDTH10H          { tsCddTpsGen3_Bit_RegWIDTH10H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH10H;
typedef union tuCddTpsGen3_RegWIDTH11H          { tsCddTpsGen3_Bit_RegWIDTH11H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH11H;
typedef union tuCddTpsGen3_RegWIDTH12H          { tsCddTpsGen3_Bit_RegWIDTH12H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH12H;
typedef union tuCddTpsGen3_RegWIDTH13H          { tsCddTpsGen3_Bit_RegWIDTH13H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH13H;
typedef union tuCddTpsGen3_RegWIDTH14H          { tsCddTpsGen3_Bit_RegWIDTH14H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH14H;
typedef union tuCddTpsGen3_RegWIDTH15H          { tsCddTpsGen3_Bit_RegWIDTH15H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH15H;
typedef union tuCddTpsGen3_RegWIDTH16H          { tsCddTpsGen3_Bit_RegWIDTH16H            Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH16H;
typedef union tuCddTpsGen3_RegWIDTH04_01L       { tsCddTpsGen3_Bit_RegWIDTH04_01L         Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH04_01L;
typedef union tuCddTpsGen3_RegWIDTH08_05L       { tsCddTpsGen3_Bit_RegWIDTH08_05L         Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH08_05L;
typedef union tuCddTpsGen3_RegWIDTH12_09L       { tsCddTpsGen3_Bit_RegWIDTH12_09L         Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH12_09L;
typedef union tuCddTpsGen3_RegWIDTH16_13L       { tsCddTpsGen3_Bit_RegWIDTH16_13L         Bit; uint8 ucRaw; } tuCddTpsGen3_RegWIDTH16_13L;
typedef union tuCddTpsGen3_RegBANK_PHASE01L     { tsCddTpsGen3_Bit_RegBANK_PHASE01L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE01L;
typedef union tuCddTpsGen3_RegBANK_PHASE02L     { tsCddTpsGen3_Bit_RegBANK_PHASE02L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE02L;
typedef union tuCddTpsGen3_RegBANK_PHASE03L     { tsCddTpsGen3_Bit_RegBANK_PHASE03L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE03L;
typedef union tuCddTpsGen3_RegBANK_PHASE04L     { tsCddTpsGen3_Bit_RegBANK_PHASE04L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE04L;
typedef union tuCddTpsGen3_RegBANK_PHASE04_01H  { tsCddTpsGen3_Bit_RegBANK_PHASE04_01H    Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE04_01H;
typedef union tuCddTpsGen3_RegBANK_PHASE05L     { tsCddTpsGen3_Bit_RegBANK_PHASE05L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE05L;
typedef union tuCddTpsGen3_RegBANK_PHASE06L     { tsCddTpsGen3_Bit_RegBANK_PHASE06L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE06L;
typedef union tuCddTpsGen3_RegBANK_PHASE07L     { tsCddTpsGen3_Bit_RegBANK_PHASE07L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE07L;
typedef union tuCddTpsGen3_RegBANK_PHASE08L     { tsCddTpsGen3_Bit_RegBANK_PHASE08L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE08L;
typedef union tuCddTpsGen3_RegBANK_PHASE08_05H  { tsCddTpsGen3_Bit_RegBANK_PHASE08_05H    Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE08_05H;
typedef union tuCddTpsGen3_RegBANK_PHASE09L     { tsCddTpsGen3_Bit_RegBANK_PHASE09L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE09L;
typedef union tuCddTpsGen3_RegBANK_PHASE10L     { tsCddTpsGen3_Bit_RegBANK_PHASE10L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE10L;
typedef union tuCddTpsGen3_RegBANK_PHASE11L     { tsCddTpsGen3_Bit_RegBANK_PHASE11L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE11L;
typedef union tuCddTpsGen3_RegBANK_PHASE12L     { tsCddTpsGen3_Bit_RegBANK_PHASE12L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE12L;
typedef union tuCddTpsGen3_RegBANK_PHASE12_09H  { tsCddTpsGen3_Bit_RegBANK_PHASE12_09H    Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE12_09H;
typedef union tuCddTpsGen3_RegBANK_PHASE13L     { tsCddTpsGen3_Bit_RegBANK_PHASE13L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE13L;
typedef union tuCddTpsGen3_RegBANK_PHASE14L     { tsCddTpsGen3_Bit_RegBANK_PHASE14L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE14L;
typedef union tuCddTpsGen3_RegBANK_PHASE15L     { tsCddTpsGen3_Bit_RegBANK_PHASE15L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE15L;
typedef union tuCddTpsGen3_RegBANK_PHASE16L     { tsCddTpsGen3_Bit_RegBANK_PHASE16L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE16L;
typedef union tuCddTpsGen3_RegBANK_PHASE16_13H  { tsCddTpsGen3_Bit_RegBANK_PHASE16_13H    Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_PHASE16_13H;
typedef union tuCddTpsGen3_RegBANK_WIDTH01L     { tsCddTpsGen3_Bit_RegBANK_WIDTH01L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH01L;
typedef union tuCddTpsGen3_RegBANK_WIDTH02L     { tsCddTpsGen3_Bit_RegBANK_WIDTH02L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH02L;
typedef union tuCddTpsGen3_RegBANK_WIDTH03L     { tsCddTpsGen3_Bit_RegBANK_WIDTH03L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH03L;
typedef union tuCddTpsGen3_RegBANK_WIDTH04L     { tsCddTpsGen3_Bit_RegBANK_WIDTH04L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH04L;
typedef union tuCddTpsGen3_RegBANK_WIDTH04_01H  { tsCddTpsGen3_Bit_RegBANK_WIDTH04_01H    Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH04_01H;
typedef union tuCddTpsGen3_RegBANK_WIDTH05L     { tsCddTpsGen3_Bit_RegBANK_WIDTH05L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH05L;
typedef union tuCddTpsGen3_RegBANK_WIDTH06L     { tsCddTpsGen3_Bit_RegBANK_WIDTH06L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH06L;
typedef union tuCddTpsGen3_RegBANK_WIDTH07L     { tsCddTpsGen3_Bit_RegBANK_WIDTH07L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH07L;
typedef union tuCddTpsGen3_RegBANK_WIDTH08L     { tsCddTpsGen3_Bit_RegBANK_WIDTH08L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH08L;
typedef union tuCddTpsGen3_RegBANK_WIDTH08_05H  { tsCddTpsGen3_Bit_RegBANK_WIDTH08_05H    Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH08_05H;
typedef union tuCddTpsGen3_RegBANK_WIDTH09L     { tsCddTpsGen3_Bit_RegBANK_WIDTH09L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH09L;
typedef union tuCddTpsGen3_RegBANK_WIDTH10L     { tsCddTpsGen3_Bit_RegBANK_WIDTH10L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH10L;
typedef union tuCddTpsGen3_RegBANK_WIDTH11L     { tsCddTpsGen3_Bit_RegBANK_WIDTH11L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH11L;
typedef union tuCddTpsGen3_RegBANK_WIDTH12L     { tsCddTpsGen3_Bit_RegBANK_WIDTH12L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH12L;
typedef union tuCddTpsGen3_RegBANK_WIDTH12_09H  { tsCddTpsGen3_Bit_RegBANK_WIDTH12_09H    Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH12_09H;
typedef union tuCddTpsGen3_RegBANK_WIDTH13L     { tsCddTpsGen3_Bit_RegBANK_WIDTH13L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH13L;
typedef union tuCddTpsGen3_RegBANK_WIDTH14L     { tsCddTpsGen3_Bit_RegBANK_WIDTH14L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH14L;
typedef union tuCddTpsGen3_RegBANK_WIDTH15L     { tsCddTpsGen3_Bit_RegBANK_WIDTH15L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH15L;
typedef union tuCddTpsGen3_RegBANK_WIDTH16L     { tsCddTpsGen3_Bit_RegBANK_WIDTH16L       Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH16L;
typedef union tuCddTpsGen3_RegBANK_WIDTH16_13H  { tsCddTpsGen3_Bit_RegBANK_WIDTH16_13H    Bit; uint8 ucRaw; } tuCddTpsGen3_RegBANK_WIDTH16_13H;
//reserved memory - 0x65 -> 0x6F
typedef union tuCddTpsGen3_RegLEDONTH01         { tsCddTpsGen3_Bit_RegLEDONTH01           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH01;
typedef union tuCddTpsGen3_RegLEDONTH02         { tsCddTpsGen3_Bit_RegLEDONTH02           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH02;
typedef union tuCddTpsGen3_RegLEDONTH03         { tsCddTpsGen3_Bit_RegLEDONTH03           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH03;
typedef union tuCddTpsGen3_RegLEDONTH04         { tsCddTpsGen3_Bit_RegLEDONTH04           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH04;
typedef union tuCddTpsGen3_RegLEDONTH05         { tsCddTpsGen3_Bit_RegLEDONTH05           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH05;
typedef union tuCddTpsGen3_RegLEDONTH06         { tsCddTpsGen3_Bit_RegLEDONTH06           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH06;
typedef union tuCddTpsGen3_RegLEDONTH07         { tsCddTpsGen3_Bit_RegLEDONTH07           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH07;
typedef union tuCddTpsGen3_RegLEDONTH08         { tsCddTpsGen3_Bit_RegLEDONTH08           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH08;
typedef union tuCddTpsGen3_RegLEDONTH09         { tsCddTpsGen3_Bit_RegLEDONTH09           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH09;
typedef union tuCddTpsGen3_RegLEDONTH10         { tsCddTpsGen3_Bit_RegLEDONTH10           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH10;
typedef union tuCddTpsGen3_RegLEDONTH11         { tsCddTpsGen3_Bit_RegLEDONTH11           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH11;
typedef union tuCddTpsGen3_RegLEDONTH12         { tsCddTpsGen3_Bit_RegLEDONTH12           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH12;
typedef union tuCddTpsGen3_RegLEDONTH13         { tsCddTpsGen3_Bit_RegLEDONTH13           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH13;
typedef union tuCddTpsGen3_RegLEDONTH14         { tsCddTpsGen3_Bit_RegLEDONTH14           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH14;
typedef union tuCddTpsGen3_RegLEDONTH15         { tsCddTpsGen3_Bit_RegLEDONTH15           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH15;
typedef union tuCddTpsGen3_RegLEDONTH16         { tsCddTpsGen3_Bit_RegLEDONTH16           Bit; uint8 ucRaw; } tuCddTpsGen3_RegLEDONTH16;
typedef union tuCddTpsGen3_RegSYSCFG            { tsCddTpsGen3_Bit_RegSYSCFG              Bit; uint8 ucRaw; } tuCddTpsGen3_RegSYSCFG;
typedef union tuCddTpsGen3_RegCMWTAP            { tsCddTpsGen3_Bit_RegCMWTAP              Bit; uint8 ucRaw; } tuCddTpsGen3_RegCMWTAP;
typedef union tuCddTpsGen3_RegPWMTICK           { tsCddTpsGen3_Bit_RegPWMTICK             Bit; uint8 ucRaw; } tuCddTpsGen3_RegPWMTICK;
typedef union tuCddTpsGen3_RegADCID             { tsCddTpsGen3_Bit_RegADCID               Bit; uint8 ucRaw; } tuCddTpsGen3_RegADCID;
typedef union tuCddTpsGen3_RegCLK_SYNC          { tsCddTpsGen3_Bit_RegCLK_SYNC            Bit; uint8 ucRaw; } tuCddTpsGen3_RegCLK_SYNC;
typedef union tuCddTpsGen3_RegSTATUS            { tsCddTpsGen3_Bit_RegSTATUS              Bit; uint8 ucRaw; } tuCddTpsGen3_RegSTATUS;
typedef union tuCddTpsGen3_RegFLT_OPEN_OR_DRVL  { tsCddTpsGen3_Bit_RegFLT_OPEN_OR_DRVL    Bit; uint8 ucRaw; } tuCddTpsGen3_RegFLT_OPEN_OR_DRVL;
typedef union tuCddTpsGen3_RegFLT_OPEN_OR_DRVH  { tsCddTpsGen3_Bit_RegFLT_OPEN_OR_DRVH    Bit; uint8 ucRaw; } tuCddTpsGen3_RegFLT_OPEN_OR_DRVH;
typedef union tuCddTpsGen3_RegFAULT_SHORTL      { tsCddTpsGen3_Bit_RegFAULT_SHORTL        Bit; uint8 ucRaw; } tuCddTpsGen3_RegFAULT_SHORTL;
typedef union tuCddTpsGen3_RegFAULT_SHORTH      { tsCddTpsGen3_Bit_RegFAULT_SHORTH        Bit; uint8 ucRaw; } tuCddTpsGen3_RegFAULT_SHORTH;
typedef union tuCddTpsGen3_RegFAULT_RESFETL     { tsCddTpsGen3_Bit_RegFAULT_RESFETL       Bit; uint8 ucRaw; } tuCddTpsGen3_RegFAULT_RESFETL;
typedef union tuCddTpsGen3_RegFAULT_RESFETH     { tsCddTpsGen3_Bit_RegFAULT_RESFETH       Bit; uint8 ucRaw; } tuCddTpsGen3_RegFAULT_RESFETH;
typedef union tuCddTpsGen3_RegCERRCNT           { tsCddTpsGen3_Bit_RegCERRCNT             Bit; uint8 ucRaw; } tuCddTpsGen3_RegCERRCNT;
// ADC1, ADC2, DIETEMP, CS Register
typedef union tuCddTpsGen3_RegVLEDON01          { tsCddTpsGen3_Bit_RegVLEDON01            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON01;
typedef union tuCddTpsGen3_RegVLEDON02          { tsCddTpsGen3_Bit_RegVLEDON02            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON02;
typedef union tuCddTpsGen3_RegVLEDON03          { tsCddTpsGen3_Bit_RegVLEDON03            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON03;
typedef union tuCddTpsGen3_RegVLEDON04          { tsCddTpsGen3_Bit_RegVLEDON04            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON04;
typedef union tuCddTpsGen3_RegVLEDON05          { tsCddTpsGen3_Bit_RegVLEDON05            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON05;
typedef union tuCddTpsGen3_RegVLEDON06          { tsCddTpsGen3_Bit_RegVLEDON06            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON06;
typedef union tuCddTpsGen3_RegVLEDON07          { tsCddTpsGen3_Bit_RegVLEDON07            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON07;
typedef union tuCddTpsGen3_RegVLEDON08          { tsCddTpsGen3_Bit_RegVLEDON08            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON08;
typedef union tuCddTpsGen3_RegVLEDON09          { tsCddTpsGen3_Bit_RegVLEDON09            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON09;
typedef union tuCddTpsGen3_RegVLEDON10          { tsCddTpsGen3_Bit_RegVLEDON10            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON10;
typedef union tuCddTpsGen3_RegVLEDON11          { tsCddTpsGen3_Bit_RegVLEDON11            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON11;
typedef union tuCddTpsGen3_RegVLEDON12          { tsCddTpsGen3_Bit_RegVLEDON12            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON12;
typedef union tuCddTpsGen3_RegVLEDON13          { tsCddTpsGen3_Bit_RegVLEDON13            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON13;
typedef union tuCddTpsGen3_RegVLEDON14          { tsCddTpsGen3_Bit_RegVLEDON14            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON14;
typedef union tuCddTpsGen3_RegVLEDON15          { tsCddTpsGen3_Bit_RegVLEDON15            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON15;
typedef union tuCddTpsGen3_RegVLEDON16          { tsCddTpsGen3_Bit_RegVLEDON16            Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDON16;
typedef union tuCddTpsGen3_RegVLEDOFF01         { tsCddTpsGen3_Bit_RegVLEDOFF01           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF01;
typedef union tuCddTpsGen3_RegVLEDOFF02         { tsCddTpsGen3_Bit_RegVLEDOFF02           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF02;
typedef union tuCddTpsGen3_RegVLEDOFF03         { tsCddTpsGen3_Bit_RegVLEDOFF03           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF03;
typedef union tuCddTpsGen3_RegVLEDOFF04         { tsCddTpsGen3_Bit_RegVLEDOFF04           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF04;
typedef union tuCddTpsGen3_RegVLEDOFF05         { tsCddTpsGen3_Bit_RegVLEDOFF05           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF05;
typedef union tuCddTpsGen3_RegVLEDOFF06         { tsCddTpsGen3_Bit_RegVLEDOFF06           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF06;
typedef union tuCddTpsGen3_RegVLEDOFF07         { tsCddTpsGen3_Bit_RegVLEDOFF07           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF07;
typedef union tuCddTpsGen3_RegVLEDOFF08         { tsCddTpsGen3_Bit_RegVLEDOFF08           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF08;
typedef union tuCddTpsGen3_RegVLEDOFF09         { tsCddTpsGen3_Bit_RegVLEDOFF09           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF09;
typedef union tuCddTpsGen3_RegVLEDOFF10         { tsCddTpsGen3_Bit_RegVLEDOFF10           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF10;
typedef union tuCddTpsGen3_RegVLEDOFF11         { tsCddTpsGen3_Bit_RegVLEDOFF11           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF11;
typedef union tuCddTpsGen3_RegVLEDOFF12         { tsCddTpsGen3_Bit_RegVLEDOFF12           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF12;
typedef union tuCddTpsGen3_RegVLEDOFF13         { tsCddTpsGen3_Bit_RegVLEDOFF13           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF13;
typedef union tuCddTpsGen3_RegVLEDOFF14         { tsCddTpsGen3_Bit_RegVLEDOFF14           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF14;
typedef union tuCddTpsGen3_RegVLEDOFF15         { tsCddTpsGen3_Bit_RegVLEDOFF15           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF15;
typedef union tuCddTpsGen3_RegVLEDOFF16         { tsCddTpsGen3_Bit_RegVLEDOFF16           Bit; uint8 ucRaw; } tuCddTpsGen3_RegVLEDOFF16;
typedef union tuCddTpsGen3_RegPWM_MISCOUNTL     { tsCddTpsGen3_Bit_RegPWM_MISCOUNTL       Bit; uint8 ucRaw; } tuCddTpsGen3_RegPWM_MISCOUNTL;
typedef union tuCddTpsGen3_RegPWM_MISCOUNTH     { tsCddTpsGen3_Bit_RegPWM_MISCOUNTH       Bit; uint8 ucRaw; } tuCddTpsGen3_RegPWM_MISCOUNTH;
//reserved memory - 0xB3 -> 0xF6
//LOTINFO1-4  Registers
//MTP_PROG1-4 Registers
//ICID Register


// R Registers
typedef union tuCddTpsGen3_RegADC1              { tsCddTpsGen3_Bit_RegADC1                Bit; uint8 ucRaw; } tuCddTpsGen3_RegADC1;
typedef union tuCddTpsGen3_RegADC2              { tsCddTpsGen3_Bit_RegADC2                Bit; uint8 ucRaw; } tuCddTpsGen3_RegADC2;
typedef union tuCddTpsGen3_RegDIETEMP           { tsCddTpsGen3_Bit_RegDIETEMP             Bit; uint8 ucRaw; } tuCddTpsGen3_RegDIETEMP;
typedef union tuCddTpsGen3_RegCS                { tsCddTpsGen3_Bit_RegCS                  Bit; uint8 ucRaw; } tuCddTpsGen3_RegCS;
typedef union tuCddTpsGen3_RegLOTINFO1          { tsCddTpsGen3_Bit_RegLOTINFO1            Bit; uint8 ucRaw; } tuCddTpsGen3_RegLOTINFO1;
typedef union tuCddTpsGen3_RegLOTINFO2          { tsCddTpsGen3_Bit_RegLOTINFO2            Bit; uint8 ucRaw; } tuCddTpsGen3_RegLOTINFO2;
typedef union tuCddTpsGen3_RegLOTINFO3          { tsCddTpsGen3_Bit_RegLOTINFO3            Bit; uint8 ucRaw; } tuCddTpsGen3_RegLOTINFO3;
typedef union tuCddTpsGen3_RegLOTINFO4          { tsCddTpsGen3_Bit_RegLOTINFO4            Bit; uint8 ucRaw; } tuCddTpsGen3_RegLOTINFO4;
typedef union tuCddTpsGen3_RegICID              { tsCddTpsGen3_Bit_RegICID                Bit; uint8 ucRaw; } tuCddTpsGen3_RegICID;


// W Registers
typedef union tuCddTpsGen3_RegMTP_PROG1         { tsCddTpsGen3_Bit_RegMTP_PROG1           Bit; uint8 ucRaw; } tuCddTpsGen3_RegMTP_PROG1;
typedef union tuCddTpsGen3_RegMTP_PROG2         { tsCddTpsGen3_Bit_RegMTP_PROG2           Bit; uint8 ucRaw; } tuCddTpsGen3_RegMTP_PROG2;
typedef union tuCddTpsGen3_RegMTP_PROG3         { tsCddTpsGen3_Bit_RegMTP_PROG3           Bit; uint8 ucRaw; } tuCddTpsGen3_RegMTP_PROG3;
typedef union tuCddTpsGen3_RegMTP_PROG4         { tsCddTpsGen3_Bit_RegMTP_PROG4           Bit; uint8 ucRaw; } tuCddTpsGen3_RegMTP_PROG4;


// group registers

/* PHASE REG contains : 16 registers + 4 registers with grouped LSBs  */
typedef struct tsCddTpsGen3_PHASE_MSB_Reg
{
  tuCddTpsGen3_RegPHASE01H      RegPHASE01H;
  tuCddTpsGen3_RegPHASE02H      RegPHASE02H;
  tuCddTpsGen3_RegPHASE03H      RegPHASE03H;
  tuCddTpsGen3_RegPHASE04H      RegPHASE04H;
  tuCddTpsGen3_RegPHASE05H      RegPHASE05H;
  tuCddTpsGen3_RegPHASE06H      RegPHASE06H;
  tuCddTpsGen3_RegPHASE07H      RegPHASE07H;
  tuCddTpsGen3_RegPHASE08H      RegPHASE08H;
  tuCddTpsGen3_RegPHASE09H      RegPHASE09H;
  tuCddTpsGen3_RegPHASE10H      RegPHASE10H;
  tuCddTpsGen3_RegPHASE11H      RegPHASE11H;
  tuCddTpsGen3_RegPHASE12H      RegPHASE12H;
  tuCddTpsGen3_RegPHASE13H      RegPHASE13H;
  tuCddTpsGen3_RegPHASE14H      RegPHASE14H;
  tuCddTpsGen3_RegPHASE15H      RegPHASE15H;
  tuCddTpsGen3_RegPHASE16H      RegPHASE16H;
}tsCddTpsGen3_PHASE_MSB_Reg;

typedef union tuCddTpsGen3_PHASE_MSB_Reg
{
  tsCddTpsGen3_PHASE_MSB_Reg    PHASE_MSB_Regs;
  uint8                         ucByte[16];
}tuCddTpsGen3_PHASE_MSB_Reg;


typedef struct tsCddTpsGen3_PHASE_LSB_Reg
{
  tuCddTpsGen3_RegPHASE04_01L   RegPHASE04_01L;
  tuCddTpsGen3_RegPHASE08_05L   RegPHASE08_05L;
  tuCddTpsGen3_RegPHASE12_09L   RegPHASE12_09L;
  tuCddTpsGen3_RegPHASE16_13L   RegPHASE16_13L;
}tsCddTpsGen3_PHASE_LSB_Reg;

typedef union tuCddTpsGen3_PHASE_LSB_Reg
{
  tsCddTpsGen3_PHASE_LSB_Reg    PHASE_LSB_Regs;
  uint8                         ucByte[4];
}tuCddTpsGen3_PHASE_LSB_Reg;

/* NOTE: PHASE regs grouped separately in 16bytes memory-zone and 4bytes memory-zone for further use 
         with separate Tx/Rx commands of : 16Bytes CMD + 4bytes CMD for COMPATIBILITY with older families   */


typedef struct tsCddTpsGen3_WIDTH_MSB_Reg
{
  tuCddTpsGen3_RegWIDTH01H      RegWIDTH01H;
  tuCddTpsGen3_RegWIDTH02H      RegWIDTH02H;
  tuCddTpsGen3_RegWIDTH03H      RegWIDTH03H;
  tuCddTpsGen3_RegWIDTH04H      RegWIDTH04H;
  tuCddTpsGen3_RegWIDTH05H      RegWIDTH05H;
  tuCddTpsGen3_RegWIDTH06H      RegWIDTH06H;
  tuCddTpsGen3_RegWIDTH07H      RegWIDTH07H;
  tuCddTpsGen3_RegWIDTH08H      RegWIDTH08H;
  tuCddTpsGen3_RegWIDTH09H      RegWIDTH09H;
  tuCddTpsGen3_RegWIDTH10H      RegWIDTH10H;
  tuCddTpsGen3_RegWIDTH11H      RegWIDTH11H;
  tuCddTpsGen3_RegWIDTH12H      RegWIDTH12H;
  tuCddTpsGen3_RegWIDTH13H      RegWIDTH13H;
  tuCddTpsGen3_RegWIDTH14H      RegWIDTH14H;
  tuCddTpsGen3_RegWIDTH15H      RegWIDTH15H;
  tuCddTpsGen3_RegWIDTH16H      RegWIDTH16H;
}tsCddTpsGen3_WIDTH_MSB_Reg;

typedef union tuCddTpsGen3_WIDTH_MSB_Reg
{
  tsCddTpsGen3_WIDTH_MSB_Reg    WIDTH_MSB_Regs;
  uint8                         ucByte[16];
}tuCddTpsGen3_WIDTH_MSB_Reg;

typedef struct tsCddTpsGen3_WIDTH_LSB_Reg
{
  tuCddTpsGen3_RegWIDTH04_01L   RegWIDTH04_01L;
  tuCddTpsGen3_RegWIDTH08_05L   RegWIDTH08_05L;
  tuCddTpsGen3_RegWIDTH12_09L   RegWIDTH12_09L;
  tuCddTpsGen3_RegWIDTH16_13L   RegWIDTH16_13L;
}tsCddTpsGen3_WIDTH_LSB_Reg;

typedef union tuCddTpsGen3_WIDTH_LSB_Reg
{
  tsCddTpsGen3_WIDTH_LSB_Reg    WIDTH_LSB_Regs;
  uint8                         ucByte[4];
}tuCddTpsGen3_WIDTH_LSB_Reg;

/* NOTE: WIDTH (PWM) regs grouped separately in 16bytes memory-zone and 4bytes memory-zone for further use
         with separate Tx/Rx commands of : 16Bytes CMD + 4bytes CMD for COMPATIBILITY with older families   */


//typedef union tuCddTpsGen3_SLEWRATE_Reg
//{
//  tsCddTpsGen3_Bit_RegSLEWL     sSLEWRATE[2];
//  uint8                         ucByte[2];
//}tuCddTpsGen3_SLEWRATE_Reg;


typedef union tuCddTpsGen3_DefWIDTHReg 
{
  tsCddTpsGen3_Bit_RegDEFWIDTH01  sRegDEFWIDTH01[16];
  uint8                           ucByte[16];
}tuCddTpsGen3_DefWIDTHReg;

//typedef struct tsCddTpsGen3_LedSubStringCfgReg
//{
//  tuCddTpsGen3_SLEWRATE_Reg       sSLEWRATE;
//  tuCddTpsGen3_DefWIDTHReg        sRegDEFWIDTH01;
//}tsCddTpsGen3_LedSubStringCfgReg;

typedef struct tsCddTpsGen3_SLEWRATE_Reg
{
  tsCddTpsGen3_Bit_RegSLEWL     sSLEWRATE_L;
  tsCddTpsGen3_Bit_RegSLEWH     sSLEWRATE_H;
}tsCddTpsGen3_SLEWRATE_Reg;

typedef union tuCddTpsGen3_SLEWRATE_Reg
{
  tsCddTpsGen3_SLEWRATE_Reg     sSLEWRATE;
  uint8                         ucByte[2];
}tuCddTpsGen3_SLEWRATE_Reg;

typedef struct tsCddTpsGen3_DefWIDTHReg
{
  tuCddTpsGen3_RegDEFWIDTH01   uRegDEFWIDTH01; 
  tuCddTpsGen3_RegDEFWIDTH02   uRegDEFWIDTH02;
  tuCddTpsGen3_RegDEFWIDTH03   uRegDEFWIDTH03;
  tuCddTpsGen3_RegDEFWIDTH04   uRegDEFWIDTH04;
  tuCddTpsGen3_RegDEFWIDTH05   uRegDEFWIDTH05;
  tuCddTpsGen3_RegDEFWIDTH06   uRegDEFWIDTH06;
  tuCddTpsGen3_RegDEFWIDTH07   uRegDEFWIDTH07;
  tuCddTpsGen3_RegDEFWIDTH08   uRegDEFWIDTH08;
  tuCddTpsGen3_RegDEFWIDTH09   uRegDEFWIDTH09;
  tuCddTpsGen3_RegDEFWIDTH10   uRegDEFWIDTH10;
  tuCddTpsGen3_RegDEFWIDTH11   uRegDEFWIDTH11;
  tuCddTpsGen3_RegDEFWIDTH12   uRegDEFWIDTH12;
  tuCddTpsGen3_RegDEFWIDTH13   uRegDEFWIDTH13;
  tuCddTpsGen3_RegDEFWIDTH14   uRegDEFWIDTH14;
  tuCddTpsGen3_RegDEFWIDTH15   uRegDEFWIDTH15;
  tuCddTpsGen3_RegDEFWIDTH16   uRegDEFWIDTH16;
}tsCddTpsGen3_DefWIDTHReg;

typedef union tuCddTpsGen3_DefWIDTHRegs
{
  tsCddTpsGen3_DefWIDTHReg      DefWIDTHRegs;
  uint8                         ucByte[16];
}tuCddTpsGen3_DefWIDTHRegs;

typedef struct tsCddTpsGen3_SystemCfgReg
{
  tuCddTpsGen3_RegSYSCFG   RegSYSCFG;
  tuCddTpsGen3_RegCMWTAP   RegCMWTAP;
  tuCddTpsGen3_RegPWMTICK  RegPWMTICK;
}tsCddTpsGen3_SystemCfgReg;


typedef struct tsCddTpsGen3_SSYNC_STATUS_Reg
{
  tuCddTpsGen3_RegCLK_SYNC  RegCLK_SYNC;
  tuCddTpsGen3_RegSTATUS    RegSTATUS;
}tsCddTpsGen3_SSYNC_STATUS_Reg;

typedef struct tsCddTpsGen3_FaultCtrlReg
{
  tuCddTpsGen3_RegFLT_OPEN_OR_DRVL    RegFLT_OPEN_OR_DRVL;
  tuCddTpsGen3_RegFLT_OPEN_OR_DRVH    RegFLT_OPEN_OR_DRVH;
  tuCddTpsGen3_RegFAULT_SHORTL        RegFAULT_SHORTL;
  tuCddTpsGen3_RegFAULT_SHORTH        RegFAULT_SHORTH;
}tsCddTpsGen3_FaultCtrlReg;


//typedef union tuCddTpsGen3_StringCfg            { tsCddTpsGen3_SLEWRATE_Reg    sStringCfg;      uint8 ucByte[18]; }tuCddTpsGen3_StringCfg;
typedef union tuCddTpsGen3_SystemCfgReg         { tsCddTpsGen3_SystemCfgReg          sSysReg;         uint8 ucByte[3];  }tuCddTpsGen3_SystemCfgReg;
typedef union tuCddTpsGen3_SSYNC_STATUS_Reg     { tsCddTpsGen3_SSYNC_STATUS_Reg      sSSYNC_STATUS;   uint8 ucByte[2];  }tuCddTpsGen3_SSYNC_STATUS_Reg;
typedef union tuCddTpsGen3_FaultCtrlReg         { tsCddTpsGen3_FaultCtrlReg          sFaultReg;       uint8 ucByte[4];  }tuCddTpsGen3_FaultCtrlReg;

#endif // CDD_TPS_GEN3_TYPES_2024_02_05_H
