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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"
 
//=============================================================================
// Stub function parameter stubs
//=============================================================================
tsRte_SysMon_VehNetState               Rte_Read_SysMon_VehNetState_Param1;
tsRte_SysMonLgtFctsReq                 Rte_Read_SysMon_StdLgtFcts_Req_Param1;
teRte_ReqLightState                    Rte_Read_SysMon_LowBeamCmd_Req_Param1;
teRte_ReqLightState                    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1;
tsRte_AnimationReq                     Rte_Read_SigPrep_AnimationReq_Param1;
teRte_MountingSide                     Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tUtilDebounceControl                   UtilDebounceInit_Param1;
tieDigState                            UtilDebounceInit_Param2;
TIMER                                  UtilDebounceInit_Param3;
TIMER                                  UtilDebounceInit_Param4;
tUtilDebounceControl                   UtilDebounce_Param1;
boolean                                UtilDebounce_Param2;
tsRteCodingParameters                  Rte_Read_CodM_Anima_Para_Param1;
tsRte_TgtAniArrScr                     Rte_Write_AnimaScrollingActivation_Param1;
tScrollingPresent_Stat                 Rte_Read_CddSwi_ScrollingOn_Stat_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType                         Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
Std_ReturnType                         Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
Std_ReturnType                         Rte_Read_SysMon_TurnIndicatorCmd_Req_RetVal;
Std_ReturnType                         Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType                         Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType                         Rte_Read_CodM_Anima_Para_RetVal;
Std_ReturnType                         Rte_Read_SigPrep_AnimationReq_RetVal;
Std_ReturnType                         Rte_Write_AnimaScrollingActivation_RetVal;
Std_ReturnType                         Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8                                 Rte_Read_SysMon_VehNetState_HitCount;
uint8                                 Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
uint8                                 Rte_Read_SysMon_LowBeamCmd_Req_HitCount;
uint32                                Rte_Read_SysMon_TurnIndicatorCmd_Req_HitCount;
uint8                                 Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8                                 UtilDebounceInit_HitCount;
uint8                                 UtilDebounce_HitCount;
uint8                                 Rte_Read_CodM_Anima_Para_HitCount;
uint32                                Rte_Read_SigPrep_AnimationReq_HitCount;
uint32                                Rte_Write_AnimaScrollingActivation_HitCount;
uint8                                 Rte_Read_CddSwi_ScrollingOn_Stat_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// Stub function.
/// \brief  Rte_Write_AnimaScrollingActivation
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_AnimaScrollingActivation
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_AnimaScrollingActivation(const tsRte_TgtAniArrScr* ppara1)
{
    Rte_Write_AnimaScrollingActivation_Param1 = *ppara1;
    Rte_Write_AnimaScrollingActivation_HitCount++;
    return Rte_Write_AnimaScrollingActivation_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddSwi_ScrollingOn_Stat
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CddSwi_ScrollingOn_Stat
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddSwi_ScrollingOn_Stat(tScrollingPresent_Stat* ppara1)
{
    *ppara1 = Rte_Read_CddSwi_ScrollingOn_Stat_Param1;
    Rte_Read_CddSwi_ScrollingOn_Stat_HitCount++;
    return Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;
}

//-----------------------------------------------------------------------------
/// Stub function.
/// \brief  Rte_Read_SigPrep_AnimationReq
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_AnimationReq
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_AnimationReq(tsRte_AnimationReq* ppara1)
{
    ppara1->eFrontLightingAnimationCtrl = Rte_Read_SigPrep_AnimationReq_Param1.eFrontLightingAnimationCtrl;
    ppara1->eDelayFmh = Rte_Read_SigPrep_AnimationReq_Param1.eDelayFmh;
    ppara1->eSigQty = Rte_Read_SigPrep_AnimationReq_Param1.eSigQty;
    Rte_Read_SigPrep_AnimationReq_HitCount++;
    return Rte_Read_SigPrep_AnimationReq_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_VehNetState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehNetState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1)
{
    *ppara1 = Rte_Read_SysMon_VehNetState_Param1;
    Rte_Read_SysMon_VehNetState_HitCount++;
    return Rte_Read_SysMon_VehNetState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_StdLgtFcts_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_StdLgtFcts_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1)
{
    *ppara1 = Rte_Read_SysMon_StdLgtFcts_Req_Param1;
    Rte_Read_SysMon_StdLgtFcts_Req_HitCount++;
    return Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LowBeamCmd_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LowBeamCmd_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1)
{
    *ppara1 = Rte_Read_SysMon_LowBeamCmd_Req_Param1;
    Rte_Read_SysMon_LowBeamCmd_Req_HitCount++;
    return Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_TurnIndicatorCmd_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_TurnIndicatorCmd_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_TurnIndicatorCmd_Req(teRte_ReqLightState* ppara1)
{
    *ppara1 = Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1;
    Rte_Read_SysMon_TurnIndicatorCmd_Req_HitCount++;
    return Rte_Read_SysMon_TurnIndicatorCmd_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAbUser_GetMountingSide
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_IoHwAbUser_GetMountingSide
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
    *ppara1 = Rte_Read_IoHwAbUser_GetMountingSide_Param1;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount++;
    return Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  UtilDebounceInit
///
/// \descr  Stub function created to simulate the behaviour of UtilDebounceInit
///
/// \param  pCtrl
/// \param  eStateInit
/// \param  tOnDelay
/// \param  tOffDelay
///
/// \return void
//-----------------------------------------------------------------------------
void UtilDebounceInit(tUtilDebounceControl* const pCtrl, tieDigState eStateInit, TIMER tOnDelay, TIMER tOffDelay)
{
    UtilDebounceInit_Param1 = *pCtrl;
    UtilDebounceInit_Param2 = eStateInit;
    UtilDebounceInit_Param3 = tOnDelay;
    UtilDebounceInit_Param4 = tOffDelay;
    UtilDebounceInit_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  UtilDebounce
///
/// \descr  Stub function created to simulate the behaviour of UtilDebounce
///
/// \param  pCtrl
/// \param  boVal
///
/// \return void
//-----------------------------------------------------------------------------
void UtilDebounce(tUtilDebounceControl* const pCtrl, boolean boVal)
{
    UtilDebounce_Param1 = *pCtrl;
    UtilDebounce_Param2 = boVal;
    UtilDebounce_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_Anima_Para
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CodM_Anima_Para
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_Anima_Para(tsRteCodingParameters* ppara1)
{
    *ppara1 = Rte_Read_CodM_Anima_Para_Param1;
    Rte_Read_CodM_Anima_Para_HitCount++;
    return Rte_Read_CodM_Anima_Para_RetVal;
}
