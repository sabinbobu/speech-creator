//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddUart_S32K_14X.h
///
/// \brief
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_UART_S32K_14X_2023_09_08_H
#define CDD_UART_S32K_14X_2023_09_08_H

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <CddUart_Types.h>

//=============================================================================
// Preprocessor definitions
//=============================================================================


//=============================================================================
// Public Type definitions
//=============================================================================


//=============================================================================
// Public API functions prototypes
//=============================================================================

void CddUart_InitIfc_Deriv(uint8 ucIfc);
void CddUart_DeInitIfc_Deriv(uint8 ucIfc);

void CddUart_FillTxFifo (uint8 ucIfc, uint8* pucTxData, uint8 ucLength);
void CddUart_ReadRxFifo (uint8 ucIfc, uint8* pucRxData, uint16 unLength);
void CddUart_ConfigureTransfer_Param(const tsCddUartDevCfg* psDevCfg);
void CddUart_StartTransfer_Deriv(uint8 ucIfc, uint32* pulTransferData, uint32* pulReceiveData, uint8 ucTxLen, uint8 ucRxLen);
void CddUart_RxIntEnable(uint8 ucIfc);

boolean CddUart_TransferCompleteDMA_Deriv(uint8 ucIfc);
boolean CddUart_IfcIdle_Deriv(uint8 ucIfc);
boolean CddUart_GetRxCbStatus(void);

#endif // CDD_UART_S32K_14X_2023_09_08_H
