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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"

//=============================================================================
// Stub function parameter stubs
//=============================================================================

uint8           CddSbc_Rou_SetCanMode_Param1;
uint8           CddSbc_Rou_SetCanMode_Param2;
uint8           CddSbc_Rou_GetCanMode_Param1;

uint8           CddTle94x1_SetCanMode_Param1;
uint8           CddTle94x1_SetCanMode_Param2;
uint8           CddTle94x1_GetCanMode_Param1;

uint8           CddSpi_TransferMsg_Param1;
uint16          CddSpi_TransferMsg_Param2;
uint32          LPTMR0_GetTimeElapsed_Param1;

uint8           CddSbc_InsertNewSchedEntry_Param1;
uint8           CddSbc_InsertNewSchedEntry_Param2;
uint8           CddSbc_InsertNewSchedEntry_Param3;
pfReadClBck     CddSbc_InsertNewSchedEntry_Param4;
uint8           CddSpi_InitIfc_Deriv_Param1;

tsCddSpiDevCfg* CddSpi_ConfigureTransfer_Deriv_Param1;
uint8           CddSpi_IfcIdle_Deriv_Param1;

uint8           CddSpi_RxFifoGet_Deriv_Param1;
uint16          CddSpi_RxFifoGet_Deriv_Param2;
uint16          CddSpi_RxFifoGet_Deriv_Param3;

tsCddSpiDevCfg* CddSpi_GetCommandWord_Deriv_Param1;
uint8           CddSpi_GetCommandWord_Deriv_Param2;
uint8           CddSpi_TransferComplete_Deriv_Param1;
uint16          CddSpi_TransferComplete_Deriv_Param2;
uint8           CddSpi_StatusFault_Param1;
uint8           CddSpi_DeInitIfc_Deriv_Param1;

uint8           CddSpi_TxFifoPut_Deriv_Param1;
uint16* CddSpi_TxFifoPut_Deriv_Param2;
uint16          CddSpi_TxFifoPut_Deriv_Param3;
uint16* Rte_Read_CddSwi_SetLssPwm_Req_Param1;

uint8           CddSpi_RxIntDisable_Deriv_Param1;
uint8           CddSpi_RxIntEnable_Deriv_Param1;

uint8           CddSpi_StartTransfer_Deriv_Param1;
uint32* CddSpi_StartTransfer_Deriv_Param2;
uint32* CddSpi_StartTransfer_Deriv_Param3;
uint16          CddSpi_StartTransfer_Deriv_Param4;

uint8           CddSpi_TransferCompleteDMA_Deriv_Param1;
uint8           CddSpi_DmaStop_Deriv_Param1;

uint16          CddTps92520_SpiTx_Param1;
uint16          CddTps92520_SpiRx_Param1;
uint32          CddTps92520_SpiRx_Param2[7];

uint16          CddStp_SpiTx_Param1;
uint16          CddStp_SpiRx_Param1;
uint32          CddStp_SpiRx_Param2;

uint16          CddNcv78702_SpiTx_Param1;
uint16          CddNcv78702_SpiRx_Param1;
uint32          CddNcv78702_SpiRx_Param2;

uint16          CddTle94x1_SpiTx_Param1;
uint16          CddTle94x1_SpiRx_Param1;
uint32          CddTle94x1_SpiRx_Param2;
uint16          CddTle94x1_SetPWM_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

uint8             CddTle94x1_GetSBCResetReason_RetVal;
uint8             CddTle94x1_GetCanMode_RetVal;
uint8             CddTle94x1_GetCanUV_RetVal;
uint8             CddSpi_GetState_RetVal;
boolean           CddSpi_TransferMsg_RetVal;
uint32            LPTMR0_GetTimeElapsed_RetVal;
boolean           CddSbc_InsertNewSchedEntry_RetVal;
boolean           CddSpi_IfcIdle_Deriv_RetVal;
uint32            CddSpi_GetCommandWord_Deriv_RetVal;
boolean           CddSpi_TransferComplete_Deriv_RetVal;
boolean           CddSpi_TransferCompleteDMA_Deriv_RetVal;
uint32            CddTps92520_SpiTx_RetVal[7];
uint32            CddStp_SpiTx_RetVal;
uint32            CddNcv78702_SpiTx_RetVal;
uint32            CddTle94x1_SpiTx_RetVal;
Std_ReturnType    Rte_Read_CddSwi_SetLssPwm_Req_RetVal;
uint16            CddTle94x1_GetPWM_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8           CddTle94x1_Init_HitCount;
uint8           CddTle94x1_DeInit_HitCount;
uint8           CddTle94x1_GetSBCResetReason_HitCount;
uint8           CddTle94x1_SetSleepMode_HitCount;
uint8           CddTle94x1_SetCanMode_HitCount;
uint8           CddTle94x1_GetCanMode_HitCount;
uint8           CddTle94x1_GetCanUV_HitCount;
uint8           CddTle94x1_SetWdgWindowModeAnd10ms_HitCount;
uint8           CddTle94x1_SetWdgWindowModeAnd200ms_HitCount;
uint8           CddTle94x1_SetWdgTimeoutModeAnd200ms_HitCount;
uint8           CddTle94x1_Short_To_VBAT_HitCount;
uint8           CddTle94x1_Reset_Short_To_VBAT_HitCount;
uint8           CddTle94x1_Short_To_GND_HitCount;
uint8           CddTle94x1_Reset_Short_To_GND_HitCount;
uint8           CddTle94x1_Thermal_Shutdown_HitCount;

uint8           CddSpi_GetState_HitCount;
uint8           CddSpi_TransferMsg_HitCount;
uint8           LPTMR0_GetTimeElapsed_HitCount;
uint8           CddSbc_InsertNewSchedEntry_HitCount;
uint8           CddSpi_InitIfc_Deriv_HitCount;
uint8           CddSpi_ConfigureTransfer_Deriv_HitCount;
uint8           CddSpi_IfcIdle_Deriv_HitCount;
uint8           CddSpi_RxFifoGet_Deriv_HitCount;
uint8           CddSpi_GetCommandWord_Deriv_HitCount;
uint8           CddSpi_TransferComplete_Deriv_HitCount;
uint8           CddSpi_StatusFault_HitCount;
uint8           CddSpi_DeInitIfc_Deriv_HitCount;
uint8           CddSpi_TxFifoPut_Deriv_HitCount;
uint8           CddSpi_RxIntDisable_Deriv_HitCount;
uint8           CddSpi_RxIntEnable_Deriv_HitCount;
uint8           CddSpi_StartTransfer_Deriv_HitCount;
uint8           CddSpi_TransferCompleteDMA_Deriv_HitCount;
uint8           CddSpi_DmaStop_Deriv_HitCount;
uint8           CddTps92520_SpiTx_HitCount;
uint8           CddTps92520_SpiRx_HitCount;
uint8           CddStp_SpiTx_HitCount;
uint8           CddStp_SpiRx_HitCount;
uint8           CddNcv78702_SpiTx_HitCount;
uint8           CddNcv78702_SpiRx_HitCount;
uint8           CddTle94x1_SpiTx_HitCount;
uint8           CddTle94x1_SpiRx_HitCount;
uint8           Rte_Read_CddSwi_SetLssPwm_Req_HitCount;
uint8           CddTle94x1_SetPWM_HitCount;
uint8           CddTle94x1_GetPWM_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief CddTle94x1_Init
///
/// \descr Stub function created to verify that the CddTle94x1_Init function correctly
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Init(void)
{
  CddTle94x1_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_DeInit
///
/// \descr Stub function created to verify that the CddTle94x1_DeInit function correctly
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------

void CddTle94x1_DeInit(void)
{
  CddTle94x1_DeInit_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief    CddTle94x1_GetSBCResetReason
///
/// \descr Stub function created to verify that the CddTle94x1_GetSBCResetReason function correctly
///
/// \param void
///
/// \return uint8
//-----------------------------------------------------------------------------


uint8 CddTle94x1_GetSBCResetReason(void)
{
  CddTle94x1_GetSBCResetReason_HitCount++;
  return CddTle94x1_GetSBCResetReason_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief     CddTle94x1_SetSleepMode
///
/// \descr Stub function created to verify that the CddTle94x1_SetSleepMode function correctly
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_SetSleepMode(void)
{
  CddTle94x1_SetSleepMode_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief     CddTle94x1_SetCanMode
///
/// \descr Stub function created to verify that the CddTle94x1_SetCanMode function correctly
///
/// \param uint8 unCanChannel - CAN Channel
///        uint8 unCanMode - CAN mode
///
/// \return void
//-----------------------------------------------------------------------------

void CddTle94x1_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode)
{
  CddTle94x1_SetCanMode_HitCount++;
  CddTle94x1_SetCanMode_Param1 = ucCanChannel;
  CddTle94x1_SetCanMode_Param1 = ucCanMode;
}

//-----------------------------------------------------------------------------
/// \brief    CddTle94x1_GetCanMode
///
/// \descr Stub function created to verify that the CddTle94x1_GetCanMode function correctly
///
/// \param uint8 - CAN Channel (CAN 0 for SBC)
///
/// \return uint8
//-----------------------------------------------------------------------------

uint8 CddTle94x1_GetCanMode(uint8 ucCanChannel)
{
  CddTle94x1_GetCanMode_HitCount++;
  CddTle94x1_GetCanMode_Param1 = ucCanChannel;
  return CddTle94x1_GetCanMode_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief    CddTle94x1_GetCanUV
///
/// \descr Stub function created to verify that the CddTle94x1_GetCanUV function correctly
///
/// \param void
///
/// \return uint8
//-----------------------------------------------------------------------------

uint8 CddTle94x1_GetCanUV(void)
{
  CddTle94x1_GetCanUV_HitCount++;
  return CddTle94x1_GetCanUV_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief    CddTle94x1_SetWdgWindowModeAnd10ms
///
/// \descr Stub function created to verify that the CddTle94x1_SetWdgWindowModeAnd10ms function correctly
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------


void CddTle94x1_SetWdgWindowModeAnd10ms(void)
{
  CddTle94x1_SetWdgWindowModeAnd10ms_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief    CddTle94x1_SetWdgWindowModeAnd200ms
///
/// \descr Stub function created to verify that the CddTle94x1_SetWdgWindowModeAnd200ms function correctly
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------

void CddTle94x1_SetWdgWindowModeAnd200ms(void)
{
  CddTle94x1_SetWdgWindowModeAnd200ms_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief    CddTle94x1_SetWdgTimeoutModeAnd200ms
///
/// \descr Stub function created to verify that the CddTle94x1_SetWdgTimeoutModeAnd200ms function correctly
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------


void CddTle94x1_SetWdgTimeoutModeAnd200ms(void)
{
  CddTle94x1_SetWdgTimeoutModeAnd200ms_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief    CddSpi_GetState
///
/// \descr Stub function created to verify that the CddSpi_GetState function correctly
///
/// \param void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CddSpi_GetState(void)
{
  CddSpi_GetState_HitCount++;
  return CddSpi_GetState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief    CddSpi_TransferMsg
///
/// \descr Stub function created to verify that the CddSpi_TransferMsg function correctly
///
/// \param uint8 ucDevice : target SPI peripheral
///        uint16 punData : in/out parameter (pointer)
///
/// \return boolean TRUE:  Transfer successful
///                 FALSE: Transfer not performed
//-----------------------------------------------------------------------------
boolean CddSpi_TransferMsg(uint8 ucDevice, uint16* punData)
{
  CddSpi_TransferMsg_HitCount++;
  CddSpi_TransferMsg_Param1 = ucDevice;
  CddSpi_TransferMsg_Param2 = punData;
  return CddSpi_TransferMsg_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR0_GetTimeElapsed
///
/// \descr Stub function for LPTMR0_GetTimeElapsed
///
/// \param   uint32 ulStartValue : Value from whitch the timer is started.
///
/// \return uint32 : The time elapsed from the ulStartValue moment
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_HitCount++;
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  return (LPTMR0_GetTimeElapsed_RetVal);
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_CddSwi_SetLssPwm_Req
///
/// \descr Stub function for Rte_Read_CddSwi_SetLssPwm_Req
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CddSwi_SetLssPwm_Req(uint16* unPwm)
{
  *unPwm = *Rte_Read_CddSwi_SetLssPwm_Req_Param1;
  Rte_Read_CddSwi_SetLssPwm_Req_HitCount++;
  return Rte_Read_CddSwi_SetLssPwm_Req_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief CddSbc_InsertNewSchedEntry
///
/// \descr Stub function for CddSbc_InsertNewSchedEntry
///
/// \param  uint8 ucAddress             : address of the SBC register
///         uint8 ucData                : data to be written in the SBC register
///         uint8 ucCommand             : write or read the register
///         pfReadClBck ClbckFunction   : callback function
///
/// \return boolean        : insertion was successful
//-----------------------------------------------------------------------------
boolean CddSbc_InsertNewSchedEntry(uint8 ucAddress, uint8 ucData, uint8 ucCommand, pfReadClBck ClbckFunction)
{
  CddSbc_InsertNewSchedEntry_HitCount++;
  CddSbc_InsertNewSchedEntry_Param1 = ucAddress;
  CddSbc_InsertNewSchedEntry_Param2 = ucData;
  CddSbc_InsertNewSchedEntry_Param3 = ucCommand;
  CddSbc_InsertNewSchedEntry_Param4 = ClbckFunction;
  return CddSbc_InsertNewSchedEntry_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_InitIfc_Deriv
///
/// \descr Stub function for CddSpi_InitIfc_Deriv
///
/// \param  uint8 ucIfc: Spi Interface to be configured
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_InitIfc_Deriv(uint8 ucIfc)
{
  CddSpi_InitIfc_Deriv_HitCount++;
  CddSpi_InitIfc_Deriv_Param1 = ucIfc;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_ConfigureTransfer_Deriv
///
/// \descr Stub function for CddSpi_ConfigureTransfer_Deriv
///
/// \param tsCddSpiDevCfg psDevCfg : pointer to  device data configuration
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_ConfigureTransfer_Deriv(const tsCddSpiDevCfg* psDevCfg)
{
  CddSpi_ConfigureTransfer_Deriv_HitCount++;
  CddSpi_ConfigureTransfer_Deriv_Param1 = psDevCfg;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_IfcIdle_Deriv
///
/// \descr Stub function for CddSpi_IfcIdle_Deriv
///
/// \param  ucIfc: Spi Interface in which status is checked
///
/// \return boolean
///           -TRUE : Interface is in idle status
///           -FALSE: Interface is not in idle status
//-----------------------------------------------------------------------------
boolean CddSpi_IfcIdle_Deriv(uint8 ucIfc)
{
  CddSpi_IfcIdle_Deriv_Param1 = ucIfc;
  return CddSpi_IfcIdle_Deriv_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_RxFifoGet_Deriv
///
/// \descr Stub function for CddSpi_RxFifoGet_Deriv
///
/// \param  ucIfc : Spi interface whose Rx-HW buffer belongs to.
///         punData: Pointer to Buffer Data
///         unLength: Number of elements
///
/// \return void
//-----------------------------------------------------------------------------
void  CddSpi_RxFifoGet_Deriv(uint8 ucIfc, uint16* punData, uint16 unLength)
{
  CddSpi_RxFifoGet_Deriv_HitCount++;
  CddSpi_RxFifoGet_Deriv_Param1 = ucIfc;
  CddSpi_RxFifoGet_Deriv_Param2 = punData;
  CddSpi_RxFifoGet_Deriv_Param3 = unLength;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_GetCommandWord_Deriv
///
/// \descr Stub function for CddSpi_GetCommandWord_Deriv
///
/// \param  psDevCfg : pointer to device data configuration
///         ucIdx : index of device (helpful if is a daisy cahin config)
///
/// \return uTempTCR.ulData : command word for a specific index
//-----------------------------------------------------------------------------
uint32 CddSpi_GetCommandWord_Deriv(const tsCddSpiDevCfg* psDevCfg, uint8 ucIdx)
{
  CddSpi_GetCommandWord_Deriv_HitCount;
  CddSpi_GetCommandWord_Deriv_Param1 = psDevCfg;
  CddSpi_GetCommandWord_Deriv_Param2 = ucIdx;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_TransferComplete_Deriv
///
/// \descr Stub function for CddSpi_TransferComplete_Deriv
///
/// \param  ucIfc     : Spi Interface in which the transmission completion is checked
/// \param  unTranSize: Number of data that the transmission consists of
///
/// \return boolean
///           -TRUE : Transmission has been completed
///           -FALSE: Transmission has not been completed
//-----------------------------------------------------------------------------
boolean CddSpi_TransferComplete_Deriv(uint8 ucIfc, uint16 unTranSize)
{
  CddSpi_TransferComplete_Deriv_HitCount++;
  CddSpi_TransferComplete_Deriv_Param1 = ucIfc;
  CddSpi_TransferComplete_Deriv_Param2 = unTranSize;
  return CddSpi_TransferComplete_Deriv_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_StatusFault
///
/// \descr Stub function for CddSpi_StatusFault - dummy function for now
///
/// \param  uint8 ucVal
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_StatusFault(uint8 ucVal)
{
  CddSpi_StatusFault_HitCount++;
  CddSpi_StatusFault_Param1 = ucVal;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_DeInitIfc_Deriv
///
/// \descr Stub function for CddSpi_DeInitIfc_Deriv
///
/// \param  uint8ucIfc : Spi Interface to be deinitialized
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_DeInitIfc_Deriv(uint8 ucIfc)
{
  CddSpi_DeInitIfc_Deriv_HitCount++;
  CddSpi_DeInitIfc_Deriv_Param1 = ucIfc;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_TxFifoPut_Deriv
///
/// \descr Stub function for CddSpi_TxFifoPut_Deriv
///
/// \param  ucIfc: Interface whose TX-Hw buffer has to be filled up
///         punData: Pointer to Buffer Data
///         unLength: Number of elements
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_TxFifoPut_Deriv(uint8 ucIfc, const uint16* punData, uint16 unLength)
{
  CddSpi_TxFifoPut_Deriv_HitCount++;
  CddSpi_TxFifoPut_Deriv_Param1 = ucIfc;
  CddSpi_TxFifoPut_Deriv_Param2 = punData;
  CddSpi_TxFifoPut_Deriv_Param3 = unLength;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_RxIntDisable_Deriv
///
/// \descr Stub function for CddSpi_RxIntDisable_Deriv
///
/// \param  ucIfc : Spi Interface in which Rx Interrupt is disabled
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_RxIntDisable_Deriv(uint8 ucIfc)
{
  CddSpi_RxIntDisable_Deriv_HitCount++;
  CddSpi_RxIntDisable_Deriv_Param1 = ucIfc;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_RxIntEnable_Deriv
///
/// \descr Stub function for CddSpi_RxIntEnable_Deriv
///
/// \param  ucIfc : Spi Interface in which Rx Interrupt is enabled
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_RxIntEnable_Deriv(uint8 ucIfc)
{
  CddSpi_RxIntEnable_Deriv_HitCount++;
  CddSpi_RxIntEnable_Deriv_Param1 = ucIfc;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_StartTransfer_Deriv
///
/// \descr Stub function for CddSpi_StartTransfer_Deriv
///
/// \param  ucIfc : Spi Interface
///         pulTransferData : address for TX data
///.........pulReceiveData : addres for RX data
///         unLen : number of words to be transferd
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_StartTransfer_Deriv(uint8 ucIfc, uint32* pulTransferData, uint32* pulReceiveData, uint16 unLen)
{
  CddSpi_StartTransfer_Deriv_HitCount++;
  CddSpi_StartTransfer_Deriv_Param1 = ucIfc;
  CddSpi_StartTransfer_Deriv_Param2 = pulTransferData;
  CddSpi_StartTransfer_Deriv_Param3 = pulReceiveData;
  CddSpi_StartTransfer_Deriv_Param4 = unLen;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_TransferCompleteDMA_Deriv
///
/// \descr Stub function for CddSpi_TransferCompleteDMA_Deriv
///
/// \param  ucIfc     : Spi Interface in which the transmission completion is checked
///
/// \return boolean
///           -TRUE : Transmission has been completed
///           -FALSE: Transmission has not been completed
//-----------------------------------------------------------------------------
boolean CddSpi_TransferCompleteDMA_Deriv(uint8 ucIfc)
{
  CddSpi_TransferCompleteDMA_Deriv_HitCount++;
  CddSpi_TransferCompleteDMA_Deriv_Param1 = ucIfc;
  return CddSpi_TransferCompleteDMA_Deriv_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_DmaStop_Deriv
///
/// \descr Stub function for CddSpi_DmaStop_Deriv
///
/// \param  ucIfc     : Spi Interface in which the transmission completion is checked
///
/// \return boolean
///           -TRUE : Transmission has been completed
///           -FALSE: Transmission has not been completed
//-----------------------------------------------------------------------------
void CddSpi_DmaStop_Deriv(uint8 ucIfc)
{
  CddSpi_DmaStop_Deriv_HitCount++;
  CddSpi_DmaStop_Deriv_Param1 = ucIfc;
}

//-----------------------------------------------------------------------------
/// \brief CddTps92520_SpiTx
///
/// \descr Stub function created to simulate the behaviour of CddTps92520_SpiTx
///
/// \param  unId - decvice Id
///
/// \return data to be transfered
//-----------------------------------------------------------------------------
uint32 CddTps92520_SpiTx(uint16 unId)
{
  CddTps92520_SpiTx_Param1 = unId;
  CddTps92520_SpiTx_HitCount++;
  return CddTps92520_SpiTx_RetVal[unId];
}

//-----------------------------------------------------------------------------
/// \brief CddTps92520_SpiRx
///
/// \descr Stub function created to simulate the behaviour of CddTps92520_SpiRx
///
/// \param  unId - decvice Id
///         ulData - data to be transfered
///
/// \return -
//-----------------------------------------------------------------------------
void CddTps92520_SpiRx(uint16 unId, uint32 ulData)
{
  CddTps92520_SpiRx_Param1 = unId;
  CddTps92520_SpiRx_Param2[unId] = ulData;
  CddTps92520_SpiRx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddStp_SpiTx
///
/// \descr Stub function created to simulate the behaviour of CddStp_SpiTx
///
/// \param  unId - decvice Id
///
/// \return data to be transfered
//-----------------------------------------------------------------------------
uint32 CddStp_SpiTx(uint16 unId)
{
  CddStp_SpiTx_Param1 = unId;
  CddStp_SpiTx_HitCount++;
  return CddStp_SpiTx_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddStp_SpiRx
///
/// \descr Stub function created to simulate the behaviour of CddStp_SpiRx
///
/// \param  unId - decvice Id
///         ulData - data to be transfered
///
/// \return -
//-----------------------------------------------------------------------------
void CddStp_SpiRx(uint16 unId, uint32 ulData)
{
  CddStp_SpiRx_Param2 = ulData;
  CddStp_SpiRx_Param1 = unId;
  CddStp_SpiRx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddNcv78702_SpiTx
///
/// \descr Stub function created to simulate the behaviour of CddNcv78702_SpiTx
///
/// \param  unId - decvice Id
///
/// \return data to be transfered
//-----------------------------------------------------------------------------
uint32 CddNcv78702_SpiTx(uint16 unId)
{
  CddNcv78702_SpiTx_Param1 = unId;
  CddNcv78702_SpiTx_HitCount++;
  return CddNcv78702_SpiTx_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddNcv78702_SpiRx
///
/// \descr Stub function created to simulate the behaviour of CddNcv78702_SpiRx
///
/// \param  unId - decvice Id
///         ulData - data to be transfered
///
/// \return -
//-----------------------------------------------------------------------------
void CddNcv78702_SpiRx(uint16 unId, uint32 ulData)
{
  CddNcv78702_SpiRx_Param1 = unId;
  CddNcv78702_SpiRx_Param2 = ulData;
  CddNcv78702_SpiRx_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_SpiTx
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_SpiTx
///
/// \param  unIx - mesaje index
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 CddTle94x1_SpiTx(uint16 unIx)
{
  CddTle94x1_SpiTx_HitCount++;
  CddTle94x1_SpiTx_Param1 = unIx;
  return CddTle94x1_SpiTx_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_SpiRx
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_SpiRx
///
/// \param  unIx - mesaje index
///         ulData - data to be transfered
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_SpiRx(uint16 unIx, uint32 ulData)
{
  CddTle94x1_SpiRx_HitCount++;
  CddTle94x1_SpiRx_Param1 = unIx;
  CddTle94x1_SpiRx_Param2 = ulData;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_Short_To_VBAT
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_Short_To_VBAT
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Short_To_VBAT(void)
{
  CddTle94x1_Short_To_VBAT_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_Reset_Short_To_VBAT
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_Reset_Short_To_VBAT
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Reset_Short_To_VBAT(void)
{
  CddTle94x1_Reset_Short_To_VBAT_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_Short_To_GND
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_Short_To_GND
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Short_To_GND(void)
{
  CddTle94x1_Short_To_GND_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_Reset_Short_To_GND
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_Reset_Short_To_GND
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Reset_Short_To_GND(void)
{
  CddTle94x1_Reset_Short_To_GND_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_Thermal_Shutdown
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_Thermal_Shutdown
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_Thermal_Shutdown(void)
{
  CddTle94x1_Thermal_Shutdown_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_SetPWM
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_SetPWM
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddTle94x1_SetPWM(uint16 unPWMDutyCycle)
{
  CddTle94x1_SetPWM_Param1 = unPWMDutyCycle;
  CddTle94x1_SetPWM_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddTle94x1_GetPWM
///
/// \descr Stub function created to simulate the behaviour of CddTle94x1_GetPWM
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
uint8 CddTle94x1_GetPWM(void)
{
  CddTle94x1_GetPWM_HitCount++;
  return CddTle94x1_GetPWM_RetVal;
}

