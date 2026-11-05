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
/// \file   ApplCmdMac.h
///
/// \brief  Alx1 - Generic operating system in C. Command scheduler macros.
///
/// \descr  Preprocessor macros for the task enum list and task RAM and ROM array list. 
///
/// \author Johannes Heusel (F89037A) ALDE-RT/EEG-PM2
///          mailTo:johannes.heusel(at)al-lighting.com
//-----------------------------------------------------------------------------

// *****************************************************************************
// macros 
// *****************************************************************************
#ifdef BEGIN_APPLCMD_LIST_MAP
  #undef  BEGIN_APPLCMD_LIST_MAP
  #undef  BEGIN_APPLCMD_LEVEL
  #undef  APPLCMD_CFG
  #undef  END_APPLCMD_LEVEL
  #undef  END_APPLCMD_LIST_MAP
#endif

#if defined(MAC_APPLCMD_LEVEL_ENUM)
  #define BEGIN_APPLCMD_LIST_MAP                      typedef enum enumCmdLevel {
  #define BEGIN_APPLCMD_LEVEL(Level)                  eCmdLevel##Level,
  #define APPLCMD_CFG(CMD, Level, SecureAccess, CALLBACK)  
  #define END_APPLCMD_LEVEL(Level)                  
  #define END_APPLCMD_LIST_MAP                        eMaxCmdLevel } enumCmdLevel_type;
 
#elif defined(APPLCMD_MAC_DECL_FCT)
  #define BEGIN_APPLCMD_LIST_MAP
  #define BEGIN_APPLCMD_LEVEL(Level)              
  #define APPLCMD_CFG(CMD, Level, SecureAccess, CALLBACK)  uint8 (CALLBACK)( MsgContextType *const pMsgContext );
  #define END_APPLCMD_LEVEL(Level)                   
  #define END_APPLCMD_LIST_MAP  
  
#elif defined(MAC_APPLCMD_LIST_ID)
  #define BEGIN_APPLCMD_LIST_MAP
  #define BEGIN_APPLCMD_LEVEL(Level)                 typedef enum enumCmdID_##Level {
  #define APPLCMD_CFG(CMD, Level, SecureAccess, CALLBACK)  e##CMD##ID,
#define END_APPLCMD_LEVEL(Level)                   eMaxID_##Level } eCmdID_##Level##_type;
  #define END_APPLCMD_LIST_MAP
  
#elif defined(MAC_APPLCMD_LIST_CALLBACK)
  #define BEGIN_APPLCMD_LIST_MAP
  #define BEGIN_APPLCMD_LEVEL(Level)                 tApplCmd fctCmd_##Level[eMaxID_##Level] = {
  #define APPLCMD_CFG(CMD, Level,  SecureAccess, CALLBACK)  {CMD,  (uint8_t)eCmdLevel##Level, SecureAccess, CALLBACK},
  #define END_APPLCMD_LEVEL(Level)                   };
  #define END_APPLCMD_LIST_MAP

#elif defined(MAC_APPLCMD_LEVEL_LIST)
  #define BEGIN_APPLCMD_LIST_MAP                     tApplCmd* fctCmd_Level[eMaxCmdLevel] = {
  #define BEGIN_APPLCMD_LEVEL(Level)                 fctCmd_##Level,
  #define APPLCMD_CFG(CMD, Level, SecureAccess, CALLBACK) 
  #define END_APPLCMD_LEVEL(Level)                   
  #define END_APPLCMD_LIST_MAP                       };

#elif defined(MAC_APPLCMD_LEVEL_RANGE_LIST)
  #define BEGIN_APPLCMD_LIST_MAP                     uint16_t  Cmd_LevelRange[eMaxCmdLevel] = {
  #define BEGIN_APPLCMD_LEVEL(Level)                 eMaxID_##Level,
  #define APPLCMD_CFG(CMD, Level, SecureAccess, CALLBACK) 
  #define END_APPLCMD_LEVEL(Level)                 
  #define END_APPLCMD_LIST_MAP                        };

// *****************************************************************************
// preprocessor error handling 
// *****************************************************************************
#else
  #error Error, reason for ApplCmd list macros undefined!
#endif

//============================================================================
// Preprocessor definitions
//=============================================================================

#ifndef BEGIN_APPLCMD_LIST_MAP
  #error Error ApplCmdMac.h can not included alone, only together with ApplCmdCfg.h.
#endif
