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
/// \file  Gpt.c
///
/// \brief Gpt Driver Source File
///
/// \author Cruciu Denis-Mihai (F31196D)
///         mailTo: denis-mihai.cruciu[at]marelli.com
//-----------------------------------------------------------------------------

//====================================================================
// Include files
//====================================================================
#include <Gpt.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

/* PRQA S 303,306,316 EOF */

//====================================================================
// Local data definitions
//====================================================================

/* Status of the Gpt Driver */
#define GPT_DRIVER_UNINITIALIZED        ((uint8_t)0U)
#define GPT_DRIVER_INITIALIZED          ((uint8_t)1U)

//====================================================================
// Local data definitions
//====================================================================

//init status variable
static uint8_t Gpt_DriverStatus = GPT_DRIVER_UNINITIALIZED;

const  Gpt_ConfigType Gpt_ConfigData = (Gpt_ConfigType) 1U;

//=============================================================================
//  Functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Gpt_Init
///
/// \descr  This function initializes the hardware timer module according
///         to a configuration set referenced by ConfigPtr
///
/// \param  Gpt_ConfigType(ConfigPtr): Pointer to Gpt configuration
///
/// \return void
//-----------------------------------------------------------------------------
void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
  (void)ConfigPtr;
  /* SysTick CSR counter is disable*/
  S32_SysTick->CSR = S32_SysTick_CSR_ENABLE_SHIFT;

  /* SysTick Reload Value is set to 0x00FFFFFFu*/
  S32_SysTick->RVR = S32_SysTick_RVR_RELOAD_MASK;

  /*SysTick Counter Value initialized with 0x0u*/
  S32_SysTick->CVR = S32_SysTick_CVR_CURRENT_SHIFT;
  
  /*Set the Clock Source to "Processor clock"*/
  S32_SysTick->CSR |= S32_SysTick_CSR_CLKSOURCE_MASK;

  /*Set the TICKINT to assert the SysTick exception request*/
  S32_SysTick->CSR |= S32_SysTick_CSR_TICKINT_MASK;

  /* SysTick CSR counter is enable*/
  S32_SysTick->CSR |= S32_SysTick_CSR_ENABLE_MASK;
  
  /* Set the driver status to "Initialized" */
  Gpt_DriverStatus = GPT_DRIVER_INITIALIZED;

}

//-----------------------------------------------------------------------------
/// \brief  Gpt_GetTimeElapsed
///
/// \descr  This function return the system tick using a multiple read
///         to ensure data consistency.
///
/// \param  Gpt_ChannelType(Channel): Numeric identifier of the GPT channel
///
/// \return Gpt_ValueType: Elapsed timer value in number of ticks
//-----------------------------------------------------------------------------
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
  (void)Channel;

  volatile uint64_t system_tick;
  /* Return the system tick using a multiple read to ensure data consistency */
  const uint32_t sys_tick_value_1 = S32_SysTick_RVR_RELOAD_MASK - S32_SysTick->CVR ;
  const uint32_t sys_tick_value_2 = S32_SysTick_RVR_RELOAD_MASK - S32_SysTick->CVR ;

  const uint64_t system_tick_gpt = system_tick;


  const uint64_t consistent_tick = (sys_tick_value_2 >= sys_tick_value_1) ? (uint64_t)(system_tick_gpt | sys_tick_value_1)
                                                                          : (uint64_t)(system_tick_gpt | sys_tick_value_2);

  const uint64_t consistent_microsecond_tick = (uint64_t)((consistent_tick + 40U) / 80U);

  return (Gpt_ValueType)consistent_microsecond_tick;

}
