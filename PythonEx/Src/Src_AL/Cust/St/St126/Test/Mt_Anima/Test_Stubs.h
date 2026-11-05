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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include "Swc/Ctrl/Led/Anima/Anima_RteAccess.h"
#include <UtilDebounce.h>

//=============================================================================
// Stub function declarations
//=============================================================================

//Anima_RteAccess.c
Std_ReturnType                     Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType                     Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1);
Std_ReturnType                     Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1);
Std_ReturnType                     Rte_Read_SysMon_TurnIndicatorCmd_Req(teRte_ReqLightState* ppara1);
Std_ReturnType                     Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType                     Rte_Read_CodM_Anima_Para(tsRteCodingParameters* ppara1);

//Anima.c
void                               UtilDebounceInit(tUtilDebounceControl* const pCtrl, tieDigState eStateInit, TIMER tOnDelay, TIMER tOffDelay);
void                               UtilDebounce(tUtilDebounceControl* const pCtrl, boolean boVal);
Std_ReturnType                     Rte_Read_SigPrep_AnimationReq(tsRte_AnimationReq* ppara1);
Std_ReturnType                     Rte_Write_AnimaScrollingActivation(const tsRte_TgtAniArrScr* ppara1);
Std_ReturnType                     Rte_Read_CddSwi_ScrollingOn_Stat(tScrollingPresent_Stat* ppara1);



///=============================================================================
// Stub function parameter stubs
//=============================================================================
extern tsRte_SysMon_VehNetState    Rte_Read_SysMon_VehNetState_Param1;
extern tsRte_SysMonLgtFctsReq      Rte_Read_SysMon_StdLgtFcts_Req_Param1;
extern teRte_ReqLightState         Rte_Read_SysMon_LowBeamCmd_Req_Param1;
extern teRte_ReqLightState         Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1;
extern tsRte_AnimationReq          Rte_Read_SigPrep_AnimationReq_Param1;
extern teRte_MountingSide          Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern tUtilDebounceControl        UtilDebounceInit_Param1;
extern tieDigState                 UtilDebounceInit_Param2;
extern TIMER                       UtilDebounceInit_Param3;
extern TIMER                       UtilDebounceInit_Param4;
extern tUtilDebounceControl        UtilDebounce_Param1;
extern boolean                     UtilDebounce_Param2;
extern tsRteCodingParameters       Rte_Read_CodM_Anima_Para_Param1;
extern tsRte_TgtAniArrScr          Rte_Write_AnimaScrollingActivation_Param1;
extern tScrollingPresent_Stat      Rte_Read_CddSwi_ScrollingOn_Stat_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern Std_ReturnType              Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
extern Std_ReturnType              Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
extern Std_ReturnType              Rte_Read_SysMon_TurnIndicatorCmd_Req_RetVal;
extern Std_ReturnType              Rte_Read_SysMon_VehNetState_RetVal;
extern uint8                       Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern uint8                       Rte_Read_CodM_Anima_Para_RetVal;
extern Std_ReturnType              Rte_Read_SigPrep_AnimationReq_RetVal;
extern Std_ReturnType              Rte_Write_AnimaScrollingActivation_RetVal;
extern Std_ReturnType              Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8                      Rte_Read_SysMon_VehNetState_HitCount;
extern uint8                      Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
extern uint8                      Rte_Read_SysMon_LowBeamCmd_Req_HitCount;
extern uint32                     Rte_Read_SysMon_TurnIndicatorCmd_Req_HitCount;
extern uint8                      Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8                      UtilDebounceInit_HitCount;
extern uint8                      UtilDebounce_HitCount;
extern uint8                      Rte_Read_CodM_Anima_Para_HitCount;
extern uint32                     Rte_Read_SigPrep_AnimationReq_HitCount;
extern uint32                     Rte_Write_AnimaScrollingActivation_HitCount;
extern uint8                      Rte_Read_CddSwi_ScrollingOn_Stat_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
