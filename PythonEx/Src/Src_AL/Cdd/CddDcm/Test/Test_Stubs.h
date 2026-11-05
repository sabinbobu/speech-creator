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
#include <AL_Helper.h>
#include <UtilUtility.h>
#include <Nvm.h>
#include <Rte/RteCommonTypes.h>
#include <CddDcmCtrl.h>
#include <CddDcmHal.h>
#include <Pwm_TargetTypes.h>
//=============================================================================
// Typedef
//=============================================================================

typedef uint32 Pwm_ChannelType;

typedef uint8  Dio_LevelType;

//=============================================================================
// Stub function declarations
//=============================================================================

void           Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1);
void           Rte_Read_DcmState0_Port(tDcmStateMsg* ppara1);
void           Rte_Read_DcmPos0_Port(tDcmPosMsg* ppara1);
void           Rte_Read_ppCtrlDcmTarget0_DcmTargetValues(tsRte_CtrlDcmTarget* ppara1);
void           Rte_Write_CddDcm_ErrorStatus(tsRte_DcmStatusError* ppara1);
void           Rte_Write_DcmState0_Port(tDcmStateMsg* ppara1);
void           Rte_Write_DcmPos0_Port(tDcmPosMsg* ppara1);
void           IoHwAbUser_GetAdc_VoltDC_OUT1(uint16 *pio_signal);
void           IoHwAb_User_SetDio_EN_DC(Dio_LevelType signal);
void           Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
void           Pwm_StartPwmChannel(Pwm_ChannelType channelNumber);
void           Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
void           Pwm_ClampPwmChannel(Pwm_ChannelType channelNumber, tePwm_OutputState level);
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tiu32Voltage_mV      Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
extern tDcmStateMsg         Rte_Read_DcmState0_Port_Param1;
extern tDcmPosMsg           Rte_Read_DcmPos0_Port_Param1;
extern tsRte_CtrlDcmTarget  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1;
extern tDcmStateMsg         Rte_Write_DcmState0_Port_Param1;
extern tsRte_DcmStatusError Rte_Write_CddDcm_ErrorStatus_Param1;
extern tDcmPosMsg           Rte_Write_DcmPos0_Port_Param1;
extern uint16               IoHwAbUser_GetAdc_VoltDC_OUT1_Param1;
extern Dio_LevelType        IoHwAb_User_SetDio_EN_DC_Param1;
extern uint16               Dem_SetEventStatus_Param1;
extern uint8                Dem_SetEventStatus_Param2;
extern Pwm_ChannelType      Pwm_StartPwmChannel_Param1;
extern Pwm_ChannelType      Pwm_SetDutyCycle_Param1;
extern uint16               Pwm_SetDutyCycle_Param2;
extern Pwm_ChannelType      Pwm_ClampPwmChannel_Param1;
extern tePwm_OutputState    Pwm_ClampPwmChannel_Param2;
extern NvM_BlockIdType      NvM_WriteBlock_Param1;
extern void*                NvM_WriteBlock_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType NvM_WriteBlock_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
extern uint8 Rte_Read_DcmState0_Port_HitCount;
extern uint8 Rte_Read_DcmPos0_Port_HitCount;
extern uint8 Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount;
extern uint8 Rte_Write_DcmState0_Port_HitCount;
extern uint8 Rte_Write_CddDcm_ErrorStatus_HitCount;
extern uint8 Rte_Write_DcmPos0_Port_HitCount;
extern uint8 IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount;
extern uint8 IoHwAb_User_SetDio_EN_DC_HitCount;
extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 Pwm_StartPwmChannel_HitCount;
extern uint8 Pwm_SetDutyCycle_HitCount;
extern uint8 Pwm_ClampPwmChannel_HitCount;
extern uint8 NvM_WriteBlock_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
