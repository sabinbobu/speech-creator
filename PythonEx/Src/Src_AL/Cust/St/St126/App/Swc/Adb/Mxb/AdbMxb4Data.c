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
/// \file  AdbMxb4Data.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Tony Vornicu  (F63906B)
///         mailTo:tony.vornicu[at]al-lighting.com
//-----------------------------------------------------------------------------

 //-----------------------------------------------------------------------------
 // Includes
 //-----------------------------------------------------------------------------

#include <UtilMath.h>
#include <UtilBase.h>
#include <Bsw/Common/Std_Types.h>

#include <Swc/CodM/CodM.h>
#include <Swc/CodM/CodM_Para.h>

#include <RteCommonTypes.h>
#include "AdbMxb4Data.h"


 //-----------------------------------------------------------------------------
 // Defines
 //-----------------------------------------------------------------------------

#define ADBMXB4DATA_HIGHREFLTHRESHOLD 80U
#define ADBMXB4DATA_MIDREFLTHRESHOLD  40U
#define ADBMXB4DATA_LOWREFLTHRESHOLD   0U
#define ADBMXB4DATA_DBLFACTOR          20 // this factor is used to store the angle value with correct resolution
#define ADBMXB4DATA_DISTANCE_2_METERS  1U

 //-----------------------------------------------------------------------------
 // Variables
 //-----------------------------------------------------------------------------

const tNvmPara_CodingArea*  AdbMxb4Data_pCodingArea;
boolean                     AdbMxb4Data_boCodingValid;


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

STATIC_AL uint16 AdbMxb4Data_unObjectConfirmationTime = 0u;
STATIC_AL teRte_MountingSide AdbMxb4Data_eHeadlampSide = { eMountedLeft };

STATIC_AL tsCamObject_ValidityTimers AdbMxb4Data_sValidityTimerYawRate = { 0u, FALSE, 0u, FALSE, 0u, FALSE };

STATIC_AL tsCamObject_ValidityTimers AdbMxb4Data_sValidityTimers[ADBMXB4DATA_CAMOBJ_NR] =
{
  {0u, FALSE, 0u, FALSE, 0u, FALSE},
  {0u, FALSE, 0u, FALSE, 0u, FALSE},
  {0u, FALSE, 0u, FALSE, 0u, FALSE},
  {0u, FALSE, 0u, FALSE, 0u, FALSE},
  {0u, FALSE, 0u, FALSE, 0u, FALSE},
};

STATIC_AL tsCamObject_AzimuthRateValidity AdbMxb4Data_sAzimuthRate_UnavalCheckTimers[ADBMXB4DATA_CAMOBJ_NR] =
{
    {0u, FALSE},
    {0u, FALSE},
    {0u, FALSE},
    {0u, FALSE},
    {0u, FALSE}
};

STATIC_AL tsCamObject_GfhbDiag  AdbMxb4Data_sGfhbDiag[ADBMXB4DATA_CAMOBJ_NR] =
{
  {FALSE},
  {FALSE},
  {FALSE},
  {FALSE},
  {FALSE}
};

STATIC_AL tsCamObjectPerceive_ValidityTimers AdbMxb4Data_sValidityTimers_Perceive[ADBMXB4DATA_CAMOBJ_PERCEIVE_NR] =
{
    {0u, FALSE},
    {0u, FALSE},
    {0u, FALSE}
};

STATIC_AL uint8 AdbMxb4Data_ucInvalidTsag = ADBMXB4DATA_ZERO_VALUE;
STATIC_AL boolean AdbMxb4Data_boYawSpeedDiag = FALSE;

STATIC_AL uint16 AdbMxb4Data_ucCvm = 0u;
STATIC_AL uint16 AdbMxb4Data_ucEventIdofFrame = 0u;

STATIC_AL CONST_AL tsAdbMxb4Data_ClusterSigGroup1_InvalidData AdbMxb4Data_sCvmInvalid[ADBMXB4DATA_CAMOBJ_NR] =
{
  {VSM_INVALID_DATA_0E3_ID},
  {VSM_INVALID_DATA_0EB_ID},
  {VSM_INVALID_DATA_103_ID},
  {VSM_INVALID_DATA_10B_ID},
  {VSM_INVALID_DATA_123_ID},
};

STATIC_AL CONST_AL tsAdbMxb4Data_PerceiveSigGroup1_InvalidData AdbMxb4Data_sPerceiveInvalid[ADBMXB4DATA_CAMOBJ_PERCEIVE_NR] =
{
  {VSM_INVALID_DATA_0AB_ID},
  {VSM_INVALID_DATA_0CB_ID},
  {VSM_INVALID_DATA_0C3_ID},
};

//-----------------------------------------------------------------------------
// Data Types
//-----------------------------------------------------------------------------

typedef enum tieReflection_tag {
  RefType_NoReflection = 0,
  RefType_LowReflection = 1,
  RefType_MidReflection = 2,
  RefType_HighReflection = 3
} tieReflection; /* Description: Reflection types */ // PRQA S 3205 1  // Program architecture and readability


 //-----------------------------------------------------------------------------
 // Funtion prototypes
 //-----------------------------------------------------------------------------
STATIC_AL     void AdbMxb4Data_MapParams(void);
STATIC_AL     void AdbMxb4Data_SetCamObjtoZero(tCamObjectTL* pCamObjectTL);
STATIC_AL     void AdbMxb4Data_SetOutputChannelToZero(tChannel* pAdbOutChannelTL, tieAdbMode nAdbMode);
STATIC_AL     void AdbMxb4Data_SetOutputChannel(tChannel* pAdbOutChannelTL, tAdbChannelX* pRefChannelTL, tieAdbMode nAdbMode);
STATIC_AL     boolean AdbMxb4Data_ValidityCheck(tsCamObject_FrmCheck* psCamObject_FrmCheck, tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, tsRte_SigPrep_ClusterSigGroup2_sVal sClusterSigGroup2, teRte_TrafficDetected eTraffDet, uint8 ucObjIdx);
STATIC_AL     boolean AdbMxb4Data_ConsistencyCheck(tsRte_SigPrep_ClusterSigGroup1_sVal sInputSigVal, teRte_TrafficDetected eTraffDet, uint8 ucObjIdx);
STATIC_AL     boolean AdbMxb4Data_InvalidCheck(tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, tsRte_SigPrep_ClusterSigGroup2_sVal sClusterSigGroup2, boolean *pboAreCamSigFail, uint8 ucObjIdx);
STATIC_AL     boolean AdbMxb4Data_UnavailableCheck(tsCamObject_FrmCheck* psCamObject_FrmCheck, tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, tsRte_SigPrep_ClusterSigGroup2_sVal sClusterSigGroup2, boolean boCameraSignals, boolean boAreCamSigFail, uint8 ucObjIdx);
STATIC_AL     boolean AdbMxb4Data_Compute_AzimuthRate(tsCamObject_FrmCheck* psCamObject_FrmCheck, tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, uint8 ucObjIdx);
STATIC_AL     boolean AdbMxb4Data_ValidityCheck_Perceive(tsCamObjectPerceive_FrmCheck* psCamObjectPerceive_FrmCheck, tsRte_SigPrep_PerceiveSigGroup1_sVal sPerceiveSigGroup1, tsRte_SigPrep_PerceiveSigGroup2_sVal sPerceiveSigGroup2, uint8 ucObjIdx);
STATIC_AL     boolean AdbMxb4Data_SignalQualityCheck(tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, tsRte_SigPrep_ClusterSigGroup2_sVal sClusterSigGroup2);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_HClusterMinDistance(uint16 unInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_HClusterDistance(uint16 unInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_HClusterAngle(sint16 nInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_HClusterBottomAngle(sint8 cInputsigVal);
LOCAL_INLINE  boolean AdbMxb4Data_UnavailableCheck_HClusterMinDistance_0E3(uint16 unInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_UnavailableCheck_HClusterMinDistance_X(uint16 unInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_UnavailableCheck_HClusterDistance(uint16 unInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_UnavailableCheck_HClusterAngle_0E3(sint16 nInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_UnavailableCheck_HClusterAngle_X(sint16 nInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_UnavailableCheck_HClusterBottomAngle(sint8 cInputsigVal);
LOCAL_INLINE  boolean AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_0E3(sint8 cInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_X(sint8 cInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_HClusterAzimuthRateLeft(sint8 cInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_HClusterAzimuthRateRight(sint8 cInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_PerceiveBrightness(uint8 ucInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_PerceiveLeftRightAngle(sint16 nInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_PerceiveTopBottomAngle(sint16 nInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_PerceiveDistance(uint16 unInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_RangeCheck_PerceiveAzimuthRate(sint8 cInputSigVal);
LOCAL_INLINE  boolean AdbMxb4Data_UnavailableCheck_Percieve(tsRte_SigPrep_PerceiveSigGroup1_sVal sPerceiveSigGroup1, tsRte_SigPrep_PerceiveSigGroup2_sVal sPerceiveSigGroup2);


//-----------------------------------------------------------------------------
// Funtions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  MapObjectType
///
/// \descr  Map camera object type of RTE to application
///
/// \param  nCamType 
///
/// \return sint16 
//-----------------------------------------------------------------------------
static sint16 AdbMxb4Data_MapObjectType(teRte_ClusterTypeX eCamType)
{
  sint16 nObjType;

  switch (eCamType)
  {
  case eClstType_Invalid:
    nObjType = 0;
    break;

  case eClstType_Oncomming: // oncomming
  case eClstType_Couple_Oncoming: // couple oncoming
  case eClstType_Couple_OC_Clearance:
    nObjType = 1;
    break;

  case eClstType_Taillight: // preceeding
  case eClstType_Couple_Taillight: // couple preceeding
    nObjType = 2;
    break;

  default:
    nObjType = 0;
    break;
  }
  return nObjType;
}


//-----------------------------------------------------------------------------
/// \func   AdbMxb4Data_ParaFct0
///
/// \brief  AdbMxb4 coding parameters
///
/// \param  eCmd (coding data valid / invalid)
/// \param  pData (pointer to coding data ram copy)
///
/// \return void
//-----------------------------------------------------------------------------
void AdbMxb4Data_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  // set pointer to Nvm Data
  AdbMxb4Data_pCodingArea = pData;
  AdbMxb4Data_boCodingValid = (eCmd == eParaFct0_CodingDataValid) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_MapParams
///
/// \descr  Mapps the coding parameter in order to acces the in AdbMxb4Data
///
/// \param  [void]
///
/// \return [void]
//-----------------------------------------------------------------------------
STATIC_AL void AdbMxb4Data_MapParams(void)
{
  tsRteCodingParameters sCodingParameters;

  (void)Rte_Read_CodM_Adb_Mxb_Para(&sCodingParameters);

  AdbMxb4Data_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_Init
///
/// \descr  initialize AdbMxb1 data
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void AdbMxb4Data_Init(void)
{
  AdbMxb4Data_MapParams();

  AdbMxb4Data_unObjectConfirmationTime = Cod_aSa2_GfhbObjectConfirmationTime();
  Rte_Read_IoHwAbUser_GetMountingSide(&AdbMxb4Data_eHeadlampSide);
  // PRQA S 5334 1 //Architecture and readability  
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetConfigVehicleMode
///
/// \descr  get the Config Vehicle Mode
///
/// \param  - 
///
/// \return teRte_ModeConfigVehicle :   
/// eModeConfigVehicle_Montage = 0U,
/// eModeConfigVehicle_Usine = 1U,
/// eModeConfigVehicle_Controle = 2U,
/// eModeConfigVehicle_Stockage = 3U,
/// eModeConfigVehicle_Client = 4U,
/// eModeConfigVehicle_Showroom = 5U,
/// eModeConfigVehicle_AfterMarket = 6U,
/// eModeConfigVehicle_Invalid = 7U,
/// eModeConfigVehicle_Invalid2 = 15U
//-----------------------------------------------------------------------------
uint8 AdbMxb4Data_GetConfigVehicleMode(void)
{
  tsRte_SigPrep_VehicleConfigSig  sVehConfigSig = { 0 };

  (void)Rte_Read_SigPrep_VehicleConfigSig(&sVehConfigSig);

  /* REQ REQ-0550663 B GFHB - HB/GFHB features for GFHB_HB_MODE*/
  return (uint8)sVehConfigSig.eVehicleCfg;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetVESMainState
///
/// \descr  Get the Vehicle Electrical state
///
/// \param  -
///
/// \return tsRte_SysMon_VehNetState :   
//-----------------------------------------------------------------------------
teRte_EtatPrincipSEV AdbMxb4Data_GetVESMainState(void)
{
  tsRte_SysMon_VehNetState  sVehNetState = { 0 };

  (void)Rte_Read_SysMon_VehNetState(&sVehNetState);

  return (teRte_EtatPrincipSEV)sVehNetState.eVESMainState;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetYawRate
///
/// \descr  Get the Vehicle lateral speed
///
/// \param  -
///
/// \return Rte_Read_SigPrep_YawSpeed
//-----------------------------------------------------------------------------
sint32 AdbMxb4Data_GetYawRate(void)
{
  tsRte_SigPrep_YawSpeed yawSpeed = { 0 };
  sint32 result = { 0 };

  (void)Rte_Read_SigPrep_YawSpeed(&yawSpeed);

  if (yawSpeed.eSigQty == SIG_TIMEOUT || yawSpeed.eSigQty == SIG_INVALID)
  {
    // First time appearance of Invalid Check Failure
    if (AdbMxb4Data_sValidityTimerYawRate.boInvalCheck_Flag == FALSE)
    {
      // Get time stamp
      AdbMxb4Data_sValidityTimerYawRate.ulInvalCheck_StartTime = TimerGetTick();
      // Set Invalid Check Failure Flag
      AdbMxb4Data_sValidityTimerYawRate.boInvalCheck_Flag = TRUE;
    }
    else
    {
      // Wait 300ms before setting the Consistency Check Failure Flag
      if (TimerGetTimeSince(AdbMxb4Data_sValidityTimerYawRate.ulInvalCheck_StartTime) >= UTILTIME_MSEC(AdbMxb4Data_unObjectConfirmationTime))
      {
        // Set the Invalid Check Failure Status
        AdbMxb4Data_boYawSpeedDiag = TRUE;
        result = 0;
      }
      else
      {
        // nothing to do
      }
    }
  }
  else {
    // PRQA S 4533, 4544  1  // Cast and bitshift is needed for the mxb algorithm. 
    result = (sint32)(((sint32)yawSpeed.eYawSpeed.nYawSpeed) << 16);
    AdbMxb4Data_boYawSpeedDiag = FALSE;
    // Set Invalid Check Failure Flag
    AdbMxb4Data_sValidityTimerYawRate.boInvalCheck_Flag = FALSE;
  }


  return result;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetTrafficStyle
///
/// \descr  Get the traffic style
///
/// \param  - 
///
/// \return tieAdbTrafficStyle :  UnknownTraffic = 0, 
///                               RightHandTraffic = 1, 
///                               LeftHandTraffic = 2 
//-----------------------------------------------------------------------------
tieAdbTrafficStyle AdbMxb4Data_GetTrafficStyle(void)
{
  tieAdbTrafficStyle tsTrafficStyleResult;
  tsRte_SigPrep_DynamicSigs  data = { 0 };
  (void)Rte_Read_SigPrep_DynamicSigs(&data);

  if (data.eSigQty == SIG_TIMEOUT)
  {
    tsTrafficStyleResult = UnknownTraffic;
  }
  else
  {
    switch (data.eSteeringType) {
    case eTypeDir_SteeringRight: tsTrafficStyleResult = RightHandTraffic; break;
    case eTypeDir_SteeringLeft: tsTrafficStyleResult = LeftHandTraffic; break;
    default: tsTrafficStyleResult = UnknownTraffic; break;
    }
  }

  return tsTrafficStyleResult;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetSpeed
///
/// \descr  Get the speed
///
/// \param  - 
///
/// \return tAdbSpeedTL_kph : sint16
//-----------------------------------------------------------------------------
tAdbSpeedTL_kph AdbMxb4Data_GetSpeed(void)
{
  tsRte_SysMon_VehicleSpeed data = { 0 };
  tAdbSpeedTL_kph nSpeedRet = 0;
  (void)Rte_Read_SysMon_VehicleSpeed(&data);

  // HBB deactivated if ego speed is invalid or unavailable
  if (data.eVehicleSpeedDispo == eVvhIndisp_Invalid || data.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoUnavailable)
  {
    nSpeedRet = 0;
  }
  else
  {
    nSpeedRet = ((tAdbSpeedTL_kph)data.eVehicleSpeed.unVehicleSpeed / 100); // limit to sint16
  }

  return nSpeedRet;
}

//-----------------------------------------------------------------------------
/// \brief  AdbStatus
///
/// \descr  Send Status for HBB and Curtain Effect to PXA Module
///
/// \param  boolean bCurtainEffectStatus, boolean bHBBStatus 
///
/// \return void 
//-----------------------------------------------------------------------------
void AdbMxb4Data_AdbStatus(boolean bCurtainEffectStatus, boolean bHBBStatus)
{
  tAdbStatus AdbStatusOut;

  AdbStatusOut.CurtainEffectStatus = bCurtainEffectStatus;
  AdbStatusOut.HBBStatus = bHBBStatus;

  // write status to RTE
  (void)Rte_Write_Adb_StatusOut(&AdbStatusOut);
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetMotorwayDetection
///
/// \descr  
///
/// \param  - 
///
/// \return 
//-----------------------------------------------------------------------------
uint8 AdbMxb4Data_GetMotorwayDetection(void)
{
  uint8 uMwDetectionResult;
  tsRte_SysMonAfsSignals  dataAfsSignals = { 0 };
  (void)Rte_Read_SysMon_Afs_Signals(&dataAfsSignals);

  if (dataAfsSignals.eSigQty == SIG_TIMEOUT)
  {
    uMwDetectionResult = 0U;
  }
  else
  {
    uMwDetectionResult = (uint8)dataAfsSignals.eMotorway_Detection;
  }

  return uMwDetectionResult;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetHBActivation
///
/// \descr  
///
/// \param  - 
///
/// \return 
//-----------------------------------------------------------------------------
uint8 AdbMxb4Data_GetHBActivation(void)
{
  tsRte_SysMonLgtFctsReq  dataLgtFctsReq = { 0 };
  (void)Rte_Read_SysMon_StdLgtFcts_Req(&dataLgtFctsReq);

  return (uint8)dataLgtFctsReq.eHb_Request;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetHBFlashActivation
///
/// \descr  
///
/// \param  - 
///
/// \return 
//-----------------------------------------------------------------------------
uint8 AdbMxb4Data_GetHBFlashActivation(void)
{
  tsRte_SysMonLgtFctsReq  dataLgtFctsReq = { 0 };
  (void)Rte_Read_SysMon_StdLgtFcts_Req(&dataLgtFctsReq);

  return (uint8)dataLgtFctsReq.eHbFlash_Request;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetGFHB_CMD
///
/// \descr  
///
/// \param  - 
///
/// \return 
//-----------------------------------------------------------------------------
uint8 AdbMxb4Data_GetGFHB_CMD(void)
{
  tsRte_SysMonAfsSignals  dataAfsSignals = { 0 };
  (void)Rte_Read_SysMon_Afs_Signals(&dataAfsSignals);

  return (uint8)dataAfsSignals.eGfhb_Cmd;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetGFHB_CMD
///
/// \descr  
///
/// \param  - 
///
/// \return 
//-----------------------------------------------------------------------------
sint16 AdbMxb4Data_GetCurvatureAngle(void)
{
  tsRte_DblOut DblSwivelling;
  sint16 snDblCurvatureAngle;

  (void)Rte_Read_Dbl_SwivellingOut(&DblSwivelling);

  //The swiveling angle is in 0.05 degrees
  if (AdbMxb4Data_eHeadlampSide != eMountedUndef)
  {
    DblSwivelling.SwivelAngle[AdbMxb4Data_eHeadlampSide] = DblSwivelling.SwivelAngle[AdbMxb4Data_eHeadlampSide] / ADBMXB4DATA_DBLFACTOR;
    snDblCurvatureAngle = DblSwivelling.SwivelAngle[AdbMxb4Data_eHeadlampSide];
  }
  else
  {
    snDblCurvatureAngle = 0;
  }

  return snDblCurvatureAngle;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_GetMountingSide
///
/// \descr  
///
/// \param  - 
///
/// \return Left/Right mounting side
//-----------------------------------------------------------------------------
tieAdbHeadlampSide AdbMxb4Data_GetMountingSide(void)
{
  tieAdbHeadlampSide result;
  switch (AdbMxb4Data_eHeadlampSide) {
  case eMountedLeft:
    result = LeftHeadlamp;
    break;
  case eMountedRight:
    result = RightHeadlamp;
    break;
  default:
    result = UndefHeadlamp;
  }
  return result;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_ConvertCamObj
///
/// \descr  Convert camera object from RTE to application
///
/// \param  pCamObjectTL 
///
/// \return void 
//-----------------------------------------------------------------------------
void AdbMxb4Data_ConvertCamObj(tCamObjectTL* pCamObjectTL, uint8 ucObjIdx)
{
  tsRte_SigPrep_ClusterSigGroup1_sVal   sCamObjMsgGr1 = { 0 };
  tsRte_SigPrep_ClusterSigGroup2_sVal   sCamObjMsgGr2 = { 0 };
  tsRte_SigPrep_PerceiveSigGroup2_sVal  sPerceiveSigGroup2 = { 0 };
  tsCamObject_FrmCheck                  sCamObject_FrmCheck = { 0 };
  boolean                               boSigValid = FALSE;

  // [Isarescu Mihai: 04.01.2023] Map the rte ports to the correct cam objects
  switch (ucObjIdx) {
  case ADBMXB4DATA_CAMOBJ_1:
    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_00(&sCamObjMsgGr1);
    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_00(&sCamObjMsgGr2);
    break;
  case ADBMXB4DATA_CAMOBJ_2:
    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_01(&sCamObjMsgGr1);
    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_01(&sCamObjMsgGr2);
    break;
  case ADBMXB4DATA_CAMOBJ_3:
    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_02(&sCamObjMsgGr1);
    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_02(&sCamObjMsgGr2);
    break;
  case ADBMXB4DATA_CAMOBJ_4:
    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_03(&sCamObjMsgGr1);
    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_03(&sCamObjMsgGr2);
    break;
  case ADBMXB4DATA_CAMOBJ_5:
    (void)Rte_Read_SigPrep_ClusterSigGroup1_sVal_04(&sCamObjMsgGr1);
    (void)Rte_Read_SigPrep_ClusterSigGroup2_sVal_04(&sCamObjMsgGr2);
    break;
  default:
    // do nothing, message is initilized to 0
    break;
  }

  (void)Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02(&sPerceiveSigGroup2);

  // Check Cluster signals consistency, range and validity
  boSigValid = AdbMxb4Data_ValidityCheck(&sCamObject_FrmCheck, sCamObjMsgGr1, sCamObjMsgGr2, sPerceiveSigGroup2.eTrafficDetected, ucObjIdx);

  //WARNING: TSAG without GFHB is not possible because of the Trafficdeted! Configuration only possible with GFHB
  if ((boSigValid == FALSE) && (sPerceiveSigGroup2.eTrafficDetected != eTrffDet_False))
  {
    if (sCamObject_FrmCheck.ucClusterId != 0u && sCamObject_FrmCheck.ucClusterId != 255u)
    {
      // PRQA S 4394, 4544, 4393  12  // Cast and bitshift is needed for the mxb algorithm. 
      pCamObjectTL->Index = (sint16)sCamObject_FrmCheck.ucClusterId;
      pCamObjectTL->Type = (sint16)AdbMxb4Data_MapObjectType(sCamObject_FrmCheck.eClusterType);
      pCamObjectTL->HorPosLeft = (sint32)(((uint32)((sint32)(sCamObject_FrmCheck.nClusterAngleLeft))) << 17); // [Amish chavda:02-09-2021:The input from Siprep is divided by 0.2 due to resolution, so instead of shifting 16, we shift 17 , to multiply by 2 and match resolution in matlab]
      pCamObjectTL->HorPosRight = (sint32)(((uint32)((sint32)(sCamObject_FrmCheck.nClusterAngleRight))) << 17); // [Amish chavda:02-09-2021:The input from Siprep is divided by 0.2 due to resolution, so instead of shifting 16, we shift 17 , to multiply by 2 and match resolution in matlab]
      pCamObjectTL->HorPosSpeedLeft = (sint32)(((uint32)(sCamObject_FrmCheck.cClusterLeftAzimuthRate * 10)) << 16);
      pCamObjectTL->HorPosSpeedRight = ((sint32)(((uint32)(sCamObject_FrmCheck.cClusterRightAzimuthRate * 10)) << 16));
      pCamObjectTL->VerPosBottom = (sint32)(((uint32)((sint32)(sCamObject_FrmCheck.cClusterBottomAngle))) << 16);
      pCamObjectTL->VerPosTop = (sint32)(((uint32)((sint32)100)) << 16);                                // not available from camera, set to 10deg
      pCamObjectTL->Distance = (sint32)(((uint32)((sint32)(sCamObject_FrmCheck.unClusterMinDistance))) << 16);
      pCamObjectTL->DistanceLeft = (sint32)(((uint32)((sint32)(sCamObject_FrmCheck.unClusterLeftDistance))) << 16);
      pCamObjectTL->DistanceRight = (sint32)(((uint32)((sint32)(sCamObject_FrmCheck.unClusterRightDistance))) << 16);
      pCamObjectTL->Reflection = 0;
    }
    else
    {
      AdbMxb4Data_SetCamObjtoZero(pCamObjectTL);
    }
  }
  else if (boSigValid != FALSE)
  {
    // no values to pass because they are invalid 
    // LDMO-2567: To fix this issue priority is changed for invalid check and traffic not detected case
    AdbMxb4Data_SetCamObjtoZero(pCamObjectTL);
    pCamObjectTL->Index = (sint16)ADBMXB4DATA_CLUSTER_ID_INVALID;
  }
  else
  {
    // no values to pass because they are invalid or unavailable , turn off GFHB
    // LDMO-2567: To fix this issue priority is changed for invalid check and traffic not detected case
    AdbMxb4Data_SetCamObjtoZero(pCamObjectTL);
  }
  // PRQA S 5324 1  // Exceeds 7 function calls 
}

void AdbMxb4Data_ConvertCamObj_Percieve(tCamObjectTL* pCamObjectTL, uint8 ucObjIdx)
{
  tsRte_SigPrep_PerceiveSigGroup1_sVal sCamObjMsgGr1 = { 0 };
  tsRte_SigPrep_PerceiveSigGroup2_sVal sCamObjMsgGr2 = { 0 };
  tsCamObjectPerceive_FrmCheck         sCamObjectPerceive_FrmCheck = { 0 };
  boolean                              boSigValid = FALSE;

  // [Isarescu Mihai: 04.01.2023] Map the rte ports to the correct sign objects
  switch (ucObjIdx) {
  case ADBMXB4DATA_CAMOBJ_PERCEIVE_1:
    (void)Rte_Read_SigPrep_PerceiveSigGroup1_sVal_00(&sCamObjMsgGr1);
    (void)Rte_Read_SigPrep_PerceiveSigGroup2_sVal_00(&sCamObjMsgGr2);
    break;
  case ADBMXB4DATA_CAMOBJ_PERCEIVE_2:
    (void)Rte_Read_SigPrep_PerceiveSigGroup1_sVal_01(&sCamObjMsgGr1);
    (void)Rte_Read_SigPrep_PerceiveSigGroup2_sVal_01(&sCamObjMsgGr2);
    break;
  case ADBMXB4DATA_CAMOBJ_PERCEIVE_3:
    (void)Rte_Read_SigPrep_PerceiveSigGroup1_sVal_02(&sCamObjMsgGr1);
    (void)Rte_Read_SigPrep_PerceiveSigGroup2_sVal_02(&sCamObjMsgGr2);
    break;
  default:
    break;
  }

  boSigValid = AdbMxb4Data_ValidityCheck_Perceive(&sCamObjectPerceive_FrmCheck, sCamObjMsgGr1, sCamObjMsgGr2, ucObjIdx);

  // Take into consideration if other objects have invalid values
  AdbMxb4Data_ucInvalidTsag = (boSigValid != FALSE) ? (AdbMxb4Data_ucInvalidTsag | (uint8)(ADBMXB4DATA_0_BIT)) : (AdbMxb4Data_ucInvalidTsag & (uint8)(~ADBMXB4DATA_0_BIT));

  if (AdbMxb4Data_ucInvalidTsag == ADBMXB4DATA_ZERO_VALUE)
  {
    if (sCamObjectPerceive_FrmCheck.ucPerceiveId != 0u && sCamObjectPerceive_FrmCheck.ucPerceiveId != 255u)
    {
      // PRQA S 4394, 4544, 4393, 4390  12  // Cast and bitshift is need for the mxb algorithm 
      pCamObjectTL->Index = (sint16)sCamObjectPerceive_FrmCheck.ucPerceiveId;
      pCamObjectTL->Type = (sint16)ADBMXB4DATA_PERCIEVERFL_X_TYPE;
      pCamObjectTL->HorPosLeft = (sint32)(((uint32)((sint32)(sCamObjectPerceive_FrmCheck.nLeftAngle / 10))) << 16);   // [Tony Vornicu:22-03-2022:The input from Siprep unit is 0.01 due to resolution, so we devide by 10 to get the resolution of 0.1]
      pCamObjectTL->HorPosRight = (sint32)(((uint32)((sint32)(sCamObjectPerceive_FrmCheck.nRightAngle / 10))) << 16); // [Tony Vornicu:22-03-2022:The input from Siprep unit is 0.01 due to resolution, so we devide by 10 to get the resolution of 0.1]
      pCamObjectTL->HorPosSpeedLeft = (sint32)(((uint32)(sCamObjectPerceive_FrmCheck.cLeftAzimuthRate * 10)) << 16);
      pCamObjectTL->HorPosSpeedRight = ((sint32)(((uint32)(sCamObjectPerceive_FrmCheck.cRightAzimuthRate * 10)) << 16));
      pCamObjectTL->VerPosBottom = (sint32)(((uint32)((sint32)(sCamObjectPerceive_FrmCheck.nBottomAngle))) << 16);
      pCamObjectTL->VerPosTop = (sint32)(((uint32)((sint32)sCamObjectPerceive_FrmCheck.nTopAngle)) << 16);
      pCamObjectTL->Distance = (sint32)(((uint32)((sint32)(sCamObjectPerceive_FrmCheck.unDistance))) << 16);
      pCamObjectTL->DistanceLeft = (sint32)(((uint32)((sint32)(sCamObjectPerceive_FrmCheck.unDistance))) << 16);
      pCamObjectTL->DistanceRight = (sint32)(((uint32)((sint32)(sCamObjectPerceive_FrmCheck.unDistance))) << 16);
      pCamObjectTL->Reflection = (sint16)(sCamObjectPerceive_FrmCheck.ucBrightness);
    }
    else
    {
      AdbMxb4Data_SetCamObjtoZero(pCamObjectTL);
    }
  }
  else
  {
    AdbMxb4Data_SetCamObjtoZero(pCamObjectTL);
  }
  // PRQA S 5324 1  // Exceeds 7 function calls 
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_ConvertAdbChannel01
///
/// \descr  Convert AdbChannel from application to RTE 
///
/// \param  pAdbChannelLeft, pAdbChannelRight 
///
/// \return void 
//-----------------------------------------------------------------------------

void AdbMxb4Data_ConvertAdbChannel(tAdbChannelX* pChannelXLeft, tAdbChannelX* pChannelXRight, tieAdbMode eAdbMode, uint8 channelIdx)
{
  tAdbOut AdbOut;

  AdbOut.State = (uint8)eAdbMode;

  // fill left headlamp channel (Channel[0])
  if (eAdbMode == (tieAdbMode)Fault)  // workaround, no object (to be removed for next ADB-Version)
  {
    AdbMxb4Data_SetOutputChannelToZero(&(AdbOut.Channel[0]), eAdbMode);
  }
  else
  {
    AdbMxb4Data_SetOutputChannel(&(AdbOut.Channel[0]), pChannelXLeft, eAdbMode);
  }

  // fill right headlamp channel (Channel[1])
  if (eAdbMode == (tieAdbMode)Fault)  // workaround, no object (to be removed for next ADB-Version)
  {
    AdbMxb4Data_SetOutputChannelToZero(&(AdbOut.Channel[1]), eAdbMode);
  }
  else
  {
    AdbMxb4Data_SetOutputChannel(&(AdbOut.Channel[1]), pChannelXRight, eAdbMode);
  }

  // write Channel to RTE
  switch (channelIdx) {
  case ADBMXB4DATA_CHANNEL_1:
    (void)Rte_Write_ppsAdb_Out_sVal_0(&AdbOut); break;
  case ADBMXB4DATA_CHANNEL_2:
    (void)Rte_Write_ppsAdb_Out_sVal_1(&AdbOut); break;
  case ADBMXB4DATA_CHANNEL_3:
    (void)Rte_Write_ppsAdb_Out_sVal_2(&AdbOut); break;
  case ADBMXB4DATA_CHANNEL_4:
    (void)Rte_Write_ppsAdb_Out_sVal_3(&AdbOut); break;
  case ADBMXB4DATA_CHANNEL_5:
    (void)Rte_Write_ppsAdb_Out_sVal_4(&AdbOut); break;
  default:
    break;
  }
}

//-----------------------------------------------------------------------------
/// \brief AdbMxb4Data_SetOutputChannelToZero
///
/// \descr  Set the CamObj's to ZERO.
///
/// \param  tChannel* pAdbOutChannelTL
///
/// \param tieAdbMode nAdbMode
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void AdbMxb4Data_SetOutputChannelToZero(tChannel* pAdbOutChannelTL, tieAdbMode nAdbMode) {
  pAdbOutChannelTL->PowerFactor = (-1);
  pAdbOutChannelTL->MaximalIntensity = 0;
  pAdbOutChannelTL->NormalizedDimmingTimeUp = 0;
  pAdbOutChannelTL->NormalizedDimmingTimeDown = 0;
  pAdbOutChannelTL->EdgeLeft = (nAdbMode == (tieAdbMode)Fault) ? -500 : 0;		// LDMO-3776 in case of fault create a fake tunnel outside of view in order to not impact other light functions
  pAdbOutChannelTL->EdgeRight = (nAdbMode == (tieAdbMode)Fault) ? -490 : 0;		// LDMO-3776 in case of fault create a fake tunnel outside of view in order to not impact other light functions
  pAdbOutChannelTL->EdgeTop = 0;
  pAdbOutChannelTL->EdgeBottom = 0;
  pAdbOutChannelTL->Type = (nAdbMode == (tieAdbMode)Fault) ? 1 : 0;			// LDMO-2258 create an empty tunnel in case of fault in order to switch to country LD safely
  pAdbOutChannelTL->Distance = 0;
  pAdbOutChannelTL->DistanceLeft = 0;
  pAdbOutChannelTL->DistanceRight = 0;
}


//-----------------------------------------------------------------------------
/// \brief AdbMxb4Data_SetOutputChannel
///
/// \descr  Set the CamObj's to ZERO.
///
/// \param  tChannel* pAdbOutChannelTL
///
/// \param tAdbChannelX* pRefChannelTL
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void AdbMxb4Data_SetOutputChannel(tChannel* pAdbOutChannelTL, tAdbChannelX* pRefChannelTL, tieAdbMode nAdbMode) {
  pAdbOutChannelTL->PowerFactor = (sint16)(pRefChannelTL->PowerFactor);
  pAdbOutChannelTL->MaximalIntensity = (sint16)(pRefChannelTL->MaximalIntensity);
  pAdbOutChannelTL->NormalizedDimmingTimeUp = (uint8)(nAdbMode == (tieAdbMode)Off) ? 0 : (pRefChannelTL->NormalizedDimmingTimeUp);   // limited inside model to 250
  pAdbOutChannelTL->NormalizedDimmingTimeDown = (uint8)(nAdbMode == (tieAdbMode)Off) ? 0 : (pRefChannelTL->NormalizedDimmingTimeDown); // limited inside model to 250
  pAdbOutChannelTL->EdgeLeft = (sint16)(ASHRI32((pRefChannelTL->EdgeLeft), 16));
  pAdbOutChannelTL->EdgeRight = (sint16)(ASHRI32((pRefChannelTL->EdgeRight), 16));
  pAdbOutChannelTL->EdgeTop = (sint16)(ASHRI32((pRefChannelTL->EdgeTop), 16)); //+ Cod_AdbMxb4_VerticalAlignment_LeftOffset());
  pAdbOutChannelTL->EdgeBottom = (sint16)(ASHRI32((pRefChannelTL->EdgeBottom), 16));// + Cod_AdbMxb4_VerticalAlignment_LeftOffset());
  pAdbOutChannelTL->Type = pRefChannelTL->Type;// + Cod_AdbMxb4_VerticalAlignment_LeftOffset());
  pAdbOutChannelTL->Distance = (sint16)(ASHRI32((pRefChannelTL->Distance), 16));// + Cod_AdbMxb4_VerticalAlignment_LeftOffset());
  pAdbOutChannelTL->DistanceLeft = (sint16)(ASHRI32((pRefChannelTL->DistanceLeft), 16));// + Cod_AdbMxb4_VerticalAlignment_LeftOffset());
  pAdbOutChannelTL->DistanceRight = (sint16)(ASHRI32((pRefChannelTL->DistanceRight), 16));// + Cod_AdbMxb4_VerticalAlignment_LeftOffset());
}


//-----------------------------------------------------------------------------
/// \brief AdbMxb4Data_SetCamObjtoZero

///
/// \descr  Set the CamObj's to ZERO.
///
/// \param  tCamObjectTL* pCamObjectTL
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void AdbMxb4Data_SetCamObjtoZero(tCamObjectTL* pCamObjectTL)
{
  pCamObjectTL->Index = (sint16)0;
  pCamObjectTL->Type = (sint16)0;
  // PRQA S 1281, 2855 2  // Edges need to be assigned -50 and 50, the normal assignment of (-50<<16) and (50<<16) is undefined because of negative value shift.
  //pCamObjectTL->HorPosLeft		    = (sint32)0x00320000;		  // [Isarescu Mihai, 13.12.2022] workaround for the delay logic on object appearance, left edge needs to be max 50 deg with lsb 16 because of dissapearance/obj moving fast delay logic in MXB clustering
  //pCamObjectTL->HorPosRight	      = (sint32)0xFFCE0000;		  // [Isarescu Mihai, 13.12.2022] workaround for the delay logic on object appearance, right edge needs to be min -50 deg with lsb 16 because of dissapearance/obj moving fast delay logic in MXB clustering
  pCamObjectTL->HorPosLeft = (sint32)0;
  pCamObjectTL->HorPosRight = (sint32)0;
  pCamObjectTL->HorPosSpeedLeft = (sint32)0;
  pCamObjectTL->HorPosSpeedRight = (sint32)0;
  pCamObjectTL->VerPosBottom = (sint32)0;
  pCamObjectTL->VerPosTop = (sint32)0;
  pCamObjectTL->Distance = (sint32)0;
  pCamObjectTL->Reflection = (sint16)0;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_ValidityCheck
///
/// \descr  Cluster (Cam) object signal ranges are checked and their validity is reported 
///         for CAN frames 0x0E3, 0x0EB, 0x103, 0x10B, 0x123, 0x163, 0x16B, 0x183, 0x18B and 0x1AB
///
/// \param  *psCamObject_FrmCheck: Output RTE Cluster type object
///         sClusterSigGroup1:     Input1 Cam Object values
///         sClusterSigGroup2:     Input2 Cam Object values
///         eTraffDet:             Input Traffic Detected values
///         ucObjIdx:              Object Index
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean AdbMxb4Data_ValidityCheck(tsCamObject_FrmCheck* psCamObject_FrmCheck, tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, tsRte_SigPrep_ClusterSigGroup2_sVal sClusterSigGroup2, teRte_TrafficDetected eTraffDet, uint8 ucObjIdx)
{
  boolean boConsistencyCheckStatus = FALSE;
  boolean boCameraSignalsStatus = FALSE;
  boolean boCameraSignalsAvailableStatus = FALSE;
  boolean boAreCameraSignalsFailing = FALSE;
  boolean boSignalValidityCheck = FALSE;
  boolean boCameraSignalsAzimuthRateStatus = FALSE;
  boolean boSignalQualityStatus = FALSE;
  teRte_EtatPrincipSEV VESState = { 0 };

  if (sClusterSigGroup2.eClusterId.ucClusterId != ADBMXB4DATA_ZERO_VALUE)
  {
    // Perform a consistency check on parameters from Camera
    boConsistencyCheckStatus = AdbMxb4Data_ConsistencyCheck(sClusterSigGroup1, eTraffDet, ucObjIdx);

    // Perform a validity check on the Camera Signals to see if there are invalid signals
    boCameraSignalsStatus = AdbMxb4Data_InvalidCheck(sClusterSigGroup1, sClusterSigGroup2, &boAreCameraSignalsFailing, ucObjIdx);

    // Perform a availability check on the Camera Signals to see if there are unavailable signals
    boCameraSignalsAvailableStatus = AdbMxb4Data_UnavailableCheck(psCamObject_FrmCheck, sClusterSigGroup1, sClusterSigGroup2, boCameraSignalsStatus, boAreCameraSignalsFailing, ucObjIdx);

    // Compute Azimuth Rate for Left and Right
    boCameraSignalsAzimuthRateStatus = AdbMxb4Data_Compute_AzimuthRate(psCamObject_FrmCheck, sClusterSigGroup1, ucObjIdx);
  }
  else
  {
    //set cluster id to 0 
    psCamObject_FrmCheck->ucClusterId = 0u;

    // LDMO-3777
    // Reset flags in order to reset the timers
    AdbMxb4Data_sValidityTimers[ucObjIdx].boConstCheck_Flag = FALSE;
    AdbMxb4Data_sValidityTimers[ucObjIdx].boInvalCheck_Flag = FALSE;
    AdbMxb4Data_sValidityTimers[ucObjIdx].boUnavalCheck_Flag = FALSE;
    AdbMxb4Data_sAzimuthRate_UnavalCheckTimers[ucObjIdx].boUnavalCheck_Flag = FALSE;
  }

  boSignalQualityStatus = AdbMxb4Data_SignalQualityCheck(sClusterSigGroup1, sClusterSigGroup2);

  VESState = AdbMxb4Data_GetVESMainState();

  if (VESState != VESState_Stop)
  {
    // Write GFHB_DIAG to SysMonTx
    AdbMxb4Data_sGfhbDiag[ucObjIdx].boDiagGfhb = (boCameraSignalsStatus != FALSE) ||
      (boCameraSignalsAzimuthRateStatus != FALSE) ||
      (boSignalQualityStatus != FALSE) ||
      (boConsistencyCheckStatus != FALSE) ||
      (AdbMxb4Data_boYawSpeedDiag != FALSE) ? TRUE : FALSE;
  }
  else {
    // in case VESState is stop no fault will be sent.
    AdbMxb4Data_sGfhbDiag[ucObjIdx].boDiagGfhb = FALSE;
  }

  // Set Signal Quality value
  if ((boCameraSignalsAvailableStatus != FALSE) || (boCameraSignalsAzimuthRateStatus != FALSE))
  {
    // CAMERA_SIGNALS_AVAILABLE = False
    boSignalValidityCheck = TRUE;

  }
  else if (boCameraSignalsStatus != FALSE)
  {
    // CAMERA_SIGNALS = False
    boSignalValidityCheck = TRUE;
  }
  else
  {
    // CAMERA_SIGNALS_AVAILABLE = TRUE and CAMERA_SIGNALS = True
    boSignalValidityCheck = FALSE;
  }

  return (boSignalValidityCheck != FALSE) || (boSignalQualityStatus != FALSE) || (boConsistencyCheckStatus != FALSE) || (AdbMxb4Data_boYawSpeedDiag != FALSE) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_ConsistencyCheck
///
/// \descr  Cluster (Cam) object signal consistency is checked and their validity is reported 
///         for CAN frames 0x0E3, 0x0EB, 0x103, 0x10B and 0x123
///
/// \param  sInputSigVal: Input Cam Object values
///         eTraffDet:    Input Traffic Detected values
///         ucObjIdx:     Object Index
///
/// \return boolean: TRUE:  signal incosistent
///                  FALSE: signal consistent
//-----------------------------------------------------------------------------
STATIC_AL boolean AdbMxb4Data_ConsistencyCheck(tsRte_SigPrep_ClusterSigGroup1_sVal sInputSigVal, teRte_TrafficDetected eTraffDet, uint8 ucObjIdx)
{
  boolean boConsistencyCheckFailureStatus = FALSE;

  if ((sInputSigVal.eClusterMinDistance.unClusterMinDistance > sInputSigVal.eClusterLeftDistance.unClusterLeftDistance) ||
    (sInputSigVal.eClusterMinDistance.unClusterMinDistance > sInputSigVal.eClusterRightDistance.unClusterRightDistance) ||
    (sInputSigVal.eClusterAngleLeft.nClusterAngleLeft > sInputSigVal.eClusterAngleRight.nClusterAngleRight) ||
    (((sInputSigVal.eClusterMinDistance.unClusterMinDistance < ADBMXB4DATA_DISTANCE_2_METERS) ||
    (sInputSigVal.eClusterLeftDistance.unClusterLeftDistance < ADBMXB4DATA_DISTANCE_2_METERS) ||
      (sInputSigVal.eClusterRightDistance.unClusterRightDistance < ADBMXB4DATA_DISTANCE_2_METERS)) &&
      (eTraffDet == eTrffDet_True)))
  {
    // First time appearance of Consistency Check Failure
    if (AdbMxb4Data_sValidityTimers[ucObjIdx].boConstCheck_Flag == FALSE)
    {
      // Get time stamp
      AdbMxb4Data_sValidityTimers[ucObjIdx].ulConstCheck_StartTime = TimerGetTick();
      // Set Consistency Check Failure Flag
      AdbMxb4Data_sValidityTimers[ucObjIdx].boConstCheck_Flag = TRUE;
    }
    else
    {
      // Wait 300ms before setting the Consistency Check Failure Flag
      if (TimerGetTimeSince(AdbMxb4Data_sValidityTimers[ucObjIdx].ulConstCheck_StartTime) >= UTILTIME_MSEC(AdbMxb4Data_unObjectConfirmationTime))
      {
        // Set the Consistency Check Failure Status
        boConsistencyCheckFailureStatus = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
  }
  else if ((sInputSigVal.eClusterMinDistance.unClusterMinDistance <= sInputSigVal.eClusterLeftDistance.unClusterLeftDistance) &&
    (sInputSigVal.eClusterMinDistance.unClusterMinDistance <= sInputSigVal.eClusterRightDistance.unClusterRightDistance) &&
    (sInputSigVal.eClusterAngleLeft.nClusterAngleLeft <= sInputSigVal.eClusterAngleRight.nClusterAngleRight) &&
    ((sInputSigVal.eClusterMinDistance.unClusterMinDistance >= ADBMXB4DATA_DISTANCE_2_METERS) &&
    (eTraffDet == eTrffDet_True)))
  {
    // Clear the Consistency Check Failure Status
    boConsistencyCheckFailureStatus = FALSE;
    // Clear Consistency Check Failure Flag
    AdbMxb4Data_sValidityTimers[ucObjIdx].boConstCheck_Flag = FALSE;
  }
  else
  {
    // nothing to do
  }

  return boConsistencyCheckFailureStatus;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_InvalidCheck
///
/// \descr  Cluster (Cam) object signal validity is checked and their validity is reported 
///         for CAN frames 0x0E3, 0x0EB, 0x103, 0x10B, 0x123, 0x163, 0x16B, 0x183, 0x18B and 0x1AB
///
/// \param  sClusterSigGroup1:     Input Cam Object values
///         cClusterBottomAngle:   Input Cluster Bottom angle value
///         boConstCheck:          Consistency Check status
///         *pboIsCamSigFail:      Status indicating if Invalid Check has started to fail
///         ucObjIdx:              Object Index
///
/// \return boolean: TRUE:  signal invalid
///                  FALSE: signal valid
//-----------------------------------------------------------------------------
STATIC_AL  boolean AdbMxb4Data_InvalidCheck(tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, tsRte_SigPrep_ClusterSigGroup2_sVal sClusterSigGroup2, boolean *pboAreCamSigFail, uint8 ucObjIdx)
{
  // Local variable which is used to set each bit of it in case of signal out of range found
  uint8   ucSignalNotValid = 0u;
  boolean boInvalidCheckFailureStatus = FALSE;

  // Check H_CLUSTER_MIN_DISTANCE_E and HCLUSTERMINDISTANCE_X signals range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_HClusterMinDistance(sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_0_BIT) : ucSignalNotValid;
  // Check H_CLUSTER_DISTANCE_LEFT_E and HCLUSTERLEFTDISTANCE_X signals range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_HClusterDistance(sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_1_BIT) : ucSignalNotValid;
  // Check H_CLUSTER_DISTANCE_RIGHT_E and HCLUSTERRIGHTDISTANCE_X signals range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_HClusterDistance(sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_2_BIT) : ucSignalNotValid;
  // Check H_CLUSTER_ANGLE_LEFT_50D and HCLUSTERANGLELEFT_X signals range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_HClusterAngle(sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_3_BIT) : ucSignalNotValid;
  // Check H_CLUSTER_ANGLE_RIGHT_50D and HCLUSTERANGLERIGHT_X signals range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_HClusterAngle(sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_4_BIT) : ucSignalNotValid;
  // Check HCLUSTERBOTTOMANGLE_X signals range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_HClusterBottomAngle(sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_5_BIT) : ucSignalNotValid;

  if (ucSignalNotValid != ADBMXB4DATA_ZERO_VALUE)
  {
    // Invalid data is starting to fail, do not pass valid values any more
    *pboAreCamSigFail = TRUE;

    // set DTC U053B-81 
    Rte_Call_DemPrj_ReportErrorStatus((uint16)AdbMxb4Data_sCvmInvalid[ucObjIdx].eDemEventId, DEM_EVENT_STATUS_FAILED);

    // First time appearance of Invalid Check Failure
    if (AdbMxb4Data_sValidityTimers[ucObjIdx].boInvalCheck_Flag == FALSE)
    {
      // Get time stamp
      AdbMxb4Data_sValidityTimers[ucObjIdx].ulInvalCheck_StartTime = TimerGetTick();
      // Set Invalid Check Failure Flag
      AdbMxb4Data_sValidityTimers[ucObjIdx].boInvalCheck_Flag = TRUE;
    }
    else
    {
      // Wait 300ms before setting the Consistency Check Failure Flag
      if (TimerGetTimeSince(AdbMxb4Data_sValidityTimers[ucObjIdx].ulInvalCheck_StartTime) >= UTILTIME_MSEC(AdbMxb4Data_unObjectConfirmationTime))
      {
        // Set the Invalid Check Failure Status
        boInvalidCheckFailureStatus = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
  }
  else
  {
    // Clear the flag
    *pboAreCamSigFail = FALSE;
    // Clear the Invalid Check Failure Status
    boInvalidCheckFailureStatus = FALSE;
    // Clear Invalid Check Failure Flag
    AdbMxb4Data_sValidityTimers[ucObjIdx].boInvalCheck_Flag = FALSE;

    // reset DTC U053B-81 
    Rte_Call_DemPrj_ReportErrorStatus((uint16)AdbMxb4Data_sCvmInvalid[ucObjIdx].eDemEventId, DEM_EVENT_STATUS_PASSED);
  }

  return boInvalidCheckFailureStatus;
  // PRQA S 5328 1 //Architecture and readability
}

STATIC_AL  boolean AdbMxb4Data_SignalQualityCheck(tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, tsRte_SigPrep_ClusterSigGroup2_sVal sClusterSigGroup2)
{
  boolean boSignalQualityStatus = FALSE;
  // Check if Consistency Check has failed or if CAN communication is lost
  if ((sClusterSigGroup1.eSigQty == SIG_TIMEOUT) || (sClusterSigGroup2.eSigQty == SIG_TIMEOUT))
  {
    // Set the Invalid Check Failure Status
    boSignalQualityStatus = TRUE;
  }
  return (boSignalQualityStatus != FALSE) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_HClusterMinDistance
///
/// \descr  H_CLUSTER_MIN_DISTANCE_E and HCLUSTERMINDISTANCE_X CAN signals range check
///
/// \param  unInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_HClusterMinDistance(uint16 unInputSigVal)
{
  return ((unInputSigVal == ADBMXB4DATA_INVALID_HCLUSTERMINDISTANCE_X) ||
    ((unInputSigVal >= ADBMXB4DATA_INVALID_HCLUSTERMINDISTANCE_X_MIN_VAL) && (unInputSigVal <= ADBMXB4DATA_INVALID_HCLUSTERMINDISTANCE_X_MAX_VAL))) ? TRUE : FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_HClusterDistance
///
/// \descr  H_CLUSTER_DISTANCE_LEFT_E, HCLUSTERLEFTDISTANCE_X, H_CLUSTER_DISTANCE_RIGHT_E
///         and HCLUSTERRIGHTDISTANCE_X CAN signals range check
///
/// \param  unInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_HClusterDistance(uint16 unInputSigVal)
{
  return ((unInputSigVal == ADBMXB4DATA_INVALID_HCLUSTERDISTANCE_X) ||
    ((unInputSigVal >= ADBMXB4DATA_INVALID_HCLUSTERDISTANCE_X_MIN_VAL) && (unInputSigVal <= ADBMXB4DATA_INVALID_HCLUSTERDISTANCE_X_MAX_VAL))) ? TRUE : FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_HClusterAngle
///
/// \descr  H_CLUSTER_ANGLE_LEFT_50D, HCLUSTERANGLELEFT_X, H_CLUSTER_ANGLE_RIGHT_50D 
///         and HCLUSTERANGLERIGHT_X CAN signals range check
///
/// \param  nInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_HClusterAngle(sint16 nInputSigVal)
{
  return ((nInputSigVal == ADBMXB4DATA_INVALID_HCLUSTERANGLE_X) ||
    ((nInputSigVal >= ADBMXB4DATA_INVALID_HCLUSTERANGLE_X_MIN_VAL_1) && (nInputSigVal <= ADBMXB4DATA_INVALID_HCLUSTERANGLE_X_MAX_VAL_1)) ||
    ((nInputSigVal >= ADBMXB4DATA_INVALID_HCLUSTERANGLE_X_MIN_VAL_2) && (nInputSigVal <= ADBMXB4DATA_INVALID_HCLUSTERANGLE_X_MAX_VAL_2))) ? TRUE : FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_HClusterBottomAngle
///
/// \descr  HCLUSTERBOTTOMANGLE_X signals range check
///
/// \param  cInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_HClusterBottomAngle(sint8 cInputsigVal)
{
  return ((cInputsigVal == ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X) ||
    ((cInputsigVal >= ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X_MIN_VAL_1) && (cInputsigVal <= ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X_MAX_VAL_1)) ||
    ((cInputsigVal >= ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X_MIN_VAL_2) && (cInputsigVal <= ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X_MAX_VAL_2))) ? TRUE : FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_UnavailableCheck
///
/// \descr  Cluster (Cam) object signal availability is checked and their validity is reported 
///         for CAN frames 0x0E3, 0x0EB, 0x103, 0x10B, 0x123, 0x163, 0x16B, 0x183, 0x18B and 0x1AB
///
/// \param  *psOutputSig: Output RTE Cluster type object
///         sInputSigVal: Input Cam Object values
///         boCameraSignals: Camera Signals validity status
///         boIsCamSigFail:  Is validity check beginning to fail ?
///         ucObjIdx:        Object Index
///
/// \return boolean: TRUE:  signal invalid
///                  FALSE: signal valid
//-----------------------------------------------------------------------------
STATIC_AL boolean AdbMxb4Data_UnavailableCheck(tsCamObject_FrmCheck* psCamObject_FrmCheck, tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, tsRte_SigPrep_ClusterSigGroup2_sVal sClusterSigGroup2, boolean boCameraSignals, boolean boAreCamSigFail, uint8 ucObjIdx)
{
  // Local variable which is used to set each bit of it in case of signal are unavailable
  uint8   ucSignalUnavailable = 0u;
  boolean boUnavailableCheckFailureStatus = FALSE;

  // Check H_CLUSTER_DISTANCE_LEFT_E and HCLUSTERLEFTDISTANCE_X signals range
  ucSignalUnavailable = (AdbMxb4Data_UnavailableCheck_HClusterDistance(sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance) != FALSE) ? (ucSignalUnavailable | ADBMXB4DATA_0_BIT) : ucSignalUnavailable;
  // Check H_CLUSTER_DISTANCE_RIGHT_E and HCLUSTERRIGHTDISTANCE_X signals range
  ucSignalUnavailable = (AdbMxb4Data_UnavailableCheck_HClusterDistance(sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance) != FALSE) ? (ucSignalUnavailable | ADBMXB4DATA_1_BIT) : ucSignalUnavailable;
  // Check HCLUSTERBOTTOMANGLE_X signals range
  ucSignalUnavailable = (AdbMxb4Data_UnavailableCheck_HClusterBottomAngle(sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle) != FALSE) ? (ucSignalUnavailable | ADBMXB4DATA_2_BIT) : ucSignalUnavailable;

  // Different unavailable values for signals of frame 0xE3
  switch (ucObjIdx)
  {
  case ADBMXB4DATA_CAMOBJ_1:
    // Check H_CLUSTER_MIN_DISTANCE_E signal range
    ucSignalUnavailable = (AdbMxb4Data_UnavailableCheck_HClusterMinDistance_0E3(sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance) != FALSE) ? (ucSignalUnavailable | ADBMXB4DATA_3_BIT) : ucSignalUnavailable;
    // Check H_CLUSTER_ANGLE_LEFT_50D signal range
    ucSignalUnavailable = (AdbMxb4Data_UnavailableCheck_HClusterAngle_0E3(sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft) != FALSE) ? (ucSignalUnavailable | ADBMXB4DATA_4_BIT) : ucSignalUnavailable;
    // Check H_CLUSTER_ANGLE_RIGHT_50D signal range
    ucSignalUnavailable = (AdbMxb4Data_UnavailableCheck_HClusterAngle_0E3(sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight) != FALSE) ? (ucSignalUnavailable | ADBMXB4DATA_5_BIT) : ucSignalUnavailable;
    break;
  default:
    // Check HCLUSTERMINDISTANCE_X signal range (X = 2 to 5)
    ucSignalUnavailable = (AdbMxb4Data_UnavailableCheck_HClusterMinDistance_X(sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance) != FALSE) ? (ucSignalUnavailable | ADBMXB4DATA_3_BIT) : ucSignalUnavailable;
    // Check HCLUSTERANGLELEFT_X signal range (X = 2 to 5)
    ucSignalUnavailable = (AdbMxb4Data_UnavailableCheck_HClusterAngle_X(sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft) != FALSE) ? (ucSignalUnavailable | ADBMXB4DATA_4_BIT) : ucSignalUnavailable;
    // Check HCLUSTERANGLERIGHT_X signal range (X = 2 to 5)
    ucSignalUnavailable = (AdbMxb4Data_UnavailableCheck_HClusterAngle_X(sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight) != FALSE) ? (ucSignalUnavailable | ADBMXB4DATA_5_BIT) : ucSignalUnavailable;
    break;
  }


  if (boCameraSignals != FALSE)
  {
    // Set the Invalid Check Failure Status
    boUnavailableCheckFailureStatus = TRUE;
  }
  else if (ucSignalUnavailable != ADBMXB4DATA_ZERO_VALUE)
  {
    // First time appearance of Invalid Check Failure
    if (AdbMxb4Data_sValidityTimers[ucObjIdx].boUnavalCheck_Flag == FALSE)
    {
      // Get time stamp
      AdbMxb4Data_sValidityTimers[ucObjIdx].ulUnavalCheck_StartTime = TimerGetTick();
      // Set Invalid Check Failure Flag
      AdbMxb4Data_sValidityTimers[ucObjIdx].boUnavalCheck_Flag = TRUE;
    }
    else
    {
      // Wait 300ms before setting the Consistency Check Failure Flag
      if (TimerGetTimeSince(AdbMxb4Data_sValidityTimers[ucObjIdx].ulUnavalCheck_StartTime) >= UTILTIME_MSEC(AdbMxb4Data_unObjectConfirmationTime))
      {
        // Set the Invalid Check Failure Status
        boUnavailableCheckFailureStatus = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
  }
  else if (boAreCamSigFail != FALSE)
  {
    // do not pass values because a failure on invalid data has already started
  }
  else
  {
    // Clear the Invalid Check Failure Status
    boUnavailableCheckFailureStatus = FALSE;
    // Clear Invalid Check Failure Flag
    AdbMxb4Data_sValidityTimers[ucObjIdx].boUnavalCheck_Flag = FALSE;

    // Fill the signal values
    psCamObject_FrmCheck->ucClusterId = sClusterSigGroup2.eClusterId.ucClusterId;
    psCamObject_FrmCheck->eClusterType = sClusterSigGroup1.eClusterType;
    psCamObject_FrmCheck->nClusterAngleLeft = sClusterSigGroup1.eClusterAngleLeft.nClusterAngleLeft;
    psCamObject_FrmCheck->nClusterAngleRight = sClusterSigGroup1.eClusterAngleRight.nClusterAngleRight;
    psCamObject_FrmCheck->cClusterLeftAzimuthRate = sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate;
    psCamObject_FrmCheck->cClusterRightAzimuthRate = sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate;
    psCamObject_FrmCheck->cClusterBottomAngle = sClusterSigGroup2.eClusterBottomAngle.cClusterBottomAngle;
    psCamObject_FrmCheck->unClusterMinDistance = ADBMXB4DATA_CAMOBJDISRES * (sClusterSigGroup1.eClusterMinDistance.unClusterMinDistance);
    psCamObject_FrmCheck->unClusterLeftDistance = ADBMXB4DATA_CAMOBJDISRES * (sClusterSigGroup1.eClusterLeftDistance.unClusterLeftDistance);
    psCamObject_FrmCheck->unClusterRightDistance = ADBMXB4DATA_CAMOBJDISRES * (sClusterSigGroup1.eClusterRightDistance.unClusterRightDistance);
  }

  return boUnavailableCheckFailureStatus;
  // PRQA S 5328 1 //Architecture and readability
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_UnavailableCheck_HClusterMinDistance_0E3
///
/// \descr  H_CLUSTER_MIN_DISTANCE_E CAN signal unavailable range check
///
/// \param  unInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_UnavailableCheck_HClusterMinDistance_0E3(uint16 unInputSigVal)
{
  return ((unInputSigVal == ADBMXB4DATA_UNAVAILABLE_HCLUSTERMINDISTANCE_0E3_1) ||
    (unInputSigVal == ADBMXB4DATA_UNAVAILABLE_HCLUSTERMINDISTANCE_0E3_2)) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_UnavailableCheck_HClusterMinDistance_X
///
/// \descr  HCLUSTERMINDISTANCE_X CAN signals unavailable range check (X = 2 to 5)
///
/// \param  unInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_UnavailableCheck_HClusterMinDistance_X(uint16 unInputSigVal)
{
  return (unInputSigVal == ADBMXB4DATA_UNAVAILABLE_HCLUSTERMINDISTANCE_X) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_UnavailableCheck_HClusterDistance
///
/// \descr  H_CLUSTER_DISTANCE_LEFT_E, HCLUSTERLEFTDISTANCE_X, H_CLUSTER_DISTANCE_RIGHT_E
///         and HCLUSTERRIGHTDISTANCE_X CAN signals unavailable range check
///
/// \param  unInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_UnavailableCheck_HClusterDistance(uint16 unInputSigVal)
{
  return (unInputSigVal == ADBMXB4DATA_UNAVAILABLE_HCLUSTERDISTANCE_X) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_UnavailableCheck_HClusterAngle_0E3
///
/// \descr  H_CLUSTER_ANGLE_LEFT_50D and H_CLUSTER_ANGLE_RIGHT_50D 
///         CAN signals unavailable range check
///
/// \param  nInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_UnavailableCheck_HClusterAngle_0E3(sint16 nInputSigVal)
{
  return (nInputSigVal == ADBMXB4DATA_UNAVAILABLE_HCLUSTERANGLE_0E3) ? TRUE : FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_UnavailableCheck_HClusterAngle
///
/// \descr  HCLUSTERANGLELEFT_X and HCLUSTERANGLERIGHT_X
///         CAN signals unavailable range check
///
/// \param  nInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_UnavailableCheck_HClusterAngle_X(sint16 nInputSigVal)
{
  return (nInputSigVal == ADBMXB4DATA_UNAVAILABLE_HCLUSTERANGLE_X) ? TRUE : FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_HClusterBottomAngle
///
/// \descr  HCLUSTERBOTTOMANGLE_X signals unavailable check
///
/// \param  cInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_UnavailableCheck_HClusterBottomAngle(sint8 cInputsigVal)
{
  return (cInputsigVal == ADBMXB4DATA_UNAVAILABLE_HCLUSTERBOTTOMANGLE_X) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  SigPrep_RxCallbacks_Compute_AzimuthRate_ClusterSigGroup1
///
/// \descr  Check if AzimuthRate for Left and right are valid , invalid, or unavailable
///
/// \param  *psCamObject_FrmCheck: Output RTE Cluster type object
///         sClusterSigGroup1:     Input Cam Object values
///         ucObjIdx:              ID of object
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean AdbMxb4Data_Compute_AzimuthRate(tsCamObject_FrmCheck* psCamObject_FrmCheck, tsRte_SigPrep_ClusterSigGroup1_sVal sClusterSigGroup1, uint8 ucObjIdx)
{
  // Local variable which is used to set each bit of it in case of signal are unavailable or invalid
  uint8   ucLeftAzimuthRateNotValid = 0u;
  uint8   ucRightAzimuthRateNotValid = 0u;
  boolean boAzimuthRateUnavailable = FALSE;

  // Check H_CLUSTER_LEFT_AZIMUTH_RATE and HCLUSTERLEFTAZIMUTHRATE_X signals range
  ucLeftAzimuthRateNotValid = (AdbMxb4Data_RangeCheck_HClusterAzimuthRateLeft(sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate) != FALSE) ? (ucLeftAzimuthRateNotValid | ADBMXB4DATA_0_BIT) : ucLeftAzimuthRateNotValid;
  // Check H_CLUSTER_RIGHT_AZIMUTH_RATE and HCLUSTERRIGHTAZIMUTHRATE_X signals range
  ucRightAzimuthRateNotValid = (AdbMxb4Data_RangeCheck_HClusterAzimuthRateRight(sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate) != FALSE) ? (ucRightAzimuthRateNotValid | ADBMXB4DATA_0_BIT) : ucRightAzimuthRateNotValid;

  switch (ucObjIdx)
  {
  case ADBMXB4DATA_CAMOBJ_1:
    // Check H_CLUSTER_LEFT_AZIMUTH_RATE and HCLUSTERLEFTAZIMUTHRATE_X signals range
    ucLeftAzimuthRateNotValid = (AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_0E3(sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate) != FALSE) ? (ucLeftAzimuthRateNotValid | ADBMXB4DATA_1_BIT) : ucLeftAzimuthRateNotValid;
    // Check H_CLUSTER_RIGHT_AZIMUTH_RATE and HCLUSTERRIGHTAZIMUTHRATE_X signals range
    ucRightAzimuthRateNotValid = (AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_0E3(sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate) != FALSE) ? (ucRightAzimuthRateNotValid | ADBMXB4DATA_1_BIT) : ucRightAzimuthRateNotValid;
    break;
  default:
    // Check H_CLUSTER_LEFT_AZIMUTH_RATE and HCLUSTERLEFTAZIMUTHRATE_X signals range
    ucLeftAzimuthRateNotValid = (AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_X(sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate) != FALSE) ? (ucLeftAzimuthRateNotValid | ADBMXB4DATA_1_BIT) : ucLeftAzimuthRateNotValid;
    // Check H_CLUSTER_RIGHT_AZIMUTH_RATE and HCLUSTERRIGHTAZIMUTHRATE_X signals range
    ucRightAzimuthRateNotValid = (AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_X(sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate) != FALSE) ? (ucRightAzimuthRateNotValid | ADBMXB4DATA_1_BIT) : ucRightAzimuthRateNotValid;
    break;
  }

  if ((ucLeftAzimuthRateNotValid != ADBMXB4DATA_ZERO_VALUE) || (ucRightAzimuthRateNotValid != ADBMXB4DATA_ZERO_VALUE) ||
    (sClusterSigGroup1.eSigQty == SIG_TIMEOUT))
  {
    // First time appearance of Invalid Check Failure
    if (AdbMxb4Data_sAzimuthRate_UnavalCheckTimers[ucObjIdx].boUnavalCheck_Flag == FALSE)
    {
      // Get time stamp
      AdbMxb4Data_sAzimuthRate_UnavalCheckTimers[ucObjIdx].ulUnavalCheck_StartTime = TimerGetTick();
      // Set Invalid Check Failure Flag
      AdbMxb4Data_sAzimuthRate_UnavalCheckTimers[ucObjIdx].boUnavalCheck_Flag = TRUE;
    }
    else
    {
      // Wait 300ms before setting the Consistency Check Failure Flag
      if (TimerGetTimeSince(AdbMxb4Data_sAzimuthRate_UnavalCheckTimers[ucObjIdx].ulUnavalCheck_StartTime) >= UTILTIME_MSEC(AdbMxb4Data_unObjectConfirmationTime))
      {
        // Set the Invalid Check Failure Status
        boAzimuthRateUnavailable = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
  }
  else
  {
    // Clear the Invalid Check Failure Status
    boAzimuthRateUnavailable = FALSE;

    // Clear Invalid Check Failure Flag
    AdbMxb4Data_sAzimuthRate_UnavalCheckTimers[ucObjIdx].boUnavalCheck_Flag = FALSE;

    psCamObject_FrmCheck->cClusterLeftAzimuthRate = sClusterSigGroup1.eClusterLeftAzimuthRate.cClusterLeftAzimuthRate;
    psCamObject_FrmCheck->cClusterRightAzimuthRate = sClusterSigGroup1.eClusterRightAzimuthRate.cClusterRightAzimuthRate;
  }

  return boAzimuthRateUnavailable;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_0E3
///
/// \descr   H_CLUSTER_LEFT_AZIMUTH_RATE and H_CLUSTER_RIGHT_AZIMUTH_RATE
///          CAN signals range check
///
/// \param  cInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_0E3(sint8 cInputSigVal)
{
  return (cInputSigVal == ADBMXB4DATA_UNAVAILABLE_HCLUSTERAZIMUTHRATE_0E3) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_X
///
/// \descr   HCLUSTERLEFTAZIMUTHRATE_X and HCLUSTERRIGHTAZIMUTHRATE_X
///          CAN signals range check
///
/// \param  cInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_UnavailableCheck_HClusterAzimuthRate_X(sint8 cInputSigVal)
{
  return (cInputSigVal == ADBMXB4DATA_UNAVAILABLE_HCLUSTERAZIMUTHRATE_X) ? TRUE : FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_HClusterAzimuthRateLeft
///
/// \descr   H_CLUSTER_LEFT_AZIMUTH_RATE and HCLUSTERLEFTAZIMUTHRATE_X 
///          CAN signals range check
///
/// \param  cInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_HClusterAzimuthRateLeft(sint8 cInputSigVal)
{
  return ((cInputSigVal == ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_X) ||
    ((cInputSigVal >= ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_LR_X_MIN_VAL_1) && (cInputSigVal <= ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_L_MAX_VAL_1)) ||
    ((cInputSigVal >= ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_X_MIN_VAL_2) && (cInputSigVal <= ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_X_MAX_VAL_2))) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_HClusterAzimuthRateRight
///
/// \descr   H_CLUSTER_RIGHT_AZIMUTH_RATE and HCLUSTERRIGHTAZIMUTHRATE_X
///          CAN signals range check
///
/// \param  cInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_HClusterAzimuthRateRight(sint8 cInputSigVal)
{
  return ((cInputSigVal == ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_X) ||
    ((cInputSigVal >= ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_LR_X_MIN_VAL_1) && (cInputSigVal <= ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_R_MAX_VAL_1)) ||
    ((cInputSigVal >= ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_X_MIN_VAL_2) && (cInputSigVal <= ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_X_MAX_VAL_2))) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_HClusterAzimuthRateRight
///
/// \descr   H_CLUSTER_RIGHT_AZIMUTH_RATE and HCLUSTERRIGHTAZIMUTHRATE_X
///          CAN signals range check
///
/// \param  cInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
boolean AdbMxb4Data_Get_GfhbDiag(void)
{
  boolean boDiagGfhb = FALSE;

  for (uint8 ucIdx = 0u; ucIdx < ADBMXB4DATA_CAMOBJ_NR; ucIdx++)
  {
    boDiagGfhb |= AdbMxb4Data_sGfhbDiag[ucIdx].boDiagGfhb;
  }

  return boDiagGfhb;
}



//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_ValidityCheck_Perceive
///
/// \descr  Cluster (Cam) object signal ranges are checked and their validity is reported 
///         for CAN frames 0xAB, 0xC3, 0xCB, 0x12B, 0x143, 0x14B
///
/// \param  *psCamObjectPerceive_FrmCheck: Output RTE Cluster type object
///         sPerceiveSigGroup1:            Reflector 1 Cam Object values
///         sPerceiveSigGroup2:            Reflector 2 Cam Object values
///         ucObjIdx:                      Object Index
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean AdbMxb4Data_ValidityCheck_Perceive(tsCamObjectPerceive_FrmCheck* psCamObjectPerceive_FrmCheck, tsRte_SigPrep_PerceiveSigGroup1_sVal sPerceiveSigGroup1, tsRte_SigPrep_PerceiveSigGroup2_sVal sPerceiveSigGroup2, uint8 ucObjIdx)
{
  boolean boSignalValidityCheck = FALSE;

  boolean ucSignalNotAvailable = 0u;
  uint8 ucSignalNotValid = 0u;  // Local variable which is used to set each bit of it in case of signal out of range found

  // Check PERCEIVERFL_X_BRIGHTNESS signal range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_PerceiveBrightness(sPerceiveSigGroup1.eBrightness.ucBrightness) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_0_BIT) : ucSignalNotValid;
  // Check PERCEIVERFL_X_LEFTANGLE signal range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_PerceiveLeftRightAngle(sPerceiveSigGroup1.eLeftAngle.nLeftAngle) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_1_BIT) : ucSignalNotValid;
  // Check PERCEIVERFL_X_RIGHTANGLE signal range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_PerceiveLeftRightAngle(sPerceiveSigGroup1.eRightAngle.nRightAngle) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_2_BIT) : ucSignalNotValid;
  // Check PERCEIVERFL_X_TOPANGLE signal range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_PerceiveTopBottomAngle(sPerceiveSigGroup1.eTopAngle.nTopAngle) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_3_BIT) : ucSignalNotValid;
  // Check PERCEIVERFL_X_BOTTOMANGLE signal range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_PerceiveTopBottomAngle(sPerceiveSigGroup1.eBottomAngle.nBottomAngle) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_4_BIT) : ucSignalNotValid;
  // Check PERCEIVERFL_X_DISTANCE signal range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_PerceiveDistance(sPerceiveSigGroup1.eDistance.unDistance) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_5_BIT) : ucSignalNotValid;
  // Check PERCEIVERFL_X_LEFTAZIMUTHRATE signal range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_PerceiveAzimuthRate(sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_6_BIT) : ucSignalNotValid;
  // Check PERCEIVERFL_X_RIGHTAZIMUTHRATE signal range
  ucSignalNotValid = (AdbMxb4Data_RangeCheck_PerceiveAzimuthRate(sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate) != FALSE) ? (ucSignalNotValid | ADBMXB4DATA_7_BIT) : ucSignalNotValid;

  ucSignalNotAvailable = AdbMxb4Data_UnavailableCheck_Percieve(sPerceiveSigGroup1, sPerceiveSigGroup2);
  // Check for Timeout of CAN signals, invalid or unavailable values
  if ((sPerceiveSigGroup1.eSigQty == SIG_TIMEOUT) || (sPerceiveSigGroup2.eSigQty == SIG_TIMEOUT))
  {
    boSignalValidityCheck = TRUE;
  }
  else if (ucSignalNotValid != ADBMXB4DATA_ZERO_VALUE)
  {
    //if PerceiveId=0 do not set DTCs
    if (sPerceiveSigGroup2.ePerceiveId.ucPerceiveId != ADBMXB4DATA_ZERO_VALUE)
    {
      // set DTC U053B-81 
      Rte_Call_DemPrj_ReportErrorStatus((uint16)AdbMxb4Data_sPerceiveInvalid[ucObjIdx].eDemEventId, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      //do nothing
    }

    // First time appearance of Invalid Check Failure
    if (AdbMxb4Data_sValidityTimers_Perceive[ucObjIdx].boInvalCheck_Flag == FALSE)
    {
      // Get time stamp
      AdbMxb4Data_sValidityTimers_Perceive[ucObjIdx].ulInvalCheck_StartTime = TimerGetTick();
      // Set Invalid Check Failure Flag
      AdbMxb4Data_sValidityTimers_Perceive[ucObjIdx].boInvalCheck_Flag = TRUE;
    }
    else
    {
      // Wait 300ms before setting the Failure Flag
      if (TimerGetTimeSince(AdbMxb4Data_sValidityTimers_Perceive[ucObjIdx].ulInvalCheck_StartTime) >= UTILTIME_MSEC(AdbMxb4Data_unObjectConfirmationTime))
      {
        // Set the Invalid Check Failure Status
        boSignalValidityCheck = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
  }
  else
  {
    // Clear the Invalid Check Failure Status
    boSignalValidityCheck = FALSE;
    // Clear Invalid Check Failure Flag
    AdbMxb4Data_sValidityTimers_Perceive[ucObjIdx].boInvalCheck_Flag = FALSE;

    //if PerceiveId=0 do not set DTCs
    if (sPerceiveSigGroup2.ePerceiveId.ucPerceiveId != ADBMXB4DATA_ZERO_VALUE)
    {
      // reset DTC U053B-81 
      Rte_Call_DemPrj_ReportErrorStatus((uint16)AdbMxb4Data_sPerceiveInvalid[ucObjIdx].eDemEventId, DEM_EVENT_STATUS_PASSED);
    }
    else
    {
      //do nothing
    }

    if (ucSignalNotAvailable != ADBMXB4DATA_ZERO_VALUE) {
      // Reset sign
      psCamObjectPerceive_FrmCheck->ucPerceiveId = 0;
      psCamObjectPerceive_FrmCheck->nLeftAngle = 0;
      psCamObjectPerceive_FrmCheck->nRightAngle = 0;
      psCamObjectPerceive_FrmCheck->cLeftAzimuthRate = 0;
      psCamObjectPerceive_FrmCheck->cRightAzimuthRate = 0;
      psCamObjectPerceive_FrmCheck->nBottomAngle = 0;
      psCamObjectPerceive_FrmCheck->nTopAngle = 0;
      psCamObjectPerceive_FrmCheck->unDistance = 0;
      psCamObjectPerceive_FrmCheck->ucBrightness = 0;
    }
    else {
      // Fill the signal values
      psCamObjectPerceive_FrmCheck->ucPerceiveId = sPerceiveSigGroup2.ePerceiveId.ucPerceiveId;
      psCamObjectPerceive_FrmCheck->nLeftAngle = sPerceiveSigGroup1.eLeftAngle.nLeftAngle;
      psCamObjectPerceive_FrmCheck->nRightAngle = sPerceiveSigGroup1.eRightAngle.nRightAngle;
      psCamObjectPerceive_FrmCheck->cLeftAzimuthRate = sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate;
      psCamObjectPerceive_FrmCheck->cRightAzimuthRate = sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate;
      psCamObjectPerceive_FrmCheck->nBottomAngle = sPerceiveSigGroup1.eBottomAngle.nBottomAngle;
      psCamObjectPerceive_FrmCheck->nTopAngle = sPerceiveSigGroup1.eTopAngle.nTopAngle;
      psCamObjectPerceive_FrmCheck->unDistance = sPerceiveSigGroup1.eDistance.unDistance;
      psCamObjectPerceive_FrmCheck->ucBrightness = sPerceiveSigGroup1.eBrightness.ucBrightness;
    }
  }

  return boSignalValidityCheck;
} // PRQA S 5324 // Surpress exceed threshold of 7 function calls


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_UnavailableCheck_Percieve
///
/// \descr  Can data unavailable check for TSAG
///
/// \param  sPerceiveSigGroup1: Can Signal value
///
/// \param  sPerceiveSigGroup2: Can Signal value
///
/// \return boolean: TRUE: one of the signals is unavailable
///                  FALSE: all signals are available
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_UnavailableCheck_Percieve(tsRte_SigPrep_PerceiveSigGroup1_sVal sPerceiveSigGroup1, tsRte_SigPrep_PerceiveSigGroup2_sVal sPerceiveSigGroup2) {

  return
    (sPerceiveSigGroup1.eBottomAngle.nBottomAngle == ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_T_B_ANGLE ||
      sPerceiveSigGroup1.eTopAngle.nTopAngle == ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_T_B_ANGLE ||
      sPerceiveSigGroup1.eLeftAngle.nLeftAngle == ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_L_R_ANGLE ||
      sPerceiveSigGroup1.eRightAngle.nRightAngle == ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_L_R_ANGLE ||
      sPerceiveSigGroup1.eBrightness.ucBrightness == ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_BRIGHTNESS ||
      sPerceiveSigGroup1.eDistance.unDistance == ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_DISTANCE ||
      sPerceiveSigGroup2.eLeftAzimuthRate.cLeftAzimuthRate == ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_AZIMUTHRATE ||
      sPerceiveSigGroup2.eRightAzimuthRate.cRightAzimuthRate == ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_AZIMUTHRATE) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_PerceiveBrightness
///
/// \descr  PERCEIVERFL_X_BRIGHTNESS signal range check
///
/// \param  ucInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_PerceiveBrightness(uint8 ucInputSigVal)
{
  return ((ucInputSigVal == ADBMXB4DATA_INVALID_PERCEIVERFL_X_BRIGHTNESS) ||
    ((ucInputSigVal >= ADBMXB4DATA_INVALID_PERCEIVERFL_X_BRIGHTNESS_MIN_VAL) && (ucInputSigVal <= ADBMXB4DATA_INVALID_PERCEIVERFL_X_BRIGHTNESS_MAX_VAL))) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_PerceiveLeftRightAngle
///
/// \descr  PERCEIVERFL_X_LEFTANGLE  and PERCEIVERFL_X_RIGHTANGLE signals range check
///
/// \param  nInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_PerceiveLeftRightAngle(sint16 nInputSigVal)
{
  return ((nInputSigVal == ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE) ||
    ((nInputSigVal >= ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE_MIN_VAL_1) && (nInputSigVal <= ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE_MAX_VAL_1)) ||
    ((nInputSigVal >= ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE_MIN_VAL_2) && (nInputSigVal <= ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE_MAX_VAL_2))) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_PerceiveTopBottomAngle
///
/// \descr  PERCEIVERFL_X_TOPANGLE and PERCEIVERFL_X_BOTTOMANGLE signals range check
///
/// \param  nInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_PerceiveTopBottomAngle(sint16 nInputSigVal)
{
  return ((nInputSigVal == ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE) ||
    ((nInputSigVal >= ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE_MIN_VAL_1) && (nInputSigVal <= ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE_MAX_VAL_1)) ||
    ((nInputSigVal >= ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE_MIN_VAL_2) && (nInputSigVal <= ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE_MAX_VAL_2))) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_PerceiveDistance
///
/// \descr  PERCEIVERFL_X_DISTANCE signal range check
///
/// \param  unInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_PerceiveDistance(uint16 unInputSigVal)
{
  return ((unInputSigVal == ADBMXB4DATA_INVALID_PERCEIVERFL_X_DISTANCE) ||
    (unInputSigVal >= ADBMXB4DATA_INVALID_PERCEIVERFL_X_DISTANCE_MIN_VAL) && (unInputSigVal <= ADBMXB4DATA_INVALID_PERCEIVERFL_X_DISTANCE_MAX_VAL)) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  AdbMxb4Data_RangeCheck_PerceiveAzimuthRate
///
/// \descr  PERCEIVERFL_X_LEFTAZIMUTHRATE and PERCEIVERFL_X_RIGHTAZIMUTHRATE signals range check
///
/// \param  cInputSigVal: Can Signal value
///
/// \return boolean: TRUE: signal out of range
///                  FALSE: signal in range
//-----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_RangeCheck_PerceiveAzimuthRate(sint8 cInputSigVal)
{
  return ((cInputSigVal == ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE) ||
    ((cInputSigVal >= ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MIN_VAL_1) && (cInputSigVal <= ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MAX_VAL_1)) ||
    ((cInputSigVal >= ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MIN_VAL_2) && (cInputSigVal <= ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MAX_VAL_2))) ? TRUE : FALSE;
}


// EOF