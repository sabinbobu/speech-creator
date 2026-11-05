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
#include <AL_Helper.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================
extern tNvmPara_CodingArea*   CddSwi_pCodingArea;
extern boolean                CddSwi_boCodingValid;
extern tsCddSwi_Router        CddSwi_asRouteList[4u];
extern boolean                CddSwi_boFanActive;
extern boolean                CddSwi_boHss3Active;
extern sint8                  snHSS3_MinDutyCycle_ut;

//=============================================================================
// Module function declarations
//=============================================================================
extern uint16                 Cod_HSS1Shor2GndThr(void);
extern uint16                 Cod_HSS1Shor2VbatThr(void);
extern uint16                 Cod_HSS1OpenLoadThr(void);
extern uint16                 Cod_HSS2Shor2GndThr(void);
extern uint16                 Cod_HSS2Shor2VbatThr(void);
extern uint16                 Cod_HSS2OpenLoadThr(void);
extern uint16                 Cod_HSS3Shor2GndThr(void);
extern uint16                 Cod_HSS3Shor2VbatThr(void);
extern uint16                 Cod_HSS3OpenLoadThr(void);
extern boolean                Cod_DiagValid(void);

extern void                   CddSwi_Rou_Init(void);
extern void                   CddSwi_Rou_Cycle0(void);
extern void                   CddSwi_Rou_SetTgt(CONST_AL uint32 ulChnIdx, CONST_AL uint16 unTgtVal);
extern tsCddSwi_SwitchStatus  CddSwi_Rou_GetState(CONST_AL uint32 ulChnIdx);
extern void                   CddSwi_Rou_DeInit(void);
extern Std_ReturnType         CddSwi_Rou_Read_Fan1_TgtVal(tCddSwi_TgtVal *pData);
extern Std_ReturnType         CddSwi_Rou_Read_Fan2_TgtVal(tCddSwi_TgtVal *pData);
extern Std_ReturnType         CddSwi_Rou_Write_SwitchStatus(tsCddSwi_SwitchStatus* asState);
extern void                   CddSwi_Rou_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
extern void                   CddSwi_Rou_MapParams(void);

extern void                   CddSwi_Init(void);
extern void                   CddSwi_Cycle0(void);
extern void                   CddSwi_DeInit(void);
extern void                   CddSwi_SetTgt(CONST_AL uint32 ulChnIdx, CONST_AL uint16 unTgtVal);
extern tsCddSwi_SwitchStatus  CddSwi_GetState(CONST_AL uint32 ulChnIdx);
extern tScrollingPresent_Stat CddSwi_Rou_CheckScrollingSatellite_Status(void);
extern Std_ReturnType         CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal(uint16 *pData);

extern void                   riCddSwi_Init(void);
extern void                   rpCddSwi_Cycle0(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
uint16                        CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1;
uint32                        CddSwi_Rou_SetTgt_Param1;
uint16                        CddSwi_Rou_SetTgt_Param2;
uint32                        CddSwi_Rou_GetState_Param1;
tCddSwi_TgtVal                CddSwi_Rou_Read_Fan1_TgtVal_Param1;
tCddSwi_TgtVal                CddSwi_Rou_Read_Fan2_TgtVal_Param1;
tsCddSwi_SwitchStatus         CddSwi_Rou_Write_SwitchStatus_Param1[3u];
tsCddSwi_SwitchStatus*        CddSwi_Rou_Write_SwitchStatus_Param1_Dummy;
tParaFct0_Cmd                 CddSwi_Rou_ParaFct0_Param1;
tNvmPara_CodingArea           CddSwi_Rou_ParaFct0_Param2;

uint32                        CddSwi_SetTgt_Param1;
uint32                        CddSwi_SetTgt_Param2;
uint32                        CddSwi_GetState_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
uint16                        Cod_DiagValid_RetVal;
uint16                        Cod_HSS1Shor2GndThr_RetVal;
uint16                        Cod_HSS1Shor2VbatThr_RetVal;
uint16                        Cod_HSS1OpenLoadThr_RetVal;
uint16                        Cod_HSS2Shor2GndThr_RetVal;
uint16                        Cod_HSS2Shor2VbatThr_RetVal;
uint16                        Cod_HSS2OpenLoadThr_RetVal;
uint16                        Cod_HSS3Shor2GndThr_RetVal;
uint16                        Cod_HSS3Shor2VbatThr_RetVal;
uint16                        Cod_HSS3OpenLoadThr_RetVal;

tsCddSwi_SwitchStatus         CddSwi_Rou_GetState_RetVal;
Std_ReturnType                CddSwi_Rou_Read_Fan1_TgtVal_RetVal;
Std_ReturnType                CddSwi_Rou_Read_Fan2_TgtVal_RetVal;
Std_ReturnType                CddSwi_Rou_Write_SwitchStatus_RetVal;
Std_ReturnType                CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_RetVal;
tScrollingPresent_Stat        CddSwi_Rou_CheckScrollingSatellite_Status_RetVal;

tsCddSwi_SwitchStatus         CddSwi_GetState_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

#endif // TEST_2023_08_25_H_
