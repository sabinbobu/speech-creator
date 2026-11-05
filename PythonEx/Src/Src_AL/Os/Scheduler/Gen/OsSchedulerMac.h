// PRQA S  881 EOF
// PRQA S 3411 EOF

// NOTE: Do not implement any file guard.
// This file will be multiply included for the macro table generations.

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
/// \file   OsMac.h
///
/// \brief  Generic multitasking scheduler in C.
///         Preprocessor macros for the task enum list
///         and task RAM and ROM array list.
///
/// \author  (ksc2rt)
///         mailTo:       christopher.kormanyos(at)al-lighting.com
//-----------------------------------------------------------------------------

// *****************************************************************************
// includes
// *****************************************************************************

// *****************************************************************************
// macros
// *****************************************************************************
#ifdef BEGIN_OS_TASK_MAP
  #undef  BEGIN_OS_TASK_MAP
  #undef  TASK_CFG
  #undef  END_OS_TASK_MAP
#endif

#if defined(AL_MAC_OS_TASK_ID)
  #define BEGIN_OS_TASK_MAP()  typedef enum OsSchedulerTaskIdType {
  #define TASK_CFG(FUNC, CYCLE, OFFSET)  OsSchedulerTask##FUNC##_ID,
  #define END_OS_TASK_MAP()              OsSchedulerTaskMax_ID } OsSchedulerTaskIdType;


#elif defined(AL_MAC_OS_TASK_PROTOTYPE)
  #define BEGIN_OS_TASK_MAP()
  #define TASK_CFG(FUNC, CYCLE, OFFSET) \
    void Task##FUNC##_Func(void);       \
    void Task##FUNC##_Init(void);       \
    void Task##FUNC##_DeInit(void);
  #define END_OS_TASK_MAP()


#elif defined(AL_MAC_OS_TASK_RAM)
  #define BEGIN_OS_TASK_MAP()  static OsSchedulerTcbVariableRamPart OsScheduler_aTcbVariableRamPart[OsSchedulerTaskMax_ID + 1U] = {
  #define TASK_CFG(FUNC, CYCLE, OFFSET)   { 0U, 0U },
  #define END_OS_TASK_MAP()               { 0U, 0U } };


#elif defined(AL_MAC_OS_TASK_ROM)
  #define BEGIN_OS_TASK_MAP()  static const OsSchedulerTcbConstRomPart OsScheduler_aTcbConstRomPart[OsSchedulerTaskMax_ID + 1U] = {
  #define TASK_CFG(FUNC, CYCLE, OFFSET)   { Task##FUNC##_Func, Task##FUNC##_Init, (CYCLE), (OFFSET) },
  #define END_OS_TASK_MAP()               { (function_type) 0U, (function_type) 0U, 0U, 0U } };

// *****************************************************************************
// preprocessor error handling
// *****************************************************************************
#else
  #error Error, reason for OS task macros undefined!
#endif

#ifndef BEGIN_OS_TASK_MAP
  #error Error OsMac.h can not be included alone, only together with OsCfg.h.
#endif
