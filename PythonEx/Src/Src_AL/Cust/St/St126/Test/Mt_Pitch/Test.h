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

#include <../Pitch/Pitch_Types.h>
#include <utilMath.h>
#include <Dem_EventListId.h>
#include <UtilMath.h>


//=============================================================================
// Defines
//=============================================================================

#define PITCH_TauTracking     Tau128   // 128 * 20ms = 2.5s: time constant used for tracking filter
#define PITCH_JitterTol       10      // 10 * 0.1mm = 1mm:  minimum change for dynamic behaviour

#define PITCH_FR_SENSOR       0u
#define PITCH_RR_SENSOR       1u
#define PITCH_RADIUS_SCALING  10000
#define PITCH_ZERO_LEVEL_DONE 0xFFu

#define Rte_Call_DemPrj_ReportErrorStatus(arg1, arg2) \
  (Dem_SetEventStatus(arg1, arg2))

#define CFG_CntSens        (2u)   
#define DEM_EVENT_STATUS_PREFAILED          0x03u
#define DEM_EVENT_STATUS_FAILED             DEM_EVENT_STATUS_PREFAILED

#define DEM_EVENT_STATUS_PREPASSED          0x0
#define DEM_EVENT_STATUS_PASSED             DEM_EVENT_STATUS_PREPASSED
#define DEM_EVENT_STATUS_FAILED             DEM_EVENT_STATUS_PREFAILED

#ifndef max
#define max(a,b)                  (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)                  (((a) < (b)) ? (a) : (b))
#endif

//=============================================================================
// Typedefs
//=============================================================================

typedef sint32 tFiltIir_s;

//=============================================================================
// Module global variables
//=============================================================================


extern TIMER     Pitch_ulCheckBHS_us;
extern TIMER     Pitch_ulCheckDisp_us;
extern sint16    Sens_Disp[2];

extern ORDER1_Filter Pitch_DT1SensFrontRMounting;
extern ORDER1_Filter Pitch_PT1SensFrontRMountingPreOk;
extern ORDER1_Filter Pitch_PT1SensFrontRMountingPreErr;
extern ORDER1_Filter Pitch_PT1SensFrontRMountingOk;
extern ORDER1_Filter Pitch_PT1SensFrontRMountingErr;

extern ORDER1_Filter Pitch_DT1SensRearRMounting;
extern ORDER1_Filter Pitch_PT1SensRearRMountingPreOk;
extern ORDER1_Filter Pitch_PT1SensRearRMountingPreErr;
extern ORDER1_Filter Pitch_PT1SensRearRMountingOk;
extern ORDER1_Filter Pitch_PT1SensRearRMountingErr;

extern sint16 Pitch_nSensFrontRHyst;
extern sint16 Pitch_nSensFrontRGrad;
extern sint16 Pitch_nSensFrontRFilterPreOk;
extern sint16 Pitch_nSensFrontRFilterPreErr;
extern sint16 Pitch_nSensFrontRFilterOk;
extern sint16 Pitch_nSensFrontRFilterErr;

extern sint16 Pitch_nSensRearRHyst;
extern sint16 Pitch_nSensRearRGrad;
extern sint16 Pitch_nSensRearRFilterPreOk;
extern sint16 Pitch_nSensRearRFilterPreErr;
extern sint16 Pitch_nSensRearRFilterOk;
extern sint16 Pitch_nSensRearRFilterErr;

extern uint8  Pitch_biSensFrontRMountingStateOk;
extern uint8  Pitch_biSensFrontRMountingStateErr;
extern uint8  Pitch_biSensRearRMountingStateOk;
extern uint8  Pitch_biSensRearRMountingStateErr;

extern sint16 Pitch_nSensFrontRInit;
extern sint16 Pitch_nSensRearRInit;

extern tNvmPara_CodingArea* Pitch_pCodingArea;

extern tsPitchErrCnt    sPitch_ErrCnt;
extern uint8            ucPitch_ErrCntVccxLoRR;
extern uint8            ucPitch_ErrCntVccxLoFR;
extern uint8            ucPitch_ErrCntVccxHiRR;
extern uint8            ucPitch_ErrCntVccxHiFR;
extern boolean          boPitch_CodingValidity;
extern tsDisplacement   sPitch_DispSens;
extern TIMER            Pitch_SensPlau_CheckSensState_us;

extern volatile tSensorPlausibility1Struct SensorPlausData;
extern  tePitchSensorState Pitch_ePitchSensorFailure;
boolean boDispValCheck[CFG_CntSens] = { FALSE, FALSE };


//=============================================================================
// Module function declarations
//=============================================================================

//*  ---------  Pitch.c  -----------*/
extern void             Pitch_SetLocal_DisplacementSens(tsDisplacement sDispSens);
extern void             Pitch_GetLocal_DisplacementSens(tsDisplacement* psDispSens);
extern tucPitchSigQty   Pitch_SigWorst(CONST_AL tucPitchSigQty ucQty1, CONST_AL tucPitchSigQty ucQty2);
extern tucPitchSigQty   Pitch_ErrCntInc(uint8* CONST_AL pucErrCnt, CONST_AL Dem_EventListId_EnumType teErrId);
extern sint16           Pitch_DispCalc(CONST_AL sint16 nSlope, tFiltIir_s* CONST_AL pFilter, CONST_AL sint32 lInput);
extern sint16           Pitch_AngleCalc(CONST_AL sint16 nFrnt, CONST_AL sint16 nRear);
extern tucPitchSigQty   Pitch_CheckSensSupply(void);
extern tucPitchSigQty   Pitch_CheckSensorState(CONST_AL uint32 ulIx);
extern void             Pitch_DispMeasurement(void);
extern void             Pitch_PitchMeasurement(void);
extern void             Pitch_Init(void);
extern tucPitchSigQty   Pitch_ErrCntDec(uint8* CONST_AL pucErrCnt, CONST_AL Dem_EventListId_EnumType teErrId);
extern void             Pitch_SetNvmFlag(void);
extern void             Pitch_ErrPassed(void);
extern void             Pitch_Cycle0(void);

//*  ---------  Pitch_RteAccess.c  -----------*/

// getter functions
extern void Pitch_RteAccess_Get_VehicleSpeed(tsPitch_VehicleSpeed* psData);
extern void Pitch_RteAccess_Get_VehNetState(tsPitch_VehNetState* psData);
extern void Pitch_RteAccess_Get_GetSens_Raw(uint16* punCntSens);
extern void Pitch_RteAccess_Get_GetSens_Balanced(sint32* pslCntSens);
extern void Pitch_RteAccess_Get_VCCX1Voltage(uint16* punVccx1);
extern void Pitch_RteAccess_Get_CodingPara(tsPitch_CodingParam* psCodingParam);
extern void Pitch_RteAccess_Get_GetAdlPhase(tePitch_LvlPhase* psData);
extern void Pitch_RteAccess_Get_GetAslPhase(tePitch_LvlPhase* psData);

// setter functions
extern void                 Pitch_RteAccess_Set_Angle(tsPitch* psPitch);
extern void                 Pitch_RteAccess_Set_SensorFailureState(tePitchSensorState* pePitch);
extern  boolean             Pitch_ParaFct0(tParaFct0_Cmd eCmd, tNvmPara_CodingArea* CONST_AL pData);
extern  boolean             Pitch_CodingDataValidation(void);
extern tePitch_PlauSigState Pitch_CheckVehSpeedData(void);
extern tePitch_PlauSigState Pitch_CheckSensValue(void);

//*  ---------  Pitch_SensPlau.c  -----------*/
extern void                 Pitch_AdjustmentCheckPlausibility(void);
extern void                 Pitch_FailureCheckPlausibility(void);
extern void                 Pitch_CheckSensMountingInit(void);
extern void                 Pitch_CheckSensMounting(void);
extern void                 Pitch_CheckSensMountingState(void);
extern void                 RateLimiterPwmSens(sint16* pRateLimiter, sint16 RateUp, sint16 RateDown, sint16  Value);
extern void                 Order1FilterPwmSens(ORDER1_Filter* const pFilter, const sint16 nValue, const uint16 unBeta);
extern sint16               Order1FilterValuePwmSens(const ORDER1_Filter* const pFilter);
extern void                 Order1FilterInitPwmSens(ORDER1_Filter* const pFilter, const sint16 nValue);

//*  ---------  ctaaPitch.c  -----------*/
void riPitch_Init(void);
void rpPitch_Cycle0(void);


//=============================================================================
// Module function parameter stubs
//=============================================================================

tsDisplacement  Pitch_SetLocal_DisplacementSens_Param1;
tsDisplacement  Pitch_GetLocal_DisplacementSens_Param1;


//*  ---------  Pitch_RteAccess.c  -----------*/

tsPitch_VehicleSpeed      Pitch_RteAccess_Get_VehicleSpeed_Param1;
tsRte_SysMon_VehicleSpeed Pitch_RteAccess_Get_VehicleSpeed_Param2;
tsPitch_VehNetState       Pitch_RteAccess_Get_VehNetState_Param1;
uint16                    Pitch_RteAccess_Get_GetSens_Raw_Param1;
tsRte_SensorBalance* Pitch_RteAccess_Get_GetSens_Balanced_Param1;
tiu16Voltage_mV           Pitch_RteAccess_Get_VCCX1Voltage_Param1;
tsPitch_CodingParam       Pitch_RteAccess_Get_CodingPara_Param1;
tePitch_LvlPhase          Pitch_RteAccess_Get_GetAdlPhase_Param1;
tePitch_LvlPhase          Pitch_RteAccess_Get_GetAslPhase_Param1;
tsPitch                   Pitch_RteAccess_Set_Angle_Param1;
tePitchSensorState        Pitch_RteAccess_Set_SensorFailureState_Param1;
tParaFct0_Cmd             Pitch_ParaFct0_Param1;
tNvmPara_CodingArea* Pitch_ParaFct0_Param2;
tsPitch_CodingParam       Pitch_CodingDataValidation_Param1;
tsPitch_VehicleSpeed      Pitch_CheckVehSpeedData_Param1;
tePitch_PlauSigState      Pitch_CheckVehSpeedData_Param2;
tePitch_PlauSigState      Pitch_CheckSensValue_Param1;


/**************** Pitch_SensPlau.c  *********/

tePitch_PlauSigState      Pitch_FailureCheckPlausibility_Param3;
tePitch_PlauSigState      Pitch_FailureCheckPlausibility_Param4;
tePitch_PlauSigState      Pitch_FailureCheckPlausibility_Param5;
tsPitch_VehNetState       Pitch_FailureCheckPlausibility_Param1 = { 0 };
tsPitch_VehNetState       Pitch_FailureCheckPlausibility_Param2 = { 0 };
tucPitchSigQty            Pitch_SigWorst_Param1;
tucPitchSigQty            Pitch_SigWorst_Param2;
tucPitchSigQty            Pitch_SigWorst_Param3;
uint8                     Pitch_ErrCntInc_Param1;
Dem_EventListId_EnumType  Pitch_ErrCntInc_Param2;
tucPitchSigQty            Pitch_ErrCntInc_Param3;
uint8                     Pitch_ErrCntDec_Param1;
Dem_EventListId_EnumType  Pitch_ErrCntDec_Param2;
tucPitchSigQty            Pitch_ErrCntDec_Param3;
uint32                    Pitch_CheckSensorState_Param1;
Std_ReturnType            Cod_Pitch_SensMin_ReturnVal;
boolean                   boSensValid;
uint16                    Pitch_CheckSensorState_unSensMin;
uint16                    Pitch_CheckSensorState_unSensMax;
Std_ReturnType            Pitch_CheckSensorState_RetVal;

sint16            Pitch_AngleCalc_Param1;
sint16            Pitch_AngleCalc_Param2;

sint16* RateLimiterPwmSens_Param1_Data;
sint16            RateLimiterPwmSens_Param2_Data;
sint16            RateLimiterPwmSens_Param3_Data;
sint16            RateLimiterPwmSens_Param4_Data;

sint16            Pitch_DispCal_Param1;
tFiltIir_s        Pitch_DispCal_Param2;
sint32            Pitch_DispCal_Param3;
sint16            Pitch_DispCal_returnVal;

UtilMath_FastIir_s_Track_Param1;
UtilMath_FastIir_s_Track_Param2;
UtilMath_FastIir_s_Track_Param3;

//=============================================================================
// Module function return value stubs
//=============================================================================

Std_ReturnType  Pitch_RteAccess_Get_VehicleSpeed_RetVal;
Std_ReturnType  Pitch_RteAccess_Get_VehNetState_RetuVal;
Std_ReturnType  Pitch_RteAccess_Get_GetSens_Balanced_RetVal;
Std_ReturnType  Pitch_RteAccess_Get_VCCX1Voltage_RetVal;
Std_ReturnType  Pitch_RteAccess_Get_CodingPara_RetVal;
Std_ReturnType  Pitch_RteAccess_Get_GetAdlPhase_RetVal;
Std_ReturnType  Pitch_RteAccess_Set_Angle_RetVal;
Std_ReturnType  Pitch_RteAccess_Set_SensorFailureState_RetVal;
Std_ReturnType  Pitch_ParaFct0_RetVal;
Std_ReturnType  Pitch_CodingDataValidation_RetVal;
Std_ReturnType  Pitch_CheckVehSpeedData_RetVal;
Std_ReturnType  Pitch_CheckSensValue_RetVal;
Std_ReturnType  Pitch_SigWorst_RetVal;
tucPitchSigQty  Pitch_CheckSensSupply_RetVal;
sint16          Pitch_AngleCalc_RetVal;


//=============================================================================
// Module function Hit Count 
//=============================================================================

uint8 Pitch_CheckVehSpeedData_HitCount;
uint8 Pitch_CheckSensValue_HitCount;
uint8 Pitch_RteAccess_Get_VehicleSpeed_HitCount;
uint8 Order1FilterInitPwmSens_HitCount;
uint8 Order1FilterValuePwmSens_HitCount;
uint8 Pitch_CheckSensMountingState_HitCount;
uint8 riPitch_Init_HitCount;
uint8 Pitch_CheckSensMountingInit_HitCount;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

//boolean                 boDispValCheck;
boolean                 boBhsValCheck;

boolean                 boSensPlauCheck = FALSE;


#endif // TEST_2023_08_25_H_
