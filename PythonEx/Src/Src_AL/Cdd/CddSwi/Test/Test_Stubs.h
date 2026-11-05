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
#include <AL_Helper.h>
#include <CddSwi_Types.h>
#include <RteCommonTypes.h>
#include <CodM_Para.h>
#include <CodM_Types.h>

//=============================================================================
// Typedef
//=============================================================================
typedef unsigned char         tucCddVnd7140_Error;
typedef unsigned char         tucCddVnd7140_HWState;

typedef struct
{
  tucCddVnd7140_HWState       ucHwState;
  uint16                      unActVal;
  uint16                      unActCurrent;
  tucCddVnd7140_Error         ucErrOpenLoad;
  tucCddVnd7140_Error         ucErrShort2VBAT;
  tucCddVnd7140_Error         ucErrShort2GND;
}tsCddVnd7140_DrvStatus;

typedef unsigned char         tucCddVn7140_Error;
typedef unsigned char         tucCddVn7140_HWState;

typedef struct
{
  tucCddVn7140_HWState        ucHwState;
  uint16                      unActVal;
  uint16                      unActCurrent;
  tucCddVn7140_Error          ucErrOpenLoad;
  tucCddVn7140_Error          ucErrShort2VBAT;
  tucCddVn7140_Error          ucErrShort2GND;
}tsCddVn7140_DrvStatus;
//=============================================================================
// Stub function declarations
//=============================================================================
Std_ReturnType                Rte_Write_CddSwi_SwitchStatus(tsRte_HssStatus *pData);
Std_ReturnType                Rte_Write_CddSwi_SetLssPwm_Req(const uint16* ppara1);
Std_ReturnType                Rte_Write_CddSwi_ScrollingOn_Stat(const boolean* ppara1);

Std_ReturnType                Rte_Read_CodM_CddSwi_Para(tsRteCodingParameters* pData);
Std_ReturnType                Rte_Read_CtrlSwi_TgtValue_Fan1(tRteSwitchTgtVal *pData);
Std_ReturnType                Rte_Read_CtrlSwi_TgtValue_Fan2(tRteSwitchTgtVal *pData);
Std_ReturnType                Rte_Read_CtrlSwi_TgtValue_SMRGB(tRteSwitchTgtVal *pData);
Std_ReturnType                Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite(teRte_SateliteStatus* ppara1);

void                          CddVn7140_DeInit(CONST_AL uint32 ulChipIdx);
void                          CddVnd7140_DeInit(CONST_AL uint32 ulChipIdx);
void                          CddVn7140_Init(CONST_AL uint32 ulChipIdx);
void                          CddVnd7140_Init(CONST_AL uint32 ulChipIdx);
void                          CddVnd7140_Cycle0(void);
void                          CddVn7140_Cycle0(void);
tsCddVnd7140_DrvStatus        CddVnd7140_GetState(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx);
tsCddVn7140_DrvStatus         CddVn7140_GetState(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx);
void                          CddVnd7140_SetTgt(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx, CONST_AL uint16 unTgtVal);
void                          CddVn7140_SetTgt(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx, CONST_AL uint16 unTgtVal);
void                          IoHwAbUser_GetOutFctDiag(boolean *boLssDiagnostic);
uint16                        CddSbc_GetPWM(uint8 ucMode);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern tsRte_HssStatus        Rte_Write_CddSwi_SwitchStatus_Param1;
extern uint16                 Rte_Write_CddSwi_SetLssPwm_Req_Param1;
extern boolean                Rte_Write_CddSwi_ScrollingOn_Stat_Param1;

extern tsRteCodingParameters  Rte_Read_CodM_CddSwi_Para_Param1;
extern tRteSwitchTgtVal       Rte_Read_CtrlSwi_TgtValue_Fan1_Param1;
extern tRteSwitchTgtVal       Rte_Read_CtrlSwi_TgtValue_Fan2_Param1;
extern tRteSwitchTgtVal       Rte_Read_CtrlSwi_TgtValue_SMRGB_Param1;
extern teRte_SateliteStatus   Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1;

extern uint32                 CddVn7140_DeInit_Param1;
extern uint32                 CddVnd7140_DeInit_Param1;
extern uint32                 CddVn7140_Init_Param1;
extern uint32                 CddVnd7140_Init_Param1;
extern uint32                 CddVnd7140_GetState_Param1;
extern uint32                 CddVnd7140_GetState_Param2;
extern uint32                 CddVn7140_GetState_Param1;
extern uint32                 CddVn7140_GetState_Param2;
extern uint32                 CddVnd7140_SetTgt_Param1;
extern uint32                 CddVnd7140_SetTgt_Param2;
extern uint16                 CddVnd7140_SetTgt_Param3;
extern uint32                 CddVn7140_SetTgt_Param1;
extern uint32                 CddVn7140_SetTgt_Param2;
extern uint16                 CddVn7140_SetTgt_Param3;
extern boolean                IoHwAbUser_GetOutFctDiag_Param1;
extern uint8                  CddSbc_GetPWM_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern Std_ReturnType         Rte_Write_CddSwi_SwitchStatus_RetVal;
extern Std_ReturnType         Rte_Write_CddSwi_SetLssPwm_Req_RetVal;
extern Std_ReturnType         Rte_Write_CddSwi_ScrollingOn_Stat_RetVal;

extern Std_ReturnType         Rte_Read_CodM_CddSwi_Para_RetVal;
extern Std_ReturnType         Rte_Read_CtrlSwi_TgtValue_Fan1_RetVal;
extern Std_ReturnType         Rte_Read_CtrlSwi_TgtValue_Fan2_RetVal;
extern Std_ReturnType         Rte_Read_CtrlSwi_TgtValue_SMRGB_RetVal;
extern Std_ReturnType         Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;

extern tsCddVnd7140_DrvStatus CddVnd7140_GetState_RetVal;
extern tsCddVn7140_DrvStatus  CddVn7140_GetState_RetVal;
extern uint16                 CddSbc_GetPWM_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8                  Rte_Write_CddSwi_SwitchStatus_HitCount;
extern uint8                  Rte_Write_CddSwi_SetLssPwm_Req_HitCount;
extern uint8                  Rte_Write_CddSwi_ScrollingOn_Stat_HitCount;

extern uint8                  Rte_Read_CodM_CddSwi_Para_HitCount;
extern uint8                  Rte_Read_CtrlSwi_TgtValue_Fan1_HitCount;
extern uint8                  Rte_Read_CtrlSwi_TgtValue_Fan2_HitCount;
extern uint8                  Rte_Read_CtrlSwi_TgtValue_SMRGB_HitCount;
extern uint8                  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount;

extern uint8                  CddVn7140_DeInit_HitCount;
extern uint8                  CddVnd7140_DeInit_HitCount;
extern uint8                  CddVn7140_Init_HitCount;
extern uint8                  CddVnd7140_Init_HitCount;
extern uint8                  CddVn7140_Cycle0_HitCount;
extern uint8                  CddVnd7140_Cycle0_HitCount;
extern uint8                  CddVn7140_GetState_HitCount;
extern uint8                  CddVnd7140_GetState_HitCount;
extern uint8                  CddVn7140_SetTgt_HitCount;
extern uint8                  CddVnd7140_SetTgt_HitCount;
extern uint8                  IoHwAbUser_GetOutFctDiag_HitCount;
extern uint8                  CddSbc_GetPWM_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
