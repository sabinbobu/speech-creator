// *****************************************************************************
// Os_Cfg.h
// *****************************************************************************

#ifndef __OS_CFG_H
#define __OS_CFG_H


// -----------------------------------------------------------------------------
// preprocessor definitions
// -----------------------------------------------------------------------------
#define OS_MPU_ENABLE                 1   // enable/disable MemoryProtectionUnit
#define OS_AIPS_ENABLE                0   // enable/disable PeripheralProtectionUnit
#define OS_TIMER_RTE_CYCLIC           0   // use SysTick-IRQ (0) or Timer-Thread (1) for RTE_CYCLIC
#define OS_OPTIMIZE_FLASH             0   // 0=Debugging
#define OS_RTE_MONITOR                1
#define OS_USE_EVALBOARD              0
#define OS_NVIC_PRIOGROUPING          5   // 2-bits group priority, 2-bits subpriority

#define OS_MAIN_THREAD_STACKSIZE   1024


// *** EventRecorder Settings (optional) ***
#define EVTREC_ENABLE_OS_MAIN         EventRecordNone // example: (EventRecordAPI | EventRecordOp)
#define EVTREC_ENABLE_OS_MPU          EventRecordNone
#define EVTREC_ENABLE_RTE_CYCLIC      EventRecordNone
#define EVTREC_ENABLE_RTE_THREAD      EventRecordNone
#define EVTREC_ENABLE_SWC             EventRecordNone

// -----------------------------------------------------------------------------
// additional includes
// -----------------------------------------------------------------------------
#include "Os_Chk.h"


#endif // __OS_CFG_H
