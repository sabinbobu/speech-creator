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
/// \file   CtrlLed_Cfg.h
///
/// \brief  Configuration file for CtrlLed module
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_LED_CFG_2021_03_30_H_
#define CTRL_LED_CFG_2021_03_30_H_

//=============================================================================
// includes
//=============================================================================
#include <Cfg/Cfg.h>
#include <AL_Helper.h>
//=============================================================================
// defines
//=============================================================================

#define CTRLLED_SET_BIT_U16(var, bitPos) ((var) |= (uint16)((uint16)1u << (uint16)(bitPos)))
#define CTRLLED_CLR_BIT_U16(var, bitPos) ((var) &= (uint16)(~((uint16)1u << (uint16)(bitPos))))
#define CTRLLED_SET_CLR_CONDITION_U16(cnd, var, bitPos) ((cnd) != FALSE) ? (uint16)CTRLLED_SET_BIT_U16((var), (bitPos)) : (uint16)CTRLLED_CLR_BIT_U16((var), (bitPos))
#define CTRLLED_CHECK_BIT_U16(var, bitPos) ((((uint16)(var) & (uint16)((uint16)1u << (uint16)(bitPos))) == (uint16)((uint16)1u << (uint16)(bitPos))) ? TRUE : FALSE)

#define CTRLLED_CFG_UNKNOWN_UINT8_VALUE               0xFFU

#define CTRLLED_CFG_HSS_NO                            1U

#define CTRLLED_CFG_LED_CHANNELS_NR                   CFG_LED_CHANNELS_NR+CTRLLED_CFG_HSS_NO
#define CTRLLED_CFG_NR_OF_LOGICAL_UNITS               CFG_LOGICAL_UNITS
#define CTRLLED_CFG_MAX_BUCK_DRV                      12U+CTRLLED_CFG_HSS_NO //coding driver type
#define CTRLLED_CFG_MAX_LMM_SW_NO                     12U //max switch number allowed
#define CTRLLED_CFG_MAX_LMM_DRV                       7U  //coding LMM type
#define CTRLLED_CFG_BASIC_LED_CH                      (CTRLLED_CFG_LED_CHANNELS_NR - CTRLLED_CFG_HSS_NO)

#define CTRLLED_CFG_MAX_BINNING_CLASSES               0x06U
#define CTRLLED_CFG_BINNING_CLASS_5                   0x05U //max binning class
#define CTRLLED_CFG_BINNING_CLASS_0                   0x00U //min binning class

#define CTRLLED_CFG_MATRIX_BUCK                       1U
#define CTRLLED_CFG_NON_MATRIX_BUCK                   0U

#define CTRLLED_MS_CONVERTION                         1000U //[us]

//gamma points coding params cfg
#define CTRLLED_CFG_GAMMA_NUMBER                      2U
#define CTRLLED_CFG_GAMMA_POINTS                      17U


#define CTRLLED_UNKNOWN_VOLT 0U
#define CTRLLED_NORMAL_VOLT  1U
#define CTRLLED_LOW2_VOLT    2U
#define CTRLLED_LOW1_VOLT    3U


#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  #define CTRLLED_CFG_NO_OF_PIXELS_PER_CHIP           CFG_MATRIX_LEDs_PER_CH_Cnt
  #define CTRLLED_CFG_MAX_PXL_ROW                     3U
  #define CTRLLED_CFG_MAX_NR_OF_PXL                   (CFG_MATRIX_RAW_CNT * CTRLLED_CFG_MAX_PXL_ROW)// number of pixels controled / MLC
#endif

#define CTRLLED_CFG_NO_ILLUMINANTS                    CFG_LSM_LED_ILLUMINANT_NR //should taken from Cfg_Prj.h after Cretu will do the same for CODM_PARA_ILLUM_SIZE 
#define CTRLLED_CFG_NO_UNIT_GROUPS                    10U
#define CTRLLED_CFG_FIRST_UNIT_GROUP                  110U
#define CTRLLED_CFG_LAST_UNIT_GROUP                   119U
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
#define CTRLLED_CFG_BIT_MAX_CHANNELS                  0x1FFFU //12 channels+1HSS
#else
#define CTRLLED_CFG_BIT_MAX_CHANNELS                  0x0FFFU //12 channels
#endif

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\\
  //the following parts always must be sync with tCddLedErrStatus LED driver AND teRte_LedErrStatus from RTE
  #define CTRLLED_DIAG_ERR_ID_UNKNOWN                 CTRLLED_CFG_UNKNOWN_UINT8_VALUE
  #define CTRLLED_DIAG_STATUS_LED_OFF                 2U      // -  eRteCddLed_Disabled = 2,         // LED off
  #define CTRLLED_DIAG_STATUS_OK                      4U      // -  eRteCddLed_StatusOk = 4,         // normal operation
  #define CTRLLED_DIAG_ERR_OPEN_LOAD                  5U      // 0  eRteCddLed_ErrOpenLoad = 5,      // open load
  #define CTRLLED_DIAG_ERR_SHORT_TO_GND               6U      // 1  eRteCddLed_ErrShortToGnd = 6,    // short to GND
  #define CTRLLED_DIAG_ERR_SHORT_TO_BAT               7U      // 2  eRteCddLed_ErrShortToUbat = 7,   // short to Ubat
  #define CTRLLED_DIAG_ERR_VOLTAGE_LOW                8U      // 3  eRteCddLed_ErrUnderVoltage = 8,  // voltage of LED string too low
  #define CTRLLED_DIAG_ERR_VOLTAGE_HIGH               9U      // 4  eRteCddLed_ErrOverVoltage = 9,   // voltage of LED string too high
  #define CTRLLED_DIAG_ERR_THERM_SHUT_DOWN            10U     // 5  eRteCddLed_ErrThermShutdn = 10,  // thermal shutdown
  #define CTRLLED_DIAG_ERR_OVER_CURRENT               11U     // 6  eRteCddLed_ErrOvercurrent = 11,  // overcurrent
  #define CTRLLED_DIAG_ERR_SPI                        12U     // 7  eRteCddLed_ErrSpi = 12,          // SPI error
  #define CTRLLED_DIAG_ERR_CRC                        13U     // 8  eRteCddLed_ErrCrc = 13,          // CRC error
  #define CTRLLED_DIAG_ERR_BOOST                      14U     //  
  #define CTRLLED_DIAG_MAX_CNT                        15U
  #define CTRLLED_DIAG_MAX_STATUS_CNT                 CTRLLED_DIAG_MAX_CNT
  #define CTRLLED_DIAG_START_ERR_CNT                  CTRLLED_DIAG_ERR_OPEN_LOAD
  #define CTRLLED_DIAG_MAX_ERR_USED                  (CTRLLED_DIAG_MAX_STATUS_CNT - CTRLLED_DIAG_START_ERR_CNT)

#if (CTRLLED_DIAG_MAX_ERR_USED == 10U)
#define CTRLLED_DIAG_CH_ERR_REACT_MASK 0x3FFU
#else
#error "nu ai configurat masca bine!"
#endif
  
#define CTRLLED_DIAG_MTX_PXL_DEFECT CTRLLED_DIAG_MAX_CNT - CTRLLED_DIAG_ERR_OPEN_LOAD
#define CTRLLED_DIAG_MTX_LOSS_COM   10U
#define CTRLLED_DIAG_MTX_CORUPT_COM 11U
#define CTRLLED_DIAG_MTX_VCCx_GND   12U
#define CTRLLED_DIAG_MTX_VCCx_BAT   13U
#define CTRLLED_DIAG_ALL_ERR        CTRLLED_DIAG_MAX_CNT

#define CTRLLED_DIAG_MTX_VCCx_GND_BIT_POS           0u
#define CTRLLED_DIAG_MTX_VCCx_BAT_BIT_POS           1u
#define CTRLLED_DIAG_MTX_EEEPROM_CHKSUM_BIT_POS     2u
#define CTRLLED_DIAG_MTX_EEEPROM_NOACCESS_BIT_POS   3u

#define CTRLLED_DIAG_SKIP_UNDER_x_mV                9000U //[mV]


#define CTRLLED_DTC_NOT_USED 0U

#define CTRLLED_SWITCH_OFF 2U
#define CTRLLED_SWITCH_ON  1U
#define CTRLLED_DO_NOTHING 0U

#define CTRLLED_CH_NAME_COD_OUTPUT_OFF  0U  //value receive from coding
#define CTRLLED_CH_NAME_MAX             15U //max value receive from coding

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)

//!!!must match with coding channel name from "Configuration" sheet IFD coding and FCTR_CFG.h !!!
#define CTRLLED_CH_NAME_LB              0U  
#define CTRLLED_CH_NAME_LB_FUSA         1U  
#define CTRLLED_CH_NAME_HB              2U  
#define CTRLLED_CH_NAME_DRL_POS         3U  
#define CTRLLED_CH_NAME_DRL_POS_SCRL    4U  
#define CTRLLED_CH_NAME_TI              5U  
#define CTRLLED_CH_NAME_TI_SCRL         6U  
#define CTRLLED_CH_NAME_SM              7U  
#define CTRLLED_CH_NAME_RGB             8U  
#define CTRLLED_CH_NAME_FOG             9U  
#define CTRLLED_CH_NAME_LB_BOOST        10U  
#define CTRLLED_CH_NAME_HB_BOOST        11U  
#define CTRLLED_CH_NAME_CL              12U    
#define CTRLLED_CH_NAME_PXL_LB          13U  
#define CTRLLED_CH_NAME_PXL_HB          14U 
#define CTRLLED_CH_NAME_COD_PXL         14U //value receive from coding
#define CTRLLED_CH_NAME_COD_MXB         15U //value receive from coding

#define CTRLLED_ILLUMINANT_KINK 14U //stand alone in coding
#define CTRLLED_ILLUMINANT_HB   15U //stand alone in coding

#define CTRLLED_SEL_PIXEL_DEFECT 0U
#define CTRLLED_SEL_CORUPT_COM   1U
#define CTRLLED_SEL_LOSS_COM     2U
#define CTRLLED_SEL_MAX_PXL_ERR  3U

#define CTRLLED_MAX_MTX_COL_SEL  CTRLLED_CFG_MAX_PXL_ROW

#define CTRLLED_MTX_ROW_BTM 0U
#define CTRLLED_MTX_ROW_MID 1U
#define CTRLLED_MTX_ROW_TOP 2U

#define CTRLLED_DTC_MTX_PXL_LIST                                                            \
{        /*PXL_DEFECT       ,       CORUPT_COM           ,         LOSS_COM            ,  */   \
/*BTM*/ { {(uint16)LB_3ROW   , (uint16)LMM_LB_CRPT_COM    , (uint16)LMM_LB_LOS_COM   }  },     \
/*MID*/ { {(uint16)LB_2ROW   , (uint16)LMM_LB_CRPT_COM    , (uint16)LMM_LB_LOS_COM   }  },     \
/*TOP*/ { {(uint16)HB_1ROW   , (uint16)LMM_HB_CRPT_COM    , (uint16)LMM_HB_LOS_COM   }  },     \
}


#define CTRLLED_DTC_CH_LIST                                                                                                                                                                                                                                                                 \
{                                                                                                                                                                                                                                                                                           \
/*                                                                OPEN_LOAD    ,           SHORT_TO_GND      ,              SHORT_TO_BAT   ,           VOLTAGE_LOW       ,            VOLTAGE_HIGH     ,            THERM_SHUT_DOWN  ,            OVER_CURRENT     ,                 SPI         ,        CRC                    BOOST                  */\
/*   0    */ /* CTRLLED_CH_NAME_LB           */ { {(uint16)Lb_Strang_E_OC      , (uint16)Lb_E_SC_GND         , (uint16)Lb_E_SC_BAT         , (uint16)LB_CVBT             , CTRLLED_DTC_NOT_USED, (uint16)LB_OT               , (uint16)LB_OC               , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   1    */ /* CTRLLED_CH_NAME_LB_FUSA      */ { {(uint16)LBSafety_OL         , (uint16)LBSafety_SC_GND     , (uint16)LBSafety_SC_BAT     , (uint16)LBSafety_CVBT       , CTRLLED_DTC_NOT_USED, (uint16)LBSafety_OT         , (uint16)LBSafety_OC         , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   2    */ /* CTRLLED_CH_NAME_HB           */ { {(uint16)HB_E_OC             , (uint16)HB_E_SC_GND         , (uint16)HB_E_SC_BAT         , (uint16)HB_CVBT             , CTRLLED_DTC_NOT_USED, (uint16)HB_OT               , (uint16)HB_OC               , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   3    */ /* CTRLLED_CH_NAME_DRL/POS      */ { {(uint16)Drl_E_OC            , (uint16)Drl_E_SC_GND        , (uint16)Drl_E_SC_BAT        , (uint16)Drl_E_UN_VOLT       , CTRLLED_DTC_NOT_USED, (uint16)Drl_E_OVTEMP_OFF    , (uint16)Drl_E_OV_CURRENT    , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   4    */ /* CTRLLED_CH_NAME_DRL/POS_SCRL */ { {(uint16)Drl_E_OC            , (uint16)Drl_E_SC_GND        , (uint16)Drl_E_SC_BAT        , (uint16)Drl_E_UN_VOLT       , CTRLLED_DTC_NOT_USED, (uint16)Drl_E_OVTEMP_OFF    , (uint16)Drl_E_OV_CURRENT    , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   5    */ /* CTRLLED_CH_NAME_TI           */ { {(uint16)Ti_Strang_E_OC      , (uint16)Ti_E_SC_GND         , (uint16)Ti_E_SC_BAT         , (uint16)TI_CVBT             , CTRLLED_DTC_NOT_USED, (uint16)TI_OT               , (uint16)TI_OC               , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   6    */ /* CTRLLED_CH_NAME_TI_SCRL      */ { {(uint16)Ti_Strang_E_OC      , (uint16)Ti_E_SC_GND         , (uint16)Ti_E_SC_BAT         , (uint16)TI_CVBT             , CTRLLED_DTC_NOT_USED, (uint16)TI_OT               , (uint16)TI_OC               , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   7    */ /* CTRLLED_CH_NAME_SM           */ { {(uint16)SM_OL               , (uint16)SM_SC_GND           , (uint16)SM_SC_BAT           , (uint16)SM_CVBT             , CTRLLED_DTC_NOT_USED, (uint16)SM_OT               , (uint16)SM_OC               , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   8    */ /* CTRLLED_CH_NAME_RGB          */ { {(uint16)RGB_LED_OL          , (uint16)RGB_LED_SCG         , (uint16)RGB_LED_SCB         , (uint16)RGB_LED_CVBT        , CTRLLED_DTC_NOT_USED, (uint16)RGB_LED_OT          , (uint16)RGB_LED_OC          , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   9    */ /* CTRLLED_CH_NAME_FOG          */ { {(uint16)FF_OL               , (uint16)FF_SC_GND           , (uint16)FF_SC_BAT           , (uint16)FF_CVBT             , CTRLLED_DTC_NOT_USED, (uint16)FF_OT               , (uint16)FF_OC               , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   10   */ /* CTRLLED_CH_NAME_LB_BOOST     */ { {(uint16)Lb_Strang_E_OC      , (uint16)Lb_E_SC_GND         , (uint16)Lb_E_SC_BAT         , (uint16)LB_CVBT             , CTRLLED_DTC_NOT_USED, (uint16)LB_OT               , (uint16)LB_OC               , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   11   */ /* CTRLLED_CH_NAME_HB_BOOST     */ { {(uint16)HB_E_OC             , (uint16)HB_E_SC_GND         , (uint16)HB_E_SC_BAT         , (uint16)HB_CVBT             , CTRLLED_DTC_NOT_USED, (uint16)HB_OT               , (uint16)HB_OC               , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   12   */ /* CTRLLED_CH_NAME_CL           */ { {(uint16)CL_SBL_OL           , (uint16)CL_SBL_SC_GND       , (uint16)CL_SBL_SC_BAT       , (uint16)CL_SBL_CVBT         , CTRLLED_DTC_NOT_USED, (uint16)CL_SBL_OT           , (uint16)CL_SBL_OC           , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*  note  */ /*in case we detect a fault on the pxl channel, select the coresponding line based on light request */                                                                                                                                                                                                            \
/*   13   */ /* CTRLLED_CH_NAME_PXL_LB       */ { {(uint16)LB_OL_LMMx          , (uint16)CTRLLED_DTC_NOT_USED,(uint16)LB_SC_BAT_LMMx       , (uint16)CTRLLED_DTC_NOT_USED, CTRLLED_DTC_NOT_USED, (uint16)LB_OT_LMMx          , (uint16)LB_OC_LMMx          , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
/*   14   */ /* CTRLLED_CH_NAME_PXL_HB       */ { {(uint16)HB_OL_LMMx          , (uint16)CTRLLED_DTC_NOT_USED,(uint16)HB_SC_BAT            , (uint16)CTRLLED_DTC_NOT_USED, CTRLLED_DTC_NOT_USED, (uint16)HB_OT_LMMx          , (uint16)HB_OC_LMMx          , (uint16)SPI_Bus2_E_DEFECT  , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT  }}, \
}

//internal reactions list
//**** it 
#define CTRLLED_REACTION_CH_LIST                                                                                                                                                                                                              \
{                                                                                                                                                                                                                                                                                   \
/*                                                     OPEN_LOAD          ,     SHORT_TO_GND      ,   SHORT_TO_BAT               ,   VOLTAGE_LOW         ,      VOLTAGE_HIGH     ,     THERM_SHUT_DOWN  ,       OVER_CURRENT     ,         SPI         ,        CRC         ,         BOOST       */\
/*   0    */ /* CTRLLED_CH_NAME_LB           */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   1    */ /* CTRLLED_CH_NAME_LB_FUSA      */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   2    */ /* CTRLLED_CH_NAME_HB           */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   3    */ /* CTRLLED_CH_NAME_DRL/POS      */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   4    */ /* CTRLLED_CH_NAME_DRL/POS_SCRL */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   5    */ /* CTRLLED_CH_NAME_TI           */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   6    */ /* CTRLLED_CH_NAME_TI_SCRL      */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   7    */ /* CTRLLED_CH_NAME_SM           */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   8    */ /* CTRLLED_CH_NAME_RGB          */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   9    */ /* CTRLLED_CH_NAME_FOG          */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   10   */ /* CTRLLED_CH_NAME_LB_BOOST     */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   11   */ /* CTRLLED_CH_NAME_HB_BOOST     */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   12   */ /* CTRLLED_CH_NAME_CL           */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*  note  */ /*in case we detect a fault on the pxl channel, select the coresponding line based on light request */                                                                                                                                                                 \
/*   13   */ /* CTRLLED_CH_NAME_PXL_LB       */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
/*   14   */ /* CTRLLED_CH_NAME_PXL_HB       */ { {CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF    , CTRLLED_SWITCH_OFF           , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF     , CTRLLED_DO_NOTHING  , CTRLLED_DO_NOTHING ,CTRLLED_DO_NOTHING }}, \
}

#define CTRLLED_SEL_VCCX_SH2GND 0
#define CTRLLED_SEL_VCCX_SH2BAT 1

#define CTRLLED_PIXEL_REACTION_LIST                             \
{                                                               \
/*                      REACTION      */                        \
/*   CTRLLED_SEL_PIXEL_DEFECT         */CTRLLED_SWITCH_OFF,\
/*   CTRLLED_SEL_CORUPT_COM           */CTRLLED_SWITCH_OFF,\
/*   CTRLLED_SEL_LOSS_COM             */CTRLLED_SWITCH_OFF,\
}

#else
//!!!must match with coding channel name from "Configuration" sheet IFD coding!!!
#define CTRLLED_CH_NAME_LB              0   
#define CTRLLED_CH_NAME_LB_FUSA         1   
#define CTRLLED_CH_NAME_HB              2   
#define CTRLLED_CH_NAME_DRL_POS         3   
#define CTRLLED_CH_NAME_DRL_POS_SCRL    4   
#define CTRLLED_CH_NAME_TI              5   
#define CTRLLED_CH_NAME_TI_SCRL         6   
#define CTRLLED_CH_NAME_SM              7   
#define CTRLLED_CH_NAME_RGB             8   
#define CTRLLED_CH_NAME_FOG             9   
#define CTRLLED_CH_NAME_LB_BOOST        10  
#define CTRLLED_CH_NAME_HB_BOOST        11  
#define CTRLLED_CH_NAME_CL              12  

#define CTRLLED_DTC_CH_LIST                                                                                                                                                                                                                                                                 \
{                                                                                                                                                                                                                                                                                           \
/*                                                      OPEN_LOAD               ,     SHORT_TO_GND                  ,       SHORT_TO_BAT             ,      VOLTAGE_LOW                ,            VOLTAGE_HIGH        ,            THERM_SHUT_DOWN       ,       OVER_CURRENT              ,                 SPI         ,        CRC             BOOST             */  \
/*   0    */ /* CTRLLED_CH_NAME_LB           */ { {(uint16)Lb_Strang_E_OC          , (uint16)Lb_E_SC_GND               , (uint16)Lb_E_SC_BAT            , (uint16)LB_CVBT                 , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)LB_OT                    , (uint16)LB_OC                   , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   1    */ /* CTRLLED_CH_NAME_LB_FUSA      */ { {(uint16)Lb_Strang_E_OC          , (uint16)Lb_E_SC_GND               , (uint16)Lb_E_SC_BAT            , (uint16)LB_CVBT                 , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)LB_OT                    , (uint16)LB_OC                   , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   2    */ /* CTRLLED_CH_NAME_HB           */ { {(uint16)HB_E_OC                 , (uint16)HB_E_SC_GND               , (uint16)HB_E_SC_BAT            , (uint16)HB_CVBT                 , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)HB_OT                    , (uint16)HB_OC                   , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   3    */ /* CTRLLED_CH_NAME_DRL/POS      */ { {(uint16)Drl_E_OC                , (uint16)Drl_E_SC_GND              , (uint16)Drl_E_SC_BAT           , (uint16)Drl_E_UN_VOLT           , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)Drl_E_OVTEMP_OFF         , (uint16)Drl_E_OV_CURRENT        , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   4    */ /* CTRLLED_CH_NAME_DRL/POS_SCRL */ { {(uint16)Drl_E_OC                , (uint16)Drl_E_SC_GND              , (uint16)Drl_E_SC_BAT           , (uint16)Drl_E_UN_VOLT           , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)Drl_E_OVTEMP_OFF         , (uint16)Drl_E_OV_CURRENT        , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   5    */ /* CTRLLED_CH_NAME_TI           */ { {(uint16)Ti_Strang_E_OC          , (uint16)Ti_E_SC_GND               , (uint16)Ti_E_SC_BAT            , (uint16)TI_CVBT                 , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)TI_OT                    , (uint16)TI_OC                   , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   6    */ /* CTRLLED_CH_NAME_TI_SCRL      */ { {(uint16)Ti_Strang_E_OC          , (uint16)Ti_E_SC_GND               , (uint16)Ti_E_SC_BAT            , (uint16)TI_CVBT                 , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)TI_OT                    , (uint16)TI_OC                   , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   7    */ /* CTRLLED_CH_NAME_SM           */ { {(uint16)SM_OL                   , (uint16)SM_SC_GND                 , (uint16)SM_SC_BAT              , (uint16)SM_CVBT                 , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)CTRLLED_DTC_NOT_USED     , (uint16)CTRLLED_DTC_NOT_USED    , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED , (uint16)Booster_E_DEFECT } }, \
/*   8    */ /* CTRLLED_CH_NAME_RGB          */ { {(uint16)RGB_LED_OL              , (uint16)RGB_LED_SCG               , (uint16)RGB_LED_SCB            , (uint16)RGB_LED_CVBT            , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)RGB_LED_OT               , (uint16)RGB_LED_OC              , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   9    */ /* CTRLLED_CH_NAME_FOG          */ { {(uint16)CTRLLED_DTC_NOT_USED    , (uint16)CTRLLED_DTC_NOT_USED      , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)CTRLLED_DTC_NOT_USED    , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)CTRLLED_DTC_NOT_USED     , (uint16)CTRLLED_DTC_NOT_USED    , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   10   */ /* CTRLLED_CH_NAME_LB_BOOST     */ { {(uint16)Lb_Strang_E_OC          , (uint16)Lb_E_SC_GND               , (uint16)Lb_E_SC_BAT            , (uint16)LB_CVBT                 , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)LB_OT                    , (uint16)LB_OC                   , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   11   */ /* CTRLLED_CH_NAME_HB_BOOST     */ { {(uint16)HB_E_OC                 , (uint16)HB_E_SC_GND               , (uint16)HB_E_SC_BAT            , (uint16)HB_CVBT                 , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)HB_OT                    , (uint16)HB_OC                   , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
/*   12   */ /* CTRLLED_CH_NAME_CL           */ { {(uint16)CTRLLED_DTC_NOT_USED    , (uint16)CTRLLED_DTC_NOT_USED      , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)CTRLLED_DTC_NOT_USED    , (uint16)CTRLLED_DTC_NOT_USED   , (uint16)CTRLLED_DTC_NOT_USED     , (uint16)CTRLLED_DTC_NOT_USED    , (uint16)SPI_Bus2_E_DEFECT   , CTRLLED_DTC_NOT_USED, (uint16)Booster_E_DEFECT  } }, \
}   

//internal reactions list
#define CTRLLED_REACTION_CH_LIST                                                                                                                                                                                                              \
{                                                                                                                                                                                                                                                                                  \
/*                                                OPEN_LOAD         ,       SHORT_TO_GND       ,       SHORT_TO_BAT   ,      VOLTAGE_LOW       ,   VOLTAGE_HIGH        , THERM_SHUT_DOWN      ,    OVER_CURRENT      ,           SPI         ,        CRC            ,     BOOST            */  \
/*   0    */ /* CTRLLED_CH_NAME_LB           */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   1    */ /* CTRLLED_CH_NAME_LB_FUSA      */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   2    */ /* CTRLLED_CH_NAME_HB           */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   3    */ /* CTRLLED_CH_NAME_DRL/POS      */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   4    */ /* CTRLLED_CH_NAME_DRL/POS_SCRL */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   5    */ /* CTRLLED_CH_NAME_TI           */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   6    */ /* CTRLLED_CH_NAME_TI_SCRL      */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   7    */ /* CTRLLED_CH_NAME_SM           */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   8    */ /* CTRLLED_CH_NAME_RGB          */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   9    */ /* CTRLLED_CH_NAME_FOG          */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   10   */ /* CTRLLED_CH_NAME_LB_BOOST     */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   11   */ /* CTRLLED_CH_NAME_HB_BOOST     */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
/*   12   */ /* CTRLLED_CH_NAME_CL           */ { {CTRLLED_SWITCH_OFF  ,   CTRLLED_SWITCH_OFF     , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING     , CTRLLED_DO_NOTHING    , CTRLLED_SWITCH_OFF   , CTRLLED_SWITCH_OFF   , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING    , CTRLLED_DO_NOTHING  } }, \
} 
#endif
 


#endif // CTRL_LED_CFG_2021_03_30_H_



