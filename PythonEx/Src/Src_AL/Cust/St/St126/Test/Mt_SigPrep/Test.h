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
#include <SigPrep_Types.h>
#include <SigPrepRx_Callbacks.h>
#include <SigPrepTx_Callbacks.h>


//=============================================================================
// Typedefs
//=============================================================================
UINT8 IL_ui8_TabMessageStaticRcpData0[1];  /* DATA_ACQ_JDD_BSI_2 -0- */
UINT8 IL_ui8_TabMessageStaticRcpData1[4];  /* CPT_TEMPOREL -1- */
UINT8 IL_ui8_TabMessageStaticRcpData2[1];  /* ETAT_PRINCIP_SEV -2- */
UINT8 IL_ui8_TabMessageStaticRcpData3[1];  /* ETAT_RESEAU_ELEC -3- */
UINT8 IL_ui8_TabMessageStaticRcpData4[1];  /* SCROLLING_TI -4- */
UINT8 IL_ui8_TabMessageStaticRcpData5[1];  /* ETAT_CLIGNOTANTS -5- */
UINT8 IL_ui8_TabMessageStaticRcpData6[1];  /* WARNING_MODE -6- */
UINT8 IL_ui8_TabMessageStaticRcpData7[1];  /* CTRL_TI_L_F_S -7- */
UINT8 IL_ui8_TabMessageStaticRcpData8[1];  /* CTRL_TI_R_F_S -8- */
UINT8 IL_ui8_TabMessageStaticRcpData9[1];  /* E2E_CRC_VSM_34E -9- */
UINT8 IL_ui8_TabMessageStaticRcpData10[1];   /* CTRL_DRL_L -10- */
UINT8 IL_ui8_TabMessageStaticRcpData11[1];   /* CTRL_DRL_R -11- */
UINT8 IL_ui8_TabMessageStaticRcpData12[1];   /* CTRL_FL_L_F -12- */
UINT8 IL_ui8_TabMessageStaticRcpData13[1];   /* E2E_ALIVE_VSM_34E -13- */
UINT8 IL_ui8_TabMessageStaticRcpData14[1];   /* CTRL_AFS -14- */
UINT8 IL_ui8_TabMessageStaticRcpData15[1];   /* CTRL_FL_R_F -15- */
UINT8 IL_ui8_TabMessageStaticRcpData16[1];   /* CTRL_HB_FLASH -16- */
UINT8 IL_ui8_TabMessageStaticRcpData17[1];   /* CTRL_HB_L -17- */
UINT8 IL_ui8_TabMessageStaticRcpData18[1];   /* CTRL_HB_R -18- */
UINT8 IL_ui8_TabMessageStaticRcpData19[1];   /* CTRL_LB_L -19- */
UINT8 IL_ui8_TabMessageStaticRcpData20[1];   /* CTRL_PL_L_F -20- */
UINT8 IL_ui8_TabMessageStaticRcpData21[1];   /* CTRL_S_M_L_F -21- */
UINT8 IL_ui8_TabMessageStaticRcpData22[1];   /* CTRL_PL_R_F -22- */
UINT8 IL_ui8_TabMessageStaticRcpData23[1];   /* CTRL_LB_R -23- */
UINT8 IL_ui8_TabMessageStaticRcpData24[1];   /* CTRL_S_M_R_F -24- */
UINT8 IL_ui8_TabMessageStaticRcpData25[1];   /* ETAT_FEUX_STATIONNEMENT -25- */
UINT8 IL_ui8_TabMessageStaticRcpData26[1];   /* GFHB_CMD -26- */
UINT8 IL_ui8_TabMessageStaticRcpData27[1];   /* LOW_BEAM_BOOST_ALLOWED -27- */
UINT8 IL_ui8_TabMessageStaticRcpData28[1];   /* AIMING_MODE_ACTIVATION -28- */
UINT8 IL_ui8_TabMessageStaticRcpData29[1];   /* PEDESTRIAN_ALLOWED -29- */
UINT8 IL_ui8_TabMessageStaticRcpData30[1];   /* CONFIG_VHL -30- */
UINT8 IL_ui8_TabMessageStaticRcpData31[1];   /* MOTORWAY_DETECTION -31- */
UINT8 IL_ui8_TabMessageStaticRcpData32[1];   /* DELAY_FMH -32- */
UINT8 IL_ui8_TabMessageStaticRcpData33[2];   /* EXT_LIGHTNING_ANIMATION_REQ -33- */
UINT8 IL_ui8_TabMessageStaticRcpData34[1];   /* ETAT_FEUX_CROIST -34- */
UINT8 IL_ui8_TabMessageStaticRcpData35[1];   /* ETAT_MAR -35- */
UINT8 IL_ui8_TabMessageStaticRcpData36[1];   /* MODE_CONFIG_VEHICLE -36- */
UINT8 IL_ui8_TabMessageStaticRcpData37[2];   /* VITESSE_LACET -37- */
UINT8 IL_ui8_TabMessageStaticRcpData38[2];   /* PRESSION_MAITRE_CYL -38- */
UINT8 IL_ui8_TabMessageStaticRcpData39[1];   /* ETAT_FEE -39- */
UINT8 IL_ui8_TabMessageStaticRcpData40[2];   /* VITESSE_VEHICULE_ROUES -40- */
UINT8 IL_ui8_TabMessageStaticRcpData41[1];   /* CPT_PROCESS_4B_38D -41- */
UINT8 IL_ui8_TabMessageStaticRcpData42[1];   /* CHKSUM_TRME_DYN_UC_FREIN -42- */
UINT8 IL_ui8_TabMessageStaticRcpData43[1];   /* VVH_INDISP -43- */
UINT8 IL_ui8_TabMessageStaticRcpData44[1];   /* SIGNE_CONSIGNE_SITE_D_RX -44- */
UINT8 IL_ui8_TabMessageStaticRcpData45[2];   /* CONSIGNE_SITE_D_RX -45- */
UINT8 IL_ui8_TabMessageStaticRcpData46[1];   /* CMD_REF_SITE_D_RX -46- */
UINT8 IL_ui8_TabMessageStaticRcpData47[1];   /* DYN_BENDING_BEAM_FAULT_L_RX -47- */
UINT8 IL_ui8_TabMessageStaticRcpData48[1];   /* AUTO_BRAKING_PRESSURE -48- */
UINT8 IL_ui8_TabMessageStaticRcpData49[1];   /* EFCMNT_PDLE_ACCEL -49- */
UINT8 IL_ui8_TabMessageStaticRcpData50[1];   /* VOLONTE_COND -50- */
UINT8 IL_ui8_TabMessageStaticRcpData51[1];   /* DIAG_INTEGRA_ELEC -51- */
UINT8 IL_ui8_TabMessageStaticRcpData52[1];   /* MODE_DIAG -52- */
UINT8 IL_ui8_TabMessageStaticRcpData53[1];   /* EFFAC_DEFAUT_DIAG -53- */
UINT8 IL_ui8_TabMessageStaticRcpData54[1];   /* DIAG_MUX_ON_BODY -54- */
UINT8 IL_ui8_TabMessageStaticRcpData55[1];   /* PHASE_VIE -55- */
UINT8 IL_ui8_TabMessageStaticRcpData56[1];   /* DEM_EFFAC_DEF -56- */
UINT8 IL_ui8_TabMessageStaticRcpData57[1];   /* INTERD_MEMO_DEF -57- */
UINT8 IL_ui8_TabMessageStaticRcpData58[1];   /* INH_ECLAIRAGE_VIRAGE_DYN -58- */
UINT8 IL_ui8_TabMessageStaticRcpData59[2];   /* ASSIETTE_VEHICULE -59- */
UINT8 IL_ui8_TabMessageStaticRcpData60[1];   /* CTRL_CL_L -60- */
UINT8 IL_ui8_TabMessageStaticRcpData61[1];   /* CTRL_CL_R -61- */
UINT8 IL_ui8_TabMessageStaticRcpData62[1];   /* CTRL_SBL_L -62- */
UINT8 IL_ui8_TabMessageStaticRcpData63[1];   /* CTRL_SBL_R -63- */
UINT8 IL_ui8_TabMessageStaticRcpData64[3];   /* KM_TOTAL -64- */
UINT8 IL_ui8_TabMessageStaticRcpData65[1];   /* PERCEIVERFL_1_BRIGHTNESS -65- */
UINT8 IL_ui8_TabMessageStaticRcpData66[2];   /* PERCEIVERFL_1_LEFTANGLE -66- */
UINT8 IL_ui8_TabMessageStaticRcpData67[2];   /* PERCEIVERFL_1_RIGHTANGLE -67- */
UINT8 IL_ui8_TabMessageStaticRcpData68[2];   /* PERCEIVERFL_1_TOPANGLE -68- */
UINT8 IL_ui8_TabMessageStaticRcpData69[2];   /* PERCEIVERFL_1_BOTTOMANGLE -69- */
UINT8 IL_ui8_TabMessageStaticRcpData70[2];   /* PERCEIVERFL_1_DISTANCE -70- */
UINT8 IL_ui8_TabMessageStaticRcpData71[1];   /* PERCEIVERFL_2_BRIGHTNESS -71- */
UINT8 IL_ui8_TabMessageStaticRcpData72[2];   /* PERCEIVERFL_2_LEFTANGLE -72- */
UINT8 IL_ui8_TabMessageStaticRcpData73[2];   /* PERCEIVERFL_2_RIGHTANGLE -73- */
UINT8 IL_ui8_TabMessageStaticRcpData74[2];   /* PERCEIVERFL_2_TOPANGLE -74- */
UINT8 IL_ui8_TabMessageStaticRcpData75[2];   /* PERCEIVERFL_2_BOTTOMANGLE -75- */
UINT8 IL_ui8_TabMessageStaticRcpData76[2];   /* PERCEIVERFL_2_DISTANCE -76- */
UINT8 IL_ui8_TabMessageStaticRcpData77[1];   /* PERCEIVERFL_3_BRIGHTNESS -77- */
UINT8 IL_ui8_TabMessageStaticRcpData78[2];   /* PERCEIVERFL_3_LEFTANGLE -78- */
UINT8 IL_ui8_TabMessageStaticRcpData79[2];   /* PERCEIVERFL_3_RIGHTANGLE -79- */
UINT8 IL_ui8_TabMessageStaticRcpData80[2];   /* PERCEIVERFL_3_TOPANGLE -80- */
UINT8 IL_ui8_TabMessageStaticRcpData81[2];   /* PERCEIVERFL_3_BOTTOMANGLE -81- */
UINT8 IL_ui8_TabMessageStaticRcpData82[2];   /* PERCEIVERFL_3_DISTANCE -82- */
UINT8 IL_ui8_TabMessageStaticRcpData83[2];   /* H_CLUSTER_MIN_DISTANCE_E -83- */
UINT8 IL_ui8_TabMessageStaticRcpData84[2];   /* H_CLUSTER_DISTANCE_LEFT_E -84- */
UINT8 IL_ui8_TabMessageStaticRcpData85[2];   /* H_CLUSTER_DISTANCE_RIGHT_E -85- */
UINT8 IL_ui8_TabMessageStaticRcpData86[2];   /* H_CLUSTER_ANGLE_LEFT_50D -86- */
UINT8 IL_ui8_TabMessageStaticRcpData87[2];   /* H_CLUSTER_ANGLE_RIGHT_50D -87- */
UINT8 IL_ui8_TabMessageStaticRcpData88[1];   /* H_CLUSTER_RIGHT_AZIMUTH_RATE -88- */
UINT8 IL_ui8_TabMessageStaticRcpData89[1];   /* H_CLUSTER_LEFT_AZIMUTH_RATE -89- */
UINT8 IL_ui8_TabMessageStaticRcpData90[1];   /* HCLUSTERTYPE_1 -90- */
UINT8 IL_ui8_TabMessageStaticRcpData91[2];   /* HCLUSTERMINDISTANCE_2 -91- */
UINT8 IL_ui8_TabMessageStaticRcpData92[2];   /* HCLUSTERLEFTDISTANCE_2 -92- */
UINT8 IL_ui8_TabMessageStaticRcpData93[2];   /* HCLUSTERRIGHTDISTANCE_2 -93- */
UINT8 IL_ui8_TabMessageStaticRcpData94[2];   /* HCLUSTERANGLELEFT_2 -94- */
UINT8 IL_ui8_TabMessageStaticRcpData95[2];   /* HCLUSTERANGLERIGHT_2 -95- */
UINT8 IL_ui8_TabMessageStaticRcpData96[1];   /* HCLUSTERRIGHTAZIMUTHRATE_2 -96- */
UINT8 IL_ui8_TabMessageStaticRcpData97[1];   /* HCLUSTERLEFTAZIMUTHRATE_2 -97- */
UINT8 IL_ui8_TabMessageStaticRcpData98[1];   /* HCLUSTERTYPE_2 -98- */
UINT8 IL_ui8_TabMessageStaticRcpData99[2];   /* HCLUSTERMINDISTANCE_3 -99- */
UINT8 IL_ui8_TabMessageStaticRcpData100[2];  /* HCLUSTERLEFTDISTANCE_3 -100- */
UINT8 IL_ui8_TabMessageStaticRcpData101[2];  /* HCLUSTERRIGHTDISTANCE_3 -101- */
UINT8 IL_ui8_TabMessageStaticRcpData102[2];  /* HCLUSTERANGLELEFT_3 -102- */
UINT8 IL_ui8_TabMessageStaticRcpData103[2];  /* HCLUSTERANGLERIGHT_3 -103- */
UINT8 IL_ui8_TabMessageStaticRcpData104[1];  /* HCLUSTERRIGHTAZIMUTHRATE_3 -104- */
UINT8 IL_ui8_TabMessageStaticRcpData105[1];  /* HCLUSTERLEFTAZIMUTHRATE_3 -105- */
UINT8 IL_ui8_TabMessageStaticRcpData106[1];  /* HCLUSTERTYPE_3 -106- */
UINT8 IL_ui8_TabMessageStaticRcpData107[2];  /* HCLUSTERMINDISTANCE_4 -107- */
UINT8 IL_ui8_TabMessageStaticRcpData108[2];  /* HCLUSTERLEFTDISTANCE_4 -108- */
UINT8 IL_ui8_TabMessageStaticRcpData109[2];  /* HCLUSTERRIGHTDISTANCE_4 -109- */
UINT8 IL_ui8_TabMessageStaticRcpData110[2];  /* HCLUSTERANGLELEFT_4 -110- */
UINT8 IL_ui8_TabMessageStaticRcpData111[2];  /* HCLUSTERANGLERIGHT_4 -111- */
UINT8 IL_ui8_TabMessageStaticRcpData112[1];  /* HCLUSTERRIGHTAZIMUTHRATE_4 -112- */
UINT8 IL_ui8_TabMessageStaticRcpData113[1];  /* HCLUSTERLEFTAZIMUTHRATE_4 -113- */
UINT8 IL_ui8_TabMessageStaticRcpData114[1];  /* HCLUSTERTYPE_4 -114- */
UINT8 IL_ui8_TabMessageStaticRcpData115[2];  /* HCLUSTERMINDISTANCE_5 -115- */
UINT8 IL_ui8_TabMessageStaticRcpData116[2];  /* HCLUSTERLEFTDISTANCE_5 -116- */
UINT8 IL_ui8_TabMessageStaticRcpData117[2];  /* HCLUSTERRIGHTDISTANCE_5 -117- */
UINT8 IL_ui8_TabMessageStaticRcpData118[2];  /* HCLUSTERANGLELEFT_5 -118- */
UINT8 IL_ui8_TabMessageStaticRcpData119[2];  /* HCLUSTERANGLERIGHT_5 -119- */
UINT8 IL_ui8_TabMessageStaticRcpData120[1];  /* HCLUSTERRIGHTAZIMUTHRATE_5 -120- */
UINT8 IL_ui8_TabMessageStaticRcpData121[1];  /* HCLUSTERLEFTAZIMUTHRATE_5 -121- */
UINT8 IL_ui8_TabMessageStaticRcpData122[1];  /* HCLUSTERTYPE_5 -122- */
UINT8 IL_ui8_TabMessageStaticRcpData123[1];  /* PERCEIVEEFL_1_ID -123- */
UINT8 IL_ui8_TabMessageStaticRcpData124[1];  /* PERCEIVERFL_1_LEFTAZIMUTHRATE -124- */
UINT8 IL_ui8_TabMessageStaticRcpData125[1];  /* PERCEIVERFL_1_RIGHTAZIMUTHRATE -125- */
UINT8 IL_ui8_TabMessageStaticRcpData126[1];  /* PERCEIVEEFL_2_ID -126- */
UINT8 IL_ui8_TabMessageStaticRcpData127[1];  /* PERCEIVERFL_2_LEFTAZIMUTHRATE -127- */
UINT8 IL_ui8_TabMessageStaticRcpData128[1];  /* PERCEIVERFL_2_RIGHTAZIMUTHRATE -128- */
UINT8 IL_ui8_TabMessageStaticRcpData129[1];  /* PERCEIVEEFL_3_ID -129- */
UINT8 IL_ui8_TabMessageStaticRcpData130[1];  /* PERCEIVERFL_3_LEFTAZIMUTHRATE -130- */
UINT8 IL_ui8_TabMessageStaticRcpData131[1];  /* PERCEIVERFL_3_RIGHTAZIMUTHRATE -131- */
UINT8 IL_ui8_TabMessageStaticRcpData132[1];  /* TRAFFICDETECTED -132- */
UINT8 IL_ui8_TabMessageStaticRcpData133[1];  /* HCLUSTERCLSUBTYPE_1 -133- */
UINT8 IL_ui8_TabMessageStaticRcpData134[1];  /* HCLUSTERBOTTOMANGLE_1 -134- */
UINT8 IL_ui8_TabMessageStaticRcpData135[1];  /* HCLUSTERID_1 -135- */
UINT8 IL_ui8_TabMessageStaticRcpData136[1];  /* HCLUSTERCLSUBTYPE_2 -136- */
UINT8 IL_ui8_TabMessageStaticRcpData137[1];  /* HCLUSTERBOTTOMANGLE_2 -137- */
UINT8 IL_ui8_TabMessageStaticRcpData138[1];  /* HCLUSTERID_2 -138- */
UINT8 IL_ui8_TabMessageStaticRcpData139[1];  /* HCLUSTERCLSUBTYPE_3 -139- */
UINT8 IL_ui8_TabMessageStaticRcpData140[1];  /* HCLUSTERBOTTOMANGLE_3 -140- */
UINT8 IL_ui8_TabMessageStaticRcpData141[1];  /* HCLUSTERID_3 -141- */
UINT8 IL_ui8_TabMessageStaticRcpData142[1];  /* HCLUSTERCLSUBTYPE_4 -142- */
UINT8 IL_ui8_TabMessageStaticRcpData143[1];  /* HCLUSTERBOTTOMANGLE_4 -143- */
UINT8 IL_ui8_TabMessageStaticRcpData144[1];  /* HCLUSTERID_4 -144- */
UINT8 IL_ui8_TabMessageStaticRcpData145[1];  /* HCLUSTERCLSUBTYPE_5 -145- */
UINT8 IL_ui8_TabMessageStaticRcpData146[1];  /* HCLUSTERBOTTOMANGLE_5 -146- */
UINT8 IL_ui8_TabMessageStaticRcpData147[1];  /* HCLUSTERID_5 -147- */
UINT8 IL_ui8_TabMessageStaticRcpData148[1];  /* LVL_REF_STATE_R_RX -148- */
UINT8 IL_ui8_TabMessageStaticRcpData149[1];  /* LVL_STEPLOSS_R_RX -149- */
UINT8 IL_ui8_TabMessageStaticRcpData150[1];  /* LVL_TEMPERATURE_R_RX -150- */
UINT8 IL_ui8_TabMessageStaticRcpData151[1];  /* LVL_ELEC_R_RX -151- */
UINT8 IL_ui8_TabMessageStaticRcpData152[1];  /* LVL_VOLT_R_RX -152- */
UINT8 IL_ui8_TabMessageStaticRcpData153[1];  /* SIGN_POS_LVL_R_RX -153- */
UINT8 IL_ui8_TabMessageStaticRcpData154[2];  /* POSITION_SITE_D_RX -154- */
UINT8 IL_ui8_TabMessageStaticRcpData155[1];  /* DYN_BENDING_BEAM_FAULT_R_RX -155- */
UINT8 IL_ui8_TabMessageStaticRcpData156[8];  /* OVERALL_DAT_VSM_34E_E2E -156- */
UINT8 IL_ui8_TabMessageStaticRcpData157[1];  /* TYPE_DIR -157- */
UINT8 IL_ui8_TabMessageStaticRcpData158[2];  /* VEH_PATH_CURVATURE -158- */
UINT8 IL_ui8_TabMessageStaticRcpData159[8];  /* OVERALL_DAT_ABR_38D_CHKSUM -159- */
UINT8 IL_ui8_TabMessageStaticRcpData160[1];  /* DIAG_LVL_R_RX -160- */
UINT8 IL_ui8_TabMessageStaticRcpData161[2];  /* STEER_WHEEL_ANGLE_CONF -161- */

//=============================================================================
// Defines
//=============================================================================
#define SUPPLIER_IDENT_MANUFACT_DATE_0  (uint8)0x01
#define SUPPLIER_IDENT_MANUFACT_DATE_1  (uint8)0x01
#define SUPPLIER_IDENT_MANUFACT_DATE_2  (uint8)0x01

#define SUPPLIER_IDENT_SITE_CODE_0      (uint8)0xFE

#define SUPPLIER_IDENT_SIGNATURE_CODE_0 (uint8)0x00
#define SUPPLIER_IDENT_SIGNATURE_CODE_1 (uint8)0x00
#define SUPPLIER_IDENT_SIGNATURE_CODE_2 (uint8)0x00

#define SUPPLIER_IDENT_NUMBER_CODE_0    (uint8)0xFE
#define SUPPLIER_IDENT_MARKING_0        (uint8)0x5C

#ifdef SAMPLE_ECO
#define SUPPLIER_IDENT_CRC_0            (uint8)0x01
#define SUPPLIER_IDENT_CRC_1            (uint8)0xB8
#else
#define SUPPLIER_IDENT_CRC_0            (uint8)0x51
#define SUPPLIER_IDENT_CRC_1            (uint8)0x8A
#endif 

#define ZI_TOTAL_SIZE_IN_BYTES          (uint8)48

tsSigprepTx_LogZoneEntry C_BOOT_ZI_Area[SIGPREPTX_LOGZONE_ENTRIES_NR] =
{ //PRQA S 693 2 // special memory mapping mechanism
  /* Initialization of the first ZI record */
  /* 00 */    (uint8)0xFF, /* Reserved */
  /* 01 */    (uint8)0xFF, /* Reserved */
  /* 02 */    (uint8)0x00, /* Reserved */
  /* 03 */    (uint8)0x00, /* Reserved */
  /* 04 */    (uint8)CFG_ULP_CAL_SUPPLIER, /* Supplier */
  /* 05 */    (uint8)CFG_ULP_CAL_SYSTEM, /* System */
  /* 06 */    (uint8)SUPPLIER_IDENT_MANUFACT_DATE_0, /* Manufacturing date0 */
  /* 07 */    (uint8)SUPPLIER_IDENT_MANUFACT_DATE_1, /*Manufacturing date1*/
  /* 08 */    (uint8)SUPPLIER_IDENT_MANUFACT_DATE_2, /*Manufacturing date2 */
  /* 09 */    (uint8)CFG_ULP_CAL_APPLICATION, /* Application */
  /* 10 */    (uint8)CFG_ULP_CAL_SOFTWARE_VERSION, /* Version */
  /* 11 */    HIBYTE(CFG_ULP_CAL_SOFTWARE_EDITION), /* Edition0 */
  /* 12 */    LOBYTE(CFG_ULP_CAL_SOFTWARE_EDITION), /* Edition1 */
  /* 13 */    (uint8)JENKINS_BUILD_DAY, /* Programming date0 */
  /* 14 */    (uint8)JENKINS_BUILD_MONTH, /* Programming date1 */
  /* 15 */    (uint8)JENKINS_BUILD_YEAR, /* Programming date2 */
  /* 16 */    (uint8)SUPPLIER_IDENT_SITE_CODE_0, /* Site */
  /* 17 */    (uint8)SUPPLIER_IDENT_SIGNATURE_CODE_0, /* Signature0 */
  /* 18 */    (uint8)SUPPLIER_IDENT_SIGNATURE_CODE_1, /* Signature1 */
  /* 19 */    (uint8)SUPPLIER_IDENT_SIGNATURE_CODE_2, /* Signature2 */
  /* 20 */    (uint8)SUPPLIER_IDENT_NUMBER_CODE_0, /* Number */
  /* 21 */    (uint8)CFG_ULP_CAL_FILE_NUMBER_1, /* ref: Software0 */
  /* 22 */    (uint8)CFG_ULP_CAL_FILE_NUMBER_2, /* ref: Software1 */
  /* 23 */    (uint8)CFG_ULP_CAL_FILE_NUMBER_3, /* ref: Software2 */
  /* 24 */    (uint8)0xFF, /* reserved 21 bytes : 0 */
  /* 25 */    (uint8)0xFF,
  /* 26 */    (uint8)0xFF,
  /* 27 */    (uint8)0xFF,
  /* 28 */    (uint8)0xFF,
  /* 29 */    (uint8)0xFF,
  /* 30 */    (uint8)0xFF,
  /* 31 */    (uint8)0xFF,
  /* 32 */    (uint8)0xFF,
  /* 33 */    (uint8)0xFF,
  /* 34 */    (uint8)0xFF,
  /* 35 */    (uint8)0xFF,
  /* 36 */    (uint8)0xFF,
  /* 37 */    (uint8)0xFF,
  /* 38 */    (uint8)0xFF,
  /* 39 */    (uint8)0xFF,
  /* 40 */    (uint8)0xFF,
  /* 41 */    (uint8)0xFF,
  /* 42 */    (uint8)0xFF,
  /* 43 */    (uint8)0xFF,
  /* 44 */    (uint8)0xFF, /* reserved 21 bytes : 20 */
  /* 45 */    (uint8)SUPPLIER_IDENT_MARKING_0, /* Marking of the recording */
  /* 46 */    (uint8)SUPPLIER_IDENT_CRC_0, /* CRC HISTO0 */
  /* 47 */    (uint8)SUPPLIER_IDENT_CRC_1, /* CRC HISTO1 */
}; // PRQA S 686 1 // only first 48 bytes are of interes

#define SIGPREP_RX_INVALID_ODOMETER                     0xFFFFFFu


//=============================================================================
// Module global variables
//=============================================================================
extern boolean                        SigPrepRx_boRxInitStatus;
extern boolean                        SigPrepRx_boCbDeactivateStatus;
extern boolean                        SigPrepTx_boActivateTx;
extern teSigPrep_TxSideFrameState     SigPrepTx_eEcuSide;
extern tsSigPrep_RxFrameInfoConst     asSigPrepCanRxFrameInfoConst[];
extern tsSigPrep_TxFrameInfoConst     asSigPrepCanTxFrameInfoConst[];
extern teRte_MountingSide             SigPrepRx_eMountingSide;
extern tsSigPrep_Coding_Options       SigPrep_Coding_Options;
extern uint16                         SigPrep_Data_unCONFIG_TIME;
extern CONST_AL tNvmPara_CodingArea*  SigPrep_Data_pCodingArea;

//=============================================================================
// STATIC variables inside functions
//=============================================================================
boolean          boTimerStatus;
STATIC_AL TIMER  ulDebounceTimers[SIGPREP_RX_NUMBER_OF_INVALID_DATA] = { 0u };


//=============================================================================
// Global variable stubs ( registers, global variables from other modules which are referenced in the module )
//=============================================================================
boolean                             boIgnitionDetected;
boolean                             boInputBHS;
boolean                             boInputINVALID;
boolean                             boInputCAN;
boolean                             boFrame350Check;
boolean                             boFrameReceived;
boolean                             boFrame468Check;
boolean                             boFrameReceived;
boolean                             boSTTPresent;
boolean                             boSTTAbsent;
boolean                             boIgnitionDetected;
LGM_BOOL                            NM_CAN_b_SleepBSIframe;
tEftData                            EftData;
tsRte_SysMon_VehNetState            sVehNetState_Old;
tNvmPara_CodingArea                 CodingDummy;


//=============================================================================
// Module function declarations
//=============================================================================
extern void                           riSigPrepRx_Init(void);
extern void                           SigPrepRx_Init(void);
extern void                           SigPrepRx_Cycle0(void);
extern void                           SigPrepRx_HandleRxFrame(uint8 ucFrmIdx);
extern void                           SigPrepRx_ComM_DisableCallbacks(void);
extern void                           SigPrepRx_ComM_EnableCallbacks(void);
extern void                           SigPrep_RxCallbacks_HS6_ACQ_NEW_JDD_55F(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DAT_VSM_36E(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DAT_VSM_3AE(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DAT_VSM_54D(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DAT4_V2_BSI_552(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN3_CMM_468(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_STTConfigDetection(teSigPrep_RxFrameState eSigPrepStateSTT);
extern void                           SigPrep_RxCallbacks_HS6_INTE_ELECTRON_BSI_092(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DAT_CSS_350(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DAT2_DRVLED_R_4D7_RX(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DAT_DRVLED_R_297_RX(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_ConfigDetection(teSigPrep_RxFrameState eSigPrep350State);
extern void                           SigPrep_RxCallbacks_HS6_DYN_BEMP_2B7_RX(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DIAG_DRVLED_R_477_RX(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_28E(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DAT_VSM_32E(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DAT7_BSI_612(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_0AB(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_0C3(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_0CB(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_0E3(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_0EB(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_103(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_10B(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_123(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_12B(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_143(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_14B(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_163(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_16B(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_183(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_18B(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_1AB(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN_VSM_257(teSigPrep_RxFrameState eSigPrepRxState);
extern void                           SigPrep_RxCallbacks_HS6_DYN2_FRE_3CD(teSigPrep_RxFrameState eSigPrepRxState);
extern boolean                        SigPrep_RxCallback_SideCheck_4D7_RX(void);
extern boolean                        SigPrep_RxCallback_SideCheck_297_RX(void);
extern boolean                        SigPrep_RxCallback_SideCheck_2B7_RX(void);
extern boolean                        SigPrep_RxCallback_SideCheck_477_RX(void);
extern void                           riSigPrepTx_Init(void);
extern void                           rpSigPrepTx_Cycle(void);
extern void                           SigPrepTx_Init(void);
extern void                           SigPrepTx_Cycle0(void);
extern void                           SigPrepTx_FramesTimerInit(void);
extern void                           SigPrepTx_FramesProcessing(void);
extern boolean                        SigPrepTx_TimeoutCheck(uint8 ucFrmIdx);
extern void                           SigPrepTx_ComM_ActivateTxBufer(void);
extern void                           SigPrepTx_ComM_DeactivateTxBuffer(void);
extern void                           SigPrep_TxCallbacks_CyclicFrame_5x7(void);
extern void                           SigPrep_TxCallbacks_ToFrame_5x7(void);
extern void                           SigPrep_TxCallbacks_CyclicFrame_2B7(void);
extern void                           SigPrep_TxCallbacks_CyclicFrame_4D7(void);
extern void                           SigPrep_TxCallbacks_ToFrame_2B7(void);
extern void                           SigPrep_TxCallbacks_ToFrame_4D7(void);
extern void                           SigPrep_TxCallbacks_CyclicFrame_297(void);
extern void                           SigPrep_TxCallbacks_ToFrame_297(void);
extern teRte_MountingSide             SigPrepRx_GetMountingSide(void);
extern void                           SigPrep_RxCallbacks_RangeCheck_VehicleAttitude(tsRte_SigPrep_VehiclePitchAngle *psOutputSig, sint16 nInputSig);
extern void                           SigPrep_RxCallbacks_RangeCheck_VehiclePathCurvature(tsRte_SigPrep_VehPathCurvature *psOutputSig, sint16 nInputSig);
extern boolean                       SigPrepRx_Callbacks_Debounce_TimerCheck(boolean *pboStartTimer, uint8 ucFrameName);
extern void                          SigPrep_RxCallbacks_Compute_ExtLightingAnimationReq(tsRte_AnimationReq *psOutputSig, uint16 unLightingAnimationReq, uint8 ucDelayFmh);
void                                  Mt_SigPrep_Reset_Default_RxCallBacks(void);
void                                  Cyclic_callback(void);
void                                  Timeout_callback(void);
void                                  Trigger_callback(void);


//=============================================================================
// Module function parameter stubs
//=============================================================================
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_ACQ_NEW_JDD_55F_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_COMMANDES_VSM_036_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT_BSI_432_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT_VSM_36E_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT_VSM_3AE_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT_VSM_54D_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT4_V2_BSI_552_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_ABR_38D_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN3_CMM_468_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_STTConfigDetection_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_INTE_ELECTRON_BSI_092_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN2_FRE_3CD_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT2_DRVLED_R_4D7_RX_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_BEMP_2B7_RX_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DIAG_DRVLED_R_477_RX_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_257_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT_CSS_350_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT_DRVLED_R_297_RX_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_ConfigDetection_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_28E_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT_VSM_32E_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DAT7_BSI_612_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_0AB_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_0C3_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_0CB_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_0E3_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_0EB_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_103_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_10B_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_123_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_12B_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_143_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_14B_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_163_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_16B_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_183_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_18B_Param1;
teSigPrep_RxFrameState           SigPrep_RxCallbacks_HS6_DYN_VSM_1AB_Param1;
uint8                            SigPrepRx_HandleRxFrame_Param1;
uint8                            SigPrepTx_TimeoutCheck_Param1;
tsRte_SigPrep_VehiclePitchAngle  SigPrep_RxCallbacks_RangeCheck_VehicleAttitude_Param1;
sint16                           SigPrep_RxCallbacks_RangeCheck_VehicleAttitude_Param2;
tsRte_SigPrep_VehPathCurvature   SigPrep_RxCallbacks_RangeCheck_VehiclePathCurvature_Param1;
sint16                           SigPrep_RxCallbacks_RangeCheck_VehiclePathCurvature_Param2;
boolean                         SigPrepRx_Callbacks_Debounce_TimerCheck_Param1;
uint8                           SigPrepRx_Callbacks_Debounce_TimerCheck_Param2;
tsRte_AnimationReq              SigPrep_RxCallbacks_Compute_ExtLightingAnimationReq_Param1;
uint16                          SigPrep_RxCallbacks_Compute_ExtLightingAnimationReq_Param2;
uint8                           SigPrep_RxCallbacks_Compute_ExtLightingAnimationReq_Param3;


//=============================================================================
// Module function return value stubs
//=============================================================================
boolean                          SigPrepTx_TimeoutCheck_RetVal;


//=============================================================================
// Module function hit count variables
//=============================================================================
uint32  Cyclic_callback_HitCount;
uint32  Timeout_callback_HitCount;
uint32  Trigger_callback_HitCount;



#endif // TEST_2023_08_25_H_
