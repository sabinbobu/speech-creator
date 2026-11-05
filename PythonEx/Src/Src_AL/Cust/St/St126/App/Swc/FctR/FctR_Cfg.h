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
/// \file  FctR_Cfg.h
///
/// \brief Config file for FctR
///
//-----------------------------------------------------------------------------
#ifndef FCT_R_CFG_H_
#define FCT_R_CFG_H_

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <AL_Helper.h>
#include <Cfg/Cfg.h>

//=============================================================================
// defines
//=============================================================================

// Macro to see if FULL Ecu variant is supported
#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
  #define FCTR_CFG_FULL_VARIANT_SUPPORTED 1u
#else
  #define FCTR_CFG_FULL_VARIANT_SUPPORTED 0u
#endif

// This value will be taken from coding
#define FCTR_CFG_LSJ_PROX_HB_CAVITY       1u
// Number of frames to wait to confirm LowBeam activation request loss
#define FCTR_CFG_LB_LOSS_DELAY    3u

// TI blinking phase in ms
#define FCTR_TI_BLINKING_PHASE        400U
// TI offset phase in ms
#define FCTR_TI_OFFSET_PHASE          100U
// Delay TI not requested in ms
#define FCTR_DELAY_TI_NOT_REQUESTED   FCTR_TI_BLINKING_PHASE + FCTR_TI_OFFSET_PHASE
// This value will be taken from coding
// Option for DRL/POS to blink or not with TI activated
#define FCTR_DRLPOS_NOT_BLINK_WITH_TI    1u

// Light Functions last index - TO BE REPLACED WITH CFG_LF_Cnt AFTER CODING INTEGRATION
//#define FCTR_CFG_LGTFCT_MAX             27u //(CFG_LF_Cnt)
#define FCTR_CFG_LGTFCT_MAX             32u 
//#define FCTR_CFG_LOGLMP_MAX             CFG_LED_CHANNELS_NR
#define FCTR_CFG_LOGLMP_MAX             CFG_LSM_LED_ILLUMINANT_NR
// Light functions look up table size
#define FCTR_CFG_LF_LUT_SIZE            40u
// Ramp type
#define FCTR_RAMP_ZK                     0u
// Light function not used by specific channel
#define FCTR_CFG_LGTFCT_NOT_USED        15u
// LB switch ON or switch OFF option in case of LB failure (1 = SWITCH ON; 2 = SWITCH OFF)
// It will be taken from coding and it can be 1 or 2
#define FCTR_CFG_AXL_SWITCH_ON          1u
#define FCTR_CFG_AXL_SWITCH_OFF         2u
#define FCTR_CFG_AXL                    FCTR_CFG_AXL_SWITCH_ON

#define FCTR_UNKNOWN_VOLT 0u //force to switch off all lights
#define FCTR_NORMAL_VOLT  1u
#define FCTR_LOW2_VOLT    2u
#define FCTR_LOW1_VOLT    3u

#define FCTR_DBLMASK_FOGGY 0x8

#define FCTR_CFG_PXL_INPUT_MASK 0x7FFu  //mask for input bits
#define FCTR_CFG_PXL_OUT1_MASK 0x3800u  //mask for first 3 output bits
#define FCTR_CFG_PXL_OUT2_MASK 0xC000u  //mask for last 2 output bits

#define FCTR_CFG_PXL_STATE 11u //FctR PxlState offset
#define FCTR_CFG_PXL_MODE  14u //FctR PxlMode offset

#define FCTR_SET_BIT_U32(var, bitPos) ((var) |= (uint32)((uint32)1U << (uint32)(bitPos)))
#define FCTR_CLR_BIT_U32(var, bitPos) ((var) &= (uint32)(~((uint32)1U << (uint32)(bitPos))))
//#define FCTR_SET_CLR_CONDITION_U32(cnd, var, bitPos) ((cnd) != FALSE) ? (uint16)CTRLLED_SET_BIT_U16((var), (bitPos)) : (uint16)CTRLLED_CLR_BIT_U16((var), (bitPos))
//#define FCTR_CHECK_BIT_U32(var, bitPos) ((((uint32)(var) & (uint32)((uint32)1U << (uint32)(bitPos))) == (uint32)((uint32)1u << (uint32)(bitPos))) ? TRUE : FALSE)
#define FCTR_CHECK_BIT_FCT_U32(var, bitFct) (((uint32)(var) & (uint32)(bitFct)) != 0U) ? TRUE : FALSE //check light illuminant function

//!!!must match with coding channel name from "Configuration" sheet IFD coding and CTRLLED_CFG.h !!!
#define FCTR_CH_NAME_LB              0U  
#define FCTR_CH_NAME_LB_FUSA         1U  
#define FCTR_CH_NAME_HB              2U  
#define FCTR_CH_NAME_DRL_POS         3U  
#define FCTR_CH_NAME_DRL_POS_SCRL    4U  
#define FCTR_CH_NAME_TI              5U  
#define FCTR_CH_NAME_TI_SCRL         6U  
#define FCTR_CH_NAME_SM              7U  
#define FCTR_CH_NAME_RGB             8U  
#define FCTR_CH_NAME_FOG             9U  
#define FCTR_CH_NAME_LB_BOOST        10U  
#define FCTR_CH_NAME_HB_BOOST        11U  
#define FCTR_CH_NAME_CL              12U    
#define FCTR_CH_NAME_PXL_LB          13U  
#define FCTR_CH_NAME_PXL_HB          14U 
#define FCTR_CH_UNKNOWN_NAME         0xFFU 

#define FCTR_LOW_BEAM_FUNCTION                      0x2403U //bit position set with FCTR_CH_NAME_LB, FCTR_CH_NAME_LB_FUSA, FCTR_CH_NAME_LB_BOOST, FCTR_CH_NAME_PXL_LB
#define FCTR_HIGH_BEAM_FUNCTION                     0x4804U //bit position set with FCTR_CH_NAME_HB, FCTR_CH_NAME_HB_BOOST, FCTR_CH_NAME_PXL_HB
#define FCTR_STATIC_BENDING_FUNCTION                0x1000U //bit position set with FCTR_CH_NAME_CL
#define FCTR_TURN_INDICATOR_FUNCTION                0x60U   //bit position set with FCTR_CH_NAME_TI, FCTR_CH_NAME_TI_SCRL
#define FCTR_DAYTIME_RUNNING_AND_POSITION_FUNCTION  0x18U   //bit position set with FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_DRL_POS_SCRL //DRL and POS are mapped on the same channels
#define FCTR_SIDE_MARKER_FUNCTION                   0x80U   //bit position set with FCTR_CH_NAME_SM
#define FCTR_FOG_FUNCTION                           0x200U  //bit position set with FCTR_CH_NAME_FOG

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)

//GFHB STATE CFG
#define FCTR_GFHB_STATE_ACTIVE     1u
#define FCTR_GFHB_STATE_CURTAIN_ON 4u

//DIAG FEEDBACK CFG
#define FCTR_CFG_DIAG_FEEDBACK_LB 0U
#define FCTR_CFG_DIAG_FEEDBACK_GFHB 1U
#define FCTR_CFG_DIAG_FEEDBACK_SBL 2U
#define FCTR_CFG_DIAG_FEEDBACK_POS 3U
#define FCTR_CFG_DIAG_FEEDBACK_DRL 4U 
#define FCTR_CFG_DIAG_FEEDBACK_HB 5U //last count
#ifndef UNIT_TEST
#define FCTR_CFG_DIAG_FEEDBACK_MAX_LIGHTS (FCTR_CFG_DIAG_FEEDBACK_HB + 1U)
#else
#define FCTR_CFG_DIAG_FEEDBACK_MAX_LIGHTS (FCTR_CFG_DIAG_FEEDBACK_HB + 1U + 1U)  //incrementation for UT to reach default state
#endif // !UNIT_TEST


//SBL with AFS CFG
#define FCTR_CFG_SBL_CL_OFF 0u
#define FCTR_CFG_SBL_CL_NOMINAL 1u
#define FCTR_CFG_SBL_CL_BAD_WEATHER 2u
#define FCTR_CFG_SBL_CL_FOGGY 3u
#define FCTR_CFG_SBL_CL_TOWN 4u
#define FCTR_CFG_SBL_CL_PEDESTRIAN 5u
#define FCTR_CFG_SBL_CL_DIM_TIME_ON_PER_PERCENT 6u
#define FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME 7u
#define FCTR_CFG_SBL_CL_DIM_TIME_OFF_PER_PERCENT 8u

#define FCTR_CFG_SBL_CL_DIM_SEL \
{               /*Current state  ,                   Target State          ,          Dimming             ,  */ \
 /* 0   */ {FCTR_CFG_SBL_CL_OFF              ,    FCTR_CFG_SBL_CL_NOMINAL		    ,    FCTR_CFG_SBL_CL_DIM_TIME_ON_PER_PERCENT           },   \
 /* 1   */ {FCTR_CFG_SBL_CL_OFF              ,    FCTR_CFG_SBL_CL_BAD_WEATHER	  ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 2   */ {FCTR_CFG_SBL_CL_OFF              ,    FCTR_CFG_SBL_CL_FOGGY			    ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 3   */ {FCTR_CFG_SBL_CL_OFF              ,    FCTR_CFG_SBL_CL_TOWN			    ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 4   */ {FCTR_CFG_SBL_CL_OFF              ,    FCTR_CFG_SBL_CL_PEDESTRIAN		,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 5   */ {FCTR_CFG_SBL_CL_NOMINAL	         ,    FCTR_CFG_SBL_CL_OFF			      ,    FCTR_CFG_SBL_CL_DIM_TIME_OFF_PER_PERCENT          },   \
 /* 6   */ {FCTR_CFG_SBL_CL_NOMINAL	         ,    FCTR_CFG_SBL_CL_BAD_WEATHER	  ,    FCTR_CFG_SBL_CL_DIM_TIME_OFF_PER_PERCENT          },   \
 /* 7   */ {FCTR_CFG_SBL_CL_NOMINAL	         ,    FCTR_CFG_SBL_CL_FOGGY			    ,    FCTR_CFG_SBL_CL_DIM_TIME_OFF_PER_PERCENT          },   \
 /* 8   */ {FCTR_CFG_SBL_CL_NOMINAL	         ,    FCTR_CFG_SBL_CL_TOWN			    ,    FCTR_CFG_SBL_CL_DIM_TIME_OFF_PER_PERCENT          },   \
 /* 9   */ {FCTR_CFG_SBL_CL_NOMINAL	         ,    FCTR_CFG_SBL_CL_PEDESTRIAN		,    FCTR_CFG_SBL_CL_DIM_TIME_OFF_PER_PERCENT          },   \
 /* 10  */ {FCTR_CFG_SBL_CL_BAD_WEATHER	     ,    FCTR_CFG_SBL_CL_OFF			      ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 11  */ {FCTR_CFG_SBL_CL_BAD_WEATHER	     ,    FCTR_CFG_SBL_CL_NOMINAL		    ,    FCTR_CFG_SBL_CL_DIM_TIME_ON_PER_PERCENT           },   \
 /* 12  */ {FCTR_CFG_SBL_CL_BAD_WEATHER	     ,    FCTR_CFG_SBL_CL_FOGGY			    ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 13  */ {FCTR_CFG_SBL_CL_BAD_WEATHER	     ,    FCTR_CFG_SBL_CL_TOWN			    ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 14  */ {FCTR_CFG_SBL_CL_BAD_WEATHER	     ,    FCTR_CFG_SBL_CL_PEDESTRIAN		,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 15  */ {FCTR_CFG_SBL_CL_FOGGY	           ,    FCTR_CFG_SBL_CL_OFF			      ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 16  */ {FCTR_CFG_SBL_CL_FOGGY	           ,    FCTR_CFG_SBL_CL_NOMINAL		    ,    FCTR_CFG_SBL_CL_DIM_TIME_ON_PER_PERCENT           },   \
 /* 17  */ {FCTR_CFG_SBL_CL_FOGGY	           ,    FCTR_CFG_SBL_CL_BAD_WEATHER	  ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 18  */ {FCTR_CFG_SBL_CL_FOGGY	           ,    FCTR_CFG_SBL_CL_TOWN			    ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 19  */ {FCTR_CFG_SBL_CL_FOGGY	           ,    FCTR_CFG_SBL_CL_PEDESTRIAN		,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 20  */ {FCTR_CFG_SBL_CL_TOWN	           ,    FCTR_CFG_SBL_CL_NOMINAL		    ,    FCTR_CFG_SBL_CL_DIM_TIME_ON_PER_PERCENT           },   \
 /* 21  */ {FCTR_CFG_SBL_CL_TOWN	           ,    FCTR_CFG_SBL_CL_OFF			      ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 22  */ {FCTR_CFG_SBL_CL_TOWN	           ,    FCTR_CFG_SBL_CL_FOGGY			    ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 23  */ {FCTR_CFG_SBL_CL_TOWN	           ,    FCTR_CFG_SBL_CL_BAD_WEATHER	  ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 24  */ {FCTR_CFG_SBL_CL_TOWN	           ,    FCTR_CFG_SBL_CL_PEDESTRIAN		,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 25  */ {FCTR_CFG_SBL_CL_PEDESTRIAN	     ,    FCTR_CFG_SBL_CL_OFF			      ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 26  */ {FCTR_CFG_SBL_CL_PEDESTRIAN	     ,    FCTR_CFG_SBL_CL_NOMINAL		    ,    FCTR_CFG_SBL_CL_DIM_TIME_ON_PER_PERCENT           },   \
 /* 27  */ {FCTR_CFG_SBL_CL_PEDESTRIAN	     ,    FCTR_CFG_SBL_CL_FOGGY			    ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 28  */ {FCTR_CFG_SBL_CL_PEDESTRIAN	     ,    FCTR_CFG_SBL_CL_TOWN			    ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
 /* 29  */ {FCTR_CFG_SBL_CL_PEDESTRIAN	     ,    FCTR_CFG_SBL_CL_BAD_WEATHER	  ,    FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME               },   \
}
#else
//DIAG FEEDBACK CFG
#define FCTR_CFG_DIAG_FEEDBACK_LB 0U
#define FCTR_CFG_DIAG_FEEDBACK_HB 1U
#define FCTR_CFG_DIAG_FEEDBACK_POS 2U
#define FCTR_CFG_DIAG_FEEDBACK_DRL 3U //last count
#define FCTR_CFG_DIAG_FEEDBACK_MAX_LIGHTS (FCTR_CFG_DIAG_FEEDBACK_DRL + 1U)
#endif

#ifdef FCTR_CODING_INVALID
// Look-up table for LED channels mapping
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
                                //                      Ch0                     ,                     Ch1                     ,                    Ch2                     ,                     Ch3                     ,                     Ch4                     ,                     Ch5                     ,                     Ch6                     ,                     Ch7                     ,                     Ch8                     ,                     Ch9                      ,                      Ch10                    ,                     Ch11                      //
#define FCTR_LED_CH_LUT_FULL    { \
 /* LB_TownLight             0 */   { {50u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_Pedestrian            1 */   { {50u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_CountryLight          2 */   { {50u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_MotorwayLight         3 */   { {50u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_MotorwayLight_Boosted 4 */   { {50u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_AdverseWeather        5 */   { {50u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_FoggyWeather          6 */   { {50u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_Reserved              7 */   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 1u , FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_HighBeam              8 */   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_FlashToPass           9 */   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Automatic             10*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u,  3u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Boost_Reserved        11*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Reserved              12*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 1u , FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Reserved              13*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 1u , FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Reserved              14*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 1u , FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Reserved              15*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 1u , FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* DRL_DaytimeRunningLight  16*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  3u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* POS_PositionLight        17*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u ,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* PKL_ParkingLight         18*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u ,  4u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* SBL_StaticBendingLight   19*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* CL_CorneringLight        20*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u , 1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* FL_FogLight              21*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* SM_SideMarker            22*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* TI_TurnIndicator         23*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u ,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 1u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* TI_POS_TurnIndicatorPos  24*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u ,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 1u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* TI_Scrolling             25*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* TI_Scrolling_POS         26*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* N/A                      27*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* N/A                      28*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* N/A                      29*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* N/A                      30*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* N/A                      31*/   { {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}   ,   {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
                                }
#else
                                //                     Ch1                     ,                     Ch2                     ,                     Ch3                     ,                     Ch4                        //
#define FCTR_LED_CH_LUT_ECO     { \
 /* LB_TownLight             0 */   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_Pedestrian            1 */   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_CountryLight          2 */   { {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_MotorwayLight         3 */   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_MotorwayLight_Boosted 4 */   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_AdverseWeather        5 */   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_FoggyWeather          6 */   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* LB_Reserved              7 */   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_HighBeam              8 */   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_FlashToPass           9 */   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Automatic             10*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Boost_Reserved        11*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Reserved              12*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Reserved              13*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Reserved              14*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* HB_Reserved              15*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* DRL_DaytimeRunningLight  16*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {100u,  3u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* POS_PositionLight        17*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  { 50u,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* PKL_ParkingLight         18*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  { 50u,  4u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* SBL_StaticBendingLight   19*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* CL_CorneringLight        20*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* FL_FogLight              21*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* SM_SideMarker            22*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* TI_TurnIndicator         23*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u ,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 1u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u ,  2u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* TI_POS_TurnIndicatorPos  24*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u ,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 1u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {50u ,  1u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* TI_Scrolling             25*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} },  \
 /* TI_Scrolling_POS         26*/   { {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u}  ,  {0u  , 15u, FCTR_RAMP_ZK, 0u, 0u, 0u, 0u} }  \
                               }
#endif
#endif //FCTR_CODING_INVALID
#endif // FCT_R_CFG_H_
