// PRQA S  881 EOF
// PRQA S 3411 EOF

// NOTE: Do not implement any file guard.

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
/// \file   OsMacEvent.h
///
/// \brief  Generic multitasking scheduler in C.
///         Preprocessor macros for the task enum list
///         and event RAM array list.
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
#if defined(AL_MAC_OS_EVENT_ID)
  #define BEGIN_OS_EVENT_MAP() static EventType EventList[] = {
  #define EVENT_CFG(FUNC)      { const Task##FUNC##_ID, 0 },
  #define END_OS_EVENT_MAP()   { TaskMax_ID,         0 } };
#else
  #if !defined(EVENT_CFG)
  #define EVENT_CFG(FUNC, INDEX)
  #endif
#endif
