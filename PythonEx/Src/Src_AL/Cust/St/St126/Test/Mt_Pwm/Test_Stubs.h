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
#include <UtilMath.h>
#include <Pwm_TargetTypes.h>

//=============================================================================
// Stub function declarations
//=============================================================================
status_t PWM_Init(const pwm_instance_t * const instance, const pwm_global_config_t* config);
void     FTM_DRV_SetChnSoftwareCtrlVal(FTM_Type * const ftmBase, uint8_t channel, bool enable);
uint16_t FTM_DRV_GetMod(const FTM_Type * ftmBase);
void     FTM_DRV_SetChnSoftwareCtrlCmd(FTM_Type * const ftmBase, uint8_t channel, bool enable);
void     FTM_DRV_EnablePwmChannelOutputs(FTM_Type * const ftmBase, uint8_t channel);
void     FTM_DRV_ClearChnEventFlag(FTM_Type * const ftmBase, uint8_t channel);
void     FTM_DRV_SetChnCountVal(FTM_Type * const ftmBase, uint8_t channel, uint16_t value);
void     FTM_DRV_SetSoftwareTriggerCmd(FTM_Type * const ftmBase, bool enable);
void     FTM_DRV_SetClockSource(FTM_Type * const ftmBase, ftm_clock_source_t clock);
void     FTM_DRV_SetMod(FTM_Type * const ftmBase, uint16_t value);
bool     FTM_DRV_GetDualChnCombineCmd(const FTM_Type * ftmBase, uint8_t chnlPairNum);
bool     FTM_DRV_GetCpwms(const FTM_Type * ftmBase);
bool     FTM_DRV_GetDualChnMofCombineCmd(const FTM_Type * ftmBase, uint8_t chnlPairNum);
void     FTM_DRV_SetChnEdgeLevel(FTM_Type * const ftmBase, uint8_t channel, uint8_t level);
uint16_t FTM_DRV_ConvertFreqToPeriodTicks(uint32_t instance, uint32_t freqencyHz);
void     FTM_DRV_SetPwmFaultBehavior(FTM_Type * const ftmBase, bool enable);
void     FTM_DRV_DisablePwmChannelOutputs(FTM_Type * const ftmBase, uint8_t channel);
void     FTM_DRV_SetFaultInputFilterVal(FTM_Type * const ftmBase, uint32_t value);
void     FTM_DRV_SetChnOutputPolarityCmd(FTM_Type * const ftmBase, uint8_t channel, bool polarity);
void     FTM_DRV_SetDualChnCompCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool polarity);
void     FTM_DRV_SetFaultInputCmd(FTM_Type * const ftmBase, uint8_t inputNum, bool enable);
void     FTM_DRV_SetFaultInputFilterCmd(FTM_Type * const ftmBase, uint8_t inputNum, bool enable);
void     FTM_DRV_SetChnMSnBAMode(FTM_Type * const ftmBase, uint8_t channel, uint8_t selection);
void     FTM_DRV_SetCpwms(FTM_Type * const ftmBase, bool mode);
void     FTM_DRV_SetDualEdgeCaptureCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable);
void     FTM_DRV_SetChnFaultInputPolarityCmd(FTM_Type * const ftmBase, uint8_t fltChannel, bool polarity);
void     FTM_DRV_SetDualChnFaultCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable);
void     FTM_DRV_SetDualChnPwmSyncCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable);
void     FTM_DRV_SetDualChnCombineCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable);
void     FTM_DRV_SetFaultControlMode(FTM_Type * const ftmBase, uint32_t mode);
void     FTM_DRV_SetDualChnMofCombineCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable);
void     FTM_DRV_SetFaultInt(FTM_Type * const ftmBase, bool state);
void     FTM_DRV_SetDualChnDeadtimeCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable);
uint8_t  FTM_DRV_GetClockSource(const FTM_Type * ftmBase);
void     FTM_DRV_SetDeadtimeCount(FTM_Type * const ftmBase, uint8_t count);
void     FTM_DRV_SetChnTriggerCmd(FTM_Type * const ftmBase, uint8_t channel, bool enable);
void     FTM_DRV_ClearTimerOverflow(FTM_Type * const ftmBase);
void     FTM_DRV_SetExtDeadtimeValue(FTM_Type * const ftmBase, uint8_t value);
void     FTM_DRV_SetWriteProtectionCmd(FTM_Type * const ftmBase, bool enable);
void     FTM_DRV_SetDeadtimePrescale(FTM_Type * const ftmBase, ftm_deadtime_ps_t divider);
void     FTM_DRV_SetInitChnOutputCmd(FTM_Type * const ftmBase, bool enable);
void     FTM_DRV_ClearFaultControl(FTM_Type * const ftmBase);
void     FTM_DRV_SetCounterInitVal(FTM_Type * const ftmBase, uint16_t value);
void     FTM_DRV_SetCounter(FTM_Type * const ftmBase, uint16_t value);
void     FTM_DRV_Enable(FTM_Type * const ftmBase, bool enable);
void     FTM_DRV_SetPwmSyncMode(FTM_Type * const ftmBase, bool enable);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern FTM_Type                FTM_DRV_SetPwmSyncMode_Param1;
extern bool                    FTM_DRV_SetPwmSyncMode_Param2;
extern FTM_Type                FTM_DRV_Enable_Param1;
extern bool                    FTM_DRV_Enable_Param2;
extern FTM_Type                FTM_DRV_SetCounter_Param1;
extern uint16_t                FTM_DRV_SetCounter_Param2;
extern FTM_Type                FTM_DRV_SetCounterInitVal_Param1;
extern uint16_t                FTM_DRV_SetCounterInitVal_Param2;
extern FTM_Type                FTM_DRV_ClearFaultControl_Param1;
extern FTM_Type                FTM_DRV_SetInitChnOutputCmd_Param1;
extern bool                    FTM_DRV_SetInitChnOutputCmd_Param2;
extern FTM_Type                FTM_DRV_SetDeadtimePrescale_Param1;
extern ftm_deadtime_ps_t       FTM_DRV_SetDeadtimePrescale_Param2;
extern FTM_Type                FTM_DRV_SetWriteProtectionCmd_Param1;
extern bool                    FTM_DRV_SetWriteProtectionCmd_Param2;
extern FTM_Type                FTM_DRV_SetExtDeadtimeValue_Param1;
extern uint8_t                 FTM_DRV_SetExtDeadtimeValue_Param2;
extern FTM_Type                FTM_DRV_ClearTimerOverflow_Param1;
extern FTM_Type                FTM_DRV_SetChnTriggerCmd_Param1;
extern uint8_t                 FTM_DRV_SetChnTriggerCmd_Param2;
extern bool                    FTM_DRV_SetChnTriggerCmd_Param3;
extern FTM_Type                FTM_DRV_SetDeadtimeCount_Param1;
extern uint8_t                 FTM_DRV_SetDeadtimeCount_Param2;
extern FTM_Type                FTM_DRV_GetClockSource_Param1;
extern FTM_Type                FTM_DRV_SetDualChnDeadtimeCmd_Param1;
extern uint8_t                 FTM_DRV_SetDualChnDeadtimeCmd_Param2;
extern bool                    FTM_DRV_SetDualChnDeadtimeCmd_Param3;
extern FTM_Type                FTM_DRV_SetFaultInt_Param1;
extern bool                    FTM_DRV_SetFaultInt_Param2;
extern FTM_Type                FTM_DRV_SetDualChnMofCombineCmd_Param1;
extern uint8_t                 FTM_DRV_SetDualChnMofCombineCmd_Param2;
extern bool                    FTM_DRV_SetDualChnMofCombineCmd_Param3;
extern FTM_Type                FTM_DRV_SetFaultControlMode_Param1;
extern uint32_t                FTM_DRV_SetFaultControlMode_Param2;
extern FTM_Type                FTM_DRV_SetDualChnCombineCmd_Param1;
extern uint8_t                 FTM_DRV_SetDualChnCombineCmd_Param2;
extern bool                    FTM_DRV_SetDualChnCombineCmd_Param3;
extern FTM_Type                FTM_DRV_SetDualChnPwmSyncCmd_Param1;
extern uint8_t                 FTM_DRV_SetDualChnPwmSyncCmd_Param2;
extern bool                    FTM_DRV_SetDualChnPwmSyncCmd_Param3;
extern FTM_Type                FTM_DRV_SetDualChnFaultCmd_Param1;
extern uint8_t                 FTM_DRV_SetDualChnFaultCmd_Param2;
extern bool                    FTM_DRV_SetDualChnFaultCmd_Param3;
extern FTM_Type                FTM_DRV_SetChnFaultInputPolarityCmd_Param1;
extern uint8_t                 FTM_DRV_SetChnFaultInputPolarityCmd_Param2;
extern bool                    FTM_DRV_SetChnFaultInputPolarityCmd_Param3;
extern FTM_Type                FTM_DRV_SetDualEdgeCaptureCmd_Param1;
extern uint8_t                 FTM_DRV_SetDualEdgeCaptureCmd_Param2;
extern bool                    FTM_DRV_SetDualEdgeCaptureCmd_Param3;
extern FTM_Type                FTM_DRV_SetCpwms_Param1;
extern bool                    FTM_DRV_SetCpwms_Param2;
extern FTM_Type                FTM_DRV_SetChnMSnBAMode_Param1;
extern uint8_t                 FTM_DRV_SetChnMSnBAMode_Param2;
extern uint8_t                 FTM_DRV_SetChnMSnBAMode_Param3;
extern FTM_Type                FTM_DRV_SetFaultInputFilterCmd_Param1;
extern uint8_t                 FTM_DRV_SetFaultInputFilterCmd_Param2;
extern bool                    FTM_DRV_SetFaultInputFilterCmd_Param3;
extern FTM_Type                FTM_DRV_SetFaultInputCmd_Param1;
extern uint8_t                 FTM_DRV_SetFaultInputCmd_Param2;
extern bool                    FTM_DRV_SetFaultInputCmd_Param3;
extern FTM_Type                FTM_DRV_SetDualChnCompCmd_Param1;
extern uint8_t                 FTM_DRV_SetDualChnCompCmd_Param2;
extern bool                    FTM_DRV_SetDualChnCompCmd_Param3;
extern FTM_Type                FTM_DRV_SetChnOutputPolarityCmd_Param1;
extern uint8_t                 FTM_DRV_SetChnOutputPolarityCmd_Param2;
extern bool                    FTM_DRV_SetChnOutputPolarityCmd_Param3;
extern FTM_Type                FTM_DRV_SetFaultInputFilterVal_Param1;
extern uint32_t                FTM_DRV_SetFaultInputFilterVal_Param2;
extern FTM_Type                FTM_DRV_DisablePwmChannelOutputs_Param1;
extern uint8_t                 FTM_DRV_DisablePwmChannelOutputs_Param2;
extern FTM_Type                FTM_DRV_SetPwmFaultBehavior_Param1;
extern bool                    FTM_DRV_SetPwmFaultBehavior_Param2;
extern uint32_t                FTM_DRV_ConvertFreqToPeriodTicks_Param1;
extern uint32_t                FTM_DRV_ConvertFreqToPeriodTicks_Param2;
extern FTM_Type                FTM_DRV_SetChnEdgeLevel_Param1;
extern uint8_t                 FTM_DRV_SetChnEdgeLevel_Param2;
extern uint8_t                 FTM_DRV_SetChnEdgeLevel_Param3;
extern FTM_Type                FTM_DRV_GetDualChnMofCombineCmd_Param1;
extern uint8_t                 FTM_DRV_GetDualChnMofCombineCmd_Param2;
extern FTM_Type                FTM_DRV_GetCpwms_Param1;
extern FTM_Type                FTM_DRV_GetDualChnCombineCmd_Param1;
extern uint8_t                 FTM_DRV_GetDualChnCombineCmd_Param2;
extern uint32_t                FTM_DRV_UpdatePwmPeriod_Param1;
extern ftm_pwm_update_option_t FTM_DRV_UpdatePwmPeriod_Param2;
extern uint32_t                FTM_DRV_UpdatePwmPeriod_Param3;
extern pwm_instance_t          PWM_Init_Param1;
extern pwm_global_config_t     PWM_Init_Param2;
extern FTM_Type                FTM_DRV_SetChnSoftwareCtrlVal_Param1;
extern uint8_t                 FTM_DRV_SetChnSoftwareCtrlVal_Param2;
extern bool                    FTM_DRV_SetChnSoftwareCtrlVal_Param3;
extern FTM_Type                FTM_DRV_GetMod_Param1;
extern FTM_Type                FTM_DRV_SetChnSoftwareCtrlCmd_Param1;
extern uint8_t                 FTM_DRV_SetChnSoftwareCtrlCmd_Param2;
extern bool                    FTM_DRV_SetChnSoftwareCtrlCmd_Param3;
extern FTM_Type                FTM_DRV_EnablePwmChannelOutputs_Param1;
extern uint8_t                 FTM_DRV_EnablePwmChannelOutputs_Param2;
extern FTM_Type                FTM_DRV_ClearChnEventFlag_Param1;
extern uint8_t                 FTM_DRV_ClearChnEventFlag_Param2;
extern FTM_Type                FTM_DRV_SetChnCountVal_Param1;
extern uint8_t                 FTM_DRV_SetChnCountVal_Param2;
extern uint16_t                FTM_DRV_SetChnCountVal_Param3;
extern FTM_Type                FTM_DRV_SetSoftwareTriggerCmd_Param1;
extern bool                    FTM_DRV_SetSoftwareTriggerCmd_Param2;
extern FTM_Type                FTM_DRV_SetClockSource_Param1;
extern ftm_clock_source_t      FTM_DRV_SetClockSource_Param2;
extern FTM_Type                FTM_DRV_SetMod_Param1;
extern uint16_t                FTM_DRV_SetMod_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern uint8_t  FTM_DRV_GetClockSource_RetVal;
extern uint16_t FTM_DRV_ConvertFreqToPeriodTicks_RetVal;
extern bool     FTM_DRV_GetDualChnMofCombineCmd_RetVal;
extern bool     FTM_DRV_GetCpwms_RetVal;
extern bool     FTM_DRV_GetDualChnCombineCmd_RetVal;
extern uint16_t FTM_DRV_GetMod_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8 FTM_DRV_SetPwmSyncMode_HitCount;
extern uint8 FTM_DRV_Enable_HitCount;
extern uint8 FTM_DRV_SetCounter_HitCount;
extern uint8 FTM_DRV_SetCounterInitVal_HitCount;
extern uint8 FTM_DRV_ClearFaultControl_HitCount;
extern uint8 FTM_DRV_SetInitChnOutputCmd_HitCount;
extern uint8 FTM_DRV_SetDeadtimePrescale_HitCount;
extern uint8 FTM_DRV_SetWriteProtectionCmd_HitCount;
extern uint8 FTM_DRV_SetExtDeadtimeValue_HitCount;
extern uint8 FTM_DRV_ClearTimerOverflow_HitCount;
extern uint8 FTM_DRV_SetChnTriggerCmd_HitCount;
extern uint8 FTM_DRV_SetDeadtimeCount_HitCount;
extern uint8 FTM_DRV_GetClockSource_HitCount;
extern uint8 FTM_DRV_SetDualChnDeadtimeCmd_HitCount;
extern uint8 FTM_DRV_SetFaultInt_HitCount;
extern uint8 FTM_DRV_SetDualChnMofCombineCmd_HitCount;
extern uint8 FTM_DRV_SetFaultControlMode_HitCount;
extern uint8 FTM_DRV_SetDualChnCombineCmd_HitCount;
extern uint8 FTM_DRV_SetDualChnPwmSyncCmd_HitCount;
extern uint8 FTM_DRV_SetDualChnFaultCmd_HitCount;
extern uint8 FTM_DRV_SetChnFaultInputPolarityCmd_HitCount;
extern uint8 FTM_DRV_SetDualEdgeCaptureCmd_HitCount;
extern uint8 FTM_DRV_SetCpwms_HitCount;
extern uint8 FTM_DRV_SetChnMSnBAMode_HitCount;
extern uint8 FTM_DRV_SetFaultInputFilterCmd_HitCount;
extern uint8 FTM_DRV_SetFaultInputCmd_HitCount;
extern uint8 FTM_DRV_SetDualChnCompCmd_HitCount;
extern uint8 FTM_DRV_SetChnOutputPolarityCmd_HitCount;
extern uint8 FTM_DRV_SetFaultInputFilterVal_HitCount;
extern uint8 FTM_DRV_DisablePwmChannelOutputs_HitCount;
extern uint8 FTM_DRV_SetPwmFaultBehavior_HitCount;
extern uint8 FTM_DRV_ConvertFreqToPeriodTicks_HitCount;
extern uint8 FTM_DRV_SetChnEdgeLevel_HitCount;
extern uint8 FTM_DRV_GetDualChnMofCombineCmd_HitCount;
extern uint8 FTM_DRV_GetCpwms_HitCount;
extern uint8 FTM_DRV_GetDualChnCombineCmd_HitCount;
extern uint8 FTM_DRV_SetMod_HitCount;
extern uint8 FTM_DRV_UpdatePwmPeriod_HitCount;
extern uint8 PWM_Init_HitCount;
extern uint8 FTM_DRV_SetChnSoftwareCtrlVal_HitCount;
extern uint8 FTM_DRV_GetMod_HitCount;
extern uint8 FTM_DRV_SetChnSoftwareCtrlCmd_HitCount;
extern uint8 FTM_DRV_EnablePwmChannelOutputs_HitCount;
extern uint8 FTM_DRV_ClearChnEventFlag_HitCount;
extern uint8 FTM_DRV_SetChnCountVal_HitCount;
extern uint8 FTM_DRV_SetSoftwareTriggerCmd_HitCount;
extern uint8 FTM_DRV_SetClockSource_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
