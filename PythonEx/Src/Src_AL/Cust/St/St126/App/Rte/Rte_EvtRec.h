#ifndef __RTE_EVTREC_H
#define __RTE_EVTREC_H

// *****************************************************************************
// Rte_EvtRec.h
//
// 
// *****************************************************************************


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// includes
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Os_Cfg.h"


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// preprocessor definitions
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef RTE_Compiler_EventRecorder
  #include "EventRecorder.h"

  #if defined(EVTREC_ENABLE_RTE_CYCLIC) && (EVTREC_ENABLE_RTE_CYCLIC != EventRecordNone)
    #define RTE_EVTREC_ID_CYCLIC      0x3D

    #define RTE_EVTREC_Cyclic_ThreadFlagsSet          EventID(EventLevelOp,     RTE_EVTREC_ID_CYCLIC, 0x00)
    #define RTE_EVTREC_Cyclic_ThreadFlagsSet_Error    EventID(EventLevelError,  RTE_EVTREC_ID_CYCLIC, 0xF0)
    #define RTE_EVTREC_Cyclic_ThreadFlagRange_Error   EventID(EventLevelError,  RTE_EVTREC_ID_CYCLIC, 0xF1)
    #define RTE_EVTREC_Cyclic_ThreadID_Error          EventID(EventLevelError,  RTE_EVTREC_ID_CYCLIC, 0xF2)
    #define RTE_EVTREC_Cyclic_ThreadIndex_Error       EventID(EventLevelError,  RTE_EVTREC_ID_CYCLIC, 0xF3)
    #define RTE_EVTREC_Cyclic_CyclicIndex_Error       EventID(EventLevelError,  RTE_EVTREC_ID_CYCLIC, 0xF4)
    #define RTE_EVTREC_Cyclic_Internal_Error          EventID(EventLevelError,  RTE_EVTREC_ID_CYCLIC, 0xFF)
  #endif

  #if defined(EVTREC_ENABLE_RTE_THREAD) && (EVTREC_ENABLE_RTE_THREAD != EventRecordNone)
    #define RTE_EVTREC_ID_THREAD      0x3C

    #define RTE_EVTREC_thread_T_HH_Start              EventID(EventLevelAPI,    RTE_EVTREC_ID_THREAD, 0x00)
    #define RTE_EVTREC_thread_T_HL_Start              EventID(EventLevelAPI,    RTE_EVTREC_ID_THREAD, 0x01)
    #define RTE_EVTREC_thread_T_LH_Start              EventID(EventLevelAPI,    RTE_EVTREC_ID_THREAD, 0x02)
    #define RTE_EVTREC_thread_T_LL_Start              EventID(EventLevelAPI,    RTE_EVTREC_ID_THREAD, 0x03)
    #define RTE_EVTREC_thread_U_HH_Start              EventID(EventLevelAPI,    RTE_EVTREC_ID_THREAD, 0x04)
    #define RTE_EVTREC_thread_U_HL_Start              EventID(EventLevelAPI,    RTE_EVTREC_ID_THREAD, 0x05)
    #define RTE_EVTREC_thread_U_LH_Start              EventID(EventLevelAPI,    RTE_EVTREC_ID_THREAD, 0x06)
    #define RTE_EVTREC_thread_U_LL_Start              EventID(EventLevelAPI,    RTE_EVTREC_ID_THREAD, 0x07)

    #define RTE_EVTREC_Thread_T_HH_Runnable           EventID(EventLevelOp,     RTE_EVTREC_ID_THREAD, 0x08)
    #define RTE_EVTREC_Thread_T_HL_Runnable           EventID(EventLevelOp,     RTE_EVTREC_ID_THREAD, 0x09)
    #define RTE_EVTREC_Thread_T_LH_Runnable           EventID(EventLevelOp,     RTE_EVTREC_ID_THREAD, 0x0A)
    #define RTE_EVTREC_Thread_T_LL_Runnable           EventID(EventLevelOp,     RTE_EVTREC_ID_THREAD, 0x0B)
    #define RTE_EVTREC_Thread_U_HH_Runnable           EventID(EventLevelOp,     RTE_EVTREC_ID_THREAD, 0x0C)
    #define RTE_EVTREC_Thread_U_HL_Runnable           EventID(EventLevelOp,     RTE_EVTREC_ID_THREAD, 0x0D)
    #define RTE_EVTREC_Thread_U_LH_Runnable           EventID(EventLevelOp,     RTE_EVTREC_ID_THREAD, 0x0E)
    #define RTE_EVTREC_Thread_U_LL_Runnable           EventID(EventLevelOp,     RTE_EVTREC_ID_THREAD, 0x0F)

    #define RTE_EVTREC_Thread_RunnableInitCall        EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0x20)
    
    #define RTE_EVTREC_Thread_T_HH_Index_Error        EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0xF0)
    #define RTE_EVTREC_Thread_T_HL_Index_Error        EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0xF1)
    #define RTE_EVTREC_Thread_T_LH_Index_Error        EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0xF2)
    #define RTE_EVTREC_Thread_T_LL_Index_Error        EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0xF3)
    #define RTE_EVTREC_Thread_U_HH_Index_Error        EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0xF4)
    #define RTE_EVTREC_Thread_U_HL_Index_Error        EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0xF5)
    #define RTE_EVTREC_Thread_U_LH_Index_Error        EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0xF6)
    #define RTE_EVTREC_Thread_U_LL_Index_Error        EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0xF7)

    #define RTE_EVTREC_Thread_Internal_Error          EventID(EventLevelError,  RTE_EVTREC_ID_THREAD, 0xFF)
  #endif
#endif

#if defined(RTE_EVTREC_ID_CYCLIC) || defined(RTE_EVTREC_ID_THREAD)
  #define RTE_EVTREC2(id, p1, p2)   EventRecord2(id, p1, p2)
#else
  #define RTE_EVTREC2(id, p1, p2)
#endif // (defined(RTE_Compiler_EventRecorder) && (EVTREC_ENABLE_RTE == 1))

#endif // __RTE_EVTREC_H
