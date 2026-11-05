////*****************************************************************************
//// (C) Automotive Lighting Reutlingen GmbH
////     Tuebinger Strasse 123, 72762 Reutlingen, Germany
////
//// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
//// This work shall not be copied, reproduced, used, modified, transferred
//// or its information shall not be disclosed without the prior written
//// authorization of Automotive Lighting Reutlingen GmbH.
////*****************************************************************************
////-----------------------------------------------------------------------------
///// \file  CddAdc_S32K_142X_Reg_Types.h
/////
///// \brief S32k14x Register types used by CddAdc
/////
///// \author Stefan Tyirean (f75617c)
/////     mailto: stefan.tyirean[at]marelli.com
/////
////-----------------------------------------------------------------------------
//
//#ifndef CDDADC_S32K_146_REG_TYPES_2021_03_05_H_
//#define CDDADC_S32K_146_REG_TYPES_2021_03_05_H_
//
//#include <Std_Types.h>
//
///** ADC - Size of Registers Arrays */
//#define ADC_SC1_COUNT                            16u
//#define ADC_R_COUNT                              16u
//#define ADC_CV_COUNT                             2u
//#define ADC_aSC1_COUNT                           24u
//#define ADC_aR_COUNT                             24u
//
//// SC1 Reg
//typedef union ADC_SC1_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//    volatile uint32 ADCH : 6;
//    volatile uint32 AEN : 1;
//    volatile uint32 COCO : 1;
//    volatile uint32 Reserved_0 : 24;
//  }Bit;
//}tuCddAdc_ADC_SC1_Reg;
//
//// CFG1 Reg
//typedef union ADC_CFG1_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//    volatile uint32 ADICLK : 2;
//    volatile uint32 MODE : 2;
//    volatile uint32 Reserved_2 : 1;
//    volatile uint32 ADIV : 2;
//    volatile uint32 Reserved_1 : 1;
//    volatile uint32 CLRLTR : 1;
//    volatile uint32 Reserved_0 : 23;
//  }Bit;
//}tuCddAdc_ADC_CFG1_Reg;
//
//// CFG2 Reg
//typedef union ADC_CFG2_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//    volatile uint32 SMPLTS : 8;
//    volatile uint32 Reserved_0 : 24;
//  }Bit;
//}tuCddAdc_ADC_CFG2_Reg;
//
//// R Reg
//typedef union ADC_R_tag
//{
//  volatile uint32 Reg;
//  // 12 Bit Access
//  struct
//  {
//		volatile uint32 D : 12;
//    volatile uint32 Reserved_0 : 20;
//  }Bit12;
//  // 10 Bit Access
//  struct
//  {
//		volatile uint32 D : 10;
//    volatile uint32 Reserved_0 : 22;
//  }Bit10;
//  // 8 Bit Access
//  struct
//  {
//		volatile uint32 D : 8;
//    volatile uint32 Reserved_0 : 24;
//  }Bit8;
//}tuCddAdc_ADC_R_Reg;
//
//// CV Reg
//typedef union ADC_CV_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CV : 8;
//    volatile uint32 Reserved_0 : 16;
//  }Bit;
//}tuCddAdc_ADC_CV_Reg;
//
//// SC2 Reg
//typedef union ADC_SC2_tag
//{
//  volatile uint32 Reg;
//  struct
//  {    
//		volatile uint32 REFSEL : 2;
//		volatile uint32 DMAEN : 1;
//		volatile uint32 ACREN : 1;
//		volatile uint32 ACFGT : 1;
//		volatile uint32 ADCFE : 1;
//		volatile uint32 ADTRG : 1;
//		volatile uint32 ADACT : 1;
//		volatile uint32 Reserved_3 : 5;
//		volatile uint32 TRGPRNUM : 2;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 TRGSTLAT : 4;
//		volatile uint32 Reserved_1 : 4;
//		volatile uint32 TRGSTERR : 4;
//    volatile uint32 Reserved_0 : 4;
//  }Bit;
//}tuCddAdc_ADC_SC2_Reg;
//
//// SC3 Reg
//typedef union ADC_SC3_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 AVGS : 2;
//		volatile uint32 AVGE : 1;
//		volatile uint32 ADCO : 1;
//		volatile uint32 Reserved_1 : 3;
//		volatile uint32 CAL : 1;
//    volatile uint32 Reserved_0 : 24;
//  }Bit;
//}tuCddAdc_ADC_SC3_Reg;
//
//// BASE_OFS Reg
//typedef union ADC_BASE_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 BA_OFS : 8;
//    volatile uint32 Reserved_0 : 24;
//  }Bit;
//}tuCddAdc_ADC_BASE_OFS_Reg;
//
//// OFS Reg
//typedef union ADC_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//	  volatile uint32 OFS : 16;
//    volatile uint32 Reserved_0 : 16;
//  }Bit;
//}tuCddAdc_ADC_OFS_Reg;
//
//// USR_OFS Reg
//typedef union ADC_USR_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 USR_OFS : 8;
//    volatile uint32 Reserved_0 : 24;
//  }Bit;
//}tuCddAdc_ADC_USR_OFS_Reg;
//
//// XOFS Reg
//typedef union ADC_XOFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 XOFS : 6;
//    volatile uint32 Reserved_0 : 26;
//  }Bit;
//}tuCddAdc_ADC_XOFS_Reg;
//
//// YOFS Reg
//typedef union ADC_YOFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 YOFS : 8;
//    volatile uint32 Reserved_0 : 24;
//  }Bit;
//}tuCddAdc_ADC_YOFS_Reg;
//
//// G Reg
//typedef union ADC_G_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 G : 11;
//    volatile uint32 Reserved_0 : 21;
//  }Bit;
//}tuCddAdc_ADC_G_Reg;
//
//// UG Reg
//typedef union ADC_UG_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//	  volatile uint32 UG : 10;
//    volatile uint32 Reserved_0 : 22;
//  }Bit;
//}tuCddAdc_ADC_UG_Reg;
//
//// CLPS Reg
//typedef union ADC_CLPS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLPS : 7;
//    volatile uint32 Reserved_0 : 25;
//  }Bit;
//}tuCddAdc_ADC_CLPS_Reg;
//
//// CLP3 Reg
//typedef union ADC_CLP3_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLP3 : 10;
//    volatile uint32 Reserved_0 : 22;
//  }Bit;
//}tuCddAdc_ADC_CLP3_Reg;
//
//// CLP2 Reg
//typedef union ADC_CLP2_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLP2 : 10;
//    volatile uint32 Reserved_0 : 22;
//  }Bit;
//}tuCddAdc_ADC_CLP2_Reg;
//
//// CLP1 Reg
//typedef union ADC_CLP1_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLP1 : 9;
//    volatile uint32 Reserved_0 : 23;
//  }Bit;
//}tuCddAdc_ADC_CLP1_Reg;
//
//// CLP0 Reg
//typedef union ADC_CLP0_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLP0 : 8;
//    volatile uint32 Reserved_0 : 24;
//  }Bit;
//}tuCddAdc_ADC_CLP0_Reg;
//
//// CLPX Reg
//typedef union ADC_CLPX_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLPX : 7;
//		volatile uint32 Reserved_1 : 1;
//    volatile uint32 Reserved_0 : 24; 
//  }Bit;
//}tuCddAdc_ADC_CLPX_Reg;
//
//// CLP9 Reg
//typedef union ADC_CLP9_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLP9 : 7;
//		volatile uint32 Reserved_1 : 1;
//    volatile uint32 Reserved_0 : 24; 
//  }Bit;
//}tuCddAdc_ADC_CLP9_Reg;
//
//// CLPS_OFS Reg
//typedef union ADC_CLPS_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLPS_OFS : 4;
//    volatile uint32 Reserved_0 : 28;
//  }Bit;
//}tuCddAdc_ADC_CLPS_OFS_Reg;
//
//// CLP3_OFS Reg
//typedef union ADC_CLP3_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLP3_OFS : 4;
//    volatile uint32 Reserved_0 : 28;
//  }Bit;
//}tuCddAdc_ADC_CLP3_OFS_Reg;
//
//// CLP2_OFS Reg
//typedef union ADC_CLP2_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLP2_OFS : 4;
//    volatile uint32 Reserved_0 : 28;
//  }Bit;
//}tuCddAdc_ADC_CLP2_OFS_Reg;
//
//// CLP1_OFS Reg
//typedef union ADC_CLP1_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLP1_OFS : 4;
//    volatile uint32 Reserved_0 : 28;
//  }Bit;
//}tuCddAdc_ADC_CLP1_OFS_Reg;
//
//// CLP0_OFS Reg
//typedef union ADC_CLP0_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CLP0_OFS : 4;
//    volatile uint32 Reserved_0 : 28;
//  }Bit;
//}tuCddAdc_ADC_CLP0_OFS_Reg;
//
//// CLPX_OFS Reg
//typedef union ADC_CLPX_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//	  volatile uint32 CLPX_OFS : 12;
//    volatile uint32 Reserved_0 : 20;
//  }Bit;
//}tuCddAdc_ADC_CLPX_OFS_Reg;
//
//// CLP9_OFS Reg
//typedef union ADC_CLP9_OFS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//    volatile uint32 CLP9_OFS : 12;
//    volatile uint32 Reserved_0 : 20;
//  }Bit;
//}tuCddAdc_ADC_CLP9_OFS_Reg;
//
///** ADC - Register Layout Typedef */
//typedef struct {
//  volatile tuCddAdc_ADC_SC1_Reg SC1[ADC_SC1_COUNT];      /**< ADC Status and Control Register 1, array offset: 0x0, array step: 0x4 */
//  volatile tuCddAdc_ADC_CFG1_Reg CFG1;                   /**< ADC Configuration Register 1, offset: 0x40 */
//  volatile tuCddAdc_ADC_CFG2_Reg CFG2;                   /**< ADC Configuration Register 2, offset: 0x44 */
//  volatile const tuCddAdc_ADC_R_Reg R[ADC_R_COUNT];      /**< ADC Data Result Registers, array offset: 0x48, array step: 0x4 */
//  volatile tuCddAdc_ADC_CV_Reg CV[ADC_CV_COUNT];         /**< Compare Value Registers, array offset: 0x88, array step: 0x4 */
//  volatile tuCddAdc_ADC_SC2_Reg SC2;                     /**< Status and Control Register 2, offset: 0x90 */
//  volatile tuCddAdc_ADC_SC3_Reg SC3;                     /**< Status and Control Register 3, offset: 0x94 */
//  volatile tuCddAdc_ADC_BASE_OFS_Reg BASE_OFS;           /**< BASE Offset Register, offset: 0x98 */
//  volatile tuCddAdc_ADC_OFS_Reg OFS;                     /**< ADC Offset Correction Register, offset: 0x9C */
//  volatile tuCddAdc_ADC_USR_OFS_Reg USR_OFS;             /**< USER Offset Correction Register, offset: 0xA0 */
//  volatile tuCddAdc_ADC_XOFS_Reg XOFS;                   /**< ADC X Offset Correction Register, offset: 0xA4 */
//  volatile tuCddAdc_ADC_YOFS_Reg YOFS;                   /**< ADC Y Offset Correction Register, offset: 0xA8 */
//  volatile tuCddAdc_ADC_G_Reg G;                         /**< ADC Gain Register, offset: 0xAC */
//  volatile tuCddAdc_ADC_UG_Reg UG;                       /**< ADC User Gain Register, offset: 0xB0 */
//  volatile tuCddAdc_ADC_CLPS_Reg CLPS;                   /**< ADC General Calibration Value Register S, offset: 0xB4 */
//  volatile tuCddAdc_ADC_CLP3_Reg CLP3;                   /**< ADC Plus-Side General Calibration Value Register 3, offset: 0xB8 */
//  volatile tuCddAdc_ADC_CLP2_Reg CLP2;                   /**< ADC Plus-Side General Calibration Value Register 2, offset: 0xBC */
//  volatile tuCddAdc_ADC_CLP1_Reg CLP1;                   /**< ADC Plus-Side General Calibration Value Register 1, offset: 0xC0 */
//  volatile tuCddAdc_ADC_CLP0_Reg CLP0;                   /**< ADC Plus-Side General Calibration Value Register 0, offset: 0xC4 */
//  volatile tuCddAdc_ADC_CLPX_Reg CLPX;                   /**< ADC Plus-Side General Calibration Value Register X, offset: 0xC8 */
//  volatile tuCddAdc_ADC_CLP9_Reg CLP9;                   /**< ADC Plus-Side General Calibration Value Register 9, offset: 0xCC */
//  volatile tuCddAdc_ADC_CLPS_OFS_Reg CLPS_OFS;           /**< ADC General Calibration Offset Value Register S, offset: 0xD0 */
//  volatile tuCddAdc_ADC_CLP3_OFS_Reg CLP3_OFS;           /**< ADC Plus-Side General Calibration Offset Value Register 3, offset: 0xD4 */
//  volatile tuCddAdc_ADC_CLP2_OFS_Reg CLP2_OFS;           /**< ADC Plus-Side General Calibration Offset Value Register 2, offset: 0xD8 */
//  volatile tuCddAdc_ADC_CLP1_OFS_Reg CLP1_OFS;           /**< ADC Plus-Side General Calibration Offset Value Register 1, offset: 0xDC */
//  volatile tuCddAdc_ADC_CLP0_OFS_Reg CLP0_OFS;           /**< ADC Plus-Side General Calibration Offset Value Register 0, offset: 0xE0 */
//  volatile tuCddAdc_ADC_CLPX_OFS_Reg CLPX_OFS;           /**< ADC Plus-Side General Calibration Offset Value Register X, offset: 0xE4 */
//  volatile tuCddAdc_ADC_CLP9_OFS_Reg CLP9_OFS;           /**< ADC Plus-Side General Calibration Offset Value Register 9, offset: 0xE8 */
//  uint8 Reserved_0[28];
//  volatile tuCddAdc_ADC_SC1_Reg aSC1[ADC_aSC1_COUNT];    /**< ADC Status and Control Register 1 (alias)..ADC Status and Control Register 1, array offset: 0x108, array step: 0x4 */
//  uint8 Reserved_1[32];
//  volatile const tuCddAdc_ADC_R_Reg aR[ADC_aR_COUNT];    /**< ADC Data Result Registers (alias)..ADC Data Result Registers, array offset: 0x188, array step: 0x4 */
//} tsCddAdc_AdcReg;
//
//
///* ADC - Peripheral instance base addresses */
///** Peripheral ADC0 base address */
//#define ADC0_BASE                                (0x4003B000u)
///** Peripheral ADC1 base address */
//#define ADC1_BASE                                (0x40027000u)
//
///** Peripheral ADC0 base pointer */
//#define ADC0                                     ((tsCddAdc_AdcReg *)ADC0_BASE)
///** Peripheral ADC1 base pointer */
//#define ADC1                                     ((tsCddAdc_AdcReg *)ADC1_BASE)
//
//#define ADC_INST_BASE_ADDR                       {ADC0, ADC1}
//
///** PDB - Size of Registers Arrays */
//#define PDB_CH_COUNT                             3u
//#define PDB_DLY_COUNT                            8u
//#define PDB_POnDLY_COUNT                         1u
//
//// SC Reg
//typedef union PDB_SC_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 LDOK : 1;
//		volatile uint32 CONT : 1;
//		volatile uint32 MULT : 2;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 PDBIE : 1;
//		volatile uint32 PDBIF : 1;
//		volatile uint32 PDBEN : 1;
//		volatile uint32 TRGSEL : 4;
//		volatile uint32 PRESCALER : 3;
//		volatile uint32 DMAEN : 1;
//		volatile uint32 SWTRIG : 1;
//		volatile uint32 PDBEIE : 1;
//		volatile uint32 LDMOD : 2;
//    volatile uint32 Reserved_0 : 12;
//  }Bit;
//}tuCddAdc_PDB_SC_Reg;
//
//// MOD Reg
//typedef union PDB_MOD_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 MOD : 16;
//    volatile uint32 Reserved_0 : 16;
//  }Bit;
//}tuCddAdc_PDB_MOD_Reg;
//
//// CNT Reg
//typedef union PDB_CNT_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CNT : 16;
//    volatile uint32 Reserved_0 : 16;
//  }Bit;
//}tuCddAdc_PDB_CNT_Reg;
//
//// IDLY Reg
//typedef union PDB_IDLY_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 IDLY : 16;
//    volatile uint32 Reserved_0 : 16;
//  }Bit;
//}tuCddAdc_PDB_IDLY_Reg;
//
//// C1 Reg
//typedef union PDB_CH_C1_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 EN : 8;
//		volatile uint32 TOS : 8;
//		volatile uint32 BB : 8;
//    volatile uint32 Reserved_0 : 8;
//  }Bit;
//}tuCddAdc_PDB_CH_C1_Reg;
//
//// S Reg
//typedef union PDB_CH_S_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 ERR : 8;
//		volatile uint32 Reserved_1 : 8;
//		volatile uint32 CF : 8;
//    volatile uint32 Reserved_0 : 8;  
//  }Bit;
//}tuCddAdc_PDB_CH_S_Reg;
//
//// DLY Regs
//typedef union PDB_CH_DLY_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 DLY : 16;
//    volatile uint32 Reserved_0 : 16;
//  }Bit;
//}tuCddAdc_PDB_CH_DLY_Reg;
//
//// CH Regs
//typedef struct PDB_CHn_tag
//{
//  volatile tuCddAdc_PDB_CH_C1_Reg C1;                     /**< Channel n Control register 1, array offset: 0x10, array step: 0x28 */
//  volatile tuCddAdc_PDB_CH_S_Reg S;                       /**< Channel n Status register, array offset: 0x14, array step: 0x28 */
//  volatile tuCddAdc_PDB_CH_DLY_Reg DLY[PDB_DLY_COUNT];    /**< Channel n Delay 0 register..Channel n Delay 7 register, array offset: 0x18, array step: index*0x28, index2*0x4 */
//}tsCddAdc_CHn_Reg;
//
//
//// POEN Reg
//typedef union PDB_POEN_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 POEN : 8;
//    volatile uint32 Reserved_0 : 24;
//  }Bit;
//}tuCddAdc_PDB_POEN_Reg;
//
//// PODLY Reg
//typedef union PDB_PODLY_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 DLY1 : 16;
//    volatile uint32 DLY2 : 16;
//  }Bit;
//}tuCddAdc_PDB_PODLY_Reg;
//
//
///** PDB - Register Layout Typedef */
//typedef struct
//{
//  volatile tuCddAdc_PDB_SC_Reg SC;                            /**< Status and Control register, offset: 0x0 */
//  volatile tuCddAdc_PDB_MOD_Reg MOD;                          /**< Modulus register, offset: 0x4 */
//  volatile const  tuCddAdc_PDB_CNT_Reg CNT;                   /**< Counter register, offset: 0x8 */
//  volatile tuCddAdc_PDB_IDLY_Reg IDLY;                        /**< Interrupt Delay register, offset: 0xC */
//  volatile tsCddAdc_CHn_Reg CH[PDB_CH_COUNT];                 /**< Channel registers    */
//  volatile uint8 Reserved_0[264];
//  volatile tuCddAdc_PDB_POEN_Reg POEN;                        /**< Pulse-Out n Enable register, offset: 0x190 */
//  volatile tuCddAdc_PDB_PODLY_Reg POnDLY[PDB_POnDLY_COUNT];   /**< Pulse-Out n Delay register, array offset: 0x194, array step: 0x4 */
//} tsCddAdc_PdbReg;
//
//
///** Peripheral PDB0 base address */
//#define PDB0_BASE                                (0x40036000u)
///** Peripheral PDB0 base pointer */
//#define PDB0                                     ((tsCddAdc_PdbReg *)PDB0_BASE)
///** Peripheral PDB1 base address */
//#define PDB1_BASE                                (0x40031000u)
///** Peripheral PDB1 base pointer */
//#define PDB1                                     ((tsCddAdc_PdbReg *)PDB1_BASE)
//
//
//// CHIPCTL Reg
//typedef union SIM_CHIPCTL_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 ADC_INTERLEAVE_EN : 4;
//		volatile uint32 CLKOUTSEL : 4;
//		volatile uint32 CLKOUTDIV : 3;
//		volatile uint32 CLKOUTEN : 1;
//		volatile uint32 TRACECLK_SEL : 1;
//		volatile uint32 PDB_BB_SEL : 1;
//		volatile uint32 Reserved_1 : 2;
//		volatile uint32 ADC_SUPPLY : 1;
//		volatile uint32 ADC_SUPPLYEN : 1;
//		volatile uint32 SRAMU_RETEN : 1;
//		volatile uint32 SRAML_RETEN : 1;
//    volatile uint32 Reserved_0 : 10;
//  }Bit;
//}tuCddAdc_SIM_CHIPCTL_Reg;
//
//// FTMOPT0 Reg
//typedef union SIM_FTMOPT0_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 FTM0FLTxSEL : 3;
//		volatile uint32 Reserved_3 : 1;
//		volatile uint32 FTM1FLTxSEL : 3;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 FTM2FLTxSEL : 3;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 FTM3FLTxSEL : 3;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 FTM4CLKSEL : 2;
//		volatile uint32 FTM5CLKSEL : 2;
//		volatile uint32 FTM6CLKSEL : 2;
//		volatile uint32 FTM7CLKSEL : 2;
//		volatile uint32 FTM0CLKSEL : 2;
//		volatile uint32 FTM1CLKSEL : 2;
//		volatile uint32 FTM2CLKSEL : 2;
//    volatile uint32 FTM3CLKSEL : 2; 
//  }Bit;
//}tuCddAdc_SIM_FTMOPT0_Reg;
//
//// LPOCLKS Reg
//typedef union SIM_LPOCLKS_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 LPO1CLKEN : 1;
//		volatile uint32 LPO32CLKEN : 1;
//		volatile uint32 LPOCLKSEL : 2;
//		volatile uint32 RTCCLKSEL : 2;
//    volatile uint32 Reserved_0 : 26;
//  }Bit;
//}tuCddAdc_SIM_LPOCLKS_Reg;
//
//// ADCOPT Reg
//typedef union SIM_ADCOPT_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 ADC0TRGSEL : 1;
//		volatile uint32 ADC0SWPRETRG : 3;
//		volatile uint32 ADC0PRETRGSEL : 2;
//		volatile uint32 Reserved_1 : 2;
//		volatile uint32 ADC1TRGSEL : 1;
//		volatile uint32 ADC1SWPRETRG : 3;
//		volatile uint32 ADC1PRETRGSEL : 2;
//    volatile uint32 Reserved_0 : 18;
//  }Bit;
//}tuCddAdc_SIM_ADCOPT_Reg;
//
//// FTMOP1T Reg
//typedef union SIM_FTMOPT_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 FTM0SYMCBIT : 1;
//		volatile uint32 FTM1SYMCBIT : 1;
//		volatile uint32 FTM2SYMCBIT : 1;
//		volatile uint32 FTM3SYMCBIT : 1;
//		volatile uint32 FTM1CH0SEL : 2;
//		volatile uint32 FTM2CH0SEL : 2;
//		volatile uint32 FTM2CH1SEL : 1;
//		volatile uint32 Reserved_0 : 2;
//		volatile uint32 FTM4SYNCBIT : 1;
//		volatile uint32 FTM5SYNCBIT : 1;
//		volatile uint32 FTM6SYNCBIT : 1;
//		volatile uint32 FTM7SYMCBIT : 1;
//		volatile uint32 FTMGLDOK : 1;
//		volatile uint32 FTM0_OUTSEL : 8;
//    volatile uint32 FTM3_OUTSEL : 8;
//  }Bit;
//}tuCddAdc_SIM_FTMOPT1_Reg;
//
//
//// MISCTRL0 Reg
//typedef union SIM_MISCTRL0_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 Reserved_3 : 9;
//		volatile uint32 STOP1_MONITOR : 1;
//		volatile uint32 STOP2_MONITOR : 1;
//		volatile uint32 Reserved_2 : 3;
//		volatile uint32 FTM_GTB_SPLIT_EN : 1;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 FTM0_OBE_CTRL : 1;
//		volatile uint32 FTM1_OBE_CTRL : 1;
//		volatile uint32 FTM2_OBE_CTRL : 1;
//		volatile uint32 FTM3_OBE_CTRL : 1;
//		volatile uint32 FTM4_OBE_CTRL : 1;
//		volatile uint32 FTM5_OBE_CTRL : 1;
//		volatile uint32 FTM6_OBE_CTRL : 1;
//		volatile uint32 FTM7_OBE_CTRL : 1;
//		volatile uint32 RMII_CLK_OBE : 1;
//		volatile uint32 RMII_CLK_SEL : 1;
//		volatile uint32 QSPI_CLK_SEL : 1;
//    volatile uint32 Reserved_0 : 5;
//  }Bit;
//}tuCddAdc_SIM_MISCTRL0_Reg;
//
//// SSID Reg
//typedef union SIM_SSID_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 FEATURES : 8;
//		volatile uint32 PACKAGE : 4;
//		volatile uint32 REVID : 4;
//		volatile uint32 RAMSIZE : 4;
//		volatile uint32 DERIVATE : 4;
//		volatile uint32 SUBSERIES : 4;
//    volatile uint32 GENERATION : 4;  
//  }Bit;
//}tuCddAdc_SIM_SSID_Reg;
//
//// PLATCGG Reg
//typedef union SIM_PLATCGC_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 CGCMSCM : 1;
//		volatile uint32 CGCMPUA : 1;
//		volatile uint32 CGCDMA : 1;
//		volatile uint32 CGCERM : 1;
//		volatile uint32 CGCEIM : 1;
//    volatile uint32 Reserved_0 : 27;
//  }Bit;
//}tuCddAdc_SIM_PLATCGC_Reg;
//
//// FCFG1 Reg
//typedef union SIM_FCFG1_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 Reserved_3 : 1;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 Reserved_1 : 10;
//		volatile uint32 DEPART : 4;
//		volatile uint32 EEERAMSIZE : 4;
//    volatile uint32 Reserved_0 : 12;
//  }Bit;
//}tuCddAdc_SIM_FCFG1_Reg;
//
//// UIDH Reg
//typedef union SIM_UIDH_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//    volatile uint32 UID127_96 : 32;
//  }Bit;
//}tuCddAdc_SIM_UIDH_Reg;
//
//// UIDMH Reg
//typedef union SIM_UIDMH_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//    volatile uint32 UID95_64 : 32;
//  }Bit;
//}tuCddAdc_SIM_UIDMH_Reg;
//
//// UIDML Reg
//typedef union SIM_UIDML_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//    volatile uint32 UID63_32 : 32;
//  }Bit;
//}tuCddAdc_SIM_UIDML_Reg;
//
//// UIDL Reg
//typedef union SIM_UIDL_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//    volatile uint32 UID31_0 : 32;
//  }Bit;
//}tuCddAdc_SIM_UIDL_Reg;
//
//// CLKDIV4 Reg
//typedef union SIM_CLKDIV4_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 TRACEFRAC : 1;
//		volatile uint32 TRACEDIV : 3;
//		volatile uint32 Reserved_1 : 24;
//		volatile uint32 TRACEDIVEN : 1;
//    volatile uint32 Reserved_0 : 3; 
//  }Bit;
//}tuCddAdc_SIM_CLKDIV4_Reg;
//
//// MISCTRL1 Reg
//typedef union SIM_MISCTRL1_tag
//{
//  volatile uint32 Reg;
//  struct
//  {
//		volatile uint32 SW_TRG : 1;
//    volatile uint32 Reserved_0 : 31;
//  }Bit;
//}tuCddAdc_SIM_MISCTRL1_Reg;
//
//
///** SIM - Register Layout Typedef */
//typedef struct {
//  volatile uint8 Reserved_0[4];
//  volatile tuCddAdc_SIM_CHIPCTL_Reg CHIPCTL;       /**< Chip Control register, offset: 0x4 */
//  volatile uint8 Reserved_1[4];
//  volatile tuCddAdc_SIM_FTMOPT0_Reg FTMOPT0;       /**< FTM Option Register 0, offset: 0xC */
//  volatile tuCddAdc_SIM_LPOCLKS_Reg LPOCLKS;       /**< LPO Clock Select Register, offset: 0x10 */
//  volatile uint8 Reserved_2[4];
//  volatile tuCddAdc_SIM_ADCOPT_Reg ADCOPT;         /**< ADC Options Register, offset: 0x18 */
//  volatile tuCddAdc_SIM_FTMOPT1_Reg FTMOPT1;       /**< FTM Option Register 1, offset: 0x1C */
//  volatile tuCddAdc_SIM_MISCTRL0_Reg MISCTRL0;     /**< Miscellaneous control register 0, offset: 0x20 */
//  volatile const  tuCddAdc_SIM_SSID_Reg SDID;      /**< System Device Identification Register, offset: 0x24 */
//  volatile uint8 Reserved_3[24];
//  volatile tuCddAdc_SIM_PLATCGC_Reg PLATCGC;       /**< Platform Clock Gating Control Register, offset: 0x40 */
//  volatile uint8 Reserved_4[8];
//  volatile const tuCddAdc_SIM_FCFG1_Reg FCFG1;     /**< Flash Configuration Register 1, offset: 0x4C */
//  volatile uint8 Reserved_5[4];
//  volatile const tuCddAdc_SIM_UIDH_Reg UIDH;       /**< Unique Identification Register High, offset: 0x54 */
//  volatile const tuCddAdc_SIM_UIDMH_Reg UIDMH;     /**< Unique Identification Register Mid-High, offset: 0x58 */
//  volatile const tuCddAdc_SIM_UIDML_Reg UIDML;     /**< Unique Identification Register Mid Low, offset: 0x5C */
//  volatile const tuCddAdc_SIM_UIDL_Reg UIDL;       /**< Unique Identification Register Low, offset: 0x60 */
//  volatile uint8 Reserved_6[4];
//  volatile tuCddAdc_SIM_CLKDIV4_Reg CLKDIV4;       /**< System Clock Divider Register 4, offset: 0x68 */
//  volatile tuCddAdc_SIM_MISCTRL1_Reg MISCTRL1;     /**< Miscellaneous Control register 1, offset: 0x6C */
//} tsCddAdc_SimReg;
//
///* SIM - Peripheral instance base addresses */
///** Peripheral SIM base address */
//#define SIM_BASE                                 (0x40048000u)
///** Peripheral SIM base pointer */
//#define SIM                                      ((tsCddAdc_SimReg *)SIM_BASE)
///** Array initializer of SIM peripheral base addresses */
//
///** TRGMUX - Size of Registers Arrays */
//#define TRGMUX_TRGMUXn_COUNT                     30u
//
//// DMAMUX0 Reg
//typedef union TRGMUX_DMAMUX0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_DMAMUX0_Reg;
//
//// EXTOUT0 Reg
//typedef union TRGMUX_EXTOUT0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_EXTOUT0_Reg;
//
//// EXTOUT1 Reg
//typedef union TRGMUX_EXTOUT1_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_EXTOUT1_Reg;
//
//// ADC0 Reg
//typedef union TRGMUX_ADC0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_ADC0_Reg;
//
//// ADC1 Reg
//typedef union TRGMUX_ADC1_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_ADC1_Reg;
//
//// CMP0 Reg
//typedef union TRGMUX_CMP0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_CMP0_Reg;
//
//// FTM0 Reg
//typedef union TRGMUX_FTM0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_FTM0_Reg;
//
//// FTM1 Reg
//typedef union TRGMUX_FTM1_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_FTM1_Reg;
//
//// FTM2 Reg
//typedef union TRGMUX_FTM2_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_FTM2_Reg;
//
//// FTM3 Reg
//typedef union TRGMUX_FTM3_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_FTM3_Reg;
//
//// PDB0 Reg
//typedef union TRGMUX_PDB0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_PDB0_Reg;
//
//// PDB1 Reg
//typedef union TRGMUX_PDB1_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_PDB1_Reg;
//
//// FLEXIO Reg
//typedef union TRGMUX_FLEXIO_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_FLEXIO_Reg;
//
//// LPIT0 Reg
//typedef union TRGMUX_LPIT0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_2 : 1;
//		volatile uint32 SEL1 : 7;
//		volatile uint32 Reserved_1 : 1;
//		volatile uint32 SEL2 : 7;
//		volatile uint32 Reserved_0 : 1;
//		volatile uint32 SEL3 : 7;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_LPIT0_Reg;
//
//// LPUART0 Reg
//typedef union TRGMUX_LPUART0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_LPUART0_Reg;
//
//// LPUART1 Reg
//typedef union TRGMUX_LPUART1_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_LPUART1_Reg;
//
//// LPI2C0 Reg
//typedef union TRGMUX_LPI2C0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_LPI2C0_Reg;
//
//// LPSPI0 Reg
//typedef union TRGMUX_LPSPI0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_LPSPI0_Reg;
//
//// LPSPI1 Reg
//typedef union TRGMUX_LPSPI1_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_LPSPI1_Reg;
//
//// LPTMR0 Reg
//typedef union TRGMUX_LPTMR0_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_LPTMR0_Reg;
//
//// LPI2C1 Reg
//typedef union TRGMUX_LPI2C1_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_LPI2C1_Reg;
//
//// FTM4 Reg
//typedef union TRGMUX_FTM4_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_FTM4_Reg;
//
//// FTM4 Reg
//typedef union TRGMUX_FTM5_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_FTM5_Reg;
//
//// FTM6 Reg
//typedef union TRGMUX_FTM6_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_FTM6_Reg;
//
//// FTM7 Reg
//typedef union TRGMUX_FTM7_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SEL0 : 7;
//		volatile uint32 Reserved_0 : 24;
//		volatile uint32 LK : 1;
//	}Bit;
//}tuCddAdc_TRGMUX_FTM7_Reg;
//
///** TRGMUX - Register Layout Typedef */
//typedef struct {
//	volatile tuCddAdc_TRGMUX_DMAMUX0_Reg DMAMUX_0;				/**< 0x00 */
//	volatile tuCddAdc_TRGMUX_EXTOUT0_Reg EXTOUT_0;				/**< 0x04 */
//	volatile tuCddAdc_TRGMUX_EXTOUT1_Reg EXTOUT_1;				/**< 0x08 */
//	volatile tuCddAdc_TRGMUX_ADC0_Reg ADC_0;							/**< 0x0C */
//	volatile tuCddAdc_TRGMUX_ADC1_Reg ADC_1;							/**< 0x10 */
//	volatile uint8 Reserved_0[8];													/**< 0x14, 0x18 */
//	volatile tuCddAdc_TRGMUX_CMP0_Reg CMP_0;							/**< 0x1C */
//	volatile uint8 Reserved_1[8];													/**< 0x20, 0x24 */
//	volatile tuCddAdc_TRGMUX_FTM0_Reg FTM_0;							/**< 0x28 */
//	volatile tuCddAdc_TRGMUX_FTM1_Reg FTM_1;							/**< 0x2C */
//	volatile tuCddAdc_TRGMUX_FTM2_Reg FTM_2;							/**< 0x30 */
//	volatile tuCddAdc_TRGMUX_FTM2_Reg FTM_3;							/**< 0x34 */
//	volatile tuCddAdc_TRGMUX_PDB0_Reg PDB_0;							/**< 0x38 */
//	volatile tuCddAdc_TRGMUX_PDB0_Reg PDB_1;							/**< 0x3C */
//  volatile uint8 Reserved_2[4];													/**< 0x40 */
//	volatile tuCddAdc_TRGMUX_FLEXIO_Reg FLEX_IO;					/**< 0x44 */
//	volatile tuCddAdc_TRGMUX_LPIT0_Reg LPIT_0;					  /**< 0x48 */
//	volatile tuCddAdc_TRGMUX_LPUART0_Reg LPUART_0;				/**< 0x4C */
//	volatile tuCddAdc_TRGMUX_LPUART1_Reg LPUART_1;				/**< 0x50 */
//	volatile tuCddAdc_TRGMUX_LPI2C0_Reg LPI2C_0;					/**< 0x54 */
//	volatile uint8 Reserved_3[4];													/**< 0x58 */
//	volatile tuCddAdc_TRGMUX_LPSPI0_Reg	LPSPI_0;					/**< 0x5C */
//	volatile tuCddAdc_TRGMUX_LPSPI1_Reg	LPSPI_1;					/**< 0x60 */
//	volatile tuCddAdc_TRGMUX_LPTMR0_Reg	LPTMR_0;					/**< 0x64 */
//	volatile uint8 Reserved_4[4];													/**< 0x68 */
//	volatile tuCddAdc_TRGMUX_LPI2C1_Reg LPI2C_1;					/**< 0x6C */
//	volatile tuCddAdc_TRGMUX_FTM4_Reg FTM_4;							/**< 0x70 */
//	volatile tuCddAdc_TRGMUX_FTM5_Reg FTM_5;							/**< 0x74 */
//	volatile tuCddAdc_TRGMUX_FTM5_Reg FTM_6;							/**< 0x78 */
//	volatile tuCddAdc_TRGMUX_FTM5_Reg FTM_7;							/**< 0x7C */
//} tsCddAdc_TrgMuxReg;
//
//
///* TRGMUX - Peripheral instance base addresses */
///** Peripheral TRGMUX base address */
//#define TRGMUX_BASE                              (0x40063000u)
///** Peripheral TRGMUX base pointer */
//#define TRGMUX                                   ((tsCddAdc_TrgMuxReg *)TRGMUX_BASE)
//
//
///** LPIT - Size of Registers Arrays */
//#define LPIT_TMR_COUNT                           4u
//
//
//// VERID Reg
//typedef union LPIT_VERID_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 FEATURE : 16;
//		volatile uint32 MINOR : 8;
//		volatile uint32 MAJOR : 8;
//	}Bit;
//}tuCddAdc_LPIT_VERID_Reg;
//
//// PARAM Reg
//typedef union LPIT_PARAM_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 CHANNEL : 8;
//		volatile uint32 EXT_TRIG : 8;
//		volatile uint32 Reserved_0 : 16;
//	}Bit;
//}tuCddAdc_LPIT_PARAM_Reg;
//
//// MCR Reg
//typedef union LPIT_MCR_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 M_CEN : 1;
//		volatile uint32 SW_RST : 1;
//		volatile uint32 DOZE_EN : 1;
//		volatile uint32 DBG_EN : 1;
//		volatile uint32 Reserved_0 : 28;
//	}Bit;
//}tuCddAdc_LPIT_MCR_Reg;
//
//// MSR Reg
//typedef union LPIT_MSR_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 TIF0 : 1;
//		volatile uint32 TIF1 : 1;
//		volatile uint32 TIF2 : 1;
//		volatile uint32 TIF3 : 1;
//		volatile uint32 Reserved_0 : 28;
//	}Bit;
//}tuCddAdc_LPIT_MSR_Reg;
//
//// MIER Reg
//typedef union LPIT_MIER_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 TIE0 : 1;
//		volatile uint32 TIE1 : 1;
//		volatile uint32 TIE2 : 1;
//		volatile uint32 TIE3 : 1;
//		volatile uint32 Reserved_0 : 28;
//	}Bit;
//}tuCddAdc_LPIT_MIER_Reg;
//
//// SETTEN Reg
//typedef union LPIT_SETTEN_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 SET_T_EN_0 : 1;
//		volatile uint32 SET_T_EN_1 : 1;
//		volatile uint32 SET_T_EN_2 : 1;
//		volatile uint32 SET_T_EN_3: 1;
//		volatile uint32 Reserved_0 : 28;
//	}Bit;
//}tuCddAdc_LPIT_SETTEN_Reg;
//
//// CLRTEN Reg
//typedef union LPIT_CLRTEN_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 CLR_T_EN_0 : 1;
//		volatile uint32 CLR_T_EN_1 : 1;
//		volatile uint32 CLR_T_EN_2 : 1;
//		volatile uint32 CLR_T_EN_3: 1;
//		volatile uint32 Reserved_0 : 28;
//	}Bit;
//}tuCddAdc_LPIT_CLRTEN_Reg;
//
//// TMRn_TVAL Reg
//typedef union LPIT_TVALn_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 TMR_VAL : 32;
//	}Bit;
//}tuCddAdc_LPIT_TVALn_Reg;
//
//// TMRn_CVAL Reg
//typedef union LPIT_CVALn_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 TMR_CUR_VAL : 32;
//	}Bit;
//}tuCddAdc_LPIT_CVALn_Reg;
//
//// TMRn_TCTRL Reg
//typedef union LPIT_TCTRLn_tag
//{
//	volatile uint32 Reg;
//	struct
//	{
//		volatile uint32 T_EN : 1;
//		volatile uint32 CHAN : 1;
//		volatile uint32 MODE : 2;
//		volatile uint32 Reserved_2 : 12;
//		volatile uint32 TSOT : 1;
//		volatile uint32 TSOI : 1;
//		volatile uint32 TROT : 1;
//		volatile uint32 Reserved_1 : 4;
//		volatile uint32 TRG_SRC : 1;
//		volatile uint32 TRG_SEL : 4;
//		volatile uint32 Reserved_0 : 4;
//	}Bit;
//}tuCddAdc_LPIT_TCTRLn_Reg;
//
//// Timer n Regs
//typedef struct LPIT_TMRn_tag									/* offset: 0x20, array step: 0x10 */
//{
//	volatile tuCddAdc_LPIT_TVALn_Reg 	TVAL;						/**< Timer Value Register, array offset: 0x20, array step: 0x10 */
//	volatile const tuCddAdc_LPIT_CVALn_Reg 	CVAL;			/**< Current Timer Value, array offset: 0x24, array step: 0x10 */
//	volatile tuCddAdc_LPIT_TCTRLn_Reg	TCTRL;					/**< Timer Control Register, array offset: 0x28, array step: 0x10 */
//	volatile uint8 Reserved_0[4];
//}tsCdd_LpitTmrnReg;
//
///** LPIT - Register Layout Typedef */
//typedef struct {
//  volatile const tuCddAdc_LPIT_VERID_Reg VERID;   				/**< Version ID Register, offset: 0x0 */
//  volatile const tuCddAdc_LPIT_PARAM_Reg PARAM;           /**< Parameter Register, offset: 0x4 */
//  volatile tuCddAdc_LPIT_MCR_Reg MCR;                     /**< Module Control Register, offset: 0x8 */
//  volatile tuCddAdc_LPIT_MSR_Reg MSR;                     /**< Module Status Register, offset: 0xC */
//  volatile tuCddAdc_LPIT_MIER_Reg MIER;                   /**< Module Interrupt Enable Register, offset: 0x10 */
//  volatile tuCddAdc_LPIT_SETTEN_Reg SETTEN;               /**< Set Timer Enable Register, offset: 0x14 */
//  volatile tuCddAdc_LPIT_CLRTEN_Reg CLRTEN;               /**< Clear Timer Enable Register, offset: 0x18 */
//  volatile uint8 Reserved_0[4];
//	volatile tsCdd_LpitTmrnReg TMR[LPIT_TMR_COUNT];				  /**< TMR Registers*//* LPIT - Peripheral instance base addresses */
//} tsCddAdc_LpitReg;
//
///* LPIT - Peripheral instance base addresses */
///** Peripheral LPIT0 base address */
//#define LPIT0_BASE                               (0x40037000u)
///** Peripheral LPIT0 base pointer */
//#define LPIT0                                    ((tsCddAdc_LpitReg *)LPIT0_BASE)
//
//#endif // CDDADC_S32K_146_REG_TYPES_2021_03_05_H_
//
////EOF
