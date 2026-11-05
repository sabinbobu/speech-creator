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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>

// Headers of the Module
#include <UtilUtility.h>
#include <Nvm.h>
#include <Rte/RteCommonTypes.h>
#include <CddDcmCtrl.h>
#include <CddDcmHal.h>
//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

extern boolean         CddDcmCtrl_boAlarmActive;
extern uint16          CddDcmCtrl_unAdjustingTime;
extern uint16          CddDcmCtrl_unTimeoutCounter;
extern boolean         CddDcmCtrl_boEepromUpdated;
extern tCtrlDcmState   CddDcmCtrl_eState;
extern sint16          CddDcmCtrl_nOldPos;
extern sint16          CddDcmCtrl_nHighestPos;
extern sint16          CddDcmCtrl_nLowestPos;
extern sint16          CddDcmCtrl_nErrCnt_ms;
extern sint16          CddDcmCtrl_nErrCntLow;
extern sint16          CddDcmCtrl_nErrCntHigh;
extern tCtrlDcmVoltage CddDcmCtrl_eVoltage;

extern uint8           CddDcmHal_ucEnablePwmOutput;
extern uint32          CddDcmHal_ulOutputLevel_FB;
extern uint16          CddDcmHal_unOutputLevel;
extern uint8           CddDcmHal_ucEnablePwmOutput;
extern uint16          CddDcmHal_unLastPwmSignal;
extern uint32          CddDcmHal_ulAverageUdcmValue;
extern uint16          CddDcmHal_unMotorPwm;

//=============================================================================
// Module function declarations
//=============================================================================

extern void            CddDcmCtrl_BbSettingStart(sint16 nPos);
extern void            CddDcmCtrl_BbSettingStop_(void);
extern void            CddDcmCtrl_BbSettingDisable_(void);
extern void            CddDcmCtrl_BbSettingVoltOnOff_(uint8 ucOnOff);
extern void            CddDcmCtrl_BbSettingErr_OnOff_(uint8 ucOnOff);
extern void            CddDcmCtrl_BbSettingInit_(sint16 nPos);
extern void            CddDcmCtrl_UpdateEepromData(uint8 byPositionStatus, sint16 nTargetPosition);
extern uint16          CddDcmCtrl_GetAdjustingTime(sint16 nPos, sint16 nLowestPos, sint16 nHighestPos);
extern void            CddDcmCtrl_AlarmSet(uint16 unTimeout);
extern void            CddDcmCtrl_DisableChannel(void);
extern void            CddDcmCtrl_Disable(void);
extern void            CddDcmCtrl_Continue(void);
extern void            CddDcmCtrl_InitChannel(void);
extern void            CddDcmCtrl_ResetErrorDetection_(void);
extern boolean         CddDcmCtrl_IsMovingChannel(void);
extern void            CddDcmCtrl_Init(void);
extern void            CddDcmCtrl_ServiceMotor(sint16 nPos);
extern void            CddDcmCtrl_AlarmTimeout(void);
extern boolean         CddDcmCtrl_CtrlMsgChannel(tDcmCtrlMsg Msg);
extern void            CddDcmCtrl_CtrlMsg(void);
extern void            CddDcmCtrl_VoltChange(void);
extern void            CddDcmCtrl_DoErrorDetection(void);
extern void            CddDcmCtrl_CyclicAlarm(void);
extern void            CddDcmCtrl_Main(void);

extern void            CddDcm_OutputEnable(boolean enable);
extern uint16          CddDcm_GetVdcm(void);
extern tiu32Voltage_mV CddDcm_GetVbat(void);
extern void            CddDcmHal_DisableAndPwmOffChannel(void);
extern void            CddDcmHal_ResetVoltageState(void);
extern void            CddDcmHal_SetOutpLevelChannel(uint16 unOutputLevel);
extern void            CddDcmHal_EnableChannel(const boolean boState);
extern uint8           CddDcmHal_GetVoltageState(void);
extern uint16          CddDcmHal_CalculatePwm(const uint32 ulOutpLevel, const uint32 ulVoltDcMotor_mV);
extern void            CddDcmHal_SetMotorPwm(const uint16 unPwm);
extern uint16          CddDcmHal_ChannelLevelCtrlStart(void);
extern uint16          CddDcmHal_ChannelLevelCtrlOn(void);
extern void            CddDcmHal_ActivateChannel(const uint8 ucState);
extern void            CddDcmHal_DoOutpPwmControl(void);
extern void            CddDcmHal_IrqHookOutputPwm(void);
extern void            CddDcmHal_Init(void);
extern void            riCddDcm_Init(void);
extern void            rpCddDcm_Cycle0(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================

sint16      CddDcmCtrl_BbSettingStart_Param1;
uint8       CddDcmCtrl_BbSettingVoltOnOff__Param1;
uint8       CddDcmCtrl_BbSettingErr_OnOff__Param1;
sint16      CddDcmCtrl_BbSettingInit__Param1;
uint8       CddDcmCtrl_UpdateEepromData_Param1;
sint16      CddDcmCtrl_UpdateEepromData_Param2;
sint16      CddDcmCtrl_GetAdjustingTime_Param1;
sint16      CddDcmCtrl_GetAdjustingTime_Param2;
sint16      CddDcmCtrl_GetAdjustingTime_Param3;
uint16      CddDcmCtrl_AlarmSet_Param1;
sint16      CddDcmCtrl_ServiceMotor_Param1;
tDcmCtrlMsg CddDcmCtrl_CtrlMsgChannel_Param1;

boolean     CddDcm_OutputEnable_Param1;
uint16      CddDcmHal_SetOutpLevelChannel_Param1;
boolean     CddDcmHal_EnableChannel_Param1;
uint32      CddDcmHal_CalculatePwm_Param1;
uint32      CddDcmHal_CalculatePwm_Param2;
uint16      CddDcmHal_SetMotorPwm_Param1;
uint8       CddDcmHal_ActivateChannel_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

uint16          CddDcmCtrl_GetAdjustingTime_RetVal;
boolean         CddDcmCtrl_IsMovingChannel_RetVal;
boolean         CddDcmCtrl_CtrlMsgChannel_RetVal;

uint16          CddDcm_GetVdcm_RetVal;
tiu32Voltage_mV CddDcm_GetVbat_RetVal;
uint8           CddDcmHal_GetVoltageState_RetVal;
uint16          CddDcmHal_CalculatePwm_RetVal;
uint16          CddDcmHal_ChannelLevelCtrlStart_RetVal;
uint16          CddDcmHal_ChannelLevelCtrlOn_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

#endif // TEST_2023_08_25_H_
