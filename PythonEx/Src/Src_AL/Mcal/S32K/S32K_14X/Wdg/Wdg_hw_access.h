/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * NXP Confidential. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */

 /*!
  * @file wdog_hw_access.h
  *
  * @page misra_violations MISRA-C:2012 violations
  *
  * @section [global]
  * Violates MISRA 2012 Advisory Directive 4.9, Function-like macro,
  * 'WDOG_UNLOCK', defined.
  * This macro is needed in order to unlock the WDOG prior to any update. The
  * reason for not using a function is the limited number of bus clocks in which
  * the WDOG can be reconfigured after an unlock sequence.
  *
  */

#ifndef WDOG_HW_ACCESS_H
#define WDOG_HW_ACCESS_H

#include <stddef.h>
#include "device_registers.h"

  /*!
   * @brief Watchdog Timer Hardware Access.
   *
   * This hardware access provides low-level access to all hardware features of the WDOG.
   * @{
   */

   /*******************************************************************************
    * Definitions
    ******************************************************************************/

    /* The dummy read is used in order to make sure that any write to the
     * WDOG registers will be started only after the write of the unlock value was
     * completed.
     */
#define WDOG_UNLOCK32(base)  \
{ \
    (base)->sCounter_Reg = FEATURE_WDOG_UNLOCK_VALUE; \
    (void)(base)->sCounter_Reg; \
}

#define WDOG_UNLOCK16(base)  \
{ \
    (base)->sCounter_Reg.bCNT_LOW = FEATURE_WDOG_UNLOCK16_FIRST_VALUE; \
    (void)(base)->sCounter_Reg; \
    (base)->sCounter_Reg.bCNT_HIGH = FEATURE_WDOG_UNLOCK16_SECOND_VALUE; \
    (void)(base)->sCounter_Reg; \
}

#define WDOG_UNLOCK(base)    \
{ \
    if ((base)->sControl_Status_Reg.bCMD32EN != 0U) \
    { \
        WDOG_UNLOCK32(base); \
    } \
    else \
    { \
        WDOG_UNLOCK16(base); \
    } \
}

     /*******************************************************************************
      * API
      ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

  /*!
   * @name WDOG Common Configurations
   * @{
   */

  /*!
   * @brief Verifies if the WDOG is enabled.
   *
   * This function verifies the state of the WDOG.
   *
   * @param[in] base WDOG base pointer.
   * @return the state of the WDOG.
   */
  static inline bool WDOG_IsEnabled(WDOG_Type * base)
  {
   // return ((base->sControl_Status_Reg.bWdgEnable ) != 0U) ? TRUE : FALSE;
    return ((base->CS & WDOG_CS_EN_MASK) >> WDOG_CS_EN_SHIFT) != 0U;
  }

  /*!
   * @brief Refreshes the WDOG counter
   *
   * @param[in] base WDOG base pointer.
   */
  static inline void WDOG_Trigger(WDOG_Type * base)
  {

    if ((base->CS & WDOG_CS_CMD32EN_MASK) != 0U)
    {
      base->CNT = FEATURE_WDOG_TRIGGER_VALUE;
    }
    else
    {
      base->CNT = FEATURE_WDOG_TRIGGER16_FIRST_VALUE;
      (void)base->CNT;
      base->CNT = FEATURE_WDOG_TRIGGER16_SECOND_VALUE;
    }
  }

  /*!
   * @brief Verifies if the WDOG updates are allowed.
   *
   * This function verifies if software is allowed to reconfigure the WDOG without
   * a reset.
   *
   * @param[in] base WDOG base pointer.
   * @return the state of the WDOG updates:
   *         - false: updates are not allowed
   *         - true: updates are allowed
   */
  static inline bool WDOG_IsUpdateEnabled(WDOG_Type * base)
  {
    //return (base->sControl_Status_Reg.bUpdateEnable != 0U) ? TRUE : FALSE ;
    return ((base->CS & WDOG_CS_UPDATE_MASK) >> WDOG_CS_UPDATE_SHIFT) != 0U;

  }

  /*!
   * @brief Checks if the WDOG is unlocked.
   *
   * This function checks if the WDOG is unlocked. If the module is unlocked,
   * reconfiguration of the registers is allowed.
   *
   * @param[in] base WDOG base pointer.
   * @return true if the module is unlocked, false if the module is locked.
   */
  static inline bool WDOG_IsUnlocked(const WDOG_Type * base)
  {
    //return (base->sControl_Status_Reg.bUnlock != 0U);
    //return ((base->CS & WDOG_CS_UPDATE_MASK) >> WDOG_CS_UPDATE_SHIFT) != 0U;
    return ((base->CS & WDOG_CS_ULK_MASK) >> WDOG_CS_ULK_SHIFT) != 0U;
  }

  /*!
   * @brief Checks if the last configuration of the WDOG was successful.
   *
   * This function checks if the last configuration of the WDOG was successful.
   *
   * @param[in] base WDOG base pointer.
   * @return true if the configuration was successful, false if not.
   */
  static inline bool WDOG_IsReconfigurationComplete(const WDOG_Type * base)
  {
    //return ((base->sControl_Status_Reg.bRcs) != 0U);
    return ((base->CS & WDOG_CS_RCS_MASK) >> WDOG_CS_RCS_SHIFT) != 0U;
  }


#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* WDOG_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
