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
/// \file  EcuM_Cfg.h
///
/// \brief Ecu Manager configuration header file
///
/// \Project LDMO
///
/// \Author Stefan Tyirean (f75617c) mailto: stefan.tyirean[a]marelli.com
///
/// \Date September 2021
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "EcuM_Mac.h"
#include <Cfg/Cfg.h>
#ifndef UNIT_TEST
#include <Os_MemMap.h>
#endif


#ifndef UNIT_TEST
#define ECUM_SHA_DATA_MEM_ADDRESS_START  (volatile uint32)(m_data_shared_start)
#define ECUM_SHA_DATA_MEM_ADDRESS_LIMIT  (volatile uint32)(m_data_shared_limit)
#define ECUM_ECC_DED_ERROR_MEM          *(volatile uint16*)0x20002F40u
#define ECUM_CRC_APPL_ERROR_MEM         *(volatile uint16*)0x20002F48u
#define ECUM_CLOCK_CFG_ERROR_MEM        *(volatile uint16*)0x20002F4Au
#define ECUM_MPU_CNT_ERROR_MEM          *(volatile uint16*)0x20002F4Eu
#define ECUM_H_FAULT_ERROR_MEM          *(volatile uint16*)0x20002F50u
#if (CFG_DEV_HOOK_EN == 1u)
#define ECUM_WDG_SPECIAL_HOOK_ENBL      *(volatile uint16*)0x20002F54u
#endif
#define ECUM_START_ERROR_MEM            0x20002F40u
#endif

#define ECUM_FAIL_VAL                 0x5A01u
#define ECUM_SELFTEST_STATUS          STD_ON

#if (ECUM_SELFTEST_STATUS == STD_ON)
#define ECUM_SELFTEST_MPU             STD_ON
#define ECUM_SELFTEST_ECC             STD_ON
#define ECUM_SELFTEST_UNUSED_OPCODE   STD_OFF
#define ECUM_SELFTEST_PLL_UNLOCK      STD_OFF
#define ECUM_SELFTEST_PASS            0x0u
#define ECUM_SELFTEST_FAIL            0x1u
#else
#define ECUM_SELFTEST_MPU             STD_OFF
#define ECUM_SELFTEST_ECC             STD_OFF
#define ECUM_SELFTEST_UNUSED_OPCODE   STD_OFF
#define ECUM_SELFTEST_PLL_UNLOCK      STD_OFF
#endif

#if (ECUM_SELFTEST_ECC == STD_ON) && !defined(UNIT_TEST)
#define ECUM_ECC_SELF_TEST_ERROR_MEM      *(volatile uint16*)0x20002F4Cu
#endif

#if (ECUM_SELFTEST_MPU == STD_ON)
#ifndef UNIT_TEST
#define ECUM_MPU_SELFTEST_FAIL_EVENT_MEM   *(volatile uint16*)0x20002F44u
#define ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS  (volatile uint32)(m_data_selftest1_start)
#define ECUM_RAM_MEMORY_END_PRIV_USER_RWX_PROHIBITED_ACCESS    ((volatile uint32)m_data_selftest1_limit-1u)
#define ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS        (volatile uint32)(m_data_selftest2_start)
#define ECUM_RAM_MEMORY_END_USER_WX_PROHIBITED_ACCESS          ((volatile uint32)m_data_selftest2_limit-1u)
#endif
#endif



#if defined(UNIT_TEST)
uint16 ulEcuM_Mpu_SelfTest[100];
uint32 ulEcuM_ExternalWadg;
uint32 EcuM_ulShaDataEccMemLocation;
uint32 EcuM_ulShaDataCrcAppLocation;
uint16 EcuM_unShaData_Clk_Cfg_Fail;
uint16 EcuM_unShaData_Wdg_Hook_Enbl;
uint16 EcuM_unShaData_Mpu_Cnt_Fail;
uint16 EcuM_unShaData_H_Fault_Fail;
uint16 EcuM_unEcc_SelfTest_Fault_Fail;
uint16 EcuM_ShaDataMem[100u];
#define ECUM_CLOCK_CFG_ERROR_MEM      EcuM_unShaData_Clk_Cfg_Fail
#define ECUM_MPU_CNT_ERROR_MEM        EcuM_unShaData_Mpu_Cnt_Fail
#define ECUM_H_FAULT_ERROR_MEM        EcuM_unShaData_H_Fault_Fail
#define ECUM_ECC_DED_ERROR_MEM        EcuM_ulShaDataEccMemLocation
#define ECUM_CRC_APPL_ERROR_MEM       EcuM_ulShaDataCrcAppLocation
#define ECUM_ECC_SELF_TEST_ERROR_MEM  EcuM_unEcc_SelfTest_Fault_Fail
#define ECUM_MPU_SELFTEST_FAIL_EVENT_MEM  ulEcuM_Mpu_SelfTest[98]
#define ECUM_SHA_DATA_MEM_ADDRESS_START  (uint32)&EcuM_ShaDataMem[0]
#define ECUM_SHA_DATA_MEM_ADDRESS_LIMIT  (uint32)&EcuM_ShaDataMem[99] + 4u
#define ECUM_MPU_SELFTEST_FAIL_VAL                            20u
#define ECUM_WDG_SPECIAL_HOOK_ENBL                            EcuM_unShaData_Wdg_Hook_Enbl
#define ECUM_START_ERROR_MEM                                  (uint32)&EcuM_ShaDataMem[32];
#define ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS (volatile uint32)&ulEcuM_Mpu_SelfTest[0]
#define ECUM_RAM_MEMORY_END_PRIV_USER_RWX_PROHIBITED_ACCESS   (volatile uint32)&ulEcuM_Mpu_SelfTest[0]
#define ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS       (volatile uint32)&ulEcuM_Mpu_SelfTest[0]
#define ECUM_RAM_MEMORY_END_USER_WX_PROHIBITED_ACCESS         (volatile uint32)&ulEcuM_Mpu_SelfTest[0]
#define ECUM_EXTERNAL_WADG                                    ulEcuM_ExternalWadg
#endif

#ifndef UNIT_TEST
#define ECUM_EXTERNAL_WADG                                    0x20002F46
#endif


//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define ECUM_SAFE_WARN_POS_USER                         STD_ON
#define ECUM_CFG_NVM_READY_TIMEOUT_US                   6500u
#define ECUM_CFG_SBC_SLEEP_TIMEOUT_MS                   50u
#if (CFG_DEV_HOOK_EN == 1u) || defined(UNIT_TEST)
#define ECUM_CFG_SBC_SLEEP_TIMEOUT_MS_HOOK              5000u
#endif
#define ECUM_CFG_SHUTDOWN_PREP_TIMEOUT_MS               350u
#define ECUM_LIFEPHASE_USER_NR                          2u
#define ECUM_LIFEPHASE_NM_USER                          0u
#define ECUM_USER_REQUEST_RUN_MASK                      0x0Fu
#define ECUM_USER_REQUEST_POST_RUN_MASK                 0xF0u
#define ECUM_IRQ_LPIT0_Ch0                              48u
#define ECUM_IRQ_LPIT0_Ch1                              49u
#define ECUM_IRQ_CAN0_ORed                              78u
#define ECUM_IRQ_CAN0_ORed_0_15_MB                      81u
#define ECUM_IRQ_CAN0_ORed_16_31_MB                     82u
#define ECUM_IRQ_PDB0                                   52u
#define ECUM_IRQ_PDB1                                   68u
#define ECUM_IRQ_DMA8                                    8u
#define ECUM_IRQ_ERM_SBC                                44u
#define ECUM_IRQ_ERM_NCE                                45u
#define ECUM_IRQ_FTFC_NCE                               21u
#define ECUM_IRQ_LPTMR                                  58u
#define ECUM_IRQ_PRIORITY_4                              4u
#define ECUM_IRQ_PRIORITY_1                              1u

//-----------------------------------------------------------------------------
// Configurations
//-----------------------------------------------------------------------------

BEGIN_ECUM_INIT_SEQUENCE

//-----------------------------------------------------------------------------
//                     DriverInitZero sequence
//-----------------------------------------------------------------------------

  DRIVER_INIT_ZERO(EcuM_SetActiveApplication)

//-----------------------------------------------------------------------------
//                     DriverInitOne sequence
//-----------------------------------------------------------------------------
  DRIVER_INIT_ONE(riFee_Init)
  DRIVER_INIT_ONE(EcuM_McuInit)
  DRIVER_INIT_ONE(EcuM_PortInit)
  DRIVER_INIT_ONE(EcuM_WdgInit)
  DRIVER_INIT_ONE(EcuM_LptmrInit)
  DRIVER_INIT_ONE(CddDma_Init)
  DRIVER_INIT_ONE(EcuM_AdcInit)
  DRIVER_INIT_ONE(EcuM_PdbInit)
  DRIVER_INIT_ONE(EcuM_TrigMuxInit)
  DRIVER_INIT_ONE(EcuM_LpitInit)

//-----------------------------------------------------------------------------
//                     StartupTwo sequence
//-----------------------------------------------------------------------------

  STARTUP_TWO_NON_TRUSTED(riNvM_Init)
  STARTUP_TWO_NON_TRUSTED(NvM_ReadAll)
  STARTUP_TWO_NON_TRUSTED(EcuM_WaitForNvMReadAllReady)
  STARTUP_TWO_NON_TRUSTED(riDem_Init)
  STARTUP_TWO_NON_TRUSTED(riErrCust_Init)
  STARTUP_TWO_TRUSTED(IoHwAbUser_InitGetMountingSide)   // Mounting side needs to be detected before Dem/ErrCust init - fix for bugfix/LDMO-2198
  STARTUP_TWO_TRUSTED(CddSpi_Init)
#ifdef CPU_S32K146
  STARTUP_TWO_TRUSTED(CddUart_Init)
#endif
  STARTUP_TWO_TRUSTED(CddSbc_Init)
  STARTUP_TWO_TRUSTED(EcuM_PwmInit)
  STARTUP_TWO_TRUSTED(EcuM_IcuInit)
  //STARTUP_TWO_TRUSTED(SysVolt_Init)
  STARTUP_TWO_TRUSTED(EcuM_SysCrcInit)
#ifdef CPU_S32K146
  STARTUP_TWO_NON_TRUSTED(CddStp_Tsp_Init)
#endif
  STARTUP_TWO_TRUSTED(EcuM_Enable_ChargePump)

#ifdef CPU_S32K146
  INTERRUPT_CFG(ECUM_IRQ_LPIT0_Ch0, ECUM_IRQ_PRIORITY_1)
#endif
  INTERRUPT_CFG(ECUM_IRQ_LPIT0_Ch1, ECUM_IRQ_PRIORITY_4)
  INTERRUPT_CFG(ECUM_IRQ_CAN0_ORed, ECUM_IRQ_PRIORITY_4)
  INTERRUPT_CFG(ECUM_IRQ_CAN0_ORed_0_15_MB, ECUM_IRQ_PRIORITY_4)
  INTERRUPT_CFG(ECUM_IRQ_CAN0_ORed_16_31_MB, ECUM_IRQ_PRIORITY_4)
  INTERRUPT_CFG(ECUM_IRQ_PDB0, ECUM_IRQ_PRIORITY_4)
  INTERRUPT_CFG(ECUM_IRQ_PDB1, ECUM_IRQ_PRIORITY_4)
  INTERRUPT_CFG(ECUM_IRQ_DMA8, ECUM_IRQ_PRIORITY_4)
  INTERRUPT_CFG(ECUM_IRQ_ERM_SBC, ECUM_IRQ_PRIORITY_1)
  INTERRUPT_CFG(ECUM_IRQ_ERM_NCE, ECUM_IRQ_PRIORITY_1)
  INTERRUPT_CFG(ECUM_IRQ_FTFC_NCE, ECUM_IRQ_PRIORITY_1)
  INTERRUPT_CFG(ECUM_IRQ_LPTMR, ECUM_IRQ_PRIORITY_4)

#ifdef CPU_S32K146
  INTERRUPT_ENABLE(ECUM_IRQ_LPIT0_Ch0)
#endif
  INTERRUPT_ENABLE(ECUM_IRQ_LPIT0_Ch1)
  INTERRUPT_ENABLE(ECUM_IRQ_CAN0_ORed)
  INTERRUPT_ENABLE(ECUM_IRQ_CAN0_ORed_0_15_MB)
  INTERRUPT_ENABLE(ECUM_IRQ_CAN0_ORed_16_31_MB)
  INTERRUPT_ENABLE(ECUM_IRQ_PDB0)
  INTERRUPT_ENABLE(ECUM_IRQ_PDB1)
  INTERRUPT_ENABLE(ECUM_IRQ_DMA8)
  INTERRUPT_ENABLE(ECUM_IRQ_ERM_SBC)
  INTERRUPT_ENABLE(ECUM_IRQ_ERM_NCE)
  INTERRUPT_ENABLE(ECUM_IRQ_FTFC_NCE)
  INTERRUPT_ENABLE(ECUM_IRQ_LPTMR)

//-----------------------------------------------------------------------------
// End of the EcuM init sequence config
//-----------------------------------------------------------------------------

END_ECUM_INIT_SEQUENCE

// EOF
