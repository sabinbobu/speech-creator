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
/// \file   CddEft.c
///
/// \brief  Default EFT data for ECU initial test operation
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <AL_Helper.h>
#include <CddEft.h>
#include <RteCommonTypes.h>
#include <Crc.h>


//=============================================================================
//  Static variable declarations
//=============================================================================
STATIC_AL boolean CddEft_CrcValid = FALSE;
STATIC_AL boolean CddEft_boCrcCalculated = FALSE;

#define REV(x) ( (((x) & 0xff000000U)>>24U) | ((( (x) & 0x00ff0000U)<<8U)>>16U) | ((((x) & 0x0000ff00U)>>8U)<<16U) | (( (x) & 0x000000ffU) << 24U) ) //invert 32byte hex

//=============================================================================
//  Const declarations
//=============================================================================
#undef USE_EFT_DEFAULT_DATA
#if defined USE_EFT_DEFAULT_DATA
CONST_AL tEftData EftData =
{
// ------------------------------------------------------------------
// Eft_Crc
// ------------------------------------------------------------------
  {
    { 1234u },                // Eft_Crc32
    { 1u, 255u, 255u, 255u }  // Eft_DocVers
  },
// ------------------------------------------------------------------


// ------------------------------------------------------------------
// Eft_Calib
// ------------------------------------------------------------------
  { // union
  {
    { { 'C', 'A', 'L', 'I' } },      // Eft_Calib_Text
    { 255u, 255u, 255u, 255u },      // Eft_Calib_Type

    CDDTPS92520_Eft_Calib_Default,   // TPS92520 calibration
    //QAC(Prio7) Msg: 2850(Constant: Implicit conversion to a signed integer type of insufficient size.) Depth: 0 Ref: MISRA C:2012 Rule-10.3
    CDDNCV78702_Eft_Calib_Default    // NCV78702 calibration
  }
  },


// ------------------------------------------------------------------
// Eft_HwDesc
// ------------------------------------------------------------------
  { // union
  {
    { { 'H', 'W', 'I', 'D' } },  // Eft_HwDesc_Text
    { 255u, 255u, 255u, 255u },  // Eft_HwDesc_Type
  }
  },


// ------------------------------------------------------------------
// Eft_EcuVarCfg
// ------------------------------------------------------------------
  { // union
  {
    { { 'V', 'C', 'F', 'G' } },                         // Eft_EcuVarCfg_Text
    { 255u, 255u, 1u, 255u },                               // Eft_EcuVarCfg_Type
    CDDTPS92520_Eft_EcuVarCfg_Default,                  // TPS92520 configuration
    CDDNCV78702_Eft_EcuVarCfg_Default,                  // NCV78702 configuration
    { 0x3FFFu, 0xFFFFu },                               // NTC
    { 216u, 9661u },                                    // ADC IN
    { { 2u, 255u }, { 0u, 255u } },                     // STP
    { 0u, 255u },                                       // DC OUT
    { 3u, 255u },                                       // EXT SUPPLY 2
    { 0u, 255u },                                       // EXT SUPPLY 3
    { 0u, 255u },                                       // SWITCH ARRAY
    { { 1u, 255u }, { 2u, 255u },                       // HSS
      { 3u, 255u }, { 0u, 255u } },                     // HSS
    { 1u, 255u },                                       // CAN2
    { 0u, 255u },                                       // CAN3
    { 0u, 255u },                                       // LIN
    { 2u, 255u },                                       // GPIO SBC
    { 0u, 255u },                                       // WK SENSE
    { { 1u, 255u }, { 1u, 255u },                       // IN
      { 3u, 255u }, { 1u, 255u } },                     // IN
    {
      5000u ,                                           // ADC FACTOR PCB TEMP
    { 6273u, 6273u, 6273u, 6273u, 6273u, 6273u, 6273u,  // ADC FACTOR NTC
      6273u, 6273u, 6273u, 6273u, 6273u, 6273u, 6273u },// ADC FACTOR NTC
      24643u,                                           // ADC FACTOR Vbat
      24643u,                                           // ADC FACTOR LrDetect
      5000u,                                            // ADC FACTOR HssSense_1_2
      5000u,                                            // ADC FACTOR HssSense_3
      0u,                                               // ADC FACTOR PosSensor
    { 6273u,  6273u,  0u },                             // ADC FACTOR Vccx
    { 0u, 0u, 0u, 0u },                                 // ADC FACTOR In
      24643u,                                           // ADC FACTOR OutFct
      0u,                                               // ADC FACTOR Vboost
      24643u                                            // ADC FACTOR DcOut
    }
  }
  }
};
#else
#ifndef UNIT_TEST
CONST_AL tEftData EftData __attribute__((section(".ARM.__at_0x0000A000")));
#else
extern uint8 Eft_ucTestData[];
tEftData EftData;
#endif
#endif

//-----------------------------------------------------------------------------
/// \brief  CddEft initialization
///
/// \descr  Check EFT data CRC
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CddEft_Init(void)
{
  // Open diagnostic window (in normal init without diag-mux-on received over the CAN, the diagnostic will not work)
  Rte_Call_DemPrj_Set_DiagWindow(TRUE);

  //apply the CRC32 on data and check if they are valid
  if (CddEft_DataValid() == TRUE)
  {
	  Rte_Call_DemPrj_ReportErrorStatus((uint16)CRC_PAV_DEFECT, DEM_EVENT_STATUS_PASSED);
  }
  else
  {
	  // set DTC for error
	  Rte_Call_DemPrj_ReportErrorStatus((uint16)CRC_PAV_DEFECT, DEM_EVENT_STATUS_FAILED);
  }

  // Close diagnostic window (in normal init without diag-mux-on received over the CAN, the diagnostic will not work)
  Rte_Call_DemPrj_Set_DiagWindow(FALSE);
}

//-----------------------------------------------------------------------------
/// \brief  Check for valid EFT data
///
/// \descr  Get EFT data CRC status
///
/// \param  none
///
/// \return boolean TRUE if valid
//-----------------------------------------------------------------------------
boolean CddEft_DataValid(void)
{
  if (CddEft_boCrcCalculated == FALSE)
  {
	  //store the Crc32 value from Flash memory
      volatile const uint32* pulCrcAddress = (volatile const uint32*)&EftData.Eft_Crc.Crc32.ulCrc;
	  uint32 ulStoreCrc =  *pulCrcAddress;

	  //Start addres of the CRC32 from EftData
    
#ifndef UNIT_TEST
      //PRQA S 306 1 // direct memory access
      uint8* startAddres = (uint8*)0xA004;
#else
      uint8* startAddres = ( uint8*)pulCrcAddress + 4u;

#endif

	  //Apply CRC32 calc
	  uint32 ulCrc32_result = Crc_CalculateCRC32_4C11DB7(startAddres, 0x2FCU, EFT_CRC_START);
	  //Shift data for CRC calculation (workaround for wrong EOL CRC)
     uint32 ulCrc32_resultShift = (ulCrc32_result & 0xFFFF00FFU) | ((ulCrc32_result & 0x000FF000U) >> 4U);
	  //Invert Crc32 from Eft
    uint32 ulCrc32_Store_Inv = REV(ulStoreCrc);
    //Invert the CRC value calculated
    uint32 ulCrc32_Result_Inv = REV(ulCrc32_result);
    //Shift data for CRC calculation (workaround for wrong EOL CRC)
    uint32 ulCrc32_Result_Inv_Shift = (ulCrc32_Result_Inv & 0xFFFF00FFU) | ((ulCrc32_Result_Inv & 0x000FF000U) >> 4U);
    //Undo the last value of CRC before applying the specified workarround
    uint32 ulCrc32_Result_Shift = REV(ulCrc32_Result_Inv_Shift);

	  //Check if CRC is valid - all cases including workarround for little and big endianeess
	  if ((ulCrc32_result != ulCrc32_Store_Inv) && (ulCrc32_resultShift != ulCrc32_Store_Inv) && (ulCrc32_result != ulStoreCrc) && (ulCrc32_Result_Shift != ulStoreCrc))
	  {
      CddEft_CrcValid = FALSE;
	  }
	  else
	  {
      CddEft_CrcValid = TRUE;
	  }

    CddEft_boCrcCalculated = TRUE;
  }

	return CddEft_CrcValid;
}

