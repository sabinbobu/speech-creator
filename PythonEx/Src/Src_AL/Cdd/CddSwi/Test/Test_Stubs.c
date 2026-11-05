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
tsRte_HssStatus        Rte_Write_CddSwi_SwitchStatus_Param1;
uint16                 Rte_Write_CddSwi_SetLssPwm_Req_Param1;
boolean                Rte_Write_CddSwi_ScrollingOn_Stat_Param1;

tsRteCodingParameters  Rte_Read_CodM_CddSwi_Para_Param1;
tRteSwitchTgtVal       Rte_Read_CtrlSwi_TgtValue_Fan1_Param1;
tRteSwitchTgtVal       Rte_Read_CtrlSwi_TgtValue_Fan2_Param1;
tRteSwitchTgtVal       Rte_Read_CtrlSwi_TgtValue_SMRGB_Param1;
teRte_SateliteStatus   Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1;

uint32                 CddVn7140_DeInit_Param1;
uint32                 CddVnd7140_DeInit_Param1;
uint32                 CddVn7140_Init_Param1;
uint32                 CddVnd7140_Init_Param1;
uint32                 CddVnd7140_GetState_Param1;
uint32                 CddVnd7140_GetState_Param2;
uint32                 CddVn7140_GetState_Param1;
uint32                 CddVn7140_GetState_Param2;
uint32                 CddVnd7140_SetTgt_Param1;
uint32                 CddVnd7140_SetTgt_Param2;
uint16                 CddVnd7140_SetTgt_Param3;
uint32                 CddVn7140_SetTgt_Param1;
uint32                 CddVn7140_SetTgt_Param2;
uint16                 CddVn7140_SetTgt_Param3;
boolean                IoHwAbUser_GetOutFctDiag_Param1;
uint8                  CddSbc_GetPWM_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType         Rte_Write_CddSwi_SwitchStatus_RetVal;
Std_ReturnType         Rte_Write_CddSwi_SetLssPwm_Req_RetVal;
Std_ReturnType         Rte_Write_CddSwi_ScrollingOn_Stat_RetVal;

Std_ReturnType         Rte_Read_CodM_CddSwi_Para_RetVal;
Std_ReturnType         Rte_Read_CtrlSwi_TgtValue_Fan1_RetVal;
Std_ReturnType         Rte_Read_CtrlSwi_TgtValue_Fan2_RetVal;
Std_ReturnType         Rte_Read_CtrlSwi_TgtValue_SMRGB_RetVal;
Std_ReturnType         Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;

tsCddVnd7140_DrvStatus CddVnd7140_GetState_RetVal;
tsCddVn7140_DrvStatus  CddVn7140_GetState_RetVal;
uint16                 CddSbc_GetPWM_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8                  Rte_Write_CddSwi_SwitchStatus_HitCount;
uint8                  Rte_Write_CddSwi_SetLssPwm_Req_HitCount;
uint8                  Rte_Write_CddSwi_ScrollingOn_Stat_HitCount;
                       
uint8                  Rte_Read_CodM_CddSwi_Para_HitCount;
uint8                  Rte_Read_CtrlSwi_TgtValue_Fan1_HitCount;
uint8                  Rte_Read_CtrlSwi_TgtValue_Fan2_HitCount;
uint8                  Rte_Read_CtrlSwi_TgtValue_SMRGB_HitCount;
uint8                  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount;
                       
uint8                  CddVn7140_DeInit_HitCount;
uint8                  CddVnd7140_DeInit_HitCount;
uint8                  CddVn7140_Init_HitCount;
uint8                  CddVnd7140_Init_HitCount;
uint8                  CddVn7140_Cycle0_HitCount;
uint8                  CddVnd7140_Cycle0_HitCount;
uint8                  CddVn7140_GetState_HitCount;
uint8                  CddVnd7140_GetState_HitCount;
uint8                  CddVn7140_SetTgt_HitCount;
uint8                  CddVnd7140_SetTgt_HitCount;
uint8                  IoHwAbUser_GetOutFctDiag_HitCount;
uint8                  CddSbc_GetPWM_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_CddSwi_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_CddSwi_Para
///
/// \param  *pData
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CddSwi_Para(tsRteCodingParameters* pData)
{
  *pData = Rte_Read_CodM_CddSwi_Para_Param1;
  Rte_Read_CodM_CddSwi_Para_HitCount++;
  return Rte_Read_CodM_CddSwi_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddVn7140_SetTgt
///
/// \descr  Stub function created to simulate the behaviour of CddVn7140_SetTgt
///
/// \param  ulChipIdx
/// \param  ulOutIdx
/// \param  unTgtVal
///
/// \return void
//-----------------------------------------------------------------------------
void CddVn7140_SetTgt(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx, CONST_AL uint16 unTgtVal)
{
  CddVn7140_SetTgt_Param1 = ulChipIdx;
  CddVn7140_SetTgt_Param2 = ulOutIdx;
  CddVn7140_SetTgt_Param3 = unTgtVal;
  CddVn7140_SetTgt_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_SetTgt
///
/// \descr  Stub function created to simulate the behaviour of CddVnd7140_SetTgt
///
/// \param  ulChipIdx
/// \param  ulOutIdx
/// \param  unTgtVal
///
/// \return void
//-----------------------------------------------------------------------------
void CddVnd7140_SetTgt(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx, CONST_AL uint16 unTgtVal)
{
  CddVnd7140_SetTgt_Param1 = ulChipIdx;
  CddVnd7140_SetTgt_Param2 = ulOutIdx;
  CddVnd7140_SetTgt_Param3 = unTgtVal;
  CddVnd7140_SetTgt_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddVn7140_GetState
///
/// \descr  Stub function created to simulate the behaviour of CddVn7140_GetState
///
/// \param  ulChipIdx
/// \param  ulOutIdx
///
/// \return tsCddVn7140_DrvStatus
//-----------------------------------------------------------------------------
tsCddVn7140_DrvStatus CddVn7140_GetState(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx)
{
  CddVn7140_GetState_Param1 = ulChipIdx;
  CddVn7140_GetState_Param2 = ulOutIdx;
  CddVn7140_GetState_HitCount++;
  return CddVn7140_GetState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_GetState
///
/// \descr  Stub function created to simulate the behaviour of CddVnd7140_GetState
///
/// \param  ulChipIdx
/// \param  ulOutIdx
///
/// \return tsCddVnd7140_DrvStatus
//-----------------------------------------------------------------------------
tsCddVnd7140_DrvStatus CddVnd7140_GetState(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx)
{
  CddVnd7140_GetState_Param1 = ulChipIdx;
  CddVnd7140_GetState_Param2 = ulOutIdx;
  CddVnd7140_GetState_HitCount++;
  return CddVnd7140_GetState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddVn7140_Cycle0
///
/// \descr  Stub function created to simulate the behaviour of CddVn7140_Cycle0
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddVn7140_Cycle0(void)
{
  CddVn7140_Cycle0_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_Cycle0
///
/// \descr  Stub function created to simulate the behaviour of CddVnd7140_Cycle0
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddVnd7140_Cycle0(void)
{
  CddVnd7140_Cycle0_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddVn7140_Init
///
/// \descr  Stub function created to simulate the behaviour of CddVn7140_Init
///
/// \param  ulChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddVn7140_Init(CONST_AL uint32 ulChipIdx)
{
  CddVn7140_Init_Param1 = ulChipIdx;
  CddVn7140_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_Init
///
/// \descr  Stub function created to simulate the behaviour of CddVnd7140_Init
///
/// \param  ulChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddVnd7140_Init(CONST_AL uint32 ulChipIdx)
{
  CddVnd7140_Init_Param1 = ulChipIdx;
  CddVnd7140_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddVn7140_DeInit
///
/// \descr  Stub function created to simulate the behaviour of CddVn7140_DeInit
///
/// \param  ulChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddVn7140_DeInit(CONST_AL uint32 ulChipIdx)
{
  CddVn7140_DeInit_Param1 = ulChipIdx;
  CddVn7140_DeInit_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddVnd7140_DeInit
///
/// \descr  Stub function created to simulate the behaviour of CddVnd7140_DeInit
///
/// \param  ulChipIdx
///
/// \return void
//-----------------------------------------------------------------------------
void CddVnd7140_DeInit(CONST_AL uint32 ulChipIdx)
{
  CddVnd7140_DeInit_Param1 = ulChipIdx;
  CddVnd7140_DeInit_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CddSwi_SwitchStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CddSwi_SwitchStatus
///
/// \param  *pData
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CddSwi_SwitchStatus(tsRte_HssStatus *pData)
{
  Rte_Write_CddSwi_SwitchStatus_Param1 = *pData;
  Rte_Write_CddSwi_SwitchStatus_HitCount++;
  return Rte_Write_CddSwi_SwitchStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlSwi_TgtValue_Fan1
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlSwi_TgtValue_Fan1
///
/// \param  *pData
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlSwi_TgtValue_Fan1(tRteSwitchTgtVal *pData)
{
  *pData = Rte_Read_CtrlSwi_TgtValue_Fan1_Param1;
  Rte_Read_CtrlSwi_TgtValue_Fan1_HitCount++;
  return Rte_Read_CtrlSwi_TgtValue_Fan1_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlSwi_TgtValue_Fan2
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlSwi_TgtValue_Fan2
///
/// \param  *pData
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlSwi_TgtValue_Fan2(tRteSwitchTgtVal *pData)
{
  *pData = Rte_Read_CtrlSwi_TgtValue_Fan2_Param1;
  Rte_Read_CtrlSwi_TgtValue_Fan2_HitCount++;
  return Rte_Read_CtrlSwi_TgtValue_Fan2_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlSwi_TgtValue_SMRGB
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlSwi_TgtValue_SMRGB
///
/// \param  *pData
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlSwi_TgtValue_SMRGB(tRteSwitchTgtVal *pData)
{
  *pData = Rte_Read_CtrlSwi_TgtValue_SMRGB_Param1;
  Rte_Read_CtrlSwi_TgtValue_SMRGB_HitCount++;
  return Rte_Read_CtrlSwi_TgtValue_SMRGB_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CddSwi_SetLssPwm_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CddSwi_SetLssPwm_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CddSwi_SetLssPwm_Req(const uint16* ppara1)
{
  Rte_Write_CddSwi_SetLssPwm_Req_Param1 = *ppara1;
  Rte_Write_CddSwi_SetLssPwm_Req_HitCount++;
  return Rte_Write_CddSwi_SetLssPwm_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CddSwi_ScrollingOn_Stat
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CddSwi_ScrollingOn_Stat
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CddSwi_ScrollingOn_Stat(const boolean* ppara1)
{
  Rte_Write_CddSwi_ScrollingOn_Stat_Param1 = *ppara1;
  Rte_Write_CddSwi_ScrollingOn_Stat_HitCount++;
  return Rte_Write_CddSwi_ScrollingOn_Stat_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite(teRte_SateliteStatus* ppara1)
{
  *ppara1 = Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1;
  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount++;
  return Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_GetOutFctDiag
///
/// \descr  Stub function created to simulate the behaviour of  IoHwAbUser_GetOutFctDiag
///
/// \param  boLssDiagnostic
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetOutFctDiag(boolean *boLssDiagnostic)
{
  *boLssDiagnostic = IoHwAbUser_GetOutFctDiag_Param1;
  IoHwAbUser_GetOutFctDiag_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddSbc_GetPWM
///
/// \descr  Stub function created to simulate the behaviour of CddSbc_GetPWM
///
/// \param  -
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 CddSbc_GetPWM(uint8 ucMode)
{
  CddSbc_GetPWM_Param1 = ucMode;
  CddSbc_GetPWM_HitCount++;
  return CddSbc_GetPWM_RetVal;
}
