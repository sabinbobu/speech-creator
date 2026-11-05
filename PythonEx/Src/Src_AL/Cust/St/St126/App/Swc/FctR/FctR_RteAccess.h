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
/// \file  FctR_RteAccess.h
///
/// \brief Rte wrappers for FctR module
///
//-----------------------------------------------------------------------------
#ifndef FCT_R_RTE_ACCESS_H_
#define FCT_R_RTE_ACCESS_H_

//=============================================================================
// includes
//=============================================================================

#include "FctR_Types.h"
#include <UtilDebounce.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Rte/RteCommonTypes.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif

//=============================================================================
// function prototypes
//=============================================================================

/* WRITE RTE PORT */
Std_ReturnType FctR_RteAccess_Write_TgtLedsVal(tsRte_TgtLedVal0Arr pData);
Std_ReturnType FctR_RteAccess_Write_LgtFctState(tsFctR_LgtFctState sState);
Std_ReturnType FctR_RteAccess_Write_LgtFctStatus(tuFctR_LgtFct uStatus);

Std_ReturnType FctR_RteAccess_Write_TiWarningMode(teFctr_TiWarningMode eTiWarningMode);

Std_ReturnType FctR_RteAccess_Write_DblCmd(teFctR_DblCommand eDblCmd);
Std_ReturnType FctR_RteAccess_Write_AfsMode(tsFctR_TgtLgtReq sTgtLgt, teFctR_AfsMode eAfsModeReceived, FctR_eAimingType eAimingMode);

/* READ RTE PORT */
Std_ReturnType FctR_RteAccess_Read_ActLedState(tsRte_LedErrStateArr *pData);
Std_ReturnType FctR_RteAccess_Read_StdLgtFctReq(tsFctR_StdLgtFctsReq *pData);
Std_ReturnType FctR_RteAccess_Read_AfsSignals(tsFctR_AfsSignals *pData);
Std_ReturnType FctR_RteAccess_Read_ClSblRequest(boolean *pboClReq, boolean* pboSblReq, boolean* pboSblClSigQty);

Std_ReturnType FctR_RteAccess_Read_TiRequest(tsFctR_TiReq *pData);
boolean        FctR_RteAccess_Read_HBB(void);
boolean        FctR_RteAccess_Get_FailureGfHB(void);

Std_ReturnType FctR_RteAccess_Read_EcuSide(teFctR_EcuSide* eEcuSide);
Std_ReturnType FctR_RteAccess_Read_PhaseVie(teFctR_EcuOperationgMode* eEcuOpMode);

Std_ReturnType FctR_RteAccess_Read_VehNetState(tsFctR_VehState *psData);
Std_ReturnType FctR_RteAccess_Read_EngineState(teFctR_EngineState *pData);
teFctR_ModeConfigVehicle FctR_RteAccess_ReadVehicleModeConfig(void);

Std_ReturnType FctR_RteAccess_Read_LedVoltRange(uint8 *pucSetVoltageState);

Std_ReturnType FctR_RteAccess_Read_OV_Status(boolean* pboStatus);
Std_ReturnType FctR_RteAccess_Read_UV_Status(boolean* pboStatus);

#endif // FCT_R_RTE_ACCESS_H_