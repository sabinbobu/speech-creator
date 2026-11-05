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

#include <Swc/FctR/FctR_Types.h>
#include <Swc\AfsMaster\Avac\AvacTypes.h>
#include <Swc/CodM/CodM_Para.h>
#include <Swc/CodM/CodM_Types.h>
#include <Nvm.h>
#include <Avac.h>
#include <AvacData.h>
#include <AvacVdd.h>
#include <AvacAlg.h>


//=============================================================================
// Typedefs
//=============================================================================

typedef sint32 ORDER1_Filter;

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

extern boolean               AvacData_boCodingValid;
extern boolean               AvacData_boUseDynamicLeveling;
extern uint8                 AvacVdd_ucDynState;
extern uint8                 AvacVdd_ucAccIndex;
extern sint8                 AvacVdd_acAccelArray[11u];
extern uint8                 AvacVdd_ucBadStreetIndex;
extern ORDER1_Filter         AvacVdd_AccelFilter;
extern ORDER1_Filter         AvacVddBadStreetHP;
extern ORDER1_Filter         AvacVddBadStreetLP;
extern boolean               AvacData_boPitchConfigValid;
extern sint16                Avac_nAutoAngle;
extern uint8                 AvacData_ucGradientLimiterUp;
extern uint8                 AvacData_ucGradientLimiterDown;
extern sint16                Avac_nStaticAngleGrad;
extern sint16                Avac_nStaticAngle;
extern uint8                 Avac_ucDynamicIndex;
extern sint8                 Avac_cDynamicIndexCtr;
extern boolean               Avac_boMovingUp;
extern sint16                Avac_nDynamicAngle;
extern uint8                 Avac_ucActualFilterTime;
extern sint16                Avac_nDynamicAngleGrad;
extern sint16                Avac_nAngleSum;
extern teRte_SigQty          Avac_AngleQty;
extern boolean               AvacData_boLowBeamOn;
extern tNvmPara_AvacStpBlock AvacData_CodingData;
extern uint16                AvacVdd_unAccelFilterCoef;          
extern uint16                AvacVdd_unBadStreetHPFilterCoef;    
extern uint16                AvacVdd_unBadStreetLPFilterCoefRise;
extern uint16                AvacVdd_unBadStreetLPFilterCoefFall;

//=============================================================================
// Module function declarations
//=============================================================================

/*Avac.c*/

extern void    Avac_CheckZeroLvl(void);

/*AvacUtil.c*/
extern sint16  AvacUtil_Order1FilterByRelTime(ORDER1_Filter* pFilter, uint16 unRelTime, sint16 nValue);
extern sint16  AvacUtil_SignalLimiter(sint16 LimitMax, sint16 LimitMin, sint16 Value);
extern void    AvacUtil_RateLimiter(sint16* pRateLimiter, sint16 RateUp, sint16 RateDown, sint16 Value);

/*AvacAlgDyn1.c*/
extern void    GetAutoAngle_(void);
extern void    DoStaticRegulation_(void);
extern void    SetDynamicIndex_(void);
extern void    SetFilterTimeConstants_(void);
extern void    DoDynamicRegulation_(void);
extern void    CreateOutputSignal_(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================

tParaFct0_Cmd                   AvacData_ParaFct0_Param1;
tNvmPara_CodingArea             AvacData_ParaFct0_Param2;
tAvac_Pitch                     AvacData_ReadPitch_Param1;
tAvac_Speed                     AvacData_ReadSpeed_Param1;
tAvac_AccelPreDetect            AvacData_ReadAccelPreDetect_Param1;
tAvac_BrakePreDetect            AvacData_ReadBrakePreDetect_Param1;
tAvac_Out                       AvacData_WriteAvacOut_Param1;

ORDER1_Filter                   AvacUtil_Order1FilterByRelTime_Param1;
uint16                          AvacUtil_Order1FilterByRelTime_Param2;
sint16                          AvacUtil_Order1FilterByRelTime_Param3;

//=============================================================================
// Module function return value stubs
//=============================================================================

boolean        AvacData_GetLowBeamOn_RetVal;
boolean        AvacData_GetAvacS_Ok_RetVal;
boolean        AvacData_GetAvacS_En_RetVal;
boolean        AvacData_GetAvacD_Ok_RetVal;
boolean        AvacData_GetAvacD_En_RetVal;

sint16         AvacUtil_Order1FilterByRelTime_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================


#endif // TEST_2023_08_25_H_
