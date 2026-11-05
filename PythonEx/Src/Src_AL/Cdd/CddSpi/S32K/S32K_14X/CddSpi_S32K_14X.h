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
/// \file  CddSpi_S32K_14X.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_SPI_S32K_14X_2020_11_25_H_
#define CDD_SPI_S32K_14X_2020_11_25_H_

#include <Std_Types.h>
#include <CddSpi_Types.h>

//=============================================================================
// Internal API  functions
//=============================================================================
void    CddSpi_InitIfc_Deriv(uint8 ucIfc);
void    CddSpi_DeInitIfc_Deriv(uint8 ucIfc);
boolean CddSpi_IfcIdle_Deriv(uint8 ucIfc);

void    CddSpi_ConfigureTransfer_Deriv(const tsCddSpiDevCfg* psDevCfg);
boolean CddSpi_TransferComplete_Deriv(uint8 ucIfc, uint16 unTranSize);
boolean CddSpi_TransferCompleteDMA_Deriv(uint8 ucIfc);
void    CddSpi_TxFifoPut_Deriv(uint8 ucIfc, const uint16* punData, uint16 unLength);
void    CddSpi_RxFifoGet_Deriv(uint8 ucIfc, uint16* punData, uint16 unLength);

boolean CddSpi_RxEventTriggered_Deriv(uint8 ucIfc);
void    CddSpi_RxIntEnable_Deriv(uint8 ucIfc);
void    CddSpi_RxIntDisable_Deriv(uint8 ucIfc);
void    CddSpi_RxTriggerEventClear_Deriv(uint8 ucIfc);

void    CddSpi_DmaStop_Deriv(uint8 ucIfc);
uint32  CddSpi_GetCommandWord_Deriv(const tsCddSpiDevCfg* psDevCfg, uint8 ucIdx);
void    CddSpi_StartTransfer_Deriv(uint8 ucIfc, uint32* pulTransferData, uint32* pulReceiveData, uint16 unLen);
#endif // CDD_SPI_S32K_14X_2020_11_25_H_
