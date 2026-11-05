//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
/// ---------------------------------------------------------------------------
///
///  \file    DblcSm.h
///
///  \author  Bernd Dreier  Bernd.Dreier@al-lighting.com
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu@al-lighting.com
///
///  \owner   Ralf Sondershaus  Ralf.Sondershaus@al-lighting.com
///
///  \date    14.03.2003
///
///  \brief   dynamic bending light control, state machine
///
///  \descr   dynamic bending light control, state machine
///
/// ---------------------------------------------------------------------------
#ifndef DBLC_SM_2021_11_02_H_
#define DBLC_SM_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================
#include <Swc/CodM/CodM.h>
#include <Swc/CodM/CodM_Para.h>
#include <UtilMath.h>
#include <UtilUtility.h>
#include <UtilDebounce.h>
#include <Util_Time.h>
#include <Cfg/Cfg.h>
#include "Dbl_Types.h"
#include <RteCommonTypes.h>

//=============================================================================
// defines
//=============================================================================
#define DBL_MAX_SPEED            (uint16)0xFFFFU  // value of invalid speed
#define DBL_SPEED_COEF                      100u // value for speed resolution 
#define DBL_MAX_INHIB                       0xFF // value for invalid value for inhib
#define DBL_SPEED_RESOLUTION10              10u // value for speed resolution
#define DBLC_HLAFILTERSIZE                  20u  //< head light angle FIR filter size
#define DBL_PIVALUE                         314L
#define DBL_FULLANGLE                       180  // value in degrees for a full angle
#define DBL_FACTOR_RESOLUTION               20   // factor to align the angle values ​​even after the correction CodDblCurveFactor from the coding is applied
#define DBL_ANGLE_FACTOR_18                 18
#define DBLSM_CURVATURE_RECEIVED_ON_CAN     (uint8)0
#define DBLSM_DBL_DISABLED                  (uint8)0

//=============================================================================
// function prototypes
//=============================================================================
void                  DblcSm_ParaFct0(void);
void                  DblcSm_Init(void);
void                  Dbl_SetSteerbackDetection(boolean boState);
void                  Dbl_DetectMode(void); 
void                  Dbl_UseMode(void); 
void                  Dbl_UseSubMode(void); 
void                  Dbl_DefOfFailure(void);
void                  Dbl_Curvature_SigQty_INV(void);
void                  Dbl_ReadInputSignals(void);
void                  Dbl_ReadEnvironmentSignals(void);
void                  Dbl_Write_OutputValues(void);
void                  Dbl_HbActive();
boolean               Dbl_GetHBStatus(void);
teTraffic             Dbl_GetTrafficSide(void);
teDbl_MountingSide    Dbl_GetSide(void);
tUtilDebounceControl* Dbl_GetTimer(void);
sint16                Dbl_Mrad2MDeg(sint16 nSwvMrad);

//=============================================================================
// Typedefs
//=============================================================================
typedef struct
{
  //input
  boolean boReq_Input;
  TIMER   ulTimeMs_Input;
  //internal
  TIMER   ulCommandStart;
  boolean boStartStopTimer;
  boolean boTimeOut;
}tsDbl_TimerCfg;

#endif // DBLC_SM_2021_11_02_H_
