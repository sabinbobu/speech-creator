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
/// \file  CtrlLed.c
///
/// \brief core module for CtrlLed
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "CtrlLed_Rte.h"
#include <UtilMath.h>
#include "CtrlLed_Cfg.h"
#include "CtrlLed_Data.h"
#include "CtrlLed_Diag.h"
#include "Anima/Anima.h"
#include "Anima/Anima_RteAccess.h"

//=============================================================================
// defines
//=============================================================================
#define CTRLLED_MIN_LED_CURRENT           0U
#define CTRLLED_CHANNEL_OFF               0U
#define CTRLLED_MAX_INTENSITY             1000U //[0.1%]
#define CTRLLED_MAX_THERMO_POW_FACTOR     1000U //[0.1%]

#define CTRLLED_CYCLE_RUN                 FALSE
#define CTRLLED_INIT_RUN                  TRUE

#define CTRLLED_SCALING_65535             0xFFFFU
#define CTRLLED_SCALING_32768             0x8000U
#define CTRLLED_SCALING_1000              0x03E8U
#define CTRLLED_SCALING_10000             0x2710U
#define CTRLLED_SCALING_200               0x00C8U
#define CTRLLED_SCALING_100               0x0064U
#define CTRLLED_LININTERPOLSHIFT          4L
#define CTRLLED_POINTS_NR                 2

//scaling number (from x->y)
#define CTRLLED_SCALING_X_TO_Y_VALUE(x, y, val) ((val) == 0U) ? 0U : (uint16)( ( (uint32)((uint32)(y) * (uint32)(val))   ) / (uint32)(x))

//=============================================================================
// variables
//=============================================================================
STATIC_AL tsCtrlled_CodingData        CtrlLed_sCodingData;
STATIC_AL boolean                     CtrlLed_boCodMap_OK = FALSE;
STATIC_AL tsCtrlled_InternalHandlings CtrlLed_sInternalHandling;

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
STATIC_AL uint8                       CtrlLed_ucCntFbit = 0U;
#endif

//=============================================================================
// function prototypes
//=============================================================================
STATIC_AL void   CtrlLed_Buck_Handling(void);
STATIC_AL void   CtrlLed_FindBuckId(uint8_fast ucIdx, uint16 *punInput, uint8 *pucBuckNumber, uint8 *pucBuckId);
STATIC_AL uint16 CtrlLed_CalcRamp  (CONST_AL uint8_fast ucIdx, CONST_AL uint16 unTgtIntensity, CONST_AL uint16 unTgtRampMs);
STATIC_AL uint16  CtrlLed_GammaCurve(uint16 unIntensity, CONST_AL uint16 *punGammaY);
STATIC_AL uint16  CtrlLed_DoRampInterpolation(uint32 ulCurrentTime, uint16 unStartPoint_Ms, uint16 unTgtPoint_Ms, uint16 unStartPoint_Int, uint16 unTgtPoint_Int);
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
STATIC_AL void CtrlLed_Matrix_Handling(void);
STATIC_AL void CtrlLed_CheckLight(uint8_fast ucIdx, uint8 ucIll, uint8 ucLmmPxl, uint16 *punDutyInt);
STATIC_AL uint16 CtrlLed_Handle_MatrixCh(CONST_AL uint8_fast ucIdxIl, uint16 unTgtInt);
STATIC_AL teCtrlLed_MatrixVoltCnd CtrlLed_MatrixVoltCond(uint8 ucVoltRange);
#endif
STATIC_AL uint8  CtrlLed_CountSetBucks(uint16 unVal);
STATIC_AL void   CtrlLed_GetBuckId(uint16 unVal, uint8 unMaxBuck, uint8* pucData);
STATIC_AL uint16 CtrlLed_Handle_NonMatrixCh(uint8_fast ucIdx, uint8_fast ucIdxIl, uint16 unTgtInt, uint16 unTgtRamp);
STATIC_AL uint16 CtrlLed_DutyCalculation(CONST_AL uint8_fast ucIdx, CONST_AL uint8_fast ucIdxIl);
STATIC_AL uint16 CtrlLed_CurrentCalculation(CONST_AL uint8_fast ucIdx);
STATIC_AL uint16 CtrlLed_CalculateGamma(uint16 unIntensity, uint8 ucIll);
//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  init function for CtrlLed
///
/// \descr  this function is called once at init
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3408 1 // architecture design
void CtrlLed_Init(void)
{
  uint8 ucBuckNo = 0u, ucBuckId[CTRLLED_CFG_MAX_BUCK_DRV];
  uint16 *punData = NULL_PTR;
  tsRte_TgtLedSig0Arr sTgtLedSig0Arr = { 0 };
  uint8_fast ucRow = 0U, ucIdx = 0u, ucIdxIl = 0U;
  
  uint16 unHss3Duty = 0U;

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  CtrlLed_sInternalHandling.ucMatrixRowLightBitPrv = 0U;
#endif

  //handle coding data
  CONST_AL boolean boCodingValidity = CtrlLed_CodingDataValidation();
  //checking validity of coding
  if(boCodingValidity != FALSE)
  { 
    Anima_Init();
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
    //reset actual row error status
    for (ucRow = 0u; ucRow < CTRLLED_MAX_MTX_COL_SEL; ucRow++)
    {
      CtrlLed_sInternalHandling.sRowMtxErr[ucRow].ucIlluminantAssigned = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
    }
#endif
    for (ucIdx = 0u; ucIdx < CTRLLED_CFG_LED_CHANNELS_NR; ucIdx++)
    {
      //fill out driver type with unknown values
      CtrlLed_sCodingData.aucChannelType[ucIdx] = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
    }

    for (ucIdx = 0u; ucIdx < CTRLLED_CFG_NO_ILLUMINANTS; ucIdx++)
    {
      //fill out driver type with unknown values
      CtrlLed_sCodingData.ucLogicalUnitIl[ucIdx] = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
    }
    //get coding ch map
    CtrlLed_boCodMap_OK = CtrlLed_CodMap(&CtrlLed_sCodingData);

    punData = &CtrlLed_sCodingData.aunChannelIlluminant[0];

    for (ucIdxIl = 0U; ucIdxIl < CTRLLED_CFG_NO_ILLUMINANTS; ucIdxIl++)
    {
      CtrlLed_RteAccess_Set_IlluminantsStatus(ucIdxIl, 0U, FALSE, CTRLLED_CFG_UNKNOWN_UINT8_VALUE);

      if ((punData[ucIdxIl] != 0U) && (punData[ucIdxIl] <= CTRLLED_CFG_BIT_MAX_CHANNELS))
      {
        CtrlLed_FindBuckId(ucIdxIl, punData, &ucBuckNo, ucBuckId);

        for (ucIdx = 0u; ucIdx < ucBuckNo; ucIdx++)
        {
          if (ucBuckId[ucIdx] == CTRLLED_CFG_BASIC_LED_CH)
          {
            unHss3Duty = 0U;
            //Write rte
            CTRLLED_RTE_SE_TGT_HSS3_PWM(unHss3Duty)
          }
          else
          {
            //get duty
            sTgtLedSig0Arr[ucBuckId[ucIdx]].unDutyCycle = 0u;
            //get current
            sTgtLedSig0Arr[ucBuckId[ucIdx]].unCurrent = 0u;
          }
        }
      }
    }
  }
  //write current and duty via RTE
  CTRLLED_RTE_SE_TGT_LED_SIG(&sTgtLedSig0Arr)
} // PRQA S 5324,5336 1 // architecture and readability

//-----------------------------------------------------------------------------
/// \brief  cycle function for CtrlLed
///
/// \descr  cyclic function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3408 1 // architecture design
void CtrlLed_Cycle0(void)
{
  static uint8 ucCycle5 = 0u;
  //check coding map
  if (CtrlLed_boCodMap_OK != FALSE)
  {
    if ((ucCycle5 % 2u) != 0u)
    {
      Anima_Cycle10();
    }
    else if ((ucCycle5 % 4u) == 0u)
    {
      //pixels handling
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
      CtrlLed_Matrix_Handling();
#endif
      //buck handling
      CtrlLed_Buck_Handling();
    }
    else
    {
      //do nothing
    }
  }
  ucCycle5++;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Buck_Handling
///
/// \descr this function remap illuminants to led channels, apply duty, ramp and gamma
///
/// \param  void
///
/// \return void
//----------------------------------------------------------------------------- 
STATIC_AL void CtrlLed_Buck_Handling(void)
{
  uint8_fast ucIdxIl = 0u, ucIdx = 0u;;
  tsRte_TgtLedSig0Arr sTgtLedSig0Arr = { 0u };
  uint16 unHss3Duty = 0U;
  uint8 ucBuckNo = 0u, ucBuckId[CTRLLED_CFG_MAX_BUCK_DRV];
  uint16 *punData = NULL_PTR;
  uint8_fast ucChannel = 0u;
#ifndef UNIT_TEST
  static tsCtrlLed_ErrorHandler sCtrlLed_ErrorHandler;
#else
  STATIC_UT_NOINIT(tsCtrlLed_ErrorHandler, sCtrlLed_ErrorHandler);
#endif
  uint8 ucLedStatus = CTRLLED_DIAG_STATUS_LED_OFF;
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  CtrlLed_ucCntFbit = 0U;
#endif
  punData = &CtrlLed_sCodingData.aunChannelIlluminant[0];

  for (ucIdxIl = 0u; ucIdxIl < CTRLLED_CFG_NO_ILLUMINANTS; ucIdxIl++)
  {
    if ((punData[ucIdxIl] != 0u) && (punData[ucIdxIl] <= CTRLLED_CFG_BIT_MAX_CHANNELS))
    {
      CtrlLed_FindBuckId(ucIdxIl, punData, &ucBuckNo, ucBuckId);

      for (ucIdx = 0u; ucIdx < ucBuckNo; ucIdx++)
      {
        //channel assigment 
        ucChannel = (uint8_fast)ucBuckId[ucIdx]; //note: each illuminant can have maximum 12 channel defines (e.g. into a unit group)
        if (ucBuckId[ucIdx] == CTRLLED_CFG_BASIC_LED_CH)
        {
          unHss3Duty = CtrlLed_DutyCalculation(ucChannel, ucIdxIl);
          //error handler
          sCtrlLed_ErrorHandler = CtrlLed_Diag_ErrorHandler(ucIdxIl, ucChannel, unHss3Duty, 0U);
          //write RTE
          CTRLLED_RTE_SE_TGT_HSS3_PWM(unHss3Duty)
        }
        else
        {
          //get duty
          sTgtLedSig0Arr[ucChannel].unDutyCycle = CtrlLed_DutyCalculation(ucChannel, ucIdxIl);
          //get current
          sTgtLedSig0Arr[ucChannel].unCurrent = CtrlLed_CurrentCalculation(ucChannel);
          //error handler
          sCtrlLed_ErrorHandler = CtrlLed_Diag_ErrorHandler(ucIdxIl, ucChannel, sTgtLedSig0Arr[ucChannel].unDutyCycle, sTgtLedSig0Arr[ucChannel].unCurrent);

          //force to switch off the channel in case an error appear
          sTgtLedSig0Arr[ucChannel].unDutyCycle = (sCtrlLed_ErrorHandler.boSwitchOffBuck[ucChannel] != FALSE) ? 0U : sTgtLedSig0Arr[ucChannel].unDutyCycle;
        }

        //in case the illuminant has more than 1 buck assigned and one of them have an error, report the error
        if (ucBuckNo > 1U)
        {
          ucLedStatus = (ucLedStatus >= CTRLLED_DIAG_START_ERR_CNT) ? ucLedStatus : sCtrlLed_ErrorHandler.ucLedState[ucChannel];
        }
        else
        {
          ucLedStatus = sCtrlLed_ErrorHandler.ucLedState[ucChannel];
        }
        const boolean boDiagStatus = (ucLedStatus != CTRLLED_DIAG_STATUS_OK) ? FALSE : TRUE;
        //store channel function name from coding
        const uint8 ucChFctName = CtrlLed_GetAndCheckLedName(ucChannel, ucIdxIl);
        //write illuminants state and status
        CTRLLED_RTE_SE_ILL_STS(ucIdxIl, CtrlLed_sInternalHandling.uIlluminantError[ucIdxIl].unRaw, boDiagStatus, ucChFctName);
      }
    }
  }

  //write duty and current via RTE
  CTRLLED_RTE_SE_TGT_LED_SIG(&sTgtLedSig0Arr)
    //write channel settings
  CTRLLED_RTE_SE_CH_SETTINGS(&sCtrlLed_ErrorHandler.sCtrlLed_ChannelSettings)
} //PRQA S 5324 1 // architecture and readability 

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_FindBuckId
///
/// \descr   
///
/// \param  ucIdx, *punInput, *pucBuckNumber, *pucBuckId
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_FindBuckId(uint8_fast ucIdx, uint16 *punInput, uint8 *pucBuckNumber, uint8 *pucBuckId)
{
  const uint8 ucBuckNo = CtrlLed_CountSetBucks(punInput[ucIdx]); //return how many bits are in punInput[ucIdx]
  CtrlLed_GetBuckId(punInput[ucIdx], ucBuckNo, pucBuckId);
  *pucBuckNumber = ucBuckNo;
}

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_MatrixVoltCond
///
/// \descr  -this function avoid to increase matrix intensities in LOW1 and 
///          switched off matrix in LOW2
///
/// \param  -ucVoltRange
///
/// \return teCtrlLed_MatrixVoltCnd
//-----------------------------------------------------------------------------
STATIC_AL teCtrlLed_MatrixVoltCnd CtrlLed_MatrixVoltCond(uint8 ucVoltRange)
{
  teCtrlLed_MatrixVoltCnd eMtxVoltCnd = CtrlLed_MtxDoNothing;
  static uint8 ucMtxRowLight_Local = 0U;
  switch (ucVoltRange)
  {
  case CTRLLED_NORMAL_VOLT:
    eMtxVoltCnd = CtrlLed_MtxDoNothing;
    ucMtxRowLight_Local = CtrlLed_sInternalHandling.ucMatrixRowLightBit;
    break;
  case CTRLLED_LOW1_VOLT:
    //matrix light has been changed
    if (ucMtxRowLight_Local > CtrlLed_sInternalHandling.ucMatrixRowLightBit)
    {
      ucMtxRowLight_Local = CtrlLed_sInternalHandling.ucMatrixRowLightBit;
      eMtxVoltCnd = CtrlLed_MtxFreeze_Write;
    }
    else if (ucMtxRowLight_Local == 0U)
    {
      eMtxVoltCnd = CtrlLed_MtxSwitchOff;
    }
    else
    {
      eMtxVoltCnd = CtrlLed_MtxFreeze_Skip;
    }
    break;
  case CTRLLED_LOW2_VOLT:
    eMtxVoltCnd = CtrlLed_MtxSwitchOff;
    break;
  default:
    break;
  }

  return eMtxVoltCnd;
}
//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Matrix_Handling
///
/// \descr  this function handle the matrix intensities, errors and reactions
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------

STATIC_AL void CtrlLed_Matrix_Handling(void)
{
  tsRte_TgtPxlSig0Arr sTgtPxlSig0Arr = { 0U };
  tsRte_PxaIntensityMatrix sPxaIntensityMatrix = { 0U };
  uint8_fast ucIdxIl = 0U, ucRow = 0U, ucIdx = 0U;
  uint8 ucData[CTRLLED_CFG_NR_OF_LOGICAL_UNITS] = { 0U };
  uint16 unIntensity = 0U;
  uint8 ucLuPxlSeg = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
  uint8 ucIll = CTRLLED_CFG_UNKNOWN_UINT8_VALUE; //store illuminant value based on matrix logical unit
  STATIC_UT(teCtrlLed_MatrixVoltCnd, eMtxVoltCnd , CtrlLed_MtxDoNothing); 
  //get voltage range
  const uint8 ucVoltRange = CTRLLED_RTE_RE_VOLT_RNG
  //get Diag En
  const boolean boDD01_Enabled = CTRLLED_RTE_RE_PIXEL_LED_DIAG_ENABLE
  //get Animation Status
  const boolean boAnimationStatus = ((Anima_Tgt()->boPriority != FALSE) && (eMtxVoltCnd != CtrlLed_MtxSwitchOff)) ? TRUE : FALSE;
  //get VCCX error Status
  const boolean boVccxErrStatus = CtrlLed_Diag_MtxVccx_Eeprom();
  //start with eMtx_Off
  CtrlLed_sInternalHandling.ucMatrixRowLightBit = 0U;
  //reset light status
  for (ucIdxIl = 0u; ucIdxIl < CTRLLED_CFG_NO_ILLUMINANTS; ucIdxIl++)
  {
    CtrlLed_sInternalHandling.boMtxLightIlStatus[ucIdxIl] = FALSE;
  }

  //reset actual row error status
  for (ucRow = 0U; ucRow < CTRLLED_MAX_MTX_COL_SEL; ucRow++)
  { 
    //new light request
    if (CtrlLed_sInternalHandling.ucMatrixRowLightBitPrv == 0U)
    {
      CtrlLed_sInternalHandling.sRowMtxErr[ucRow].boRowErr_Act = FALSE;
      CtrlLed_sInternalHandling.aulPixelAffected[ucRow] = 0U;
    }
  }

  if ((boDD01_Enabled != FALSE) && (eMtxVoltCnd != CtrlLed_MtxSwitchOff))
  {
    //read diag service
    CTRLLED_RTE_RE_PIXEL_LED_DIAG_INTENSITY(ucData)
  }
  else if ((boAnimationStatus == FALSE) && (eMtxVoltCnd != CtrlLed_MtxSwitchOff))
  {
    CTRLLED_RTE_RE_TGT_PXL_INTENSITIES(&sPxaIntensityMatrix)
  }
  else
  {

  }

  //read 103 units, each unit has 3 types of error
  for ( ucIdx = 0U; ucIdx < CTRLLED_CFG_MAX_NR_OF_PXL; ucIdx++)
  {
    ucLuPxlSeg = CtrlLed_sCodingData.aucLmmSwitchNo[ucIdx];

    if ((ucLuPxlSeg != CTRLLED_CFG_UNKNOWN_UINT8_VALUE) && (boVccxErrStatus == FALSE))
    {
      if (boDD01_Enabled != FALSE)
      {
        unIntensity = ucData[ucLuPxlSeg];
      }
      else
      {
        unIntensity =  (boAnimationStatus == FALSE) ? (*(uint16*)(&sPxaIntensityMatrix.Top[0] + ucIdx)) : (CtrlLed_sCodingData.aucAnimaMap[ucLuPxlSeg] == 255U) ? 0U : Anima_Tgt()->unTgtAni[CtrlLed_sCodingData.aucAnimaMap[ucLuPxlSeg]];
      }
      //get illuminant value based on pixel logical unit
      ucIll = Cod_IluminantType(ucLuPxlSeg);
      //check errors status and set the DTCs and do the reactions in case a fault is occurred
      if((ucVoltRange == CTRLLED_LOW2_VOLT) || (CtrlLed_sInternalHandling.boFbitMtx != FALSE))
      {
        sTgtPxlSig0Arr.unPxl_Int[ucLuPxlSeg] = 0U;
      }
      else if(ucIll != CTRLLED_CFG_UNKNOWN_UINT8_VALUE)
      {
        //scale intenity to 65535
        if (boDD01_Enabled != FALSE) //diagnostic service
        {
          //unIntensity = scale CTRLLED_SCALING_100 to CTRLLED_SCALING_65535 the unIntensity;
          if (unIntensity == CTRLLED_SCALING_100)
          {
            unIntensity = CTRLLED_SCALING_65535;
          }
          else
          {
            unIntensity *= 655U;
          }
        }
        else if (boAnimationStatus == FALSE) //PXA 
        {
          //unIntensity = scale CTRLLED_SCALING_10000 to CTRLLED_SCALING_65535 the unIntensity;
          uint32 ulTmp = (uint32)unIntensity * 429490U; //max input value is 10000 => it will not overflow 
          unIntensity = (uint16)(ulTmp >> 16U);
        }
        else //Animation
        {
          if (unIntensity == CTRLLED_SCALING_32768)
          {
            unIntensity = CTRLLED_SCALING_65535;
          }
          else
          {
            unIntensity <<= 1U;// scale from CTRLLED_SCALING_32768 to CTRLLED_SCALING_65535 the unIntensity;
          }
        }
        //calculate GAMMA if is not a diag service
        sTgtPxlSig0Arr.unPxl_Int[ucLuPxlSeg] = (boDD01_Enabled != FALSE) ? unIntensity : CtrlLed_CalculateGamma(unIntensity, ucIll);
        //check which illuminant and row is switched on and based on that report DTC and ERRORS
        CtrlLed_CheckLight(ucIdx, ucIll, ucLuPxlSeg, &sTgtPxlSig0Arr.unPxl_Int[ucLuPxlSeg]);
      }
      else
      {
        //no illuminant assigned
      }
    }
  }
  
  CtrlLed_HandleMatrixDtc();

  eMtxVoltCnd = CtrlLed_MatrixVoltCond(ucVoltRange);

  CtrlLed_sInternalHandling.boMtxLightStatus = ((eMtxVoltCnd != CtrlLed_MtxSwitchOff) && ((CtrlLed_sInternalHandling.ucMatrixRowLightBit != 0U) || (boAnimationStatus != FALSE))) ? TRUE : FALSE;
  
  CtrlLed_sInternalHandling.ucMatrixRowLightBitPrv = CtrlLed_sInternalHandling.ucMatrixRowLightBit;

  if (eMtxVoltCnd != CtrlLed_MtxFreeze_Skip)
  {
    CTRLLED_RTE_SE_TGT_PXL_PWM(&sTgtPxlSig0Arr)
  }
} // PRQA S 5336, 5316, 5324, 5310 1 // design

 
//-----------------------------------------------------------------------------
/// \brief  CtrlLed_CheckLight
///
/// \descr   this function check which row Is lighting and which buck has to be switch on when the coresponding pixel
///          is active (CtrlLed_sInternalHandling.boMtxLightIlStatus[ucIll])
///
/// \param   boStartSq,  ucIdx,  ucLmmPxl,  unDutyInt)
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_CheckLight(uint8_fast ucIdx, uint8 ucIll, uint8 ucLmmPxl, uint16 *punDutyInt)
{
  uint8 ucRowSel = CTRLLED_MAX_MTX_COL_SEL;
  boolean boErrStatus = FALSE;

  if (ucIdx < CFG_MATRIX_RAW_CNT)
  {
    ucRowSel = CTRLLED_MTX_ROW_TOP;
  }
  else if ((ucIdx >= CFG_MATRIX_RAW_CNT) && (ucIdx < (CTRLLED_CFG_MAX_NR_OF_PXL - CFG_MATRIX_RAW_CNT)))
  {
    ucRowSel = CTRLLED_MTX_ROW_MID;
  }
  else if ((ucIdx >= (CTRLLED_CFG_MAX_NR_OF_PXL - CFG_MATRIX_RAW_CNT)) && (ucIdx < CTRLLED_CFG_MAX_NR_OF_PXL))
  {
    ucRowSel = CTRLLED_MTX_ROW_BTM;
  }
  else
  {
    //unknown
  }

  if ( (*punDutyInt != 0u) && (ucRowSel != CTRLLED_MAX_MTX_COL_SEL ) )
  {
    CtrlLed_sInternalHandling.ucMatrixRowLightBit |= (uint8)((uint8)1U << ucRowSel);
  }

  if ((ucRowSel < CTRLLED_MAX_MTX_COL_SEL) && (ucLmmPxl != CTRLLED_CFG_UNKNOWN_UINT8_VALUE))
  {
    boErrStatus = CtrlLed_GetMatrixError(ucRowSel, ucLmmPxl, ucIll);
    
    if (boErrStatus != FALSE)
    {
      CtrlLed_sInternalHandling.aulPixelAffected[ucRowSel] |= (uint32)1U << ((uint32)ucIdx - ((uint32)(CTRLLED_MTX_ROW_TOP - (uint32)ucRowSel) * CFG_MATRIX_RAW_CNT));
    }

    if ((CtrlLed_sInternalHandling.aulPixelAffected[ucRowSel] & ((uint32)1U << ((uint32)ucIdx - ((uint32)(CTRLLED_MTX_ROW_TOP - (uint32)ucRowSel) * CFG_MATRIX_RAW_CNT)))) != 0U)
    {
      *punDutyInt = 0U;
    }
  }

  if (ucIll != CTRLLED_CFG_UNKNOWN_UINT8_VALUE)
  {
    CtrlLed_sInternalHandling.boMtxLightIlStatus[ucIll] = (*punDutyInt != 0U) ? TRUE : CtrlLed_sInternalHandling.boMtxLightIlStatus[ucIll];
  }
  
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Handle_MatrixCh
///
/// \descr  this function switches matrix channel to ON(100% duty) or OFF(0% duty)
///         based on request
///
/// \param  ucIdxIl, unTgtInt
///
/// \return uint16
//-----------------------------------------------------------------------------
STATIC_AL uint16 CtrlLed_Handle_MatrixCh(CONST_AL uint8_fast ucIdxIl, uint16 unTgtInt)
{
  //update: for buck power for coresponding LMM chip will follow the CtrlLed_sInternalHandling.boMtxLightIlStatus
  (void)unTgtInt;
  boolean boStatus = FALSE;
  uint16  unRetVal = CTRLLED_CHANNEL_OFF;
  //read rte port
  CTRLLED_RTE_RE_GET_MTX_SYS_MODE(&boStatus)

  if ((boStatus != FALSE) && (CtrlLed_sInternalHandling.boFbitMtx == FALSE))
  {
    //do not switch off the corresponding buck which has assigned a pwm and pixel pwm even if the function received intensity = 0%
    //this line avoids to switched off the matrix bucks while pixel dimming is ongoing and target intensity = 0%
    //
    //last check, (unTgtInt != 0U) is provided by fctR and in case the coding data (LSM) is not filled out corectly, the buck will have 100% => light distribution, 
    //mapping list, unit groups and illuminants from LSM should fit 1:1
    unRetVal = (CtrlLed_sInternalHandling.boMtxLightIlStatus[ucIdxIl] != FALSE) ? CTRLLED_SCALING_32768 : CTRLLED_CHANNEL_OFF;
  }
  //return dutycycle
  return unRetVal;
}
#endif

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_CalculateGamma
///
/// \descr   
///
/// \param   unIntensity, ucIll
///
/// \return uint16
//-----------------------------------------------------------------------------
STATIC_AL uint16 CtrlLed_CalculateGamma(uint16 unIntensity, uint8 ucIll)
{
  uint16 unDuty = 0U;

  if ((CtrlLed_sCodingData.sGamma.aucGammaSel[ucIll] != CTRLLED_CFG_UNKNOWN_UINT8_VALUE) && (CtrlLed_sCodingData.sGamma.aucGammaSel[ucIll] > 0u))
  {
    unDuty = CtrlLed_GammaCurve(unIntensity, &CtrlLed_sCodingData.sGamma.aunGamma[CtrlLed_sCodingData.sGamma.aucGammaSel[ucIll] - 1U][0]);
  }
  else //gamma correction is missing
  {
    unDuty = unIntensity;
  }

  return unDuty;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_CalcRamp
///
/// \descr  this function calculate the current intensity based on target intensity and target ramp (dimming)
///
/// \param  ucIdx, unTgtIntensity, unTgtRampMs
///
/// \return uint16(ramp)
//-----------------------------------------------------------------------------
STATIC_AL uint16 CtrlLed_CalcRamp(CONST_AL uint8_fast ucIdx, CONST_AL uint16 unTgtIntensity, CONST_AL uint16 unTgtRampMs)
{
  STATIC_UT(tsCtrlLed_RampValues, sRampValues[CTRLLED_CFG_LED_CHANNELS_NR], { 0u });
  STATIC_UT(uint16, unStartPoint_Int[CTRLLED_CFG_LED_CHANNELS_NR], { 0u });
  STATIC_UT(uint32, ulTimerGetTimeSince_us[CTRLLED_CFG_LED_CHANNELS_NR], { 0u });
  STATIC_UT(boolean, boDimInProgress[CTRLLED_CFG_LED_CHANNELS_NR], { 0u });
  uint16 unIntRemain = 0u;
  uint32 ulMsTime = 0u;

  //check target ramp for dimming
  if (unTgtRampMs != 0u)
  {
    //check if ramping or intensity have been changed 
    if ((sRampValues[ucIdx].unOldIntensity != unTgtIntensity) || (sRampValues[ucIdx].unOldRamping != unTgtRampMs))
    {
      //always start from current intensity
      unStartPoint_Int[ucIdx] = sRampValues[ucIdx].unCurrentIntensity;
      //store the previous value for ramping
      sRampValues[ucIdx].unOldRamping = unTgtRampMs;
      //store the previous value for intensity
      sRampValues[ucIdx].unOldIntensity = unTgtIntensity;
      //should be call once, store the current timer value
      ulTimerGetTimeSince_us[ucIdx] = TimerGetTick();
      //remaining ramp: the bellow code is only required when dimming is in progres and the ramping should be addapted based on difference between target and current intensity
      if ((boDimInProgress[ucIdx] != FALSE) && (sRampValues[ucIdx].unCurrentIntensity < unTgtIntensity)) //dimming up
      {
        sRampValues[ucIdx].unNewRamp = ((unTgtIntensity - sRampValues[ucIdx].unCurrentIntensity) * unTgtRampMs) / CTRLLED_SCALING_1000;
      }
      else if ((boDimInProgress[ucIdx] != FALSE) && (sRampValues[ucIdx].unCurrentIntensity > unTgtIntensity)) //dimming down
      {
        sRampValues[ucIdx].unNewRamp = ((sRampValues[ucIdx].unCurrentIntensity - unTgtIntensity) * unTgtRampMs) / CTRLLED_SCALING_1000;
      }
      else
      {
        sRampValues[ucIdx].unNewRamp = unTgtRampMs;
      }
    }

    //get current time
    ulMsTime = (TimerGetTimeSince(ulTimerGetTimeSince_us[ucIdx]) / CTRLLED_MS_CONVERTION);
    //current intensity is given by a linear interpolation while dimming is in progress
    if (sRampValues[ucIdx].unCurrentIntensity != unTgtIntensity)
    {
      boDimInProgress[ucIdx] = TRUE;
      sRampValues[ucIdx].unCurrentIntensity = CtrlLed_DoRampInterpolation(ulMsTime, 0u, sRampValues[ucIdx].unNewRamp, unStartPoint_Int[ucIdx], unTgtIntensity);
    }
    else
    {
      boDimInProgress[ucIdx] = FALSE;
      sRampValues[ucIdx].unCurrentIntensity = unTgtIntensity;
    }
  }
  else
  {
    //no dimming
    sRampValues[ucIdx].unCurrentIntensity = unTgtIntensity;
    //no ramp
    sRampValues[ucIdx].unOldRamping = unTgtRampMs;
  }

  //return computed intensity
  return sRampValues[ucIdx].unCurrentIntensity;
}


//-----------------------------------------------------------------------------
/// \brief   CtrlLed_DoRampInterpolation
///
/// \descr   this function calculate the current intenity with a liniar interpolation function
///          based on parameters below 
///
/// \param   ulCurrentTime, unStartPoint_Ms, unTgtPoint_Ms, unStartPoint_Int, unTgtPoint_Int
///
/// \return  interpolated point
//-----------------------------------------------------------------------------
STATIC_AL uint16 CtrlLed_DoRampInterpolation(uint32 ulCurrentTime, uint16 unStartPoint_Ms, uint16 unTgtPoint_Ms, uint16 unStartPoint_Int, uint16 unTgtPoint_Int)
{
  tLinearPoint Points[CTRLLED_POINTS_NR];

  Points[0].X = (sint32)unStartPoint_Ms;
  Points[1].X = (sint32)unTgtPoint_Ms;
  Points[0].Y = (sint32)unStartPoint_Int;
  Points[1].Y = (sint32)unTgtPoint_Int;
  const sint32 lRetVal = UtilMath_LinearInterpolate(Points, (sint32)CTRLLED_POINTS_NR, (sint32)ulCurrentTime);
  //return interpolated point and avoid overshooting or undershooting the values
  return (lRetVal < 0) ? 0u : (uint16)lRetVal;
}

//-----------------------------------------------------------------------------
/// \brief   CtrlLed_GammaCurve
///
/// \descr  this function apply a fast interpolation function for 17 points to correct
///         the current intenity received
///
/// \param  unIntensity, *punGammaY
///
/// \return unRetVal
//-----------------------------------------------------------------------------
STATIC_AL uint16 CtrlLed_GammaCurve(uint16 unIntensity, CONST_AL uint16 *punGammaY)
{
  uint16 unRetVal = 0u;

  //check intensity
  if (unIntensity != 0u)
  {
    unRetVal = UtilMath_FastInterpolateU16(punGammaY, CTRLLED_LININTERPOLSHIFT, unIntensity);
  }

  return unRetVal;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlLed_CountSetBucks
///
/// \descr  this function extract number of buks stored in unVal (on bits)
///
/// \param  unVal
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 CtrlLed_CountSetBucks(uint16 unVal)
{
  uint8 ucCount = 0U;

  while ((unVal != 0U) && (ucCount <= CTRLLED_CFG_MAX_BUCK_DRV))
  {
    unVal &= (unVal - 1U);
    ucCount++;
  }

  return ucCount;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_GetBuckId
///
/// \descr  this function set in *pucData the Buck ID extract from unVal
///
/// \param  unVal, unMaxBuck, *pucData
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_GetBuckId(uint16 unVal, uint8 unMaxBuck, uint8* pucData)
{
  uint8 ucBitPos = 0U, ucCount = 0U;
  uint16 unMask = 0U;

  while ((ucCount < unMaxBuck) && (ucBitPos <= CTRLLED_CFG_MAX_BUCK_DRV))
  {
    unMask = (uint16)((uint16)1U << (uint16)ucBitPos);
    
    if ((unVal & unMask) != 0U)
    {
      pucData[ucCount] = ucBitPos;
      ucCount++;
    }
    ucBitPos++;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Handle_NonMatrixCh
///
/// \descr  this function provide the duty cycle (after ramp, gamma, binning and
///         thermo calculation) for each channel
///
/// \param  ucIdx, unTgtInt, unTgtRamp, *punGammaY
///
/// \return uint16
//-----------------------------------------------------------------------------
STATIC_AL uint16 CtrlLed_Handle_NonMatrixCh(uint8_fast ucIdx, uint8_fast ucIdxIl, uint16 unTgtInt, uint16 unTgtRamp)
{
  uint16 unDutyInt = 0u;
  //calculate current intensity based on Ramp Calculation
  unDutyInt = CtrlLed_CalcRamp(ucIdx, unTgtInt, unTgtRamp);
  //scaling the intenity to 65535
  //unDutyInt = CTRLLED_SCALING_X_TO_Y_VALUE(CTRLLED_SCALING_1000, CTRLLED_SCALING_65535, unDutyInt);
  uint32 ulTmp = (uint32)unDutyInt * 4294900U; //max input value is 10000 => it will not overflow 
  unDutyInt = (uint16)(ulTmp >> 16U);
  //apply gamma correction
  unDutyInt = CtrlLed_CalculateGamma(unDutyInt, (uint8)ucIdxIl);
  //scaling to 32768
  //unDutyInt = CTRLLED_SCALING_X_TO_Y_VALUE(CTRLLED_SCALING_65535, CTRLLED_SCALING_32768, unDutyInt);

  unDutyInt >>= 1U;
  //return dutycycle
  return unDutyInt;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_CurrentCalculation
///
/// \descr  this function calculate voltage derating and set the current based on it
///
/// \param  ucIdx
///
/// \return uint16
//-----------------------------------------------------------------------------
STATIC_AL uint16 CtrlLed_CurrentCalculation(CONST_AL uint8_fast ucIdx)
{
  uint8 ucBinningSelect = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  static boolean aboBinningSelected[CTRLLED_CFG_BASIC_LED_CH] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
#else
  static boolean aboBinningSelected[CTRLLED_CFG_BASIC_LED_CH] = { FALSE, FALSE, FALSE, FALSE };
#endif
  //check for new updates
  if ((aboBinningSelected[ucIdx] == FALSE) && (ucIdx != CTRLLED_CFG_BASIC_LED_CH))
  {
    ucBinningSelect = CTRLLED_RTE_RE_BINNING_CLASS(ucIdx)
    //compare actual binning selection with the previous one
    if (ucBinningSelect != CtrlLed_sCodingData.aucBinningSelection[ucIdx])
    {
      //update binning current
      (void)CtrlLed_CurrentUpdates(ucIdx, ucBinningSelect, &CtrlLed_sCodingData);
      
      aboBinningSelected[ucIdx] = FALSE;
    }
    else
    {
      //used to stop Rte and Update of currents until Binning Class is Valid (avoid processing and once a binning is valid
      //there is no need to recall the mechanism
      aboBinningSelected[ucIdx] = TRUE;
    }
  }

  //return current
  return CtrlLed_sCodingData.aunBinningCurrent[ucIdx];
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_DutyCalculation
///
/// \descr  this function handles all channels and returns a duty cycle based on 
///         a target intensity and a ramp
///
/// \param  ucIdx, ucIdxIl
///
/// \return uint16
//-----------------------------------------------------------------------------
STATIC_AL uint16 CtrlLed_DutyCalculation(CONST_AL uint8_fast ucIdx, CONST_AL uint8_fast ucIdxIl)
{
  uint16 unDuty = CTRLLED_CHANNEL_OFF;
  tsRte_TgtLedVal0Arr sTgtLedVal0Arr = { 0u };
  uint16 unTgtInt = 0u, unTgtRamp = 0u;
  boolean boFbit = FALSE;
  const boolean boAnimationStatus = (Anima_Tgt()->boPriority != FALSE) ? TRUE : FALSE;
  //uint8 animationIntLu[CTRLLED_CFG_NR_OF_LOGICAL_UNITS]; //to be removed and replace with value from port
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  uint8 ucData[CTRLLED_CFG_NR_OF_LOGICAL_UNITS];
  const boolean boDD01_Enabled = CTRLLED_RTE_RE_PIXEL_LED_DIAG_ENABLE
  //this branch is applicable only for non matrix buck control (for matrix- see matrix handling function) and must have a higher priority in front of default path (anima or fctR)
  if ((boDD01_Enabled != FALSE) && (CtrlLed_sCodingData.aucChannelType[ucIdx] == CTRLLED_CFG_NON_MATRIX_BUCK)) //diag path
  {
    //get data value via diag service
    CTRLLED_RTE_RE_PIXEL_LED_DIAG_INTENSITY(ucData)
    //up scale from 1 -> 0.1 resolution
    unTgtInt = (CtrlLed_sCodingData.ucLogicalUnitIl[ucIdxIl] != CTRLLED_CFG_UNKNOWN_UINT8_VALUE) ? (10u * (uint16)(ucData[CtrlLed_sCodingData.ucLogicalUnitIl[ucIdxIl]])) : unTgtInt;
  }
  else
#endif
  {
    //read animation status via RTE
    if (boAnimationStatus != FALSE)
    {
      if ((CtrlLed_sCodingData.aucChannelType[ucIdx] == CTRLLED_CFG_NON_MATRIX_BUCK) && (CtrlLed_sCodingData.ucLogicalUnitIl[ucIdxIl] != CTRLLED_CFG_UNKNOWN_UINT8_VALUE))
      {
        unTgtInt = (CtrlLed_sCodingData.aucAnimaMap[CtrlLed_sCodingData.ucLogicalUnitIl[ucIdxIl]] == CTRLLED_CFG_UNKNOWN_UINT8_VALUE) ? 0U : CTRLLED_SCALING_X_TO_Y_VALUE(CTRLLED_SCALING_32768, CTRLLED_SCALING_1000, Anima_Tgt()->unTgtAni[CtrlLed_sCodingData.aucAnimaMap[CtrlLed_sCodingData.ucLogicalUnitIl[ucIdxIl]]]);
      }
    }
    else
    {
      //get intensity and ramp for each led channel
      CTRLLED_RTE_RE_TGT_LED(&sTgtLedVal0Arr)
      //store the ramp and intensity received
      unTgtInt = (sTgtLedVal0Arr.asTgtLedVal[ucIdxIl].unTgtIntensity > CTRLLED_SCALING_1000) ? CTRLLED_SCALING_1000 : sTgtLedVal0Arr.asTgtLedVal[ucIdxIl].unTgtIntensity;
      unTgtRamp = sTgtLedVal0Arr.asTgtLedVal[ucIdxIl].unRampTime;
      //set Fbit sent by FctR to force off all channels
      CTRLLED_RTE_SE_CH_FBIT(ucIdx, sTgtLedVal0Arr.asTgtLedVal[ucIdxIl].boFBit)
    }
  }
  
  switch (CtrlLed_sCodingData.aucChannelType[ucIdx])
  {
  case CTRLLED_CFG_NON_MATRIX_BUCK:
    //for non matrix supply channels, calculate the ramp, apply gamma corretion and thermo power factor
    unDuty = CtrlLed_Handle_NonMatrixCh(ucIdx, ucIdxIl, unTgtInt, unTgtRamp);
    break;
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  case CTRLLED_CFG_MATRIX_BUCK:
    CtrlLed_ucCntFbit = (sTgtLedVal0Arr.asTgtLedVal[ucIdxIl].boFBit != FALSE) ? (CtrlLed_ucCntFbit + 1U) : CtrlLed_ucCntFbit;
    boFbit = sTgtLedVal0Arr.asTgtLedVal[ucIdxIl].boFBit;
    CtrlLed_sInternalHandling.boFbitMtx |= boFbit;
    //while target intensity is OFF, switch off the buck, otherwise keep matrix buck to 100% pwm
    unDuty = CtrlLed_Handle_MatrixCh(ucIdxIl, unTgtInt);
    break;
#endif
  default:
    //UNKNOWN BUCK
    unDuty = CTRLLED_CHANNEL_OFF;
    break;
  }
  
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  if ((ucIdxIl == (CTRLLED_CFG_NO_ILLUMINANTS - 1U)) && (CtrlLed_ucCntFbit == 0U))
  {
    CtrlLed_sInternalHandling.boFbitMtx = FALSE;
  }
#endif
  //return duty
  return unDuty;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_pfCodingData
///
/// \descr  this function return coding data address
///
/// \param  void
///
/// \return tsCtrlLed_VoltDerating*
//-----------------------------------------------------------------------------
tsCtrlled_CodingData *CtrlLed_pfCodingData(void)
{
  return &CtrlLed_sCodingData;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_pfInternalHandling
///
/// \descr  this function return internal handling address
///
/// \param  void
///
/// \return tsCtrlled_InternalHandlings*
//-----------------------------------------------------------------------------
tsCtrlled_InternalHandlings* CtrlLed_pfInternalHandling(void)
{
  return &CtrlLed_sInternalHandling;
}

