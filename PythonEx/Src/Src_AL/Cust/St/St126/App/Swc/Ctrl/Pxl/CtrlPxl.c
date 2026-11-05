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
/// \file   CtrlPxl.c
///
/// \brief  Control Pixel:
///
/// \descr  This module control the LMM(or MLC) driver chips which provide
///         PWM values for all pixels mapped in coding parameters appling 
///         derating(Thermo) and calibrations(EEPROM).
///
/// \author Ionut Caba  ALRO-CJ (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "CtrlPxl.h"
#include "CtrlPxl_RteAccess.h"
#include "CtrlPxl_Types.h"
#include <AL_Helper.h>
#include "CtrlPxl_Data.h"
#include "CtrlPxl_Diag.h"
#include "CtrlPxl_DataInterfaces.h"
#include "CtrlPxl_MemHandling.h"
#include <UtilBase.h>

//=============================================================================
// function prototype
//=============================================================================
STATIC_AL void CtrlPxl_ProcessIntensities(uint16 *punMxBuff_Out);

//=============================================================================
// variables
//=============================================================================
STATIC_AL boolean CtrlPxl_boCodMap_OK = FALSE;
tsCtrlPxl_InternalHandling CtrlPxl_sInternalHandling;   //is used to keep the information regarding matrix module, coding mapping and eeprom

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_Init
///
/// \descr  init function for CtrlPxl module
///
/// \param  none
///
/// \return none
//-----------------------------------------------------------------------------
void CtrlPxl_Init(void)
{
  //handle coding data
  CONST_AL boolean boCodingValidity = CtrlPxl_CodingDataValidation();

  //check coding validation
  if (boCodingValidity != FALSE)
  {
    //initialize buffer where Lu will be mapped to Segment in case Lmm or SwNr are received with 0
    for (uint8_fast ucLmm = 0u; ucLmm < CTRLPXL_CFG_NR_OF_MATRIX_DRV; ucLmm++)
    {
      for (uint8_fast ucPxl = 0u; ucPxl < CTRLPXL_CFG_NR_OF_PXLs_STRING; ucPxl++)
      {
        CTRLPXL_SEGMENT_POSITION[ucLmm][ucPxl] = 0xFFu;
      }
    }

   CtrlPxl_boCodMap_OK |= CtrlPxl_PxlMap(CTRLPXL_LOGICAL_UNIT_MAP);
   CtrlPxl_boCodMap_OK |= CtrlPxl_Data_Matrix(CTRLPXL_SEGMENT_MAP, CTRLPXL_SEGMENT_POSITION);

  }

   // check CRC from NVM and start handling EEprom data (checking shall be done only at start-up)
   CtrlPxl_ReadAndCheckNvMMatrixData();

   //initialize diagnosis control commands
   CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.boDiagMatrixControlActive               = FALSE;
   CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromRead   = FALSE;
   CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite  = FALSE;

}

// ---------------------------------------------------------------------------
///  \func     CtrlPxl_Cycle0
///
///  \brief    cyclic function 
///
///  \param    void
///
///  \return   void
// ---------------------------------------------------------------------------
void CtrlPxl_Cycle0(void)
{
  uint16 aunPWMs[CTRLPXL_CFG_PXL_NUMBERS] = { 0x00u };
  //If is necessary, do some commands for MLC driver like:
  //-enable transmition/ be sure if the bucks power first the MLC driver and so on
  if (CtrlPxl_boCodMap_OK != FALSE)
  {
 
    //do processing for received intensities
    CtrlPxl_ProcessIntensities(aunPWMs);

    //check for Eeprom Data and follow the state machine
    CtrlPxl_ProcessMatrixEEPROM();

  }

  //check for errors before sending pwms
  CtrlPxl_Diag_ErrorDetected();

  //send pwm intensities to MLC devices
  CTRLPXL_RTE_SE_PWMs_MLC(aunPWMs)
}

// ---------------------------------------------------------------------------
///  \func     CtrlPxl_ProcessIntensities
///
///  \brief    this function remap all intensities  received via RTE based on 
///            coding mapping list and sends DEV frames
///
///  \param    *punMxBuff_Out
///
///  \return   void
// ---------------------------------------------------------------------------
STATIC_AL void CtrlPxl_ProcessIntensities(uint16 *punMxBuff_Out)
{
  uint8_fast ucLmm = 0U, ucPxl = 0U;

  //get intensities
  uint16 aunInputIntensities[CTRLPXL_CFG_NR_OF_LOGICAL_UNITS] = { 0x00u };

  //save the error corresponding to the logical unit
  STATIC_UT(tuCtrlPxl_bErr, aunErr_LogUnit[CTRLPXL_CFG_NR_OF_LOGICAL_UNITS],  { 0x00u });

  //store the segment PWM target in [%] and mtx pixel fault
  tsRte_ucActualPxlPWM    sActualPxlPWM   = { .aucActualPercMtxPWM = {0u} };
  tsRte_boMtxSegmentFault sPxlMtxFault    = { 0u };
  tuCtrlPxl_bErr          uMtxFaults;

  // output from cpm
  CTRLPXL_RTE_RE_GET_INTENSITIES_CPM(aunInputIntensities)

  if (punMxBuff_Out != NULL_PTR)
  {
    for (ucLmm = 0u; ucLmm < CTRLPXL_CFG_NR_OF_MATRIX_DRV; ucLmm++)
    {
      for (ucPxl = 0u; ucPxl < CTRLPXL_CFG_NR_OF_PXLs_STRING; ucPxl++)
      {
        uint8 ucTempLogUnitIdx = CTRLPXL_LOGICAL_UNIT_MAP[ucLmm][ucPxl];

        //scale intensities with the brightness value from eeprom
        punMxBuff_Out[ucLmm * CTRLPXL_CFG_NR_OF_PXLs_STRING + ucPxl] = (CTRLPXL_DO_SCALLING_FOR_MLC(aunInputIntensities[ucTempLogUnitIdx]) * CTRLPXL_NVM_BRIGHTNESS[ucLmm * CTRLPXL_CFG_NR_OF_PXLs_STRING + ucPxl])/ CTRL_PXL_BRIGHTNESS_FACTOR; // to matrix (10-bit)

        uMtxFaults = CtrlPxl_GetMtxFaults(ucLmm, ucPxl);

        // read matrix faults for the corresponding logical unit
        aunErr_LogUnit[ucTempLogUnitIdx].bErr.bLossComm     = uMtxFaults.bErr.bLossComm;
        aunErr_LogUnit[ucTempLogUnitIdx].bErr.bCoruptComm   = uMtxFaults.bErr.bCoruptComm;
        aunErr_LogUnit[ucTempLogUnitIdx].bErr.bEEPromErr    = uMtxFaults.bErr.bEEPromErr;
        aunErr_LogUnit[ucTempLogUnitIdx].bErr.bPxlFault     = uMtxFaults.bErr.bPxlFault;

        // Check if Instrumented Frames has been activated by Diagnostic Request
        if (NvmBlockInstrumentatedFrames != FALSE)
        {
          uint8 ucTempSegPos = CTRLPXL_SEGMENT_POSITION[ucLmm][ucPxl];

          //only for validation frames when active
          if (ucTempSegPos != 255U)
          {
            sActualPxlPWM.aucActualPercMtxPWM[ucTempSegPos] = (uint8)CTRLPXL_PERC_PWM(punMxBuff_Out[ucLmm * CTRLPXL_CFG_NR_OF_PXLs_STRING + ucPxl]);
            sPxlMtxFault.aboMtxSegmentFault[ucTempSegPos]   = (uMtxFaults.bErr.bPxlFault != 0U) ? TRUE : FALSE;
          }
        }
      }
    }
    
    CTRLPXL_RTE_SE_MATRIX_FAULT_BITERROR(aunErr_LogUnit);

    // Check if Instrumented Frames has been activated by Diagnostic Request
    if (NvmBlockInstrumentatedFrames != FALSE)
    {
      CTRLPXL_RTE_SE_PXL_VALID_FRM_PWM_PERCENTAGE(&sActualPxlPWM);
      CTRLPXL_RTE_SE_PXL_VALID_FRM_PXL_DEFECT(&sPxlMtxFault);
    }
  }
  //PRQA S 5336 1 // STMIF>4 because of "else if" list - Function is maintainable and well-structured
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_GetInternalHandling
///
/// \descr  get address of internal handling for eeprom operations from
///         CtrlPxl_MemHandling.h and also saves the internal remapping of coding data
///
/// \param  void 
///
/// \return tsCtrlPxl_InternalHandling *  stores the address of CtrlPxl_sInternalHandling
//-----------------------------------------------------------------------------
tsCtrlPxl_InternalHandling * CtrlPxl_GetInternalHandlingStruct(void)
{
  return &CtrlPxl_sInternalHandling;
}
