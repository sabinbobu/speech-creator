//**********************************************************************************************************************
// (C) Automotive Lighting Tolmezzo
//     <Site Address>
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Tolmezzo.
//**********************************************************************************************************************

//----------------------------------------------------------------------------------------------------------------------
/// \file  Smc_MemMap.h
///
/// \brief  State Machine Controller - Memory Mapping
///
///
/// \author Marco Antonipieri
///         
//----------------------------------------------------------------------------------------------------------------------


//======================================================================================================================
//  Includes
//======================================================================================================================

//======================================================================================================================
// PostBuildConfiguration Data Memory Mapping
//======================================================================================================================

#ifdef SMC_START_SEC_CONST_PBCFG
#undef SMC_START_SEC_CONST_PBCFG
# if defined(__ICCARM__)
#pragma default_variable_attributes = @ ".pbSmcSection"
#elif defined(__clang__) || defined(__ARMCC_VERSION)
#pragma clang section rodata = ".pbSmcSection"
# endif
#endif

#ifdef SMC_STOP_SEC_CONST_PBCFG
#undef SMC_STOP_SEC_CONST_PBCFG
# if defined(__ICCARM__)
#pragma default_variable_attributes =
#elif defined(__clang__) || defined(__ARMCC_VERSION)
#pragma clang section rodata = ""
# endif
#endif


//======================================================================================================================
// Module Data Memory Mapping
//======================================================================================================================

#ifdef SMC_START_SEC_CONST
#undef SMC_START_SEC_CONST
# if defined(__ICCARM__)
#pragma default_variable_attributes = @ ".SmcDataSection"
#elif defined(__clang__) || defined(__ARMCC_VERSION)
#pragma clang section rodata = ".SmcDataSection"
#endif
#endif

#ifdef SMC_STOP_SEC_CONST
#undef SMC_STOP_SEC_CONST
# if defined(__ICCARM__)
#pragma default_variable_attributes =
#elif defined(__clang__) || defined(__ARMCC_VERSION)
#pragma clang section rodata = ""
# endif
#endif


//======================================================================================================================
// Module Initialized Variable Memory Mapping
//======================================================================================================================

#ifdef SMC_START_SEC_VAR_INIT
#undef SMC_START_SEC_VAR_INIT
# if defined(__ICCARM__)
#pragma default_variable_attributes = @ "data.Smc"
#elif defined(__clang__) || defined(__ARMCC_VERSION)
#pragma clang section data = ".data.Smc" bss = ".bss.Smc"
# endif
#endif

#ifdef SMC_STOP_SEC_VAR_INIT
#undef SMC_STOP_SEC_VAR_INIT
# if defined(__ICCARM__)
#pragma default_variable_attributes =
#elif defined(__clang__) || defined(__ARMCC_VERSION)
#pragma clang section data = "" bss = ""
# endif
#endif


//======================================================================================================================
// Module Not Initialized Variable Memory Mapping
//======================================================================================================================

#ifdef SMC_START_SEC_VAR_NOINIT
#undef SMC_START_SEC_VAR_NOINIT
# if defined(__ICCARM__)
//#pragma default_variable_attributes = @ "MyDataSection"
#elif defined(__clang__) || defined(__ARMCC_VERSION)
//#pragma clang section data = "MyDataSection"
#endif
#endif

#ifdef SMC_STOP_SEC_VAR_NOINIT
#undef SMC_STOP_SEC_VAR_NOINIT
# if defined(__ICCARM__)
//#pragma default_variable_attributes =
#elif defined(__clang__) || defined(__ARMCC_VERSION)
//#pragma clang section
# endif
#endif


//======================================================================================================================
// Module Code Memory Mapping
//======================================================================================================================

#ifdef SMC_START_SEC_CODE
#undef SMC_START_SEC_CODE
# if defined(__ICCARM__)
#pragma default_function_attributes = @ ".SmcCodeSection"
#elif defined(__clang__) || defined(__ARMCC_VERSION)
#pragma clang section text = ".SmcCodeSection"
#endif
#endif

#ifdef SMC_STOP_SEC_CODE
#undef SMC_STOP_SEC_CODE
# if defined(__ICCARM__)
#pragma default_function_attributes =
#elif defined(__clang__) || defined(__ARMCC_VERSION)
#pragma clang section text = ""
# endif
#endif

//======================================================================================================================
// End of file
//======================================================================================================================
