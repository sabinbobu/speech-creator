#ifndef __OS_EVTREC_H
#define __OS_EVTREC_H

// *****************************************************************************
// Os_EvtRec.h
//
// 
// *****************************************************************************


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// includes
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Os_Cfg.h"


// -----------------------------------------------------------------------------
// preprocessor definitions
// -----------------------------------------------------------------------------
#ifdef RTE_Compiler_EventRecorder
  #include "EventRecorder.h"

  #if defined(EVTREC_ENABLE_OS_MAIN) && (EVTREC_ENABLE_OS_MAIN != EventRecordNone)
    #define OS_EVTREC_ID_MAIN         0x3F

    #define OS_EVTREC_thread_Main_Start           EventID(EventLevelAPI,    OS_EVTREC_ID_MAIN, 0x00)
    #define OS_EVTREC_thread_Idle_Start           EventID(EventLevelAPI,    OS_EVTREC_ID_MAIN, 0x01)
    #define OS_EVTREC_Os_RtePrepare               EventID(EventLevelAPI,    OS_EVTREC_ID_MAIN, 0x10)
    #define OS_EVTREC_Os_RteTriggerInitRunnables  EventID(EventLevelAPI,    OS_EVTREC_ID_MAIN, 0x11)
    #define OS_EVTREC_Os_RteStart                 EventID(EventLevelAPI,    OS_EVTREC_ID_MAIN, 0x12)
    #define OS_EVTREC_OsMain_Internal_Error       EventID(EventLevelError,  OS_EVTREC_ID_MAIN, 0xFF)
  #endif

  #if defined(EVTREC_ENABLE_OS_MPU) && (EVTREC_ENABLE_OS_MPU != EventRecordNone)
    #define OS_EVTREC_ID_MPU          0x3E

    #define OS_EVTREC_MpuInit                     EventID(EventLevelAPI,    OS_EVTREC_ID_MPU,  0x00)
    #define OS_EVTREC_AipsInit                    EventID(EventLevelAPI,    OS_EVTREC_ID_MPU,  0x01)
    #define OS_EVTREC_osZoneSetup_System          EventID(EventLevelOp,     OS_EVTREC_ID_MPU,  0x02)
    #define OS_EVTREC_osRtxMpuLoad_Trusted        EventID(EventLevelOp,     OS_EVTREC_ID_MPU,  0x03)
    #define OS_EVTREC_osRtxMpuLoad_Untrusted      EventID(EventLevelOp,     OS_EVTREC_ID_MPU,  0x04)
    #define OS_EVTREC_OsMpu_Internal_Error        EventID(EventLevelError,  OS_EVTREC_ID_MPU,  0xFF)
  #endif
#endif

#if defined(OS_EVTREC_ID_MAIN) || defined(OS_EVTREC_ID_MPU)
  #define OS_EVTREC2(id, p1, p2)   EventRecord2(id, p1, p2)
#else
  #define OS_EVTREC2(id, p1, p2)
#endif

#endif // __OS_EVTREC_H