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
/// \file  Port.c
///
/// \brief  Port module APIs.
///
/// \descr  This file contains the implementation of Port module APIs.
///
/// \author Mertic Alexandru 
///         mailTo:alexandru-laurentiu.mertic(at)magnetimarelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
#include <Port.h>
#include <AL_Helper.h>
#ifndef UNIT_TEST
  #include <pins_driver.h>
#endif

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

/* PRQA S 303,306,316 EOF */

//=============================================================================
// Private variables
//=============================================================================

typedef enum
{
    PIN_ADC_INTERLEAVE_DISABLE0    = 0xEu,   /*!< xxx0b ADC1_SE14 channel is connected to PTB15 */
    PIN_ADC_INTERLEAVE_DISABLE1    = 0xDu,   /*!< xx0xb ADC1_SE15 channel is connected to PTB16 */
    PIN_ADC_INTERLEAVE_DISABLE2    = 0xBu,   /*!< x0xxb ADC0_SE8  channel is connected to PTC0  */
    PIN_ADC_INTERLEAVE_DISABLE3    = 0x7u,   /*!< 0xxxb ADC0_SE9  channel is connected to PTC1  */
    PIN_ADC_INTERLEAVE_ENABLE0     = 0x1u,   /*!< xxx1b ADC1_SE14 channel is connected to PTB0  */
    PIN_ADC_INTERLEAVE_ENABLE1     = 0x2u,   /*!< xx1xb ADC1_SE15 channel is connected to PTB1  */
    PIN_ADC_INTERLEAVE_ENABLE2     = 0x4u,   /*!< x1xxb ADC0_SE8  channel is connected to PTB13 */
    PIN_ADC_INTERLEAVE_ENABLE3     = 0x8u,   /*!< 1xxxb ADC0_SE9  channel is connected to PTB14 */
    PIN_ADC_INTERLEAVE_INVALID     = 0xFFu   /*!< ADC interleave is invalid                     */
} pin_adc_interleave_mux_t;


STATIC_AL uint32_t PINS_GetAdcInterleaveVal(const PORT_Type * base,
                                         const uint32_t pinPortIdx,
                                         const uint32_t currentVal)
{
    uint32_t adcInterleaveVal = (uint32_t)PIN_ADC_INTERLEAVE_INVALID;
    /* calculate appropriate value to enable or disable in SIM_CHIPCTL[ADC_INTERLEAVE_EN] */
    if ((uint32_t)base == (uint32_t)PORTB)
    {
        switch (pinPortIdx)
        {
            case 0U:
                adcInterleaveVal = (uint32_t)PIN_ADC_INTERLEAVE_ENABLE0 | currentVal;
                break;
            case 1U:
                adcInterleaveVal = (uint32_t)PIN_ADC_INTERLEAVE_ENABLE1 | currentVal;
                break;
            case 13U:
                adcInterleaveVal = (uint32_t)PIN_ADC_INTERLEAVE_ENABLE2 | currentVal;
                break;
            case 14U:
                adcInterleaveVal = (uint32_t)PIN_ADC_INTERLEAVE_ENABLE3 | currentVal;
                break;
            case 15U:
                adcInterleaveVal = (uint32_t)PIN_ADC_INTERLEAVE_DISABLE0 & currentVal;
                break;
            case 16U:
                adcInterleaveVal = (uint32_t)PIN_ADC_INTERLEAVE_DISABLE1 & currentVal;
                break;
            default:
                /* invalid command */
                break;
        }
    }
    else if ((uint32_t)base == (uint32_t)PORTC)
    {
        switch (pinPortIdx)
        {
            case 0U:
                adcInterleaveVal = (uint32_t)PIN_ADC_INTERLEAVE_DISABLE2 & currentVal;
                break;
            case 1U:
                adcInterleaveVal = (uint32_t)PIN_ADC_INTERLEAVE_DISABLE3 & currentVal;
                break;
            default:
                /* invalid command */
                break;
        }
    }
    else
    {
        /* invalid command */
    }
    return adcInterleaveVal;
}

STATIC_AL  void PINS_GPIO_WritePin(GPIO_Type * const base,
                                      pins_channel_type_t pin,
                                      pins_level_type_t value)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    pins_channel_type_t pinsValues = (pins_channel_type_t)base->PDOR;
    pinsValues &= (pins_channel_type_t)(~((pins_channel_type_t)1U << pin));
    pinsValues |= (pins_channel_type_t)((pins_channel_type_t)value << pin);
    base->PDOR = GPIO_PDOR_PDO(pinsValues);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    pins_channel_type_t pinsValues = (pins_channel_type_t)base->PGPDO;
    pinsValues &= (pins_channel_type_t)(~((pins_channel_type_t)1U << (15U - pin)));
    pinsValues |= (pins_channel_type_t)((pins_channel_type_t)value << (15U - pin));
    base->PGPDO = pinsValues;
#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */
}


//-----------------------------------------------------------------------------
/// \brief  Port initialization function.
///
/// \descr   The function is using the user-defined configuration map from 
///          Port_Cfg.h. It is not using the configuration structure given
///          as parameter.
///          The function takes each pin from the list and initializes it 
///          accordingly.
///
/// \param   *ConfigPtr - configuration structure. Not used. 
///
/// \return  void
//-----------------------------------------------------------------------------
void Port_Init(const Port_ConfigType* ConfigPtr)
{
  uint32_t digitalFilters;
  uint32_t directions;
  uint32_t regValue;

  for(uint8 i = 0U; i < ConfigPtr->ucCountOfPorts; ++i)
  {
    const Port_PinSpecificCharacteristicsType cfg = (ConfigPtr->ptyPinSpecificCharacteristics)[i];

    PORT_Type* pCfgPortBase = cfg.portBaseIndex == 0U ? ((PORT_Type*) PORTA_BASE) :
                              cfg.portBaseIndex == 1U ? ((PORT_Type*) PORTB_BASE) :
                              cfg.portBaseIndex == 2U ? ((PORT_Type*) PORTC_BASE) :
                              cfg.portBaseIndex == 3U ? ((PORT_Type*) PORTD_BASE) :
                              cfg.portBaseIndex == 4U ? ((PORT_Type*) PORTE_BASE) :
                                                        ((PORT_Type*) PORTA_BASE);

    GPIO_Type* pCfgGpioBase = cfg.gpioBaseIndex == 0U ? ((GPIO_Type*) PTA_BASE) :
                              cfg.gpioBaseIndex == 1U ? ((GPIO_Type*) PTB_BASE) :
                              cfg.gpioBaseIndex == 2U ? ((GPIO_Type*) PTC_BASE) :
                              cfg.gpioBaseIndex == 3U ? ((GPIO_Type*) PTD_BASE) :
                              cfg.gpioBaseIndex == 4U ? ((GPIO_Type*) PTE_BASE) :
                                                        ((GPIO_Type*) PTA_BASE);

    regValue = pCfgPortBase->PCR[cfg.pinPortIdx];

    switch (cfg.pullConfig)
    {
      case (uint8)PORT_INTERNAL_PULL_NOT_ENABLED:
        regValue &= ~((uint32_t)PORT_PCR_PE_MASK);
        break;
      case (uint8)PORT_INTERNAL_PULL_DOWN_ENABLED:
        regValue &= ~((uint32_t)PORT_PCR_PS_MASK);
        regValue |= PORT_PCR_PE(1U);
        break;  
      case (uint8)PORT_INTERNAL_PULL_UP_ENABLED:
        regValue |= PORT_PCR_PE(1U);
        regValue |= PORT_PCR_PS(1U);
        break;
      default:
        /* invalid command */ 
        break;
    }

    regValue &= ~((uint32_t)PORT_PCR_PFE_MASK);
    regValue |= PORT_PCR_PFE(cfg.passiveFilter);

    regValue &= ~((uint32_t)PORT_PCR_DSE_MASK);
    regValue |= PORT_PCR_DSE(cfg.driveSelect);

    uint8 muxing = cfg.mux;
    if (muxing == (uint8)PORT_MUX_ADC_INTERLEAVE)
    {
        /* Get ADC Interleave from SIM and enable/disable desired bit */
        uint32_t chipCtlReg = (SIM->CHIPCTL & SIM_CHIPCTL_ADC_INTERLEAVE_EN_MASK) >> SIM_CHIPCTL_ADC_INTERLEAVE_EN_SHIFT;
        uint32_t interleaveVal = PINS_GetAdcInterleaveVal(pCfgPortBase, cfg.pinPortIdx, chipCtlReg);
        if (interleaveVal != (uint32_t)PIN_ADC_INTERLEAVE_INVALID)
        {
            SIM->CHIPCTL &= ~((uint32_t)SIM_CHIPCTL_ADC_INTERLEAVE_EN_MASK);
            SIM->CHIPCTL |= SIM_CHIPCTL_ADC_INTERLEAVE_EN(interleaveVal);
        }
        /* return real muxing for pin */
        muxing = (uint8)PORT_PIN_DISABLED;
    }

    regValue &= ~((uint32_t)PORT_PCR_MUX_MASK);
    regValue |= PORT_PCR_MUX(muxing);

    pCfgPortBase->PCR[cfg.pinPortIdx] = regValue;

    /* Read current digital filter of port */
    digitalFilters = (uint32_t)(pCfgPortBase->DFER);
    digitalFilters &= ~(1UL << (cfg.pinPortIdx));
    digitalFilters |= (((uint32_t)(cfg.digitalFilter)) << (cfg.pinPortIdx));

    /* Write to digital filter enable register */
    pCfgPortBase->DFER = digitalFilters;

    /* If gpioBase address not null setup the direction of pin */
    if ((uint8)PORT_MUX_AS_GPIO == cfg.mux)
    {
      /* Read current direction */
      directions = (uint32_t)(pCfgGpioBase->PDDR);
      switch (cfg.direction)
      {
        case (uint8)GPIO_INPUT_DIRECTION:
          directions &= ~(1UL << cfg.pinPortIdx);
          break;

        case (uint8)GPIO_OUTPUT_DIRECTION:
          directions |= (1UL << cfg.pinPortIdx);
          break;

        case (uint8)GPIO_UNSPECIFIED_DIRECTION:
          /* pass-through */
          default:
          /* nothing to configure */
          break;
      }

      /* Configure direction */
      pCfgGpioBase->PDDR = GPIO_PDDR_PDD(directions);

      /* Configure initial value for output */
      if(cfg.direction == (uint8)GPIO_OUTPUT_DIRECTION)
      {
        PINS_GPIO_WritePin(pCfgGpioBase, cfg.pinPortIdx, cfg.initValue);
      }
    }
  }
  // PRQA S 5310 1 // STPTH = 85 exceeds threshold 80
}


//-----------------------------------------------------------------------------
// \brief  Port_Read
//
// \descr  Function which reads the value of a specific pin of a port
//
// \param  portNb   port number
// \param  portNb   pin number
// \param  *result  the read value
//
// \return status code  E_NOT_OK: the pin could not be read
//                      E_OK    : the pin was read successfully
//-----------------------------------------------------------------------------

// PRQA S 1503 1 // not used at the moment
Std_ReturnType Port_Read(uint32 portNb, uint32 pinNb, uint8 *result)
{
  (void)portNb;
  (void)pinNb;
  (void)result;

  Std_ReturnType retVal = E_NOT_OK;
  
  return retVal;
}

//-----------------------------------------------------------------------------
// \brief  Port_Write
//
// \descr  Function which writes the given value for a specific pin of a port
//
// \param  portNb  port number
// \param  portNb  pin number
// \param  value   value to be written
//
// \return status code  E_NOT_OK: the pin could not be written
//                      E_OK    : the pin was written successfully
//-----------------------------------------------------------------------------

// PRQA S 1503 1 // not used at the moment
Std_ReturnType Port_Write(uint32 portNb, uint32 pinNb, uint8 value)
{
  (void) portNb;
  (void) pinNb;
  (void) value;
  Std_ReturnType retVal = E_NOT_OK;
  

  return retVal;
}
