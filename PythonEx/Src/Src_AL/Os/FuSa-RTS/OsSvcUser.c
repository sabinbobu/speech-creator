/*
 * Copyright (c) 2013-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * -----------------------------------------------------------------------------
 *
 * Project:     CMSIS-RTOS RTX
 * Title:       SVC User Table
 *
 * -----------------------------------------------------------------------------
 */

#include <stdint.h>
#include "Os_Main.h"


// -----------------------------------------------------------------------------
// preprocessor definitions
// -----------------------------------------------------------------------------
#define USER_SVC_COUNT  2       // Number of user SVC functions


// -----------------------------------------------------------------------------
// vars, constants
// -----------------------------------------------------------------------------
void * const osRtxUserSVC[1+USER_SVC_COUNT] = 
{
  (void *)USER_SVC_COUNT,
  (void *)Os_SvcAccessReg32,
  (void *)Os_SvcIrqSafeMemcpy,
// ...
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SvcAccessReg32
//
// Svc-User stub function to access peripheral registers in privileged mode
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__attribute__((always_inline)) uint32_t SvcAccessReg32(volatile uint32_t *pRegister, uint32_t ClrMask, uint32_t SetMask)
{
  register uint32_t r0 __asm("r0") = (uint32_t)pRegister;
  register uint32_t r1 __asm("r1") = (uint32_t)ClrMask;
  register uint32_t r2 __asm("r2") = (uint32_t)SetMask;
  register uint32_t result;
  
  __asm volatile ("SVC #1" : "=l" (result) : "l" ((uint32_t)pRegister), "l" (ClrMask), "l" (SetMask) : "cc", "memory");
  
  return (result);
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SvcIrqSafeMemcpy
//
// Svc-User stub function for irq-safe memcpy
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__attribute__((always_inline)) void SvcIrqSafeMemcpy(void* pDest, const void* pSrc, uint32_t ulSize)
{
  register uint32_t r0 __asm("r0") = (uint32_t)pDest;
  register uint32_t r1 __asm("r1") = (uint32_t)pSrc;
  register uint32_t r2 __asm("r2") = (uint32_t)ulSize;
  
  __asm volatile ("SVC #2" : : "l" ((uint32_t)pDest), "l" (pSrc), "l" (ulSize) : "cc", "memory");
}


