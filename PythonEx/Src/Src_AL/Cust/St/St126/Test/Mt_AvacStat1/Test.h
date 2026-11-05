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

// Headers of the Module
#include <Rte/RteCommonTypes.h>
#include <Nvm.h>
#include <UtilMath.h>
#include <AvacStat1Types.h>
#include <AvacStat1Data.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

extern tNvmPara_CodingArea*  AvacStat1_pCodingArea;
extern sint16                AvacStat1_nAutoAngleMin;
extern sint16                AvacStat1_nAutoAngleMax;
extern sint16                AvacStat1_nLwrStaticFilterServiceCounter;
extern uint8                 AvacStat1_byLwrRegulationExtendedMode;
extern uint8                 AvacStat1_bySampleTimeLong;
extern uint8                 AvacStat1_byStaticFilterSampleTime;
extern sint16                AvacStat1_nLwrConstantSpeedCounter;
extern uint8                 AvacStat1_byTstatic;
extern uint8                 AvacStat1_byLwrRegulationMode;
extern ORDER1_Filter         AvacStat1_LwrAccelerationFilter;
extern sint16                AvacStat1_nLwrTransientStateCounter;
extern sint16                AvacStat1_nAutoAngleGrad;
extern sint16                AvacStat1_nStaticAngle;
extern sint16                AvacStat1_nAutoAngle;
extern sint16                AvacStat1_nActualHeadlightAngle;
extern sint16                AvacStat1_nLwrLoadChangeCounter;
extern sint16                AvacStat1_nRefAngle;
extern boolean               AvacStat1_boCodingValidity;
extern uint8                 AvacStat1_ucSamplingUnitTest;
extern uint8                 AvacStat1_ucSafetyDelayUnitTest;
extern boolean               AvacStat1Data_boLowBeamOn;

//=============================================================================
// Module function declarations
//=============================================================================

extern void    riAvacStat1_Init(void);
extern void    rpAvacStat1_Cycle0(void);

extern void    AvacStat1_CheckZeroLvl(void);
extern void    AvacStat1_SetSpeedMode(void);
extern void    AvacStat1_Init(void);
extern boolean AvacStat1_SetStaticFilterParameters(void);
extern void    AvacStat1_SetRegMode(sint16 Speed, sint16 Acc, uint8 Mode);
extern sint16  AvacStat1_GetHeadlightAngle(void);
extern void    AvacStat1_Cycle0(void);

extern void    AvacStat1Util_Order1Filter(ORDER1_Filter* pFilter, sint16 nValue, uint16 unBeta);
extern void    AvacStat1Util_Order1FilterInit(ORDER1_Filter* pFilter, sint16 Value);
extern sint16  AvacStat1Util_Order1FilterValue(ORDER1_Filter* pFilter);

extern void    AvacStat1Data_ReadAslPhase(teAvacStat1_LvlPhase* psData);
extern void    AvacStat1Data_ReadSpeed(tAvacStat_Speed* pSpeed);
extern void    AvacStat1Data_ReadPitch(tAvacStat_Pitch* pPitch);
extern void    AvacStat1Data_WriteSpeedMode(const teAvacStat_SpeedMode* peAvacSpeedMode);
extern void    AvacStat1Data_WriteAvacOut(const tAvacStat_Out* pAvacOut);
extern boolean AvacStat1Data_GetAvacS_En(void);
extern boolean AvacStat1Data_GetAvacS_Ok(void);
extern boolean AvacStat1Data_GetLowBeamOn(void);
extern boolean AvacStat1Data_ParaFct0(tParaFct0_Cmd eCmd, tNvmPara_CodingArea* CONST_AL pData);
extern boolean AvacStat1Data_CodingDataValidation(void);
extern void    AvacStat1Data_Get_CodingPara(tsAvacStat1_CodingParam *psCodingParam);

//=============================================================================
// Module function parameter stubs
//=============================================================================

sint16                  AvacStat1_SetRegMode_Param1;
sint16                  AvacStat1_SetRegMode_Param2;
uint8                   AvacStat1_SetRegMode_Param3;

ORDER1_Filter           AvacStat1Util_Order1Filter_Param1;
sint16                  AvacStat1Util_Order1Filter_Param2;
uint16                  AvacStat1Util_Order1Filter_Param3;
ORDER1_Filter           AvacStat1Util_Order1FilterInit_Param1;
sint16                  AvacStat1Util_Order1FilterInit_Param2;
ORDER1_Filter           AvacStat1Util_Order1FilterValue_Param1;

teAvacStat1_LvlPhase    AvacStat1Data_ReadAslPhase_Param1;
tAvacStat_Speed         AvacStat1Data_ReadSpeed_Param1;
tAvacStat_Pitch         AvacStat1Data_ReadPitch_Param1;
teAvacStat_SpeedMode    AvacStat1Data_WriteSpeedMode_Param1;
tAvacStat_Out           AvacStat1Data_WriteAvacOut_Param1;
tParaFct0_Cmd           AvacStat1Data_ParaFct0_Param1;
tNvmPara_CodingArea*    AvacStat1Data_ParaFct0_Param2;
tsAvacStat1_CodingParam AvacStat1Data_Get_CodingPara_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

boolean       AvacStat1_SetStaticFilterParameters_RetVal;
sint16        AvacStat1_GetHeadlightAngle_RetVal;

sint16        AvacStat1Util_Order1FilterValue_RetVal;

boolean       AvacStat1Data_GetAvacS_En_RetVal;
boolean       AvacStat1Data_GetAvacS_Ok_RetVal;
boolean       AvacStat1Data_GetLowBeamOn_RetVal;
boolean       AvacStat1Data_ParaFct0_RetVal;
boolean       AvacStat1Data_CodingDataValidation_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

tNvmPara_CodingArea AvacStat1_Coding_Dummy;

#endif // TEST_2023_08_25_H_
