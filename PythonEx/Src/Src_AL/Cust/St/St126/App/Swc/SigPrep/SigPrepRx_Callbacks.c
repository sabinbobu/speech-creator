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
/// \file   SigPrepRxCallbacks.c
///
/// \brief  Input Frame Rx Callbacks
///
/// \descr  Input Frame Rx Callbacks [Init, Receprion Event, Time-out error, Checksum/Cnt Error]
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <SigPrepRx_Callbacks.h>
#include <SigPrepRx.h>

#include <Nvm.h>

#include <UtilMath.h>

#include <LgmDEHMainAPI.h>
#include <LgmDEHCtxtMgt.h>
#include <LgmDEHMainAPI.h>


//-----------------------------------------------------------------------------
// global variables
//-----------------------------------------------------------------------------
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
STATIC_AL CONST_AL tsSigPrep_ClusterSigGroup1_InvalidData SigPrep_RxCallbacks_sCvmInvalid[SIGPREP_RX_CVM_FRAMES] = 
{
  {VSM_INVALID_DATA_163_ID},
  {VSM_INVALID_DATA_16B_ID},
  {VSM_INVALID_DATA_183_ID},
  {VSM_INVALID_DATA_18B_ID},
  {VSM_INVALID_DATA_1AB_ID},
  {VSM_INVALID_DATA_12B_ID},
  {VSM_INVALID_DATA_143_ID},
  {VSM_INVALID_DATA_14B_ID},
};

#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

STATIC_AL TIMER SigPrepRx_Callbacks_ulFrameState_us    = 0u;
STATIC_AL TIMER SigPrepRx_Callbacks_ulFrameStateSTT_us = 0u;
 //-----------------------------------------------------------------------------
 // funtion prototypes
 //-----------------------------------------------------------------------------
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
STATIC_AL  tPitch0                SigPrep_RxCallbacks_ConfigDetection(teSigPrep_RxFrameState eSigPrep350State);
STATIC_AL  teRte_ClusterSubTypeX  SigPrep_RxCallbacks_Compute_ClusterSubType(uint8 ucClusterSubTypeX);
STATIC_AL  teRte_ClusterTypeX     SigPrep_RxCallbacks_Compute_ClusterType(uint8 ucClusterTpeX);
STATIC_AL  teRte_TrafficDetected  SigPrep_RxCallbacks_Compute_TrafficDetected(uint8 ucTrafficDetected);
STATIC_AL  void                   SigPrep_RxCallbacks_DtcCheck_ClusterSigGroup2(tsRte_SigPrep_ClusterSigGroup2_sVal sInputSig, uint8 ucMessageId);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_PerceiveSigGroup2(tsRte_SigPrep_PerceiveSigGroup2_sVal sInputSig, uint8 ucMessageId);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_VehicleAttitude(tsRte_SigPrep_VehiclePitchAngle *psOutputSig, sint16 nInputSig);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_VehiclePathCurvature(tsRte_SigPrep_VehPathCurvature *psOutputSig, sint16 nInputSig);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_PositionSiteD(tsRte_LevellingFeedback *psOutputSig, uint16 unInputSig);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_DynBendBeamFault(tsRte_BendingBeamFault_OtherHL *psOutputSig, uint8 ucInputSig);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_LevellingRight(tsRte_LevellingDiagStatus *psOutputSig, teLvlRefStateR eInputSig);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_SteeringWheel(tsRte_SigPrep_SteeringWheelAngle *psOutputSig, sint16 nInputSig);

LOCAL_INLINE boolean              SigPrep_RxCallbacks_RangeCheck_PerceiveAzimuthRate(sint8 cInputSigVal);
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

STATIC_AL  void                   SigPrep_RxCallbacks_STTConfigDetection(teSigPrep_RxFrameState eSigPrepStateSTT);
STATIC_AL  void                   SigPrep_RxCallbacks_Compute_ExtLightingAnimationReq(tsRte_AnimationReq *psOutputSig, uint16 unLightingAnimationReq, uint8 ucDelayFmh);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_YawSpeed(tsRte_SigPrep_YawSpeed *psOutputSig, tsSigPrep_RxYawSpeedFrmCheck sInputSig);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_DynamicSigs(tsRte_SigPrep_DynamicSigs *psOutputSig, tsSigPrep_RxDynamicSigsFrmCheck sInputSig);
STATIC_AL  void                   SigPrep_RxCallbacks_RangeCheck_ConsigneSiteD(tsRte_LevellingTgtPos *psOutputSig, uint16 unInputSig);
STATIC_AL  sint32                 SigPrep_RxCallbacks_ConvertValueInt2Sint(uint32 ulInValue, uint8 ucbitLength);
STATIC_AL  boolean                SigPrepRx_Callbacks_Debounce_TimerCheck(boolean *pboStartTimer, uint8 ucFrameName);
STATIC_AL  DAPI_TE_ConfigMode     SigPrepRx_Callbacks_RangeCheck_ConfigVehicle(tsRte_SigPrep_VehicleConfigSig *psOutputSig, uint8 ucConfigVeh);
 //-----------------------------------------------------------------------------
 // functions
 //-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_ACQ_NEW_JDD_55F
///
/// \descr Handling of 0x55F receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_ACQ_NEW_JDD_55F(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucDehAckVal = 0u;

  switch (eSigPrepRxState)
  {
  case eFrameInit:

    break;
  case eFrmEvent:
    ucDehAckVal = *DATA_ACQ_JDD_BSI_2;

    // Indication of aknowledge reception
    DAPI_BSIAckState(ucDehAckVal);
    break;
  case eFrmTimeOut:
    break;
  default:
    break;
  }
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DAT_VSM_36E
///
/// \descr Handling of 0x36E receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DAT_VSM_36E(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8   ucDelayFmh                = 0u;
  uint16  unExtLightingAnimationReq = 0u;
  uint8   ucLowBeamState            = 0u;

  tsRte_AnimationReq  sAnimaReq = { 0 };

  sAnimaReq.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_AnimationReq(&sAnimaReq);

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sAnimaReq.eSigQty = SIG_SNA;

    break;

  case eFrmEvent:
    // Reset DTC U0140-87 - HS6_DAT_VSM_36E frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_36E_ID, DEM_EVENT_STATUS_PASSED);

    // Read CAN signals
    ucDelayFmh                = *DELAY_FMH;
    unExtLightingAnimationReq = (uint16)((uint16)(*EXT_LIGHTNING_ANIMATION_REQ) + (uint16)((uint16)(*(EXT_LIGHTNING_ANIMATION_REQ + 1U)) << 8U));
    ucLowBeamState            = *ETAT_FEUX_CROIST;

    // Compute Lighting animation request
    SigPrep_RxCallbacks_Compute_ExtLightingAnimationReq(&sAnimaReq, unExtLightingAnimationReq, ucDelayFmh);

    // Compute Low Beam State
    sAnimaReq.eLowBeamState = (ucLowBeamState != SIGPREP_RX_ZERO_VALUE) ? eLightedOn : eLightedOff;

    break;

  case eFrmTimeOut:
    sAnimaReq.eDelayFmh                    = eDelayFmh_NotUsed;
    sAnimaReq.eFrontLightingAnimationCtrl  = eExtLightingAnimationReq_None;

    // Set DTC U0140-87 - HS6_DAT_VSM_36E frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_36E_ID, DEM_EVENT_STATUS_FAILED);

    // Set signal quality for RTE port as time-out
    sAnimaReq.eSigQty = SIG_TIMEOUT;
    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_AnimationReq(&sAnimaReq);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DAT_VSM_3AE
///
/// \descr Handling of 0x3AE receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DAT_VSM_3AE(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8               ucModeConfigVhl = 0u;
  uint8               ucEtatMar       = 0u;
  DAPI_TE_ConfigMode  eConfigMode = 0;

  tsRte_SigPrep_VehicleConfigSig  sVehConfigSig = { 0 };

  sVehConfigSig.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_VehicleConfigSig(&sVehConfigSig);

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sVehConfigSig.eSigQty = SIG_SNA;

    break;

  case eFrmEvent:
    // Reset DTC U0140-87 - HS6_DAT_VSM_3AE frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_3AE_ID, DEM_EVENT_STATUS_PASSED);

    // Read CAN signals
    ucModeConfigVhl = *MODE_CONFIG_VEHICLE;

    // Compute State of vehicle configuration
    eConfigMode = SigPrepRx_Callbacks_RangeCheck_ConfigVehicle(&sVehConfigSig, ucModeConfigVhl);

    ucEtatMar = *ETAT_MAR;

    // Compute Reverse gear status
    sVehConfigSig.eEtatMar = (ucEtatMar != SIGPREP_RX_ZERO_VALUE) ? eEtatMar_Reverse : eEtatMar_Forward;
    break;

  case eFrmTimeOut:
    sVehConfigSig.eVehicleCfg  = eModeConfigVehicle_Client;
    sVehConfigSig.eEtatMar     = eEtatMar_Reverse;

    // Set Customer/Client value for DEH API
    eConfigMode = DAPI_E_MC_CUSTOMER;

    // Set DTC U0140-87 - HS6_DAT_VSM_3AE frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_3AE_ID, DEM_EVENT_STATUS_FAILED);

    // Set signal quality for RTE port as time-out
    sVehConfigSig.eSigQty = SIG_TIMEOUT;
    break;

  default:
    break;
  }

  // Update Config Mode in DEH module
  DAPI_SetConfigMode(eConfigMode);

  (void)Rte_Write_SigPrep_VehicleConfigSig(&sVehConfigSig);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DAT_VSM_54D
///
/// \descr Handling of 0x54D receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DAT_VSM_54D(teSigPrep_RxFrameState eSigPrepRxState)
{
  tsRte_OdometerTotal  sOdometerTotal = { 0 };
  uint32               ulRawOdometerTotal = 0u;
  STATIC_UT(boolean, boTimerStatus, FALSE);

  sOdometerTotal.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_OdometerTotal(&sOdometerTotal);

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sOdometerTotal.eSigQty = SIG_SNA;
    break;

  case eFrmEvent:
    // Clear DTC U1218-81 - HS6_DAT_VSM_54D frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_54D_ID, DEM_EVENT_STATUS_PASSED);

    ulRawOdometerTotal = (uint32)((uint32)(*KM_TOTAL) + (uint32)((uint32)*(KM_TOTAL + 1U) << 8U) + (uint32)((uint32)*(KM_TOTAL + 2U) << 16U));

    // Validate Odometer signal and quality factor
    if (ulRawOdometerTotal == SIGPREP_RX_INVALID_ODOMETER)
    {
      // Check 2 seconds for invalid data before setting SigQty to INVALID
      if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_KM_TOTAL_ID) == TRUE)
      {
        // Store Invalid Odometer Total value after 2 seconds debounce
        sOdometerTotal.eOdometerTotal.ulOdometerTotal = ulRawOdometerTotal;

        // Set signal quality for RTE port as invalid
        sOdometerTotal.eSigQty = SIG_INVALID;

        // Set DTC U1218-81 - KM_TOTAL invalid data
        Rte_Call_DemPrj_ReportErrorStatus((uint16)INVALID_DATA_54D, DEM_EVENT_STATUS_FAILED);
      };
    }
    else
    {
      // Reset Timer Status
      boTimerStatus = FALSE;

      // Store Odometer Total value
      sOdometerTotal.eOdometerTotal.ulOdometerTotal = ulRawOdometerTotal;

      // Set signal quality for RTE port as valid
      sOdometerTotal.eSigQty = SIG_VALID;

      // Clear DTC U1218-81 - KM_TOTAL invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)INVALID_DATA_54D, DEM_EVENT_STATUS_PASSED);
    }

    break;

  case eFrmTimeOut:
    // Set DTC U1218-81 - HS6_DAT_VSM_54D frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_54D_ID, DEM_EVENT_STATUS_FAILED);

    // Set signal quality for RTE port as time-out
    sOdometerTotal.eSigQty = SIG_TIMEOUT;
    break;

  default:
    break;
  }

  // Update the Mileage in the DEH module
  CMGT_SetMileage(sOdometerTotal.eOdometerTotal.ulOdometerTotal);

  (void)Rte_Write_SigPrep_OdometerTotal(&sOdometerTotal);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DAT4_V2_BSI_552
///
/// \descr Handling of 0x552 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DAT4_V2_BSI_552(teSigPrep_RxFrameState eSigPrepRxState)
{
  tsRte_VehTimeCntr  sVehTimeCntr = { 0 };
  uint32             ulRawVehTimeCntr = 0u;
  STATIC_UT(boolean, boTimerStatus, FALSE);

  sVehTimeCntr.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_VehTimeCntr(&sVehTimeCntr);

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sVehTimeCntr.eSigQty = SIG_SNA;
    break;

  case eFrmEvent:
    // Clear DTC U0140-87 - HS6_DAT4_V2_BSI_552 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT4_V2_BSI_552, DEM_EVENT_STATUS_PASSED);

    ulRawVehTimeCntr = (uint32)((uint32)(*CPT_TEMPOREL) + (uint32)((uint32)*(CPT_TEMPOREL + 1U) << 8U) + (uint32)((uint32)*(CPT_TEMPOREL + 2U) << 16U) + (uint32)((uint32)*(CPT_TEMPOREL + 3U) << 24U));

    // Check DTC for invalid data on CPT_TEMPOREL signal
    if (ulRawVehTimeCntr == SIGPREP_RX_INVALID_CPT_TEMPOREL)
    {
      // Check 2 seconds for invalid data before setting SigQty to INVALID
      if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_CPT_TEMPOREL_ID) == TRUE)
      {
        // Store Invalid Computer Temporel value after 2 seconds debounce
        sVehTimeCntr.eCompteurTemporelVehicule.ulCompteurTemporelVehicule = ulRawVehTimeCntr;

        // Set signal quality for RTE port as invalid
        sVehTimeCntr.eSigQty = SIG_INVALID;

        // Stop sending DEH frames
        DAPI_SetPermToSend(LDEH_E_SEND_NOTPERM);

        // Set DTC U1218-81 - CPT_TEMPOREL invalid data
        Rte_Call_DemPrj_ReportErrorStatus((uint16)CPT_TEMPOREL_INVALID_DATA_552, DEM_EVENT_STATUS_FAILED);
      };
    }
    else
    {
      // Reset Timer Status
      boTimerStatus = FALSE;

      // Store Computer Temporel value
      sVehTimeCntr.eCompteurTemporelVehicule.ulCompteurTemporelVehicule = ulRawVehTimeCntr;

      // Set signal quality for RTE port as valid
      sVehTimeCntr.eSigQty = SIG_VALID;

      // Check for unavailable value of CPT_TEMPOREL
      if (sVehTimeCntr.eCompteurTemporelVehicule.ulCompteurTemporelVehicule == SIGPREP_RX_UNAVAILABLE_CPT_TEMPOREL)
      {
        // Stop sending DEH frames
        DAPI_SetPermToSend(LDEH_E_SEND_NOTPERM);
      }
      else
      {
        // Restart sending DEH frames
        DAPI_SetPermToSend(LDEH_E_SEND_PERM);

        // [LDMO-4085] Bug fixed by moving API call from the end of the function , into inside of the Event Case
        // Update time information
        DAPI_SyncModule(sVehTimeCntr.eCompteurTemporelVehicule.ulCompteurTemporelVehicule);
      }

      // Clear DTC U1218-81 - CPT_TEMPOREL invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)CPT_TEMPOREL_INVALID_DATA_552, DEM_EVENT_STATUS_PASSED);
    }

    break;

  case eFrmTimeOut:
    // Set DTC U0140-87 - HS6_DAT4_V2_BSI_552 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT4_V2_BSI_552, DEM_EVENT_STATUS_FAILED);

    // Set signal quality for RTE port as time-out
    sVehTimeCntr.eSigQty = SIG_TIMEOUT;

    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_VehTimeCntr(&sVehTimeCntr);  // currently only internal usage in SigPrep. Is kept in RTE for possible future usage. LDMO-2121
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN3_CMM_468
///
/// \descr Handling of 0x468 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN3_CMM_468(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucEtatFee = 0u;

  tsRte_SigPrep_ElecSupState  sElecSupState = { 0 };
  tsRte_SysMon_VehNetState    sVehNetState  = { 0 };
  STATIC_UT(boolean, boTimerStatus, FALSE);

  sElecSupState.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_ElecSupState(&sElecSupState);
  (void)Rte_Read_SysMon_VehNetState(&sVehNetState);

  SigPrep_RxCallbacks_STTConfigDetection(eSigPrepRxState); // detect STT configuration

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sElecSupState.eSigQty = SIG_SNA;

    break;

  case eFrmEvent:
    // Reset DTC U160587 - HS6_DYN3_CMM_468 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN3_CMM_468_ID, DEM_EVENT_STATUS_PASSED);

    // Read CAN signal
    ucEtatFee = *ETAT_FEE;

    // Compute Status of the 12V electrical energy supply in by engine
    //switch (ucEtatFee)
    //{
    //  case 0u:  { sElecSupState.eElectrSupplyState = eEtatFee_1_1;     }  break;
    //  case 1u:  { sElecSupState.eElectrSupplyState = eEtatFee_1_2;     }  break;
    //  case 2u:  { sElecSupState.eElectrSupplyState = eEtatFee_1_3c;    }  break;
    //  case 3u:  { sElecSupState.eElectrSupplyState = eEtatFee_1_3r;    }  break;
    //  case 4u:  { sElecSupState.eElectrSupplyState = eEtatFee_2_1;     }  break;
    //  case 5u:  { sElecSupState.eElectrSupplyState = eEtatFee_3c_1;    }  break;
    //  case 6u:  { sElecSupState.eElectrSupplyState = eEtatFee_3r_1;    }  break;
    //  case 7u:  { sElecSupState.eElectrSupplyState = eEtatFee_4_1;     }  break;
    //  case 8u:  { sElecSupState.eElectrSupplyState = eEtatFee_5_5;     }  break;
    //  case 9u:  { sElecSupState.eElectrSupplyState = eEtatFee_1_3vr;   }  break;
    //  case 10u: { sElecSupState.eElectrSupplyState = eEtatFee_3vr_1;   }  break;
    //  default:  { sElecSupState.eElectrSupplyState = eEtatFee_Invalid; }  break;
    //}
    // Florin Onufiriciuc: Reduce cyc. complexity  by optimizing the type conversion of above
    if (ucEtatFee > 10U)
    {
      // Check 2 seconds for invalid data before setting SigQty to INVALID
      if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_ETAT_FEE_ID) == TRUE)
      {
        // Set signal quality for RTE port as invalid
        sElecSupState.eSigQty = SIG_INVALID;

        // Store invalid ETAT_FEE value
        sElecSupState.eElectrSupplyState = eEtatFee_Invalid;

        if (sVehNetState.eVESMainState != VESState_Stop)
        {
          // Set DTC U1208-81 - ETAT_FEE invalid data
          Rte_Call_DemPrj_ReportErrorStatus((uint16)ETAT_FEE_INVALID_DATA, DEM_EVENT_STATUS_FAILED);
        }
        else
        {
          // don't set the DTC because it is inhibited
        }
      };
    }
    else
    {
      // Reset Timer Status
      boTimerStatus = FALSE;

      //PRQA S 4342 1 // intended cast to enum of same type data
      sElecSupState.eElectrSupplyState = (teRte_EtatFee)ucEtatFee;

      // Set signal quality for RTE port as valid
      sElecSupState.eSigQty = SIG_VALID;

      //Reset DTC U1208-81 - ETAT_FEE invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)ETAT_FEE_INVALID_DATA, DEM_EVENT_STATUS_PASSED);
    }

    break;

  case eFrmTimeOut:
    sElecSupState.eElectrSupplyState = eEtatFee_Invalid;

    if ((NvmBlockDeltaPwmPara.eNVM_Function_STT == eOptionSTT_Present) && (sVehNetState.eVESMainState != VESState_Stop))
    {
        // Set DTC U160587 - HS6_DYN3_CMM_468 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN3_CMM_468_ID, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      // don't set the DTC if STT is not supported
    }

    // Set signal quality for RTE port as time-out
    sElecSupState.eSigQty = SIG_TIMEOUT;
    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_ElecSupState(&sElecSupState);
} // PRQA S 5336 1 // program architecture and readability


//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_STTConfigDetection
///
/// \descr Handling of NVM Configuration for STT function
///
/// \param  eSigPrepStateSTT: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void SigPrep_RxCallbacks_STTConfigDetection(teSigPrep_RxFrameState eSigPrepStateSTT)
{
  STATIC_UT(tsRte_SysMon_VehNetState, sVehNetState_Old, { 0 });
  tsRte_SysMon_VehNetState         sVehNetState_New = { 0 };

  STATIC_UT(boolean, boFrame468Check,      TRUE); // Check if time from configuration has passed
  STATIC_UT(boolean, boFrameReceived,     FALSE); // Flag used for detection of 468 frame
  STATIC_UT(boolean, boSTTAbsent,         FALSE); // Flag used for detection of STT function
  STATIC_UT(boolean, boSTTPresent,        FALSE); // Flag used for detection of STT function
  STATIC_UT(boolean, boIgnitionDetected,  FALSE); 

  static teFunctionSTT eLastSTTState  = eOptionSTT_Absent;
  teFunctionSTT eNewSTTState          = eOptionSTT_Absent;

  (void)Rte_Read_SysMon_VehNetState(&sVehNetState_New);  // Read ETAT_PRINCIP_SEV 
  
  // Detection during Ignition/Start
  if ((((sVehNetState_Old.eVESMainState == VESState_Stop) && ((sVehNetState_New.eVESMainState == VESState_Ignition) || (sVehNetState_New.eVESMainState == VESState_Start)) && (sVehNetState_New.eSigQty == SIG_VALID))) || (boIgnitionDetected != FALSE))
  {
    // Ignition was detected
    boIgnitionDetected = TRUE;

    if (boFrame468Check != FALSE)
    {
      // Start timer
      SigPrepRx_Callbacks_ulFrameStateSTT_us = TimerGetTick();
      // Invalidate flag so that we do not restart the timer
      boFrame468Check = FALSE;
    }
    else if (TimerGetTimeSince(SigPrepRx_Callbacks_ulFrameStateSTT_us) < UTILTIME_MSEC(SigPrepRx_GetConfigTime()))
    {
      // Check if Frame 0x468 is received
      if (eSigPrepStateSTT == eFrmEvent)
      {
        // Frame received
        boFrameReceived = TRUE;

        // Invalidate flag so that we stop the detection
        boIgnitionDetected = FALSE;
      }
      else
      {
        // do nothing
      }
    }
    else if (boFrameReceived == FALSE) // Frame 468 Not Received
    {
      boSTTAbsent = TRUE;

      // Invalidate flag so that we stop the detection
      boIgnitionDetected = FALSE;
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    // Validate flag so that the timer will be restarted at the next detection
    boFrame468Check = TRUE;
  }

  // Check if frame 0x468 is received even after autoconfiguration is complete
  if (eSigPrepStateSTT == eFrmEvent)
  {
    // Frame is received
    boSTTPresent = TRUE;
  }
  else
  {
    // do nothing
  }

  if ((boSTTPresent != FALSE) || (boSTTAbsent != FALSE))
  {
    if (boSTTPresent != FALSE) // Write in NVM that STT is present
    {
      // Set STT Config Present in NVM
      NvmBlockDeltaPwmPara.eNVM_Function_STT = eOptionSTT_Present;
      eNewSTTState                           = eOptionSTT_Present;
    }
    else 
    {
      // Set STT Config Absent in NVM
      NvmBlockDeltaPwmPara.eNVM_Function_STT = eOptionSTT_Absent;
      eNewSTTState                           = eOptionSTT_Absent;
    }

    if (eLastSTTState != eNewSTTState)
    {
      (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);
    }
    else
    {
      // do nothing
    }

    eLastSTTState = eNewSTTState;

    // Reset flags 
    boFrameReceived = FALSE;
    boSTTPresent    = FALSE;
    boSTTAbsent     = FALSE;
  }
  else
  {
    // do nothing
  }

  // Store previous value
  sVehNetState_Old = sVehNetState_New;
  //PRQA S 5310 1 // STPTH is exceeded due to program architecture and readability
}


//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_INTE_ELECTRON_BSI_092
///
/// \descr Handling of 0x92 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_INTE_ELECTRON_BSI_092(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8   ucEraseFailuresCode  = 0u;
  uint8   ucModeDiag           = 0u;
  uint8   ucDiagIntegraElec    = 0u;
  TE_Bool eEraseFailureCode    = E_FALSE;

  tsRte_ElecIntegra         sElecIntegra = { 0 };
  tsRte_SysMon_LifePhases   sLifePhases  = { 0 };
  tsRte_SysMon_VehicleSpeed sVehSpeed = { 0 };


  sElecIntegra.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_ElecIntegra(&sElecIntegra);
  (void)Rte_Read_SysMon_LifePhases(&sLifePhases);
  (void)Rte_Read_SysMon_VehicleSpeed(&sVehSpeed);

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sElecIntegra.eSigQty = SIG_SNA;
    break;

  case eFrmEvent:
    ucEraseFailuresCode = *EFFAC_DEFAUT_DIAG;
    ucModeDiag          = *MODE_DIAG;
    ucDiagIntegraElec   = *DIAG_INTEGRA_ELEC;

    eEraseFailureCode = (ucEraseFailuresCode != SIGPREP_RX_ZERO_VALUE) ? E_TRUE : E_FALSE;

    // Compute Erase failures code
    sElecIntegra.eEraseFailureCode = (ucEraseFailuresCode != SIGPREP_RX_ZERO_VALUE) ? eEffacDefautDiag_FaultMemoryErase : eEffacDefautDiag_NoAction;

    // Compute Diagnosis mode
    sElecIntegra.eDiagnosisMode = (ucModeDiag != SIGPREP_RX_ZERO_VALUE) ? eModeDiag_OpAndCommInhibited : eModeDiag_NoOp;

    // Compute Diagnosis for Electronic integration mode
    sElecIntegra.eDiagForElecIntegrationMode = (ucDiagIntegraElec != SIGPREP_RX_ZERO_VALUE) ? eDiagIntegraElec_NoFrameTransmission : eDiagIntegraElec_NoParticularOp;

    // Set signal quality for RTE port as valid
    sElecIntegra.eSigQty = SIG_VALID;
    break;

  case eFrmTimeOut:
    // Set signal quality for RTE port as time-out
    sElecIntegra.eSigQty = SIG_TIMEOUT;
    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_ElecIntegra(&sElecIntegra);  // currently only internal usage in SigPrep. Is kept in RTE for possible future usage. LDMO-2121
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN2_FRE_3CD
///
/// \descr Handling of 0x3CD receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN2_FRE_3CD(teSigPrep_RxFrameState eSigPrepRxState)
{
  tsRte_SigPrep_YawSpeed        sYawSpeed = { 0 };
  tsSigPrep_RxYawSpeedFrmCheck  sFrmYawSpeedInfo;
  uint16                        unYawSpeed = 0U;
  tsRte_SysMon_VehNetState  sVehNetState = { 0 };

  sYawSpeed.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_YawSpeed(&sYawSpeed);
  (void)Rte_Read_SysMon_VehNetState(&sVehNetState);

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sYawSpeed.eSigQty = SIG_SNA;

    // Reset DTC U111387 - frame lost -removed with v16 of DTC_LIST
    // Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN2_FRE_3CD_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U121381 - removed with LDMO-2753
    // Rte_Call_DemPrj_ReportErrorStatus((uint16)Yaw_rate_ID, DEM_EVENT_STATUS_PASSED); 
    break;

  case eFrmEvent:
    // Reset DTC U111387 - frame lost -removed with v16 of DTC_LIST
    // Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN2_FRE_3CD_ID, DEM_EVENT_STATUS_PASSED);

    // Read CAN signals
    unYawSpeed = (uint16)((uint16)(*VITESSE_LACET) + (uint16)((uint16)*(VITESSE_LACET + 1U) << 8U));

    sFrmYawSpeedInfo.unCylinderPressure = (uint16)((uint16)(*PRESSION_MAITRE_CYL) + (uint16)((uint16)*(PRESSION_MAITRE_CYL + 1U) << 8U));
    sFrmYawSpeedInfo.nYawSpeed          = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unYawSpeed, SIGPREP_RX_LENGTH_VITESSE_LACET);

    // Check signals range
    SigPrep_RxCallbacks_RangeCheck_YawSpeed(&sYawSpeed, sFrmYawSpeedInfo);

    break;

  case eFrmTimeOut:
    if (sVehNetState.eVESMainState != VESState_Stop)
    {
      // Set DTC U111387 - frame lost -removed with v16 of DTC_LIST
      //Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN2_FRE_3CD_ID, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      //don't set a DTC
    }

    // Set signal quality for RTE port as time-out
    sYawSpeed.eSigQty = SIG_TIMEOUT;
    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_YawSpeed(&sYawSpeed); // currently only internal usage in SigPrep. Is kept in RTE for possible future usage. LDMO-2121
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_BEMP_2B7_RX
///
/// \descr Handling of 0x2B7 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_BEMP_2B7_RX(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8   ucRCmdSignLvl  = 0u;
  uint8   ucRCmdRefLvl   = 0u;
  uint16  unRCmdPosLvl   = 0u;
  teRte_SigQty  eDblQty  = SIG_SNA;

  tsRte_LevellingTgtPos  sLvlTgtPos = { 0 };

  sLvlTgtPos.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_LevellingTgtPos(&sLvlTgtPos);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  uint8                           ucDynBendingBeamFaultL    = 0u;
  tsRte_BendingBeamFault_OtherHL  sBendingBeamFaultFromLeft = { 0 };

  sBendingBeamFaultFromLeft.eSigQty = SIG_INIT; // Initialise the structure

  (void)Rte_Read_SigPrepRx_Dbl_LeftStatus(&sBendingBeamFaultFromLeft);
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sLvlTgtPos.eSigQty = SIG_SNA;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    sBendingBeamFaultFromLeft.eSigQty = SIG_SNA;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
      break;

  case eFrmEvent:
    // Reset DTC U111F-87 - HS6_DYN_BEMP_2B7_RX frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN_BEMP_2B7_ID, DEM_EVENT_STATUS_PASSED);

    // Read CAN signals
    ucRCmdSignLvl = *SIGNE_CONSIGNE_SITE_D_RX;

    // Compute sign of ADL order for Right LDM
    sLvlTgtPos.eRCmdSignLvl = (ucRCmdSignLvl != SIGPREP_RX_ZERO_VALUE) ? eSigneConsigneSiteD_Negativ : eSigneConsigneSiteD_Positive;

    ucRCmdRefLvl = *CMD_REF_SITE_D_RX;

    // Compute referencing control of automatic levelling of Right LDM
    sLvlTgtPos.eRCmdRefLvl = (ucRCmdRefLvl != SIGPREP_RX_ZERO_VALUE) ? eCmdRefSiteD_Referencing : eCmdRefSiteD_NoReferencing;

    unRCmdPosLvl = (uint16)((uint16)(*CONSIGNE_SITE_D_RX) + (uint16)((uint16)*(CONSIGNE_SITE_D_RX + 1U) << 8U));

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    ucDynBendingBeamFaultL = *DYN_BENDING_BEAM_FAULT_L_RX;

    // Check DYN_BENDING_BEAM_FAULT_R_X signal range
    SigPrep_RxCallbacks_RangeCheck_DynBendBeamFault(&sBendingBeamFaultFromLeft, ucDynBendingBeamFaultL);

    // Set Signal Quality for DTC
    eDblQty = sBendingBeamFaultFromLeft.eSigQty;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

    // Check CONSIGNE_SITE_D_RX signal range
    SigPrep_RxCallbacks_RangeCheck_ConsigneSiteD(&sLvlTgtPos, unRCmdPosLvl);

    // Check invalid data DTC
    if ((sLvlTgtPos.eSigQty == SIG_INVALID) || (eDblQty == SIG_INVALID))
    {
      // Set DTC U12E0-81 - Command Position Levelling invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)INVALID_DATA_2B7, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      // Clear DTC U12E0-81 - Command Position Levelling invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)INVALID_DATA_2B7, DEM_EVENT_STATUS_PASSED);
    }

    break;

  case eFrmTimeOut:
    sLvlTgtPos.eRCmdRefLvl              = eCmdRefSiteD_NoReferencing;
    sLvlTgtPos.eRCmdPosLvl.unRCmdPosLvl = SIGPREP_RX_INVALID_CONSIGNE_SITE_D_MAX_VAL;

    // Set DTC U111F-87 - HS6_DYN_BEMP_2B7_RX frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN_BEMP_2B7_ID, DEM_EVENT_STATUS_FAILED);

    // Set signal quality for RTE port as time-out
    sLvlTgtPos.eSigQty = SIG_TIMEOUT;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    sBendingBeamFaultFromLeft.eSigQty = SIG_TIMEOUT;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_LevellingTgtPos(&sLvlTgtPos);
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  (void)Rte_Write_SigPrepRx_Dbl_LeftStatus(&sBendingBeamFaultFromLeft);
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
}



#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST) // Applicable only for ECO version
//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DIAG_DRVLED_R_477_RX
///
/// \descr Handling of 0x477 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DIAG_DRVLED_R_477_RX(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucDiagLvlR = 0u;

  tsRte_DcmDiagStatusR  sDcmDiagStatusR = { 0 };

  sDcmDiagStatusR.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_DcmDiagStatusR(&sDcmDiagStatusR);

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sDcmDiagStatusR.eSigQty = SIG_SNA;
    break;

  case eFrmEvent:
    ucDiagLvlR = *DIAG_LVL_R_RX;

    // Set Diagnostic status of DC Motor of Right LDM
    switch (ucDiagLvlR)
    {
      case SIGPREP_RX_DIAG_LVL_R_OK:  { sDcmDiagStatusR.eLevellingAdjustFaultR = eDiagLvl_Ok;  }  break;
      case SIGPREP_RX_DIAG_LVL_R_NOK: { sDcmDiagStatusR.eLevellingAdjustFaultR = eDiagLvl_Nok; }  break;
      default:                        { sDcmDiagStatusR.eLevellingAdjustFaultR = eDiagLvl_Nok; }  break;
    }

    // Set signal quality for RTE port as valid
    sDcmDiagStatusR.eSigQty = SIG_VALID;
    break;

  case eFrmTimeOut:
    sDcmDiagStatusR.eLevellingAdjustFaultR = eDiagLvl_Nok;

    // Set signal quality for RTE port as time-out
    sDcmDiagStatusR.eSigQty = SIG_TIMEOUT;
    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_DcmDiagStatusR(&sDcmDiagStatusR);
}
#endif



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_257
///
/// \descr Handling of 0x257 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_257(teSigPrep_RxFrameState eSigPrepRxState)
{
  tsRte_SigPrep_DynamicSigs        sDynamicSigs = { 0 };
  tsSigPrep_RxDynamicSigsFrmCheck  sFrmDynamicSigsInfo;
  tsRte_SysMon_VehNetState         sVehNetState = { 0 };
  uint8                            ucSteeringType = 0u;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  tsRte_SigPrep_SteeringWheelAngle sSteerAngleSig = { 0 };
  uint16                           unRawSteeringWheelAngle      = 0u;
  sint16                           nSignedRawSteeringWheelAngle = 0;

  boolean                          boDbl_Enable = Cod_Dbl_Enable();

  sSteerAngleSig.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_SteeringWheelAngle(&sSteerAngleSig);
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
  sDynamicSigs.eSigQty   = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_DynamicSigs(&sDynamicSigs);
  (void)Rte_Read_SysMon_VehNetState(&sVehNetState); //read ETAT_PRINCIP_SEV

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sDynamicSigs.eSigQty   = SIG_SNA;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    sSteerAngleSig.eSigQty = SIG_SNA;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

    break;

  case eFrmEvent:
      // Reset DTC U1105-87 - HS6_DYN_VSM_257 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN_VSM_257_ID, DEM_EVENT_STATUS_PASSED);

    // Read CAN signals
    sFrmDynamicSigsInfo.ucPedalAcceleration = *EFCMNT_PDLE_ACCEL;
    sFrmDynamicSigsInfo.ucBrakePressure     = *AUTO_BRAKING_PRESSURE;
    sFrmDynamicSigsInfo.ucDriverRequest     = *VOLONTE_COND;
    ucSteeringType                          = *TYPE_DIR;

    // Compute Hand drive side
    switch (ucSteeringType)
    {
      case 1u: { sFrmDynamicSigsInfo.eSteeringType = eTypeDir_SteeringRight; }  break;
      case 2u: { sFrmDynamicSigsInfo.eSteeringType = eTypeDir_SteeringLeft;  }  break;
      default: { sFrmDynamicSigsInfo.eSteeringType = eTypeDir_Invalid;       }  break;
    }
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    // Check if DBL option is present in Coding
    if (boDbl_Enable != FALSE)
    {
      unRawSteeringWheelAngle = (uint16)((uint16)(*STEER_WHEEL_ANGLE_CONF) + (uint16)((uint16)*(STEER_WHEEL_ANGLE_CONF + 1U) << 8U));

      // Convert Steering Wheel Angle from Unsigned to Signed 16 bit
      nSignedRawSteeringWheelAngle = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unRawSteeringWheelAngle, SIGPREP_RX_LENGTH_STEER_WHEEL_ANGLE);

      // Check Steering Wheel Angle signal range
      SigPrep_RxCallbacks_RangeCheck_SteeringWheel(&sSteerAngleSig, nSignedRawSteeringWheelAngle);
    }
    else
    {
      // nothing to do, DBL is inhibited
    }
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

    // Check signals range
    SigPrep_RxCallbacks_RangeCheck_DynamicSigs(&sDynamicSigs, sFrmDynamicSigsInfo);

    break;

  case eFrmTimeOut:
    // Set signal quality for RTE port as time-out
    sDynamicSigs.eSigQty   = SIG_TIMEOUT;

    // Set flow to invalid based on customer requirement REQ-0603446 A
    // Updated based on internal bug LDMO-4102
    sDynamicSigs.eSteeringType = eTypeDir_Invalid;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    sSteerAngleSig.eSigQty = SIG_TIMEOUT;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

    if (sVehNetState.eVESMainState != VESState_Stop)
    {
      // Set DTC U1105-87 - HS6_DYN_VSM_257 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN_VSM_257_ID, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      //do not set the DTC
    }
    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_DynamicSigs(&sDynamicSigs);
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // Check if DBL option is present in Coding
  if (boDbl_Enable == FALSE)
  {
    // Clear DTC U1218-81 - Steering Wheel Angle invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)STEER_WHEEL_ANGLE_INVALID_DATA_257, DEM_EVENT_STATUS_PASSED);
    // Inhibit the DBL value for Steering Wheel Angle
    sSteerAngleSig.nSteeringWheelAngle  = 0;
    sSteerAngleSig.eSigQty              = SIG_VALID;
  }
  else
  {
    // nothing to do
  }

  (void)Rte_Write_SigPrep_SteeringWheelAngle(&sSteerAngleSig);
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
}// PRQA S 5324 1 // Program architecture and readability



#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DAT_CSS_350
///
/// \descr Handling of 0x350 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DAT_CSS_350(teSigPrep_RxFrameState eSigPrepRxState)
{
  tsRte_SigPrep_VehiclePitchAngle  sVehPitchAngle = { 0 };
  tsRte_SigPrep_VehicleConfigSig   sVehConfigSig = { 0 };
  uint16                           unVehiclePitchAngle = 0U;
  sint16                           snVehiclePitchAngle = 0;
  tPitch0                          sPitchData = { 0 };
  tsRte_SysMon_VehNetState         sVehNetState = { 0 };

  // Check if ADL option is present in Coding
  if (Cod_AvacStp_Enable() != FALSE)
  {
    sVehConfigSig.eSigQty = SIG_INIT; //Initialise the structure
    sVehPitchAngle.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_VehicleConfigSig(&sVehConfigSig);
    (void)Rte_Read_SigPrep_VehiclePitchAngle(&sVehPitchAngle);
    (void)Rte_Read_SysMon_VehNetState(&sVehNetState); //read ETAT_PRINCIP_SEV

    // Detection only in PLANT or APV
    if (sVehConfigSig.eVehicleCfg == eModeConfigVehicle_Usine || sVehConfigSig.eVehicleCfg == eModeConfigVehicle_AfterMarket)
    {
      sPitchData = SigPrep_RxCallbacks_ConfigDetection(eSigPrepRxState); // Detect Leveling Configuration
    }
    else
    {
      // do nothing
    }

    if ((NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_Invalid) && (sVehConfigSig.eVehicleCfg == eModeConfigVehicle_Usine || sVehConfigSig.eVehicleCfg == eModeConfigVehicle_AfterMarket))
    {
      // Set DTC U1116-87 - HS6_DAT_CSS_350 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_CSS_350_ID, DEM_EVENT_STATUS_FAILED);
      // Set DTC C1155-15 - BHS front open circuit
      Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_OC, DEM_EVENT_STATUS_FAILED);
      // Set DTC C1155-15 - BHS rear open circuit
      Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_OC, DEM_EVENT_STATUS_FAILED);
    }
    else if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_Invalid)
    {
      // Set DTC U1116-87 - HS6_DAT_CSS_350 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_CSS_350_ID, DEM_EVENT_STATUS_PASSED);
      // Set DTC C1155-15 - BHS front open circuit
      Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_OC, DEM_EVENT_STATUS_PASSED);
      // Set DTC C1155-15 - BHS rear open circuit
      Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_OC, DEM_EVENT_STATUS_PASSED);
    }
    else
    {
      // do nothing
    }

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sVehPitchAngle.eSigQty = SIG_SNA;
      //Florin Onufricuc: it is wrong to set to pass a DTC for which you do not know if the signal is present or not
      // Reset DTC U111687 - frame lost
      //Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_CSS_350_ID, DEM_EVENT_STATUS_PASSED);
      // Reset DTC U121681
      //Rte_Call_DemPrj_ReportErrorStatus((uint16)Vehicle_attitude_ID, DEM_EVENT_STATUS_PASSED);
      break;

    case eFrmEvent:
      if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN)
      {
        // Reset DTC U1116-87 - HS6_DAT_CSS_350 frame lost
        Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_CSS_350_ID, DEM_EVENT_STATUS_PASSED);

        // Read CAN signal
        unVehiclePitchAngle = (uint16)((uint16)(*ASSIETTE_VEHICULE) + (uint16)((uint16)*(ASSIETTE_VEHICULE + 1U) << 8U));
        snVehiclePitchAngle = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unVehiclePitchAngle, SIGPREP_RX_LENGTH_ASSIETTE_VEHICULE);

        // Check VEHICLE_ATTITUDE signal range
        SigPrep_RxCallbacks_RangeCheck_VehicleAttitude(&sVehPitchAngle, snVehiclePitchAngle);
      }
      else
      {
        // do nothing
      }
      break;

    case eFrmTimeOut:

      // check HLS signal quality 
      if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN)
      {
        sVehPitchAngle.eAssietteVehicule.nVehiclePitchAngle = SIGPREP_RX_INVALID_ASSIETTE_VEHICULE;
        // Set signal quality for RTE port as time-out
        sVehPitchAngle.eSigQty = SIG_TIMEOUT;

        if (sVehNetState.eVESMainState != VESState_Stop)
        {
          // Set DTC U1116-87 - HS6_DAT_CSS_350 frame lost
          Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_CSS_350_ID, DEM_EVENT_STATUS_FAILED);
        }
        else
        {
          //do not set any DTC
        }
      }
      else if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_HLS)
      {
        sVehPitchAngle.eAssietteVehicule.nVehiclePitchAngle = sPitchData.nAngle;

        // Set DTC U1116-87 - HS6_DAT_CSS_350 frame lost
        Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_CSS_350_ID, DEM_EVENT_STATUS_PASSED);

        // Set signal quality for RTE port as time-out
        sVehPitchAngle.eSigQty = SIG_TIMEOUT;
      }
      else
      {
        sVehPitchAngle.eAssietteVehicule.nVehiclePitchAngle = SIGPREP_RX_INVALID_ASSIETTE_VEHICULE;

        // Set signal quality for RTE port as time-out
        sVehPitchAngle.eSigQty = SIG_TIMEOUT;
      }

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U111687 - 0x350 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_CSS_350_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U121681 - -0x350 invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)Vehicle_attitude_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC C115515 - BHS front open circuit
    Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_OC, DEM_EVENT_STATUS_PASSED);
    // Reset DTC C115515 - BHS rear open circuit
    Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_OC, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sVehPitchAngle.eAssietteVehicule.nVehiclePitchAngle  = 0;
    sVehPitchAngle.eSigQty                               = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_VehiclePitchAngle(&sVehPitchAngle);
} // PRQA S 5324, 5310, 5316, 5330, 5336 1 // HIS metrics 


//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_ConfigDetection
///
/// \descr Handling of NVM Configuration for leveling depending of Frame 0x350 frame
///        and signal quality of leveling sensors
///
/// \param  eSigPrep350State: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL tPitch0 SigPrep_RxCallbacks_ConfigDetection(teSigPrep_RxFrameState eSigPrep350State)
{
  STATIC_UT(tsRte_SysMon_VehNetState, sVehNetState_Old, { 0 });
  tsRte_SysMon_VehNetState            sVehNetState_New = { 0 };

  STATIC_UT(boolean, boFrame350Check,      TRUE); // Check if 1000 ms have passed
  STATIC_UT(boolean, boIgnitionDetected,  FALSE);
  STATIC_UT(boolean, boFrameReceived,     FALSE); // Flag used for detection of 350 frame
  STATIC_UT(boolean, boInputCAN,          FALSE); // Flag used for detection of CAN config
  STATIC_UT(boolean, boInputBHS,          FALSE); // Flag used for detection of BHS config
  STATIC_UT(boolean, boInputINVALID,      FALSE); // Flag used for detection of INVALID config

  tPitch0 sPitchData = { 0 };

  (void)Rte_Read_Pitch_Angle(&sPitchData);               // Read HLS Data from Pitch
  (void)Rte_Read_SysMon_VehNetState(&sVehNetState_New);  // Read ETAT_PRINCIP_SEV 

  
  // Detection during Ignition/Start
  if ((((sVehNetState_Old.eVESMainState == VESState_Stop) && ((sVehNetState_New.eVESMainState == VESState_Ignition) || (sVehNetState_New.eVESMainState == VESState_Start)) && (sVehNetState_New.eSigQty == SIG_VALID))) || (boIgnitionDetected != FALSE))
  {
    // Ignition was detected
    boIgnitionDetected = TRUE;

    if ((NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN) || (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_Invalid) || (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_HLS))
    {
      if (boFrame350Check != FALSE)
      {
        // Start timer
        SigPrepRx_Callbacks_ulFrameState_us = TimerGetTick();
        // Invalidate flag so that we do not restart the timer
        boFrame350Check = FALSE;
      }
      else if (TimerGetTimeSince(SigPrepRx_Callbacks_ulFrameState_us) < UTILTIME_MSEC(SigPrepRx_GetConfigTime()))
      {
        // Check if Frame 0x350 is received
        if (eSigPrep350State == eFrmEvent)
        {
          // Frame received
          boInputCAN = TRUE;
          boFrameReceived = TRUE;

          // Invalidate flag so that we stop the detection
          boIgnitionDetected = FALSE;

          if (NvmBlockDeltaPwmPara.eZeroLevProgInput == eInput_HLS)
          {
            // Delete zero level programming
            NvmBlockDeltaPwmPara.ucZeroLevProg &= 0x00u;
            NvmBlockDeltaPwmPara.snVehicleAttitude = 0;
            NvmBlockDeltaPwmPara.eZeroLevProgInput = eInput_Invalid;
          }
        }
        else
        {
          // do nothing
        }
      }
      else if (boFrameReceived == FALSE) // Frame 350 Not Received
      {
        // Set Flag for INVALID Config 
        boInputINVALID = TRUE;

        // Invalidate flag so that we stop the detection
        boIgnitionDetected = FALSE;
      }
      else
      {
        // do nothing
      }

      // Check if Leveling Sensors are available and no Electrical Errors are present
      if ((eSigPrep350State != eFrmEvent) &&
        (NvmBlockDeltaPwmPara.ucSensGndError[0u] == 0u && NvmBlockDeltaPwmPara.ucSensVbatError[0u] == 0u) &&
        (NvmBlockDeltaPwmPara.ucSensGndError[1u] == 0u && NvmBlockDeltaPwmPara.ucSensVbatError[1u] == 0u))
      {
        // Set Flag for BHS Config
        boInputBHS = TRUE;

        // Invalidate flag so that we stop the detection
        boIgnitionDetected = FALSE;

        if (NvmBlockDeltaPwmPara.eZeroLevProgInput == eInput_CAN)
        {
          // Delete zero level programming
          NvmBlockDeltaPwmPara.ucZeroLevProg &= 0x00u;
          NvmBlockDeltaPwmPara.snVehicleAttitude = 0;
          NvmBlockDeltaPwmPara.eZeroLevProgInput = eInput_Invalid;
        }
        else
        {
          // do nothing
        }
      }
      else
      {
        // do nothing
      }
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    // Validate flag so that the timer will be restarted at the next detection
    boFrame350Check = TRUE;
  }


  // Check if Frame 0x350 is received
  if ((eSigPrep350State == eFrmEvent) && (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_HLS))
  {
    // Frame received
    boInputCAN = TRUE;

    // Delete zero level programming
    NvmBlockDeltaPwmPara.ucZeroLevProg &= 0x00u;
    NvmBlockDeltaPwmPara.snVehicleAttitude = 0;
    NvmBlockDeltaPwmPara.eZeroLevProgInput = eInput_Invalid;
  }
  else
  {
    // do nothing
  }

  // Write in NVM config state
  if ((boInputCAN != FALSE) || (boInputBHS != FALSE) || (boInputINVALID != FALSE))
  {
    if (boInputCAN != FALSE) // CAN has highest priority
    {
      // Set CAN Config in NVM
      NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;
    }
    else if (boInputBHS != FALSE) // BHS has second highest priority
    {
      // Set BHS Config in NVM
      NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
    }
    else
    {
      // Set INVALID Config in NVM
      NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_Invalid;
    }

    // Reset flags 
    boFrameReceived = FALSE;
    boInputCAN      = FALSE;
    boInputBHS      = FALSE;
    boInputINVALID  = FALSE;

   (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);
  }
  else
  {
    // do nothing
  }


  // Store previous value
  sVehNetState_Old = sVehNetState_New;

  return sPitchData;
} // PRQA S 5336, 5310 1 // HIS metrics 


//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DAT_DRVLED_R_297_RX
///
/// \descr Handling of 0x297 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DAT_DRVLED_R_297_RX(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8   ucRPosSignLvl          = 0u;
  uint8   ucDynBendingBeamFaultR = 0u;
  uint16  unRPosLvl              = 0u;

  tsRte_LevellingFeedback         sLvlFeedback                = { 0 };
  tsRte_BendingBeamFault_OtherHL  sBendingBeamFaultFromRight  = { 0 };

  sLvlFeedback.eSigQty                = SIG_INIT; //Initialise the structure
  sBendingBeamFaultFromRight.eSigQty  = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_LevellingFeedback(&sLvlFeedback);
  (void)Rte_Read_SigPrepRx_Dbl_RightStatus(&sBendingBeamFaultFromRight);

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sLvlFeedback.eSigQty                = SIG_SNA;
    sBendingBeamFaultFromRight.eSigQty  = SIG_SNA;

    break;

  case eFrmEvent:
    // Reset DTC U111E-87 - HS6_DAT_DRVLED_R_297 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_DRVLED_R_297_ID, DEM_EVENT_STATUS_PASSED);

    // Read CAN signals
    ucRPosSignLvl           = *SIGN_POS_LVL_R_RX;
    ucDynBendingBeamFaultR  = *DYN_BENDING_BEAM_FAULT_R_RX;
    unRPosLvl               = (uint16)((uint16)(*POSITION_SITE_D_RX) + (uint16)((uint16)*(POSITION_SITE_D_RX + 1U) << 8U));

    // Compute Sign of lighting level Right
    sLvlFeedback.eRPosSignLvl = (ucRPosSignLvl != SIGPREP_RX_ZERO_VALUE) ? eSIGNPOSLVLR_Negative : eSIGNPOSLVLR_Positiv;

    // Check CONSIGNE_SITE_D_RX signal range
    SigPrep_RxCallbacks_RangeCheck_PositionSiteD(&sLvlFeedback, unRPosLvl);

    // Check DYN_BENDING_BEAM_FAULT_R_X signal range
    SigPrep_RxCallbacks_RangeCheck_DynBendBeamFault(&sBendingBeamFaultFromRight, ucDynBendingBeamFaultR);

    // Check invalid data DTC
    if ((sLvlFeedback.eSigQty == SIG_INVALID) || (sBendingBeamFaultFromRight.eSigQty == SIG_INVALID))
    {
      // Set DTC U12E3-81 - DBL/VAC invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VacPos_DBLErr_INVALID_DATA, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      // Clear DTC U12E3-81 - DBL/VAC invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VacPos_DBLErr_INVALID_DATA, DEM_EVENT_STATUS_PASSED);
    }

    break;

  case eFrmTimeOut:
    sLvlFeedback.eRPosSignLvl              = eSIGNPOSLVLR_Negative;
    sLvlFeedback.ePositionSiteD.unRPosLvl  = SIGPREP_RX_INVALID_POSITION_SITE_D;

    // Set signal quality for RTE port as time-out
    sLvlFeedback.eSigQty                = SIG_TIMEOUT;
    sBendingBeamFaultFromRight.eSigQty  = SIG_TIMEOUT;

    // Set DTC U111E-87 - HS6_DAT_DRVLED_R_297 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_DRVLED_R_297_ID, DEM_EVENT_STATUS_FAILED);

    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_LevellingFeedback(&sLvlFeedback);
  (void)Rte_Write_SigPrepRx_Dbl_RightStatus(&sBendingBeamFaultFromRight);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DAT2_DRVLED_R_4D7_RX
///
/// \descr Handling of 0x4D7 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DAT2_DRVLED_R_4D7_RX(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucLvlElecR         = 0u;
  uint8  ucLvlTemperatureR  = 0u;
  uint8  ucLvlSteplossR     = 0u;
  uint8  ucLvlRefStateR     = 0u;
  uint8  ucLvlVoltR         = 0u;

  teLvlRefStateR             eLevelRefState = eLvlRefStateR_WaitingForNewRefCmd;
  tsRte_LevellingDiagStatus  sLvlDiagStatus = { 0 };

  // Check if ADL option is present in Coding
  if (Cod_AvacStp_Enable() != FALSE)
  {
    sLvlDiagStatus.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_LevellingDiagStatus(&sLvlDiagStatus);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sLvlDiagStatus.eSigQty = SIG_SNA;
      break;

    case eFrmEvent:
      // Reset DTC U1FE3-87 - HS6_DAT2_DRVLED_R_4D7 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_DRVLED_R_4D7_ID, DEM_EVENT_STATUS_PASSED);

      ucLvlElecR = *LVL_ELEC_R_RX;

      // Compute Electric status of levelling stepper of Right LDM
      switch (ucLvlElecR)
      {
      case 0u: { sLvlDiagStatus.eLvlElecR = eLvlElecR_NoDefect;     }  break;
      case 1u: { sLvlDiagStatus.eLvlElecR = eLvlElecR_OpenCircuit;  }  break;
      case 2u: { sLvlDiagStatus.eLvlElecR = eLvlElecR_ShortCircuit; }  break;
      default: { sLvlDiagStatus.eLvlElecR = eLvlElecR_Reserved;     }  break;
      }

      ucLvlTemperatureR = *LVL_TEMPERATURE_R_RX;

      // Compute Temperature status of levelling stepper of Right LDM
      switch (ucLvlTemperatureR)
      {
      case 0u: { sLvlDiagStatus.eLvlTemperatureR = eLvlTemperatureR_NoWarning;               }  break;
      case 1u: { sLvlDiagStatus.eLvlTemperatureR = eLvlTemperatureR_ColdTemperature;         }  break;
      case 2u: { sLvlDiagStatus.eLvlTemperatureR = eLvlTemperatureR_HighTemperatureWarning;  }  break;
      default: { sLvlDiagStatus.eLvlTemperatureR = eLvlTemperatureR_HighTemperatureShutdown; }  break;
      }

      ucLvlSteplossR = *LVL_STEPLOSS_R_RX;

      // Compute Step loss status of levelling stepper of Right LDM
      sLvlDiagStatus.eLvlSteplossR = (ucLvlSteplossR != SIGPREP_RX_ZERO_VALUE) ? eLvlSteplossR_SteplossRisk : eLvlSteplossR_NoSteploss;

      ucLvlRefStateR = *LVL_REF_STATE_R_RX;

      // Compute Referencing status of levelling stepper of Right LDM
      switch (ucLvlRefStateR)
      {
        case 0u: { eLevelRefState = eLvlRefStateR_WaitingForNewRefCmd;  }  break;
        case 1u: { eLevelRefState = eLvlRefStateR_RefInProgress;        }  break;
        case 2u: { eLevelRefState = eLvlRefStateR_SuccessfullyFinished; }  break;
        default: { eLevelRefState = eLvlRefStateR_Invalid;              }  break;
      }

      ucLvlVoltR = *LVL_VOLT_R_RX;

      // Compute Voltage status of right levelling stepper
      switch (ucLvlVoltR)
      {
      case 0u: { sLvlDiagStatus.eLvlVoltR = eLvlVoltR_NominalVoltage; }  break;
      case 1u: { sLvlDiagStatus.eLvlVoltR = eLvlVoltR_UnderVoltage;   }  break;
      case 2u: { sLvlDiagStatus.eLvlVoltR = eLvlVoltR_NotUsed;        }  break;
      default: { sLvlDiagStatus.eLvlVoltR = eLvlVoltR_OverVoltage;    }  break;
      }

      // Check Levelling Reference State signal range
      SigPrep_RxCallbacks_RangeCheck_LevellingRight(&sLvlDiagStatus, eLevelRefState);

      break;

    case eFrmTimeOut:
      sLvlDiagStatus.eLvlElecR         = eLvlElecR_Reserved;
      sLvlDiagStatus.eLvlTemperatureR  = eLvlTemperatureR_HighTemperatureShutdown;
      sLvlDiagStatus.eLvlSteplossR     = eLvlSteplossR_SteplossRisk;
      sLvlDiagStatus.eLvlRefStateR     = eLvlRefStateR_Invalid;
      sLvlDiagStatus.eLvlVoltR         = eLvlVoltR_OverVoltage;

      // Set signal quality for RTE port as time-out
      sLvlDiagStatus.eSigQty = SIG_TIMEOUT;

      // Set DTC U1FE3-87 - HS6_DAT2_DRVLED_R_4D7 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_DRVLED_R_4D7_ID, DEM_EVENT_STATUS_FAILED);
      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FE387 - frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_DRVLED_R_4D7_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U12E381 - invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)INVALID_DATA_4D7, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sLvlDiagStatus.eLvlElecR         = eLvlElecR_NoDefect;
    sLvlDiagStatus.eLvlTemperatureR  = eLvlTemperatureR_NoWarning;
    sLvlDiagStatus.eLvlSteplossR     = eLvlSteplossR_NoSteploss;
    sLvlDiagStatus.eLvlRefStateR     = eLvlRefStateR_WaitingForNewRefCmd;
    sLvlDiagStatus.eLvlVoltR         = eLvlVoltR_NominalVoltage;
    sLvlDiagStatus.eSigQty           = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_LevellingDiagStatus(&sLvlDiagStatus);
} // PRQA S 5310, 5316, 5330 1 // program architecture and readability



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_28E
///
/// \descr Handling of 0x28E receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_28E(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint16                          unVehiclePathCurv = 0U;
  sint16                          nVehiclePathCurv  = 0;
  tsRte_SigPrep_VehPathCurvature  sVehPathCurv      = { 0 };
  tsRte_SysMon_VehNetState        sVehNetState      = { 0 };

  boolean  boDbl_Enable     = Cod_Dbl_Enable();
  boolean  boCurvatureMode  = Cod_CurvatureMode();

  // Check if Vehicle Curvature Path is present in Coding
  if ((boDbl_Enable != FALSE) && (boCurvatureMode == FALSE))
  {
    sVehPathCurv.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_VehPathCurvature(&sVehPathCurv);
    (void)Rte_Read_SysMon_VehNetState(&sVehNetState);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sVehPathCurv.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1113-87 - HS6_DYN_VSM_28E frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN_VSM_28E_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signal
      unVehiclePathCurv = (uint16)((uint16)(*VEH_PATH_CURVATURE) + (uint16)((uint16)*(VEH_PATH_CURVATURE + 1U) << 8U));
      nVehiclePathCurv  = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unVehiclePathCurv, SIGPREP_RX_LENGTH_VEH_PATH_CURVATURE);

      // Check VEH_PATH_CURVATURE signal range
      SigPrep_RxCallbacks_RangeCheck_VehiclePathCurvature(&sVehPathCurv, nVehiclePathCurv);

      break;

    case eFrmTimeOut:
      sVehPathCurv.eVehiclePathCurvature.nVehiclePathCurvature = SIGPREP_RX_INVALID_VEH_PATH_CURVATURE;

      // Set signal quality for RTE port as time-out
      sVehPathCurv.eSigQty = SIG_TIMEOUT;

      if (sVehNetState.eVESMainState != VESState_Stop)
      {
        // Reset DTC U1113-87 - HS6_DYN_VSM_28E frame lost
        Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN_VSM_28E_ID, DEM_EVENT_STATUS_FAILED);
      }
      else
      {
        // don't set the DTC because it is inhibited
      }

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U111387 - 0x28E frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN_VSM_28E_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U121381 - invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)DBL_28E_INVALID_DATA, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sVehPathCurv.eVehiclePathCurvature.nVehiclePathCurvature  = 0;
    sVehPathCurv.eSigQty                                      = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_VehPathCurvature(&sVehPathCurv);
} // PRQA S 5324 1 // Readability



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DAT_VSM_32E
///
/// \descr Handling of 0x32E receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DAT_VSM_32E(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucStaticBendingBeamCmd = 0u;
  uint8  ucCorneringBeamCmd     = 0u;

  tsRte_SigPrepLgtClSblReq  sLgtClSblReq  = { 0 };
  teRte_MountingSide        eMountingSide = { 0 };

  sLgtClSblReq.eSigQty = SIG_INIT; //Initialise the structure

  // Get headlamp mounting side
  eMountingSide = SigPrepRx_GetMountingSide();

  (void)Rte_Read_SigPrep_StdLgtClSbl_Req(&sLgtClSblReq);

  switch (eSigPrepRxState)
  {
  case eFrameInit:
    // Set signal quality for RTE port as SNA
    sLgtClSblReq.eSigQty = SIG_SNA;
    break;

  case eFrmEvent:
    // Reset DTC U0140-87 - HS6_DAT_VSM_32E frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_32E_ID, DEM_EVENT_STATUS_PASSED);

    // Read CAN signals
    ucStaticBendingBeamCmd  = (eMountingSide != eMountedRight) ? *CTRL_SBL_L : *CTRL_SBL_R;
    ucCorneringBeamCmd      = (eMountingSide != eMountedRight) ? *CTRL_CL_L : *CTRL_CL_R;

    sLgtClSblReq.eSbl_Request = (ucStaticBendingBeamCmd != SIGPREP_RX_ZERO_VALUE) ? ReqLighted_On : ReqLighted_Off;
    sLgtClSblReq.eCl_Request  = (ucCorneringBeamCmd     != SIGPREP_RX_ZERO_VALUE) ? ReqLighted_On : ReqLighted_Off;

    // Set signal quality for RTE port as valid
    sLgtClSblReq.eSigQty = SIG_VALID;
    break;

  case eFrmTimeOut:
    sLgtClSblReq.eSbl_Request = ReqLighted_Off;
    sLgtClSblReq.eCl_Request  = ReqLighted_Off;

    // Set signal quality for RTE port as time-out
    sLgtClSblReq.eSigQty = SIG_TIMEOUT;

    // Set DTC U0140-87 - HS6_DAT_VSM_32E frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_32E_ID, DEM_EVENT_STATUS_FAILED);
    break;

  default:
    break;
  }

  (void)Rte_Write_SigPrep_StdLgtClSbl_Req(&sLgtClSblReq);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DAT7_BSI_612
///
/// \descr Handling of 0x612 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DAT7_BSI_612(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucDblInhibition = 0u;

  tsRte_SigPrep_EnvCondition  sEnvConditions = { 0 };

  // Check if DBL option is present in Coding
  if (Cod_Dbl_Enable() != FALSE)
  {
    sEnvConditions.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_EnvCondition(&sEnvConditions);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sEnvConditions.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U0140-87 - HS6_DAT7_BSI_612 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT7_BSI_612_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signal
      ucDblInhibition = *INH_ECLAIRAGE_VIRAGE_DYN;

      // Compute Dynamic curve lighting inhibition
      sEnvConditions.eDblInhibition = (ucDblInhibition != SIGPREP_RX_ZERO_VALUE) ? eInhEclairageVirageDyn_Inhibition : eInhEclairageVirageDyn_NoInhibition;

      // Set signal quality for RTE port as valid
      sEnvConditions.eSigQty = SIG_VALID;
      break;

    case eFrmTimeOut:
      sEnvConditions.eDblInhibition = eInhEclairageVirageDyn_Inhibition;

      // Set signal quality for RTE port as time-out
      sEnvConditions.eSigQty = SIG_TIMEOUT;

      // Set DTC U0140-87 - HS6_DAT7_BSI_612 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT7_BSI_612_ID, DEM_EVENT_STATUS_FAILED);
      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U014087 - frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT7_BSI_612_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sEnvConditions.eDblInhibition = eInhEclairageVirageDyn_NoInhibition;
    // Set signal quality for RTE port as valid
    sEnvConditions.eSigQty        = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_EnvCondition(&sEnvConditions);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_0AB
///
/// \descr Handling of 0xAB receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_0AB(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint16  unLeftAngle   = 0U;
  uint16  unRightAngle  = 0U;
  uint16  unTopAngle    = 0U;
  uint16  unBottomAngle = 0U;

  tsRte_SigPrep_PerceiveSigGroup1_sVal  sPerceiveSigGroup1 = { 0 };

  // Check if TSAG option is present in Coding
  if (Cod_TSAG_Enable() != FALSE)
  {
    sPerceiveSigGroup1.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00(&sPerceiveSigGroup1);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sPerceiveSigGroup1.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_0AB frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0AB_ID, DEM_EVENT_STATUS_PASSED);
      // Read CAN signals
      unLeftAngle    = (uint16)((uint16)(*PERCEIVERFL_1_LEFTANGLE) + (uint16)((uint16)*(PERCEIVERFL_1_LEFTANGLE + 1U) << 8U));
      unRightAngle   = (uint16)((uint16)(*PERCEIVERFL_1_RIGHTANGLE) + (uint16)((uint16)*(PERCEIVERFL_1_RIGHTANGLE + 1U) << 8U));
      unTopAngle     = (uint16)((uint16)(*PERCEIVERFL_1_TOPANGLE) + (uint16)((uint16)*(PERCEIVERFL_1_TOPANGLE + 1U) << 8U));
      unBottomAngle  = (uint16)((uint16)(*PERCEIVERFL_1_BOTTOMANGLE) + (uint16)((uint16)*(PERCEIVERFL_1_BOTTOMANGLE + 1U) << 8U));

      sPerceiveSigGroup1.eBrightness.ucBrightness   = *PERCEIVERFL_1_BRIGHTNESS;
      sPerceiveSigGroup1.eLeftAngle.nLeftAngle      = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unLeftAngle, SIGPREP_RX_LENGTH_PERCEIVE_L_R_ANGLE);
      sPerceiveSigGroup1.eRightAngle.nRightAngle    = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unRightAngle, SIGPREP_RX_LENGTH_PERCEIVE_L_R_ANGLE);
      sPerceiveSigGroup1.eTopAngle.nTopAngle        = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unTopAngle, SIGPREP_RX_LENGTH_PERCEIVE_T_B_ANGLE);
      sPerceiveSigGroup1.eBottomAngle.nBottomAngle  = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unBottomAngle, SIGPREP_RX_LENGTH_PERCEIVE_T_B_ANGLE);
      sPerceiveSigGroup1.eDistance.unDistance       = (uint16)((uint16)(*PERCEIVERFL_1_DISTANCE) + (uint16)((uint16)*(PERCEIVERFL_1_DISTANCE + 1U) << 8U));

      // Set signal quality for RTE port as valid
      sPerceiveSigGroup1.eSigQty = SIG_VALID;

      break;

    case eFrmTimeOut:
      sPerceiveSigGroup1.eBrightness.ucBrightness   = SIGPREP_RX_INVALID_PERCEIVERFL_X_BRIGHTNESS;
      sPerceiveSigGroup1.eLeftAngle.nLeftAngle      = SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE;
      sPerceiveSigGroup1.eRightAngle.nRightAngle    = SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE;
      sPerceiveSigGroup1.eTopAngle.nTopAngle        = SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE;
      sPerceiveSigGroup1.eBottomAngle.nBottomAngle  = SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE;
      sPerceiveSigGroup1.eDistance.unDistance       = SIGPREP_RX_INVALID_PERCEIVERFL_X_DISTANCE;

      // Set signal quality for RTE port as time-out
      sPerceiveSigGroup1.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_0AB frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0AB_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC 1FC587 - 0xAB frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0AB_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B-81 - 0xAB invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_0AB_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sPerceiveSigGroup1.eBrightness.ucBrightness   = 0u;
    sPerceiveSigGroup1.eLeftAngle.nLeftAngle      = 0;
    sPerceiveSigGroup1.eRightAngle.nRightAngle    = 0;
    sPerceiveSigGroup1.eTopAngle.nTopAngle        = 0;
    sPerceiveSigGroup1.eBottomAngle.nBottomAngle  = 0;
    sPerceiveSigGroup1.eDistance.unDistance       = 0u;
    sPerceiveSigGroup1.eSigQty                    = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_PerceiveSigGroup1_sVal_00(&sPerceiveSigGroup1);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_0C3
///
/// \descr Handling of 0xC3 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_0C3(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint16  unLeftAngle   = 0U;
  uint16  unRightAngle  = 0U;
  uint16  unTopAngle    = 0U;
  uint16  unBottomAngle = 0U;

  tsRte_SigPrep_PerceiveSigGroup1_sVal  sPerceiveSigGroup1 = { 0 };

  // Check if TSAG option is present in Coding
  if (Cod_TSAG_Enable() != FALSE)
  {
    (void)Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01(&sPerceiveSigGroup1);

    sPerceiveSigGroup1.eSigQty = SIG_INIT; //Initialise the structure

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sPerceiveSigGroup1.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_0C3 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0C3_ID, DEM_EVENT_STATUS_PASSED);
      // Read CAN signals
      unLeftAngle    = (uint16)((uint16)(*PERCEIVERFL_2_LEFTANGLE) + (uint16)((uint16)*(PERCEIVERFL_2_LEFTANGLE + 1U) << 8U));
      unRightAngle   = (uint16)((uint16)(*PERCEIVERFL_2_RIGHTANGLE) + (uint16)((uint16)*(PERCEIVERFL_2_RIGHTANGLE + 1U) << 8U));
      unTopAngle     = (uint16)((uint16)(*PERCEIVERFL_2_TOPANGLE) + (uint16)((uint16)*(PERCEIVERFL_2_TOPANGLE + 1U) << 8U));
      unBottomAngle  = (uint16)((uint16)(*PERCEIVERFL_2_BOTTOMANGLE) + (uint16)((uint16)*(PERCEIVERFL_2_BOTTOMANGLE + 1U) << 8U));

      sPerceiveSigGroup1.eBrightness.ucBrightness   = *PERCEIVERFL_2_BRIGHTNESS;
      sPerceiveSigGroup1.eLeftAngle.nLeftAngle      = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unLeftAngle, SIGPREP_RX_LENGTH_PERCEIVE_L_R_ANGLE);
      sPerceiveSigGroup1.eRightAngle.nRightAngle    = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unRightAngle, SIGPREP_RX_LENGTH_PERCEIVE_L_R_ANGLE);
      sPerceiveSigGroup1.eTopAngle.nTopAngle        = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unTopAngle, SIGPREP_RX_LENGTH_PERCEIVE_T_B_ANGLE);
      sPerceiveSigGroup1.eBottomAngle.nBottomAngle  = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unBottomAngle, SIGPREP_RX_LENGTH_PERCEIVE_T_B_ANGLE);
      sPerceiveSigGroup1.eDistance.unDistance       = (uint16)((uint16)(*PERCEIVERFL_2_DISTANCE) + (uint16)((uint16)*(PERCEIVERFL_2_DISTANCE + 1U) << 8U));
      
      // Set signal quality for RTE port as valid
      sPerceiveSigGroup1.eSigQty = SIG_VALID;
      
      break;

    case eFrmTimeOut:
      sPerceiveSigGroup1.eBrightness.ucBrightness   = SIGPREP_RX_INVALID_PERCEIVERFL_X_BRIGHTNESS;
      sPerceiveSigGroup1.eLeftAngle.nLeftAngle      = SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE;
      sPerceiveSigGroup1.eRightAngle.nRightAngle    = SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE;
      sPerceiveSigGroup1.eTopAngle.nTopAngle        = SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE;
      sPerceiveSigGroup1.eBottomAngle.nBottomAngle  = SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE;
      sPerceiveSigGroup1.eDistance.unDistance       = SIGPREP_RX_INVALID_PERCEIVERFL_X_DISTANCE;

      // Set signal quality for RTE port as time-out
      sPerceiveSigGroup1.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_0C3 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0C3_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC 1FC587 - 0xC3 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0C3_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B-81 - 0xC3 invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_0C3_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sPerceiveSigGroup1.eBrightness.ucBrightness   = 0u;
    sPerceiveSigGroup1.eLeftAngle.nLeftAngle      = 0;
    sPerceiveSigGroup1.eRightAngle.nRightAngle    = 0;
    sPerceiveSigGroup1.eTopAngle.nTopAngle        = 0;
    sPerceiveSigGroup1.eBottomAngle.nBottomAngle  = 0;
    sPerceiveSigGroup1.eDistance.unDistance       = 0u;
    sPerceiveSigGroup1.eSigQty                    = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_PerceiveSigGroup1_sVal_01(&sPerceiveSigGroup1);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_0CB
///
/// \descr Handling of 0xCB receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_0CB(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint16  unLeftAngle   = 0U;
  uint16  unRightAngle  = 0U;
  uint16  unTopAngle    = 0U;
  uint16  unBottomAngle = 0U;

  tsRte_SigPrep_PerceiveSigGroup1_sVal  sPerceiveSigGroup1 = { 0 };

  // Check if TSAG option is present in Coding
  if (Cod_TSAG_Enable() != FALSE)
  {
    (void)Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02(&sPerceiveSigGroup1);

    sPerceiveSigGroup1.eSigQty = SIG_INIT; //Initialise the structure

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sPerceiveSigGroup1.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_0CB frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0CB_ID, DEM_EVENT_STATUS_PASSED);
      // Read CAN signals
      unLeftAngle    = (uint16)((uint16)(*PERCEIVERFL_3_LEFTANGLE) + (uint16)((uint16)*(PERCEIVERFL_3_LEFTANGLE + 1U) << 8U));
      unRightAngle   = (uint16)((uint16)(*PERCEIVERFL_3_RIGHTANGLE) + (uint16)((uint16)*(PERCEIVERFL_3_RIGHTANGLE + 1U) << 8U));
      unTopAngle     = (uint16)((uint16)(*PERCEIVERFL_3_TOPANGLE) + (uint16)((uint16)*(PERCEIVERFL_3_TOPANGLE + 1U) << 8U));
      unBottomAngle  = (uint16)((uint16)(*PERCEIVERFL_3_BOTTOMANGLE) + (uint16)((uint16)*(PERCEIVERFL_3_BOTTOMANGLE + 1U) << 8U));

      sPerceiveSigGroup1.eBrightness.ucBrightness   = *PERCEIVERFL_3_BRIGHTNESS;
      sPerceiveSigGroup1.eLeftAngle.nLeftAngle      = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unLeftAngle, SIGPREP_RX_LENGTH_PERCEIVE_L_R_ANGLE);
      sPerceiveSigGroup1.eRightAngle.nRightAngle    = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unRightAngle, SIGPREP_RX_LENGTH_PERCEIVE_L_R_ANGLE);
      sPerceiveSigGroup1.eTopAngle.nTopAngle        = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unTopAngle, SIGPREP_RX_LENGTH_PERCEIVE_T_B_ANGLE);
      sPerceiveSigGroup1.eBottomAngle.nBottomAngle  = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unBottomAngle, SIGPREP_RX_LENGTH_PERCEIVE_T_B_ANGLE);
      sPerceiveSigGroup1.eDistance.unDistance       = (uint16)((uint16)(*PERCEIVERFL_3_DISTANCE) + (uint16)((uint16)*(PERCEIVERFL_3_DISTANCE + 1U) << 8U));
      
      // Set signal quality for RTE port as valid
      sPerceiveSigGroup1.eSigQty = SIG_VALID;
      
      break;

    case eFrmTimeOut:
      sPerceiveSigGroup1.eBrightness.ucBrightness   = SIGPREP_RX_INVALID_PERCEIVERFL_X_BRIGHTNESS;
      sPerceiveSigGroup1.eLeftAngle.nLeftAngle      = SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE;
      sPerceiveSigGroup1.eRightAngle.nRightAngle    = SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE;
      sPerceiveSigGroup1.eTopAngle.nTopAngle        = SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE;
      sPerceiveSigGroup1.eBottomAngle.nBottomAngle  = SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE;
      sPerceiveSigGroup1.eDistance.unDistance       = SIGPREP_RX_INVALID_PERCEIVERFL_X_DISTANCE;

      // Set signal quality for RTE port as time-out
      sPerceiveSigGroup1.eSigQty = SIG_TIMEOUT;

      // Set DTC U1FC5-87 - HS6_DYN_VSM_0CB frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0CB_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC 1FC587 - 0xCB frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0CB_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B-81 - 0xCB invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_0CB_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sPerceiveSigGroup1.eBrightness.ucBrightness   = 0u;
    sPerceiveSigGroup1.eLeftAngle.nLeftAngle      = 0;
    sPerceiveSigGroup1.eRightAngle.nRightAngle    = 0;
    sPerceiveSigGroup1.eTopAngle.nTopAngle        = 0;
    sPerceiveSigGroup1.eBottomAngle.nBottomAngle  = 0;
    sPerceiveSigGroup1.eDistance.unDistance       = 0u;
    sPerceiveSigGroup1.eSigQty                    = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_PerceiveSigGroup1_sVal_02(&sPerceiveSigGroup1);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_0E3
///
/// \descr Handling of 0xE3 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_0E3(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint16 unClusterAngleLeft        = 0U;
  uint16 unClusterAngleRight       = 0U;
  uint8  ucClusterRightAzimuthRate = 0U;
  uint8  ucClusterLeftAzimuthRate  = 0U;
  uint8  ucClusterType             = 0U;

  tsRte_SigPrep_ClusterSigGroup1_sVal  sClusterSigGroup1 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup1.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_00(&sClusterSigGroup1);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup1.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_0E3 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0E3_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      unClusterAngleLeft         = (uint16)((uint16)(*H_CLUSTER_ANGLE_LEFT_50D) + (uint16)((uint16)*(H_CLUSTER_ANGLE_LEFT_50D + 1U) << 8U));
      unClusterAngleRight        = (uint16)((uint16)(*H_CLUSTER_ANGLE_RIGHT_50D) + (uint16)((uint16)*(H_CLUSTER_ANGLE_RIGHT_50D + 1U) << 8U));
      ucClusterRightAzimuthRate  = *H_CLUSTER_RIGHT_AZIMUTH_RATE;
      ucClusterLeftAzimuthRate   = *H_CLUSTER_LEFT_AZIMUTH_RATE;

      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = (uint16)((uint16)(*H_CLUSTER_MIN_DISTANCE_E) + (uint16)((uint16)*(H_CLUSTER_MIN_DISTANCE_E + 1U) << 8U));
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = (uint16)((uint16)(*H_CLUSTER_DISTANCE_LEFT_E) + (uint16)((uint16)*(H_CLUSTER_DISTANCE_LEFT_E + 1U) << 8U));
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = (uint16)((uint16)(*H_CLUSTER_DISTANCE_RIGHT_E) + (uint16)((uint16)*(H_CLUSTER_DISTANCE_RIGHT_E + 1U) << 8U));
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleLeft, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleRight, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterRightAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterLeftAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      ucClusterType                                                        = *HCLUSTERTYPE_1;

      // Compute Vehicle light type detected
      sClusterSigGroup1.eClusterType = SigPrep_RxCallbacks_Compute_ClusterType(ucClusterType);
      
      // Set signal quality for RTE port as valid
      sClusterSigGroup1.eSigQty = SIG_VALID;

      break;

    case eFrmTimeOut:
      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = SIGPREP_RX_INVALID_HCLUSTERMINDISTANCE_X;
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterType                                       = eClstType_Invalid;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup1.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_0E3 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0E3_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0xE3 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0E3_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B-81 - 0xE3 invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_0E3_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = 0u;
    sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = 0u;
    sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = 0u;
    sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = 0;
    sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = 0;
    sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = 0;
    sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = 0;
    sClusterSigGroup1.eClusterType                                       = eClstType_Reserved;
    sClusterSigGroup1.eSigQty                                            = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup1_sVal_00(&sClusterSigGroup1);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_0EB
///
/// \descr Handling of 0xEB receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_0EB(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint16 unClusterAngleLeft        = 0U;
  uint16 unClusterAngleRight       = 0U;
  uint8  ucClusterRightAzimuthRate = 0U;
  uint8  ucClusterLeftAzimuthRate  = 0U;
  uint8  ucClusterType             = 0U;

  tsRte_SigPrep_ClusterSigGroup1_sVal  sClusterSigGroup1 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup1.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_01(&sClusterSigGroup1);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup1.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_0EB frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0EB_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      unClusterAngleLeft         = (uint16)((uint16)(*HCLUSTERANGLELEFT_2) + (uint16)((uint16)*(HCLUSTERANGLELEFT_2 + 1U) << 8U));
      unClusterAngleRight        = (uint16)((uint16)(*HCLUSTERANGLERIGHT_2) + (uint16)((uint16)*(HCLUSTERANGLERIGHT_2 + 1U) << 8U));
      ucClusterRightAzimuthRate  = *HCLUSTERRIGHTAZIMUTHRATE_2;
      ucClusterLeftAzimuthRate   = *HCLUSTERLEFTAZIMUTHRATE_2;

      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = (uint16)((uint16)(*HCLUSTERMINDISTANCE_2) + (uint16)((uint16)*(HCLUSTERMINDISTANCE_2 + 1U) << 8U));
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = (uint16)((uint16)(*HCLUSTERLEFTDISTANCE_2) + (uint16)((uint16)*(HCLUSTERLEFTDISTANCE_2 + 1U) << 8U));
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = (uint16)((uint16)(*HCLUSTERRIGHTDISTANCE_2) + (uint16)((uint16)*(HCLUSTERRIGHTDISTANCE_2 + 1U) << 8U));
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleLeft, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleRight, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterRightAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterLeftAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      ucClusterType                                                        = *HCLUSTERTYPE_2;

      // Compute Vehicle light type detected
      sClusterSigGroup1.eClusterType = SigPrep_RxCallbacks_Compute_ClusterType(ucClusterType);

      // Set signal quality for RTE port as valid
      sClusterSigGroup1.eSigQty = SIG_VALID;

      break;

    case eFrmTimeOut:
      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = SIGPREP_RX_INVALID_HCLUSTERMINDISTANCE_X;
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterType                                       = eClstType_Invalid;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup1.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_0EB frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0EB_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0xEB frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_0EB_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B-81 - 0xEB invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_0EB_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = 0u;
    sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = 0u;
    sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = 0u;
    sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = 0;
    sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = 0;
    sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = 0;
    sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = 0;
    sClusterSigGroup1.eClusterType                                       = eClstType_Reserved;
    sClusterSigGroup1.eSigQty                                            = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup1_sVal_01(&sClusterSigGroup1);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_103
///
/// \descr Handling of 0x103 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_103(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint16 unClusterAngleLeft           = 0U;
  uint16 unClusterAngleRight          = 0U;
  uint8  ucClusterRightAzimuthRate    = 0U;
  uint8  ucClusterLeftAzimuthRate     = 0U;
  uint8  ucClusterType                = 0U;

  tsRte_SigPrep_ClusterSigGroup1_sVal  sClusterSigGroup1 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup1.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_02(&sClusterSigGroup1);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup1.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_103 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_103_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      unClusterAngleLeft         = (uint16)((uint16)(*HCLUSTERANGLELEFT_3) + (uint16)((uint16)*(HCLUSTERANGLELEFT_3 + 1U) << 8U));
      unClusterAngleRight        = (uint16)((uint16)(*HCLUSTERANGLERIGHT_3) + (uint16)((uint16)*(HCLUSTERANGLERIGHT_3 + 1U) << 8U));
      ucClusterRightAzimuthRate  = *HCLUSTERRIGHTAZIMUTHRATE_3;
      ucClusterLeftAzimuthRate   = *HCLUSTERLEFTAZIMUTHRATE_3;

      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = (uint16)((uint16)(*HCLUSTERMINDISTANCE_3) + (uint16)((uint16)*(HCLUSTERMINDISTANCE_3 + 1U) << 8U));
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = (uint16)((uint16)(*HCLUSTERLEFTDISTANCE_3) + (uint16)((uint16)*(HCLUSTERLEFTDISTANCE_3 + 1U) << 8U));
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = (uint16)((uint16)(*HCLUSTERRIGHTDISTANCE_3) + (uint16)((uint16)*(HCLUSTERRIGHTDISTANCE_3 + 1U) << 8U));
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleLeft, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleRight, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterRightAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterLeftAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      ucClusterType                                                        = *HCLUSTERTYPE_3;

      // Compute Vehicle light type detected
      sClusterSigGroup1.eClusterType = SigPrep_RxCallbacks_Compute_ClusterType(ucClusterType);

      // Set signal quality for RTE port as valid
      sClusterSigGroup1.eSigQty = SIG_VALID;

      break;

    case eFrmTimeOut:
      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = SIGPREP_RX_INVALID_HCLUSTERMINDISTANCE_X;
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterType                                       = eClstType_Invalid;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup1.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_103 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_103_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x103 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_103_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B-81 - 0x103 invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_103_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = 0u;
    sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = 0u;
    sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = 0u;
    sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = 0;
    sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = 0;
    sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = 0;
    sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = 0;
    sClusterSigGroup1.eClusterType                                       = eClstType_Reserved;
    sClusterSigGroup1.eSigQty                                            = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup1_sVal_02(&sClusterSigGroup1);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_10B
///
/// \descr Handling of 0x10B receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_10B(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint16 unClusterAngleLeft           = 0U;
  uint16 unClusterAngleRight          = 0U;
  uint8  ucClusterRightAzimuthRate    = 0U;
  uint8  ucClusterLeftAzimuthRate     = 0U;
  uint8  ucClusterType                = 0U;

  tsRte_SigPrep_ClusterSigGroup1_sVal  sClusterSigGroup1 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup1.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_03(&sClusterSigGroup1);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup1.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_10B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_10B_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      unClusterAngleLeft         = (uint16)((uint16)(*HCLUSTERANGLELEFT_4) + (uint16)((uint16)*(HCLUSTERANGLELEFT_4 + 1U) << 8U));
      unClusterAngleRight        = (uint16)((uint16)(*HCLUSTERANGLERIGHT_4) + (uint16)((uint16)*(HCLUSTERANGLERIGHT_4 + 1U) << 8U));
      ucClusterRightAzimuthRate  = *HCLUSTERRIGHTAZIMUTHRATE_4;
      ucClusterLeftAzimuthRate   = *HCLUSTERLEFTAZIMUTHRATE_4;

      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = (uint16)((uint16)(*HCLUSTERMINDISTANCE_4) + (uint16)((uint16)*(HCLUSTERMINDISTANCE_4 + 1U) << 8U));
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = (uint16)((uint16)(*HCLUSTERLEFTDISTANCE_4) + (uint16)((uint16)*(HCLUSTERLEFTDISTANCE_4 + 1U) << 8U));
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = (uint16)((uint16)(*HCLUSTERRIGHTDISTANCE_4) + (uint16)((uint16)*(HCLUSTERRIGHTDISTANCE_4 + 1U) << 8U));
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleLeft, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleRight, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterRightAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterLeftAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      ucClusterType                                                        = *HCLUSTERTYPE_4;

      // Compute Vehicle light type detected
      sClusterSigGroup1.eClusterType = SigPrep_RxCallbacks_Compute_ClusterType(ucClusterType);

      // Set signal quality for RTE port as valid
      sClusterSigGroup1.eSigQty = SIG_VALID;

      break;

    case eFrmTimeOut:
      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = SIGPREP_RX_INVALID_HCLUSTERMINDISTANCE_X;
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterType                                       = eClstType_Invalid;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup1.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_10B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_10B_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x10B frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_10B_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B-81 - 0x10B invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_10B_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = 0u;
    sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = 0u;
    sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = 0u;
    sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = 0;
    sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = 0;
    sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = 0;
    sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = 0;
    sClusterSigGroup1.eClusterType                                       = eClstType_Reserved;
    sClusterSigGroup1.eSigQty                                            = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup1_sVal_03(&sClusterSigGroup1);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_123
///
/// \descr Handling of 0x123 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_123(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint16 unClusterAngleLeft           = 0U;
  uint16 unClusterAngleRight          = 0U;
  uint8  ucClusterRightAzimuthRate    = 0U;
  uint8  ucClusterLeftAzimuthRate     = 0U;
  uint8  ucClusterType                = 0U;

  tsRte_SigPrep_ClusterSigGroup1_sVal  sClusterSigGroup1 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup1.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_04(&sClusterSigGroup1);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup1.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_123 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_123_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      unClusterAngleLeft         = (uint16)((uint16)(*HCLUSTERANGLELEFT_5) + (uint16)((uint16)*(HCLUSTERANGLELEFT_5 + 1U) << 8U));
      unClusterAngleRight        = (uint16)((uint16)(*HCLUSTERANGLERIGHT_5) + (uint16)((uint16)*(HCLUSTERANGLERIGHT_5 + 1U) << 8U));
      ucClusterRightAzimuthRate  = *HCLUSTERRIGHTAZIMUTHRATE_5;
      ucClusterLeftAzimuthRate   = *HCLUSTERLEFTAZIMUTHRATE_5;

      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = (uint16)((uint16)(*HCLUSTERMINDISTANCE_5) + (uint16)((uint16)*(HCLUSTERMINDISTANCE_5 + 1U) << 8U));
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = (uint16)((uint16)(*HCLUSTERLEFTDISTANCE_5) + (uint16)((uint16)*(HCLUSTERLEFTDISTANCE_5 + 1U) << 8U));
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = (uint16)((uint16)(*HCLUSTERRIGHTDISTANCE_5) + (uint16)((uint16)*(HCLUSTERRIGHTDISTANCE_5 + 1U) << 8U));
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleLeft, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = (sint16)SigPrep_RxCallbacks_ConvertValueInt2Sint(unClusterAngleRight, SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R);
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterRightAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterLeftAzimuthRate, SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE);
      ucClusterType                                                        = *HCLUSTERTYPE_5;

      // Compute Vehicle light type detected
      sClusterSigGroup1.eClusterType = SigPrep_RxCallbacks_Compute_ClusterType(ucClusterType);

      // Set signal quality for RTE port as valid
      sClusterSigGroup1.eSigQty = SIG_VALID;

      break;

    case eFrmTimeOut:
      sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = SIGPREP_RX_INVALID_HCLUSTERMINDISTANCE_X;
      sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X;
      sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = SIGPREP_RX_INVALID_HCLUSTERANGLE_X;
      sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X;
      sClusterSigGroup1.eClusterType                                       = eClstType_Invalid;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup1.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_123 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_123_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x123 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_123_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B-81 - 0x123 invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_123_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance           = 0u;
    sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance         = 0u;
    sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance       = 0u;
    sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft                = 0;
    sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight              = 0;
    sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate  = 0;
    sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate    = 0;
    sClusterSigGroup1.eClusterType                                       = eClstType_Reserved;
    sClusterSigGroup1.eSigQty                                            = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup1_sVal_04(&sClusterSigGroup1);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_12B
///
/// \descr Handling of 0x12B receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_12B(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8 ucLeftAzimuthRate   = 0U;
  uint8 ucRightAzimuthRate  = 0U;

  tsRte_SigPrep_PerceiveSigGroup2_sVal  sPerceiveSigGroup2 = { 0 };

  // Check if TSAG option is present in Coding
  if (Cod_TSAG_Enable() != FALSE)
  {
    sPerceiveSigGroup2.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00(&sPerceiveSigGroup2);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sPerceiveSigGroup2.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_12B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_12B_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      ucLeftAzimuthRate   = *PERCEIVERFL_1_LEFTAZIMUTHRATE;
      ucRightAzimuthRate  = *PERCEIVERFL_1_RIGHTAZIMUTHRATE;

      sPerceiveSigGroup2.ePerceiveId.ucPerceiveId             = *PERCEIVEEFL_1_ID;
      sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate    = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucLeftAzimuthRate, SIGPREP_RX_LENGTH_PERCEIVE_L_R_AZIMUTHRATE);
      sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucRightAzimuthRate, SIGPREP_RX_LENGTH_PERCEIVE_L_R_AZIMUTHRATE);

      // Set signal quality for RTE port as valid
      sPerceiveSigGroup2.eSigQty = SIG_VALID;

      if (sPerceiveSigGroup2.ePerceiveId.ucPerceiveId != SIGPREPRX_ZERO_VALUE)
      {
        // Check Perceive signals range and based on the signal validity fill up RTE cam object
        SigPrep_RxCallbacks_RangeCheck_PerceiveSigGroup2(sPerceiveSigGroup2, SIGPREP_RX_12B_ID);
      }
      else
      {
        //do nothing
      }

      break;

    case eFrmTimeOut:
      sPerceiveSigGroup2.ePerceiveId.ucPerceiveId             = SIGPREP_RX_INVALID_PERCEIVEEFL_X_ID;
      sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate    = SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE;
      sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate  = SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE;

      // Set signal quality for RTE port as time-out
      sPerceiveSigGroup2.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_12B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_12B_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x12B frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_12B_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B81 - 0x12B invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_12B_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sPerceiveSigGroup2.ePerceiveId.ucPerceiveId             = 0u;
    sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate    = 0;
    sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate  = 0;
    sPerceiveSigGroup2.eSigQty                              = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_PerceiveSigGroup2_sVal_00(&sPerceiveSigGroup2);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_143
///
/// \descr Handling of 0x143 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_143(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8 ucLeftAzimuthRate   = 0U;
  uint8 ucRightAzimuthRate  = 0U;

  tsRte_SigPrep_PerceiveSigGroup2_sVal  sPerceiveSigGroup2 = { 0 };

  // Check if TSAG option is present in Coding
  if (Cod_TSAG_Enable() != FALSE)
  {
    sPerceiveSigGroup2.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01(&sPerceiveSigGroup2);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sPerceiveSigGroup2.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_143 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_143_ID, DEM_EVENT_STATUS_PASSED);
      // Read CAN signals
      ucLeftAzimuthRate   = *PERCEIVERFL_2_LEFTAZIMUTHRATE;
      ucRightAzimuthRate  = *PERCEIVERFL_2_RIGHTAZIMUTHRATE;

      sPerceiveSigGroup2.ePerceiveId.ucPerceiveId             = *PERCEIVEEFL_2_ID;
      sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate    = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucLeftAzimuthRate, SIGPREP_RX_LENGTH_PERCEIVE_L_R_AZIMUTHRATE);
      sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucRightAzimuthRate, SIGPREP_RX_LENGTH_PERCEIVE_L_R_AZIMUTHRATE);

      // Set signal quality for RTE port as valid
      sPerceiveSigGroup2.eSigQty = SIG_VALID;

      if (sPerceiveSigGroup2.ePerceiveId.ucPerceiveId != SIGPREPRX_ZERO_VALUE)
      {
        // Check Perceive signals range and based on the signal validity fill up RTE cam object
        SigPrep_RxCallbacks_RangeCheck_PerceiveSigGroup2(sPerceiveSigGroup2, SIGPREP_RX_143_ID);
      }
      else
      {
        //do nothing
      }

      break;

    case eFrmTimeOut:
      sPerceiveSigGroup2.ePerceiveId.ucPerceiveId             = SIGPREP_RX_INVALID_PERCEIVEEFL_X_ID;
      sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate    = SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE;
      sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate  = SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE;

      // Set signal quality for RTE port as time-out
      sPerceiveSigGroup2.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_143 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_143_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x143 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_143_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B81 - 0x143 invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_143_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sPerceiveSigGroup2.ePerceiveId.ucPerceiveId             = 0u;
    sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate    = 0;
    sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate  = 0;
    sPerceiveSigGroup2.eSigQty                              = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_PerceiveSigGroup2_sVal_01(&sPerceiveSigGroup2);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_14B
///
/// \descr Handling of 0x14B receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_14B(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucLeftAzimuthRate   = 0U;
  uint8  ucRightAzimuthRate  = 0U;
  uint8  ucTrafficDetected   = 0u;

  tsRte_SigPrep_PerceiveSigGroup2_sVal  sPerceiveSigGroup2 = { 0 };

  // Check if TSAG option is present in Coding
  if (Cod_TSAG_Enable() != FALSE)
  {
    sPerceiveSigGroup2.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02(&sPerceiveSigGroup2);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sPerceiveSigGroup2.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_14B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_14B_ID, DEM_EVENT_STATUS_PASSED);
      // Read CAN signals
      ucLeftAzimuthRate   = *PERCEIVERFL_3_LEFTAZIMUTHRATE;
      ucRightAzimuthRate  = *PERCEIVERFL_3_RIGHTAZIMUTHRATE;

      sPerceiveSigGroup2.ePerceiveId.ucPerceiveId             = *PERCEIVEEFL_3_ID;
      sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate    = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucLeftAzimuthRate, SIGPREP_RX_LENGTH_PERCEIVE_L_R_AZIMUTHRATE);
      sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucRightAzimuthRate, SIGPREP_RX_LENGTH_PERCEIVE_L_R_AZIMUTHRATE);
      ucTrafficDetected                                       = *TRAFFICDETECTED;

      // Compute Presence of the host vehicle in traffic
      sPerceiveSigGroup2.eTrafficDetected = SigPrep_RxCallbacks_Compute_TrafficDetected(ucTrafficDetected);

      // Set signal quality for RTE port as valid
      sPerceiveSigGroup2.eSigQty = SIG_VALID;

      if (sPerceiveSigGroup2.ePerceiveId.ucPerceiveId != SIGPREPRX_ZERO_VALUE)
      {
        // Check Perceive signals range and based on the signal validity fill up RTE cam object
        SigPrep_RxCallbacks_RangeCheck_PerceiveSigGroup2(sPerceiveSigGroup2, SIGPREP_RX_14B_ID);
      }
      else
      {
        //do nothing
      }

      break;

    case eFrmTimeOut:
      sPerceiveSigGroup2.ePerceiveId.ucPerceiveId             = SIGPREP_RX_INVALID_PERCEIVEEFL_X_ID;
      sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate    = SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE;
      sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate  = SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE;
      sPerceiveSigGroup2.eTrafficDetected                     = eTrffDet_Invalid;

      // Set signal quality for RTE port as time-out
      sPerceiveSigGroup2.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_14B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_14B_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x14B frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_14B_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B81 - 0x14B invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_14B_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sPerceiveSigGroup2.ePerceiveId.ucPerceiveId             = 0u;
    sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate    = 0;
    sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate  = 0;
    sPerceiveSigGroup2.eTrafficDetected                     = eTrffDet_False;
    sPerceiveSigGroup2.eSigQty                              = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_PerceiveSigGroup2_sVal_02(&sPerceiveSigGroup2);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_163
///
/// \descr Handling of 0x163 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_163(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucClusterBottomAngle     = 0u;
  uint8  ucClusterSubType         = 0u;

  tsRte_SigPrep_ClusterSigGroup2_sVal  sClusterSigGroup2 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup2.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_00(&sClusterSigGroup2);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup2.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_163 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_163_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      ucClusterBottomAngle                                      = *HCLUSTERBOTTOMANGLE_1;
      ucClusterSubType                                          = *HCLUSTERCLSUBTYPE_1;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterBottomAngle, SIGPREP_RX_LENGTH_CLUSTER_BOTTOMANGLE);
      sClusterSigGroup2.eClusterId.ucClusterId                  = *HCLUSTERID_1;

      // Compute Cluster sub type
      sClusterSigGroup2.eClusterSubType = SigPrep_RxCallbacks_Compute_ClusterSubType(ucClusterSubType);

      // Set signal quality for RTE port as valid
      sClusterSigGroup2.eSigQty = SIG_VALID;

      if (sClusterSigGroup2.eClusterId.ucClusterId != SIGPREPRX_ZERO_VALUE)
      {
        // Verify signals validity and set DTC based on it
        SigPrep_RxCallbacks_DtcCheck_ClusterSigGroup2(sClusterSigGroup2, SIGPREP_RX_163_ID);
      }
      else
      {
        //do nothing
      }
     
      break;

    case eFrmTimeOut:
      sClusterSigGroup2.eClusterSubType                          = eClstSubType_Invalid;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X;
      sClusterSigGroup2.eClusterId.ucClusterId                   = SIGPREP_RX_INVALID_HCLUSTERID_X;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup2.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_163 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_163_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x163 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_163_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B82 - 0x163 invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_163_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup2.eClusterSubType                          = eClstSubType_Reserved;
    sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = 0;
    sClusterSigGroup2.eClusterId.ucClusterId                   = 0u;
    sClusterSigGroup2.eSigQty                                  = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup2_sVal_00(&sClusterSigGroup2);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_16B
///
/// \descr Handling of 0x16B receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_16B(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucClusterBottomAngle     = 0u;
  uint8  ucClusterSubType         = 0u;

  tsRte_SigPrep_ClusterSigGroup2_sVal  sClusterSigGroup2 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup2.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_01(&sClusterSigGroup2);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup2.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_16B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_16B_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      ucClusterBottomAngle                                       = *HCLUSTERBOTTOMANGLE_2;
      ucClusterSubType                                           = *HCLUSTERCLSUBTYPE_2;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterBottomAngle, SIGPREP_RX_LENGTH_CLUSTER_BOTTOMANGLE);
      sClusterSigGroup2.eClusterId.ucClusterId                   = *HCLUSTERID_2;

      // Compute Cluster sub type
      sClusterSigGroup2.eClusterSubType = SigPrep_RxCallbacks_Compute_ClusterSubType(ucClusterSubType);

      // Set signal quality for RTE port as valid 
      sClusterSigGroup2.eSigQty = SIG_VALID;

      if (sClusterSigGroup2.eClusterId.ucClusterId != SIGPREPRX_ZERO_VALUE)
      {
        // Verify signals validity and set DTC based on it
        SigPrep_RxCallbacks_DtcCheck_ClusterSigGroup2(sClusterSigGroup2, SIGPREP_RX_16B_ID);
      }
      else
      {
        //do nothing
      }

      break;

    case eFrmTimeOut:
      sClusterSigGroup2.eClusterSubType                          = eClstSubType_Invalid;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X;
      sClusterSigGroup2.eClusterId.ucClusterId                   = SIGPREP_RX_INVALID_HCLUSTERID_X;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup2.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_16B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_16B_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x16B frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_16B_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B82 - 0x16B invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_16B_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup2.eClusterSubType                          = eClstSubType_Reserved;
    sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = 0;
    sClusterSigGroup2.eClusterId.ucClusterId                   = 0u;
    sClusterSigGroup2.eSigQty                                  = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup2_sVal_01(&sClusterSigGroup2);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_183
///
/// \descr Handling of 0x183 receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_183(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucClusterBottomAngle     = 0u;
  uint8  ucClusterSubType         = 0u;

  tsRte_SigPrep_ClusterSigGroup2_sVal  sClusterSigGroup2 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup2.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_02(&sClusterSigGroup2);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup2.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_183 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_183_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      ucClusterBottomAngle                                       = *HCLUSTERBOTTOMANGLE_3;
      ucClusterSubType                                           = *HCLUSTERCLSUBTYPE_3;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterBottomAngle, SIGPREP_RX_LENGTH_CLUSTER_BOTTOMANGLE);
      sClusterSigGroup2.eClusterId.ucClusterId                   = *HCLUSTERID_3;

      // Compute Cluster sub type
      sClusterSigGroup2.eClusterSubType = SigPrep_RxCallbacks_Compute_ClusterSubType(ucClusterSubType);

      // Set singal quality for RTE port as valid
      sClusterSigGroup2.eSigQty = SIG_VALID;

      if (sClusterSigGroup2.eClusterId.ucClusterId != SIGPREPRX_ZERO_VALUE)
      {
        // Verify signals validity and set DTC based on it
        SigPrep_RxCallbacks_DtcCheck_ClusterSigGroup2(sClusterSigGroup2, SIGPREP_RX_183_ID);
      }
      else
      {
        //do nothing
      }

      break;

    case eFrmTimeOut:
      sClusterSigGroup2.eClusterSubType                          = eClstSubType_Invalid;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X;
      sClusterSigGroup2.eClusterId.ucClusterId                   = SIGPREP_RX_INVALID_HCLUSTERID_X;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup2.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_183 frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_183_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x183 frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_183_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B82 - 0x183 invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_183_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup2.eClusterSubType                          = eClstSubType_Reserved;
    sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = 0;
    sClusterSigGroup2.eClusterId.ucClusterId                   = 0u;
    sClusterSigGroup2.eSigQty                                  = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup2_sVal_02(&sClusterSigGroup2);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_18B
///
/// \descr Handling of 0x18B receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_18B(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucClusterBottomAngle     = 0u;
  uint8  ucClusterSubType         = 0u;

  tsRte_SigPrep_ClusterSigGroup2_sVal  sClusterSigGroup2 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup2.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_03(&sClusterSigGroup2);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup2.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_18B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_18B_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      ucClusterBottomAngle                                       = *HCLUSTERBOTTOMANGLE_4;
      ucClusterSubType                                           = *HCLUSTERCLSUBTYPE_4;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterBottomAngle, SIGPREP_RX_LENGTH_CLUSTER_BOTTOMANGLE);
      sClusterSigGroup2.eClusterId.ucClusterId                   = *HCLUSTERID_4;

      // Compute Cluster sub type
      sClusterSigGroup2.eClusterSubType = SigPrep_RxCallbacks_Compute_ClusterSubType(ucClusterSubType);

      // Set signal quality for RTE port as valid
      sClusterSigGroup2.eSigQty = SIG_VALID;

      if (sClusterSigGroup2.eClusterId.ucClusterId != SIGPREPRX_ZERO_VALUE)
      {
        // Verify signals validity and set DTC based on it
        SigPrep_RxCallbacks_DtcCheck_ClusterSigGroup2(sClusterSigGroup2, SIGPREP_RX_18B_ID);
      }
      else
      {
        //do nothing
      }

      break;

    case eFrmTimeOut:
      sClusterSigGroup2.eClusterSubType                          = eClstSubType_Invalid;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X;
      sClusterSigGroup2.eClusterId.ucClusterId                   = SIGPREP_RX_INVALID_HCLUSTERID_X;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup2.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_18B frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_18B_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x18B frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_18B_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B82 - 0x18B invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_18B_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup2.eClusterSubType                          = eClstSubType_Reserved;
    sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = 0;
    sClusterSigGroup2.eClusterId.ucClusterId                   = 0u;
    sClusterSigGroup2.eSigQty                                  = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup2_sVal_03(&sClusterSigGroup2);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallbacks_HS6_DYN_VSM_1AB
///
/// \descr Handling of 0x1AB receive CAN frame
///
/// \param  eSigPrepRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_DYN_VSM_1AB(teSigPrep_RxFrameState eSigPrepRxState)
{
  uint8  ucClusterBottomAngle     = 0u;
  uint8  ucClusterSubType         = 0u;

  tsRte_SigPrep_ClusterSigGroup2_sVal  sClusterSigGroup2 = { 0 };

  // Check if GFHB option is present in Coding
  if (Cod_GFHB_Enable() != FALSE)
  {
    sClusterSigGroup2.eSigQty = SIG_INIT; //Initialise the structure

    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_04(&sClusterSigGroup2);

    switch (eSigPrepRxState)
    {
    case eFrameInit:
      // Set signal quality for RTE port as SNA
      sClusterSigGroup2.eSigQty = SIG_SNA;

      break;

    case eFrmEvent:
      // Reset DTC U1FC5-87 - HS6_DYN_VSM_1AB frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_1AB_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      ucClusterBottomAngle                                       = *HCLUSTERBOTTOMANGLE_5;
      ucClusterSubType                                           = *HCLUSTERCLSUBTYPE_5;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = (sint8)SigPrep_RxCallbacks_ConvertValueInt2Sint(ucClusterBottomAngle, SIGPREP_RX_LENGTH_CLUSTER_BOTTOMANGLE);
      sClusterSigGroup2.eClusterId.ucClusterId                   = *HCLUSTERID_5;

      // Compute Cluster sub type
      sClusterSigGroup2.eClusterSubType = SigPrep_RxCallbacks_Compute_ClusterSubType(ucClusterSubType);

      // Set signal quality for RTE port as valid
      sClusterSigGroup2.eSigQty = SIG_VALID;

      if (sClusterSigGroup2.eClusterId.ucClusterId != SIGPREPRX_ZERO_VALUE)
      {
        // Verify signals validity and set DTC based on it
        SigPrep_RxCallbacks_DtcCheck_ClusterSigGroup2(sClusterSigGroup2, SIGPREP_RX_1AB_ID);
      }
      else
      {
        //do nothing
      }

      break;

    case eFrmTimeOut:
      sClusterSigGroup2.eClusterSubType                          = eClstSubType_Invalid;
      sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X;
      sClusterSigGroup2.eClusterId.ucClusterId                   = SIGPREP_RX_INVALID_HCLUSTERID_X;

      // Set signal quality for RTE port as time-out
      sClusterSigGroup2.eSigQty = SIG_TIMEOUT;
      // Set DTC U1FC5-87 - HS6_DYN_VSM_1AB frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_1AB_ID, DEM_EVENT_STATUS_FAILED);

      break;

    default:
      break;
    }
  }
  else
  {
    // Reset DTC U1FC587 - 0x1AB frame lost
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_FRAME_LOST_1AB_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U053B82 - 0x1AB invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)VSM_INVALID_DATA_1AB_ID, DEM_EVENT_STATUS_PASSED);
    // Fill the Rte port with dummy data because the option is inhibited
    sClusterSigGroup2.eClusterSubType                          = eClstSubType_Reserved;
    sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle  = 0;
    sClusterSigGroup2.eClusterId.ucClusterId                   = 0u;
    sClusterSigGroup2.eSigQty                                  = SIG_VALID;
  }

  (void)Rte_Write_SigPrep_ClusterSigGroup2_sVal_04(&sClusterSigGroup2);
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_Compute_ClusterSubType
///
/// \descr  Compute Cluster Sub Type Command
///
/// \param  ucClusterSubTypeX  - input signal received on CAN
///
/// \return teRte_ClusterSubTypeX
//-----------------------------------------------------------------------------
STATIC_AL teRte_ClusterSubTypeX SigPrep_RxCallbacks_Compute_ClusterSubType(uint8 ucClusterSubTypeX)
{
  teRte_ClusterSubTypeX  eRetClusterSubTypeX = eClstSubType_Invalid;

  switch (ucClusterSubTypeX)
  {
    case 0u: {eRetClusterSubTypeX = eClstSubType_Invalid;                  }  break;
    case 1u: {eRetClusterSubTypeX = eClstSubType_Oncomming;                }  break;
    case 2u: {eRetClusterSubTypeX = eClstSubType_Taillight;                }  break;
    case 3u: {eRetClusterSubTypeX = eClstSubType_Left_Oncoming;            }  break;
    case 4u: {eRetClusterSubTypeX = eClstSubType_Right_Oncoming;           }  break;
    case 5u: {eRetClusterSubTypeX = eClstSubType_Left_and_Right_Oncoming;  }  break;
    case 6u: {eRetClusterSubTypeX = eClstSubType_Left_and_Right_Taillight; }  break;
    default: {eRetClusterSubTypeX = eClstSubType_Reserved;                 }  break;
  }

  return (eRetClusterSubTypeX);
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_Compute_ClusterType
///
/// \descr  Compute Cluster Type Command
///
/// \param  ucClusterTpeX  - input signal received on CAN
///
/// \return teRte_ClusterTypeX
//-----------------------------------------------------------------------------
STATIC_AL teRte_ClusterTypeX SigPrep_RxCallbacks_Compute_ClusterType(uint8 ucClusterTpeX)
{
  teRte_ClusterTypeX  eRetClusterTypeX = eClstType_Invalid;

  switch (ucClusterTpeX)
  {
    case 0u: {eRetClusterTypeX = eClstType_Invalid;             }  break;
    case 1u: {eRetClusterTypeX = eClstType_Oncomming;           }  break;
    case 2u: {eRetClusterTypeX = eClstType_Couple_Oncoming;     }  break;
    case 3u: {eRetClusterTypeX = eClstType_Taillight;           }  break;
    case 4u: {eRetClusterTypeX = eClstType_Couple_Taillight;    }  break;
    case 5u: {eRetClusterTypeX = eClstType_Couple_OC_Clearance; }  break;
    default: {eRetClusterTypeX = eClstType_Reserved;            }  break;
  }

  return (eRetClusterTypeX);
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_Compute_TrafficDetected
///
/// \descr  Compute Traffic Detected Command
///
/// \param  ucTrafficDetected  - input signal received on CAN
///
/// \return teRte_TrafficDetected
//-----------------------------------------------------------------------------
STATIC_AL teRte_TrafficDetected SigPrep_RxCallbacks_Compute_TrafficDetected(uint8 ucTrafficDetected)
{
  teRte_TrafficDetected  eRetTrafficDetected = eTrffDet_Invalid;

  // Compute Presence of the host vehicle in traffic
  switch (ucTrafficDetected)
  {
    case 0u: {eRetTrafficDetected = eTrffDet_True;        }  break;
    case 1u: {eRetTrafficDetected = eTrffDet_False;       }  break;
    case 3u: {eRetTrafficDetected = eTrffDet_Unavailable; }  break;
    default: {eRetTrafficDetected = eTrffDet_Invalid;     }  break;
  }
  return (eRetTrafficDetected);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallback_SideCheck_297_RX
///
/// \descr Precheck callback for Rx frame Id 0x297
///
/// \param  -
///
/// \return boolean FALSE: Frame is incompatible with headlamp side
///                 TRUE:  Frame is compatible with headlamp side
//-----------------------------------------------------------------------------
boolean SigPrep_RxCallback_SideCheck_297_RX(void)
{
  // HeadLamp side
  teRte_MountingSide eMountingSide = { 0 };

  // Get headlamp mounting side
  eMountingSide = SigPrepRx_GetMountingSide();

  // Return status of compatibility
  return ((eMountingSide != eMountedLeft) ? FALSE : TRUE);
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallback_SideCheck_4D7_RX
///
/// \descr Precheck callback for Rx frame Id 0x4D7
///
/// \param  -
///
/// \return boolean FALSE: Frame is incompatible with headlamp side
///                 TRUE:  Frame is compatible with headlamp side
//-----------------------------------------------------------------------------
boolean SigPrep_RxCallback_SideCheck_4D7_RX(void)
{
  // HeadLamp side
  teRte_MountingSide eMountingSide = { 0 };

  // Get headlamp mounting side
  eMountingSide = SigPrepRx_GetMountingSide();

  // Return status of compatibility
  return ((eMountingSide != eMountedLeft) ? FALSE : TRUE);
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_PositionSiteD
///
/// \descr  Check range of POSITION_SITE_D signal
///
/// \param  *psOutputSig - output signal after range check
///          nInputSig   - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void SigPrep_RxCallbacks_RangeCheck_PositionSiteD(tsRte_LevellingFeedback *psOutputSig, uint16 unInputSig)
{
  STATIC_UT(boolean, boTimerStatus, FALSE);

  if ((unInputSig >= SIGPREP_RX_INVALID_CONSIGNE_SITE_D_MIN_VAL) && (unInputSig <= SIGPREP_RX_INVALID_CONSIGNE_SITE_D_MAX_VAL))
  {
    // Check 2 seconds for invalid data before setting SigQty to INVALID
    if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_POSITION_SITE_D_ID) == TRUE)
    {
      // Set signal quality for RTE ports as invalid
      psOutputSig->eSigQty = SIG_INVALID;
    };
  }
  else
  {
    // Store Vehicle Attitude value
    psOutputSig->ePositionSiteD.unRPosLvl = unInputSig;

    // Set signal quality for RTE ports as valid
    psOutputSig->eSigQty = SIG_VALID;
  }
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_DynBendBeamFault
///
/// \descr  Check range of DYN_BEND_BEAM_FAULT signal
///
/// \param  *psOutputSig - output signal after range check
///          ucInputSig  - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_RxCallbacks_RangeCheck_DynBendBeamFault(tsRte_BendingBeamFault_OtherHL *psOutputSig, uint8 ucInputSig)
{
  teRte_DynBendingBeamFault eDynBendingBeamFault = 0;
  STATIC_UT(boolean, boTimerStatus, FALSE);

  // Compute Dynamic bending beam fault
  switch (ucInputSig)
  {
    case 0u: { eDynBendingBeamFault = eDynBendingBeamFault_False;       }  break;
    case 1u: { eDynBendingBeamFault = eDynBendingBeamFault_True;        }  break;
    case 2u: { eDynBendingBeamFault = eDynBendingBeamFault_Unavailable; }  break;
    default: { eDynBendingBeamFault = eDynBendingBeamFault_Invalid;     }  break;
  }

  // Range check DYN_BENDING_BEAM_FAULT and set signal validity
  if (eDynBendingBeamFault == eDynBendingBeamFault_Invalid)
  {
    // Check 2 seconds for invalid data before setting SigQty to INVALID
    if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_DYN_BEND_BEAM_FAULT_ID) == TRUE)
    {
      // Set signal quality for RTE ports as invalid
      psOutputSig->eSigQty = SIG_INVALID;
    };
  }
  else
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    // Store DBL Fault value
    psOutputSig->eDynBendingBeamFault = eDynBendingBeamFault;

    // Set signal quality for RTE ports as valid
    psOutputSig->eSigQty = SIG_VALID;
  }
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_VehicleAttitude
///
/// \descr  Check range of ASSIETTE_VEHICULE signal, validate it and set DTC in case of signal out of range
///
/// \param  *psOutputSig - output signal after range check
///          nInputSig   - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_RxCallbacks_RangeCheck_VehicleAttitude(tsRte_SigPrep_VehiclePitchAngle *psOutputSig, sint16 nInputSig)
{
  STATIC_UT(boolean, boTimerStatus, FALSE);

  if ((nInputSig == SIGPREP_RX_INVALID_ASSIETTE_VEHICULE) ||
      ((nInputSig >= SIGPREP_RX_INVALID_ASSIETTE_VEHICULE_MIN_VAL_1) && (nInputSig <= SIGPREP_RX_INVALID_ASSIETTE_VEHICULE_MAX_VAL_1)) ||
      ((nInputSig >= SIGPREP_RX_INVALID_ASSIETTE_VEHICULE_MIN_VAL_2) && (nInputSig <= SIGPREP_RX_INVALID_ASSIETTE_VEHICULE_MAX_VAL_2)))
  {
    // Check 2 seconds for invalid data before setting SigQty to INVALID
    if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_PITCH_ID) == TRUE)
    {
      // Set signal quality for RTE ports as invalid
      psOutputSig->eSigQty = SIG_INVALID;

      // Set DTC U1216-81 - Pitch invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)Vehicle_attitude_ID, DEM_EVENT_STATUS_FAILED);
    };
  }
  else
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    // Store Vehicle Attitude value and apply resolution to VEHICLE_ATTITUDE
    psOutputSig->eAssietteVehicule.nVehiclePitchAngle = nInputSig * SIGPREP_RX_ASSIETTE_VEHICULE_RESOLUTION_NUMERATOR / SIGPREP_RX_ASSIETTE_VEHICULE_RESOLUTION_DENOMINATOR;

    // Set signal quality for RTE ports as valid
    psOutputSig->eSigQty = SIG_VALID;

    // Reset DTC U1216-81 - Pitch invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)Vehicle_attitude_ID, DEM_EVENT_STATUS_PASSED);
  }
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_VehiclePathCurvature
///
/// \descr  Check range of VEH_PATH_CURVATURE signal and set/clear DTC
///
/// \param  *psOutputSig - output signal after range check
///          nInputSig   - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void SigPrep_RxCallbacks_RangeCheck_VehiclePathCurvature(tsRte_SigPrep_VehPathCurvature *psOutputSig, sint16 nInputSig)
{
  if ((nInputSig == SIGPREP_RX_INVALID_VEH_PATH_CURVATURE) ||
      ((nInputSig >= SIGPREP_RX_INVALID_VEH_PATH_CURVATURE_MIN_VAL_1) && (nInputSig <= SIGPREP_RX_INVALID_VEH_PATH_CURVATURE_MAX_VAL_1)) ||
      ((nInputSig >= SIGPREP_RX_INVALID_VEH_PATH_CURVATURE_MIN_VAL_2) && (nInputSig <= SIGPREP_RX_INVALID_VEH_PATH_CURVATURE_MAX_VAL_2)))
  {
    // Set signal quality for RTE ports as invalid
    psOutputSig->eSigQty = SIG_INVALID;
  }
  else if (nInputSig == SIGPREP_RX_UNAVAILABLE_VEH_PATH_CURVATURE)
  {
    // Set signal quality for RTE ports as unavailable
    psOutputSig->eSigQty = SIG_UNAVAILABLE;
  }
  else
  {
    // Set signal quality for RTE ports as valid
    psOutputSig->eSigQty = SIG_VALID;
  }

  // Set/Clear DTC for invalid data
  if (psOutputSig->eSigQty != SIG_INVALID)
  {
    // Reset DTC U1213-81 - Vehicle Path Curvature invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)DBL_28E_INVALID_DATA, DEM_EVENT_STATUS_PASSED);
  }
  else
  {
    // Set DTC U1213-81 - Vehicle Path Curvature invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)DBL_28E_INVALID_DATA, DEM_EVENT_STATUS_FAILED);
  }

  // Store Vehicle Attitude value
  psOutputSig->eVehiclePathCurvature.nVehiclePathCurvature = nInputSig;
}

//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_DtcCheck_ClusterSigGroup2
///
/// \descr  Cluster (Cam) object signal ranges are checked and DTC is set
///         for CAN frames 0x163, 0x16B, 0x183, 0x18B, 0x1AB
///
/// \param  sInputSigVal: Input Cam Object values
///         ucMessageId:  CAN message ID
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_RxCallbacks_DtcCheck_ClusterSigGroup2(tsRte_SigPrep_ClusterSigGroup2_sVal sInputSig, uint8 ucMessageId)
{
  // Check if there are signals out of range for 3 consecutive frames
  if (((sInputSig.eClusterBottomAngle.cClusterBottomAngle== SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X) ||
    ((sInputSig.eClusterBottomAngle.cClusterBottomAngle >= SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X_MIN_VAL_1) && (sInputSig.eClusterBottomAngle.cClusterBottomAngle <= SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X_MAX_VAL_1)) ||
    ((sInputSig.eClusterBottomAngle.cClusterBottomAngle >= SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X_MIN_VAL_2) && (sInputSig.eClusterBottomAngle.cClusterBottomAngle <= SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X_MAX_VAL_2)))
    )
  {
    // Set DTC U053B-82 - Camera invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)SigPrep_RxCallbacks_sCvmInvalid[ucMessageId].eDemEventId, DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    // Reset DTC U053B-82 - Camera invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)SigPrep_RxCallbacks_sCvmInvalid[ucMessageId].eDemEventId, DEM_EVENT_STATUS_PASSED);
  }
}

//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_PerceiveSigGroup2
///
/// \descr  Cluster (Cam) object signal ranges are checked and their validity is reported 
///         for CAN frames 0x12B, 0x143, 0x14B
///
/// \param  sInputSig: Output RTE Cluster type object
///         ucMessageId: Message ID
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_RxCallbacks_RangeCheck_PerceiveSigGroup2(tsRte_SigPrep_PerceiveSigGroup2_sVal sInputSig, uint8 ucMessageId)
{
  uint8 ucSignalNotValid = 0u;  // Local variable which is used to set each bit of it in case of signal out of range found

  // Check PERCEIVERFL_X_LEFTAZIMUTHRATE signal range
  ucSignalNotValid = (SigPrep_RxCallbacks_RangeCheck_PerceiveAzimuthRate(sInputSig.eLeftAzimuthRate.cLeftAzimuthRate) != FALSE) ? (ucSignalNotValid | SIGPREP_RX_0_BIT) : ucSignalNotValid;
  // Check PERCEIVERFL_X_RIGHTAZIMUTHRATE signal range
  ucSignalNotValid = (SigPrep_RxCallbacks_RangeCheck_PerceiveAzimuthRate(sInputSig.eRightAzimuthRate.cRightAzimuthRate) != FALSE) ? (ucSignalNotValid | SIGPREP_RX_1_BIT) : ucSignalNotValid;

  // Check if there are signals out of range
  if ((ucSignalNotValid != 0u) || (sInputSig.eTrafficDetected == eTrffDet_Invalid))
  {
    // Set DTC U053B-81 - Camera invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)SigPrep_RxCallbacks_sCvmInvalid[ucMessageId].eDemEventId, DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    // Set DTC U053B-81 - Camera invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)SigPrep_RxCallbacks_sCvmInvalid[ucMessageId].eDemEventId, DEM_EVENT_STATUS_PASSED);
  }
}


//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_PerceiveAzimuthRate
///
/// \descr  PERCEIVERFL_X_LEFTAZIMUTHRATE and PERCEIVERFL_X_RIGHTAZIMUTHRATE signals range check
///
/// \param  cInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean SigPrep_RxCallbacks_RangeCheck_PerceiveAzimuthRate(sint8 cInputSigVal)
{
  return ((cInputSigVal == SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE) ||
          ((cInputSigVal >= SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MIN_VAL_1) && (cInputSigVal <= SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MAX_VAL_1)) ||
          ((cInputSigVal >= SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MIN_VAL_2) && (cInputSigVal <= SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MAX_VAL_2))) ? TRUE : FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_LevellingRight
///
/// \descr  Check range of Levelling signals, validate it and set DTC in case of signal out of range
///
/// \param  *psOutputSig - output signal after range check
///          eInputsig   - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_RxCallbacks_RangeCheck_LevellingRight(tsRte_LevellingDiagStatus *psOutputSig, teLvlRefStateR eInputSig)
{
  STATIC_UT(boolean, boTimerStatus, FALSE);

  // Levelling signal validity
  if (eInputSig == eLvlRefStateR_Invalid)
  {
    // Check 2 seconds for invalid data before setting SigQty to INVALID
    if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_LVL_REF_STATE_ID) == TRUE)
    {
      // Store invalid Levelling Referencing State value
      psOutputSig->eLvlRefStateR = eInputSig;

      // Set invalid signal quality factor
      psOutputSig->eSigQty = SIG_INVALID;

      // Set DTC U12E3-81 - Levelling Ref State invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)INVALID_DATA_4D7, DEM_EVENT_STATUS_FAILED);
    };
  }
  else
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    // Store Levelling Referencing State value
    psOutputSig->eLvlRefStateR = eInputSig;

    // Set invalid signal quality factor
    psOutputSig->eSigQty = SIG_VALID;

    // Clear DTC U12E3-81 - Levelling Ref State invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)INVALID_DATA_4D7, DEM_EVENT_STATUS_PASSED);
  }
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_SteeringWheel
///
/// \descr  Check range of STEER_WHEEL_ANGLE_CONF signal, validate it and set 
///          signal quality in case of signal out of range
///
/// \param  *psOutputSig - output signal after range check
///          nInputSig   - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_RxCallbacks_RangeCheck_SteeringWheel(tsRte_SigPrep_SteeringWheelAngle *psOutputSig, sint16 nInputSig)
{
  if (((nInputSig >= SIGPREP_RX_VALID_STEER_WHEEL_ANGLE_MIN_VAL) && (nInputSig <= SIGPREP_RX_VALID_STEER_WHEEL_ANGLE_MAX_VAL)) ||
      (nInputSig == SIGPREP_RX_STEER_WHEEL_ANGLE_INIT_IN_PROGRESS))
  {
    // Store Vehicle Attitude value
    psOutputSig->nSteeringWheelAngle = nInputSig;

    // Set signal quality for RTE ports as valid
    psOutputSig->eSigQty = SIG_VALID;

    // Clear DTC U1218-81 - Steering Wheel Angle invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)STEER_WHEEL_ANGLE_INVALID_DATA_257, DEM_EVENT_STATUS_PASSED);
  }
  else
  {
    // Set signal quality for RTE ports as invalid
    psOutputSig->eSigQty = SIG_INVALID;

    // Set DTC U1218-81 - Steering Wheel Angle invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)STEER_WHEEL_ANGLE_INVALID_DATA_257, DEM_EVENT_STATUS_FAILED);
  }
}
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)


//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_Callbacks_Debounce_TimerCheck
///
/// \descr  Check timer value for invalid data
///
/// \param  pboStartTimer - start/stop timer
///         ucFrameName   - element number from structure
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SigPrepRx_Callbacks_Debounce_TimerCheck(boolean *pboStartTimer, uint8 ucFrameName)
{
  boolean          boTimeout                                           = FALSE;
  STATIC_AL TIMER  ulDebounceTimers[SIGPREP_RX_NUMBER_OF_INVALID_DATA] = { 0u };

  if (*pboStartTimer == FALSE)
  {
    ulDebounceTimers[ucFrameName] = UTILTIME_TIMER_START(UTILTIME_MSEC(SIGPREP_RX_MSEC_INVALID_DATA));
    *pboStartTimer = TRUE;
  }
  else
  {
    boTimeout = UTILTIME_TIMER_TIMEOUT(ulDebounceTimers[ucFrameName]);
  }

  return boTimeout;
}



//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallback_SideCheck_2B7_RX
///
/// \descr Precheck callback for Rx frame Id 0x2B7
///
/// \param  -
///
/// \return boolean FALSE: Frame is incompatible with headlamp side
///                 TRUE:  Frame is compatible with headlamp side
//-----------------------------------------------------------------------------
boolean SigPrep_RxCallback_SideCheck_2B7_RX(void)
{
  // HeadLamp side
  teRte_MountingSide eMountingSide = { 0 };

  // Get headlamp mounting side
  eMountingSide = SigPrepRx_GetMountingSide();

  // Return status of compatibility
  return ((eMountingSide != eMountedLeft) ? TRUE : FALSE);
}


#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST) // Applicable only for ECO version
//-----------------------------------------------------------------------------
/// \brief SigPrep_RxCallback_SideCheck_477_RX
///
/// \descr Precheck callback for Rx frame Id 0x477
///
/// \param  -
///
/// \return boolean FALSE: Frame is incompatible with headlamp side
///                 TRUE:  Frame is compatible with headlamp side
//-----------------------------------------------------------------------------
boolean SigPrep_RxCallback_SideCheck_477_RX(void)
{
  // HeadLamp side
  teRte_MountingSide eMountingSide = { 0 };

  // Get headlamp mounting side
  eMountingSide = SigPrepRx_GetMountingSide();

  // Return status of compatibility
  return ((eMountingSide != eMountedLeft) ? FALSE : TRUE);
}
#endif

//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_ConsigneSiteD
///
/// \descr  Check range of CONSIGNE_SITE_D signal
///
/// \param  *psOutputSig - output signal after range check
///          unInputSig  - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void SigPrep_RxCallbacks_RangeCheck_ConsigneSiteD(tsRte_LevellingTgtPos *psOutputSig, uint16 unInputSig)
{
  STATIC_UT(boolean, boTimerStatus, FALSE);

  if ((unInputSig >= SIGPREP_RX_INVALID_CONSIGNE_SITE_D_MIN_VAL) && (unInputSig <= SIGPREP_RX_INVALID_CONSIGNE_SITE_D_MAX_VAL))
  {
    // Check 2 seconds for invalid data before setting SigQty to INVALID
    if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_CONSIGNE_SITE_D_ID) == TRUE)
    {
      // Set signal quality for RTE ports as invalid
      psOutputSig->eSigQty = SIG_INVALID;
    };
  }
  else
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    // Store Vehicle Attitude value
    psOutputSig->eRCmdPosLvl.unRCmdPosLvl = unInputSig;

    // Set signal quality for RTE ports as valid
    psOutputSig->eSigQty = SIG_VALID;
  }
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_Compute_ExtLightingAnimationReq
///
/// \descr  Compute ExtLightintgAnimationReq
///
/// \param  *psOutputSig           - output signal after range check
///         unLightingAnimationReq - input signal received on CAN
///         ucDelayFmh             - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_RxCallbacks_Compute_ExtLightingAnimationReq(tsRte_AnimationReq *psOutputSig, uint16 unLightingAnimationReq, uint8 ucDelayFmh)
{
  teRte_ExtLightingAnimationReq eRetLightingAnimationReq = eExtLightingAnimationReq_None;
  teRte_DelayFmh                eDelayFmh                = eDelayFmh_NotUsed;
  STATIC_UT(boolean, boTimerStatus, FALSE);

  switch (unLightingAnimationReq)
  {
    case 0u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_None                  ; }  break;
    case 1u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_WelcomeDay            ; }  break;
    case 2u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_WelcomeNight          ; }  break;
    case 3u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_ByeByeDay             ; }  break;
    case 4u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_ByeByeNight           ; }  break;
    case 5u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_ByeByeNightFmh        ; }  break;
    case 6u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_UnlockDay             ; }  break;
    case 7u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_UnlockNight           ; }  break;
    case 8u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_UnlockDayExtension    ; }  break;
    case 9u:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_UnlockNightExtension  ; }  break;
    case 10u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_Fmh                   ; }  break;
    case 11u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_RemoteLighting        ; }  break;
    case 12u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_LockDay               ; }  break;
    case 13u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_LockNight             ; }  break;
    case 14u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_LockNightExtension    ; }  break;
    case 15u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_Autorelock            ; }  break;
    case 16u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_LocalizationDay       ; }  break;
    case 17u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_LocalizationNight     ; }  break;
    case 18u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_ShowroomEvent         ; }  break;
    case 19u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_ShowroomContinu       ; }  break;
    case 20u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_EndNightByeBye        ; }  break;
    case 21u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_SwitchOff             ; }  break;
    case 22u: { eRetLightingAnimationReq    = eExtLightingAnimationReq_LockDayExtension      ; }  break;
    default:  { eRetLightingAnimationReq    = eExtLightingAnimationReq_Invalid               ; }  break;
  }

  // Compute Delay of follow me home function
  switch (ucDelayFmh)
  {
    case 0u: { eDelayFmh = eDelayFmh_15Seconds; }  break;
    case 1u: { eDelayFmh = eDelayFmh_30Seconds; }  break;
    case 2u: { eDelayFmh = eDelayFmh_60Seconds; }  break;
    default: { eDelayFmh = eDelayFmh_NotUsed;   }  break;
  }

  // Set Signal Quality to Valid/Invalid
  if (eRetLightingAnimationReq == eExtLightingAnimationReq_Invalid)
  {
    // Check 2 seconds timeout before setting SigQty to TIMEOUT
    if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_ANIMA_ID) == TRUE)
    {
      // Set signal quality factor as invalid
      psOutputSig->eSigQty = SIG_INVALID;

      // Set DTC U1218-81 - Animation invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)ANIMA_INVALID_DATA_36E, DEM_EVENT_STATUS_FAILED);
    };
  }
  else
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    // Store the Animation and Delay FMH values
    psOutputSig->eFrontLightingAnimationCtrl = eRetLightingAnimationReq;
    psOutputSig->eDelayFmh                   = eDelayFmh;

    // Set signal quality factor as valid
    psOutputSig->eSigQty = SIG_VALID;

    // Clear DTC U1218-81 - Animation invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)ANIMA_INVALID_DATA_36E, DEM_EVENT_STATUS_PASSED);
  }
} // PRQA S 5310, 5316, 5330 1 // Program architecture and readability



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_YawSpeed
///
/// \descr  Check range of VITESSE_LACET and  PRESSION_MAITRE_CYL signals, validate it and set DTC in case of signal out of range
///
/// \param  *psOutputSig - output signal after range check
///          sInputSig   - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_RxCallbacks_RangeCheck_YawSpeed(tsRte_SigPrep_YawSpeed *psOutputSig, tsSigPrep_RxYawSpeedFrmCheck sInputSig)
{
  boolean boYawSpeedSigSts;
  boolean boCylinderPressureSigSts;

  // Check Yaw Speed signal validity
  if ((sInputSig.nYawSpeed == SIGPREP_RX_INVALID_VITESSE_LACET) ||
      ((sInputSig.nYawSpeed >= SIGPREP_RX_INVALID_VITESSE_LACET_MIN_VAL_1) && (sInputSig.nYawSpeed <= SIGPREP_RX_INVALID_VITESSE_LACET_MAX_VAL_1)) ||
      ((sInputSig.nYawSpeed >= SIGPREP_RX_INVALID_VITESSE_LACET_MIN_VAL_2) && (sInputSig.nYawSpeed <= SIGPREP_RX_INVALID_VITESSE_LACET_MAX_VAL_2)))
  {
    // Invalidate signal
    boYawSpeedSigSts = FALSE;
    // Set DTC U121381 - removed with LDMO-2753
    // Rte_Call_DemPrj_ReportErrorStatus((uint16)Yaw_rate_ID, DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    // Store Yaw Speed value
    psOutputSig->eYawSpeed.nYawSpeed = sInputSig.nYawSpeed;
    // Validate signal
    boYawSpeedSigSts = TRUE;
    // Reset DTC U121381 - removed with LDMO-2753
    // Rte_Call_DemPrj_ReportErrorStatus((uint16)Yaw_rate_ID, DEM_EVENT_STATUS_PASSED);
  }

  // Check Cylinder Pressure signal validity
  if (sInputSig.unCylinderPressure == SIGPREP_RX_INVALID_CYLINDER_PRESSURE)
  {
    // Invalidate signal
    boCylinderPressureSigSts = FALSE;
  }
  else
  {
    // Store Cylinder Pressure value
    psOutputSig->eCylinderPressure.unCylinderPressure = sInputSig.unCylinderPressure;
    // Validate signal
    boCylinderPressureSigSts = TRUE;
  }

  if ((FALSE != boYawSpeedSigSts) && (FALSE != boCylinderPressureSigSts))
  {
    psOutputSig->eSigQty = SIG_VALID;
  }
  else
  {
    psOutputSig->eSigQty = SIG_INVALID;
  }
}



//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_RangeCheck_DynamicSigs
///
/// \descr  Check range of EFCMNT_PDLE_ACCEL, AUTO_BRAKING_PRESSURE signals,
///         validate it and set DTC in case of signal out of range
///
/// \param  *psOutputSig - output signal after range check
///          sInputSig   - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SigPrep_RxCallbacks_RangeCheck_DynamicSigs(tsRte_SigPrep_DynamicSigs *psOutputSig, tsSigPrep_RxDynamicSigsFrmCheck sInputSig)
{
  boolean boPedalAccelerationSigSts;
  boolean boBrakePressureSigSts;
  boolean boSteeringTypeSigSts;
  STATIC_UT(boolean, boTimerStatus, FALSE);

  // Check Pedal Acceleration signal validity
  if (sInputSig.ucPedalAcceleration <= SIGPREP_RX_EFCMNT_PDLE_ACCEL_MAX_VAL)
  {
    // Store Pedal Acceleration value
    psOutputSig->ePedalAcceleration.ucPedalAcceleration = sInputSig.ucPedalAcceleration;
    // Validate signal
    boPedalAccelerationSigSts = TRUE;
  }
  else
  {
    // Invalidate signal
    boPedalAccelerationSigSts = FALSE;
  }

  // Check Brake Pressure signal validity
  if (sInputSig.ucBrakePressure <= SIGPREP_RX_AUTO_BRAKING_PRESSURE_MAX_VAL)
  {
    // Store Brake Pressure value
    psOutputSig->eBrakePressure.ucBrakePressure = sInputSig.ucBrakePressure;
    // Validate signal
    boBrakePressureSigSts = TRUE;
  }
  else
  {
    // Invalidate signal
    boBrakePressureSigSts = FALSE;
  }

  // Check Steering Type signal validity
  if (sInputSig.eSteeringType != eTypeDir_Invalid)
  {
    // Store Steering Type value
    psOutputSig->eSteeringType = sInputSig.eSteeringType;
    // Validate signal
    boSteeringTypeSigSts = TRUE;
  }
  else
  {
    // Invalidate signal
    boSteeringTypeSigSts = FALSE;
  }

  // Check signal validity and set/clear DTC and set signal quality factor
  if ((FALSE != boPedalAccelerationSigSts) && (FALSE != boBrakePressureSigSts) && 
      (FALSE != boSteeringTypeSigSts))
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    psOutputSig->eSigQty = SIG_VALID;

    // Clear DTC U1218-81 - Acceleration invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)ACCELERATION_INVALID_DATA_257, DEM_EVENT_STATUS_PASSED);
  }
  else
  {
    // Check 2 seconds for invalid data before setting SigQty to INVALID
    if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_ACCELERATION_ID) == TRUE)
    {
      // Store invalid Steering Type value
      psOutputSig->eSteeringType = sInputSig.eSteeringType;

      // Set signal quality of frame to INVALID
      psOutputSig->eSigQty = SIG_INVALID;

      // Set DTC U1218-81 - Acceleration invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)ACCELERATION_INVALID_DATA_257, DEM_EVENT_STATUS_FAILED);
    };
  }
}



/// ---------------------------------------------------------------------------
/// \func     SigPrep_RxCallbacks_ConvertValueInt2Sint
///
/// \brief    Convert unsigned values into signed values 
///
/// \param    ulInValue     - Input Unsigned Value
///           ucbitLength   - Signal Length in bits
///
/// \return   sint32 - value signed
/// ---------------------------------------------------------------------------
STATIC_AL sint32 SigPrep_RxCallbacks_ConvertValueInt2Sint(uint32 ulInValue, uint8 ucbitLength)
{
  sint32 slValue = (sint32)ulInValue;
  uint32 ulBitToCheck = ((uint32)slValue) >> (ucbitLength - 1u);

  // PRQA S 1843 1 // The Right-hand signed operand is located in macro bellow from UtilMath.h
  if ((ulBitToCheck & 1u) != 0u)
  {
    // PRQA S 4532, 4394  1 // All forms of bit operations on single-bit bitfields allowed for efficiency
    slValue = slValue | (sint32)(SIGPREP_CFG_32_BIT_MASK << ucbitLength);
  }
  else
  {
    // Keep positive value
  }

  return slValue;
}



/// ---------------------------------------------------------------------------
/// \func     SigPrepRx_Callbacks_RangeCheck_ConfigVehicle
///
/// \brief    Range check vehicle configuration mode and set DTC and signal quality factor
///
/// \param    psOutputSig   - Output structure
///           ucConfigVeh   - value read from CAN
///
/// \return   sint32 - value signed
/// ---------------------------------------------------------------------------
STATIC_AL  DAPI_TE_ConfigMode SigPrepRx_Callbacks_RangeCheck_ConfigVehicle(tsRte_SigPrep_VehicleConfigSig *psOutputSig, uint8 ucConfigVeh)
{
  teRte_ModeConfigVehicle    eVehConfigMode;
  static DAPI_TE_ConfigMode  eConfigMode = 0;
  STATIC_UT(boolean, boTimerStatus,  FALSE);

  // Compute Vehicle Configuration Mode
  switch (ucConfigVeh)
  {
    case SIGPREP_RX_VEHICLE_CONFIG_FITTING:
      eVehConfigMode  = eModeConfigVehicle_Montage;
      eConfigMode     = DAPI_E_MC_FITTING;
      break;
    case SIGPREP_RX_VEHICLE_CONFIG_PLANT:
      eVehConfigMode  = eModeConfigVehicle_Usine;
      eConfigMode     = DAPI_E_MC_PLANT;
      break;
    case SIGPREP_RX_VEHICLE_CONFIG_CHECK:
      eVehConfigMode  = eModeConfigVehicle_Controle;
      eConfigMode     = DAPI_E_MC_CHECK;
      break;
    case SIGPREP_RX_VEHICLE_CONFIG_STORAGE:
      eVehConfigMode  = eModeConfigVehicle_Stockage;
      eConfigMode     = DAPI_E_MC_STORAGE;
      break;
    case SIGPREP_RX_VEHICLE_CONFIG_CLIENT:
      eVehConfigMode  = eModeConfigVehicle_Client;
      eConfigMode     = DAPI_E_MC_CUSTOMER;
      break;
    case SIGPREP_RX_VEHICLE_CONFIG_SHOWROOM:
      eVehConfigMode  = eModeConfigVehicle_Showroom;
      eConfigMode     = DAPI_E_MC_SHOWROOM;
      break;
    case SIGPREP_RX_VEHICLE_CONFIG_APV:
      eVehConfigMode  = eModeConfigVehicle_AfterMarket;
      eConfigMode     = DAPI_E_MC_AFTERMARKET;
      break;
    default:
      eVehConfigMode  = eModeConfigVehicle_Invalid2;
      break;
  }

  // Set Signal Quality to Valid/Invalid and Set/Clear DTC for invalid data
  if (eVehConfigMode == eModeConfigVehicle_Invalid2)
  {
    // Check 2 seconds for invalid data before setting SigQty to INVALID
    if (SigPrepRx_Callbacks_Debounce_TimerCheck(&boTimerStatus, SIGPREP_RX_MODE_CONFIG_VEHICLE_ID) == TRUE)
    {
      psOutputSig->eSigQty = SIG_INVALID;

      // Set signal value as Invalid
      psOutputSig->eVehicleCfg = eModeConfigVehicle_Invalid2;

      // Set invalid value for DEH API
      eConfigMode = 0x07;

      // Set DTC U1218-81 - Vehicle Configuration Mode invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)LOCATION_INVALID_DATA_3AE, DEM_EVENT_STATUS_FAILED);
    };
  }
  else
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    // Store Vehicle Configuration Mode value
    psOutputSig->eVehicleCfg = eVehConfigMode;

    // Set signal quality for RTE ports as valid
    psOutputSig->eSigQty = SIG_VALID;

    // Clear DTC U1218-81 - Vehicle Configuration Mode invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)LOCATION_INVALID_DATA_3AE, DEM_EVENT_STATUS_PASSED);
  }

  return eConfigMode;
}



// EOF
