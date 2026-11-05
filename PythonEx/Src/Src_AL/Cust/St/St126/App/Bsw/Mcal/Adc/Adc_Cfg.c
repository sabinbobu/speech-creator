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
/// \file  Adc_Cfg.c
///
/// \brief Project related ADC configuration
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
//
//-----------------------------------------------------------------------------

#include <Adc.h>
#include <UtilUtility.h>
#include <Std_Types.h>
#include <Cfg/Cfg.h>
#include <CddEft.h>

#if defined (CPU_S32K146)
#define SAMPLE_FULL
#elif defined (CPU_S32K142)
#define SAMPLE_ECO
#endif

#define ADC_CFG_CLOCK_FREQ_SOURCE     40000000u // LDM ADC pheripheral clock 40 MHz

// ADC0 eol calibration getter callback
STATIC_AL boolean Adc_EolCalibration_ADC0(uint32* pvStart);
// ADC1 eol calibration getter callback
STATIC_AL boolean Adc_EolCalibration_ADC1(uint32* pvStart);

// Adc Instances Configuration (ADC0 and ADC1)
STATIC_AL CONST_AL tsAdc_AdcInstanceCfg Adc_asAdcInstCfg[] =
{
  /*Instance,       Clk Divide,     Smpl pts          Resolution,         Clk Source,           Trigger type,       Pretrigger selector,        Trigger Selector,   Dma Request,          Reference,      Continous   Supply Mon,  Average,     Average Mode,                 Adc Clk Freq          EOL Calibration,    Calibration getter*/
  {   0u,       eADC_CLK_DIVIDE_1,    20u,      eADC_RESOLUTION_12BIT,  eADC_CLK_ALT_1,   eADC_TRIGGER_HARDWARE,  eADC_PRETRIGGER_SEL_PDB,    eADC_TRIGGER_SEL_PDB,     TRUE,     eADC_VOLTAGEREF_VREF,     FALSE,      FALSE,      FALSE,     eADC_AVERAGE_32,       ADC_CFG_CLOCK_FREQ_SOURCE,           TRUE,       Adc_EolCalibration_ADC0 },
  {   1u,       eADC_CLK_DIVIDE_1,    20u,      eADC_RESOLUTION_12BIT,  eADC_CLK_ALT_1,   eADC_TRIGGER_HARDWARE,  eADC_PRETRIGGER_SEL_PDB,    eADC_TRIGGER_SEL_PDB,     TRUE,     eADC_VOLTAGEREF_VREF,     FALSE,      FALSE,      FALSE,     eADC_AVERAGE_32,       ADC_CFG_CLOCK_FREQ_SOURCE,           TRUE,       Adc_EolCalibration_ADC1 }
};

#ifdef LDMO_A0_SAMPLE
#define ADC_NO_INPUTS_CH    21u
#elif defined (LDMO_B0_SAMPLE)
#ifdef SAMPLE_FULL
#define ADC_NO_INPUTS_CH    22u
#elif defined(SAMPLE_ECO)
#define ADC_NO_INPUTS_CH    16u
#endif
#endif

// Data source of ADC DMA transfer (all ADC channels data transfered in RAM)
STATIC_AL uint32 Adc_aulAdcChData[ADC_NO_INPUTS_CH];

// Adc Channels configuration related ADC inputs
// Maping has to be the same with IoHwAbUser channels defined order
STATIC_AL CONST_AL tsAdc_AdcInputCfg Adc_asAdcChMapCfg[] =
{
  /*Adc Input,   AdcInstance, Adc Channel,  Input,    Int Enable,     DMA RAM data source*/
#ifdef LDMO_A0_SAMPLE
  { eADC_PCB,         1u,         0u,     eAdcExtCh3,    FALSE,      &Adc_aulAdcChData[11] },
  { eADC_EXT_1,       0u,         0u,     eAdcExtCh11,   FALSE,      &Adc_aulAdcChData[0]  },
  { eADC_EXT_2,       0u,         1u,     eAdcExtCh9,    FALSE,      &Adc_aulAdcChData[1]  },
  { eADC_EXT_3,       0u,         2u,     eAdcExtCh8,    FALSE,      &Adc_aulAdcChData[2]  },
  { eADC_EXT_4,       0u,         3u,     eAdcExtCh15,   FALSE,      &Adc_aulAdcChData[3]  },
  { eADC_EXT_5,       0u,         4u,     eAdcExtCh14,   FALSE,      &Adc_aulAdcChData[4]  },
  { eADC_EXT_6,       0u,         5u,     eAdcExtCh13,   FALSE,      &Adc_aulAdcChData[5]  },
  { eADC_EXT_7,       0u,         6u,     eAdcExtCh12,   FALSE,      &Adc_aulAdcChData[6]  },
  { eADC_EXT_8,       0u,         7u,     eAdcExtCh2,    FALSE,      &Adc_aulAdcChData[7]  },
  { eADC_EXT_11,      0u,         8u,     eAdcExtCh10,   FALSE,      &Adc_aulAdcChData[8]  },
  { eADC_EXT_12,      1u,         1u,     eAdcExtCh14,   FALSE,      &Adc_aulAdcChData[12] },
  { eADC_EXT_13,      1u,         2u,     eAdcExtCh9,    FALSE,      &Adc_aulAdcChData[13] },
  { eADC_EXT_14,      1u,         3u,     eAdcExtCh13,   FALSE,      &Adc_aulAdcChData[14] },
  { eADC_VBAT,        1u,         4u,     eAdcExtCh6,    FALSE,      &Adc_aulAdcChData[15] },
  { eADC_ST_SENS,     1u,         5u,     eAdcExtCh7,    FALSE,      &Adc_aulAdcChData[16] },
  { eADC_LR,          1u,         6u,     eAdcExtCh2,    FALSE,      &Adc_aulAdcChData[17] },
  { eADC_VCCX1,       1u,         7u,     eAdcExtCh1,    FALSE,      &Adc_aulAdcChData[18] },
  { eADC_VCCX2,       1u,         8u,     eAdcExtCh10,   FALSE,      &Adc_aulAdcChData[19] },
  { eADC_SENSE_1_2,   0u,         9u,     eAdcExtCh1,    FALSE,      &Adc_aulAdcChData[9]  },
  { eADC_SENSE_3,     1u,         9u,     eAdcExtCh15,   FALSE,      &Adc_aulAdcChData[20] },
  { eADC_OUT_FCT,     0u,        10u,     eAdcExtCh0,    FALSE,      &Adc_aulAdcChData[10] }
#elif defined(LDMO_B0_SAMPLE)
#ifdef SAMPLE_FULL
  { eADC_PCB,         1u,         0u,     eAdcExtCh2,    FALSE,      &Adc_aulAdcChData[12] },
  { eADC_EXT_1,       0u,         0u,     eAdcExtCh11,   FALSE,      &Adc_aulAdcChData[0]  },
  { eADC_EXT_2,       0u,         1u,     eAdcExtCh9,    FALSE,      &Adc_aulAdcChData[1]  },
  { eADC_EXT_3,       0u,         2u,     eAdcExtCh8,    FALSE,      &Adc_aulAdcChData[2]  },
  { eADC_EXT_4,       0u,         3u,     eAdcExtCh15,   FALSE,      &Adc_aulAdcChData[3]  },
  { eADC_EXT_5,       0u,         4u,     eAdcExtCh14,   FALSE,      &Adc_aulAdcChData[4]  },
  { eADC_EXT_6,       0u,         5u,     eAdcExtCh13,   FALSE,      &Adc_aulAdcChData[5]  },
  { eADC_EXT_7,       0u,         6u,     eAdcExtCh7,    FALSE,      &Adc_aulAdcChData[6]  },
  { eADC_EXT_8,       0u,         7u,     eAdcExtCh2,    FALSE,      &Adc_aulAdcChData[7]  },
  { eADC_EXT_9,       1u,         1u,     eAdcExtCh0,    FALSE,      &Adc_aulAdcChData[13] },
  { eADC_EXT_10,      1u,         2u,     eAdcExtCh8,    FALSE,      &Adc_aulAdcChData[14] },
  { eADC_EXT_11,      0u,         8u,     eAdcExtCh10,   FALSE,      &Adc_aulAdcChData[8]  },
  { eADC_EXT_12,      1u,         3u,     eAdcExtCh14,   FALSE,      &Adc_aulAdcChData[15] },
  { eADC_EXT_13,      1u,         4u,     eAdcExtCh9,    FALSE,      &Adc_aulAdcChData[16] },
  { eADC_EXT_14,      1u,         5u,     eAdcExtCh13,   FALSE,      &Adc_aulAdcChData[17] },
  { eADC_VBAT,        1u,         6u,     eAdcExtCh6,    FALSE,      &Adc_aulAdcChData[18] },
  { eADC_LR,          0u,         9u,     eAdcExtCh3,    FALSE,      &Adc_aulAdcChData[9]  },
  { eADC_VCCX1,       1u,         7u,     eAdcExtCh1,    FALSE,      &Adc_aulAdcChData[19] },
  { eADC_VCCX2,       1u,         8u,     eAdcExtCh10,   FALSE,      &Adc_aulAdcChData[20] },
  { eADC_SENSE_1_2,   0u,        10u,     eAdcExtCh1,    FALSE,      &Adc_aulAdcChData[10] },
  { eADC_SENSE_3,     1u,         9u,     eAdcExtCh15,   FALSE,      &Adc_aulAdcChData[21] },
  { eADC_OUT_FCT,     0u,        11u,     eAdcExtCh0,    FALSE,      &Adc_aulAdcChData[11] }
#elif defined(SAMPLE_ECO)
  { eADC_PCB,         0u,         0u,     eAdcExtCh11,   FALSE,      &Adc_aulAdcChData[0]  },
  { eADC_EXT_1,       0u,         1u,     eAdcExtCh3,    FALSE,      &Adc_aulAdcChData[1]  },
  { eADC_EXT_2,       0u,         2u,     eAdcExtCh2,    FALSE,      &Adc_aulAdcChData[2]  },
  { eADC_EXT_3,       1u,         0u,     eAdcExtCh8,    FALSE,      &Adc_aulAdcChData[11] },
  { eADC_EXT_4,       1u,         1u,     eAdcExtCh6,    FALSE,      &Adc_aulAdcChData[12] },
  { eADC_EXT_5,       1u,         2u,     eAdcExtCh2,    FALSE,      &Adc_aulAdcChData[13] },
  { eADC_EXT_6,       0u,         3u,     eAdcExtCh13,   FALSE,      &Adc_aulAdcChData[3]  },
  { eADC_EXT_7,       0u,         4u,     eAdcExtCh14,   FALSE,      &Adc_aulAdcChData[4]  },
  { eADC_EXT_8,       0u,         5u,     eAdcExtCh15,   FALSE,      &Adc_aulAdcChData[5]  },
  { eADC_EXT_9,       0u,         6u,     eAdcExtCh8,    FALSE,      &Adc_aulAdcChData[6]  },
  { eADC_EXT_10,      0u,         7u,     eAdcExtCh10,   FALSE,      &Adc_aulAdcChData[7]  },
  { eADC_OUT_FCT,     1u,         3u,     eAdcExtCh1,    FALSE,      &Adc_aulAdcChData[14] },
  { eADC_VBAT,        1u,         4u,     eAdcExtCh0,    FALSE,      &Adc_aulAdcChData[15] },
  { eADC_LR,          0u,         8u,     eAdcExtCh9,    FALSE,      &Adc_aulAdcChData[8]  },
  { eADC_VCCX1,       0u,         9u,     eAdcExtCh7,    FALSE,      &Adc_aulAdcChData[9]  },
  { eADC_SENSE_1_2,   0u,        10u,     eAdcExtCh1,    FALSE,      &Adc_aulAdcChData[10] }
#endif
#endif
};

// Extern data configuration passed to Adc Init function
const tsAdc_CfgData Adc_sAdcCfgData =
{
  /*     Config array,            count*/ 
  { &Adc_asAdcInstCfg[0],  countof(Adc_asAdcInstCfg)  },
  { &Adc_asAdcChMapCfg[0], countof(Adc_asAdcChMapCfg) },
  { &Adc_aulAdcChData[0],  countof(Adc_aulAdcChData)  }
};

//-----------------------------------------------------------------------------
/// \brief Adc_EolCalibration_ADC0
///
/// \descr ADC0 eol calibration getter callback
///
/// \param  pvStart - ADC0 eol parameters start address
///
/// \return boolean - EOL availability status
//-----------------------------------------------------------------------------
STATIC_AL boolean Adc_EolCalibration_ADC0(uint32* pvStart)
{
  boolean boEolValid = FALSE;

  // EOL valid
  if (EFT_DATA_VALID_STATUS != FALSE)
  {
    // Return true
    boEolValid = TRUE;
    // Get EOL start address for ADC0 eol parameters
    // 2 Bytes offset
    // PRQA S 306, 310, 311 1 // program architecture and readability - Casting to different object pointer type wanted and documented
    *pvStart = (uint32)((uint8*)&EFT_ADC_CALIBRATION_BASE(0u) + 2u);
  }
  else
  {
    // keep null ptr and return false
  }

  return boEolValid;
}

//-----------------------------------------------------------------------------
/// \brief Adc_EolCalibration_ADC1
///
/// \descr ADC1 eol calibration getter callback
///
/// \param  pvStart - ADC1 eol parameters start address
///
/// \return boolean - EOL availability status
//-----------------------------------------------------------------------------
STATIC_AL boolean Adc_EolCalibration_ADC1(uint32* pvStart)
{
  boolean boEolValid = FALSE;

  // EOL valid
  if (EFT_DATA_VALID_STATUS != FALSE)
  {
    // Return true
    boEolValid = TRUE;
    // Get EOL start address for ADC1 eol parameters
    // 2 Bytes offset
    // PRQA S 306, 310, 311 1 // program architecture and readability - Casting to different object pointer type wanted and documented
    *pvStart = (uint32)((uint8*)&EFT_ADC_CALIBRATION_BASE(1u) + 2u);
  }
  else
  {
    // keep null ptr and return false
  }

  return boEolValid;
}

// EOF
