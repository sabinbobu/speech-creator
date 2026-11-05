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
/// \file  EcuM.c
///
/// \brief Ecu Manager functionality defines
///
/// \Project LDMO
///
/// \Author Stefan Tyirean mailto: stefan.tyirean[at]marelli.com
///
/// \Date September 2021
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include <Cfg/Cfg.h>
#include <Bsw/IoHwAb/IoHwAbUser.h>
#include <Bsw/WdgM/WdgM.h>
#include <EcuM_Types.h>
#include <ErrCust.h>
#include <Dem.h>
#include <Dio.h>
#include <Pwm.h>
#include <Mcu.h>
#include <LPTMR.h>
#include <EcuM.h>
#include <CddDma.h>
#include <CddSpi.h>
#include <CddSbc.h>
#include <CddBoost.h>
#include <Adc.h>
#include <Pdb.h>
#include <Lpit.h>
#include <TrigMux.h>
#include <SysCrc.h>

#include <Fee.h>
#include <Nvm.h>
#include <Util_Time.h>

#include <SysMonRx.h>
#include <SysMonTx.h>
#include <SysMonRx_ASIL.h>


#ifndef UNIT_TEST
#include <Port.h>
#include <Icu.h>
#include <Rte.h>
#include <Os_Main.h>
#include <interrupt_manager.h>
#include <s32_core_cm4.h>
#include <Swc/StatM/StatM.h>
#else
#include <Device_TargetTypes.h>
#endif

#ifdef SAMPLE_FULL
  #include <CddUart.h>
  #include <CddTpsGen2.h>
  #include <CddTpsGen3.h>
  #include <CddStp_Tsp.h>
  #include <S32K146.h>
#elif defined(SAMPLE_ECO)
  #include <S32K144.h>
#else
#endif

// PRQA S 3408 1 // program architecture and readability
const volatile uint32 config_flash[4] __attribute__((used, section(".flash_config"))) = 
{
  0xFFFFFFFFu,     /* 8 bytes backdoor comparison key           */
  0xFFFFFFFFu,     /*                                           */
  0xFFFFFFFFu,     /* 4 bytes program flash protection bytes    */
  0xFFFF7FFEu      /* FDPROT:FEPROT:FOPT:FSEC(0xFE = unsecured) */
};

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

#define ECUM_RAM_PORTS_NR             2u
#define ECUM_ECC_ERROR_ENABLE         20212022u
#define ECUM_NVM_RETRY_MAXIMUM_NR     1u
#define ECUM_LGM_TRUE     0xAAU
#define ECUM_LGM_FALSE    0x55U

//-----------------------------------------------------------------------------
// extending Ecum configurations
//-----------------------------------------------------------------------------

#define ECUM_MAC_DECL_INIT
#include "EcuM_Cfg.h"
#undef ECUM_MAC_DECL_INIT

#define ECUM_MAC_DRIVER_INIT_ZERO_FPTR_LIST
#include "EcuM_Cfg.h"
#undef ECUM_MAC_DRIVER_INIT_ZERO_FPTR_LIST

#define ECUM_MAC_DRIVER_INIT_ONE_FPTR_LIST
#include "EcuM_Cfg.h"
#undef ECUM_MAC_DRIVER_INIT_ONE_FPTR_LIST

#define ECUM_MAC_STARTUP_TWO_TRUSTED_FPTR_LIST
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_TWO_TRUSTED_FPTR_LIST

#define ECUM_MAC_STARTUP_TWO_NON_TRUSTED_FPTR_LIST
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_TWO_NON_TRUSTED_FPTR_LIST

#define ECUM_MAC_DRIVER_INIT_ZERO_ID
#include "EcuM_Cfg.h"
#undef ECUM_MAC_DRIVER_INIT_ZERO_ID

#define ECUM_MAC_DRIVER_INIT_ONE_ID
#include "EcuM_Cfg.h"
#undef ECUM_MAC_DRIVER_INIT_ONE_ID

#define ECUM_MAC_STARTUP_TWO_TRUSTED_ID
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_TWO_TRUSTED_ID

#define ECUM_MAC_STARTUP_TWO_NON_TRUSTED_ID
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_TWO_NON_TRUSTED_ID

#define ECUM_MAC_STARTUP_INT_CFG
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_INT_CFG

#define ECUM_MAC_STARTUP_INT_ENBL
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_INT_ENBL

#define ECUM_MAC_STARTUP_INT_DISABLE
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_INT_DISABLE

#define ECUM_MAC_STARTUP_INT_CFG_ID
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_INT_CFG_ID

#define ECUM_MAC_STARTUP_INT_ENBL_ID
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_INT_ENBL_ID

#define ECUM_MAC_STARTUP_INT_DISABLE_ID
#include "EcuM_Cfg.h"
#undef ECUM_MAC_STARTUP_INT_DISABLE_ID

#define ECUM_MPU_SELF_TEST_RESULT_NA         0u
#define ECUM_MPU_SELF_TEST_RESULT_PASS       1u
#define ECUM_MPU_SELF_TEST_RESULT_FAIL       2u
#define ECUM_CRC_APP_CYCLIC_CHECK_TIME_MS   50u
#define ECUM_MPU_CYCLIC_CHECK_TIME_MS      100u


//-----------------------------------------------------------------------------
// prototypes
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_OnStateStartup                      (void);
STATIC_AL void EcuM_AL_InterruptCfg                     (void);
STATIC_AL void EcuM_AL_InterruptEnable                  (void);
STATIC_AL void EcuM_AL_DriverInitOne                    (void);
STATIC_AL void EcuM_AL_DriverInitZero                   (void);
STATIC_AL void EcuM_SetResetReason                      (void);
STATIC_AL void EcuM_StartOS                             (AppModeType Mode);
STATIC_AL void EcuM_OnStateUp                           (void);
STATIC_AL void EcuM_OnStateShutDownPrep                 (void);
STATIC_AL void EcuM_OnStateShutDown                     (void);
STATIC_AL void EcuM_EnterPrep_Shutdown                  (void);
STATIC_AL void EcuM_ExitPrep_Shutdown                   (void);
STATIC_AL void EcuM_Enter_Shutdown                      (void);
STATIC_AL void EcuM_Up_HandleTransitions                (void);
STATIC_AL void EcuM_StartUp_HandleTransitions           (void);
STATIC_AL void EcuM_ShutDown_HandleTransitions          (void);
STATIC_AL NvM_RequestResultType EcuM_HandleNvmWrite     (void);
STATIC_AL boolean EcuM_NvmWrite                         (void);
STATIC_AL void EcuM_ShutDownPrep_HandleTransitions      (void);
STATIC_AL void EcuM_Evaluate_RequestPostRun_Condtion    (void);
STATIC_AL boolean EcuM_WaitNvMReady                     (uint16 unBlockNumber);
STATIC_AL boolean EcuM_CheckNonCorectableMemErrors      (void);


LOCAL_INLINE boolean EcuM_GetRequestRunStatus          (uint8 ucUser);
LOCAL_INLINE boolean EcuM_GetReleaseRunStatus          (uint8 ucUser);
LOCAL_INLINE boolean EcuM_GetRequestPostRunStatus      (uint8 ucUser);
LOCAL_INLINE boolean EcuM_GetReleasePostRunStatus      (uint8 ucUser);

STATIC_AL void EcuM_GetMcuPrivilegeStatus             (void);
STATIC_AL void EcuM_UserSwitch                        (void);
STATIC_AL void EcuM_PrivilegeSwitch                   (void);

STATIC_AL void EcuM_Invalidate_Shutdown               (void);
STATIC_AL void EcuM_Evaluate_ReleasePostRun_Condtion  (void);
STATIC_AL void EcuM_Check_MPU_Errors                  (void);

STATIC_AL void EcuM_ECCProtEnable                     (void);

STATIC_AL void EcuM_Inject_RAM_SEC_ECCError           (void);
STATIC_AL void EcuM_Inject_RAM_DED_ECCError           (void);
STATIC_AL void EcuM_Inject_FLASH_DED_ECCError         (void);
STATIC_AL void EcuM_DED_Error_Reaction                (void);
STATIC_AL void EcuM_CheckAppCrc                       (void);
STATIC_AL void EcuM_InitShaDataMem                    (void);
STATIC_AL boolean EcuM_ClockCfg_Consistency_Check     (void);


#if (ECUM_SELFTEST_STATUS == STD_ON)
STATIC_AL uint8 EcuM_McuSelfTest(void);
#endif

STATIC_AL volatile uint32 EcuM_ulECC_RAM_SEC_TestEnable   = 0u;
STATIC_AL volatile uint32 EcuM_ulECC_RAM_DED_TestEnable   = 0u;
STATIC_AL volatile uint32 EcuM_ulECC_FLASH_DED_TestEnable = 0u;
STATIC_AL volatile uint32 EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 0u;
STATIC_AL volatile uint32 EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 0u;
STATIC_AL volatile uint32 EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 0u;
STATIC_AL volatile uint32 EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 0u;
STATIC_AL volatile uint32 EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 0u;
STATIC_AL volatile uint32 EcuM_ulECC_DED_Reset_Inhib_TestEnable = 0u;

STATIC_AL volatile tuEcuM_MpuSelf_Test_Res EcuM_uMpu_SelfTest_State;

#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_MPU_SelfTest_Fail_Reaction(void);
STATIC_AL void EcuM_MPU_SelfTest_MPU_Config(void);
STATIC_AL void EcuM_MPU_SelfTest_GetDefaultReg0W2(void);
STATIC_AL void EcuM_MPU_SelfTest_RestoreDefaultReg0W2(void);
STATIC_AL void EcuM_mpu_SelfTest_GestMpuHwStatus(tsEcuM_MPUSelfTestDetails* sMpuErrStat);

STATIC_AL void EcuM_MPU_SelfTest_Test_1 (void);
STATIC_AL void EcuM_MPU_SelfTest_Test_2 (void);
STATIC_AL void EcuM_MPU_SelfTest_Test_3 (void);
STATIC_AL void EcuM_MPU_SelfTest_Test_4 (void);
STATIC_AL void EcuM_MPU_SelfTest_Test_5 (void);
STATIC_AL void EcuM_MPU_SelfTest_Test_6 (void);
STATIC_AL void EcuM_MPU_SelfTest_Test_7 (void);
STATIC_AL void EcuM_MPU_SelfTest_Test_8 (void);
STATIC_AL uint8 EcuM_MPUSelfTest        (void);
#endif


#if (ECUM_SELFTEST_ECC == STD_ON) || defined(UNIT_TEST)
STATIC_AL uint8 EcuM_ECCSelfTest(void);
STATIC_AL void EcuM_ECC_SelfTest_Fail_Reaction(void);
STATIC_AL void EcuM_EccSelfTest_DummyCode(void);
#endif

#if (ECUM_SELFTEST_UNUSED_OPCODE == STD_ON) || defined(UNIT_TEST)
STATIC_AL uint8 EcuM_UnusedOpcodeSelfTest(void);
STATIC_AL void EcuM_Unused_Opcode_SelfTest_Fail_Reaction(void);
#endif

#if (ECUM_SELFTEST_PLL_UNLOCK == STD_ON) || defined(UNIT_TEST)
STATIC_AL uint8 EcuM_PLLUnlockSelfTest(void);
STATIC_AL void EcuM_PLL_Unlock_SelfTest_Fail_Reaction(void);
#endif

#ifdef UNIT_TEST
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_1(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_2(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_3(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_4(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_5(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_6(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_7(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_8(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_RAM_SEC_Injection(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_RAM_DED_Injection(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_Flash_NCE_Injection(void);
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_NvM_Ready(NvM_RequestResultType *pNvmResult, uint32 *ulTime);
#endif

//-----------------------------------------------------------------------------
// global variables
//-----------------------------------------------------------------------------

STATIC_AL tsEcuM_ResetReason EcuM_sEcuInternalResetReason = { MCU_RESET_UNDEFINED, {0u} };
STATIC_AL teEcuM_ChargePumpState EcuM_eChargePumpState    = eEcuM_ChargePump_NotEnabled;
STATIC_AL boolean EcuM_boTriggerNvmWrite                  = FALSE;
STATIC_AL teEcuM_EcuState EcuM_eState                     = eEcuM_Undefined;
STATIC_AL uint8 EcuM_aucUser[ECUM_LIFEPHASE_USER_NR]      = { 0u };
STATIC_AL uint32 EcuM_ulRunRequestCnt                     = 0u;
STATIC_AL uint32 EcuM_ulPostRunRequestCnt                 = 0u;
STATIC_AL TIMER EcuM_ulShutDownPrep_us                    = 0u;
STATIC_AL TIMER EcuM_ulShutDownp_us                       = 0u;

STATIC_AL boolean EcuM_boFlashCrcFailure;

boolean EcuM_boDiagReqReset = FALSE;
STATIC_AL volatile uint32 EcuM_ulMcuPrivStatus = 0u;

#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL volatile uint32 EcuM_ulMPUSelfTestEnable = 0u;
STATIC_AL volatile uint32 EcuM_ulRegion0Word2_DefaultValue = 0u;
STATIC_AL volatile uint32 EcuM_ulHardFaultErrCnt = 0u;
STATIC_AL tsEcuM_MPUSelfTestDetails EcuM_sMpuErrState;
STATIC_AL volatile uint8_least EcuM_ucMPUSelfTestErrCnt = 0u;
#endif

#if (ECUM_SELFTEST_ECC == STD_ON)
STATIC_AL volatile uint8_least EcuM_ucEccCntDummy = 0u;
#endif

#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
#define ECUM_CHANGE_SLEEP_TIME_OUT_HOOK_ACTIVATION      20212022u
STATIC_AL volatile uint32 EcuM_ulChangeSbcSleep_Timeout_Hook = 0u;
STATIC_AL volatile uint32 EcuM_ulMPU_Fault_Hook_Addr         = 0u;
#endif

// PRQA S 3447 1 // program architecture and readability
extern uint32 Os_Get_BusFaultCnt(void);

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief EcuM_McuInit
///
/// \descr Mcu Initialization (Clocking and Pll setup)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_McuInit(void)
{
  boolean boClockCfgStatus = FALSE;
  (void)Mcu_InitClock(&Mcu_ClockData);
  (void)Mcu_DistributePllClock();

  // Check the Clocking consistency
  boClockCfgStatus = EcuM_ClockCfg_Consistency_Check();

  // Check the Clock Config Consistency
  if (boClockCfgStatus == FALSE)
  {
    // Update Share data memory with Clock Cfg Fail Reset Reason
    // PRQA S 303 1 // program architecture and readability
    ECUM_CLOCK_CFG_ERROR_MEM = ECUM_FAIL_VAL;
    // Mcu Perform Reset
    Mcu_PerformReset();
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_WdgInit
///
/// \descr Watchdog Initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_WdgInit(void)
{
  // Check if WATCHDOG reset hook is activated (multiple reset)
#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
  if (ECUM_WDG_SPECIAL_HOOK_ENBL != 0x5A01u) // PRQA S 303 1 // direct memory access
  {
    CddSbc_SetWdgTimeoutModeAnd200ms();
  }
#else
  CddSbc_SetWdgTimeoutModeAnd200ms();
#endif
}

//-----------------------------------------------------------------------------
/// \brief EcuM_PortInit
///
/// \descr Port initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_PortInit(void)
{
  Port_Init(&Port_ConfigData);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_IcuInit
///
/// \descr Icu initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_IcuInit(void)
{
  Icu_Init(&sIcu_Config);
}


//-----------------------------------------------------------------------------
/// \brief EcuM_PwmInit
///
/// \descr Pwm output initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_PwmInit(void)
{
  Pwm_Init(&Pwm_Config);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_LptmrInit
///
/// \descr Low power timer initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_LptmrInit(void)
{
  LPTMR_INIT(&LPTMR_Config);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_AdcInit
///
/// \descr Adc Initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_AdcInit(void)
{
  Adc_Init(&Adc_sAdcCfgData);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_PdbInit
///
/// \descr Programable delay block initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_PdbInit(void)
{
  Pdb_Init(&Pdb_sPdbDatatCfg);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_TrigMuxInit
///
/// \descr Trigger Multiplexer Initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_TrigMuxInit(void)
{
  TrigMux_Init(&TrigMux_sTrigMuxDatatCfg);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_LpitInit
///
/// \descr Low power interrupt timer initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_LpitInit(void)
{
  Lpit_Init(&Lpit_sLpitDatatCfg);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_SysCrcInit
///
/// \descr Hardware CRC initialization
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_SysCrcInit(void)
{
  SysCrc_RomSegs_Init(&SysCrc_Config);
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_Init
///
/// \descr  Init function of the module
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_Init(void)
{
  // Init ECC Error Counters
  EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 0u;
  EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 0u;
  EcuM_boFlashCrcFailure = FALSE;
  EcuM_uMpu_SelfTest_State.ulMpuTest_Result_Stat = 0u;

  // Set the current state of the EcuM to startup
  EcuM_eState = eEcuM_Startup;

  // Sha Data memory init - no posibly to get ECC error
  EcuM_InitShaDataMem();

  // Init driver list zero
  EcuM_AL_DriverInitZero();

  // Init driver list one
  EcuM_AL_DriverInitOne();

  // Config interrupt
  EcuM_AL_InterruptCfg();

  // Interrupt enable
  EcuM_AL_InterruptEnable();

  // Start-Up Two Trusted
  EcuM_StartupTwo_Trusted();

  // Start-Up Two Unrusted
  EcuM_StartupTwo_NonTrusted();

  // Set Mcu Reset Reason
  EcuM_SetResetReason();

  // Report watchdog reset
  EcuM_ReportWgdReset();

  // Report APP CRC reset
  EcuM_ReportAppCrcReset();

  // ECC protection enable
  EcuM_ECCProtEnable();

#if (ECUM_SELFTEST_STATUS == STD_ON)
  //Mcu Self test performing
  (void)EcuM_McuSelfTest();
#endif

  // Os start
  EcuM_StartOS((AppModeType)0);

  // Clear flag for flexible error set/clear (unconditional set/clear without DiagMuxOn Can signal with 1 value in start-up phase)
  Dem_ClearStartUpStatus();

  // PRQA S 5324 1 // program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_SetResetReason
///
/// \descr  Read the reset reason using Mcu_GetResetReason
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_SetResetReason(void)
{
 // PRQA S 306 1 // program architecture and readability
  tsEcuM_EcuInternalErrors *psShaDataHwErr = (tsEcuM_EcuInternalErrors *)ECUM_START_ERROR_MEM;

  // Get ShaData reet reason if exist
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Word                               = 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biSBC_WDG_ResetReason          = (psShaDataHwErr->unSBC_Wdg_Reset == ECUM_FAIL_VAL)        ? 1u : 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biMPU_Self_Test_ResetReason    = (psShaDataHwErr->unMpu_Self_Test_Reset == ECUM_FAIL_VAL)  ? 1u : 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biECC_DED_ResetReason          = (psShaDataHwErr->unEcc_DED_Reset == ECUM_FAIL_VAL)        ? 1u : 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason          = (psShaDataHwErr->unCRC_App_Reset == ECUM_FAIL_VAL)        ? 1u : 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biECC_Self_Test_ResetReason    = (psShaDataHwErr->unEcc_Self_Test_Reset == ECUM_FAIL_VAL)  ? 1u : 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biClock_Cfg_ResetReason        = (psShaDataHwErr->unClock_Cfg_Reset == ECUM_FAIL_VAL)      ? 1u : 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biHard_Fault_ResetReason       = (psShaDataHwErr->unHardFaultSwLock == ECUM_FAIL_VAL)      ? 1u : 0u;

  // Get Mcu Reset Reason
  EcuM_sEcuInternalResetReason.eMcuResetReason = Mcu_GetResetReason();

  // Reset BusFault Cnt
  if (EcuM_sEcuInternalResetReason.eMcuResetReason == MCU_POWER_ON_RESET)
  {
    // Reset 0x20002f4E
    psShaDataHwErr->unMPU_Bus_Fault_Cnt = 0u;
  }
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_StartupTwo_Trusted
///
/// \descr  Executes the startup twp trusted sequence defined in EcuM_Cfg.h
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_StartupTwo_Trusted(void)
{
  uint8 ucIndex;

  // Execute the initialization sequence according to the configuration done in the EcuM_Cfg.h
  for (ucIndex = 0u; ucIndex < (uint8)EcuM_Startup_Two_Trusted_Id_Count; ucIndex++)
  {
    // The function call shall be done immediately
    EcuM_StartupTwo_Trusted_FunctionList[ucIndex]();
  }
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_StartupTwo_NonTrusted
///
/// \descr  Executes the startup twp non-trusted sequence defined in EcuM_Cfg.h
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_StartupTwo_NonTrusted(void)
{
  uint8 ucIndex;

  // Execute the initialization sequence according to the configuration done in the EcuM_Cfg.h
  for (ucIndex = 0u; ucIndex < (uint8)EcuM_Startup_Two_NonTrusted_Id_Count; ucIndex++)
  {
    // The function call shall be done immediately
    EcuM_StartupTwo_NonTrusted_FunctionList[ucIndex]();
  }
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_MainFunction
///
/// \descr  Main runnable of the EcuM. Executes the current state
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_MainFunction(void)
{

  // ECC Error Staus
  boolean boECCError_Status = FALSE;

  // Checkpoint Ecum
  WdgM_SetLocalCheckPoint(1u);

  // EcuM states
  switch (EcuM_eState)
  {
  case eEcuM_Startup:
    EcuM_OnStateStartup();
    break;
  case eEcuM_Up:
    EcuM_OnStateUp();
    break;
  case eEcuM_ShutDownPrep:
    EcuM_OnStateShutDownPrep();
    break;
  case eEcuM_ShutDown:
    EcuM_OnStateShutDown();
    break;
  default:
    EcuM_eState = eEcuM_Undefined;
    break;
  }

  // ECC RAM SEC Hook Enable for SEC Error Injection
  if (EcuM_ulECC_RAM_SEC_TestEnable == ECUM_ECC_ERROR_ENABLE)
  {
    // RAM SEC Error Injection
    EcuM_Inject_RAM_SEC_ECCError();
    // Reset Hook Key value
    EcuM_ulECC_RAM_SEC_TestEnable = 0u;
  }

  // ECC RAM DED Hook Enable for DED Error Injection
  if (EcuM_ulECC_RAM_DED_TestEnable == ECUM_ECC_ERROR_ENABLE)
  {
    // RAM DED Error Injection
    EcuM_Inject_RAM_DED_ECCError();
    // Reset Hook Key value
    EcuM_ulECC_RAM_DED_TestEnable = 0u;
  }

  // ECC Flash DED Hook Enable for DED Error Injection
  if (EcuM_ulECC_FLASH_DED_TestEnable == ECUM_ECC_ERROR_ENABLE)
  {
    // Flash DED Error Injection
    EcuM_Inject_FLASH_DED_ECCError();
    // Reset Hook Key value
    EcuM_ulECC_FLASH_DED_TestEnable = 0u;
  }

  // Check the ECC Non-Corectable Error Counters and update ECC status
  boECCError_Status = EcuM_CheckNonCorectableMemErrors();

  // ECC NCE present
  if (boECCError_Status != FALSE)
  {
    // Write Share Memory data and call MCU Reset
    EcuM_DED_Error_Reaction();
  }

  // CRC over application
  EcuM_CheckAppCrc();

  // MPU Error check
  EcuM_Check_MPU_Errors();

  // PRQA S 5324 1 // program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief EcuM_DED_Error_Reaction
///
/// \descr Mcu Reaction when ECC Non-Corecatble errors are reported
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_DED_Error_Reaction(void)
{
  // Get Core Privilege level in order to update the ShareData Memory
  EcuM_GetMcuPrivilegeStatus();

  // If User
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }
#ifndef UNIT_TEST
  // Update Share data memory with ECC Reset Reason
  // PRQA S 303 1 // program architecture and readability
  ECUM_ECC_DED_ERROR_MEM = ECUM_FAIL_VAL;
#endif
  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If Privilege
  if (EcuM_ulMcuPrivStatus != 0u)
  {
    // Switch to User
    EcuM_UserSwitch();
  }

  // Check Reset Inhibit Hook
  if (EcuM_ulECC_DED_Reset_Inhib_TestEnable != ECUM_ECC_ERROR_ENABLE)
  {
    // Mcu Perform Reset
    Mcu_PerformReset();
  }
  else
  {
    // Reset Avoided
  }
}


//-----------------------------------------------------------------------------
/// \brief  EcuM_EnterPrep_Shutdown
///
/// \descr  Transitions the EcuM into Prep_Shutdown state
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_EnterPrep_Shutdown(void)
{
  // Update the EcuM state
  EcuM_eState = eEcuM_ShutDownPrep;

  // deinit the Statistics
  (void)Rte_Write_EcuM_Deinit(TRUE);
  //StatM_Deinit();

  // Set the NvM write trigger flag and trigger the writing
  EcuM_boTriggerNvmWrite = TRUE;
  (void)EcuM_NvmWrite();
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_ExitPrep_Shutdown
///
/// \descr  It is called when postrun request is released
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_ExitPrep_Shutdown(void)
{
  // Update the EcuM state
  EcuM_eState = eEcuM_Up;
  EcuM_boTriggerNvmWrite = FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_Enter_Shutdown
///
/// \descr  It is called after postrun requesr and after the NvM write has been done.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Enter_Shutdown(void)
{
  // Update the EcuM state
  EcuM_eState = eEcuM_ShutDown;
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_OnStateUp
///
/// \descr  EcuM Up state function. In case of normal behaviour 
///         this function will be called periodically by the EcuM_MainFunction
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_OnStateUp(void)
{
  TIMER ulStartTime = 0u;
  STATIC_UT(boolean, boNvmWriteStatus, FALSE);
  STATIC_UT(boolean, boResetTimerStatus, TRUE);

  if (EcuM_boDiagReqReset == FALSE)
  {
    // Call EcuM handle transition procedure
    EcuM_Up_HandleTransitions();
  }
  else
  {
    if (boResetTimerStatus != FALSE)
    {
      // Start the timer
      ulStartTime = TimerGetTick();
      // Clear Reset start flag
      boResetTimerStatus = FALSE;
    }
    else
    {
      // Wait 50ms before making the reset
      if (TimerGetTimeSince(ulStartTime) >= UTILTIME_MSEC(50u))
      {
        boResetTimerStatus = TRUE;

        // Get Nvm write status
        // PRQA S 3415 1 // No side effect
        boNvmWriteStatus = ((boNvmWriteStatus == FALSE) && (EcuM_NvmWrite() == FALSE)) ? FALSE : TRUE;

        if (boNvmWriteStatus != FALSE)
        {
          // Reset is done
          Mcu_PerformReset();
        }
        else
        {
          // Nothing to be done
        }
      }
      else
      {
        // Nothing to be done
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_Up_HandleTransitions
///
/// \descr  This function is the responsible to transition the EcuM into other states
///         after reaching the Up Run state
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Up_HandleTransitions(void)
{
  // Release Run Request reached, Save Nvm
  if (EcuM_ulRunRequestCnt == 0u)
  {
    // Prepare for Ecu ShutDown
    EcuM_EnterPrep_Shutdown();
  }
  else
  {
    // Keep Ecu Up State
  }
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_DiagResetRequest
///
/// \descr  This function is used by Diag to indicate that a reset is requested.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_DiagResetRequest(void)
{
  EcuM_boDiagReqReset = TRUE;
}


//-----------------------------------------------------------------------------
/// \brief  EcuM_OnStateShutDownPrep
///
/// \descr  EcuM state function. In case Switch to StandBy can signal request this function
///         will be requested by the EcuM_MainFunction.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_OnStateShutDownPrep(void)
{
  // Call EcuM handle transition procedure
  EcuM_ShutDownPrep_HandleTransitions();
}

//-----------------------------------------------------------------------------
/// \brief EcuM_OnStateShutDown
///
/// \descr ShutDown EcuM state handling
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_OnStateShutDown(void)
{
  EcuM_ShutDown_HandleTransitions();
}

//-----------------------------------------------------------------------------
/// \brief EcuM_NvmWrite
///
/// \descr Nvm write command handling
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean EcuM_NvmWrite(void)
{
  NvM_RequestResultType NvmWriteStatus;

  if (EcuM_boTriggerNvmWrite != FALSE)
  {
    // Trigger a write request for all NvM blocks
    NvM_WriteAll();

    // Reset the trigger flag
    EcuM_boTriggerNvmWrite = FALSE;
  }
  else
  {
    // Skip, Nvm trigger is not armed
  }

  // Handle Nvm wrinting opperation
  NvmWriteStatus = EcuM_HandleNvmWrite();

  // Return Nvm write status
  return (NvmWriteStatus == NVM_REQ_OK) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_ShutDownPrep_HandleTransitions
///
/// \descr Shut-Down Prepare handling transition routine
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_ShutDownPrep_HandleTransitions(void)
{
  // Shut-Down Start status (it is true when shut-down is triggered)
  STATIC_UT(boolean, boShutDownStartStatus, TRUE);

  // Nvm write status
  STATIC_UT(uint8, ucNvMWrRetryCnt, 0u);

  // Evaluate PostRun condition - SleepBsi (StandBy)
  EcuM_Evaluate_RequestPostRun_Condtion();

  // Shut-Down procedure start
  if (boShutDownStartStatus != FALSE)
  {
    // Get time stamp
    EcuM_ulShutDownPrep_us = TimerGetTick();
    // Clear Shut-Down start flag
    boShutDownStartStatus = FALSE;
  }
  // Shut-Down procedure ongoing
  // Nvm write procedure done
  // Time-Out of 350 ms
  else
  {
    if (TimerGetTimeSince(EcuM_ulShutDownPrep_us) >= UTILTIME_MSEC(ECUM_CFG_SHUTDOWN_PREP_TIMEOUT_MS))
    {
      // Set Shut-Down start flag
      boShutDownStartStatus = TRUE;

      // NvM Failed
      if (EcuM_NvmWrite() != FALSE)
      {
        //NVM written, turn off the writting and continue to shutdown
        EcuM_boTriggerNvmWrite = FALSE;
      }
      else
      {
        // Set the NvM write trigger flag
        EcuM_boTriggerNvmWrite = (ucNvMWrRetryCnt < ECUM_NVM_RETRY_MAXIMUM_NR) ? TRUE : FALSE;
        // Increment Counter
        ucNvMWrRetryCnt++;
      }

      // Run request (release shut-down)
      if (EcuM_ulRunRequestCnt > 0u)
      {
        // Exit preparing shut-down
        EcuM_ExitPrep_Shutdown();
        // Reset NvM retry counter
        ucNvMWrRetryCnt = 0u;
      }
      // Post-Run request (continue to SBC sleep) and there is no NwM retry
      else if ((EcuM_ulPostRunRequestCnt > 0u) && (EcuM_boTriggerNvmWrite == FALSE))
      {
        // Shut-Down enter
        EcuM_Enter_Shutdown();
      }
      else
      {
        // Keep going
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_ShutDown_HandleTransitions
///
/// \descr Shut-Down handling transitions (release postrun or SBC sleep)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_ShutDown_HandleTransitions(void)
{
  // Shut-Down status
  STATIC_UT(boolean, boShutDownStatus, TRUE);

  uint32 ulSleepTime_Out_Ms = ECUM_CFG_SBC_SLEEP_TIMEOUT_MS;

  // Evaluate release port run condition (autonomous warning light active together with Pos light)
  EcuM_Evaluate_ReleasePostRun_Condtion();

  // Start SBC sleep timer
  if (boShutDownStatus == TRUE)
  {
    // Get timestamp
    EcuM_ulShutDownp_us = TimerGetTick();
    // Clear SBC time-out flag
    boShutDownStatus = FALSE;
    // PRQA S 2004 2 // program architecture and readability
  }
  else
  {

#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)

    if (EcuM_ulChangeSbcSleep_Timeout_Hook == ECUM_CHANGE_SLEEP_TIME_OUT_HOOK_ACTIVATION)
    {
      ulSleepTime_Out_Ms = ECUM_CFG_SBC_SLEEP_TIMEOUT_MS_HOOK;
    }
    else
    {
       // keep 50ms time-out
    }

#endif 

    // SBC sleep tme-out expire
    if (TimerGetTimeSince(EcuM_ulShutDownp_us) >= UTILTIME_MSEC(ulSleepTime_Out_Ms))
    {
      // Set time-out flag for restart time-out mechanism for a new postrun request
      boShutDownStatus = TRUE;
#if 0
      if (EcuM_ulRunRequestCnt > 0u)
      {
        // PostRun invalidated by special light request
        EcuM_Invalidate_Shutdown();
        // PRQA S 2004 2 // program architecture and readability
      }
      // PostRun Request
      else if (EcuM_ulPostRunRequestCnt > 0u)
#endif
      if (EcuM_ulPostRunRequestCnt > 0u)
      {
        //SPI Cyclic should be stopped and set in SingleTransferMode
        CddSpi_Stop();
        // Stop booster opperation for low current consumption
        CddBoost_Shutdown();
        // SBC sleep (ECU shut-down)
        CddSbc_SetSleepMode();
      }
      else
      {
         // Unexpected situation
      }
    }
    else
    {
      // Time-Out doesn't expire, continue
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Invalidate_Shutdown
///
/// \descr
///
/// \param  -
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Invalidate_Shutdown(void) // PRQA S 3219 1 // architecture; not used at this time
{
  // Update the EcuM state
  EcuM_eState = eEcuM_Up;
} 

//-----------------------------------------------------------------------------
/// \brief  EcuM_HandleNvmWrite
///
/// \descr  Handle NvM write and returns the status of write operation 
///
/// \param  -
///
/// \return Status of write NvM operation
//-----------------------------------------------------------------------------
STATIC_AL NvM_RequestResultType EcuM_HandleNvmWrite(void)
{
  NvM_RequestResultType NvmWriteAllStatus;

  // Get Nvm write error status
  (void)NvM_GetErrorStatus((uint16)NvmBlockMultiBlockRequestId, &NvmWriteAllStatus);

  // Return Nvm writing error status
  return NvmWriteAllStatus;
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_AL_DriverInitZero
///
/// \descr  Calls the DriverInitZero sequence as configured in the EcuM_Cfg.h
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_AL_DriverInitZero(void)
{
  uint8 ucIndex = 0u;

  // Execute the initialization sequence according to the configuration done in the EcuM_Cfg.h
  for (ucIndex = 0u; ucIndex < (uint8)EcuM_DriverInitZero_Id_Count; ucIndex++)
  {
    // Call the configured function
    EcuM_DriverInitZero_FunctionList[ucIndex]();
  }
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_SetActiveApplication
///
/// \descr  Sets the active application into the ShaData right after the application starts
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_SetActiveApplication(void)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_AL_DriverInitOne
///
/// \descr  Calls the DriverInitOne sequence as configured in the EcuM_Cfg.h
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_AL_DriverInitOne(void)
{
  uint8 ucIndex = 0u;

  // Execute the initialization sequence according to the configuration done in the EcuM_Cfg.h
  for (ucIndex = 0u; ucIndex < (uint8)EcuM_DriverInitOne_Id_Count; ucIndex++)
  {
    // Call the configured function
    EcuM_DriverInitOne_FunctionList[ucIndex]();
  }
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_StartOS
///
/// \descr  Peforms the initialization sequence of the Os
///
/// \param  AppModeType
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_StartOS(AppModeType Mode)
{
  // Start Os
  StartOS(Mode);
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_Enable_ChargePump
///
/// \descr  Enables the charge pump. Charge Pump voltage enabled by SBC at SBC init.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_Enable_ChargePump(void)
{
  // Charge pump ready, reset DTC
  EcuM_eChargePumpState = eEcuM_ChargePump_Enabled;
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_StartUp_HandleTransitions
///
/// \descr  Finishes the startup
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_StartUp_HandleTransitions(void)
{
  // Run Request
  if (EcuM_ulRunRequestCnt > 0u)
  {
    // Transition to Up run
    EcuM_eState = eEcuM_Up;
  }
  else
  {
    // Keep start-up state until Nm is wake
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_ReportWgdReset
///
/// \descr Function to report watchdog defect error
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_ReportWgdReset(void)
{
  // Open diagnostic window (in normal init without diag-mux-on received over the CAN, the diagnostic will not work)
  Rte_Call_DemPrj_Set_DiagWindow(TRUE);
  // Internal watchdoh RESET
  if (EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biSBC_WDG_ResetReason != 0u)
  {
     // Set watchdog defect error
    Rte_Call_DemPrj_ReportErrorStatus((uint16)WATCHDOG_DEFECT, DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    // Reset watchdog defect error
    Rte_Call_DemPrj_ReportErrorStatus((uint16)WATCHDOG_DEFECT, DEM_EVENT_STATUS_PASSED);
  }
  // Close diagnostic window (in normal init without diag-mux-on received over the CAN, the diagnostic will not work)
  Rte_Call_DemPrj_Set_DiagWindow(FALSE);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_ReportAppCrcReset
///
/// \descr Function to report APP CRC defect error
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_ReportAppCrcReset(void)
{
  // Open diagnostic window (in normal init without diag-mux-on received over the CAN, the diagnostic will not work)
  Rte_Call_DemPrj_Set_DiagWindow(TRUE);
  // Application CRC RESET
  if (EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason != 0u)
  {
    // Set App CRC error
    Rte_Call_DemPrj_ReportErrorStatus((uint16)CRC_APP_DEFECT, DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    // Reset App CRC error
    Rte_Call_DemPrj_ReportErrorStatus((uint16)CRC_APP_DEFECT, DEM_EVENT_STATUS_PASSED);
  }
  // Close diagnostic window (in normal init without diag-mux-on received over the CAN, the diagnostic will not work)
  Rte_Call_DemPrj_Set_DiagWindow(FALSE);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_WaitNvMReady
///
/// \descr Wait for Nvm ready function
///
/// \param  unBlockNumber - NvM block number
///
/// \return  boolean: Ready status (FALSE - Not Ready, TRUE - Ready)
//-----------------------------------------------------------------------------
STATIC_AL boolean EcuM_WaitNvMReady(uint16 unBlockNumber)
{

  // Nvm Error status report
  NvM_RequestResultType Int_NvStatus;
 
  // Gneral purpose timers for time-out not ready Nvm
  TIMER ulNvmInitTmr_us = 0u;
  TIMER ulNvmInitOnTmr_us = 0u;

  // Get Timer Tick
  ulNvmInitTmr_us = TimerGetTick();
 
  // Perform Fee and Nvm main functions until Nvm is Ready
  do
  {
    // Nvm Main function
    NvM_MainFunction();
 
    // Fee Main function
    Fee_MainFunction();
 
    // Get Nvm Error status
    (void)NvM_GetErrorStatus(unBlockNumber, &Int_NvStatus);
 
    // Get timer since init
    ulNvmInitOnTmr_us = TimerGetTimeSince(ulNvmInitTmr_us);


#ifdef UNIT_TEST

	//////////////////////////////////////////////
	// Special do-while code instrumentation for UT
	///////////////////////////////////////////////

  EcuM_Check_For_Special_UT_Instrumentation_NvM_Ready(&Int_NvStatus, &ulNvmInitOnTmr_us);
	

#endif
 
    // Do Nvm and Fee main function till not time-out (6.5ms) and status is pending
  } while ((Int_NvStatus == NVM_REQ_PENDING) && (ulNvmInitOnTmr_us < ECUM_CFG_NVM_READY_TIMEOUT_US));
 
  // Return Nvm wait status
  return (Int_NvStatus == NVM_REQ_OK) ? TRUE: FALSE;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_WaitForNvMReadAllReady
///
/// \descr Callback from EcuM StartUp two for Nvm Ready wait
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_WaitForNvMReadAllReady(void)
{
  // Wait Nvm
  (void)EcuM_WaitNvMReady((uint16)NvmBlockMultiBlockRequestId);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_OnStateStartup
///
/// \descr StartUp On state EcuM (wait until network is active)
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_OnStateStartup(void)
{
  // Check for transition request (Up)
  EcuM_StartUp_HandleTransitions();
}

//-----------------------------------------------------------------------------
/// \brief EcuM_AL_InterruptCfg
///
/// \descr Interrupt configuration routine (interrupt number, priority)
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_AL_InterruptCfg(void)
{
  uint8 ucIndex = 0u;

  // Execute the initialization sequence for interrupt list (interrupt, priotity)
  for (ucIndex = 0u; ucIndex < (uint8)EcuM_Startup_Interrupt_Cfg_Id_Count; ucIndex++)
  {
    // The function call shall be done immediately
    // PRQA S 4442 1 // program architecture and readability
    INT_SYS_SetPriority(EcuM_InterruptCfg_List[ucIndex].ucInterrupt, EcuM_InterruptCfg_List[ucIndex].ucPriority);
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_AL_InterruptEnable
///
/// \descr Interrupt enable routine (interrupt number)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_AL_InterruptEnable(void)
{
  uint8 ucIndex = 0u;

  // Execute the enable sequence for interrupt
  for (ucIndex = 0u; ucIndex < (uint8)EcuM_Startup_Interrupt_Enable_Id_Count; ucIndex++)
  {
    // The function call shall be done immediately
    // PRQA S 4442 1 // program architecture and readability
    INT_SYS_EnableIRQ(EcuM_InterruptEnbl_List[ucIndex]);
  }

  // Interrupt enable
  ENABLE_INTERRUPTS();
}

//-----------------------------------------------------------------------------
/// \brief EcuM_RequestRUN
///
/// \descr User Request Run notification
///
/// \param  ucUser - User based on user list
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_RequestRUN(uint8 ucUser)
{
  // Get Run Request status
  if (EcuM_GetRequestRunStatus(ucUser) != FALSE)
  {
    // If Run request status for actual user is true (no other run request), increment Run Request counter
    EcuM_ulRunRequestCnt = (EcuM_ulRunRequestCnt < 0xFFFFFFFFu) ? EcuM_ulRunRequestCnt + 1u : EcuM_ulRunRequestCnt;
  }
  else
  {
    // Skip, run request status invalid
  }

  // Set Run Request flag
  EcuM_aucUser[ucUser] |= ECUM_USER_REQUEST_RUN_MASK;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_RequestPOST_RUN
///
/// \descr User Request PostRun notification
///
/// \param  ucUser - User based on user list
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_RequestPOST_RUN(uint8 ucUser)
{
  // Get PostRun Request status
  if (EcuM_GetRequestPostRunStatus(ucUser) != FALSE)
  {
    // If PostRun request status for actual user is true (no other postrun request), increment PostRun Request counter
    EcuM_ulPostRunRequestCnt = (EcuM_ulPostRunRequestCnt < 0xFFFFFFFFu) ? EcuM_ulPostRunRequestCnt + 1u : EcuM_ulPostRunRequestCnt;
  }
  else
  {
    // Skip, postrun request status invalid
  }

  // Set PostRun Request flag
  EcuM_aucUser[ucUser] |= ECUM_USER_REQUEST_POST_RUN_MASK;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_ReleaseRUN
///
/// \descr User Release Run notification
///
/// \param  ucUser - User based on user list
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_ReleaseRUN(uint8 ucUser)
{
  // Get Run Release status
  if (EcuM_GetReleaseRunStatus(ucUser) != FALSE)
  {
    // If Run release status for actual user is true (no other run release), decrement Run Request counter
    EcuM_ulRunRequestCnt = (EcuM_ulRunRequestCnt > 0u) ? EcuM_ulRunRequestCnt - 1u : EcuM_ulRunRequestCnt;
  }
  else
  {
    // Skip, run release status invalid
  }

  // Clear Run Request flag
  EcuM_aucUser[ucUser] &= (uint8)(~(uint8)ECUM_USER_REQUEST_RUN_MASK);
}

//-----------------------------------------------------------------------------
/// \brief EcuM_ReleasePOST_RUN
///
/// \descr User Release PostRun notification
///
/// \param  ucUser - User based on user list
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_ReleasePOST_RUN(uint8 ucUser)
{
  // Get PostRun Release status
  if (EcuM_GetReleasePostRunStatus(ucUser) != FALSE)
  {
    // If PostRun release status for actual user is true (no other postrun release), decrement PostRun Request counter
    EcuM_ulPostRunRequestCnt = (EcuM_ulPostRunRequestCnt > 0u) ? EcuM_ulPostRunRequestCnt - 1u : EcuM_ulPostRunRequestCnt;
  }
  else
  {
    // Skip, postrun release status invalid
  }

  // Clear PostRun Request flag
  EcuM_aucUser[ucUser] &= (uint8)(~(uint8)ECUM_USER_REQUEST_POST_RUN_MASK);
}

//-----------------------------------------------------------------------------
/// \brief  EcuM_FlashCrcFailure_Indication
///
/// \descr  Callback function used to indicate a flash CRC failure
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_FlashCrcFailure_Indication(void)
{
  // Set Flash CRC failure indication flag
  EcuM_boFlashCrcFailure = TRUE;
}


//-----------------------------------------------------------------------------
/// \brief EcuM_GetRequestRunStatus
///
/// \descr Run Request Status getter function
///
/// \param  ucUser - User based on user list
///
/// \return boolean: TRUE-Run Request present; FALSE-Run Request absent
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean EcuM_GetRequestRunStatus(uint8 ucUser)
{
  // Return Run request status
  return ((EcuM_aucUser[ucUser] & ECUM_USER_REQUEST_RUN_MASK) == 0u) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_GetReleaseRunStatus
///
/// \descr Release Request Status getter function
///
/// \param  ucUser - User based on user list
///
/// \return boolean: TRUE-Run Release present; FALSE-Run Release absent
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean EcuM_GetReleaseRunStatus(uint8 ucUser)
{
  // Return Run release status
  return ((EcuM_aucUser[ucUser] & ECUM_USER_REQUEST_RUN_MASK) == ECUM_USER_REQUEST_RUN_MASK) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_GetRequestPostRunStatus
///
/// \descr PostRun Request Status getter function
///
/// \param  ucUser - User based on user list
///
/// \return boolean: TRUE-PostRun Request present; FALSE-PostRun Request absent
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean EcuM_GetRequestPostRunStatus(uint8 ucUser)
{
  // Return PostRun request status
  return ((EcuM_aucUser[ucUser] & ECUM_USER_REQUEST_POST_RUN_MASK) == 0u) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_GetReleasePostRunStatus
///
/// \descr PostRun Release Status getter function
///
/// \param  ucUser - User based on user list
///
/// \return boolean: TRUE-PostRun Release present; FALSE-PostRun Release absent
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean EcuM_GetReleasePostRunStatus(uint8 ucUser)
{
  // Return PostRun release status
  return ((EcuM_aucUser[ucUser] & ECUM_USER_REQUEST_POST_RUN_MASK) == ECUM_USER_REQUEST_POST_RUN_MASK) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Evaluate_RequestPostRun_Condtion
///
/// \descr Post Run request evaluation procedure based on "NM_CAN_b_SleepBSIframe" external varaible
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Evaluate_RequestPostRun_Condtion(void)
{
  // Instant Sleep status
  STATIC_UT(boolean, boBsiInstantSleepStatus, TRUE);
  uint8 u8SleepBSI;
  (void)Rte_Read_SigPrep_SleepBSI(&u8SleepBSI);
  // Evaluate BSI sleep status
  if(u8SleepBSI == ECUM_LGM_TRUE)
  {
    // First sleep detection
    if (boBsiInstantSleepStatus != FALSE)
    {
      // NM Post Run request
      EcuM_RequestPOST_RUN(ECUM_LIFEPHASE_NM_USER);
    }
    else
    {
      // First sleep flag clear
      boBsiInstantSleepStatus = FALSE;
    }
  }
  else
  {
    // Check first Post Run request, if BSi sleep is false, keep it false, no overpost run request
    boBsiInstantSleepStatus = TRUE;
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Evaluate_ReleasePostRun_Condtion
///
/// \descr Release PostRun request evaluation (special conditions base on autonmous warning light and position)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Evaluate_ReleasePostRun_Condtion(void)
{
  // Position light carrier
  tsRte_SysMonLgtFctsReq  sDataLgtFctsReq = { 0 };
  // Autonomous warning light carrier
  teRte_WarningMode       eWarningMode = eWarningMode_PilotedWarningMode;
  // Request of low beam
  teRte_ReqLightState     eLowBeamReq = ReqLighted_Off;
  // State of Emergency Operation Mode activation
  boolean                 boLbEmergeOpMode = FALSE;
  // Speed State 
  SysMon_EnumSpeedState   eSpeedState = SysMon_Speed_0_State;
  // LowBeam State
  SysMon_EnumLowBeamState eLowBeamState = SysMon_LowBeam_Valid_State;
  // Mounting side of ECU
  teRte_MountingSide      eMountingSide = eMountedRight;

  // Read RTE Mounting Side of ECU
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  // Read RTE Low Beam Request
  (void)Rte_Read_SysMon_LowBeamCmd_Req(&eLowBeamReq);

  // Get Low Beam Emergency Operation state
  boLbEmergeOpMode = Rte_Call_Get_LB_EmergencyOperationMode;

  // Get Speed State value
  eSpeedState = Rte_Call_Get_SpeedState;

    // Get Low Beam State value
  eLowBeamState = Rte_Call_Get_LowBeamState;

  // Read RTE Parking light
  (void)Rte_Read_SysMon_StdLgtFcts_Req(&sDataLgtFctsReq);
  // Read RTE Autonomous warning light
  (void)Rte_Read_FctR_TiWarningMode(&eWarningMode);

  // Check custom postrun release based on special light requests
  if (((sDataLgtFctsReq.eEtatFeuxStat == eEtatFeuxStationnement_LeftSide) && (eMountingSide == eMountedLeft)) ||
      ((sDataLgtFctsReq.eEtatFeuxStat == eEtatFeuxStationnement_RightSide) && (eMountingSide == eMountedRight)) ||
      (eWarningMode != eWarningMode_PilotedWarningMode) ||
      ((eLowBeamReq != ReqLighted_Off) && (eSpeedState == SysMon_Speed_Drive_State) && (eLowBeamState != SysMon_LowBeam_Invalid_State)) ||
      ((eLowBeamReq != ReqLighted_Off) && (boLbEmergeOpMode != FALSE)))
  {
    // PostRun release
    EcuM_ReleasePOST_RUN(ECUM_LIFEPHASE_NM_USER);
    // Run request
    EcuM_RequestRUN(ECUM_LIFEPHASE_NM_USER);
  }
  else
  {
    // Skip release PostRun
  }
} // PRQA S 5324 1 // Readability

//-----------------------------------------------------------------------------
/// \brief EcuM_McuSelfTest
///
/// \descr MCU self test performing like MPU, ECC, unused opcode, PLL Unlock
///
/// \param  void
///
/// \return uint8 - Self Test result
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_STATUS == STD_ON)
STATIC_AL uint8 EcuM_McuSelfTest(void)
{
  // Self Test Error counter
  uint8_least ucErrCnt = 0u;

#if (ECUM_SELFTEST_MPU == STD_ON)

  // MPU Self test started
  EcuM_ulMPUSelfTestEnable = 1u;

  // Run MPU Self Test and get the result
  uint8 ucMPUSelfTestResult = EcuM_MPUSelfTest();

  // MPU Self test completed 
  EcuM_ulMPUSelfTestEnable = 0u;

  // Check the MPU self test result
  if (ucMPUSelfTestResult != ECUM_SELFTEST_PASS)
  {
    // Report and react when MPU test failed (Reset + share data memory updated)
    EcuM_MPU_SelfTest_Fail_Reaction();
    // ErrCnt increment
    ucErrCnt++;
  }
  else
  {
    // Do nothing
  }
#endif

#if (ECUM_SELFTEST_ECC == STD_ON)
  uint8 ucECCSelftTestresult = EcuM_ECCSelfTest();

  if (ucECCSelftTestresult != ECUM_SELFTEST_PASS)
  {
    // Report and react when ECC test failed
    EcuM_ECC_SelfTest_Fail_Reaction();
    // ErrCnt increment
    ucErrCnt++;
  }
  else
  {
    // Do nothing
  }
#endif

#if (ECUM_SELFTEST_UNUSED_OPCODE == STD_ON)
  uint8 ucUnOpCodeSelftTestresult = EcuM_UnusedOpcodeSelfTest();

  if (ucUnOpCodeSelftTestresult != ECUM_SELFTEST_PASS)
  {
    // Report and react when Unused OpCode test failed
    EcuM_Unused_Opcode_SelfTest_Fail_Reaction();
    // ErrCnt increment
    ucErrCnt++;
  }
  else
  {
    // Do nothing
  }
#endif

#if (ECUM_SELFTEST_PLL_UNLOCK == STD_ON)
  uint8 ucPLLUnlockSelftTestresult = EcuM_PLLUnlockSelfTest();

  if (ucPLLUnlockSelftTestresult != ECUM_SELFTEST_PASS)
  {
    // Report and react when Unused OpCode test failed
    EcuM_PLL_Unlock_SelfTest_Fail_Reaction();
    // ErrCnt increment
    ucErrCnt++;
  }
  else
  {
    // Do nothing
  }
#endif

  return (ucErrCnt == 0u) ? ECUM_SELFTEST_PASS : ECUM_SELFTEST_FAIL;

  // PRQA S 5324 1 // program architecture and readability
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPUSelfTest
///
/// \descr MPU self test performing
///
/// \param void
///
/// \return uint8 - Self Test result
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL uint8 EcuM_MPUSelfTest(void)
{
  // Reset MPU Self test Error counter 
  EcuM_ucMPUSelfTestErrCnt = 0u;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If PRIVILEGE
  if (EcuM_ulMcuPrivStatus != 0u)
  {
    // Get Region 0 WORD 2 register reset value
    EcuM_MPU_SelfTest_GetDefaultReg0W2();

    // Update MPU with self test configuration
    EcuM_MPU_SelfTest_MPU_Config();
  }
  else
  {
    // Something gone wrong, error cnt is incremented
    EcuM_ucMPUSelfTestErrCnt++;
  }

  // Test 1, get the MPU status
  // No errors to be shown after ECU reset
  EcuM_mpu_SelfTest_GestMpuHwStatus(&EcuM_sMpuErrState);

  // No MPU error shall be reported until now
  if (EcuM_sMpuErrState.boMPUErrorStatus != FALSE)
  {
    // Increment self test error
    EcuM_ucMPUSelfTestErrCnt++;
  }

  // Privileage read from a totaly prohibited RAM Area - FAULTY access test
  EcuM_MPU_SelfTest_Test_1();
  // Privileage from a totaly prohibited RAM Area - FAULTY access test
  EcuM_MPU_SelfTest_Test_2();
  // User read from a totaly prohibited RAM Area - FAULTY access test
  EcuM_MPU_SelfTest_Test_3();
  // User write to a totaly prohibited RAM Area - FAULTY access test
  EcuM_MPU_SelfTest_Test_4(); 
  // Privileage read from a trusted RAM Area (Privilege read, write, executed allowed, user read allowed) - NOT FAULTY access test
  EcuM_MPU_SelfTest_Test_5();
  // Privileage write to a trusted RAM Area (Privilege read, write, executed allowed, user read allowed) - NOT FAULTY access test
  EcuM_MPU_SelfTest_Test_6();
  // User read from a trusted RAM Area (Privilege read, write, executed allowed, user read allowed) - NOT FAULTY access test
  EcuM_MPU_SelfTest_Test_7();
  // User write to a trusted RAM Area (Privilege read, write, executed allowed, user read allowed) - FAULTY access test
  EcuM_MPU_SelfTest_Test_8();

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch back to privilege
    EcuM_PrivilegeSwitch();
  }

  // Restore Region 1 MPU config and clear ERR flags
  EcuM_MPU_SelfTest_RestoreDefaultReg0W2();

  // Update global MPU Self Test Status
  EcuM_uMpu_SelfTest_State.Bit.biMpuAllTests_Res = ((EcuM_uMpu_SelfTest_State.ulMpuTest_Result_Stat & 0x0000FFFFu) != 0x00005555u) ? ECUM_MPU_SELF_TEST_RESULT_FAIL : ECUM_MPU_SELF_TEST_RESULT_PASS;

  return (EcuM_ucMPUSelfTestErrCnt != 0u) ? ECUM_SELFTEST_FAIL : ECUM_SELFTEST_PASS;

  // PRQA S 5324 1 // program architecture and readability
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_Fail_Reaction
///
/// \descr MPU Self Test Reaction
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_MPU_SelfTest_Fail_Reaction(void)
{
  // MPU Self Test failed reaction
  // Write 0x5a01 in specific share data ram memory location
  // PRQA S 303 1 // Pointer cast needed
  ECUM_MPU_SELFTEST_FAIL_EVENT_MEM = ECUM_FAIL_VAL;

  // Perform MCU Reset and write specific Share Ram location
  Mcu_PerformReset();

}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_ECCSelfTest
///
/// \descr ECC Ram memory Self Test
///
/// \param  void
///
/// \return uint8 - Self Test result
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_ECC == STD_ON) || defined(UNIT_TEST)
STATIC_AL uint8 EcuM_ECCSelfTest(void)
{

  uint32 ulEccErrCnt = 0u;
  uint32 ulDummyTemp = 0u;

  //********************************************
  // Test 1 - Inject Single Bit error in RAM U/L
  //********************************************

  EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 0u;

  // RAM SEC Error Injection
  EcuM_Inject_RAM_SEC_ECCError();

#ifdef UNIT_TEST

  // Trigger the ISR (UT instrumentation)
  EcuM_Check_For_Special_UT_Instrumentation_RAM_SEC_Injection();

#endif

  // PRQA S 3415 1 // Opperation without any side effects
  if ((EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt != 1u) || (EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt != 1u))
  {
    ulEccErrCnt++;
  }

  EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 0u;

  //********************************************
  // Test 2 - Inject Double Bit error in RAM U/L
  //********************************************

  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 0u;

  // RAM DED Error Injection
  EcuM_Inject_RAM_DED_ECCError();

#ifdef UNIT_TEST
  
  // Trigger the ISR (UT instrumentation)
  EcuM_Check_For_Special_UT_Instrumentation_RAM_DED_Injection();

#endif


  // PRQA S 3415 1 // Opperation without any side effects
  if ((EcuM_ulECC_RAM_L_DED_Irq_ErrCnt != 1u) || (EcuM_ulECC_RAM_U_DED_Irq_ErrCnt != 1u))
  {
    ulEccErrCnt++;
  }

  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 0u;

  //********************************************
  // Test 3 - Inject Double Bit error in Flash
  //********************************************

  EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 0u;

  // Flash DED Error Injection
  EcuM_Inject_FLASH_DED_ECCError();

  // do some dummy code to catch the Flash NCE
  EcuM_EccSelfTest_DummyCode();

#ifdef UNIT_TEST

  // Trigger the ISR (UT instrumentation)
  EcuM_Check_For_Special_UT_Instrumentation_Flash_NCE_Injection();

#endif

  if (EcuM_ulECC_Flash_NCE_Irq_ErrCnt != 1u)
  {
    ulEccErrCnt++;
  }

  EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 0u;

  // Report the ECC self test result

  return (ulEccErrCnt == 0u) ? ECUM_SELFTEST_PASS : ECUM_SELFTEST_FAIL;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_DummyCode
///
/// \descr Dummy Code for ECC self test (FLASH non-correctable error catching)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_EccSelfTest_DummyCode(void)
{
  EcuM_ucEccCntDummy = 10u;

  // PRQA S 2461 1 // program architecture and readability
  while (EcuM_ucEccCntDummy > 0u)
  {
    EcuM_ucEccCntDummy--;
  }
}
#endif



//-----------------------------------------------------------------------------
/// \brief EcuM_ECC_SelfTest_Fail_Reaction
///
/// \descr ECC Self Test Fail Reaction
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_ECC == STD_ON) || defined(UNIT_TEST)
STATIC_AL void EcuM_ECC_SelfTest_Fail_Reaction(void)
{
  // MPU Self Test failed reaction
  // Write 0x5a01 in specific share data ram memory location
  // PRQA S 303 1 // Pointer cast needed
  ECUM_ECC_SELF_TEST_ERROR_MEM = ECUM_FAIL_VAL;

  // Perform MCU Reset and write specific Share Ram location
  Mcu_PerformReset();
}
#endif


//-----------------------------------------------------------------------------
/// \brief EcuM_UnusedOpcodeSelfTest
///
/// \descr Unused Opcode Self Test
///
/// \param void
///
/// \return uint8 - Self Test result
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_UNUSED_OPCODE == STD_ON) || defined(UNIT_TEST)
STATIC_AL uint8 EcuM_UnusedOpcodeSelfTest(void)
{
  return ECUM_SELFTEST_PASS;
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_Unused_Opcode_SelfTest_Fail_Reaction
///
/// \descr Unused Opcode Self Test Fail Reaction
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_UNUSED_OPCODE == STD_ON) || defined(UNIT_TEST)
STATIC_AL void EcuM_Unused_Opcode_SelfTest_Fail_Reaction(void)
{
  return;
}
#endif


//-----------------------------------------------------------------------------
/// \brief EcuM_PLLUnlockSelfTest
///
/// \descr Pll Unlock Self Test
///
/// \param  void
///
/// \return uint8 - Self Test result
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_PLL_UNLOCK == STD_ON) || defined(UNIT_TEST)
STATIC_AL uint8 EcuM_PLLUnlockSelfTest(void)
{
  return ECUM_SELFTEST_PASS;
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_PLL_Unlock_SelfTest_Fail_Reaction
///
/// \descr PLL Unlock Self Test Fail Reaction
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_PLL_UNLOCK == STD_ON) || defined(UNIT_TEST)
STATIC_AL void EcuM_PLL_Unlock_SelfTest_Fail_Reaction(void)
{
  return;
}
#endif


#ifndef UNIT_TEST
//-----------------------------------------------------------------------------
/// \brief EcuM_GetMcuPrivilegeStatus
///
/// \descr Get Core Master Privilege bit from control register
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_GetMcuPrivilegeStatus(void)
{
  // ASM routine
  __asm volatile 
  (
      " push {r0-r1}                    \n"
      " mrs r0, control                 \n"
      " ldr r1, =EcuM_ulMcuPrivStatus   \n"
      " eor r0, r0, #~0x0               \n"
      " and r0, r0, #0x1                \n"
      " str r0, [r1]                    \n"
      " pop {r0-r1}                     \n"
   );
  // PRQA S 5334 1 // program architecture and readability
}


//-----------------------------------------------------------------------------
/// \brief EcuM_UserSwitch
///
/// \descr Set Core Master Handler (USER) mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_UserSwitch(void)
{
  // ASM routine
  __asm volatile
  (
    " push {r0}                        \n"
    " mrs r0, control                  \n"
    " orr r0, r0, #0x1                 \n"
    " msr control, r0                  \n"
    " pop {r0}                         \n"
  );
  // PRQA S 5334 1 // program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief EcuM_PrivilegeSwitch
///
/// \descr Set Core Master Privilege (PRIVILEGE) mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_PrivilegeSwitch(void)
{
  // ASM routine
  __asm volatile
  (
    " push {r12}                       \n"
    " ldr r12, =EcuM_PrivilegeUpdate   \n"
    // System call for supervison switch
    " svc #0x0                         \n"
    " pop {r12}                        \n"
    );
  // PRQA S 5334 1 // program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief EcuM_McuPrivilegeSwitch
///
/// \descr Arm Core privilege changer
///
/// \param  ucMode - Core privilege level
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_McuPrivilegeSwitch(uint8 ucMode)
{
  EcuM_GetMcuPrivilegeStatus();
  switch (ucMode)
  {
    case 0u: if (EcuM_ulMcuPrivStatus == 1u) { EcuM_UserSwitch(); } break;
    case 1u: if (EcuM_ulMcuPrivStatus == 0u) { EcuM_PrivilegeSwitch(); } break;
    default: break;
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_PrivilegeUpdate
///
/// \descr Privilege update in control register, routine called by SVC_Handler (System Call)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_PrivilegeUpdate(void)
{
  // ASM routine
  __asm volatile
  (
    " push {r0}                        \n"
    " mrs r0, control                  \n"
    " and r0, r0, #~0x1                \n"
    " msr control, r0                  \n"
    " pop {r0}                         \n"
  );
  // PRQA S 5334 1 // program architecture and readability
}
#endif

// PRQA S 306 ++ // Pointer cast needed - MCU register access
// PRQA S 303 ++ // Pointer cast needed - RAM address and register access

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_MPU_Config
///
/// \descr MPU configuration for MPU self Test
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_MPU_SelfTest_MPU_Config(void)
{
  // Temporary register value
  uint32 ulReg2Temp = 0u;

  // Disable MPU
  MPU->CESR &= (volatile uint32)(~(uint32)0x1u);

  //Region 0 shall be kept as default

  // Region 1 configuration
   // Start Address
  MPU->RGD[1].WORD0 = (volatile uint32)0;
  // End Address
  MPU->RGD[1].WORD1 = ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS - 1u;
  // Full access for all masters
  ulReg2Temp = MPU->RGD[1].WORD2;
  // Mask bitfield for M3, M2, M1 and M0
  ulReg2Temp &= (volatile uint32)0xFF800000u;
  // Master 3 - ENET
  // Master 2 - DMA
  // Master 1 - Debugger
  // Matser 0 - Core
  // ENET Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 21u);
  // ENET User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 18u);
  // DMA Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 15u);
  // DMA User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 12u);
  // Debugger Process Identifier disable
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 11u);
  // Debugger Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 9u);
  // Debugger User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 6u);
  // Core Process Identifier disable
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 5u);
  // Core Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 3u);
  // Core User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 0u);
  // Store word 2 register
  MPU->RGD[1].WORD2 = ulReg2Temp;
  // Region Enable
  MPU->RGD[1].WORD3 |= (volatile uint32)0x1u;


  // Region 2 configuration
  // Start Address
  MPU->RGD[2].WORD0 = (volatile uint32)ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS;
  // End Address
  MPU->RGD[2].WORD1 = (volatile uint32)ECUM_RAM_MEMORY_END_PRIV_USER_RWX_PROHIBITED_ACCESS;
  // Full access for all masters
  ulReg2Temp = MPU->RGD[2].WORD2;
  // Mask bitfield for M3, M2, M1 and M0
  ulReg2Temp &= (volatile uint32)0xFF800000u;
  // Master 3 - ENET
  // Master 2 - DMA
  // Master 1 - Debugger
  // Matser 0 - Core
  // ENET Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 21u);
  // ENET User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 18u);
  // DMA Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 15u);
  // DMA User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 12u);
  // Debugger Process Identifier disable
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 11u);
  // Debugger Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 9u);
  // Debugger User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 6u);
  // Core Process Identifier disable
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 5u);
  // Core Supervision Mode Access control - R/W/X not allowed same as for USER
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x03u) << 3u);
  // Core User Mode Access control - R/W/X not allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 0u);
  // Store word 2 register
  MPU->RGD[2].WORD2 = ulReg2Temp;
  // Region Enable
  MPU->RGD[2].WORD3 |= (volatile uint32)0x1u;


  // Region 3 configuration
  // Start Address
  MPU->RGD[3].WORD0 = ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS;
  // End Address
  MPU->RGD[3].WORD1 = ECUM_RAM_MEMORY_END_USER_WX_PROHIBITED_ACCESS;
  // Full access for all masters
  ulReg2Temp = MPU->RGD[3].WORD2;
  // Mask bitfield for M3, M2, M1 and M0
  ulReg2Temp &= (volatile uint32)0xFF800000u;
  // Master 3 - ENET
  // Master 2 - DMA
  // Master 1 - Debugger
  // Matser 0 - Core
  // ENET Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 21u);
  // ENET User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 18u);
  // DMA Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 15u);
  // DMA User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 12u);
  // Debugger Process Identifier disable
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 11u);
  // Debugger Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 9u);
  // Debugger User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 6u);
  // Core Process Identifier disable
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 5u);
  // Core Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 3u);
  // Core User Mode Access control - R allowed, W/X not allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x04u) << 0u);
  // Store word 2 register
  MPU->RGD[3].WORD2 = ulReg2Temp;
  // Region Enable
  MPU->RGD[3].WORD3 |= (volatile uint32)0x1u;

  // Region 4 configuration
  // Start Address
  MPU->RGD[4].WORD0 = ECUM_RAM_MEMORY_END_USER_WX_PROHIBITED_ACCESS + 1u;
  // End Address
  MPU->RGD[4].WORD1 = (volatile uint32)0xFFFFFFFFu;
  // Full access for all masters
  ulReg2Temp = MPU->RGD[4].WORD2;
  // Mask bitfield for M3, M2, M1 and M0
  ulReg2Temp &= (volatile uint32)0xFF800000u;
  // Master 3 - ENET
  // Master 2 - DMA
  // Master 1 - Debugger
  // Matser 0 - Core
  // ENET Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 21u);
  // ENET User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 18u);
  // DMA Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 15u);
  // DMA User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 12u);
  // Debugger Process Identifier disable
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 11u);
  // Debugger Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 9u);
  // Debugger User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 6u);
  // Core Process Identifier disable
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 5u);
  // Core Supervision Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 3u);
  // Core User Mode Access control - R/W/X allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x07u) << 0u);
  // Store word 2 register
  MPU->RGD[4].WORD2 = ulReg2Temp;
  // Region Enable
  MPU->RGD[4].WORD3 |= (volatile uint32)0x1u;

  // Region 0 will privilege access is changed for Master Core
  // Read region 0 word 2 register
  ulReg2Temp = MPU->RGD[0].WORD2;
  // Mask privilege rights for other masters
  ulReg2Temp &= (volatile uint32)0xFFFFFE0u;
  // Core Supervision Mode Access control - R/W/X not allowed as for USER
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x03u) << 3u);
  // Core User Mode Access control - R/W/X not allowed
  ulReg2Temp |= (volatile uint32)((volatile uint32)(0x00u) << 0u);
  // RGDAAC register update
  MPU->RGDAAC[0] = ulReg2Temp;

  // Enable MPU
  MPU->CESR |= 0x1u;

  // PRQA S 5330 1 // program architecture and readability
}
#endif


//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_GetDefaultReg0W2
///
/// \descr Get default region 0 (REG0) WORD2 descriptor in order to restore it after MPU selftest
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_MPU_SelfTest_GetDefaultReg0W2(void)
{
  // Store RGD0 WORD2
  EcuM_ulRegion0Word2_DefaultValue = MPU->RGD[0].WORD2;
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_RestoreDefaultReg0W2
///
/// \descr Restore default region 0 (REG0) WORD2 descriptor after MPU self test and clear MPU error flags
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_MPU_SelfTest_RestoreDefaultReg0W2(void)
{
  uint32 ulTemp = 0u;

  // // Restore RGD0 WORD2
  MPU->RGDAAC[0] = EcuM_ulRegion0Word2_DefaultValue;

  // Get MPU Error Flags
  ulTemp = (MPU->CESR) & 0xF8000000u;

  // Clear Error flags
  MPU->CESR |= ulTemp;
}
#endif


//-----------------------------------------------------------------------------
/// \brief EcuM_mpu_SelfTest_GestMpuHwStatus
///
/// \descr Get MPU error status and error information in order to perform MPU selftest
///
/// \param  *sMpuErrStat - MPU status returned
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_mpu_SelfTest_GestMpuHwStatus(tsEcuM_MPUSelfTestDetails* sMpuErrStat)
{
  // Get MPU Control Status Register
  uint32 ulMPU_CESRReg = MPU->CESR;

  // Check the MPU access error flags on all slave ports
  if ((uint32)(ulMPU_CESRReg >> (uint32)27u) != 0u)
  {
    // Set MPU error
    sMpuErrStat->boMPUErrorStatus = TRUE;
    // Get error flags
    sMpuErrStat->ucMPUErrorFlags = (uint8)(ulMPU_CESRReg >> (uint32)27u);
    // Get error addresses and detailed informations for all MPU slave ports
    for (uint8_least ucIndx = 0u; ucIndx < 4u; ucIndx++)
    {
      sMpuErrStat->ulMPUAddressError[ucIndx] = MPU->EAR_EDR[ucIndx].EAR;
      sMpuErrStat->ulMPUDetailedError[ucIndx] = MPU->EAR_EDR[ucIndx].EDR;
    }
  }
  else
  {
    // No MPU errors
    sMpuErrStat->boMPUErrorStatus = FALSE;
  }
}
#endif

//-----------------------------------------------------------------------------
/// \brief HardFault_Handler
///
/// \descr MCU Hard_Fault handler (triggered by a MPU Memory fault)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void HardFault_Handler(void)
{
#if (ECUM_SELFTEST_MPU == STD_ON)
  // MPU Self Test started
  if (EcuM_ulMPUSelfTestEnable != 0u)
  {
    // Handler Counter to be incremented
    EcuM_ulHardFaultErrCnt++;

    // Get the MPU status
    // Errors to be shown after ECU reset
    EcuM_mpu_SelfTest_GestMpuHwStatus(&EcuM_sMpuErrState);

    // Deactivate MPU for no longer unrecovery memory access faults [lock-up]
    MPU->CESR &= (uint32)(~(uint32)0x01u);
  }
  else
  {
#ifndef UNIT_TEST
    ECUM_H_FAULT_ERROR_MEM = ECUM_FAIL_VAL;
    // No MPU selftest
    while (1)
    {
      // Program to be stuck here (unrecovereable error) -> Watchdog reset
    }
#endif
  }
#else
  while (1)
  {
    // Program to be stuck here (unrecovereable error) -> Watchdog reset
  }
#endif
}

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_Test_1
///
/// \descr MPU seftest - subtest[1] - Privileage read from a totaly prohibited RAM Area - FAULTY access test
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_MPU_SelfTest_Test_1(void)
{
  uint32 ulMPUTemp = 0u;
  uint32 ulLocalErrCnt = EcuM_ucMPUSelfTestErrCnt;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

  // Test 1 check the privilege access in a totaly prohibited RAM area (r,w,x) defined by
  //[ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS -- ECUM_RAM_MEMORY_END_PRIV_USER_RWX_PROHIBITED_ACCESS]

  // Reset Hard Fault counter
  EcuM_ulHardFaultErrCnt = 0u;

  // Read access -> Hard Fault
  ulMPUTemp = *(volatile uint32*)(ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS + 4u);

#ifdef UNIT_TEST

  //////////////////////////////////////////////
  // Special HardFault exception ISR code instrumentation for UT
  ///////////////////////////////////////////////

  EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_1();

#endif

  // Check Hard Fault counter (should be incremented)
  if (EcuM_ulHardFaultErrCnt != 1u)
  {
    // Increment self test error
    EcuM_ucMPUSelfTestErrCnt++;
  }
  else
  {
    //MPU error shall be reported
    if (EcuM_sMpuErrState.boMPUErrorStatus == FALSE)
    {
      // Increment self test error
      EcuM_ucMPUSelfTestErrCnt++;
    }
    else
    {
      // SRAM_U error on slave port 3
      if (EcuM_sMpuErrState.ucMPUErrorFlags != 0x2u)
      {
        // Increment self test error
        EcuM_ucMPUSelfTestErrCnt++;
      }
      else
      {
        //Check faulty address
        if (EcuM_sMpuErrState.ulMPUAddressError[3] != (ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS + 4u))
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (EATR) - Supervision
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 1u) & (uint32)0x07u) != 0x3u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (ERW) - Read
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 0u) & (uint32)0x01u) != 0x0u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
      }
      // Clear error flags
      MPU->CESR |= (uint32)((uint32)EcuM_sMpuErrState.ucMPUErrorFlags << 27u);
    }
  }

  // MPU re-enable
  MPU->CESR |= (uint32)(0x01u);

  //  Update the MPU Self Test Global Status
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = (ulLocalErrCnt != EcuM_ucMPUSelfTestErrCnt) ? ECUM_MPU_SELF_TEST_RESULT_FAIL : ECUM_MPU_SELF_TEST_RESULT_PASS;
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_Test_2
///
/// \descr MPU seftest - subtest[2] - Privileage write to a totaly prohibited RAM Area - FAULTY access test
///
/// \param  -
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
// PRQA S 3006 1 // program architecture and readability
STATIC_AL void EcuM_MPU_SelfTest_Test_2(void)
{

  uint32 ulMPUTemp = 10u;
  uint32 ulLocalErrCnt = EcuM_ucMPUSelfTestErrCnt;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

  // Test 2 check the privilege access in a totaly prohibited RAM area (r,w,x) defined by
  //[ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS -- ECUM_RAM_MEMORY_END_PRIV_USER_RWX_PROHIBITED_ACCESS]

  // Reset Hard Fault counter
  EcuM_ulHardFaultErrCnt = 0u;

  // Write access -> Hard Fault
  *(volatile uint32*)(ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS + 16u) = ulMPUTemp;

  // Small delay
  for (uint8_least ucIx = 0u; ucIx < 5u; ucIx++)
  {
    __asm volatile("nop");

  }

#ifdef UNIT_TEST

  //////////////////////////////////////////////
  // Special HardFault exception ISR code instrumentation for UT 
  ///////////////////////////////////////////////

  EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_2();

#endif

  // Check Hard Fault counter (should be incremented)
  if (EcuM_ulHardFaultErrCnt != 1u)
  {
    // Increment self test error
    EcuM_ucMPUSelfTestErrCnt++;
  }
  else
  {
    //MPU error shall be reported
    if (EcuM_sMpuErrState.boMPUErrorStatus == FALSE)
    {
      // Increment self test error
      EcuM_ucMPUSelfTestErrCnt++;
    }
    else
    {
      // SRAM_U error on slave port 3
      if (EcuM_sMpuErrState.ucMPUErrorFlags != 0x2u)
      {
        // Increment self test error
        EcuM_ucMPUSelfTestErrCnt++;
      }
      else
      {
        //Check faulty address
        if (EcuM_sMpuErrState.ulMPUAddressError[3] != (ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS + 16u))
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (EATR) - Supervision
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 1u) & (uint32)0x07u) != 0x3u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (ERW) - Write
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 0u) & (uint32)0x01u) != 0x1u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
      }
      // Clear error flags
      MPU->CESR |= (uint32)((uint32)EcuM_sMpuErrState.ucMPUErrorFlags << 27u);
    }
  }

  // MPU re-enable
  MPU->CESR |= (uint32)(0x01u);


  //  Update the MPU Self Test Global Status
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = (ulLocalErrCnt != EcuM_ucMPUSelfTestErrCnt) ? ECUM_MPU_SELF_TEST_RESULT_FAIL : ECUM_MPU_SELF_TEST_RESULT_PASS;
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_Test_3
///
/// \descr MPU seftest - subtest[3] - User read from a totaly prohibited RAM Area - FAULTY access test
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_MPU_SelfTest_Test_3(void)
{ 

  uint32 ulMPUTemp = 0u;
  uint32 ulLocalErrCnt = EcuM_ucMPUSelfTestErrCnt;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus != 0u)
  {
    // Switch to user mode
    EcuM_UserSwitch();
  }

  // Test 3 check the user access in a totaly prohibited RAM area (r,w,x) defined by
  //[ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS -- ECUM_RAM_MEMORY_END_PRIV_USER_RWX_PROHIBITED_ACCESS]

  // Reset Hard Fault counter
  EcuM_ulHardFaultErrCnt = 0u;

  // Read access -> Hard Fault
  ulMPUTemp = *(volatile uint32*)(ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS + 8u);

#ifdef UNIT_TEST

  //////////////////////////////////////////////
  // Special HardFault exception ISR code instrumentation for UT
  ///////////////////////////////////////////////

  EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_3();

#endif


  // Check Hard Fault counter (should be incremented)
  if (EcuM_ulHardFaultErrCnt != 1u)
  {
    // Increment self test error
    EcuM_ucMPUSelfTestErrCnt++;
  }
  else
  {
    //MPU error shall be reported
    if (EcuM_sMpuErrState.boMPUErrorStatus == FALSE)
    {
      // Increment self test error
      EcuM_ucMPUSelfTestErrCnt++;
    }
    else
    {
      // SRAM_U error on slave port 3
      if (EcuM_sMpuErrState.ucMPUErrorFlags != 0x2u)
      {
        // Increment self test error
        EcuM_ucMPUSelfTestErrCnt++;
      }
      else
      {
        //Check faulty address
        if (EcuM_sMpuErrState.ulMPUAddressError[3] != (ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS + 8u))
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (EATR) - User
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 1u) & (uint32)0x07u) != 0x1u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (ERW) - Read
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 0u) & (uint32)0x01u) != 0x0u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
      }

      // Get Core Privilege level
      EcuM_GetMcuPrivilegeStatus();

      // If USER
      if (EcuM_ulMcuPrivStatus == 0u)
      {
        // Switch to privilege
        EcuM_PrivilegeSwitch();
      }

      // Clear error flags
      MPU->CESR |= (uint32)((uint32)EcuM_sMpuErrState.ucMPUErrorFlags << 27u);
    }
  }

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

  // MPU re-enable
  MPU->CESR |= (uint32)(0x01u);


  //  Update the MPU Self Test Global Status
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = (ulLocalErrCnt != EcuM_ucMPUSelfTestErrCnt) ? ECUM_MPU_SELF_TEST_RESULT_FAIL : ECUM_MPU_SELF_TEST_RESULT_PASS;
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_Test_4
///
/// \descr MPU seftest - subtest[4] - User write to a totaly prohibited RAM Area - FAULTY access test
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
// PRQA S 3006 1 // program architecture and readability
STATIC_AL void EcuM_MPU_SelfTest_Test_4(void)
{

  uint32 ulMPUTemp = 0u;
  uint32 ulLocalErrCnt = EcuM_ucMPUSelfTestErrCnt;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus != 0u)
  {
    // Switch to user mode
    EcuM_UserSwitch();
  }

  // Test 4 check the privilege access in a totaly prohibited RAM area (r,w,x) defined by
  //[ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS -- ECUM_RAM_MEMORY_END_PRIV_USER_RWX_PROHIBITED_ACCESS]

  // Reset Hard Fault counter
  EcuM_ulHardFaultErrCnt = 0u;

  // Write access -> Hard Fault
  *(volatile uint32*)(ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS + 24u) = ulMPUTemp;

  // Small delay
  for (uint8_least ucIx = 0u; ucIx < 5u; ucIx++)
  {
    __asm volatile("nop");
  }

#ifdef UNIT_TEST

  //////////////////////////////////////////////
  // Special HardFault exception ISR code instrumentation for UT
  ///////////////////////////////////////////////

  EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_4();

#endif

  // Check Hard Fault counter (should be incremented)
  if (EcuM_ulHardFaultErrCnt != 1u)
  {
    // Increment self test error
    EcuM_ucMPUSelfTestErrCnt++;
  }
  else
  {
    //MPU error shall be reported
    if (EcuM_sMpuErrState.boMPUErrorStatus == FALSE)
    {
      // Increment self test error
      EcuM_ucMPUSelfTestErrCnt++;
    }
    else
    {
      // SRAM_U error on slave port 3
      if (EcuM_sMpuErrState.ucMPUErrorFlags != 0x2u)
      {
        // Increment self test error
        EcuM_ucMPUSelfTestErrCnt++;
      }
      else
      {
        //Check faulty address
        if (EcuM_sMpuErrState.ulMPUAddressError[3] != (ECUM_RAM_MEMORY_START_PRIV_USER_RWX_PROHIBITED_ACCESS + 24u))
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (EATR) - User
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 1u) & (uint32)0x07u) != 0x1u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (ERW) - Write
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 0u) & (uint32)0x01u) != 0x1u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
      }

      // Get Core Privilege level
      EcuM_GetMcuPrivilegeStatus();

      // If USER
      if (EcuM_ulMcuPrivStatus == 0u)
      {
        // Switch to privilege
        EcuM_PrivilegeSwitch();
      }

      // Clear error flags
      MPU->CESR |= (uint32)((uint32)EcuM_sMpuErrState.ucMPUErrorFlags << 27u);
    }
  }

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

  // MPU re-enable
  MPU->CESR |= (uint32)(0x01u);

  //  Update the MPU Self Test Global Status
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = (ulLocalErrCnt != EcuM_ucMPUSelfTestErrCnt) ? ECUM_MPU_SELF_TEST_RESULT_FAIL : ECUM_MPU_SELF_TEST_RESULT_PASS;

  // PRQA S 5310 1 // program architecture and readability
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_Test_5
///
/// \descr MPU seftest - subtest[5] - Privileage read from a trusted RAM Area (Privilege read, write, executed allowed, user read allowed) - NOT FAULTY access test
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_MPU_SelfTest_Test_5(void)
{

  uint32 ulMPUTemp = 0u;
  uint32 ulLocalErrCnt = EcuM_ucMPUSelfTestErrCnt;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

  // Test 5 check the privilege read access in a trusted RAM area (r,w,x allowed) defined by
  //[ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS -- ECUM_RAM_MEMORY_END_USER_WX_PROHIBITED_ACCESS]

  // Reset Hard Fault counter
  EcuM_ulHardFaultErrCnt = 0u;

  // Read access ->No Hard Fault
  ulMPUTemp = *(volatile uint32*)(ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS + 4u);

#ifdef UNIT_TEST

  //////////////////////////////////////////////
  // Special HardFault exception ISR code instrumentation for UT
  ///////////////////////////////////////////////

  EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_5();

#endif

  // Check Hard Fault counter (should be not incremented)
  if (EcuM_ulHardFaultErrCnt != 0u)
  {
    // Increment self test error
    EcuM_ucMPUSelfTestErrCnt++;
    // Clear error flags
    MPU->CESR |= (uint32)((uint32)EcuM_sMpuErrState.ucMPUErrorFlags << 27u);

    // MPU re-enable - disable caused by hard fault recovery
    MPU->CESR |= (uint32)(0x01u);
  }
  else
  {
   // Behavior ok, skip
  }

  //  Update the MPU Self Test Global Status
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest5_Res = (ulLocalErrCnt != EcuM_ucMPUSelfTestErrCnt) ? ECUM_MPU_SELF_TEST_RESULT_FAIL : ECUM_MPU_SELF_TEST_RESULT_PASS;
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_Test_6
///
/// \descr MPU seftest - subtest[6] - Privileage write to a trusted RAM Area (Privilege read, write, executed allowed, user read allowed) - NOT FAULTY access test
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
// PRQA S 3006 1 // program architecture and readability
STATIC_AL void EcuM_MPU_SelfTest_Test_6(void)
{

  uint32 ulMPUTemp = 10u;
  uint32 ulMemTemp = 0u;
  uint32 ulLocalErrCnt = EcuM_ucMPUSelfTestErrCnt;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

  // Test 6 check the privilege write access in a trusted RAM area (r,w,x allowed) defined by
  //[ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS -- ECUM_RAM_MEMORY_END_USER_WX_PROHIBITED_ACCESS]

  // Reset Hard Fault counter
  EcuM_ulHardFaultErrCnt = 0u;

  // Read location
  ulMemTemp = *(volatile uint32*)(ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS + 16u);

  // Write access -> no Hard Fault
  *(volatile uint32*)(ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS + 16u) = ulMPUTemp;

  // Small delay
  for (uint8_least ucIx = 0u; ucIx < 5u; ucIx++)
  {
    __asm volatile("nop");
  }

#ifdef UNIT_TEST

  //////////////////////////////////////////////
  // Special HardFault exception ISR code instrumentation for UT
  ///////////////////////////////////////////////

  EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_6();

#endif

  // Check Hard Fault counter (should be not incremented)
  if (EcuM_ulHardFaultErrCnt != 0u)
  {
    // Increment self test error
    EcuM_ucMPUSelfTestErrCnt++;
    // Clear error flags
    MPU->CESR |= (uint32)((uint32)EcuM_sMpuErrState.ucMPUErrorFlags << 27u);

    // MPU re-enable - disable caused by hard fault recovery
    MPU->CESR |= (uint32)(0x01u);
  }
  else
  {
    // Behavior ok, skip
    // Restore memory location
    *(volatile uint32*)(ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS + 16u) = ulMemTemp;
  }

  //  Update the MPU Self Test Global Status
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res = (ulLocalErrCnt != EcuM_ucMPUSelfTestErrCnt) ? ECUM_MPU_SELF_TEST_RESULT_FAIL : ECUM_MPU_SELF_TEST_RESULT_PASS;
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_Test_7
///
/// \descr MPU seftest - subtest[7] - User read from  a trusted RAM Area (Privilege read, write, executed allowed, user read allowed) - NOT FAULTY access test
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
STATIC_AL void EcuM_MPU_SelfTest_Test_7(void)
{

  uint32 ulMPUTemp = 0u;
  uint32 ulLocalErrCnt = EcuM_ucMPUSelfTestErrCnt;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus != 0u)
  {
    // Switch to user mode
    EcuM_UserSwitch();
  }

  // Test 7 check the user read access in a trusted RAM area (only read allowed) defined by
  //[ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS -- ECUM_RAM_MEMORY_END_USER_WX_PROHIBITED_ACCESS]

  // Reset Hard Fault counter
  EcuM_ulHardFaultErrCnt = 0u;

  // Read access -> no Hard Fault
  ulMPUTemp = *(volatile uint32*)(ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS + 8u);

#ifdef UNIT_TEST

  //////////////////////////////////////////////
  // Special HardFault exception ISR code instrumentation for UT
  ///////////////////////////////////////////////

  EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_7();

#endif

  // Check Hard Fault counter (should be not incremented)
  if (EcuM_ulHardFaultErrCnt != 0u)
  {
    // Increment self test error
    EcuM_ucMPUSelfTestErrCnt++;

    // Get Core Privilege level
    EcuM_GetMcuPrivilegeStatus();

    // If USER
    if (EcuM_ulMcuPrivStatus == 0u)
    {
      // Switch to privilege
      EcuM_PrivilegeSwitch();
    }

    // Clear error flags
    MPU->CESR |= (uint32)((uint32)EcuM_sMpuErrState.ucMPUErrorFlags << 27u);

    // MPU re-enable - disable caused by hard fault recovery
    MPU->CESR |= (uint32)(0x01u);
  }
  else
  {
   // Behavior ok, skip
  }


  //  Update the MPU Self Test Global Status
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res = (ulLocalErrCnt != EcuM_ucMPUSelfTestErrCnt) ? ECUM_MPU_SELF_TEST_RESULT_FAIL : ECUM_MPU_SELF_TEST_RESULT_PASS;
}
#endif

//-----------------------------------------------------------------------------
/// \brief EcuM_MPU_SelfTest_Test_8
///
/// \descr MPU seftest - subtest[8] - User write to a trusted RAM Area (Privilege read, write, executed allowed, user read allowed) - FAULTY access test
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (ECUM_SELFTEST_MPU == STD_ON)
// PRQA S 3006 1 // program architecture and readability
STATIC_AL void EcuM_MPU_SelfTest_Test_8(void)
{

  uint32 ulMPUTemp = 0u;
  uint32 ulLocalErrCnt = EcuM_ucMPUSelfTestErrCnt;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus != 0u)
  {
    // Switch to user mode
    EcuM_UserSwitch();
  }

  // Test 8 check the user write access in a trusted RAM area (only read allowed) defined by
  //[ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS -- ECUM_RAM_MEMORY_END_USER_WX_PROHIBITED_ACCESS]

  // Reset Hard Fault counter
  EcuM_ulHardFaultErrCnt = 0u;

  // Write access -> Hard Fault
  *(volatile uint32*)(ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS + 16u) = ulMPUTemp;

  // Small delay
  for (uint8_least ucIx = 0u; ucIx < 5u; ucIx++)
  {
    __asm volatile("nop");
  }

#ifdef UNIT_TEST

  //////////////////////////////////////////////
  // Special HardFault exception ISR code instrumentation for UT
  ///////////////////////////////////////////////

  EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_8();

#endif

  // Check Hard Fault counter (should be incremented)
  if (EcuM_ulHardFaultErrCnt != 1u)
  {
    // Increment self test error
    EcuM_ucMPUSelfTestErrCnt++;
  }
  else
  {
    //MPU error shall be reported
    if (EcuM_sMpuErrState.boMPUErrorStatus == FALSE)
    {
      // Increment self test error
      EcuM_ucMPUSelfTestErrCnt++;
    }
    else
    {
      // SRAM_U error on slave port 3
      if (EcuM_sMpuErrState.ucMPUErrorFlags != 0x2u)
      {
        // Increment self test error
        EcuM_ucMPUSelfTestErrCnt++;
      }
      else
      {
        //Check faulty address
        if (EcuM_sMpuErrState.ulMPUAddressError[3] != (ECUM_RAM_MEMORY_START_USER_WX_PROHIBITED_ACCESS + 16u))
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (EATR) - User
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 1u) & (uint32)0x07u) != 0x1u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
        // Check the MPU error info (ERW) - Write
        if (((EcuM_sMpuErrState.ulMPUDetailedError[3] >> 0u) & (uint32)0x01u) != 0x1u)
        {
          // Increment self test error
          EcuM_ucMPUSelfTestErrCnt++;
        }
      }

      // Get Core Privilege level
      EcuM_GetMcuPrivilegeStatus();

      // If USER
      if (EcuM_ulMcuPrivStatus == 0u)
      {
        // Switch to privilege
        EcuM_PrivilegeSwitch();
      }

      // Clear error flags
      MPU->CESR |= (uint32)((uint32)EcuM_sMpuErrState.ucMPUErrorFlags << 27u);
    }
  }

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If USER
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

  // MPU re-enable
  MPU->CESR |= (uint32)(0x01u);


  //  Update the MPU Self Test Global Status
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = (ulLocalErrCnt != EcuM_ucMPUSelfTestErrCnt) ? ECUM_MPU_SELF_TEST_RESULT_FAIL : ECUM_MPU_SELF_TEST_RESULT_PASS;

  // PRQA S 5310 1 // program architecture and readability
}
#endif


//-----------------------------------------------------------------------------
/// \brief EcuM_ECCProtEnable
///
/// \descr ECC protection enabling procedure over RAM and Flash memory
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_ECCProtEnable(void)
{

  /////////////////////////////
  // Enable ECC protection in MCM
  ////////////////////////////

  // Check SRAM_L/ SRAM_U ECC protection
  for (uint8_least ucRamIdx = 0u; ucRamIdx < ECUM_RAM_PORTS_NR; ucRamIdx++)
  {
    // Check and update control field 0 for SRAM_L/SRAM_U
    if ((MCM->LMDR[0] & 0x0000000Fu) != 0x00000003u)
    {
      // Check Lock Bit
      if ((MCM->LMDR[0] & 0x00010000u) == 0u)
      {
        // Update the ECC enable protection
        MCM->LMDR[0] |= 0x00000003u;
      }
      else
      {
        // Lock written and no chance to update it
      }
    }
    else
    {
      // Control field already updated
    }
  }

  // Check PC Cache ECC protection
  // Check and update control field 0 for SRAM_L
  if ((MCM->LMDR2 & 0x000000F0u) != 0x000000A0u)
  {
    // Check Lock Bit
    if ((MCM->LMDR2 & 0x00010000u) == 0u)
    {
      MCM->LMDR[0] |= 0x000000A0u;
    }
    else
    {
      // Lock written and no chance to update it
    }
  }
  else
  {
    // Control field already updated
  }

  /////////////////////////////
  // Enable ERM
  ////////////////////////////

  // Clear ERM flags
  ERM->SR0 = 0xCC000000u;

  // RAM_L SBC (Single Bit Correction Interrupt Enable)
  ERM->CR0 |= 0x80000000u;
  // RAM_L NCE (Non Correctable Interrupt Enable)
  ERM->CR0 |= 0x40000000u;

  // RAM_U SBC (Single Bit Correction Interrupt Enable)
  ERM->CR0 |= 0x08000000u;
  // RAM_U NCE (Non Correctable Interrupt Enable)
  ERM->CR0 |= 0x04000000u;

  // Flash controller Double Bit error enable
  FTFC->FERCNFG |= (uint8)0x02u;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Inject_RAM_SEC_ECCError
///
/// \descr Single Bit Coretable error injection in RAM_L, RAM_U
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Inject_RAM_SEC_ECCError(void)
{
  // Temporary purpose variables
  volatile uint32 ulRamValueRaw = 0u, ulTemp = 0u;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If User
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

#ifndef UNIT_TEST
  // Read Vale from RAM_L
  ulRamValueRaw = *(volatile uint32*)(0x1FFFC000u);
#endif

  // Invert last bit for Single Bit Error
  EIM->EICHDn[0].WORD1 = (uint32)0x1u;

  // RAM_L ECC enable
  EIM->EICHEN |= (uint32)0x80000000u;

  // EIM module enable
  EIM->EIMCR |= (uint32)0x00000001u;

#ifndef UNIT_TEST
  // Read Back - Error trigger (ERM ISR)
  ulTemp = *(volatile uint32*)(0x1FFFC000u);
#endif

  // RAM_L ECC disable
  EIM->EICHEN &= (uint32)(~(uint32)0x80000000u);

  // EIM module disable
  EIM->EIMCR &= (uint32)(~(uint32)0x00000001u);

#ifndef UNIT_TEST
  // Restore Vale from RAM_L
  *(volatile uint32*)(0x1FFFC000u) = ulRamValueRaw;

  // Read Vale from RAM_U
  ulRamValueRaw = *(volatile uint32*)(0x20001000u);
#endif

  // Invert last bit for Single Bit Error
  EIM->EICHDn[1].WORD1 = (uint32)0x1u;

  // RAM_U ECC enable
  EIM->EICHEN |= (uint32)0x40000000u;

  // EIM module enable
  EIM->EIMCR |= (uint32)0x00000001u;

#ifndef UNIT_TEST
  // Read Back - Error trigger (ERM ISR)
  ulTemp = *(volatile uint32*)(0x20001000u);
#endif

  // RAM_U ECC disable
  EIM->EICHEN &= (uint32)(~(uint32)0x40000000u);

  // EIM module disable
  EIM->EIMCR &= (uint32)(~(uint32)0x00000001u);

#ifndef UNIT_TEST
  // Restore Vale from RAM_U
  *(volatile uint32*)(0x20001000u) = ulRamValueRaw;
#endif

  // If Privilege
  if (EcuM_ulMcuPrivStatus != 0u)
  {
    // Switch to User
    EcuM_UserSwitch();
  }

  //  EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt shall be +1!
  //  EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt shall be +1!
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Inject_RAM_DED_ECCError
///
/// \descr Double Bit Uncorectable error injection in RAM_L, RAM_U
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Inject_RAM_DED_ECCError(void)
{
  // Temporary purpose variables
  volatile uint32 ulRamValueRaw = 0u, ulTemp = 0u;

  // Get Core Privilege level
  EcuM_GetMcuPrivilegeStatus();

  // If User
  if (EcuM_ulMcuPrivStatus == 0u)
  {
    // Switch to privilege
    EcuM_PrivilegeSwitch();
  }

  // Invert last 2 bits for Double Bit Error
  EIM->EICHDn[0].WORD1 = (uint32)0x3u;

  // RAM_L ECC enable
  EIM->EICHEN |= (uint32)0x80000000u;

  // EIM module enable
  EIM->EIMCR |= (uint32)0x00000001u;

#ifndef UNIT_TEST
  // Read Back - Error trigger (ERM ISR)
  ulTemp = *(volatile uint32*)(0x1FFFC000u);
#endif

  // RAM_L ECC disable
  EIM->EICHEN &= (uint32)(~(uint32)0x80000000u);

  // EIM module disable
  EIM->EIMCR &= (uint32)(~(uint32)0x00000001u);

  // Invert last 2 bits for Double Bit Error
  EIM->EICHDn[1].WORD1 = (uint32)0x3u;

  // RAM_U ECC enable
  EIM->EICHEN |= (uint32)0x40000000u;

  // EIM module enable
  EIM->EIMCR |= (uint32)0x00000001u;

#ifndef UNIT_TEST
  // Read Back - Error trigger (ERM ISR)
  ulTemp = *(volatile uint32*)(0x20001000u);
#endif

  // RAM_U ECC disable
  EIM->EICHEN &= (uint32)(~(uint32)0x40000000u);

  // EIM module disable
  EIM->EIMCR &= (uint32)(~(uint32)0x00000001u);

  // If Privilege
  if (EcuM_ulMcuPrivStatus != 0u)
  {
    // Switch to User
    EcuM_UserSwitch();
  }

  //  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt shall be +1!
  //  EcuM_ulECC_RAM_U_DED_Irq_ErrCnt shall be +1!
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Inject_FLASH_DED_ECCError
///
/// \descr Flash double bit injection procedure by Sw
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Inject_FLASH_DED_ECCError(void)
{
  // Inject a flash double bit error
  FTFC->FERCNFG |= (uint8)0x20u;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_CheckNonCorectableMemErrors
///
/// \descr Return the ECC Uncorectable error status based on RAM_L, RAM_U and Flash ports
///
/// \param  void
///
/// \return  boolean - TRUE: ECC Uncorectable error present
//-----------------------------------------------------------------------------
STATIC_AL boolean EcuM_CheckNonCorectableMemErrors(void)
{
  // Return value
  boolean boRetVal = FALSE;

  // Evaluate the uncorectable error counters and return based on that
  // PRQA S 3415 1 // program architecture and readability
  boRetVal = ((EcuM_ulECC_RAM_L_DED_Irq_ErrCnt > 0u) || (EcuM_ulECC_RAM_U_DED_Irq_ErrCnt > 0u) || (EcuM_ulECC_Flash_NCE_Irq_ErrCnt > 0u)) ? TRUE : FALSE;

  return boRetVal;
}

//-----------------------------------------------------------------------------
/// \brief ERM_single_fault_IRQHandler
///
/// \descr Ram Single Bit Corectable Error Reporter Irq
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void ERM_single_fault_IRQHandler(void)
{
  // Check if the error was caused by EIM
  if ((EIM->EIMCR & (uint32)0x01) != 0u)
  {
    // Disable EIM in this case
    EIM->EIMCR &= (uint32)(~(uint32)0x01u);
  }

  // Check the RAM_L port
  if ((ERM->SR0 & 0x80000000u) != 0u)
  {
    // Clear the Single Bit Corectable error for RAM_L
    ERM->SR0 = 0x80000000u;
    // Increment the RAM_L Single Bit Error Event Counter
    EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt++;
  }
  
  // Check the RAM_U port
  if ((ERM->SR0 & 0x08000000u) != 0u)
  {
    // Clear the Single Bit Corectable error for RAM_U
    ERM->SR0 = 0x08000000u;
    // Increment the RAM_U Single Bit Error Event Counter
    EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt++;
  }
}

//-----------------------------------------------------------------------------
/// \brief ERM_double_fault_IRQHandler
///
/// \descr Ram Multi Bit Uncorectable Error Reporter Irq
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void ERM_double_fault_IRQHandler(void)
{
  // Check if the error was caused by EIM
  if ((EIM->EIMCR & (uint32)0x01u) != 0u)
  {
    // Disable EIM in this case
    EIM->EIMCR &= (uint32)(~(uint32)0x01u);
  }

  // Check the RAM_L port
  if ((ERM->SR0 & 0x40000000u) != 0u)
  {
    // Clear the Multi Bit Non-Corectable error for RAM_L
    ERM->SR0 = 0x40000000u;
    // Increment the RAM_L Double Bit Error Event Counter
    EcuM_ulECC_RAM_L_DED_Irq_ErrCnt++;
  }

  // Check the RAM_U port
  if ((ERM->SR0 & 0x04000000u) != 0u)
  {
    // Clear the Multi Bit Non-Corectable error for RAM_U
    ERM->SR0 = 0x04000000u;
    // Increment the RAM_U Double Bit Error Event Counter
    EcuM_ulECC_RAM_U_DED_Irq_ErrCnt++;
  }
}


//-----------------------------------------------------------------------------
/// \brief FTFC_IRQHandler
///
/// \descr Flash Double Bit Error Irq Handler
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void FTFC_Fault_IRQHandler(void)
{
  // Clear Injection bit if it is set
  if ((FTFC->FERCNFG & 0x20u) != 0u)
  {
    // Clear FDFD bit
    FTFC->FERCNFG &= (uint8)(~(uint8)0x20u);
  }

  // Clear Double error flag (DFDIF)
  FTFC->FERSTAT = 0x02u;

  // Increment the Flash Double Bit Error Event Counter
  EcuM_ulECC_Flash_NCE_Irq_ErrCnt++;
}


//-----------------------------------------------------------------------------
/// \brief EcuM_ClockCfg_Consistency_Check
///
/// \descr Check Clock errors
///
/// \param  
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL boolean EcuM_ClockCfg_Consistency_Check(void)
{
  uint32 ulClockCfgErr_Cnt = 0u;

  // Check System OSC clock - SOSCERR bit
  if ((SCG->SOSCCSR & 0x04000000u) != 0u)
  {
    ulClockCfgErr_Cnt++;
  }

  // Check Fast IRC clock - FIRCERR bit
  if ((SCG->FIRCCSR & 0x04000000u) != 0u)
  {
    ulClockCfgErr_Cnt++;
  }

  //Check SPLL Clock - SPLLERR
  if ((SCG->SPLLCSR & 0x04000000u) != 0u)
  {
    ulClockCfgErr_Cnt++;
  }

  return (ulClockCfgErr_Cnt == 0u) ? TRUE : FALSE;
}
//-----------------------------------------------------------------------------
/// \brief EcuM_InvalidInterrupt_Reset
///
/// \descr Invalid and Unused Interrupt Reset Handler (called from startup_s32k14x.s)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_InvalidInterrupt_Reset(void)
{
  // Mcu Perform Reset
  Mcu_PerformReset();
}

//-----------------------------------------------------------------------------
/// \brief EcuM_CheckAppCrc
///
/// \descr Checking APP CRC fail status and react to it
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_CheckAppCrc(void)
{
  // Counter for time selective checking
  STATIC_UT(uint8_least, ucCounter, 0u);

  if (ucCounter >= ECUM_CRC_APP_CYCLIC_CHECK_TIME_MS)
  {
    if (EcuM_boFlashCrcFailure != FALSE)
    {
      // Store sha data app crc fail reason
      ECUM_CRC_APPL_ERROR_MEM = ECUM_FAIL_VAL;
      // Mcu Perform Reset
      Mcu_PerformReset();
    }
    ucCounter = 0u;
  }

  ucCounter++;
}


#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief EcuM_Get_Mpu_Test_Hook_Address
///
/// \descr Local address provider function for untrusted component (MPU fault hook)
///
/// \param  void
///
/// \return void *
//-----------------------------------------------------------------------------
void * EcuM_Get_Mpu_Test_Hook_Address(void)
{
  // PRQA S 312 1 // Lost pointer qualification no impact since this function is used as hook for validation purpose
  return (void*)&EcuM_ulMPU_Fault_Hook_Addr;
}
#endif


//-----------------------------------------------------------------------------
/// \brief EcuM_Check_MPU_Errors
///
/// \descr MPU fault DTC logger based on BusFault recorder counter get from Os (Set internal DTC)
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_MPU_Errors(void)
{
  // Counter for time selective checking
  STATIC_UT(uint8_least, ucCounter1,         0u);
  STATIC_UT(uint8_least, ulBusFaultCnt_Last, 0u);
  uint32 ulBusFaultCnt = 0u;

  // Once at 100ms check MPU faults
  if (ucCounter1 >= ECUM_MPU_CYCLIC_CHECK_TIME_MS)
  {
    // Get BusFault Counter recorded
    ulBusFaultCnt = Os_Get_BusFaultCnt();
    // Write on RTE the number of BusFaults
    (void)Rte_Write_MPU_ErrorCounter(&ulBusFaultCnt);
    // New BusFault recorded
    if (ulBusFaultCnt_Last != ulBusFaultCnt)
    {
      // Set MPU fault (Internal DTC)
      Rte_Call_DemPrj_ReportErrorStatus((uint16)MPU_Error, DEM_EVENT_STATUS_FAILED);
      // Update the BusFault Counter
      ECUM_MPU_CNT_ERROR_MEM = (ulBusFaultCnt < 0xFFFFu) ? (uint16)ulBusFaultCnt : 0xFFFFu;
    }
    // Reset time counter
    ucCounter1 = 0u;
    // Take the last BusFault Counter
    ulBusFaultCnt_Last = ulBusFaultCnt;
  }

  ucCounter1++;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_InitShaDataMem
///
/// \descr ShaData Ram initialization (no ECC error)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_InitShaDataMem(void)
{
  volatile uint32 ulData = 0u;
  volatile uint32* pulShaDataAddress = (uint32*)ECUM_SHA_DATA_MEM_ADDRESS_START;

  // Read-Rewrite the shadata memory (ecc errors are eliminated)
  for (uint8_least ucId = 0u; ucId < (ECUM_SHA_DATA_MEM_ADDRESS_LIMIT - ECUM_SHA_DATA_MEM_ADDRESS_START); ucId += 4u)
  {
    ulData = *pulShaDataAddress;
    *pulShaDataAddress = ulData;
    pulShaDataAddress++;
  }
}

#ifdef UNIT_TEST

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_1
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_1(void)
{

  STATIC_UT(boolean, EcuM_boTriggerHardFault_MPUST1,  FALSE);
  STATIC_UT(boolean, EcuM_boUpdateMPUReg_MPUST1,      FALSE);

  // Test Passed
  if (EcuM_boTriggerHardFault_MPUST1 != FALSE)
  {
    if (EcuM_boUpdateMPUReg_MPUST1 != FALSE)
    {
      // Fill the data for MPU - UT Passed
      MPU->CESR |= 0x2u << 27u;
      MPU->EAR_EDR[0].EAR = 0u;
      MPU->EAR_EDR[0].EDR = 0u;
      MPU->EAR_EDR[1].EAR = 0u;
      MPU->EAR_EDR[1].EDR = 0u;
      MPU->EAR_EDR[2].EAR = 0u;
      MPU->EAR_EDR[2].EDR = 0u;
      MPU->EAR_EDR[3].EAR = ((uint32)&ulEcuM_Mpu_SelfTest[0]) + 4u;
      MPU->EAR_EDR[3].EDR = 0x3u << 1u;
      EcuM_boUpdateMPUReg_MPUST1 = FALSE;
    }
    HardFault_Handler();
    EcuM_boTriggerHardFault_MPUST1 = FALSE;
  }
  else
  {
    // Test Failed
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_2
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_2(void)
{
  STATIC_UT(boolean, EcuM_boTriggerHardFault_MPUST2,  FALSE);
  STATIC_UT(boolean, EcuM_boUpdateMPUReg_MPUST2,      FALSE);

  if (EcuM_boTriggerHardFault_MPUST2 != FALSE)
  {
    if (EcuM_boUpdateMPUReg_MPUST2 != FALSE)
    {
      // Fill the data for MPU - UT Passed
      MPU->CESR |= 0x2u << 27u;
      MPU->EAR_EDR[0].EAR = 0u;
      MPU->EAR_EDR[0].EDR = 0u;
      MPU->EAR_EDR[1].EAR = 0u;
      MPU->EAR_EDR[1].EDR = 0u;
      MPU->EAR_EDR[2].EAR = 0u;
      MPU->EAR_EDR[2].EDR = 0u;
      MPU->EAR_EDR[3].EAR = ((uint32)&ulEcuM_Mpu_SelfTest[0]) + 16u;
      MPU->EAR_EDR[3].EDR = (0x3u << 1u) | 0x1u;
      EcuM_boUpdateMPUReg_MPUST2 = FALSE;
    }
    HardFault_Handler();
    EcuM_boTriggerHardFault_MPUST2 = FALSE;
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_3
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_3(void)
{

  STATIC_UT(boolean, EcuM_boTriggerHardFault_MPUST3,  FALSE);
  STATIC_UT(boolean, EcuM_boUpdateMPUReg_MPUST3,      FALSE);

  if (EcuM_boTriggerHardFault_MPUST3 != FALSE)
  {
    if (EcuM_boUpdateMPUReg_MPUST3 != FALSE)
    {
      // Fill the data for MPU - UT Passed
      MPU->CESR |= 0x2u << 27u;
      MPU->EAR_EDR[0].EAR = 0u;
      MPU->EAR_EDR[0].EDR = 0u;
      MPU->EAR_EDR[1].EAR = 0u;
      MPU->EAR_EDR[1].EDR = 0u;
      MPU->EAR_EDR[2].EAR = 0u;
      MPU->EAR_EDR[2].EDR = 0u;
      MPU->EAR_EDR[3].EAR = ((uint32)&ulEcuM_Mpu_SelfTest[0]) + 8u;
      MPU->EAR_EDR[3].EDR = (0x1u << 1u);
      EcuM_boUpdateMPUReg_MPUST3 = FALSE;
    }
    HardFault_Handler();
    EcuM_boTriggerHardFault_MPUST3 = FALSE;
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_4
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_4(void)
{

  STATIC_UT(boolean, EcuM_boTriggerHardFault_MPUST4,  FALSE);
  STATIC_UT(boolean, EcuM_boUpdateMPUReg_MPUST4,      FALSE);

  if (EcuM_boTriggerHardFault_MPUST4 != FALSE)
  {
    if (EcuM_boUpdateMPUReg_MPUST4 != FALSE)
    {
      // Fill the data for MPU - UT Passed
      MPU->CESR |= 0x2u << 27u;
      MPU->EAR_EDR[0].EAR = 0u;
      MPU->EAR_EDR[0].EDR = 0u;
      MPU->EAR_EDR[1].EAR = 0u;
      MPU->EAR_EDR[1].EDR = 0u;
      MPU->EAR_EDR[2].EAR = 0u;
      MPU->EAR_EDR[2].EDR = 0u;
      MPU->EAR_EDR[3].EAR = ((uint32)&ulEcuM_Mpu_SelfTest[0]) + 24u;
      MPU->EAR_EDR[3].EDR = (0x1u << 1u) | 0x1u;
      EcuM_boUpdateMPUReg_MPUST4 = FALSE;
    }
    HardFault_Handler();
    EcuM_boTriggerHardFault_MPUST4 = FALSE;
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_5
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_5(void)
{

  STATIC_UT(boolean, EcuM_boTriggerHardFault_MPUST5,    FALSE);

  if (EcuM_boTriggerHardFault_MPUST5 != FALSE)
  {
    HardFault_Handler();
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_6
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_6(void)
{

  STATIC_UT(boolean, EcuM_boTriggerHardFault_MPUST6,    FALSE);

  if (EcuM_boTriggerHardFault_MPUST6 != FALSE)
  {
    HardFault_Handler();
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_7
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_7(void)
{

  STATIC_UT(boolean, EcuM_boTriggerHardFault_MPUST7, FALSE);

  if (EcuM_boTriggerHardFault_MPUST7 != FALSE)
  {
    HardFault_Handler();
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_8
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_MPU_SelfTest_8(void)
{

  STATIC_UT(boolean, EcuM_boTriggerHardFault_MPUST8,  FALSE);
  STATIC_UT(boolean, EcuM_boUpdateMPUReg_MPUST8,      FALSE);

  if (EcuM_boTriggerHardFault_MPUST8 != FALSE)
  {
    if (EcuM_boUpdateMPUReg_MPUST8 != FALSE)
    {
      // Fill the data for MPU - UT Passed
      MPU->CESR |= 0x2u << 27u;
      MPU->EAR_EDR[0].EAR = 0u;
      MPU->EAR_EDR[0].EDR = 0u;
      MPU->EAR_EDR[1].EAR = 0u;
      MPU->EAR_EDR[1].EDR = 0u;
      MPU->EAR_EDR[2].EAR = 0u;
      MPU->EAR_EDR[2].EDR = 0u;
      MPU->EAR_EDR[3].EAR = ((uint32)&ulEcuM_Mpu_SelfTest[0]) + 16u;
      MPU->EAR_EDR[3].EDR = (0x1u << 1u) | 0x1u;
      EcuM_boUpdateMPUReg_MPUST8 = FALSE;
    }
    HardFault_Handler();
    EcuM_boTriggerHardFault_MPUST8 = FALSE;
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_RAM_SEC_Injection
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_RAM_SEC_Injection(void)
{

  STATIC_UT(boolean, EcuM_boTriggerSEC_ISR_Test,    FALSE);

  if (EcuM_boTriggerSEC_ISR_Test != FALSE)
  {
    // Simulate error
    ERM->SR0 = 0x80000000u;
    ERM_single_fault_IRQHandler();
    ERM->SR0 = 0x08000000u;
    ERM_single_fault_IRQHandler();
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_RAM_DED_Injection
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_RAM_DED_Injection(void)
{
  STATIC_UT(boolean, EcuM_boTriggerDED_ISR_Test, FALSE);

  if (EcuM_boTriggerDED_ISR_Test != FALSE)
  {
    // Simulate error
    ERM->SR0 = 0x40000000u;
    ERM_double_fault_IRQHandler();
    ERM->SR0 = 0x04000000u;
    ERM_double_fault_IRQHandler();
  }
}
//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_Flash_NCE_Injection
///
/// \descr Special UT instrumentation handler (simulates ISRs and exception)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_Flash_NCE_Injection(void)
{

  STATIC_UT(boolean, EcuM_boTriggerFNCE_ISR_Test, FALSE);

  if (EcuM_boTriggerFNCE_ISR_Test != FALSE)
  {
    // Simulate error
    FTFC_Fault_IRQHandler();
  }
}

//-----------------------------------------------------------------------------
/// \brief EcuM_Check_For_Special_UT_Instrumentation_NvM_Ready
///
/// \descr Special UT instrumentation handler - Simulates the NvM behavior
///
/// \param  pNvmResult - Result Out
/// \param  ulTime - Time-Out
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void EcuM_Check_For_Special_UT_Instrumentation_NvM_Ready(NvM_RequestResultType *pNvmResult, uint32 *ulTime)
{

  static uint8 ucCntTest = 0u;
  STATIC_UT(uint8, EcuM_WaitNvMReady_WhileTestMode, 0u);

  // Force while exit
  if (EcuM_WaitNvMReady_WhileTestMode == 0x55u)
  {
    *pNvmResult = NVM_REQ_OK;
    *ulTime = 100u;
  }
  else if (EcuM_WaitNvMReady_WhileTestMode == 0xAAu)
  {
    if (ucCntTest < 5u)
    {
      *pNvmResult = NVM_REQ_PENDING;
      *ulTime = 1000u * ucCntTest;
      ucCntTest++;
    }
    else
    {
      *pNvmResult = NVM_REQ_OK;
      ucCntTest = 0u;
    }
  }
  else
  {
    // skip the while instrumentation
  }
}
#endif

// EOF
