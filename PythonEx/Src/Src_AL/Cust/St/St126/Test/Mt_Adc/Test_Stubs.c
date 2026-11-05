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
CddDma_DynConfig_DmaChannelName_EnumType     CddDma_StartJob_Param1;
tsCddDma_Parameter                           CddDma_StartJob_Param2;
CddDma_tfpCallback                           CddDma_StartJob_Param3;

uint32*                                      Adc_EolCalibration_ADC0_Param1;
uint32*                                      Adc_EolCalibration_ADC1_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
boolean Adc_EolCalibration_ADC0_RetVal;
boolean Adc_EolCalibration_ADC1_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint32 CddDma_StartJob_HitCount;
uint32 Adc_EolCalibration_ADC0_HitCount;
uint32 Adc_EolCalibration_ADC1_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief CddDma_StartJob
///
/// \descr Stub function created to simulate the behaviour of CddDma_StartJob
///
/// \param  eDmaChannelName - DMA channel Id
///         psParameter     - parameter with repetitions and addresses
///         fpCallback      - function pointer for a callback
///
/// \return 
//-----------------------------------------------------------------------------
void CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback)
{
    CddDma_StartJob_Param1 = eDmaChannelName;
    CddDma_StartJob_Param2 = *psParameter;
    CddDma_StartJob_Param3 = fpCallback;
    CddDma_StartJob_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Adc_EolCalibration_ADC0
///
/// \descr Stub function created to simulate the behaviour of Adc_EolCalibration_ADC0
///
/// \param  pvStart
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Adc_EolCalibration_ADC0(uint32* pvStart)
{
    *pvStart = (uint32)Adc_EolCalibration_ADC0_Param1;
    Adc_EolCalibration_ADC0_HitCount++;
    return Adc_EolCalibration_ADC0_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Adc_EolCalibration_ADC1
///
/// \descr Stub function created to simulate the behaviour of Adc_EolCalibration_ADC1
///
/// \param  pvStart
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Adc_EolCalibration_ADC1(uint32* pvStart)
{
    *pvStart = (uint32)Adc_EolCalibration_ADC1_Param1;
    Adc_EolCalibration_ADC1_HitCount++;
    return Adc_EolCalibration_ADC1_RetVal;
}
