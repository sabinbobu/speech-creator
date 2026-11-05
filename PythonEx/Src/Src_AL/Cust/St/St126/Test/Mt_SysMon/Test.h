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
#include <SysMon_Types.h>
#include <SysMonCheck_Data.h>
#include <SysMonRx_Callbacks.h>



//=============================================================================
// Typedefs
//=============================================================================
UINT8 IL_ui8_TabMessageStaticRcpData0[1];     /* DATA_ACQ_JDD_BSI_2 -0- */
UINT8 IL_ui8_TabMessageStaticRcpData1[4];     /* CPT_TEMPOREL -1- */
UINT8 IL_ui8_TabMessageStaticRcpData2[1];     /* ETAT_PRINCIP_SEV -2- */
UINT8 IL_ui8_TabMessageStaticRcpData3[1];     /* ETAT_RESEAU_ELEC -3- */
UINT8 IL_ui8_TabMessageStaticRcpData4[1];     /* SCROLLING_TI -4- */
UINT8 IL_ui8_TabMessageStaticRcpData5[1];     /* ETAT_CLIGNOTANTS -5- */
UINT8 IL_ui8_TabMessageStaticRcpData6[1];     /* WARNING_MODE -6- */
UINT8 IL_ui8_TabMessageStaticRcpData7[1];     /* CTRL_TI_L_F_S -7- */
UINT8 IL_ui8_TabMessageStaticRcpData8[1];     /* CTRL_TI_R_F_S -8- */
UINT8 IL_ui8_TabMessageStaticRcpData9[1];     /* E2E_CRC_VSM_34E -9- */
UINT8 IL_ui8_TabMessageStaticRcpData10[1];    /* CTRL_DRL_L -10- */
UINT8 IL_ui8_TabMessageStaticRcpData11[1];    /* CTRL_DRL_R -11- */
UINT8 IL_ui8_TabMessageStaticRcpData12[1];    /* CTRL_FL_L_F -12- */
UINT8 IL_ui8_TabMessageStaticRcpData13[1];    /* E2E_ALIVE_VSM_34E -13- */
UINT8 IL_ui8_TabMessageStaticRcpData14[1];    /* CTRL_AFS -14- */
UINT8 IL_ui8_TabMessageStaticRcpData15[1];    /* CTRL_FL_R_F -15- */
UINT8 IL_ui8_TabMessageStaticRcpData16[1];    /* CTRL_HB_FLASH -16- */
UINT8 IL_ui8_TabMessageStaticRcpData17[1];    /* CTRL_HB_L -17- */
UINT8 IL_ui8_TabMessageStaticRcpData18[1];    /* CTRL_HB_R -18- */
UINT8 IL_ui8_TabMessageStaticRcpData19[1];    /* CTRL_LB_L -19- */
UINT8 IL_ui8_TabMessageStaticRcpData20[1];    /* CTRL_PL_L_F -20- */
UINT8 IL_ui8_TabMessageStaticRcpData21[1];    /* CTRL_S_M_L_F -21- */
UINT8 IL_ui8_TabMessageStaticRcpData22[1];    /* CTRL_PL_R_F -22- */
UINT8 IL_ui8_TabMessageStaticRcpData23[1];    /* CTRL_LB_R -23- */
UINT8 IL_ui8_TabMessageStaticRcpData24[1];    /* CTRL_S_M_R_F -24- */
UINT8 IL_ui8_TabMessageStaticRcpData25[1];    /* ETAT_FEUX_STATIONNEMENT -25- */
UINT8 IL_ui8_TabMessageStaticRcpData26[1];    /* GFHB_CMD -26- */
UINT8 IL_ui8_TabMessageStaticRcpData27[1];    /* LOW_BEAM_BOOST_ALLOWED -27- */
UINT8 IL_ui8_TabMessageStaticRcpData28[1];    /* AIMING_MODE_ACTIVATION -28- */
UINT8 IL_ui8_TabMessageStaticRcpData29[1];    /* PEDESTRIAN_ALLOWED -29- */
UINT8 IL_ui8_TabMessageStaticRcpData30[1];    /* CONFIG_VHL -30- */
UINT8 IL_ui8_TabMessageStaticRcpData31[1];    /* MOTORWAY_DETECTION -31- */
UINT8 IL_ui8_TabMessageStaticRcpData32[1];    /* DELAY_FMH -32- */
UINT8 IL_ui8_TabMessageStaticRcpData33[2];    /* EXT_LIGHTNING_ANIMATION_REQ -33- */
UINT8 IL_ui8_TabMessageStaticRcpData34[1];    /* ETAT_FEUX_CROIST -34- */
UINT8 IL_ui8_TabMessageStaticRcpData35[1];    /* ETAT_MAR -35- */
UINT8 IL_ui8_TabMessageStaticRcpData36[1];    /* MODE_CONFIG_VEHICLE -36- */
UINT8 IL_ui8_TabMessageStaticRcpData37[2];    /* VITESSE_LACET -37- */
UINT8 IL_ui8_TabMessageStaticRcpData38[2];    /* PRESSION_MAITRE_CYL -38- */
UINT8 IL_ui8_TabMessageStaticRcpData39[1];    /* ETAT_FEE -39- */
UINT8 IL_ui8_TabMessageStaticRcpData40[2];    /* VITESSE_VEHICULE_ROUES -40- */
UINT8 IL_ui8_TabMessageStaticRcpData41[1];    /* CPT_PROCESS_4B_38D -41- */
UINT8 IL_ui8_TabMessageStaticRcpData42[1];    /* CHKSUM_TRME_DYN_UC_FREIN -42- */
UINT8 IL_ui8_TabMessageStaticRcpData43[1];    /* VVH_INDISP -43- */
UINT8 IL_ui8_TabMessageStaticRcpData44[1];    /* SIGNE_CONSIGNE_SITE_D_RX -44- */
UINT8 IL_ui8_TabMessageStaticRcpData45[2];    /* CONSIGNE_SITE_D_RX -45- */
UINT8 IL_ui8_TabMessageStaticRcpData46[1];    /* CMD_REF_SITE_D_RX -46- */
UINT8 IL_ui8_TabMessageStaticRcpData47[1];    /* DYN_BENDING_BEAM_FAULT_L_RX -47- */
UINT8 IL_ui8_TabMessageStaticRcpData48[1];    /* AUTO_BRAKING_PRESSURE -48- */
UINT8 IL_ui8_TabMessageStaticRcpData49[1];    /* EFCMNT_PDLE_ACCEL -49- */
UINT8 IL_ui8_TabMessageStaticRcpData50[1];    /* VOLONTE_COND -50- */
UINT8 IL_ui8_TabMessageStaticRcpData51[1];    /* DIAG_INTEGRA_ELEC -51- */
UINT8 IL_ui8_TabMessageStaticRcpData52[1];    /* MODE_DIAG -52- */
UINT8 IL_ui8_TabMessageStaticRcpData53[1];    /* EFFAC_DEFAUT_DIAG -53- */
UINT8 IL_ui8_TabMessageStaticRcpData54[1];    /* DIAG_MUX_ON_BODY -54- */
UINT8 IL_ui8_TabMessageStaticRcpData55[1];    /* PHASE_VIE -55- */
UINT8 IL_ui8_TabMessageStaticRcpData56[1];    /* DEM_EFFAC_DEF -56- */
UINT8 IL_ui8_TabMessageStaticRcpData57[1];    /* INTERD_MEMO_DEF -57- */
UINT8 IL_ui8_TabMessageStaticRcpData58[1];    /* INH_ECLAIRAGE_VIRAGE_DYN -58- */
UINT8 IL_ui8_TabMessageStaticRcpData59[2];    /* ASSIETTE_VEHICULE -59- */
UINT8 IL_ui8_TabMessageStaticRcpData60[1];    /* CTRL_CL_L -60- */
UINT8 IL_ui8_TabMessageStaticRcpData61[1];    /* CTRL_CL_R -61- */
UINT8 IL_ui8_TabMessageStaticRcpData62[1];    /* CTRL_SBL_L -62- */
UINT8 IL_ui8_TabMessageStaticRcpData63[1];    /* CTRL_SBL_R -63- */
UINT8 IL_ui8_TabMessageStaticRcpData64[3];    /* KM_TOTAL -64- */
UINT8 IL_ui8_TabMessageStaticRcpData65[1];    /* PERCEIVERFL_1_BRIGHTNESS -65- */
UINT8 IL_ui8_TabMessageStaticRcpData66[2];    /* PERCEIVERFL_1_LEFTANGLE -66- */
UINT8 IL_ui8_TabMessageStaticRcpData67[2];    /* PERCEIVERFL_1_RIGHTANGLE -67- */
UINT8 IL_ui8_TabMessageStaticRcpData68[2];    /* PERCEIVERFL_1_TOPANGLE -68- */
UINT8 IL_ui8_TabMessageStaticRcpData69[2];    /* PERCEIVERFL_1_BOTTOMANGLE -69- */
UINT8 IL_ui8_TabMessageStaticRcpData70[2];    /* PERCEIVERFL_1_DISTANCE -70- */
UINT8 IL_ui8_TabMessageStaticRcpData71[1];    /* PERCEIVERFL_2_BRIGHTNESS -71- */
UINT8 IL_ui8_TabMessageStaticRcpData72[2];    /* PERCEIVERFL_2_LEFTANGLE -72- */
UINT8 IL_ui8_TabMessageStaticRcpData73[2];    /* PERCEIVERFL_2_RIGHTANGLE -73- */
UINT8 IL_ui8_TabMessageStaticRcpData74[2];    /* PERCEIVERFL_2_TOPANGLE -74- */
UINT8 IL_ui8_TabMessageStaticRcpData75[2];    /* PERCEIVERFL_2_BOTTOMANGLE -75- */
UINT8 IL_ui8_TabMessageStaticRcpData76[2];    /* PERCEIVERFL_2_DISTANCE -76- */
UINT8 IL_ui8_TabMessageStaticRcpData77[1];    /* PERCEIVERFL_3_BRIGHTNESS -77- */
UINT8 IL_ui8_TabMessageStaticRcpData78[2];    /* PERCEIVERFL_3_LEFTANGLE -78- */
UINT8 IL_ui8_TabMessageStaticRcpData79[2];    /* PERCEIVERFL_3_RIGHTANGLE -79- */
UINT8 IL_ui8_TabMessageStaticRcpData80[2];    /* PERCEIVERFL_3_TOPANGLE -80- */
UINT8 IL_ui8_TabMessageStaticRcpData81[2];    /* PERCEIVERFL_3_BOTTOMANGLE -81- */
UINT8 IL_ui8_TabMessageStaticRcpData82[2];    /* PERCEIVERFL_3_DISTANCE -82- */
UINT8 IL_ui8_TabMessageStaticRcpData83[2];    /* H_CLUSTER_MIN_DISTANCE_E -83- */
UINT8 IL_ui8_TabMessageStaticRcpData84[2];    /* H_CLUSTER_DISTANCE_LEFT_E -84- */
UINT8 IL_ui8_TabMessageStaticRcpData85[2];    /* H_CLUSTER_DISTANCE_RIGHT_E -85- */
UINT8 IL_ui8_TabMessageStaticRcpData86[2];    /* H_CLUSTER_ANGLE_LEFT_50D -86- */
UINT8 IL_ui8_TabMessageStaticRcpData87[2];    /* H_CLUSTER_ANGLE_RIGHT_50D -87- */
UINT8 IL_ui8_TabMessageStaticRcpData88[1];    /* H_CLUSTER_RIGHT_AZIMUTH_RATE -88- */
UINT8 IL_ui8_TabMessageStaticRcpData89[1];    /* H_CLUSTER_LEFT_AZIMUTH_RATE -89- */
UINT8 IL_ui8_TabMessageStaticRcpData90[1];    /* HCLUSTERTYPE_1 -90- */
UINT8 IL_ui8_TabMessageStaticRcpData91[2];    /* HCLUSTERMINDISTANCE_2 -91- */
UINT8 IL_ui8_TabMessageStaticRcpData92[2];    /* HCLUSTERLEFTDISTANCE_2 -92- */
UINT8 IL_ui8_TabMessageStaticRcpData93[2];    /* HCLUSTERRIGHTDISTANCE_2 -93- */
UINT8 IL_ui8_TabMessageStaticRcpData94[2];    /* HCLUSTERANGLELEFT_2 -94- */
UINT8 IL_ui8_TabMessageStaticRcpData95[2];    /* HCLUSTERANGLERIGHT_2 -95- */
UINT8 IL_ui8_TabMessageStaticRcpData96[1];    /* HCLUSTERRIGHTAZIMUTHRATE_2 -96- */
UINT8 IL_ui8_TabMessageStaticRcpData97[1];    /* HCLUSTERLEFTAZIMUTHRATE_2 -97- */
UINT8 IL_ui8_TabMessageStaticRcpData98[1];    /* HCLUSTERTYPE_2 -98- */
UINT8 IL_ui8_TabMessageStaticRcpData99[2];    /* HCLUSTERMINDISTANCE_3 -99- */
UINT8 IL_ui8_TabMessageStaticRcpData100[2];   /* HCLUSTERLEFTDISTANCE_3 -100- */
UINT8 IL_ui8_TabMessageStaticRcpData101[2];   /* HCLUSTERRIGHTDISTANCE_3 -101- */
UINT8 IL_ui8_TabMessageStaticRcpData102[2];   /* HCLUSTERANGLELEFT_3 -102- */
UINT8 IL_ui8_TabMessageStaticRcpData103[2];   /* HCLUSTERANGLERIGHT_3 -103- */
UINT8 IL_ui8_TabMessageStaticRcpData104[1];   /* HCLUSTERRIGHTAZIMUTHRATE_3 -104- */
UINT8 IL_ui8_TabMessageStaticRcpData105[1];   /* HCLUSTERLEFTAZIMUTHRATE_3 -105- */
UINT8 IL_ui8_TabMessageStaticRcpData106[1];   /* HCLUSTERTYPE_3 -106- */
UINT8 IL_ui8_TabMessageStaticRcpData107[2];   /* HCLUSTERMINDISTANCE_4 -107- */
UINT8 IL_ui8_TabMessageStaticRcpData108[2];   /* HCLUSTERLEFTDISTANCE_4 -108- */
UINT8 IL_ui8_TabMessageStaticRcpData109[2];   /* HCLUSTERRIGHTDISTANCE_4 -109- */
UINT8 IL_ui8_TabMessageStaticRcpData110[2];   /* HCLUSTERANGLELEFT_4 -110- */
UINT8 IL_ui8_TabMessageStaticRcpData111[2];   /* HCLUSTERANGLERIGHT_4 -111- */
UINT8 IL_ui8_TabMessageStaticRcpData112[1];   /* HCLUSTERRIGHTAZIMUTHRATE_4 -112- */
UINT8 IL_ui8_TabMessageStaticRcpData113[1];   /* HCLUSTERLEFTAZIMUTHRATE_4 -113- */
UINT8 IL_ui8_TabMessageStaticRcpData114[1];   /* HCLUSTERTYPE_4 -114- */
UINT8 IL_ui8_TabMessageStaticRcpData115[2];   /* HCLUSTERMINDISTANCE_5 -115- */
UINT8 IL_ui8_TabMessageStaticRcpData116[2];   /* HCLUSTERLEFTDISTANCE_5 -116- */
UINT8 IL_ui8_TabMessageStaticRcpData117[2];   /* HCLUSTERRIGHTDISTANCE_5 -117- */
UINT8 IL_ui8_TabMessageStaticRcpData118[2];   /* HCLUSTERANGLELEFT_5 -118- */
UINT8 IL_ui8_TabMessageStaticRcpData119[2];   /* HCLUSTERANGLERIGHT_5 -119- */
UINT8 IL_ui8_TabMessageStaticRcpData120[1];   /* HCLUSTERRIGHTAZIMUTHRATE_5 -120- */
UINT8 IL_ui8_TabMessageStaticRcpData121[1];   /* HCLUSTERLEFTAZIMUTHRATE_5 -121- */
UINT8 IL_ui8_TabMessageStaticRcpData122[1];   /* HCLUSTERTYPE_5 -122- */
UINT8 IL_ui8_TabMessageStaticRcpData123[1];   /* PERCEIVEEFL_1_ID -123- */
UINT8 IL_ui8_TabMessageStaticRcpData124[1];   /* PERCEIVERFL_1_LEFTAZIMUTHRATE -124- */
UINT8 IL_ui8_TabMessageStaticRcpData125[1];   /* PERCEIVERFL_1_RIGHTAZIMUTHRATE -125- */
UINT8 IL_ui8_TabMessageStaticRcpData126[1];   /* PERCEIVEEFL_2_ID -126- */
UINT8 IL_ui8_TabMessageStaticRcpData127[1];   /* PERCEIVERFL_2_LEFTAZIMUTHRATE -127- */
UINT8 IL_ui8_TabMessageStaticRcpData128[1];   /* PERCEIVERFL_2_RIGHTAZIMUTHRATE -128- */
UINT8 IL_ui8_TabMessageStaticRcpData129[1];   /* PERCEIVEEFL_3_ID -129- */
UINT8 IL_ui8_TabMessageStaticRcpData130[1];   /* PERCEIVERFL_3_LEFTAZIMUTHRATE -130- */
UINT8 IL_ui8_TabMessageStaticRcpData131[1];   /* PERCEIVERFL_3_RIGHTAZIMUTHRATE -131- */
UINT8 IL_ui8_TabMessageStaticRcpData132[1];   /* TRAFFICDETECTED -132- */
UINT8 IL_ui8_TabMessageStaticRcpData133[1];   /* HCLUSTERCLSUBTYPE_1 -133- */
UINT8 IL_ui8_TabMessageStaticRcpData134[1];   /* HCLUSTERBOTTOMANGLE_1 -134- */
UINT8 IL_ui8_TabMessageStaticRcpData135[1];   /* HCLUSTERID_1 -135- */
UINT8 IL_ui8_TabMessageStaticRcpData136[1];   /* HCLUSTERCLSUBTYPE_2 -136- */
UINT8 IL_ui8_TabMessageStaticRcpData137[1];   /* HCLUSTERBOTTOMANGLE_2 -137- */
UINT8 IL_ui8_TabMessageStaticRcpData138[1];   /* HCLUSTERID_2 -138- */
UINT8 IL_ui8_TabMessageStaticRcpData139[1];   /* HCLUSTERCLSUBTYPE_3 -139- */
UINT8 IL_ui8_TabMessageStaticRcpData140[1];   /* HCLUSTERBOTTOMANGLE_3 -140- */
UINT8 IL_ui8_TabMessageStaticRcpData141[1];   /* HCLUSTERID_3 -141- */
UINT8 IL_ui8_TabMessageStaticRcpData142[1];   /* HCLUSTERCLSUBTYPE_4 -142- */
UINT8 IL_ui8_TabMessageStaticRcpData143[1];   /* HCLUSTERBOTTOMANGLE_4 -143- */
UINT8 IL_ui8_TabMessageStaticRcpData144[1];   /* HCLUSTERID_4 -144- */
UINT8 IL_ui8_TabMessageStaticRcpData145[1];   /* HCLUSTERCLSUBTYPE_5 -145- */
UINT8 IL_ui8_TabMessageStaticRcpData146[1];   /* HCLUSTERBOTTOMANGLE_5 -146- */
UINT8 IL_ui8_TabMessageStaticRcpData147[1];   /* HCLUSTERID_5 -147- */
UINT8 IL_ui8_TabMessageStaticRcpData148[1];   /* LVL_REF_STATE_R_RX -148- */
UINT8 IL_ui8_TabMessageStaticRcpData149[1];   /* LVL_STEPLOSS_R_RX -149- */
UINT8 IL_ui8_TabMessageStaticRcpData150[1];   /* LVL_TEMPERATURE_R_RX -150- */
UINT8 IL_ui8_TabMessageStaticRcpData151[1];   /* LVL_ELEC_R_RX -151- */
UINT8 IL_ui8_TabMessageStaticRcpData152[1];   /* LVL_VOLT_R_RX -152- */
UINT8 IL_ui8_TabMessageStaticRcpData153[1];   /* SIGN_POS_LVL_R_RX -153- */
UINT8 IL_ui8_TabMessageStaticRcpData154[2];   /* POSITION_SITE_D_RX -154- */
UINT8 IL_ui8_TabMessageStaticRcpData155[1];   /* DYN_BENDING_BEAM_FAULT_R_RX -155- */
UINT8 IL_ui8_TabMessageStaticRcpData156[8];   /* OVERALL_DAT_VSM_34E_E2E -156- */
UINT8 IL_ui8_TabMessageStaticRcpData157[1];   /* TYPE_DIR -157- */
UINT8 IL_ui8_TabMessageStaticRcpData158[2];   /* VEH_PATH_CURVATURE -158- */
UINT8 IL_ui8_TabMessageStaticRcpData159[8];   /* OVERALL_DAT_ABR_38D_CHKSUM -159- */

typedef struct
{
  //input
  boolean boReq_Input;
  TIMER   ulTimeMs_Input;
  //internal
  TIMER   ulCommandStart;
  boolean boStartStopTimer;
  boolean boTimeOut;
}tsSysMonCheck_TiTimerCfg;


//=============================================================================
// Defines
//=============================================================================
#define SYSMONTX_CALLBACKS_DIAG_TI_OK                    0x01u
#define SYSMONTX_CALLBACKS_DIAG_TI_NOK                   0x02u
#define SYSMONRX_CALLBACKS_CRCERR_TIMEOUT                2000u
#define SYSMONRX_CALLBACKS_ALIVEERR_TIMEOUT              2000u
#define SYSMONRX_CALLBACKS_SPEED_INVALID                 2000u
#define SYSMONRX_CALLBACKS_CRCERR_TIMER                     0u
#define SYSMONRX_CALLBACKS_ALIVEERR_TIMER                   1u
#define SYSMONRX_CALLBACKS_VEH_SPEED_TIMER                  2u
#define SYSMONRX_CALLBACKS_VVH_DISP_TIMER                   3u
#define SYSMONRX_CALLBACKS_NUMBER_OF_TIMERS                 4u


//=============================================================================
// Global variable stubs ( registers, global variables from other modules which are referenced in the module )
//=============================================================================
tNvmPara_CodingArea    CodingDummy;
const LPTMR_ConfigType LPTMR_Config;

EECO_TE_RxIndicator APPLI_ui32_Hs6DatVsm34eIndicator;

CONF_TAC_ChunkIdListArray CONF_Au8_ChunkListInsidePdu1 = {
DF_TO_UINT8(CONF_D_FRONT_LIGHT_DATA)
};

CONF_TA_PduCharacArray const CONF_AS_PduPara =
{
  {
    DF_TO_UINT32(100),
    OVERALL_DAT_VSM_34E_E2E,
    (EECO_TEP_RxIndicatorPtr)&APPLI_ui32_Hs6DatVsm34eIndicator,
    DF_TO_UINT8(CONF_D_NB_CHUNKS_PDU1),
    CONF_Au8_ChunkListInsidePdu1
  }
};

STATIC_AL TIMER  ulTimersFrameLost[CANRX_NR_EVENTS] = { 0u };


//=============================================================================
// Module global variables
//=============================================================================
extern boolean                                           SysMonRx_boRxInitStatus;
extern boolean                                           SysMonRx_boCbDeactivateStatus;
extern teRte_MountingSide                                SysMonRx_eMountingSide;
extern boolean                                           SysMonTx_boActivateTx;
extern boolean                                           SysMonTx_eEcuSide;
extern tsSysMon_RxFrameInfoConst                         asSysMonCanRxFrameInfoConst[];
extern tsSysMon_TxFrameInfoConst                         asSysMonCanTxFrameInfoConst[];
extern boolean                                           SysMonCheck_boInitialized;
extern boolean                                           SysMonCheck_Data_boIsCodingDataValid;
extern boolean                                           SysMonCheck_Data_boAreFuSaParam_Invalid;
extern tsRte_TgtLedSig0_ASIL*                            SysMonCheck_LedCtrl_pTargetLed_ASIL;
extern tsRte_TgtLedSig0*                                 SysMonCheck_LedCtrl_pTargetLed;
extern tsSysMonCheck_FUSA_LB_ASIL                        SysMonCheck_FUSA_LB_ASIL;
extern tsSysMonCheck_FUSA_TI_ASIL                        SysMonCheck_FUSA_TI_ASIL;
extern tSysMonRx_Signal_Low_Beam                         SysMonRx_ASIL_sSignalLowBeam;
extern tSysMonRx_Signal_Life_Phase                       SysMonRx_ASIL_sSignalLifePhase;
extern tSysMonRx_Signal_Speed                            SysMonRx_ASIL_sSignalSpeed;
extern tSysMonRx_Signal_VES_Main_State                   SysMonRx_ASIL_sSignalVESMainState;
extern tSysMonRx_Signal_Turn_Indicator                   SysMonRx_ASIL_sSignalTurnIndicator;
extern tSysMonCheck_Data_FuSaParamValid                  SysMonCheck_Data_eAreFuSaParamValid;
extern tSysMonCheck_Data_LedChParam                      SysMonCheck_Data_aLedChParam[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];
extern tsRte_TgtLedSig0                                  SysMonCheck_aLedTarget[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];
extern tsRte_TgtLedSig0_ASIL                             SysMonCheck_LedTarget_ASIL;
extern boolean                                           SysMonCheck_Data_IsLowBeamEnabled;
extern boolean                                           SysMonCheck_Data_IsTurnIndEnabled;
extern tsRteCodingParameters                             SysMonCheck_Data_sCodingParam;
extern boolean                                           SysMonCheck_Data_boFuSaIntegrityCheckPerformed;
extern boolean                                           SysMonCheck_Data_boCrc32OverCoding;
extern tsSysMonCheck_Data_EftData                        SysMonCheck_Data_sEftData;
extern void                                              SysMonCheck_RteAccess_Get_ChannelState(uint8_fast ucIdx, tsSysMon_aChannelState *psChannelState);
extern uint8                                             SysMonCheck_RteAccess_Get_VoltageRange(void);
extern tsSysMonRx_TimerCfg                               SysMonRx_Callbacks_sTimerCfg[SYSMONRX_CALLBACKS_NUMBER_OF_TIMERS];
extern STATIC_AL tSysMonLbEmergencyOperationData         SysMonRx_ASIL_EmergencyOperationData_LowBeam;
extern STATIC_AL boolean                                 SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation;
extern STATIC_AL boolean                                 SysMonRx_ASIL_boEmergencyOperation_FinalLowBeamStatus;
extern STATIC_AL boolean                                 SysMonRx_ASIL_boDiagLowBeamStatus;
extern STATIC_AL boolean                                 SysMonRx_ASIL_boEmergencyOperation_FinalTurnIndicatorStatus;
extern STATIC_AL boolean                                 SysMonRx_ASIL_boDiagTurnIndicatorStatus;
extern STATIC_AL tSysMonTiEmergencyOperationData         SysMonRx_ASIL_EmergencyOperationData_TurnIndicator;
extern           tSysMonCheck_Data_FuSaParam             SysMonCheck_Data_FuSaParam_raw;
extern CONST_AL tNvmPara_CodingArea*                     SysMonCheck_Data_pCodingArea;
extern STATIC_AL boolean                                 SysMonCheck_boCrc32OverCoding;
extern STATIC_AL boolean                                 SysMonRx_ASIL_boEmergencyOperationLowBeam;
extern STATIC_AL boolean                                 SysMonRx_ASIL_boEmergencyOperationTurnIndicator;
extern STATIC_AL tsSysMonRx_LowBeamSignal                SysMonRx_Callbacks_sLowBeamSignal;
extern STATIC_AL tsSysMonRx_LifePhaseSignal              SysMonRx_Callbacks_sLifePhaseSignal;
extern STATIC_AL teSysMonRx_SpeedSignal                  SysMonRx_Callbacks_sSpeedSignal;
extern STATIC_AL teRte_SigQty                            SysMonRx_Callbacks_eVESMainStateSignal;
extern STATIC_AL tsSysMonRx_TurnIndicatorSignal          SysMonRx_Callbacks_sTurnIndicatorSignal;
extern STATIC_AL EECO_TE_ProfileOneChunkStatus           SysMonRx_Callbacks_pte_ChunkStateE2E;
extern STATIC_AL CONST_AL tSysMonCheck_Data_LedChParam*  SysMonCheck_LedtCtrl_pLedChParam;
extern tsSysMon_ErrorHandler                             SysMonCheck_LedDiag_asErrorHandler[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];
extern tsSysMon_Error                                    SysMonCheck_LedDiag_sLed_Debounce;
extern STATIC_AL boolean                                 SysMonCheck_InternalCom_boLedStateCrcError_ASIL;
extern STATIC_AL boolean                                 SysMonCheck_InternalCom_boTgtLed_FaultStatus_ASIL;
extern STATIC_AL boolean                                 SysMonCheck_InternalCom_boTgtLed_FaultStatus_SysMon_ASIL;
extern STATIC_AL boolean                                 SysMonCheck_InternalCom_boInternalComErrActive;
extern STATIC_AL tSysMon_RxCyclicCounters                SysMonRx_sRedundencyCounters;
extern STATIC_AL uint32                                  SysMonRx_ulCycleCounter;
extern STATIC_AL boolean                                 SysMonCheck_boTurnIndicatorDiagStatus;
extern STATIC_AL NM_ModeType                             SysMonRx_eNMMode;
extern STATIC_AL boolean                                 SysMonCheck_Data_boIsTiScrollingPresent;
extern STATIC_AL uint32                                  SysMonCheck_Data_ulComputedFusaCrc;
extern STATIC_AL boolean                                 SysMonCheck_Data_boCrc32RamFail;
extern STATIC_AL boolean                                 SysMonCheck_Data_boCrc32RomFail;
extern STATIC_AL boolean                                 SysMonCheck_boCodingFailureDiagLowBeam;
extern STATIC_AL boolean                                 SysMonCheck_boCodingFailureDiagTurnIndicator;
extern STATIC_AL tSysMon_FuSaChannelsStatusReaction      SysMonCheck_sFuSaChannelsStatusReaction;
extern STATIC_AL boolean                                 SysMonRx_Callbacks_boTiDegarde;
extern STATIC_AL tsSysMon_DiagMuxState                   SysMon_RxCallbacks_sDiagMuxOnPwtState;
extern STATIC_AL uint8                                   SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_LENGTH_38D];
extern STATIC_AL boolean                                 SysMonCheck_boTICommandValue;
extern STATIC_AL tsRte_LedChFbit                         SysMonCheck_LedChFbit;
extern STATIC_AL boolean                                 SysMonRx_Callbacks_boFirstFrameRec;
extern STATIC_AL teSysMon_WarningMode                    SysMonRx_Callbacks_eTiWarningMode;
extern STATIC_AL tsSysMonCheck_TiTimerCfg                SysMonCheck_sTiTimerCfg[2];
extern STATIC_AL uint16                                  SysMonCheck_unDELAY_TI_NOT_REQUESTED;

// STATIC variables inside functions
boolean                   boCrcFailure;
boolean                   boTimeoutFailure;
boolean                   boNoFailure;
boolean                   boSetLowBeamInvalid;
boolean                   boInvalidFailure;
boolean                   boNoFailure;
boolean                   boSetLifePhaseInvalid;
boolean                   boSetTurnIndicatorInvalid;
boolean                   boSetSpeedInvalid;
boolean                   boSetVESMainStateInvalid;
boolean                   boCodingRamCheck;
boolean                   boCheckTiScrl;
boolean                   boTiScrlCheck;
boolean                   boCheckTiScrlTimerStart;
uint32                    ulCounter;
uint8                     ucProccesCounterOld;
TIMER                     ulCheckTiScrlTimer_us;
TIMER                     ulCrcTimer;
boolean                   boGetDebounceCoding;
boolean                   boDemEfacTrig;
boolean                   ucDemEfacCnt;
boolean                   boTimerStatus;
uint8                     ucCheckSumFrameCounter;
boolean                   boChkSumDTCSet;
uint8                     ucProcCounter;
boolean                   boProcCounterDTCSet;
uint8                     ucValidSigQtyCounter;;
uint16                    SysMonCheck_unMpuTest_1minute = 0u;
tsSysMon_Diag_ErrHandler  asErrorHandler[SYSMON_CFG_MAX_BUCK_DRV];
TIMER                     ulCycleTimer[SYSMON_CFG_MAX_BUCK_DRV];
TIMER                     ulGeneralTimer[SYSMON_CFG_MAX_BUCK_DRV];

// dummy for Sys Mon
void WdgM_SetLocalCheckPoint(uint8 ucId)
{
  ;
}


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
        0u                                                // ADC FACTOR Vboost
      }
    }
    }
};


//=============================================================================
// Module function declarations
//=============================================================================
// ctaaSysMonRx.c
extern void                                        riSysMonRxInit(void);
extern void                                        rpSysMonRx_Cycle(void);
extern void                                        reSysMonRx_EnableCallbacks(void);

// SysMon_E2E.c
extern teRte_SigQty                                SysMon_E2EGetChunkState(Tu8_Int CONST_AL unChunkId, EECO_TEP_ProfileOneChunkStatusPtr CONST_AL pte_ChunkStateE2E);

// SysMonCheck_LedCtrl.c
extern           void                              SysMonCheck_LedCtrl_Init(CONST_AL tsRte_TgtLedSig0* CONST_AL paTargetLed, tsRte_TgtLedSig0_ASIL* CONST_AL paTargetLed_ASIL);
extern           void                              SysMonCheck_LedCtrl_Cycle(void);
extern STATIC_AL void                              SysMonCheck_LedCtrl_EvaluateLightSourceReq(void);
extern           void                              SysMonCheck_LedDiag_Init(void);
extern           boolean                           SysMonCheck_LedDiag_IsLightSourceErrorFree(uint8 ucChIdx);
extern           boolean                           SysMonCheck_LedDiag_IsLightSourceSpiErrorFree(uint8 ucChIdx);
extern           boolean                           SysMonCheck_LedDiag_IsTiLightSourceErrorFree(void);
extern           void                              SysMonCheck_Set_CodingFailureDiagLowBeamStatus(boolean boDiagLbStatus);
extern           void                              SysMonCheck_Set_CodingFailureDiagTurnIndicatorStatus(boolean boDiagLbStatus);
extern           void                              SysMonCheck_ResetLbStatusReaction(void);
extern           void                              SysMonCheck_ResetTiStatusReaction(void);
extern tSysMon_FuSaChannelsStatusReaction          SysMonCheck_Get_LbTiFuSa_OffStatus(void);
extern void                                        SysMonCheck_InternalCom_SetInternalComErrActive(boolean boStatus);
extern void                                        SysMonCheck_Ti_DiagWindow(void);
extern void                                        SysMonCheck_RteAccess_Get_TiFailureStatus(boolean *pboStatus);
extern void                                        SysMonCheck_RteAccess_Get_ElecSupState(teSysMon_EngineState *pData);
extern uint8                                       SysMonCheck_CtrlTiDelayStatus(const boolean boReqInput, const TIMER ulTimeMs, const sint8 scTiTimerSel);
extern uint8                                       SysMoncheck_LedDiag_ErrorHandler(uint8_fast ucCh, uint8 ucChStatus);
extern uint8                                       SysMonCheck_LedDiag_ErrorDebounce(uint8_fast ucChId, uint8 ucErrStatus);
extern boolean                                     SysMonCheck_TI_Diag_Status(void);
extern boolean                                     SysMonCheck_InternalCom_IsComErrActive(void);
extern boolean                                     SysMonCheck_Get_TgtLed_FaultStatus_ASIL(void);
extern boolean                                     SysMonCheck_GetTurnIndicatorCommandValue(void);
extern boolean                                     SysMonCheck_InternalCom_LedState_CheckCrc(tsRte_LedStates* pLedStates_ASIL);
extern boolean                                     SysMonCheck_InternalCom_TgtLed_FaultStatus_ASIL_CheckCrc(tsRte_TgtLedSig0_FaultStatus_ASIL* pTgtLed_FaultStatus_ASIL);
extern boolean                                     SysMonCheck_TiDelayStatus(tsSysMonCheck_TiTimerCfg *sTiCfg, const sint8 scTiTimerSel);
extern boolean                                     SysMonCheck_LedDiag_RetainErrorReaction(uint8_fast ucChannelIdx, tSysMon_FuSaChannelsStatusReaction sFuSaChannelsStatusReaction);
extern void                                        SysMonCheck_VerifyTiNonFuSaActivation(void);

// SysMonCheck_LedDiag.c
extern void                                        SysMonCheck_LedDiag_Cycle(void);

// SysMonRx.c
extern void                                        SysMonRx_Init(void);
extern void                                        SysMonRx_HandleRxFrame(uint8 ucFrmIdx);
extern void                                        SysMonRx_ComM_DisableCallbacks(void);
extern void                                        SysMonRx_ComM_EnableCallbacks(void);
extern void                                        reSysMonRx_HS6_DAT_VSM_2AE_Received(void);
extern void                                        reSysMonRx_HS6_DAT_VSM_2AE_NotReceived(void);
extern void                                        reSysMonRx_HS6_DAT_VSM_34E_Received(void);
extern void                                        reSysMonRx_HS6_DAT_VSM_34E_NotReceived(void);
extern void                                        reSysMonRx_HS6_COMMANDES_VSM_036_Received(void);
extern void                                        reSysMonRx_HS6_COMMANDES_VSM_036_NotReceived(void);
extern void                                        reSysMonRx_HS6_DAT_BSI_432_Received(void);
extern void                                        reSysMonRx_HS6_DAT_BSI_432_NotReceived(void);
extern void                                        reSysMonRx_HS6_DYN_ABR_38D_Received(void);
extern void                                        reSysMonRx_HS6_DYN_ABR_38D_NotReceived(void);
extern void                                        SysMonRx_ASIL_EmergencyOperation(void);
extern void                                        SysMonRx_Callbacks_GetLowBeamSignal(uint8 *pucValue, teRte_SigQty *peSigQty);
extern void                                        SysMonRx_Callbacks_GetLifePhaseSignal(teRte_PhaseVie *peValue, teRte_SigQty *peSigQty);
extern void                                        SysMonRx_Callbacks_GetSpeedSignal(uint16 *punSpeedValue, teRte_SigQty *peSigQty);
extern void                                        SysMonRx_Callbacks_GetVESMainStateSignal(teRte_SigQty *peSigQty);
extern void                                        SysMonRx_Callbacks_GetTurnIndicatorSignal(uint8 *pucValue, teRte_SigQty *peSigQty);
extern boolean                                     SysMonRx_Callbacks_Hb_Cmd_OtherCond(void);
extern boolean                                     SysMonRx_Callbacks_Timeout(CONST_AL boolean boReqInput, CONST_AL TIMER ulTimeMs, CONST_AL uint8 ucTiTimerSel);
extern boolean                                     SysMonRx_Callbacks_HandleDelayStatus(tsSysMonRx_TimerCfg *psTimersCfg, CONST_AL uint8 ucTimerSel);

// SysMonRx_ASIL.c
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Cycle(void);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Refresh(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_CheckDataAndCases(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_HandleLowBeamDiag(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Valid(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_ActivateLowBeam(void);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_DeactivateLowBeam(void);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_FollowLowBeam(void);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_SetDiagLowBeam(void);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_ClearDiagLowBeam(void);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_HandleLowBeam(tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicator(tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_ON(tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_OFF(tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_ON(tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_OFF(tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Valid(tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_Compute_LowBeamState(void);
extern STATIC_AL void                              SysMonRx_ASIL_Compute_LB_PhaseVieState(void);
extern STATIC_AL void                              SysMonRx_ASIL_Compute_TI_PhaseVieState(void);
extern STATIC_AL void                              SysMonRx_ASIL_Compute_TurnIndicatorState(void);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Refresh(tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL void                              SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicatorDiag(tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
extern STATIC_AL boolean                           SysMonRx_ASIL_Check_TI_Scrolling(void);
extern SysMon_EnumLowBeamState                     SysMonRx_ASIL_GetLowBeamState(void);

// SysMonRx_Callbacks.c
extern           void                              SysMon_RxCallbacks_HS6_DAT_VSM_2AE(teSysMon_RxFrameState eSysMonRxState);
extern           void                              SysMon_RxCallbacks_HS6_DAT_VSM_34E(teSysMon_RxFrameState eSysMonRxState);
extern           void                              SysMon_RxCallbacks_HS6_COMMANDES_VSM_036(teSysMon_RxFrameState eSysMonRxState);
extern           void                              SysMon_RxCallbacks_HS6_DAT_BSI_432(teSysMon_RxFrameState eSysMonRxState);
extern           void                              SysMon_RxCallbacks_HS6_DYN_ABR_38D(teSysMon_RxFrameState eSysMonRxState);
extern STATIC_AL void                              SysMonRx_Callbacks_RangeCheck_LightDynAbr(tsRte_SysMon_VehicleSpeed *psOutputSig, tsSysMon_RxSpeedFrmCheck sInputSig, teRte_SigQty *peSigQty);
extern STATIC_AL teRte_ModeConfigVehicle           SysMonRx_Callbacks_Compute_ConfigVhl(uint8 ucConfigVhl);
extern STATIC_AL void                              SysMonRx_Callbacks_Compute_AfsMode(tsRte_SysMonAfsSignals *psOutputSig, uint8 ucAfsMode);
extern STATIC_AL teRte_GfHb_Cmd                    SysMonRx_Callbacks_Compute_GfhbCmd(uint8 ucGfhbCmd);
extern STATIC_AL teRte_SigQty                      SysMonRx_Callbacks_Compute_VESMainState(tsRte_SysMon_VehNetState *psOutputSig, uint8 ucInputSig);
extern STATIC_AL void                              SysMonRx_Callbacks_Compute_EletricalNetworkState(tsRte_SysMon_VehNetState *psOutputSig, uint8 ucInputSig);
extern STATIC_AL uint8                             SysMonRx_Callbacks_Compute_TurnIndicatorCmd(uint8 ucTiCmd);
extern STATIC_AL teRte_SigQty                      SysMonRx_Callbacks_EvaluateCrcAndAliveDtcs(teRte_SigQty eSigQty, teRte_SigQty eOldSigQty);
extern STATIC_AL boolean                           SysMonRx_Callbacks_CheckSumCheck(const uint8 ucRxData[], uint8 ucDLC);
extern STATIC_AL boolean                           SysMonRx_Callbacks_ProcessCntCheck(const uint8 ucCmpProc);

// SysMonTx.c
extern STATIC_AL void                              SysMonTx_FramesTimerInit(void);
extern STATIC_AL void                              SysMonTx_FramesProcessing(void);
extern STATIC_AL boolean                           SysMonTx_TimeoutCheck(uint8 ucFrmIdx);
extern           void                              SysMonTx_Init(void);
extern           void                              SysMonTx_Cycle0(void);
extern           void                              SysMonTx_ComM_ActivateTxBufer(void);
extern           void                              SysMonTx_ComM_DeactivateTxBuffer(void);
extern           void                              LGM_HS6_DIAG_DRVLED_Sent(void);
extern           void                              reSysMonTx_ActivateTxBufer(void);

// SysMonTx_Callbacks.c
extern           void                              SysMon_TxCallbacks_CyclicFrame_457(void);
extern           void                              SysMon_TxCallbacks_CyclicFrame_477(void);

// SysMonCheck_Data.c
extern STATIC_AL void                              SysMonCheck_ReadRTE(void);
extern STATIC_AL void                              SysMonCheck_WriteRTE(void);
extern STATIC_AL void                              SysMonCheck_EmergModeMinimumBrightnessCheck(void);
extern STATIC_AL void                              SysMonCheck_Cycle10ms_HandleLowBeamAndTurnIndicator(void);
extern STATIC_AL void                              SysMonCheck_CheckMinPWMandCurrent(uint8 ucChannelIdx);
extern STATIC_AL void                              SysMonCheck_Data_FuSaCodingIntegrityCheck(void);
extern STATIC_AL void                              SysMonCheck_Data_GetEftData(tsSysMonCheck_Data_EftData * CONST_AL pEftData);
extern STATIC_AL boolean                           SysMonCheck_Data_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
extern STATIC_AL boolean                           SysMonCheck_Data_FuSaParamRangeCheckTI(void);
extern           void                              SysMonCheck_TriggerCddLed_TurnIndicator_Off(void);
extern           void                              SysMonCheck_Data_Cycle10ms_FuSaMonitoring(void);
extern           void                              SysMonCheck_Data_SetCodingDataSatus(boolean boIsCodingDataValid);
extern           void                              SysMonCheck_Cycle0(void);
extern           void                              SysMonCheck_Data_ComputeFuSaParam(void);
extern           void                              SysMonCheck_Data_CheckEFT_ECUVARCFG_LED(void);
extern           void                              SysMonCheck_Data_RamMCodingMirrorCheck(void);
extern           void                              SysMonCheck_CheckMinPWMandCurrent(uint8 ucChannelIdx);
extern           void                              SysMonCheck_TriggerCddLed_LowBeam(uint8 ucValue);
extern           void                              SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_tLFName eLEDChannelParamName);
extern           void                              SysMonCheck_Cycle10ms_HandleTurnIndicatorFuSaBehaviour(boolean boTiCmd);
extern           void                              SysMonCheck_Data_Set_Crc32RomFailure(boolean boCrc32RomFail);
extern           void                              SysMonCheck_TurnOffChannel(uint8 ucChannelIdx);
extern           void                              SysMonCheck_Cycle10ms_HandleTurnIndicatorAndLowBeamDiagFeedback(void);
extern           void                              SysMonRx_Callbacks_GetDiagMuxState(boolean *pboValue);
extern           void                              SysMonCheck_Data_Set_Crc32RamFailure(boolean boCrc32RamFail);
extern           uint8                             SysMonCheck_Data_Get_ucFUSA_LB_FS_BEHAVIOUR_ASIL(void);
extern           uint8                             SysMonCheck_Data_Get_ucFUSA_TI_FS_BEHAVIOUR_ASIL(void);
extern           uint8                             SysMonCheck_Data_Get_IsLowBeamEnabled(void);
extern           uint8                             SysMonCheck_Data_Get_IsTurnIndEnabled(void);
extern           uint32                            SysMonCheck_Data_CalcComputedFuSaParamCrc32(void);
extern           boolean                           SysMonCheck_Data_CodingDataValidation(void);
extern           boolean                           SysMonCheck_Data_FuSaParamRangeCheckLB(void);
extern           boolean                           SysMonCheck_Data_IsNbOfFuSaChannelsAllowed(void);
extern           boolean                           SysMonCheck_Data_IsTiScrollingPresent(void);
extern           boolean                           SysMonCheck_Data_Get_TiScrollingPresent(void);
extern           boolean                           SysMonCheck_Data_AreAllLedChSupportedByHw(void);
extern           boolean                           SysMonCheck_Data_AreFuSaParam_Invalid(void);
extern           boolean                           SysMonCheck_Data_IsCodingDataValid(void);
extern           boolean                           SysMonCheck_Data_IsTurnIndicatorFuSa(uint8 ucFuSaIdx);
extern           boolean                           SysMonCheck_Data_Get_Crc32RamFailure(void);
extern           boolean                           SysMonCheck_Data_Get_Crc32RomFailure(void);
extern           tSysMonCheck_Data_FuSaParamValid  SysMonCheck_Data_AreFuSaParamValid(void);
extern           tSysMonCheck_Data_LedChParam*     SysMonCheck_Data_GetaLEDChParamPtr(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
teSysMon_EngineState                SysMonCheck_RteAccess_Get_ElecSupState_Param1;
uint8                               SysMonCheck_LedDiag_IsLightSourceSpiErrorFree_Param1;
boolean                             SysMonCheck_Set_CodingFailureDiagLowBeamStatus_Param1;
boolean                             SysMonCheck_Set_CodingFailureDiagTurnIndicatorStatus_Param1;
boolean                             SysMonCheck_CtrlTiDelayStatus_Param1;
TIMER                               SysMonCheck_CtrlTiDelayStatus_Param2;
sint8                               SysMonCheck_CtrlTiDelayStatus_Param3;
tsSysMonCheck_TiTimerCfg            SysMonCheck_TiDelayStatus_Param1;
sint8                               SysMonCheck_TiDelayStatus_Param2;
uint8_fast                          SysMonCheck_LedDiag_RetainErrorReaction_Param1;
tSysMon_FuSaChannelsStatusReaction  SysMonCheck_LedDiag_RetainErrorReaction_Param2;
uint8_fast                          SysMoncheck_LedDiag_ErrorHandler_Param1;
uint8                               SysMoncheck_LedDiag_ErrorHandler_Param2;
uint8_fast                          SysMonCheck_LedDiag_ErrorDebounce_Param1;
uint8                               SysMonCheck_LedDiag_ErrorDebounce_Param2;
tsRte_LedStates                     SysMonCheck_InternalCom_LedState_CheckCrc_Param1;
tsRte_TgtLedSig0_FaultStatus_ASIL   SysMonCheck_InternalCom_TgtLed_FaultStatus_ASIL_CheckCrc_param1;
boolean                             SysMonCheck_InternalCom_SetInternalComErrActive_Param1;
boolean                             SysMonCheck_RteAccess_Get_TiFailureStatus_Param1;
tsRte_TgtLedSig0                    SysMon_LedCtrl_Init_Param1;
tsRte_TgtLedSig0_ASIL               SysMon_LedCtrl_Init_Param2;
uint8                               SysMonRx_HandleRxFrame_Param1;
teSysMon_RxFrameState               SysMon_RxCallbacks_HS6_DAT_VSM_2AE_Param1;
teSysMon_RxFrameState               SysMon_RxCallbacks_HS6_DAT_VSM_34E_Param1;
teSysMon_RxFrameState               SysMon_RxCallbacks_HS6_COMMANDES_VSM_036_Param1;
teSysMon_RxFrameState               SysMon_RxCallbacks_HS6_DAT_BSI_432_Param1;
teSysMon_RxFrameState               SysMon_RxCallbacks_HS6_DYN_ABR_38D_Param1;
uint8                               SysMon_RxCallbacks_Compute_ConfigVhl_Param1;
uint8                               SysMon_RxCallbacks_Compute_AfsMode_Param1;
uint8                               SysMon_RxCallbacks_Compute_GfhbMode_Param1;
boolean                             SysMon_RxCallbacks_GetDiagMuxState_Param1;
boolean                             SysMon_RxCallbacks_GetDiagMuxState_Param2;
tsRte_SysMon_VehicleSpeed           SysMon_RxCallbacks_RangeCheck_LightDynAbr_Param1;
tsSysMon_RxSpeedFrmCheck            SysMon_RxCallbacks_RangeCheck_LightDynAbr_Param2;
uint8                               SysMonTx_TimeoutCheck_Param1;
tsRte_SysMonAfsSignals              SysMonRx_Callbacks_Compute_AfsMode_Param1;
uint8                               SysMonRx_Callbacks_Compute_AfsMode_Param2;
tsRte_SysMon_VehNetState            SysMonRx_Callbacks_Compute_VESMainState_Param1;
uint8                               SysMonRx_Callbacks_Compute_VESMainState_Param2;
tsRte_SysMon_VehNetState            SysMonRx_Callbacks_Compute_EletricalNetworkState_Param1;
uint8                               SysMonRx_Callbacks_Compute_EletricalNetworkState_Param2;

Tu8_Int                             SysMon_E2EGetChunkState_Param1;
EECO_TEP_ProfileOneChunkStatusPtr   SysMon_E2EGetChunkState_Param2;
tsRte_TgtLedSig0                    SysMonCheck_LedCtrl_Init_Param1;
tsRte_TgtLedSig0_ASIL*              SysMonCheck_LedCtrl_Init_Param2;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_OFF_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_ON_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_OFF_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_ON_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_OFF_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_ON_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_OFF_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_ON_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_OFF_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_ON_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_OFF_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_ON_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_OFF_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_ON_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_OFF_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_ON_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_OFF_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_ON_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_HandleLowBeam_Param1;
tSysMonTiEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicator_Param1;
tSysMonTiEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_ON_Param1;
tSysMonTiEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_OFF_Param1;
tSysMonTiEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_ON_Param1;
tSysMonTiEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_OFF_Param1;
tSysMonTiEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Valid_Param1;
uint8                               SysMonRx_Callbacks_Compute_TurnIndicatorCmd_Param1;
uint8                               SysMonCheck_CheckMinPWMandCurrent_Param1;
SysMon_EnumLowBeamState             SysMonRx_ASIL_SetLowBeamState_Param1;
uint8                               SysMonRx_ASIL_SetLowBeamValue_Param1;
tParaFct0_Cmd                       SysMonCheck_Data_ParaFct0_Param1;
tNvmPara_CodingArea                 SysMonCheck_Data_ParaFct0_Param2;
boolean                             SysMonCheck_Data_SetCodingDataSatus_Param1;
uint8                               SysMonCheck_Data_IsTurnIndicatorFuSa_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Refresh_Param1;
uint8                               SysMonRx_Callbacks_GetLowBeamSignal_Param1;
teRte_SigQty                        SysMonRx_Callbacks_GetLowBeamSignal_Param2;
teRte_PhaseVie                      SysMonRx_Callbacks_GetLifePhaseSignal_Param1;
teRte_SigQty                        SysMonRx_Callbacks_GetLifePhaseSignal_Param2;
teRte_SigQty                        SysMonRx_Callbacks_EvaluateCrcAndAliveDtcs_Param1;
teRte_SigQty                        SysMonRx_Callbacks_EvaluateCrcAndAliveDtcs_Param2;
uint16                              SysMonRx_Callbacks_GetSpeedSignal_Param1;
teVvhIndisp                         SysMonRx_Callbacks_GetSpeedSignal_Param2;
teRte_SigQty                        SysMonRx_Callbacks_GetSpeedSignal_Param3;
teRte_SigQty                        SysMonRx_Callbacks_GetVESMainStateSignal_Param1;
uint8                               SysMonRx_Callbacks_GetTurnIndicatorSignal_Param1;
teRte_SigQty                        SysMonRx_Callbacks_GetTurnIndicatorSignal_Param2;
teVvhIndisp                         SysMonRx_ASIL_VerifySpeedDispo_Param1;
uint16                              SysMonRx_ASIL_VerifySpeedDispo_Param2;
uint16                              SysMonRx_ASIL_VerifySpeedDispo_Param3;
teRte_SigQty                        SysMonRx_ASIL_VerifySpeedDispo_Param4;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_LowBeam_Valid_Param1;
tSysMonLbEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_HandleLowBeamDiag_Param1;
tSysMonTiEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Refresh_Param1;
tSysMonTiEmergencyOperationData     SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicatorDiag_Param1;
tsSysMonCheck_Data_EftData          SysMonCheck_Data_GetEftData_Param1;
uint8                               SysMonCheck_CheckMinPWMandCurrent_Param1;
uint8                               SysMonCheck_TriggerCddLed_LowBeam_Param1;
SysMonCheck_Data_tLFName            SysMonCheck_TurnOffFusaChannels_Param1;
boolean                             SysMonCheck_Cycle10ms_HandleTurnIndicatorFuSaBehaviour_Param1;
boolean                             SysMonCheck_Data_Set_Crc32RamFailure_Param1;
boolean                             SysMonCheck_Data_Set_Crc32RomFailure_Param1;
uint8                               SysMonCheck_LedDiag_IsLightSourceErrorFree_Param1;
uint8                               SysMonCheck_TurnOffChannel_Param1;
uint8                               SysMonRx_Callbacks_CheckSumCheck_Param1[];
uint8                               SysMonRx_Callbacks_CheckSumCheck_Param2;
boolean                             SysMonRx_Callbacks_GetDiagMuxState_Param1;
tsRte_SysMon_VehicleSpeed           SysMonRx_Callbacks_RangeCheck_LightDynAbr_Param1;
tsSysMon_RxSpeedFrmCheck            SysMonRx_Callbacks_RangeCheck_LightDynAbr_Param2;
teRte_SigQty                        SysMonRx_Callbacks_RangeCheck_LightDynAbr_Param3;
uint8                               SysMonRx_Callbacks_ProcessCntCheck_Param1;
boolean                             SysMonRx_Callbacks_Timeout_Param1;
TIMER                               SysMonRx_Callbacks_Timeout_Param2;
uint8                               SysMonRx_Callbacks_Timeout_Param3;
tsSysMonRx_TimerCfg                 SysMonRx_Callbacks_HandleDelayStatus_Param1[3];
uint8                               SysMonRx_Callbacks_HandleDelayStatus_Param2;


//=============================================================================
// Module function return value stubs
//=============================================================================
uint8                               SysMonCheck_CtrlTiDelayStatus_RetVal;
uint8                               SysMoncheck_LedDiag_ErrorHandler_RetVal;
uint8                               SysMonCheck_LedDiag_ErrorDebounce_RetVal;
boolean                             SysMonCheck_LedDiag_IsLightSourceSpiErrorFree_RetVal;
boolean                             SysMonCheck_LedDiag_IsTiLightSourceErrorFree_RetVal;
boolean                             SysMonCheck_TI_Diag_Status_RetVal;
boolean                             SysMonCheck_TiDelayStatus_RetVal;
boolean                             SysMonCheck_LedDiag_RetainErrorReaction_RetVal;
boolean                             SysMonCheck_InternalCom_LedState_CheckCrc_RetVal;
boolean                             SysMonCheck_InternalCom_TgtLed_FaultStatus_ASIL_CheckCrc_RetVal;
boolean                             SysMonCheck_InternalCom_IsComErrActive_RetVal;
boolean                             SysMonCheck_Get_TgtLed_FaultStatus_ASIL_RetVal;
tSysMon_FuSaChannelsStatusReaction  SysMonCheck_Get_LbTiFuSa_OffStatus_RetVal;
teRte_ModeConfigVehicle             SysMon_RxCallbacks_Compute_ConfigVhl_RetVal;
teRte_Ctrl_AFS                      SysMon_RxCallbacks_Compute_AfsMode_RetVal;
teRte_GfHb_Cmd                      SysMon_RxCallbacks_Compute_GfhbCmd_RetVal;
teRte_SigQty                        SysMonRx_Callbacks_Compute_VESMainState_RetVal;
TE_ReturnType                       EEPL_MainFunction_RetVal;
teRte_SigQty                        SysMon_E2EGetChunkState_RetVal;
uint8                               SysMonRx_Callbacks_Compute_TurnIndicatorCmd_RetVal;
tSysMonCheck_Data_LedChParam*       SysMonCheck_Data_GetaLEDChParamPtr_RetVal;
boolean                             SysMonCheck_Data_IsCodingDataValid_RetVal;
tSysMonCheck_Data_FuSaParamValid    SysMonCheck_Data_AreFuSaParamValid_RetVal;
boolean                             SysMonCheck_Data_CodingDataValidation_RetVal;
boolean                             SysMonCheck_Data_FuSaParamRangeCheckTI_RetVal;
boolean                             SysMonCheck_Data_IsTurnIndicatorFuSa_RetVal;
boolean                             SysMonCheck_Data_FuSaParamRangeCheckLB_RetVal;
boolean                             SysMonCheck_Data_IsNbOfFuSaChannelsAllowed_RetVal;
boolean                             SysMonCheck_Data_IsTiScrollingPresent_RetVal;
boolean                             SysMonCheck_Data_Get_TiScrollingPresent_RetVal;
boolean                             SysMonRx_ASIL_Check_TI_Scrolling_RetVal;
boolean                             SysMonCheck_Data_AreAllLedChSupportedByHw_RetVal;
uint32                              SysMonCheck_Data_CalcComputedFuSaParamCrc32_RetVal;
boolean                             SysMonCheck_Data_Get_Crc32RamFailure_RetVal;
boolean                             SysMonCheck_Data_Get_Crc32RomFailure_RetVal;
boolean                             SysMonCheck_LedDiag_IsLightSourceErrorFree_RetVal;
boolean                             SysMonCheck_Data_ParaFct0_RetVal;
boolean                             SysMonTx_TimeoutCheck_RetVal;
boolean                             SysMonRx_Callbacks_Hb_Cmd_OtherCond_RetVal;
boolean                             SysMonRx_Callbacks_CheckSumCheck_RetVal;
teRte_SigQty                        SysMonRx_Callbacks_EvaluateCrcAndAliveDtcs_RetVal;
boolean                             SysMonRx_Callbacks_ProcessCntCheck_RetVal;
boolean                             SysMonRx_Callbacks_Timeout_RetVal;
boolean                             SysMonRx_Callbacks_HandleDelayStatus_RetVal;
uint8                               SysMonCheck_RteAccess_Get_VoltageRange_RetVal;


#endif // TEST_2023_08_25_H_
