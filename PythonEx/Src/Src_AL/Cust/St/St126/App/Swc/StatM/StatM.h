#ifndef __STATM_H__
#define __STATM_H__ 

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
/// \file  StatM.h
///
/// \brief  
///
/// \descr  StatM header
///
///         
///         
///
/// \author Liviu Topliceanu (F03343C)
///         mailTo:liviu.topliceanu[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <RteCommonTypes.h>
#include <Bsw/Nvm/NvM_Para.h>
#include <../../Bsw/NvM/Nvm.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif
//=============================================================================
// defines
//=============================================================================

#define STATM_READ_FROM_NVM   TRUE
#define STATM_READ_FROM_RAM   FALSE
#define STATM_S_TO_H(x)      (x=((x)/3600u))
#ifdef UNIT_TEST
uint8 ucTemp[101];
// Rte_Threads (stack sizes)
#define RTE_THREAD_T_HH   6u
#define RTE_THREAD_T_HL   10u
#define RTE_THREAD_T_LH   14u
#define RTE_THREAD_T_LL   20u
#define RTE_THREAD_U_HH   8u
#define RTE_THREAD_U_HL   12u
#define RTE_THREAD_U_LH   16u
#define RTE_THREAD_U_LL   14u
// MPU-Region4: Application Trusted-RAM area
#define m_data_trusted_start            (uint32)&ucTemp[0]
#define m_data_trusted_limit            (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL]
// MPU-Region3: Application Untrusted-RAM area
#define m_data_untrusted_start          (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL]
#define m_data_untrusted_limit          (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH + RTE_THREAD_U_HL + RTE_THREAD_U_LH + RTE_THREAD_U_LL]
#define UINT16_MAX                65535u
#define UINT32_MAX       4294967295U

#define STATM_STACK_U_HH_END    (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL]
#define STATM_STACK_U_HH_START  (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH]
#define STATM_STACK_U_HH_SIZE   (uint32) RTE_THREAD_U_HH

#define STATM_STACK_U_HL_END    (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH]
#define STATM_STACK_U_HL_START  (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH + RTE_THREAD_U_HL]
#define STATM_STACK_U_HL_SIZE   (uint32) RTE_THREAD_U_HL

#define STATM_STACK_U_LH_END    (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH + RTE_THREAD_U_HL]
#define STATM_STACK_U_LH_START  (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH + RTE_THREAD_U_HL + RTE_THREAD_U_LH]
#define STATM_STACK_U_LH_SIZE   (uint32) RTE_THREAD_U_LH

#define STATM_STACK_U_LL_END    (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH + RTE_THREAD_U_HL + RTE_THREAD_U_LH]
#define STATM_STACK_U_LL_START  (uint32) &ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL + RTE_THREAD_U_HH + RTE_THREAD_U_HL + RTE_THREAD_U_LH + RTE_THREAD_U_LL]
#define STATM_STACK_U_LL_SIZE   (uint32) RTE_THREAD_U_LL


#define STATM_STACK_T_HH_END    (uint32)&ucTemp[0]
#define STATM_STACK_T_HH_START  (uint32)&ucTemp[RTE_THREAD_T_HH]
#define STATM_STACK_T_HH_SIZE   (uint32) RTE_THREAD_T_HH

#define STATM_STACK_T_HL_END    (uint32)&ucTemp[RTE_THREAD_T_HH]
#define STATM_STACK_T_HL_START  (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL]
#define STATM_STACK_T_HL_SIZE   (uint32) RTE_THREAD_T_HL

#define STATM_STACK_T_LH_END    (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL]
#define STATM_STACK_T_LH_START  (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH]
#define STATM_STACK_T_LH_SIZE   (uint32) RTE_THREAD_T_LH

#define STATM_STACK_T_LL_END    (uint32)&ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH]
#define STATM_STACK_T_LL_START  (uint32) &ucTemp[RTE_THREAD_T_HH + RTE_THREAD_T_HL + RTE_THREAD_T_LH + RTE_THREAD_T_LL]
#define STATM_STACK_T_LL_SIZE   (uint32) RTE_THREAD_T_LL

#define STATM_STACK_SIZE        (uint32)(STATM_STACK_U_HH_SIZE + STATM_STACK_U_HL_SIZE + STATM_STACK_U_LH_SIZE + STATM_STACK_U_LL_SIZE + STATM_STACK_T_HH_SIZE + STATM_STACK_T_HL_SIZE + STATM_STACK_T_LH_SIZE + STATM_STACK_T_LL_SIZE)

#else

#define STATM_STACK_U_HH_END    (uint32)(m_data_untrusted_limit - RTE_THREAD_U_HH - RTE_THREAD_U_HL - RTE_THREAD_U_LH - RTE_THREAD_U_LL)
#define STATM_STACK_U_HH_START  (uint32)(m_data_untrusted_limit - RTE_THREAD_U_HL - RTE_THREAD_U_LH - RTE_THREAD_U_LL)
#define STATM_STACK_U_HH_SIZE   (uint32) RTE_THREAD_U_HH

#define STATM_STACK_U_HL_END    (uint32)(m_data_untrusted_limit - RTE_THREAD_U_HL - RTE_THREAD_U_LH - RTE_THREAD_U_LL)
#define STATM_STACK_U_HL_START  (uint32)(m_data_untrusted_limit - RTE_THREAD_U_LH - RTE_THREAD_U_LL)
#define STATM_STACK_U_HL_SIZE   (uint32) RTE_THREAD_U_HL

#define STATM_STACK_U_LH_END    (uint32)(m_data_untrusted_limit - RTE_THREAD_U_LH - RTE_THREAD_U_LL)
#define STATM_STACK_U_LH_START  (uint32)(m_data_untrusted_limit - RTE_THREAD_U_LL)
#define STATM_STACK_U_LH_SIZE   (uint32) RTE_THREAD_U_LH

#define STATM_STACK_U_LL_END    (uint32)(m_data_untrusted_limit - RTE_THREAD_U_LL)
#define STATM_STACK_U_LL_START  (uint32) m_data_untrusted_limit
#define STATM_STACK_U_LL_SIZE   (uint32) RTE_THREAD_U_LL


#define STATM_STACK_T_HH_END    (uint32)(m_data_trusted_limit - RTE_THREAD_T_HH - RTE_THREAD_T_HL - RTE_THREAD_T_LH - RTE_THREAD_T_LL)
#define STATM_STACK_T_HH_START  (uint32)(m_data_trusted_limit - RTE_THREAD_T_HL - RTE_THREAD_T_LH - RTE_THREAD_T_LL)
#define STATM_STACK_T_HH_SIZE   (uint32) RTE_THREAD_T_HH

#define STATM_STACK_T_HL_END    (uint32)(m_data_trusted_limit - RTE_THREAD_T_HL - RTE_THREAD_T_LH - RTE_THREAD_T_LL)
#define STATM_STACK_T_HL_START  (uint32)(m_data_trusted_limit - RTE_THREAD_T_LH - RTE_THREAD_T_LL)
#define STATM_STACK_T_HL_SIZE   (uint32) RTE_THREAD_T_HL

#define STATM_STACK_T_LH_END    (uint32)(m_data_trusted_limit - RTE_THREAD_T_LH - RTE_THREAD_T_LL)
#define STATM_STACK_T_LH_START  (uint32)(m_data_trusted_limit - RTE_THREAD_T_LL)
#define STATM_STACK_T_LH_SIZE   (uint32) RTE_THREAD_T_LH

#define STATM_STACK_T_LL_END    (uint32)(m_data_trusted_limit - RTE_THREAD_T_LL)
#define STATM_STACK_T_LL_START  (uint32) m_data_trusted_limit
#define STATM_STACK_T_LL_SIZE   (uint32) RTE_THREAD_T_LL

#define STATM_STACK_SIZE        (uint32)(STATM_STACK_U_HH_SIZE + STATM_STACK_U_HL_SIZE + STATM_STACK_U_LH_SIZE + STATM_STACK_U_LL_SIZE + STATM_STACK_T_HH_SIZE + STATM_STACK_T_HL_SIZE + STATM_STACK_T_LH_SIZE + STATM_STACK_T_LL_SIZE)

#endif
//=============================================================================
// types
//=============================================================================

//defined in NvM_Para.h

//=============================================================================
// function prototypes
//=============================================================================
void StatM_Init(void);
void StatM_Cycle0(void);
void StatM_Deinit(void);
void StatM_ResetStatistics(void);
void StatM_ReadStatistics(tstStatistics *pstStats, boolean boFromNvM);

#endif /* (__STATM_H_ ) */
