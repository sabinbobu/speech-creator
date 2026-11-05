#include <Appl_LGM_Wrap.h>
#include <LGM_OS.h>
#include <_NM_types.h>
#include <p_DRV_CAN.h>
#include <p_MgrCAN.h>
#include <_DrvCAN_Types.h>
#include <_MgrCAN_Types.h>
#include <Cfg/Cfg.h>

#ifndef UNIT_TEST
#include <Rte.h>
#endif // UNIT_TEST
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riComStack1_Init)
SYS_LOAD_MEAS_VAR_DEC(rpComStack1_Cycle0)
#endif


//void LGM_Scheduler1(void);
//void LGM_Scheduler2(void);
//void Function_Test(void);



#define APPLI_NB_FRAMES_TO_ENABLE (UINT8)62
#define NB_OF_VARIANTS  (UINT8)4

/* RIGHT_FULL, RIGHT_ECO, LEFT_FULL,  LEFT_ECO */
STATIC_AL const LGM_BOOL APPLI_ui8_EnableVariantFrames[APPLI_NB_FRAMES_TO_ENABLE][NB_OF_VARIANTS] =
{
   { LGM_TRUE,  LGM_FALSE, LGM_FALSE, LGM_FALSE},   /* NM_IPDU_HS6_DAT_DRVLED_R_297_TX -0-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DIAG_DRVLED -1-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_FLT_EVT_DRVLED -2-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_SUPV_DRVLED -3-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_VERS_DRVLED -4-*/
   { LGM_TRUE,  LGM_FALSE,  LGM_FALSE, LGM_FALSE},  /* NM_IPDU_HS6_DAT2_DRVLED_R_4D7_TX -5-*/
   { LGM_FALSE, LGM_FALSE, LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DYN_BEMP_2B7_TX -6-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_LIGHTS_LUMINOSITY -7-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_LIGHTS_TEMP -8-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_LIGHTS_TEMP_DERATE -9-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_01 -10-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_02 -11-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_03 -12-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_04 -13-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_05 -14-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_06 -15-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_07 -16-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_08 -17-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_09 -18-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_10 -19-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_11 -20-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_LMM_SET_12 -21-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_LUM_MOTORS_STATUS -22-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_POWER_FACT_ATTITUDE_BHS -23-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_ACQ_NEW_JDD_55F -24-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_COMMANDES_VSM_036 -25-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DAT4_V2_BSI_552 -26-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DAT_BSI_432 -27-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DAT_VSM_2AE -28-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DAT_VSM_34E -29-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DAT_VSM_36E -30-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DAT_VSM_3AE -31-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DYN2_FRE_3CD -32-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DYN3_CMM_468 -33-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DYN_ABR_38D -34-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_FALSE, LGM_FALSE},   /* NM_IPDU_HS6_DYN_BEMP_2B7_RX -35-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DYN_VSM_257 -36-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_INTE_ELECTRON_BSI_092 -37-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DAT7_BSI_612 -38-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DAT_CSS_350 -39-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DAT_VSM_32E -40-*/
   { LGM_TRUE,  LGM_TRUE,  LGM_TRUE,  LGM_TRUE},    /* NM_IPDU_HS6_DAT_VSM_54D -41-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_0AB -42-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_0C3 -43-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_0CB -44-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_0E3 -45-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_0EB -46-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_103 -47-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_10B -48-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_123 -49-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_12B -50-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_143 -51-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_14B -52-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_163 -53-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_16B -54-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_183 -55-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_18B -56-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_1AB -57-*/
   { LGM_FALSE, LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DAT2_DRVLED_R_4D7_RX -58-*/
   { LGM_FALSE, LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DAT_DRVLED_R_297_RX -59-*/
   { LGM_TRUE,  LGM_FALSE, LGM_TRUE,  LGM_FALSE},   /* NM_IPDU_HS6_DYN_VSM_28E -60-*/
   { LGM_FALSE, LGM_FALSE, LGM_FALSE, LGM_TRUE}     /* NM_IPDU_HS6_DIAG_DRVLED_R_477_RX -61-*/
};

/* RIGHT_FULL, RIGHT_ECO, LEFT_FULL, LEFT_ECO */
/* Example: This can also be called as DRV_CAN_Update_CANID(0x0E3, DRV_CAN_TSDU_HS6_DYN_VSM_0E3) */
STATIC_AL const UINT16 APPLI_ui16_CANID_DRV[NB_MAILBOXES_USED][NB_OF_VARIANTS] =
{
        { (UINT16)0x257, (UINT16)0x257, (UINT16)0x257, (UINT16)0x257 },     /* HS6_DYN_VSM_257 -0-*/
        { (UINT16)0x34E, (UINT16)0x34E, (UINT16)0x34E, (UINT16)0x34E },     /* HS6_DAT_VSM_34E -1-*/
        { (UINT16)0x350, (UINT16)0x350, (UINT16)0x350, (UINT16)0x350 },     /* HS6_DAT_CSS_350 -2-*/
        { (UINT16)0x3AE, (UINT16)0x3AE, (UINT16)0x3AE, (UINT16)0x3AE },     /* HS6_DAT_VSM_3AE -3-*/
        { (UINT16)0x468, (UINT16)0x468, (UINT16)0x468, (UINT16)0x468 },     /* HS6_DYN3_CMM_468 -4-*/
        { (UINT16)0x552, (UINT16)0x552, (UINT16)0x552, (UINT16)0x552 },     /* HS6_DAT4_V2_BSI_552 -5-*/
        { (UINT16)0x5B7, (UINT16)0x5B7, (UINT16)0x597, (UINT16)0x597 },     /* HS6_REQ_DIAG_ON_CAN -6-*/
        { (UINT16)0x7FF, (UINT16)0x7FF, (UINT16)0x7FF, (UINT16)0x7FF },     /* HS6_DIAG_UDS_ON_CAN -7-*/
        { (UINT16)0x0EB, (UINT16)0x0EB, (UINT16)0x0EB, (UINT16)0x0EB },     /* HS6_DYN_VSM_0EB -8-*/
        { (UINT16)0x0C3, (UINT16)0x0C3, (UINT16)0x0C3, (UINT16)0x0C3 },     /* HS6_DYN_VSM_0C3 -9-*/
        { (UINT16)0x10B, (UINT16)0x10B, (UINT16)0x10B, (UINT16)0x10B },     /* HS6_DYN_VSM_10B -10-*/
        { (UINT16)0x123, (UINT16)0x123, (UINT16)0x123, (UINT16)0x123 },     /* HS6_DYN_VSM_123 -11-*/
        { (UINT16)0x143, (UINT16)0x143, (UINT16)0x143, (UINT16)0x143 },     /* HS6_DYN_VSM_143 -12-*/
        { (UINT16)0x163, (UINT16)0x163, (UINT16)0x163, (UINT16)0x163 },     /* HS6_DYN_VSM_163 -13-*/
        { (UINT16)0x183, (UINT16)0x183, (UINT16)0x183, (UINT16)0x183 },     /* HS6_DYN_VSM_183 -14-*/
        { (UINT16)0x2AE, (UINT16)0x2AE, (UINT16)0x2AE, (UINT16)0x2AE },     /* HS6_DAT_VSM_2AE -15-*/
        { (UINT16)0x297, (UINT16)0x297, (UINT16)0x297, (UINT16)0x297 },     /* HS6_DAT_DRVLED_R_297_RX -16-*/
        { (UINT16)0x32E, (UINT16)0x32E, (UINT16)0x32E, (UINT16)0x32E },     /* HS6_DAT_VSM_32E -17-*/
        { (UINT16)0x38D, (UINT16)0x38D, (UINT16)0x38D, (UINT16)0x38D },     /* HS6_DYN_ABR_38D -18-*/
        { (UINT16)0x432, (UINT16)0x432, (UINT16)0x432, (UINT16)0x432 },     /* HS6_DAT_BSI_432 -19-*/
        { (UINT16)0x477, (UINT16)0x477, (UINT16)0x477, (UINT16)0x477 },     /* HS6_DIAG_DRVLED_R_477_RX -20-*/
        { (UINT16)0x55F, (UINT16)0x55F, (UINT16)0x55F, (UINT16)0x55F },     /* HS6_ACQ_NEW_JDD_55F -21-*/
        { (UINT16)0x092, (UINT16)0x092, (UINT16)0x092, (UINT16)0x092 },     /* HS6_INTE_ELECTRON_BSI_092 -22-*/
        { (UINT16)0x1AB, (UINT16)0x1AB, (UINT16)0x1AB, (UINT16)0x1AB }      /* HS6_DYN_VSM_1AB -23-*/
};

/* RIGHT_FULL, RIGHT_ECO, LEFT_FULL, LEFT_ECO */
/* Example: This can also be called as MGR_CAN_Update_CANID_RX(0x036, MGR_CAN_TSDU_HS6_COMMANDES_VSM_036) */
STATIC_AL const UINT16 APPLI_ui16_CANID_MGR_RX[MGR_CAN_RX_FRAME_TBL_SIZE_PORT0][NB_OF_VARIANTS] =
{
        { (UINT16)0x036, (UINT16)0x036, (UINT16)0x036, (UINT16)0x036 },     /* HS6_COMMANDES_VSM_036 -0-*/
        { (UINT16)0x092, (UINT16)0x092, (UINT16)0x092, (UINT16)0x092 },     /* HS6_INTE_ELECTRON_BSI_092 -1-*/
        { (UINT16)0x0AB, (UINT16)0x0AB, (UINT16)0x0AB, (UINT16)0x0AB },     /* HS6_DYN_VSM_0AB -2-*/
        { (UINT16)0x0C3, (UINT16)0x0C3, (UINT16)0x0C3, (UINT16)0x0C3 },     /* HS6_DYN_VSM_0C3 -3-*/
        { (UINT16)0x0CB, (UINT16)0x0CB, (UINT16)0x0CB, (UINT16)0x0CB },     /* HS6_DYN_VSM_0CB -4-*/
        { (UINT16)0x0E3, (UINT16)0x0E3, (UINT16)0x0E3, (UINT16)0x0E3 },     /* HS6_DYN_VSM_0E3 -5-*/
        { (UINT16)0x0EB, (UINT16)0x0EB, (UINT16)0x0EB, (UINT16)0x0EB },     /* HS6_DYN_VSM_0EB -6-*/
        { (UINT16)0x103, (UINT16)0x103, (UINT16)0x103, (UINT16)0x103 },     /* HS6_DYN_VSM_103 -7-*/
        { (UINT16)0x10B, (UINT16)0x10B, (UINT16)0x10B, (UINT16)0x10B },     /* HS6_DYN_VSM_10B -8-*/
        { (UINT16)0x123, (UINT16)0x123, (UINT16)0x123, (UINT16)0x123 },     /* HS6_DYN_VSM_123 -9-*/
        { (UINT16)0x12B, (UINT16)0x12B, (UINT16)0x12B, (UINT16)0x12B },     /* HS6_DYN_VSM_12B -10-*/
        { (UINT16)0x143, (UINT16)0x143, (UINT16)0x143, (UINT16)0x143 },     /* HS6_DYN_VSM_143 -11-*/
        { (UINT16)0x14B, (UINT16)0x14B, (UINT16)0x14B, (UINT16)0x14B },     /* HS6_DYN_VSM_14B -12-*/
        { (UINT16)0x163, (UINT16)0x163, (UINT16)0x163, (UINT16)0x163 },     /* HS6_DYN_VSM_163 -13-*/
        { (UINT16)0x16B, (UINT16)0x16B, (UINT16)0x16B, (UINT16)0x16B },     /* HS6_DYN_VSM_16B -14-*/
        { (UINT16)0x183, (UINT16)0x183, (UINT16)0x183, (UINT16)0x183 },     /* HS6_DYN_VSM_183 -15-*/
        { (UINT16)0x18B, (UINT16)0x18B, (UINT16)0x18B, (UINT16)0x18B },     /* HS6_DYN_VSM_18B -16-*/
        { (UINT16)0x1AB, (UINT16)0x1AB, (UINT16)0x1AB, (UINT16)0x1AB },     /* HS6_DYN_VSM_1AB -17- */
        { (UINT16)0x28E, (UINT16)0x28E, (UINT16)0x28E, (UINT16)0x28E },     /* HS6_DYN_VSM_28E -18- */
        { (UINT16)0x297, (UINT16)0x297, (UINT16)0x297, (UINT16)0x297 },     /* HS6_DAT_DRVLED_R_297_RX -19- */
        { (UINT16)0x2AE, (UINT16)0x2AE, (UINT16)0x2AE, (UINT16)0x2AE },     /* HS6_DAT_VSM_2AE -20- */
        { (UINT16)0x2B7, (UINT16)0x2B7, (UINT16)0x2B7, (UINT16)0x2B7 },     /* HS6_DYN_BEMP_2B7_RX -21- */
        { (UINT16)0x32E, (UINT16)0x32E, (UINT16)0x32E, (UINT16)0x32E },     /* HS6_DAT_VSM_32E -22- */
        { (UINT16)0x36E, (UINT16)0x36E, (UINT16)0x36E, (UINT16)0x36E },     /* HS6_DAT_VSM_36E -23- */
        { (UINT16)0x38D, (UINT16)0x38D, (UINT16)0x38D, (UINT16)0x38D },     /* HS6_DYN_ABR_38D -24- */
        { (UINT16)0x3CD, (UINT16)0x3CD, (UINT16)0x3CD, (UINT16)0x3CD },     /* HS6_DYN2_FRE_3CD -25- */
        { (UINT16)0x432, (UINT16)0x432, (UINT16)0x432, (UINT16)0x432 },     /* HS6_DAT_BSI_432 -26- */
        { (UINT16)0x477, (UINT16)0x477, (UINT16)0x477, (UINT16)0x477 },     /* HS6_DIAG_DRVLED_R_477_RX -27- */
        { (UINT16)0x4D7, (UINT16)0x4D7, (UINT16)0x4D7, (UINT16)0x4D7 },     /* HS6_DAT2_DRVLED_R_4D7_RX -28- */
        { (UINT16)0x54D, (UINT16)0x54D, (UINT16)0x54D, (UINT16)0x54D },     /* HS6_DAT_VSM_54D -29- */
        { (UINT16)0x55F, (UINT16)0x55F, (UINT16)0x55F, (UINT16)0x55F },     /* HS6_ACQ_NEW_JDD_55F -30- */
        { (UINT16)0x5B7, (UINT16)0x5B7, (UINT16)0x597, (UINT16)0x597 },     /* HS6_REQ_DIAG_ON_CAN -31- */
        { (UINT16)0x612, (UINT16)0x612, (UINT16)0x612, (UINT16)0x612 },     /* HS6_DAT7_BSI_612 -32- */
        { (UINT16)0x7FF, (UINT16)0x7FF, (UINT16)0x7FF, (UINT16)0x7FF }      /* HS6_DIAG_UDS_ON_CAN -33- */
};

/* RIGHT_FULL, RIGHT_ECO, LEFT_FULL, LEFT_ECO */
/* Example: This can also be called as MGR_CAN_Update_CANID_TX(0x0F7, MGR_CAN_TSDU_HS6_VERS_DRVLED) */
STATIC_AL const UINT16 APPLI_ui16_CANID_MGR_TX[MGR_CAN_TX_FRAME_TBL_SIZE_PORT0][NB_OF_VARIANTS] =
{
        { (UINT16)0x0F7, (UINT16)0x0F7, (UINT16)0x0D7, (UINT16)0x0D7 },     /* HS6_VERS_DRVLED -0- */
        { (UINT16)0x297, (UINT16)0x297, (UINT16)0x297, (UINT16)0x297 },     /* HS6_DAT_DRVLED_R_297_TX -1- */
        { (UINT16)0x2B7, (UINT16)0x2B7, (UINT16)0x2B7, (UINT16)0x2B7 },     /* HS6_DYN_BEMP_2B7_TX -2- */
        { (UINT16)0x477, (UINT16)0x477, (UINT16)0x457, (UINT16)0x457 },     /* HS6_DIAG_DRVLED -3- */
        { (UINT16)0x4D7, (UINT16)0x4D7, (UINT16)0x4D7, (UINT16)0x4D7 },     /* HS6_DAT2_DRVLED_R_4D7_RX -4- */
        { (UINT16)0x577, (UINT16)0x577, (UINT16)0x557, (UINT16)0x557 },     /* HS6_REP_DIAG_ON_CAN -5- */
        { (UINT16)0x5F5, (UINT16)0x5F5, (UINT16)0x5D5, (UINT16)0x5D5 },     /* HS6_EMIS_NEW_JDD_DRVLED -6- */
        { (UINT16)0x5F7, (UINT16)0x5F7, (UINT16)0x5D7, (UINT16)0x5D7 },     /* HS6_SUPV_DRVLED -7- */
        { (UINT16)0x7F1, (UINT16)0x7F1, (UINT16)0x7D1, (UINT16)0x7D1 },     /* RL_LIGHTS_TEMP_DERATE -8- */
        { (UINT16)0x7F2, (UINT16)0x7F2, (UINT16)0x7D2, (UINT16)0x7D2 },     /* RL_LIGHTS_LUMINOSITY -9- */
        { (UINT16)0x7F3, (UINT16)0x7F3, (UINT16)0x7D3, (UINT16)0x7D3 },     /* RL_LIGHTS_TEMP -10- */
        { (UINT16)0x7F4, (UINT16)0x7F4, (UINT16)0x7D4, (UINT16)0x7D4 },     /* RL_LMM_SET_01 -11- */
        { (UINT16)0x7F5, (UINT16)0x7F5, (UINT16)0x7D5, (UINT16)0x7D5 },     /* RL_LMM_SET_02 -12- */
        { (UINT16)0x7F6, (UINT16)0x7F6, (UINT16)0x7D6, (UINT16)0x7D6 },     /* RL_LMM_SET_03 -13- */
        { (UINT16)0x7F7, (UINT16)0x7F7, (UINT16)0x7D7, (UINT16)0x7D7 },     /* RL_LUM_MOTORS_STATUS -14- */
        { (UINT16)0x7F8, (UINT16)0x7F8, (UINT16)0x7D8, (UINT16)0x7D8 },     /* RL_POWER_FACT_ATTITUDE_BHS -15- */
        { (UINT16)0x7E7, (UINT16)0x7E7, (UINT16)0x7D9, (UINT16)0x7D9 },     /* RL_LMM_SET_12_GFHB_ANGLE -16- */
        { (UINT16)0x7F9, (UINT16)0x7F9, (UINT16)0x7DB, (UINT16)0x7DB },     /* RL_LMM_SET_04 -17- */
        { (UINT16)0x7FA, (UINT16)0x7FA, (UINT16)0x7DC, (UINT16)0x7DC },     /* RL_LMM_SET_05 -18- */
        { (UINT16)0x7FB, (UINT16)0x7FB, (UINT16)0x7DD, (UINT16)0x7DD },     /* RL_LMM_SET_06 -19- */
        { (UINT16)0x7FD, (UINT16)0x7FD, (UINT16)0x7DE, (UINT16)0x7DE },     /* RL_LMM_SET_07 -20- */
        { (UINT16)0x7FE, (UINT16)0x7FE, (UINT16)0x7DF, (UINT16)0x7DF },     /* RL_LMM_SET_08 -21- */
        { (UINT16)0x7DA, (UINT16)0x7DA, (UINT16)0x7E1, (UINT16)0x7E1 },     /* RL_LMM_SET_09 -22- */
        { (UINT16)0x7E5, (UINT16)0x7E5, (UINT16)0x7E2, (UINT16)0x7E2 },     /* RL_LMM_SET_10 -23- */
        { (UINT16)0x7E6, (UINT16)0x7E6, (UINT16)0x7E3, (UINT16)0x7E3 }      /* RL_LMM_SET_11 -24- */
};

typedef enum {
  RIGHT_FULL =  0x00,
  RIGHT_ECO =   0x01,
  LEFT_FULL =   0x02,
  LEFT_ECO =    0x03
} APPLI_ArchitectureType_Type;

#ifdef CFG_VARIANT_FULL
  static APPLI_ArchitectureType_Type APPLI_E_ActualArchi = LEFT_FULL; /* This variable needs to be initialized for each configuration */
#elif defined (CFG_VARIANT_ECO)
  static APPLI_ArchitectureType_Type APPLI_E_ActualArchi = LEFT_ECO; /* This variable needs to be initialized for each configuration */
#elif defined (UNIT_TEST)
  APPLI_ArchitectureType_Type APPLI_E_ActualArchi = LEFT_FULL;
#endif



static void APPLI_SelectCANID(void)
{
  UINT8               ui8_FrameIndex = (UINT8)0;
  UINT16              ui16_VariantIndex;
  teRte_MountingSide  eMountingSide = { 0 };

  // Get MountingSide from Rte port
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  switch (eMountingSide)
  {
  case eMountedLeft:
#ifdef CFG_VARIANT_FULL
    APPLI_E_ActualArchi = LEFT_FULL;
#elif defined (CFG_VARIANT_ECO)
    APPLI_E_ActualArchi = LEFT_ECO;
#endif
    break;
  case eMountedRight:
#ifdef CFG_VARIANT_FULL
    APPLI_E_ActualArchi = RIGHT_FULL;
#elif defined (CFG_VARIANT_ECO)
    APPLI_E_ActualArchi = RIGHT_ECO;
#endif
    break;
  default:
#ifdef CFG_VARIANT_FULL
    APPLI_E_ActualArchi = RIGHT_FULL;
#elif defined (CFG_VARIANT_ECO)
    APPLI_E_ActualArchi = RIGHT_ECO;
#endif
    break;
  }

  switch (APPLI_E_ActualArchi)
  {
  case RIGHT_FULL:
    ui16_VariantIndex = (UINT16) RIGHT_FULL;
    break;

  case RIGHT_ECO:
    ui16_VariantIndex = (UINT16) RIGHT_ECO;
    break;

  case LEFT_FULL:
    ui16_VariantIndex = (UINT16) LEFT_FULL;
    break;

  case LEFT_ECO:
    ui16_VariantIndex = (UINT16) LEFT_ECO;
    break;

  default:
    ui16_VariantIndex = (UINT16) RIGHT_ECO;
    break;
  }

  /* Update CAN ID array for the CAN driver */
  for (ui8_FrameIndex = (UINT8)0; ui8_FrameIndex < NB_MAILBOXES_USED; ui8_FrameIndex++)
  {
    (void)DRV_CAN_Update_CANID(APPLI_ui16_CANID_DRV[ui8_FrameIndex][ui16_VariantIndex], ui8_FrameIndex);
  }

  /* Update CAN ID array for the CAN_RX manager */
  for (ui8_FrameIndex = (UINT8)0; ui8_FrameIndex < MGR_CAN_RX_FRAME_TBL_SIZE_PORT0; ui8_FrameIndex++)
  {
    (void)MGR_CAN_Update_CANID_RX(APPLI_ui16_CANID_MGR_RX[ui8_FrameIndex][ui16_VariantIndex], ui8_FrameIndex);
  }

  /* Update CAN ID array for the CAN_TX manager */
  for (ui8_FrameIndex = (UINT8)0; ui8_FrameIndex < MGR_CAN_TX_FRAME_TBL_SIZE_PORT0; ui8_FrameIndex++)
  {
    (void)MGR_CAN_Update_CANID_TX(APPLI_ui16_CANID_MGR_TX[ui8_FrameIndex][ui16_VariantIndex], ui8_FrameIndex);
  }
} // PRQA S 5310 1 // interface function

/* Enable or disable frames depending on the configuration */
static void APPLI_SelectVehicleArchiVariant(void)
{
  UINT8 ui8_FrameIndex = (UINT8)0;
  UINT16 ui16_VariantIndex;

  switch (APPLI_E_ActualArchi)
  {
  case RIGHT_FULL:
    ui16_VariantIndex = (UINT16) RIGHT_FULL;
    break;

  case RIGHT_ECO:
    ui16_VariantIndex = (UINT16) RIGHT_ECO;
    break;

  case LEFT_FULL:
    ui16_VariantIndex = (UINT16) LEFT_FULL;
    break;

  case LEFT_ECO:
    ui16_VariantIndex = (UINT16) LEFT_ECO;
    break;

  default:
    ui16_VariantIndex = (UINT16) RIGHT_ECO;
    break;
  }

  for (ui8_FrameIndex = (UINT8)0; ui8_FrameIndex < APPLI_NB_FRAMES_TO_ENABLE; ui8_FrameIndex++)
  {
    if (APPLI_ui8_EnableVariantFrames[ui8_FrameIndex][ui16_VariantIndex] == LGM_FALSE)
    {
      NM_DisableVariantFrame(ui8_FrameIndex);
    }
    else
    {
      // nothing to do
    }
  }
}

extern uint8 Enter_intterupts; // PRQA S 3447 1 // lib interface access

void APPLI_Run(void)
{
  /* ... */
  /* Hardware and OS init */
  if (LGM_OS_Init() == LGM_E_OK)
  {
    /* CAN ID init */
    APPLI_SelectCANID();

    /* Com start */
    if (NM_Start() == NM_OK)
    {
      Enter_intterupts = 0;
    }
    else
    {
      // nothing to do
    }
  }
  else
  {
    // nothing to do
  }

  /* Enable/disable frames */
  APPLI_SelectVehicleArchiVariant();

  //while (1)
  //{
  //  /* ... */
  //}
}


//-----------------------------------------------------------------------------
/// \brief riComStack1_Init
///
/// \descr Init runnable for com stack
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riComStack1_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riComStack1_Init)
#endif

    APPLI_Run();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riComStack1_Init)
#endif  
}

//-----------------------------------------------------------------------------
/// \brief rpComStack1_Cycle0
///
/// \descr Cyclic function for com stack
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpComStack1_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpComStack1_Cycle0)
#endif

  // This task is to be called from OS scheduler or from the RTE every 5ms.
  LGM_Scheduler2();
  LGM_Scheduler1();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpComStack1_Cycle0)
#endif
}
