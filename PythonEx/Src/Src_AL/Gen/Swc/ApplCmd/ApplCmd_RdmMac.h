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
/// \file   ApplCmd_RdmMac.h
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

#ifdef BEGIN_APPLCMD_RDM_LIST_MAP
  #undef  BEGIN_APPLCMD_RDM_LIST_MAP
  #undef  APPLCMD_RDM_CFG
  #undef  END_APPLCMD_RDM_LIST_MAP
#endif

#if defined(APPLCMD_RDM_MAC_DECL_FCT)
  #define BEGIN_APPLCMD_RDM_LIST_MAP
#define APPLCMD_RDM_CFG(CALLBACK)  			void* (CALLBACK)(uint32* pulSize);
  #define END_APPLCMD_RDM_LIST_MAP  
	
#elif defined(MAC_APPLCMD_RDM_ENUM)
  #define BEGIN_APPLCMD_RDM_LIST_MAP      typedef enum enumCmdRdmList {
  #define APPLCMD_RDM_CFG(CALLBACK)  			eCmdRdm##CALLBACK,
  #define END_APPLCMD_RDM_LIST_MAP        eMaxCmdRdmList } enumCmdRdmList_type;

#elif defined(MAC_APPLCMD_RDM_LIST_CALLBACK)
  #define BEGIN_APPLCMD_RDM_LIST_MAP     	static const tpfnGetVirtData apfnGetVirtDataUserStructs[eMaxCmdRdmList] = {
  #define APPLCMD_RDM_CFG(CALLBACK)  			(CALLBACK),
  #define END_APPLCMD_RDM_LIST_MAP 				};

// *****************************************************************************
// preprocessor error handling 
// *****************************************************************************
#else
  #error Error, reason for ApplCmd Rdm list macros undefined!
#endif

//============================================================================
// Preprocessor definitions
//=============================================================================
#ifndef BEGIN_APPLCMD_RDM_LIST_MAP
  #error Error ApplCmd_RdmMac.h can not included alone, only together with ApplCmd_RdmCfg.h.
#endif
