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
#include <Std_Types.h>
#include <IoHwAbUser.h>
#include <UtilMath.h>
#include <CddEft.h>
#include <Fee.h>

//=============================================================================
// typedefs
//=============================================================================

typedef sint32 tFiltIir_s;

typedef enum enumDigState
{
  Di_Off = 0,
  Di_OnDelay = 1,
  Di_On = 2,
  Di_OffDelay = 3,
  Di_Sna = 4
}
tieDigState;

enum
{
  NvmBlockDeltaPwmParaId = 5
};

typedef sint32 ORDER1_Filter;

typedef struct
{
  uint32 MT_MEM_ADDR_LR_DET;
  uint32 MT_MEM_ADDR_LR_DET_INV;
} Mt_IoHwAbUserLRDet;


typedef uint32 Dio_ChannelType;
typedef uint8  Dio_LevelType;
typedef uint32 Pwm_ChannelType;

//=============================================================================
// Stub function declarations
//=============================================================================

Std_ReturnType Rte_Write_IoHwAbUser_GetMountingSide(teRte_SysVolt_Results* eSetVoltageState);
Std_ReturnType Adc_ReadGroup(uint8 ucAdcIn, uint16* const unAdcValue);
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(uint16* Arg1);
Std_ReturnType Rte_Read_CodM_IoHwAbUser_Para(tsRteCodingParameters* ppara1);

Std_ReturnType Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT(const tiu32Voltage_mV* ppara1);
//Std_ReturnType Rte_Write_IoHwAb_NTCVoltage(const tsRte_Ntc* ppara1);
Std_ReturnType Rte_Write_IoHwAb_GetVoltage_NTCs(const tsRte_Voltage_mV* ppara1);
Std_ReturnType Rte_Write_IoHwAb_GetSens_Raw(const tsRte_SensorRaw* ppara1);
Std_ReturnType Rte_Write_IoHwAb_GetSens_Balanced(const tsRte_SensorBalance* ppara1);
Std_ReturnType Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1);
Std_ReturnType Rte_Write_IoHwAb_GetPCB(const tiu16Voltage_mV* ppara1);
Std_ReturnType Rte_Write_IoHwAb_VCCX1Voltage(const tiu16Voltage_mV* ppara1);
uint16         Icu_ReadPwmSensor(uint8 ucIdx);
void           Order1FilterInit(ORDER1_Filter* const pFilter, const sint16 nValue);
uint16         Order1FilterGetCoef(const uint16 unSamplimgTime, const uint16 unFilterTime); sint16 Order1FilterValue(const ORDER1_Filter* const pFilter);
uint32         LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
sint32         Order1Filter32(ORDER1_Filter32* pFilter, uint32 unBeta, sint32 nValue);
void           Order1Filter(ORDER1_Filter* const pFilter, const sint16 nValue, const uint16 unBeta);
Std_ReturnType Rte_Write_IoHwAb_VCCX1Voltage(const tiu16Voltage_mV* ppara1);
Std_ReturnType Rte_Write_IoHwAbUser_VccxLineState(const teRte_VccxLineState* ppara1);
Std_ReturnType Rte_Read_CddSwi_ScrollingOn_Stat(boolean* boStat);
uint16         Icu_GetMeasurementSens(uint8 ucIdx);
void           Icu_ChangeMeasurementMode(uint8 ucIndex, uint8 ucMesMode);
void           Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
uint16         UtilMath_FastIir_u_GetResult(const tFiltIir_u* pY);
void           UtilMath_FastIir_u(tFiltIir_u* const pY, const uint16 unInput, const uint8 ucFilt);
void           UtilMath_FastIir_u_Init(tFiltIir_u* const pY, const uint16 unInputInit);
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
uint16         CddSbc_GetPWM(uint8 ucMode);


//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tieFeeState                           Fee_State;
extern MemIf_JobResultType                   Fee_JobResult;

extern teRte_SysVolt_Results*                Rte_Write_IoHwAbUser_GetMountingSide_Param1;

extern uint8                                 Adc_ReadGroup_Param1;
extern uint16                                Adc_ReadGroup_Param2;

extern tsRteCodingParameters                 Rte_Read_CodM_IoHwAbUser_Para_Param1;

extern uint16*                               Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;

extern tiu32Voltage_mV*                      Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;

extern ORDER1_Filter*                        Order1FilterInit_Param1;
extern sint16                                Order1FilterInit_Param2;

extern uint16                                Order1FilterGetCoef_Param1;
extern uint16                                Order1FilterGetCoef_Param2;

extern ORDER1_Filter*                        Order1FilterValue_Param1;

extern uint32                                LPTMR0_GetTimeElapsed_Param1;

extern ORDER1_Filter32                       Order1Filter32_Param1;
extern uint32                                Order1Filter32_Param2;
extern sint32                                Order1Filter32_Param3;

extern ORDER1_Filter                         Order1Filter_Param1;
extern sint16                                Order1Filter_Param2;
extern uint16                                Order1Filter_Param3;

extern tsRte_SensorBalance*                  Rte_Write_IoHwAb_GetSens_Balanced_Param1;

extern tsRte_SensorRaw*                      Rte_Write_IoHwAb_GetSens_Raw_Param1;

//extern tsRte_Ntc*                            Rte_Write_IoHwAb_NTCVoltage_Param1;
extern tsRte_Voltage_mV*                     Rte_Write_IoHwAb_GetVoltage_NTCs_Param1;

extern tsRte_SensorRaw                        Rte_Read_IoHwAb_GetSens_Raw_Param1;

extern uint8                                 Icu_ReadPwmSensor_Param1;
extern uint8                                 Icu_GetMeasurementSens_Param1;
extern uint8                                 Icu_ChangeMeasurementMode_Param1;
extern uint8                                 Icu_ChangeMeasurementMode_Param2;

extern tiu16Voltage_mV                       Rte_Write_IoHwAb_GetPCB_Param1;

extern tiu16Voltage_mV                       Rte_Write_IoHwAb_VCCX1Voltage_Param1;

extern teRte_VccxLineState                   Rte_Write_IoHwAbUser_VccxLineState_Param1;

extern uint16                                Dem_SetEventStatus_Param1;
extern uint8                                 Dem_SetEventStatus_Param2;

extern tFiltIir_u                            UtilMath_FastIir_u_GetResult_Param1;

extern tFiltIir_u                            UtilMath_FastIir_u_Param1;
extern uint16                                UtilMath_FastIir_u_Param2;
extern uint8                                 UtilMath_FastIir_u_Param3;

extern tFiltIir_u                            UtilMath_FastIir_u_Init_Param1;
extern uint16                                UtilMath_FastIir_u_Init_Param2;
extern boolean*                              Rte_Read_CddSwi_ScrollingOn_Stat_Param1;

extern NvM_BlockIdType                       NvM_WriteBlock_Param1;
extern void*                                 NvM_WriteBlock_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType Rte_Write_IoHwAbUser_GetMountingSide_RetVal;
extern Std_ReturnType Adc_ReadGroup_RetVal;
extern Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
extern Std_ReturnType Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
extern Std_ReturnType Rte_Read_CodM_IoHwAbUser_Para_RetVal;
extern uint16         Order1FilterGetCoef_RetVal;
extern sint16         Order1FilterValue_RetVal;
extern uint32         LPTMR0_GetTimeElapsed_RetVal;
extern sint32         Order1Filter32_RetVal;
extern Std_ReturnType Rte_Write_IoHwAb_GetSens_Raw_RetVal;
//extern Std_ReturnType Rte_Write_IoHwAb_NTCVoltage_RetVal;
extern Std_ReturnType Rte_Write_IoHwAb_GetVoltage_NTCs_RetVal;
extern Std_ReturnType Rte_Write_IoHwAb_GetSens_Balanced_RetVal;
extern Std_ReturnType Rte_Read_IoHwAb_GetSens_Raw_RetVal;
extern uint16         Icu_ReadPwmSensor_RetVal;
extern uint16         Icu_GetMeasurementSens_RetVal;
extern Std_ReturnType Rte_Write_IoHwAb_GetPCB_RetVal;
extern Std_ReturnType Rte_Write_IoHwAb_VCCX1Voltage_RetVal;
extern Std_ReturnType Rte_Write_IoHwAbUser_VccxLineState_RetVal;
extern uint16         UtilMath_FastIir_u_GetResult_RetVal;
extern Std_ReturnType NvM_WriteBlock_RetVal;
extern Std_ReturnType Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint32 Rte_Write_IoHwAbUser_GetMountingSide_HitCount;
extern uint32 Adc_ReadGroup_HitCount;
extern uint32 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
extern uint32 Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
extern uint32 Rte_Read_CodM_IoHwAbUser_Para_HitCount;
extern uint32 Order1FilterInit_HitCount;
extern uint32 Order1FilterGetCoef_HitCount;
extern uint32 Order1FilterValue_HitCount;
extern uint32 LPTMR0_GetTimeElapsed_HitCount;
extern uint32 Order1Filter32_HitCount;
extern uint32 Order1Filter_HitCount;
//extern uint32 Rte_Write_IoHwAb_NTCVoltage_HitCount;
extern uint32 Rte_Write_IoHwAb_GetVoltage_NTCs_HitCount;
extern uint32 Rte_Write_IoHwAb_GetSens_Raw_HitCount;
extern uint32 Rte_Write_IoHwAb_GetSens_Balanced_HitCount;
extern uint32 Rte_Read_IoHwAb_GetSens_Raw_HitCount;
extern uint32 Icu_ReadPwmSensor_HitCount;
extern uint32 Icu_GetMeasurementSens_HitCount;
extern uint32 Icu_ChangeMeasurementMode_HitCount;
extern uint32 Rte_Write_IoHwAb_GetPCB_HitCount;
extern uint32 Rte_Write_IoHwAb_VCCX1Voltage_HitCount;
extern uint32 Rte_Write_IoHwAbUser_VccxLineState_HitCount;
extern uint32 Rte_Read_CddSwi_ScrollingOn_Stat_HitCount;
extern uint32 Dem_SetEventStatus_HitCount;
extern uint32 UtilMath_FastIir_u_GetResult_HitCount;
extern uint32 UtilMath_FastIir_u_HitCount;
extern uint32 UtilMath_FastIir_u_Init_HitCount;
extern uint32 NvM_WriteBlock_HitCount;
extern uint32 CddSbc_GetPWM_HitCount;


#endif // TEST_STUBS_2023_08_25_H_
