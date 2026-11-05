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
/// \file  Bmg.c
///
/// \brief  Functions for AL- specific initialization:
///             - mounting side LEFT /RIGHT
///             - EFT entry condition --> Normal Mode or "WaitForRAMAppl"
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Cosmin Cojocaru (f11501c)
///         mailTo:constantin-cosmin.cojocaru(at)marelli.com
//-----------------------------------------------------------------------------

#include <Swc/Bmg/Bmg.h>

#ifdef BMG_DETECT_VBAT_LEVEL
  static uint8 Bmg_VbatLevelCounter                     = 0U;
#endif

#ifdef BMG_DETECT_MOUNTING_SIDE
  static uint8 Bmg_MountingSideLeftCounter              = 0U;
  static uint8 Bmg_MountingSideRightCounter             = 0U;
  static uint8 Bmg_MountingSideUnknown                  = 0U;
#endif

#ifdef BMG_DETECT_ENTRY_CONDITION
  static uint8 Bmg_WaitForRAMApplCounter                = 0U;
#endif

static TIMER Bmg_SampeRateTimer;

//function prototypes
#ifdef BMG_DETECT_VBAT_LEVEL
  static void Bmg_CheckVbatLevel(uint16 adcRawVal);
#endif

#ifdef BMG_DETECT_ENTRY_CONDITION
  static void Bmg_CheckWaitForRAMAppl(uint16 adcRawVal1, uint16 adcRawVal2, uint16 adcRawVal3);

  #ifndef BMG_IS_ENTRY_COND_VAL1 
    #error BMG_IS_ENTRY_COND_VAL1 must be set in BmgCgf.h
  #endif

  #ifndef BMG_IS_ENTRY_COND_VAL2 
    #define BMG_IS_ENTRY_COND_VAL2(x)   (1U) 
  #endif

  #ifndef BMG_IS_ENTRY_COND_VAL3 
    #define BMG_IS_ENTRY_COND_VAL3(x)   (1U) 
  #endif

#endif

#ifdef BMG_DETECT_MOUNTING_SIDE
  static void Bmg_CheckMountingSide(uint16 adcRawVal, uint16 adcRawValKl30);
#endif

#ifdef BMG_DETECT_HW_ID
  static uint8  au8_HwIDCounter[BMG_HW_ID_ITEMS];
  static uint16 au16_HwIDcondition[BMG_HW_ID_ITEMS] = BMG_HW_ID_CONDITIONS;

  static void Bmg_CheckHwID(uint16 adcRawVal);
#endif

// ---------------------------------------------------------------------------
void Bmg_BootStatus_detection(void)
{
  uint8 u8_Index;
  #ifdef BMG_DETECT_MOUNTING_SIDE
    uint16 u16_RawMoutingSide = 0U;
    uint16 u16_RawVbatLevel = 0U;
  #endif

  #ifdef BMG_DETECT_ENTRY_CONDITION
    uint16 u16_RawEntryCondVal1 = 0U;
    uint16 u16_RawEntryCondVal2 = 0U;
    uint16 u16_RawEntryCondVal3 = 0U;
  #endif

  #ifdef BMG_DETECT_HW_ID
    uint16 u16_RawHwID = 0U;
  #endif

  // reset the used counters to enable reusage of the fct
  #ifdef BMG_DETECT_VBAT_LEVEL
    Bmg_VbatLevelCounter = 0U;
  #endif

  #ifdef BMG_DETECT_MOUNTING_SIDE
    Bmg_MountingSideLeftCounter = 0U;
    Bmg_MountingSideRightCounter = 0U;
    Bmg_MountingSideUnknown      = 0U;
  #endif 

  #ifdef BMG_DETECT_ENTRY_CONDITION
    Bmg_WaitForRAMApplCounter = 0U; 
  #endif

  #ifdef BMG_DETECT_HW_ID
    for( u8_Index = (uint8)0; u8_Index < BMG_HW_ID_ITEMS; u8_Index++ )
    {
      au8_HwIDCounter[u8_Index] = 0U;
    }
  #endif

  for( u8_Index = (uint8)0; u8_Index < BMG_NR_SAMPES; u8_Index++ )
  {
    //set sample rate time
    Bmg_SampeRateTimer = TimerStart( BMG_SAMPLE_RATE );

    //Read all required ADC channels
    #ifdef BMG_DETECT_VBAT_LEVEL
      Adc_ReadSingleHwPin_ForUnInitializedAdc(BMG_VBAT_PIN, BMG_VBAT_ADC, &u16_RawVbatLevel, 1U);
    #endif

    #ifdef BMG_DETECT_MOUNTING_SIDE
      Adc_ReadSingleHwPin_ForUnInitializedAdc(BMG_MOUNTING_SIDE_PIN, BMG_MOUNTING_SIDE_ADC, &u16_RawMoutingSide, 1U);
    #endif

    #ifdef BMG_DETECT_ENTRY_CONDITION
      #ifdef BMG_ENTRY_COND_ADC_VAL1
        Adc_ReadSingleHwPin_ForUnInitializedAdc(BMG_ENTRY_COND_PIN_VAL1, BMG_ENTRY_COND_ADC_VAL1, &u16_RawEntryCondVal1, 1U);
      #else
         #error BMG_ENTRY_COND_ADC_VAL1 must be set in BmgCgf.h
      #endif

      #ifdef BMG_ENTRY_COND_ADC_VAL2
        Adc_ReadSingleHwPin_ForUnInitializedAdc(BMG_ENTRY_COND_PIN_VAL2, BMG_ENTRY_COND_ADC_VAL2, &u16_RawEntryCondVal2, 1U);
      #endif

      #ifdef BMG_ENTRY_COND_ADC_VAL3
        Adc_ReadSingleHwPin_ForUnInitializedAdc(BMG_ENTRY_COND_PIN_VAL3, BMG_ENTRY_COND_ADC_VAL3, &u16_RawEntryCondVal3, 1U);
      #endif
    #endif

    #ifdef BMG_DETECT_HW_ID
      Adc_ReadSingleHwPin_ForUnInitializedAdc(BMG_HW_ID_PIN_VAL, BMG_HW_ID_ADC_VAL, &u16_RawEntryCondVal3, 1U);
    #endif

    #ifdef BMG_TEST_OVERWRITE_ADC_VALUE
      u16_RawMoutingSide = BMG_TEST_OVERWRITE_ADC_VALUE;
    #endif //BMG_TEST_OVERWRITE_ADC_VALUE

    //check results
    #ifdef BMG_DETECT_VBAT_LEVEL
      Bmg_CheckVbatLevel(u16_RawVbatLevel);
    #endif
    #ifdef BMG_DETECT_MOUNTING_SIDE
      Bmg_CheckMountingSide(u16_RawMoutingSide, u16_RawVbatLevel);
    #endif

    #ifdef BMG_DETECT_ENTRY_CONDITION
      Bmg_CheckWaitForRAMAppl(u16_RawEntryCondVal1, u16_RawEntryCondVal2, u16_RawEntryCondVal3);
    #endif

    #ifdef BMG_DETECT_HW_ID
      Bmg_CheckHwID(u16_RawHwID);
    #endif

    //wait for sample rate timing   
    while ( TimerTimeout( Bmg_SampeRateTimer ) == 0u ) {;}
  }
}

#ifdef BMG_DETECT_VBAT_LEVEL

  // ---------------------------------------------------------------------------
  static void Bmg_CheckVbatLevel(uint16 adcRawVal)
  {
    //check if VBAT is in range
    if (BMG_IS_VBAT_INSIDE(adcRawVal))
    {
      Bmg_VbatLevelCounter++;
    }
  }

  // ---------------------------------------------------------------------------
  boolean Bmg_BootStatus_isVbatValid(void)
  {
    //if most of the samples match the condition returns true
    return ( (Bmg_VbatLevelCounter > BMG_MAJORITY_OF_COUNTS_CHECKS) ? TRUE : FALSE );
  }

#endif

#ifdef BMG_DETECT_MOUNTING_SIDE
  // ---------------------------------------------------------------------------
  static void Bmg_CheckMountingSide(uint16 adcRawVal, uint16 adcRawValKl30)
  {
    // if value under the detection threshold left side is detected 
    if( BMG_IS_MOUNTING_SIDE_LEFT(adcRawVal))
    {
      Bmg_MountingSideLeftCounter++;
    }
    else if(BMG_IS_MOUNTING_SIDE_RIGHT(adcRawVal))
    {
      Bmg_MountingSideRightCounter++;
    }
    else
    {
      Bmg_MountingSideUnknown++;
    }
    (void)adcRawValKl30; // parameter is unused, avoid any warnings
  }

  // ---------------------------------------------------------------------------
  boolean Bmg_BootStatus_isMountingSideLeft(void)
  {
    //if most of the samples match the condition returns true
    return ( (Bmg_MountingSideLeftCounter > BMG_MAJORITY_OF_COUNTS_CHECKS) ? TRUE : FALSE );
  }


  //---------------------------------------------------------------------------
    boolean Bmg_BootStatus_isMountingSideRight(void)
  {
    //if most of the samples match the condition returns true
    return ( (Bmg_MountingSideRightCounter > BMG_MAJORITY_OF_COUNTS_CHECKS) ? TRUE : FALSE );
  }
#endif

#ifdef BMG_DETECT_ENTRY_CONDITION
  // ---------------------------------------------------------------------------
  static void Bmg_CheckWaitForRAMAppl(uint16 adcRawVal1, uint16 adcRawVal2, uint16 adcRawVal3)
  {
    // all three defined condition must match to detect the entry condititon 
    if ( ( BMG_IS_ENTRY_COND_VAL1( adcRawVal1 ) )
      && ( BMG_IS_ENTRY_COND_VAL2( adcRawVal2 ) )
      && ( BMG_IS_ENTRY_COND_VAL3( adcRawVal3 ) ) )
    {
      Bmg_WaitForRAMApplCounter++;
    }
  }

  // ---------------------------------------------------------------------------
  boolean Bmg_BootStatus_waitForRAMAppl(void)
  {
    //if most of the samples match the condition returns true
    return ( (Bmg_WaitForRAMApplCounter > BMG_MAJORITY_OF_COUNTS_CHECKS) ? TRUE : FALSE );
  }
#endif

#ifdef BMG_DETECT_HW_ID
  static void Bmg_CheckHwID(uint16 adcRawVal)
  {
    uint8 u8_Index;

    for( u8_Index = (uint8)0; u8_Index < BMG_HW_ID_ITEMS; u8_Index++ )
    {
      if (adcRawVal <= au16_HwIDcondition[u8_Index])
      {
        au8_HwIDCounter[u8_Index] += 1U;
        break;
      }
      }
    }
  
  // ---------------------------------------------------------------------------
  uint8 Bmg_BootStatus_getHwID(void)
  {
    uint8 u8_MaxVal = BMG_MAJORITY_OF_COUNTS_CHECKS;
    uint8 u8_RetVal = BMG_HW_ID_ITEM_UNKNOWN;
    uint8 u8_Index;

    for( u8_Index = (uint8)0; u8_Index < BMG_HW_ID_ITEMS; u8_Index++ )
    {
      if (au8_HwIDCounter[u8_Index] > u8_MaxVal)
      {
        u8_MaxVal = au8_HwIDCounter[u8_Index];
        u8_RetVal = u8_Index;
      }
    }

    return u8_RetVal;
  }
#endif
// EOF
