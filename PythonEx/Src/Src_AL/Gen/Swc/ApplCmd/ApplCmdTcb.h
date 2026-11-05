#ifndef __APPL_CMD_TCB_01_07_15_H_
#define __APPL_CMD_TCB_01_07_15_H_

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
/// \file   ApplCmdMac.h
///
/// \brief  Alx1 - Generic operating system in C. Command scheduler macros.
///
/// \descr  Preprocessor macros for the task enum list and task RAM and ROM array list. 
///
/// \author Johannes Heusel (F89037A) ALDE-RT/EEG-PM2
///          mailTo:johannes.heusel(at)al-lighting.com
//-----------------------------------------------------------------------------

//=============================================================================
// Public types
//=============================================================================


typedef uint8  (*__ApplCmd_CallbackPrototoype)( MsgContextType *const pMsgContext );


  typedef struct structApplCmd
  {
    const uint32_t id;    
    const uint8_t level;
    boolean  loginRequested;
    const __ApplCmd_CallbackPrototoype function;    
  }
  tApplCmd;

#endif//__APPL_CMD_TCB_01_07_15_H_
