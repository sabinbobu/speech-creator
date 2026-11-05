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
/// \file   ErrCust_RteAccess.h
///
/// \brief  encapsule RTE access
///
/// \descr  Functions used for the ErrCust RTE wrapper, for input/output 
///
/// \author 
///        
//-----------------------------------------------------------------------------
#ifndef __CTRLLED_RTEACCESS_H__
#define __CTRLLED_RTEACCESS_H__

//=============================================================================
// Includes
//=============================================================================

#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <RteCommonTypes.h> 
#endif // UNIT_TEST

#include <Bsw/Err/ErrCust_Types.h>

//=============================================================================
// function prototypes
//=============================================================================
void ErrCust_RteAccess_Read_CtrlStp_ActStatStp(tsErrCust_TypesActStatStp *psActStatStp);
void ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(teErrCust_Types_MountingSide *peEcuSide);
void ErrCust_RteAccess_Read_FctR_LgtFctErrState(tsErrCust_LgtFctState *psErrCust_RteAccess_LgtFctState);
void ErrCust_RteAccess_Read_FctR_LgtFctStatus(tsErrCust_LgtFctStatus *psErrCust_RteAccess_LgtFctStatus);
void ErrCust_RteAccess_Read_FctR_TI_FctErrState(boolean *boErrCust_RteAccess_Lgt_TI_State);

#endif // __CTRLLED_RTEACCESS_H__
//EOF
