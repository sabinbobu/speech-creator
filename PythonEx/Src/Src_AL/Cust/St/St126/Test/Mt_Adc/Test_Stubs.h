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
#include <CddDma_Types.h>

//=============================================================================
// Stub function declarations
//=============================================================================
void CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback);
boolean Adc_EolCalibration_ADC0(uint32* pvStart);
boolean Adc_EolCalibration_ADC1(uint32* pvStart);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern CddDma_DynConfig_DmaChannelName_EnumType     CddDma_StartJob_Param1;
extern tsCddDma_Parameter                           CddDma_StartJob_Param2;
extern CddDma_tfpCallback                           CddDma_StartJob_Param3;

extern uint32*                                      Adc_EolCalibration_ADC0_Param1;
extern uint32*                                      Adc_EolCalibration_ADC1_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern boolean Adc_EolCalibration_ADC0_RetVal;
extern boolean Adc_EolCalibration_ADC1_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint32 CddDma_StartJob_HitCount;
extern uint32 Adc_EolCalibration_ADC0_HitCount;
extern uint32 Adc_EolCalibration_ADC1_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
