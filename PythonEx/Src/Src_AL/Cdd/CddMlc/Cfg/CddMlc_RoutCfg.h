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
/// \file  CddMlc_RoutCfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_MLC_ROUT_CFG_2024_04_01_H
#define CDD_MLC_ROUT_CFG_2024_04_01_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#ifdef UNIT_TEST

#include <Test_Ext.h>

#else
#include <CddTpsGen2.h>
#include <CddTpsGen3.h>
#include <IoHwAbUser.h>
#include <Rte.h>

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Access to interacting modules
//-----------------------------------------------------------------------------
#define CDDMLC_IS_VCCX_POWERED          ( Dio_ReadChannel(IOHWABUSER_DIO_CHANNEL_MAP_VCCX_EN) == (Dio_LevelType)STD_HIGH ? TRUE : FALSE)
#define CDDMLC_GET_VCCX_FAULT(pTarget)                  (void)Rte_Read_IoHwAbUser_VccxLineState(pTarget)
#define CDDMLC_GET_TARGET_PWM(pTarget)                  (void)Rte_Read_CtrlPxl_TgtMtxPixels_sVal(pTarget)
#define CDDMLC_GET_REINIT_MLC(pTarget)                  (void)Rte_Read_CtrlPxl_CddMlc_ReinitMatrix(pTarget)

#define CDDMLC_RTE_SEND_MTX_COMM_STATUS(pTarget)        (void)Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal(pTarget);
#define CDDMLC_RTE_SEND_MTX_CRC_STATUS(pTarget)         (void)Rte_Write_CtrlPxl_CddMlc_CrcError_sVal(pTarget);
#define CDDMLC_RTE_SEND_MTX_PXL_FAULT(pTarget)          (void)Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal(pTarget);
#define CDDMLC_RTE_SEND_MTX_ADC_DATA(pTarget)           (void)Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal(pTarget);
#define CDDMLC_RTE_SEND_CLR_REINIT_MLC(pTarget)         (void)Rte_Write_CtrlPxl_CddMlc_ReinitMatrix(pTarget);
#define CDDMLC_RTE_SEND_MTX_INIT_STATUS(pTarget)        (void)Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal(pTarget);

//-----------------------------------------------------------------------------
// Access to chip specific implementation
//-----------------------------------------------------------------------------

#define CDDMLC_DRV_GEN2_SetDutyCycle(DrvId, Duty)         CddTpsGen2_SetDutyCycle_1_1024(DrvId, Duty)
#define CDDMLC_DRV_GEN3_SetDutyCycle(DrvId, Duty)         CddTpsGen3_SetDutyCycle_1_1024(DrvId, Duty)

#define CDDMLC_DRV_GEN2_ReinitMatrix(Cmd)                 CddTpsGen2_ReinitSch(Cmd)
#define CDDMLC_DRV_GEN3_ReinitMatrix(Cmd)                 CddTpsGen3_ReinitSch(Cmd)

#define CDDMLC_DRV_GEN2_IsShortToGnd(DrvId)               CddTpsGen2_GetPixelFault(DrvId)
#define CDDMLC_DRV_GEN2_IsComFault(DrvId)                 CddTpsGen2_GetComFault(DrvId)

#define CDDMLC_DRV_GEN3_IsShortToGnd(DrvId)               CddTpsGen3_GetPixelFault(DrvId)
#define CDDMLC_DRV_GEN3_IsComFault(DrvId)                 CddTpsGen3_GetComFault(DrvId)

#define CDDMLC_DRV_GEN2_IsCrcFault(DrvId)                 CddTpsGen2_GetCrcFault(DrvId)
#define CDDMLC_DRV_GEN3_IsCrcFault(DrvId)                 CddTpsGen3_GetCrcFault(DrvId)

#define CDDMLC_DRV_GEN2_IsDrvInit(void)                   CddTpsGen2_GetInitStatus()
#define CDDMLC_DRV_GEN3_IsDrvInit(void)                   CddTpsGen3_GetInitStatus()

#define CDDMLC_DRV_GEN2_GetSensorInfo(DrvId, pData)       CddTpsGen2_GetSensorInfo(DrvId, pData)
#define CDDMLC_DRV_GEN3_GetSensorInfo(DrvId, pData)       CddTpsGen3_GetSensorInfo(DrvId, pData)

#define CDDMLC_DRV_GEN2_GetPWRStatus(void)                CddTpsGen2_GetPWRStatus()
#define CDDMLC_DRV_GEN3_GetPWRStatus(void)                CddTpsGen3_GetPWRStatus()

#define CDDMLC_DRV_GEN2_InitEEprom(CbOk, CbNOk)                     (void)CddTpsGen2_I2C_StartInit(CbOk, CbNOk)
#define CDDMLC_DRV_GEN2_ReadEEprom(pData, Adr, Len, CbOk, CbNOk)    (void)CddTpsGen2_I2C_ReadEeprom(pData, Adr, Len, CbOk, CbNOk)
#define CDDMLC_DRV_GEN2_WriteEEprom(pData, Adr, Len, CbOk, CbNOk)   (void)CddTpsGen2_I2C_WriteEeprom(pData, Adr, Len, CbOk, CbNOk)

#define CDDMLC_EEPROM_TIMEOUT(void)                                 CddTpsGen2_I2C_Timeout()
#define CDDMLC_EEPROM_CONNECTED_ID(void)                            CddTpsGen2_GetEEConnectedId()

#endif // UNIT_TEST

#define CDDMLC_DRV_IsGEN2(DrvId)                          CddMlc_IsDevGEN2(DrvId)
#define CDDMLC_DRV_IsGEN3(DrvId)                          CddMlc_IsDevGEN3(DrvId)

#endif // CDD_MLC_ROUT_CFG_2024_04_01_H
