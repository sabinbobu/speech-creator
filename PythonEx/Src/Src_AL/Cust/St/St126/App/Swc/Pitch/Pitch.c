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
/// \file  Pitch.c
///
/// \brief
///
/// \descr
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Ott, Peter ALRT/EEG-PM2 * (otp2rt)
///         mailTo:Peter.Ott[at]al-lighting.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#ifndef UNIT_TEST
#include <Bsw/Common/Std_Types.h>

#endif // !UNIT_TEST
#include <Nvm.h>

#include <Cfg/Cfg.h>
#include <Swc/CodM/CodM.h>

#include "Pitch.h"
#include "PitchCfg.h"
#include "Pitch_Data.h"
#include "Pitch_Types.h"
#include "Pitch_RteAccess.h"
#include <UtilMath.h>

//=============================================================================
// variables
//=============================================================================

//=============================================================================
// Static Variables
//=============================================================================
STATIC_AL tsPitchErrCnt  sPitch_ErrCnt;
STATIC_AL uint8          ucPitch_ErrCntVccxLoRR;
STATIC_AL uint8          ucPitch_ErrCntVccxLoFR;
STATIC_AL uint8          ucPitch_ErrCntVccxHiRR;
STATIC_AL uint8          ucPitch_ErrCntVccxHiFR;
STATIC_AL boolean        boPitch_CodingValidity = FALSE;
STATIC_AL tsDisplacement sPitch_DispSens = { {0, 0}, {0, 0} };

//=============================================================================
// prototypes
//=============================================================================
STATIC_AL sint16         Pitch_DispCalc(CONST_AL sint16 nSlope, tFiltIir_s* CONST_AL pFilter, CONST_AL sint32 lInput);
STATIC_AL void           Pitch_DispMeasurement  (void);

STATIC_AL tucPitchSigQty Pitch_SigWorst         (CONST_AL tucPitchSigQty ucQty1, CONST_AL tucPitchSigQty ucQty2);
STATIC_AL tucPitchSigQty Pitch_ErrCntInc        (uint8* CONST_AL pucErrCnt, CONST_AL Dem_EventListId_EnumType teErrId);
STATIC_AL tucPitchSigQty Pitch_ErrCntDec        (uint8* CONST_AL pucErrCnt, CONST_AL Dem_EventListId_EnumType teErrId);

STATIC_AL tucPitchSigQty Pitch_CheckSensorState (CONST_AL uint32 ulIx);
//STATIC_AL tucPitchSigQty Pitch_CheckSensSupply  (void);

STATIC_AL sint16         Pitch_AngleCalc        (CONST_AL sint16 nFrnt, CONST_AL sint16 nRear);
STATIC_AL void           Pitch_PitchMeasurement (void);
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
STATIC_AL void           Pitch_ErrPassed(void);
#endif

//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief Pitch_SetLocal_DisplacementSens
///
/// \descr This function is used to write dates in a global structure used in this file
///
/// \param  sDispSens
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_SetLocal_DisplacementSens(tsDisplacement sDispSens)
{
  for (uint32 ulIdx = 0u; ulIdx < CFG_CntSens; ulIdx++)
  {
    sPitch_DispSens.eSigQty[ulIdx] = sDispSens.eSigQty[ulIdx];
    sPitch_DispSens.nDisp[ulIdx]   = sDispSens.nDisp[ulIdx];
  }
}


//-----------------------------------------------------------------------------
/// \brief Pitch_GetLocal_DisplacementSens
///
/// \descr function to read data from a global structure used inside this file
///
/// \param  psDispSens
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_GetLocal_DisplacementSens(tsDisplacement* psDispSens)
{
  for (uint32 ulIdx = 0; ulIdx < CFG_CntSens; ulIdx++)
  {
    psDispSens->nDisp[ulIdx]   = sPitch_DispSens.nDisp[ulIdx];
    psDispSens->eSigQty[ulIdx] = sPitch_DispSens.eSigQty[ulIdx];
  }
}


//-----------------------------------------------------------------------------
/// \brief  Combine 2 signal qualities: get worst of both
///
/// \descr  Regard the following 3 qualities:
///         prio1: SIG_INVALID
///         prio2: SIG_SNA
///         prio3: SIG_VALID
///
/// \param  Qty1
/// \param  Qty2
///
/// \return  tucPitchSigQty
//-----------------------------------------------------------------------------
STATIC_AL tucPitchSigQty Pitch_SigWorst(CONST_AL tucPitchSigQty ucQty1, CONST_AL tucPitchSigQty ucQty2)
{
  tucPitchSigQty ucSigQty = SIG_SNA;

  if((ucQty1 == SIG_VALID) && (ucQty2 == SIG_VALID))
  {
    ucSigQty = SIG_VALID;
  }

  if((ucQty1 == SIG_INVALID) || (ucQty2 == SIG_INVALID))
  {
    ucSigQty = SIG_INVALID;
  }
  return ucSigQty;
}


//-----------------------------------------------------------------------------
/// \brief Seting DTCs
///
/// \descr This function is setting to FAILD the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
/// \param  pucErrCnt
/// \param  ErrId
///
/// \return tucPitchSigQty
//-----------------------------------------------------------------------------
STATIC_AL tucPitchSigQty Pitch_ErrCntInc(uint8* CONST_AL pucErrCnt, CONST_AL Dem_EventListId_EnumType teErrId)
{
  tucPitchSigQty ucSigQty = SIG_SNA;

  if(*pucErrCnt < Cod_Pitch_ErrCntMax())
  {
    (*pucErrCnt)++;

    if(*pucErrCnt >= Cod_Pitch_ErrCntMax())
    {

      Rte_Call_DemPrj_ReportErrorStatus((uint16)teErrId, DEM_EVENT_STATUS_FAILED);
    }
  }
  else  // error already validated
  {
    ucSigQty = SIG_INVALID;
  }
  return ucSigQty;
}


//-----------------------------------------------------------------------------
/// \brief Seting DTCs
///
/// \descr This function is setting to PASED the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
/// \param  pucErrCnt
/// \param  ErrId
///
/// \return tucPitchSigQty
//-----------------------------------------------------------------------------
STATIC_AL tucPitchSigQty Pitch_ErrCntDec(uint8* CONST_AL pucErrCnt, CONST_AL Dem_EventListId_EnumType teErrId)
{
  tucPitchSigQty ucSigQty = SIG_SNA;

  if(*pucErrCnt < Cod_Pitch_ErrCntMax())  // check for lock in case of validated error
  {
    if(*pucErrCnt > 0u)
    {
      (*pucErrCnt)--;

      if(*pucErrCnt == 0u)
      {
        Rte_Call_DemPrj_ReportErrorStatus((uint16)teErrId, DEM_EVENT_STATUS_PASSED);
      }
    }
    else  // counter == 0
    {
      ucSigQty = SIG_VALID;
    }
  }
  else  // error already validated and locked
  {
    ucSigQty = SIG_INVALID;
  }
  return ucSigQty;
}


//-----------------------------------------------------------------------------
/// \brief  Displacement Calculation
///
/// \descr
///
/// \param  nSlope  sensor slope [um/%] (=0.1mm/FullScaleRange)
/// \param  pFilter pointer to fast IIR filter variable
/// \param  lInput  balanced sensor value [sensor raw]
///
/// \return sint16  displacement [0.1mm]
//-----------------------------------------------------------------------------
STATIC_AL sint16 Pitch_DispCalc(CONST_AL sint16 nSlope, tFiltIir_s* CONST_AL pFilter, CONST_AL sint32 lInput)
{
  // note: abs(lInput) < 65536 --> no overflow possible
  sint32 slDisp = (lInput * nSlope) / 65536;

  slDisp = min(slDisp,  32767);
  slDisp = max(slDisp, -32768);

  UtilMath_FastIir_s_Track(pFilter, (sint16) slDisp, PITCH_TauTracking, PITCH_JitterTol);

  return UtilMath_FastIir_s_GetResult(pFilter);
}


//-----------------------------------------------------------------------------
/// \brief  Angle Calculation
///
/// \descr  calculate AutoAngle in 1/10 mrad (mm at distance of 10m)
///         --------------------------------------------------------
///         AutoAngle[0.1mrad] = ((Front[mm]    - Rear[mm])    * 10000 ) / Wheelbase[mm]
///                            = ((Front[0.1mm] - Rear[0.1mm]) *  1000 ) / Wheelbase[mm]
///
/// \param  nFrnt: Displacement Front [0.1mm]
/// \param  nRear: Displacement Rear  [0.1mm]
///
/// \return sint16 Pitch Angle [0.1mrad]
//-----------------------------------------------------------------------------
STATIC_AL sint16 Pitch_AngleCalc(CONST_AL sint16 nFrnt, CONST_AL sint16 nRear)
{
   sint32 lAngle         = 0;
   sint32 lAngleMin      = 0;
   sint32 lAngleMax      = 0;
   sint32 slRadiusOffset = ((sint32)Cod_Pitch_R1() - (sint32)Cod_Pitch_R2()) * PITCH_RADIUS_SCALING;

   if(Cod_Pitch_Wheelbase() != 0u)
   {
    lAngle =(    (   (  ( (sint32) (nFrnt * (sint32)Cod_Pitch_DPF() - nRear * (sint32)Cod_Pitch_DPR()) * 10 ) + slRadiusOffset  ) / (sint32)Cod_Pitch_Wheelbase()   )    );
   }
   else  // avoid division by zero
   {
     lAngle = 0;
   }

   lAngleMin = Cod_Pitch_AngleMin();
   lAngleMax = Cod_Pitch_AngleMax();
   lAngle = min(lAngle, lAngleMax);
   lAngle = max(lAngle, lAngleMin);

   return (sint16) lAngle;
}


//-----------------------------------------------------------------------------
/// \brief   Pitch_CheckSensSupply
///
/// \descr This function is checking the sensors supply voltage Vccx to be in
///        to be in range of datasheet parameters  4.5V - 5V - 5.5V
///
/// \param  -
///
/// \return tucPitchSigQty
//-----------------------------------------------------------------------------
tucPitchSigQty Pitch_CheckSensSupply(void)
{
  tucPitchSigQty ucSigQtyLoRR = SIG_VALID;
  tucPitchSigQty ucSigQtyLoFR = SIG_VALID;
  tucPitchSigQty ucSigQtyHiRR = SIG_VALID;
  tucPitchSigQty ucSigQtyHiFR = SIG_VALID;
  tucPitchSigQty ucSigQtyLo   = SIG_VALID;
  tucPitchSigQty ucSigQtyHi   = SIG_VALID;
  uint16     unVccx       = 0u;

  //Read the value of signal Vccx1 from Rte
   Pitch_RteAccess_Get_VCCX1Voltage(&unVccx);

  if(unVccx < Cod_Pitch_VccxMin())
  {
    ucSigQtyLoRR = Pitch_ErrCntInc(&ucPitch_ErrCntVccxLoRR, RR_BHS_SUPPLY_LOW);
    ucSigQtyLoFR = Pitch_ErrCntInc(&ucPitch_ErrCntVccxLoFR, FR_BHS_SUPPLY_LOW);
    
    ucSigQtyHiRR = Pitch_ErrCntDec(&ucPitch_ErrCntVccxHiRR, RR_BHS_SUPPLY_HIGH);
    ucSigQtyHiFR = Pitch_ErrCntDec(&ucPitch_ErrCntVccxHiFR, FR_BHS_SUPPLY_HIGH);
  }

  else if(unVccx > Cod_Pitch_VccxMax())
  {
    ucSigQtyLoRR = Pitch_ErrCntDec(&ucPitch_ErrCntVccxLoRR, RR_BHS_SUPPLY_LOW);
    ucSigQtyLoFR = Pitch_ErrCntDec(&ucPitch_ErrCntVccxLoFR, FR_BHS_SUPPLY_LOW);
    
    ucSigQtyHiRR = Pitch_ErrCntInc(&ucPitch_ErrCntVccxHiRR, RR_BHS_SUPPLY_HIGH);
    ucSigQtyHiFR = Pitch_ErrCntInc(&ucPitch_ErrCntVccxHiFR, FR_BHS_SUPPLY_HIGH);
  }
  else
  {
    // do nothing
  }

  // set the state of the signal
  ucSigQtyLo = Pitch_SigWorst(ucSigQtyLoRR, ucSigQtyLoFR);
  ucSigQtyHi = Pitch_SigWorst(ucSigQtyHiRR, ucSigQtyHiFR);

  return Pitch_SigWorst(ucSigQtyLo, ucSigQtyHi);
}


//-----------------------------------------------------------------------------
/// \brief Checking the sensor state
///
/// \descr This function is checking the sensor state and set the coresponding DTC
///        in case of invalid state of the signal, also the it will set the quality
///        variable for coresponding state SIG_VALID; SIG_INVALID or SIG_SNA
///
/// \param  uint32 ulIx
///         uint16 unSensRaw
///
/// \return tucPitchSigQty
//-----------------------------------------------------------------------------
STATIC_AL tucPitchSigQty Pitch_CheckSensorState(CONST_AL uint32 ulIx)
{
  CONST_AL uint16 unSensMin = Cod_Pitch_SensMin();
  CONST_AL uint16 unSensMax = Cod_Pitch_SensMax();

  tucPitchSigQty SigQty   = SIG_VALID;

  // if is rear sensor it will have rear events otherways it will be front events
  uint16 eDtc_BHS_CSG = (PITCH_RR_SENSOR == ulIx) ? (uint16)RR_BHS_CSG : (uint16)FR_BHS_CSG;
  uint16 eDtc_BHS_OC  = (PITCH_RR_SENSOR == ulIx) ? (uint16)RR_BHS_OC : (uint16)FR_BHS_OC;

  if (((PITCH_FR_SENSOR == ulIx) || (PITCH_RR_SENSOR == ulIx)) && NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_HLS)
  {
    // LOW signal for Front and Rear sensors
    if (NvmBlockDeltaPwmPara.ucSensGndError[ulIx] != 0u) // singnal lower than 5%  set DTC as FAILD
    {
      //SigQty = SIG_INVALID;
      Rte_Call_DemPrj_ReportErrorStatus(eDtc_BHS_CSG, DEM_EVENT_STATUS_FAILED); // set DTC for SC to GNG as FAILD
    }
    // HIGH signal for Front and Rear sensors
    else if (NvmBlockDeltaPwmPara.ucSensVbatError[ulIx] != 0u) // signl higher than 95% set DTC as FAILD
    {
      //SigQty = SIG_INVALID;
      Rte_Call_DemPrj_ReportErrorStatus(eDtc_BHS_OC, DEM_EVENT_STATUS_FAILED); // set DTC for SC to VBAT as FAILD
    }
    else
    {
      SigQty = (Pitch_GetSensorError() == eHLS_FROZEN_FAILURE) ? SIG_INVALID : SIG_VALID;
      Rte_Call_DemPrj_ReportErrorStatus(eDtc_BHS_CSG, DEM_EVENT_STATUS_PASSED); // set DTC for SC to GNG as PASSED
      Rte_Call_DemPrj_ReportErrorStatus(eDtc_BHS_OC, DEM_EVENT_STATUS_PASSED); // set DTC for SC to VABT as PASSED
    }
  }
  #if defined(SAMPLE_FULL) || defined(UNIT_TEST) 
  else if (NvmBlockDeltaPwmPara.eNVM_VAC_Input != eInput_HLS)
  {
    SigQty = SIG_VALID;
  }
#endif
  else
  {
    // do nothing
  }
  return  SigQty;
}


//-----------------------------------------------------------------------------
/// \brief Displacement maseurement
///
/// \descr This function is setting the wuality of the signal based on Displancemet
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pitch_DispMeasurement(void)
{
  tFiltIir_s aFilter[CFG_CntSens] = { 0 };
  uint16 aucSensRaw[CFG_CntSens]  = { 0u };
  sint32 alSensIn[CFG_CntSens]    = { 0 };

  tsDisplacement sDisp            = { 0 };
  tucPitchSigQty VccxQty               = Pitch_CheckSensSupply();
  uint32 ulIdx;

  // Read RAW value from sonsors
  Pitch_RteAccess_Get_GetSens_Raw(&aucSensRaw[0]);
  // Read balanced value from IoHwabUser-> balenced value is the valuye afther zero level programing
  Pitch_RteAccess_Get_GetSens_Balanced(&alSensIn[0]);

  for (ulIdx = 0; ulIdx < CFG_CntSens; ulIdx++)
  {
    // calculate the Diplacement
    sDisp.nDisp[ulIdx]      = Pitch_DispCalc(Cod_Pitch_SensorSlope(ulIdx), &aFilter[ulIdx], alSensIn[ulIdx]);

    // check signla quality of the sensors and set DTC
    sDisp.eSigQty[ulIdx] = Pitch_CheckSensorState(ulIdx); 
    sDisp.eSigQty[ulIdx] = Pitch_SigWorst(sDisp.eSigQty[ulIdx], VccxQty);

    if (sDisp.eSigQty[ulIdx] == SIG_SNA)  // only possible at transition from SIG_VALID to SIG_INVALID
    {
      Pitch_GetLocal_DisplacementSens(&sDisp);// get values before error
      sDisp.eSigQty[ulIdx] = SIG_VALID;
    }
    else
    {
      // do nothing
    }
  }
  Pitch_SetLocal_DisplacementSens(sDisp);
}// PRQA S 5324 1 // design


//-----------------------------------------------------------------------------
/// \brief Pitch measurement
///
/// \descr The function is delivering the Pitch angle and the quality of the signal
///        based on the displacement. This function is the output of this module
///        The Angle and the quality of the signal is needed in AVAC module
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pitch_PitchMeasurement(void)
{
  tsPitch         sPitch = { 0 };
  tsDisplacement  sDisp  = { 0 };

  Pitch_GetLocal_DisplacementSens(&sDisp);
  sPitch.nAngle = Pitch_AngleCalc(sDisp.nDisp[PITCH_FR_SENSOR], sDisp.nDisp[PITCH_RR_SENSOR]); // calculate pitch angle
  sPitch.eSigQty = Pitch_SigWorst(sDisp.eSigQty[PITCH_FR_SENSOR], sDisp.eSigQty[PITCH_RR_SENSOR]);
  sPitch.nHeightErr = 0;

  Pitch_RteAccess_Set_Angle(&sPitch);
}


  //-----------------------------------------------------------------------------
/// \brie fPitch_Init
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_Init(void)
{
  for (uint32 ulIdx = 0; ulIdx < CFG_CntSens; ulIdx++)
  {
    sPitch_ErrCnt.aucSigLo[ulIdx] = 1;  // reset to warning level --> PASSED at 1st sample
    sPitch_ErrCnt.aucSigHi[ulIdx] = 1;
  }
  boPitch_CodingValidity = Pitch_CodingDataValidation();// read coding and validate it

  Pitch_CheckSensMountingInit();
}
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief Pitch_ErrPassed
///
/// \descr This function is called when AMVAR config is active, DTCs related to the HLS
///        are deleted
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pitch_ErrPassed(void)
{
  Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_SUPPLY_HIGH, DEM_EVENT_STATUS_PASSED);
  Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_SUPPLY_HIGH, DEM_EVENT_STATUS_PASSED);
  
  Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_SUPPLY_LOW, DEM_EVENT_STATUS_PASSED);
  Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_SUPPLY_LOW, DEM_EVENT_STATUS_PASSED);
  
  Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_CSG, DEM_EVENT_STATUS_PASSED);
  Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_CSG, DEM_EVENT_STATUS_PASSED);
  
  Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_OC, DEM_EVENT_STATUS_PASSED);
  Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_OC, DEM_EVENT_STATUS_PASSED);
  
  Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_PLAUS_FAIL, DEM_EVENT_STATUS_PASSED);
  Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_PLAUS_FAIL, DEM_EVENT_STATUS_PASSED);
} // PRQA S 5310 1 // interface function
#endif

//-----------------------------------------------------------------------------
/// \brief Pitch_Cycle0
///
/// \descr This function is called cyclical
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_Cycle0(void)
{
  if (boPitch_CodingValidity != FALSE 
#if defined(SAMPLE_ECO) 
    && NvmBlockDeltaPwmPara.eASL_Present != eASL_Absent
#endif
    )
  {
    static tePitch_LvlPhase ePitch_LvlPhase;

    Pitch_DispMeasurement();
    Pitch_PitchMeasurement();
    
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
    // Read Adl Phase from CtrlStp
    Pitch_RteAccess_Get_GetAdlPhase(&ePitch_LvlPhase);
#elif defined(SAMPLE_ECO)
    // Read Asl Phase from CtrlDcm
    Pitch_RteAccess_Get_GetAslPhase(&ePitch_LvlPhase);
#endif

    if (ePitch_LvlPhase == ePitchState_Adj)
    {
      Pitch_AdjustmentCheckPlausibility();
    }
    else if (ePitch_LvlPhase == ePitchState_Fail)
    {
      Pitch_FailureCheckPlausibility();
    }
    else
    {
      // do not check plausibility
    }

    #if defined(SAMPLE_FULL) || defined(UNIT_TEST) 
    if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN)
    {
      // Remove DTCs when in CAN config (frame 0x350)
      Pitch_ErrPassed();
    }
    #endif
  }
  else
  {
    boPitch_CodingValidity = Pitch_CodingDataValidation();
  }
} // PRQA S 5324 1 // design 
// EOF
