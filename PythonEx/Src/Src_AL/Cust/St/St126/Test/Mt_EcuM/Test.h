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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================

//#include <EcuM.h>
#include "Test_Stubs.h"

//=============================================================================
// Typedefs
//=============================================================================

// Moved in Test_Stubs.h to solve build issues

//=============================================================================
// Defines
//=============================================================================

#define ECUM_RAM_PORTS_NR             2u
#define ECUM_ECC_ERROR_ENABLE         20212022u
#define ECUM_NVM_RETRY_MAXIMUM_NR     1u
//#define ECUM_COMMUNICATION_DISABLE   FALSE
//#define ECUM_COMMUNICATION_ENABLE     TRUE
#define ECUM_LGM_TRUE     0xAAU
#define ECUM_LGM_FALSE    0x55U

#define ECUM_CFG_SHUTDOWN_PREP_TIMEOUT_MS               200u
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
#define ECUM_CHANGE_SLEEP_TIME_OUT_HOOK_ACTIVATION      20212022u

//=============================================================================
// Module global variables
//=============================================================================

extern CONST_AL tpInitFunction EcuM_StartupTwo_NonTrusted_FunctionList[];
extern CONST_AL tpInitFunction EcuM_StartupTwo_Trusted_FunctionList[];
extern CONST_AL tpInitFunction EcuM_DriverInitZero_FunctionList[];
extern CONST_AL tpInitFunction EcuM_DriverInitOne_FunctionList[];
extern CONST_AL tsEcuM_InterruptCfg EcuM_InterruptCfg_List[];
extern CONST_AL uint8 EcuM_InterruptEnbl_List[];
extern CONST_AL uint8 EcuM_InterruptDis_List[];
extern boolean EcuM_boDiagReqReset;
extern teEcuM_ChargePumpState EcuM_eChargePumpState;
extern tsEcuM_ResetReason EcuM_sEcuInternalResetReason;
extern boolean EcuM_boTriggerNvmWrite;
extern teEcuM_EcuState EcuM_eState;
extern uint8 EcuM_aucUser[1u];
extern uint8 EcuM_aucUser[1u];
extern uint32 EcuM_ulRunRequestCnt;
extern uint32 EcuM_ulPostRunRequestCnt;
extern TIMER EcuM_ulShutDownPrep_us;
extern TIMER EcuM_ulShutDownp_us;
extern boolean EcuM_boFlashCrcFailure;
extern volatile uint32 EcuM_ulMcuPrivStatus;
extern volatile uint32 EcuM_ulHardFaultErrCnt;
extern volatile uint8_least EcuM_ucMPUSelfTestErrCnt;
extern volatile uint32 EcuM_ulRegion0Word2_DefaultValue;
extern volatile uint32 EcuM_ulMPUSelfTestEnable;
extern tsEcuM_MPUSelfTestDetails EcuM_sMpuErrState;
extern MPU_Type  Mpu;
extern MCM_Type  Mcm;
extern ERM_Type  Erm;
extern FTFC_Type FTFC_sReg;
extern EIM_Type  Eim;
extern SCG_Type  Scg;
extern uint32 ulEcuM_ExternalWadg;
extern uint32 EcuM_ulShaDataEccMemLocation;
extern uint32 EcuM_ulShaDataCrcAppLocation;
extern volatile uint32 EcuM_ulECC_RAM_SEC_TestEnable;
extern volatile uint32 EcuM_ulECC_RAM_DED_TestEnable;
extern volatile uint32 EcuM_ulECC_FLASH_DED_TestEnable;
extern volatile uint32 EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt;
extern volatile uint32 EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt;
extern volatile uint32 EcuM_ulECC_RAM_L_DED_Irq_ErrCnt;
extern volatile uint32 EcuM_ulECC_RAM_U_DED_Irq_ErrCnt;
extern volatile uint32 EcuM_ulECC_Flash_NCE_Irq_ErrCnt;
extern volatile uint32 EcuM_ulECC_DED_Reset_Inhib_TestEnable;
extern volatile tuEcuM_MpuSelf_Test_Res EcuM_uMpu_SelfTest_State;
extern volatile uint32 EcuM_ulMPU_Fault_Hook_Addr;
extern volatile uint8_least EcuM_ucEccCntDummy;
extern volatile  uint16 EcuM_unShaData_Clk_Cfg_Fail;
extern uint16 EcuM_ShaDataMem[];
extern uint16 ulEcuM_Mpu_SelfTest[];
extern uint16 EcuM_unShaData_Wdg_Hook_Enbl;

const Port_ConfigType Port_ConfigData;
const Pwm_SpecificType Pwm_Config;
const LPTMR_SpecificType LPTMR_Config;
const SysCrc_SpecificType SysCrc_Config;

CONST_AL tsAdc_CfgData Adc_sAdcCfgData;
CONST_AL tsIcu_SpecificType sIcu_Config;
CONST_AL tsPdb_CfgData Pdb_sPdbDatatCfg;
CONST_AL tsTrigMux_CfgData TrigMux_sTrigMuxDatatCfg;
CONST_AL tsLpit_CfgData Lpit_sLpitDatatCfg;
boolean  boShutDownStatus = TRUE;
boolean  boShutDownStartStatus = TRUE;
boolean  boBsiInstantSleepStatus = TRUE;
boolean  boNvmWriteStatus = TRUE;
boolean  boResetTimerStatus = TRUE;
boolean  ucCounter = 0u;
uint8_least  ucCounter1 = 0u;
uint8_least  ulBusFaultCnt_Last = 0u;
uint8    ucNvMWrRetryCnt = 0u;
uint8 EcuM_WaitNvMReady_WhileTestMode = 0u;
boolean EcuM_boTriggerHardFault_MPUST1 = FALSE;
boolean EcuM_boUpdateMPUReg_MPUST1 = FALSE;
boolean EcuM_boTriggerHardFault_MPUST2 = FALSE;
boolean EcuM_boUpdateMPUReg_MPUST2 = FALSE;
boolean EcuM_boTriggerHardFault_MPUST3 = FALSE;
boolean EcuM_boUpdateMPUReg_MPUST3 = FALSE;
boolean EcuM_boTriggerHardFault_MPUST4 = FALSE;
boolean EcuM_boUpdateMPUReg_MPUST4 = FALSE;
boolean EcuM_boTriggerHardFault_MPUST5 = FALSE;
boolean EcuM_boUpdateMPUReg_MPUST5 = FALSE;
boolean EcuM_boTriggerHardFault_MPUST6 = FALSE;
boolean EcuM_boUpdateMPUReg_MPUST6 = FALSE;
boolean EcuM_boTriggerHardFault_MPUST7 = FALSE;
boolean EcuM_boUpdateMPUReg_MPUST7 = FALSE;
boolean EcuM_boTriggerHardFault_MPUST8 = FALSE;
boolean EcuM_boUpdateMPUReg_MPUST8 = FALSE;
boolean EcuM_boTriggerSEC_ISR_Test = FALSE;
boolean EcuM_boTriggerDED_ISR_Test = FALSE;
boolean EcuM_boTriggerFNCE_ISR_Test = FALSE;

//hook test
extern uint32 EcuM_ulChangeSbcSleep_Timeout_Hook;

//=============================================================================
// Module function declarations
//=============================================================================

//=============================================================================
// Module function parameter stubs
//=============================================================================

tsEcuM_MPUSelfTestDetails EcuM_mpu_SelfTest_GestMpuHwStatus_Param1;
AppModeType               EcuM_StartOS_Param1;
uint16                    EcuM_WaitNvMReady_Param1;
uint8                     EcuM_RequestRUN_Param1;
uint8                     EcuM_RequestPOST_RUN_Param1;
uint8                     EcuM_ReleaseRUN_Param1;
uint8                     EcuM_ReleasePOST_RUN_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

uint8                 EcuM_PLLUnlockSelfTest_RetVal;
uint8                 EcuM_UnusedOpcodeSelfTest_RetVal;
uint8                 EcuM_ECCSelfTest_RetVal;
boolean               EcuM_WaitNvMReady_RetVal;
NvM_RequestResultType EcuM_HandleNvmWrite_RetVal;
boolean               EcuM_NvmWrite_RetVal;
uint8                 EcuM_MPUSelfTest_RetVal;
uint8                 EcuM_McuSelfTest_RetVal;
boolean               EcuM_ClockCfg_Consistency_Check_RetVal;


#endif // TEST_2023_08_25_H_
