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
#include <Port.h>

//=============================================================================
// Typedefs
//=============================================================================
typedef enum
{
  PIN_ADC_INTERLEAVE_DISABLE0 = 0xEu,   /*!< xxx0b ADC1_SE14 channel is connected to PTB15 */
  PIN_ADC_INTERLEAVE_DISABLE1 = 0xDu,   /*!< xx0xb ADC1_SE15 channel is connected to PTB16 */
  PIN_ADC_INTERLEAVE_DISABLE2 = 0xBu,   /*!< x0xxb ADC0_SE8  channel is connected to PTC0  */
  PIN_ADC_INTERLEAVE_DISABLE3 = 0x7u,   /*!< 0xxxb ADC0_SE9  channel is connected to PTC1  */
  PIN_ADC_INTERLEAVE_ENABLE0 =  0x1u,   /*!< xxx1b ADC1_SE14 channel is connected to PTB0  */
  PIN_ADC_INTERLEAVE_ENABLE1 =  0x2u,   /*!< xx1xb ADC1_SE15 channel is connected to PTB1  */
  PIN_ADC_INTERLEAVE_ENABLE2 =  0x4u,   /*!< x1xxb ADC0_SE8  channel is connected to PTB13 */
  PIN_ADC_INTERLEAVE_ENABLE3 =  0x8u,   /*!< 1xxxb ADC0_SE9  channel is connected to PTB14 */
  PIN_ADC_INTERLEAVE_INVALID =  0xFFu   /*!< ADC interleave is invalid                     */
} pin_adc_interleave_mux_t;

//=============================================================================
// Defines
//=============================================================================


//=============================================================================
// Module global variables
//=============================================================================


//=============================================================================
// Module function declarations
//=============================================================================
extern void Port_Init(const Port_ConfigType* ConfigPtr);
extern Std_ReturnType Port_Read(uint32 portNb, uint32 pinNb, uint8* result);
extern Std_ReturnType Port_Write(uint32 portNb, uint32 pinNb, uint8 value);
extern STATIC_AL  void PINS_GPIO_WritePin(GPIO_Type* const base, pins_channel_type_t pin, pins_level_type_t value);
extern STATIC_AL uint32_t PINS_GetAdcInterleaveVal(const PORT_Type* base, const uint32_t pinPortIdx, const uint32_t currentVal);

//=============================================================================
// Module function parameter stubs
//=============================================================================


//=============================================================================
// Module function return value stubs
//=============================================================================

#endif // TEST_2023_08_25_H_
