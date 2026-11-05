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
/// \file  reg_stubs.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef REG_STUBS_2021_08_23_H_
#define REG_STUBS_2021_08_23_H_

/* SIM - Register Layout Typedef */
typedef struct {
  uint8 RESERVED_0[4];
  uint32 CHIPCTL;                           /**< Chip Control register, offset: 0x4 */
  uint8 RESERVED_1[4];
  uint32 FTMOPT0;                           /**< FTM Option Register 0, offset: 0xC */
  uint32 LPOCLKS;                           /**< LPO Clock Select Register, offset: 0x10 */
  uint8 RESERVED_2[4];
  uint32 ADCOPT;                            /**< ADC Options Register, offset: 0x18 */
  uint32 FTMOPT1;                           /**< FTM Option Register 1, offset: 0x1C */
  uint32 MISCTRL0;                          /**< Miscellaneous control register 0, offset: 0x20 */
  uint32 SDID;                              /**< System Device Identification Register, offset: 0x24 */
  uint8 RESERVED_3[24];
  uint32 PLATCGC;                           /**< Platform Clock Gating Control Register, offset: 0x40 */
  uint8 RESERVED_4[8];
  uint32 FCFG1;                             /**< Flash Configuration Register 1, offset: 0x4C */
  uint8 RESERVED_5[4];
  uint32 UIDH;                              /**< Unique Identification Register High, offset: 0x54 */
  uint32 UIDMH;                             /**< Unique Identification Register Mid-High, offset: 0x58 */
  uint32 UIDML;                             /**< Unique Identification Register Mid Low, offset: 0x5C */
  uint32 UIDL;                              /**< Unique Identification Register Low, offset: 0x60 */
  uint8 RESERVED_6[4];
  uint32 CLKDIV4;                           /**< System Clock Divider Register 4, offset: 0x68 */
  uint32 MISCTRL1;                          /**< Miscellaneous Control register 1, offset: 0x6C */
} SIM_Type, *SIM_MemMapPtr;

/** Number of instances of the SIM module. */
#define SIM_INSTANCE_COUNT                       (1u)

SIM_Type Sim_sReg;

/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base address */
#define SIM_BASE                                &Sim_sReg
/** Peripheral SIM base pointer */
#define SIM                                      ((SIM_Type *)SIM_BASE)


#define ADC_SC1_COUNT                            16u
#define ADC_R_COUNT                              16u
#define ADC_CV_COUNT                             2u
#define ADC_aSC1_COUNT                           24u
#define ADC_aR_COUNT                             24u
#define ADC_aR_COUNT                             24u

/** ADC - Register Layout Typedef */
typedef struct {
  uint32 SC1[ADC_SC1_COUNT];                /**< ADC Status and Control Register 1, array offset: 0x0, array step: 0x4 */
  uint32 CFG1;                              /**< ADC Configuration Register 1, offset: 0x40 */
  uint32 CFG2;                              /**< ADC Configuration Register 2, offset: 0x44 */
  uint32 R[ADC_R_COUNT];                    /**< ADC Data Result Registers, array offset: 0x48, array step: 0x4 */
  uint32 CV[ADC_CV_COUNT];                  /**< Compare Value Registers, array offset: 0x88, array step: 0x4 */
  uint32 SC2;                               /**< Status and Control Register 2, offset: 0x90 */
  uint32 SC3;                               /**< Status and Control Register 3, offset: 0x94 */
  uint32 BASE_OFS;                          /**< BASE Offset Register, offset: 0x98 */
  uint32 OFS;                               /**< ADC Offset Correction Register, offset: 0x9C */
  uint32 USR_OFS;                           /**< USER Offset Correction Register, offset: 0xA0 */
  uint32 XOFS;                              /**< ADC X Offset Correction Register, offset: 0xA4 */
  uint32 YOFS;                              /**< ADC Y Offset Correction Register, offset: 0xA8 */
  uint32 G;                                 /**< ADC Gain Register, offset: 0xAC */
  uint32 UG;                                /**< ADC User Gain Register, offset: 0xB0 */
  uint32 CLPS;                              /**< ADC General Calibration Value Register S, offset: 0xB4 */
  uint32 CLP3;                              /**< ADC Plus-Side General Calibration Value Register 3, offset: 0xB8 */
  uint32 CLP2;                              /**< ADC Plus-Side General Calibration Value Register 2, offset: 0xBC */
  uint32 CLP1;                              /**< ADC Plus-Side General Calibration Value Register 1, offset: 0xC0 */
  uint32 CLP0;                              /**< ADC Plus-Side General Calibration Value Register 0, offset: 0xC4 */
  uint32 CLPX;                              /**< ADC Plus-Side General Calibration Value Register X, offset: 0xC8 */
  uint32 CLP9;                              /**< ADC Plus-Side General Calibration Value Register 9, offset: 0xCC */
  uint32 CLPS_OFS;                          /**< ADC General Calibration Offset Value Register S, offset: 0xD0 */
  uint32 CLP3_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 3, offset: 0xD4 */
  uint32 CLP2_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 2, offset: 0xD8 */
  uint32 CLP1_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 1, offset: 0xDC */
  uint32 CLP0_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 0, offset: 0xE0 */
  uint32 CLPX_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register X, offset: 0xE4 */
  uint32 CLP9_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 9, offset: 0xE8 */
  uint8 RESERVED_0[28];
  uint32 aSC1[ADC_aSC1_COUNT];              /**< ADC Status and Control Register 1 (alias)..ADC Status and Control Register 1, array offset: 0x108, array step: 0x4 */
  uint8 RESERVED_1[32];
  uint32 aR[ADC_aR_COUNT];                  /**< ADC Data Result Registers (alias)..ADC Data Result Registers, array offset: 0x188, array step: 0x4 */
} ADC_Type, *ADC_MemMapPtr;


typedef volatile uint32 vuint32;

ADC_Type Adc0_sReg;
ADC_Type Adc1_sReg;

#define ADC0_BASE  &Adc0_sReg
#define ADC1_BASE  &Adc1_sReg


#define ADC0                                     (ADC0_BASE)
#define ADC1                                     (ADC1_BASE)

#endif // REG_STUBS_2021_08_23_H_
