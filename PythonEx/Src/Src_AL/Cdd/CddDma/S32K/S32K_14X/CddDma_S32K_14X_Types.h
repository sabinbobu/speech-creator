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
/// \file  CddDma_S32K_14X_Types.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_DMA_S32K_14X_TYPES_2021_05_10_H_
#define CDD_DMA_S32K_14X_TYPES_2021_05_10_H_


#include <Std_Types.h>

/** DMA - Size of Registers Arrays */
#define CDDDMA_DCHPRI_COUNT                         16u
#define CDDDMA_TCD_COUNT                            16u
#define CDDDMAMUX_CHCFG_COUNT                       16u

/* CR Bit Fields */
#define CDDDMA_CR_EDBG_MASK                         0x2u
#define CDDDMA_CR_EDBG_SHIFT                        1u
#define CDDDMA_CR_EDBG_WIDTH                        1u
#define CDDDMA_CR_EDBG(x)                           (((uint32)(((uint32)(x))<<CDDDMA_CR_EDBG_SHIFT))&CDDDMA_CR_EDBG_MASK)
#define CDDDMA_CR_ERCA_MASK                         0x4u
#define CDDDMA_CR_ERCA_SHIFT                        2u
#define CDDDMA_CR_ERCA_WIDTH                        1u
#define CDDDMA_CR_ERCA(x)                           (((uint32)(((uint32)(x))<<CDDDMA_CR_ERCA_SHIFT))&CDDDMA_CR_ERCA_MASK)
#define CDDDMA_CR_HOE_MASK                          0x10u
#define CDDDMA_CR_HOE_SHIFT                         4u
#define CDDDMA_CR_HOE_WIDTH                         1u
#define CDDDMA_CR_HOE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_CR_HOE_SHIFT))&CDDDMA_CR_HOE_MASK)
#define CDDDMA_CR_HALT_MASK                         0x20u
#define CDDDMA_CR_HALT_SHIFT                        5u
#define CDDDMA_CR_HALT_WIDTH                        1u
#define CDDDMA_CR_HALT(x)                           (((uint32)(((uint32)(x))<<CDDDMA_CR_HALT_SHIFT))&CDDDMA_CR_HALT_MASK)
#define CDDDMA_CR_CLM_MASK                          0x40u
#define CDDDMA_CR_CLM_SHIFT                         6u
#define CDDDMA_CR_CLM_WIDTH                         1u
#define CDDDMA_CR_CLM(x)                            (((uint32)(((uint32)(x))<<CDDDMA_CR_CLM_SHIFT))&CDDDMA_CR_CLM_MASK)
#define CDDDMA_CR_EMLM_MASK                         0x80u
#define CDDDMA_CR_EMLM_SHIFT                        7u
#define CDDDMA_CR_EMLM_WIDTH                        1u
#define CDDDMA_CR_EMLM(x)                           (((uint32)(((uint32)(x))<<CDDDMA_CR_EMLM_SHIFT))&CDDDMA_CR_EMLM_MASK)
#define CDDDMA_CR_ECX_MASK                          0x10000u
#define CDDDMA_CR_ECX_SHIFT                         16u
#define CDDDMA_CR_ECX_WIDTH                         1u
#define CDDDMA_CR_ECX(x)                            (((uint32)(((uint32)(x))<<CDDDMA_CR_ECX_SHIFT))&CDDDMA_CR_ECX_MASK)
#define CDDDMA_CR_CX_MASK                           0x20000u
#define CDDDMA_CR_CX_SHIFT                          17u
#define CDDDMA_CR_CX_WIDTH                          1u
#define CDDDMA_CR_CX(x)                             (((uint32)(((uint32)(x))<<CDDDMA_CR_CX_SHIFT))&CDDDMA_CR_CX_MASK)
#define CDDDMA_CR_ACTIVE_MASK                       0x80000000u
#define CDDDMA_CR_ACTIVE_SHIFT                      31u
#define CDDDMA_CR_ACTIVE_WIDTH                      1u
#define CDDDMA_CR_ACTIVE(x)                         (((uint32)(((uint32)(x))<<CDDDMA_CR_ACTIVE_SHIFT))&CDDDMA_CR_ACTIVE_MASK)
/* ES Bit Fields */
#define CDDDMA_ES_DBE_MASK                          0x1u
#define CDDDMA_ES_DBE_SHIFT                         0u
#define CDDDMA_ES_DBE_WIDTH                         1u
#define CDDDMA_ES_DBE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_DBE_SHIFT))&CDDDMA_ES_DBE_MASK)
#define CDDDMA_ES_SBE_MASK                          0x2u
#define CDDDMA_ES_SBE_SHIFT                         1u
#define CDDDMA_ES_SBE_WIDTH                         1u
#define CDDDMA_ES_SBE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_SBE_SHIFT))&CDDDMA_ES_SBE_MASK)
#define CDDDMA_ES_SGE_MASK                          0x4u
#define CDDDMA_ES_SGE_SHIFT                         2u
#define CDDDMA_ES_SGE_WIDTH                         1u
#define CDDDMA_ES_SGE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_SGE_SHIFT))&CDDDMA_ES_SGE_MASK)
#define CDDDMA_ES_NCE_MASK                          0x8u
#define CDDDMA_ES_NCE_SHIFT                         3u
#define CDDDMA_ES_NCE_WIDTH                         1u
#define CDDDMA_ES_NCE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_NCE_SHIFT))&CDDDMA_ES_NCE_MASK)
#define CDDDMA_ES_DOE_MASK                          0x10u
#define CDDDMA_ES_DOE_SHIFT                         4u
#define CDDDMA_ES_DOE_WIDTH                         1u
#define CDDDMA_ES_DOE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_DOE_SHIFT))&CDDDMA_ES_DOE_MASK)
#define CDDDMA_ES_DAE_MASK                          0x20u
#define CDDDMA_ES_DAE_SHIFT                         5u
#define CDDDMA_ES_DAE_WIDTH                         1u
#define CDDDMA_ES_DAE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_DAE_SHIFT))&CDDDMA_ES_DAE_MASK)
#define CDDDMA_ES_SOE_MASK                          0x40u
#define CDDDMA_ES_SOE_SHIFT                         6u
#define CDDDMA_ES_SOE_WIDTH                         1u
#define CDDDMA_ES_SOE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_SOE_SHIFT))&CDDDMA_ES_SOE_MASK)
#define CDDDMA_ES_SAE_MASK                          0x80u
#define CDDDMA_ES_SAE_SHIFT                         7u
#define CDDDMA_ES_SAE_WIDTH                         1u
#define CDDDMA_ES_SAE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_SAE_SHIFT))&CDDDMA_ES_SAE_MASK)
#define CDDDMA_ES_ERRCHN_MASK                       0xF00u
#define CDDDMA_ES_ERRCHN_SHIFT                      8u
#define CDDDMA_ES_ERRCHN_WIDTH                      4u
#define CDDDMA_ES_ERRCHN(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ES_ERRCHN_SHIFT))&CDDDMA_ES_ERRCHN_MASK)
#define CDDDMA_ES_CPE_MASK                          0x4000u
#define CDDDMA_ES_CPE_SHIFT                         14u
#define CDDDMA_ES_CPE_WIDTH                         1u
#define CDDDMA_ES_CPE(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_CPE_SHIFT))&CDDDMA_ES_CPE_MASK)
#define CDDDMA_ES_ECX_MASK                          0x10000u
#define CDDDMA_ES_ECX_SHIFT                         16u
#define CDDDMA_ES_ECX_WIDTH                         1u
#define CDDDMA_ES_ECX(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_ECX_SHIFT))&CDDDMA_ES_ECX_MASK)
#define CDDDMA_ES_VLD_MASK                          0x80000000u
#define CDDDMA_ES_VLD_SHIFT                         31u
#define CDDDMA_ES_VLD_WIDTH                         1u
#define CDDDMA_ES_VLD(x)                            (((uint32)(((uint32)(x))<<CDDDMA_ES_VLD_SHIFT))&CDDDMA_ES_VLD_MASK)
/* ERQ Bit Fields */
#define CDDDMA_ERQ_ERQ0_MASK                        0x1u
#define CDDDMA_ERQ_ERQ0_SHIFT                       0u
#define CDDDMA_ERQ_ERQ0_WIDTH                       1u
#define CDDDMA_ERQ_ERQ0(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ0_SHIFT))&CDDDMA_ERQ_ERQ0_MASK)
#define CDDDMA_ERQ_ERQ1_MASK                        0x2u
#define CDDDMA_ERQ_ERQ1_SHIFT                       1u
#define CDDDMA_ERQ_ERQ1_WIDTH                       1u
#define CDDDMA_ERQ_ERQ1(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ1_SHIFT))&CDDDMA_ERQ_ERQ1_MASK)
#define CDDDMA_ERQ_ERQ2_MASK                        0x4u
#define CDDDMA_ERQ_ERQ2_SHIFT                       2u
#define CDDDMA_ERQ_ERQ2_WIDTH                       1u
#define CDDDMA_ERQ_ERQ2(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ2_SHIFT))&CDDDMA_ERQ_ERQ2_MASK)
#define CDDDMA_ERQ_ERQ3_MASK                        0x8u
#define CDDDMA_ERQ_ERQ3_SHIFT                       3u
#define CDDDMA_ERQ_ERQ3_WIDTH                       1u
#define CDDDMA_ERQ_ERQ3(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ3_SHIFT))&CDDDMA_ERQ_ERQ3_MASK)
#define CDDDMA_ERQ_ERQ4_MASK                        0x10u
#define CDDDMA_ERQ_ERQ4_SHIFT                       4u
#define CDDDMA_ERQ_ERQ4_WIDTH                       1u
#define CDDDMA_ERQ_ERQ4(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ4_SHIFT))&CDDDMA_ERQ_ERQ4_MASK)
#define CDDDMA_ERQ_ERQ5_MASK                        0x20u
#define CDDDMA_ERQ_ERQ5_SHIFT                       5u
#define CDDDMA_ERQ_ERQ5_WIDTH                       1u
#define CDDDMA_ERQ_ERQ5(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ5_SHIFT))&CDDDMA_ERQ_ERQ5_MASK)
#define CDDDMA_ERQ_ERQ6_MASK                        0x40u
#define CDDDMA_ERQ_ERQ6_SHIFT                       6u
#define CDDDMA_ERQ_ERQ6_WIDTH                       1u
#define CDDDMA_ERQ_ERQ6(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ6_SHIFT))&CDDDMA_ERQ_ERQ6_MASK)
#define CDDDMA_ERQ_ERQ7_MASK                        0x80u
#define CDDDMA_ERQ_ERQ7_SHIFT                       7u
#define CDDDMA_ERQ_ERQ7_WIDTH                       1u
#define CDDDMA_ERQ_ERQ7(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ7_SHIFT))&CDDDMA_ERQ_ERQ7_MASK)
#define CDDDMA_ERQ_ERQ8_MASK                        0x100u
#define CDDDMA_ERQ_ERQ8_SHIFT                       8u
#define CDDDMA_ERQ_ERQ8_WIDTH                       1u
#define CDDDMA_ERQ_ERQ8(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ8_SHIFT))&CDDDMA_ERQ_ERQ8_MASK)
#define CDDDMA_ERQ_ERQ9_MASK                        0x200u
#define CDDDMA_ERQ_ERQ9_SHIFT                       9u
#define CDDDMA_ERQ_ERQ9_WIDTH                       1u
#define CDDDMA_ERQ_ERQ9(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ9_SHIFT))&CDDDMA_ERQ_ERQ9_MASK)
#define CDDDMA_ERQ_ERQ10_MASK                       0x400u
#define CDDDMA_ERQ_ERQ10_SHIFT                      10u
#define CDDDMA_ERQ_ERQ10_WIDTH                      1u
#define CDDDMA_ERQ_ERQ10(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ10_SHIFT))&CDDDMA_ERQ_ERQ10_MASK)
#define CDDDMA_ERQ_ERQ11_MASK                       0x800u
#define CDDDMA_ERQ_ERQ11_SHIFT                      11u
#define CDDDMA_ERQ_ERQ11_WIDTH                      1u
#define CDDDMA_ERQ_ERQ11(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ11_SHIFT))&CDDDMA_ERQ_ERQ11_MASK)
#define CDDDMA_ERQ_ERQ12_MASK                       0x1000u
#define CDDDMA_ERQ_ERQ12_SHIFT                      12u
#define CDDDMA_ERQ_ERQ12_WIDTH                      1u
#define CDDDMA_ERQ_ERQ12(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ12_SHIFT))&CDDDMA_ERQ_ERQ12_MASK)
#define CDDDMA_ERQ_ERQ13_MASK                       0x2000u
#define CDDDMA_ERQ_ERQ13_SHIFT                      13u
#define CDDDMA_ERQ_ERQ13_WIDTH                      1u
#define CDDDMA_ERQ_ERQ13(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ13_SHIFT))&CDDDMA_ERQ_ERQ13_MASK)
#define CDDDMA_ERQ_ERQ14_MASK                       0x4000u
#define CDDDMA_ERQ_ERQ14_SHIFT                      14u
#define CDDDMA_ERQ_ERQ14_WIDTH                      1u
#define CDDDMA_ERQ_ERQ14(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ14_SHIFT))&CDDDMA_ERQ_ERQ14_MASK)
#define CDDDMA_ERQ_ERQ15_MASK                       0x8000u
#define CDDDMA_ERQ_ERQ15_SHIFT                      15u
#define CDDDMA_ERQ_ERQ15_WIDTH                      1u
#define CDDDMA_ERQ_ERQ15(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERQ_ERQ15_SHIFT))&CDDDMA_ERQ_ERQ15_MASK)
/* EEI Bit Fields */
#define CDDDMA_EEI_EEI0_MASK                        0x1u
#define CDDDMA_EEI_EEI0_SHIFT                       0u
#define CDDDMA_EEI_EEI0_WIDTH                       1u
#define CDDDMA_EEI_EEI0(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI0_SHIFT))&CDDDMA_EEI_EEI0_MASK)
#define CDDDMA_EEI_EEI1_MASK                        0x2u
#define CDDDMA_EEI_EEI1_SHIFT                       1u
#define CDDDMA_EEI_EEI1_WIDTH                       1u
#define CDDDMA_EEI_EEI1(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI1_SHIFT))&CDDDMA_EEI_EEI1_MASK)
#define CDDDMA_EEI_EEI2_MASK                        0x4u
#define CDDDMA_EEI_EEI2_SHIFT                       2u
#define CDDDMA_EEI_EEI2_WIDTH                       1u
#define CDDDMA_EEI_EEI2(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI2_SHIFT))&CDDDMA_EEI_EEI2_MASK)
#define CDDDMA_EEI_EEI3_MASK                        0x8u
#define CDDDMA_EEI_EEI3_SHIFT                       3u
#define CDDDMA_EEI_EEI3_WIDTH                       1u
#define CDDDMA_EEI_EEI3(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI3_SHIFT))&CDDDMA_EEI_EEI3_MASK)
#define CDDDMA_EEI_EEI4_MASK                        0x10u
#define CDDDMA_EEI_EEI4_SHIFT                       4u
#define CDDDMA_EEI_EEI4_WIDTH                       1u
#define CDDDMA_EEI_EEI4(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI4_SHIFT))&CDDDMA_EEI_EEI4_MASK)
#define CDDDMA_EEI_EEI5_MASK                        0x20u
#define CDDDMA_EEI_EEI5_SHIFT                       5u
#define CDDDMA_EEI_EEI5_WIDTH                       1u
#define CDDDMA_EEI_EEI5(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI5_SHIFT))&CDDDMA_EEI_EEI5_MASK)
#define CDDDMA_EEI_EEI6_MASK                        0x40u
#define CDDDMA_EEI_EEI6_SHIFT                       6u
#define CDDDMA_EEI_EEI6_WIDTH                       1u
#define CDDDMA_EEI_EEI6(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI6_SHIFT))&CDDDMA_EEI_EEI6_MASK)
#define CDDDMA_EEI_EEI7_MASK                        0x80u
#define CDDDMA_EEI_EEI7_SHIFT                       7u
#define CDDDMA_EEI_EEI7_WIDTH                       1u
#define CDDDMA_EEI_EEI7(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI7_SHIFT))&CDDDMA_EEI_EEI7_MASK)
#define CDDDMA_EEI_EEI8_MASK                        0x100u
#define CDDDMA_EEI_EEI8_SHIFT                       8u
#define CDDDMA_EEI_EEI8_WIDTH                       1u
#define CDDDMA_EEI_EEI8(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI8_SHIFT))&CDDDMA_EEI_EEI8_MASK)
#define CDDDMA_EEI_EEI9_MASK                        0x200u
#define CDDDMA_EEI_EEI9_SHIFT                       9u
#define CDDDMA_EEI_EEI9_WIDTH                       1u
#define CDDDMA_EEI_EEI9(x)                          (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI9_SHIFT))&CDDDMA_EEI_EEI9_MASK)
#define CDDDMA_EEI_EEI10_MASK                       0x400u
#define CDDDMA_EEI_EEI10_SHIFT                      10u
#define CDDDMA_EEI_EEI10_WIDTH                      1u
#define CDDDMA_EEI_EEI10(x)                         (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI10_SHIFT))&CDDDMA_EEI_EEI10_MASK)
#define CDDDMA_EEI_EEI11_MASK                       0x800u
#define CDDDMA_EEI_EEI11_SHIFT                      11u
#define CDDDMA_EEI_EEI11_WIDTH                      1u
#define CDDDMA_EEI_EEI11(x)                         (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI11_SHIFT))&CDDDMA_EEI_EEI11_MASK)
#define CDDDMA_EEI_EEI12_MASK                       0x1000u
#define CDDDMA_EEI_EEI12_SHIFT                      12u
#define CDDDMA_EEI_EEI12_WIDTH                      1u
#define CDDDMA_EEI_EEI12(x)                         (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI12_SHIFT))&CDDDMA_EEI_EEI12_MASK)
#define CDDDMA_EEI_EEI13_MASK                       0x2000u
#define CDDDMA_EEI_EEI13_SHIFT                      13u
#define CDDDMA_EEI_EEI13_WIDTH                      1u
#define CDDDMA_EEI_EEI13(x)                         (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI13_SHIFT))&CDDDMA_EEI_EEI13_MASK)
#define CDDDMA_EEI_EEI14_MASK                       0x4000u
#define CDDDMA_EEI_EEI14_SHIFT                      14u
#define CDDDMA_EEI_EEI14_WIDTH                      1u
#define CDDDMA_EEI_EEI14(x)                         (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI14_SHIFT))&CDDDMA_EEI_EEI14_MASK)
#define CDDDMA_EEI_EEI15_MASK                       0x8000u
#define CDDDMA_EEI_EEI15_SHIFT                      15u
#define CDDDMA_EEI_EEI15_WIDTH                      1u
#define CDDDMA_EEI_EEI15(x)                         (((uint32)(((uint32)(x))<<CDDDMA_EEI_EEI15_SHIFT))&CDDDMA_EEI_EEI15_MASK)
/* CEEI Bit Fields */
#define CDDDMA_CEEI_CEEI_MASK                       0xFu
#define CDDDMA_CEEI_CEEI_SHIFT                      0u
#define CDDDMA_CEEI_CEEI_WIDTH                      4u
#define CDDDMA_CEEI_CEEI(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CEEI_CEEI_SHIFT))&CDDDMA_CEEI_CEEI_MASK)
#define CDDDMA_CEEI_CAEE_MASK                       0x40u
#define CDDDMA_CEEI_CAEE_SHIFT                      6u
#define CDDDMA_CEEI_CAEE_WIDTH                      1u
#define CDDDMA_CEEI_CAEE(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CEEI_CAEE_SHIFT))&CDDDMA_CEEI_CAEE_MASK)
#define CDDDMA_CEEI_NOP_MASK                        0x80u
#define CDDDMA_CEEI_NOP_SHIFT                       7u
#define CDDDMA_CEEI_NOP_WIDTH                       1u
#define CDDDMA_CEEI_NOP(x)                          (((uint8)(((uint8)(x))<<CDDDMA_CEEI_NOP_SHIFT))&CDDDMA_CEEI_NOP_MASK)
/* SEEI Bit Fields */
#define CDDDMA_SEEI_SEEI_MASK                       0xFu
#define CDDDMA_SEEI_SEEI_SHIFT                      0u
#define CDDDMA_SEEI_SEEI_WIDTH                      4u
#define CDDDMA_SEEI_SEEI(x)                         (((uint8)(((uint8)(x))<<CDDDMA_SEEI_SEEI_SHIFT))&CDDDMA_SEEI_SEEI_MASK)
#define CDDDMA_SEEI_SAEE_MASK                       0x40u
#define CDDDMA_SEEI_SAEE_SHIFT                      6u
#define CDDDMA_SEEI_SAEE_WIDTH                      1u
#define CDDDMA_SEEI_SAEE(x)                         (((uint8)(((uint8)(x))<<CDDDMA_SEEI_SAEE_SHIFT))&CDDDMA_SEEI_SAEE_MASK)
#define CDDDMA_SEEI_NOP_MASK                        0x80u
#define CDDDMA_SEEI_NOP_SHIFT                       7u
#define CDDDMA_SEEI_NOP_WIDTH                       1u
#define CDDDMA_SEEI_NOP(x)                          (((uint8)(((uint8)(x))<<CDDDMA_SEEI_NOP_SHIFT))&CDDDMA_SEEI_NOP_MASK)
/* CERQ Bit Fields */
#define CDDDMA_CERQ_CERQ_MASK                       0xFu
#define CDDDMA_CERQ_CERQ_SHIFT                      0u
#define CDDDMA_CERQ_CERQ_WIDTH                      4u
#define CDDDMA_CERQ_CERQ(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CERQ_CERQ_SHIFT))&CDDDMA_CERQ_CERQ_MASK)
#define CDDDMA_CERQ_CAER_MASK                       0x40u
#define CDDDMA_CERQ_CAER_SHIFT                      6u
#define CDDDMA_CERQ_CAER_WIDTH                      1u
#define CDDDMA_CERQ_CAER(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CERQ_CAER_SHIFT))&CDDDMA_CERQ_CAER_MASK)
#define CDDDMA_CERQ_NOP_MASK                        0x80u
#define CDDDMA_CERQ_NOP_SHIFT                       7u
#define CDDDMA_CERQ_NOP_WIDTH                       1u
#define CDDDMA_CERQ_NOP(x)                          (((uint8)(((uint8)(x))<<CDDDMA_CERQ_NOP_SHIFT))&CDDDMA_CERQ_NOP_MASK)
/* SERQ Bit Fields */
#define CDDDMA_SERQ_SERQ_MASK                       0xFu
#define CDDDMA_SERQ_SERQ_SHIFT                      0u
#define CDDDMA_SERQ_SERQ_WIDTH                      4u
#define CDDDMA_SERQ_SERQ(x)                         (((uint8)(((uint8)(x))<<CDDDMA_SERQ_SERQ_SHIFT))&CDDDMA_SERQ_SERQ_MASK)
#define CDDDMA_SERQ_SAER_MASK                       0x40u
#define CDDDMA_SERQ_SAER_SHIFT                      6u
#define CDDDMA_SERQ_SAER_WIDTH                      1u
#define CDDDMA_SERQ_SAER(x)                         (((uint8)(((uint8)(x))<<CDDDMA_SERQ_SAER_SHIFT))&CDDDMA_SERQ_SAER_MASK)
#define CDDDMA_SERQ_NOP_MASK                        0x80u
#define CDDDMA_SERQ_NOP_SHIFT                       7u
#define CDDDMA_SERQ_NOP_WIDTH                       1u
#define CDDDMA_SERQ_NOP(x)                          (((uint8)(((uint8)(x))<<CDDDMA_SERQ_NOP_SHIFT))&CDDDMA_SERQ_NOP_MASK)
/* CDNE Bit Fields */
#define CDDDMA_CDNE_CDNE_MASK                       0xFu
#define CDDDMA_CDNE_CDNE_SHIFT                      0u
#define CDDDMA_CDNE_CDNE_WIDTH                      4u
#define CDDDMA_CDNE_CDNE(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CDNE_CDNE_SHIFT))&CDDDMA_CDNE_CDNE_MASK)
#define CDDDMA_CDNE_CADN_MASK                       0x40u
#define CDDDMA_CDNE_CADN_SHIFT                      6u
#define CDDDMA_CDNE_CADN_WIDTH                      1u
#define CDDDMA_CDNE_CADN(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CDNE_CADN_SHIFT))&CDDDMA_CDNE_CADN_MASK)
#define CDDDMA_CDNE_NOP_MASK                        0x80u
#define CDDDMA_CDNE_NOP_SHIFT                       7u
#define CDDDMA_CDNE_NOP_WIDTH                       1u
#define CDDDMA_CDNE_NOP(x)                          (((uint8)(((uint8)(x))<<CDDDMA_CDNE_NOP_SHIFT))&CDDDMA_CDNE_NOP_MASK)
/* SSRT Bit Fields */
#define CDDDMA_SSRT_SSRT_MASK                       0xFu
#define CDDDMA_SSRT_SSRT_SHIFT                      0u
#define CDDDMA_SSRT_SSRT_WIDTH                      4u
#define CDDDMA_SSRT_SSRT(x)                         (((uint8)(((uint8)(x))<<CDDDMA_SSRT_SSRT_SHIFT))&CDDDMA_SSRT_SSRT_MASK)
#define CDDDMA_SSRT_SAST_MASK                       0x40u
#define CDDDMA_SSRT_SAST_SHIFT                      6u
#define CDDDMA_SSRT_SAST_WIDTH                      1u
#define CDDDMA_SSRT_SAST(x)                         (((uint8)(((uint8)(x))<<CDDDMA_SSRT_SAST_SHIFT))&CDDDMA_SSRT_SAST_MASK)
#define CDDDMA_SSRT_NOP_MASK                        0x80u
#define CDDDMA_SSRT_NOP_SHIFT                       7u
#define CDDDMA_SSRT_NOP_WIDTH                       1u
#define CDDDMA_SSRT_NOP(x)                          (((uint8)(((uint8)(x))<<CDDDMA_SSRT_NOP_SHIFT))&CDDDMA_SSRT_NOP_MASK)
/* CERR Bit Fields */
#define CDDDMA_CERR_CERR_MASK                       0xFu
#define CDDDMA_CERR_CERR_SHIFT                      0u
#define CDDDMA_CERR_CERR_WIDTH                      4u
#define CDDDMA_CERR_CERR(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CERR_CERR_SHIFT))&CDDDMA_CERR_CERR_MASK)
#define CDDDMA_CERR_CAEI_MASK                       0x40u
#define CDDDMA_CERR_CAEI_SHIFT                      6u
#define CDDDMA_CERR_CAEI_WIDTH                      1u
#define CDDDMA_CERR_CAEI(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CERR_CAEI_SHIFT))&CDDDMA_CERR_CAEI_MASK)
#define CDDDMA_CERR_NOP_MASK                        0x80u
#define CDDDMA_CERR_NOP_SHIFT                       7u
#define CDDDMA_CERR_NOP_WIDTH                       1u
#define CDDDMA_CERR_NOP(x)                          (((uint8)(((uint8)(x))<<CDDDMA_CERR_NOP_SHIFT))&CDDDMA_CERR_NOP_MASK)
/* CINT Bit Fields */
#define CDDDMA_CINT_CINT_MASK                       0xFu
#define CDDDMA_CINT_CINT_SHIFT                      0u
#define CDDDMA_CINT_CINT_WIDTH                      4u
#define CDDDMA_CINT_CINT(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CINT_CINT_SHIFT))&CDDDMA_CINT_CINT_MASK)
#define CDDDMA_CINT_CAIR_MASK                       0x40u
#define CDDDMA_CINT_CAIR_SHIFT                      6u
#define CDDDMA_CINT_CAIR_WIDTH                      1u
#define CDDDMA_CINT_CAIR(x)                         (((uint8)(((uint8)(x))<<CDDDMA_CINT_CAIR_SHIFT))&CDDDMA_CINT_CAIR_MASK)
#define CDDDMA_CINT_NOP_MASK                        0x80u
#define CDDDMA_CINT_NOP_SHIFT                       7u
#define CDDDMA_CINT_NOP_WIDTH                       1u
#define CDDDMA_CINT_NOP(x)                          (((uint8)(((uint8)(x))<<CDDDMA_CINT_NOP_SHIFT))&CDDDMA_CINT_NOP_MASK)
/* INT Bit Fields */
#define CDDDMA_INT_INT0_MASK                        0x1u
#define CDDDMA_INT_INT0_SHIFT                       0u
#define CDDDMA_INT_INT0_WIDTH                       1u
#define CDDDMA_INT_INT0(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT0_SHIFT))&CDDDMA_INT_INT0_MASK)
#define CDDDMA_INT_INT1_MASK                        0x2u
#define CDDDMA_INT_INT1_SHIFT                       1u
#define CDDDMA_INT_INT1_WIDTH                       1u
#define CDDDMA_INT_INT1(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT1_SHIFT))&CDDDMA_INT_INT1_MASK)
#define CDDDMA_INT_INT2_MASK                        0x4u
#define CDDDMA_INT_INT2_SHIFT                       2u
#define CDDDMA_INT_INT2_WIDTH                       1u
#define CDDDMA_INT_INT2(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT2_SHIFT))&CDDDMA_INT_INT2_MASK)
#define CDDDMA_INT_INT3_MASK                        0x8u
#define CDDDMA_INT_INT3_SHIFT                       3u
#define CDDDMA_INT_INT3_WIDTH                       1u
#define CDDDMA_INT_INT3(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT3_SHIFT))&CDDDMA_INT_INT3_MASK)
#define CDDDMA_INT_INT4_MASK                        0x10u
#define CDDDMA_INT_INT4_SHIFT                       4u
#define CDDDMA_INT_INT4_WIDTH                       1u
#define CDDDMA_INT_INT4(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT4_SHIFT))&CDDDMA_INT_INT4_MASK)
#define CDDDMA_INT_INT5_MASK                        0x20u
#define CDDDMA_INT_INT5_SHIFT                       5u
#define CDDDMA_INT_INT5_WIDTH                       1u
#define CDDDMA_INT_INT5(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT5_SHIFT))&CDDDMA_INT_INT5_MASK)
#define CDDDMA_INT_INT6_MASK                        0x40u
#define CDDDMA_INT_INT6_SHIFT                       6u
#define CDDDMA_INT_INT6_WIDTH                       1u
#define CDDDMA_INT_INT6(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT6_SHIFT))&CDDDMA_INT_INT6_MASK)
#define CDDDMA_INT_INT7_MASK                        0x80u
#define CDDDMA_INT_INT7_SHIFT                       7u
#define CDDDMA_INT_INT7_WIDTH                       1u
#define CDDDMA_INT_INT7(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT7_SHIFT))&CDDDMA_INT_INT7_MASK)
#define CDDDMA_INT_INT8_MASK                        0x100u
#define CDDDMA_INT_INT8_SHIFT                       8u
#define CDDDMA_INT_INT8_WIDTH                       1u
#define CDDDMA_INT_INT8(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT8_SHIFT))&CDDDMA_INT_INT8_MASK)
#define CDDDMA_INT_INT9_MASK                        0x200u
#define CDDDMA_INT_INT9_SHIFT                       9u
#define CDDDMA_INT_INT9_WIDTH                       1u
#define CDDDMA_INT_INT9(x)                          (((uint32)(((uint32)(x))<<CDDDMA_INT_INT9_SHIFT))&CDDDMA_INT_INT9_MASK)
#define CDDDMA_INT_INT10_MASK                       0x400u
#define CDDDMA_INT_INT10_SHIFT                      10u
#define CDDDMA_INT_INT10_WIDTH                      1u
#define CDDDMA_INT_INT10(x)                         (((uint32)(((uint32)(x))<<CDDDMA_INT_INT10_SHIFT))&CDDDMA_INT_INT10_MASK)
#define CDDDMA_INT_INT11_MASK                       0x800u
#define CDDDMA_INT_INT11_SHIFT                      11u
#define CDDDMA_INT_INT11_WIDTH                      1u
#define CDDDMA_INT_INT11(x)                         (((uint32)(((uint32)(x))<<CDDDMA_INT_INT11_SHIFT))&CDDDMA_INT_INT11_MASK)
#define CDDDMA_INT_INT12_MASK                       0x1000u
#define CDDDMA_INT_INT12_SHIFT                      12u
#define CDDDMA_INT_INT12_WIDTH                      1u
#define CDDDMA_INT_INT12(x)                         (((uint32)(((uint32)(x))<<CDDDMA_INT_INT12_SHIFT))&CDDDMA_INT_INT12_MASK)
#define CDDDMA_INT_INT13_MASK                       0x2000u
#define CDDDMA_INT_INT13_SHIFT                      13u
#define CDDDMA_INT_INT13_WIDTH                      1u
#define CDDDMA_INT_INT13(x)                         (((uint32)(((uint32)(x))<<CDDDMA_INT_INT13_SHIFT))&CDDDMA_INT_INT13_MASK)
#define CDDDMA_INT_INT14_MASK                       0x4000u
#define CDDDMA_INT_INT14_SHIFT                      14u
#define CDDDMA_INT_INT14_WIDTH                      1u
#define CDDDMA_INT_INT14(x)                         (((uint32)(((uint32)(x))<<CDDDMA_INT_INT14_SHIFT))&CDDDMA_INT_INT14_MASK)
#define CDDDMA_INT_INT15_MASK                       0x8000u
#define CDDDMA_INT_INT15_SHIFT                      15u
#define CDDDMA_INT_INT15_WIDTH                      1u
#define CDDDMA_INT_INT15(x)                         (((uint32)(((uint32)(x))<<CDDDMA_INT_INT15_SHIFT))&CDDDMA_INT_INT15_MASK)
/* ERR Bit Fields */
#define CDDDMA_ERR_ERR0_MASK                        0x1u
#define CDDDMA_ERR_ERR0_SHIFT                       0u
#define CDDDMA_ERR_ERR0_WIDTH                       1u
#define CDDDMA_ERR_ERR0(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR0_SHIFT))&CDDDMA_ERR_ERR0_MASK)
#define CDDDMA_ERR_ERR1_MASK                        0x2u
#define CDDDMA_ERR_ERR1_SHIFT                       1u
#define CDDDMA_ERR_ERR1_WIDTH                       1u
#define CDDDMA_ERR_ERR1(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR1_SHIFT))&CDDDMA_ERR_ERR1_MASK)
#define CDDDMA_ERR_ERR2_MASK                        0x4u
#define CDDDMA_ERR_ERR2_SHIFT                       2u
#define CDDDMA_ERR_ERR2_WIDTH                       1u
#define CDDDMA_ERR_ERR2(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR2_SHIFT))&CDDDMA_ERR_ERR2_MASK)
#define CDDDMA_ERR_ERR3_MASK                        0x8u
#define CDDDMA_ERR_ERR3_SHIFT                       3u
#define CDDDMA_ERR_ERR3_WIDTH                       1u
#define CDDDMA_ERR_ERR3(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR3_SHIFT))&CDDDMA_ERR_ERR3_MASK)
#define CDDDMA_ERR_ERR4_MASK                        0x10u
#define CDDDMA_ERR_ERR4_SHIFT                       4u
#define CDDDMA_ERR_ERR4_WIDTH                       1u
#define CDDDMA_ERR_ERR4(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR4_SHIFT))&CDDDMA_ERR_ERR4_MASK)
#define CDDDMA_ERR_ERR5_MASK                        0x20u
#define CDDDMA_ERR_ERR5_SHIFT                       5u
#define CDDDMA_ERR_ERR5_WIDTH                       1u
#define CDDDMA_ERR_ERR5(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR5_SHIFT))&CDDDMA_ERR_ERR5_MASK)
#define CDDDMA_ERR_ERR6_MASK                        0x40u
#define CDDDMA_ERR_ERR6_SHIFT                       6u
#define CDDDMA_ERR_ERR6_WIDTH                       1u
#define CDDDMA_ERR_ERR6(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR6_SHIFT))&CDDDMA_ERR_ERR6_MASK)
#define CDDDMA_ERR_ERR7_MASK                        0x80u
#define CDDDMA_ERR_ERR7_SHIFT                       7u
#define CDDDMA_ERR_ERR7_WIDTH                       1u
#define CDDDMA_ERR_ERR7(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR7_SHIFT))&CDDDMA_ERR_ERR7_MASK)
#define CDDDMA_ERR_ERR8_MASK                        0x100u
#define CDDDMA_ERR_ERR8_SHIFT                       8u
#define CDDDMA_ERR_ERR8_WIDTH                       1u
#define CDDDMA_ERR_ERR8(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR8_SHIFT))&CDDDMA_ERR_ERR8_MASK)
#define CDDDMA_ERR_ERR9_MASK                        0x200u
#define CDDDMA_ERR_ERR9_SHIFT                       9u
#define CDDDMA_ERR_ERR9_WIDTH                       1u
#define CDDDMA_ERR_ERR9(x)                          (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR9_SHIFT))&CDDDMA_ERR_ERR9_MASK)
#define CDDDMA_ERR_ERR10_MASK                       0x400u
#define CDDDMA_ERR_ERR10_SHIFT                      10u
#define CDDDMA_ERR_ERR10_WIDTH                      1u
#define CDDDMA_ERR_ERR10(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR10_SHIFT))&CDDDMA_ERR_ERR10_MASK)
#define CDDDMA_ERR_ERR11_MASK                       0x800u
#define CDDDMA_ERR_ERR11_SHIFT                      11u
#define CDDDMA_ERR_ERR11_WIDTH                      1u
#define CDDDMA_ERR_ERR11(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR11_SHIFT))&CDDDMA_ERR_ERR11_MASK)
#define CDDDMA_ERR_ERR12_MASK                       0x1000u
#define CDDDMA_ERR_ERR12_SHIFT                      12u
#define CDDDMA_ERR_ERR12_WIDTH                      1u
#define CDDDMA_ERR_ERR12(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR12_SHIFT))&CDDDMA_ERR_ERR12_MASK)
#define CDDDMA_ERR_ERR13_MASK                       0x2000u
#define CDDDMA_ERR_ERR13_SHIFT                      13u
#define CDDDMA_ERR_ERR13_WIDTH                      1u
#define CDDDMA_ERR_ERR13(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR13_SHIFT))&CDDDMA_ERR_ERR13_MASK)
#define CDDDMA_ERR_ERR14_MASK                       0x4000u
#define CDDDMA_ERR_ERR14_SHIFT                      14u
#define CDDDMA_ERR_ERR14_WIDTH                      1u
#define CDDDMA_ERR_ERR14(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR14_SHIFT))&CDDDMA_ERR_ERR14_MASK)
#define CDDDMA_ERR_ERR15_MASK                       0x8000u
#define CDDDMA_ERR_ERR15_SHIFT                      15u
#define CDDDMA_ERR_ERR15_WIDTH                      1u
#define CDDDMA_ERR_ERR15(x)                         (((uint32)(((uint32)(x))<<CDDDMA_ERR_ERR15_SHIFT))&CDDDMA_ERR_ERR15_MASK)
/* HRS Bit Fields */
#define CDDDMA_HRS_HRS0_MASK                        0x1u
#define CDDDMA_HRS_HRS0_SHIFT                       0u
#define CDDDMA_HRS_HRS0_WIDTH                       1u
#define CDDDMA_HRS_HRS0(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS0_SHIFT))&CDDDMA_HRS_HRS0_MASK)
#define CDDDMA_HRS_HRS1_MASK                        0x2u
#define CDDDMA_HRS_HRS1_SHIFT                       1u
#define CDDDMA_HRS_HRS1_WIDTH                       1u
#define CDDDMA_HRS_HRS1(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS1_SHIFT))&CDDDMA_HRS_HRS1_MASK)
#define CDDDMA_HRS_HRS2_MASK                        0x4u
#define CDDDMA_HRS_HRS2_SHIFT                       2u
#define CDDDMA_HRS_HRS2_WIDTH                       1u
#define CDDDMA_HRS_HRS2(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS2_SHIFT))&CDDDMA_HRS_HRS2_MASK)
#define CDDDMA_HRS_HRS3_MASK                        0x8u
#define CDDDMA_HRS_HRS3_SHIFT                       3u
#define CDDDMA_HRS_HRS3_WIDTH                       1u
#define CDDDMA_HRS_HRS3(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS3_SHIFT))&CDDDMA_HRS_HRS3_MASK)
#define CDDDMA_HRS_HRS4_MASK                        0x10u
#define CDDDMA_HRS_HRS4_SHIFT                       4u
#define CDDDMA_HRS_HRS4_WIDTH                       1u
#define CDDDMA_HRS_HRS4(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS4_SHIFT))&CDDDMA_HRS_HRS4_MASK)
#define CDDDMA_HRS_HRS5_MASK                        0x20u
#define CDDDMA_HRS_HRS5_SHIFT                       5u
#define CDDDMA_HRS_HRS5_WIDTH                       1u
#define CDDDMA_HRS_HRS5(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS5_SHIFT))&CDDDMA_HRS_HRS5_MASK)
#define CDDDMA_HRS_HRS6_MASK                        0x40u
#define CDDDMA_HRS_HRS6_SHIFT                       6u
#define CDDDMA_HRS_HRS6_WIDTH                       1u
#define CDDDMA_HRS_HRS6(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS6_SHIFT))&CDDDMA_HRS_HRS6_MASK)
#define CDDDMA_HRS_HRS7_MASK                        0x80u
#define CDDDMA_HRS_HRS7_SHIFT                       7u
#define CDDDMA_HRS_HRS7_WIDTH                       1u
#define CDDDMA_HRS_HRS7(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS7_SHIFT))&CDDDMA_HRS_HRS7_MASK)
#define CDDDMA_HRS_HRS8_MASK                        0x100u
#define CDDDMA_HRS_HRS8_SHIFT                       8u
#define CDDDMA_HRS_HRS8_WIDTH                       1u
#define CDDDMA_HRS_HRS8(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS8_SHIFT))&CDDDMA_HRS_HRS8_MASK)
#define CDDDMA_HRS_HRS9_MASK                        0x200u
#define CDDDMA_HRS_HRS9_SHIFT                       9u
#define CDDDMA_HRS_HRS9_WIDTH                       1u
#define CDDDMA_HRS_HRS9(x)                          (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS9_SHIFT))&CDDDMA_HRS_HRS9_MASK)
#define CDDDMA_HRS_HRS10_MASK                       0x400u
#define CDDDMA_HRS_HRS10_SHIFT                      10u
#define CDDDMA_HRS_HRS10_WIDTH                      1u
#define CDDDMA_HRS_HRS10(x)                         (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS10_SHIFT))&CDDDMA_HRS_HRS10_MASK)
#define CDDDMA_HRS_HRS11_MASK                       0x800u
#define CDDDMA_HRS_HRS11_SHIFT                      11u
#define CDDDMA_HRS_HRS11_WIDTH                      1u
#define CDDDMA_HRS_HRS11(x)                         (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS11_SHIFT))&CDDDMA_HRS_HRS11_MASK)
#define CDDDMA_HRS_HRS12_MASK                       0x1000u
#define CDDDMA_HRS_HRS12_SHIFT                      12u
#define CDDDMA_HRS_HRS12_WIDTH                      1u
#define CDDDMA_HRS_HRS12(x)                         (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS12_SHIFT))&CDDDMA_HRS_HRS12_MASK)
#define CDDDMA_HRS_HRS13_MASK                       0x2000u
#define CDDDMA_HRS_HRS13_SHIFT                      13u
#define CDDDMA_HRS_HRS13_WIDTH                      1u
#define CDDDMA_HRS_HRS13(x)                         (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS13_SHIFT))&CDDDMA_HRS_HRS13_MASK)
#define CDDDMA_HRS_HRS14_MASK                       0x4000u
#define CDDDMA_HRS_HRS14_SHIFT                      14u
#define CDDDMA_HRS_HRS14_WIDTH                      1u
#define CDDDMA_HRS_HRS14(x)                         (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS14_SHIFT))&CDDDMA_HRS_HRS14_MASK)
#define CDDDMA_HRS_HRS15_MASK                       0x8000u
#define CDDDMA_HRS_HRS15_SHIFT                      15u
#define CDDDMA_HRS_HRS15_WIDTH                      1u
#define CDDDMA_HRS_HRS15(x)                         (((uint32)(((uint32)(x))<<CDDDMA_HRS_HRS15_SHIFT))&CDDDMA_HRS_HRS15_MASK)
/* EARS Bit Fields */
#define CDDDMA_EARS_EDREQ_0_MASK                    0x1u
#define CDDDMA_EARS_EDREQ_0_SHIFT                   0u
#define CDDDMA_EARS_EDREQ_0_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_0(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_0_SHIFT))&CDDDMA_EARS_EDREQ_0_MASK)
#define CDDDMA_EARS_EDREQ_1_MASK                    0x2u
#define CDDDMA_EARS_EDREQ_1_SHIFT                   1u
#define CDDDMA_EARS_EDREQ_1_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_1(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_1_SHIFT))&CDDDMA_EARS_EDREQ_1_MASK)
#define CDDDMA_EARS_EDREQ_2_MASK                    0x4u
#define CDDDMA_EARS_EDREQ_2_SHIFT                   2u
#define CDDDMA_EARS_EDREQ_2_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_2(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_2_SHIFT))&CDDDMA_EARS_EDREQ_2_MASK)
#define CDDDMA_EARS_EDREQ_3_MASK                    0x8u
#define CDDDMA_EARS_EDREQ_3_SHIFT                   3u
#define CDDDMA_EARS_EDREQ_3_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_3(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_3_SHIFT))&CDDDMA_EARS_EDREQ_3_MASK)
#define CDDDMA_EARS_EDREQ_4_MASK                    0x10u
#define CDDDMA_EARS_EDREQ_4_SHIFT                   4u
#define CDDDMA_EARS_EDREQ_4_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_4(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_4_SHIFT))&CDDDMA_EARS_EDREQ_4_MASK)
#define CDDDMA_EARS_EDREQ_5_MASK                    0x20u
#define CDDDMA_EARS_EDREQ_5_SHIFT                   5u
#define CDDDMA_EARS_EDREQ_5_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_5(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_5_SHIFT))&CDDDMA_EARS_EDREQ_5_MASK)
#define CDDDMA_EARS_EDREQ_6_MASK                    0x40u
#define CDDDMA_EARS_EDREQ_6_SHIFT                   6u
#define CDDDMA_EARS_EDREQ_6_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_6(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_6_SHIFT))&CDDDMA_EARS_EDREQ_6_MASK)
#define CDDDMA_EARS_EDREQ_7_MASK                    0x80u
#define CDDDMA_EARS_EDREQ_7_SHIFT                   7u
#define CDDDMA_EARS_EDREQ_7_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_7(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_7_SHIFT))&CDDDMA_EARS_EDREQ_7_MASK)
#define CDDDMA_EARS_EDREQ_8_MASK                    0x100u
#define CDDDMA_EARS_EDREQ_8_SHIFT                   8u
#define CDDDMA_EARS_EDREQ_8_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_8(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_8_SHIFT))&CDDDMA_EARS_EDREQ_8_MASK)
#define CDDDMA_EARS_EDREQ_9_MASK                    0x200u
#define CDDDMA_EARS_EDREQ_9_SHIFT                   9u
#define CDDDMA_EARS_EDREQ_9_WIDTH                   1u
#define CDDDMA_EARS_EDREQ_9(x)                      (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_9_SHIFT))&CDDDMA_EARS_EDREQ_9_MASK)
#define CDDDMA_EARS_EDREQ_10_MASK                   0x400u
#define CDDDMA_EARS_EDREQ_10_SHIFT                  10u
#define CDDDMA_EARS_EDREQ_10_WIDTH                  1u
#define CDDDMA_EARS_EDREQ_10(x)                     (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_10_SHIFT))&CDDDMA_EARS_EDREQ_10_MASK)
#define CDDDMA_EARS_EDREQ_11_MASK                   0x800u
#define CDDDMA_EARS_EDREQ_11_SHIFT                  11u
#define CDDDMA_EARS_EDREQ_11_WIDTH                  1u
#define CDDDMA_EARS_EDREQ_11(x)                     (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_11_SHIFT))&CDDDMA_EARS_EDREQ_11_MASK)
#define CDDDMA_EARS_EDREQ_12_MASK                   0x1000u
#define CDDDMA_EARS_EDREQ_12_SHIFT                  12u
#define CDDDMA_EARS_EDREQ_12_WIDTH                  1u
#define CDDDMA_EARS_EDREQ_12(x)                     (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_12_SHIFT))&CDDDMA_EARS_EDREQ_12_MASK)
#define CDDDMA_EARS_EDREQ_13_MASK                   0x2000u
#define CDDDMA_EARS_EDREQ_13_SHIFT                  13u
#define CDDDMA_EARS_EDREQ_13_WIDTH                  1u
#define CDDDMA_EARS_EDREQ_13(x)                     (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_13_SHIFT))&CDDDMA_EARS_EDREQ_13_MASK)
#define CDDDMA_EARS_EDREQ_14_MASK                   0x4000u
#define CDDDMA_EARS_EDREQ_14_SHIFT                  14u
#define CDDDMA_EARS_EDREQ_14_WIDTH                  1u
#define CDDDMA_EARS_EDREQ_14(x)                     (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_14_SHIFT))&CDDDMA_EARS_EDREQ_14_MASK)
#define CDDDMA_EARS_EDREQ_15_MASK                   0x8000u
#define CDDDMA_EARS_EDREQ_15_SHIFT                  15u
#define CDDDMA_EARS_EDREQ_15_WIDTH                  1u
#define CDDDMA_EARS_EDREQ_15(x)                     (((uint32)(((uint32)(x))<<CDDDMA_EARS_EDREQ_15_SHIFT))&CDDDMA_EARS_EDREQ_15_MASK)
/* DCHPRI Bit Fields */
#define CDDDMA_DCHPRI_CHPRI_MASK                    0xFu
#define CDDDMA_DCHPRI_CHPRI_SHIFT                   0u
#define CDDDMA_DCHPRI_CHPRI_WIDTH                   4u
#define CDDDMA_DCHPRI_CHPRI(x)                      (((uint8)(((uint8)(x))<<CDDDMA_DCHPRI_CHPRI_SHIFT))&CDDDMA_DCHPRI_CHPRI_MASK)
#define CDDDMA_DCHPRI_DPA_MASK                      0x40u
#define CDDDMA_DCHPRI_DPA_SHIFT                     6u
#define CDDDMA_DCHPRI_DPA_WIDTH                     1u
#define CDDDMA_DCHPRI_DPA(x)                        (((uint8)(((uint8)(x))<<CDDDMA_DCHPRI_DPA_SHIFT))&CDDDMA_DCHPRI_DPA_MASK)
#define CDDDMA_DCHPRI_ECP_MASK                      0x80u
#define CDDDMA_DCHPRI_ECP_SHIFT                     7u
#define CDDDMA_DCHPRI_ECP_WIDTH                     1u
#define CDDDMA_DCHPRI_ECP(x)                        (((uint8)(((uint8)(x))<<CDDDMA_DCHPRI_ECP_SHIFT))&CDDDMA_DCHPRI_ECP_MASK)
/* TCD_SADDR Bit Fields */
#define CDDDMA_TCD_SADDR_SADDR_MASK                 0xFFFFFFFFu
#define CDDDMA_TCD_SADDR_SADDR_SHIFT                0u
#define CDDDMA_TCD_SADDR_SADDR_WIDTH                32u
#define CDDDMA_TCD_SADDR_SADDR(x)                   (((uint32)(((uint32)(x))<<CDDDMA_TCD_SADDR_SADDR_SHIFT))&CDDDMA_TCD_SADDR_SADDR_MASK)
/* TCD_SOFF Bit Fields */
#define CDDDMA_TCD_SOFF_SOFF_MASK                   0xFFFFu
#define CDDDMA_TCD_SOFF_SOFF_SHIFT                  0u
#define CDDDMA_TCD_SOFF_SOFF_WIDTH                  16u
#define CDDDMA_TCD_SOFF_SOFF(x)                     (((uint16)(((uint16)(x))<<CDDDMA_TCD_SOFF_SOFF_SHIFT))&CDDDMA_TCD_SOFF_SOFF_MASK)
/* TCD_ATTR Bit Fields */
#define CDDDMA_TCD_ATTR_DSIZE_MASK                  0x7u
#define CDDDMA_TCD_ATTR_DSIZE_SHIFT                 0u
#define CDDDMA_TCD_ATTR_DSIZE_WIDTH                 3u
#define CDDDMA_TCD_ATTR_DSIZE(x)                    (((uint16)(((uint16)(x))<<CDDDMA_TCD_ATTR_DSIZE_SHIFT))&CDDDMA_TCD_ATTR_DSIZE_MASK)
#define CDDDMA_TCD_ATTR_DMOD_MASK                   0xF8u
#define CDDDMA_TCD_ATTR_DMOD_SHIFT                  3u
#define CDDDMA_TCD_ATTR_DMOD_WIDTH                  5u
#define CDDDMA_TCD_ATTR_DMOD(x)                     (((uint16)(((uint16)(x))<<CDDDMA_TCD_ATTR_DMOD_SHIFT))&CDDDMA_TCD_ATTR_DMOD_MASK)
#define CDDDMA_TCD_ATTR_SSIZE_MASK                  0x700u
#define CDDDMA_TCD_ATTR_SSIZE_SHIFT                 8u
#define CDDDMA_TCD_ATTR_SSIZE_WIDTH                 3u
#define CDDDMA_TCD_ATTR_SSIZE(x)                    (((uint16)(((uint16)(x))<<CDDDMA_TCD_ATTR_SSIZE_SHIFT))&CDDDMA_TCD_ATTR_SSIZE_MASK)
#define CDDDMA_TCD_ATTR_SMOD_MASK                   0xF800u
#define CDDDMA_TCD_ATTR_SMOD_SHIFT                  11u
#define CDDDMA_TCD_ATTR_SMOD_WIDTH                  5u
#define CDDDMA_TCD_ATTR_SMOD(x)                     (((uint16)(((uint16)(x))<<CDDDMA_TCD_ATTR_SMOD_SHIFT))&CDDDMA_TCD_ATTR_SMOD_MASK)
/* TCD_NBYTES_MLNO Bit Fields */
#define CDDDMA_TCD_NBYTES_MLNO_NBYTES_MASK          0xFFFFFFFFu
#define CDDDMA_TCD_NBYTES_MLNO_NBYTES_SHIFT         0u
#define CDDDMA_TCD_NBYTES_MLNO_NBYTES_WIDTH         32u
#define CDDDMA_TCD_NBYTES_MLNO_NBYTES(x)            (((uint32)(((uint32)(x))<<CDDDMA_TCD_NBYTES_MLNO_NBYTES_SHIFT))&CDDDMA_TCD_NBYTES_MLNO_NBYTES_MASK)
/* TCD_NBYTES_MLOFFNO Bit Fields */
#define CDDDMA_TCD_NBYTES_MLOFFNO_NBYTES_MASK       0x3FFFFFFFu
#define CDDDMA_TCD_NBYTES_MLOFFNO_NBYTES_SHIFT      0u
#define CDDDMA_TCD_NBYTES_MLOFFNO_NBYTES_WIDTH      30u
#define CDDDMA_TCD_NBYTES_MLOFFNO_NBYTES(x)         (((uint32)(((uint32)(x))<<CDDDMA_TCD_NBYTES_MLOFFNO_NBYTES_SHIFT))&CDDDMA_TCD_NBYTES_MLOFFNO_NBYTES_MASK)
#define CDDDMA_TCD_NBYTES_MLOFFNO_DMLOE_MASK        0x40000000u
#define CDDDMA_TCD_NBYTES_MLOFFNO_DMLOE_SHIFT       30u
#define CDDDMA_TCD_NBYTES_MLOFFNO_DMLOE_WIDTH       1u
#define CDDDMA_TCD_NBYTES_MLOFFNO_DMLOE(x)          (((uint32)(((uint32)(x))<<CDDDMA_TCD_NBYTES_MLOFFNO_DMLOE_SHIFT))&CDDDMA_TCD_NBYTES_MLOFFNO_DMLOE_MASK)
#define CDDDMA_TCD_NBYTES_MLOFFNO_SMLOE_MASK        0x80000000u
#define CDDDMA_TCD_NBYTES_MLOFFNO_SMLOE_SHIFT       31u
#define CDDDMA_TCD_NBYTES_MLOFFNO_SMLOE_WIDTH       1u
#define CDDDMA_TCD_NBYTES_MLOFFNO_SMLOE(x)          (((uint32)(((uint32)(x))<<CDDDMA_TCD_NBYTES_MLOFFNO_SMLOE_SHIFT))&CDDDMA_TCD_NBYTES_MLOFFNO_SMLOE_MASK)
/* TCD_NBYTES_MLOFFYES Bit Fields */
#define CDDDMA_TCD_NBYTES_MLOFFYES_NBYTES_MASK      0x3FFu
#define CDDDMA_TCD_NBYTES_MLOFFYES_NBYTES_SHIFT     0u
#define CDDDMA_TCD_NBYTES_MLOFFYES_NBYTES_WIDTH     10u
#define CDDDMA_TCD_NBYTES_MLOFFYES_NBYTES(x)        (((uint32)(((uint32)(x))<<CDDDMA_TCD_NBYTES_MLOFFYES_NBYTES_SHIFT))&CDDDMA_TCD_NBYTES_MLOFFYES_NBYTES_MASK)
#define CDDDMA_TCD_NBYTES_MLOFFYES_MLOFF_MASK       0x3FFFFC00u
#define CDDDMA_TCD_NBYTES_MLOFFYES_MLOFF_SHIFT      10u
#define CDDDMA_TCD_NBYTES_MLOFFYES_MLOFF_WIDTH      20u
#define CDDDMA_TCD_NBYTES_MLOFFYES_MLOFF(x)         (((uint32)(((uint32)(x))<<CDDDMA_TCD_NBYTES_MLOFFYES_MLOFF_SHIFT))&CDDDMA_TCD_NBYTES_MLOFFYES_MLOFF_MASK)
#define CDDDMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK       0x40000000u
#define CDDDMA_TCD_NBYTES_MLOFFYES_DMLOE_SHIFT      30u
#define CDDDMA_TCD_NBYTES_MLOFFYES_DMLOE_WIDTH      1u
#define CDDDMA_TCD_NBYTES_MLOFFYES_DMLOE(x)         (((uint32)(((uint32)(x))<<CDDDMA_TCD_NBYTES_MLOFFYES_DMLOE_SHIFT))&CDDDMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK)
#define CDDDMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK       0x80000000u
#define CDDDMA_TCD_NBYTES_MLOFFYES_SMLOE_SHIFT      31u
#define CDDDMA_TCD_NBYTES_MLOFFYES_SMLOE_WIDTH      1u
#define CDDDMA_TCD_NBYTES_MLOFFYES_SMLOE(x)         (((uint32)(((uint32)(x))<<CDDDMA_TCD_NBYTES_MLOFFYES_SMLOE_SHIFT))&CDDDMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK)
/* TCD_SLAST Bit Fields */
#define CDDDMA_TCD_SLAST_SLAST_MASK                 0xFFFFFFFFu
#define CDDDMA_TCD_SLAST_SLAST_SHIFT                0u
#define CDDDMA_TCD_SLAST_SLAST_WIDTH                32u
#define CDDDMA_TCD_SLAST_SLAST(x)                   (((uint32)(((uint32)(x))<<CDDDMA_TCD_SLAST_SLAST_SHIFT))&CDDDMA_TCD_SLAST_SLAST_MASK)
/* TCD_DADDR Bit Fields */
#define CDDDMA_TCD_DADDR_DADDR_MASK                 0xFFFFFFFFu
#define CDDDMA_TCD_DADDR_DADDR_SHIFT                0u
#define CDDDMA_TCD_DADDR_DADDR_WIDTH                32u
#define CDDDMA_TCD_DADDR_DADDR(x)                   (((uint32)(((uint32)(x))<<CDDDMA_TCD_DADDR_DADDR_SHIFT))&CDDDMA_TCD_DADDR_DADDR_MASK)
/* TCD_DOFF Bit Fields */
#define CDDDMA_TCD_DOFF_DOFF_MASK                   0xFFFFu
#define CDDDMA_TCD_DOFF_DOFF_SHIFT                  0u
#define CDDDMA_TCD_DOFF_DOFF_WIDTH                  16u
#define CDDDMA_TCD_DOFF_DOFF(x)                     (((uint16)(((uint16)(x))<<CDDDMA_TCD_DOFF_DOFF_SHIFT))&CDDDMA_TCD_DOFF_DOFF_MASK)
/* TCD_CITER_ELINKNO Bit Fields */
#define CDDDMA_TCD_CITER_ELINKNO_CITER_MASK         0x7FFFu
#define CDDDMA_TCD_CITER_ELINKNO_CITER_SHIFT        0u
#define CDDDMA_TCD_CITER_ELINKNO_CITER_WIDTH        15u
#define CDDDMA_TCD_CITER_ELINKNO_CITER(x)           (((uint16)(((uint16)(x))<<CDDDMA_TCD_CITER_ELINKNO_CITER_SHIFT))&CDDDMA_TCD_CITER_ELINKNO_CITER_MASK)
#define CDDDMA_TCD_CITER_ELINKNO_ELINK_MASK         0x8000u
#define CDDDMA_TCD_CITER_ELINKNO_ELINK_SHIFT        15u
#define CDDDMA_TCD_CITER_ELINKNO_ELINK_WIDTH        1u
#define CDDDMA_TCD_CITER_ELINKNO_ELINK(x)           (((uint16)(((uint16)(x))<<CDDDMA_TCD_CITER_ELINKNO_ELINK_SHIFT))&CDDDMA_TCD_CITER_ELINKNO_ELINK_MASK)
/* TCD_CITER_ELINKYES Bit Fields */
#define CDDDMA_TCD_CITER_ELINKYES_CITER_LE_MASK     0x1FFu
#define CDDDMA_TCD_CITER_ELINKYES_CITER_LE_SHIFT    0u
#define CDDDMA_TCD_CITER_ELINKYES_CITER_LE_WIDTH    9u
#define CDDDMA_TCD_CITER_ELINKYES_CITER_LE(x)       (((uint16)(((uint16)(x))<<CDDDMA_TCD_CITER_ELINKYES_CITER_LE_SHIFT))&CDDDMA_TCD_CITER_ELINKYES_CITER_LE_MASK)
#define CDDDMA_TCD_CITER_ELINKYES_LINKCH_MASK       0x1E00u
#define CDDDMA_TCD_CITER_ELINKYES_LINKCH_SHIFT      9u
#define CDDDMA_TCD_CITER_ELINKYES_LINKCH_WIDTH      4u
#define CDDDMA_TCD_CITER_ELINKYES_LINKCH(x)         (((uint16)(((uint16)(x))<<CDDDMA_TCD_CITER_ELINKYES_LINKCH_SHIFT))&CDDDMA_TCD_CITER_ELINKYES_LINKCH_MASK)
#define CDDDMA_TCD_CITER_ELINKYES_ELINK_MASK        0x8000u
#define CDDDMA_TCD_CITER_ELINKYES_ELINK_SHIFT       15u
#define CDDDMA_TCD_CITER_ELINKYES_ELINK_WIDTH       1u
#define CDDDMA_TCD_CITER_ELINKYES_ELINK(x)          (((uint16)(((uint16)(x))<<CDDDMA_TCD_CITER_ELINKYES_ELINK_SHIFT))&CDDDMA_TCD_CITER_ELINKYES_ELINK_MASK)
/* TCD_DLASTSGA Bit Fields */
#define CDDDMA_TCD_DLASTSGA_DLASTSGA_MASK           0xFFFFFFFFu
#define CDDDMA_TCD_DLASTSGA_DLASTSGA_SHIFT          0u
#define CDDDMA_TCD_DLASTSGA_DLASTSGA_WIDTH          32u
#define CDDDMA_TCD_DLASTSGA_DLASTSGA(x)             (((uint32)(((uint32)(x))<<CDDDMA_TCD_DLASTSGA_DLASTSGA_SHIFT))&CDDDMA_TCD_DLASTSGA_DLASTSGA_MASK)
/* TCD_CSR Bit Fields */
#define CDDDMA_TCD_CSR_START_MASK                   0x1u
#define CDDDMA_TCD_CSR_START_SHIFT                  0u
#define CDDDMA_TCD_CSR_START_WIDTH                  1u
#define CDDDMA_TCD_CSR_START(x)                     (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_START_SHIFT))&CDDDMA_TCD_CSR_START_MASK)
#define CDDDMA_TCD_CSR_INTMAJOR_MASK                0x2u
#define CDDDMA_TCD_CSR_INTMAJOR_SHIFT               1u
#define CDDDMA_TCD_CSR_INTMAJOR_WIDTH               1u
#define CDDDMA_TCD_CSR_INTMAJOR(x)                  (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_INTMAJOR_SHIFT))&CDDDMA_TCD_CSR_INTMAJOR_MASK)
#define CDDDMA_TCD_CSR_INTHALF_MASK                 0x4u
#define CDDDMA_TCD_CSR_INTHALF_SHIFT                2u
#define CDDDMA_TCD_CSR_INTHALF_WIDTH                1u
#define CDDDMA_TCD_CSR_INTHALF(x)                   (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_INTHALF_SHIFT))&CDDDMA_TCD_CSR_INTHALF_MASK)
#define CDDDMA_TCD_CSR_DREQ_MASK                    0x8u
#define CDDDMA_TCD_CSR_DREQ_SHIFT                   3u
#define CDDDMA_TCD_CSR_DREQ_WIDTH                   1u
#define CDDDMA_TCD_CSR_DREQ(x)                      (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_DREQ_SHIFT))&CDDDMA_TCD_CSR_DREQ_MASK)
#define CDDDMA_TCD_CSR_ESG_MASK                     0x10u
#define CDDDMA_TCD_CSR_ESG_SHIFT                    4u
#define CDDDMA_TCD_CSR_ESG_WIDTH                    1u
#define CDDDMA_TCD_CSR_ESG(x)                       (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_ESG_SHIFT))&CDDDMA_TCD_CSR_ESG_MASK)
#define CDDDMA_TCD_CSR_MAJORELINK_MASK              0x20u
#define CDDDMA_TCD_CSR_MAJORELINK_SHIFT             5u
#define CDDDMA_TCD_CSR_MAJORELINK_WIDTH             1u
#define CDDDMA_TCD_CSR_MAJORELINK(x)                (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_MAJORELINK_SHIFT))&CDDDMA_TCD_CSR_MAJORELINK_MASK)
#define CDDDMA_TCD_CSR_ACTIVE_MASK                  0x40u
#define CDDDMA_TCD_CSR_ACTIVE_SHIFT                 6u
#define CDDDMA_TCD_CSR_ACTIVE_WIDTH                 1u
#define CDDDMA_TCD_CSR_ACTIVE(x)                    (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_ACTIVE_SHIFT))&CDDDMA_TCD_CSR_ACTIVE_MASK)
#define CDDDMA_TCD_CSR_DONE_MASK                    0x80u
#define CDDDMA_TCD_CSR_DONE_SHIFT                   7u
#define CDDDMA_TCD_CSR_DONE_WIDTH                   1u
#define CDDDMA_TCD_CSR_DONE(x)                      (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_DONE_SHIFT))&CDDDMA_TCD_CSR_DONE_MASK)
#define CDDDMA_TCD_CSR_MAJORLINKCH_MASK             0xF00u
#define CDDDMA_TCD_CSR_MAJORLINKCH_SHIFT            8u
#define CDDDMA_TCD_CSR_MAJORLINKCH_WIDTH            4u
#define CDDDMA_TCD_CSR_MAJORLINKCH(x)               (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_MAJORLINKCH_SHIFT))&CDDDMA_TCD_CSR_MAJORLINKCH_MASK)
#define CDDDMA_TCD_CSR_BWC_MASK                     0xC000u
#define CDDDMA_TCD_CSR_BWC_SHIFT                    14u
#define CDDDMA_TCD_CSR_BWC_WIDTH                    2u
#define CDDDMA_TCD_CSR_BWC(x)                       (((uint16)(((uint16)(x))<<CDDDMA_TCD_CSR_BWC_SHIFT))&CDDDMA_TCD_CSR_BWC_MASK)
/* TCD_BITER_ELINKNO Bit Fields */
#define CDDDMA_TCD_BITER_ELINKNO_BITER_MASK         0x7FFFu
#define CDDDMA_TCD_BITER_ELINKNO_BITER_SHIFT        0u
#define CDDDMA_TCD_BITER_ELINKNO_BITER_WIDTH        15u
#define CDDDMA_TCD_BITER_ELINKNO_BITER(x)           (((uint16)(((uint16)(x))<<CDDDMA_TCD_BITER_ELINKNO_BITER_SHIFT))&CDDDMA_TCD_BITER_ELINKNO_BITER_MASK)
#define CDDDMA_TCD_BITER_ELINKNO_ELINK_MASK         0x8000u
#define CDDDMA_TCD_BITER_ELINKNO_ELINK_SHIFT        15u
#define CDDDMA_TCD_BITER_ELINKNO_ELINK_WIDTH        1u
#define CDDDMA_TCD_BITER_ELINKNO_ELINK(x)           (((uint16)(((uint16)(x))<<CDDDMA_TCD_BITER_ELINKNO_ELINK_SHIFT))&CDDDMA_TCD_BITER_ELINKNO_ELINK_MASK)
/* TCD_BITER_ELINKYES Bit Fields */
#define CDDDMA_TCD_BITER_ELINKYES_BITER_MASK        0x1FFu
#define CDDDMA_TCD_BITER_ELINKYES_BITER_SHIFT       0u
#define CDDDMA_TCD_BITER_ELINKYES_BITER_WIDTH       9u
#define CDDDMA_TCD_BITER_ELINKYES_BITER(x)          (((uint16)(((uint16)(x))<<CDDDMA_TCD_BITER_ELINKYES_BITER_SHIFT))&CDDDMA_TCD_BITER_ELINKYES_BITER_MASK)
#define CDDDMA_TCD_BITER_ELINKYES_LINKCH_MASK       0x1E00u
#define CDDDMA_TCD_BITER_ELINKYES_LINKCH_SHIFT      9u
#define CDDDMA_TCD_BITER_ELINKYES_LINKCH_WIDTH      4u
#define CDDDMA_TCD_BITER_ELINKYES_LINKCH(x)         (((uint16)(((uint16)(x))<<CDDDMA_TCD_BITER_ELINKYES_LINKCH_SHIFT))&CDDDMA_TCD_BITER_ELINKYES_LINKCH_MASK)
#define CDDDMA_TCD_BITER_ELINKYES_ELINK_MASK        0x8000u
#define CDDDMA_TCD_BITER_ELINKYES_ELINK_SHIFT       15u
#define CDDDMA_TCD_BITER_ELINKYES_ELINK_WIDTH       1u
#define CDDDMA_TCD_BITER_ELINKYES_ELINK(x)          (((uint16)(((uint16)(x))<<CDDDMA_TCD_BITER_ELINKYES_ELINK_SHIFT))&CDDDMA_TCD_BITER_ELINKYES_ELINK_MASK)

/** CDDDMA - Size of Registers Arrays */
#define CDDDMA_DCHPRI_COUNT                         16u
#define CDDDMA_TCD_COUNT                            16u

/** Number of instances of the DMA module. */
#define CDDDMA_INSTANCE_COUNT                       (1u)

/* DMA module features */

/* @brief Number of DMA channels. */
#define FEATURE_DMA_CHANNELS (16U)
/* @brief Number of DMA virtual channels. */
#define FEATURE_DMA_VIRTUAL_CHANNELS (FEATURE_DMA_CHANNELS * CDDDMA_INSTANCE_COUNT)
/* @brief Number of DMA interrupt lines. */
#define FEATURE_DMA_CHANNELS_INTERRUPT_LINES (16U)
/* @brief Number of DMA virtual interrupt lines. */
#define FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES ((uint32)FEATURE_DMA_CHANNELS_INTERRUPT_LINES * (uint32)CDDDMA_INSTANCE_COUNT)
/* @brief Number of DMA error interrupt lines. */
#define FEATURE_DMA_ERROR_INTERRUPT_LINES (1U)
/* @brief Number of DMA virtual error interrupt lines. */
#define FEATURE_DMA_VIRTUAL_ERROR_INTERRUPT_LINES ((uint32)FEATURE_DMA_ERROR_INTERRUPT_LINES * (uint32)CDDDMA_INSTANCE_COUNT)
/* @brief DMA module has error interrupt. */
#define FEATURE_DMA_HAS_ERROR_IRQ
/* @brief DMA module separate interrupt lines for each channel */
#define FEATURE_DMA_SEPARATE_IRQ_LINES_PER_CHN
/* @brief Conversion from channel index to DCHPRI index. */
#define FEATURE_DMA_CHN_TO_DCHPRI_INDEX(x) ((x) ^ 3U)
/* @brief DMA channel groups count. */
#define FEATURE_DMA_CHANNEL_GROUP_COUNT (1U)
/* @brief Clock name for DMA */
//#define FEATURE_DMA_CLOCK_NAMES {SIM_DMA_CLK}
#define FEATURE_DMA_CLOCK_NAMES {35U}
/* @brief DMA channel width based on number of TCDs: 2^N, N=4,5,... */
#define FEATURE_DMA_CH_WIDTH (4U)
/* @brief DMA channel to instance */
#define FEATURE_DMA_VCH_TO_INSTANCE(x)   ((x) >> (uint32)FEATURE_DMA_CH_WIDTH)
/* @brief DMA virtual channel to channel */
#define FEATURE_DMA_VCH_TO_CH(x)        ((x) & ((uint32)FEATURE_DMA_CHANNELS - 1U))
/* @brief DMA supports the following particular transfer size: */
#define FEATURE_DMA_TRANSFER_SIZE_16B
#define FEATURE_DMA_TRANSFER_SIZE_32B

/* DMAMUX module features */

/* @brief DMAMUX peripheral is available in silicon. */
#define FEATURE_DMAMUX_AVAILABLE
/* @brief Number of DMA channels. */
#define FEATURE_DMAMUX_CHANNELS (16U)
/* @brief Has the periodic trigger capability */
#define FEATURE_DMAMUX_HAS_TRIG (1)
/* @brief Conversion from request source to the actual DMAMUX channel */
#define FEATURE_DMAMUX_REQ_SRC_TO_CH(x) (x)
/* @brief Mapping between request source and DMAMUX instance */
#define FEATURE_DMAMUX_REQ_SRC_TO_INSTANCE(x) (0U)
/* @brief Conversion from eDMA channel index to DMAMUX channel. */
#define FEATURE_DMAMUX_DMA_CH_TO_CH(x) (x)
/* @brief Conversion from DMAMUX channel DMAMUX register index. */
#define FEATURE_DMAMUX_CHN_REG_INDEX(x) (x)
/* @brief Clock names for DMAMUX. */
//#define FEATURE_DMAMUX_CLOCK_NAMES {DMAMUX0_CLK}
#define FEATURE_DMAMUX_CLOCK_NAMES {43u}

typedef enum {
  CDDDMA_CHN_PRIORITY_0 = 0U,
  CDDDMA_CHN_PRIORITY_1 = 1U,
  CDDDMA_CHN_PRIORITY_2 = 2U,
  CDDDMA_CHN_PRIORITY_3 = 3U,
#ifndef FEATURE_DMA_4_CH_PRIORITIES    
  CDDDMA_CHN_PRIORITY_4 = 4U,
  CDDDMA_CHN_PRIORITY_5 = 5U,
  CDDDMA_CHN_PRIORITY_6 = 6U,
  CDDDMA_CHN_PRIORITY_7 = 7U,
#ifndef FEATURE_DMA_8_CH_PRIORITIES
  CDDDMA_CHN_PRIORITY_8 = 8U,
  CDDDMA_CHN_PRIORITY_9 = 9U,
  CDDDMA_CHN_PRIORITY_10 = 10U,
  CDDDMA_CHN_PRIORITY_11 = 11U,
  CDDDMA_CHN_PRIORITY_12 = 12U,
  CDDDMA_CHN_PRIORITY_13 = 13U,
  CDDDMA_CHN_PRIORITY_14 = 14U,
  CDDDMA_CHN_PRIORITY_15 = 15U,
#endif
#endif
  CDDDMA_CHN_DEFAULT_PRIORITY = 255U
} tsCddDma_Channel_Priority;


typedef enum {
  CDDDMA_CHN_NORMAL = 0U,           /*!< eDMA channel normal state. */
  CDDDMA_CHN_ERROR                  /*!< An error occurred in the eDMA channel. */
} teCddDma_Chn_Status;

typedef void(*cdddma_Callback_Function)(void *parameter, teCddDma_Chn_Status status);

typedef struct {
  uint8 virtChn;                            /*!< Virtual channel number. */
  cdddma_Callback_Function callback;        /*!< Callback function pointer for the eDMA channel. It will
                                            be called at the eDMA channel complete and eDMA channel
                                            error. */
  void *parameter;                          /*!< Parameter for the callback function pointer. */
  volatile teCddDma_Chn_Status status;      /*!< eDMA channel status. */
} tsCddDma_Chn_State;

typedef struct {
  tsCddDma_Chn_State * volatile virtChnState[(uint32)FEATURE_DMA_VIRTUAL_CHANNELS];   /*!< Pointer array storing channel state. */
} tsCddDma_State;

//------------------------------------------------------------------------
/* DMA - Peripheral instance base addresses */
/** Peripheral DMA base address */
#define CDDDMA_BASE                                 (0x40008000u)
/** Peripheral DMA base pointer */
#define CDDDMA                                      ((volatile tsCddDma_S32K_146_Registers*)CDDDMA_BASE)
/** Array initializer of DMA peripheral base addresses */
#define CDDDMA_BASE_ADDRS                           { CDDDMA_BASE }
/** Array initializer of DMA peripheral base pointers */
#define CDDDMA_BASE_PTRS                            { CDDDMA }
 /** Number of interrupt vector arrays for the DMA module. */
#define CDDDMA_IRQS_ARR_COUNT                       (2u)
 /** Number of interrupt channels for the CHN type of DMA module. */
#define CDDDMA_CHN_IRQS_CH_COUNT                    (16u)
 /** Number of interrupt channels for the ERROR type of DMA module. */
#define CDDDMA_ERROR_IRQS_CH_COUNT                  (1u)
/** Interrupt vectors for the DMA peripheral type */
#define CDDDMA_CHN_IRQS                             { CDDDMA0_IRQn, CDDDMA1_IRQn, CDDDMA2_IRQn, CDDDMA3_IRQn, CDDDMA4_IRQn, CDDDMA5_IRQn, CDDDMA6_IRQn, CDDDMA7_IRQn, CDDDMA8_IRQn, CDDDMA9_IRQn, CDDDMA10_IRQn, CDDDMA11_IRQn, CDDDMA12_IRQn, CDDDMA13_IRQn, CDDDMA14_IRQn, CDDDMA15_IRQn }
#define CDDDMA_ERROR_IRQS                           { CDDDMA_Error_IRQn }

#define CDDDMA_DMAMUX_BASE                          (0x40021000u)
/** Peripheral DMAMUX base pointer */
#define CDDDMA_DMAMUX                               ((volatile tsCddDmaMux_S32K_146_Register *)CDDDMA_DMAMUX_BASE)

/**
  * \brief CR defines the basic operating configuration of the DMA
  */
typedef struct tsCddDma_S32K_146_CR
{
  uint32 Reserved_1   : 1;
  uint32 u1EDBG       : 1;
  uint32 u1ERCA       : 1;
  uint32 Reserved_2   : 1;
  uint32 u1HOE        : 1;
  uint32 u1HALT       : 1;
  uint32 u1CLM        : 1;
  uint32 u1EMLM       : 1;
  uint32 Reserved_3   : 8;
  uint32 u1ECX        : 1;
  uint32 u1CX         : 1;
  uint32 Reserved_4   : 6;
  uint32 Reserved_5   : 7;
  uint32 u1ACTIVE     : 1;
}tsCddDma_S32K_146_CR;

typedef union tuCddDma_S32K_146_CR
{
  tsCddDma_S32K_146_CR      sBit;
  uint32                    ulData;
  uint16                    aunData[2];
  uint8                     aucData[4];
}tuCddDma_S32K_146_CR;


/**
  * \brief ES provides information concerning the last recorded channel error
  */
typedef struct tsCddDma_S32K_146_ES
{
  uint32 u1DBE        : 1;
  uint32 u1SBE        : 1;
  uint32 u1SGE        : 1;
  uint32 u1NCE        : 1;
  uint32 u1DOE        : 1;
  uint32 u1DAE        : 1;
  uint32 u1SOE        : 1;
  uint32 u1SAE        : 1;
  uint32 u4ERRCHN     : 4;
  uint32 Reserved_1   : 2;
  uint32 u1CPE        : 1;
  uint32 Reserved_2   : 1;
  uint32 u1ECX        : 1;
  uint32 Reserved_3   : 14;
  uint32 u1VLD        : 1;
}tsCddDma_S32K_146_ES;

typedef union tuCddDma_S32K_146_ES
{
  tsCddDma_S32K_146_ES      sBit;
  uint32                    ulData;
  uint16                    aunData[2];
  uint8                     aucData[4];
}tuCddDma_S32K_146_ES;


/**
 * \brief ERQ register provides a bit map for the 16 channels to enable the request signal for each channel
 */
typedef struct tsCddDma_S32K_146_ERQ
{
  uint32  u1ERQ0    : 1;
  uint32  u1ERQ1    : 1;
  uint32  u1ERQ2    : 1;
  uint32  u1ERQ3    : 1;
  uint32  u1ERQ4    : 1;
  uint32  u1ERQ5    : 1;
  uint32  u1ERQ6    : 1;
  uint32  u1ERQ7    : 1;
  uint32  u1ERQ8    : 1;
  uint32  u1ERQ9    : 1;
  uint32  u1ERQ10   : 1;
  uint32  u1ERQ11   : 1;
  uint32  u1ERQ12   : 1;
  uint32  u1ERQ13   : 1;
  uint32  u1ERQ14   : 1;
  uint32  u1ERQ15   : 1;
  uint32  Reserved  : 16;
}tsCddDma_S32K_146_ERQ;

typedef union tuCddDma_S32K_146_ERQ
{
  tsCddDma_S32K_146_ERQ       sBit;
  uint32                      ulData;
  uint16                      aunData[2];
  uint8                       aucData[4];
}tuCddDma_S32K_146_ERQ;


/**
 * \brief EEI register provides a bit map for the 16 channels to enable the error interrupt signal for each channel
 */
typedef struct tsCddDma_S32K_146_EEI
{
  uint32 u1EEI0   : 1;
  uint32 u1EEI1   : 1;
  uint32 u1EEI2   : 1;
  uint32 u1EEI3   : 1;
  uint32 u1EEI4   : 1;
  uint32 u1EEI5   : 1;
  uint32 u1EEI6   : 1;
  uint32 u1EEI7   : 1;
  uint32 u1EEI8   : 1;
  uint32 u1EEI9   : 1;
  uint32 u1EEI10  : 1;
  uint32 u1EEI11  : 1;
  uint32 u1EEI12  : 1;
  uint32 u1EEI13  : 1;
  uint32 u1EEI14  : 1;
  uint32 u1EEI15  : 1;
  uint32 Reserved : 16;
}tsCddDma_S32K_146_EEI;

typedef union tuCddDma_S32K_146_EEI
{
  tsCddDma_S32K_146_EEI       sBit;
  uint32                      ulData;
  uint16                      aunData[2];
  uint8                       aucData[4];
}tuCddDma_S32K_146_EEI;


/**
 * \brief CEEI provides a simple memory-mapped mechanism to clear a given bit in the EEI
to disable the error interrupt for a given channel
  */
typedef struct tsCddDma_S32K_146_CEEI
{
  uint8 u4CEEI    : 4;
  uint8 Reserved  : 2;
  uint8 u1CAEE    : 1;
  uint8 u1NOP     : 1;
}tsCddDma_S32K_146_CEEI;

typedef union tuCddDma_S32K_146_CEEI
{
  tsCddDma_S32K_146_CEEI    sBit;
  uint8                     ucData;
}tuCddDma_S32K_146_CEEI;


/**
 * \brief SEEI provides a simple memory-mapped mechanism to set a given bit in the EEI to
enable the error interrupt for a given channel
  */
typedef struct tsCddDma_S32K_146_SEEI
{
  uint8 u4SEEI    : 4;
  uint8 Reserved  : 2;
  uint8 u1SAEE    : 1;
  uint8 u1NOP     : 1;
}tsCddDma_S32K_146_SEEI;

typedef union tuCddDma_S32K_146_SEEI
{
  tsCddDma_S32K_146_SEEI     sBit;
  uint8                      ucData;
}tuCddDma_S32K_146_SEEI;


/**
 * \brief CERQ provides a simple memory-mapped mechanism to clear a given bit in the
ERQ to disable the DMA request for a given channel
  */
typedef struct tsCddDma_S32K_146_CERQ
{
  uint8 u4CERQ    : 4;
  uint8 Reserved  : 2;
  uint8 u1CAER    : 1;
  uint8 u1NOP     : 1;
}tsCddDma_S32K_146_CERQ;

typedef union tuCddDma_S32K_146_CERQ
{
  tsCddDma_S32K_146_CERQ      sBit;
  uint8                       ucData;
}tuCddDma_S32K_146_CERQ;


/**
 * \brief SERQ provides a simple memory-mapped mechanism to set a given bit in the ERQ
to enable the DMA request for a given channel
  */
typedef struct tsCddDma_S32K_146_SERQ
{
  uint8 u4SERQ    : 4;
  uint8 Reserved  : 2;
  uint8 u1SAER    : 1;
  uint8 u1NOP     : 1;
}tsCddDma_S32K_146_SERQ;

typedef union tuCddDma_S32K_146_SERQ
{
  tsCddDma_S32K_146_SERQ      sBit;
  uint8                       ucData;
}tuCddDma_S32K_146_SERQ;


/**
 * \brief CDNE provides a simple memory-mapped mechanism to clear the DONE bit in the
TCD of the given channel
  */
typedef struct tsCddDma_S32K_146_CDNE
{
  uint8 u4CDNE    : 4;
  uint8 Reserved  : 2;
  uint8 u1CADN    : 1;
  uint8 u1NOP     : 1;
}tsCddDma_S32K_146_CDNE;

typedef union tuCddDma_S32K_146_CDNE
{
  tsCddDma_S32K_146_CDNE      sBit;
  uint8                       ucData;
}tuCddDma_S32K_146_CDNE;


/**
 * \brief SSRT provides a simple memory-mapped mechanism to set the START bit in the
TCD of the given channel
  */
typedef struct tsCddDma_S32K_146_SSRT
{
  uint8 u4SSRT    : 4;
  uint8 Reserved  : 2;
  uint8 u1SAST    : 1;
  uint8 u1NOP     : 1;
}tsCddDma_S32K_146_SSRT;

typedef union tuCddDma_S32K_146_SSRT
{
  tsCddDma_S32K_146_SSRT      sBit;
  uint8                       ucData;
}tuCddDma_S32K_146_SSRT;


/**
 * \brief CERR provides a simple memory-mapped mechanism to clear a given bit in the ERR
to disable the error condition flag for a given channel
  */
typedef struct tsCddDma_S32K_146_CERR
{
  uint8 u4CERR    : 4;
  uint8 Reserved  : 2;
  uint8 u1CAEI    : 1;
  uint8 u1NOP     : 1;
}tsCddDma_S32K_146_CERR;

typedef union tuCddDma_S32K_146_CERR
{
  tsCddDma_S32K_146_CERR      sBit;
  uint8                       ucData;
}tuCddDma_S32K_146_CERR;


/**
 * \brief CINT provides a simple, memory-mapped mechanism to clear a given bit in the INT
to disable the interrupt request for a given channel
  */
typedef struct tsCddDma_S32K_146_CINT
{
  uint8 u4CINT    : 4;
  uint8 Reserved  : 2;
  uint8 u1CAIR    : 1;
  uint8 u1NOP     : 1;
}tsCddDma_S32K_146_CINT;

typedef union tuCddDma_S32K_146_CINT
{
  tsCddDma_S32K_146_CINT      sBit;
  uint8                        ucData;
}tuCddDma_S32K_146_CINT;


/**
 * \brief INT register provides a bit map for the 16 channels signaling the presence of an
interrupt request for each channel. Depending on the appropriate bit setting in the
transfer-control descriptors, the eDMA engine generates an interrupt on data transfer
completion. The outputs of this register are directly routed to the interrupt controller
  */
typedef struct tsCddDma_S32K_146_INT
{
  uint32 u1INT0   : 1;
  uint32 u1INT1   : 1;
  uint32 u1INT2   : 1;
  uint32 u1INT3   : 1;
  uint32 u1INT4   : 1;
  uint32 u1INT5   : 1;
  uint32 u1INT6   : 1;
  uint32 u1INT7   : 1;
  uint32 u1INT8   : 1;
  uint32 u1INT9   : 1;
  uint32 u1INT10  : 1;
  uint32 u1INT11  : 1;
  uint32 u1INT12  : 1;
  uint32 u1INT13  : 1;
  uint32 u1INT14  : 1;
  uint32 u1INT15  : 1;
  uint32 Reserved : 16;
}tsCddDma_S32K_146_INT;

typedef union tuCddDma_S32K_146_INT
{
  tsCddDma_S32K_146_INT        sBit;
  uint32                       ulData;
  uint16                       aunData[2];
  uint8                        aucData[4];
}tuCddDma_S32K_146_INT;


/**
* \brief ERR register provides a bit map for the 16 channels, signaling the presence of an
error for each channel. The eDMA engine signals the occurrence of an error condition by
setting the appropriate bit in this register. The outputs of this register are enabled by the
contents of the EEI register, and then routed to the interrupt controller. During the
execution of the interrupt-service routine associated with any DMA errors, it is software's
responsibility to clear the appropriate bit, negating the error-interrupt request.
  */
typedef struct tsCddDma_S32K_146_ERR
{
  uint32 u1ERR0   : 1;
  uint32 u1ERR1   : 1;
  uint32 u1ERR2   : 1;
  uint32 u1ERR3   : 1;
  uint32 u1ERR4   : 1;
  uint32 u1ERR5   : 1;
  uint32 u1ERR6   : 1;
  uint32 u1ERR7   : 1;
  uint32 u1ERR8   : 1;
  uint32 u1ERR9   : 1;
  uint32 u1ERR10  : 1;
  uint32 u1ERR11  : 1;
  uint32 u1ERR12  : 1;
  uint32 u1ERR13  : 1;
  uint32 u1ERR14  : 1;
  uint32 u1ERR15  : 1;
  uint32 Reserved : 16;
}tsCddDma_S32K_146_ERR;

typedef union tuCddDma_S32K_146_ERR
{
  tsCddDma_S32K_146_ERR         sBit;
  uint32                        ulData;
  uint16                        aunData[2];
  uint8                         aucData[4];
}tuCddDma_S32K_146_ERR;


/**
 * \brief HRS register provides a bit map for the DMA channels, signaling the presence of a
hardware request for each channel. The hardware request status bits reflect the current
state of the register and qualified (via the ERQ fields) DMA request signals as seen by
the DMA's arbitration logic
  */
typedef struct tsCddDma_S32K_146_HRS
{
  uint32 u1HRS0   : 1;
  uint32 u1HRS1   : 1;
  uint32 u1HRS2   : 1;
  uint32 u1HRS3   : 1;
  uint32 u1HRS4   : 1;
  uint32 u1HRS5   : 1;
  uint32 u1HRS6   : 1;
  uint32 u1HRS7   : 1;
  uint32 u1HRS8   : 1;
  uint32 u1HRS9   : 1;
  uint32 u1HRS10  : 1;
  uint32 u1HRS11  : 1;
  uint32 u1HRS12  : 1;
  uint32 u1HRS13  : 1;
  uint32 u1HRS14  : 1;
  uint32 u1HRS15  : 1;
  uint32 Reserved : 16;
}tsCddDma_S32K_146_HRS;

typedef union tuCddDma_S32K_146_HRS
{
  tsCddDma_S32K_146_HRS       sBit;
  uint32                      ulData;
  uint16                      aunData[2];
  uint8                       aucData[4];
}tuCddDma_S32K_146_HRS;


/**
 * \brief EARS register is used to enable or disable the DMA requests in Enable Request
Register (ERQ) by AND'ing the bits of these two registers
  */
typedef struct tsCddDma_S32K_146_EARS
{
  uint32 u1EDREQ_0  : 1;
  uint32 u1EDREQ_1  : 1;
  uint32 u1EDREQ_2  : 1;
  uint32 u1EDREQ_3  : 1;
  uint32 u1EDREQ_4  : 1;
  uint32 u1EDREQ_5  : 1;
  uint32 u1EDREQ_6  : 1;
  uint32 u1EDREQ_7  : 1;
  uint32 u1EDREQ_8  : 1;
  uint32 u1EDREQ_9  : 1;
  uint32 u1EDREQ_10 : 1;
  uint32 u1EDREQ_11 : 1;
  uint32 u1EDREQ_12 : 1;
  uint32 u1EDREQ_13 : 1;
  uint32 u1EDREQ_14 : 1;
  uint32 u1EDREQ_15 : 1;
  uint32 Reserved   : 16;
}tsCddDma_S32K_146_EARS;

typedef union tuCddDma_S32K_146_EARS
{
  tsCddDma_S32K_146_EARS      sBit;
  uint32                      ulData;
  uint16                      aunData[2];
  uint8                       aucData[4];
}tuCddDma_S32K_146_EARS;


/**
* \brief Channel Priority Register
When fixed-priority channel arbitration is enabled (CR[ERCA] = 0), the contents of these
registers define the unique priorities associated with each channel. The channel priorities
are evaluated by numeric value; for example, 0 is the lowest priority, 1 is the next higher
priority, then 2, 3, etc. Software must program the channel priorities with unique values;
otherwise, a configuration error is reported. The range of the priority value is limited to
the values of 0 through 15.   (m = 0 to 15)
  */
typedef struct tsCddDma_S32K_146_DCHPRIm
{
  uint8 u4CHPRI     : 4;
  uint8 u2Reserved  : 2;
  uint8 u1DPA       : 1;
  uint8 u1ECP       : 1;
}tsCddDma_S32K_146_DCHPRIm;

typedef union tuCddDma_S32K_146_DCHPRIm
{
  tsCddDma_S32K_146_DCHPRIm    sBit;
  uint8                        ucData;
}tuCddDma_S32K_146_DCHPRIm;



/**
  * \brief TCD Source Address Register = TCDn_SADDR (TCD0_SADDR - TCD15_SADDR)
  */
typedef struct tsCddDma_S32K_146_TCDn_SADDR
{
  uint32   u32SADDR      : 32;
}tsCddDma_S32K_146_TCDn_SADDR;

typedef union tuCddDma_S32K_146_TCDn_SADDR
{
  tsCddDma_S32K_146_TCDn_SADDR      sBit;
  uint32                            ulData;
  uint16                            aunData[2];
  uint8                             aucData[4];
}tuCddDma_S32K_146_TCDn_SADDR;


/**
* \brief TCD Signed Source Address Register = TCDn_SOFF (TCD0_SOFF - TCD15_SOFF)
*/
typedef struct tsCddDma_S32K_146_TCDn_SOFF
{
  uint16   u16SOFF      : 16;
}tsCddDma_S32K_146_TCDn_SOFF;

typedef union tuCddDma_S32K_146_TCDn_SOFF
{
  tsCddDma_S32K_146_TCDn_SOFF        sBit;
  uint16                             unData;
  uint8                              aucData[2];
}tuCddDma_S32K_146_TCDn_SOFF;



/**
* \brief TCD Transfer Attributes = TCDn_ATTR (TCD0_ATTR - TCD15_ATTR)
*/
typedef struct tsCddDma_S32K_146_TCDn_ATTR
{
  uint16  u3DSIZE   : 3;
  uint16  u5DMOD    : 5;
  uint16  u3SSIZE   : 3;
  uint16  u5SMOD    : 5;
}tsCddDma_S32K_146_TCDn_ATTR;

typedef union tuCddDma_S32K_146_TCDn_ATTR
{
  tsCddDma_S32K_146_TCDn_ATTR         sBit;
  uint16                              unData;
  uint8                               aucData[2];
}tuCddDma_S32K_146_TCDn_ATTR;



/**
* \brief TCD Minor Byte Count (Minor Loop Mapping Disabled) = TCDn_NBYTES_MLNO (TCD0_NBYTES_MLNO - TCD15_NBYTES_MLNO)
This register, or one of the next two registers (TCD_NBYTES_MLOFFNO,
TCD_NBYTES_MLOFFYES), defines the number of bytes to transfer per request.
Which register to use depends on whether minor loop mapping is disabled, enabled but
not used for this channel, or enabled and used.
TCD word 2 is defined as follows if:
  • Minor loop mapping is disabled (CR[EMLM] = 0)
*/
typedef struct tsCddDma_S32K_146_TCDn_NBYTES_MLNO
{
  uint32 u32NBYTES             : 32;
}tsCddDma_S32K_146_TCDn_NBYTES_MLNO;

typedef union tuCddDma_S32K_146_TCDn_NBYTES_MLNO
{
  tsCddDma_S32K_146_TCDn_NBYTES_MLNO      sBit;
  uint32                                  ulData;
  uint16                                  aunData[2];
  uint8                                   aucData[4];
}tuCddDma_S32K_146_TCDn_NBYTES_MLNO;


/**
* \brief TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset Disabled) (TCD0_NBYTES_MLOFFNO -
TCD15_NBYTES_MLOFFNO)
One of three registers (this register, TCD_NBYTES_MLNO, or TCD_NBYTES_MLOFFYES), defines the number of bytes to transfer per request.
Which register to use depends on whether minor loop mapping is disabled, enabled but
not used for this channel, or enabled and used.
TCD word 2 is defined as follows if:
  • Minor loop mapping is enabled (CR[EMLM] = 1) and
  • SMLOE = 0 and DMLOE = 0
*/

typedef struct tsCddDma_S32K_146_TCDn_NBYTES_MLOFFNO
{
  uint32 u30NBYTES    : 30;
  uint32 u1DMLOE      : 1;
  uint32 u1SMLOE      : 1;
}tsCddDma_S32K_146_TCDn_NBYTES_MLOFFNO;

typedef union tuCddDma_S32K_146_TCDn_NBYTES_MLOFFNO
{
  tsCddDma_S32K_146_TCDn_NBYTES_MLOFFNO     sBit;
  uint32                                    ulData;
  uint16                                    aunData[2];
  uint8                                     aucData[4];
}tuCddDma_S32K_146_TCDn_NBYTES_MLOFFNO;


/**
* \brief TCD Signed Minor Loop Offset (Minor Loop Mapping and Offset Enabled) (TCD0_NBYTES_MLOFFYES - TCD15_NB
YTES_MLOFFYES)
  One of three registers (this register, TCD_NBYTES_MLNO, or TCD_NBYTES_MLOFFNO), defines the number of bytes to transfer per request. Which
  register to use depends on whether minor loop mapping is disabled, enabled but not used
  for this channel, or enabled and used.
  TCD word 2 is defined as follows if:
    • Minor loop mapping is enabled (CR[EMLM] = 1) and
    • Minor loop offset is enabled (SMLOE or DMLOE = 1)
  */
typedef struct tsCddDma_S32K_146_TCDn_NBYTES_MLOFFYES
{
  uint32 u10NBYTES    : 10;
  uint32 u20MLOFF     : 20;
  uint32 u1DMLOE      : 1;
  uint32 u1SMLOE      : 1;
}tsCddDma_S32K_146_TCDn_NBYTES_MLOFFYES;

typedef union tuCddDma_S32K_146_TCDn_NBYTES_MLOFFYES
{
  tsCddDma_S32K_146_TCDn_NBYTES_MLOFFYES      sBit;
  uint32                                      ulData;
  uint16                                      aunData[2];
  uint8                                       aucData[4];
}tuCddDma_S32K_146_TCDn_NBYTES_MLOFFYES;


typedef union tuCddDma_S32K_146_TCDn_NBYTES
{
  tuCddDma_S32K_146_TCDn_NBYTES_MLNO         tuMLNO;
  tuCddDma_S32K_146_TCDn_NBYTES_MLOFFNO      tuMLOFFNO;
  tuCddDma_S32K_146_TCDn_NBYTES_MLOFFYES     tuMLOFFYES;
}tuCddDma_S32K_146_TCDn_NBYTES;


/**
* \brief TCD Last Source Address Adjustment (TCD0_SLAST - TCD15_SLAST)
*/

typedef struct tsCddDma_S32K_146_TCDn_SLAST
{
  uint32 u32SLAST        : 32;
}tsCddDma_S32K_146_TCDn_SLAST;

typedef union tuCddDma_S32K_146_TCDn_SLAST
{
  tsCddDma_S32K_146_TCDn_SLAST      sBit;
  uint32                            ulData;
}tuCddDma_S32K_146_TCDn_SLAST;


/**
* \brief TCD Destination Address (TCD0_DADDR - TCD15_DADDR)
*/
typedef struct tsCddDma_S32K_146_TCDn_DADDR
{
  uint32 u32DADDR        : 32;
}tsCddDma_S32K_146_TCDn_DADDR;

typedef union tuCddDma_S32K_146_TCDn_DADDR
{
  tsCddDma_S32K_146_TCDn_DADDR      sBit;
  uint32                            ulData;
}tuCddDma_S32K_146_TCDn_DADDR;


/**
* \brief TCD Signed Destination Address Offset (TCD0_DOFF - TCD15_DOFF)
*/
typedef struct tsCddDma_S32K_146_TCDn_DOFF
{
  uint16 u16DOFF        : 16;
}tsCddDma_S32K_146_TCDn_DOFF;

typedef union tuCddDma_S32K_146_TCDn_DOFF
{
  tsCddDma_S32K_146_TCDn_DOFF       sBit;
  uint16                            unData;
}tuCddDma_S32K_146_TCDn_DOFF;


/**
 * \brief   TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled) (TCD0_CITER_ELINKNO - TCD15_CITER_ELINKNO)
 This register contains the minor-loop channel-linking configuration and the channel's
 current iteration count. It is the same register as TCD Current Minor Loop Link, Major
 Loop Count (Channel Linking Enabled) (TCD0_CITER_ELINKYES - TCD15_CITER_
 ELINKYES), but its fields are defined differently based on the state of the ELINK field.
 If the ELINK field is cleared, this register is defined as follows.
 */

typedef struct tsCddDma_S32K_146_TCDn_CITER_ELINKNO
{
  uint16 u15CITER     : 15;
  uint16 u1ELINK      : 1;
}tsCddDma_S32K_146_TCDn_CITER_ELINKNO;

typedef union tuCddDma_S32K_146_TCDn_CITER_ELINKNO
{
  tsCddDma_S32K_146_TCDn_CITER_ELINKNO    sBit;
  uint16                                  unData;
}tuCddDma_S32K_146_TCDn_CITER_ELINKNO;


/**
* \brief   TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled) (TCD0_CITER_ELINKYES - TCD15_CITER_ELINKYES)
This register contains the minor-loop channel-linking configuration and the channel's
current iteration count. It is the same register as TCD Current Minor Loop Link, Major
Loop Count (Channel Linking Disabled) (TCD0_CITER_ELINKNO - TCD15_CITER_
ELINKNO), but its fields are defined differently based on the state of the ELINK field. If
the ELINK field is set, this register is defined as follows.
*/
typedef struct tsCddDma_S32K_146_TCDn_CITER_ELINKYES
{
  uint16 u9CITER    : 9;
  uint16 u4LINKCH   : 4;
  uint16 Reserved   : 2;
  uint16 u1ELINK    : 1;

}tsCddDma_S32K_146_TCDn_CITER_ELINKYES;

typedef union tuCddDma_S32K_146_TCDn_CITER_ELINKYES
{
  tsCddDma_S32K_146_TCDn_CITER_ELINKYES       sBit;
  uint16                                      unData;
}tuCddDma_S32K_146_TCDn_CITER_ELINKYES;


typedef union tuCddDma_S32K_146_TCDn_CITER
{
  tuCddDma_S32K_146_TCDn_CITER_ELINKNO      tuELINKNO;
  tuCddDma_S32K_146_TCDn_CITER_ELINKYES     tuELINKYES;
}tuCddDma_S32K_146_TCDn_CITER;

/**
* \brief   TCD Last Destination Address Adjustment/Scatter Gather Address (TCD0_DLASTSGA - TCD15_DLASTSGA)
*/
typedef struct tsCddDma_S32K_146_TCDn_DLASTSGA
{
  uint32 u32DLASTSGA        : 32;
}tsCddDma_S32K_146_TCDn_DLASTSGA;

typedef union tuCddDma_S32K_146_TCDn_DLASTSGA
{
  tsCddDma_S32K_146_TCDn_DLASTSGA         sBit;
  uint32                                  ulData;
}tuCddDma_S32K_146_TCDn_DLASTSGA;


/**
* \brief   TCD Control and Status (TCD0_CSR - TCD15_CSR)
*/
typedef struct tsCddDma_S32K_146_TCDn_CSR
{
  uint16 u1START        : 1;
  uint16 u1INTMAJOR     : 1;
  uint16 u1INTHALF      : 1;
  uint16 u1DREQ         : 1;
  uint16 u1ESG          : 1;
  uint16 u1MAJORELINK   : 1;
  uint16 u1ACTIVE       : 1;
  uint16 u1DONE         : 1;
  uint16 u4MAJORLINKCH  : 1;
  uint16 Reserved       : 2;
  uint16 u2BWC          : 2;
}tsCddDma_S32K_146_TCDn_CSR;

typedef union tuCddDma_S32K_146_TCDn_CSR
{
  tsCddDma_S32K_146_TCDn_CSR    sBit;
  uint16                        unData;
}tuCddDma_S32K_146_TCDn_CSR;


/**
* \brief  TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled) (TCD0_BITER_ELINKNO - TCD15_BITER_ELINKNO)
If the TCDn_BITER[ELINK] bit is cleared, the TCDn_BITER register is defined as follows.
*/

typedef struct tsCddDma_S32K_146_TCDn_BITER_ELINKNO
{
  uint16 u15BITER     : 15;
  uint16 u1ELINK      : 1;
}tsCddDma_S32K_146_TCDn_BITER_ELINKNO;

typedef union tuCddDma_S32K_146_TCDn_BITER_ELINKNO
{
  tsCddDma_S32K_146_TCDn_BITER_ELINKNO    sBit;
  uint16                                  unData;
}tuCddDma_S32K_146_TCDn_BITER_ELINKNO;


/**
* \brief  TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled) (TCD0_BITER_ELINKYES - TCD15_BITER_ELINKYES)
If the TCDn_BITER[ELINK] bit is set, the TCDn_BITER register is defined as follows.
*/
typedef struct tsCddDma_S32K_146_TCDn_BITER_ELINKYES
{
  uint16 u9BITER    : 9;
  uint16 u4LINKCH   : 4;
  uint16 Reserved   : 2;
  uint16 u1ELINK    : 1;
}tsCddDma_S32K_146_TCDn_BITER_ELINKYES;

typedef union tuCddDma_S32K_146_TCDn_BITER_ELINKYES
{
  tsCddDma_S32K_146_TCDn_BITER_ELINKYES    sBit;
  uint16                                   unData;
}tuCddDma_S32K_146_TCDn_BITER_ELINKYES;


typedef union tuCddDma_S32K_146_TCDn_BITER
{
  tuCddDma_S32K_146_TCDn_BITER_ELINKNO     tuELINKNO;
  tuCddDma_S32K_146_TCDn_BITER_ELINKYES    tuELINKYES;

}tuCddDma_S32K_146_TCDn_BITER;


typedef struct tsCddDma_TCDn
{
  tuCddDma_S32K_146_TCDn_SADDR        tuTCDn_SADDR;       //TCD Source Address, array offset: 0x1000, array step: 0x20
  tuCddDma_S32K_146_TCDn_SOFF         tuTCDn_SOFF;        //TCD Signed Source Address Offset, array offset: 0x1004, array step: 0x20
  tuCddDma_S32K_146_TCDn_ATTR         tuTCDn_ATTR;        //TCD Transfer Attributes, array offset: 0x1006, array step: 0x20
  tuCddDma_S32K_146_TCDn_NBYTES       tuTCDn_NBYTES;      //TCD Minor Byte Count/TCD Signed Minor Loop Offset, offset: 0x1008, array step: 0x20 
  tuCddDma_S32K_146_TCDn_SLAST        tuTCDn_SLAST;       //TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20
  tuCddDma_S32K_146_TCDn_DADDR        tuTCDn_DADDR;       //TCD Destination Address, array offset: 0x1010, array step: 0x20
  tuCddDma_S32K_146_TCDn_DOFF         tuTCDn_DOFF;        //TCD Signed Destination Address Offset, array offset: 0x1014, array step: 0x20
  tuCddDma_S32K_146_TCDn_CITER        tuTCDn_CITER;       //TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled/Enabled) offset: 0x1016, array step: 0x20
  tuCddDma_S32K_146_TCDn_DLASTSGA     tuTCDn_DLASTSGA;    //TCD Last Destination Address Adjustment/Scatter Gather Address, array offset: 0x1018, array step: 0x20
  tuCddDma_S32K_146_TCDn_CSR          tuTCDn_CSR;         //TCD Control and Status, array offset: 0x101C, array step: 0x20
  tuCddDma_S32K_146_TCDn_BITER        tuTCDn_BITER;       //TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled/Enabled) offset: 0x101E, array step: 0x20
}tsCddDma_TCDn;


typedef struct tsCddDma_S32K_146_Registers
{
  tuCddDma_S32K_146_CR                Reg_CR;             //Control Register, offset: 0x0
  tuCddDma_S32K_146_ES                Reg_ES;             //Error Status Register, offset: 0x4
  uint8                               Reserved_0[4];
  tuCddDma_S32K_146_ERQ               Reg_ERQ;            //Enable Request Register, offset: 0xC
  uint8                               Reserved_1[4];
  tuCddDma_S32K_146_EEI               Reg_EEI;            //Enable Error Interrupt Register, offset: 0x14
  tuCddDma_S32K_146_CEEI              Reg_CEEI;           //Clear Enable Error Interrupt Register, offset: 0x18
  tuCddDma_S32K_146_SEEI              Reg_SEEI;           //Set Enable Error Interrupt Register, offset: 0x19
  tuCddDma_S32K_146_CERQ              Reg_CERQ;           //Clear Enable Request Register, offset: 0x1A
  tuCddDma_S32K_146_SERQ              Reg_SERQ;           //Set Enable Request Register, offset: 0x1B
  tuCddDma_S32K_146_CDNE              Reg_CDNE;           //Clear DONE Status Bit Register, offset: 0x1C
  tuCddDma_S32K_146_SSRT              Reg_SSRT;           //Set START Bit Register, offset: 0x1D
  tuCddDma_S32K_146_CERR              Reg_CERR;           //Clear Error Register, offset: 0x1E
  tuCddDma_S32K_146_CINT              Reg_CINT;           //Clear Interrupt Request Register, offset: 0x1F
  uint8                               Reserved_2[4];
  tuCddDma_S32K_146_INT               Reg_INT;            //Interrupt Request Register, offset: 0x24
  uint8                               Reserved_3[4];
  tuCddDma_S32K_146_ERR               Reg_ERR;            //Error Register, offset: 0x2C
  uint8                               Reserved_4[4];
  tuCddDma_S32K_146_HRS               Reg_HRS;            //Hardware Request Status Register, offset: 0x34
  uint8                               Reserved_5[12];
  tuCddDma_S32K_146_EARS              Reg_EARS;           //Enable Asynchronous Request in Stop Register, offset: 0x44
  uint8                               Reserved_6[184];
  tuCddDma_S32K_146_DCHPRIm           Reg_DCHPRIm[CDDDMA_DCHPRI_COUNT];   //Channel n Priority Register, array offset: 0x100, array step: 0x1     
  uint8                               Reserved_7[3824];
  tsCddDma_TCDn                       Reg_TCDn[CDDDMA_TCD_COUNT];         //offset: 0x1000, array step: 0x20
}tsCddDma_S32K_146_Registers;

/* CHCFG Bit Fields */
#define CDDDMA_DMAMUX_CHCFG_SOURCE_MASK                 0x3Fu
#define CDDDMA_DMAMUX_CHCFG_SOURCE_SHIFT                0u
#define CDDDMA_DMAMUX_CHCFG_SOURCE_WIDTH                6u
#define CDDDMA_DMAMUX_CHCFG_SOURCE(x)                   (((uint8)(((uint8)(x))<<CDDDMA_DMAMUX_CHCFG_SOURCE_SHIFT))&CDDDMA_DMAMUX_CHCFG_SOURCE_MASK)
#define CDDDMA_DMAMUX_CHCFG_TRIG_MASK                   0x40u
#define CDDDMA_DMAMUX_CHCFG_TRIG_SHIFT                  6u
#define CDDDMA_DMAMUX_CHCFG_TRIG_WIDTH                  1u
#define CDDDMA_DMAMUX_CHCFG_TRIG(x)                     (((uint8)(((uint8)(x))<<CDDDMA_DMAMUX_CHCFG_TRIG_SHIFT))&CDDDMA_DMAMUX_CHCFG_TRIG_MASK)
#define CDDDMA_DMAMUX_CHCFG_ENBL_MASK                   0x80u
#define CDDDMA_DMAMUX_CHCFG_ENBL_SHIFT                  7u
#define CDDDMA_DMAMUX_CHCFG_ENBL_WIDTH                  1u
#define CDDDMA_DMAMUX_CHCFG_ENBL(x)                     (((uint8)(((uint8)(x))<<CDDDMA_DMAMUX_CHCFG_ENBL_SHIFT))&CDDDMA_DMAMUX_CHCFG_ENBL_MASK)

typedef struct tsCddDmaMux_S32K_146_CHCFGn
{
  uint8 u6SOURCE    : 6;
  uint8 u1TRIG      : 1;
  uint8 u1ENBL      : 1;
}tsCddDmaMux_S32K_146_CHCFGn;

typedef union tuCddDmaMux_S32K_146_CHCFGn
{
  tsCddDmaMux_S32K_146_CHCFGn     sBit;
  uint8                           ucData;
}tuCddDmaMux_S32K_146_CHCFGn;

typedef struct tsCddDmaMux_S32K_146_Register
{
  tuCddDmaMux_S32K_146_CHCFGn     Reg_CHCFGn[CDDDMAMUX_CHCFG_COUNT]; //Channel Configuration register, array offset: 0x0, array step: 0x1
}tsCddDmaMux_S32K_146_Register;



#endif // CDD_DMA_S32K_14X_TYPES_2021_05_10_H_
