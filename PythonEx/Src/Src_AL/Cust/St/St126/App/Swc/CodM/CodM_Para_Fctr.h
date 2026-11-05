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
///  \file   CodM_Para_FctR.h
///
///  \brief  Content of datagroup "FctR"
///
///  \descr  Source: PS60_R2.xlsm. 
///         
///          For further details see coding parameter
///
///  \author Cretu Vlad (F78845C)
///          mailTo:vladut-ioan.cretu[at]marelli.com
///
///  \date   24.07.2018, 14:38:28
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================
#ifndef __CODM_PARA_FCTR_H__
#define __CODM_PARA_FCTR_H__

#include <Cfg/Cfg.h>

//=============================================================================
// Definitions
//=============================================================================

//=============================================================================
// Types
//=============================================================================
typedef struct
{
  // Not_Used=0, LB=10, HB=20, TI1=30, DRL_POS=40, CL=50
  uint8 CH_SOURCE                    ; 
  uint8 CH_T_ON                      ; 
  uint8 CH_T_OFF                     ; 
  uint8 CH_PWM                       ; 
}
tNvmPara_Fctr_CHANNEL_cell;

typedef struct
{
  uint16 unDELAY_TI_NOT_REQUESTED;
  uint8 ucNumber_Indp_DRLPL_light_sources; //commes out directly from the lsm
  uint8 ucPL_INTENSITY; //commes out directly from the lsm
  uint8 ucDRL_INTENSITY; //commes out directly from the lsm
  uint8 ucReserved;
}
tsNvmPara_Fctr_POS_DRL_LGT_SETTINGS;

typedef struct 
{
  tNvmPara_Fctr_CHANNEL_cell          CHANNEL_MAPPING [5];  // 20 bytes
  tsNvmPara_Fctr_POS_DRL_LGT_SETTINGS  POS_LGHT_SETTINGS;    //  4 bytes
} tNvmPara_FctrBlock;                                       // 25 bytes

#endif // __CODM_PARA_FCTR_H__

// EOF
