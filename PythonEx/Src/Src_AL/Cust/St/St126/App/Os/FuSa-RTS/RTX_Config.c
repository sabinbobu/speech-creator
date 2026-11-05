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
 * $Revision:   V5.1.0
 *
 * Project:     CMSIS-RTOS RTX
 * Title:       RTX Configuration
 *
 * -----------------------------------------------------------------------------
 */
 

#include <Rte.h>
#include "cmsis_compiler.h"
#include "rtx_os.h"
#include <Util_Time.h>
#include "RTX_Config_CPUload.h"

#define RTX_CPULOAD_TIME_MS 10000u

static RTX_tsCPULoad_CheckPoint RTX_sIdleThread = { .ulTimeEntry = 0u, .ulTimeExit = 0u, .boEventEntry = FALSE, .boEventExit = FALSE };
static uint32  RTX_ulIdleTimeAcumulator = 0u;
static uint32  RTX_ulCPULoad = 0u;
static uint32  RTX_ulCnt1ms = 0u;
static boolean RTX_boEvaluateCPULoad_Status = FALSE;
static boolean boGetIdleInfo_Flag = FALSE;

// OS Idle Thread
__WEAK __NO_RETURN void osRtxIdleThread (void *argument) {
  (void)argument;

  for (;;) {}
}
 
// OS Error Callback function
__WEAK uint32_t osRtxErrorNotify (uint32_t code, void *object_id) {
  (void)object_id;

  switch (code) {
    case osRtxErrorStackUnderflow:
      // Stack overflow detected for thread (thread_id=object_id)
      break;
    case osRtxErrorISRQueueOverflow:
      // ISR Queue overflow detected when inserting object (object_id)
      break;
    case osRtxErrorTimerQueueOverflow:
      // User Timer Callback Queue overflow detected for timer (timer_id=object_id)
      break;
    case osRtxErrorClibSpace:
      // Standard C/C++ library libspace not available: increase OS_THREAD_LIBSPACE_NUM
      break;
    case osRtxErrorClibMutex:
      // Standard C/C++ library mutex initialization failed
      break;
    default:
      // Reserved
      break;
  }
  for (;;) {}
//return 0U;
}

void RTX_WorkThreadSwitch_Notification(void)
{
  boGetIdleInfo_Flag = TRUE;
  RTX_sIdleThread.boEventExit = TRUE;

  if (RTX_sIdleThread.boEventEntry != FALSE)
  {
    RTX_sIdleThread.ulTimeExit = TimerGetTick();
    RTX_ulIdleTimeAcumulator += TimerGetTimeSince(RTX_sIdleThread.ulTimeEntry);
    RTX_sIdleThread.boEventEntry = FALSE;
  }
}

void RTX_IdleThreadSwitch_Notification(void)
{
  RTX_sIdleThread.boEventEntry = TRUE;
  RTX_sIdleThread.ulTimeEntry = TimerGetTick();
}

void RTX_Timer_Notification(void)
{
  static boolean RTX_boFirst = TRUE;
  if (RTX_ulCnt1ms >= RTX_CPULOAD_TIME_MS)
  {
      if (RTX_boFirst == TRUE)
      {
          RTX_boFirst = FALSE;
          RTX_ulIdleTimeAcumulator = 0u;
          RTX_ulCnt1ms = 0u;
      }
      else
      {
          uint8 ucPeak;

          RTX_boEvaluateCPULoad_Status = TRUE;
          RTX_ulCPULoad = ((RTX_CPULOAD_TIME_MS * 1000u) - RTX_ulIdleTimeAcumulator) * 100u / (RTX_CPULOAD_TIME_MS * 1000u);

          (void)Rte_Read_OS_CPULoadPeak(&ucPeak);

          if (ucPeak < RTX_ulCPULoad)
          {
              ucPeak = RTX_ulCPULoad;
              (void)Rte_Write_OS_CPULoadPeak((uint8)ucPeak);
          }

          (void)Rte_Write_OS_CPULoadAvg((uint8)RTX_ulCPULoad);

          RTX_ulIdleTimeAcumulator = 0u;
          RTX_ulCnt1ms = 0u;

          RTX_boEvaluateCPULoad_Status = FALSE;
      }
  }
  else
  {
    RTX_ulCnt1ms += 1u;
  }
}

void RTX_Custom_IdleTask(void)
{
  if (boGetIdleInfo_Flag != FALSE)
  {
    RTX_IdleThreadSwitch_Notification();
    boGetIdleInfo_Flag = FALSE;
  }
}
