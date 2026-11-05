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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================

#include <CddSpi.h>
#include <CddSpi_Types.h>
#include <CddTle94x1.h>
#include <CddTle94x1_Com.h>
#include <../../CddTle94x1/Gen/CddTle94x1_Types.h>

//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================


void              CddTle94x1_Init(void);
void              CddTle94x1_DeInit(void);
void              CddTle94x1_SetSleepMode(void);
void              CddTle94x1_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode);
uint8             CddTle94x1_GetCanMode(uint8 ucCanChannel);
uint8             CddTle94x1_GetCanUV(void);
uint8             CddTle94x1_GetSBCResetReason(void);
void              CddTle94x1_SetWdgWindowModeAnd10ms(void);
void              CddTle94x1_SetWdgWindowModeAnd200ms(void);
void              CddTle94x1_SetWdgTimeoutModeAnd200ms(void);
void              CddTle94x1_Short_To_VBAT(void);
void              CddTle94x1_Reset_Short_To_VBAT(void);
void              CddTle94x1_Short_To_GND(void);
void              CddTle94x1_Reset_Short_To_GND(void);
void              CddTle94x1_Thermal_Shutdown(void);
void              CddTle94x1_SetPWM(uint16 unPWMDutyCycle);
uint8             CddTle94x1_GetPWM(void);

uint8             CddSpi_GetState(void);
boolean           CddSpi_TransferMsg(uint8 ucDevice, uint16* punData);
uint32            LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
boolean           CddSbc_InsertNewSchedEntry(uint8 ucAddress, uint8 ucData, uint8 ucCommand, pfReadClBck ClbckFunction);
void              CddSpi_InitIfc_Deriv(uint8 ucIfc);
void              CddSpi_ConfigureTransfer_Deriv(const tsCddSpiDevCfg* psDevCfg);
boolean           CddSpi_IfcIdle_Deriv(uint8 ucIfc);
uint32            CddSpi_GetCommandWord_Deriv(const tsCddSpiDevCfg* psDevCfg, uint8 ucIdx);
boolean           CddSpi_TransferComplete_Deriv(uint8 ucIfc, uint16 unTranSize);
void              CddSpi_StatusFault(uint8 ucVal);
void              CddSpi_DeInitIfc_Deriv(uint8 ucIfc);
void              CddSpi_TxFifoPut_Deriv(uint8 ucIfc, const uint16* punData, uint16 unLength);
void              CddSpi_RxIntDisable_Deriv(uint8 ucIfc);
void              CddSpi_RxIntEnable_Deriv(uint8 ucIfc);
void              CddSpi_StartTransfer_Deriv(uint8 ucIfc, uint32* pulTransferData, uint32* pulReceiveData, uint16 unLen);
boolean           CddSpi_TransferCompleteDMA_Deriv(uint8 ucIfc);
void              CddSpi_DmaStop_Deriv(uint8 ucIfc);
uint32            CddTps92520_SpiTx(uint16 unId);
void              CddTps92520_SpiRx(uint16 unId, uint32 ulData);
uint32            CddStp_SpiTx(uint16 unId);
void              CddStp_SpiRx(uint16 unId, uint32 ulData);
uint32            CddNcv78702_SpiTx(uint16 unId);
void              CddNcv78702_SpiRx(uint16 unId, uint32 ulData);
uint32            CddTle94x1_SpiTx(uint16 unIx);
void              CddTle94x1_SpiRx(uint16 unIx, uint32 ulData);
Std_ReturnType    Rte_Read_CddSwi_SetLssPwm_Req(uint16* unPwm);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern uint8           CddSbc_Rou_SetCanMode_Param1;
extern uint8           CddSbc_Rou_SetCanMode_Param2;
extern uint8           CddSbc_Rou_GetCanMode_Param1;

extern uint8           CddTle94x1_SetCanMode_Param1;
extern uint8           CddTle94x1_SetCanMode_Param2;
extern uint8           CddTle94x1_GetCanMode_Param1;

extern uint8           CddSpi_TransferMsg_Param1;
extern uint16          CddSpi_TransferMsg_Param2;
extern uint32          LPTMR0_GetTimeElapsed_Param1;

extern uint8           CddSbc_InsertNewSchedEntry_Param1;
extern uint8           CddSbc_InsertNewSchedEntry_Param2;
extern uint8           CddSbc_InsertNewSchedEntry_Param3;
extern pfReadClBck     CddSbc_InsertNewSchedEntry_Param4;
extern uint8           CddSpi_InitIfc_Deriv_Param1;

extern tsCddSpiDevCfg* CddSpi_ConfigureTransfer_Deriv_Param1;
extern uint8           CddSpi_IfcIdle_Deriv_Param1;
 
extern uint8           CddSpi_RxFifoGet_Deriv_Param1;
extern uint16          CddSpi_RxFifoGet_Deriv_Param2;
extern uint16          CddSpi_RxFifoGet_Deriv_Param3;

extern tsCddSpiDevCfg* CddSpi_GetCommandWord_Deriv_Param1;
extern uint8           CddSpi_GetCommandWord_Deriv_Param2;
extern uint8           CddSpi_TransferComplete_Deriv_Param1;
extern uint16          CddSpi_TransferComplete_Deriv_Param2;
extern uint8           CddSpi_StatusFault_Param1;
extern uint8           CddSpi_DeInitIfc_Deriv_Param1;

extern uint8           CddSpi_TxFifoPut_Deriv_Param1;
extern uint16* CddSpi_TxFifoPut_Deriv_Param2;
extern uint16          CddSpi_TxFifoPut_Deriv_Param3;
extern uint16* Rte_Read_CddSwi_SetLssPwm_Req_Param1;
 
extern uint8           CddSpi_RxIntDisable_Deriv_Param1;
extern uint8           CddSpi_RxIntEnable_Deriv_Param1;
 
extern uint8           CddSpi_StartTransfer_Deriv_Param1;
extern uint32* CddSpi_StartTransfer_Deriv_Param2;
extern uint32* CddSpi_StartTransfer_Deriv_Param3;
extern uint16          CddSpi_StartTransfer_Deriv_Param4;

extern uint8           CddSpi_TransferCompleteDMA_Deriv_Param1;
extern uint8           CddSpi_DmaStop_Deriv_Param1;

extern uint16          CddTps92520_SpiTx_Param1;
extern uint16          CddTps92520_SpiRx_Param1;
extern uint32          CddTps92520_SpiRx_Param2[7];

extern uint16          CddStp_SpiTx_Param1;
extern uint16          CddStp_SpiRx_Param1;
extern uint32          CddStp_SpiRx_Param2;

extern uint16          CddNcv78702_SpiTx_Param1;
extern uint16          CddNcv78702_SpiRx_Param1;
extern uint32          CddNcv78702_SpiRx_Param2;

extern uint16          CddTle94x1_SpiTx_Param1;
extern uint16          CddTle94x1_SpiRx_Param1;
extern uint32          CddTle94x1_SpiRx_Param2;
extern uint16          CddTle94x1_SetPWM_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern uint8             CddTle94x1_GetSBCResetReason_RetVal;
extern uint8             CddTle94x1_GetCanMode_RetVal;
extern uint8             CddTle94x1_GetCanUV_RetVal;
extern uint8             CddSpi_GetState_RetVal;
extern boolean           CddSpi_TransferMsg_RetVal;
extern uint32            LPTMR0_GetTimeElapsed_RetVal;
extern boolean           CddSbc_InsertNewSchedEntry_RetVal;
extern boolean           CddSpi_IfcIdle_Deriv_RetVal;
extern uint32            CddSpi_GetCommandWord_Deriv_RetVal;
extern boolean           CddSpi_TransferComplete_Deriv_RetVal;
extern boolean           CddSpi_TransferCompleteDMA_Deriv_RetVal;
extern uint32            CddTps92520_SpiTx_RetVal[7];
extern uint32            CddStp_SpiTx_RetVal;
extern uint32            CddNcv78702_SpiTx_RetVal;
extern uint32            CddTle94x1_SpiTx_RetVal;
extern Std_ReturnType    Rte_Read_CddSwi_SetLssPwm_Req_RetVal;
extern uint16            CddTle94x1_GetPWM_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8           CddTle94x1_Init_HitCount;
extern uint8           CddTle94x1_DeInit_HitCount;
extern uint8           CddTle94x1_GetSBCResetReason_HitCount;
extern uint8           CddTle94x1_SetSleepMode_HitCount;
extern uint8           CddTle94x1_SetCanMode_HitCount;
extern uint8           CddTle94x1_GetCanMode_HitCount;
extern uint8           CddTle94x1_GetCanUV_HitCount;
extern uint8           CddTle94x1_SetWdgWindowModeAnd10ms_HitCount;
extern uint8           CddTle94x1_SetWdgWindowModeAnd200ms_HitCount;
extern uint8           CddTle94x1_SetWdgTimeoutModeAnd200ms_HitCount;
extern uint8           CddTle94x1_Short_To_VBAT_HitCount;
extern uint8           CddTle94x1_Reset_Short_To_VBAT_HitCount;
extern uint8           CddTle94x1_Short_To_GND_HitCount;
extern uint8           CddTle94x1_Reset_Short_To_GND_HitCount;
extern uint8           CddTle94x1_Thermal_Shutdown_HitCount;

extern uint8           CddSpi_GetState_HitCount;
extern uint8           CddSpi_TransferMsg_HitCount;
extern uint8           LPTMR0_GetTimeElapsed_HitCount;
extern uint8           CddSbc_InsertNewSchedEntry_HitCount;
extern uint8           CddSpi_InitIfc_Deriv_HitCount;
extern uint8           CddSpi_ConfigureTransfer_Deriv_HitCount;
extern uint8           CddSpi_IfcIdle_Deriv_HitCount;
extern uint8           CddSpi_RxFifoGet_Deriv_HitCount;
extern uint8           CddSpi_GetCommandWord_Deriv_HitCount;
extern uint8           CddSpi_TransferComplete_Deriv_HitCount;
extern uint8           CddSpi_StatusFault_HitCount;
extern uint8           CddSpi_DeInitIfc_Deriv_HitCount;
extern uint8           CddSpi_TxFifoPut_Deriv_HitCount;
extern uint8           CddSpi_RxIntDisable_Deriv_HitCount;
extern uint8           CddSpi_RxIntEnable_Deriv_HitCount;
extern uint8           CddSpi_StartTransfer_Deriv_HitCount;
extern uint8           CddSpi_TransferCompleteDMA_Deriv_HitCount;
extern uint8           CddSpi_DmaStop_Deriv_HitCount;
extern uint8           CddTps92520_SpiTx_HitCount;
extern uint8           CddTps92520_SpiRx_HitCount;
extern uint8           CddStp_SpiTx_HitCount;
extern uint8           CddStp_SpiRx_HitCount;
extern uint8           CddNcv78702_SpiTx_HitCount;
extern uint8           CddNcv78702_SpiRx_HitCount;
extern uint8           CddTle94x1_SpiTx_HitCount;
extern uint8           CddTle94x1_SpiRx_HitCount;
extern uint8           Rte_Read_CddSwi_SetLssPwm_Req_HitCount;
extern uint8           CddTle94x1_SetPWM_HitCount;
extern uint8           CddTle94x1_GetPWM_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
