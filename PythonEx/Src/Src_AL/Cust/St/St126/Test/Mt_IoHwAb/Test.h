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
#include "Test_Stubs.h"

//=============================================================================
// Typedefs
//=============================================================================


//=============================================================================
// Defines
//=============================================================================


//=============================================================================
// Module global variables
//=============================================================================

extern uint8                         IoHwAbUser_ucRingBuffElem;

extern uint16                        IoHwAbUser_unFactorVBAT;

extern uint16                        IoHwAbUser_unFilterCoefHssSenseS1_2;
extern ORDER1_Filter                 IoHwAbUser_slHssSenseS1_2_Filter;

extern uint16                        IoHwAbUser_unFilterCoefHssSenseS3;
extern ORDER1_Filter                 IoHwAbUser_slHssSenseS3_Filter;

extern ORDER1_Filter                 IoHwAbUser_slPCB_Filter;
extern uint16                        IoHwAbUser_unFilterCoefPCB;
extern uint16                        IoHwAbUser_unFilterCoefNTC;
extern ORDER1_Filter                 IoHwAbUser_aslNTC_Filter[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS];

extern tiu32Voltage_mV               IoHwAbUser_ulVBatMean;
extern tiu32Voltage_mV               IoHwAbUser_ulVBatMin;

extern tiu32Voltage_mV               IoHwAbUser_ulPCB;
extern tiu32Voltage_mV               IoHwAbUser_ulADCHSS_3;
extern tsIoHwAbUser_HSSDioInfo       IoHwAbUser_sHssDioInfo;
extern uint16                        IoHwAbUser_unFactorHssSense3;
extern uint16                        IoHwAbUser_unFactorHssSenseS1_2;
extern tiu32Voltage_mV               IoHwAbUser_aulHSSSensorVoltage[IOHWABUSER_NR_HSSSENSOR];

extern tiu32Voltage_mV               IoHwAbUser_aulRingBuff[IOHWABUSER_RINGBUFFER_SIZE];

extern tieMountingSideRaw            IoHwAbUser_ulMountingSideRaw;
extern uint8                         IoHwAb_Adc_EXT_Channel_Map[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS];

extern Dio_ChannelType               Dio_WriteChannel_Param1;
extern Dio_LevelType                 Dio_WriteChannel_Param2;

extern Pwm_ChannelType               Pwm_SetDutyCycle_Param1;
extern uint16                        Pwm_SetDutyCycle_Param2;

extern boolean                       IoHwAbUser_boVccxStatus;

extern Dio_ChannelType               Dio_ReadChannel_Param1;

extern Dio_LevelType                 Dio_ReadChannel_RetVal;
extern uint32                        Dio_ReadChannel_HitCount;

extern uint16                        IoHwAbUser_unFactorNTC[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS];
extern tiu16Voltage_mV               IoHwAbUser_aunNTCVoltage[IOHWABUSER_CFG_MAX_NO_OF_EXT_NTCS];

extern sint32                        slSensPwmTarget[IOHWABUSER_NR_PWMTARGET];

extern sint32                        IoHwAbUser_aslSensPwmTarget[IOHWABUSER_NR_PWMTARGET];

extern uint16                        IoHwAbUser_unFactorPCB;
extern boolean                       IoHwAb_boLssDiagnostic;
extern boolean                       IoHwAbUser_boFctOut_ShGnd;
extern boolean                       IoHwAbUser_boFctOut_ShVbat;
extern uint32                        IoHwAbUser_ulFctOut_Voltage_Acc;
extern uint32                        IoHwAbUser_ulFctOut_Cnt;
extern uint16                        IoHwAbUser_unFctOut_Voltage_mV;
extern uint16                        IoHwAbUser_unFactorFout;

extern uint16                        IoHwAbUser_unSensCalculatedDuty[2u];
extern uint8                         IoHwAbUser_ucMeasMode;
extern uint8                         IoHwAbUser_ucMeasCycle;

extern uint32*                       IoHwAbUser_FTM0;
extern uint32*                       IoHwAbUser_FTM4;
extern uint32*                       IoHwAbUser_CHOVBitStatus;
extern uint16                        IoHwAbUser_unSensMeasPeriodAndDuty[2u][2u];

extern tFiltIir_u                    IoHwAbUser_aFltDC_OUT;

extern boolean                       IoHwAbUser_boIsCodingValid;

//=============================================================================
// Module function declarations
//=============================================================================

extern void IoHwAbUser_Init(void);
extern void IoHwAbUser_DeInit(void);
extern void IoHwAbUser_Cycle(void);
extern void IoHwAbUser_InitGetMountingSide(void);
extern void IoHwAbUser_HSSOperation(boolean init);
extern void IoHwAbUser_GetMountingSideRaw(tieMountingSideRaw* peVal);
extern void IoHwAbUser_SetBoostMode(const boolean boEnable1);
extern void IoHwAbUser_SetHss_En1(tun16Percent_1_328 unTgtVal);
extern void IoHwAbUser_SetHss_En2(tun16Percent_1_328 unTgtVal);
extern void IoHwAbUser_SetHss_En3(tun16Percent_1_328 unTgtVal);
extern void IoHwAbUser_SetHss_Error(boolean boSettingValue);
extern void IoHwAbUser_SetHss_Sel1(boolean boSettingValue);
extern void IoHwAbUser_SetHss_Sel2(boolean boSettingValue);
extern void IoHwAbUser_SetHss_Sen(boolean boSettingValue);
extern void IoHwAbUser_ResetHss(boolean boSettingValue);
extern void IoHwAbUser_SenseEnableHss(boolean boSettingValue);
extern void IoHwAbUser_SetDirLwr(boolean boSettingValue);
extern void IoHwAbUser_SetLwrSleep(boolean boSettingValue);
extern void IoHwAbUser_SetLwrDrvOff(boolean boSettingValue);
extern void IoHwAbUser_SetVccxEn(boolean boSettingValue);
extern void IoHwAbserTimer0Notification(void);
extern void IoHwAbUser_CalcVBatMeanValue(void);
extern void IoHwAbUser_HSSOperationForEcuHighVar(void);
extern void IoHwAbUser_HSSOperationForEcuLowVar(void);
extern void IoHwAbUser_InitializeBuffers(void);
extern void IoHwAbUser_FilterInitialization(void);
extern void riIoHwAbUserInit(void);
extern void riIoHwAbUserDeInit(void);
extern void rpIoHwAbUser5ms(void);
extern void IoHwAbUser_Set_Vccx_State(boolean boVccx_desiredState);
extern void IoHwAbUser_VccxStateCyclicCheck(void);
extern void IoHwAbUser_Get_PCB(void);
extern void IoHwAbUser_ParaFct0(void);
extern void IoHwAbUser_GetHss0Sense(uint32* unDiagVal);
extern void IoHwAbUser_GetHss1Sense(uint32* unDiagVal);
extern void IoHwAbUser_GetHss2Sense(uint32* unDiagVal);
extern tiu16Voltage_mV IoHwAbUser_Read_VCCX1(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT1(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT2(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT3(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT4(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT5(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT6(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT7(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT8(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT9(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT10(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT11(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT12(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT13(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT14(void);
extern void IoHwAbUser_GetVoltage_NTC(void);
extern tiu16Voltage_mV IoHwAbUser_GetVoltage_NTCs(uint8 ucIdx);
extern void IoHwAbUser_GetSens_Balanced(void);
extern void IoHwAbUser_GetSens_Raw(void);
extern void IoHwAbUser_CalcInputPwmSens(void);
extern boolean IoHwAbUser_CheckSens0_OpenLoad(void);
extern boolean IoHwAbUser_CheckSens1_OpenLoad(void);
extern void IoHwAbUser_ReportVccx2Error(teIoHwAb_VccxLineState eVccx1ErrorState);
extern void IoHwAb_User_SetDio_EN_DC(Dio_LevelType signal);
extern void IoHwAbUser_GetAdc_VoltDC_OUT1(uint16 *pio_signal);
extern void IoHwAbUser_SetTgtHss3(tun16Percent_1_328 unTgtVal);
extern void reIoHwAbUser_GetLssDiagnostic(void);
extern void IoHwAbUser_GetOutFctDiag(boolean *boLssDiagnostic);
extern  void IoHwAbUser_ProcessOutFctDiag(void);
extern  void IoHwAbUser_SetNvm_ElecError(uint8 ucSensIdx);


//=============================================================================
// Module function parameter stubs
//=============================================================================

boolean                   IoHwAbUser_HSSOperation_Param1;
tieMountingSideRaw*       IoHwAbUser_GetMountingSideRaw_Param1;
boolean                   IoHwAbUser_SetBoostMode_Param1;
boolean                   IoHwAbUser_HSSOperation_Param1;
tun16Percent_1_328        IoHwAbUser_SetHss_En1_Param1;
tun16Percent_1_328        IoHwAbUser_SetHss_En2_Param1;
tun16Percent_1_328        IoHwAbUser_SetHss_En3_Param1;
boolean                   IoHwAbUser_SetHss_Error_Param1;
boolean                   IoHwAbUser_SetHss_Sel1_Param1;
boolean                   IoHwAbUser_SetHss_Sel2_Param1;
boolean                   IoHwAbUser_SetHss_Sen_Param1;
boolean                   IoHwAbUser_ResetHss_Param1;
boolean                   IoHwAbUser_SenseEnableHss_Param1;
boolean                   IoHwAbUser_SetDirLwr_Param1;
boolean                   IoHwAbUser_SetLwrSleep_Param1;
boolean                   IoHwAbUser_SetLwrDrvOff_Param1;
boolean                   IoHwAbUser_SetVccxEn_Param1;
boolean                   IoHwAbUser_Set_Vccx_State_Param1;
uint32*                   IoHwAbUser_GetHss0Sense_Param1;
uint32*                   IoHwAbUser_GetHss1Sense_Param1;
uint32*                   IoHwAbUser_GetHss2Sense_Param1;
uint8                     IoHwAbUser_GetVoltage_NTCs_Param1;
teIoHwAb_VccxLineState    IoHwAbUser_ReportVccx2Error_Param1;
Dio_LevelType             IoHwAb_User_SetDio_EN_DC_Param1;
uint16                    IoHwAbUser_GetAdc_VoltDC_OUT1_Param1;
tun16Percent_1_328        IoHwAbUser_SetTgtHss3_Param1;
boolean                   IoHwAbUser_GetOutFctDiag_Param1[2];
uint8                     IoHwAbUser_SetNvm_ElecError_Param1;
uint8                     CddSbc_GetPWM_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

uint16          IoHwAbUser_Get_PCB_RetVal;
tiu16Voltage_mV IoHwAbUser_Read_VCCX1_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT1_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT2_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT3_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT4_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT5_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT6_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT7_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT8_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT9_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT10_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT11_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT12_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT13_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT14_RetVal;
tiu16Voltage_mV IoHwAbUser_GetVoltage_NTCs_RetVal;
boolean         IoHwAbUser_CheckSens0_OpenLoad_RetVal;
boolean         IoHwAbUser_CheckSens1_OpenLoad_RetVal;
uint16          CddSbc_GetPWM_RetVal;


#endif // TEST_2023_08_25_H_
