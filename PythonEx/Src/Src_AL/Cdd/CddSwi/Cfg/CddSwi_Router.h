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
/// \file  CddSwi_Router.h
///
/// \brief  Configuration of Cdd Switch router
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_SWI_ROUTER_2021_03_01_H_
#define CDD_SWI_ROUTER_2021_03_01_H_

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>
#include <CddSwi_Types.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

//=============================================================================
// externals variables
//=============================================================================
extern CONST_AL  tNvmPara_CodingArea*  CddSwi_pCodingArea;

//=============================================================================
// Prototypes
//=============================================================================

uint16                Cod_HSS1Shor2GndThr(void);
uint16                Cod_HSS1Shor2VbatThr(void);
uint16                Cod_HSS1OpenLoadThr(void);
uint16                Cod_HSS2Shor2GndThr(void);
uint16                Cod_HSS2Shor2VbatThr(void);
uint16                Cod_HSS2OpenLoadThr(void);
uint16                Cod_HSS3Shor2GndThr(void);
uint16                Cod_HSS3Shor2VbatThr(void);
uint16                Cod_HSS3OpenLoadThr(void);
boolean               Cod_DiagValid(void);
uint8                 Cod_HSS3Min_Pwm(void);

void                  CddSwi_Rou_Init(void);
void                  CddSwi_Rou_Cycle0(void);
void                  CddSwi_Rou_SetTgt(CONST_AL uint32 ulChnIdx, CONST_AL uint16 unTgtVal);
void                  CddSwi_Rou_DeInit(void);
tsCddSwi_SwitchStatus CddSwi_Rou_GetState(CONST_AL uint32 ulChnIdx);
Std_ReturnType        CddSwi_Rou_Read_Fan1_TgtVal(tCddSwi_TgtVal *pData);
Std_ReturnType        CddSwi_Rou_Write_SwitchStatus(tsCddSwi_SwitchStatus* asState);
void                  CddSwi_Rou_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
void                  CddSwi_Rou_MapParams(void);
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
tScrollingPresent_Stat CddSwi_Rou_CheckScrollingSatellite_Status(void);
Std_ReturnType        CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal(uint16 *pData);
#endif


#ifdef SAMPLE_FULL
Std_ReturnType        CddSwi_Rou_Read_Fan2_TgtVal(tCddSwi_TgtVal *pData);
#endif
Std_ReturnType        CddSwi_Rou_Read_RGB_SM_TgtVal(tCddSwi_TgtVal *pData);

#endif // CDD_SWI_ROUTER_2021_03_01_H_