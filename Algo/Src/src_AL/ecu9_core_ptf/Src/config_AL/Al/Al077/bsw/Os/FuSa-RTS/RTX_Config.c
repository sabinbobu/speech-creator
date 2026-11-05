/*
 * Copyright (c) 2013-2021 Arm Limited. All rights reserved.
 *
 * This Software is licensed under an Arm proprietary license.
 *
 * -----------------------------------------------------------------------------
 *
 * $Revision:   V5.2.0
 *
 * Project:     CMSIS-RTOS RTX
 * Title:       RTX Configuration
 *              Original file: Src\Src_ThirdParty\OS\FuSa-RTS\FuSaRTS_V1.10\CortexM0+_Package\FSRTS-SW-00000-r1p1-00rel0\CMSIS\RTOS2\RTX\Config\RTX_Config.c
 *
 * -----------------------------------------------------------------------------
 */
 
#include "cmsis_compiler.h"
#include "rtx_os.h"
 
// OS Idle Thread
__WEAK __NO_RETURN void osRtxIdleThread (void *argument) {
  (void)argument;

  for (;;) {}
}
 
// OS Error Callback function
__WEAK uint32_t osRtxErrorNotify (uint32_t code, void *object_id) {
  (void)object_id;

  switch (code) {
    case osRtxErrorStackOverflow:
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
    case osRtxErrorSVC:
      // Invalid SVC function called (function=object_id)
      break;
    default:
      // Reserved
      break;
  }
  for (;;) {}
//return 0U;
}
