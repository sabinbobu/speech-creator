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

/** TRGMUX - Size of Registers Arrays */
#define TRGMUX_TRGMUXn_COUNT                     30u

/** TRGMUX - Register Layout Typedef */
typedef struct {
   uint32 TRGMUXn[TRGMUX_TRGMUXn_COUNT];     /**< TRGMUX DMAMUX0 Register..TRGMUX FTM5 Register, array offset: 0x0, array step: 0x4 */
} TRGMUX_Type, *TRGMUX_MemMapPtr;

/** Number of instances of the TRGMUX module. */
#define TRGMUX_INSTANCE_COUNT                    (1u)

typedef volatile uint32 vuint32;

TRGMUX_Type TrigMux_sReg;

#define TRGMUX_BASE  &TrigMux_sReg


#define TRGMUX                                     ((ADC_Type *)TRGMUX_BASE)

/* TRGMUX index offsets */
#define TRGMUX_DMAMUX0_INDEX                     0
#define TRGMUX_EXTOUT0_INDEX                     1
#define TRGMUX_EXTOUT1_INDEX                     2
#define TRGMUX_ADC0_INDEX                        3
#define TRGMUX_ADC1_INDEX                        4
#define TRGMUX_CMP0_INDEX                        7
#define TRGMUX_FTM0_INDEX                        10
#define TRGMUX_FTM1_INDEX                        11
#define TRGMUX_FTM2_INDEX                        12
#define TRGMUX_FTM3_INDEX                        13
#define TRGMUX_PDB0_INDEX                        14
#define TRGMUX_PDB1_INDEX                        15
#define TRGMUX_FLEXIO_INDEX                      17
#define TRGMUX_LPIT0_INDEX                       18
#define TRGMUX_LPUART0_INDEX                     19
#define TRGMUX_LPUART1_INDEX                     20
#define TRGMUX_LPI2C0_INDEX                      21
#define TRGMUX_LPSPI0_INDEX                      23
#define TRGMUX_LPSPI1_INDEX                      24
#define TRGMUX_LPTMR0_INDEX                      25
#define TRGMUX_FTM4_INDEX                        28
#define TRGMUX_FTM5_INDEX                        29


#endif // REG_STUBS_2021_08_23_H_
