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
/// \file  CddUart_S32K_14X_Types.h
///
/// \brief
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_UART_S32K_14X_TYPES_2023_09_08_H
#define CDD_UART_S32K_14X_TYPES_2023_09_08_H

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>

//=============================================================================
// Preprocessor Definitions
//=============================================================================


/* VERID Bit Fields */
#define CDDUART_VERID_FEATURE_MASK                0xFFFFu
#define CDDUART_VERID_FEATURE_SHIFT               0u
#define CDDUART_VERID_FEATURE_WIDTH               16u
#define CDDUART_VERID_FEATURE(x)                  (((uint32_t)(((uint32_t)(x))<<CDDUART_VERID_FEATURE_SHIFT))&CDDUART_VERID_FEATURE_MASK)
#define CDDUART_VERID_MINOR_MASK                  0xFF0000u
#define CDDUART_VERID_MINOR_SHIFT                 16u
#define CDDUART_VERID_MINOR_WIDTH                 8u
#define CDDUART_VERID_MINOR(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_VERID_MINOR_SHIFT))&CDDUART_VERID_MINOR_MASK)
#define CDDUART_VERID_MAJOR_MASK                  0xFF000000u
#define CDDUART_VERID_MAJOR_SHIFT                 24u
#define CDDUART_VERID_MAJOR_WIDTH                 8u
#define CDDUART_VERID_MAJOR(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_VERID_MAJOR_SHIFT))&CDDUART_VERID_MAJOR_MASK)

/* PARAM Bit Fields */
#define CDDUART_PARAM_TXFIFO_MASK                 0xFFu
#define CDDUART_PARAM_TXFIFO_SHIFT                0u
#define CDDUART_PARAM_TXFIFO_WIDTH                8u
#define CDDUART_PARAM_TXFIFO(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_PARAM_TXFIFO_SHIFT))&CDDUART_PARAM_TXFIFO_MASK)
#define CDDUART_PARAM_RXFIFO_MASK                 0xFF00u
#define CDDUART_PARAM_RXFIFO_SHIFT                8u
#define CDDUART_PARAM_RXFIFO_WIDTH                8u
#define CDDUART_PARAM_RXFIFO(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_PARAM_RXFIFO_SHIFT))&CDDUART_PARAM_RXFIFO_MASK)

/* GLOBAL Bit Fields */
#define CDDUART_GLOBAL_RST_MASK                   0x2u
#define CDDUART_GLOBAL_RST_SHIFT                  1u
#define CDDUART_GLOBAL_RST_WIDTH                  1u
#define CDDUART_GLOBAL_RST(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_GLOBAL_RST_SHIFT))&CDDUART_GLOBAL_RST_MASK)

/* PINCFG Bit Fields */
#define CDDUART_PINCFG_TRGSEL_MASK                0x3u
#define CDDUART_PINCFG_TRGSEL_SHIFT               0u
#define CDDUART_PINCFG_TRGSEL_WIDTH               2u
#define CDDUART_PINCFG_TRGSEL(x)                  (((uint32_t)(((uint32_t)(x))<<CDDUART_PINCFG_TRGSEL_SHIFT))&CDDUART_PINCFG_TRGSEL_MASK)

/* BAUD Bit Fields */
#define CDDUART_BAUD_SBR_MASK                     0x1FFFu
#define CDDUART_BAUD_SBR_SHIFT                    0u
#define CDDUART_BAUD_SBR_WIDTH                    13u
#define CDDUART_BAUD_SBR(x)                       (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_SBR_SHIFT))&CDDUART_BAUD_SBR_MASK)
#define CDDUART_BAUD_SBNS_MASK                    0x2000u
#define CDDUART_BAUD_SBNS_SHIFT                   13u
#define CDDUART_BAUD_SBNS_WIDTH                   1u
#define CDDUART_BAUD_SBNS(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_SBNS_SHIFT))&CDDUART_BAUD_SBNS_MASK)
#define CDDUART_BAUD_RXEDGIE_MASK                 0x4000u
#define CDDUART_BAUD_RXEDGIE_SHIFT                14u
#define CDDUART_BAUD_RXEDGIE_WIDTH                1u
#define CDDUART_BAUD_RXEDGIE(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_RXEDGIE_SHIFT))&CDDUART_BAUD_RXEDGIE_MASK)
#define CDDUART_BAUD_LBKDIE_MASK                  0x8000u
#define CDDUART_BAUD_LBKDIE_SHIFT                 15u
#define CDDUART_BAUD_LBKDIE_WIDTH                 1u
#define CDDUART_BAUD_LBKDIE(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_LBKDIE_SHIFT))&CDDUART_BAUD_LBKDIE_MASK)
#define CDDUART_BAUD_RESYNCDIS_MASK               0x10000u
#define CDDUART_BAUD_RESYNCDIS_SHIFT              16u
#define CDDUART_BAUD_RESYNCDIS_WIDTH              1u
#define CDDUART_BAUD_RESYNCDIS(x)                 (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_RESYNCDIS_SHIFT))&CDDUART_BAUD_RESYNCDIS_MASK)
#define CDDUART_BAUD_BOTHEDGE_MASK                0x20000u
#define CDDUART_BAUD_BOTHEDGE_SHIFT               17u
#define CDDUART_BAUD_BOTHEDGE_WIDTH               1u
#define CDDUART_BAUD_BOTHEDGE(x)                  (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_BOTHEDGE_SHIFT))&CDDUART_BAUD_BOTHEDGE_MASK)
#define CDDUART_BAUD_MATCFG_MASK                  0xC0000u
#define CDDUART_BAUD_MATCFG_SHIFT                 18u
#define CDDUART_BAUD_MATCFG_WIDTH                 2u
#define CDDUART_BAUD_MATCFG(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_MATCFG_SHIFT))&CDDUART_BAUD_MATCFG_MASK)
#define CDDUART_BAUD_RIDMAE_MASK                  0x100000u
#define CDDUART_BAUD_RIDMAE_SHIFT                 20u
#define CDDUART_BAUD_RIDMAE_WIDTH                 1u
#define CDDUART_BAUD_RIDMAE(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_RIDMAE_SHIFT))&CDDUART_BAUD_RIDMAE_MASK)
#define CDDUART_BAUD_RDMAE_MASK                   0x200000u
#define CDDUART_BAUD_RDMAE_SHIFT                  21u
#define CDDUART_BAUD_RDMAE_WIDTH                  1u
#define CDDUART_BAUD_RDMAE(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_RDMAE_SHIFT))&CDDUART_BAUD_RDMAE_MASK)
#define CDDUART_BAUD_TDMAE_MASK                   0x800000u
#define CDDUART_BAUD_TDMAE_SHIFT                  23u
#define CDDUART_BAUD_TDMAE_WIDTH                  1u
#define CDDUART_BAUD_TDMAE(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_TDMAE_SHIFT))&CDDUART_BAUD_TDMAE_MASK)
#define CDDUART_BAUD_OSR_MASK                     0x1F000000u
#define CDDUART_BAUD_OSR_SHIFT                    24u
#define CDDUART_BAUD_OSR_WIDTH                    5u
#define CDDUART_BAUD_OSR(x)                       (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_OSR_SHIFT))&CDDUART_BAUD_OSR_MASK)
#define CDDUART_BAUD_M10_MASK                     0x20000000u
#define CDDUART_BAUD_M10_SHIFT                    29u
#define CDDUART_BAUD_M10_WIDTH                    1u
#define CDDUART_BAUD_M10(x)                       (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_M10_SHIFT))&CDDUART_BAUD_M10_MASK)
#define CDDUART_BAUD_MAEN2_MASK                   0x40000000u
#define CDDUART_BAUD_MAEN2_SHIFT                  30u
#define CDDUART_BAUD_MAEN2_WIDTH                  1u
#define CDDUART_BAUD_MAEN2(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_MAEN2_SHIFT))&CDDUART_BAUD_MAEN2_MASK)
#define CDDUART_BAUD_MAEN1_MASK                   0x80000000u
#define CDDUART_BAUD_MAEN1_SHIFT                  31u
#define CDDUART_BAUD_MAEN1_WIDTH                  1u
#define CDDUART_BAUD_MAEN1(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_BAUD_MAEN1_SHIFT))&CDDUART_BAUD_MAEN1_MASK)

/* STAT Bit Fields */
#define CDDUART_STAT_MA2F_MASK                    0x4000u
#define CDDUART_STAT_MA2F_SHIFT                   14u
#define CDDUART_STAT_MA2F_WIDTH                   1u
#define CDDUART_STAT_MA2F(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_MA2F_SHIFT))&CDDUART_STAT_MA2F_MASK)
#define CDDUART_STAT_MA1F_MASK                    0x8000u
#define CDDUART_STAT_MA1F_SHIFT                   15u
#define CDDUART_STAT_MA1F_WIDTH                   1u
#define CDDUART_STAT_MA1F(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_MA1F_SHIFT))&CDDUART_STAT_MA1F_MASK)
#define CDDUART_STAT_PF_MASK                      0x10000u
#define CDDUART_STAT_PF_SHIFT                     16u
#define CDDUART_STAT_PF_WIDTH                     1u
#define CDDUART_STAT_PF(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_PF_SHIFT))&CDDUART_STAT_PF_MASK)
#define CDDUART_STAT_FE_MASK                      0x20000u
#define CDDUART_STAT_FE_SHIFT                     17u
#define CDDUART_STAT_FE_WIDTH                     1u
#define CDDUART_STAT_FE(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_FE_SHIFT))&CDDUART_STAT_FE_MASK)
#define CDDUART_STAT_NF_MASK                      0x40000u
#define CDDUART_STAT_NF_SHIFT                     18u
#define CDDUART_STAT_NF_WIDTH                     1u
#define CDDUART_STAT_NF(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_NF_SHIFT))&CDDUART_STAT_NF_MASK)
#define CDDUART_STAT_OR_MASK                      0x80000u
#define CDDUART_STAT_OR_SHIFT                     19u
#define CDDUART_STAT_OR_WIDTH                     1u
#define CDDUART_STAT_OR(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_OR_SHIFT))&CDDUART_STAT_OR_MASK)
#define CDDUART_STAT_IDLE_MASK                    0x100000u
#define CDDUART_STAT_IDLE_SHIFT                   20u
#define CDDUART_STAT_IDLE_WIDTH                   1u
#define CDDUART_STAT_IDLE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_IDLE_SHIFT))&CDDUART_STAT_IDLE_MASK)
#define CDDUART_STAT_RDRF_MASK                    0x200000u
#define CDDUART_STAT_RDRF_SHIFT                   21u
#define CDDUART_STAT_RDRF_WIDTH                   1u
#define CDDUART_STAT_RDRF(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_RDRF_SHIFT))&CDDUART_STAT_RDRF_MASK)
#define CDDUART_STAT_TC_MASK                      0x400000u
#define CDDUART_STAT_TC_SHIFT                     22u
#define CDDUART_STAT_TC_WIDTH                     1u
#define CDDUART_STAT_TC(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_TC_SHIFT))&CDDUART_STAT_TC_MASK)
#define CDDUART_STAT_TDRE_MASK                    0x800000u
#define CDDUART_STAT_TDRE_SHIFT                   23u
#define CDDUART_STAT_TDRE_WIDTH                   1u
#define CDDUART_STAT_TDRE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_TDRE_SHIFT))&CDDUART_STAT_TDRE_MASK)
#define CDDUART_STAT_RAF_MASK                     0x1000000u
#define CDDUART_STAT_RAF_SHIFT                    24u
#define CDDUART_STAT_RAF_WIDTH                    1u
#define CDDUART_STAT_RAF(x)                       (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_RAF_SHIFT))&CDDUART_STAT_RAF_MASK)
#define CDDUART_STAT_LBKDE_MASK                   0x2000000u
#define CDDUART_STAT_LBKDE_SHIFT                  25u
#define CDDUART_STAT_LBKDE_WIDTH                  1u
#define CDDUART_STAT_LBKDE(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_LBKDE_SHIFT))&CDDUART_STAT_LBKDE_MASK)
#define CDDUART_STAT_BRK13_MASK                   0x4000000u
#define CDDUART_STAT_BRK13_SHIFT                  26u
#define CDDUART_STAT_BRK13_WIDTH                  1u
#define CDDUART_STAT_BRK13(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_BRK13_SHIFT))&CDDUART_STAT_BRK13_MASK)
#define CDDUART_STAT_RWUID_MASK                   0x8000000u
#define CDDUART_STAT_RWUID_SHIFT                  27u
#define CDDUART_STAT_RWUID_WIDTH                  1u
#define CDDUART_STAT_RWUID(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_RWUID_SHIFT))&CDDUART_STAT_RWUID_MASK)
#define CDDUART_STAT_RXINV_MASK                   0x10000000u
#define CDDUART_STAT_RXINV_SHIFT                  28u
#define CDDUART_STAT_RXINV_WIDTH                  1u
#define CDDUART_STAT_RXINV(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_RXINV_SHIFT))&CDDUART_STAT_RXINV_MASK)
#define CDDUART_STAT_MSBF_MASK                    0x20000000u
#define CDDUART_STAT_MSBF_SHIFT                   29u
#define CDDUART_STAT_MSBF_WIDTH                   1u
#define CDDUART_STAT_MSBF(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_MSBF_SHIFT))&CDDUART_STAT_MSBF_MASK)
#define CDDUART_STAT_RXEDGIF_MASK                 0x40000000u
#define CDDUART_STAT_RXEDGIF_SHIFT                30u
#define CDDUART_STAT_RXEDGIF_WIDTH                1u
#define CDDUART_STAT_RXEDGIF(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_RXEDGIF_SHIFT))&CDDUART_STAT_RXEDGIF_MASK)
#define CDDUART_STAT_LBKDIF_MASK                  0x80000000u
#define CDDUART_STAT_LBKDIF_SHIFT                 31u
#define CDDUART_STAT_LBKDIF_WIDTH                 1u
#define CDDUART_STAT_LBKDIF(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_STAT_LBKDIF_SHIFT))&CDDUART_STAT_LBKDIF_MASK)

/* CTRL Bit Fields */
#define CDDUART_CTRL_PT_MASK                      0x1u
#define CDDUART_CTRL_PT_SHIFT                     0u
#define CDDUART_CTRL_PT_WIDTH                     1u
#define CDDUART_CTRL_PT(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_PT_SHIFT))&CDDUART_CTRL_PT_MASK)
#define CDDUART_CTRL_PE_MASK                      0x2u
#define CDDUART_CTRL_PE_SHIFT                     1u
#define CDDUART_CTRL_PE_WIDTH                     1u
#define CDDUART_CTRL_PE(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_PE_SHIFT))&CDDUART_CTRL_PE_MASK)
#define CDDUART_CTRL_ILT_MASK                     0x4u
#define CDDUART_CTRL_ILT_SHIFT                    2u
#define CDDUART_CTRL_ILT_WIDTH                    1u
#define CDDUART_CTRL_ILT(x)                       (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_ILT_SHIFT))&CDDUART_CTRL_ILT_MASK)
#define CDDUART_CTRL_WAKE_MASK                    0x8u
#define CDDUART_CTRL_WAKE_SHIFT                   3u
#define CDDUART_CTRL_WAKE_WIDTH                   1u
#define CDDUART_CTRL_WAKE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_WAKE_SHIFT))&CDDUART_CTRL_WAKE_MASK)
#define CDDUART_CTRL_M_MASK                       0x10u
#define CDDUART_CTRL_M_SHIFT                      4u
#define CDDUART_CTRL_M_WIDTH                      1u
#define CDDUART_CTRL_M(x)                         (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_M_SHIFT))&CDDUART_CTRL_M_MASK)
#define CDDUART_CTRL_RSRC_MASK                    0x20u
#define CDDUART_CTRL_RSRC_SHIFT                   5u
#define CDDUART_CTRL_RSRC_WIDTH                   1u
#define CDDUART_CTRL_RSRC(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_RSRC_SHIFT))&CDDUART_CTRL_RSRC_MASK)
#define CDDUART_CTRL_DOZEEN_MASK                  0x40u
#define CDDUART_CTRL_DOZEEN_SHIFT                 6u
#define CDDUART_CTRL_DOZEEN_WIDTH                 1u
#define CDDUART_CTRL_DOZEEN(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_DOZEEN_SHIFT))&CDDUART_CTRL_DOZEEN_MASK)
#define CDDUART_CTRL_LOOPS_MASK                   0x80u
#define CDDUART_CTRL_LOOPS_SHIFT                  7u
#define CDDUART_CTRL_LOOPS_WIDTH                  1u
#define CDDUART_CTRL_LOOPS(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_LOOPS_SHIFT))&CDDUART_CTRL_LOOPS_MASK)
#define CDDUART_CTRL_IDLECFG_MASK                 0x700u
#define CDDUART_CTRL_IDLECFG_SHIFT                8u
#define CDDUART_CTRL_IDLECFG_WIDTH                3u
#define CDDUART_CTRL_IDLECFG(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_IDLECFG_SHIFT))&CDDUART_CTRL_IDLECFG_MASK)
#define CDDUART_CTRL_M7_MASK                      0x800u
#define CDDUART_CTRL_M7_SHIFT                     11u
#define CDDUART_CTRL_M7_WIDTH                     1u
#define CDDUART_CTRL_M7(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_M7_SHIFT))&CDDUART_CTRL_M7_MASK)
#define CDDUART_CTRL_MA2IE_MASK                   0x4000u
#define CDDUART_CTRL_MA2IE_SHIFT                  14u
#define CDDUART_CTRL_MA2IE_WIDTH                  1u
#define CDDUART_CTRL_MA2IE(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_MA2IE_SHIFT))&CDDUART_CTRL_MA2IE_MASK)
#define CDDUART_CTRL_MA1IE_MASK                   0x8000u
#define CDDUART_CTRL_MA1IE_SHIFT                  15u
#define CDDUART_CTRL_MA1IE_WIDTH                  1u
#define CDDUART_CTRL_MA1IE(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_MA1IE_SHIFT))&CDDUART_CTRL_MA1IE_MASK)
#define CDDUART_CTRL_SBK_MASK                     0x10000u
#define CDDUART_CTRL_SBK_SHIFT                    16u
#define CDDUART_CTRL_SBK_WIDTH                    1u
#define CDDUART_CTRL_SBK(x)                       (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_SBK_SHIFT))&CDDUART_CTRL_SBK_MASK)
#define CDDUART_CTRL_RWU_MASK                     0x20000u
#define CDDUART_CTRL_RWU_SHIFT                    17u
#define CDDUART_CTRL_RWU_WIDTH                    1u
#define CDDUART_CTRL_RWU(x)                       (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_RWU_SHIFT))&CDDUART_CTRL_RWU_MASK)
#define CDDUART_CTRL_RE_MASK                      0x40000u
#define CDDUART_CTRL_RE_SHIFT                     18u
#define CDDUART_CTRL_RE_WIDTH                     1u
#define CDDUART_CTRL_RE(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_RE_SHIFT))&CDDUART_CTRL_RE_MASK)
#define CDDUART_CTRL_TE_MASK                      0x80000u
#define CDDUART_CTRL_TE_SHIFT                     19u
#define CDDUART_CTRL_TE_WIDTH                     1u
#define CDDUART_CTRL_TE(x)                        (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_TE_SHIFT))&CDDUART_CTRL_TE_MASK)
#define CDDUART_CTRL_ILIE_MASK                    0x100000u
#define CDDUART_CTRL_ILIE_SHIFT                   20u
#define CDDUART_CTRL_ILIE_WIDTH                   1u
#define CDDUART_CTRL_ILIE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_ILIE_SHIFT))&CDDUART_CTRL_ILIE_MASK)
#define CDDUART_CTRL_RIE_MASK                     0x200000u
#define CDDUART_CTRL_RIE_SHIFT                    21u
#define CDDUART_CTRL_RIE_WIDTH                    1u
#define CDDUART_CTRL_RIE(x)                       (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_RIE_SHIFT))&CDDUART_CTRL_RIE_MASK)
#define CDDUART_CTRL_TCIE_MASK                    0x400000u
#define CDDUART_CTRL_TCIE_SHIFT                   22u
#define CDDUART_CTRL_TCIE_WIDTH                   1u
#define CDDUART_CTRL_TCIE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_TCIE_SHIFT))&CDDUART_CTRL_TCIE_MASK)
#define CDDUART_CTRL_TIE_MASK                     0x800000u
#define CDDUART_CTRL_TIE_SHIFT                    23u
#define CDDUART_CTRL_TIE_WIDTH                    1u
#define CDDUART_CTRL_TIE(x)                       (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_TIE_SHIFT))&CDDUART_CTRL_TIE_MASK)
#define CDDUART_CTRL_PEIE_MASK                    0x1000000u
#define CDDUART_CTRL_PEIE_SHIFT                   24u
#define CDDUART_CTRL_PEIE_WIDTH                   1u
#define CDDUART_CTRL_PEIE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_PEIE_SHIFT))&CDDUART_CTRL_PEIE_MASK)
#define CDDUART_CTRL_FEIE_MASK                    0x2000000u
#define CDDUART_CTRL_FEIE_SHIFT                   25u
#define CDDUART_CTRL_FEIE_WIDTH                   1u
#define CDDUART_CTRL_FEIE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_FEIE_SHIFT))&CDDUART_CTRL_FEIE_MASK)
#define CDDUART_CTRL_NEIE_MASK                    0x4000000u
#define CDDUART_CTRL_NEIE_SHIFT                   26u
#define CDDUART_CTRL_NEIE_WIDTH                   1u
#define CDDUART_CTRL_NEIE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_NEIE_SHIFT))&CDDUART_CTRL_NEIE_MASK)
#define CDDUART_CTRL_ORIE_MASK                    0x8000000u
#define CDDUART_CTRL_ORIE_SHIFT                   27u
#define CDDUART_CTRL_ORIE_WIDTH                   1u
#define CDDUART_CTRL_ORIE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_ORIE_SHIFT))&CDDUART_CTRL_ORIE_MASK)
#define CDDUART_CTRL_TXINV_MASK                   0x10000000u
#define CDDUART_CTRL_TXINV_SHIFT                  28u
#define CDDUART_CTRL_TXINV_WIDTH                  1u
#define CDDUART_CTRL_TXINV(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_TXINV_SHIFT))&CDDUART_CTRL_TXINV_MASK)
#define CDDUART_CTRL_TXDIR_MASK                   0x20000000u
#define CDDUART_CTRL_TXDIR_SHIFT                  29u
#define CDDUART_CTRL_TXDIR_WIDTH                  1u
#define CDDUART_CTRL_TXDIR(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_TXDIR_SHIFT))&CDDUART_CTRL_TXDIR_MASK)
#define CDDUART_CTRL_R9T8_MASK                    0x40000000u
#define CDDUART_CTRL_R9T8_SHIFT                   30u
#define CDDUART_CTRL_R9T8_WIDTH                   1u
#define CDDUART_CTRL_R9T8(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_R9T8_SHIFT))&CDDUART_CTRL_R9T8_MASK)
#define CDDUART_CTRL_R8T9_MASK                    0x80000000u
#define CDDUART_CTRL_R8T9_SHIFT                   31u
#define CDDUART_CTRL_R8T9_WIDTH                   1u
#define CDDUART_CTRL_R8T9(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_CTRL_R8T9_SHIFT))&CDDUART_CTRL_R8T9_MASK)

/* DATA Bit Fields */
#define CDDUART_DATA_R0T0_MASK                    0x1u
#define CDDUART_DATA_R0T0_SHIFT                   0u
#define CDDUART_DATA_R0T0_WIDTH                   1u
#define CDDUART_DATA_R0T0(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R0T0_SHIFT))&CDDUART_DATA_R0T0_MASK)
#define CDDUART_DATA_R1T1_MASK                    0x2u
#define CDDUART_DATA_R1T1_SHIFT                   1u
#define CDDUART_DATA_R1T1_WIDTH                   1u
#define CDDUART_DATA_R1T1(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R1T1_SHIFT))&CDDUART_DATA_R1T1_MASK)
#define CDDUART_DATA_R2T2_MASK                    0x4u
#define CDDUART_DATA_R2T2_SHIFT                   2u
#define CDDUART_DATA_R2T2_WIDTH                   1u
#define CDDUART_DATA_R2T2(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R2T2_SHIFT))&CDDUART_DATA_R2T2_MASK)
#define CDDUART_DATA_R3T3_MASK                    0x8u
#define CDDUART_DATA_R3T3_SHIFT                   3u
#define CDDUART_DATA_R3T3_WIDTH                   1u
#define CDDUART_DATA_R3T3(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R3T3_SHIFT))&CDDUART_DATA_R3T3_MASK)
#define CDDUART_DATA_R4T4_MASK                    0x10u
#define CDDUART_DATA_R4T4_SHIFT                   4u
#define CDDUART_DATA_R4T4_WIDTH                   1u
#define CDDUART_DATA_R4T4(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R4T4_SHIFT))&CDDUART_DATA_R4T4_MASK)
#define CDDUART_DATA_R5T5_MASK                    0x20u
#define CDDUART_DATA_R5T5_SHIFT                   5u
#define CDDUART_DATA_R5T5_WIDTH                   1u
#define CDDUART_DATA_R5T5(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R5T5_SHIFT))&CDDUART_DATA_R5T5_MASK)
#define CDDUART_DATA_R6T6_MASK                    0x40u
#define CDDUART_DATA_R6T6_SHIFT                   6u
#define CDDUART_DATA_R6T6_WIDTH                   1u
#define CDDUART_DATA_R6T6(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R6T6_SHIFT))&CDDUART_DATA_R6T6_MASK)
#define CDDUART_DATA_R7T7_MASK                    0x80u
#define CDDUART_DATA_R7T7_SHIFT                   7u
#define CDDUART_DATA_R7T7_WIDTH                   1u
#define CDDUART_DATA_R7T7(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R7T7_SHIFT))&CDDUART_DATA_R7T7_MASK)
#define CDDUART_DATA_R8T8_MASK                    0x100u
#define CDDUART_DATA_R8T8_SHIFT                   8u
#define CDDUART_DATA_R8T8_WIDTH                   1u
#define CDDUART_DATA_R8T8(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R8T8_SHIFT))&CDDUART_DATA_R8T8_MASK)
#define CDDUART_DATA_R9T9_MASK                    0x200u
#define CDDUART_DATA_R9T9_SHIFT                   9u
#define CDDUART_DATA_R9T9_WIDTH                   1u
#define CDDUART_DATA_R9T9(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_R9T9_SHIFT))&CDDUART_DATA_R9T9_MASK)
#define CDDUART_DATA_IDLINE_MASK                  0x800u
#define CDDUART_DATA_IDLINE_SHIFT                 11u
#define CDDUART_DATA_IDLINE_WIDTH                 1u
#define CDDUART_DATA_IDLINE(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_IDLINE_SHIFT))&CDDUART_DATA_IDLINE_MASK)
#define CDDUART_DATA_RXEMPT_MASK                  0x1000u
#define CDDUART_DATA_RXEMPT_SHIFT                 12u
#define CDDUART_DATA_RXEMPT_WIDTH                 1u
#define CDDUART_DATA_RXEMPT(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_RXEMPT_SHIFT))&CDDUART_DATA_RXEMPT_MASK)
#define CDDUART_DATA_FRETSC_MASK                  0x2000u
#define CDDUART_DATA_FRETSC_SHIFT                 13u
#define CDDUART_DATA_FRETSC_WIDTH                 1u
#define CDDUART_DATA_FRETSC(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_FRETSC_SHIFT))&CDDUART_DATA_FRETSC_MASK)
#define CDDUART_DATA_PARITYE_MASK                 0x4000u
#define CDDUART_DATA_PARITYE_SHIFT                14u
#define CDDUART_DATA_PARITYE_WIDTH                1u
#define CDDUART_DATA_PARITYE(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_PARITYE_SHIFT))&CDDUART_DATA_PARITYE_MASK)
#define CDDUART_DATA_NOISY_MASK                   0x8000u
#define CDDUART_DATA_NOISY_SHIFT                  15u
#define CDDUART_DATA_NOISY_WIDTH                  1u
#define CDDUART_DATA_NOISY(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_DATA_NOISY_SHIFT))&CDDUART_DATA_NOISY_MASK)

/* MATCH Bit Fields */
#define CDDUART_MATCH_MA1_MASK                    0x3FFu
#define CDDUART_MATCH_MA1_SHIFT                   0u
#define CDDUART_MATCH_MA1_WIDTH                   10u
#define CDDUART_MATCH_MA1(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_MATCH_MA1_SHIFT))&CDDUART_MATCH_MA1_MASK)
#define CDDUART_MATCH_MA2_MASK                    0x3FF0000u
#define CDDUART_MATCH_MA2_SHIFT                   16u
#define CDDUART_MATCH_MA2_WIDTH                   10u
#define CDDUART_MATCH_MA2(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_MATCH_MA2_SHIFT))&CDDUART_MATCH_MA2_MASK)

/* MODIR Bit Fields */
#define CDDUART_MODIR_TXCTSE_MASK                 0x1u
#define CDDUART_MODIR_TXCTSE_SHIFT                0u
#define CDDUART_MODIR_TXCTSE_WIDTH                1u
#define CDDUART_MODIR_TXCTSE(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_MODIR_TXCTSE_SHIFT))&CDDUART_MODIR_TXCTSE_MASK)
#define CDDUART_MODIR_TXRTSE_MASK                 0x2u
#define CDDUART_MODIR_TXRTSE_SHIFT                1u
#define CDDUART_MODIR_TXRTSE_WIDTH                1u
#define CDDUART_MODIR_TXRTSE(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_MODIR_TXRTSE_SHIFT))&CDDUART_MODIR_TXRTSE_MASK)
#define CDDUART_MODIR_TXRTSPOL_MASK               0x4u
#define CDDUART_MODIR_TXRTSPOL_SHIFT              2u
#define CDDUART_MODIR_TXRTSPOL_WIDTH              1u
#define CDDUART_MODIR_TXRTSPOL(x)                 (((uint32_t)(((uint32_t)(x))<<CDDUART_MODIR_TXRTSPOL_SHIFT))&CDDUART_MODIR_TXRTSPOL_MASK)
#define CDDUART_MODIR_RXRTSE_MASK                 0x8u
#define CDDUART_MODIR_RXRTSE_SHIFT                3u
#define CDDUART_MODIR_RXRTSE_WIDTH                1u
#define CDDUART_MODIR_RXRTSE(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_MODIR_RXRTSE_SHIFT))&CDDUART_MODIR_RXRTSE_MASK)
#define CDDUART_MODIR_TXCTSC_MASK                 0x10u
#define CDDUART_MODIR_TXCTSC_SHIFT                4u
#define CDDUART_MODIR_TXCTSC_WIDTH                1u
#define CDDUART_MODIR_TXCTSC(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_MODIR_TXCTSC_SHIFT))&CDDUART_MODIR_TXCTSC_MASK)
#define CDDUART_MODIR_TXCTSSRC_MASK               0x20u
#define CDDUART_MODIR_TXCTSSRC_SHIFT              5u
#define CDDUART_MODIR_TXCTSSRC_WIDTH              1u
#define CDDUART_MODIR_TXCTSSRC(x)                 (((uint32_t)(((uint32_t)(x))<<CDDUART_MODIR_TXCTSSRC_SHIFT))&CDDUART_MODIR_TXCTSSRC_MASK)
#define CDDUART_MODIR_RTSWATER_MASK               0x300u
#define CDDUART_MODIR_RTSWATER_SHIFT              8u
#define CDDUART_MODIR_RTSWATER_WIDTH              2u
#define CDDUART_MODIR_RTSWATER(x)                 (((uint32_t)(((uint32_t)(x))<<CDDUART_MODIR_RTSWATER_SHIFT))&CDDUART_MODIR_RTSWATER_MASK)
#define CDDUART_MODIR_TNP_MASK                    0x30000u
#define CDDUART_MODIR_TNP_SHIFT                   16u
#define CDDUART_MODIR_TNP_WIDTH                   2u
#define CDDUART_MODIR_TNP(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_MODIR_TNP_SHIFT))&CDDUART_MODIR_TNP_MASK)
#define CDDUART_MODIR_IREN_MASK                   0x40000u
#define CDDUART_MODIR_IREN_SHIFT                  18u
#define CDDUART_MODIR_IREN_WIDTH                  1u
#define CDDUART_MODIR_IREN(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_MODIR_IREN_SHIFT))&CDDUART_MODIR_IREN_MASK)

/* FIFO Bit Fields */
#define CDDUART_FIFO_RXFIFOSIZE_MASK              0x7u
#define CDDUART_FIFO_RXFIFOSIZE_SHIFT             0u
#define CDDUART_FIFO_RXFIFOSIZE_WIDTH             3u
#define CDDUART_FIFO_RXFIFOSIZE(x)                (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_RXFIFOSIZE_SHIFT))&CDDUART_FIFO_RXFIFOSIZE_MASK)
#define CDDUART_FIFO_RXFE_MASK                    0x8u
#define CDDUART_FIFO_RXFE_SHIFT                   3u
#define CDDUART_FIFO_RXFE_WIDTH                   1u
#define CDDUART_FIFO_RXFE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_RXFE_SHIFT))&CDDUART_FIFO_RXFE_MASK)
#define CDDUART_FIFO_TXFIFOSIZE_MASK              0x70u
#define CDDUART_FIFO_TXFIFOSIZE_SHIFT             4u
#define CDDUART_FIFO_TXFIFOSIZE_WIDTH             3u
#define CDDUART_FIFO_TXFIFOSIZE(x)                (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_TXFIFOSIZE_SHIFT))&CDDUART_FIFO_TXFIFOSIZE_MASK)
#define CDDUART_FIFO_TXFE_MASK                    0x80u
#define CDDUART_FIFO_TXFE_SHIFT                   7u
#define CDDUART_FIFO_TXFE_WIDTH                   1u
#define CDDUART_FIFO_TXFE(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_TXFE_SHIFT))&CDDUART_FIFO_TXFE_MASK)
#define CDDUART_FIFO_RXUFE_MASK                   0x100u
#define CDDUART_FIFO_RXUFE_SHIFT                  8u
#define CDDUART_FIFO_RXUFE_WIDTH                  1u
#define CDDUART_FIFO_RXUFE(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_RXUFE_SHIFT))&CDDUART_FIFO_RXUFE_MASK)
#define CDDUART_FIFO_TXOFE_MASK                   0x200u
#define CDDUART_FIFO_TXOFE_SHIFT                  9u
#define CDDUART_FIFO_TXOFE_WIDTH                  1u
#define CDDUART_FIFO_TXOFE(x)                     (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_TXOFE_SHIFT))&CDDUART_FIFO_TXOFE_MASK)
#define CDDUART_FIFO_RXIDEN_MASK                  0x1C00u
#define CDDUART_FIFO_RXIDEN_SHIFT                 10u
#define CDDUART_FIFO_RXIDEN_WIDTH                 3u
#define CDDUART_FIFO_RXIDEN(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_RXIDEN_SHIFT))&CDDUART_FIFO_RXIDEN_MASK)
#define CDDUART_FIFO_RXFLUSH_MASK                 0x4000u
#define CDDUART_FIFO_RXFLUSH_SHIFT                14u
#define CDDUART_FIFO_RXFLUSH_WIDTH                1u
#define CDDUART_FIFO_RXFLUSH(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_RXFLUSH_SHIFT))&CDDUART_FIFO_RXFLUSH_MASK)
#define CDDUART_FIFO_TXFLUSH_MASK                 0x8000u
#define CDDUART_FIFO_TXFLUSH_SHIFT                15u
#define CDDUART_FIFO_TXFLUSH_WIDTH                1u
#define CDDUART_FIFO_TXFLUSH(x)                   (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_TXFLUSH_SHIFT))&CDDUART_FIFO_TXFLUSH_MASK)
#define CDDUART_FIFO_RXUF_MASK                    0x10000u
#define CDDUART_FIFO_RXUF_SHIFT                   16u
#define CDDUART_FIFO_RXUF_WIDTH                   1u
#define CDDUART_FIFO_RXUF(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_RXUF_SHIFT))&CDDUART_FIFO_RXUF_MASK)
#define CDDUART_FIFO_TXOF_MASK                    0x20000u
#define CDDUART_FIFO_TXOF_SHIFT                   17u
#define CDDUART_FIFO_TXOF_WIDTH                   1u
#define CDDUART_FIFO_TXOF(x)                      (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_TXOF_SHIFT))&CDDUART_FIFO_TXOF_MASK)
#define CDDUART_FIFO_RXEMPT_MASK                  0x400000u
#define CDDUART_FIFO_RXEMPT_SHIFT                 22u
#define CDDUART_FIFO_RXEMPT_WIDTH                 1u
#define CDDUART_FIFO_RXEMPT(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_RXEMPT_SHIFT))&CDDUART_FIFO_RXEMPT_MASK)
#define CDDUART_FIFO_TXEMPT_MASK                  0x800000u
#define CDDUART_FIFO_TXEMPT_SHIFT                 23u
#define CDDUART_FIFO_TXEMPT_WIDTH                 1u
#define CDDUART_FIFO_TXEMPT(x)                    (((uint32_t)(((uint32_t)(x))<<CDDUART_FIFO_TXEMPT_SHIFT))&CDDUART_FIFO_TXEMPT_MASK)

/* WATER Bit Fields */
#define CDDUART_WATER_TXWATER_MASK                0x3u
#define CDDUART_WATER_TXWATER_SHIFT               0u
#define CDDUART_WATER_TXWATER_WIDTH               2u
#define CDDUART_WATER_TXWATER(x)                  (((uint32_t)(((uint32_t)(x))<<CDDUART_WATER_TXWATER_SHIFT))&CDDUART_WATER_TXWATER_MASK)
#define CDDUART_WATER_TXCOUNT_MASK                0x700u
#define CDDUART_WATER_TXCOUNT_SHIFT               8u
#define CDDUART_WATER_TXCOUNT_WIDTH               3u
#define CDDUART_WATER_TXCOUNT(x)                  (((uint32_t)(((uint32_t)(x))<<CDDUART_WATER_TXCOUNT_SHIFT))&CDDUART_WATER_TXCOUNT_MASK)
#define CDDUART_WATER_RXWATER_MASK                0x30000u
#define CDDUART_WATER_RXWATER_SHIFT               16u
#define CDDUART_WATER_RXWATER_WIDTH               2u
#define CDDUART_WATER_RXWATER(x)                  (((uint32_t)(((uint32_t)(x))<<CDDUART_WATER_RXWATER_SHIFT))&CDDUART_WATER_RXWATER_MASK)
#define CDDUART_WATER_RXCOUNT_MASK                0x7000000u
#define CDDUART_WATER_RXCOUNT_SHIFT               24u
#define CDDUART_WATER_RXCOUNT_WIDTH               3u
#define CDDUART_WATER_RXCOUNT(x)                  (((uint32_t)(((uint32_t)(x))<<CDDUART_WATER_RXCOUNT_SHIFT))&CDDUART_WATER_RXCOUNT_MASK)

#define CDDUART_STAT_ERROR_FLAGS_MASK             0xC01FC000U
#define CDDUART_CLEAR_ERROR_FLAGS                 0xF0000


//=============================================================================
// Types Definitions
//=============================================================================

// Version ID Register
typedef struct tsCddMlcUart_NXP_VERID
{
  uint32 u16FEATURE   : 16;
  uint32 u8MINOR      : 8;
  uint32 u8MAJOR      : 8;
}tsCddMlcUart_NXP_VERID;

typedef union tuCddMlcUart_NXP_VERID
{
  tsCddMlcUart_NXP_VERID    sBit;
  uint32                    u32Register;
}tuCddMlcUart_NXP_VERID;


// Parameter Register
typedef struct tsCddMlcUart_NXP_PARAM
{
  uint32 u8TXFIFO : 8;
  uint32 u8RXFIFO : 8;
  uint32 Reserved : 16;

}tsCddMlcUart_NXP_PARAM;

typedef union tuCddMlcUart_NXP_PARAM
{
  tsCddMlcUart_NXP_PARAM    sBit;
  uint32                    u32Register;
}tuCddMlcUart_NXP_PARAM;


//LPUART Global Register
typedef struct tsCddMlcUart_NXP_GLOBAL
{
  uint32 Reserved1 : 1;
  uint32 u1RST     : 1;
  uint32 Reserved2 : 30;

}tsCddMlcUart_NXP_GLOBAL;

typedef union tuCddMlcUart_NXP_GLOBAL
{
  tsCddMlcUart_NXP_GLOBAL   sBit;
  uint32                    u32Register;
}tuCddMlcUart_NXP_GLOBAL;


//LPUART Pin Configuration Register
typedef struct tsCddMlcUart_NXP_PINCFG
{
  uint32 u2TRGSEL   : 2;
  uint32 Reserved   : 30;
}tsCddMlcUart_NXP_PINCFG;

typedef union tuCddMlcUart_NXP_PINCFG
{
  tsCddMlcUart_NXP_PINCFG   sBit;
  uint32                    u32Register;
}tuCddMlcUart_NXP_PINCFG;


//LPUART Baud Rate Register
typedef struct tsCddMlcUart_NXP_BAUD
{
  uint32 u13SBR       : 13;
  uint32 u1SBNS       : 1;
  uint32 u1RXEDGIE    : 1;
  uint32 u1LBKDIE     : 1;
  uint32 u1RESYNCDIS  : 1;
  uint32 u1BOTHEDGE   : 1;
  uint32 u2MATCFG     : 2;
  uint32 u1RIDMAE     : 1;
  uint32 u1RDMAE      : 1;
  uint32 Reserved     : 1;
  uint32 u1TDMAE      : 1;
  uint32 u5OSR        : 5;
  uint32 u1M10        : 1;
  uint32 u1MAEN2      : 1;
  uint32 u1MAEN1      : 1;

}tsCddMlcUart_NXP_BAUD;

typedef union tuCddMlcUart_NXP_BAUD
{
  tsCddMlcUart_NXP_BAUD     sBit;
  uint32                    u32Register;
}tuCddMlcUart_NXP_BAUD;


//LPUART Status Register
typedef struct tsCddMlcUart_NXP_STAT
{
  uint32 Reserved1  : 2;
  uint32 Reserved2  : 12;
  uint32 u1MA2F     : 1;
  uint32 u1MA1F     : 1;
  uint32 u1PF       : 1;
  uint32 u1FE       : 1;
  uint32 u1NF       : 1;
  uint32 u1OR       : 1;
  uint32 u1IDLE     : 1;
  uint32 u1RDRF     : 1;
  uint32 u1TC       : 1;
  uint32 u1TDRE     : 1;
  uint32 u1RAF      : 1;
  uint32 u1LBKDE    : 1;
  uint32 u1BRK13    : 1;
  uint32 u1RWUID    : 1;
  uint32 u1RXINV    : 1;
  uint32 u1MSBF     : 1;
  uint32 u1RXEDGIF  : 1;
  uint32 u1LBKDIF   : 1;

}tsCddMlcUart_NXP_STAT;

typedef union tuCddMlcUart_NXP_STAT
{
  tsCddMlcUart_NXP_STAT     sBit;
  uint32                    u32Register;
}tuCddMlcUart_NXP_STAT;


//LPUART Control Register
typedef struct tsCddMlcUart_NXP_CTRL
{
  uint32 u1PT       : 1;
  uint32 u1PE       : 1;
  uint32 u1ILT      : 1;
  uint32 u1WAKE     : 1;
  uint32 u1M        : 1;
  uint32 u1RSRC     : 1;
  uint32 u1DOZEEN   : 1;
  uint32 u1LOOPS    : 1;
  uint32 u3IDLECFG  : 3;
  uint32 u1M7       : 1;
  uint32 Reserved   : 2;
  uint32 u1MA2IE    : 1;
  uint32 u1MA1IE    : 1;
  uint32 u1SBK      : 1;
  uint32 u1RWU      : 1;
  uint32 u1RE       : 1;
  uint32 u1TE       : 1;
  uint32 u1ILIE     : 1;
  uint32 u1RIE      : 1;
  uint32 u1TCIE     : 1;
  uint32 u1TIE      : 1;
  uint32 u1PEIE     : 1;
  uint32 u1FEIE     : 1;
  uint32 u1NEIE     : 1;
  uint32 u1ORIE     : 1;
  uint32 u1TXINV    : 1;
  uint32 u1TXDIR    : 1;
  uint32 u1R9T8     : 1;
  uint32 u1R8T9     : 1;
}tsCddMlcUart_NXP_CTRL;

typedef union tuCddMlcUart_NXP_CTRL
{
  tsCddMlcUart_NXP_CTRL   sBit;
  uint32                  u32Register;
}tuCddMlcUart_NXP_CTRL;


//LPUART Data Register
typedef struct tsCddMlcUart_NXP_DATA
{
  uint32 u1R0T0     : 1;
  uint32 u1R1T1     : 1;
  uint32 u1R2T2     : 1;
  uint32 u1R3T3     : 1;
  uint32 u1R4T4     : 1;
  uint32 u1R5T5     : 1;
  uint32 u1R6T6     : 1;
  uint32 u1R7T7     : 1;
  uint32 u1R8T8     : 1;
  uint32 u1R9T9     : 1;
  uint32 Reserved1  : 1;
  uint32 u1IDLINE   : 1;
  uint32 u1RXEMPT   : 1;
  uint32 u1FRETSC   : 1;
  uint32 u1PARITYE  : 1;
  uint32 u1NOISY    : 1;
  uint32 Reserved2  : 16;
}tsCddMlcUart_NXP_DATA;


typedef union tuCddMlcUart_NXP_DATA
{
  tsCddMlcUart_NXP_DATA   sBit;
  uint32                  u32Register;
}tuCddMlcUart_NXP_DATA;


// LPUART Match Address Register
typedef struct tsCddMlcUart_NXP_MATCH
{
  uint32 u10MA1     : 10;
  uint32 Reserved1  : 6;
  uint32 u10MA2     : 10;
  uint32 Reserved2  : 6;
}tsCddMlcUart_NXP_MATCH;

typedef union tuCddMlcUart_NXP_MATCH
{
  tsCddMlcUart_NXP_MATCH  sBit;
  uint32                  u32Register;
}tuCddMlcUart_NXP_MATCH;


// LPUART Modem IrDA Register
typedef struct tsCddMlcUart_NXP_MODIR
{
  uint32 u1TXCTSE   : 1;
  uint32 u1TXRTSE   : 1;
  uint32 u1TXRTSPOL : 1;
  uint32 u1RXRTSE   : 1;
  uint32 u1TXCTSC   : 1;
  uint32 u1TXCTSSRC : 1;
  uint32 Reserved   : 2;
  uint32 u2RTSWATER : 2;
  uint32 Reserved1  : 6;
  uint32 u2TNP      : 2;
  uint32 u1IREN     : 1;
  uint32 Reserved2  : 13;

}tsCddMlcUart_NXP_MODIR;

typedef union tuCddMlcUart_NXP_MODIR
{
  tsCddMlcUart_NXP_MODIR  sBit;
  uint32                  u32Register;
}tuCddMlcUart_NXP_MODIR;



//LPUART FIFO Register
typedef struct tsCddMlcUart_NXP_FIFO
{
  uint32 u3RXFIFOSIZE   : 3;
  uint32 u1RXFE         : 1;
  uint32 u3TXFIFOSIZE   : 3;
  uint32 u1TXFE         : 1;
  uint32 u1RXUFE        : 1;
  uint32 u1TXOFE        : 1;
  uint32 u3RXIDEN       : 3;
  uint32 Reserved1      : 1;
  uint32 u1RXFLUSH      : 1;
  uint32 u1TXFLUSH      : 1;
  uint32 u1RXUF         : 1;
  uint32 u1TXOF         : 1;
  uint32 Reserved2      : 4;
  uint32 u1RXEMPT       : 1;
  uint32 u1TXEMPT       : 1;
  uint32 Reserved3      : 8;
}tsCddMlcUart_NXP_FIFO;

typedef union tuCddMlcUart_NXP_FIFO
{
  tsCddMlcUart_NXP_FIFO  sBit;
  uint32                 u32Register;
}tuCddMlcUart_NXP_FIFO;


//LPUART Watermark Register
typedef struct tsCddMlcUart_NXP_WATER
{
  uint32 u2TXWATER  : 2;
  uint32 Reserved   : 6;
  uint32 u3TXCOUNT  : 3;
  uint32 Reserved1  : 5;
  uint32 u2RXWATER  : 2;
  uint32 Reserved2  : 6;
  uint32 u3RXCOUNT  : 3;
  uint32 Reserved3  : 5;
}tsCddMlcUart_NXP_WATER;

typedef union tuCddMlcUart_NXP_WATER
{
  tsCddMlcUart_NXP_WATER  sBit;
  uint32                  u32Register;
}tuCddMlcUart_NXP_WATER;


typedef struct  __attribute__((packed, aligned(4))) tsCddUart_S32K_14X_Registers
{
  tuCddMlcUart_NXP_VERID      uVERID;       //<UART_BASE> + 0H
  tuCddMlcUart_NXP_PARAM      uPARAM;       //<UART_BASE> + 4H
  tuCddMlcUart_NXP_GLOBAL     uGLOBAL;      //<UART_BASE> + 8H
  tuCddMlcUart_NXP_PINCFG     uPINCFG;      //<UART_BASE> + CH
  tuCddMlcUart_NXP_BAUD       uBAUD;        //<UART_BASE> + 10H
  tuCddMlcUart_NXP_STAT       uSTAT;        //<UART_BASE> + 14H
  tuCddMlcUart_NXP_CTRL       uCTRL;        //<UART_BASE> + 18H
  tuCddMlcUart_NXP_DATA       uDATA;        //<UART_BASE> + 1CH
  tuCddMlcUart_NXP_MATCH      uMATCH;       //<UART_BASE> + 20H
  tuCddMlcUart_NXP_MODIR      uMODIR;       //<UART_BASE> + 24H
  tuCddMlcUart_NXP_FIFO       uFIFO;        //<UART_BASE> + 28H
  tuCddMlcUart_NXP_WATER      uWATER;       //<UART_BASE> + 2CH
}tsCddUart_S32K_14X_Registers;


/* LPUART - Peripheral instance base addresses */
#define UART_BASE                                     (0x4006B000u)

/** Peripheral LPUART base pointer */
#define CDDUARTBASE                                   ((volatile tsCddUart_S32K_14X_Registers *)UART_BASE)



#endif // CDD_UART_S32K_14X_TYPES_2023_09_08_H
