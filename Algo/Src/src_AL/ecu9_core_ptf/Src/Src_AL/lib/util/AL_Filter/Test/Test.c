//*************************************************************************************************************************************************************
// (C) Marelli Automotive Lighting - ALIT-TO
//     Strada del Drosso 29, 10135 Torino (IT) 
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*************************************************************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/// \file  Test.c
///
/// \brief This file consists of a set of Unit Test Cases for the module AL_Filter
///
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//=============================================================================================================================================================
//
//  AL_Filter module and Mt_AL_Filter artifacts.
//
//=============================================================================================================================================================
#include <ALUnitTest_UserInterface.h>
#include <AL_Helper.h>
#include "AL_Filter.h"


//=============================================================================
// Private typedefs
//=============================================================================
// 
//=============================================================================
//  Global define
//=============================================================================
#define FILTER_BETA               125
#define NUM_SAMPLES_BUFF          10
//=============================================================================
//  Global variables of module itself
//=============================================================================
uint16 BufferFast[NUM_SAMPLES_BUFF];
uint16 BufferSlow[NUM_SAMPLES_BUFF+1];
uint32 BufferLpFilter[2];
#define FILTER_BETA 125
/* Mean fast filter configuration */
STATIC CONST(AL_Filter_MeanFastParamType, ) MeanFastFilterParamCfg[1] =
{
  {
        /* Mean buffer */
        BufferFast,
        /* Number of samples to mean */
        NUM_SAMPLES_BUFF,
      },
};

STATIC CONST(AL_Filter_MeanSlowParamType, ) MeanSlowFilterParamCfg[1] =
{
  {
        /* Mean buffer */
        BufferSlow,
        /* Number of samples to mean */
        NUM_SAMPLES_BUFF,
      },
};

/* Lowpass filter configuration */
STATIC CONST(AL_Filter_Order1FilterParamType, )LpFilterParamCfg[1] =
{
  {
        /* Mean buffer */
        BufferLpFilter,
        /* Number of samples to mean */
        FILTER_BETA,
      },
};
//=============================================================================
//  Mcal functions stub 
//=============================================================================

//=============================================================================
//  Mocks
//=============================================================================

//=============================================================================
//  Global define
//=============================================================================

//=============================================================================
//  Global variables
//=============================================================================

//=============================================================================
//  Extern data
//=============================================================================

//=============================================================================================================================================================
//
//  AL_Filter Unit Test Cases
//
//
//=============================================================================================================================================================
//-----------------------------------------------------------------------------
/// \Test Case : Mt_AL_Filter_MeanFast
///
/// \Functional Safety: QM
///
/// \Test Case Description
///     - Test subject:
///         Check if the function AL_Filter_MeanFast:
///         - return the mean value of a buffer
///
///     - Test Design Technique: ET (Exploratory Testing)
///
///
//-----------------------------------------------------------------------------
void Mt_AL_Filter_MeanFast(void)
{
    uint16 meanvalue = 0;
    uint32 mean_check_value = 0;
    uint8 i = 0;

    /* init sampled buffer */
    for (i = 0; i < NUM_SAMPLES_BUFF; i++)
    {
        BufferFast[i] = 5;
    }
    /* check mean value */
    meanvalue = AL_Filter_MeanFast(0, &MeanFastFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 5, == );

    /* change half buffer */
    for (i = 5; i < NUM_SAMPLES_BUFF; i++)
    {
        BufferFast[i] = 20;
    }

    /* compute mean value to verify */
    for (i = 0U; i < NUM_SAMPLES_BUFF; i++)
    {
        /* Apply mean */
        mean_check_value += (uint32)BufferFast[i];
    }

    /* check mean value */
    meanvalue = AL_Filter_MeanFast(0, &MeanFastFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, ((uint16)(mean_check_value / NUM_SAMPLES_BUFF)) , == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_AL_Filter_MeanSlow
///
/// \Functional Safety: QM
///
/// \Test Case Description
///     - Test subject:
///         Check if the function AL_Filter_MeanSlow:
///         - return the mean value of a buffer
///
///     - Test Design Technique: ET (Exploratory Testing)
///
///
//-----------------------------------------------------------------------------
void Mt_AL_Filter_MeanSlow(void)
{
    uint16 meanvalue = 0;
    uint8 i = 0;

    /* init sampled buffer */
    for (i = 0; i < NUM_SAMPLES_BUFF; i++)
    {
        BufferSlow[i] = 1000;
    }
    /* check mean value with a new a raw value each time */
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 900, == );
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 800, == );
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 700, == );
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 600, == );
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 500, == );
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 400, == );
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 300, == );
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 200, == );
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 100, == );
    meanvalue = AL_Filter_MeanSlow(0, &MeanSlowFilterParamCfg);
    AL_UNITTEST_CHECK(meanvalue, 0, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_AL_Filter_Order1Filter
///
/// \Functional Safety: QM
///
/// \Test Case Description
///     - Test subject:
///         Check if the function AL_Filter_Order1Filter:
///         - compute the 1st order filter
///
///     - Test Design Technique: ET (Exploratory Testing)
///
///
//-----------------------------------------------------------------------------
void Mt_AL_Filter_Order1Filter(void)
{
    uint32 meanvalue = 0;
    uint32 new_meanvalue = 0;
    uint32 result_value = 0;
    uint32 raw_value = 1000;

    /* init the filter and check */
    meanvalue = AL_Filter_Order1Filter(raw_value, &LpFilterParamCfg);
    AL_UNITTEST_CHECK(BufferLpFilter[0], (raw_value <<9), == );
    AL_UNITTEST_CHECK(BufferLpFilter[1], (0x86421357), == );
    AL_UNITTEST_CHECK(meanvalue, raw_value, == );

    /* check filter for a new value */
    raw_value = 2000;
    result_value = (uint32)((uint32)(((uint32)(BufferLpFilter[0U] * (uint8)FILTER_BETA) + (uint8)64u) >> 7u)
        + (uint32)((uint16)((uint16)((uint16)128u - (uint16)FILTER_BETA) * (uint16)4u) * (uint32)raw_value));

    new_meanvalue = (uint16)(((uint32)(result_value + (uint16)256u)) >> 9u);

    meanvalue = AL_Filter_Order1Filter(raw_value, &LpFilterParamCfg);

    AL_UNITTEST_CHECK(BufferLpFilter[0], result_value, == );
    AL_UNITTEST_CHECK(meanvalue, new_meanvalue, == );
}


// ----------------------------------------------------------------------------
// Test Cases
//-----------------------------------------------------------------------------
void ALUnitTest_AddTests(void)
{
  ALUnitTest_AddFunction("Mt_AL_Filter_MeanFast", Mt_AL_Filter_MeanFast);
  ALUnitTest_AddFunction("Mt_AL_Filter_MeanSlow", Mt_AL_Filter_MeanSlow);
  ALUnitTest_AddFunction("Mt_AL_Filter_Order1Filter", Mt_AL_Filter_Order1Filter);
}
