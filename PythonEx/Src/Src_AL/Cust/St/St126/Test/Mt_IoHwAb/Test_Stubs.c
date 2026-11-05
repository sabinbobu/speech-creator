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
#include <ALUnitTest_UserInterface.h>
#include "Test.h"
#include "Test_Stubs.h"

//=============================================================================
// Stub function parameter stubs
//=============================================================================

tieFeeState                           Fee_State;
MemIf_JobResultType                   Fee_JobResult;

teRte_SysVolt_Results*                Rte_Write_IoHwAbUser_GetMountingSide_Param1;

uint8                                 Adc_ReadGroup_Param1;
uint16                                Adc_ReadGroup_Param2;

tsRteCodingParameters                 Rte_Read_CodM_IoHwAbUser_Para_Param1;

uint16*                               Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;

tiu32Voltage_mV*                      Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;

ORDER1_Filter*                        Order1FilterInit_Param1;
sint16                                Order1FilterInit_Param2;

uint16                                Order1FilterGetCoef_Param1;
uint16                                Order1FilterGetCoef_Param2;

ORDER1_Filter*                        Order1FilterValue_Param1;

uint32                                LPTMR0_GetTimeElapsed_Param1;

ORDER1_Filter32                       Order1Filter32_Param1;
uint32                                Order1Filter32_Param2;
sint32                                Order1Filter32_Param3;

ORDER1_Filter                         Order1Filter_Param1;
sint16                                Order1Filter_Param2;
uint16                                Order1Filter_Param3;

tsRte_SensorBalance*                  Rte_Write_IoHwAb_GetSens_Balanced_Param1;

tsRte_SensorRaw*                      Rte_Write_IoHwAb_GetSens_Raw_Param1;

//tsRte_Ntc*                            Rte_Write_IoHwAb_NTCVoltage_Param1;
tsRte_Voltage_mV*                     Rte_Write_IoHwAb_GetVoltage_NTCs_Param1;

tsRte_SensorRaw                        Rte_Read_IoHwAb_GetSens_Raw_Param1;

uint8                                 Icu_ReadPwmSensor_Param1;
uint8                                 Icu_GetMeasurementSens_Param1;
uint8                                 Icu_ChangeMeasurementMode_Param1;
uint8                                 Icu_ChangeMeasurementMode_Param2;

tiu16Voltage_mV                       Rte_Write_IoHwAb_GetPCB_Param1;

tiu16Voltage_mV                       Rte_Write_IoHwAb_VCCX1Voltage_Param1;

teRte_VccxLineState                   Rte_Write_IoHwAbUser_VccxLineState_Param1;

uint16                                Dem_SetEventStatus_Param1;
uint8                                 Dem_SetEventStatus_Param2;

tFiltIir_u                            UtilMath_FastIir_u_GetResult_Param1;

tFiltIir_u                            UtilMath_FastIir_u_Param1;
uint16                                UtilMath_FastIir_u_Param2;
uint8                                 UtilMath_FastIir_u_Param3;

tFiltIir_u                            UtilMath_FastIir_u_Init_Param1;
uint16                                UtilMath_FastIir_u_Init_Param2;
boolean*                              Rte_Read_CddSwi_ScrollingOn_Stat_Param1;

NvM_BlockIdType                       NvM_WriteBlock_Param1;
void*                                 NvM_WriteBlock_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType Rte_Write_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType Adc_ReadGroup_RetVal;
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
Std_ReturnType Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
Std_ReturnType Rte_Read_CodM_IoHwAbUser_Para_RetVal;
uint16         Order1FilterGetCoef_RetVal;
sint16         Order1FilterValue_RetVal;
uint32         LPTMR0_GetTimeElapsed_RetVal;
sint32         Order1Filter32_RetVal;
Std_ReturnType Rte_Write_IoHwAb_GetSens_Raw_RetVal;
//Std_ReturnType Rte_Write_IoHwAb_NTCVoltage_RetVal;
Std_ReturnType Rte_Write_IoHwAb_GetVoltage_NTCs_RetVal;
Std_ReturnType Rte_Write_IoHwAb_GetSens_Balanced_RetVal;
Std_ReturnType Rte_Read_IoHwAb_GetSens_Raw_RetVal;
uint16         Icu_ReadPwmSensor_RetVal;
uint16         Icu_GetMeasurementSens_RetVal;
Std_ReturnType Rte_Write_IoHwAb_GetPCB_RetVal;
Std_ReturnType Rte_Write_IoHwAb_VCCX1Voltage_RetVal;
Std_ReturnType Rte_Write_IoHwAbUser_VccxLineState_RetVal;
uint16         UtilMath_FastIir_u_GetResult_RetVal;
Std_ReturnType NvM_WriteBlock_RetVal;
Std_ReturnType Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint32 Rte_Write_IoHwAbUser_GetMountingSide_HitCount;
uint32 Adc_ReadGroup_HitCount;
uint32 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
uint32 Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
uint32 Rte_Read_CodM_IoHwAbUser_Para_HitCount;
uint32 Order1FilterInit_HitCount;
uint32 Order1FilterGetCoef_HitCount;
uint32 Order1FilterValue_HitCount;
uint32 LPTMR0_GetTimeElapsed_HitCount;
uint32 Order1Filter32_HitCount;
uint32 Order1Filter_HitCount;
//uint32 Rte_Write_IoHwAb_NTCVoltage_HitCount;
uint32 Rte_Write_IoHwAb_GetVoltage_NTCs_HitCount;
uint32 Rte_Write_IoHwAb_GetSens_Raw_HitCount;
uint32 Rte_Write_IoHwAb_GetSens_Balanced_HitCount;
uint32 Rte_Read_IoHwAb_GetSens_Raw_HitCount;
uint32 Icu_ReadPwmSensor_HitCount;
uint32 Icu_GetMeasurementSens_HitCount;
uint32 Icu_ChangeMeasurementMode_HitCount;
uint32 Rte_Write_IoHwAb_GetPCB_HitCount;
uint32 Rte_Write_IoHwAb_VCCX1Voltage_HitCount;
uint32 Rte_Write_IoHwAbUser_VccxLineState_HitCount;
uint32 Rte_Read_CddSwi_ScrollingOn_Stat_HitCount;
uint32 Dem_SetEventStatus_HitCount;
uint32 UtilMath_FastIir_u_GetResult_HitCount;
uint32 UtilMath_FastIir_u_HitCount;
uint32 UtilMath_FastIir_u_Init_HitCount;
uint32 NvM_WriteBlock_HitCount;
uint32 CddSbc_GetPWM_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  NvM_WriteBlock
///
/// \descr  Stub function created to simulate the behaviour of NvM_WriteBlock
///
/// \param  - BlockId, NvM_SrcPtr
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr)
{
  NvM_WriteBlock_Param1 = BlockId;
  NvM_WriteBlock_Param2 = NvM_SrcPtr;
  NvM_WriteBlock_HitCount++;
  return NvM_WriteBlock_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Icu_ChangeMeasurementMode
///
/// \descr  Stub function created to simulate the behaviour of Icu_ChangeMeasurementMode
///
/// \param  ucIndex, ucMesMode
///
/// \return void
//-----------------------------------------------------------------------------
void Icu_ChangeMeasurementMode(uint8 ucIndex, uint8 ucMesMode)
{
  Icu_ChangeMeasurementMode_Param1 = ucIndex;
  Icu_ChangeMeasurementMode_Param2 = ucMesMode;
  Icu_ChangeMeasurementMode_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  UtilMath_FastIir_u_GetResult
///
/// \descr  Stub function created to simulate the behaviour of UtilMath_FastIir_u_GetResult
///
/// \param  ucIndex, ucMesMode
///
/// \return void
//-----------------------------------------------------------------------------
uint16 UtilMath_FastIir_u_GetResult(const tFiltIir_u* pY)
{
  UtilMath_FastIir_u_GetResult_Param1 = *pY;
  UtilMath_FastIir_u_GetResult_HitCount++;
  return UtilMath_FastIir_u_GetResult_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  UtilMath_FastIir_u
///
/// \descr  Stub function created to simulate the behaviour of UtilMath_FastIir_u
///
/// \param  ucIndex, ucMesMode
///
/// \return void
//-----------------------------------------------------------------------------
void UtilMath_FastIir_u(tFiltIir_u* const pY, const uint16 unInput, const uint8 ucFilt)
{
  UtilMath_FastIir_u_Param1 = pY;
  UtilMath_FastIir_u_Param2 = unInput;
  UtilMath_FastIir_u_Param3 = ucFilt;
  UtilMath_FastIir_u_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  UtilMath_FastIir_u
///
/// \descr  Stub function created to simulate the behaviour of UtilMath_FastIir_u
///
/// \param  ucIndex, ucMesMode
///
/// \return void
//-----------------------------------------------------------------------------
void UtilMath_FastIir_u_Init(tFiltIir_u* const pY, const uint16 unInputInit)
{
  UtilMath_FastIir_u_Init_Param1 = pY;
  UtilMath_FastIir_u_Init_Param2 = unInputInit;
  UtilMath_FastIir_u_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of Dem_SetEventStatus
///
/// \param  unAlecId
/// \param  ucTestStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus)
{
  Dem_SetEventStatus_Param1 = unAlecId;
  Dem_SetEventStatus_Param2 = ucTestStatus;
  Dem_SetEventStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Icu_GetMeasurementSens
///
/// \descr  Stub function created to simulate the behaviour of Icu_GetMeasurementSens
///
/// \param  ucIdx
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 Icu_GetMeasurementSens(uint8 ucIdx)
{
  Icu_GetMeasurementSens_Param1 = ucIdx;
  Icu_GetMeasurementSens_HitCount++;
  return Icu_GetMeasurementSens_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief
/// \descr  Stub function created to simulate the behaviour of Rte_Write_IoHwAb_VCCX1Voltage
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_IoHwAb_VCCX1Voltage(const tiu16Voltage_mV* ppara1)
{
  Rte_Write_IoHwAb_VCCX1Voltage_Param1 = ppara1;
  Rte_Write_IoHwAb_VCCX1Voltage_HitCount++;
  return Rte_Write_IoHwAb_VCCX1Voltage_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAb_GetSens_Raw
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAb_GetSens_Raw
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_GetSens_Raw_Param1;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount++;
  return Rte_Read_IoHwAb_GetSens_Raw_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Order1Filter
///
/// \descr  Stub function created to simulate the behaviour of Order1Filter
///
/// \param  pFilter
/// \param  nValue
/// \param  unBeta
///
/// \return void
//-----------------------------------------------------------------------------
void Order1Filter(ORDER1_Filter* const pFilter, const sint16 nValue, const uint16 unBeta)
{
  Order1Filter_Param1 = *pFilter;
  Order1Filter_Param2 = nValue;
  Order1Filter_Param3 = unBeta;
  Order1Filter_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Icu_ReadPwmSensor
///
/// \descr  Stub function created to simulate the behaviour of Icu_ReadPwmSensor
///
/// \param  ucIdx
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 Icu_ReadPwmSensor(uint8 ucIdx)
{
  Icu_ReadPwmSensor_Param1 = ucIdx;
  Icu_ReadPwmSensor_HitCount++;
  return Icu_ReadPwmSensor_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Order1Filter32
///
/// \descr  Stub function created to simulate the behaviour of Order1Filter32
///
/// \param  pFilter
/// \param  unBeta
/// \param  nValue
///
/// \return sint32
//-----------------------------------------------------------------------------
sint32 Order1Filter32(ORDER1_Filter32* pFilter, uint32 unBeta, sint32 nValue)
{
  Order1Filter32_Param1 = *pFilter;
  Order1Filter32_Param2 = unBeta;
  Order1Filter32_Param3 = nValue;
  Order1Filter32_HitCount++;
  return Order1Filter32_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_IoHwAbUser_GetMountingSide
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_IoHwAbUser_GetMountingSide
///
/// \param  eSetVoltageState
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_IoHwAbUser_GetMountingSide(teRte_SysVolt_Results* eSetVoltageState)
{
  Rte_Write_IoHwAbUser_GetMountingSide_Param1 = eSetVoltageState;
  Rte_Write_IoHwAbUser_GetMountingSide_HitCount++;
  return Rte_Write_IoHwAbUser_GetMountingSide_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_IoHwAbUser_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_IoHwAbUser_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_IoHwAbUser_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_IoHwAbUser_Para_Param1;
  Rte_Read_CodM_IoHwAbUser_Para_HitCount++;
  return Rte_Read_CodM_IoHwAbUser_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_IoHwAb_GetPCB
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_IoHwAb_GetPCB
///
/// \param  eSetVoltageState
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_IoHwAb_GetPCB(const tiu16Voltage_mV* ppara1)
{
  Rte_Write_IoHwAb_GetPCB_Param1 = *ppara1;
  Rte_Write_IoHwAb_GetPCB_HitCount++;
  return Rte_Write_IoHwAb_GetPCB_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_IoHwAb_NTCVoltage
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_IoHwAb_NTCVoltage
///
/// \param  eSetVoltageState
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
//Std_ReturnType Rte_Write_IoHwAb_NTCVoltage(const tsRte_Ntc* ppara1)
//{
//  Rte_Write_IoHwAb_NTCVoltage_Param1 = ppara1;
//  Rte_Write_IoHwAb_NTCVoltage_HitCount++;
//  return Rte_Write_IoHwAb_NTCVoltage_RetVal;
//}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_IoHwAb_GetVoltage_NTCs
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_IoHwAb_GetVoltage_NTCs
///
/// \param  eSetVoltageState
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_IoHwAb_GetVoltage_NTCs(const tsRte_Voltage_mV* ppara1)
{
  Rte_Write_IoHwAb_GetVoltage_NTCs_Param1 = ppara1;
  Rte_Write_IoHwAb_GetVoltage_NTCs_HitCount++;
  return Rte_Write_IoHwAb_GetVoltage_NTCs_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_IoHwAb_GetSens_Balanced
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_IoHwAb_GetSens_Balanced
///
/// \param  tsRte_SensorCounter
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_IoHwAb_GetSens_Balanced(const tsRte_SensorBalance* ppara1)
{
  Rte_Write_IoHwAb_GetSens_Balanced_Param1 = ppara1;
  Rte_Write_IoHwAb_GetSens_Balanced_HitCount++;
  return Rte_Write_IoHwAb_GetSens_Balanced_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_IoHwAb_GetSens_Raw
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_IoHwAb_GetSens_Raw
///
/// \param  tsRte_SensorCounter
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_IoHwAb_GetSens_Raw(const tsRte_SensorRaw* ppara1)
{
  Rte_Write_IoHwAb_GetSens_Raw_Param1 = ppara1;
  Rte_Write_IoHwAb_GetSens_Raw_HitCount++;
  return Rte_Write_IoHwAb_GetSens_Raw_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR0_GetTimeElapsed
///
/// \descr Stub function for LPTMR0_GetTimeElapsed
///
/// \param  ulStartValue
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_HitCount++;
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  return (LPTMR0_GetTimeElapsed_RetVal);
}

//-----------------------------------------------------------------------------
/// \brief  Adc_ReadGroup
///
/// \descr  Stub function created to simulate the behaviour of Adc_ReadGroup
///
/// \param  ucAdcIn
/// \param  unAdcValue
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Adc_ReadGroup(uint8 ucAdcIn, uint16* const unAdcValue)
{
  Adc_ReadGroup_Param1 = ucAdcIn;
  *unAdcValue = Adc_ReadGroup_Param2;
  Adc_ReadGroup_HitCount++;
  return Adc_ReadGroup_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \param  Arg1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(uint16* Arg1)
{
  *Arg1 = Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount++;
  return Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT(const tiu32Voltage_mV* ppara1)
{
  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_Param1 = ppara1;
  Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount++;
  return Rte_Write_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Order1FilterInit
///
/// \descr  Stub function created to simulate the behaviour of Order1FilterInit
///
/// \param  pFilter
/// \param  nValue
///
/// \return -
//-----------------------------------------------------------------------------
void Order1FilterInit(ORDER1_Filter* const pFilter, const sint16 nValue)
{
  Order1FilterInit_Param1 = pFilter;
  Order1FilterInit_Param2 = nValue;
  Order1FilterInit_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Order1FilterGetCoef
///
/// \descr  Stub function created to simulate the behaviour of Order1FilterGetCoef
///
/// \param  unSamplimgTime
/// \param  unFilterTime
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 Order1FilterGetCoef(const uint16 unSamplimgTime, const uint16 unFilterTime)
{
  Order1FilterGetCoef_Param1 = unSamplimgTime;
  Order1FilterGetCoef_Param2 = unFilterTime;
  Order1FilterGetCoef_HitCount++;
  return Order1FilterGetCoef_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Order1FilterValue
///
/// \descr  Stub function created to simulate the behaviour of Order1FilterValue
///
/// \param  pFilter
///
/// \return sint16
//-----------------------------------------------------------------------------
sint16 Order1FilterValue(const ORDER1_Filter* const pFilter)
{
  Order1FilterValue_Param1 = pFilter;
  Order1FilterValue_HitCount++;
  return Order1FilterValue_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_IoHwAbUser_VccxLineState
///
/// \descr  stub function to simulate the behaviour of Rte_Write_IoHwAbUser_VccxLineState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_IoHwAbUser_VccxLineState(const teRte_VccxLineState* ppara1)
{
  Rte_Write_IoHwAbUser_VccxLineState_Param1 = *ppara1;
  Rte_Write_IoHwAbUser_VccxLineState_HitCount++;

  return Rte_Write_IoHwAbUser_VccxLineState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddSwi_ScrollingOn_Stat
///
/// \descr  stub function to simulate the behaviour of Rte_Read_CddSwi_ScrollingOn_Stat
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddSwi_ScrollingOn_Stat(boolean* boStat)
{
  *boStat = *Rte_Read_CddSwi_ScrollingOn_Stat_Param1;
  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount++;
  return Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddSbc_GetPWM
///
/// \descr
///
/// \param  -
///
/// \return uint32
//-----------------------------------------------------------------------------
uint16 CddSbc_GetPWM(uint8 ucMode)
{
  CddSbc_GetPWM_Param1 = ucMode;
  CddSbc_GetPWM_HitCount++;
  return CddSbc_GetPWM_RetVal;
}