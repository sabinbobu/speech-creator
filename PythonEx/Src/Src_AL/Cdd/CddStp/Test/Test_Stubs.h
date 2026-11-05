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

#include <RteCommonTypes.h>
#include <Lpit_TargetTypes.h>
#include <Pwm_TargetTypes.h>
#include <CodM_Para/CodM_Para_Lwr.h>
#include <Gpt.h>

//=============================================================================
// Typedef
//=============================================================================

typedef uint32 Pwm_ChannelType;


//=============================================================================
// Stub function declarations
//=============================================================================

void                    Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
uint32                  LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
void                    Pwm_StartPwmChannel(Pwm_ChannelType channelNumber);
void                    IoHwAbUser_SetDirLwr(boolean boSettingValue);
void                    IoHwAbUser_SetLwrSleep(boolean boSettingValue);
void                    IoHwAbUser_SetLwrDrvOff(boolean boSettingValue);
void                    Lpit_LpitSetTmrChCompVal(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulCompVal);
void                    Lpit_LpitSetTmrChIntEnbl(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulIntEnbl);
void                    Lpit_LpitSetTmrEnblBit(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulEnblBit);
Std_ReturnType          Rte_Read_CodM_CddStp_Para(tsRteCodingParameters* ppara1);
Std_ReturnType          Rte_Read_ppCtrlStpTarget0_StpTargetValues(tsRte_CtrlStpTarget* ppara1);
Std_ReturnType          Rte_Write_ppCddStpActual0_sStpActualValues(const tsRte_CddStpActual* ppara1);
Std_ReturnType          Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType          Rte_Read_CtrlStp_Validation_Port(tsRte_CtrlStpValidation* ppara1);
Std_ReturnType          Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1);

boolean                 CddEft_DataValid(void);
void                    ENABLE_INTERRUPTS(void);
void                    DISABLE_INTERRUPTS(void);

void           Pwm_ClampPwmChannel(Pwm_ChannelType channelNumber, tePwm_OutputState level);
void Lpit_LpitClearTimeout(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr);
uint32 Lpit_LpitReturnCount(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr);


//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern uint16                   Dem_SetEventStatus_Param1;
extern uint8                    Dem_SetEventStatus_Param2;
extern uint32                   LPTMR0_GetTimeElapsed_Param1;
extern Pwm_ChannelType          Pwm_StartPwmChannel_Param1;
extern boolean                  IoHwAbUser_SetDirLwr_Param1;
extern boolean                  IoHwAbUser_SetLwrSleep_Param1;
extern boolean                  IoHwAbUser_SetLwrDrvOff_Param1;
extern tsLpit_LpitTmrCfg* Lpit_LpitSetTmrChCompVal_Param1;
extern tsLpit_LpitTmrCfg* Lpit_LpitSetTmrChIntEnbl_Param1;
extern tsLpit_LpitTmrCfg* Lpit_LpitSetTmrEnblBit_Param1;
extern tsLpit_LpitTmrCfg* Lpit_LpitClearTimeout_Param1;
extern tsLpit_LpitTmrCfg* Lpit_LpitReturnCount_Param1;
extern uint32                   Lpit_LpitSetTmrChCompVal_Param2;
extern uint32                   Lpit_LpitSetTmrChIntEnbl_Param2;
extern uint32                   Lpit_LpitSetTmrEnblBit_Param2;
extern tsRteCodingParameters    Rte_Read_CodM_CddStp_Para_Param1;
extern tsRte_CtrlStpTarget      Rte_Read_ppCtrlStpTarget0_StpTargetValues_Param1;
extern tsRte_CddStpActual       Rte_Write_ppCddStpActual0_sStpActualValues_Param1;
extern teRte_MountingSide       Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern tsRte_CtrlStpValidation  Rte_Read_CtrlStp_Validation_Port_Param1;
extern tiu32Voltage_mV      Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
extern Pwm_ChannelType      Pwm_ClampPwmChannel_Param1;
extern tePwm_OutputState    Pwm_ClampPwmChannel_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern uint32         LPTMR0_GetTimeElapsed_RetVal;
extern Std_ReturnType Rte_Read_CodM_CddStp_Para_RetVal;
extern Std_ReturnType Rte_Read_ppCtrlStpTarget0_StpTargetValues_RetVal;
extern Std_ReturnType Rte_Write_ppCddStpActual0_sStpActualValues_RetVal;
extern Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern Std_ReturnType Rte_Read_CtrlStp_Validation_Port_RetVal;
extern Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
extern boolean        CddEft_DataValid_RetVal;
extern uint32 Lpit_LpitReturnCount_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 LPTMR0_GetTimeElapsed_HitCount;
extern uint8 Pwm_StartPwmChannel_HitCount;
extern uint8 IoHwAbUser_SetDirLwr_HitCount;
extern uint8 IoHwAbUser_SetLwrSleep_HitCount;
extern uint8 IoHwAbUser_SetLwrDrvOff_HitCount;
extern uint8 Lpit_LpitSetTmrChCompVal_HitCount;
extern uint8 Lpit_LpitSetTmrChIntEnbl_HitCount;
extern uint8 Lpit_LpitSetTmrEnblBit_HitCount;
extern uint8 Rte_Read_CodM_CddStp_Para_HitCount;
extern uint8 Rte_Read_ppCtrlStpTarget0_StpTargetValues_HitCount;
extern uint8 Rte_Write_ppCddStpActual0_sStpActualValues_HitCount;
extern uint8 Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8 Rte_Read_CtrlStp_Validation_Port_HitCount;
extern uint8 CddEft_DataValid_Hit_Count;
extern uint8 ENABLE_INTERRUPTS_HitCount;
extern uint8 DISABLE_INTERRUPTS_HitCount;
extern uint8 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
extern uint8 Pwm_ClampPwmChannel_HitCount;
extern uint8 Lpit_LpitReturnCount_HitCount;
extern uint8 Lpit_LpitClearTimeout_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
