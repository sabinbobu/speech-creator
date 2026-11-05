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
/// \file  CtrlPxl_RteAccess.h
///
/// \brief rte access header file
///
/// \author Ionut Caba  ALRO-CJ (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_PXL_RTE_ACCESS_2021_03_09_H_
#define CTRL_PXL_RTE_ACCESS_2021_03_09_H_

//=============================================================================
// includes
//=============================================================================
#include "CtrlPxl_Types.h"
#include <Nvm.h>
#include <UtilBase.h>

#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <RteCommonTypes.h>
#endif

//=============================================================================
// functions prototypes
//=============================================================================
//getter
uint8   CtrlPxl_RteAccess_Get_ECU_Side(void);
void    CtrlPxl_RteAccess_Get_Coding(tsCtrlPxl_CodingParameters *psCodingParam);
void    CtrlPxl_RteAccess_Get_MlcCrcError(uint8* pucCrcErrorStatus);
void    CtrlPxl_RteAccess_Get_Intensities_CPM(uint16* punMxBuff);
teCtrlPxl_VccxLineState   CtrlPxl_RteAccess_Get_VccxState(void);

//setter
void    CtrlPxl_RteAccess_Set_MLCTgtPWMs(uint16 *punData);
void    CtrlPxl_RteAccess_Set_MLC_EnableTransmission(void);
//void    CtrlPxl_RteAccess_Set_MLC_DisableTransmission(void);
void    CtrlPxl_RteAccess_Reset_MLCSettings(void);
void    CtrlPxl_RteAccess_Write_MatrixFaultStatus(tsCtrlPxl_MatrixFaultStates *psMatrixFaultState);
void    CtrlPxl_RteAccess_Write_MlcErrors(tuCtrlPxl_bErr* puMtxbErr);
void    CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames(tsRte_ucActualPxlPWM*  psPxlPWM);
void    CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames(tsRte_boMtxSegmentFault*  psPxlError_DiagStatus);

//for CtrlPxl_Diag.c
boolean CtrlPxl_RteAccess_Get_PxlErrorStatus(tuCtrlPxl_PxlFault* puLedFault);
boolean CtrlPxl_RteAccess_Get_CommErrorStatus(tsCtrlPxl_ComStatus* psCddMlcComStatus);
boolean CtrlPxl_RteAccess_Get_ResetErrorStatus(void);

// for CtrlPxl_MemHandling.c
void CtrlPxl_RteAccess_MatrixEE_Init(void(*pfnSuccess)(void), void(*pfnFail)(void));
void CtrlPxl_RteAccess_MtxEE_Write(uint8 ucBuff_List[], uint16 unStartAddr, uint16 unLength, void(*pfnSuccess)(void), void(*pfnFail)(void));
void CtrlPxl_RteAccess_ReadEntireMatrixData(boolean boAccessEEPromReading, uint8* pucMtxEEProm_MemCf);
void CtrlPxl_RteAccess_WriteBinningClass(boolean boValidData, uint8* pucData);
void CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM(uint8* pucMtxEEProm_MemCfg);
void CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus(boolean boWrng_Chksum, boolean boNoAccess);


//macro guards for received RTE ports
#define CTRLPXL_RTE_RE_GET_ECU_SIDE                               CtrlPxl_RteAccess_Get_ECU_Side();                     // from IoHw
#define CTRLPXL_RTE_RE_GET_CODING_DATA(pTarget)                   CtrlPxl_RteAccess_Get_Coding(pTarget);                // from CodM
#define CTRLPXL_RTE_RE_GET_VCCX_STATUS                            CtrlPxl_RteAccess_Get_VccxState()                     // from IoHwAbUser
#define CTRLPXL_RTE_RE_GET_MLC_CRCERROR(pTarget)                  CtrlPxl_RteAccess_Get_MlcCrcError(pTarget)            // from CddMlc
#define CTRLPXL_RTE_RE_GET_INTENSITIES_CPM(pTarget)               CtrlPxl_RteAccess_Get_Intensities_CPM(pTarget);       // from CPM


//macro guards for sender RTE ports
#define CTRLPXL_RTE_SE_MATRIX_FAULT(pTarget)                      CtrlPxl_RteAccess_Write_MatrixFaultStatus(pTarget);   // to CtrlLed
#define CTRLPXL_RTE_SE_MATRIX_FAULT_BITERROR(pTarget)             CtrlPxl_RteAccess_Write_MlcErrors(pTarget);           // to CtrlLed
#define CTRLPXL_RTE_SE_PWMs_MLC(pTarget)                          CtrlPxl_RteAccess_Set_MLCTgtPWMs(pTarget);            // to CddMlc
#define CTRLPXL_RTE_SE_EEPROM_ERR_STATUS(boWRNG_CHKSUM, boNO_ACC) CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus(boWRNG_CHKSUM, boNO_ACC);  // to CtrlLed and RSens

#define CTRLPXL_RTE_SE_PXL_VALID_FRM_PWM_PERCENTAGE(pTarget)      CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames(pTarget);  // send valid. frame every 100ms
#define CTRLPXL_RTE_SE_PXL_VALID_FRM_PXL_DEFECT(pTarget)          CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames(pTarget);       // send valid. frame every 100ms

#endif // CTRL_PXL_RTE_ACCESS_2021_03_09_H_
