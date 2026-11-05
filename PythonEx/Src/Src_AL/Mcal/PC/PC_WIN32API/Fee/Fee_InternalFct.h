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
/// \file  Fee_Internal.h
///
/// \brief  Header file for Fee_Internal.c
///
/// \descr  
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#if (!defined _FEE_INTERNAL_H_)    /* Multiple inclusion protection viewed from MemIf.h */
#define _FEE_INTERNAL_H_

extern tieFeeState Fee_State;
extern MemIf_StatusType Fee_t_Status;        // status of FLASH EEPROM Emulation
extern MemIf_JobResultType Fee_JobResult;    // result of last job

void FeeStateMachine(tieFeeState eFee_State);
uint16 Fee_LookUpIndex(uint16 unBlockNumber);
uint16 Fee_GetAddressOffset(uint16 unBlockNumber);

#endif /*_FEE_INTERNAL_H_ */
