///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//=============================================================================
// Includes
//=============================================================================
#include <Mcu.h>
//#include <mcal_reg_access.h>
//#include <cstdint>
#ifndef UNIT_TEST
#include <clock_S32K1xx.h>
#include <Os_SvcUser.h>
#endif

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif


//=============================================================================
// Static functions declarations
//=============================================================================

//namespace
//{
//  bool set_system_core_clock()
//  {
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_sosccsr,
//                      std::uint32_t(UINT32_C(1) << 26)>::reg_set();
//    //SCG->SOSCCSR = SCG_SOSCCSR_SOSCERR(1U);
//
//    // set up OSC clock.
//    // Setup dividers.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_soscdiv,
//                      UINT32_C(0x00000101)>::reg_set();
//    //SCG->SOSCDIV = (SCG_SOSCDIV_SOSCDIV1(1U) |
//    //                SCG_SOSCDIV_SOSCDIV2(1U)  );
//
//    // Set OSC configuration.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_sosccfg,
//                      UINT32_C(0x00000024)>::reg_set();
//    //SCG->SOSCCFG = (SCG_SOSCCFG_EREFS(1U) |
//    //                SCG_SOSCCFG_RANGE(2U)  );
//
//    // Enable clock.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_sosccsr,
//                      UINT32_C(0x00000001)>::reg_set();
//    //SCG->SOSCCSR = (SCG_SOSCCSR_SOSCEN(1U) );
//
//    // Wait for the oscillator clock to become valid.
//    while(mcal::reg::access<std::uint32_t,
//                            std::uint32_t,
//                            mcal::reg::scg_sosccsr,
//                            UINT32_C(24)>::bit_get() == false)
//    {
//      HalCpuNop();
//    }
//    //while (!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD(1U))) __NOP();
//
//    // Init SIRC
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_sirccsr,
//                      UINT32_C(0x00000000)>::reg_set();
//    //SCG->SIRCCSR = 0U;
//
//    // Setup dividers.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_sircdiv,
//                      UINT32_C(0x00000202)>::reg_set();
//    //SCG->SIRCDIV = (SCG_SIRCDIV_SIRCDIV1(1U) |
//    //                SCG_SIRCDIV_SIRCDIV2(1U)  );
//
//    // Set SIRC configuration.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_sirccfg,
//                      UINT32_C(0x00000001)>::reg_set();
//    //SCG->SIRCCFG = SCG_SIRCCFG_RANGE(1U);
//
//    // Enable clock.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_sirccsr,
//                      UINT32_C(0x00000001)>::reg_set();
//    //SCG->SIRCCSR = SCG_SIRCCSR_SIRCEN(1U);
//
//    // Wait for SIRC clock to be valid.
//    while(mcal::reg::access<std::uint32_t,
//                            std::uint32_t,
//                            mcal::reg::scg_sirccsr,
//                            UINT32_C(24)>::bit_get() == false)
//    {
//      HalCpuNop();
//    }
//    //while (!(SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD(1U))) __NOP();
//
//    // Change to SIRC as system clock source
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_rccr,
//                      UINT32_C(0x02000000)>::reg_set();
//    //SCG->RCCR = (SCG_RCCR_DIVSLOW(0U) |
//    //             SCG_RCCR_DIVBUS(0U)  |
//    //             SCG_RCCR_DIVCORE(0U) |
//    //             SCG_RCCR_SCS(2U)     );
//
//    // Wait for clock source switch finished.
//    while((mcal::reg::access<std::uint32_t,
//                            std::uint32_t,
//                            mcal::reg::scg_rccr>::reg_get() & UINT32_C(0x02000000)) != UINT32_C(0x02000000))
//    {
//      HalCpuNop();
//    }
//    //while ((SCG->RCCR & 0x0F000000) != 0x02000000) __NOP();;
//
//    // Init FIRC.SIRC_CLK
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_firccsr,
//                      UINT32_C(0x00000000)>::reg_set();
//    //SCG->FIRCCSR = 0U;
//
//    // Setup dividers.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_fircdiv,
//                      UINT32_C(0x00000101)>::reg_set();
//    //SCG->FIRCDIV = (SCG_FIRCDIV_FIRCDIV1(1U) |
//    //                SCG_FIRCDIV_FIRCDIV2(1U)  );
//
//    // Set FIRC configuration.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_firccfg,
//                      UINT32_C(0x00000000)>::reg_set();
//    //SCG->FIRCCFG = SCG_FIRCCFG_RANGE(0U);
//
//    // Enable clock.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_firccsr,
//                      UINT32_C(0x00000001)>::reg_or();
//    //SCG->FIRCCSR |= SCG_FIRCCSR_FIRCEN(1U);
//
//    // Wait for FIRC clock to be valid.
//    while(mcal::reg::access<std::uint32_t,
//                            std::uint32_t,
//                            mcal::reg::scg_firccsr,
//                            UINT32_C(24)>::bit_get() == false)
//    {
//      HalCpuNop();
//    }
//    //while (!(SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD(1U))) __NOP();;
//
//    // Init SysPll
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_spllcsr,
//                      std::uint32_t(UINT32_C(1) << 26)>::reg_set();
//    //SCG->SPLLCSR = SCG_SPLLCSR_SPLLERR(1U);
//
//    // Setup dividers.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_splldiv,
//                      UINT32_C(0x00000301)>::reg_set();
//    //SCG->SPLLDIV = (SCG_SPLLDIV_SPLLDIV1(1U) |
//    //                SCG_SPLLDIV_SPLLDIV2(1U)  );
//
//    // Set PLL configuration.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_spllcfg,
//                      std::uint32_t(0x00040100)>::reg_set();
//    //SCG->SPLLCFG = (SCG_SPLLCFG_PREDIV(1U) |      // prediv 1
//    //                SCG_SPLLCFG_MULT(4U)   );    // pll multiply 20
//
//    // Enable clock.
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_spllcsr,
//                      UINT32_C(0x00000001)>::reg_set();
//    //SCG->SPLLCSR = SCG_SPLLCSR_SPLLEN(1U);
//
//    // Wait for PLL clock to be valid.
//    while(mcal::reg::access<std::uint32_t,
//                            std::uint32_t,
//                            mcal::reg::scg_spllcsr,
//                            UINT32_C(24)>::bit_get() == false)
//    {
//      HalCpuNop();
//    }
//    //while (!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD(1U))) __NOP();
//
//    // Change to use PLL as system clock source
//    mcal::reg::access<std::uint32_t,
//                      std::uint32_t,
//                      mcal::reg::scg_rccr,
//                      std::uint32_t(  (UINT32_C(7) <<  0)
//                                    | (UINT32_C(0) <<  4)
//                                    | (UINT32_C(0) << 16)
//                                    | (UINT32_C(6) << 24))>::reg_set();
//    //SCG->RCCR = (SCG_RCCR_DIVSLOW(7U) |
//    //             SCG_RCCR_DIVBUS(1U)  |
//    //             SCG_RCCR_DIVCORE(1U) |
//    //             SCG_RCCR_SCS(6U)     );
//    // Wait for clock source switch finished.
//
//    while((mcal::reg::access<std::uint32_t,
//                            std::uint32_t,
//                            mcal::reg::scg_rccr>::reg_get() & UINT32_C(0x0F000000)) != UINT32_C(0x06000000))
//    {
//      HalCpuNop();
//    }
//    //while ((SCG->RCCR & 0x0F000000) != 0x06000000) __NOP();
//
//    bool set_system_core_clock_is_ok = false;
//
//    // Read back the system clock source.
//    const std::uint32_t value_scg_csr =
//      mcal::reg::access<std::uint32_t,
//                        std::uint32_t,
//                        mcal::reg::scg_csr>::reg_get();
//
//    const std::uint32_t system_clock_source_readback =
//      (value_scg_csr & UINT32_C(0x0F000000)) >> 24;
//
//    if(system_clock_source_readback == UINT32_C(6))
//    {
//      // System PLL
//      std::uint32_t scg_output_clock = UINT32_C(8000000);
//
//      const std::uint32_t value_scg_spllcfg =
//        mcal::reg::access<std::uint32_t,
//                          std::uint32_t,
//                          mcal::reg::scg_spllcfg>::reg_get();
//
//      const std::uint32_t prescaler  = ((value_scg_spllcfg & UINT32_C(0x00000700)) >>  8) +  1U;
//      const std::uint32_t multiplier = ((value_scg_spllcfg & UINT32_C(0x001F0000)) >> 16) + 16U;
//      const std::uint32_t divider    = ((value_scg_csr     & UINT32_C(0x000F0000)) >> 16) +  1U;
//
//      scg_output_clock = (scg_output_clock * multiplier) / (prescaler * 1U);
//
//      const std::uint32_t system_core_clock = scg_output_clock / divider;
//
//      // TBD: Set the core system clock to 112MHz
//      set_system_core_clock_is_ok = (system_core_clock == UINT32_C(80000000));
//    }
//
//    return set_system_core_clock_is_ok;
//  }
//}

//=============================================================================
// Public functions definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Mcu initialization function. 
///
/// \descr  The function is initializing the Mcu specific clocks and the
///         peripheral clocks, following the configuration structure form
///         ConfigPtr.
///
/// \param  *ConfigPtr - configuration structure containing the peripheral
///         clock configuration.
///
/// \return void 
//-----------------------------------------------------------------------------

//const uint16_t clockNameMappings[] = PCC_CLOCK_NAME_MAPPINGS;

void Mcu_Init(const Mcu_ConfigType* ConfigPtr)
{
  (void)ConfigPtr;
  // Enable CP10 and CP11 coprocessors
  // PRQA S 306 1 // program architecture and readability - Cast between a pointer to object and an integral type wanted and documented
  S32_SCB->CPACR |= (S32_SCB_CPACR_CP10_MASK | S32_SCB_CPACR_CP11_MASK);

  // Invalidate and enable code cache
  // PRQA S 306 1 // program architecture and readability - Cast between a pointer to object and an integral type wanted and documented
  LMEM->PCCCR = LMEM_PCCCR_INVW0(1) | LMEM_PCCCR_INVW1(1) | LMEM_PCCCR_GO(1) | LMEM_PCCCR_ENCACHE(1);

  /*const bool set_system_core_clock_is_ok = set_system_core_clock();

  static_cast<void>(set_system_core_clock_is_ok);
*/
}

Std_ReturnType Mcu_InitClock(Mcu_ClockType* ClockSetting)
{
  uint16 unRetVal = 0;

  (void)CLOCK_SYS_Init((clock_manager_user_config_t const **)ClockSetting->clockConfigsPtr, // PRQA S 310 // Necessary cast
                 CLOCK_MANAGER_CONFIG_CNT, 
                 (clock_manager_callback_user_config_t **)ClockSetting->callbacksPtr, // PRQA S 310 // Necessary cast
                 CLOCK_MANAGER_CALLBACK_CNT);

  unRetVal = (uint16)CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

  return (unRetVal == 0x00U ? E_OK : E_NOT_OK);
}


Std_ReturnType Mcu_DistributePllClock(void)
{
  return E_OK;
}

Mcu_ResetType Mcu_GetResetReason(void)
{
  Mcu_ResetType resetValue = MCU_RESET_UNDEFINED;

  // PRQA S 306 1 // program architecture and readability - Cast between a pointer to object and an integral type wanted and documented
  switch (RCM->SRS)
  {
    case(RCM_SRS_SACKERR_MASK):
      resetValue = MCU_STOP_ACKNOWLEDGE_ERROR_RESET;
      break;
    case(RCM_SRS_MDM_AP_MASK):
      resetValue = MCU_MDM_AP_SYSTEM_RESET_REQUEST;
      break;
    case(RCM_SRS_SW_MASK):
      resetValue = MCU_SOFTWARE_RESET;
      break;
    case(RCM_SRS_LOCKUP_MASK):
      resetValue = MCU_CORE_LOCKUP;
      break;
    case(RCM_SRS_JTAG_MASK):
      resetValue = MCU_JTAG_GENERATED_RESET;
      break;
    case(RCM_SRS_POR_MASK):
      resetValue = MCU_POWER_ON_RESET;
      break;
    case(RCM_SRS_PIN_MASK):
      resetValue = MCU_EXTERNAL_PIN_RESET;
      break;
    case(RCM_SRS_WDOG_MASK):
      resetValue = MCU_WATCHDOG_RESET;
      break;
    case(RCM_SRS_CMU_LOC_MASK):
      resetValue = MCU_CMU_LOSS_OF_CLOCK_RESET;;
      break;
    case(RCM_SRS_LOL_MASK):
      resetValue = MCU_LOSS_OF_LOCK_RESET;
      break;
    case(RCM_SRS_LOC_MASK):
      resetValue = MCU_LOSS_OF_CLOCK_RESET;
      break;
    case(RCM_SRS_LVD_MASK):
      resetValue = MCU_LOW_VOLTAGE_DETECT_OR_HIGH_VOLTAGE_DETECT_RESET;
      break;
    case(RCM_SRS_POR_MASK | RCM_SRS_LVD_MASK):
      resetValue = MCU_POWER_ON_RESET;
      break;
    default:
      resetValue = MCU_RESET_UNDEFINED;
      break;
  }

  return resetValue;
}

//-----------------------------------------------------------------------------
/// \brief  void Mcu_PerformReset(void)
///
/// \descr  Function to perform software reset
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void Mcu_PerformReset(void)
{
  /* Indicate that it will not be a PowerOn Reset, in case application has not yet reset the flag */
  (void)SvcAccessReg32(&(RCM->SSRS), RCM_SSRS_SPOR_MASK, RCM_SSRS_SPOR(1)); // PRQA S 306 // It's a correct cast because the member we access is a uint32_t as the function parameter

  /* Generating soft reset*/
  (void)SvcAccessReg32(&(S32_SCB->AIRCR), S32_SCB_AIRCR_VECTKEY_MASK, (S32_SCB_AIRCR_VECTKEY(0x5FAU) | S32_SCB_AIRCR_SYSRESETREQ(0x1u))); // PRQA S 306 // It's a correct cast because the member we access is a uint32_t as the function parameter
}

#if 0
int CLOCK_SYS_GetFreq(clock_names_t clockName, uint32_t* frequency)
{
  (void) clockName;

  if(frequency != nullptr)
  {
    *frequency = 80000000UL;
  }

  return 0;
}
#endif
