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
FTM_Type                FTM_DRV_SetPwmSyncMode_Param1;
bool                    FTM_DRV_SetPwmSyncMode_Param2;
FTM_Type                FTM_DRV_Enable_Param1;
bool                    FTM_DRV_Enable_Param2;
FTM_Type                FTM_DRV_SetCounter_Param1;
uint16_t                FTM_DRV_SetCounter_Param2;
FTM_Type                FTM_DRV_SetCounterInitVal_Param1;
uint16_t                FTM_DRV_SetCounterInitVal_Param2;
FTM_Type                FTM_DRV_ClearFaultControl_Param1;
FTM_Type                FTM_DRV_SetInitChnOutputCmd_Param1;
bool                    FTM_DRV_SetInitChnOutputCmd_Param2;
FTM_Type                FTM_DRV_SetDeadtimePrescale_Param1;
ftm_deadtime_ps_t       FTM_DRV_SetDeadtimePrescale_Param2;
FTM_Type                FTM_DRV_SetWriteProtectionCmd_Param1;
bool                    FTM_DRV_SetWriteProtectionCmd_Param2;
FTM_Type                FTM_DRV_SetExtDeadtimeValue_Param1;
uint8_t                 FTM_DRV_SetExtDeadtimeValue_Param2;
FTM_Type                FTM_DRV_ClearTimerOverflow_Param1;
FTM_Type                FTM_DRV_SetChnTriggerCmd_Param1;
uint8_t                 FTM_DRV_SetChnTriggerCmd_Param2;
bool                    FTM_DRV_SetChnTriggerCmd_Param3;
FTM_Type                FTM_DRV_SetDeadtimeCount_Param1;
uint8_t                 FTM_DRV_SetDeadtimeCount_Param2;
FTM_Type                FTM_DRV_GetClockSource_Param1;
FTM_Type                FTM_DRV_SetDualChnDeadtimeCmd_Param1;
uint8_t                 FTM_DRV_SetDualChnDeadtimeCmd_Param2;
bool                    FTM_DRV_SetDualChnDeadtimeCmd_Param3;
FTM_Type                FTM_DRV_SetFaultInt_Param1;
bool                    FTM_DRV_SetFaultInt_Param2;
FTM_Type                FTM_DRV_SetDualChnMofCombineCmd_Param1;
uint8_t                 FTM_DRV_SetDualChnMofCombineCmd_Param2;
bool                    FTM_DRV_SetDualChnMofCombineCmd_Param3;
FTM_Type                FTM_DRV_SetFaultControlMode_Param1;
uint32_t                FTM_DRV_SetFaultControlMode_Param2;
FTM_Type                FTM_DRV_SetDualChnCombineCmd_Param1;
uint8_t                 FTM_DRV_SetDualChnCombineCmd_Param2;
bool                    FTM_DRV_SetDualChnCombineCmd_Param3;
FTM_Type                FTM_DRV_SetDualChnPwmSyncCmd_Param1;
uint8_t                 FTM_DRV_SetDualChnPwmSyncCmd_Param2;
bool                    FTM_DRV_SetDualChnPwmSyncCmd_Param3;
FTM_Type                FTM_DRV_SetDualChnFaultCmd_Param1;
uint8_t                 FTM_DRV_SetDualChnFaultCmd_Param2;
bool                    FTM_DRV_SetDualChnFaultCmd_Param3;
FTM_Type                FTM_DRV_SetChnFaultInputPolarityCmd_Param1;
uint8_t                 FTM_DRV_SetChnFaultInputPolarityCmd_Param2;
bool                    FTM_DRV_SetChnFaultInputPolarityCmd_Param3;
FTM_Type                FTM_DRV_SetDualEdgeCaptureCmd_Param1;
uint8_t                 FTM_DRV_SetDualEdgeCaptureCmd_Param2;
bool                    FTM_DRV_SetDualEdgeCaptureCmd_Param3;
FTM_Type                FTM_DRV_SetCpwms_Param1;
bool                    FTM_DRV_SetCpwms_Param2;
FTM_Type                FTM_DRV_SetChnMSnBAMode_Param1;
uint8_t                 FTM_DRV_SetChnMSnBAMode_Param2;
uint8_t                 FTM_DRV_SetChnMSnBAMode_Param3;
FTM_Type                FTM_DRV_SetFaultInputFilterCmd_Param1;
uint8_t                 FTM_DRV_SetFaultInputFilterCmd_Param2;
bool                    FTM_DRV_SetFaultInputFilterCmd_Param3;
FTM_Type                FTM_DRV_SetFaultInputCmd_Param1;
uint8_t                 FTM_DRV_SetFaultInputCmd_Param2;
bool                    FTM_DRV_SetFaultInputCmd_Param3;
FTM_Type                FTM_DRV_SetDualChnCompCmd_Param1;
uint8_t                 FTM_DRV_SetDualChnCompCmd_Param2;
bool                    FTM_DRV_SetDualChnCompCmd_Param3;
FTM_Type                FTM_DRV_SetChnOutputPolarityCmd_Param1;
uint8_t                 FTM_DRV_SetChnOutputPolarityCmd_Param2;
bool                    FTM_DRV_SetChnOutputPolarityCmd_Param3;
FTM_Type                FTM_DRV_SetFaultInputFilterVal_Param1;
uint32_t                FTM_DRV_SetFaultInputFilterVal_Param2;
FTM_Type                FTM_DRV_DisablePwmChannelOutputs_Param1;
uint8_t                 FTM_DRV_DisablePwmChannelOutputs_Param2;
FTM_Type                FTM_DRV_SetPwmFaultBehavior_Param1;
bool                    FTM_DRV_SetPwmFaultBehavior_Param2;
uint32_t                FTM_DRV_ConvertFreqToPeriodTicks_Param1;
uint32_t                FTM_DRV_ConvertFreqToPeriodTicks_Param2;
FTM_Type                FTM_DRV_SetChnEdgeLevel_Param1;
uint8_t                 FTM_DRV_SetChnEdgeLevel_Param2;
uint8_t                 FTM_DRV_SetChnEdgeLevel_Param3;
FTM_Type                FTM_DRV_GetDualChnMofCombineCmd_Param1;
uint8_t                 FTM_DRV_GetDualChnMofCombineCmd_Param2;
FTM_Type                FTM_DRV_GetCpwms_Param1;
FTM_Type                FTM_DRV_GetDualChnCombineCmd_Param1;
uint8_t                 FTM_DRV_GetDualChnCombineCmd_Param2;
uint32_t                FTM_DRV_UpdatePwmPeriod_Param1;
ftm_pwm_update_option_t FTM_DRV_UpdatePwmPeriod_Param2;
uint32_t                FTM_DRV_UpdatePwmPeriod_Param3;
pwm_instance_t          PWM_Init_Param1;
pwm_global_config_t     PWM_Init_Param2;
FTM_Type                FTM_DRV_SetChnSoftwareCtrlVal_Param1;
uint8_t                 FTM_DRV_SetChnSoftwareCtrlVal_Param2;
bool                    FTM_DRV_SetChnSoftwareCtrlVal_Param3;
FTM_Type                FTM_DRV_GetMod_Param1;
FTM_Type                FTM_DRV_SetChnSoftwareCtrlCmd_Param1;
uint8_t                 FTM_DRV_SetChnSoftwareCtrlCmd_Param2;
bool                    FTM_DRV_SetChnSoftwareCtrlCmd_Param3;
FTM_Type                FTM_DRV_EnablePwmChannelOutputs_Param1;
uint8_t                 FTM_DRV_EnablePwmChannelOutputs_Param2;
FTM_Type                FTM_DRV_ClearChnEventFlag_Param1;
uint8_t                 FTM_DRV_ClearChnEventFlag_Param2;
FTM_Type                FTM_DRV_SetChnCountVal_Param1;
uint8_t                 FTM_DRV_SetChnCountVal_Param2;
uint16_t                FTM_DRV_SetChnCountVal_Param3;
FTM_Type                FTM_DRV_SetSoftwareTriggerCmd_Param1;
bool                    FTM_DRV_SetSoftwareTriggerCmd_Param2;
FTM_Type                FTM_DRV_SetClockSource_Param1;
ftm_clock_source_t      FTM_DRV_SetClockSource_Param2;
FTM_Type                FTM_DRV_SetMod_Param1;
uint16_t                FTM_DRV_SetMod_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
uint8_t  FTM_DRV_GetClockSource_RetVal;
uint16_t FTM_DRV_ConvertFreqToPeriodTicks_RetVal;
bool     FTM_DRV_GetDualChnMofCombineCmd_RetVal;
bool     FTM_DRV_GetCpwms_RetVal;
bool     FTM_DRV_GetDualChnCombineCmd_RetVal;
uint16_t FTM_DRV_GetMod_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 FTM_DRV_SetPwmSyncMode_HitCount;
uint8 FTM_DRV_Enable_HitCount;
uint8 FTM_DRV_SetCounter_HitCount;
uint8 FTM_DRV_SetCounterInitVal_HitCount;
uint8 FTM_DRV_ClearFaultControl_HitCount;
uint8 FTM_DRV_SetInitChnOutputCmd_HitCount;
uint8 FTM_DRV_SetDeadtimePrescale_HitCount;
uint8 FTM_DRV_SetWriteProtectionCmd_HitCount;
uint8 FTM_DRV_SetExtDeadtimeValue_HitCount;
uint8 FTM_DRV_ClearTimerOverflow_HitCount;
uint8 FTM_DRV_SetChnTriggerCmd_HitCount;
uint8 FTM_DRV_SetDeadtimeCount_HitCount;
uint8 FTM_DRV_GetClockSource_HitCount;
uint8 FTM_DRV_SetDualChnDeadtimeCmd_HitCount;
uint8 FTM_DRV_SetFaultInt_HitCount;
uint8 FTM_DRV_SetDualChnMofCombineCmd_HitCount;
uint8 FTM_DRV_SetFaultControlMode_HitCount;
uint8 FTM_DRV_SetDualChnCombineCmd_HitCount;
uint8 FTM_DRV_SetDualChnPwmSyncCmd_HitCount;
uint8 FTM_DRV_SetDualChnFaultCmd_HitCount;
uint8 FTM_DRV_SetChnFaultInputPolarityCmd_HitCount;
uint8 FTM_DRV_SetDualEdgeCaptureCmd_HitCount;
uint8 FTM_DRV_SetCpwms_HitCount;
uint8 FTM_DRV_SetChnMSnBAMode_HitCount;
uint8 FTM_DRV_SetFaultInputFilterCmd_HitCount;
uint8 FTM_DRV_SetFaultInputCmd_HitCount;
uint8 FTM_DRV_SetDualChnCompCmd_HitCount;
uint8 FTM_DRV_SetChnOutputPolarityCmd_HitCount;
uint8 FTM_DRV_SetFaultInputFilterVal_HitCount;
uint8 FTM_DRV_DisablePwmChannelOutputs_HitCount;
uint8 FTM_DRV_SetPwmFaultBehavior_HitCount;
uint8 FTM_DRV_ConvertFreqToPeriodTicks_HitCount;
uint8 FTM_DRV_SetChnEdgeLevel_HitCount;
uint8 FTM_DRV_GetDualChnMofCombineCmd_HitCount;
uint8 FTM_DRV_GetCpwms_HitCount;
uint8 FTM_DRV_GetDualChnCombineCmd_HitCount;
uint8 FTM_DRV_SetMod_HitCount;
uint8 FTM_DRV_UpdatePwmPeriod_HitCount;
uint8 PWM_Init_HitCount;
uint8 FTM_DRV_SetChnSoftwareCtrlVal_HitCount;
uint8 FTM_DRV_GetMod_HitCount;
uint8 FTM_DRV_SetChnSoftwareCtrlCmd_HitCount;
uint8 FTM_DRV_EnablePwmChannelOutputs_HitCount;
uint8 FTM_DRV_ClearChnEventFlag_HitCount;
uint8 FTM_DRV_SetChnCountVal_HitCount;
uint8 FTM_DRV_SetSoftwareTriggerCmd_HitCount;
uint8 FTM_DRV_SetClockSource_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetPwmSyncMode
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetPwmSyncMode
///
/// \param  ftmBase
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetPwmSyncMode(FTM_Type * const ftmBase, bool enable)
{
	FTM_DRV_SetPwmSyncMode_Param1 = *ftmBase;
	FTM_DRV_SetPwmSyncMode_Param2 = enable;
	FTM_DRV_SetPwmSyncMode_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_Enable
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_Enable
///
/// \param  ftmBase
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_Enable(FTM_Type * const ftmBase, bool enable)
{
	FTM_DRV_Enable_Param1 = *ftmBase;
	FTM_DRV_Enable_Param2 = enable;
	FTM_DRV_Enable_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetCounter
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetCounter
///
/// \param  ftmBase
/// \param  value
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetCounter(FTM_Type * const ftmBase, uint16_t value)
{
	FTM_DRV_SetCounter_Param1 = *ftmBase;
	FTM_DRV_SetCounter_Param2 = value;
	FTM_DRV_SetCounter_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetCounterInitVal
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetCounterInitVal
///
/// \param  ftmBase
/// \param  value
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetCounterInitVal(FTM_Type * const ftmBase, uint16_t value)
{
	FTM_DRV_SetCounterInitVal_Param1 = *ftmBase;
	FTM_DRV_SetCounterInitVal_Param2 = value;
	FTM_DRV_SetCounterInitVal_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_ClearFaultControl
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_ClearFaultControl
///
/// \param  ftmBase
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_ClearFaultControl(FTM_Type * const ftmBase)
{
	FTM_DRV_ClearFaultControl_Param1 = *ftmBase;
	FTM_DRV_ClearFaultControl_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetInitChnOutputCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetInitChnOutputCmd
///
/// \param  ftmBase
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetInitChnOutputCmd(FTM_Type * const ftmBase, bool enable)
{
	FTM_DRV_SetInitChnOutputCmd_Param1 = *ftmBase;
	FTM_DRV_SetInitChnOutputCmd_Param2 = enable;
	FTM_DRV_SetInitChnOutputCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetDeadtimePrescale
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetDeadtimePrescale
///
/// \param  ftmBase
/// \param  divider
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetDeadtimePrescale(FTM_Type * const ftmBase, ftm_deadtime_ps_t divider)
{
	FTM_DRV_SetDeadtimePrescale_Param1 = *ftmBase;
	FTM_DRV_SetDeadtimePrescale_Param2 = divider;
	FTM_DRV_SetDeadtimePrescale_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetWriteProtectionCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetWriteProtectionCmd
///
/// \param  ftmBase
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetWriteProtectionCmd(FTM_Type * const ftmBase, bool enable)
{
	FTM_DRV_SetWriteProtectionCmd_Param1 = *ftmBase;
	FTM_DRV_SetWriteProtectionCmd_Param2 = enable;
	FTM_DRV_SetWriteProtectionCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetExtDeadtimeValue
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetExtDeadtimeValue
///
/// \param  ftmBase
/// \param  value
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetExtDeadtimeValue(FTM_Type * const ftmBase, uint8_t value)
{
	FTM_DRV_SetExtDeadtimeValue_Param1 = *ftmBase;
	FTM_DRV_SetExtDeadtimeValue_Param2 = value;
	FTM_DRV_SetExtDeadtimeValue_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_ClearTimerOverflow
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_ClearTimerOverflow
///
/// \param  ftmBase
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_ClearTimerOverflow(FTM_Type * const ftmBase)
{
	FTM_DRV_ClearTimerOverflow_Param1 = *ftmBase;
	FTM_DRV_ClearTimerOverflow_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetChnTriggerCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetChnTriggerCmd
///
/// \param  ftmBase
/// \param  channel
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetChnTriggerCmd(FTM_Type * const ftmBase, uint8_t channel, bool enable)
{
	FTM_DRV_SetChnTriggerCmd_Param1 = *ftmBase;
	FTM_DRV_SetChnTriggerCmd_Param2 = channel;
	FTM_DRV_SetChnTriggerCmd_Param3 = enable;
	FTM_DRV_SetChnTriggerCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetDeadtimeCount
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetDeadtimeCount
///
/// \param  ftmBase
/// \param  count
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetDeadtimeCount(FTM_Type * const ftmBase, uint8_t count)
{
	FTM_DRV_SetDeadtimeCount_Param1 = *ftmBase;
	FTM_DRV_SetDeadtimeCount_Param2 = count;
	FTM_DRV_SetDeadtimeCount_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_GetClockSource
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_GetClockSource
///
/// \param  ftmBase
///
/// \return void
//-----------------------------------------------------------------------------
uint8_t FTM_DRV_GetClockSource(const FTM_Type * ftmBase)
{
	FTM_DRV_GetClockSource_Param1 = *ftmBase;
	FTM_DRV_GetClockSource_HitCount++;
	return FTM_DRV_GetClockSource_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetDualChnDeadtimeCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetDualChnDeadtimeCmd
///
/// \param  ftmBase
/// \param  chnlPairNum
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetDualChnDeadtimeCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable)
{
	FTM_DRV_SetDualChnDeadtimeCmd_Param1 = *ftmBase;
	FTM_DRV_SetDualChnDeadtimeCmd_Param2 = chnlPairNum;
	FTM_DRV_SetDualChnDeadtimeCmd_Param3 = enable;
	FTM_DRV_SetDualChnDeadtimeCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetFaultInt
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetFaultInt
///
/// \param  ftmBase
/// \param  state
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetFaultInt(FTM_Type * const ftmBase, bool state)
{
	FTM_DRV_SetFaultInt_Param1 = *ftmBase;
	FTM_DRV_SetFaultInt_Param2 = state;
	FTM_DRV_SetFaultInt_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetDualChnMofCombineCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetDualChnMofCombineCmd
///
/// \param  ftmBase
/// \param  chnlPairNum
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetDualChnMofCombineCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable)
{
	FTM_DRV_SetDualChnMofCombineCmd_Param1 = *ftmBase;
	FTM_DRV_SetDualChnMofCombineCmd_Param2 = chnlPairNum;
	FTM_DRV_SetDualChnMofCombineCmd_Param3 = enable;
	FTM_DRV_SetDualChnMofCombineCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetFaultControlMode
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetFaultControlMode
///
/// \param  ftmBase
/// \param  mode
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetFaultControlMode(FTM_Type * const ftmBase, uint32_t mode)
{
	FTM_DRV_SetFaultControlMode_Param1 = *ftmBase;
	FTM_DRV_SetFaultControlMode_Param2 = mode;
	FTM_DRV_SetFaultControlMode_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetDualChnCombineCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetDualChnCombineCmd
///
/// \param  ftmBase
/// \param  chnlPairNum
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetDualChnCombineCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable)
{
	FTM_DRV_SetDualChnCombineCmd_Param1 = *ftmBase;
	FTM_DRV_SetDualChnCombineCmd_Param2 = chnlPairNum;
	FTM_DRV_SetDualChnCombineCmd_Param3 = enable;
	FTM_DRV_SetDualChnCombineCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetDualChnPwmSyncCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetDualChnPwmSyncCmd
///
/// \param  ftmBase
/// \param  chnlPairNum
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetDualChnPwmSyncCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable)
{
	FTM_DRV_SetDualChnPwmSyncCmd_Param1 = *ftmBase;
	FTM_DRV_SetDualChnPwmSyncCmd_Param2 = chnlPairNum;
	FTM_DRV_SetDualChnPwmSyncCmd_Param3 = enable;
	FTM_DRV_SetDualChnPwmSyncCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetDualChnFaultCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetDualChnFaultCmd
///
/// \param  ftmBase
/// \param  chnlPairNum
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetDualChnFaultCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable)
{
	FTM_DRV_SetDualChnFaultCmd_Param1 = *ftmBase;
	FTM_DRV_SetDualChnFaultCmd_Param2 = chnlPairNum;
	FTM_DRV_SetDualChnFaultCmd_Param3 = enable;
	FTM_DRV_SetDualChnFaultCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetChnFaultInputPolarityCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetChnFaultInputPolarityCmd
///
/// \param  ftmBase
/// \param  fltChannel
/// \param  polarity
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetChnFaultInputPolarityCmd(FTM_Type * const ftmBase, uint8_t fltChannel, bool polarity)
{
	FTM_DRV_SetChnFaultInputPolarityCmd_Param1 = *ftmBase;
	FTM_DRV_SetChnFaultInputPolarityCmd_Param2 = fltChannel;
	FTM_DRV_SetChnFaultInputPolarityCmd_Param3 = polarity;
	FTM_DRV_SetChnFaultInputPolarityCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetDualEdgeCaptureCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetDualEdgeCaptureCmd
///
/// \param  ftmBase
/// \param  chnlPairNum
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetDualEdgeCaptureCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool enable)
{
	FTM_DRV_SetDualEdgeCaptureCmd_Param1 = *ftmBase;
	FTM_DRV_SetDualEdgeCaptureCmd_Param2 = chnlPairNum;
	FTM_DRV_SetDualEdgeCaptureCmd_Param3 = enable;
	FTM_DRV_SetDualEdgeCaptureCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetCpwms
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetCpwms
///
/// \param  ftmBase
/// \param  mode
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetCpwms(FTM_Type * const ftmBase, bool mode)
{
	FTM_DRV_SetCpwms_Param1 = *ftmBase;
	FTM_DRV_SetCpwms_Param2 = mode;
	FTM_DRV_SetCpwms_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetChnMSnBAMode
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetChnMSnBAMode
///
/// \param  ftmBase
/// \param  channel
/// \param  selection
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetChnMSnBAMode(FTM_Type * const ftmBase, uint8_t channel, uint8_t selection)
{
	FTM_DRV_SetChnMSnBAMode_Param1 = *ftmBase;
	FTM_DRV_SetChnMSnBAMode_Param2 = channel;
	FTM_DRV_SetChnMSnBAMode_Param3 = selection;
	FTM_DRV_SetChnMSnBAMode_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetFaultInputFilterCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetFaultInputFilterCmd
///
/// \param  ftmBase
/// \param  inputNum
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetFaultInputFilterCmd(FTM_Type * const ftmBase, uint8_t inputNum, bool enable)
{
	FTM_DRV_SetFaultInputFilterCmd_Param1 = *ftmBase;
	FTM_DRV_SetFaultInputFilterCmd_Param2 = inputNum;
	FTM_DRV_SetFaultInputFilterCmd_Param3 = enable;
	FTM_DRV_SetFaultInputFilterCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetFaultInputCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetFaultInputCmd
///
/// \param  ftmBase
/// \param  inputNum
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetFaultInputCmd(FTM_Type * const ftmBase, uint8_t inputNum, bool enable)
{
	FTM_DRV_SetFaultInputCmd_Param1 = *ftmBase;
	FTM_DRV_SetFaultInputCmd_Param2 = inputNum;
	FTM_DRV_SetFaultInputCmd_Param3 = enable;
	FTM_DRV_SetFaultInputCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetDualChnCompCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetDualChnCompCmd
///
/// \param  ftmBase
/// \param  chnlPairNum
/// \param  polarity
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetDualChnCompCmd(FTM_Type * const ftmBase, uint8_t chnlPairNum, bool polarity)
{
	FTM_DRV_SetDualChnCompCmd_Param1 = *ftmBase;
	FTM_DRV_SetDualChnCompCmd_Param2 = chnlPairNum;
	FTM_DRV_SetDualChnCompCmd_Param3 = polarity;
	FTM_DRV_SetDualChnCompCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetChnOutputPolarityCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetChnOutputPolarityCmd
///
/// \param  ftmBase
/// \param  channel
/// \param  polarity
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetChnOutputPolarityCmd(FTM_Type * const ftmBase, uint8_t channel, bool polarity)
{
	FTM_DRV_SetChnOutputPolarityCmd_Param1 = *ftmBase;
	FTM_DRV_SetChnOutputPolarityCmd_Param2 = channel;
	FTM_DRV_SetChnOutputPolarityCmd_Param3 = polarity;
	FTM_DRV_SetChnOutputPolarityCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetFaultInputFilterVal
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetFaultInputFilterVal
///
/// \param  ftmBase
/// \param  value
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetFaultInputFilterVal(FTM_Type * const ftmBase, uint32_t value)
{
	FTM_DRV_SetFaultInputFilterVal_Param1 = *ftmBase;
	FTM_DRV_SetFaultInputFilterVal_Param2 = value;
	FTM_DRV_SetFaultInputFilterVal_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_DisablePwmChannelOutputs
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_DisablePwmChannelOutputs
///
/// \param  ftmBase
/// \param  channel
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_DisablePwmChannelOutputs(FTM_Type * const ftmBase, uint8_t channel)
{
	FTM_DRV_DisablePwmChannelOutputs_Param1 = *ftmBase;
	FTM_DRV_DisablePwmChannelOutputs_Param2 = channel;
	FTM_DRV_DisablePwmChannelOutputs_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetPwmFaultBehavior
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetPwmFaultBehavior
///
/// \param  ftmBase
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetPwmFaultBehavior(FTM_Type * const ftmBase, bool enable)
{
	FTM_DRV_SetPwmFaultBehavior_Param1 = *ftmBase;
	FTM_DRV_SetPwmFaultBehavior_Param2 = enable;
	FTM_DRV_SetPwmFaultBehavior_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_ConvertFreqToPeriodTicks
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_ConvertFreqToPeriodTicks
///
/// \param  instance
/// \param  freqencyHz
///
/// \return uint16_t
//-----------------------------------------------------------------------------
uint16_t FTM_DRV_ConvertFreqToPeriodTicks(uint32_t instance, uint32_t freqencyHz)
{
	FTM_DRV_ConvertFreqToPeriodTicks_Param1 = instance;
	FTM_DRV_ConvertFreqToPeriodTicks_Param2 = freqencyHz;
	FTM_DRV_ConvertFreqToPeriodTicks_HitCount++;
	return FTM_DRV_ConvertFreqToPeriodTicks_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetChnEdgeLevel
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetChnEdgeLevel
///
/// \param  ftmBase
/// \param  channel
/// \param  level
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetChnEdgeLevel(FTM_Type * const ftmBase, uint8_t channel, uint8_t level)
{
	FTM_DRV_SetChnEdgeLevel_Param1 = *ftmBase;
	FTM_DRV_SetChnEdgeLevel_Param2 = channel;
	FTM_DRV_SetChnEdgeLevel_Param3 = level;
	FTM_DRV_SetChnEdgeLevel_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_GetDualChnMofCombineCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_GetDualChnMofCombineCmd
///
/// \param  ftmBase
/// \param  chnlPairNum
///
/// \return bool
//-----------------------------------------------------------------------------
bool FTM_DRV_GetDualChnMofCombineCmd(const FTM_Type * ftmBase, uint8_t chnlPairNum)
{
	FTM_DRV_GetDualChnMofCombineCmd_Param1 = *ftmBase;
	FTM_DRV_GetDualChnMofCombineCmd_Param2 = chnlPairNum;
	FTM_DRV_GetDualChnMofCombineCmd_HitCount++;
	return FTM_DRV_GetDualChnMofCombineCmd_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_GetCpwms
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_GetCpwms
///
/// \param  ftmBase
///
/// \return bool
//-----------------------------------------------------------------------------
bool FTM_DRV_GetCpwms(const FTM_Type * ftmBase)
{
	FTM_DRV_GetCpwms_Param1 = *ftmBase;
	FTM_DRV_GetCpwms_HitCount++;
	return FTM_DRV_GetCpwms_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_GetDualChnCombineCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_GetDualChnCombineCmd
///
/// \param  ftmBase
/// \param  chnlPairNum
///
/// \return bool
//-----------------------------------------------------------------------------
bool FTM_DRV_GetDualChnCombineCmd(const FTM_Type * ftmBase, uint8_t chnlPairNum)
{
	FTM_DRV_GetDualChnCombineCmd_Param1 = *ftmBase;
	FTM_DRV_GetDualChnCombineCmd_Param2 = chnlPairNum;
	FTM_DRV_GetDualChnCombineCmd_HitCount++;
	return FTM_DRV_GetDualChnCombineCmd_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetMod
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetMod
///
/// \param  ftmBase
/// \param  value
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetMod(FTM_Type * const ftmBase, uint16_t value)
{
	FTM_DRV_SetMod_Param1 = *ftmBase;
	FTM_DRV_SetMod_Param2 = value;
	FTM_DRV_SetMod_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetClockSource
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetClockSource
///
/// \param  ftmBase
/// \param  clock
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetClockSource(FTM_Type * const ftmBase, ftm_clock_source_t clock)
{
	FTM_DRV_SetClockSource_Param1 = *ftmBase;
	FTM_DRV_SetClockSource_Param2 = clock;
	FTM_DRV_SetClockSource_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetSoftwareTriggerCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetSoftwareTriggerCmd
///
/// \param  ftmBase
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetSoftwareTriggerCmd(FTM_Type * const ftmBase, bool enable)
{
	FTM_DRV_SetSoftwareTriggerCmd_Param1 = *ftmBase;
	FTM_DRV_SetSoftwareTriggerCmd_Param2 = enable;
	FTM_DRV_SetSoftwareTriggerCmd_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetChnCountVal
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetChnCountVal
///
/// \param  ftmBase
/// \param  channel
/// \param  value
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetChnCountVal(FTM_Type * const ftmBase, uint8_t channel, uint16_t value)
{
	FTM_DRV_SetChnCountVal_Param1 = *ftmBase;
	FTM_DRV_SetChnCountVal_Param2 = channel;
	FTM_DRV_SetChnCountVal_Param3 = value;
	FTM_DRV_SetChnCountVal_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_ClearChnEventFlag
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_ClearChnEventFlag
///
/// \param  ftmBase
/// \param  channel
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_ClearChnEventFlag(FTM_Type * const ftmBase, uint8_t channel)
{
	FTM_DRV_ClearChnEventFlag_Param1 = *ftmBase;
	FTM_DRV_ClearChnEventFlag_Param2 = channel;
	FTM_DRV_ClearChnEventFlag_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_EnablePwmChannelOutputs
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_EnablePwmChannelOutputs
///
/// \param  ftmBase
/// \param  channel
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_EnablePwmChannelOutputs(FTM_Type * const ftmBase, uint8_t channel)
{
	FTM_DRV_EnablePwmChannelOutputs_Param1 = *ftmBase;
	FTM_DRV_EnablePwmChannelOutputs_Param2 = channel;
	FTM_DRV_EnablePwmChannelOutputs_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetChnSoftwareCtrlCmd
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetChnSoftwareCtrlCmd
///
/// \param  ftmBase
/// \param  channel
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetChnSoftwareCtrlCmd(FTM_Type * const ftmBase, uint8_t channel, bool enable)
{
	FTM_DRV_SetChnSoftwareCtrlCmd_Param1 = *ftmBase;
	FTM_DRV_SetChnSoftwareCtrlCmd_Param2 = channel;
	FTM_DRV_SetChnSoftwareCtrlCmd_Param3 = enable;
	FTM_DRV_SetChnSoftwareCtrlCmd_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_GetMod
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_GetMod
///
/// \param  ftmBase
///
/// \return uint16_t
//-----------------------------------------------------------------------------
uint16_t FTM_DRV_GetMod(const FTM_Type * ftmBase)
{
	FTM_DRV_GetMod_Param1 = *ftmBase;
	FTM_DRV_GetMod_HitCount++;
	return FTM_DRV_GetMod_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  PWM_Init
///
/// \descr  Stub function created to simulate the behaviour of PWM_Init
///
/// \param  instance
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t PWM_Init(const pwm_instance_t * const instance, const pwm_global_config_t* config)
{
	PWM_Init_Param1 = *instance;
	PWM_Init_Param2 = *config;
	PWM_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_SetChnSoftwareCtrlVal
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_SetChnSoftwareCtrlVal
///
/// \param  ftmBase
/// \param  channel
/// \param  enable
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_DRV_SetChnSoftwareCtrlVal(FTM_Type * const ftmBase, uint8_t channel, bool enable)
{
	FTM_DRV_SetChnSoftwareCtrlVal_Param1 = *ftmBase;
	FTM_DRV_SetChnSoftwareCtrlVal_Param2 = channel;
	FTM_DRV_SetChnSoftwareCtrlVal_Param3 = enable;
	FTM_DRV_SetChnSoftwareCtrlVal_HitCount++;
}


 // EOF

