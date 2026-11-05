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
/// \file  CddStp8899Types.h
///
/// \brief  Types of complex driver Texas Instruments TI-DRV8899
///
/// \descr  
///
/// \author Wuesteney, Ulrich ALRT/EEG-PM2 * (wu82rt)
///         mailTo:ulrich.wuesteney[A]al-lighting.com       
///         J. Kling ALRT-EES6 (f84304b)
//-----------------------------------------------------------------------------

#ifndef __CDDSTP8899TYPES_H__
#define __CDDSTP8899TYPES_H__


// ---------------------------------------------------------------------------
// constant definitions
// ---------------------------------------------------------------------------

#define CDDSTP88XX_eCurAmpltNoChange      (0xFFu) // magic value

#define CDDSTP8899_IncPhaseHS             (4u)    //us 1/8 FS - phase count increment at each HS - both modules HalStp and CddStp always work with half steps

#define CDDSTP8899_DirPos                 (0x00u) // clockwise
#define CDDSTP8899_DirNeg                 (0x01u) // counter clockwise

//
// jk-info
//
// TI DRV8899-Q1 A
// https://www.ti.com/lit/ds/symlink/drv8899-q1.pdf
//
//
// OnSemi NCV70514
// https://www.onsemi.com/pub/Collateral/NCV70514-D.PDF
//
// BEMF
//  Motion detection is based on the Back Electromotive Force (BEMF or back emf) generated into the running motor.
//  When the motor is blocked, e.g. when it hits the end?position, the velocity and as a result also the generated back emf, is disturbed. 
//  The NCV70514 measures the back emf during the current zero crossing phase and makes it available in the SPI status register 4. 
//  The back emf voltage is measured several times in each PWM cycle during zero crossing phase. 
//
//
// MOTEN - 'CddStp88XX_HalStpLwr_HandleMotEn_' - 'CddStp8899Com_GetCRegRxMotEn' - 'CddStp88XX_HalStpLwr_SendCReg2'
//  CddStp88XX_HalStp_BitsLwr.Bit.biMotEn;
//  CddStp88XX_HalStp_aucSPI_TX[0][1]: Bit '7' (of 7)
//  CddStp8899Com_DataMirror.CtrlTx.aCReg2[0].Bit.u1DIS_OUT
//  CddStp8899Com_DataMirror.CtrlRx.aCReg2[0].Bit.u1DIS_OUT
//



// new TI DRV8899-Q1
// ******** Status-Registers ********
// Status-Registers - Status-Byte (comes each time of an Rx 'automatically')
//   '1.1.UVLO.CPUV.OCP.RSVD.TF.OL'
#define CDDSTP88xx_BitPos_OL                0u  // Indicates open-load condition. (consider CTRL4: 'EN_OL')(... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!) ('Cod_LwrTestOlIgnor')
#define CDDSTP88xx_Mask_OL               0x01u  // Indicates open-load condition. (consider CTRL4: 'EN_OL')(... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!) ('Cod_LwrTestOlIgnor')

#define CDDSTP88xx_BitPos_TF                1u  // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown. (consider CTRL4: 'TW_REP')
#define CDDSTP88xx_Mask_TF               0x02u  // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown. (consider CTRL4: 'TW_REP')

#define CDDSTP88xx_BitPos_OCP               3u  // Indicates overcurrent fault condition
#define CDDSTP88xx_Mask_OCP              0x08u  // Indicates overcurrent fault condition

#define CDDSTP88xx_BitPos_CPUV              4u  // Indicates charge pump undervoltage fault condition
#define CDDSTP88xx_Mask_CPUV             0x10u  // Indicates charge pump undervoltage fault condition

#define CDDSTP88xx_BitPos_UVLO              5u  // Indicates an undervoltage lockout fault condition.
#define CDDSTP88xx_Mask_UVLO             0x20u  // Indicates an undervoltage lockout fault condition.

//
// Status-Registers - FAULT Status
//  'FAULT.SPI_ERROR.UVLO.CPUV.OCP.RSVD.TF.OL'
// see above: CDDSTP88xx_BitPos_OL          0u  // Indicates open-load condition.
// see above: CDDSTP88xx_BitPos_TF          1u  // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
// see above: CDDSTP88xx_BitPos_OCP         3u  // Indicates overcurrent fault condition
// see above: CDDSTP88xx_BitPos_CPUV        4u  // Indicates charge pump undervoltage fault condition
// see above: CDDSTP88xx_BitPos_UVLO        5u  // Indicates an undervoltage lockout fault condition.

#define CDDSTP88xx_BitPos_SPI_ERROR         6u  // Indicates SPI protocol errors. Becomes high in fault and the nFAULT pin is driven low. Normal operation resumes when the protocol error is removed and a clear faults command has been issued either through the CLR_FLT bit or an nSLEEP reset pulse.
#define CDDSTP88xx_Mask_SPI_ERROR        0x40u  // Indicates SPI protocol errors. Becomes high in fault and the nFAULT pin is driven low. Normal operation resumes when the protocol error is removed and a clear faults command has been issued either through the CLR_FLT bit or an nSLEEP reset pulse.

#define CDDSTP88xx_BitPos_FAULT             7u  // When nFAULT pin is at 1, FAULT bit is 0. When nFAULT pin is at 0, FAULT bit is 1.
#define CDDSTP88xx_Mask_FAULT            0x80u  // When nFAULT pin is at 1, FAULT bit is 0. When nFAULT pin is at 0, FAULT bit is 1.


//
// Status-Registers - DIAG Status 1
//  'OCP_LS2_B.OCP_HS2_B.OCP_LS1_B.OCP_HS1_B.OCP_LS2_A.OCP_HS2_A.OCP_LS1_A.OCP_HS1_A'
#define CDDSTP88xx_BitPos_OCP_HS1_A         0u  // Indicates overcurrent fault on the high-side FET of half bridge 1 in AOUT
#define CDDSTP88xx_Mask_OCP_HS1_A        0x01u

#define CDDSTP88xx_BitPos_OCP_LS1_A         1u  // Indicates overcurrent fault on the low-side FET of half bridge 1 in AOUT
#define CDDSTP88xx_Mask_OCP_LS1_A        0x02u

#define CDDSTP88xx_BitPos_OCP_HS2_A         2u  // Indicates overcurrent fault on the high-side FET of half bridge 2 in AOUT
#define CDDSTP88xx_Mask_OCP_HS2_A        0x04u

#define CDDSTP88xx_BitPos_OCP_LS2_A         3u  // Indicates overcurrent fault on the low-side FET of half bridge 2 in AOUT
#define CDDSTP88xx_Mask_OCP_LS2_A        0x08u

#define CDDSTP88xx_BitPos_OCP_HS1_B         4u  // Indicates overcurrent fault on the high-side FET of half bridge 1 in BOUT
#define CDDSTP88xx_Mask_OCP_HS1_B        0x10u

#define CDDSTP88xx_BitPos_OCP_LS1_B         5u  // Indicates overcurrent fault on the low-side FET of half bridge 1 in BOUT
#define CDDSTP88xx_Mask_OCP_LS1_B        0x20u

#define CDDSTP88xx_BitPos_OCP_HS2_B         6u  // Indicates overcurrent fault on the high-side FET of half bridge 2 in BOUT
#define CDDSTP88xx_Mask_OCP_HS2_B        0x40u

#define CDDSTP88xx_BitPos_OCP_LS2_B         7u  // Indicates overcurrent fault on the low-side FET of half bridge 2 in BOUT
#define CDDSTP88xx_Mask_OCP_LS2_B        0x80u


//
// Status-Registers - DIAG Status 2
//  'UTW.OTW.OTS.RSVD.OL_B.OL_A'
#define CDDSTP88xx_BitPos_OL_A              0u  // Indicates open-load detection on AOUT (... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!)
#define CDDSTP88xx_Mask_OL_A             0x01u  // Indicates open-load detection on AOUT (... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!)

#define CDDSTP88xx_BitPos_OL_B              1u  // Indicates open-load detection on BOUT (... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!)
#define CDDSTP88xx_Mask_OL_B             0x02u  // Indicates open-load detection on BOUT (... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!)

#define CDDSTP88xx_BitPos_OTS               5u  // Indicates overtemperature shutdown
#define CDDSTP88xx_Mask_OTS              0x20u  // Indicates overtemperature shutdown

#define CDDSTP88xx_BitPos_OTW               6u  // Indicates overtemperature warning.
#define CDDSTP88xx_Mask_OTW              0x40u  // Indicates overtemperature warning.

#define CDDSTP88xx_BitPos_UTW               7u  // Indicates undertemperature warning.
#define CDDSTP88xx_Mask_UTW              0x80u  // Indicates undertemperature warning.


//
//
// ******** Control-Registers ********
// Control-Registers - CTRL1
//  'TRQ_DAC [3:0].RSVD.SLEW_RATE [1:0]'
#define CDDSTP88xx_BitPos_SLEW_RATE           (0u)  // S.8: Output slew rate (direct correlation to '7.3.7 Blanking Time') - 00b = 10-V/탎 | 01b = 35-V/탎 | 10b = 50-V/탎 | 11b = 105-V/탎
#define CDDSTP88xx_Mask_SLEW_RATE          (0x03u)  // 000.0011
#define CDDSTP88xx_default_SLEW_RATE       (0x01u)  // probably overwritten by coding data (Blanking-Time (S.27) 00b = 10V/us ... 11b = 105V/us)

#define CDDSTP88xx_BitPos_TRQ_DAC             (4u)  // S.18: 7.3.5 Current Regulation - 0000b = 100% | 0001b = 93.75% | 0010b = 87.5% | 0011b = 81.25% | 0100b = 75% | 0101b = 68.75% | 0110b = 62.5% | 0111b = 56.25% | 1000b = 50% | 1001b = 43.75% | 1010b = 37.5% | 1011b = 31.25% | 1100b = 25% | 1101b = 18.75% | 1110b = 12.5% | 1111b = 6.25%
#define CDDSTP88xx_Mask_TRQ_DAC            (0xF0u)  // 1111.000
#define CDDSTP88xx_default_TRQ_DAC         (0x0Eu)  // probably overwritten by coding data (Torque-DAC    (S.17) 0000b = 100% ... 1111b = 6.25% | 0x0E=1110b=12,5%)


//
// Control-Registers - CTRL2
//  'DIS_OUT.RSVD.TOFF [1:0].DECAY [2:0]'
#define CDDSTP88xx_BitPos_DECAY               (0u)  // S.20: 7.3.6 Decay Modes - 000b = Increasing SLOW, decreasing SLOW | 001b = Incr. SLOW, decr. MIXED 30% | 010b = Incr. SLOW, decr. MIXED 60% | 011b = Incr. SLOW, decr. FAST | 100b = Incr. MIXED 30%, decr.MIXED 30% | 101b = Incr. MIXED 60%, decr.MIXED 60% | 110b = Smart tune Dynamic Decay | 111b = Smart tune Ripple Control
#define CDDSTP88xx_Mask_DECAY              (0x07u)  // 000.0111
#define CDDSTP88xx_default_DECAY           (0x07u)  // (S.19) (0x07=0111b='Smart tune Ripple Control')

#define CDDSTP88xx_BitPos_TOFF                (3u)  // PWM off-time (correlation to DECAY) - 00b = 7 탎 | 01b = 16 탎 | 10b = 24 탎 | 11b = 32 탎
#define CDDSTP88xx_Mask_TOFF               (0x18u)  // 0001.1000
#define CDDSTP88xx_default_TOFF            (0x01u)  // 00b=7us ... 11b=32us, 0x01=01b=16탎
                                                    
#define CDDSTP88xx_BitPos_DIS_OUT             (7u)  // ('MOTEN') Write '1' to Hi-Z all outputs. OR'ed with DRVOFF pin. Ensure OL fault detection is disabled by writing '0' to EN_OL bit, before making the outputs Hi-Z by writing '1' to DIS_OUT.
#define CDDSTP88xx_Mask_DIS_OUT            (0x80u)  // (similar to CDDSTP8899_old_BitPos_MOTEN, CDDSTP8899_old_Mask_MOTEN)
#define CDDSTP88xx_default_DIS_OUT         (0x01u)  // Write '1' to Hi-Z all outputs. OR'ed with DRVOFF pin. Ensure OL fault detection is disabled by writing '0' to EN_OL bit, before making the outputs Hi-Z by writing '1' to DIS_OUT (... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!).


//
// Control-Registers - CTRL3
//  'DIR.STEP.SPI_DIR.SPI_STEP.MICROSTEP_MODE [3:0]'
#define CDDSTP88xx_BitPos_MICROSTEP_MODE      0u  // 0000b = Full step (2-phase excitation) with 100% current | 0001b = Full step (2-phase excitation) with 71% current | 0010b = Non-circular 1/2 step | 0011b = 1/2 step | 0100b = 1/4 step | 0101b = 1/8 step | 0110b = 1/16 step | 0111b = 1/32 step | 1000b = 1/64 step | 1001b = 1/128 step | 1010b = 1/256 step | 1011b to 1111b = Reserved
#define CDDSTP88xx_Mask_MICROSTEP_MODE     0x0Fu  // 0000.1111
#define CDDSTP88xx_default_MICROSTEP_MODE  0x05u  // 0x05 = 0101b = 1/8 step

#define CDDSTP88xx_BitPos_SPI_STEP            4u  // 0b = Outputs follow input pin for STEP | 1b = Outputs follow SPI registers STEP
#define CDDSTP88xx_Mask_SPI_STEP           0x10u  // 0001.0000
#define CDDSTP88xx_default_SPI_STEP        0x00u  // 0b = Outputs follow input pin for STEP

#define CDDSTP88xx_BitPos_SPI_DIR             5u  // 0b = Outputs follow input pin for DIR |  1b = Outputs follow SPI registers DIR
#define CDDSTP88xx_Mask_SPI_DIR            0x20u  // 0010.0000
#define CDDSTP88xx_default_SPI_DIR         0x00u  // 0b = Outputs follow input pin for DIR

#define CDDSTP88xx_BitPos_STEP                6u  // Step input. Logic '1' causes the indexer to advance one step, when SPI_STEP = 1.
#define CDDSTP88xx_Mask_STEP               0x40u  // 0100.0000
#define CDDSTP88xx_default_STEP            0x00u  // Step input. Logic '1' causes the indexer to advance one step, when SPI_STEP = 1.

#define CDDSTP88xx_BitPos_DIR                 7u  // Direction input. Logic '1' sets the direction of stepping, when SPI_DIR = 1.
#define CDDSTP88xx_Mask_DIR                0x80u  // 1000.0000
#define CDDSTP88xx_default_DIR             0x00u  // Direction input. Logic '1' sets the direction of stepping, when SPI_DIR = 1.


//
// Control-Registers - CTRL4
//  'CLR_FLT.LOCK [2:0].EN_OL.OCP_MODE.OTSD_MODE.TW_REP'
#define CDDSTP88xx_BitPos_TW_REP              0u
#define CDDSTP88xx_Mask_TW_REP             0x01u
#define CDDSTP88xx_default_TW_REP          0x01u  // 0b = Over- or undertemp. warning is not reported on the nFAULT line | 1b = Over- or undertemp. warning is reported on the nFAULT line

#define CDDSTP88xx_BitPos_OTSD_MODE           1u
#define CDDSTP88xx_Mask_OTSD_MODE          0x02u
#define CDDSTP88xx_default_OTSD_MODE       0x00u  // 0b = Overtemperature condition will cause latched fault | 1b = Overtemperature condition will cause automatic recovery fault

#define CDDSTP88xx_BitPos_OCP_MODE            2u
#define CDDSTP88xx_Mask_OCP_MODE           0x04u
#define CDDSTP88xx_default_OCP_MODE        0x00u  // 0b = Overcurrent condition causes a latched fault | 1b = Overcurrent condition causes an automatic retrying fault

#define CDDSTP88xx_BitPos_EN_OL               3u
#define CDDSTP88xx_Mask_EN_OL              0x08u
#define CDDSTP88xx_default_EN_OL           0x00u  // Write '1' to enable open load detection (... 'u1EN_OL'!) ('Cod_LwrTestOlIgnor') ('DIS_OUT' = 'Hi-Z all outputs': Ensure OL fault detection is disabled before making the outputs Hi-Z)

#define CDDSTP88xx_BitPos_LOCK                4u
#define CDDSTP88xx_Mask_LOCK               0x70u
#define CDDSTP88xx_default_LOCK            0x03u  // Write 110b to lock the settings by ignoring further register writes except to these bits and address 0x06h bit 7 (CLR_FLT). Writing any sequence other than 110b has no effect when unlocked. Write 011b to this register to unlock all registers. Writing any sequence other than 011b has no effect when locked.

#define CDDSTP88xx_BitPos_CLR_FLT             7u
#define CDDSTP88xx_Mask_CLR_FLT            0x80u
#define CDDSTP88xx_default_CLR_FLT         0x00u  // Write '1' to this bit to clear all latched fault bits. This bit automatically resets after being written.



// ************************************************************************************
// *************************** previous NCV-Registers *********************************
// ************************************************************************************
// ********* https://www.onsemi.com/pub/Collateral/NCV70514-D.PDF page 25 ff **********
// ************************************************************************************

  // Control registers:
  // Control register 1:
  // *************************** previous NCV-Registers *********************************
  // jk-obsolet ...9_old_BitPos_StTrh           0u        // NCV70514:Speed threshold register, BEMF measurement and stall detection is activated when Speed register value is less than or equal to <SpThr> value
  // jk-obsolet ...9_old_Mask_StTrh             0x0Fu

  // jk-obsolet ...9_old_BitPos_MOTEN           4u        // NCV70514: Enables the H?bridges (motor activated in RUN or HOLD mode)
  // jk-obsolet ...9_old_Mask_MOTEN             0x10u     // (similar to CDDSTP88xx_BitPos_DIS_OUT, CDDSTP88xx_Mask_DIS_OUT)

  // jk-obsolet ...9_old_BitPos_NXTP            5u        // NCV70514: Push button pin, generating next step in position table
  // jk-obsolet ...9_old_Mask_NXTP              0x20u

  // jk-obsolet ...9_old_BitPos_RHBP            6u        // NCV70514: Polarity of RHB pin, which controls RUN/HOLD status; RHBP = 1 inverts logic polarity of the RHB pin (Hold = NOT(RHB XOR <RHBP>))
  // jk-obsolet ...9_old_Mask_RHBP              0x40u

  // jk-obsolet ...9_old_BitPos_DIRP            7u        // NCV70514: Polarity of DIR pin, which controls direction status; DIRP = 1 inverts the logic polarity of the DIR pin)
  // jk-obsolet ...9_old_Mask_DIRP              0x80u

  // Control register 2:
  // *************************** previous NCV-Registers *********************************
  // jk-obsolet ...9_old_BitPos_Irun            0u        // NCV70514: Current amplitude in RUN mode
  // jk-obsolet ...9_old_Mask_Irun              0x0Fu

  // jk-obsolet ...9_old_BitPos_Ihold           4u        // NCV70514: Current amplitude in HOLD mode
  // jk-obsolet ...9_old_Mask_Ihold             0xF0u

  // Control register 3:
  // *************************** previous NCV-Registers *********************************
  // jk-obsolet ...9_old_BitPos_StepMode        0u        // NCV70514: Step mode selection (S. 21)
  // jk-obsolet ...9_old_Mask_StepMode          0x07u

  // jk-obsolet ...9_old_BitPos_SLP             3u        // NCV70514: Places device in sleep mode with low current consumption (when 1)
  // jk-obsolet ...9_old_Mask_SLP               0x08u

  // jk-obsolet ...9_old_BitPos_EMC             4u        // NCV70514: Voltage slope defining bits for motor driver switching
  // jk-obsolet ...9_old_Mask_EMC               0x30u

  // jk-obsolet ...9_old_BitPos_DIAGEN          6u        // NCV70514: Enables automatic diagnostic at rising edge of <MOTEN> bit
  // jk-obsolet ...9_old_Mask_DIAGEN            0x40u

  // jk-obsolet ...9_old_BitPos_EnhBemfEn       7u        // NCV70514: Enhanced BEMF measurement functionality is activated when bit is set
  // jk-obsolet ...9_old_Mask_EnhBemfEn         0x80u

  // Control register 4:
  // *************************** previous NCV-Registers *********************************
  // jk-obsolet ...9_old_BitPos_StTo            0u        // NCV70514: Max difference between two successive full step next pulse periods (timeout), after this time the BEMF sample is taken to verify stall
  // jk-obsolet ...9_old_Mask_StTo              0xFFu


  // Status registers:
  // Status register 0:
  // *************************** previous NCV-Registers *********************************
  // jk-obsolet ...9_old_BitPos_HardReset       0u        // NCV70514: Hard reset flag: 1 indicates a hard reset has occurred
  // jk-obsolet ...9_old_Mask_HardReset         0x01u

  // jk-obsolet ...9_old_BitPos_STALL           1u        // NCV70514: Stall detected by the internal algorithm
  // jk-obsolet ...9_old_Mask_STALL             0x02u

  // Status register 1:
  // *************************** previous NCV-Registers *********************************
  // jk-obsolet ...9_old_BitPos_HardReset       0u        // NCV70514: Hard reset flag: 1 indicates a hard reset has occurred
  // jk-obsolet ...9_old_Mask_HardReset         0x01u

  // jk-obsolet ...9_old_BitPos_STALL           1u        // NCV70514: Stall detected by the internal algorithm
  // jk-obsolet ...9_old_Mask_STALL             0x02u

  // jk-obsolet ...9_old_BitPos_TW              2u        // NCV70514: Thermal warning
  // jk-obsolet ...9_old_Mask_TW                0x04u

  // jk-obsolet ...9_old_BitPos_TSD             3u        // NCV70514: Thermal shutdown
  // jk-obsolet ...9_old_Mask_TSD               0x08u

  // jk-obsolet ...9_old_BitPos_OPEN            4u        // NCV70514: Open Coil X or Y detected (common: set if at least one of the two specific X/Y open coil bits is set)
  // jk-obsolet ...9_old_Mask_OPEN              0x10u

  // jk-obsolet ...9_old_BitPos_SHORT           5u        // NCV70514: An over current detected (common: set if at least one of the SHORTij individual bits is set)
  // jk-obsolet ...9_old_Mask_SHORT             0x20u

  // jk-obsolet ...9_old_BitPos_SPI             6u        // NCV70514: SPI error: no multiple of 16 rising clock edges between falling and rising edge of CSB line
  // jk-obsolet ...9_old_Mask_SPI               0x40u

  // Status register 2:
  // *************************** previous NCV-Registers *********************************
  // jk-obsolet ...9_old_BitPos_UV3M            0u        // NCV70514: Under voltage 3 detection and NXT pulse arrive during UV3 state (Motion)
  // jk-obsolet ...9_old_Mask_UV3M              0x01u

  // jk-obsolet ...9_old_BitPos_UV3             1u        // NCV70514: Under voltage 3 detection
  // jk-obsolet ...9_old_Mask_UV3               0x02u

  // jk-obsolet ...9_old_BitPos_UV2M            2u        // NCV70514: 
  // jk-obsolet ...9_old_Mask_UV2M              0x04u

  // jk-obsolet ...9_old_BitPos_UV2             3u        // NCV70514: 
  // jk-obsolet ...9_old_Mask_UV2               0x08u

  // jk-obsolet ...9_old_BitPos_UV1             4u        // NCV70514: 
  // jk-obsolet ...9_old_Mask_UV1               0x10u

  // jk-obsolet ...9_old_BitPos_BemfRes         5u        // NCV70514: BEMF result ready at <Bemf> register
  // jk-obsolet ...9_old_Mask_BemfRes           0x20u

  // jk-obsolet ...9_old_BitPos_ORErr           6u        // NCV70514: Logic OR of all bits of SR1 (Error bits)
  // jk-obsolet ...9_old_Mask_ORErr             0x40u



  // *************************** new TI DRV8899-Q1-Status-Registers ***************************
  // ***** Status-Registers - Status-Byte (comes each time of an Rx 'automatically')  ==  '1.1.UVLO.CPUV.OCP.RSVD.TF.OL'
  // CDDSTP88xx_BitPos_OL               // Indicates open-load condition. (consider CTRL4: 'EN_OL')(... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!) ('Cod_LwrTestOlIgnor')
  // CDDSTP88xx_BitPos_TF               // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown. (consider CTRL4: 'TW_REP')
  // CDDSTP88xx_BitPos_OCP              // Indicates overcurrent fault condition
  // CDDSTP88xx_BitPos_CPUV             // Indicates charge pump undervoltage fault condition
  // CDDSTP88xx_BitPos_UVLO             // Indicates an undervoltage lockout fault condition.
  // ***** Status-Registers - FAULT Status  ==  'FAULT.SPI_ERROR.UVLO.CPUV.OCP.RSVD.TF.OL'
  // CDDSTP88xx_BitPos_OL               // Indicates open-load condition.
  // CDDSTP88xx_BitPos_TF               // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
  // CDDSTP88xx_BitPos_OCP              // Indicates overcurrent fault condition
  // CDDSTP88xx_BitPos_CPUV             // Indicates charge pump undervoltage fault condition
  // CDDSTP88xx_BitPos_UVLO             // Indicates an undervoltage lockout fault condition.
  // CDDSTP88xx_BitPos_SPI_ERROR        // Indicates SPI protocol errors. Becomes high in fault and the nFAULT pin is driven low. Normal operation resumes when the protocol error is removed and a clear faults command has been issued either through the CLR_FLT bit or an nSLEEP reset pulse.
  // CDDSTP88xx_BitPos_FAULT            // When nFAULT pin is at 1, FAULT bit is 0. When nFAULT pin is at 0, FAULT bit is 1.
  // ***** Status-Registers - DIAG Status 1  ==  'OCP_LS2_B.OCP_HS2_B.OCP_LS1_B.OCP_HS1_B.OCP_LS2_A.OCP_HS2_A.OCP_LS1_A.OCP_HS1_A'
  // CDDSTP88xx_BitPos_OCP_HS1_A        // Indicates overcurrent fault on the high-side FET of half bridge 1 in AOUT
  // CDDSTP88xx_BitPos_OCP_LS1_A        // Indicates overcurrent fault on the low-side FET of half bridge 1 in AOUT
  // CDDSTP88xx_BitPos_OCP_HS2_A        // Indicates overcurrent fault on the high-side FET of half bridge 2 in AOUT
  // CDDSTP88xx_BitPos_OCP_LS2_A        // Indicates overcurrent fault on the low-side FET of half bridge 2 in AOUT
  // CDDSTP88xx_BitPos_OCP_HS1_B        // Indicates overcurrent fault on the high-side FET of half bridge 1 in BOUT
  // CDDSTP88xx_BitPos_OCP_LS1_B        // Indicates overcurrent fault on the low-side FET of half bridge 1 in BOUT
  // CDDSTP88xx_BitPos_OCP_HS2_B        // Indicates overcurrent fault on the high-side FET of half bridge 2 in BOUT
  // CDDSTP88xx_BitPos_OCP_LS2_B        // Indicates overcurrent fault on the low-side FET of half bridge 2 in BOUT
  // ***** Status-Registers - DIAG Status 2  ==  'UTW.OTW.OTS.RSVD.OL_B.OL_A'
  // CDDSTP88xx_BitPos_OL_A             // Indicates open-load detection on AOUT (... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!)
  // CDDSTP88xx_BitPos_OL_B             // Indicates open-load detection on BOUT (... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!)
  // CDDSTP88xx_BitPos_OTS              // Indicates overtemperature shutdown
  // CDDSTP88xx_BitPos_OTW              // Indicates overtemperature warning.
  // CDDSTP88xx_BitPos_UTW              // Indicates undertemperature warning.



// *************************** previous NCV-Status-Registers ***************************
// xx_HardReset  NCV70514:         Hard reset flag: 1 indicates a hard reset has occurred   ('CDDSTP8899_old_Mask_HardReset')
//               TI: ------------- NOT used in current (HCM-) code
// xx_STALL      NCV70514:         Stall detected by the internal algorithm                 ('CDDSTP8899_old_Mask_STALL')
//               TI: ------------- NOT used in current (HCM-) code
// xx_TW         NCV70514:         Thermal warning                                          ('CDDSTP8899_old_Mask_TW')
//               TI: xx_OTW        Indicates overtemperature warning.
// xx_TSD        NCV70514:         Thermal shutdown                                         ('CDDSTP8899_old_Mask_TSD')
//               TI: xx_OTS        Indicates overtemperature shutdown
// xx_OPEN       NCV70514:         Open Coil X or Y detected (common: set if at least one of the two specific X/Y open coil bits is set)('OPENX' Bit 6 (SR7A): Open Coil X detected | 'OPENY' Bit 6 (SR8A): Open Coil Y detected)  ('CDDSTP8899_old_Mask_OPEN')
//               TI: xx_OL         Indicates open-load condition. ('EN_OL' shall be '1' to enable OL-Detection) ('Cod_LwrTestOlIgnor')  ***  ('CddStp88XX_HalStp_ucOLCntLwr' & 'CddStp88XX_aucOLCntMax')
//               TI: xx_OL_A       Indicates open-load detection on AOUT (... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!)
//               TI: xx_OL_B       Indicates open-load detection on BOUT (... 'u1EN_OL' / 'CDDSTP88xx_default_EN_OL'!)
// xx_SHORT      NCV70514:         An over current detected (common: set if at least one of the SHORTij individual bits is set)('SHRTXPB', 'SHRTXNB', 'SHRTXPT', 'SHRTXNT', 'SHRTYPB', 'SHRTYNB', 'SHRTYPT', 'SHRTYNT')            ('CDDSTP8899_old_Mask_SHORT')
//               TI: xx_OCP        Indicates overcurrent fault condition                                                                ***  ('CddStp88XX_HalStp_ucSCCntLwr')
//               TI: xx_OCP_HS1_A  Indicates overcurrent fault on the high-side FET of half bridge 1 in AOUT
//               TI: xx_OCP_LS1_A  Indicates overcurrent fault on the low-side FET of half bridge 1 in AOUT
//               TI: xx_OCP_HS2_A  Indicates overcurrent fault on the high-side FET of half bridge 2 in AOUT
//               TI: xx_OCP_LS2_A  Indicates overcurrent fault on the low-side FET of half bridge 2 in AOUT
//               TI: xx_OCP_HS1_B  Indicates overcurrent fault on the high-side FET of half bridge 1 in BOUT
//               TI: xx_OCP_LS1_B  Indicates overcurrent fault on the low-side FET of half bridge 1 in BOUT
//               TI: xx_OCP_HS2_B  Indicates overcurrent fault on the high-side FET of half bridge 2 in BOUT
//               TI: xx_OCP_LS2_B  Indicates overcurrent fault on the low-side FET of half bridge 2 in BOUT
// xx_SPI        NCV70514:         SPI error: no multiple of 16 rising clock edges between falling and rising edge of CSB line   ('CDDSTP8899_old_Mask_SPI')
//               TI: xx_SPI_ERROR  Indicates SPI protocol errors. Becomes high in fault and the nFAULT pin is driven low. Normal operation resumes when the protocol error is removed and a clear faults command has been issued either through the CLR_FLT bit or an nSLEEP reset pulse.
// xx_UV3M       NCV70514:         Under voltage 3 detection and NXT pulse arrive during UV3 state (Motion)                      ('CDDSTP8899_old_Mask_UV3M')
//               TI: ------------- NOT used in current (HCM-) code
// xx_UV3        NCV70514:         Under voltage 3 detection (H?Bridge off voltage low threshold)                                ('CDDSTP8899_old_Mask_UV3')
//               TI: xx_UVLO       Indicates an VM (Power supply voltage / Voltage Main) undervoltage lockout fault condition.
// xx_UV2M       NCV70514:         Under voltage 2 detection                                                                     ('CDDSTP8899_old_Mask_UV2M')
//               TI: ------------- NOT used in current (HCM-) code
// xx_UV2        NCV70514:         Under voltage 2 detection                                                                     ('CDDSTP8899_old_Mask_UV2')
//               TI: ------------- NOT used in current (HCM-) code
// xx_UV1        NCV70514:         Under voltage 1 detection                                                                     ('CDDSTP8899_old_Mask_UV1')
//               TI: ------------- NOT used in current (HCM-) code
// xx_BemfRes    NCV70514:         BEMF result ready at <Bemf> register                                                          ('CDDSTP8899_old_Mask_BemfRes')
//               TI: ------------- NOT used in current (HCM-) code
// xx_ORErr      NCV70514:         Logic OR of all bits of SR1 (Error bits)                                                      ('CDDSTP8899_old_Mask_ORErr')
//               TI: xx_FAULT      When nFAULT pin is at 1, FAULT bit is 0. When nFAULT pin is at 0, FAULT bit is 1.
//-------------- In NCV70514 NOT available -------------
//               TI: xx_CPUV       Indicates charge pump undervoltage fault condition
//               TI: xx_TF         Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
//               TI: xx_UTW        Indicates undertemperature warning.



  // ---------------------------------------------------------------------------
  // type definitions
  // ---------------------------------------------------------------------------

  typedef struct
  {
    uint16 biFinishMove           : 1;    // 0:  HalStp: FinishMove
  }
  tCddStpEventBit;

  typedef union
  {
    uint16            unData;
    tCddStpEventBit   Bit;
  }
  tCddStpEvent;


  typedef enum
  {
    CDDSTP88XX_eStepModeMS                 = 0,  // must be 0 (init. value) //us
    CDDSTP88XX_eStepModeNC,                      // 1 // not compensated HS //NCHS
//NCHS    CDDSTP88XX_eStepModeHS,                // 2 //     compensated HS
    CDDSTP88XX_eStepModeIx                       // 2 // numbers of step mode index
  } tStepModeCddStp88XX;

  /* see tCddStpTempState in file CddStpIfc.h:  
  typedef enum
  {
    CDDSTP88XX_eNormTemp                   = 0,  // must be 0 (init. value)
    CDDSTP88XX_eLowTemp,                         // 1
    CDDSTP88XX_eHighTemp,                        // 2
    CDDSTP88XX_eTempIx                           // 3 // numbers of temperature index
  } tTempCddStp88XX;
  */
  
  typedef enum
  {
    CDDSTP88XX_eCurAmpltStateHold          = 0,  // must be 0 (init. value)
    CDDSTP88XX_eCurAmpltStateNorm,               // 1
    CDDSTP88XX_eCurAmpltStateNoChange            // 2
  } tCurAmpltStateCddStp88XX;


  // ---------------------------------------------------------------------------
  // CddStp88XX bits - global module internal use but initialized only once per PowerOn cycle
  typedef struct
  {
    uint8   biCodingDataValid    : 1; //0:  coding data is valid - data block is saved completely in NVM (not compatible to Afs2)
    uint8   biCtrlStpVdd         : 1; //1:  control of stepper driver VDD after power on - DRV88XX specific (not compatible to Afs2)
  }tCddStp88XXBitsGlobalInitOnce;

  typedef union
  {
    tCddStp88XXBitsGlobalInitOnce Bit;     ///< bit signal access
    uint8                          ucRaw;   ///< raw signal access
  } uCddStp88XXBitsGlobalInitOnce;


  // ---------------------------------------------------------------------------
  // CddStp88XX bits - module internal use
  typedef struct
  {
    uint32  Reserved1            : 1; //0:  reserved
    uint32  biRefWaitExit        : 1; //1:  special StpCtrl message handling to force state machine from Exit of RefWait (= Entry of Idle) in Move if necessary without acknowledge by StpState bit 'IsReady'
    uint32  biTransOff           : 1; //2:  special transition condition from StateRef1/2/Wait or StateStby to StateOff
    uint32  biIsRegSlope         : 1; //3:  last Psens slope at debounced signal change                            was regulation slope (high precision)
    
    uint32  biIsRegSlopeBest     : 1; //4:  best Psens slope at last ePosMiddleUp/Down  middle desensitivity state was regulation slope (high precision)
    uint32  biIsRegSlopePos      : 1; //5:  best positive Psens slope at ePosMiddleUp   middle desensitivity state was regulation slope (high precision)
    uint32  biIsRegSlopeNeg      : 1; //6:  best negative Psens slope at ePosMiddleDown middle desensitivity state was regulation slope (high precision)
    uint32  biErrPosRegLower     : 1; //7:  register lower ErrPos for desensitivity of Psens
    
    uint32  biErrPosRegUpper     : 1; //8:  register upper ErrPos for desensitivity of Psens
    uint32  biIsPositiveRefStart : 1; //9:  save position sensor level at start of reference run
    uint32  biSlopePosInvalid    : 1; //10: slope position of sensor is invalid after reference run
    uint32  biCorrValueSign      : 1; //11: sign of position correction value
    
    uint32  biSetTestStep        : 1; //12: do test steps
    uint32  biWaitStabilize      : 1; //13: to avoid range overflow in timeout polling
    uint32  biWaitVoltage        : 1; //14: to avoid range overflow in timeout polling
    uint32  biWaitErrPrealarm    : 1; //15: to avoid range overflow in timeout polling
    
    uint32  biWaitMinHT          : 1; //16: to avoid range overflow in timeout polling
    uint32  biWaitDurLT          : 1; //17: to avoid range overflow in timeout polling
    uint32  biLockLT             : 1; //18: to lock low temperature state in this power on cycle
    uint32  biUpdStat            : 1; //19: set if statistic contents have to be stored in NVM
    
    uint32  biExitLT             : 1; //20: do not use because of DRV88XX property: switch to low current in RDS groups - DRV88XX specific
    uint32  biDisOLDetect        : 1; //21: disable open load (OL) detection while stepping (movement) - DRV88XX specific
    uint32  biWaitStabilizeChg   : 1; //22: change of flag biWaitStabilize is handled
    uint32  Reserved2            : 1; //23: reserved
    
    uint32  biOldStateNotInit    : 1; //24: to avoid TSD problem at entry of Off-State - DRV88XX specific
    uint32  biClrDriverResetDeb  : 1; //25: clear driver reset debounce flag - DRV88XX specific
    uint32  biHalStpInit         : 1; //26: HalStp init done                                             (not compatible to Afs2)
    uint32  biStpOn              : 1; //27: stepper on or off for StpOnTime calculation
    
    uint32  biDemErrDrvDefect    : 1; //28: Dem is called because of driver defect error - DRV88XX specific
  }tCSSBitsMod;

  typedef union
  {
    tCSSBitsMod Bit;     ///< bit signal access
    uint32      ulRaw;   ///< raw signal access
  } tCddStp88XXBitsMod;

  // ---------------------------------------------------------------------------
  // CddStp88XX bits - external use
  typedef struct
  {
    uint16  biTransitionErrDone  : 1; //0:  check of error bits is done in CddStp88XX_TransitionErr() - used in CddStp88XX_HalStpVer/Hor/Sht_ErrnCb()
    uint16  biGetRegAll          : 1; //1:  read DRV88XX debug information: all registers
    uint16  biTestStepDone       : 1; //2:  test steps done
    uint16  biInvPsensPol        : 1; //3:  polarity changed by CddStpXxx0/1_InvertPsensPolarity() - only used in case CFG_Stp_UseInvPsensPol
    
    uint16  biInvPsensPolValid   : 1; //4:  valid flag set   in CddStpXxx0/1_InvertPsensPolarity() - only used in case CFG_Stp_UseInvPsensPol
    uint16  biPsensSigDiag       : 1; //5:  position sensor signal diagnosis active flag set in CddStpXxx0/1_SwitchPsensSignalDiag()- only used in case CFG_Stp_SwitchPsensSigDiag
    uint16  biWaitErrInh         : 1; //6:  to avoid range overflow in timeout polling
    uint16  biActPosValid        : 1; //7:  indicates valid actual position
    
    uint16  biSigInit            : 1; //8:  indicates signal initialized
    uint16  biLT                 : 1; //9:  low temperature                                              (not compatible to Afs2)
    uint16  biRetryTestStepDone  : 1; //10: bit indicates if retry test step is done
    uint16  biDoRetryTestStep    : 1; //11: bit to do a retry test step in case of pseudo OL

    uint16  biRichtung           : 1; //12: stepper direction
    uint16  biPsensPol           : 1; //13: polarity of psens signal (used for AHL only)
    uint16  biRegelflanke        : 1; //14: definition of sensor slope (used for AHL only)
    uint16  biDummy15            : 1; //15: dummy bit
  }tCSSBits;

  typedef union
  {
    tCSSBits Bit;     ///< bit signal access
    uint16   unRaw;   ///< raw signal access
  } tCddStp88XXBits;

  #define tCddStp_Bits tCddStp88XXBits

#endif // __CDDSTP8899TYPES_H__

// EOF
