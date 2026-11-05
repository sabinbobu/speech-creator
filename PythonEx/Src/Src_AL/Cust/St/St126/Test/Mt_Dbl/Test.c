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
/// \file  Test.c
///
/// \brief Module test of Dbl
///
//----------------`-------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include <ALUnitTest_UserInterface.h>
#include <UtilMath.h>
#include <UtilDebounce.h>
#include <Swc/CodM/CodM_Para.h>
#include <Swc/CodM/CodM_Types.h>
#include <Dbl_Types.h>
#include <RteCommonTypes.h>
#include <DblData.h>
#include <DblcSm.h>

//=============================================================================
// Typedef
//=============================================================================
/* needed due to inclusion of Err in Fee -> generates redefinition of mounted side*/
typedef  enum Fee_State
{
  FEE_STATE_NOT_INIT = 0u,
  FEE_STATE_IDLE = 1u,
  FEE_STATE_WRITE = 2u,
  FEE_STATE_READ = 4u,
  FEE_STATE_READ_ALL = 5u,
  FEE_STATE_FORMAT1 = 6u,
  FEE_STATE_FORMAT2 = 7u,
  FEE_STATE_ERROR = 8u
}tieFeeState;

typedef enum
{
  MEMIF_JOB_OK = 0,
  MEMIF_JOB_FAILED,
  MEMIF_JOB_PENDING,
  MEMIF_JOB_CANCELLED,
  MEMIF_BLOCK_INCONSISTENT,
  MEMIF_BLOCK_INVALID
} MemIf_JobResultType;

typedef struct
{
  //input
  boolean boReq_Input;
  TIMER   ulTimeMs_Input;
  //internal
  TIMER   ulCommandStart;
  boolean boStartStopTimer;
  boolean boTimeOut;
}tsDblCrState_TimerCfg;


//=============================================================================
// Defines
//=============================================================================
#define DBLCRSTATE_NUMBER_OF_TIMERS                                    4u
#define DBL_CURVATURE_INVALID_VALUE                                    0x7FFF
#define DBL_STEERING_WHEEL_INIT_IN_PROGRESS_VALUE                     -28673 // this value is used for init in progress value of steering wheel
#define DBLCRSTATE_SIG_QTY_INVALID_TIMER_SEL                           0u
#define DBLCRCALC_DEGREE2RADIAN(x)                                    ((x) * (3140 / 180)) // convert degree to radian with 10000 resolution
#define DBLCRCALC_POSITIVE_CURVATURE_LIMIT                             25000
#define DBLCRCALC_NEGATIVE_CURVATURE_LIMIT                            -25000
#define DBLCRCALC_NULL_VALUE                                           0
// quadrant degree x 10 delimeters
#define DBLCRCALC_Q1_MIN_LIMIT                              0u //quadrant 1 min limit
#define DBLCRCALC_Q1_MAX_LIMIT                            900u //quadrant 1 max limit
#define DBLCRCALC_Q2_MAX_LIMIT                           1800u //quadrant 2 max limit
#define DBLCRCALC_Q3_MAX_LIMIT                           2700u //quadrant 3 max limit
#define DBLCRCALC_Q4_MAX_LIMIT                           3600u //quadrant 4 max limit
// angle sign
#define DBLCRCALC_POSITIVE_ANGLE_SIGN                        1
#define DBLCRCALC_NEGATIVE_ANGLE_SIGN                       -1
// parameters for weghting factor algorithm
#define DBLCRCALC_CFG_VVEHICLE_WF_1                          0    //[m/s]
#define DBLCRCALC_CFG_VVEHICLE_WF_2                          0  //[0.01m/s]
#define DBLCRCALC_CFG_VVEHICLE_WF_3                          DBLCRCALC_CFG_VVEHICLE_WF_2
#define DBLCRCALC_CFG_VVEHICLE_WF_4                          0  //[0.01m/s]
#define DBLCRCALC_CFG_WF_YAW_RATE_1                          0u
#define DBLCRCALC_CFG_WF_YAW_RATE_2                          0
#define DBLCRCALC_CFG_WF_YAW_RATE_3                          DBLCRCALC_CFG_WF_YAW_RATE_2
#define DBLCRCALC_CFG_WF_YAW_RATE_4                          0
#define DBLCRCALC_CFG_WF_YAW_RATE_MAX                        100
#define DBLCRCALC_CFG_WF_1ST_POINT                           -0
#define DBLCRCALC_CFG_WF_2ND_POINT                            1
#define DBLCRCALC_RESOLUTION_FACTOR_100                       100
#define DBLCRCALC_RESOLUTION_FACTOR_10                        10
#define DBLCRCALC_VELOCITY_FACTOR                             1000 / 3600  // [km / h to m / s]
#define DBLCRCALC_CURVATURE_FACTOR                            1000000000
#define DBLCRCALC_WF_CCALCULATION_FIRST_SLOPE                  0
#define DBLCRCALC_WF_CCALCULATION_SECOND_SLOPE                 1
#define DBL_NEGATIVE_FACTOR                                  -1
#define DBL_POSITIVE_CURVATURE_LIMIT                          25000
#define DBL_NEGATIVE_CURVATURE_LIMIT                         -25000
#define DBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION(x)               (((x) * 4) / 10) // factor applied on curvature
#define DBL_CURVATURE_INVALID_VALUE                           0x7FFF // this value is used for init in progress value AND for invalid value-may be splitted in next releases
#define DBL_NUMBER_OF_TIMERS                                  2
//=============================================================================
// Global variable stubs ( registers, global variables from other modules which are referenced in the module )
//=============================================================================
tNvmPara_CodingArea Dbl_sCodingParam_Dummy;
//=============================================================================
// Global variables (of the module itself)
//=============================================================================
extern ORDER1_Filter32         Cl_Filter_Speed;
extern tsRteCodingParameters   Dbl_sCodingParam;
extern boolean                 Dbl_boIsCodingValid;
extern tUtilDebounceControl    Dbl_HighSpeedTimer;
extern tuDblDriveSituation     Dbl_sDriveSituation;
extern tUtilDebounceControl    Dbl_sSwivelBckTimer;
extern sint32                  Dbl_slnHlaOut;
extern tDblcSignal             Dbl_sSignal;
extern tDbl_State              Dbl_sState;
extern TIMER                   Dbl_ulTimerSigQty_Inv;
extern TIMER                   Dbl_ulTimerSigQty_Unav;
extern boolean                 Dbl_boCurvature_SigQty_ERR;
extern boolean                 Dbl_boPowertrainActive;
extern boolean                 Dbl_boSwivelingFunctionalFault_LR;
extern teRte_MountingSide      Dbl_eMountingSide;
extern teDbl_eMainMode         Dbl_eMainMode;
extern teDbl_eSubMode          Dbl_eSubMode;
extern boolean                 Dbl_boErrorFromOtherHL;
extern boolean                 Dbl_boHB;
extern sint16                  Dbl_snSwivelAngleLeft;
extern sint16                  Dbl_snSwivelAngleRight;
extern tsRte_Dbl_SwivellingOut Dbl_sMsgOut;
extern sint32                  Dbl_slanHLAFilter[DBLC_HLAFILTERSIZE];
extern teTraffic               Dbl_eTrafficSide;
extern tsDbl_StateMType        Dbl_atStateMachine[4];
extern boolean                 Dbl_boDYN_BENDING_BEAM_FAULT;
extern boolean                 Dbl_eErrorStatus;
extern boolean                 Dbl_boCurvature_UNAV;
extern boolean                 Dbl_boL_Internal_Failure;
extern boolean                 Dbl_boR_Internal_Failure;
extern boolean                 Dbl_boEtatMar;
extern tsDblCrState_TimerCfg   DblCrState_sTimerCfg[DBLCRSTATE_NUMBER_OF_TIMERS];
extern uint16                  DblCrState_unEgoVehicleMotionConfirmation;
extern boolean                 DblCrState_boSigQty_TimeoutFlag;
extern uint16                  DblCrCalc_unSteering_Ratio;
extern uint16                  DblCrCalc_unCrcVehicleWheelbase;
extern tsWfTable               DblCrCalc_asCrv_WfTable[];
extern tsDbl_VehPathCurvatureData Dbl_sCurvatureData;
extern boolean                 Dbl_boFailureTimerFlag_Inv;
extern boolean                 Dbl_boFailureTimerFlag_Unav;
extern tsDbl_TimerCfg          Dbl_sTimerCfg[DBL_NUMBER_OF_TIMERS];
extern tsDbl_FilteredCalculatedCurvatureData         Dbl_sCrCalcFilterData;
extern uint16                                        Dbl_unEgoMotionTime;
//=============================================================================
// Function declarations (of the module itself)
//=============================================================================
extern sint32                _ClPolySolverCalcMaxStartSlope(sint32 nCrev);
extern sint32                _ClPolySolverCalcStartSlope(sint32 nV, sint32 nEndC, teDir nDir, sint32 nC);
extern sint32                UtilMath_LinearInterpolateP32(sint32 lx, sint32 lx1, sint32 lx2, sint32 ly1, sint32 ly2);
extern sint16                UtilLinearInterpolatePClamp32(sint16 x, sint16 x1, sint16 x2, sint16 y1, sint16 y2);
extern sint32                UtilMath_LinearInterpolateP32(sint32 lx, sint32 lx1, sint32 lx2, sint32 ly1, sint32 ly2);
extern sint32                _ClPolySolverCalcEndSlope(sint32 nC, teDir nDir);
extern sint32                _ClPolySolverCalcEndC(sint32 nV, teDir nDir);
extern sint32                ClPolySolver(sint32 nC, sint32 nVin);
extern void                  ClResetSpeedFilter(void);
extern sint32                ClHlaIdlePosition(sint32 nHla, sint32 nVin);
extern sint32                ClHlaAttenuationFactor(sint32 nC, sint32 nVin);
extern sint32                ClPoly3(sint32 x, sint32 x1, sint32 y1, sint32 m0, sint32 m1);
extern void                  LrRelation2(sint32 nHla, sint32* pnAngleLeft, sint32* pnAngleRight);
extern void                  DblcSm_ParaFct0(void);
extern void                  DblcSm_Init(void);
extern sint32                DblcCl(sint32 nC, sint32 nCG, sint32 nV, uint8 ucStreetClass);
extern sint32                DblcOutputControl(sint32 nHla, sint32 nReqPercentage);
extern void                  Dbl_ConstHighSpeed_Detect(sint32 snSpeed);
extern void                  Dbl_SetSteerbackDetection(boolean boState);
extern sint16                Dbl_Mrad2MDeg(sint16 nSwvMrad);
extern tUtilDebounceControl* Dbl_GetTimer(void);
extern sint32                ClIdleSignal(sint32 nC, sint32 nIdleRange);
extern sint32                Time2Inc(uint32 unTime);
extern sint32                Time2Step(uint32 unTime, sint32 nTarget);
extern sint32                ClIdleRange(sint32 nV, sint32 nC, sint32 nCg, uint8 ucSc);
extern sint16                Dblc_Convert_Deg_mRad(sint16 nDeg);
extern sint16                Dblc_Convert_Deg_mRadHr(sint16 nDeg);
extern void                  DblcCalculateSwiveling(sint32 nC, sint32 nCG, uint8 ucStreetClass);
extern sint32                DblcLimitSwiveling(sint32 nC, sint32 nCG, sint32 nHla, sint32 nHlaOld, uint8 ucStreetClass);
extern void                  Dbl_RteAccess_WriteSwimRate(tsDbl_SwiRateLimMsg sDblLimits);
extern void                  Dbl_RteAccess_WriteDriveSituation(uint8 ucDblDriveSit);
extern teTraffic             Dbl_RteAccess_ReadDblTrafficSide(void);
extern void                  Dbl_RteAccess_Read_EcuSide(teDbl_MountingSide* eEcuSide);
extern sint16                Dbl_RteAccess_ReadDblOutput(void);
extern void                  Dbl_RteAccess_WriteDblOutput(tsDbl_SwivellingOut nAngle, uint8 ucState, teDbl_eSubMode eMode);
extern void                  Dbl_RteAccess_WriteDblSysMonTx_FullStatus(boolean boFailureStatus);
extern void                  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus(teDbl_MountingSide eSide, boolean boStatus);
extern uint8                 Dbl_RteAccess_ReadReverseGearStatus(void);
extern uint8                 Dbl_RteAccess_ReadVehicleModeConfig(void);
extern teDbl_EtatPrincipSEV  Dbl_RteAccess_ReadVESMainState(void);
extern uint8                 Dbl_RteAccess_ReadVehicleElectricState(void);
extern void                  Dbl_RteAccess_ReadCurvature(sint32* nCurvature);
extern uint32                Dbl_RteAccess_ReadSpeed(void);
extern uint8                 Dbl_RteAccess_ReadDynBendingBeamFaultR(void);
extern uint8                 Dbl_RteAccess_ReadDynBendingBeamFaultL(void);
extern uint8                 Dbl_RteAccess_ReadSteeringType(void);
extern boolean               Dbl_RteAccess_ReadEnvCondition(void);
extern tsDbl_SwiRateLimMsg   Dbl_RteAccess_ReadSwimRate(void);
extern uint8                 Dbl_RteAccess_ReadDblCmd(void);
extern uint8                 Dbl_RteAccess_ReadGfhbCmd(void);
extern uint8                 Dbl_RteAccess_ReadHbCmd(void);
extern uint8                 Dbl_RteAccess_ReadFlashBeamCmd(void);
extern void                  Dbl_Init(void);
extern void                  Dbl_Cycle(void);
extern void                  riDbl_Init(void);
extern void                  rpDbl_Cycle(void);
extern sint32                CalcIdleRange(sint32 nV, teDir Dir, uint8 ucSc);
extern void                  Dbl_Curvature_SigQty_INV(void);
extern boolean               Dbl_RetPowerTrainActive(void);
extern boolean               Dbl_ReadFault(teDbl_MountingSide ucSide);
extern void                  Dbl_DefOfFailure(void);
extern boolean               Dbl_RetDigitalSwivelingFunctionalFault_LR(void);
extern void                  Dbl_DetectSide(void);
extern teDbl_MountingSide    Dbl_GetSide(void);
extern teTraffic             Dbl_GetTrafficSide(void);
extern void                  Dbl_DetectMode(void);
extern void                  Dbl_UseMode(void);
extern void                  Dbl_UseSubMode(void);
extern void                  Dbl_ModeAssembly(void);
extern void                  Dbl_ModeCustomer(void);
extern boolean               Dbl_GetHBStatus(void);
extern boolean               Dbl_Transition_Assembly_To_Frozen(void);
extern boolean               Dbl_Transition_Customer_To_Unavailable(void);
extern boolean               Dbl_Transition_Customer_To_Available(void);
extern boolean               Dbl_Transition_Fail_To_Init(void);
extern boolean               Dbl_Transition_Init_To_Nominal(void);
extern boolean               Dbl_Transition_Fail_To_Nominal(void);
extern boolean               Dbl_Transition_Adj_To_Nominal(void);
extern boolean               Dbl_Transition_Nominal_To_Adj(void);
extern boolean               Dbl_Transition_Init_To_Adj(void);
extern boolean               Dbl_Transition_Fail_To_Adj(void);
extern boolean               Dbl_Transition_Init_To_Fail(void);
extern boolean               Dbl_Transition_Nominal_To_Fail(void);
extern boolean               Dbl_Transition_Adj_To_Fail(void);
extern boolean               Dbl_Read_PhaseVie(void);
extern void                  Dbl_ReadEnvironmentSignals(void);
extern void                  Dbl_Call_StateNormal(void);
extern void                  Dbl_Call_StateOff(void);
extern void                  Dbl_Call_StateHold(void);
extern void                  Dbl_StateMachine_StateInit(void);
extern void                  Dbl_StateMachine_StateNominal(void);
extern void                  Dbl_StateMachine_StateFail(void);
extern void                  Dbl_StateMachine_StateAdj(void);
extern void                  Dbl_SubModeFrozen(void);
extern void                  Dbl_SubModeUnavailable(void);
extern void                  Dbl_HbActive(void);
extern void                  Dbl_Write_OutputValues(void);
extern void                  Dbl_StMch(void);
extern void                  Dbl_ReadInputSignals();
extern boolean               Dbl_Transition_Adj_To_Init(void);
extern boolean               Dbl_Transition_Nominal_To_Init(void);
extern void                  Dbl_Call_StateFailure(void);
extern sint32                Dbl_SmoothTransition(sint32 slParam1, sint32 slParam2);
extern void                  Dbl_Call_StateHold(void);
extern void                  DblCrvCalc_Get_CurvatureCodingParameters(void);
extern void                  DblCrvCalc_Get_WfCodingParameters(void);
extern tsAngleData           DblCrvCalc_ProcessAngle(sint16 snAngle);
extern uint32                DblCrvCalc_getLinearInterpolatedValue(uint32 ulPointX, uint32 ulPointX0, uint32 ulPointX1, uint32 ulPointY0, uint32 ulPointY1);
extern uint8                 DblCrvCalc_WeightingFactorCalculation(uint16 nVehicleSpeed);
extern uint8                 DblCrvCalc_FindWfZone(uint32 ulVehicleSpeed);
extern sint32                DblCrvCalc_GetSin(sint16 snAngle);
extern sint32                DblCrvCalc_getCurvatureValue(void);
extern void                  DblCrState_Init(void);
extern sint32                DblCrState_State_Machine(void);
extern boolean               DblCrState_Transition_CalculationPhase_Nominal_to_Invalid(void);
extern boolean               DblCrState_Transition_CalculationPhase_Invalid_to_Nominal(void);
extern boolean               DblCrState_Transition_CalculationMode_Available_to_Unavailable(void);
extern boolean               DblCrState_Transition_CalculationMode_Unavailable_to_Available(void);
extern boolean               DblCrState_PowerTrain_State(void);
extern boolean               DblCrState_HandleDelayStatus(tsDblCrState_TimerCfg *psTimersCfg, CONST_AL uint8 ucTimerSel);
extern boolean               DblCrState_Timeout(CONST_AL boolean boReqInput, CONST_AL TIMER ulTimeMs, CONST_AL uint8 ucTiTimerSel);
extern teDbl_SigQty          Dbl_RteAccess_ReadEtatReseauElec(void);
extern tsDbl_VehicleSpeed                 Dbl_RteAccess_ReadVehicleSpeed(void);
extern tsDbl_SteeringWheelAngle           Dbl_RteAccess_ReadSteeringWheelAngle(void);
extern tsDbl_YawSpeed                     Dbl_RteAccess_ReadYawSpeed(void);
extern boolean                            Dbl_HandleDelayStatus(tsDbl_TimerCfg *psTimersCfg, CONST_AL uint8 ucTimerSel);
extern boolean                            Dbl_Timeout(CONST_AL boolean boReqInput, CONST_AL TIMER ulTimeMs, CONST_AL uint8 ucTiTimerSel);
extern sint32                             Dbl_Get_Filtered_Calculated_Curvature_Value(sint32 lCurvatureCalculated);
extern sint32                             Dbl_FilterIIR_Input(sint32 nNewSample);
extern void                               Dbl_Get_Calculated_Curvature_Coding_Parameters(void);
STATIC_AL teRte_SigQty                    Dbl_Curvature_SigQty(void);

//=============================================================================
// Function parameter stubs (of the module ifself)
//=============================================================================
sint32                       _ClPolySolverCalcMaxStartSlope_Param1;
sint32                       _ClPolySolverCalcStartSlope_Param1;
sint32                       _ClPolySolverCalcStartSlope_Param2;
teDir                         _ClPolySolverCalcStartSlope_Param3;
sint32                       _ClPolySolverCalcStartSlope_Param4;
sint32                       _ClPolySolverCalcEndSlope_Param1;
teDir                         _ClPolySolverCalcEndSlope_Param2;
sint32                       _ClPolySolverCalcEndC_Param1;
teDir                         _ClPolySolverCalcEndC_Param2;
sint32                       ClPolySolver_Param1;
sint32                       ClPolySolver_Param2;
sint32                       ClHlaIdlePosition_Param1;
sint32                       ClHlaIdlePosition_Param2;
sint16                       UtilLinearInterpolatePClamp32_Param1;
sint16                       UtilLinearInterpolatePClamp32_Param2;
sint16                       UtilLinearInterpolatePClamp32_Param3;
sint16                       UtilLinearInterpolatePClamp32_Param4;
sint16                       UtilLinearInterpolatePClamp32_Param5;
sint32                       UtilMath_LinearInterpolateP32_Param1;
sint32                       UtilMath_LinearInterpolateP32_Param2;
sint32                       UtilMath_LinearInterpolateP32_Param3;
sint32                       UtilMath_LinearInterpolateP32_Param4;
sint32                       UtilMath_LinearInterpolateP32_Param5;
sint32                       ClHlaAttenuationFactor_Param1;
sint32                       ClHlaAttenuationFactor_Param2;
sint32                       ClPoly3_Param1;
sint32                       ClPoly3_Param2;
sint32                       ClPoly3_Param3;
sint32                       ClPoly3_Param4;
sint32                       ClPoly3_Param5;
sint32                       LrRelation2_Param1;
sint32*                      LrRelation2_Param2;
sint32*                      LrRelation2_Param3;
sint32                       DblcCl_Param1;
sint32                       DblcCl_Param2;
sint32                       DblcCl_Param3;
uint8                        DblcCl_Param4;
sint32                       DblcOutputControl_Param1;
sint32                       DblcOutputControl_Param2;
sint32                       Dbl_ConstHighSpeed_Detect_Param1;
boolean                      Dbl_SetSteerbackDetection_Param1;
sint16                       Dbl_Mrad2MDeg_Param1;
tAction                      StateNormal_Param1;
sint32                       ClIdleSignal_Param1;
sint32                       ClIdleSignal_Param2;
uint32                       Time2Inc_Param1;
uint32                       Time2Step_Param1;
sint32                       Time2Step_Param2;
sint32                       ClIdleRange_Param1;
sint32                       ClIdleRange_Param2;
sint32                       ClIdleRange_Param3;
uint8                        ClIdleRange_Param4;
sint16                       Dblc_Convert_Deg_mRad_Param1;
sint16                       Dblc_Convert_Deg_mRadHr_Param1;
sint32                       DblcCalculateSwiveling_Param1;
sint32                       DblcCalculateSwiveling_Param2;
uint8                        DblcCalculateSwiveling_Param3;
sint32                       DblcLimitSwiveling_Param1;
sint32                       DblcLimitSwiveling_Param2;
sint32                       DblcLimitSwiveling_Param3;
sint32                       DblcLimitSwiveling_Param4;
uint8                        DblcLimitSwiveling_Param5;
tsDbl_SwiRateLimMsg          Dbl_RteAccess_WriteSwimRate_Param1;
uint8                        Dbl_RteAccess_WriteDriveSituation_Param1;
tsDbl_SwivellingOut          Dbl_RteAccess_WriteDblOutput_Param1;
uint8                        Dbl_RteAccess_WriteDblOutput_Param2;
teDbl_eSubMode               Dbl_RteAccess_WriteDblOutput_Param3;
boolean                      Dbl_RteAccess_WriteDblSysMonTx_FullStatus_Param1;
teDbl_MountingSide           Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param1;
boolean                      Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param2;
teDbl_MountingSide           Dbl_RteAccess_Read_EcuSide_Param1;
sint32                       Dbl_RteAccess_ReadCurvature_Param1;
sint32                       CalcIdleRange_Param1;
teDir                        CalcIdleRange_Param2;
uint8                        CalcIdleRange_Param3;
teDbl_MountingSide           Dbl_ReadFault_Param1;
sint32                       Dbl_SmoothTransition_Param1;
sint32                       Dbl_SmoothTransition_Param2;
uint32                       DblCrvCalc_getLinearInterpolatedValue_Param1;
uint32                       DblCrvCalc_getLinearInterpolatedValue_Param2;
uint32                       DblCrvCalc_getLinearInterpolatedValue_Param3;
uint32                       DblCrvCalc_getLinearInterpolatedValue_Param4;
uint32                       DblCrvCalc_getLinearInterpolatedValue_Param5;
uint16                       DblCrvCalc_WeightingFactorCalculation_Param1;
uint32                       DblCrvCalc_FindWfZone_Param1;
sint16                       DblCrvCalc_GetSin_Param1;
tsDblCrState_TimerCfg        DblCrState_HandleDelayStatus_Param1[10];
uint8                        DblCrState_HandleDelayStatus_Param2;
boolean                      DblCrState_Timeout_Param1;
TIMER                        DblCrState_Timeout_Param2;
uint8                        DblCrState_Timeout_Param3;
boolean                      Dbl_Timeout_Param1;
TIMER                        Dbl_Timeout_Param2;
uint8                        Dbl_Timeout_Param3;
uint8                        Dbl_HandleDelayStatus_Param2;
tsDbl_TimerCfg               Dbl_HandleDelayStatus_Param1[10];
sint32                       Dbl_Get_Filtered_Calculated_Curvature_Value_Param1;
sint32                       Dbl_FilterIIR_Input_Param1;

//=============================================================================
// Function return value stubs (of the module ifself)
//=============================================================================
sint32                       _ClPolySolverCalcMaxStartSlope_RetVal;
sint32                       _ClPolySolverCalcStartSlope_RetVal;
sint32                       _ClPolySolverCalcEndSlope_RetVal;
sint32                       _ClPolySolverCalcEndC_RetVal;
sint32                       ClPolySolver_RetVal;
sint32                       ClHlaIdlePosition_RetVal;
sint32                       ClHlaAttenuationFactor_RetVal;
sint32                       ClPoly3_RetVal;
sint32                       DblcCl_RetVal;
sint16                       UtilLinearInterpolatePClamp32_RetVal;
sint32                       UtilMath_LinearInterpolateP32_RetVal;
sint32                       DblcOutputControl_RetVal;
sint16                       Dbl_Mrad2MDeg_RetVal;
tUtilDebounceControl*        Dbl_GetTimer_RetVal;
sint32                       ClIdleSignal_RetVal;
sint32                       Time2Inc_RetVal;
sint32                       Time2Step_RetVal;
sint32                       ClIdleRange_RetVal;
sint16                       Dblc_Convert_Deg_mRad_RetVal;
sint16                       Dblc_Convert_Deg_mRadHr_RetVal;
sint32                       DblcLimitSwiveling_RetVal;
teTraffic                    Dbl_RteAccess_ReadDblTrafficSide_RetVal;
sint16                       Dbl_RteAccess_ReadDblOutput_RetVal;
uint8                        Dbl_RteAccess_ReadReverseGearStatus_RetVal;
uint8                        Dbl_RteAccess_ReadVehicleModeConfig_RetVal;
teDbl_EtatPrincipSEV         Dbl_RteAccess_ReadVESMainState_RetVal;
uint8                        Dbl_RteAccess_ReadVehicleElectricState_RetVal;
uint32                       Dbl_RteAccess_ReadSpeed_RetVal;
uint8                        Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal;
uint8                        Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal;
uint8                        Dbl_RteAccess_ReadSteeringType_RetVal;
boolean                      Dbl_RteAccess_ReadEnvCondition_RetVal;
tsDbl_SwiRateLimMsg          Dbl_RteAccess_ReadSwimRate_RetVal;
uint8                        Dbl_RteAccess_ReadDblCmd_RetVal;
uint8                        Dbl_RteAccess_ReadGfhbCmd_RetVal;
uint8                        Dbl_RteAccess_ReadHbCmd_RetVal;
uint8                        Dbl_RteAccess_ReadFlashBeamCmd_RetVal;
sint32                       CalcIdleRange_RetVal;
teDbl_MountingSide           Dbl_GetSide_RetVal;
teTraffic                    Dbl_GetTrafficSide_RetVal;
boolean                      Dbl_GetHBStatus_RetVal;
boolean                      Dbl_RetPowerTrainActive_RetVal;
boolean                      Dbl_ReadFault_RetVal;
boolean                      Dbl_RetDigitalSwivelingFunctionalFault_LR_RetVal;
boolean                      Dbl_Transition_Assembly_To_Frozen_RetVal;
boolean                      Dbl_Transition_Customer_To_Unavailable_RetVal;
boolean                      Dbl_Transition_Customer_To_Available_RetVal;
boolean                      Dbl_Transition_Fail_To_Init_RetVal;
boolean                      Dbl_Transition_Init_To_Nominal_RetVal;
boolean                      Dbl_Transition_Fail_To_Nominal_RetVal;
boolean                      Dbl_Transition_Adj_To_Nominal_RetVal;
boolean                      Dbl_Transition_Nominal_To_Adj_RetVal;
boolean                      Dbl_Transition_Init_To_Adj_RetVal;
boolean                      Dbl_Transition_Fail_To_Adj_RetVal;
boolean                      Dbl_Transition_Init_To_Fail_RetVal;
boolean                      Dbl_Transition_Nominal_To_Fail_RetVal;
boolean                      Dbl_Transition_Adj_To_Fail_RetVal;
boolean                      Dbl_Transition_Adj_To_Init_RetVal;
boolean                      Dbl_Transition_Nominal_To_Init_RetVal;
boolean                      Dbl_Read_PhaseVie_RetVal;
sint32                       Dbl_SmoothTransition_RetVal;
tsAngleData                  DblCrvCalc_ProcessAngle_RetVal;
uint32                       DblCrvCalc_getLinearInterpolatedValue_RetVal;
uint8                        DblCrvCalc_WeightingFactorCalculation_RetVal;
uint8                        DblCrvCalc_FindWfZone_RetVal;
sint32                       DblCrvCalc_GetSin_RetVal;
sint32                       DblCrvCalc_getCurvatureValue_RetVal;
sint32                       DblCrState_State_Machine_RetVal;
boolean                      DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal;
boolean                      DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal;
boolean                      DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal;
boolean                      DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal;
boolean                      DblCrState_PowerTrain_State_RetVal;
boolean                      DblCrState_HandleDelayStatus_RetVal;
boolean                      DblCrState_Timeout_RetVal;
teDbl_SigQty                 Dbl_RteAccess_ReadEtatReseauElec_RetVal;
tsDbl_VehicleSpeed           Dbl_RteAccess_ReadVehicleSpeed_RetVal;
tsDbl_SteeringWheelAngle     Dbl_RteAccess_ReadSteeringWheelAngle_RetVal;
tsDbl_YawSpeed               Dbl_RteAccess_ReadYawSpeed_RetVal;
boolean                      Dbl_Timeout_RetVal;
boolean                      Dbl_HandleDelayStatus_RetVal;
sint32                       Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal;
sint32                       Dbl_FilterIIR_Input_RetVal;
sint32                       Dbl_Curvature_SigQty_RetVal;
//=============================================================================
// Stub function declarations
//=============================================================================
sint32                       Order1TrackingFilter32(ORDER1_Filter32* pFilter, uint32 unBeta, sint32 nValue, uint32 unDeviation);
sint32                       FirFilter32(sint32 alFirFilter[], sint32 lFilterSize, sint32 lValue);
void                         UtilDebounce(tUtilDebounceControl* const pCtrl, boolean boVal);
void                         Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
sint32                       Order1Filter32(ORDER1_Filter32* pFilter, uint32 unBeta, sint32 nValue);
Std_ReturnType               Rte_Write_AfsDbl_SwiRateLimMsg(const tsRte_SwiRateLimMsg* ppara1);
Std_ReturnType               Rte_Read_AfsDbl_DblDriveSit(tsRte_AfsDblDriveSituation* ppara1);
Std_ReturnType               Rte_Read_CodM_Dbl_Para(tsRteCodingParameters* ppara1);
Std_ReturnType               Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1);
Std_ReturnType               Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1);
Std_ReturnType               Rte_Read_SysMon_Afs_Signals(tsRte_SysMonAfsSignals* ppara1);
Std_ReturnType               Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1);
Std_ReturnType               Rte_Read_Dbl_SwivellingOut(tsRte_DblOut* ppara1);
Std_ReturnType               Rte_Write_Dbl_Mode(const teRte_DblSubMode* ppara1);
Std_ReturnType               Rte_Write_Dbl_SwivellingOut(const tsRte_DblOut* ppara1);
Std_ReturnType               Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType               Rte_Read_AfsDbl_SwiRateLimMsg(tsRte_SwiRateLimMsg* ppara1);
Std_ReturnType               Rte_Read_FctR_AfsDblCmd(tsRte_AfsDblCmd* ppara1);
Std_ReturnType               Rte_Read_SigPrep_VehPathCurvature(tsRte_SigPrep_VehPathCurvature* ppara1);
Std_ReturnType               Rte_Write_AfsDbl_DblDriveSit(const tsRte_AfsDblDriveSituation* ppara1);
void                         UtilDebounceInit(tUtilDebounceControl* const pCtrl, tieDigState eStateInit, TIMER tOnDelay, TIMER tOffDelay);
uint32                       LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
Std_ReturnType               Rte_Read_SigPrepRx_Dbl_RightStatus(tsRte_BendingBeamFault_OtherHL* ppara1);
Std_ReturnType               Rte_Read_SigPrepRx_Dbl_LeftStatus(tsRte_BendingBeamFault_OtherHL* ppara1);
Std_ReturnType               Rte_Read_SigPrep_EnvCondition(tsRte_SigPrep_EnvCondition* ppara1);
Std_ReturnType               Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType               Rte_Write_Dbl_SysMonTx_FullStatus(const tsRte_Hs6_Diag_Drvled_BendingBeamFault* ppara1);
Std_ReturnType               Rte_Write_Dbl_SigPrepTx_LeftStatus(const tsRte_BendingBeamFault_OtherHL* ppara1);
Std_ReturnType               Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType               Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType               Rte_Read_SigPrep_YawSpeed(tsRte_SigPrep_YawSpeed* ppara1);
Std_ReturnType               Rte_Read_SigPrep_SteeringWheelAngle(tsRte_SigPrep_SteeringWheelAngle* ppara1);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
tieFeeState                            Fee_State;
MemIf_JobResultType                    Fee_JobResult;
ORDER1_Filter32                        Order1TrackingFilter32_Param1;
uint32                                 Order1TrackingFilter32_Param2;
sint32                                 Order1TrackingFilter32_Param3;
uint32                                 Order1TrackingFilter32_Param4;
sint32                                 FirFilter32_Param1[DBLC_HLAFILTERSIZE];
sint32                                 FirFilter32_Param2;
sint32                                 FirFilter32_Param3;
tUtilDebounceControl                   UtilDebounce_Param1;
boolean                                UtilDebounce_Param2;
ORDER1_Filter32                        Order1Filter32_Param1;
uint32                                 Order1Filter32_Param2;
sint32                                 Order1Filter32_Param3;
sint16                                 LinEquCalculator_Param1;
tLinEqu                                LinEquCalculator_Param2;
tPoint                                 LinEquSolver_Param1;
tPoint                                 LinEquSolver_Param2;
tLinEqu                                LinEquSolver_Param3;
tsRteCodingParameters                  Rte_Read_CodM_Dbl_Para_Param1;
tsRte_SigPrep_VehPathCurvature         Rte_Read_SigPrep_VehPathCurvature_Param1;
tsRte_SysMon_VehicleSpeed              Rte_Read_SysMon_VehicleSpeed_Param1;
tsRte_SwiRateLimMsg                    Rte_Read_AfsDbl_SwiRateLimMsg_Param1;
tsRte_AfsDblCmd                        Rte_Read_FctR_AfsDblCmd_Param1;
tsRte_SigPrep_VehicleConfigSig         Rte_Read_SigPrep_VehicleConfigSig_Param1;
tsRte_SigPrep_DynamicSigs              Rte_Read_SigPrep_DynamicSigs_Param1;
tsRte_SysMonAfsSignals                 Rte_Read_SysMon_Afs_Signals_Param1;
tsRte_SysMonLgtFctsReq                 Rte_Read_SysMon_StdLgtFcts_Req_Param1;
tsRte_SwiRateLimMsg                    Rte_Write_AfsDbl_SwiRateLimMsg_Param1;
tsRte_AfsDblDriveSituation             Rte_Read_AfsDbl_DblDriveSit_Param1;
tsRte_DblOut                           Rte_Read_Dbl_SwivellingOut_Param1;
teRte_DblSubMode                       Rte_Write_Dbl_Mode_Param1;
tsRte_DblOut                           Rte_Write_Dbl_SwivellingOut_Param1;
tsRte_AfsDblDriveSituation             Rte_Write_AfsDbl_DblDriveSit_Param1;
tUtilDebounceControl                   UtilDebounceInit_Param1;
tieDigState                            UtilDebounceInit_Param2;
TIMER                                  UtilDebounceInit_Param3;
TIMER                                  UtilDebounceInit_Param4;
uint32                                 LPTMR0_GetTimeElapsed_Param1;
tsRte_AfsDblCmd                        Rte_Read_FctR_AfsDblFoggy_Param1;
tsRte_BendingBeamFault_OtherHL         Rte_Read_SigPrepRx_Dbl_RightStatus_Param1;
tsRte_BendingBeamFault_OtherHL         Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1;
tsRte_SigPrep_EnvCondition             Rte_Read_SigPrep_EnvCondition_Param1;
tsRte_SysMon_VehNetState               Rte_Read_SysMon_VehNetState_Param1;
tsRte_Hs6_Diag_Drvled_BendingBeamFault Rte_Write_Dbl_SysMonTx_FullStatus_Param1;
tsRte_BendingBeamFault_OtherHL         Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1;
teRte_MountingSide                     Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRte_BendingBeamFault_OtherHL         Rte_Write_Dbl_SigPrepTx_RightStatus_Param1;
uint16                                 Dem_SetEventStatus_Param1;
uint8                                  Dem_SetEventStatus_Param2;
tsRte_SysMon_LifePhases                Rte_Read_SysMon_LifePhases_Param1;
tsRte_SigPrep_YawSpeed                 Rte_Read_SigPrep_YawSpeed_Param1;
tsRte_SigPrep_SteeringWheelAngle       Rte_Read_SigPrep_SteeringWheelAngle_Param1;
sint16                                 DblCrvCalc_ProcessAngle_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
uint32                                 LPTMR0_GetTimeElapsed_RetVal;
sint32                                 Order1TrackingFilter32_RetVal;
sint32                                 FirFilter32_RetVal;
sint32                                 Order1Filter32_RetVal;
sint16                                 LinEquCalculator_RetVal;
Std_ReturnType                         Rte_Read_FctR_AfsDblCmd_RetVal;
Std_ReturnType                         Rte_Read_AfsDbl_SwiRateLimMsg_RetVal;
Std_ReturnType                         Rte_Read_CodM_Dbl_Para_RetVal;
Std_ReturnType                         Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType                         Rte_Read_SigPrep_VehPathCurvature_RetVal;
Std_ReturnType                         Rte_Read_SigPrep_VehicleConfigSig_RetVal;
Std_ReturnType                         Rte_Read_SigPrep_DynamicSigs_RetVal;
Std_ReturnType                         Rte_Read_SysMon_Afs_Signals_RetVal;
Std_ReturnType                         Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
Std_ReturnType                         Rte_Read_Dbl_SwivellingOut_RetVal;
Std_ReturnType                         Rte_Write_Dbl_Mode_RetVal;
Std_ReturnType                         Rte_Write_Dbl_SwivellingOut_RetVal;
Std_ReturnType                         Rte_Read_AfsDbl_DblDriveSit_RetVal;
Std_ReturnType                         Rte_Write_AfsDbl_SwiRateLimMsg_RetVal;
Std_ReturnType                         Rte_Write_AfsDbl_DblDriveSit_RetVal;
Std_ReturnType                         Rte_Read_SigPrepRx_Dbl_RightStatus_RetVal;
Std_ReturnType                         Rte_Read_SigPrepRx_Dbl_LeftStatus_RetVal;
Std_ReturnType                         Rte_Read_SigPrep_EnvCondition_RetVal;
Std_ReturnType                         Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType                         Rte_Write_Dbl_SysMonTx_FullStatus_RetVal;
Std_ReturnType                         Rte_Write_Dbl_SigPrepTx_LeftStatus_RetVal;
Std_ReturnType                         Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType                         Rte_Write_Dbl_SigPrepTx_RightStatus_RetVal;
Std_ReturnType                         Rte_Read_SysMon_LifePhases_RetVal;
Std_ReturnType                         Rte_Read_SigPrep_YawSpeed_RetVal;
Std_ReturnType                         Rte_Read_SigPrep_SteeringWheelAngle_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8                                  Order1TrackingFilter32_HitCount;
uint8                                  FirFilter32_HitCount;
uint8                                  UtilDebounce_HitCount;
uint8                                  Order1Filter32_HitCount;
uint8                                  LinEquCalculator_HitCount;
uint8                                  LinEquSolver_HitCount;
uint8                                  Rte_Read_CodM_Dbl_Para_HitCount;
uint8                                  Rte_Read_SigPrep_VehicleConfigSig_HitCount;
uint8                                  Rte_Read_SigPrep_DynamicSigs_HitCount;
uint8                                  Rte_Read_SysMon_Afs_Signals_HitCount;
uint8                                  Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
uint8                                  Rte_Read_Dbl_SwivellingOut_HitCount;
uint8                                  Rte_Read_AfsDbl_DblDriveSit_HitCount;
uint8                                  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount;
uint8                                  Rte_Read_Dbl_SwivellingOut_HitCount;
uint8                                  Rte_Write_AfsDbl_DblDriveSit_HitCount;
uint8                                  Rte_Write_Dbl_Mode_HitCount;
uint8                                  Rte_Write_Dbl_SwivellingOut_HitCount;
uint8                                  Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8                                  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount;
uint8                                  Rte_Read_FctR_AfsDblCmd_HitCount;
uint8                                  UtilDebounceInit_HitCount;
uint8                                  Rte_Read_SigPrep_VehPathCurvature_HitCount;
uint8                                  LPTMR0_GetTimeElapsed_HitCount;
uint8                                  Rte_Read_FctR_AfsDblFoggy_HitCount;
uint8                                  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount;
uint8                                  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount;
uint8                                  Rte_Read_SigPrep_EnvCondition_HitCount;
uint8                                  Rte_Read_SysMon_VehNetState_HitCount;
uint8                                  Rte_Write_Dbl_SysMonTx_FullStatus_HitCount;
uint8                                  Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount;
uint8                                  Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8                                  Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount;
uint8                                  Dem_SetEventStatus_HitCount;
uint8                                  Rte_Read_SysMon_LifePhases_HitCount;
uint8                                  Rte_Read_SigPrep_YawSpeed_HitCount;
uint8                                  Rte_Read_SigPrep_SteeringWheelAngle_HitCount;

//=============================================================================
// Coding related
//=============================================================================
tNvmPara_CodingArea                    Coding_Dummy = { 0u };
tParaFct0_Cmd                          Coding_State;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LifePhases
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LifePhases
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LifePhases_Param1;
  Rte_Read_SysMon_LifePhases_HitCount++;
  return Rte_Read_SysMon_LifePhases_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of Dem_SetEventStatus
///
/// \param  unAlecId
/// \param  ucTestStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus)
{
  Dem_SetEventStatus_Param1 = unAlecId;
  Dem_SetEventStatus_Param2 = ucTestStatus;
  Dem_SetEventStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SigPrepRx_Dbl_RightStatus
///
/// \descr Stub function for Rte_Read_SigPrepRx_Dbl_RightStatus
///
/// \param  tsRte_BendingBeamFault_OtherHL
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrepRx_Dbl_RightStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  *ppara1 = Rte_Read_SigPrepRx_Dbl_RightStatus_Param1;
  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount++;
  return Rte_Read_SigPrepRx_Dbl_RightStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_CodM_Dbl_Para
///
/// \descr Stub function for Rte_Read_CodM_Dbl_Para
///
/// \param  tsRteCodingParameters
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_Dbl_Para(tsRteCodingParameters* ppara1)
{
  Rte_Read_CodM_Dbl_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_Dbl_Para_Param1.eCodingState = Coding_State;

  *ppara1 = Rte_Read_CodM_Dbl_Para_Param1;
  Rte_Read_CodM_Dbl_Para_HitCount++;
  return Rte_Read_CodM_Dbl_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SigPrepRx_Dbl_LeftStatus
///
/// \descr Stub function for Rte_Read_SigPrepRx_Dbl_LeftStatus
///
/// \param  tsRte_BendingBeamFault_OtherHL
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrepRx_Dbl_LeftStatus(tsRte_BendingBeamFault_OtherHL* ppara1)
{
  *ppara1 = Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount++;
  return Rte_Read_SigPrepRx_Dbl_LeftStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SigPrep_EnvCondition
///
/// \descr Stub function for Rte_Read_SigPrep_EnvCondition
///
/// \param  tsRte_SigPrep_EnvCondition
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_EnvCondition(tsRte_SigPrep_EnvCondition* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_EnvCondition_Param1;
  Rte_Read_SigPrep_EnvCondition_HitCount++;
  return Rte_Read_SigPrep_EnvCondition_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysMon_VehNetState
///
/// \descr Stub function for Rte_Read_SysMon_VehNetState
///
/// \param  tsRte_SysMon_VehNetState
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
/// \brief Rte_Read_IoHwAbUser_GetMountingSide
///
/// \descr Stub function for Rte_Read_IoHwAbUser_GetMountingSide
///
/// \param  teRte_MountingSide
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_GetMountingSide_Param1;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount++;
  return Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_Dbl_SigPrepTx_RightStatus
///
/// \descr Stub function for Rte_Write_Dbl_SigPrepTx_RightStatus
///
/// \param  tsRte_BendingBeamFault_OtherHL
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Dbl_SigPrepTx_RightStatus(const tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_Write_Dbl_SigPrepTx_RightStatus_Param1 = *ppara1;
  Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount++;
  return Rte_Write_Dbl_SigPrepTx_RightStatus_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief Rte_Write_Dbl_SigPrepTx_LeftStatus
///
/// \descr Stub function for Rte_Write_Dbl_SigPrepTx_LeftStatus
///
/// \param  tsRte_BendingBeamFault_OtherHL
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Dbl_SigPrepTx_LeftStatus(const tsRte_BendingBeamFault_OtherHL* ppara1)
{
  Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1 = *ppara1;
  Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount++;
  return Rte_Write_Dbl_SigPrepTx_LeftStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR0_GetTimeElapsed
///
/// \descr Stub function for LPTMR0_GetTimeElapsed
///
/// \param  ulStartValue
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_HitCount++;
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  return (LPTMR0_GetTimeElapsed_RetVal);
}

//-----------------------------------------------------------------------------
/// \brief  Order1TrackingFilter32
///
/// \descr  Stub function created to simulate the behaviour of Order1TrackingFilter32
///
/// \param  pFilter
/// \param  unBeta
/// \param  nValue
/// \param  unDeviation
///
/// \return sint32
//-----------------------------------------------------------------------------
sint32 Order1TrackingFilter32(ORDER1_Filter32* pFilter, uint32 unBeta, sint32 nValue, uint32 unDeviation)
{
  Order1TrackingFilter32_Param1 = *pFilter;
  Order1TrackingFilter32_Param2 = unBeta;
  Order1TrackingFilter32_Param3 = nValue;
  Order1TrackingFilter32_Param4 = unDeviation;
  Order1TrackingFilter32_HitCount++;
  return Order1TrackingFilter32_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FirFilter32
///
/// \descr  Stub function created to simulate the behaviour of FirFilter32
///
/// \param  alFirFilter
/// \param  lFilterSize
/// \param  lValue
///
/// \return sint32
//-----------------------------------------------------------------------------
sint32 FirFilter32(sint32 alFirFilter[], sint32 lFilterSize, sint32 lValue)
{
  for (uint8 i = 0; i < DBLC_HLAFILTERSIZE; i++)
  {
    FirFilter32_Param1[i] = alFirFilter[i];
  }
  FirFilter32_Param2 = lFilterSize;
  FirFilter32_Param3 = lValue;
  FirFilter32_HitCount++;
  return FirFilter32_RetVal;
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
  *pCtrl = UtilDebounce_Param1;
  UtilDebounce_Param2 = boVal;
  UtilDebounce_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  Order1Filter32
///
/// \descr  Stub function created to simulate the behaviour of Order1Filter32
///
/// \param  pFilter
/// \param  unBeta
/// \param  nValue
///
/// \return sint32
//-----------------------------------------------------------------------------
sint32 Order1Filter32(ORDER1_Filter32* pFilter, uint32 unBeta, sint32 nValue)
{
  Order1Filter32_Param1 = *pFilter;
  Order1Filter32_Param2 = unBeta;
  Order1Filter32_Param3 = nValue;
  Order1Filter32_HitCount++;
  return Order1Filter32_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  LinEquCalculator
///
/// \descr  Stub function created to simulate the behaviour of LinEquCalculator
///
/// \param  nX
/// \param  pLinEquPar
///
/// \return sint16
//-----------------------------------------------------------------------------
sint16 LinEquCalculator(const sint16 nX, const tLinEqu *const pLinEquPar)
{
  LinEquCalculator_Param1 = nX;
  LinEquCalculator_Param2 = *pLinEquPar;
  LinEquCalculator_HitCount++;
  return LinEquCalculator_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  LinEquSolver
///
/// \descr  Stub function created to simulate the behaviour of LinEquSolver
///
/// \param  Point1
/// \param  Point2
/// \param  pLinEquPar
///
/// \return void
//-----------------------------------------------------------------------------
void LinEquSolver(tPoint Point1, tPoint Point2, tLinEqu* pLinEquPar)
{
  LinEquSolver_Param1 = Point1;
  LinEquSolver_Param2 = Point2;
  LinEquSolver_Param3 = *pLinEquPar;
  LinEquSolver_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_AfsDbl_SwiRateLimMsg
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_AfsDbl_SwiRateLimMsg
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_AfsDbl_SwiRateLimMsg(const tsRte_SwiRateLimMsg* ppara1)
{
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1 = *ppara1;
  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount++;
  return Rte_Write_AfsDbl_SwiRateLimMsg_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_AfsDbl_DblDriveSit
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_AfsDbl_DblDriveSit
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_AfsDbl_DblDriveSit(const tsRte_AfsDblDriveSituation* ppara1)
{
  Rte_Write_AfsDbl_DblDriveSit_Param1 = *ppara1;
  Rte_Write_AfsDbl_DblDriveSit_HitCount++;
  return Rte_Write_AfsDbl_DblDriveSit_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_AfsDbl_DblDriveSit
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_AfsDbl_DblDriveSit
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_AfsDbl_DblDriveSit(tsRte_AfsDblDriveSituation* ppara1)
{
  *ppara1 = Rte_Read_AfsDbl_DblDriveSit_Param1;
  Rte_Read_AfsDbl_DblDriveSit_HitCount++;
  return Rte_Read_AfsDbl_DblDriveSit_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehicleConfigSig
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehicleConfigSig
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehicleConfigSig_Param1;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount++;
  return Rte_Read_SigPrep_VehicleConfigSig_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_DynamicSigs
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_DynamicSigs
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_DynamicSigs_Param1;
  Rte_Read_SigPrep_DynamicSigs_HitCount++;
  return Rte_Read_SigPrep_DynamicSigs_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_Afs_Signals
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_Afs_Signals
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_Afs_Signals(tsRte_SysMonAfsSignals* ppara1)
{
  *ppara1 = Rte_Read_SysMon_Afs_Signals_Param1;
  Rte_Read_SysMon_Afs_Signals_HitCount++;
  return Rte_Read_SysMon_Afs_Signals_RetVal;
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
/// \brief  Rte_Read_Dbl_SwivellingOut
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Dbl_SwivellingOut
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Dbl_SwivellingOut(tsRte_DblOut* ppara1)
{
  *ppara1 = Rte_Read_Dbl_SwivellingOut_Param1;
  Rte_Read_Dbl_SwivellingOut_HitCount++;
  return Rte_Read_Dbl_SwivellingOut_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Dbl_Mode
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Dbl_Mode
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Dbl_Mode(const teRte_DblSubMode* ppara1)
{
  Rte_Write_Dbl_Mode_Param1 = *ppara1;
  Rte_Write_Dbl_Mode_HitCount++;
  return Rte_Write_Dbl_Mode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Dbl_SwivellingOut
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Dbl_SwivellingOut
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Dbl_SwivellingOut(const tsRte_DblOut* ppara1)
{
  Rte_Write_Dbl_SwivellingOut_Param1 = *ppara1;
  Rte_Write_Dbl_SwivellingOut_HitCount++;
  return Rte_Write_Dbl_SwivellingOut_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Dbl_SysMonTx_FullStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Dbl_SysMonTx_FullStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Dbl_SysMonTx_FullStatus(const tsRte_Hs6_Diag_Drvled_BendingBeamFault* ppara1)
{
  Rte_Write_Dbl_SysMonTx_FullStatus_Param1 = *ppara1;
  Rte_Write_Dbl_SysMonTx_FullStatus_HitCount++;
  return Rte_Write_Dbl_SysMonTx_FullStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_VehicleSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehicleSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehicleSpeed_Param1;
  Rte_Read_SysMon_VehicleSpeed_HitCount++;
  return Rte_Read_SysMon_VehicleSpeed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehPathCurvature
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehPathCurvature
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehPathCurvature(tsRte_SigPrep_VehPathCurvature* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehPathCurvature_Param1;
  Rte_Read_SigPrep_VehPathCurvature_HitCount++;
  return Rte_Read_SigPrep_VehPathCurvature_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_AfsDbl_SwiRateLimMsg
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_AfsDbl_SwiRateLimMsg
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_AfsDbl_SwiRateLimMsg(tsRte_SwiRateLimMsg* ppara1)
{
  *ppara1 = Rte_Read_AfsDbl_SwiRateLimMsg_Param1;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount++;
  return Rte_Read_AfsDbl_SwiRateLimMsg_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_FctR_AfsDblCmd
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_FctR_AfsDblCmd
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_FctR_AfsDblCmd(tsRte_AfsDblCmd* ppara1)
{
  *ppara1 = Rte_Read_FctR_AfsDblCmd_Param1;
  Rte_Read_FctR_AfsDblCmd_HitCount++;
  return Rte_Read_FctR_AfsDblCmd_RetVal;
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
/// \brief  Rte_Read_SigPrep_YawSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_YawSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_YawSpeed(tsRte_SigPrep_YawSpeed* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_YawSpeed_Param1;
  Rte_Read_SigPrep_YawSpeed_HitCount++;
  return Rte_Read_SigPrep_YawSpeed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_SteeringWheelAngle
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_YawSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_SteeringWheelAngle(tsRte_SigPrep_SteeringWheelAngle* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_SteeringWheelAngle_Param1;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount++;
  return Rte_Read_SigPrep_SteeringWheelAngle_RetVal;
}


//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcMaxStartSlope_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function returns the correct calculated slope limit
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcMaxStartSlope_Param1 = 1000u
///
/// - Expectations:
///
/// \output _ClPolySolverCalcMaxStartSlope_RetVal = 62u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcMaxStartSlope_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  _ClPolySolverCalcMaxStartSlope_Param1 = 1000;

  //Step 3) Call FUT
  _ClPolySolverCalcMaxStartSlope_RetVal = _ClPolySolverCalcMaxStartSlope(_ClPolySolverCalcMaxStartSlope_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(_ClPolySolverCalcMaxStartSlope_RetVal, 62u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcMaxStartSlope_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function returns the correct calculated slope limit
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcMaxStartSlope_Param1 = 3000u
///
/// - Expectations:
///
/// \output _ClPolySolverCalcMaxStartSlope_RetVal = 21u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcMaxStartSlope_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  _ClPolySolverCalcMaxStartSlope_Param1 = 3000u;

  //Step 3) Call FUT
  _ClPolySolverCalcMaxStartSlope_RetVal = _ClPolySolverCalcMaxStartSlope(_ClPolySolverCalcMaxStartSlope_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(_ClPolySolverCalcMaxStartSlope_RetVal, 21u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcMaxStartSlope
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function returns the correct calculated slope limit

///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcMaxStartSlope(void)
{
  Mt_Dbl__ClPolySolverCalcMaxStartSlope_TestCase_1();
  Mt_Dbl__ClPolySolverCalcMaxStartSlope_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcStartSlope_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates the start slope of the 
///                        polynom function in dependency of the vehicle speed
///                        and the swiveling direction
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcStartSlope_Param1                                 = 1u
/// \input  _ClPolySolverCalcStartSlope_Param2                                 = 1000u
/// \input  _ClPolySolverCalcStartSlope_Param3                                 = 3u
/// \input  _ClPolySolverCalcStartSlope_Param4                                 = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.ucV1                     = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.ucV2                     = 3u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[3].ucSlope1    = 4u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[3].ucSlope2    = 5u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[3].ucSlopeDenG = 1u
/// \input  Order1TrackingFilter32_Param2                                      = 0u
/// \input  Order1TrackingFilter32_Param3                                      = 0u
/// \input  Order1TrackingFilter32_Param4                                      = 0u
/// \input  Order1TrackingFilter32_HitCount                                    = 0u
/// \input  Order1TrackingFilter32_RetVal                                      = 1u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateP32_HitCount                            = 1u
/// \output Order1TrackingFilter32_Param2                                     = 127u
/// \output Order1TrackingFilter32_Param3                                     = 2u
/// \output Order1TrackingFilter32_Param4                                     = 2u
/// \output Order1TrackingFilter32_HitCount                                   = 1u
/// \output _ClPolySolverCalcStartSlope_RetVal                                = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcStartSlope_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks               = &Coding_Dummy;
  _ClPolySolverCalcStartSlope_Param1                       = 1u;
  _ClPolySolverCalcStartSlope_Param2                       = 1000u;
  _ClPolySolverCalcStartSlope_Param3                       = 1u;
  _ClPolySolverCalcStartSlope_Param4                       = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV1                     = 2u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV2                     = 3u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS1        = 4u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS2        = 5u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucDG        = 1u;
  Order1TrackingFilter32_RetVal = 1u;

  //Step 3) Call FUT
  _ClPolySolverCalcStartSlope_RetVal = _ClPolySolverCalcStartSlope(_ClPolySolverCalcStartSlope_Param1, _ClPolySolverCalcStartSlope_Param2, _ClPolySolverCalcStartSlope_Param3, _ClPolySolverCalcStartSlope_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param2,     127u, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param3,       5u, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param4,       2u, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_HitCount,     1u, == );
  AL_UNITTEST_CHECK(_ClPolySolverCalcStartSlope_RetVal,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcStartSlope_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates the start slope of the 
///                        polynom function in dependency of the vehicle speed
///                        and the swiveling direction
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcStartSlope_Param1                                 = 1u
/// \input  _ClPolySolverCalcStartSlope_Param2                                 = 11000u
/// \input  _ClPolySolverCalcStartSlope_Param3                                 = 3u
/// \input  _ClPolySolverCalcStartSlope_Param4                                 = 0u
/// \input  UtilMath_LinearInterpolateP32_RetVal                               = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.ucV1                     = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.ucV2                     = 3u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[3].ucSlope1    = 4u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[3].ucSlope2    = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[3].ucSlopeDenG = 1u
/// \input  Order1TrackingFilter32_Param2                                      = 0u
/// \input  Order1TrackingFilter32_Param3                                      = 0u
/// \input  Order1TrackingFilter32_Param4                                      = 0u
/// \input  Order1TrackingFilter32_HitCount                                    = 0u
/// \input  Order1TrackingFilter32_RetVal                                      = 1u
///
/// - Expectations:
///
/// \output Order1TrackingFilter32_Param2                                     = 127u
/// \output Order1TrackingFilter32_Param3                                     = -3
/// \output Order1TrackingFilter32_Param4                                     = 2u
/// \output Order1TrackingFilter32_HitCount                                   = 1u
/// \output _ClPolySolverCalcStartSlope_RetVal                                = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcStartSlope_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks           = &Coding_Dummy;
  _ClPolySolverCalcStartSlope_Param1                   = 1u;
  _ClPolySolverCalcStartSlope_Param2                   = 11000u;
  _ClPolySolverCalcStartSlope_Param3                   = 1u;
  _ClPolySolverCalcStartSlope_Param4                   = 0u;
  UtilMath_LinearInterpolateP32_RetVal                 = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV1                 = 2u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV2                 = 3u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS1    = 4u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS2    = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucDG = 1u;
  Order1TrackingFilter32_Param2 = 0u;
  Order1TrackingFilter32_Param3 = 0u;
  Order1TrackingFilter32_Param4 = 0u;
  Order1TrackingFilter32_HitCount = 0u;
  Order1TrackingFilter32_RetVal = 1u;

  //Step 3) Call FUT
  _ClPolySolverCalcStartSlope_RetVal = _ClPolySolverCalcStartSlope(_ClPolySolverCalcStartSlope_Param1, _ClPolySolverCalcStartSlope_Param2, _ClPolySolverCalcStartSlope_Param3, _ClPolySolverCalcStartSlope_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param2,      127u, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param3,        -3, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param4,        2u, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_HitCount,      1u, == );
  AL_UNITTEST_CHECK(_ClPolySolverCalcStartSlope_RetVal,   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcStartSlope_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function calculates the start slope of the 
///                        polynom function in dependency of the vehicle speed
///                        and the swiveling direction
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcStartSlope_Param1                                 = 1u
/// \input  _ClPolySolverCalcStartSlope_Param2                                 = 1000u
/// \input  _ClPolySolverCalcStartSlope_Param3                                 = 3u
/// \input  _ClPolySolverCalcStartSlope_Param4                                 = 1u
/// \input  UtilMath_LinearInterpolateP32_RetVal                               = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.ucV1                     = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.ucV2                     = 3u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[3].ucSlope1    = 4u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[3].ucSlope2    = 5u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[3].ucSlopeDenG = 0u
/// \input  Order1TrackingFilter32_Param2                                      = 0u
/// \input  Order1TrackingFilter32_Param3                                      = 0u
/// \input  Order1TrackingFilter32_Param4                                      = 0u
/// \input  Order1TrackingFilter32_HitCount                                    = 0u
/// \input  Order1TrackingFilter32_RetVal                                      = 1u
///
/// - Expectations:
///
/// \output Order1TrackingFilter32_Param2                                     = 127u
/// \output Order1TrackingFilter32_Param3                                     = 1u
/// \output Order1TrackingFilter32_Param4                                     = 2u
/// \output Order1TrackingFilter32_HitCount                                   = 1u
/// \output _ClPolySolverCalcStartSlope_RetVal                                = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcStartSlope_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks           = &Coding_Dummy;
  _ClPolySolverCalcStartSlope_Param1                   = 1;
  _ClPolySolverCalcStartSlope_Param2                   = 1000;
  _ClPolySolverCalcStartSlope_Param3                   = 1;
  _ClPolySolverCalcStartSlope_Param4                   = 1;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV1                 = 2u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV2                 = 3u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS1    = 4u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS2    = 5u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucDG    = 0u;

  //Step 3) Call FUT
  _ClPolySolverCalcStartSlope_RetVal = _ClPolySolverCalcStartSlope(_ClPolySolverCalcStartSlope_Param1, _ClPolySolverCalcStartSlope_Param2, _ClPolySolverCalcStartSlope_Param3, _ClPolySolverCalcStartSlope_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param2,     127u, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param3,       4u, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param4,       2u, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_HitCount,     2u, == );
  AL_UNITTEST_CHECK(_ClPolySolverCalcStartSlope_RetVal,  1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcStartSlope
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the start slope of the 
///                        polynom function 
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcStartSlope(void)
{
  Mt_Dbl__ClPolySolverCalcStartSlope_TestCase_1();
  Mt_Dbl__ClPolySolverCalcStartSlope_TestCase_2();
  Mt_Dbl__ClPolySolverCalcStartSlope_TestCase_3();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UtilLinearInterpolatePClamp32_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 2 and 
///                        eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  UtilLinearInterpolatePClamp32_Param1                                  = 1222u
/// \input  UtilLinearInterpolatePClamp32_Param2                                  = 2132u
/// \input  UtilLinearInterpolatePClamp32_Param3                                  = 3322u
/// \input  UtilLinearInterpolatePClamp32_Param4                                  = 424u
/// \input  UtilLinearInterpolatePClamp32_Param5                                  = 10u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateP32_RetVal                                  = 424u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UtilLinearInterpolatePClamp32_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  UtilLinearInterpolatePClamp32_Param1 = 1222u;
  UtilLinearInterpolatePClamp32_Param2 = 2132u;
  UtilLinearInterpolatePClamp32_Param3 = 3322u;
  UtilLinearInterpolatePClamp32_Param4 = 424u;
  UtilLinearInterpolatePClamp32_Param5 = 10u;


  //Step 3) Call FUT
  UtilLinearInterpolatePClamp32_RetVal = UtilLinearInterpolatePClamp32(UtilLinearInterpolatePClamp32_Param1, UtilLinearInterpolatePClamp32_Param2, UtilLinearInterpolatePClamp32_Param3, UtilLinearInterpolatePClamp32_Param4, UtilLinearInterpolatePClamp32_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilLinearInterpolatePClamp32_RetVal, 424u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UtilLinearInterpolatePClamp32_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 2 and 
///                        eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  UtilLinearInterpolatePClamp32_Param1                                  = 1222u
/// \input  UtilLinearInterpolatePClamp32_Param2                                  = 0u
/// \input  UtilLinearInterpolatePClamp32_Param3                                  = 0u
/// \input  UtilLinearInterpolatePClamp32_Param4                                  = 0u
/// \input  UtilLinearInterpolatePClamp32_Param5                                  = 10u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateP32_RetVal                                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UtilLinearInterpolatePClamp32_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  UtilLinearInterpolatePClamp32_Param1 = 1222u;
  UtilLinearInterpolatePClamp32_Param2 = 0u;
  UtilLinearInterpolatePClamp32_Param3 = 0u;
  UtilLinearInterpolatePClamp32_Param4 = 0u;
  UtilLinearInterpolatePClamp32_Param5 = 10u;

  //Step 3) Call FUT
  UtilLinearInterpolatePClamp32_RetVal = UtilLinearInterpolatePClamp32(UtilLinearInterpolatePClamp32_Param1, UtilLinearInterpolatePClamp32_Param2, UtilLinearInterpolatePClamp32_Param3, UtilLinearInterpolatePClamp32_Param4, UtilLinearInterpolatePClamp32_Param5);
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilLinearInterpolatePClamp32_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UtilLinearInterpolatePClamp32_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 2 and 
///                        eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  UtilLinearInterpolatePClamp32_Param1                                  = 100u
/// \input  UtilLinearInterpolatePClamp32_Param2                                  = 0u
/// \input  UtilLinearInterpolatePClamp32_Param3                                  = 1000u
/// \input  UtilLinearInterpolatePClamp32_Param4                                  = 0u
/// \input  UtilLinearInterpolatePClamp32_Param5                                  = 10u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateP32_RetVal                                  = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UtilLinearInterpolatePClamp32_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  UtilLinearInterpolatePClamp32_Param1 = 100u;
  UtilLinearInterpolatePClamp32_Param2 = 0u;
  UtilLinearInterpolatePClamp32_Param3 = 1000u;
  UtilLinearInterpolatePClamp32_Param4 = 0u;
  UtilLinearInterpolatePClamp32_Param5 = 10u;

  //Step 3) Call FUT
  UtilLinearInterpolatePClamp32_RetVal = UtilLinearInterpolatePClamp32(UtilLinearInterpolatePClamp32_Param1, UtilLinearInterpolatePClamp32_Param2, UtilLinearInterpolatePClamp32_Param3, UtilLinearInterpolatePClamp32_Param4, UtilLinearInterpolatePClamp32_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilLinearInterpolatePClamp32_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UtilLinearInterpolatePClamp32
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UtilLinearInterpolatePClamp32(void)
{
  Mt_Dbl_UtilLinearInterpolatePClamp32_TestCase_1();
  Mt_Dbl_UtilLinearInterpolatePClamp32_TestCase_2();
  Mt_Dbl_UtilLinearInterpolatePClamp32_TestCase_3();
}




//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UtilMath_LinearInterpolateP32_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 2 and 
///                        eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  UtilMath_LinearInterpolateP32_Param1                                  = 1u
/// \input  UtilMath_LinearInterpolateP32_Param2                                  = 2u
/// \input  UtilMath_LinearInterpolateP32_Param3                                  = 3u
/// \input  UtilMath_LinearInterpolateP32_Param4                                  = 4u
/// \input  UtilMath_LinearInterpolateP32_Param5                                  = 5u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateP32_RetVal                                  = 3u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UtilMath_LinearInterpolateP32_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  UtilMath_LinearInterpolateP32_Param1 = 1u;
  UtilMath_LinearInterpolateP32_Param2 = 2u;
  UtilMath_LinearInterpolateP32_Param3 = 3u;
  UtilMath_LinearInterpolateP32_Param4 = 4u;
  UtilMath_LinearInterpolateP32_Param5 = 5u;

  //Step 3) Call FUT
  UtilMath_LinearInterpolateP32_RetVal = UtilMath_LinearInterpolateP32(UtilMath_LinearInterpolateP32_Param1, UtilMath_LinearInterpolateP32_Param2, UtilMath_LinearInterpolateP32_Param3, UtilMath_LinearInterpolateP32_Param4, UtilMath_LinearInterpolateP32_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateP32_RetVal, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UtilMath_LinearInterpolateP32_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 2 and 
///                        eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  UtilMath_LinearInterpolateP32_Param1                                  = 0u
/// \input  UtilMath_LinearInterpolateP32_Param2                                  = 0u
/// \input  UtilMath_LinearInterpolateP32_Param3                                  = 0u
/// \input  UtilMath_LinearInterpolateP32_Param4                                  = 0u
/// \input  UtilMath_LinearInterpolateP32_Param5                                  = -1
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateP32_RetVal                                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UtilMath_LinearInterpolateP32_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  UtilMath_LinearInterpolateP32_Param1 = 0u;
  UtilMath_LinearInterpolateP32_Param2 = 0u;
  UtilMath_LinearInterpolateP32_Param3 = 0u;
  UtilMath_LinearInterpolateP32_Param4 = 0u;
  UtilMath_LinearInterpolateP32_Param5 = -1;

  //Step 3) Call FUT
  UtilMath_LinearInterpolateP32_RetVal = UtilMath_LinearInterpolateP32(UtilMath_LinearInterpolateP32_Param1, UtilMath_LinearInterpolateP32_Param2, UtilMath_LinearInterpolateP32_Param3, UtilMath_LinearInterpolateP32_Param4, UtilMath_LinearInterpolateP32_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateP32_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UtilMath_LinearInterpolateP32_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 2 and 
///                        eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  UtilMath_LinearInterpolateP32_Param1                                  = -1
/// \input  UtilMath_LinearInterpolateP32_Param2                                  = -2
/// \input  UtilMath_LinearInterpolateP32_Param3                                  = -1
/// \input  UtilMath_LinearInterpolateP32_Param4                                  = -1
/// \input  UtilMath_LinearInterpolateP32_Param5                                  = -1
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateP32_RetVal                                  = -1
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UtilMath_LinearInterpolateP32_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  UtilMath_LinearInterpolateP32_Param1 = -1;
  UtilMath_LinearInterpolateP32_Param2 = -2;
  UtilMath_LinearInterpolateP32_Param3 = -1;
  UtilMath_LinearInterpolateP32_Param4 = -1;
  UtilMath_LinearInterpolateP32_Param5 = -1;

  //Step 3) Call FUT
  UtilMath_LinearInterpolateP32_RetVal = UtilMath_LinearInterpolateP32(UtilMath_LinearInterpolateP32_Param1, UtilMath_LinearInterpolateP32_Param2, UtilMath_LinearInterpolateP32_Param3, UtilMath_LinearInterpolateP32_Param4, UtilMath_LinearInterpolateP32_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateP32_RetVal, -1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UtilMath_LinearInterpolateP32
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UtilMath_LinearInterpolateP32(void)
{
  Mt_Dbl_UtilMath_LinearInterpolateP32_TestCase_1();
  Mt_Dbl_UtilMath_LinearInterpolateP32_TestCase_2();
  Mt_Dbl_UtilMath_LinearInterpolateP32_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 2 and 
///                        eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcEndSlope_Param1                                   = 10000u
/// \input  _ClPolySolverCalcEndSlope_Param2                                   = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2                  = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1                  = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].ucE2                  = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].ucE1                  = 0u
///
/// - Expectations:
///
/// \output _ClPolySolverCalcEndSlope_RetVal                                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  _ClPolySolverCalcEndSlope_Param1                  = 10000u;
  _ClPolySolverCalcEndSlope_Param2                  = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].ucE2 = 0;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].ucE1 = 0;

  //Step 3) Call FUT
  _ClPolySolverCalcEndSlope_RetVal = _ClPolySolverCalcEndSlope(_ClPolySolverCalcEndSlope_Param1, _ClPolySolverCalcEndSlope_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(_ClPolySolverCalcEndSlope_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 1, limits end slope
///                        and eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcEndSlope_Param1                                   = -1
/// \input  _ClPolySolverCalcEndSlope_Param2                                   = 1u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2                  = 11u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1                  = -11
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].ucE2                  = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].ucE1                  = 0u
///
/// - Expectations:
///
/// \output _ClPolySolverCalcEndSlope_RetVal                                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks                                       = &Coding_Dummy;
  _ClPolySolverCalcEndSlope_Param1                                                 = -1u;
  _ClPolySolverCalcEndSlope_Param2                                                 = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].snC1 = 11u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].snC2 = -11u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].ucE2 = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].ucE2 = 0u;

  //Step 3) Call FUT
  _ClPolySolverCalcEndSlope_RetVal = _ClPolySolverCalcEndSlope(_ClPolySolverCalcEndSlope_Param1, _ClPolySolverCalcEndSlope_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(_ClPolySolverCalcEndSlope_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function calculates slope in dependency of C
///                        and eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcEndSlope_Param1                                   = 101u
/// \input  _ClPolySolverCalcEndSlope_Param2                                   = 1u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS2                  = 100u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS1                  = 2u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucE1                  = 10u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1                  = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2                  = 0u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateP32_Param1                              = -1
/// \output UtilMath_LinearInterpolateP32_Param2                              = -2
/// \output UtilMath_LinearInterpolateP32_Param3                              = -1
/// \output UtilMath_LinearInterpolateP32_Param4                              = -1
/// \output UtilMath_LinearInterpolateP32_Param5                              = -1
/// \output UtilMath_LinearInterpolateP32_HitCount                            = 0u
/// \output _ClPolySolverCalcEndSlope_RetVal                                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
  _ClPolySolverCalcEndSlope_Param1 = 101u;
  _ClPolySolverCalcEndSlope_Param2 = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS2 = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucS1 = 2u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucE1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 0u;
  UtilMath_LinearInterpolateP32_RetVal = 0u;

  //Step 3) Call FUT
  _ClPolySolverCalcEndSlope_RetVal = _ClPolySolverCalcEndSlope(_ClPolySolverCalcEndSlope_Param1, _ClPolySolverCalcEndSlope_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateP32_Param1, -1, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateP32_Param2, -2, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateP32_Param3, -1, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateP32_Param4, -1, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateP32_Param5, -1, == );
  AL_UNITTEST_CHECK(_ClPolySolverCalcEndSlope_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 1, limits end slope
///                        and eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcEndSlope_Param1                                                 = 150u;
/// \input  _ClPolySolverCalcEndSlope_Param2                                                 = 1u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].snC1 = 11u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].snC2 = 120u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].ucE1 = 100000u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].ucE2 = 1000000u;
///
/// - Expectations:
///
/// \output _ClPolySolverCalcEndSlope_RetVal                                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks                                       = &Coding_Dummy;
  _ClPolySolverCalcEndSlope_Param1                                                 = 150u;
  _ClPolySolverCalcEndSlope_Param2                                                 = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].snC1 = 11u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].snC2 = 120u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].ucE1 = 100000u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[_ClPolySolverCalcEndSlope_Param2].ucE2 = 1000000u;

  //Step 3) Call FUT
  _ClPolySolverCalcEndSlope_RetVal = _ClPolySolverCalcEndSlope(_ClPolySolverCalcEndSlope_Param1, _ClPolySolverCalcEndSlope_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(_ClPolySolverCalcEndSlope_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcEndSlope
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates slope
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcEndSlope(void)
{
  Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_1();
  Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_2();
  Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_3();
  Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_4();
  Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function sets end slope to slope 1, limits end slope
///                        and eliminates step width > 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  _ClPolySolverCalcEndSlope_Param1                                   = 1u
/// \input  _ClPolySolverCalcEndSlope_Param2                                   = 1u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2                  = 1u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucE2                  = 1u
///
/// - Expectations:
///
/// \output _ClPolySolverCalcEndSlope_RetVal                                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcEndSlope_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  _ClPolySolverCalcEndSlope_Param1                  = 1u;
  _ClPolySolverCalcEndSlope_Param2                  = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucE2 = 1u;

  //Step 3) Call FUT
  _ClPolySolverCalcEndSlope_RetVal = _ClPolySolverCalcEndSlope(_ClPolySolverCalcEndSlope_Param1, _ClPolySolverCalcEndSlope_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(_ClPolySolverCalcEndSlope_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl__ClPolySolverCalcEndC
///
/// \Test Case Description
///        - Test subject: Test if function calculates the end curvature
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                                         = FALSE;
/// \input  _ClPolySolverCalcEndC_Param1                                = 999u;
/// \input  _ClPolySolverCalcEndC_Param2                                = 999u;
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.ucV1              = 2u;
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.ucV2              = 3u;
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[10].nC1 = 4u;
/// \input  Dbl_sCodingParam_Dummy.Dbl.AFSPolySolver2.Parameter[10].nC2 = 5u;
/// \input  UtilMath_LinearInterpolateP32_Param1                        = 100u;
/// \input  UtilMath_LinearInterpolateP32_Param2                        = 1000u;
/// \input  UtilMath_LinearInterpolateP32_Param3                        = 1000u;
/// \input  UtilMath_LinearInterpolateP32_Param4                        = 1000u;
/// \input  UtilMath_LinearInterpolateP32_Param5                        = 1000u;
/// \input  UtilMath_LinearInterpolateP32_HitCount                      = 0u;
/// \input  UtilMath_LinearInterpolateP32_RetVal                        = 23u
///
/// - Expectations:
///
/// \output _ClPolySolverCalcEndC_RetVal                               = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl__ClPolySolverCalcEndC(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  Dbl_boIsCodingValid                                = FALSE;
  _ClPolySolverCalcEndC_Param1                       = 999u;
  _ClPolySolverCalcEndC_Param2                       = 999u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV1               = 2u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV2               = 3u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[10].snC1 = 4u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[10].snC2 = 5u;
  UtilMath_LinearInterpolateP32_Param1               = 100u;
  UtilMath_LinearInterpolateP32_Param2               = 1000u;
  UtilMath_LinearInterpolateP32_Param3               = 1000u;
  UtilMath_LinearInterpolateP32_Param4               = 1000u;
  UtilMath_LinearInterpolateP32_Param5               = 1000u;
  UtilMath_LinearInterpolateP32_RetVal               = 23u;

  //Step 3) Call FUT
  _ClPolySolverCalcEndC_RetVal = _ClPolySolverCalcEndC(_ClPolySolverCalcEndC_Param1, _ClPolySolverCalcEndC_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(_ClPolySolverCalcEndC_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function when
///                        EEPROM is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                               = TRUE;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 10;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 10;
/// \input  ClPolySolver_Param1                               = -1u;
/// \input  ClPolySolver_Param2                               = 0u;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal  = 1000u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                               = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 10;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 10;
  ClPolySolver_Param1                               = -1;
  ClPolySolver_Param2                               = 0u;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 1000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function on left bend
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                               = TRUE;
/// \input  ClPolySolver_Param1                               = 333;
/// \input  ClPolySolver_Param2                               = 10;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 100;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1  =10;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2  =10;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2  =10;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].ucE1  =10;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucE1 = 10;
/// \input  UtilMath_LinearInterpolateP32_RetVal              = 10;
/// \input  _ClPolySolverCalcEndC_Param1                      = 999u;
/// \input  _ClPolySolverCalcEndC_Param2                      = 999u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV1              = 2u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV2              = 3u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[10].snC1= 4u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[10].snC2= 5u;
/// \input  UtilMath_LinearInterpolateP32_Param1              = 100u;
/// \input  UtilMath_LinearInterpolateP32_Param2              = 1000u;
/// \input  UtilMath_LinearInterpolateP32_Param3              = 1000u;
/// \input  UtilMath_LinearInterpolateP32_Param4              = 1000u;
/// \input  UtilMath_LinearInterpolateP32_Param5              = 1000u;
/// \input  UtilMath_LinearInterpolateP32_RetVal              = 23u;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                                      = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                                = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClPolySolver_Param1                                = 333;
  ClPolySolver_Param2                                = 10;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1  = 100;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1  = 10;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2  = 10;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2  = 10;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].ucE1  = 10;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].ucE1  = 10;
  UtilMath_LinearInterpolateP32_RetVal               = 10;
  _ClPolySolverCalcEndC_Param1                       = 999u;
  _ClPolySolverCalcEndC_Param2                       = 999u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV1               = 2u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV2               = 3u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[10].snC1 = 4u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[10].snC2 = 5u;
  UtilMath_LinearInterpolateP32_Param1               = 100u;
  UtilMath_LinearInterpolateP32_Param2               = 1000u;
  UtilMath_LinearInterpolateP32_Param3               = 1000u;
  UtilMath_LinearInterpolateP32_Param4               = 1000u;
  UtilMath_LinearInterpolateP32_Param5               = 1000u;
  UtilMath_LinearInterpolateP32_RetVal               = 23u;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function on left bend
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                              =  TRUE;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks       =  &Coding_Dummy;
/// \input  ClPolySolver_Param1                               = 99999999u;
/// \input  ClPolySolver_Param2                               = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 10u;
/// \input  UtilMath_LinearInterpolateP32_RetVal              = 10u;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                                       = 2616u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_33(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                               = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  ClPolySolver_Param1                               = 99999999u;
  ClPolySolver_Param2                               = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 10u;
  UtilMath_LinearInterpolateP32_RetVal              = 10u;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 2616u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function on left bend
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                              = TRUE;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks       = &Coding_Dummy;
/// \input  ClPolySolver_Param1                               =-10u;
/// \input  ClPolySolver_Param2                               =10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 =10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 =10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 =10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 =10u;
/// \input  UtilMath_LinearInterpolateP32_RetVal              =10u;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                                       = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                               = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  ClPolySolver_Param1                               = -10u;
  ClPolySolver_Param2                               = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 10u;
  UtilMath_LinearInterpolateP32_RetVal              = 10u;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function on right bend
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                                  = TRUE;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks           = &Coding_Dummy;
/// \input  ClPolySolver_Param1                              .   = 5u;
/// \input  ClPolySolver_Param2                              .   = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1.   = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1.   = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2    = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2    = 10u;
/// \input  UtilMath_LinearInterpolateP32_RetVal                 = 10u;
/// \input  Dbl_sSwivelBckTimer.eState                           = Di_Off;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                                       = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                               = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  ClPolySolver_Param1                               = 5u;
  ClPolySolver_Param2                               = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 10u;
  UtilMath_LinearInterpolateP32_RetVal              = 10u;
  Dbl_sSwivelBckTimer.eState                        = Di_Off;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function on right bend
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input   Dbl_boIsCodingValid                                      = TRUE;
/// \input   Dbl_sCodingParam.psCodingParameters_Blocks               = &Coding_Dummy;
/// \input   ClPolySolver_Param1                                      = 1u;
/// \input   ClPolySolver_Param2                                      = 10u;
/// \input   Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1        = 10u;
/// \input   Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1        = 10u;
/// \input   Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2        = 10u;
/// \input   Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2        = 10u;
/// \input   UtilMath_LinearInterpolateP32_RetVal                     = 10u;
/// \input   Dbl_sSwivelBckTimer.eState                               = Di_On;
/// \input   Coding_Dummy.Dbl.DrivingSituationParam.ucSwivelBackAngle = 0u;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                                       = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                                      = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks               = &Coding_Dummy;
  ClPolySolver_Param1                                      = 1u;
  ClPolySolver_Param2                                      = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1        = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1        = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2        = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2        = 10u;
  UtilMath_LinearInterpolateP32_RetVal                     = 10u;
  Dbl_sSwivelBckTimer.eState                               = Di_On;
  Coding_Dummy.Dbl.DrivingSituationParam.ucSwivelBackAngle = 0u;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                               = TRUE;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
/// \input  ClPolySolver_Param1                               = 0u;
/// \input  ClPolySolver_Param2                               = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 10u;
/// \input  UtilMath_LinearInterpolateP32_RetVal              = 10u;
/// \input  Dbl_sSwivelBckTimer.eState                        = Di_On;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                              = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                               = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  ClPolySolver_Param1                               = 0u;
  ClPolySolver_Param2                               = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 10u;
  UtilMath_LinearInterpolateP32_RetVal              = 10u;
  Dbl_sSwivelBckTimer.eState                        = Di_On;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function on right band
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input   Dbl_boIsCodingValid                               = TRUE;
/// \input   Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
/// \input   ClPolySolver_Param1                               = 5u;
/// \input   ClPolySolver_Param2                               = 10u;
/// \input   Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10u;
/// \input   Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10u;
/// \input   Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 20u;
/// \input   Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 20u;
/// \input   UtilMath_LinearInterpolateP32_RetVal              = 1u;
/// \input   Dbl_sSwivelBckTimer.eState                        = Di_On;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                                       = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                               = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  ClPolySolver_Param1                               = 5u;
  ClPolySolver_Param2                               = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 20u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 20u;
  UtilMath_LinearInterpolateP32_RetVal              = 1u;
  Dbl_sSwivelBckTimer.eState                        = Di_On;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function on right band
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                               = TRUE;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
/// \input  ClPolySolver_Param1                               = -5u;
/// \input  ClPolySolver_Param2                               = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 0u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 0u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 20u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 20u;
/// \input  UtilMath_LinearInterpolateP32_RetVal              = 1u;
/// \input  Dbl_sSwivelBckTimer.eState                        = Di_On;

///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                                       = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_8(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                               = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  ClPolySolver_Param1                               = -5u;
  ClPolySolver_Param2                               = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 20u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 20u;
  UtilMath_LinearInterpolateP32_RetVal              = 1u;
  Dbl_sSwivelBckTimer.eState                        = Di_On;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_9
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function on left band
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                                      = TRUE;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks               = &Coding_Dummy;
/// \input  ClPolySolver_Param1                                      = -1u;
/// \input  ClPolySolver_Param2                                      = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1        = 0u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1        = 0u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2        = 20u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2        = 20u;
/// \input  UtilMath_LinearInterpolateP32_RetVal                     = 10000u;
/// \input  Dbl_sSwivelBckTimer.eState                               = Di_On;
/// \input  Order1TrackingFilter32_RetVal                            =-10000u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle         = 0;
/// \input  Coding_Dummy.Dbl.DrivingSituationParam.ucSwivelBackAngle = 0;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                                       = 1000u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_9(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                                      = TRUE;
  Dbl_sCodingParam.psCodingParameters_Blocks               = &Coding_Dummy;
  ClPolySolver_Param1                                      = -1u;
  ClPolySolver_Param2                                      = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1        = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1        = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2        = 20u;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2        = 20u;
  UtilMath_LinearInterpolateP32_RetVal                     = 10000u;
  Dbl_sSwivelBckTimer.eState                               = Di_On;
  Order1TrackingFilter32_RetVal                            = -10000u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle         = 0;
  Coding_Dummy.Dbl.DrivingSituationParam.ucSwivelBackAngle = 0;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver_TestCase_10
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function on left band
///                        when EEPROM is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boIsCodingValid                               = FALSE;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
/// \input  ClPolySolver_Param1                               = -20;
/// \input  ClPolySolver_Param2                               = 0;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 0;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 0;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 20;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 20;
/// \input  UtilMath_LinearInterpolateP32_RetVal              = 10000;
/// \input  Dbl_sSwivelBckTimer.eState                        = Di_On;
/// \input  Order1TrackingFilter32_RetVal                     = -10000;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle  = 0u;
/// \input  Dbl_sSwivelBckTimer.eState                        = 2u;
/// \input  UtilDebounce_Param1.eState                        = 2u;
///
/// - Expectations:
///
/// \output ClPolySolver_RetVal                                       = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver_TestCase_10(void)
{
  //Step 1) Set pre-conditions
  Dbl_boIsCodingValid                               = FALSE;
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  ClPolySolver_Param1                               = -20;
  ClPolySolver_Param2                               = 0;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC1 = 0;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC1 = 0;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[0].snC2 = 20;
  Coding_Dummy.Dbl.AFSPolySolver2.Parameter[1].snC2 = 20;
  UtilMath_LinearInterpolateP32_RetVal              = 10000;
  Dbl_sSwivelBckTimer.eState                        = Di_On;
  Order1TrackingFilter32_RetVal                     = -10000;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle  = 0u;
  Dbl_sSwivelBckTimer.eState                        = 2u;
  UtilDebounce_Param1.eState                        = 2u;

  //Step 3) Call FUT
  ClPolySolver_RetVal = ClPolySolver(ClPolySolver_Param1, ClPolySolver_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPolySolver_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPolySolver
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the polynom function
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPolySolver(void)
{
  Mt_Dbl_ClPolySolver_TestCase_3(); 
  Mt_Dbl_ClPolySolver_TestCase_4(); 
  Mt_Dbl_ClPolySolver_TestCase_5(); 
  Mt_Dbl_ClPolySolver_TestCase_6(); 
  Mt_Dbl_ClPolySolver_TestCase_7(); 
  Mt_Dbl_ClPolySolver_TestCase_8(); 
  Mt_Dbl_ClPolySolver_TestCase_9(); 
  Mt_Dbl_ClPolySolver_TestCase_10();
  Mt_Dbl_ClPolySolver_TestCase_1();
  Mt_Dbl_ClPolySolver_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClResetSpeedFilter
///
/// \Test Case Description
///        - Test subject: Test if function resets speed filter
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Cl_Filter_Speed = 10u
///
/// - Expectations:
///
/// \output Cl_Filter_Speed = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClResetSpeedFilter(void)
{
  //Step 1) Set pre-conditions
  Cl_Filter_Speed = 10u;

  //Step 3) Call FUT
  ClResetSpeedFilter();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Cl_Filter_Speed, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClHlaIdlePosition_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates the idle position of the system
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
/// \input  ClHlaIdlePosition_Param1                   = 1u;
/// \input  ClHlaIdlePosition_Param2                   = 100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV0       = 1u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV1       = 2u;
/// \input  Order1Filter32_Param2                      = 0u;
/// \input  Order1Filter32_Param3                      = 0u;
/// \input  Order1Filter32_HitCount                    = 0u;
/// \input  Order1Filter32_RetVal                      = 0u;
///
/// - Expectations:
///
/// \output Order1Filter32_Param2                        = 122u
/// \output Order1Filter32_Param3                        = 90u
/// \output Order1Filter32_HitCount                      = 1u
/// \output ClHlaIdlePosition_RetVal                     = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClHlaIdlePosition_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
  ClHlaIdlePosition_Param1                   = 1u;
  ClHlaIdlePosition_Param2                   = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV0       = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV1       = 2u;
  Order1Filter32_Param2                      = 0u;
  Order1Filter32_Param3                      = 0u;
  Order1Filter32_HitCount                    = 0u;
  Order1Filter32_RetVal                      = 0u;

  //Step 3) Call FUT
  ClHlaIdlePosition_RetVal = ClHlaIdlePosition(ClHlaIdlePosition_Param1, ClHlaIdlePosition_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Order1Filter32_Param2,   122u, == );
  AL_UNITTEST_CHECK(Order1Filter32_Param3,    90u, == );
  AL_UNITTEST_CHECK(Order1Filter32_HitCount,   1u, == );
  AL_UNITTEST_CHECK(ClHlaIdlePosition_RetVal,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClHlaIdlePosition_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates the idle position of the system
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
/// \input  ClHlaIdlePosition_Param1                   = 1u;
/// \input  ClHlaIdlePosition_Param2                   = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV0       = 2u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV1       = 2u;
/// \input  Order1Filter32_Param2                      = 0u;
/// \input  Order1Filter32_Param3                      = 0u;
/// \input  Order1Filter32_HitCount                    = 0u;
/// \input  Order1Filter32_RetVal                      = 0u;
///
/// - Expectations:
///
/// \output Order1Filter32_Param2                         = 122u
/// \output Order1Filter32_Param3                         = 0u
/// \output Order1Filter32_HitCount                       = 1u
/// \output ClHlaIdlePosition_RetVal                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClHlaIdlePosition_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
  ClHlaIdlePosition_Param1                   = 1u;
  ClHlaIdlePosition_Param2                   = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV0       = 2u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV1       = 2u;
  Order1Filter32_Param2                      = 0u;
  Order1Filter32_Param3                      = 0u;
  Order1Filter32_HitCount                    = 0u;
  Order1Filter32_RetVal                      = 0u;

  //Step 3) Call FUT
  ClHlaIdlePosition_RetVal = ClHlaIdlePosition(ClHlaIdlePosition_Param1, ClHlaIdlePosition_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Order1Filter32_Param2,  122u, == );
  AL_UNITTEST_CHECK(Order1Filter32_Param3,    0u, == );
  AL_UNITTEST_CHECK(Order1Filter32_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ClHlaIdlePosition_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClHlaIdlePosition
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the idle position of the system
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClHlaIdlePosition(void)
{
  Mt_Dbl_ClHlaIdlePosition_TestCase_1();
  Mt_Dbl_ClHlaIdlePosition_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClHlaAttenuationFactor_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates the head light angle attenuation factor
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
/// \input  ClHlaAttenuationFactor_Param1              = 0u;
/// \input  ClHlaAttenuationFactor_Param2              = 0u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV3       = 2u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4       = 1u;
///
/// - Expectations:
///
/// \output ClHlaAttenuationFactor_RetVal                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClHlaAttenuationFactor_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
  ClHlaAttenuationFactor_Param1              = 0u;
  ClHlaAttenuationFactor_Param2              = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV3       = 2u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4       = 1u;

  //Step 3) Call FUT
  ClHlaAttenuationFactor_RetVal = ClHlaAttenuationFactor(ClHlaAttenuationFactor_Param1, ClHlaAttenuationFactor_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClHlaAttenuationFactor_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClHlaAttenuationFactor_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates the head light angle attenuation factor
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
/// \input  ClHlaAttenuationFactor_Param1              = 0u;
/// \input  ClHlaAttenuationFactor_Param2              = 0u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV3       = 1u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4       = 2u;
///
/// - Expectations:
///
/// \output ClHlaAttenuationFactor_RetVal                = 1000u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClHlaAttenuationFactor_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
  ClHlaAttenuationFactor_Param1              = 0u;
  ClHlaAttenuationFactor_Param2              = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV3       = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4       = 2u;

  //Step 3) Call FUT
  ClHlaAttenuationFactor_RetVal = ClHlaAttenuationFactor(ClHlaAttenuationFactor_Param1, ClHlaAttenuationFactor_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClHlaAttenuationFactor_RetVal, 1000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClHlaAttenuationFactor_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function calculates the head light angle attenuation factor
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
/// \input  ClHlaAttenuationFactor_Param1              = 0u;
/// \input  ClHlaAttenuationFactor_Param2              = 15u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV3       = 1u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4       = 2u;
///
/// - Expectations:
///
/// \output ClHlaAttenuationFactor_RetVal                = 500u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClHlaAttenuationFactor_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
  ClHlaAttenuationFactor_Param1              = 0u;
  ClHlaAttenuationFactor_Param2              = 15u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV3       = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4       = 2u;

  //Step 3) Call FUT
  ClHlaAttenuationFactor_RetVal = ClHlaAttenuationFactor(ClHlaAttenuationFactor_Param1, ClHlaAttenuationFactor_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClHlaAttenuationFactor_RetVal, 500u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClHlaAttenuationFactor_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function calculates the head light angle attenuation factor
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
/// \input  ClHlaAttenuationFactor_Param1              = 0u;
/// \input  ClHlaAttenuationFactor_Param2              = 15u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV3       = 1u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4       = 1u;
///
/// - Expectations:
///
/// \output ClHlaAttenuationFactor_RetVal                = 1000u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClHlaAttenuationFactor_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
  ClHlaAttenuationFactor_Param1              = 0u;
  ClHlaAttenuationFactor_Param2              = 15u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV3       = 1u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4       = 1u;

  //Step 3) Call FUT
  ClHlaAttenuationFactor_RetVal = ClHlaAttenuationFactor(ClHlaAttenuationFactor_Param1, ClHlaAttenuationFactor_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClHlaAttenuationFactor_RetVal, 1000u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClHlaAttenuationFactor
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the idle position of the system
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClHlaAttenuationFactor(void)
{
  Mt_Dbl_ClHlaAttenuationFactor_TestCase_1();
  Mt_Dbl_ClHlaAttenuationFactor_TestCase_2();
  Mt_Dbl_ClHlaAttenuationFactor_TestCase_3();
  Mt_Dbl_ClHlaAttenuationFactor_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClPoly3
///
/// \Test Case Description
///        - Test subject: Test if function calculates the cubic polynomial
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClPoly3_Param1 = 2u
/// \input  ClPoly3_Param2 = 2u
/// \input  ClPoly3_Param3 = 2u
/// \input  ClPoly3_Param4 = 2u
/// \input  ClPoly3_Param5 = 2u
///
/// - Expectations:
///
/// \output ClPoly3_RetVal = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClPoly3(void)
{
  //Step 1) Set pre-conditions
  ClPoly3_Param1 = 2u;
  ClPoly3_Param2 = 2u;
  ClPoly3_Param3 = 2u;
  ClPoly3_Param4 = 2u;
  ClPoly3_Param5 = 2u;

  //Step 3) Call FUT
  ClPoly3_RetVal = ClPoly3(ClPoly3_Param1, ClPoly3_Param2, ClPoly3_Param3, ClPoly3_Param4, ClPoly3_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClPoly3_RetVal, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_LrRelation2_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates the left and right head light angle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                                          = &Coding_Dummy;
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvatur = 1200u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                         = SIG_VALID;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                   = eTypeDir_SteeringRight;
/// \input  LrRelation2_Param1                                                                  = -100;
/// \input  LrRelation2_Param2                                                                  = &LrRelation2_Param2_Dummy;
/// \input  LrRelation2_Param3                                                                  = &LrRelation2_Param3_Dummy;
/// \input  Dbl_boHB                                                                            = FALSE;
/// \input  Dbl_eMountingSide                                                                   = Dbl_eMountedLeft;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMIT_LEFT_RHT                  = 10u;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMITS_RIGHT_RGT[0]             = 20u;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMITS_RIGHT_RGT[1]             = 0u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                             = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                             = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                            = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                    = 10u;
/// \input  Coding_Dummy.Sys.Configurability.ucDbl_Enable                                       = 0u;
///
/// - Expectations:
///
/// \output *LrRelation2_Param2                                       = -6
/// \output *LrRelation2_Param3                                       = -6
///
//-----------------------------------------------------------------------------
void Mt_Dbl_LrRelation2_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  sint32 LrRelation2_Param2_Dummy;
  sint32 LrRelation2_Param3_Dummy;

  Dbl_sCodingParam.psCodingParameters_Blocks                                           = &Coding_Dummy;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 1200u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                          = SIG_VALID;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eTypeDir_SteeringRight;
  LrRelation2_Param1                                                                   = -100;
  LrRelation2_Param2                                                                   = &LrRelation2_Param2_Dummy;
  LrRelation2_Param3                                                                   = &LrRelation2_Param3_Dummy;
  Dbl_boHB                                                                             = FALSE;
  Dbl_eMountingSide                                                                    = Dbl_eMountedLeft;
  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMIT_LEFT_RHT                   = 10u;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMITS_RIGHT_RGT[0]              = 20u;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMITS_RIGHT_RGT[1]              = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                              = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                              = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                             = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                     = 10u;
  Dbl_sCurvatureData.ucCurvatureMode = 1u;

  //Step 3) Call FUT
  LrRelation2(LrRelation2_Param1, LrRelation2_Param2, LrRelation2_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*LrRelation2_Param2, -6, == );
  AL_UNITTEST_CHECK(*LrRelation2_Param3, -6, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_LrRelation2_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates the left and right head light angle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvatur 1200u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                         SIG_VALID;
/// \input  Dbl_boHB                                                                            FALSE;
/// \input  Dbl_eMountingSide                                                                   0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                   eTypeDir_SteeringLeft;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                                          &Coding_Dummy;
/// \input  LrRelation2_Param1                                                                  100u;
/// \input  LrRelation2_Param2                                                                  &LrRelation2_Param2_Dummy;
/// \input  LrRelation2_Param3                                                                  &LrRelation2_Param3_Dummy;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]              10u;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                 100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                             10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                             100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                            100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                    10u;
/// \input  Coding_Dummy.Sys.Configurability.ucDbl_Enable                                       1u;
/// \input  Dbl_sCurvatureData.ucCurvatureMode                                                0u;
/// \input  Dbl_sCurvatureData.slCurvatureProcessedValue                                      5u;
///
/// - Expectations:
///
/// \output *LrRelation2_Param2                                       = 220u
/// \output *LrRelation2_Param3                                       = 220u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_LrRelation2_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  sint32 LrRelation2_Param2_Dummy;
  sint32 LrRelation2_Param3_Dummy;

  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 1200u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                          = SIG_VALID;
  Dbl_boHB                                                                             = FALSE;
  Dbl_eMountingSide                                                                    = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eTypeDir_SteeringLeft;
  Dbl_sCodingParam.psCodingParameters_Blocks                                           = &Coding_Dummy;
  LrRelation2_Param1                                                                   = 100u;
  LrRelation2_Param2                                                                   = &LrRelation2_Param2_Dummy;
  LrRelation2_Param3                                                                   = &LrRelation2_Param3_Dummy;
  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]               = 10u;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                  = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                              = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                              = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                             = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                     = 10u;
  Dbl_sCurvatureData.ucCurvatureMode                                                   = 0u;
  Dbl_sCurvatureData.slCurvatureProcessedValue                                         = 5;

  //Step 3) Call FUT
  LrRelation2(LrRelation2_Param1, LrRelation2_Param2, LrRelation2_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*LrRelation2_Param2, 220u, == );
  AL_UNITTEST_CHECK(*LrRelation2_Param3, 220, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_LrRelation2_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function calculates the left and right head light angle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boHB                                                          = TRUE;
/// \input  Dbl_eMountingSide                                                 = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                 = eTypeDir_SteeringLeft;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                        = &Coding_Dummy;
/// \input  LrRelation2_Param1                                                = 100u;
/// \input  LrRelation2_Param2                                                = &LrRelation2_Param2_Dummy;
/// \input  LrRelation2_Param3                                                = &LrRelation2_Param3_Dummy;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.ucHBS_HB_SWIVELING_ANGLE_MAX = 50u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                           = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                           = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                          = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                  = 10u;
///
/// - Expectations:
///
/// \output *LrRelation2_Param2                                       = -5
/// \output *LrRelation2_Param3                                       = -5
///
//-----------------------------------------------------------------------------
void Mt_Dbl_LrRelation2_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  sint32 LrRelation2_Param2_Dummy;
  sint32 LrRelation2_Param3_Dummy;

  Dbl_boHB                                                          = TRUE;
  Dbl_eMountingSide                                                 = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                 = eTypeDir_SteeringLeft;
  Dbl_sCodingParam.psCodingParameters_Blocks                        = &Coding_Dummy;
  LrRelation2_Param1                                                = 100u;
  LrRelation2_Param2                                                = &LrRelation2_Param2_Dummy;
  LrRelation2_Param3                                                = &LrRelation2_Param3_Dummy;
  Coding_Dummy.Dbl.DblAngleLimitations.ucHBS_HB_SWIVELING_ANGLE_MAX = 50u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                           = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                           = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                          = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                  = 10u;
  Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode = 1u;


  //Step 3) Call FUT
  LrRelation2(LrRelation2_Param1, LrRelation2_Param2, LrRelation2_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*LrRelation2_Param2, -5, == );
  AL_UNITTEST_CHECK(*LrRelation2_Param3, -5, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_LrRelation2_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function calculates the left and right head light angle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 1200u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                          = SIG_VALID;
/// \input  Dbl_boHB                                                                             = FALSE;
/// \input  Dbl_eMountingSide                                                                    = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eTypeDir_Invalid;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                                           = &Coding_Dummy;
/// \input  LrRelation2_Param1                                                                   = 100u;
/// \input  LrRelation2_Param2                                                                   = &LrRelation2_Param2_Dummy;
/// \input  LrRelation2_Param3                                                                   = &LrRelation2_Param3_Dummy;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]               = 10u;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                  = 100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                              = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                              = 100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                             = 100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                     = 10u;
///
/// - Expectations:
///
/// \output *LrRelation2_Param2                                       = 0u
/// \output *LrRelation2_Param3                                       = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_LrRelation2_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  sint32 LrRelation2_Param2_Dummy;
  sint32 LrRelation2_Param3_Dummy;

  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature  = 1200u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                           = SIG_VALID;
  Dbl_boHB                                                                              = FALSE;
  Dbl_eMountingSide                                                                     = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                     = eTypeDir_Invalid;
  Dbl_sCodingParam.psCodingParameters_Blocks                                            = &Coding_Dummy;
  LrRelation2_Param1                                                                    = 100u;
  LrRelation2_Param2                                                                    = &LrRelation2_Param2_Dummy;
  LrRelation2_Param3                                                                    = &LrRelation2_Param3_Dummy;
  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]                = 10u;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                   = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                               = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                               = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                              = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                      = 10u;
  Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode = 1u;


  //Step 3) Call FUT
  LrRelation2(LrRelation2_Param1, LrRelation2_Param2, LrRelation2_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*LrRelation2_Param2, 0u, == );
  AL_UNITTEST_CHECK(*LrRelation2_Param3, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_LrRelation2_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function calculates the left and right head light angle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature= -1200;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                         = SIG_VALID;
/// \input  Dbl_boHB                                                                            = FALSE;
/// \input  Dbl_eMountingSide                                                                   = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                   = eTypeDir_Invalid;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                                          = &Coding_Dummy;
/// \input  LrRelation2_Param1                                                                  = 100u;
/// \input  LrRelation2_Param2                                                                  = &LrRelation2_Param2_Dummy;
/// \input  LrRelation2_Param3                                                                  = &LrRelation2_Param3_Dummy;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]              = 10u;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                 = 100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                             = 10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                             = 100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                            = 100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                    = 10u;
///
/// - Expectations:
///
/// \output *LrRelation2_Param2                                       = 0u
/// \output *LrRelation2_Param3                                       = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_LrRelation2_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  sint32 LrRelation2_Param2_Dummy;
  sint32 LrRelation2_Param3_Dummy;

  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = -1200;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                          = SIG_VALID;
  Dbl_boHB                                                                             = FALSE;
  Dbl_eMountingSide                                                                    = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eTypeDir_Invalid;
  Dbl_sCodingParam.psCodingParameters_Blocks                                           = &Coding_Dummy;
  LrRelation2_Param1                                                                   = 100u;
  LrRelation2_Param2                                                                   = &LrRelation2_Param2_Dummy;
  LrRelation2_Param3                                                                   = &LrRelation2_Param3_Dummy;
  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]               = 10u;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                  = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                              = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                              = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                             = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                     = 10u;

  //Step 3) Call FUT
  LrRelation2(LrRelation2_Param1, LrRelation2_Param2, LrRelation2_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*LrRelation2_Param2, 0u, == );
  AL_UNITTEST_CHECK(*LrRelation2_Param3, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_LrRelation2_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function calculates the left and right head light angle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature =  -1200;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                          =  SIG_VALID;
/// \input  Dbl_boHB                                                                             =  FALSE;
/// \input  Dbl_eMountingSide                                                                    =  0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    =  eTypeDir_SteeringRight;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                                           =  &Coding_Dummy;
/// \input  LrRelation2_Param1                                                                   =  100u;
/// \input  LrRelation2_Param2                                                                   =  &LrRelation2_Param2_Dummy;
/// \input  LrRelation2_Param3                                                                   =  &LrRelation2_Param3_Dummy;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]               =  10u;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                  =  100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                              =  10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                              =  100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                             =  100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                     =  10u;
///
/// - Expectations:
///
/// \output *LrRelation2_Param2                                       = 220u
/// \output *LrRelation2_Param3                                       = 220u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_LrRelation2_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  sint32 LrRelation2_Param2_Dummy;
  sint32 LrRelation2_Param3_Dummy;

  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = -1200;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                          = SIG_VALID;
  Dbl_boHB                                                                             = FALSE;
  Dbl_eMountingSide                                                                    = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eTypeDir_SteeringRight;
  Dbl_sCodingParam.psCodingParameters_Blocks                                           = &Coding_Dummy;
  LrRelation2_Param1                                                                   = 100u;
  LrRelation2_Param2                                                                   = &LrRelation2_Param2_Dummy;
  LrRelation2_Param3                                                                   = &LrRelation2_Param3_Dummy;
  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]               = 10u;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                  = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                              = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                              = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                             = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                     = 10u;

  //Step 3) Call FUT
  LrRelation2(LrRelation2_Param1, LrRelation2_Param2, LrRelation2_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*LrRelation2_Param2, 220u, == );
  AL_UNITTEST_CHECK(*LrRelation2_Param3, 220u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_LrRelation2_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function calculates the left and right head light angle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvatur = -1200;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                         =  SIG_VALID;
/// \input  Dbl_boHB                                                                            =  FALSE;
/// \input  Dbl_eMountingSide                                                                   =  0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                   =  eTypeDir_SteeringLeft;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                                          =  &Coding_Dummy;
/// \input  LrRelation2_Param1                                                                  =  100u;
/// \input  LrRelation2_Param2                                                                  =  &LrRelation2_Param2_Dummy;
/// \input  LrRelation2_Param3                                                                  =  &LrRelation2_Param3_Dummy;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]              =  10u;
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                 =  100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                             =  10u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                             =  100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                            =  100u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                    =  10u;
///
/// - Expectations:
///
/// \output *LrRelation2_Param2                                       = 214u
/// \output *LrRelation2_Param3                                       = 226u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_LrRelation2_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  sint32 LrRelation2_Param2_Dummy;
  sint32 LrRelation2_Param3_Dummy;

  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature  = -1200;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                           =  SIG_VALID;
  Dbl_boHB                                                                              =  FALSE;
  Dbl_eMountingSide                                                                     =  0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                     =  eTypeDir_SteeringLeft;
  Dbl_sCodingParam.psCodingParameters_Blocks                                            =  &Coding_Dummy;
  LrRelation2_Param1                                                                    =  100u;
  LrRelation2_Param2                                                                    =  &LrRelation2_Param2_Dummy;
  LrRelation2_Param3                                                                    =  &LrRelation2_Param3_Dummy;
  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]                =  10u;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                   =  100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                               =  10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                               =  100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                              =  100u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                      =  10u;

  //Step 3) Call FUT
  LrRelation2(LrRelation2_Param1, LrRelation2_Param2, LrRelation2_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*LrRelation2_Param2, 214u, == );
  AL_UNITTEST_CHECK(*LrRelation2_Param3, 226u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_LrRelation2_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function calculates the left and right head light angle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  LrRelation2_Param2                                                                    = &LrRelation2_Param2_Dummy;
/// \input  LrRelation2_Param3                                                                    = &LrRelation2_Param3_Dummy;
/// \input  Dbl_boHB                                                                              = FALSE;
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature  = 0;
///
/// - Expectations:
///
/// \output *LrRelation2_Param2                                       = 207u
/// \output *LrRelation2_Param3                                       = 226u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_LrRelation2_TestCase_8(void)
{
  //Step 1) Set pre-conditions
  sint32 LrRelation2_Param2_Dummy;
  sint32 LrRelation2_Param3_Dummy;

  LrRelation2_Param2                                                                   = &LrRelation2_Param2_Dummy;
  LrRelation2_Param3                                                                   = &LrRelation2_Param3_Dummy;
  Dbl_boHB                                                                             = FALSE;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 0;

  //Step 3) Call FUT
  LrRelation2(LrRelation2_Param1, LrRelation2_Param2, LrRelation2_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*LrRelation2_Param2, 207u, == );
  AL_UNITTEST_CHECK(*LrRelation2_Param3, 226u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_LrRelation2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the left and right head light angle
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_LrRelation2(void)
{
  Mt_Dbl_LrRelation2_TestCase_1();
  Mt_Dbl_LrRelation2_TestCase_2();
  Mt_Dbl_LrRelation2_TestCase_3();
  Mt_Dbl_LrRelation2_TestCase_4();
  Mt_Dbl_LrRelation2_TestCase_5();
  Mt_Dbl_LrRelation2_TestCase_6();
  Mt_Dbl_LrRelation2_TestCase_7();
  Mt_Dbl_LrRelation2_TestCase_8();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcSm_ParaFct0_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test for Coding Status Invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Dbl_Para_HitCount        = 0u
/// \input  Dbl_boIsCodingValid                    = TRUE
/// \input  Coding_State                           = eParaFct0_CodingDataInvalid (0u)
///
/// - Expectations:
///
/// \output Rte_Read_CodM_Dbl_Para_HitCount        = 1u
/// \output Dbl_boIsCodingValid                    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcSm_ParaFct0_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_CodM_Dbl_Para_HitCount = 0u;
  Dbl_boIsCodingValid             = TRUE;
  Coding_State                    = eParaFct0_CodingDataInvalid;

  //Step 3) Call FUT
  DblcSm_ParaFct0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Dbl_Para_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_boIsCodingValid,          FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcSm_ParaFct0_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test for Coding Status Valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Dbl_Para_HitCount        = 0u
/// \input  Dbl_boIsCodingValid                    = FALSE
/// \input  Coding_State                           = eParaFct0_CodingDataValid (1u)
///
/// - Expectations:
///
/// \output Rte_Read_CodM_Dbl_Para_HitCount        = 1u
/// \output Dbl_boIsCodingValid                    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcSm_ParaFct0_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_CodM_Dbl_Para_HitCount = 0u;
  Dbl_boIsCodingValid             = FALSE;
  Coding_State                    = eParaFct0_CodingDataValid;

  //Step 3) Call FUT
  DblcSm_ParaFct0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Dbl_Para_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_boIsCodingValid,           TRUE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcSm_ParaFct0
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test for Coding Status Valid
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcSm_ParaFct0(void)
{
  Mt_Dbl_DblcSm_ParaFct0_TestCase_1();
  Mt_Dbl_DblcSm_ParaFct0_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcSm_Init
///
/// \Test Case Description
///        - Test subject: Test if function initializes variables
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Dbl_Para_HitCount              = 0u
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Read_CodM_Dbl_Para_HitCount              = 1u
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcSm_Init(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_CodM_Dbl_Para_HitCount              = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;

  //Step 3) Call FUT
  DblcSm_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Dbl_Para_HitCount,              1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_DblDblcCl_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates head light angle for right hand traffic
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 0u
/// \input  Rte_Read_SigPrep_HandTraffic_Port_Param1.eHandTraffic = eRightHandTraffic
/// \input  Dbl_slnHlaOut                                         = -10u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_Param1.nLimit[0]   = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_Param1.nLimit[1]   = 20u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 1u
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 1u
/// \output DblcCl_RetVal                                         = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCl_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eRightHandTraffic;
  Dbl_slnHlaOut                                     = -10u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]    = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]    = 20u;

  //Step 3) Call FUT
  DblcCl_RetVal = DblcCl(DblcCl_Param1, DblcCl_Param2, DblcCl_Param3, DblcCl_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcCl_RetVal,                          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCl_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates head light angle for left hand traffic
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 0u
/// \input  Rte_Read_SigPrep_HandTraffic_Port_Param1.eHandTraffic = eRightHandTraffic
/// \input  Dbl_slnHlaOut                                         = -10u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_Param1.nLimit[0]   = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_Param1.nLimit[1]   = -30
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 1u
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 1u
/// \output DblcCl_RetVal                                        = -40
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCl_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eLeftHandTraffic;
  Dbl_slnHlaOut                                     = -10;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]    = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]    = -30;

  //Step 3) Call FUT
  DblcCl_RetVal = DblcCl(DblcCl_Param1, DblcCl_Param2, DblcCl_Param3, DblcCl_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcCl_RetVal,                         -40, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCl_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function calculates head light angle 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 0u
/// \input  Rte_Read_SigPrep_HandTraffic_Port_Param1.eHandTraffic = 3u
/// \input  Dbl_slnHlaOut                                         = 10u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_Param1.nLimit[0]   = -20
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_Param1.nLimit[1]   = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 1u
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 1u
/// \output DblcCl_RetVal                                         = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCl_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = 3u;
  Dbl_slnHlaOut                                     = 10u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]    = -20;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]    = 0u;

  //Step 3) Call FUT
  DblcCl_RetVal = DblcCl(DblcCl_Param1, DblcCl_Param2, DblcCl_Param3, DblcCl_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcCl_RetVal,                          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCl_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function calculates head light angle 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 0u
/// \input  Rte_Read_SigPrep_HandTraffic_Port_Param1.eHandTraffic = 3u
/// \input  Dbl_slnHlaOut                                         = 10u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_Param1.nLimit[0]   = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_Param1.nLimit[1]   = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 1u
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 1u
/// \output DblcCl_RetVal                                        = 10u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCl_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = 3u;
  Dbl_slnHlaOut                                     = 10;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]    = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]    = 0u;

  //Step 3) Call FUT
  DblcCl_RetVal = DblcCl(DblcCl_Param1, DblcCl_Param2, DblcCl_Param3, DblcCl_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcCl_RetVal,                         10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCl_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function calculates head light angle 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 0u
/// \input  Rte_Read_SigPrep_HandTraffic_Port_Param1.eHandTraffic = 3u
/// \input  Dbl_slnHlaOut                                         = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_HandTraffic_Port_HitCount            = 1u
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount           = 1u
/// \output DblcCl_RetVal                                         = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCl_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = 3u;
  Dbl_slnHlaOut                                     = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 0u;

  //Step 3) Call FUT
  DblcCl_RetVal = DblcCl(DblcCl_Param1, DblcCl_Param2, DblcCl_Param3, DblcCl_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcCl_RetVal,                          0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCl
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates head light angle 
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCl(void)
{
  Mt_Dbl_DblcCl_TestCase_1();
  Mt_Dbl_DblcCl_TestCase_2();
  Mt_Dbl_DblcCl_TestCase_3();
  Mt_Dbl_DblcCl_TestCase_4();
  Mt_Dbl_DblcCl_TestCase_5();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcOutputContro
///
/// \Test Case Description
///        - Test subject: Test if function controls dynamic bending light output
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcOutputControl_Param1 = 100u
/// \input  DblcOutputControl_Param2 = 10u
///
/// - Expectations:
///
/// \output DblcOutputControl_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcOutputContro(void)
{
  //Step 1) Set pre-conditions
  DblcOutputControl_Param1 = 100u;
  DblcOutputControl_Param2 = 10u;

  //Step 3) Call FUT
  DblcOutputControl_RetVal = DblcOutputControl(DblcOutputControl_Param1, DblcOutputControl_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DblcOutputControl_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ConstHighSpeed_Detect_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function checks if vehicle is in constant speed interval
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  UtilDebounce_HitCount                                               = 0u
/// \input  UtilDebounce_Param1.eState                                          = Di_On (2u)
/// \input  UtilDebounce_Param2                                                 = FALSE
/// \input  Dbl_ConstHighSpeed_Detect_Param1                                    = 35u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.DBL_CONSTANT_SPEED_THRESHOLD_UPPER  = 15u
/// \input  Coding_Dummy.Dbl.DrivingSituationParam.ucConstMaxThr                = 55u
///
/// - Expectations:
///
/// \output UtilDebounce_HitCount                                               = 1u
/// \output UtilDebounce_Param2                                                 = TRUE
/// \output Dbl_sDriveSituation.Bit.bHighSpeed                                  = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ConstHighSpeed_Detect_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  UtilDebounce_HitCount                                              = 0u;
  UtilDebounce_Param1.eState                                         = Di_On;
  UtilDebounce_Param2                                                = FALSE;
  Dbl_ConstHighSpeed_Detect_Param1                                   = 35u;
  Coding_Dummy.Dbl.AFSPolySolver2.DBL_CONSTANT_SPEED_THRESHOLD_UPPER = 15u;
  Coding_Dummy.Dbl.DrivingSituationParam.ucConstMaxThr               = 55u;
  Dbl_sCodingParam.psCodingParameters_Blocks                         = &Coding_Dummy;

  //Step 3) Call FUT
  Dbl_ConstHighSpeed_Detect(Dbl_ConstHighSpeed_Detect_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilDebounce_HitCount,              1u, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param2,              TRUE, == );
  AL_UNITTEST_CHECK(Dbl_sDriveSituation.Bit.bHighSpeed, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ConstHighSpeed_Detect_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function checks if vehicle is in constant speed interval
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  UtilDebounce_HitCount                                               = 0u
/// \input  UtilDebounce_Param1.eState                                          = Di_OnDelay (1u)
/// \input  UtilDebounce_Param2                                                 = FALSE
/// \input  Dbl_sDriveSituation.Bit.bHighSpeed                                  = FALSE
/// \input  Dbl_ConstHighSpeed_Detect_Param1                                    = 35
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.DBL_CONSTANT_SPEED_THRESHOLD_UPPER  = 15u
/// \input  Coding_Dummy.Dbl.DrivingSituationParam.ucConstMaxThr                = 55u
///
/// - Expectations:
///
/// \output UtilDebounce_HitCount                                               = 1u
/// \output UtilDebounce_Param2                                                 = TRUE
/// \output Dbl_sDriveSituation.Bit.bHighSpeed                                  = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ConstHighSpeed_Detect_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  UtilDebounce_HitCount                                              = 0u;
  UtilDebounce_Param1.eState                                         = Di_OnDelay;
  UtilDebounce_Param2                                                = FALSE;
  Dbl_sDriveSituation.Bit.bHighSpeed                                 = FALSE;
  Dbl_ConstHighSpeed_Detect_Param1                                   = 35u;
  Coding_Dummy.Dbl.AFSPolySolver2.DBL_CONSTANT_SPEED_THRESHOLD_UPPER = 15u;
  Coding_Dummy.Dbl.DrivingSituationParam.ucConstMaxThr               = 55u;
  Dbl_sCodingParam.psCodingParameters_Blocks                         = &Coding_Dummy;

  //Step 3) Call FUT
  Dbl_ConstHighSpeed_Detect(Dbl_ConstHighSpeed_Detect_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilDebounce_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param2,                 TRUE, == );
  AL_UNITTEST_CHECK(Dbl_sDriveSituation.Bit.bHighSpeed, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ConstHighSpeed_Detect_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function checks if vehicle is in constant speed interval
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_HighSpeedTimer.eState                                           = Di_OnDelay (1u)
/// \input  Dbl_ConstHighSpeed_Detect_Param1                                    = 5
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.DBL_CONSTANT_SPEED_THRESHOLD_UPPER  = 15u
/// \input  Coding_Dummy.Dbl.DrivingSituationParam.ucConstMaxThr                = 55u
///
/// - Expectations:
///
/// \output Dbl_sDriveSituation.Bit.bHighSpeed                                  = FALSE
/// \output Dbl_HighSpeedTimer.eState                                           = Di_Sna (4u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ConstHighSpeed_Detect_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_HighSpeedTimer.eState                                          = Di_OnDelay;
  Dbl_ConstHighSpeed_Detect_Param1                                   = 5;
  Coding_Dummy.Dbl.AFSPolySolver2.DBL_CONSTANT_SPEED_THRESHOLD_UPPER = 15u;
  Coding_Dummy.Dbl.DrivingSituationParam.ucConstMaxThr               = 55u;
  Dbl_sCodingParam.psCodingParameters_Blocks                         = &Coding_Dummy;

  //Step 3) Call FUT
  Dbl_ConstHighSpeed_Detect(Dbl_ConstHighSpeed_Detect_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sDriveSituation.Bit.bHighSpeed, FALSE, == );
  AL_UNITTEST_CHECK(Dbl_HighSpeedTimer.eState,         Di_Sna, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ConstHighSpeed_Detect
///
///        - Test subject: Test if function checks if vehicle is in constant speed interval
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ConstHighSpeed_Detect(void)
{
  Mt_Dbl_ConstHighSpeed_Detect_TestCase_1();
  Mt_Dbl_ConstHighSpeed_Detect_TestCase_2();
  Mt_Dbl_ConstHighSpeed_Detect_TestCase_3();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_SetSteerbackDetection
///
/// \Test Case Description
///        - Test subject: Test if function sets Steerback Detection
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sDriveSituation.Bit.bSteerBack = 1u
/// \input  Dbl_SetSteerbackDetection_Param1   = FALSE
///
/// - Expectations:
///
/// \output Dbl_sDriveSituation.Bit.bSteerBack = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_SetSteerbackDetection(void)
{
  //Step 1) Set pre-conditions
  Dbl_sDriveSituation.Bit.bSteerBack = 1u;
  Dbl_SetSteerbackDetection_Param1   = FALSE;

  //Step 3) Call FUT
  Dbl_SetSteerbackDetection(Dbl_SetSteerbackDetection_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sDriveSituation.Bit.bSteerBack, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Mrad2MDeg
///
/// \Test Case Description
///        - Test subject: Test if function converts angle in 0.1 rad to 0.05 degree
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_Mrad2MDeg_Param1 = 10u
///
/// - Expectations:
///
/// \output Dbl_Mrad2MDeg_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Mrad2MDeg(void)
{
  //Step 1) Set pre-conditions
  Dbl_Mrad2MDeg_Param1 = 10u;

  //Step 3) Call FUT
  Dbl_Mrad2MDeg_RetVal = Dbl_Mrad2MDeg(Dbl_Mrad2MDeg_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Mrad2MDeg_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Call_StateNormal_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function performs do activity on normal operation
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Dbl_sSignal.nSpeed                                                                   = 10;
/// \input Dbl_sSignal.slCurvature                                                              = 10;
/// \input Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 10;
/// \input Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eLeftHandTraffic;
/// \input Dbl_slnHlaOut                                                                        = -1000;
/// \input Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]                                       = 0u;
/// \input Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]                                       = -30;
/// \input Rte_Read_SigPrep_DynamicSigs_HitCount                                                = 0u;
/// \input Rte_Read_AfsDbl_SwiRateLimMsg_HitCount                                               = 0u;
/// \input Order1Filter32_HitCount                                                              = 0u;
/// \input Order1Filter32_RetVal                                                                = 0u;
/// \input Dbl_eMountingSide                                                                     = eMountedRight;
/// \input Coding_Dummy.Dbl.DblAngleLimitations.ucHBS_HB_SWIVELING_ANGLE_MAX                     = 100;
/// \input Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                               = 6;
/// \input Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                              = 100;
/// \input Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                      = 10u;
/// \input Coding_Dummy.Dbl.AFSPolySolver2.ucV0                                                  = 10u;
/// \input Coding_Dummy.Dbl.AFSPolySolver2.ucV1                                                  = 10u;
/// \input Coding_Dummy.Dbl.AFSPolySolver2.ucV2                                                  = 10u;
/// \input Dbl_boHB                                                                              = TRUE;
///
/// - Expectations:
///
/// \output Dbl_snSwivelAngleLeft                             = 0
/// \output Dbl_snSwivelAngleRight                            = 0
/// \output Dbl_sMsgOut.SwivellingAngle[0].Hor                = 0
/// \output Dbl_sMsgOut.State                                 = 1u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount             = 3u
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 1u
/// \output Order1Filter32_HitCount                           = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Call_StateNormal_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_sSignal.nSpeed                                                                   = 10;
  Dbl_sSignal.slCurvature                                                              = 10;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 10;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eLeftHandTraffic;
  Dbl_slnHlaOut                                                                        = -1000;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]                                       = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]                                       = -30;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                                = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount                                               = 0u;
  Order1Filter32_HitCount                                                              = 0u;
  Order1Filter32_RetVal                                                                = 0u;
  Dbl_eMountingSide                                                                    = eMountedRight;
  Coding_Dummy.Dbl.DblAngleLimitations.ucHBS_HB_SWIVELING_ANGLE_MAX                    = 100;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                              = 10;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                              = 6;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                             = 100;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                     = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                                                 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV1                                                 = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV2                                                 = 10u;
  Dbl_boHB                                                                             = TRUE;

  //Step 3) Call FUT
  Dbl_Call_StateNormal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_snSwivelAngleLeft,                  0u, == );
  AL_UNITTEST_CHECK(Dbl_snSwivelAngleRight,                  0, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[0].Hor,      0, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.State,                      0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,  3u, == );
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Order1Filter32_HitCount,                1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Call_StateNormal_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function performs do activity on normal operation
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 1200u
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                          = SIG_VALID
/// \input  Dbl_boHB                                                                             = FALSE
/// \input  Dbl_eMountingSide                                                                    = 0u
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eTypeDir_SteeringLeft
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                                           = &Coding_Dummy
/// \input  LrRelation2_Param1                                                                   = 100u
/// \input  LrRelation2_Param2                                                                   = &LrRelation2_Param2_Dummy
/// \input  LrRelation2_Param3                                                                   = &LrRelation2_Param3_Dummy
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]               = 10u
/// \input  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                  = 100u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                              = 10u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                              = 100u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                             = 100u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                     = 10u
/// \input  Dbl_sSignal.nSpeed                                                                   = 10
/// \input  Dbl_sSignal.slCurvature                                                              = -1
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eLeftHandTraffic
/// \input  Coding_Dummy.Dbl.AfsHld.ucHlaFilterSize                                              = 10u
/// \input  Dbl_slnHlaOut                                                                        = -10
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]                                       = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]                                       = -30
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                                = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount                                               = 0u
/// \input  Order1Filter32_HitCount                                                              = 0u
/// \input  Order1Filter32_RetVal                                                                = 0u
/// \input  Dbl_eMountingSide                                                                    = eMountedLeft
///
/// - Expectations:
///
/// \output Dbl_snSwivelAngleLeft                             = 0u
/// \output Dbl_snSwivelAngleRight                            = 0u
/// \output Dbl_sMsgOut.SwivellingAngle[0].Hor                = 0u
/// \output Dbl_sMsgOut.State                                 = 1u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount             = 3u
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 1u
/// \output Order1Filter32_HitCount                           = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Call_StateNormal_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  sint32 LrRelation2_Param2_Dummy;
  sint32 LrRelation2_Param3_Dummy;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 1200u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                          = SIG_VALID;
  Dbl_boHB                                                                             = FALSE;
  Dbl_eMountingSide                                                                    = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eTypeDir_SteeringLeft;
  Dbl_sCodingParam.psCodingParameters_Blocks                                           = &Coding_Dummy;
  LrRelation2_Param1                                                                   = 100u;
  LrRelation2_Param2                                                                   = &LrRelation2_Param2_Dummy;
  LrRelation2_Param3                                                                   = &LrRelation2_Param3_Dummy;
  Coding_Dummy.Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[0]               = 10u;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT                  = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S0                                              = 10u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S1                                              = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2Angle.S12                                             = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucHeadLightAngle                                     = 10u;
  Dbl_sSignal.nSpeed                                                                   = 10;
  Dbl_sSignal.slCurvature                                                              = -1;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType                                    = eLeftHandTraffic;
  Coding_Dummy.Dbl.AfsHld.ucHlaFilterSize                                              = 10u;
  Dbl_slnHlaOut                                                                        = -10;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]                                       = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]                                       = -30;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                                = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount                                               = 0u;
  Order1Filter32_HitCount                                                              = 0u;
  Order1Filter32_RetVal                                                                = 0u;
  Dbl_eMountingSide                                                                    = eMountedLeft;

  //Step 3) Call FUT
  Dbl_Call_StateNormal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_snSwivelAngleLeft,                  0u, == );
  AL_UNITTEST_CHECK(Dbl_snSwivelAngleRight,                 0u, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[0].Hor,     0u, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.State,                      0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,  3u, == );
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Order1Filter32_HitCount,                1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Call_StateNormal
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function performs do activity on normal operation
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Call_StateNormal(void)
{
  Mt_Dbl_Call_StateNormal_TestCase_1();
  Mt_Dbl_Call_StateNormal_TestCase_2();
  Mt_Dbl_Call_StateNormal_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Call_StateNormal_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function performs do activity on normal operation
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sSignal.ucMotion                              = Motion_Backward
/// \input  Dbl_sSignal.nSpeed                                = 10
/// \input  Dbl_sSignal.slCurvature                           = -1
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eLeftHandTraffic
/// \input  Dbl_slnHlaOut                                     = -10
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]    = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]    = -30u
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 0u
/// \input  Order1Filter32_HitCount                           = 0u
/// \input  Order1Filter32_RetVal                             = 0u
/// \input  Dbl_eMountingSide                                 = eMountedLeft
///
/// - Expectations:
///
/// \output Dbl_snSwivelAngleLeft                             = 0u
/// \output Dbl_snSwivelAngleRight                            = 0u
/// \output Dbl_sMsgOut.SwivellingAngle[0].Hor                = 0u
/// \output Dbl_sMsgOut.State                                 = 3u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount             = 3u
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 1u
/// \output Order1Filter32_HitCount                           = 1u
/// \output Dbl_slnHlaOut                                     = -40
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Call_StateNormal_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sSignal.ucMotion                              = Motion_Backward;
  Dbl_sSignal.nSpeed                                = 10;
  Dbl_sSignal.slCurvature                           = 10;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eLeftHandTraffic;
  Dbl_slnHlaOut                                     = -10;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]    = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]    = -30u;
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount            = 0u;
  Order1Filter32_HitCount                           = 0u;
  Order1Filter32_RetVal                             = 0u;
  Dbl_eMountingSide                                 = eMountedLeft;

  //Step 3) Call FUT
  Dbl_Call_StateNormal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_snSwivelAngleLeft,                  0u, == );
  AL_UNITTEST_CHECK(Dbl_snSwivelAngleRight,                 0u, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[0].Hor,     0u, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.State,                      0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,  3u, == );
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Order1Filter32_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Dbl_slnHlaOut,                         -40, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Call_StateOff
///
/// \Test Case Description
///        - Test subject: Test if function performs StateOff processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor        = 11
/// \input  Dbl_sMsgOut.SwivellingAngle[eRight].Hor       = 15
/// \input  Dbl_sMsgOut.State                             = Dbl_eState_Nominal
/// \input  Dbl_slanHLAFilter[0..DBLC_HLAFILTERSIZE-1]    = 1
/// \input  Cl_Filter_Speed                               = 5
///
/// - Expectations:
///
/// \output  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor       = 0
/// \output  Dbl_sMsgOut.SwivellingAngle[eRight].Hor      = 0
/// \output  Dbl_sMsgOut.State                            = Dbl_eState_Init
/// \output  Dbl_slanHLAFilter[0..DBLC_HLAFILTERSIZE-1]   = 0
/// \output  Cl_Filter_Speed                              = 0
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Call_StateOff(void)
{
  //Step 1) Set pre-conditions
  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor  = 11;
  Dbl_sMsgOut.SwivellingAngle[eRight].Hor = 15;
  Dbl_sMsgOut.State                       = Dbl_eState_Nominal;
  Cl_Filter_Speed                         = 5;

  for (uint8 ucCounter = 0u; ucCounter < DBLC_HLAFILTERSIZE; ucCounter++)
  {
    Dbl_slanHLAFilter[ucCounter] = 1;
  }

  //Step 3) Call FUT
  Dbl_Call_StateOff();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eLeft].Hor,  0, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eRight].Hor, 0, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.State,      Dbl_eState_Nominal, == );
  AL_UNITTEST_CHECK(Cl_Filter_Speed,                         0, == );
  for (uint8 ucCounter = 0u; ucCounter < DBLC_HLAFILTERSIZE; ucCounter++)
  {
    AL_UNITTEST_CHECK(Dbl_slanHLAFilter[ucCounter], 0, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Call_StateHold
///
/// \Test Case Description
///        - Test subject: Test if function performs StateHold processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_Dbl_SwivellingOut_HitCount              = 0u
/// \input  Rte_Read_Dbl_SwivellingOut_Param1.SwivelAngle[0] = 55
/// \input  Rte_Read_Dbl_SwivellingOut_Param1.SwivelAngle[1] = 55
/// \input  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor           = 11
/// \input  Dbl_sMsgOut.SwivellingAngle[eRight].Hor          = 15
///
/// - Expectations:
///
/// \output  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor       = 55
/// \output  Dbl_sMsgOut.SwivellingAngle[eRight].Hor      = 55
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Call_StateHold(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_Dbl_SwivellingOut_HitCount              = 0u;
  Rte_Read_Dbl_SwivellingOut_Param1.SwivelAngle[0] = 55;
  Rte_Read_Dbl_SwivellingOut_Param1.SwivelAngle[1] = 55;
  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor           = 11;
  Dbl_sMsgOut.SwivellingAngle[eRight].Hor          = 15;

  //Step 3) Call FUT
  Dbl_Call_StateHold();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eLeft].Hor,  55, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eRight].Hor, 55, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StateMachine_StateInit
///
/// \Test Case Description
///        - Test subject: Test if function performs StateMachine_StateInit processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_Dbl_SwivellingOut_HitCount           = 0u
/// \input  Dbl_boErrorFromOtherHL                        = TRUE
/// \input  Dbl_boSwivelingFunctionalFault_LR             = TRUE
///
/// - Expectations:
///
/// \output  Rte_Read_Dbl_SwivellingOut_HitCount          = 1u
/// \output  Dbl_boErrorFromOtherHL                       = FALSE
/// \output  Dbl_boSwivelingFunctionalFault_LR            = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StateMachine_StateInit(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_Dbl_SwivellingOut_HitCount = 0u;
  Dbl_boErrorFromOtherHL              = TRUE;
  Dbl_boSwivelingFunctionalFault_LR   = TRUE;

  //Step 3) Call FUT
  Dbl_StateMachine_StateInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Dbl_SwivellingOut_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_boErrorFromOtherHL,           FALSE, == );
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StateMachine_StateNominal
///
/// \Test Case Description
///        - Test subject: Test if function performs StateMachine_StateNominal processing
///          Unit test for underlying function will be done separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input
///
/// - Expectations:
///
/// \output Dbl_sMsgOut.SwivellingAngle[eLeft].Hor = 0u
/// \output Dbl_sMsgOut.SwivellingAngle[eRight].Hor = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StateMachine_StateNominal(void)
{
  //Step 1) Set pre-conditions


  //Step 3) Call FUT
  Dbl_StateMachine_StateNominal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eLeft].Hor,  0u, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eRight].Hor, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StateMachine_StateFail_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function performs StateMachine_StateFail processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMountingSide                    = Dbl_eMountedLeft (0u)
/// \input  Dbl_boSwivelingFunctionalFault_LR    = TRUE
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StateMachine_StateFail_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMountingSide                 = Dbl_eMountedLeft;
  Dbl_boSwivelingFunctionalFault_LR = TRUE;

  //Step 3) Call FUT
  Dbl_StateMachine_StateFail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR, TRUE, == );
  AL_UNITTEST_CHECK(Dbl_boDYN_BENDING_BEAM_FAULT,      TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StateMachine_StateFail_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function performs StateMachine_StateFail processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMountingSide                    = Dbl_eMountedRight (1u)
/// \input  Dbl_boSwivelingFunctionalFault_LR    = TRUE
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StateMachine_StateFail_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMountingSide                 = Dbl_eMountedRight;
  Dbl_boSwivelingFunctionalFault_LR = TRUE;

  //Step 3) Call FUT
  Dbl_StateMachine_StateFail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StateMachine_StateFail_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function performs StateMachine_StateFail processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMountingSide                    = Dbl_eMountedLeft (0u)
/// \input  Dbl_boSwivelingFunctionalFault_LR    = TRUE
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StateMachine_StateFail_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMountingSide                 = Dbl_eMountedLeft;
  Dbl_boSwivelingFunctionalFault_LR = TRUE;
  Dbl_boL_Internal_Failure          = TRUE;

  //Step 3) Call FUT
  Dbl_StateMachine_StateFail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR, TRUE, == );
  AL_UNITTEST_CHECK(Dbl_boDYN_BENDING_BEAM_FAULT,      TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StateMachine_StateFail_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function performs StateMachine_StateFail processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMountingSide                    = Dbl_eMountedRight (1u)
/// \input  Dbl_boSwivelingFunctionalFault_LR    = TRUE
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StateMachine_StateFail_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMountingSide                 = Dbl_eMountedUndef;
  Dbl_boSwivelingFunctionalFault_LR = FALSE;

  //Step 3) Call FUT
  Dbl_StateMachine_StateFail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StateMachine_StateFail_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function performs StateMachine_StateFail processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMountingSide                    = Dbl_eMountedRight (1u)
/// \input  Dbl_boErrorFromOtherHL               = FALSE
/// \input  Dbl_boR_Internal_Failure             = TRUE
///
/// - Expectations:
///
/// \output Dbl_boErrorFromOtherHL    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StateMachine_StateFail_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMountingSide                 = Dbl_eMountedRight;
  Dbl_boErrorFromOtherHL            = FALSE;
  Dbl_boR_Internal_Failure          = TRUE;

  //Step 3) Call FUT
  Dbl_StateMachine_StateFail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boErrorFromOtherHL, TRUE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StateMachine_StateFail
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function performs StateMachine
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StateMachine_StateFail(void)
{
  Mt_Dbl_StateMachine_StateFail_TestCase_1();
  Mt_Dbl_StateMachine_StateFail_TestCase_2();
  Mt_Dbl_StateMachine_StateFail_TestCase_3();
  Mt_Dbl_StateMachine_StateFail_TestCase_4();
  Mt_Dbl_StateMachine_StateFail_TestCase_5();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StateMachine_StateAdj
///
/// \Test Case Description
///        - Test subject: Test if function performs StateMachine_StateAdj processing
///          Unit test for underlying function will be done separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input
///
/// - Expectations:
///
/// \output Dbl_sMsgOut.SwivellingAngle[eLeft].Hor = 
/// \output Dbl_sMsgOut.SwivellingAngle[eRight].Hor = 
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StateMachine_StateAdj(void)
{
  //Step 1) Set pre-conditions

  //Step 3) Call FUT
  Dbl_StateMachine_StateAdj();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eLeft].Hor,  0u, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eRight].Hor, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_SubModeFrozen
///
/// \Test Case Description
///        - Test subject: Test if function performs SubModeFrozen processing
///          Unit test for underlying function will be done separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input
///
/// - Expectations:
///
/// \output Dbl_sMsgOut.SwivellingAngle[eLeft].Hor  = 55u
/// \output Dbl_sMsgOut.SwivellingAngle[eRight].Hor = 55u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_SubModeFrozen(void)
{
  //Step 1) Set pre-conditions

  //Step 3) Call FUT
  Dbl_SubModeFrozen();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eLeft].Hor,  55u, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eRight].Hor, 55u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_SubModeUnavailable
///
/// \Test Case Description
///        - Test subject: Test if function performs SubModeUnavailable processing
///          Unit test for underlying function will be done separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input
///
/// - Expectations:
///
/// \output Dbl_sMsgOut.SwivellingAngle[eLeft].Hor = 
/// \output Dbl_sMsgOut.SwivellingAngle[eRight].Hor = 
///
//-----------------------------------------------------------------------------
void Mt_Dbl_SubModeUnavailable(void)
{
  //Step 1) Set pre-conditions

  //Step 3) Call FUT
  Dbl_SubModeUnavailable();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eLeft].Hor,  0u, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eRight].Hor, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_HbActive_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function performs HbActive processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_StdLgtFcts_Req_HitCount       = 0u
/// \input Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_INVALID (3u)
/// \input Rte_Read_SysMon_Afs_Signals_HitCount          = 0u
/// \input Rte_Read_SysMon_Afs_Signals_Param1.eSigQty    = SIG_VALID (1u)
/// \input Rte_Read_SysMon_Afs_Signals_Param1.eGfhb_Cmd  = eGfhbCmd_On (2u)
/// \input Dbl_boHB                                      = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount      = 2u
/// \output Rte_Read_SysMon_Afs_Signals_HitCount         = 1u
/// \output Dbl_boHB                                     = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_HbActive_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount           = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request = TRUE;
  Rte_Read_SysMon_Afs_Signals_HitCount              = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty        = SIG_VALID;
  Rte_Read_SysMon_Afs_Signals_Param1.eGfhb_Cmd      = eGfhbCmd_On;
  Coding_Dummy.Dbl.DblDiversity.ucTYPE_ECL_VIR_DYN  = Dbl_eAUC_02;
  Dbl_sCodingParam.psCodingParameters_Blocks        = &Coding_Dummy;
  Dbl_boHB                                          = FALSE;

  //Step 3) Call FUT
  Dbl_HbActive();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Dbl_boHB,                              TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_HbActive_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function performs HbActive processing
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_StdLgtFcts_Req_HitCount       = 0u
/// \input Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_INVALID (3u)
/// \input Rte_Read_SysMon_Afs_Signals_HitCount          = 0u
/// \input Rte_Read_SysMon_Afs_Signals_Param1.eSigQty    = SIG_INVALID (3u)
/// \input Dbl_boHB                                      = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount      = 2u
/// \output Rte_Read_SysMon_Afs_Signals_HitCount         = 1u
/// \output Dbl_boHB                                     = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_HbActive_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount       = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_INVALID;
  Rte_Read_SysMon_Afs_Signals_HitCount          = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty    = SIG_INVALID;
  Dbl_boHB                                      = FALSE;

  //Step 3) Call FUT
  Dbl_HbActive();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Dbl_boHB,                             FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_HbActive
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function performs HbActive processing
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_HbActive(void)
{
  Mt_Dbl_HbActive_TestCase_1();
  Mt_Dbl_HbActive_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Write_OutputValues_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function writes the Output Values
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Rte_Write_Dbl_SwivellingOut_HitCount                                        = 0u
/// \input Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle                              = 0
/// \input Rte_Write_Dbl_SwivellingOut_Param1.DblState                                 = eState_Init (0u)
/// \input Rte_Write_Dbl_Mode_HitCount                                                 = 0u
/// \input Rte_Write_Dbl_Mode_Param1                                                   = eSubModeUnavailable (0u)
/// \input Rte_Write_Dbl_SysMonTx_FullStatus_HitCount                                  = 0u
/// \input Rte_Write_Dbl_SysMonTx_FullStatus_Param1.eDynamicBendingBeamFault           = eDiagDbl_Ok (0u)
/// \input Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount                                 = 0u
/// \input Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1.eDynBendingBeamFault              = eDynBendingBeamFault_False (0u)
/// \input Dbl_sSignal.slCurvature                                                     = -1
/// \input Dbl_sMsgOut.SwivellingAngle[eMountedLeft].Hor                               = 1
/// \input Dbl_sMsgOut.SwivellingAngle[eMountedRight].Hor                              = 1
/// \input Dbl_sState.eMain                                                            = Dbl_eState_Nominal (1u)
/// \input Dbl_eMountingSide                                                           = Dbl_eMountedLeft (0u)
/// \input Dbl_eSubMode                                                                = Dbl_eSubModeAvailable (1u)
/// \input Dbl_boSwivelingFunctionalFault_LR                                           = TRUE
/// \input Dbl_boErrorFromOtherHL                                                      = TRUE
/// \input Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION = 100u
/// \input Dbl_sCurvatureData.ucCurvatureMode                                          = DBLSM_DBL_DISABLED

///
/// - Expectations:
///
/// \output Rte_Write_Dbl_SwivellingOut_HitCount                                       = 1u
/// \output Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle                             = 5
/// \output Rte_Write_Dbl_SwivellingOut_Param1.DblState                                = eState_Nominal (1u)
/// \output Rte_Write_Dbl_Mode_HitCount                                                = 1u
/// \output Rte_Write_Dbl_Mode_Param1                                                  = eSubModeAvailable (1u)
/// \output Rte_Write_Dbl_SysMonTx_FullStatus_HitCount                                 = 1u
/// \output Rte_Write_Dbl_SysMonTx_FullStatus_Param1.eDynamicBendingBeamFault          = eDiagDbl_Nok (1u)
/// \output Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount                                = 1u
/// \output Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1.eDynBendingBeamFault             = eDynBendingBeamFault_True (1u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Write_OutputValues_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Write_Dbl_SwivellingOut_HitCount                                        = 0u;
  Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[0]                           = 0;
  Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[1]                           = 0;
  Rte_Write_Dbl_SwivellingOut_Param1.DblState                                 = eState_Init;
  Rte_Write_Dbl_Mode_HitCount                                                 = 0u;
  Rte_Write_Dbl_Mode_Param1                                                   = eSubModeUnavailable;
  Rte_Write_Dbl_SysMonTx_FullStatus_HitCount                                  = 0u;
  Rte_Write_Dbl_SysMonTx_FullStatus_Param1.eDynamicBendingBeamFault           = eDiagDbl_Ok;
  Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount                                 = 0u;
  Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1.eDynBendingBeamFault              = eDynBendingBeamFault_False;
  Dbl_sSignal.slCurvature                                                     = -1;
  Dbl_sMsgOut.SwivellingAngle[eMountedLeft].Hor                               = 1;
  Dbl_sMsgOut.SwivellingAngle[eMountedRight].Hor                              = 1;
  Dbl_sState.eMain                                                            = Dbl_eState_Nominal;
  Dbl_eMountingSide                                                           = Dbl_eMountedLeft;
  Dbl_eSubMode                                                                = Dbl_eSubModeAvailable;
  Dbl_boSwivelingFunctionalFault_LR                                           = TRUE;
  Dbl_boErrorFromOtherHL                                                      = TRUE;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION = 100u;
  Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
  Dbl_sCurvatureData.ucCurvatureMode                                          = DBLSM_DBL_DISABLED;

  //Step 3) Call FUT
  Dbl_Write_OutputValues();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_HitCount,                                                  1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[0],                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[1],                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.DblState,                               eState_Nominal, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_Mode_HitCount,                                                           1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_Mode_Param1,                                              eSubModeAvailable, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SysMonTx_FullStatus_HitCount,                                            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SysMonTx_FullStatus_Param1.eDynamicBendingBeamFault,           eDiagDbl_Nok, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount,                                           1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1.eDynBendingBeamFault, eDynBendingBeamFault_True, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Write_OutputValues_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function writes the Output Values
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Rte_Write_Dbl_SwivellingOut_HitCount                                        = 0u
/// \input Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle                              = 0
/// \input Rte_Write_Dbl_SwivellingOut_Param1.DblState                                 = eState_Init (0u)
/// \input Rte_Write_Dbl_Mode_HitCount                                                 = 0u
/// \input Rte_Write_Dbl_Mode_Param1                                                   = eSubModeUnavailable (0u)
/// \input Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                                = 0u
/// \input Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault             = eDynBendingBeamFault_False (0u)
/// \input Dbl_sSignal.slCurvature                                                     = 1
/// \input Dbl_sMsgOut.SwivellingAngle[eMountedLeft].Hor                               = 1
/// \input Dbl_sMsgOut.SwivellingAngle[eMountedRight].Hor                              = 1
/// \input Dbl_sState.eMain                                                            = Dbl_eState_Nominal (1u)
/// \input Dbl_eMountingSide                                                           = Dbl_eMountedRight (1u)
/// \input Dbl_eSubMode                                                                = Dbl_eSubModeAvailable (1u)
/// \input Dbl_boErrorFromOtherHL                                                      = TRUE
/// \input Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION = 100u
/// \input  Dbl_sCurvatureData.ucDblEnable                                             = 1
///
/// - Expectations:
///
/// \output Rte_Write_Dbl_SwivellingOut_HitCount                                       = 1u
/// \output Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle                             = 5
/// \output Rte_Write_Dbl_SwivellingOut_Param1.DblState                                = eState_Nominal (1u)
/// \output Rte_Write_Dbl_Mode_HitCount                                                = 1u
/// \output Rte_Write_Dbl_Mode_Param1                                                  = eSubModeAvailable (1u)
/// \output Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                               = 1u
/// \output Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault            = eDynBendingBeamFault_True (1u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Write_OutputValues_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Write_Dbl_SwivellingOut_HitCount                                        = 0u;
  Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[0]                           = 0;
  Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[1]                           = 0;
  Rte_Write_Dbl_SwivellingOut_Param1.DblState                                 = eState_Init;
  Rte_Write_Dbl_Mode_HitCount                                                 = 0u;
  Rte_Write_Dbl_Mode_Param1                                                   = eSubModeUnavailable;
  Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                                = 0u;
  Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault             = eDynBendingBeamFault_False;
  Dbl_sSignal.slCurvature                                                     = 1;
  Dbl_sMsgOut.SwivellingAngle[eMountedLeft].Hor                               = 1;
  Dbl_sMsgOut.SwivellingAngle[eMountedRight].Hor                              = 1;
  Dbl_sState.eMain                                                            = Dbl_eState_Nominal;
  Dbl_eMountingSide                                                           = Dbl_eMountedRight;
  Dbl_eSubMode                                                                = Dbl_eSubModeAvailable;
  Dbl_boErrorFromOtherHL                                                      = TRUE;
  Coding_Dummy.Dbl.DblAngleLimitations.ucDBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION = 100u;
  Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
  Dbl_sCurvatureData.ucDblEnable                                              = 1;
  //Step 3) Call FUT
  Dbl_Write_OutputValues();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_HitCount,                                                   1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[0],                                      1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[1],                                      1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.DblState,                                eState_Nominal, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_Mode_HitCount,                                                            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_Mode_Param1,                                               eSubModeAvailable, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount,                                           1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault, eDynBendingBeamFault_True, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Write_OutputValues_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function writes the Output Values
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Rte_Write_Dbl_SwivellingOut_HitCount                                        = 0u
/// \input Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle                              = 0
/// \input Rte_Write_Dbl_SwivellingOut_Param1.DblState                                 = eState_Init (0u)
/// \input Rte_Write_Dbl_Mode_HitCount                                                 = 0u
/// \input Rte_Write_Dbl_Mode_Param1                                                   = eSubModeUnavailable (0u)
/// \input Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                                = 0u
/// \input Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault             = eDynBendingBeamFault_False (0u)
/// \input Dbl_sSignal.slCurvature                                                     = 0
/// \input Dbl_sMsgOut.SwivellingAngle[eMountedLeft].Hor                               = 1
/// \input Dbl_sMsgOut.SwivellingAngle[eMountedRight].Hor                              = 1
/// \input Dbl_sState.eMain                                                            = Dbl_eState_Nominal (1u)
/// \input Dbl_eMountingSide                                                           = Dbl_eMountedRight (1u)
/// \input Dbl_eSubMode                                                                = Dbl_eSubModeAvailable (1u)
/// \input Dbl_boErrorFromOtherHL                                                      = TRUE
///
/// - Expectations:
///
/// \output Rte_Write_Dbl_SwivellingOut_HitCount                                       = 1u
/// \output Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle                             = 1
/// \output Rte_Write_Dbl_SwivellingOut_Param1.DblState                                = eState_Nominal (1u)
/// \output Rte_Write_Dbl_Mode_HitCount                                                = 1u
/// \output Rte_Write_Dbl_Mode_Param1                                                  = eSubModeAvailable (1u)
/// \output Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                               = 1u
/// \output Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault            = eDynBendingBeamFault_True (1u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Write_OutputValues_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Write_Dbl_SwivellingOut_HitCount                            = 0u;
  Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[0]               = 0;
  Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[1]               = 0;
  Rte_Write_Dbl_SwivellingOut_Param1.DblState                     = eState_Init;
  Rte_Write_Dbl_Mode_HitCount                                     = 0u;
  Rte_Write_Dbl_Mode_Param1                                       = eSubModeUnavailable;
  Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                    = 0u;
  Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_False;
  Dbl_sSignal.slCurvature                                         = 0;
  Dbl_sMsgOut.SwivellingAngle[eMountedLeft].Hor                   = 1;
  Dbl_sMsgOut.SwivellingAngle[eMountedRight].Hor                  = 1;
  Dbl_sState.eMain                                                = Dbl_eState_Nominal;
  Dbl_eMountingSide                                               = Dbl_eMountedRight;
  Dbl_eSubMode                                                    = Dbl_eSubModeAvailable;
  Dbl_boErrorFromOtherHL                                          = TRUE;

  //Step 3) Call FUT
  Dbl_Write_OutputValues();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_HitCount,                                                  1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[0],                                      1, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[1],                                      1, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.DblState,                               eState_Nominal, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_Mode_HitCount,                                                            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_Mode_Param1,                                               eSubModeAvailable, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount,                                           1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault, eDynBendingBeamFault_True, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Write_OutputValues
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function writes the Output Values
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Write_OutputValues(void)
{
  Mt_Dbl_Write_OutputValues_TestCase_1();
  Mt_Dbl_Write_OutputValues_TestCase_2();
  Mt_Dbl_Write_OutputValues_TestCase_3();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_GetTimer
///
/// \Test Case Description
///        - Test subject: Test if function returns the address of the timer
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sSwivelBckTimer.eState  = 1u
///
/// - Expectations:
///
/// \output Dbl_GetTimer_RetVal->eState = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_GetTimer(void)
{
  //Step 1) Set pre-conditions
  Dbl_sSwivelBckTimer.eState = 1u;

  //Step 3) Call FUT
  Dbl_GetTimer_RetVal = Dbl_GetTimer();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_GetTimer_RetVal->eState, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleSignal_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function returns the idle curvature signal
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleSignal_Param1 = -1
/// \input  ClIdleSignal_Param2 = 2u
///
/// - Expectations:
///
/// \output ClIdleSignal_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleSignal_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  ClIdleSignal_Param1 = -1;
  ClIdleSignal_Param2 = 2u;

  //Step 3) Call FUT
  ClIdleSignal_RetVal = ClIdleSignal(ClIdleSignal_Param1, ClIdleSignal_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleSignal_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleSignal_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function returns the idle curvature signal
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleSignal_Param1 = 1u
/// \input  ClIdleSignal_Param2 = 0u
///
/// - Expectations:
///
/// \output ClIdleSignal_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleSignal_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  ClIdleSignal_Param1 = 1u;
  ClIdleSignal_Param2 = 0u;

  //Step 3) Call FUT
  ClIdleSignal_RetVal = ClIdleSignal(ClIdleSignal_Param1, ClIdleSignal_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleSignal_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleSignal
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function returns the idle curvature signal
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleSignal(void)
{
  Mt_Dbl_ClIdleSignal_TestCase_1();
  Mt_Dbl_ClIdleSignal_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Time2Inc
///
/// \Test Case Description
///        - Test subject: Test if function makes the time convertion to 
///                        increments per 20ms calculation
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Time2Inc_Param1 = 1u
///
/// - Expectations:
///
/// \output Time2Inc_RetVal = 5u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Time2Inc(void)
{
  //Step 1) Set pre-conditions
  Time2Inc_Param1 = 1u;

  //Step 3) Call FUT
  Time2Inc_RetVal = Time2Inc(Time2Inc_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Time2Inc_RetVal, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Time2Step_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function makes the time convertion to
///                        increment per 20ms in order to reach target in time
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Time2Step_Param1 = 1u
/// \input  Time2Step_Param2 = 1u
///
/// - Expectations:
///
/// \output Time2Step_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Time2Step_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Time2Step_Param1 = 1u;
  Time2Step_Param2 = 1u;

  //Step 3) Call FUT
  Time2Step_RetVal = Time2Step(Time2Step_Param1, Time2Step_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Time2Step_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Time2Step_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function makes the time convertion to
///                        increment per 20ms in order to reach target in time
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Time2Step_Param1 = 0u
/// \input  Time2Step_Param2 = 1u
///
/// - Expectations:
///
/// \output Time2Step_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Time2Step_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Time2Step_Param1 = 0u;
  Time2Step_Param2 = 1u;

  //Step 3) Call FUT
  Time2Step_RetVal = Time2Step(Time2Step_Param1, Time2Step_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Time2Step_RetVal, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Time2Step
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function makes the time convertion
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Time2Step(void)
{
  Mt_Dbl_Time2Step_TestCase_1();
  Mt_Dbl_Time2Step_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                   = &Coding_Dummy;
/// \input  ClIdleRange_Param1                                           = 10;
/// \input  ClIdleRange_Param2                                           = -1;
/// \input  ClIdleRange_Param3                                           = -1;
/// \input  ClIdleRange_Param4                                           = -1;
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 2u;
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange0[0]           = 0u;
///
/// - Expectations:
///
/// \output ClIdleRange_RetVal                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks                   = &Coding_Dummy;
  ClIdleRange_Param1                                           = 10;
  ClIdleRange_Param2                                           = -1;
  ClIdleRange_Param3                                           = -1;
  ClIdleRange_Param4                                           = -1;
  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 2u;
  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange0[0]           = 0u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleRange_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                = 10u
/// \input  ClIdleRange_Param2                                = 3u
/// \input  ClIdleRange_Param3                                = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange1[0] = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 0u
///
/// - Expectations:
///
/// \output ClIdleRange_RetVal                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10;
  ClIdleRange_Param2                                 = 3u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucIdleRange1[0]           = 2u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleRange_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                = 10u
/// \input  ClIdleRange_Param2                                = -3u
/// \input  ClIdleRange_Param3                                = -1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange1[0] = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 0u
///
/// - Expectations:
///
/// \output ClIdleRange_RetVal                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10;
  ClIdleRange_Param2                                 = -3;
  ClIdleRange_Param3                                 = -1;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucIdleRange1[0]           = 2u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleRange_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                = 10u
/// \input  ClIdleRange_Param2                                = 1u
/// \input  ClIdleRange_Param3                                = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange1[0] = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 2u
///
/// - Expectations:
///
/// \output ClIdleRange_RetVal                                = 200u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10;
  ClIdleRange_Param2                                 = 1u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucIdleRange1[1]           = 2u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 2u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleRange_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                = 10
/// \input  ClIdleRange_Param2                                = 1u
/// \input  ClIdleRange_Param3                                = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange1[1] = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 0u
///
/// - Expectations:
///
/// \output ClIdleRange_RetVal                               = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10;
  ClIdleRange_Param2                                 = 1;
  ClIdleRange_Param3                                 = 1;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 0;
  Coding_Dummy.Dbl.AfsIdle.ucIdleRange1[1]           = 2;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleRange_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                 = 10
/// \input  ClIdleRange_Param2                                 = 1u
/// \input  ClIdleRange_Param3                                 = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 2u
/// \input  LinEquSolver_HitCount                              = 0u
/// \input  LinEquCalculator_HitCount                          = 0u
/// \input  LinEquCalculator_RetVal                            = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange1[1] = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 0u
///
/// - Expectations:
///
/// \output LinEquSolver_HitCount                             = 1u
/// \output LinEquCalculator_HitCount                         = 1u
/// \output ClIdleRange_RetVal                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10;
  ClIdleRange_Param2                                 = 1u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 2u;
  LinEquSolver_HitCount                              = 0u;
  LinEquCalculator_HitCount                          = 0u;
  LinEquCalculator_RetVal                            = 2u;
  Coding_Dummy.Dbl.AfsIdle.ucIdleRange1[1]           = 2u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LinEquSolver_HitCount,     1u, == );
  AL_UNITTEST_CHECK(LinEquCalculator_HitCount, 1u, == );
  AL_UNITTEST_CHECK(ClIdleRange_RetVal,        0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                 = 10u
/// \input  ClIdleRange_Param2                                 = 300u
/// \input  ClIdleRange_Param3                                 = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange1[1] = 200u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOffTime       = 1u
///
/// - Expectations:
///
/// \output ClIdleRange_RetVal                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10u;
  ClIdleRange_Param2                                 = 300u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucIdleRange1[1]           = 200u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucOffTime                 = 1u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleRange_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                = 10u
/// \input  ClIdleRange_Param2                                = 1u
/// \input  ClIdleRange_Param3                                = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange1[1] = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 0u
///
/// - Expectations:
///
/// \output ClIdleRange_RetVal                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_8(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10u;
  ClIdleRange_Param2                                 = 1u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucIdleRange1[1]           = 2u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleRange_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_9
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                 = 10u
/// \input  ClIdleRange_Param2                                 = 200u
/// \input  ClIdleRange_Param3                                 = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 2u
/// \input  LinEquSolver_HitCount                              = 0u
/// \input  LinEquCalculator_HitCount                          = 0u
/// \input  LinEquCalculator_RetVal                            = -100u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOffTime       = 1u
///
/// - Expectations:
///
/// \output LinEquSolver_HitCount                             = 1u
/// \output LinEquCalculator_HitCount                         = 1u
/// \output ClIdleRange_RetVal                                = 20
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_9(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10u;
  ClIdleRange_Param2                                 = 200u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 2u;
  LinEquSolver_HitCount                              = 0u;
  LinEquCalculator_HitCount                          = 0u;
  LinEquCalculator_RetVal                            = -100u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucOffTime                 = 1u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LinEquSolver_HitCount,     1u, == );  
  AL_UNITTEST_CHECK(LinEquCalculator_HitCount, 1u, == );
  AL_UNITTEST_CHECK(ClIdleRange_RetVal,        20, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_10
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                = 10u
/// \input  ClIdleRange_Param2                                = 200u
/// \input  ClIdleRange_Param3                                = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 2u
/// \input  LinEquSolver_HitCount                             = 0u
/// \input  LinEquCalculator_HitCount                         = 0u
/// \input  LinEquCalculator_RetVal                           = -100u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOffTime       = 1u
///
/// - Expectations:
///
/// \output LinEquSolver_HitCount     = 1u
/// \output LinEquCalculator_HitCount = 1u
/// \output ClIdleRange_RetVal        = 40
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_10(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10u;
  ClIdleRange_Param2                                 = 200u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 2u;
  LinEquSolver_HitCount                              = 0u;
  LinEquCalculator_HitCount                          = 0u;
  LinEquCalculator_RetVal                            = -100u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucOffTime                 = 1u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LinEquSolver_HitCount,     1u, == );
  AL_UNITTEST_CHECK(LinEquCalculator_HitCount, 1u, == );
  AL_UNITTEST_CHECK(ClIdleRange_RetVal,        40, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_11
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                          = 10u
/// \input  ClIdleRange_Param2                          = 200u
/// \input  ClIdleRange_Param3                          = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1      = 2u
/// \input  LinEquSolver_HitCount                       = 0u
/// \input  LinEquCalculator_HitCount                   = 0u
/// \input  LinEquCalculator_RetVal                     = 210u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOffTime = 1u
///
/// - Expectations:
///
/// \output LinEquSolver_HitCount                       = 1u
/// \output LinEquCalculator_HitCount                   = 1u
/// \output ClIdleRange_RetVal                          = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_11(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10u;
  ClIdleRange_Param2                                 = 200u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 2u;
  LinEquSolver_HitCount                              = 0u;
  LinEquCalculator_HitCount                          = 0u;
  LinEquCalculator_RetVal                            = 210;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucOffTime                 = 1u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LinEquSolver_HitCount,     1u, == );  
  AL_UNITTEST_CHECK(LinEquCalculator_HitCount, 1u, == );
  AL_UNITTEST_CHECK(ClIdleRange_RetVal,         0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_12
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                                = 10u
/// \input  ClIdleRange_Param2                                = 1u
/// \input  ClIdleRange_Param3                                = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1            = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucIdleRange1[1] = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay       = 0u
///
/// - Expectations:
///
/// \output ClIdleRange_RetVal                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_12(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10u;
  ClIdleRange_Param2                                 = 1u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucIdleRange1[1]           = 2u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ClIdleRange_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_13
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                          = 10u
/// \input  ClIdleRange_Param2                          = 0u
/// \input  ClIdleRange_Param3                          = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1      = 2u
/// \input  LinEquSolver_HitCount                       = 0u
/// \input  LinEquCalculator_HitCount                   = 0u
/// \input  LinEquCalculator_RetVal                     = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOffTime = 1u
///
/// - Expectations:
///
/// \output LinEquSolver_HitCount                       = 1u
/// \output LinEquCalculator_HitCount                   = 1u
/// \output ClIdleRange_RetVal                          = 1i
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_13(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10;
  ClIdleRange_Param2                                 = 0;
  ClIdleRange_Param3                                 = 1;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 2;
  LinEquSolver_HitCount                              = 0u;
  LinEquCalculator_HitCount                          = 0u;
  LinEquCalculator_RetVal                            = 1;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucOffTime                 = 1;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LinEquSolver_HitCount,     1u, == );
  AL_UNITTEST_CHECK(LinEquCalculator_HitCount, 1u, == );
  AL_UNITTEST_CHECK(ClIdleRange_RetVal,         1, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_14
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                          = 10i
/// \input  ClIdleRange_Param2                          = 0u
/// \input  ClIdleRange_Param3                          = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1      = 2u
/// \input  LinEquSolver_HitCount                       = 0u
/// \input  LinEquCalculator_HitCount                   = 0u
/// \input  LinEquCalculator_RetVal                     = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOffTime = 1u
///
/// - Expectations:
///
/// \output LinEquSolver_HitCount                       = 1u
/// \output LinEquCalculator_HitCount                   = 1u
/// \output ClIdleRange_RetVal                          = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_14(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10u;
  ClIdleRange_Param2                                 = 0u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 2u;
  LinEquSolver_HitCount                              = 0u;
  LinEquCalculator_HitCount                          = 0u;
  LinEquCalculator_RetVal                            = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucOffTime                 = 1u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LinEquSolver_HitCount,     1u, == );
  AL_UNITTEST_CHECK(LinEquCalculator_HitCount, 1u, == );
  AL_UNITTEST_CHECK(ClIdleRange_RetVal,         1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange_TestCase_15
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///                        in dependency of vehicle speed
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  ClIdleRange_Param1                          = 10u
/// \input  ClIdleRange_Param2                          = 2u
/// \input  ClIdleRange_Param3                          = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV0      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucV1      = 2u
/// \input  LinEquSolver_HitCount                       = 0u
/// \input  LinEquCalculator_HitCount                   = 0u
/// \input  LinEquCalculator_RetVal                     = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOnDelay = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsIdle.ucOffTime = 0u
///
/// - Expectations:
///
/// \output LinEquSolver_HitCount                       = 1u
/// \output LinEquCalculator_HitCount                   = 1u
/// \output ClIdleRange_RetVal                          = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange_TestCase_15(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  ClIdleRange_Param1                                 = 10u;
  ClIdleRange_Param2                                 = 2u;
  ClIdleRange_Param3                                 = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 2u;
  LinEquSolver_HitCount                              = 0u;
  LinEquCalculator_HitCount                          = 0u;
  LinEquCalculator_RetVal                            = 1u;
  Coding_Dummy.Dbl.AfsIdle.ucOnDelay                 = 0u;
  Coding_Dummy.Dbl.AfsIdle.ucOffTime                 = 1u;

  //Step 3) Call FUT
  ClIdleRange_RetVal = ClIdleRange(ClIdleRange_Param1, ClIdleRange_Param2, ClIdleRange_Param3, ClIdleRange_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LinEquSolver_HitCount,     1u, == );
  AL_UNITTEST_CHECK(LinEquCalculator_HitCount, 1u, == );
  AL_UNITTEST_CHECK(ClIdleRange_RetVal,         0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ClIdleRange(void)
{
 Mt_Dbl_ClIdleRange_TestCase_1();
 Mt_Dbl_ClIdleRange_TestCase_2();
 Mt_Dbl_ClIdleRange_TestCase_3();
 Mt_Dbl_ClIdleRange_TestCase_4();
 Mt_Dbl_ClIdleRange_TestCase_6();
 Mt_Dbl_ClIdleRange_TestCase_5();
 Mt_Dbl_ClIdleRange_TestCase_7();
 Mt_Dbl_ClIdleRange_TestCase_8();
 Mt_Dbl_ClIdleRange_TestCase_9();
 Mt_Dbl_ClIdleRange_TestCase_10();
 Mt_Dbl_ClIdleRange_TestCase_11();
 Mt_Dbl_ClIdleRange_TestCase_12();
 Mt_Dbl_ClIdleRange_TestCase_13();
 Mt_Dbl_ClIdleRange_TestCase_14();
 Mt_Dbl_ClIdleRange_TestCase_15();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_CalcIdleRange_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates the idle range
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  CalcIdleRange_Param1           = 19u
/// \input  CalcIdleRange_Param2           = 20u
/// \input  CalcIdleRange_Param3           = 20u
///
/// - Expectations:
///
/// \output CalcIdleRange_RetVal  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_CalcIdleRange_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  CalcIdleRange_Param1 = 19u;
  CalcIdleRange_Param2 = 20u;
  CalcIdleRange_Param3 = 20u;

  //Step 3) Call FUT
  CalcIdleRange_RetVal = CalcIdleRange(CalcIdleRange_Param1, CalcIdleRange_Param2, CalcIdleRange_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CalcIdleRange_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_CalcIdleRange_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates the idle range
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks             = &Coding_Dummy;
/// \input  CalcIdleRange_Param1                                   = 21u;
/// \input  CalcIdleRange_Param2                                   = 20u;
/// \input  CalcIdleRange_Param3                                   = 20u;
/// \input  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed     = 22u;
///
/// - Expectations:
///
/// \output CalcIdleRange_RetVal  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_CalcIdleRange_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  CalcIdleRange_Param1                               = 21u;
  CalcIdleRange_Param2                               = 20u;
  CalcIdleRange_Param3                               = 20u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 22u;
 
  //Step 3) Call FUT
  CalcIdleRange_RetVal = CalcIdleRange(CalcIdleRange_Param1, CalcIdleRange_Param2, CalcIdleRange_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CalcIdleRange_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_CalcIdleRange_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function calculates the idle range
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks               = &Coding_Dummy;
/// \input  CalcIdleRange_Param1                                     = 55u;
/// \input  CalcIdleRange_Param2                                     = 20u;
/// \input  CalcIdleRange_Param3                                     = 20u;
/// \input  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed       = 22u;
/// \input  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed       = 62u;
///
/// - Expectations:
///
/// \output CalcIdleRange_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_CalcIdleRange_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks         = &Coding_Dummy;
  CalcIdleRange_Param1                               = 55u;
  CalcIdleRange_Param2                               = 20u;
  CalcIdleRange_Param3                               = 20u;
  Coding_Dummy.Dbl.AfsIdle.ucV0_straight_ahead_speed = 22u;
  Coding_Dummy.Dbl.AfsIdle.ucV1_straight_ahead_speed = 62u;

  //Step 3) Call FUT
  CalcIdleRange_RetVal = CalcIdleRange(CalcIdleRange_Param1, CalcIdleRange_Param2, CalcIdleRange_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CalcIdleRange_RetVal, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_CalcIdleRange
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_CalcIdleRange(void)
{
  Mt_Dbl_CalcIdleRange_TestCase_1();
  Mt_Dbl_CalcIdleRange_TestCase_2();
  Mt_Dbl_CalcIdleRange_TestCase_3();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_DblDblc_Convert_Deg_mRad_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates swiveling rates
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dblc_Convert_Deg_mRad_Param1 = 2u
///
/// - Expectations:
///
/// \output Dblc_Convert_Deg_mRad_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_DblDblc_Convert_Deg_mRad(void)
{
  //Step 1) Set pre-conditions
  Dblc_Convert_Deg_mRad_Param1 = 2u;

  //Step 3) Call FUT
  Dblc_Convert_Deg_mRad_RetVal = Dblc_Convert_Deg_mRad(Dblc_Convert_Deg_mRad_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dblc_Convert_Deg_mRad_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Dblc_Convert_Deg_mRadHr_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function calculates swiveling rates
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dblc_Convert_Deg_mRadHr_Param1 = 0u
///
/// - Expectations:
///
/// \output Dblc_Convert_Deg_mRad_RetVal   = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Dblc_Convert_Deg_mRadHr_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dblc_Convert_Deg_mRadHr_Param1 = 0u;

  //Step 3) Call FUT
  Dblc_Convert_Deg_mRadHr_RetVal = Dblc_Convert_Deg_mRadHr(Dblc_Convert_Deg_mRadHr_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dblc_Convert_Deg_mRad_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Dblc_Convert_Deg_mRadHr_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function calculates swiveling rates
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dblc_Convert_Deg_mRadHr_Param1 = 2u
///
/// - Expectations:
///
/// \output Dblc_Convert_Deg_mRad_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Dblc_Convert_Deg_mRadHr_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dblc_Convert_Deg_mRadHr_Param1 = 2u;

  //Step 3) Call FUT
  Dblc_Convert_Deg_mRadHr_RetVal = Dblc_Convert_Deg_mRadHr(Dblc_Convert_Deg_mRadHr_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dblc_Convert_Deg_mRad_RetVal, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Dblc_Convert_Deg_mRadHr
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates swiveling rates
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Dblc_Convert_Deg_mRadHr(void)
{
  Mt_Dbl_Dblc_Convert_Deg_mRadHr_TestCase_1();
  Mt_Dbl_Dblc_Convert_Deg_mRadHr_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCalculateSwiveling_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function increases bend radius on right bend
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcCalculateSwiveling_Param1                          = 1u
/// \input  DblcCalculateSwiveling_Param2                          = -20u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.CGCorrection   = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ConstCurvature = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimOutFast     = -2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimInSlow      = -2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateOut  = 5u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = 1u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 1u
///
/// - Expectations:
///
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 1u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = 0u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCalculateSwiveling_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks      = &Coding_Dummy;
  DblcCalculateSwiveling_Param1                   = -1u;
  DblcCalculateSwiveling_Param2                   = -20u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucCGCorrection   = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucConstCurvature = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimOutFast     = -2u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimInSlow      = -2u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateOut  = 5u;
  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 1u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 1u;

  //Step 3) Call FUT
  DblcCalculateSwiveling(DblcCalculateSwiveling_Param1, DblcCalculateSwiveling_Param2, DblcCalculateSwiveling_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0], 0, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1], 0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCalculateSwiveling_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function decreases bend radius on right bend
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcCalculateSwiveling_Param1                          = 1u
/// \input  DblcCalculateSwiveling_Param2                          = -22u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ConstCurvature = 1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimInFast      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimOutSlow     = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateIn   = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.CGCorrection   = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateOut  = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = 1u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 1u
///
/// - Expectations:
///
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 1u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = -16u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 16u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCalculateSwiveling_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks      = &Coding_Dummy;
  DblcCalculateSwiveling_Param1                   = 1u;
  DblcCalculateSwiveling_Param2                   = -22u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucConstCurvature = 1u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimInFast      = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimOutSlow     = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateIn   = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucCGCorrection   = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateOut  = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 1u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 1u;

  //Step 3) Call FUT
  DblcCalculateSwiveling(DblcCalculateSwiveling_Param1, DblcCalculateSwiveling_Param2, DblcCalculateSwiveling_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_HitCount,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0], 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCalculateSwiveling_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if functionv keeps constant bend radius on right bend
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcCalculateSwiveling_Param1                           = 1u
/// \input  DblcCalculateSwiveling_Param2                           = -8u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.CGCorrection   = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateOut  = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ConstCurvature = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimOutSlow     = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimInSlow      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateIn   = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                 = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]         = 1u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]         = 1u
///
/// - Expectations:
///
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 1u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = -4u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 4u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCalculateSwiveling_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks      = &Coding_Dummy;
  DblcCalculateSwiveling_Param1                   = 0u;
  DblcCalculateSwiveling_Param2                   = -8u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucCGCorrection   = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateOut  = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucConstCurvature =-8u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimOutSlow     = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimInSlow      = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateIn   = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 1u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 1u;

  //Step 3) Call FUT
  DblcCalculateSwiveling(DblcCalculateSwiveling_Param1, DblcCalculateSwiveling_Param2, DblcCalculateSwiveling_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_HitCount,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0], 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCalculateSwiveling_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if functionv increases bend radius on left bend
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcCalculateSwiveling_Param1                           = -1u
/// \input  DblcCalculateSwiveling_Param2                           = -1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.CGCorrection   = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateOut  = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ConstCurvature = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimOutSlow     = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimInSlow      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateIn   = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                 = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]         = 1u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]         = 1u
///
/// - Expectations:
///
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 1u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = -17u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 17u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCalculateSwiveling_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks      = &Coding_Dummy;
  DblcCalculateSwiveling_Param1                   = -1u;
  DblcCalculateSwiveling_Param2                   = -1u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucCGCorrection   = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateOut  = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucConstCurvature = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimOutSlow     = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimInSlow      = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateIn   = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 1u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 1u;

  //Step 3) Call FUT
  DblcCalculateSwiveling(DblcCalculateSwiveling_Param1, DblcCalculateSwiveling_Param2, DblcCalculateSwiveling_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_HitCount,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0], 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCalculateSwiveling_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if functionv decreases bend radius on left bend
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcCalculateSwiveling_Param1                           = 11u
/// \input  DblcCalculateSwiveling_Param2                           = 12u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.CGCorrection   = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateOut  = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ConstCurvature = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimOutSlow     = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimInSlow      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateIn   = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = 1u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 1u
///
/// - Expectations:
///
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 1u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = -20u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 20u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCalculateSwiveling_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks      = &Coding_Dummy;
  DblcCalculateSwiveling_Param1                   = 11u;
  DblcCalculateSwiveling_Param2                   = 12u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucCGCorrection   = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateOut  = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucConstCurvature = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimOutSlow     = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimInSlow      = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateIn   = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 1u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 1u;

  //Step 3) Call FUT
  DblcCalculateSwiveling(DblcCalculateSwiveling_Param1, DblcCalculateSwiveling_Param2, DblcCalculateSwiveling_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_HitCount,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0], 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCalculateSwiveling_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if functionv keeps constant bend radius on left bend
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcCalculateSwiveling_Param1                          = 10u
/// \input  DblcCalculateSwiveling_Param2                          = 10u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.CGCorrection   = -1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateOut  = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ConstCurvature = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimOutSlow     = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimInSlow      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateIn   = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = 1u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 1u
///
/// - Expectations:
///
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 1u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = -23u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 23u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCalculateSwiveling_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks      = &Coding_Dummy;
  DblcCalculateSwiveling_Param1                   = -10u;
  DblcCalculateSwiveling_Param2                   = 10u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucCGCorrection   = -1u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateOut  = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucConstCurvature = 10u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimOutSlow     = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimInSlow      = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateIn   = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 1u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 1u;

  //Step 3) Call FUT
  DblcCalculateSwiveling(DblcCalculateSwiveling_Param1, DblcCalculateSwiveling_Param2, DblcCalculateSwiveling_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_HitCount,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0], 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcCalculateSwiveling_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if functionv keeps constant bend radius on left bend
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcCalculateSwiveling_Param1                          = -10u
/// \input  DblcCalculateSwiveling_Param2                          = 8u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.CGCorrection   = -1u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateOut  = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ConstCurvature = 2u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimOutSlow     = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.LimInSlow      = 0u
/// \input  Dbl_sCodingParam_Dummy.Dbl.AfsSwiRateLim.ChangeRateIn   = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = 1u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 1u
///
/// - Expectations:
///
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_HitCount                = 1u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]        = -26u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]        = 26u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCalculateSwiveling_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks      = &Coding_Dummy;
  DblcCalculateSwiveling_Param1                   = -10u;
  DblcCalculateSwiveling_Param2                   = 8u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucCGCorrection   = -1u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateOut  = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucConstCurvature = 2u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimOutSlow     = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucLimInSlow      = 0u;
  Coding_Dummy.Dbl.AfsSwiRateLim.ucChangeRateIn   = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 1u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 1u;

  //Step 3) Call FUT
  DblcCalculateSwiveling(DblcCalculateSwiveling_Param1, DblcCalculateSwiveling_Param2, DblcCalculateSwiveling_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_HitCount,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0], 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if functionv keeps constant bend radius
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcCalculateSwiveling(void)
{
  Mt_Dbl_DblcCalculateSwiveling_TestCase_1();
  Mt_Dbl_DblcCalculateSwiveling_TestCase_2();
  Mt_Dbl_DblcCalculateSwiveling_TestCase_3();
  Mt_Dbl_DblcCalculateSwiveling_TestCase_4();
  Mt_Dbl_DblcCalculateSwiveling_TestCase_5();
  Mt_Dbl_DblcCalculateSwiveling_TestCase_6();
  Mt_Dbl_DblcCalculateSwiveling_TestCase_7();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcLimitSwiveling_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if functionv limit the swiveling angle on swiveling right
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcLimitSwiveling_Param1                           = 0u
/// \input  DblcLimitSwiveling_Param2                           = 0u
/// \input  DblcLimitSwiveling_Param3                           = 1u
/// \input  DblcLimitSwiveling_Param4                           = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount              = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]      = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]      = 1u
///
/// - Expectations:
///
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_HitCount              = 1u
/// \output DblcLimitSwiveling_RetVal                           = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcLimitSwiveling_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  DblcLimitSwiveling_Param1                      = 0u;
  DblcLimitSwiveling_Param2                      = 0u;
  DblcLimitSwiveling_Param3                      = 1u;
  DblcLimitSwiveling_Param4                      = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 1u;

  //Step 3) Call FUT
  DblcLimitSwiveling_RetVal = DblcLimitSwiveling(DblcLimitSwiveling_Param1, DblcLimitSwiveling_Param2, DblcLimitSwiveling_Param3, DblcLimitSwiveling_Param4, DblcLimitSwiveling_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcLimitSwiveling_RetVal,              1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcLimitSwiveling_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if functionv limit the swiveling angle on swiveling right
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcLimitSwiveling_Param1                           = 0u
/// \input  DblcLimitSwiveling_Param2                           = 0u
/// \input  DblcLimitSwiveling_Param3                           = 1u
/// \input  DblcLimitSwiveling_Param4                           = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount              = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]      = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]      = 0u
///
/// - Expectations:
///
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_HitCount             = 1u
/// \output DblcLimitSwiveling_RetVal                          = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcLimitSwiveling_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  DblcLimitSwiveling_Param1                      = 0u;
  DblcLimitSwiveling_Param2                      = 0u;
  DblcLimitSwiveling_Param3                      = 1u;
  DblcLimitSwiveling_Param4                      = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 0u;

  //Step 3) Call FUT
  DblcLimitSwiveling_RetVal = DblcLimitSwiveling(DblcLimitSwiveling_Param1, DblcLimitSwiveling_Param2, DblcLimitSwiveling_Param3, DblcLimitSwiveling_Param4, DblcLimitSwiveling_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcLimitSwiveling_RetVal,              0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcLimitSwiveling_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if functionv limit the swiveling angle on swiveling left
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcLimitSwiveling_Param1                           = 0u
/// \input  DblcLimitSwiveling_Param2                           = 0u
/// \input  DblcLimitSwiveling_Param3                           = 0u
/// \input  DblcLimitSwiveling_Param4                           = 1u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount              = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]      = -2u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]      = 0u
///
/// - Expectations:
///
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_HitCount              = 1u
/// \output DblcLimitSwiveling_RetVal                           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcLimitSwiveling_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  DblcLimitSwiveling_Param1                      = 0u;
  DblcLimitSwiveling_Param2                      = 0u;
  DblcLimitSwiveling_Param3                      = 0u;
  DblcLimitSwiveling_Param4                      = 1u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = -2u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 0u;

  //Step 3) Call FUT
  DblcLimitSwiveling_RetVal = DblcLimitSwiveling(DblcLimitSwiveling_Param1, DblcLimitSwiveling_Param2, DblcLimitSwiveling_Param3, DblcLimitSwiveling_Param4, DblcLimitSwiveling_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcLimitSwiveling_RetVal,              0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcLimitSwiveling_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if functionv limit the swiveling angle on swiveling left
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcLimitSwiveling_Param1                           = 0u
/// \input  DblcLimitSwiveling_Param2                           = 0u
/// \input  DblcLimitSwiveling_Param3                           = 0u
/// \input  DblcLimitSwiveling_Param4                           = 1u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount              = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]      = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]      = 0u
///
/// - Expectations:
///
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_HitCount              = 1u
/// \output DblcLimitSwiveling_RetVal                           = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcLimitSwiveling_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  DblcLimitSwiveling_Param1                      = 0u;
  DblcLimitSwiveling_Param2                      = 0u;
  DblcLimitSwiveling_Param3                      = 0u;
  DblcLimitSwiveling_Param4                      = 1u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 0u;

  //Step 3) Call FUT
  DblcLimitSwiveling_RetVal = DblcLimitSwiveling(DblcLimitSwiveling_Param1, DblcLimitSwiveling_Param2, DblcLimitSwiveling_Param3, DblcLimitSwiveling_Param4, DblcLimitSwiveling_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcLimitSwiveling_RetVal,              1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcLimitSwiveling_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if functionv limit the swiveling angle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  DblcLimitSwiveling_Param1                           = 0u
/// \input  DblcLimitSwiveling_Param2                           = 0u
/// \input  DblcLimitSwiveling_Param3                           = 1u
/// \input  DblcLimitSwiveling_Param4                           = 1u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount              = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]      = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]      = 0u
///
/// - Expectations:
///
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_HitCount              = 1u
/// \output DblcLimitSwiveling_RetVal                           = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcLimitSwiveling_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  DblcLimitSwiveling_Param1                      = 0u;
  DblcLimitSwiveling_Param2                      = 0u;
  DblcLimitSwiveling_Param3                      = 1u;
  DblcLimitSwiveling_Param4                      = 1u;
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 0u;

  //Step 3) Call FUT
  DblcLimitSwiveling_RetVal = DblcLimitSwiveling(DblcLimitSwiveling_Param1, DblcLimitSwiveling_Param2, DblcLimitSwiveling_Param3, DblcLimitSwiveling_Param4, DblcLimitSwiveling_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount, 1u, == );
  AL_UNITTEST_CHECK(DblcLimitSwiveling_RetVal,              1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DblcLimitSwiveling
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if functionv limit the swiveling angle
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DblcLimitSwiveling(void)
{
  Mt_Dbl_DblcLimitSwiveling_TestCase_1();
  Mt_Dbl_DblcLimitSwiveling_TestCase_2();
  Mt_Dbl_DblcLimitSwiveling_TestCase_3();
  Mt_Dbl_DblcLimitSwiveling_TestCase_4();
  Mt_Dbl_DblcLimitSwiveling_TestCase_5();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_WriteSwimRate
///
/// \Test Case Description
///        - Test subject: Test if function writes swim rate
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_WriteSwimRate_Param1.nLimit[0]         = 23u
/// \input  Dbl_RteAccess_WriteSwimRate_Param1.nLimit[1]         = 13u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount              = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]      = 0u
/// \input  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]      = 0u
///
/// - Expectations:
///
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_HitCount              = 1u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0]      = 23u
/// \output Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1]      = 13u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_WriteSwimRate(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_WriteSwimRate_Param1.nLimit[0]    = 23u;
  Dbl_RteAccess_WriteSwimRate_Param1.nLimit[1]    = 13u;
  Rte_Write_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 0u;
  Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_WriteSwimRate(Dbl_RteAccess_WriteSwimRate_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[0], 23u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_SwiRateLimMsg_Param1.nLimit[1], 13u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_WriteSwimRate
///
/// \Test Case Description
///        - Test subject: Test if function writes driving situation 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_WriteDriveSituation_Param1        = 23u
/// \input  Rte_Write_AfsDbl_DblDriveSit_HitCount           = 0u
/// \input  Rte_Write_AfsDbl_DblDriveSit_Param1.ucData      = 0u
///
/// - Expectations:
///
/// \output Rte_Write_AfsDbl_DblDriveSit_HitCount           = 1u
/// \output Rte_Write_AfsDbl_DblDriveSit_Param1.ucData      = 23u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_WriteDriveSituation(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_WriteDriveSituation_Param1   = 23u;
  Rte_Write_AfsDbl_DblDriveSit_HitCount      = 0u;
  Rte_Write_AfsDbl_DblDriveSit_Param1.ucData = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_WriteDriveSituation(Dbl_RteAccess_WriteDriveSituation_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_DblDriveSit_HitCount,       1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AfsDbl_DblDriveSit_Param1.ucData, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDblTrafficSide_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads traffic wheel drive side
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eTypeDir_SteeringLeft
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount             = 1u
/// \output Dbl_RteAccess_ReadDblTrafficSide_RetVal           = LeftHandTraffic
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDblTrafficSide_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eTypeDir_SteeringLeft;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDblTrafficSide_RetVal = Dbl_RteAccess_ReadDblTrafficSide();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDblTrafficSide_RetVal, LeftHandTraffic, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDblTrafficSide_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads traffic wheel drive side
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eTypeDir_SteeringRight
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount             = 1u
/// \output Dbl_RteAccess_ReadDblTrafficSide_RetVal           = RightHandTraffic
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDblTrafficSide_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eTypeDir_SteeringRight;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDblTrafficSide_RetVal = Dbl_RteAccess_ReadDblTrafficSide();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDblTrafficSide_RetVal, RightHandTraffic, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDblTrafficSide_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads traffic wheel drive side
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = 3u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDblTrafficSide_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = 3u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDblTrafficSide_RetVal = Dbl_RteAccess_ReadDblTrafficSide();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDblTrafficSide
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads traffic wheel drive side
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDblTrafficSide(void)
{
  Mt_Dbl_RteAccess_ReadDblTrafficSide_TestCase_1();
  Mt_Dbl_RteAccess_ReadDblTrafficSide_TestCase_2();
  Mt_Dbl_RteAccess_ReadDblTrafficSide_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_Read_EcuSide_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads Ecu mounting side from Rte for case eMountedLeft
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft (0u)
/// \input  Dbl_RteAccess_Read_EcuSide_Param1            = Dbl_eMountedUndef
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
/// \output Dbl_RteAccess_Read_EcuSide_Param1            = Dbl_eMountedLeft
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_Read_EcuSide_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft;
  Dbl_RteAccess_Read_EcuSide_Param1            = Dbl_eMountedUndef;

  //Step 3) Call FUT
  Dbl_RteAccess_Read_EcuSide(&Dbl_RteAccess_Read_EcuSide_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_Read_EcuSide_Param1, Dbl_eMountedLeft, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_Read_EcuSide_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads Ecu mounting side from Rte for case eMountedRight
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedRight (1u)
/// \input  Dbl_RteAccess_Read_EcuSide_Param1            = Dbl_eMountedUndef
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
/// \output Dbl_RteAccess_Read_EcuSide_Param1            = Dbl_eMountedRight
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_Read_EcuSide_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedRight;
  Dbl_RteAccess_Read_EcuSide_Param1            = Dbl_eMountedUndef;

  //Step 3) Call FUT
  Dbl_RteAccess_Read_EcuSide(&Dbl_RteAccess_Read_EcuSide_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_Read_EcuSide_Param1, Dbl_eMountedRight, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_Read_EcuSide_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads Ecu mounting side from Rte for case default
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_Param1   = 15u
/// \input  Dbl_RteAccess_Read_EcuSide_Param1            = Dbl_eMountedUndef
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
/// \output Dbl_RteAccess_Read_EcuSide_Param1            = Dbl_eMountedRight
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_Read_EcuSide_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1   = 15u;
  Dbl_RteAccess_Read_EcuSide_Param1            = Dbl_eMountedUndef;

  //-----------------------------------------------------------------------------
  //Step 3) Call FUT
  //-----------------------------------------------------------------------------

  Dbl_RteAccess_Read_EcuSide(&Dbl_RteAccess_Read_EcuSide_Param1);

  //-----------------------------------------------------------------------------
  //Step 4) Check expected output values
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_Read_EcuSide_Param1, Dbl_eMountedRight, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_Read_EcuSide
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads Ecu mounting side from Rte
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_Read_EcuSide(void)
{
  Mt_Dbl_RteAccess_Read_EcuSide_TestCase_1();
  Mt_Dbl_RteAccess_Read_EcuSide_TestCase_2();
  Mt_Dbl_RteAccess_Read_EcuSide_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDblOutput
///
/// \Test Case Description
///        - Test subject: Test if function reads output angle of Dbl
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_Dbl_SwivellingOut_HitCount           = 0u
/// \input  Rte_Read_Dbl_SwivellingOut_Param1.SwivelAngle = 23u
///
/// - Expectations:
///
/// \output Rte_Read_Dbl_SwivellingOut_HitCount           = 1u
/// \output Dbl_RteAccess_ReadDblOutput_RetVal            = -1024
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDblOutput(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_Dbl_SwivellingOut_HitCount              = 0u;
  Rte_Read_Dbl_SwivellingOut_Param1.SwivelAngle[0] = 23u;
  Rte_Read_Dbl_SwivellingOut_Param1.SwivelAngle[1] = 23u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDblOutput_RetVal = Dbl_RteAccess_ReadDblOutput();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Dbl_SwivellingOut_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDblOutput_RetVal,  -1024, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_WriteDblOutput
///
/// \Test Case Description
///        - Test subject: Test if function writes Dbl output
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_WriteDblOutput_Param1            = 23u
/// \input  Dbl_RteAccess_WriteDblOutput_Param2            = 13u
/// \input  Dbl_RteAccess_WriteDblOutput_Param3            = Dbl_eSubModeAvailable
/// \input  Rte_Write_Dbl_SwivellingOut_HitCount           = 0u
/// \input  Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle = 0u
/// \input  Rte_Write_Dbl_SwivellingOut_Param1.DblState    = 0u
/// \input  Rte_Write_Dbl_Mode_HitCount                    = 0u
/// \input  Rte_Write_Dbl_Mode_Param1                      = eSubModeUnavailable
///
/// - Expectations:
///
/// \output Rte_Write_Dbl_SwivellingOut_HitCount           = 1u
/// \output Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle = 23u
/// \output Rte_Write_Dbl_SwivellingOut_Param1.DblState    = 13u
/// \output Rte_Write_Dbl_Mode_HitCount                    = 1u
/// \output Rte_Write_Dbl_Mode_Param1                      = Dbl_eSubModeAvailable
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_WriteDblOutput(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_WriteDblOutput_Param1.SwivellingAngle[0].Hor = 23u;
  Dbl_RteAccess_WriteDblOutput_Param1.SwivellingAngle[1].Hor = 23u;
  Dbl_RteAccess_WriteDblOutput_Param2                        = 13u;
  Dbl_RteAccess_WriteDblOutput_Param3                        = Dbl_eSubModeAvailable;
  Rte_Write_Dbl_SwivellingOut_HitCount                       = 0u;
  Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[0]          = 0u;
  Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[1]          = 0u;
  Rte_Write_Dbl_SwivellingOut_Param1.DblState                = 0u;
  Rte_Write_Dbl_Mode_HitCount                                = 0u;
  Rte_Write_Dbl_Mode_Param1                                  = eSubModeUnavailable;

  //Step 3) Call FUT
  Dbl_RteAccess_WriteDblOutput(Dbl_RteAccess_WriteDblOutput_Param1, Dbl_RteAccess_WriteDblOutput_Param2, Dbl_RteAccess_WriteDblOutput_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_HitCount,               1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[0], 23u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.SwivelAngle[1], 23u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SwivellingOut_Param1.DblState,       13u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_Mode_HitCount,                        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_Mode_Param1,       Dbl_eSubModeAvailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_WriteDblSysMonTx_FullStatus
///
/// \Test Case Description
///        - Test subject: Test if function writes Dbl SysMon status
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_WriteDblSysMonTx_FullStatus_Param1                  = TRUE
/// \input  Rte_Write_Dbl_SysMonTx_FullStatus_HitCount                        = 0u
/// \input  Rte_Write_Dbl_SysMonTx_FullStatus_Param1.eDynamicBendingBeamFault = eDiagDbl_Ok
///
/// - Expectations:
///
/// \output Rte_Write_Dbl_SysMonTx_FullStatus_HitCount                        = 1u
/// \output Rte_Write_Dbl_SysMonTx_FullStatus_Param1.eDynamicBendingBeamFault = eDiagDbl_Nok
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_WriteDblSysMonTx_FullStatus(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_WriteDblSysMonTx_FullStatus_Param1                  = TRUE;
  Rte_Write_Dbl_SysMonTx_FullStatus_HitCount                        = 0u;
  Rte_Write_Dbl_SysMonTx_FullStatus_Param1.eDynamicBendingBeamFault = eDiagDbl_Ok;

  //Step 3) Call FUT
  Dbl_RteAccess_WriteDblSysMonTx_FullStatus(Dbl_RteAccess_WriteDblSysMonTx_FullStatus_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SysMonTx_FullStatus_HitCount,                                  1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SysMonTx_FullStatus_Param1.eDynamicBendingBeamFault, eDiagDbl_Nok, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function writes dbl fault status for full variant for left side
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param1          = Dbl_eMountedLeft (0u)
/// \input  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param2          = TRUE
/// \input  Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                    = 0u
/// \input  Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount                     = 0u
/// \input  Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1.eDynBendingBeamFault  = eDynBendingBeamFault_False
///
/// - Expectations:
///
/// \output Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount                     = 1u
/// \output Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                    = 0u
/// \output Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1.eDynBendingBeamFault  = eDynBendingBeamFault_True
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param1         = Dbl_eMountedLeft;
  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param2         = TRUE;
  Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                   = 0u;
  Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount                    = 0u;
  Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_False;

  //Step 3) Call FUT
  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus(Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param1, Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount,                                           1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount,                                          0u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_LeftStatus_Param1.eDynBendingBeamFault, eDynBendingBeamFault_True, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function writes dbl fault status for full variant for right side
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param1          = Dbl_eMountedRight (1u)
/// \input  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param2          = FALSE
/// \input  Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount                     = 0u
/// \input  Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                    = 0u
/// \input  Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_True
///
/// - Expectations:
///
/// \output Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount                     = 0u
/// \output Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                    = 1u
/// \output Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_False
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param1          = Dbl_eMountedRight;
  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param2          = FALSE;
  Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount                     = 0u;
  Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount                    = 0u;
  Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_True;

  //Step 3) Call FUT
  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus(Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param1, Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_LeftStatus_HitCount,                                             0u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_RightStatus_HitCount,                                            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Dbl_SigPrepTx_RightStatus_Param1.eDynBendingBeamFault, eDynBendingBeamFault_False, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function writes dbl fault status
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus(void)
{
  Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_TestCase_1();
  Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadReverseGearStatus_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function gets reverse gear status when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                   = SIG_VALID
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eEtatMar                  = 1u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadReverseGearStatus_RetVal                         = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadReverseGearStatus_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty  = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eEtatMar = 1u;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount        = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadReverseGearStatus_RetVal = Dbl_RteAccess_ReadReverseGearStatus();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadReverseGearStatus_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadReverseGearStatus_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function gets reverse gear status when signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount       = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadReverseGearStatus_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount       = 0u;
  Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode    = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadReverseGearStatus_RetVal = Dbl_RteAccess_ReadReverseGearStatus();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadReverseGearStatus_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function gets reverse gear status when signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_TIMEOUT
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount       = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount       = 1u
/// \output Dbl_RteAccess_ReadReverseGearStatus_RetVal       = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadReverseGearStatus_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_TIMEOUT;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount       = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadReverseGearStatus_RetVal = Dbl_RteAccess_ReadReverseGearStatus();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadReverseGearStatus_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadReverseGearStatus
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets reverse gear status
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadReverseGearStatus(void)
{
  Mt_Dbl_RteAccess_ReadReverseGearStatus_TestCase_1();
  Mt_Dbl_RteAccess_ReadReverseGearStatus_TestCase_2();
  Mt_Dbl_RteAccess_ReadReverseGearStatus_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVehicleModeConfig_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads the state of vehicle configuration when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                   = SIG_VALID
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg               = eModeConfigVehicle_Client (4u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadVehicleModeConfig_RetVal                         = 4u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVehicleModeConfig_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVehicleModeConfig_RetVal = Dbl_RteAccess_ReadVehicleModeConfig();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVehicleModeConfig_RetVal, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVehicleModeConfig_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads the state of vehicle configuration when signal is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                   = SIG_INVALID
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg               = eModeConfigVehicle_Client (4u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadVehicleModeConfig_RetVal                         = 15u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVehicleModeConfig_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_INVALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVehicleModeConfig_RetVal = Dbl_RteAccess_ReadVehicleModeConfig();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVehicleModeConfig_RetVal, 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVehicleModeConfig_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads the state of vehicle configuration when signal is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                   = SIG_TIMEOUT
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg               = eModeConfigVehicle_Client (4u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadVehicleModeConfig_RetVal                         = 4u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVehicleModeConfig_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty      = SIG_TIMEOUT;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg  = eModeConfigVehicle_Client;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount            = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVehicleModeConfig_RetVal = Dbl_RteAccess_ReadVehicleModeConfig();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVehicleModeConfig_RetVal, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVehicleModeConfig
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads the state of vehicle configuration when signal is not valid
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVehicleModeConfig(void)
{
  Mt_Dbl_RteAccess_ReadVehicleModeConfig_TestCase_1();
  Mt_Dbl_RteAccess_ReadVehicleModeConfig_TestCase_2();
  Mt_Dbl_RteAccess_ReadVehicleModeConfig_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVESMainState_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads the vechicle electric state when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                   = SIG_VALID
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState             = VESState_Ignition (1u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadVESMainState_RetVal                        = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVESMainState_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehNetState_Param1.eSigQty       = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVESMainState_RetVal = Dbl_RteAccess_ReadVESMainState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVESMainState_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVESMainState_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads the vechicle electric state when signal is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                   = SIG_INVALID
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState             = VESState_Ignition (1u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadVESMainState_RetVal                        = 3u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVESMainState_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehNetState_Param1.eSigQty       = SIG_INVALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVESMainState_RetVal = Dbl_RteAccess_ReadVESMainState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVESMainState_RetVal, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVESMainState_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads the vechicle electric state when signal is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                   = SIG_INVALID
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState             = VESState_Ignition (1u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadVESMainState_RetVal                        = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVESMainState_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehNetState_Param1.eSigQty       = SIG_TIMEOUT;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVESMainState_RetVal = Dbl_RteAccess_ReadVESMainState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVESMainState_RetVal, 1u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVESMainState
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads the vechicle electric state
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVESMainState(void)
{
  Mt_Dbl_RteAccess_ReadVESMainState_TestCase_1();
  Mt_Dbl_RteAccess_ReadVESMainState_TestCase_2();
  Mt_Dbl_RteAccess_ReadVESMainState_TestCase_3();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVehicleElectricState_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads the vechicle electric state when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                   = SIG_VALID
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState     = eTA_NOMINAL (5u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadVehicleElectricState_RetVal                = 5u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVehicleElectricState_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
  Rte_Read_SysMon_VehNetState_HitCount                     = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVehicleElectricState_RetVal = Dbl_RteAccess_ReadVehicleElectricState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVehicleElectricState_RetVal, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVehicleElectricState_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads the vechicle electric state when signal is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                   = SIG_INVALID
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState     = eTA_NOMINAL (5u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadVehicleElectricState_RetVal                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVehicleElectricState_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_INVALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
  Rte_Read_SysMon_VehNetState_HitCount                     = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVehicleElectricState_RetVal = Dbl_RteAccess_ReadVehicleElectricState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVehicleElectricState_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVehicleElectricState_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads the vechicle electric state when signal is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                   = SIG_TIMEOUT
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState     = eTA_NOMINAL (5u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                         = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount                         = 1u
/// \output Dbl_RteAccess_ReadVehicleElectricState_RetVal                = 5u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVehicleElectricState_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_TIMEOUT;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
  Rte_Read_SysMon_VehNetState_HitCount                     = 0u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVehicleElectricState_RetVal = Dbl_RteAccess_ReadVehicleElectricState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVehicleElectricState_RetVal, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadVehicleElectricState
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads the vechicle electric state
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadVehicleElectricState(void)
{
  Mt_Dbl_RteAccess_ReadVehicleElectricState_TestCase_1();
  Mt_Dbl_RteAccess_ReadVehicleElectricState_TestCase_2();
  Mt_Dbl_RteAccess_ReadVehicleElectricState_TestCase_3();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadCurvature_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads curvature when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_ReadCurvature_Param1                                                   = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount                                           = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                                     = SIG_VALID
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 25005
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount                                           = 1u
/// \output Dbl_RteAccess_ReadCurvature_Param1                                                   = 10000
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadCurvature_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_ReadCurvature_Param1                                                   = 0u;
  Rte_Read_SigPrep_VehPathCurvature_HitCount                                           = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                                     = SIG_VALID;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 25005;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadCurvature(&Dbl_RteAccess_ReadCurvature_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadCurvature_Param1,      10000, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadCurvature_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads curvature when signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_ReadCurvature_Param1                          = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount                  = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty            = SIG_INVALID
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount                  = 1u
/// \output Dbl_RteAccess_ReadCurvature_Param1                          = 10002
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadCurvature_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_ReadCurvature_Param1               = 0u;
  Rte_Read_SigPrep_VehPathCurvature_HitCount       = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_INVALID;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadCurvature(&Dbl_RteAccess_ReadCurvature_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadCurvature_Param1,      10002, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadCurvature_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads curvature when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_ReadCurvature_Param1                                                   = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount                                           = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                                     = SIG_VALID
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = -25005
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount                                           = 1u
/// \output Dbl_RteAccess_ReadCurvature_Param1                                                   = -10000
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadCurvature_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_ReadCurvature_Param1 = 0u;
  Rte_Read_SigPrep_VehPathCurvature_HitCount = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = -25005;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadCurvature(&Dbl_RteAccess_ReadCurvature_Param1);
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadCurvature_Param1,     -10000, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadCurvature_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function reads curvature when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_ReadCurvature_Param1                                                   = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount                                           = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                                     = SIG_VALID
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 25u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount                                           = 1u
/// \output Dbl_RteAccess_ReadCurvature_Param1                                                   = 10
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadCurvature_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_ReadCurvature_Param1 = 0u;
  Rte_Read_SigPrep_VehPathCurvature_HitCount = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = 25u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadCurvature(&Dbl_RteAccess_ReadCurvature_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadCurvature_Param1, 10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadCurvature_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function reads curvature when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_RteAccess_ReadCurvature_Param1                                                   = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount                                           = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                                     = SIG_VALID
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = -25
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount                                           = 1u
/// \output Dbl_RteAccess_ReadCurvature_Param1                                                   = -10
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadCurvature_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Dbl_RteAccess_ReadCurvature_Param1 = 0u;
  Rte_Read_SigPrep_VehPathCurvature_HitCount = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eVehiclePathCurvature.nVehiclePathCurvature = -25;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadCurvature(&Dbl_RteAccess_ReadCurvature_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadCurvature_Param1, -10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadCurvature
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads curvature
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadCurvature(void)
{
  Mt_Dbl_RteAccess_ReadCurvature_TestCase_1();
  Mt_Dbl_RteAccess_ReadCurvature_TestCase_2();
  Mt_Dbl_RteAccess_ReadCurvature_TestCase_3();
  Mt_Dbl_RteAccess_ReadCurvature_TestCase_4();
  Mt_Dbl_RteAccess_ReadCurvature_TestCase_5();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads speed when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_TIMEOUT
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                            = 2u
/// \output Dbl_RteAccess_ReadSpeed_RetVal                                   = 65535u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                   = SIG_TIMEOUT;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSpeed_RetVal = Dbl_RteAccess_ReadSpeed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSpeed_RetVal,    65535u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads speed when signal quality is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount            = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl      = SIG_INVALID
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount            = 1u
/// \output Dbl_RteAccess_ReadSpeed_RetVal                   = DBL_MAX_SPEED
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_HitCount       = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl = SIG_INVALID;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSpeed_RetVal = Dbl_RteAccess_ReadSpeed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSpeed_RetVal, DBL_MAX_SPEED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads speed when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_DISABLED
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                            = 1u
/// \output Dbl_RteAccess_ReadSpeed_RetVal                                   = 65535u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_DISABLED;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSpeed_RetVal = Dbl_RteAccess_ReadSpeed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSpeed_RetVal,    65535u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function reads speed when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_TIMEOUT
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                            = 1u
/// \output Dbl_RteAccess_ReadSpeed_RetVal                                   = 65535u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_TIMEOUT;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSpeed_RetVal = Dbl_RteAccess_ReadSpeed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSpeed_RetVal,    65535u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function reads speed when signal quality is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount            = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl      = SIG_E2E_CRCERR
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount            = 1u
/// \output Dbl_RteAccess_ReadSpeed_RetVal                   = DBL_MAX_SPEED
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl = SIG_E2E_CRCERR;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSpeed_RetVal = Dbl_RteAccess_ReadSpeed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSpeed_RetVal, DBL_MAX_SPEED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function reads speed when signal quality is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount            = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl      = SIG_E2E_ALIVEERR
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount            = 1u
/// \output Dbl_RteAccess_ReadSpeed_RetVal                   = DBL_MAX_SPEED
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl = SIG_E2E_ALIVEERR;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSpeed_RetVal = Dbl_RteAccess_ReadSpeed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSpeed_RetVal, DBL_MAX_SPEED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function reads speed when signal quality is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                  = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl         = SIG_VALID
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount            = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_HitCount                  = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl         = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSpeed_RetVal = Dbl_RteAccess_ReadSpeed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if function reads speed when signal quality is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                  = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl         = SIG_VALID
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoUnavailable
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount            = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed_TestCase_8(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_HitCount                  = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl         = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoUnavailable;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSpeed_RetVal = Dbl_RteAccess_ReadSpeed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed_TestCase_9
///
/// \Test Case Description
///        - Test subject: Test if function reads speed when signal quality is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                  = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl         = SIG_INVALID
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount            = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed_TestCase_9(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_HitCount                  = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl         = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSpeed_RetVal = Dbl_RteAccess_ReadSpeed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSpeed
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads speede
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSpeed(void)
{
  Mt_Dbl_RteAccess_ReadSpeed_TestCase_1();
  Mt_Dbl_RteAccess_ReadSpeed_TestCase_2();
  Mt_Dbl_RteAccess_ReadSpeed_TestCase_3();
  Mt_Dbl_RteAccess_ReadSpeed_TestCase_4();
  Mt_Dbl_RteAccess_ReadSpeed_TestCase_5();
  Mt_Dbl_RteAccess_ReadSpeed_TestCase_6();
  Mt_Dbl_RteAccess_ReadSpeed_TestCase_7();
  Mt_Dbl_RteAccess_ReadSpeed_TestCase_8();
  Mt_Dbl_RteAccess_ReadSpeed_TestCase_9();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for right side when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_VALID (1u)
///         Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Unavailable (2u)
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal                  = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Unavailable;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultR();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for right side when signal quality is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_INVALID (3u)
///         Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Unavailable (2u)
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal                  = eDbl_DynBendingBeamFault_True
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_INVALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Unavailable;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultR();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal, eDbl_DynBendingBeamFault_True, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for right side when signal quality is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_INVALID (3u)
///         Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Unavailable (2u)
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_False;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultR();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for right side when signal quality is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_INVALID (3u)
///         Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Invalid (2u)
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal                  = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Invalid;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultR();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for right side when signal quality is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_INIT 
///         Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Invalid (2u)
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal                  = eDbl_DynBendingBeamFault_SNA
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_INIT;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Invalid;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultR();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultR_RetVal, eDbl_DynBendingBeamFault_SNA, == );

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for right side
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR(void)
{
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_1();
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_2();
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_3();
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_4();
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR_TestCase_5();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for left side when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_VALID (1u)
///         Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_True (1u)
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal                 = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_True;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultL();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for left side when signal quality is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_INVALID (3u)
///         Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_True (1u)
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal                 = eDbl_DynBendingBeamFault_True
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_INVALID;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_True;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultL();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal, eDbl_DynBendingBeamFault_True, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for left side when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_VALID (1u)
///         Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Unavailable
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal                 = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Unavailable;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultL();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for left side when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_VALID (1u)
///         Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Invalid (1u)
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal                 = eDbl_DynBendingBeamFault_Unavailable
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Invalid;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultL();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal, eDbl_DynBendingBeamFault_Unavailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for left side when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_INIT 
///         Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Invalid (1u)
/// - Expectations:
///
/// \output Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal                 = eDbl_DynBendingBeamFault_SNA
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_5(void)
{
  //Step 1) Set pre-conditions

  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_INIT;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_Invalid;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal = Dbl_RteAccess_ReadDynBendingBeamFaultL();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDynBendingBeamFaultL_RetVal, eDbl_DynBendingBeamFault_SNA, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads Dyn bending fault for left side 
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL(void)
{
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_1();
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_2();
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_3();
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_4();
  Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL_TestCase_5();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSteeringType_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads steering type when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty       = SIG_VALID
///         Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eTypeDir_SteeringRight (1u)
/// - Expectations:
///
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount             = 1u
/// \output Dbl_RteAccess_ReadSteeringType_RetVal             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSteeringType_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty       = SIG_VALID;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eTypeDir_SteeringRight;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSteeringType_RetVal = Dbl_RteAccess_ReadSteeringType();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSteeringType_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSteeringType_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads steering type when signal quality is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                    = 0u
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty              = SIG_INVALID (3u)
///         Rte_Read_SigPrep_DynamicSigs_Param1.eDynBendingBeamFault = eTypeDir_SteeringRight (1u)
/// - Expectations:
///
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadSteeringType_RetVal                    = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSteeringType_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty       = SIG_INVALID;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eTypeDir_SteeringRight;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSteeringType_RetVal = Dbl_RteAccess_ReadSteeringType();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSteeringType_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSteeringType_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads steering type when signal quality is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                    = 0u
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty              = SIG_INVALID (3u)
///         Rte_Read_SigPrep_DynamicSigs_Param1.eDynBendingBeamFault = 5u
/// - Expectations:
///
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount                    = 1u
/// \output Dbl_RteAccess_ReadSteeringType_RetVal                    = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSteeringType_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty       = SIG_VALID;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = 5u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSteeringType_RetVal = Dbl_RteAccess_ReadSteeringType();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSteeringType_RetVal, 2u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSteeringType
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads steering type
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSteeringType(void)
{
  Mt_Dbl_RteAccess_ReadSteeringType_TestCase_1();
  Mt_Dbl_RteAccess_ReadSteeringType_TestCase_2();
  Mt_Dbl_RteAccess_ReadSteeringType_TestCase_3();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadEnvCondition_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads environment condition when signal quality is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_EnvCondition_HitCount              = 0u
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty        = SIG_VALID
///         Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition = eInhEclairageVirageDyn_Inhibition (1u)
/// - Expectations:
///
/// \output Rte_Read_SigPrep_EnvCondition_HitCount              = 1u
/// \output Dbl_RteAccess_ReadEnvCondition_RetVal               = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadEnvCondition_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_EnvCondition_HitCount              = 0u;
  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty        = SIG_VALID;
  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition = eInhEclairageVirageDyn_Inhibition;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadEnvCondition_RetVal = Dbl_RteAccess_ReadEnvCondition();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_EnvCondition_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadEnvCondition_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadEnvCondition_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads environment condition when signal quality is not valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_EnvCondition_HitCount              = 0u
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty        = SIG_INVALID
///         Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition = eInhEclairageVirageDyn_Inhibition (1u)
/// - Expectations:
///
/// \output Rte_Read_SigPrep_EnvCondition_HitCount              = 1u
/// \output Dbl_RteAccess_ReadEnvCondition_RetVal               = DBL_MAX_INHIB (0xFF)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadEnvCondition_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_EnvCondition_HitCount              = 0u;
  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty        = SIG_INVALID;
  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition = eInhEclairageVirageDyn_Inhibition;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadEnvCondition_RetVal = Dbl_RteAccess_ReadEnvCondition();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_EnvCondition_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadEnvCondition_RetVal, DBL_MAX_INHIB, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadEnvCondition
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads environment condition
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadEnvCondition(void)
{
  Mt_Dbl_RteAccess_ReadEnvCondition_TestCase_1();
  Mt_Dbl_RteAccess_ReadEnvCondition_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadSwimRate
///
/// \Test Case Description
///        - Test subject: Test if function reads Swim rate
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount         = 0u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 13u
/// \input  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 13u
///
/// - Expectations:
///
/// \output Rte_Read_AfsDbl_SwiRateLimMsg_Port_HitCount    = 1u
/// \output Dbl_RteAccess_ReadSwimRate_RetVal.nLimit[0]    = 13u
/// \output Dbl_RteAccess_ReadSwimRate_RetVal.nLimit[1]    = 13u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadSwimRate(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_AfsDbl_SwiRateLimMsg_HitCount         = 0u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[0] = 13u;
  Rte_Read_AfsDbl_SwiRateLimMsg_Param1.nLimit[1] = 13u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadSwimRate_RetVal = Dbl_RteAccess_ReadSwimRate();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_AfsDbl_SwiRateLimMsg_HitCount,       1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSwimRate_RetVal.nLimit[0], 13u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSwimRate_RetVal.nLimit[1], 13u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDblCmd_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads Dbl command
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_FctR_AfsDblCmd_HitCount       = 0u
/// \input  Rte_Read_FctR_AfsDblCmd_Param1.Primary = 13u
///
/// - Expectations:
///
/// \output Rte_Read_FctR_AfsDblCmd_HitCount       = 1u
/// \output Dbl_RteAccess_ReadDblCmd_RetVal        = 3u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDblCmd_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_FctR_AfsDblCmd_HitCount       = 0u;
  Rte_Read_FctR_AfsDblCmd_Param1.Primary = 13u;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDblCmd_RetVal = Dbl_RteAccess_ReadDblCmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_FctR_AfsDblCmd_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDblCmd_RetVal,  3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadDblCmd_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads Dbl command
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_FctR_AfsDblCmd_HitCount                                                = 0u;
/// \input  Rte_Read_FctR_AfsDblCmd_Param1.Primary                                          = 1u;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblDiversity.ucTYPE_ECL_VIR_DYN = Dbl_eAUC_01;
///
/// - Expectations:
///
/// \output Rte_Read_FctR_AfsDblCmd_HitCount       = 1u
/// \output Dbl_RteAccess_ReadDblCmd_RetVal        = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDblCmd_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_FctR_AfsDblCmd_HitCount                                                = 0u;
  Rte_Read_FctR_AfsDblCmd_Param1.Primary                                          = 1u;
  Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblDiversity.ucTYPE_ECL_VIR_DYN = Dbl_eAUC_01;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadDblCmd_RetVal = Dbl_RteAccess_ReadDblCmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_FctR_AfsDblCmd_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadDblCmd_RetVal,  1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadDblCmd(void)
{
  Mt_Dbl_RteAccess_ReadDblCmd_TestCase_1();
  Mt_Dbl_RteAccess_ReadDblCmd_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadGfhbCmd_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads Gfhb command when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_Afs_Signals_HitCount         = 0u
/// \input  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty   = SIG_VALID;
/// \input  Rte_Read_SysMon_Afs_Signals_Param1.eGfhb_Cmd = eGfhbCmd_On;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_Afs_Signals_HitCount         = 1u
/// \output Dbl_RteAccess_ReadGfhbCmd_RetVal             = eGfhbCmd_On
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadGfhbCmd_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_Afs_Signals_HitCount         = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty   = SIG_VALID;
  Rte_Read_SysMon_Afs_Signals_Param1.eGfhb_Cmd = eGfhbCmd_On;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadGfhbCmd_RetVal = Dbl_RteAccess_ReadGfhbCmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount,      1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadGfhbCmd_RetVal, eGfhbCmd_On, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadGfhbCmd_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads Gfhb command when signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_Afs_Signals_HitCount         = 0u
/// \input  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty   = SIG_INVALID;
/// \input  Rte_Read_SysMon_Afs_Signals_Param1.eGfhb_Cmd = eGfhbCmd_On;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_Afs_Signals_HitCount         = 1u
/// \output Dbl_RteAccess_ReadGfhbCmd_RetVal             = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadGfhbCmd_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_Afs_Signals_HitCount         = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty   = SIG_INVALID;
  Rte_Read_SysMon_Afs_Signals_Param1.eGfhb_Cmd = eGfhbCmd_On;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadGfhbCmd_RetVal = Dbl_RteAccess_ReadGfhbCmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadGfhbCmd_RetVal,     0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadGfhbCmd
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads Gfhb command
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadGfhbCmd(void)
{
  Mt_Dbl_RteAccess_ReadGfhbCmd_TestCase_1();
  Mt_Dbl_RteAccess_ReadGfhbCmd_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadHbCmd_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads Hb command when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount           = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty     = SIG_VALID;
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request = ReqLighted_On;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount           = 1u
/// \output Dbl_RteAccess_ReadHbCmd_RetVal                    = ReqLighted_On
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadHbCmd_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount           = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request = ReqLighted_On;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadHbCmd_RetVal = Dbl_RteAccess_ReadHbCmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadHbCmd_RetVal, ReqLighted_On, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadHbCmd_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads Hb command when signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount           = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty     = SIG_INVALID;
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request = ReqLighted_On;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount           = 1u
/// \output Dbl_RteAccess_ReadHbCmd_RetVal                    = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadHbCmd_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount           = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty     = SIG_INVALID;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request = ReqLighted_On;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadHbCmd_RetVal = Dbl_RteAccess_ReadHbCmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadHbCmd_RetVal,          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadHbCmd
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadHbCmd(void)
{
  Mt_Dbl_RteAccess_ReadHbCmd_TestCase_1();
  Mt_Dbl_RteAccess_ReadHbCmd_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadFlashBeamCmd_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads Flash Beam command when signal is valid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty          = SIG_VALID;
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request = ReqLighted_On;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                = 1u
/// \output Dbl_RteAccess_ReadFlashBeamCmd_RetVal                  = ReqLighted_On
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadFlashBeamCmd_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty          = SIG_VALID;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request = ReqLighted_On;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadFlashBeamCmd_RetVal = Dbl_RteAccess_ReadFlashBeamCmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadFlashBeamCmd_RetVal, ReqLighted_On, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadFlashBeamCmd_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads Flash Beam command when signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty          = SIG_INVALID;
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request = ReqLighted_On;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                = 1u
/// \output Dbl_RteAccess_ReadFlashBeamCmd_RetVal                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadFlashBeamCmd_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty          = SIG_INVALID;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request = ReqLighted_On;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadFlashBeamCmd_RetVal = Dbl_RteAccess_ReadFlashBeamCmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadFlashBeamCmd_RetVal,   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RteAccess_ReadFlashBeamCmd
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads Flash Beam command
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RteAccess_ReadFlashBeamCmd(void)
{
  Mt_Dbl_RteAccess_ReadFlashBeamCmd_TestCase_1();
  Mt_Dbl_RteAccess_ReadFlashBeamCmd_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
/// \input Dbl_sCurvatureData.ucCurvatureMode                                          = 1u;
/// \input DblCrState_unEgoVehicleMotionConfirmation                                   = 0u;
/// \input Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u;
/// \input Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode                               = 1u;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle              = DBL_CURVATURE_INVALID_VALUE + 1;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                          = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                                  = SIG_VALID;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                                    = SIG_INVALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState                    = eTA_NOMINAL;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                        = 10;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed            = 5;
/// \input   Dbl_sCurvatureData.sCurvatureState.eCalculationPhase                      = eDbl_Nominal;
///
/// - Expectations:
///
/// \output Dbl_sCurvatureData.sCurvatureState.eCalculationPhase     = eDbl_Invalid
/// \output Dbl_sCurvatureData.slCurvatureProcessedValue             = DBL_CURVATURE_INVALID_VALUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
  Dbl_sCurvatureData.ucCurvatureMode                                          = 1u;
  DblCrState_unEgoVehicleMotionConfirmation                                   = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u;
  Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode                               = 1u;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle              = DBL_CURVATURE_INVALID_VALUE + 1;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                          = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                                  = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                                    = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState                    = eTA_NOMINAL;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                        = 10;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed            = 5;
  Dbl_sCurvatureData.sCurvatureState.eCalculationPhase                        = eDbl_Nominal;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Dbl_sCurvatureData.sCurvatureState.eCalculationPhase, eDbl_Invalid       , == );
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.slCurvatureProcessedValue, DBL_CURVATURE_INVALID_VALUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_VehPathCurvature_HitCount                            = 0u;
/// \input Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                      = SIG_INVALID;
/// \input LPTMR0_GetTimeElapsed_HitCount                                        = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal                                          = 100u;
/// \input Dbl_ulTimerSigQty_Inv                                                     = 0u;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
/// \input Dbl_sCurvatureData.ucCurvatureMode                                    = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount       = 1u
/// \output LPTMR0_GetTimeElapsed_HitCount                   = 1u
/// \output Dbl_ulTimerSigQty_Inv                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehPathCurvature_HitCount                            = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                      = SIG_INVALID;
  LPTMR0_GetTimeElapsed_HitCount                                        = 0u;
  LPTMR0_GetTimeElapsed_RetVal                                          = 100u;
  Dbl_ulTimerSigQty_Inv = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
  Dbl_sCurvatureData.ucCurvatureMode                                    = 0u;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Dbl_ulTimerSigQty_Inv,                          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount                            = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                      = SIG_INVALID (3u)
/// \input  LPTMR0_GetTimeElapsed_HitCount                                        = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                                          = 100u
/// \input  Dbl_boCurvature_SigQty_ERR                                            = FALSE
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME  = 1u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount                            = 2u
/// \output LPTMR0_GetTimeElapsed_HitCount                                        = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehPathCurvature_HitCount                           = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                     = SIG_INVALID;
  LPTMR0_GetTimeElapsed_HitCount                                       = 0u;
  LPTMR0_GetTimeElapsed_RetVal                                         = 100u;
  Dbl_boCurvature_SigQty_ERR                                           = FALSE;
  Dbl_sCodingParam.psCodingParameters_Blocks                           = &Coding_Dummy;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 1u;
  Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode = 1;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();
  LPTMR0_GetTimeElapsed_RetVal = 1100u;
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 2u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount                            = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                      = SIG_UNAVAILABLE
/// \input  LPTMR0_GetTimeElapsed_HitCount                                        = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                                          = 100u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME  = 1u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount                            = 1u
/// \output LPTMR0_GetTimeElapsed_HitCount                                        = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehPathCurvature_HitCount                           = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                     = SIG_UNAVAILABLE;
  LPTMR0_GetTimeElapsed_HitCount                                       = 0u;
  LPTMR0_GetTimeElapsed_RetVal                                         = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 0u;
  Dbl_sCodingParam.psCodingParameters_Blocks                           = &Coding_Dummy;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount       = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_VALID (1u)
/// \input  LPTMR0_GetTimeElapsed_HitCount                   = 0u
/// \input  Dbl_boCurvature_SigQty_ERR                       = TRUE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount       = 1u
/// \output LPTMR0_GetTimeElapsed_HitCount                   = 0u
/// \output Dbl_boCurvature_SigQty_ERR                       = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehPathCurvature_HitCount        = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty  = SIG_VALID;
  LPTMR0_GetTimeElapsed_HitCount                    = 0u;
  Dbl_boCurvature_SigQty_ERR                        = TRUE;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0u, == );
  AL_UNITTEST_CHECK(Dbl_boCurvature_SigQty_ERR,              FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount       = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_UNAVAILABLE
/// \input  LPTMR0_GetTimeElapsed_HitCount                   = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                     = 100u
/// \input  Dbl_ulTimerSigQty_Unav                                = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount       = 1u
/// \output LPTMR0_GetTimeElapsed_HitCount                   = 2u
/// \output Dbl_ulTimerSigQty_Unav                                =0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehPathCurvature_HitCount       = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_UNAVAILABLE;
  LPTMR0_GetTimeElapsed_HitCount                   = 0u;
  LPTMR0_GetTimeElapsed_RetVal                     = 1000000u;
  Dbl_ulTimerSigQty_Unav = 0u;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             2u, == );
  AL_UNITTEST_CHECK(Dbl_ulTimerSigQty_Unav,                    0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount       = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_TIMEOUT
/// \input  LPTMR0_GetTimeElapsed_HitCount                   = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                     = 100u
/// \input  Dbl_ulTimerSigQty_Unav                                = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehPathCurvature_HitCount       = 1u
/// \output Dbl_ulTimerSigQty_Unav                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehPathCurvature_HitCount        = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty  = SIG_TIMEOUT;
  LPTMR0_GetTimeElapsed_HitCount                    = 0u;
  LPTMR0_GetTimeElapsed_RetVal                      = 100u;
  Dbl_ulTimerSigQty_Unav                                 = 0u;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehPathCurvature_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_ulTimerSigQty_Unav,                          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount       = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_DISABLED
/// \input  LPTMR0_GetTimeElapsed_HitCount                   = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                     = 100u
/// \input  Dbl_ulTimerSigQty_Unav                                = 0u
///
/// - Expectations:
///
/// \output Dbl_ulTimerSigQty_Unav                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_8(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehPathCurvature_HitCount       = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_DISABLED;
  LPTMR0_GetTimeElapsed_HitCount                   = 0u;
  LPTMR0_GetTimeElapsed_RetVal                     = 100u;
  Dbl_ulTimerSigQty_Unav                                = 0u;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_ulTimerSigQty_Unav,                          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_9
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                     = SIG_INVALID;
/// \input LPTMR0_GetTimeElapsed_HitCount                                       = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal                                         = 100u;
/// \input Dbl_ulTimerSigQty_Inv                                                    = 0u;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                             = Dbl_SIG_INVALID;
/// \input DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal     = FALSE;
/// \input Rte_Read_SigPrep_YawSpeed_HitCount                                   = 0u;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                         = 0u;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                                = 0u;
/// \input Rte_Read_SysMon_VehNetState_HitCount                                 = 0u;
/// \input DblCrState_boSigQty_TimeoutFlag                                      = FALSE;
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                           = &Coding_Dummy;
/// \input Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 0u;
/// \input Dbl_sCurvatureData.ucCurvatureMode                                   = 0u;
///
/// - Expectations:
///
/// \output Dbl_ulTimerSigQty                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_9(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty                     = SIG_INVALID;
  LPTMR0_GetTimeElapsed_HitCount                                       = 0u;
  LPTMR0_GetTimeElapsed_RetVal                                         = 100u;
  Dbl_ulTimerSigQty_Inv                                                    = 0u;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                             = Dbl_SIG_INVALID;
  DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal     = FALSE;
  Rte_Read_SigPrep_YawSpeed_HitCount                                   = 0u;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                         = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                                 = 0u;
  DblCrState_boSigQty_TimeoutFlag                                      = FALSE;
  Dbl_sCodingParam.psCodingParameters_Blocks                           = &Coding_Dummy;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 0u;
  Dbl_sCurvatureData.ucCurvatureMode                                   = 0u;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_ulTimerSigQty_Inv,                        0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_10
///
/// \Test Case Description
///        - Test subject: Test if calculated curvature stays in unavailable
///          check if the signal is invalid
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
/// \input Dbl_sCurvatureData.ucCurvatureMode                                          = 1u;
/// \input DblCrState_unEgoVehicleMotionConfirmation                                   = 0u;
///
/// - Expectations:
///
/// \output Dbl_sCurvatureData.slCurvatureProcessedValue                             = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_10(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
  Dbl_sCurvatureData.ucCurvatureMode                                          = 1u;
  DblCrState_unEgoVehicleMotionConfirmation                                   = 0u;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_INV();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.slCurvatureProcessedValue, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_11
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is invalid and flag is setted to false
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount       = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_INVALID
/// \input  LPTMR0_GetTimeElapsed_HitCount                   = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                     = 100u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 65535
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy
///
/// - Expectations:
///
/// \output Dbl_ulTimerSigQty_Unav = 0
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_11(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_INVALID;
  LPTMR0_GetTimeElapsed_RetVal = 100u;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 65535;
  Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode = 1u;
  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
  LPTMR0_GetTimeElapsed_RetVal = 1100u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Dbl_Curvature_SigQty_INV();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

   AL_UNITTEST_CHECK(Dbl_ulTimerSigQty_Unav, 0u, == );
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV_TestCase_12
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte and 
///          check if the signal is unavailable and flag is setted to false
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehPathCurvature_HitCount       = 0u
/// \input  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_UNAVAILABLE
/// \input  LPTMR0_GetTimeElapsed_HitCount                   = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                     = 1000000u
/// \input  Dbl_ulTimerSigQty_Unav                                = 0u
/// \input    Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 65535
///
/// - Expectations:
///
/// \output Dbl_ulTimerSigQty_Unav                           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV_TestCase_12(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_SigPrep_VehPathCurvature_HitCount = 0u;
  Rte_Read_SigPrep_VehPathCurvature_Param1.eSigQty = SIG_UNAVAILABLE;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 1000000u;
  Dbl_ulTimerSigQty_Unav = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 65535;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Dbl_Curvature_SigQty_INV();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dbl_ulTimerSigQty_Unav, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Curvature_SigQty_INV
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads the curvature from Rte
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Curvature_SigQty_INV(void)
{
  Mt_Dbl_Curvature_SigQty_INV_TestCase_1();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_2();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_3();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_4();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_5();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_6();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_7();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_8();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_9();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_10();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_11();
  Mt_Dbl_Curvature_SigQty_INV_TestCase_12();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RetPowerTrainActive
/// \Test Case Description
///        - Test subject: Test if function returns the status of the PowerTrain condition
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive         = TRUE
/// \input  Dbl_RetPowerTrainActive_RetVal = FALSE
///
/// - Expectations:
///
/// \output Dbl_RetPowerTrainActive_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RetPowerTrainActive(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive         = TRUE;
  Dbl_RetPowerTrainActive_RetVal = FALSE;

  //Step 3) Call FUT
  Dbl_RetPowerTrainActive_RetVal = Dbl_RetPowerTrainActive();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_RetPowerTrainActive_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ReadFault_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function returns the fault status of the other headlamp
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_ReadFault_Param1                                           = Dbl_eMountedLeft (0u)
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                     = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_VALID (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_True (1u)
///
/// - Expectations:
///
/// \output Dbl_ReadFault_RetVal                                           = TRUE
/// \output Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 1u
/// \output Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                     = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ReadFault_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_ReadFault_Param1                                           = Dbl_eMountedLeft;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                     = 0u;
  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty              = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_True;

  //Step 3) Call FUT
  Dbl_ReadFault_RetVal = Dbl_ReadFault(Dbl_ReadFault_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_ReadFault_RetVal,                        TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ReadFault_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function returns the fault status of the other headlamp
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_ReadFault_Param1                                          = Dbl_eMountedRight (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                   = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_VALID (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_False (0u)
///
/// - Expectations:
///
/// \output Dbl_ReadFault_RetVal                                          = FALSE
/// \output Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                   = 0u
/// \output Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ReadFault_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_ReadFault_Param1                                          = eMountedRight;
  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                   = 0u;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                    = 0u;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eSigQty              = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_LeftStatus_Param1.eDynBendingBeamFault = eDynBendingBeamFault_False;

  //Step 3) Call FUT
  Dbl_ReadFault_RetVal = Dbl_ReadFault(Dbl_ReadFault_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_ReadFault_RetVal,                       FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount,   0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ReadFault
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ReadFault(void)
{
  Mt_Dbl_ReadFault_TestCase_1();
  Mt_Dbl_ReadFault_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DefOfFailure_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function runs the definition of failure flow
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR = FALSE
/// \input  Dbl_boCurvature_SigQty_ERR        = TRUE
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DefOfFailure_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR = FALSE;
  Dbl_boCurvature_SigQty_ERR        = TRUE;

  //Step 3) Call FUT
  Dbl_DefOfFailure();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DefOfFailure_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function runs the definition of failure flow
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Dbl_boCurvature_SigQty_ERR                                        = FALSE
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Dbl_eMountingSide                                                 = Dbl_eMountedLeft (0u)
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                        = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                       = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                 = SIG_VALID (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault    = eDynBendingBeamFault_False (0u)
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DefOfFailure_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR                                = TRUE;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo           = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Dbl_eMountingSide                                                = Dbl_eMountedLeft;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault   = eDynBendingBeamFault_False;

  //Step 3) Call FUT
  Dbl_DefOfFailure();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DefOfFailure_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function runs the definition of failure flow
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Dbl_boCurvature_SigQty_ERR                                        = FALSE
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Dbl_eMountingSide                                                 = Dbl_eMountedLeft (0u)
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                        = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                       = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                 = SIG_VALID (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault    = eDynBendingBeamFault_False (0u)
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR,                                = TRUE
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DefOfFailure_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR                                = TRUE;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo           = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Dbl_eErrorStatus                                                 = eDbl_DynBendingBeamFault_True;
  Dbl_eMountingSide                                                = Dbl_eMountedRight;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault   = eDynBendingBeamFault_False;

  //Step 3) Call FUT
  Dbl_DefOfFailure();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR,   TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DefOfFailure_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function runs the definition of failure flow
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Dbl_boCurvature_SigQty_ERR                                        = FALSE
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Dbl_eMountingSide                                                 = Dbl_eMountedLeft (0u)
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                        = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                       = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                 = SIG_VALID (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault    = eDynBendingBeamFault_False (0u)
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DefOfFailure_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR                                = TRUE;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo           = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Dbl_eMountingSide                                                = Dbl_eMountedUndef;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault   = eDynBendingBeamFault_False;

  //Step 3) Call FUT
  Dbl_DefOfFailure();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR,   TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DefOfFailure_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function runs the definition of failure flow
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Dbl_boCurvature_SigQty_ERR                                        = FALSE
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Dbl_eMountingSide                                                 = Dbl_eMountedLeft (0u)
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                        = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                       = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                 = SIG_VALID (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault    = eDynBendingBeamFault_False (0u)
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DefOfFailure_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR                                = TRUE;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo           = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Dbl_boCurvature_SigQty_ERR                                       = TRUE;
  Dbl_eMountingSide                                                = Dbl_eMountedRight;
  Dbl_eErrorStatus                                                 = eDbl_DynBendingBeamFault_False;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault   = eDynBendingBeamFault_False;

  //Step 3) Call FUT
  Dbl_DefOfFailure();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR,   TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DefOfFailure_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function runs the definition of failure flow
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Dbl_boCurvature_SigQty_ERR                                        = FALSE
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Dbl_eMountingSide                                                 = Dbl_eMountedLeft (0u)
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                        = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                       = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                 = SIG_VALID (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault    = eDynBendingBeamFault_False (0u)
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DefOfFailure_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR                                = TRUE;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo           = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Dbl_boCurvature_SigQty_ERR                                       = TRUE;
  Dbl_eMountingSide                                                = Dbl_eMountedRight;
  Dbl_eErrorStatus                                                 = eDbl_DynBendingBeamFault_True;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault  = eDynBendingBeamFault_False;

  //Step 3) Call FUT
  Dbl_DefOfFailure();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR,   TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DefOfFailure_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function runs the definition of failure flow
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Dbl_boCurvature_SigQty_ERR                                        = FALSE
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Dbl_eMountingSide                                                 = Dbl_eMountedLeft (0u)
/// \input  Rte_Read_SigPrepRx_Dbl_LeftStatus_HitCount                        = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_HitCount                       = 0u
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                 = SIG_VALID (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault    = eDynBendingBeamFault_False (0u)
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DefOfFailure_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u;
  Dbl_boCurvature_SigQty_ERR                                        = FALSE;
  Dbl_eMountingSide                                                 = Dbl_eMountedRight;
  Dbl_eErrorStatus                                                  = eDbl_DynBendingBeamFault_Invalid;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                 = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault    = eDynBendingBeamFault_False;

  //Step 3) Call FUT
  Dbl_DefOfFailure();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DefOfFailure
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DefOfFailure(void)
{
  Mt_Dbl_DefOfFailure_TestCase_1();
  Mt_Dbl_DefOfFailure_TestCase_2();
  Mt_Dbl_DefOfFailure_TestCase_3();
  Mt_Dbl_DefOfFailure_TestCase_4();
  Mt_Dbl_DefOfFailure_TestCase_5();
  Mt_Dbl_DefOfFailure_TestCase_6();
  Mt_Dbl_DefOfFailure_TestCase_7();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_RetDigitalSwivelingFunctionalFault_LR
///
/// \Test Case Description
///        - Test subject: Test if function returns the status of the digital swiveling functional fault
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR                = TRUE
/// \input  Dbl_RetDigitalSwivelingFunctionalFault_LR_RetVal = FALSE
///
/// - Expectations:
///
/// \output Dbl_RetDigitalSwivelingFunctionalFault_LR_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_RetDigitalSwivelingFunctionalFault_LR(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR                = TRUE;
  Dbl_RetDigitalSwivelingFunctionalFault_LR_RetVal = FALSE;

  //Step 3) Call FUT
  Dbl_RetDigitalSwivelingFunctionalFault_LR_RetVal = Dbl_RetDigitalSwivelingFunctionalFault_LR();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_RetDigitalSwivelingFunctionalFault_LR_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DetectMode_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function detects the mode
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client (4u)
/// \input  Dbl_eMainMode                                        = Dbl_eModeAssembly (0u)
///
/// - Expectations:
///
/// \output Dbl_eMainMode                                        = Dbl_eModeCustomer (1u)
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DetectMode_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client;
  Dbl_eMainMode                                        = Dbl_eModeAssembly;

  //Step 3) Call FUT
  Dbl_DetectMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eMainMode,               Dbl_eModeCustomer, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DetectMode_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function detects the mode
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket (6u)
/// \input  Dbl_eMainMode                                        = Dbl_eModeCustomer (1u)
///
/// - Expectations:
///
/// \output Dbl_eMainMode                                        = Dbl_eModeAssembly (0u)
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DetectMode_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
  Dbl_eMainMode                                        = Dbl_eModeCustomer;

  //Step 3) Call FUT
  Dbl_DetectMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eMainMode,               Dbl_eModeAssembly, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DetectMode
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function detects the mode
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DetectMode(void)
{
  Mt_Dbl_DetectMode_TestCase_1();
  Mt_Dbl_DetectMode_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UseMode_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test function path in case of Dbl_eModeAssembly
///          Unit test for underlying function will be done separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMainMode = Dbl_eModeAssembly (0u)
///
/// - Expectations:
///
/// \output Dbl_eSubMode = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UseMode_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMainMode = Dbl_eModeAssembly;

  //Step 3) Call FUT
  Dbl_UseMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eSubMode, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UseMode_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test function path in case of Dbl_eModeCustomer
///          Unit test for underlying function will be done separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMainMode = Dbl_eModeCustomer (1u)
///
/// - Expectations:
///
/// \output Dbl_eSubMode = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UseMode_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMainMode = Dbl_eModeCustomer;

  //Step 3) Call FUT
  Dbl_UseMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eSubMode, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UseMode_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test function path in case of default
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMainMode = 2u
///
/// - Expectations:
///
/// \output Dbl_eSubMode = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UseMode_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMainMode = 2u;

  //Step 3) Call FUT
  Dbl_UseMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eSubMode, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UseMode
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test function path 
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UseMode(void)
{
  Mt_Dbl_UseMode_TestCase_1();
  Mt_Dbl_UseMode_TestCase_2();
  Mt_Dbl_UseMode_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UseSubMode_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test function path in case of Dbl_eSubModeUnavailable
///          Unit test for underlying function will be done separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eSubMode = Dbl_eSubModeUnavailable (0u)
///
/// - Expectations:
///
/// \output
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UseSubMode_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_eSubMode = Dbl_eSubModeUnavailable;

  //Step 3) Call FUT
  Dbl_UseSubMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eSubMode, Dbl_eModeAssembly, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UseSubMode_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test function path in case of Dbl_eSubModeAvailable
///          Unit test for underlying function will be done separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eSubMode = Dbl_eSubModeAvailable (1u)
///
/// - Expectations:
///
/// \output Dbl_eSubMode = Dbl_eSubModeAvailable
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UseSubMode_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_eSubMode = Dbl_eSubModeAvailable;

  //Step 3) Call FUT
  Dbl_UseSubMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eSubMode, Dbl_eSubModeAvailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UseSubMode_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test function path in case of Dbl_eSubModeFrozen
///          Unit test for underlying function will be done separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eSubMode = Dbl_eSubModeFrozen (2u)
///
/// - Expectations:
///
/// \output Dbl_sMsgOut.SwivellingAngle[eLeft].Hor  = 23u
/// \output Dbl_sMsgOut.SwivellingAngle[eRight].Hor = 23u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UseSubMode_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Dbl_eSubMode = Dbl_eSubModeFrozen;

  //Step 3) Call FUT
  Dbl_UseSubMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eLeft].Hor,  23u, == );
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[eRight].Hor, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UseSubMode_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test function path in case of default
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eSubMode = 3u
///
/// - Expectations:
///
/// \outputDbl_eSubMode = Dbl_eModeAssembly
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UseSubMode_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Dbl_eSubMode = 3u;

  //Step 3) Call FUT
  Dbl_UseSubMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eSubMode, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_UseSubMode
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test function path
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_UseSubMode(void)
{
  Mt_Dbl_UseSubMode_TestCase_1();
  Mt_Dbl_UseSubMode_TestCase_2();
  Mt_Dbl_UseSubMode_TestCase_3();
  Mt_Dbl_UseSubMode_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ModeAssembly_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function detects the submode for Assembly mode
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine (1u)
/// \input  Dbl_eSubMode                                         = Dbl_eSubModeUnavailable (0u)
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
/// \output Dbl_eSubMode                                         = Dbl_eSubModeFrozen (2u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ModeAssembly_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
  Dbl_eSubMode                                         = Dbl_eSubModeUnavailable;

  //Step 3) Call FUT
  Dbl_ModeAssembly();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_eSubMode,               Dbl_eSubModeFrozen, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ModeAssembly_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function detects the submode for Assembly mode
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom (5u)
/// \input  Dbl_eSubMode                                         = Dbl_eSubModeAvailable (1u)
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
/// \output Dbl_eSubMode                                         = Dbl_eSubModeAvailable (1u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ModeAssembly_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom;
  Dbl_eSubMode                                         = Dbl_eSubModeAvailable;

  //Step 3) Call FUT
  Dbl_ModeAssembly();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_eSubMode,            Dbl_eSubModeAvailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function detects the submode
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ModeAssembly(void)
{
  Mt_Dbl_ModeAssembly_TestCase_1();
  Mt_Dbl_ModeAssembly_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ModeCustomer_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function detects the submode for Customer mode
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom (5u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Ignition (1u)
/// \input  Dbl_eSubMode                                         = Dbl_eSubModeUnavailable (0u)
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 1u
/// \output Dbl_eSubMode                                         = Dbl_eSubModeAvailable (1u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ModeCustomer_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom;
  Rte_Read_SysMon_VehNetState_HitCount                 = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Ignition;
  Dbl_eSubMode                                         = Dbl_eSubModeUnavailable;

  //Step 3) Call FUT
  Dbl_ModeCustomer();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,       1u, == );
  AL_UNITTEST_CHECK(Dbl_eSubMode,            Dbl_eSubModeAvailable, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ModeCustomer_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function detects the submode for Customer mode
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom (5u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Stop (0u)
/// \input  Dbl_eSubMode                                         = Dbl_eSubModeAvailable (1u)
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 2u
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 2u
/// \output Dbl_eSubMode                                         = Dbl_eSubModeUnavailable (0u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ModeCustomer_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom;
  Rte_Read_SysMon_VehNetState_HitCount                 = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Stop;
  Dbl_eSubMode                                         = Dbl_eSubModeAvailable;

  //Step 3) Call FUT
  Dbl_ModeCustomer();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,       2u, == );
  AL_UNITTEST_CHECK(Dbl_eSubMode, Dbl_eSubModeUnavailable,          == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ModeCustomer_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function detects the submode for Customer mode
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine (1u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Ignition (1u)
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 2u
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ModeCustomer_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
  Rte_Read_SysMon_VehNetState_HitCount                 = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Ignition;

  //Step 3) Call FUT
  Dbl_ModeCustomer();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,       2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ModeCustomer
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function detects the submode
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ModeCustomer(void)
{
  Mt_Dbl_ModeCustomer_TestCase_1();
  Mt_Dbl_ModeCustomer_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_GetSide
///
/// \Test Case Description
///        - Test subject: Test if function gets the Side
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMountingSide        = Dbl_eMountedRight (1u)
/// \input  Dbl_GetSide_RetVal       = Dbl_eMountedLeft (0u)
///
/// - Expectations:
///
/// \output Dbl_GetSide_RetVal       = Dbl_eMountedRight (1u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_GetSide(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMountingSide = Dbl_eMountedRight;
  Dbl_GetSide_RetVal = Dbl_eMountedLeft;

  //Step 3) Call FUT
  Dbl_GetSide_RetVal = Dbl_GetSide();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_GetSide_RetVal, Dbl_eMountedRight, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_GetTrafficSide
///
/// \Test Case Description
///        - Test subject: Test if function gets the Traffic Side
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                 = 0u
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType     = eTypeDir_SteeringLeft (2u)
/// \input  Dbl_GetTrafficSide_RetVal                             = RightHandTraffic (1u)
///
/// - Expectations:
///
/// \output Dbl_GetTrafficSide_RetVal                             = LeftHandTraffic (2u)
///
//-----------------------------------------------------------------------------
void Mt_Dbl_GetTrafficSide(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_DynamicSigs_HitCount             = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSteeringType = eTypeDir_SteeringLeft;
  Dbl_GetTrafficSide_RetVal                         = RightHandTraffic;

  //Step 3) Call FUT
  Dbl_GetTrafficSide_RetVal = Dbl_GetTrafficSide();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_GetTrafficSide_RetVal, LeftHandTraffic, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_GetHBStatus
///
/// \Test Case Description
///        - Test subject: Test if function gets the status of HB
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boHB                 = TRUE
/// \input  Dbl_GetHBStatus_RetVal   = FALSE
///
/// - Expectations:
///
/// \output Dbl_GetHBStatus_RetVal   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_GetHBStatus(void)
{
  //Step 1) Set pre-conditions
  Dbl_boHB               = TRUE;
  Dbl_GetHBStatus_RetVal = FALSE;

  //Step 3) Call FUT
  Dbl_GetHBStatus_RetVal = Dbl_GetHBStatus();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_GetHBStatus_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Assembly_To_Frozen_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Montage (0u)
/// \input  Dbl_Transition_Assembly_To_Frozen_RetVal             = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
/// \output Dbl_Transition_Assembly_To_Frozen_RetVal             = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Assembly_To_Frozen_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Montage;
  Dbl_Transition_Assembly_To_Frozen_RetVal             = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Assembly_To_Frozen_RetVal = Dbl_Transition_Assembly_To_Frozen();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Assembly_To_Frozen_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Assembly_To_Frozen_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Stockage (3u)
/// \input  Dbl_Transition_Assembly_To_Frozen_RetVal             = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
/// \output Dbl_Transition_Assembly_To_Frozen_RetVal             = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Assembly_To_Frozen_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Stockage;
  Dbl_Transition_Assembly_To_Frozen_RetVal             = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Assembly_To_Frozen_RetVal = Dbl_Transition_Assembly_To_Frozen();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Assembly_To_Frozen_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Assembly_To_Frozen
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Assembly_To_Frozen(void)
{
  Mt_Dbl_Transition_Assembly_To_Frozen_TestCase_1();
  Mt_Dbl_Transition_Assembly_To_Frozen_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Customer_To_Unavailable_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client (4u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Stop (0u)
/// \input  Dbl_Transition_Customer_To_Unavailable_RetVal        = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 1u
/// \output Dbl_Transition_Customer_To_Unavailable_RetVal        = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Customer_To_Unavailable_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client;
  Rte_Read_SysMon_VehNetState_HitCount                 = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Stop;
  Dbl_Transition_Customer_To_Unavailable_RetVal        = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Customer_To_Unavailable_RetVal = Dbl_Transition_Customer_To_Unavailable();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount,      1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Customer_To_Unavailable_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Customer_To_Unavailable_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount        = 0u;
/// \input  Rte_Read_SysMon_VehNetState_HitCount              = 0u;
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty        = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState  = VESState_Start (2u)
/// \input  Dbl_Transition_Customer_To_Unavailable_RetVal     = FALSE;
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount        = 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount              = 1u
/// \output Dbl_Transition_Customer_To_Unavailable_RetVal     = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Customer_To_Unavailable_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount       = 0u;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty       = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;
  Dbl_Transition_Customer_To_Unavailable_RetVal    = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Customer_To_Unavailable_RetVal = Dbl_Transition_Customer_To_Unavailable();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount,       1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Customer_To_Unavailable_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Customer_To_Unavailable
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Customer_To_Unavailable(void)
{
  Mt_Dbl_Transition_Customer_To_Unavailable_TestCase_1();
  Mt_Dbl_Transition_Customer_To_Unavailable_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Customer_To_Available_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client (4u)
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Start (2u)
/// \input  Dbl_Transition_Customer_To_Available_RetVal          = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 1u
/// \output Dbl_Transition_Customer_To_Available_RetVal          = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Customer_To_Available_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty     = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client;
  Rte_Read_SysMon_VehNetState_HitCount                 = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Start;
  Dbl_Transition_Customer_To_Available_RetVal          = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Customer_To_Available_RetVal = Dbl_Transition_Customer_To_Available();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Customer_To_Available_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Customer_To_Available_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 0u
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty           = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Stop (0u)
/// \input  Dbl_Transition_Customer_To_Available_RetVal          = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount           = 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 1u
/// \output Dbl_Transition_Customer_To_Available_RetVal          = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Customer_To_Available_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_VehicleConfigSig_HitCount       = 0u;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty       = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Stop;
  Dbl_Transition_Customer_To_Available_RetVal      = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Customer_To_Available_RetVal = Dbl_Transition_Customer_To_Available();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Customer_To_Available_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Customer_To_Available
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Customer_To_Available(void)
{
  Mt_Dbl_Transition_Customer_To_Available_TestCase_1();
  Mt_Dbl_Transition_Customer_To_Available_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Fail_To_Init_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive                                            = FALSE
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
///
/// - Expectations:
///
/// \output Dbl_boErrorFromOtherHL                                            = FALSE
/// \output Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \output Dbl_Transition_Fail_To_Init_RetVal                                = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Fail_To_Init_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive            = FALSE;
  Dbl_boSwivelingFunctionalFault_LR = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Fail_To_Init_RetVal = Dbl_Transition_Fail_To_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boErrorFromOtherHL,            FALSE, == );
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR, FALSE, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Fail_To_Init_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Fail_To_Init_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive                                            = TRUE
/// \input  Dbl_Transition_Fail_To_Init_RetVal                                = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Fail_To_Init_RetVal                                = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Fail_To_Init_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive             = TRUE;
  Dbl_Transition_Fail_To_Init_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Fail_To_Init_RetVal = Dbl_Transition_Fail_To_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Fail_To_Init_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Fail_To_Init
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Fail_To_Init(void)
{
  Mt_Dbl_Transition_Fail_To_Init_TestCase_1();
  Mt_Dbl_Transition_Fail_To_Init_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Init_To_Nominal_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u
/// \input  Dbl_boPowertrainActive                                           = TRUE
/// \input  Dbl_boCurvature_SigQty_ERR                                       = FALSE
/// \input  Dbl_boSwivelingFunctionalFault_LR                                = FALSE
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                             = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                             = 1u
/// \input  Dbl_Transition_Init_To_Nominal_RetVal                            = FALSE
///
/// - Expectations:
///
/// \output Dbl_Transition_Init_To_Nominal_RetVal                            = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Init_To_Nominal_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Dbl_boPowertrainActive                                           = TRUE;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Dbl_boSwivelingFunctionalFault_LR                                = FALSE;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                             = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                             = 1u;
  Dbl_sCodingParam.psCodingParameters_Blocks                       = &Coding_Dummy;
  Dbl_Transition_Init_To_Nominal_RetVal                            = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Init_To_Nominal_RetVal = Dbl_Transition_Init_To_Nominal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Init_To_Nominal_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Init_To_Nominal_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive                                           = FALSE
/// \input  Dbl_boCurvature_SigQty_ERR                                       = FALSE
/// \input  Dbl_Transition_Init_To_Nominal_RetVal                            = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Init_To_Nominal_RetVal                            = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Init_To_Nominal_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive                = FALSE;
  Dbl_boCurvature_SigQty_ERR            = FALSE;
  Dbl_Transition_Init_To_Nominal_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Init_To_Nominal_RetVal = Dbl_Transition_Init_To_Nominal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Init_To_Nominal_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Init_To_Nominal(void)
{
  Mt_Dbl_Transition_Init_To_Nominal_TestCase_1();
  Mt_Dbl_Transition_Init_To_Nominal_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Fail_To_Nominal_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Dbl_eMountingSide                                                 = Dbl_eMountedLeft (0u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                 = SIG_VALID (1u)
/// \input  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault    = eDynBendingBeamFault_True (1u)
/// \input  Dbl_boPowertrainActive                                            = TRUE
/// \input  Dbl_boCurvature_SigQty_ERR                                        = TRUE
/// \input  Dbl_boErrorFromOtherHL                                            = FALSE
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                              = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                              = 1u
/// \input  Dbl_Transition_Fail_To_Nominal_RetVal                             = FALSE
///
/// - Expectations:
///
/// \output Dbl_boErrorFromOtherHL                                            = FALSE
/// \output Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \output Dbl_Transition_Fail_To_Nominal_RetVal                             = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Fail_To_Nominal_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Dbl_eMountingSide                                                = Dbl_eMountedLeft;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eSigQty                = SIG_VALID;
  Rte_Read_SigPrepRx_Dbl_RightStatus_Param1.eDynBendingBeamFault   = eDynBendingBeamFault_True;
  Dbl_boSwivelingFunctionalFault_LR                                = FALSE;
  Dbl_boPowertrainActive                                           = TRUE;
  Dbl_boCurvature_UNAV                                             = TRUE;
  Dbl_boCurvature_SigQty_ERR                                       = TRUE;
  Dbl_boErrorFromOtherHL                                           = FALSE;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                             = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                             = 1u;
  Dbl_sCodingParam.psCodingParameters_Blocks                       = &Coding_Dummy;

  //Step 3) Call FUT
  Dbl_Transition_Fail_To_Nominal_RetVal = Dbl_Transition_Fail_To_Nominal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boErrorFromOtherHL,               FALSE, == );
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR,    FALSE, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Fail_To_Nominal_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Fail_To_Nominal_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive                                            = FALSE
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Dbl_Transition_Fail_To_Nominal_RetVal                             = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Fail_To_Nominal_RetVal                             = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Fail_To_Nominal_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive                = FALSE;
  Dbl_boSwivelingFunctionalFault_LR     = TRUE;
  Dbl_Transition_Fail_To_Nominal_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Fail_To_Nominal_RetVal = Dbl_Transition_Fail_To_Nominal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Fail_To_Nominal_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Fail_To_Nominal
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Fail_To_Nominal(void)
{
  Mt_Dbl_Transition_Fail_To_Nominal_TestCase_1();
  Mt_Dbl_Transition_Fail_To_Nominal_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Adj_To_Nominal_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_FctR_AfsDblCmd_Param1.Primary                            = 3u
/// \input  Dbl_boHB                                                          = FALSE
/// \input  Dbl_Transition_Adj_To_Nominal_RetVal                              = FALSE
/// \input  Dbl_boCurvature_UNAV                                              = FALSE
///
/// - Expectations:
///
/// \output Dbl_Transition_Adj_To_Nominal_RetVal                              = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Adj_To_Nominal_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_FctR_AfsDblCmd_Param1.Primary = 3u;
  Dbl_boCurvature_UNAV                   = FALSE;
  Dbl_boHB                               = FALSE;
  Dbl_Transition_Adj_To_Nominal_RetVal   = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Adj_To_Nominal_RetVal = Dbl_Transition_Adj_To_Nominal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Adj_To_Nominal_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Adj_To_Nominal_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty                      = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition               = eInhEclairageVirageDyn_NoInhibition (0u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                  = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eEtatMar                 = eEtatMar_Forward (0u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Rte_Read_FctR_AfsDblCmd_Param1.Primary                            = 3u
/// \input  Dbl_boHB                                                          = TRUE
/// \input  Dbl_boCurvature_SigQty_ERR                                        = FALSE
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                              = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                              = 5u
/// \input  Dbl_Transition_Adj_To_Nominal_RetVal                              = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Adj_To_Nominal_RetVal                              = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Adj_To_Nominal_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty                     = SIG_VALID;
  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition              = eInhEclairageVirageDyn_NoInhibition;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                 = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eEtatMar                = eEtatMar_Forward;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Rte_Read_FctR_AfsDblCmd_Param1.Primary                           = 3u;
  Dbl_boHB                                                         = TRUE;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                             = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                             = 5u;
  Dbl_sCodingParam.psCodingParameters_Blocks                       = &Coding_Dummy;
  Dbl_Transition_Adj_To_Nominal_RetVal                             = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Adj_To_Nominal_RetVal = Dbl_Transition_Adj_To_Nominal();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Adj_To_Nominal_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ClIdleRange
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Adj_To_Nominal(void)
{
  Mt_Dbl_Transition_Adj_To_Nominal_TestCase_1();
  Mt_Dbl_Transition_Adj_To_Nominal_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Nominal_To_Adj_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty                      = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition               = eInhEclairageVirageDyn_NoInhibition (0u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                  = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eEtatMar                 = eEtatMar_Forward (0u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Rte_Read_FctR_AfsDblCmd_Param1.Primary                            = 1u
/// \input  Dbl_boHB                                                          = FALSE
/// \input  Dbl_boPowertrainActive                                            = TRUE
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                              = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                              = 5u
/// \input  Dbl_Transition_Nominal_To_Adj_RetVal                              = FALSE
///
/// - Expectations:
///
/// \output Dbl_Transition_Nominal_To_Adj_RetVal                              = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Nominal_To_Adj_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty                     = SIG_VALID;
  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition              = eInhEclairageVirageDyn_NoInhibition;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                 = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eEtatMar                = eEtatMar_Forward;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Rte_Read_FctR_AfsDblCmd_Param1.Primary                           = 1u;
  Dbl_boHB                                                         = FALSE;
  Dbl_boPowertrainActive                                           = TRUE;
  Dbl_boSwivelingFunctionalFault_LR                                = FALSE;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                             = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                             = 5u;
  Dbl_boCurvature_UNAV                                             = FALSE;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Dbl_sCodingParam.psCodingParameters_Blocks                       = &Coding_Dummy;
  Dbl_Transition_Nominal_To_Adj_RetVal                             = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Nominal_To_Adj_RetVal = Dbl_Transition_Nominal_To_Adj();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Nominal_To_Adj_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Nominal_To_Adj_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive                                            = FALSE
/// \input  Dbl_Transition_Nominal_To_Adj_RetVal                              = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Nominal_To_Adj_RetVal                              = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Nominal_To_Adj_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive               = FALSE;
  Dbl_Transition_Nominal_To_Adj_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Nominal_To_Adj_RetVal = Dbl_Transition_Nominal_To_Adj();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Nominal_To_Adj_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Nominal_To_Adj
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Nominal_To_Adj(void)
{
  Mt_Dbl_Transition_Nominal_To_Adj_TestCase_1();
  Mt_Dbl_Transition_Nominal_To_Adj_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Init_To_Adj_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty                      = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition               = eInhEclairageVirageDyn_NoInhibition (0u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                  = SIG_VALID (1u)
/// \input  Rte_Read_SigPrep_VehicleConfigSig_Param1.eEtatMar                 = eEtatMar_Forward (0u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u
/// \input  Rte_Read_FctR_AfsDblCmd_Param1.Primary                            = 1u
/// \input  Dbl_boHB                                                          = FALSE
/// \input  Dbl_boPowertrainActive                                            = TRUE
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                              = 0u
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                              = 5u
/// \input  Dbl_Transition_Init_To_Adj_RetVal                                 = FALSE
///
/// - Expectations:
///
/// \output Dbl_Transition_Init_To_Adj_RetVal                                 = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Init_To_Adj_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty                     = SIG_VALID;
  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition              = eInhEclairageVirageDyn_NoInhibition;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty                 = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eEtatMar                = eEtatMar_Forward;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Rte_Read_FctR_AfsDblCmd_Param1.Primary                           = 1u;
  Dbl_boCurvature_UNAV                                             = FALSE;
  Dbl_boHB                                                         = TRUE;
  Dbl_boPowertrainActive                                           = TRUE;
  Dbl_boSwivelingFunctionalFault_LR                                = FALSE;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                             = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                             = 5u;
  Dbl_sCodingParam.psCodingParameters_Blocks                       = &Coding_Dummy;
  Dbl_Transition_Init_To_Adj_RetVal                                = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Init_To_Adj_RetVal = Dbl_Transition_Init_To_Adj();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Init_To_Adj_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Init_To_Adj_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Dbl_Transition_Init_To_Adj_RetVal                                 = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Init_To_Adj_RetVal                                 = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Init_To_Adj_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR = TRUE;
  Dbl_Transition_Init_To_Adj_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Init_To_Adj_RetVal = Dbl_Transition_Init_To_Adj();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Init_To_Adj_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Init_To_Adj
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Init_To_Adj(void)
{
  Mt_Dbl_Transition_Init_To_Adj_TestCase_1();
  Mt_Dbl_Transition_Init_To_Adj_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Fail_To_Adj_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 300u;
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty                      = SIG_VALID;
/// \input  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition               = eInhEclairageVirageDyn_NoInhibition;
/// \input  Dbl_boEtatMar                                                     = FALSE;
/// \input  Dbl_boCurvature_UNAV                                              = FALSE;
/// \input  Dbl_boCurvature_SigQty_ERR                                        = FALSE;
/// \input  Dbl_boPowertrainActive                                            = TRUE;
/// \input  Dbl_boErrorFromOtherHL                                            = TRUE;
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = FALSE;
/// \input  Rte_Read_FctR_AfsDblCmd_Param1.Primary                            = 1u;
/// \input  Dbl_boHB                                                          = TRUE;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                              = 0u;
/// \input  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                              = 1u;
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks                        = &Coding_Dummy;
/// \input  Dbl_Transition_Fail_To_Adj_RetVal                                 = FALSE;
///
/// - Expectations:
///
/// \output Dbl_boErrorFromOtherHL                                            = FALSE
/// \output Dbl_boSwivelingFunctionalFault_LR                                 = FALSE
/// \output Dbl_Transition_Fail_To_Adj_RetVal                                 = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Fail_To_Adj_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 300u;
  Rte_Read_SigPrep_EnvCondition_Param1.eSigQty                     = SIG_VALID;
  Rte_Read_SigPrep_EnvCondition_Param1.eDblInhibition              = eInhEclairageVirageDyn_NoInhibition;
  Dbl_boEtatMar                                                    = FALSE;
  Dbl_boCurvature_UNAV                                             = FALSE;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;
  Dbl_boPowertrainActive                                           = TRUE;
  Dbl_boErrorFromOtherHL                                           = TRUE;
  Dbl_boSwivelingFunctionalFault_LR                                = FALSE;
  Rte_Read_FctR_AfsDblCmd_Param1.Primary                           = 1u;
  Dbl_boHB                                                         = TRUE;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV0                             = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.ucV4                             = 1u;
  Dbl_sCodingParam.psCodingParameters_Blocks                       = &Coding_Dummy;
  Dbl_Transition_Fail_To_Adj_RetVal                                = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Fail_To_Adj_RetVal = Dbl_Transition_Fail_To_Adj();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boErrorFromOtherHL,            FALSE, == );
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR, FALSE, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Fail_To_Adj_RetVal,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Fail_To_Adj_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR                                 = TRUE
/// \input  Dbl_Transition_Fail_To_Adj_RetVal                                 = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Fail_To_Adj_RetVal                                 = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Fail_To_Adj_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR = TRUE;
  Dbl_Transition_Fail_To_Adj_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Fail_To_Adj_RetVal = Dbl_Transition_Fail_To_Adj();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Fail_To_Adj_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Fail_To_Adj
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Fail_To_Adj(void)
{
  Mt_Dbl_Transition_Fail_To_Adj_TestCase_1();
  Mt_Dbl_Transition_Fail_To_Adj_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Init_To_Fail_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR  = TRUE
/// \input  Dbl_Transition_Init_To_Fail_RetVal = FALSE
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR  = TRUE
/// \output Dbl_Transition_Init_To_Fail_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Init_To_Fail_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR  = TRUE;
  Dbl_Transition_Init_To_Fail_RetVal = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Init_To_Fail_RetVal = Dbl_Transition_Init_To_Fail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR,  TRUE, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Init_To_Fail_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Init_To_Fail_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR  = FALSE
/// \input  Dbl_Transition_Init_To_Fail_RetVal = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Init_To_Fail_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Init_To_Fail_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR  = FALSE;
  Dbl_Transition_Init_To_Fail_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Init_To_Fail_RetVal = Dbl_Transition_Init_To_Fail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Init_To_Fail_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Init_To_Fail
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Init_To_Fail(void)
{
  Mt_Dbl_Transition_Init_To_Fail_TestCase_1();
  Mt_Dbl_Transition_Init_To_Fail_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Nominal_To_Fail_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR     = TRUE
/// \input  Dbl_Transition_Nominal_To_Fail_RetVal = FALSE
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR     = TRUE
/// \output Dbl_Transition_Nominal_To_Fail_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Nominal_To_Fail_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR     = TRUE;
  Dbl_Transition_Nominal_To_Fail_RetVal = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Nominal_To_Fail_RetVal = Dbl_Transition_Nominal_To_Fail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR,     TRUE, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Nominal_To_Fail_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Nominal_To_Fail_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR     = FALSE
/// \input  Dbl_Transition_Nominal_To_Fail_RetVal = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Nominal_To_Fail_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Nominal_To_Fail_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR     = FALSE;
  Dbl_Transition_Nominal_To_Fail_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Nominal_To_Fail_RetVal = Dbl_Transition_Nominal_To_Fail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Nominal_To_Fail_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Nominal_To_Fail
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Nominal_To_Fail(void)
{
  Mt_Dbl_Transition_Nominal_To_Fail_TestCase_1();
  Mt_Dbl_Transition_Nominal_To_Fail_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Adj_To_Fail_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR = TRUE
/// \input  Dbl_Transition_Adj_To_Fail_RetVal = FALSE
///
/// - Expectations:
///
/// \output Dbl_boSwivelingFunctionalFault_LR = TRUE
/// \output Dbl_Transition_Adj_To_Fail_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Adj_To_Fail_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR = TRUE;
  Dbl_Transition_Adj_To_Fail_RetVal = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Adj_To_Fail_RetVal = Dbl_Transition_Adj_To_Fail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boSwivelingFunctionalFault_LR, TRUE, == );
  AL_UNITTEST_CHECK(Dbl_Transition_Adj_To_Fail_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Adj_To_Fail_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boSwivelingFunctionalFault_LR = FALSE
/// \input  Dbl_Transition_Adj_To_Fail_RetVal = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Adj_To_Fail_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Adj_To_Fail_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boSwivelingFunctionalFault_LR = FALSE;
  Dbl_Transition_Adj_To_Fail_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Adj_To_Fail_RetVal = Dbl_Transition_Adj_To_Fail();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Adj_To_Fail_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Adj_To_Fail
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Adj_To_Fail(void)
{
  Mt_Dbl_Transition_Adj_To_Fail_TestCase_1();
  Mt_Dbl_Transition_Adj_To_Fail_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ReadEnvironmentSignals_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reads the RTE environmental signals
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_HitCount                     = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL (5u)
/// \input  Dbl_boPowertrainActive                                   = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount                     = 1u
/// \output Dbl_boPowertrainActive                                   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ReadEnvironmentSignals_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehNetState_HitCount                     = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
  Dbl_boPowertrainActive                                   = FALSE;

  //Step 3) Call FUT
  Dbl_ReadEnvironmentSignals();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_boPowertrainActive,             TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ReadEnvironmentSignals_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reads the RTE environmental signals
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_HitCount                     = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID (1u)
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTI_NOMINAL (0u)
/// \input  Dbl_boPowertrainActive                                   = TRUE
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount                     = 1u
/// \output Dbl_boPowertrainActive                                   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ReadEnvironmentSignals_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehNetState_HitCount                     = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTI_NOMINAL;
  Dbl_boPowertrainActive                                   = TRUE;

  //Step 3) Call FUT
  Dbl_ReadEnvironmentSignals();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_boPowertrainActive,            FALSE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ReadEnvironmentSignals
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads the RTE environmental signals
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ReadEnvironmentSignals(void)
{
  Mt_Dbl_ReadEnvironmentSignals_TestCase_1();
  Mt_Dbl_ReadEnvironmentSignals_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_DetectSide
///
/// \Test Case Description
///        - Test subject: Test if function reads ECU side
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft (0u)
/// \input  Dbl_eMountingSide                            = 1u
/// \input  
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
/// \output Dbl_eMountingSide                            = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_DetectSide(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft;
  Dbl_eMountingSide                            = 1u;

  //Step 3) Call FUT
  Dbl_DetectSide();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_eMountingSide,                            0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Init
///
/// \Test Case Description
///        - Test subject: Wrapper function - main functions to be tested separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input
///
/// - Expectations:
///
/// \output Dbl_RteAccess_Read_EcuSide_Param1 = 1u;
///
//-----------------------------------------------------------------------------





void Mt_Dbl_Init(void)
{
  //Step 1) Set pre-conditions

  //Step 3) Call FUT
  Dbl_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_RteAccess_Read_EcuSide_Param1, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Cycle_TestCase_1
///
/// \Test Case Description
///        - Test subject: Wrapper function - main functions to be tested separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input
///
/// - Expectations:
///
/// \output Dbl_boCurvature_UNAV = 0u;
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Cycle_TestCase_1(void)
{
  //Step 1) Set pre-conditions

  //Step 3) Call FUT
  Dbl_Cycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boCurvature_UNAV, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Cycle_TestCase_1
///
/// \Test Case Description
///        - Test subject: Wrapper function - main functions to be tested separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input
///  Dbl_sCodingParam.eCodingState =  eParaFct0_CodingDataInvalid
/// - Expectations:
///
/// \output Dbl_boCurvature_UNAV = 0u;
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Cycle_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sCodingParam.eCodingState = eParaFct0_CodingDataInvalid;

  //Step 3) Call FUT
  Dbl_Cycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boCurvature_UNAV, 0u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Dbl_Cycle
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Wrapper function 
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Cycle(void)
{
  Mt_Dbl_Cycle_TestCase_1();
  Mt_Dbl_Cycle_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_riDbl_Init
///
/// \Test Case Description
///        - Test subject: Wrapper function - main functions to be tested separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input
///
/// - Expectations:
///
/// \output Dbl_RteAccess_Read_EcuSide_Param1 = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Dbl_riDbl_Init(void)
{
  //Step 1) Set pre-conditions

  //Step 3) Call FUT
  riDbl_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_RteAccess_Read_EcuSide_Param1, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_riDbl_Init
///
/// \Test Case Description
///        - Test subject: Wrapper function - main functions to be tested separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input
///
/// - Expectations:
///
/// \output Dbl_boCurvature_UNAV = 0u;
///
//-----------------------------------------------------------------------------
void Mt_Dbl_rpDbl_Cycle(void)
{
  //Step 1) Set pre-conditions

  //Step 3) Call FUT
  rpDbl_Cycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boCurvature_UNAV, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_riDbl_Init
///
/// \Test Case Description
///        - Test subject: Wrapper function - main functions to be tested separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Dbl_sState.boEntry = FALSE
///
/// - Expectations:
///
/// \output  Dbl_sState.boEntry = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StMch_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_sState.boEntry = FALSE;

  //Step 3) Call FUT
  Dbl_StMch();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sState.boEntry, TRUE, == );
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_rpDbl_Cycle_TestCase_2
///
/// \Test Case Description
///        - Test subject: Wrapper function - main functions to be tested separately
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input Dbl_sState.boEntry = FALSE
/// \input Dbl_sState.eMain   = Dbl_eState_Init
///
/// - Expectations:
///
/// \output  Dbl_sState.boEntry = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StMch_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_sState.boEntry = FALSE;
  for (uint8 ucIx = 0; ucIx < Dbl_atStateMachine[(uint8)Dbl_sState.eMain].ucCount; ucIx++)
  {
    Dbl_atStateMachine[(uint8)Dbl_sState.eMain].pTransition[ucIx].ptTransitionFct() == FALSE;

    // change current state 
    Dbl_sState.eMain = Dbl_eState_Init;
    // mark new state as entered
    Dbl_sState.boEntry = TRUE;

  }
  //Step 3) Call FUT
  Dbl_StMch();
  Dbl_StMch();
  Dbl_StMch();
  Dbl_StMch();
  Dbl_StMch();
  Dbl_StMch();
  Dbl_StMch();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sState.boEntry, TRUE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_StMch
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Wrapper
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_StMch(void)
{
  Mt_Dbl_StMch_TestCase_1();
  Mt_Dbl_StMch_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Read_PhaseVie_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test the status for the flag that indicate if the ecu is in normal mode
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_LifePhases_Param1.eSigQty   = SIG_VALID
/// \input  Rte_Read_SysMon_LifePhases_HitCount         = 0u
/// \input  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie = eNormalMode
/// \input  
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_LifePhases_HitCount        = 1u
/// \output Dbl_Read_PhaseVie_RetVal                   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Read_PhaseVie_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_LifePhases_HitCount         = 0u;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie = eNormalMode;
  Rte_Read_SysMon_LifePhases_Param1.eSigQty   = SIG_VALID;

  //Step 3) Call FUT
  Dbl_Read_PhaseVie_RetVal = Dbl_Read_PhaseVie();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_Read_PhaseVie_RetVal,          TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Read_PhaseVie_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test the status for the flag that indicate if the ecu is in normal mode
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_LifePhases_Param1.eSigQty   = SIG_INVALID
/// \input  Rte_Read_SysMon_LifePhases_HitCount         = 0u
/// \input  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie = eNormalMode
/// \input  
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_LifePhases_HitCount        = 1u
/// \output Dbl_Read_PhaseVie_RetVal                   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Read_PhaseVie_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_LifePhases_HitCount         = 0u;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie = eNormalMode;
  Rte_Read_SysMon_LifePhases_Param1.eSigQty   = SIG_INVALID;

  //Step 3) Call FUT
  Dbl_Read_PhaseVie_RetVal = Dbl_Read_PhaseVie();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dbl_Read_PhaseVie_RetVal,         FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Read_PhaseVie
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Read_PhaseVie(void)
{
  Mt_Dbl_Read_PhaseVie_TestCase_1();
  Mt_Dbl_Read_PhaseVie_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ReadInputSignals_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test is the function is setting/desetting the corresponding DTC in case of curvature invalid or time loss
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                        = SIG_VALID
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed   = 555u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo             = eVvhIndisp_SpeedInfoAvailable
/// \input  Dbl_boCurvature_SigQty_ERR                                         = TRUE
/// \input  
///
/// - Expectations:
///
/// \output Dbl_eErrorStatus                 = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ReadInputSignals_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 555u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo           = eVvhIndisp_SpeedInfoAvailable;
  Dbl_boCurvature_SigQty_ERR                                       = TRUE;

  //Step 3) Call FUT
  Dbl_ReadInputSignals();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eErrorStatus, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ReadInputSignals_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test is the function is setting/desetting the corresponding DTC in case of curvature invalid or time loss
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                        = SIG_VALID
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed   = 555u
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo             = eVvhIndisp_SpeedInfoAvailable
/// \input  Dbl_boCurvature_SigQty_ERR                                         = FALSE
/// \input  
///
/// - Expectations:
///
/// \output Dbl_eErrorStatus                 = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ReadInputSignals_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 555u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo           = eVvhIndisp_SpeedInfoAvailable;
  Dbl_boCurvature_SigQty_ERR                                       = FALSE;

  //Step 3) Call FUT
  Dbl_ReadInputSignals();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_eErrorStatus, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_ReadInputSignals
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test is the function is setting/desetting the corresponding DTC 
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_ReadInputSignals(void)
{
  Mt_Dbl_ReadInputSignals_TestCase_1();
  Mt_Dbl_ReadInputSignals_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Adj_To_Init_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive     = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Adj_To_Init_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Adj_To_Init_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Adj_To_Init_RetVal = Dbl_Transition_Adj_To_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Adj_To_Init_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Adj_To_Init_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive     = FALSE
///
/// - Expectations:
///
/// \output Dbl_Transition_Adj_To_Init_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Adj_To_Init_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Adj_To_Init_RetVal = Dbl_Transition_Adj_To_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Adj_To_Init_RetVal, TRUE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Adj_To_Init
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates the Idle range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Adj_To_Init(void)
{
  Mt_Dbl_Transition_Adj_To_Init_TestCase_1();
  Mt_Dbl_Transition_Adj_To_Init_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Nominal_To_Init_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive     = TRUE
///
/// - Expectations:
///
/// \output Dbl_Transition_Nominal_To_Init_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Nominal_To_Init_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive = TRUE;

  //Step 3) Call FUT
  Dbl_Transition_Nominal_To_Init_RetVal = Dbl_Transition_Nominal_To_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Nominal_To_Init_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Nominal_To_Init_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boPowertrainActive     = FALSE
///
/// - Expectations:
///
/// \output Dbl_Transition_Nominal_To_Init_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Nominal_To_Init_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Dbl_boPowertrainActive = FALSE;

  //Step 3) Call FUT
  Dbl_Transition_Nominal_To_Init_RetVal = Dbl_Transition_Nominal_To_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_Transition_Nominal_To_Init_RetVal, TRUE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Transition_Nominal_To_Init
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Transition_Nominal_To_Init(void)
{
  Mt_Dbl_Transition_Nominal_To_Init_TestCase_1();
  Mt_Dbl_Transition_Nominal_To_Init_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Call_StateFailure
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_eMountingSide     = Dbl_eMountedUndef
///
/// - Expectations:
///
/// \output Dbl_sMsgOut.SwivellingAngle[0].Hor = 0
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Call_StateFailure(void)
{
  //Step 1) Set pre-conditions
  Dbl_eMountingSide = Dbl_eMountedUndef;

  //Step 3) Call FUT
  Dbl_Call_StateFailure();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_sMsgOut.SwivellingAngle[0].Hor, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_SmoothTransition
///
/// \Test Case Description
///        - Test subject: Test if function does the transition check
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_SmoothTransition_Param1 = 0u
/// \input  Dbl_SmoothTransition_Param2 = 5u
///
/// - Expectations:
///
/// \output Dbl_SmoothTransition_RetVal = 5u
///
//-----------------------------------------------------------------------------
void Mt_Dbl_SmoothTransition(void)
{
  //Step 1) Set pre-conditions
  Dbl_SmoothTransition_Param1 = 0u;
  Dbl_SmoothTransition_Param2 = 5u;

  //Step 3) Call FUT
  Dbl_SmoothTransition_RetVal = Dbl_SmoothTransition(Dbl_SmoothTransition_Param1, Dbl_SmoothTransition_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_SmoothTransition_RetVal, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dbl_Reset_Flags
///
/// \Test Case Description
///        - Test subject: Test if function does reset error flag
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dbl_boFailureTimerFlag_Unav = TRUE
/// \input  Dbl_boFailureTimerFlag_Inv = TRUE
///
/// - Expectations:
///
/// \output Dbl_boFailureTimerFlag_Unav = FALSE
/// \output Dbl_boFailureTimerFlag_Inv = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dbl_Reset_Flags(void)
{
  //Step 1) Set pre-conditions
  Dbl_boFailureTimerFlag_Unav = TRUE;
  Dbl_boFailureTimerFlag_Inv  = TRUE;

  //Step 3) Call FUT
  Dbl_Reset_Flags();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dbl_boFailureTimerFlag_Unav, FALSE, == );
  AL_UNITTEST_CHECK(Dbl_boFailureTimerFlag_Inv, FALSE, == );
}





//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_Get_CurvatureCodingParameters
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets correct coding parameters for curvature calculation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                          = &Coding_Dummy
/// \input Coding_Dummy.Dbl.DblCurvatureCalculation.unCRC_STEERING_RATIO       = 1u
/// \input Coding_Dummy.Dbl.DblCurvatureCalculation.unCRC_VEHICLE_WHEELBASE    = 1u
///
/// - Expectations:
///
/// \output Coding_Dummy.Dbl.DblCurvatureCalculation.unCRC_STEERING_RATIO       = 1u
/// \output Coding_Dummy.Dbl.DblCurvatureCalculation.unCRC_VEHICLE_WHEELBASE    = 1u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_Get_CurvatureCodingParameters(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_sCodingParam.psCodingParameters_Blocks                          = &Coding_Dummy;
  Coding_Dummy.Dbl.DblCurvatureCalculation.unCRC_STEERING_RATIO       = 1u;
  Coding_Dummy.Dbl.DblCurvatureCalculation.unCRC_VEHICLE_WHEELBASE    = 1u;

  //Step 3) Call FUT
  DblCrvCalc_Get_CurvatureCodingParameters();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Coding_Dummy.Dbl.DblCurvatureCalculation.unCRC_STEERING_RATIO   , 1u, == );
  AL_UNITTEST_CHECK(Coding_Dummy.Dbl.DblCurvatureCalculation.unCRC_VEHICLE_WHEELBASE, 1u, == );

}



//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_Get_WfCodingParameters
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if funtion gets correct parameters for weighting factor algorithm
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                              = &Coding_Dummy
/// \input Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_1       = 1u
/// \input Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_2       = 1u
/// \input Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_3       = 1u
/// \input Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_1                     = 1u
/// \input Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_2                     = 1u
/// \input Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_3                     = 1u
///
/// - Expectations:
///
/// \output Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_1       = 1u
/// \output Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_2       = 1u
/// \output Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_3       = 1u
/// \output Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_1                     = 1u
/// \output Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_2                     = 1u
/// \output Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_3                     = 1u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_Get_WfCodingParameters(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_sCodingParam.psCodingParameters_Blocks                              = &Coding_Dummy;
  Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_1       = 1u;
  Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_2       = 1u;
  Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_3       = 1u;
  Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_1                     = 1u;
  Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_2                     = 1u;
  Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_3                     = 1u;

  //Step 3) Call FUT
  DblCrvCalc_Get_WfCodingParameters();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_1, 1u, == );
  AL_UNITTEST_CHECK(Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_2, 1u, == );
  AL_UNITTEST_CHECK(Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_3, 1u, == );
  AL_UNITTEST_CHECK(Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_1              , 1u, == );
  AL_UNITTEST_CHECK(Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_2              , 1u, == );
  AL_UNITTEST_CHECK(Coding_Dummy.Dbl.DblCurvatureCalculation.ucCRC_WF_3              , 1u, == );
}



//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_ProcessAngle_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if angle is positive
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_ProcessAngle_Param1 = 0
///
/// - Expectations:
///
/// \output DblCrvCalc_ProcessAngle_RetVal.snAngleValue = 0
/// \output DblCrvCalc_ProcessAngle_RetVal.scSgn        = 1
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_ProcessAngle_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrvCalc_ProcessAngle_Param1 = 0;

  //Step 3) Call FUT
  DblCrvCalc_ProcessAngle_RetVal = DblCrvCalc_ProcessAngle(DblCrvCalc_ProcessAngle_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.snAngleValue, 0, == );
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.scSgn,  1, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_ProcessAngle_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if angle is negative
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_ProcessAngle_Param1 = -1
///
/// - Expectations:
///
/// \output DblCrvCalc_ProcessAngle_RetVal.snAngleValue = 1
/// \output DblCrvCalc_ProcessAngle_RetVal.scSgn        = -1
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_ProcessAngle_TestCase_2(void)
{
  //Step 1) Set pre - conditions
   //Step 2) Assign Input values
  DblCrvCalc_ProcessAngle_Param1 = -1;

  //Step 3) Call FUT
  DblCrvCalc_ProcessAngle_RetVal = DblCrvCalc_ProcessAngle(DblCrvCalc_ProcessAngle_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.snAngleValue,  1, == );
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.scSgn,        -1, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_ProcessAngle_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if angle is positive and out of [0, 720] range
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_ProcessAngle_Param1 = 7800
///
/// - Expectations:
///
/// \output DblCrvCalc_ProcessAngle_RetVal.snAngleValue = 600
/// \output DblCrvCalc_ProcessAngle_RetVal.scSgn        = 1
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_ProcessAngle_TestCase_3(void)
{
  //Step 1) Set pre - conditions
   //Step 2) Assign Input values
  DblCrvCalc_ProcessAngle_Param1 = 7800;

  //Step 3) Call FUT
  DblCrvCalc_ProcessAngle_RetVal = DblCrvCalc_ProcessAngle(DblCrvCalc_ProcessAngle_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.snAngleValue,  600, == );
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.scSgn,         1, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_ProcessAngle_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if angle is positive and out of [0, 360] range
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_ProcessAngle_Param1 = 3700
///
/// - Expectations:
///
/// \output DblCrvCalc_ProcessAngle_RetVal.snAngleValue = 100
/// \output DblCrvCalc_ProcessAngle_RetVal.scSgn        = 1
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_ProcessAngle_TestCase_4(void)
{
  //Step 1) Set pre - conditions
   //Step 2) Assign Input values
  DblCrvCalc_ProcessAngle_Param1 = 3700;

  //Step 3) Call FUT
  DblCrvCalc_ProcessAngle_RetVal = DblCrvCalc_ProcessAngle(DblCrvCalc_ProcessAngle_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.snAngleValue,  100, == );
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.scSgn,         1, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_ProcessAngle_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if angle is in quadrant 2
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_ProcessAngle_Param1 = 1500
///
/// - Expectations:
///
/// \output DblCrvCalc_ProcessAngle_RetVal.snAngleValue = 300
/// \output DblCrvCalc_ProcessAngle_RetVal.scSgn        = 1
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_ProcessAngle_TestCase_5(void)
{
  //Step 1) Set pre - conditions
   //Step 2) Assign Input values
  DblCrvCalc_ProcessAngle_Param1 = 1500;

  //Step 3) Call FUT
  DblCrvCalc_ProcessAngle_RetVal = DblCrvCalc_ProcessAngle(DblCrvCalc_ProcessAngle_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.snAngleValue,  300, == );
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.scSgn,         1, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_ProcessAngle_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if angle is in quadrant 3
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_ProcessAngle_Param1 = 1900
///
/// - Expectations:
///
/// \output DblCrvCalc_ProcessAngle_RetVal.snAngleValue = 100
/// \output DblCrvCalc_ProcessAngle_RetVal.scSgn        = -1
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_ProcessAngle_TestCase_6(void)
{
  //Step 1) Set pre - conditions
   //Step 2) Assign Input values
  DblCrvCalc_ProcessAngle_Param1 = 1900;

  //Step 3) Call FUT
  DblCrvCalc_ProcessAngle_RetVal = DblCrvCalc_ProcessAngle(DblCrvCalc_ProcessAngle_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.snAngleValue,  100, == );
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.scSgn,         -1, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_ProcessAngle_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if angle is in quadrant 4
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_ProcessAngle_Param1 = 1900
///
/// - Expectations:
///
/// \output DblCrvCalc_ProcessAngle_RetVal.snAngleValue = 800
/// \output DblCrvCalc_ProcessAngle_RetVal.scSgn        = -1
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_ProcessAngle_TestCase_7(void)
{
  //Step 1) Set pre - conditions
   //Step 2) Assign Input values
  DblCrvCalc_ProcessAngle_Param1 = 2800;

  //Step 3) Call FUT
  DblCrvCalc_ProcessAngle_RetVal = DblCrvCalc_ProcessAngle(DblCrvCalc_ProcessAngle_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.snAngleValue,  800, == );
  AL_UNITTEST_CHECK(DblCrvCalc_ProcessAngle_RetVal.scSgn,         -1, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_ProcessAngle    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrvCalc_ProcessAngle(void)
{
  Mt_DblCrvCalc_ProcessAngle_TestCase_1();
  Mt_DblCrvCalc_ProcessAngle_TestCase_2();
  Mt_DblCrvCalc_ProcessAngle_TestCase_3();
  Mt_DblCrvCalc_ProcessAngle_TestCase_4();
  Mt_DblCrvCalc_ProcessAngle_TestCase_5();
  Mt_DblCrvCalc_ProcessAngle_TestCase_6();
  Mt_DblCrvCalc_ProcessAngle_TestCase_7();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_getLinearInterpolatedValue
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_getLinearInterpolatedValue_Param1 = 1u
/// \input DblCrvCalc_getLinearInterpolatedValue_Param2 = 5u
/// \input DblCrvCalc_getLinearInterpolatedValue_Param3 = 6u
/// \input DblCrvCalc_getLinearInterpolatedValue_Param4 = 7u
/// \input DblCrvCalc_getLinearInterpolatedValue_Param5 = 8u
///
/// - Expectations:
///
/// \output DblCrvCalc_getLinearInterpolatedValue_RetVal =3u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_getLinearInterpolatedValue(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrvCalc_getLinearInterpolatedValue_Param1 = 1u;
  DblCrvCalc_getLinearInterpolatedValue_Param2 = 5u;
  DblCrvCalc_getLinearInterpolatedValue_Param3 = 6u;
  DblCrvCalc_getLinearInterpolatedValue_Param4 = 7u;
  DblCrvCalc_getLinearInterpolatedValue_Param5 = 8u;
  //Step 3) Call FUT

  DblCrvCalc_getLinearInterpolatedValue_RetVal = DblCrvCalc_getLinearInterpolatedValue(DblCrvCalc_getLinearInterpolatedValue_Param1, DblCrvCalc_getLinearInterpolatedValue_Param2, DblCrvCalc_getLinearInterpolatedValue_Param3, DblCrvCalc_getLinearInterpolatedValue_Param4, DblCrvCalc_getLinearInterpolatedValue_Param5);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_getLinearInterpolatedValue_RetVal, 3u, == );
}



//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_WeightingFactorCalculation_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    DblCrvCalc_WeightingFactorCalculation_Param1  = 36u;
/// \input  DblCrCalc_asCrv_WfTable[0u].ulV_Min = 11u;
/// \input  DblCrCalc_asCrv_WfTable[0u].ulV_Max = 13u;
/// \input  DblCrCalc_asCrv_WfTable[1u].ulV_Min = 11u;
/// \input  DblCrCalc_asCrv_WfTable[1u].ulV_Max = 13u;
/// \input  DblCrCalc_asCrv_WfTable[0u].ucWf_Max = 11u;
/// \input  DblCrCalc_asCrv_WfTable[0u].ucWf_Min = 13u;
/// \input  DblCrCalc_asCrv_WfTable[1u].ucWf_Max = 11u;
/// \input  DblCrCalc_asCrv_WfTable[1u].ucWf_Min = 13u;
///
/// - Expectations:
///
/// \output DblCrvCalc_WeightingFactorCalculation_RetVal = 11u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_WeightingFactorCalculation_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrvCalc_WeightingFactorCalculation_Param1  = 36u;
  DblCrCalc_asCrv_WfTable[0u].ulV_Min           = 11u;
  DblCrCalc_asCrv_WfTable[0u].ulV_Max           = 13u;
  DblCrCalc_asCrv_WfTable[1u].ulV_Min           = 11u;
  DblCrCalc_asCrv_WfTable[1u].ulV_Max           = 13u;
  DblCrCalc_asCrv_WfTable[0u].ucWf_Max          = 11u;
  DblCrCalc_asCrv_WfTable[0u].ucWf_Min          = 13u;
  DblCrCalc_asCrv_WfTable[1u].ucWf_Max          = 11u;
  DblCrCalc_asCrv_WfTable[1u].ucWf_Min          = 13u;

  //Step 3) Call FUT
  DblCrvCalc_WeightingFactorCalculation_RetVal = DblCrvCalc_WeightingFactorCalculation(DblCrvCalc_WeightingFactorCalculation_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_WeightingFactorCalculation_RetVal, 11u, == );

}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_WeightingFactorCalculation_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_WeightingFactorCalculation_Param1 = 36u;
/// \input DblCrCalc_asCrv_WfTable[0u].ulV_Min = 0u;
/// \input DblCrCalc_asCrv_WfTable[1u].ulV_Max = 0u;
/// \input DblCrCalc_asCrv_WfTable[1u].ucWf_Max = 23u;
///
/// - Expectations:
///
/// \output DblCrvCalc_WeightingFactorCalculation_RetVal = 23u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_WeightingFactorCalculation_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrvCalc_WeightingFactorCalculation_Param1 = 36u;
  DblCrCalc_asCrv_WfTable[0u].ulV_Min           = 0u;
  DblCrCalc_asCrv_WfTable[1u].ulV_Max           = 0u;
  DblCrCalc_asCrv_WfTable[1u].ucWf_Max          = 23u;

  //Step 3) Call FUT
  DblCrvCalc_WeightingFactorCalculation_RetVal = DblCrvCalc_WeightingFactorCalculation(DblCrvCalc_WeightingFactorCalculation_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_WeightingFactorCalculation_RetVal, 23u, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_WeightingFactorCalculation_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_WeightingFactorCalculation_Param1 = 36u;
/// \input DblCrCalc_asCrv_WfTable[0u].ulV_Min = 0u;
/// \input DblCrCalc_asCrv_WfTable[1u].ulV_Max = 65535u;
///
/// - Expectations:
///
/// \output DblCrvCalc_WeightingFactorCalculation_RetVal = 13
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_WeightingFactorCalculation_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrvCalc_WeightingFactorCalculation_Param1 = 36u;
  DblCrCalc_asCrv_WfTable[0u].ulV_Min           = 0u;
  DblCrCalc_asCrv_WfTable[1u].ulV_Max           = 65535u;

  //Step 3) Call FUT
  DblCrvCalc_WeightingFactorCalculation_RetVal = DblCrvCalc_WeightingFactorCalculation(DblCrvCalc_WeightingFactorCalculation_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_WeightingFactorCalculation_RetVal, 13u, == );
}
//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_WeightingFactorCalculation    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrvCalc_WeightingFactorCalculation(void)
{
  Mt_DblCrvCalc_WeightingFactorCalculation_TestCase_1();
  Mt_DblCrvCalc_WeightingFactorCalculation_TestCase_2();
  Mt_DblCrvCalc_WeightingFactorCalculation_TestCase_3();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_FindWfZone_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if zone 2 is finded
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_FindWfZone_Param1       = 1u
/// \input DblCrCalc_asCrv_WfTable[0].ulV_Min = 2u
/// \input DblCrCalc_asCrv_WfTable[0].ulV_Max = 0u
/// \input DblCrvCalc_FindWfZone_RetVal       = 0u
///
/// - Expectations:
///
/// \output DblCrvCalc_FindWfZone_RetVal       = 2u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_FindWfZone_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrvCalc_FindWfZone_Param1       = 1u;
  DblCrCalc_asCrv_WfTable[0].ulV_Min = 2u;
  DblCrCalc_asCrv_WfTable[0].ulV_Max = 0u;
  DblCrvCalc_FindWfZone_RetVal       = 0u;

  //Step 3) Call FUT
  DblCrvCalc_FindWfZone_RetVal = DblCrvCalc_FindWfZone(DblCrvCalc_FindWfZone_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_FindWfZone_RetVal, 2u, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_FindWfZone_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if zone 1 is finded
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  DblCrvCalc_FindWfZone_Param1       = 1u
/// \input  DblCrCalc_asCrv_WfTable[0].ulV_Min = 2u
/// \input  DblCrCalc_asCrv_WfTable[0].ulV_Max = 0u
/// \input  DblCrCalc_asCrv_WfTable[1].ulV_Min = 1u
/// \input  DblCrCalc_asCrv_WfTable[2].ulV_Max = 1u
/// \input  DblCrvCalc_FindWfZone_RetVal       = 0u
///
/// - Expectations:
/// 
/// \output DblCrvCalc_FindWfZone_RetVal       = 1u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_FindWfZone_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrvCalc_FindWfZone_Param1       = 1u;
  DblCrCalc_asCrv_WfTable[0].ulV_Min = 2u;
  DblCrCalc_asCrv_WfTable[0].ulV_Max = 0u;
  DblCrCalc_asCrv_WfTable[1].ulV_Min = 1u;
  DblCrCalc_asCrv_WfTable[2].ulV_Max = 1u;
  DblCrvCalc_FindWfZone_RetVal       = 0u;

  //Step 3) Call FUT
  DblCrvCalc_FindWfZone_RetVal = DblCrvCalc_FindWfZone(DblCrvCalc_FindWfZone_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_FindWfZone_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_FindWfZone    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrvCalc_FindWfZone(void)
{
  Mt_DblCrvCalc_FindWfZone_TestCase_1();
  Mt_DblCrvCalc_FindWfZone_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_GetSin_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets correct sinus for a fixed angle-last digit is 0
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_GetSin_Param1 = 60u
///
/// - Expectations:
///
/// \output DblCrvCalc_GetSin_RetVal = 100000u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_GetSin_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrvCalc_GetSin_Param1 = 900u;

  //Step 3) Call FUT
  DblCrvCalc_GetSin_RetVal = DblCrvCalc_GetSin(DblCrvCalc_GetSin_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_GetSin_RetVal, 100000u, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_GetSin_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets correct sinus for an angle which needs to be interpolated
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrvCalc_GetSin_Param1 = 363
///
/// - Expectations:
///
/// \output DblCrvCalc_GetSin_RetVal = 59200
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_GetSin_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrvCalc_GetSin_Param1 = 363;

  //Step 3) Call FUT
  DblCrvCalc_GetSin_RetVal = DblCrvCalc_GetSin(DblCrvCalc_GetSin_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrvCalc_GetSin_RetVal, 59200, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_GetSin    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrvCalc_GetSin(void)
{
  Mt_DblCrvCalc_GetSin_TestCase_1();
  Mt_DblCrvCalc_GetSin_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_getCurvatureValue_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test radius steering in case of wrong input
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                = Dbl_SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = Dbl_SIG_VALID;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                          = Dbl_SIG_VALID;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle    = 0;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 12u;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed              = 10;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                      = 0u;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
/// \input Rte_Read_SigPrep_YawSpeed_HitCount                                = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount        = 1u
/// \output Rte_Read_SigPrep_YawSpeed_HitCount           = 1u
/// \output DblCrvCalc_getCurvatureValue_RetVal          = 10000
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_getCurvatureValue_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                = Dbl_SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                       = Dbl_SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                          = Dbl_SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle    = 1;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 12u;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed              = 0;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                      = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SigPrep_YawSpeed_HitCount                                = 0u;

  //Step 3) Call FUT
  DblCrvCalc_getCurvatureValue_RetVal = DblCrvCalc_getCurvatureValue();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount       , 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_YawSpeed_HitCount          , 1u, == );
  AL_UNITTEST_CHECK(DblCrvCalc_getCurvatureValue_RetVal         , 10000, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_getCurvatureValue_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test radius steering value with valid inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                = Dbl_SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                    = SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                          = Dbl_SIG_VALID;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle    = 0;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 12u;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed              = 10;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                      = 0u;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
/// \input Rte_Read_SigPrep_YawSpeed_HitCount                                = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount        = 1u
/// \output Rte_Read_SigPrep_YawSpeed_HitCount           = 1u
/// \output DblCrvCalc_getCurvatureValue_RetVal          = 10000
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_getCurvatureValue_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                = Dbl_SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                    = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                          = Dbl_SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle    = 3000;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 100u;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed              = 10;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                      = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SigPrep_YawSpeed_HitCount                                = 0u;

  //Step 3) Call FUT
  DblCrvCalc_getCurvatureValue_RetVal = DblCrvCalc_getCurvatureValue();
  
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount       , 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_YawSpeed_HitCount          , 1u, == );
  AL_UNITTEST_CHECK(DblCrvCalc_getCurvatureValue_RetVal         , 10000, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_getCurvatureValue_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test curvature max limitation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                = Dbl_SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                    = Dbl_SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = Dbl_SIG_VALID;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                          = Dbl_SIG_VALID;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle    = 0;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 12u;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed              = 0;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                      = 0u;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
/// \input Rte_Read_SigPrep_YawSpeed_HitCount                                = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount        = 1u
/// \output Rte_Read_SigPrep_YawSpeed_HitCount           = 1u
/// \output DblCrvCalc_getCurvatureValue_RetVal          = -10000
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_getCurvatureValue_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                = Dbl_SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                    = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo            = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                          = Dbl_SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle    = -7800;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 100u;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed              = -1;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                      = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SigPrep_YawSpeed_HitCount                                = 0u;

  //Step 3) Call FUT
  DblCrvCalc_getCurvatureValue_RetVal = DblCrvCalc_getCurvatureValue();
  
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount       , 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_YawSpeed_HitCount          , 1u, == );
  AL_UNITTEST_CHECK(DblCrvCalc_getCurvatureValue_RetVal         , -10000, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_getCurvatureValue_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test curvature max limitation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                = Dbl_SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                    = Dbl_SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = Dbl_SIG_VALID;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                          = Dbl_SIG_VALID;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle    = 0;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 12u;
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed              = 0;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                      = 0u;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
/// \input Rte_Read_SigPrep_YawSpeed_HitCount                                = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount        = 1u
/// \output Rte_Read_SigPrep_YawSpeed_HitCount           = 1u
/// \output DblCrvCalc_getCurvatureValue_RetVal          = 0
///
//----------------------------------------------------------------------------- 
void Mt_DblCrvCalc_getCurvatureValue_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                = Dbl_SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                    = Dbl_SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                          = Dbl_SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle    = 0;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 0;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed              = 0;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                      = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SigPrep_YawSpeed_HitCount                                = 0u;

  //Step 3) Call FUT
  DblCrvCalc_getCurvatureValue_RetVal = DblCrvCalc_getCurvatureValue();
  
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount       , 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_YawSpeed_HitCount          , 1u, == );
  AL_UNITTEST_CHECK(DblCrvCalc_getCurvatureValue_RetVal         , 0, == );
}
//-----------------------------------------------------------------------------
/// Mt_DblCrvCalc_getCurvatureValue    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrvCalc_getCurvatureValue(void)
{
  Mt_DblCrvCalc_getCurvatureValue_TestCase_1();
  Mt_DblCrvCalc_getCurvatureValue_TestCase_2();
  Mt_DblCrvCalc_getCurvatureValue_TestCase_3();
  Mt_DblCrvCalc_getCurvatureValue_TestCase_4();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if state machine is initialized correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                            = &Coding_Dummy
/// \input Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME  = 5u
/// \input Dbl_sCurvatureData.sCurvatureState.eCalculationMode                  = Available
/// \input Dbl_sCurvatureData.sCurvatureState.eCalculationPhase                 = Invalid
///
/// - Expectations:
///
/// \output    Dbl_sCurvatureData.sCurvatureState.eCalculationMode             = eDbl_Unavailable
/// \output    Dbl_sCurvatureData.sCurvatureState.eCalculationPhase            = eDbl_Nominal
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Init(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_sCodingParam.psCodingParameters_Blocks                            = &Coding_Dummy;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME  = 0u;
  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Available;
  Dbl_sCurvatureData.sCurvatureState.eCalculationPhase                  = eDbl_Invalid;

  //Step 3) Call FUT
  DblCrState_Init();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.sCurvatureState.eCalculationMode,  eDbl_Unavailable, == );
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.sCurvatureState.eCalculationPhase, eDbl_Nominal    , == );
}



//-----------------------------------------------------------------------------
/// Mt_DblCrState_State_Machine_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transition unavailable to available works-goes to available
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
/// \input  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
/// \input  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
/// \input  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
/// \input  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Unavailable;
///
/// - Expectations:
///
/// \output Dbl_sCurvatureData.sCurvatureState.eCalculationMode = Available
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_State_Machine_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE + 1;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Unavailable;

  //Step 3) Call FUT
  DblCrState_State_Machine();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.sCurvatureState.eCalculationMode, eDbl_Available, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_State_Machine_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transition unavailable to available works-stays in unavailable
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
/// \input  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
/// \input  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
/// \input  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
/// \input  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Available;
///
/// - Expectations:
///
/// \output Dbl_sCurvatureData.sCurvatureState.eCalculationMode = eDbl_Unavailable
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_State_Machine_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTI_NOMINAL;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Available;

  //Step 3) Call FUT
  DblCrState_State_Machine();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.sCurvatureState.eCalculationMode, eDbl_Unavailable, == );

}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_State_Machine_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transition unavailable to available works-goes to available and calculation phase goes to invalid
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
/// \input  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
/// \input  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_INVALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
/// \input  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
/// \input  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Unavailable;
/// \input   Dbl_sCurvatureData.sCurvatureState.eCalculationPhase                 = eDbl_Nominal;
///
/// - Expectations:
///
/// \output Dbl_sCurvatureData.sCurvatureState.eCalculationMode    = eDbl_Available
/// \output  Dbl_sCurvatureData.sCurvatureState.eCalculationPhase  = eDbl_Invalid
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_State_Machine_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE + 1;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Unavailable;
  Dbl_sCurvatureData.sCurvatureState.eCalculationPhase = eDbl_Nominal;

  //Step 3) Call FUT
  DblCrState_State_Machine();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.sCurvatureState.eCalculationMode ,   eDbl_Available, == );
  AL_UNITTEST_CHECK( Dbl_sCurvatureData.sCurvatureState.eCalculationPhase , eDbl_Invalid  , == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrState_State_Machine_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transition unavailable to available works-goes to available and calculation phase stays in nominal
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
/// \input  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
/// \input  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_INVALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
/// \input  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
/// \input  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Unavailable;
/// \input   Dbl_sCurvatureData.sCurvatureState.eCalculationPhase                 = eDbl_Invalid;
///
/// - Expectations:
///
/// \output Dbl_sCurvatureData.sCurvatureState.eCalculationMode    = eDbl_Available
/// \output  Dbl_sCurvatureData.sCurvatureState.eCalculationPhase  = eDbl_Nominal
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_State_Machine_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE + 1;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Unavailable;
   Dbl_sCurvatureData.sCurvatureState.eCalculationPhase                 = eDbl_Invalid;
  DblCrState_boSigQty_TimeoutFlag = FALSE;

  //Step 3) Call FUT
  DblCrState_State_Machine();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.sCurvatureState.eCalculationMode ,   eDbl_Available, == );
  AL_UNITTEST_CHECK( Dbl_sCurvatureData.sCurvatureState.eCalculationPhase , eDbl_Nominal  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_State_Machine_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transition invalid to nominal works-stays in nominal
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE + 1
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = Dbl_SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount                                  = 0u
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_VALID
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 10
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5
/// \input Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Unavailable
///
/// - Expectations:
///
/// \output Dbl_sCurvatureData.sCurvatureState.eCalculationMode = eDbl_Available
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_State_Machine_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE ;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTI_NOMINAL;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Available;

  //Step 3) Call FUT
  DblCrState_State_Machine();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.sCurvatureState.eCalculationMode, eDbl_Unavailable, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrState_State_Machine_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transition unavailable to available works
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE + 1
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = Dbl_SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount                                  = 0u
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_VALID
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 10
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5
/// \input Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Unavailable
///
/// - Expectations:
///
/// \output Dbl_sCurvatureData.sCurvatureState.eCalculationMode = eDbl_Available
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_State_Machine_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                    = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                              = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                           = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTI_NOMINAL;
  Rte_Read_SigPrep_YawSpeed_Param1.eYawSpeed.nYawSpeed                  = 10;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed      = 5;
  Dbl_sCurvatureData.sCurvatureState.eCalculationMode                   = eDbl_Available;

  //Step 3) Call FUT
  DblCrState_State_Machine();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_sCurvatureData.sCurvatureState.eCalculationMode, eDbl_Unavailable, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrState_State_Machine    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrState_State_Machine(void)
{
  Mt_DblCrState_State_Machine_TestCase_1();
  Mt_DblCrState_State_Machine_TestCase_2();
  Mt_DblCrState_State_Machine_TestCase_3();
  Mt_DblCrState_State_Machine_TestCase_4();
  Mt_DblCrState_State_Machine_TestCase_5();
  Mt_DblCrState_State_Machine_TestCase_6();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transitions codintions work
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                             = SIG_INVALID;
/// \input DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal     = FALSE;
/// \input Rte_Read_SigPrep_YawSpeed_HitCount                                   = 0u;
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                         = 0u;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                                = 0u;
/// \input Rte_Read_SysMon_VehNetState_HitCount                                 = 0u;
/// \input DblCrState_boSigQty_TimeoutFlag                                      = FALSE;
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                           = &Coding_Dummy;
/// \input Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 0u;
///
/// - Expectations:
///
/// \output DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal = TRUE
/// \output Rte_Read_SigPrep_YawSpeed_HitCount                               = 1u
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount                     = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                            = 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount                             = 1u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                             = SIG_INVALID;
  DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal     = FALSE;
  Rte_Read_SigPrep_YawSpeed_HitCount                                   = 0u;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                         = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                                 = 0u;
  DblCrState_boSigQty_TimeoutFlag                                      = FALSE;
  Dbl_sCodingParam.psCodingParameters_Blocks                           = &Coding_Dummy;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME = 0u;

  //Step 3) Call FUT
  DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal = DblCrState_Transition_CalculationPhase_Nominal_to_Invalid();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_YawSpeed_HitCount                              , 1u  , == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount                    , 1u  , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount                           , 1u  , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                            , 1u  , == );

}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transitions codintions work
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                         = Dbl_SIG_VALID
/// \input DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal = FALSE
/// \input Rte_Read_SigPrep_YawSpeed_HitCount                               = 0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount                             = 0u
///
/// - Expectations:
///
/// \output DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal = TRUE
/// \output Rte_Read_SigPrep_YawSpeed_HitCount                               = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                            = 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount                             = 1u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                         = SIG_VALID;
  DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal = TRUE;
  Rte_Read_SigPrep_YawSpeed_HitCount                               = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                             = 0u;
  DblCrState_boSigQty_TimeoutFlag = FALSE;

  //Step 3) Call FUT
  DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal = DblCrState_Transition_CalculationPhase_Nominal_to_Invalid();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_YawSpeed_HitCount                              , 1u  , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                            , 1u  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid(void)
{
  Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_TestCase_1();
  Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transition works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                         = eTI_NOMINAL
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty               = SIG_VALID
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID
/// \input Rte_Read_SigPrep_YawSpeed_HitCount                               = 0u
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                     = 0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount                             = 0u
/// \input DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_YawSpeed_HitCount                               = 1u   
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount                     = 1u   
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                            = 1u   
/// \output Rte_Read_SysMon_VehNetState_HitCount                             = 1u   
/// \output DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal = TRUE 
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                         = eTI_NOMINAL;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty               = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_HitCount                               = 0u;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                     = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                             = 0u;
  DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal = FALSE;
  
  //Step 3) Call FUT
  DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal = DblCrState_Transition_CalculationPhase_Invalid_to_Nominal();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_YawSpeed_HitCount                              , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount                    , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount                           , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                            , 1u    , == );
  AL_UNITTEST_CHECK(DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal, TRUE  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transition works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                         = eInvalid
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty               = SIG_INVALID
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_INVALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_INVALID
/// \input Rte_Read_SigPrep_YawSpeed_HitCount                               = 0u
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                     = 0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount                             = 0u
/// \input DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal = TRUE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_YawSpeed_HitCount                               = 1u   
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount                     = 1u   
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                            = 1u   
/// \output Rte_Read_SysMon_VehNetState_HitCount                             = 1u   
/// \output DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal = FALSE 
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                         = eInvalid;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty               = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                      = SIG_INVALID;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                       = SIG_INVALID;
  Rte_Read_SigPrep_YawSpeed_HitCount                               = 0u;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                     = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                             = 0u;
  DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal = TRUE;
  
  //Step 3) Call FUT
  DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal = DblCrState_Transition_CalculationPhase_Invalid_to_Nominal();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_YawSpeed_HitCount                              , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount                    , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount                           , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                            , 1u    , == );
  AL_UNITTEST_CHECK(DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal, FALSE  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal(void)
{
  Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_TestCase_1();
  Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if transition works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_STEERING_WHEEL_INIT_IN_PROGRESS_VALUE + 1
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = Dbl_SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTI_NOMINAL
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount                                  = 0u
/// \input DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal = TRUE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 1u    
/// \output Rte_Read_SysMon_VehNetState_HitCount                                  = 1u    
/// \output DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal = FALSE 
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_STEERING_WHEEL_INIT_IN_PROGRESS_VALUE + 1;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = Dbl_SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTI_NOMINAL;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                                  = 0u;
  DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal = FALSE;

  //Step 3) Call FUT
  DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal = DblCrState_Transition_CalculationMode_Available_to_Unavailable();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount                         , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                                 , 1u    , == );
  AL_UNITTEST_CHECK(DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal, TRUE  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_STEERING_WHEEL_INIT_IN_PROGRESS_VALUE + 1
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount                                  = 0u
/// \input DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 1u    
/// \output Rte_Read_SysMon_VehNetState_HitCount                                  = 1u    
/// \output DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal = TRUE 
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_STEERING_WHEEL_INIT_IN_PROGRESS_VALUE + 1;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                                  = 0u;
  DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal = TRUE;


  //Step 3) Call FUT
  DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal = DblCrState_Transition_CalculationMode_Available_to_Unavailable();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount                         , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                                 , 1u    , == );
  AL_UNITTEST_CHECK(DblCrState_Transition_CalculationMode_Available_to_Unavailable_RetVal, FALSE  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable(void)
{
  Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable_TestCase_1();
  Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE + 1
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = Dbl_SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u
/// \input DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal = FALSE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          == 1u   
/// \output Rte_Read_SysMon_VehNetState_HitCount                                  == 1u   
/// \output DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal == TRUE 
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE + 1;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = Dbl_SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTA_NOMINAL;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                                  = 0u;
  DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal = FALSE;

  //Step 3) Call FUT
  DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal = DblCrState_Transition_CalculationMode_Unavailable_to_Available();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount                         , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                                 , 1u    , == );
  AL_UNITTEST_CHECK(DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal, TRUE  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTI_NOMINAL
/// \input Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount                                  = 0u
/// \input DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal = TRUE
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          == 1u   
/// \output Rte_Read_SysMon_VehNetState_HitCount                                  == 1u   
/// \output DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal == FALSE 
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle        = DBL_CURVATURE_INVALID_VALUE;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                            = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState              = eTI_NOMINAL;
  Rte_Read_SigPrep_SteeringWheelAngle_HitCount                          = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                                  = 0u;
  DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal = TRUE;

  //Step 3) Call FUT
  DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal = DblCrState_Transition_CalculationMode_Unavailable_to_Available();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SteeringWheelAngle_HitCount                         , 1u    , == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                                 , 1u    , == );
  AL_UNITTEST_CHECK(DblCrState_Transition_CalculationMode_Unavailable_to_Available_RetVal, FALSE  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available(void)
{
  Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available_TestCase_1();
  Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL
/// \input DblCrState_PowerTrain_State_RetVal = FALSE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = TRUE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
  DblCrState_PowerTrain_State_RetVal                       = FALSE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, TRUE  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL
/// \input DblCrState_PowerTrain_State_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTI_NOMINAL;
  DblCrState_PowerTrain_State_RetVal                       = TRUE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, FALSE  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL
/// \input DblCrState_PowerTrain_State_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eInvalid;
  DblCrState_PowerTrain_State_RetVal                       = TRUE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, FALSE  , == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain-default case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL
/// \input DblCrState_PowerTrain_State_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = 10;
  DblCrState_PowerTrain_State_RetVal = TRUE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, FALSE, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain-based on eElectricNetworkState
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblTA_DEGRADE
/// \input DblCrState_PowerTrain_State_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblTA_DEGRADE;
  DblCrState_PowerTrain_State_RetVal = FALSE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain-based on eElectricNetworkState
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblTA_SECU
/// \input DblCrState_PowerTrain_State_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblTA_SECU;
  DblCrState_PowerTrain_State_RetVal = FALSE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain-based on eElectricNetworkState
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblREDEMARRAGE
/// \input DblCrState_PowerTrain_State_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblREDEMARRAGE;
  DblCrState_PowerTrain_State_RetVal = FALSE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, TRUE, == );
}



//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain-based on eElectricNetworkState
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblTI_DEGRADE
/// \input DblCrState_PowerTrain_State_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblTI_DEGRADE;
  DblCrState_PowerTrain_State_RetVal = TRUE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, FALSE, == );
}



//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain-based on eElectricNetworkState
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblTI_DISPO_DEM
/// \input DblCrState_PowerTrain_State_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblTI_DISPO_DEM;
  DblCrState_PowerTrain_State_RetVal = TRUE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, FALSE, == );
}



//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State_TestCase_10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets the correct powertrain-based on eElectricNetworkState
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblDEMARRAGE
/// \input DblCrState_PowerTrain_State_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_PowerTrain_State_RetVal = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_PowerTrain_State_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDblDEMARRAGE;
  DblCrState_PowerTrain_State_RetVal = TRUE;

  //Step 3) Call FUT
  DblCrState_PowerTrain_State_RetVal = DblCrState_PowerTrain_State();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_PowerTrain_State_RetVal, FALSE, == );
}
//-----------------------------------------------------------------------------
/// Mt_DblCrState_PowerTrain_State    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrState_PowerTrain_State(void)
{
  Mt_DblCrState_PowerTrain_State_TestCase_1();
  Mt_DblCrState_PowerTrain_State_TestCase_2();
  Mt_DblCrState_PowerTrain_State_TestCase_3();
  Mt_DblCrState_PowerTrain_State_TestCase_4();
  Mt_DblCrState_PowerTrain_State_TestCase_5();
  Mt_DblCrState_PowerTrain_State_TestCase_6();
  Mt_DblCrState_PowerTrain_State_TestCase_7();
  Mt_DblCrState_PowerTrain_State_TestCase_8();
  Mt_DblCrState_PowerTrain_State_TestCase_9();
  Mt_DblCrState_PowerTrain_State_TestCase_10();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_HandleDelayStatus_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test timer input in start case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrState_HandleDelayStatus_Param2                                                       = 0u;
/// \input DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boReq_Input      = TRUE;
/// \input DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = FALSE;
///
/// - Expectations:
///
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].ulCommandStart == UTILTIME_TIMER_START(UTILTIME_MSEC(DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].ulTimeMs_Input))
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer == TRUE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_HandleDelayStatus_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrState_HandleDelayStatus_Param2                                                       = 0u;
  DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boReq_Input      = TRUE;
  DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = FALSE;

  //Step 3) Call FUT
  DblCrState_HandleDelayStatus_RetVal = DblCrState_HandleDelayStatus(DblCrState_HandleDelayStatus_Param1, DblCrState_HandleDelayStatus_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].ulCommandStart  , UTILTIME_TIMER_START(UTILTIME_MSEC(DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].ulTimeMs_Input)), == );
  AL_UNITTEST_CHECK(DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer, TRUE, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_HandleDelayStatus_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test timer input in reset case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrState_HandleDelayStatus_Param2                                                       = 0u;
/// \input DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boReq_Input      = FALSE;
/// \input DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = FALSE;
///
/// - Expectations:
///
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boTimeOut        = FALSE
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = FALSE
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].ulCommandStart   = 0u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_HandleDelayStatus_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrState_HandleDelayStatus_Param2                                                       = 0u;
  DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boReq_Input      = FALSE;
  DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = FALSE;

  //Step 3) Call FUT
  DblCrState_HandleDelayStatus_RetVal = DblCrState_HandleDelayStatus(DblCrState_HandleDelayStatus_Param1, DblCrState_HandleDelayStatus_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boTimeOut       , FALSE,==);
  AL_UNITTEST_CHECK(DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer, FALSE,==);
  AL_UNITTEST_CHECK(DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].ulCommandStart  , 0u   ,==);
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_HandleDelayStatus_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if timer is still running
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrState_HandleDelayStatus_Param2                                                       = 0u
/// \input DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = FALSE
///
/// - Expectations:
///
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boTimeOut        = FALSE
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = FALSE
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].ulCommandStart   = 0u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_HandleDelayStatus_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrState_HandleDelayStatus_Param2                                                       = 0u;
  DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boReq_Input      = TRUE;
  DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = FALSE;

  LPTMR0_GetTimeElapsed_RetVal = 100000000;
  //Step 3) Call FUT
  DblCrState_HandleDelayStatus_RetVal = DblCrState_HandleDelayStatus(DblCrState_HandleDelayStatus_Param1, DblCrState_HandleDelayStatus_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boTimeOut, UTILTIME_TIMER_TIMEOUT(DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].ulCommandStart), == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_HandleDelayStatus_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if timer is not running

///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrState_HandleDelayStatus_Param2                                                       = 0u
/// \input DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = TRUE
/// \input DblCrState_HandleDelayStatus_RetVal = FALSE
///
/// - Expectations:
///
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boTimeOut        = FALSE
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = FALSE
/// \output DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].ulCommandStart   = 0u
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_HandleDelayStatus_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrState_HandleDelayStatus_Param2 = 0u;
  DblCrState_HandleDelayStatus_Param1[DblCrState_HandleDelayStatus_Param2].boStartStopTimer = TRUE;
  DblCrState_HandleDelayStatus_RetVal = FALSE;

  //Step 3) Call FUT
  DblCrState_HandleDelayStatus_RetVal = DblCrState_HandleDelayStatus(DblCrState_HandleDelayStatus_Param1, DblCrState_HandleDelayStatus_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_HandleDelayStatus_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_HandleDelayStatus    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrState_HandleDelayStatus(void)
{
  Mt_DblCrState_HandleDelayStatus_TestCase_1();
  Mt_DblCrState_HandleDelayStatus_TestCase_2();
  Mt_DblCrState_HandleDelayStatus_TestCase_3();
  Mt_DblCrState_HandleDelayStatus_TestCase_4();
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Timeout_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if number of selected timers protection works
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrState_Timeout_Param1 = 0u
/// \input DblCrState_Timeout_Param2 = 0u
/// \input DblCrState_Timeout_Param3 = DBLCRSTATE_NUMBER_OF_TIMERS - 1u
/// \input DblCrState_Timeout_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_sTimerCfg[DblCrState_Timeout_Param3].ulTimeMs_Input = DblCrState_Timeout_Param2
/// \output DblCrState_sTimerCfg[DblCrState_Timeout_Param3].boReq_Input    = DblCrState_Timeout_Param1
/// \output DblCrState_Timeout_RetVal                                      = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Timeout_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrState_Timeout_Param1 = 0u;
  DblCrState_Timeout_Param2 = 0u;
  DblCrState_Timeout_Param3 = DBLCRSTATE_NUMBER_OF_TIMERS - 1u;
  DblCrState_Timeout_RetVal = TRUE;

  //Step 3) Call FUT
  DblCrState_Timeout_RetVal = DblCrState_Timeout(DblCrState_Timeout_Param1, DblCrState_Timeout_Param2, DblCrState_Timeout_Param3);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_sTimerCfg[DblCrState_Timeout_Param3].ulTimeMs_Input, DblCrState_Timeout_Param2, == );
  AL_UNITTEST_CHECK(DblCrState_sTimerCfg[DblCrState_Timeout_Param3].boReq_Input   , DblCrState_Timeout_Param1, == );
  AL_UNITTEST_CHECK(DblCrState_Timeout_RetVal                                     , FALSE, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Timeout_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if number of selected timers protection works
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DblCrState_Timeout_Param1 = 0u
/// \input DblCrState_Timeout_Param2 = 0u
/// \input DblCrState_Timeout_Param3 = DBLCRSTATE_NUMBER_OF_TIMERS - 1u
/// \input DblCrState_Timeout_RetVal = TRUE
///
/// - Expectations:
///
/// \output DblCrState_Timeout_RetVal                                      = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_DblCrState_Timeout_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  DblCrState_Timeout_Param1 = 0u;
  DblCrState_Timeout_Param2 = 0u;
  DblCrState_Timeout_Param3 = DBLCRSTATE_NUMBER_OF_TIMERS + 1u;
  DblCrState_Timeout_RetVal = TRUE;

  //Step 3) Call FUT
  DblCrState_Timeout_RetVal = DblCrState_Timeout(DblCrState_Timeout_Param1, DblCrState_Timeout_Param2, DblCrState_Timeout_Param3);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(DblCrState_Timeout_RetVal                                     , FALSE, == );
}

//-----------------------------------------------------------------------------
/// Mt_DblCrState_Timeout    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_DblCrState_Timeout(void)
{
  Mt_DblCrState_Timeout_TestCase_1();
  Mt_DblCrState_Timeout_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test rte wrapper 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID;
///
/// - Expectations:
///
/// \output Dbl_RteAccess_ReadEtatReseauElec_RetVal                                = Dbl_SIG_INVALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  //Step 3) Call FUT
  Dbl_RteAccess_ReadEtatReseauElec_RetVal = Dbl_RteAccess_ReadEtatReseauElec();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadEtatReseauElec_RetVal, Dbl_SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test rte wrapper 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_INIT;
///
/// - Expectations:
///
/// \output Dbl_RteAccess_ReadEtatReseauElec_RetVal                                = Dbl_SIG_INVALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INIT;
  //Step 3) Call FUT
  Dbl_RteAccess_ReadEtatReseauElec_RetVal = Dbl_RteAccess_ReadEtatReseauElec();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadEtatReseauElec_RetVal, Dbl_SIG_VALID, == );

}


//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test rte wrapper 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_SNA;
///
/// - Expectations:
///
/// \output DblCrState_Timeout_RetVal                                = Dbl_SIG_INVALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_SNA;
  //Step 3) Call FUT
  Dbl_RteAccess_ReadEtatReseauElec_RetVal = Dbl_RteAccess_ReadEtatReseauElec();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadEtatReseauElec_RetVal, Dbl_SIG_VALID, == );

}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test rte wrapper 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty               = SIG_VALID;
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eInvalid;
///
/// - Expectations:
///
/// \output DblCrState_Timeout_RetVal                                      = Dbl_SIG_INVALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eInvalid;
  //Step 3) Call FUT
  Dbl_RteAccess_ReadEtatReseauElec_RetVal = Dbl_RteAccess_ReadEtatReseauElec();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadEtatReseauElec_RetVal, Dbl_SIG_INVALID, == );

}
//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadEtatReseauElec    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------   
void Mt_Dbl_RteAccess_ReadEtatReseauElec(void)
{
  Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_1();
  Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_2();
  Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_3();
  Mt_Dbl_RteAccess_ReadEtatReseauElec_TestCase_4();
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadVehicleSpeed_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test valid signal case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl = SIG_VALID;
///
/// - Expectations: Dbl_RteAccess_ReadVehicleSpeed_RetVal.eSigQty = Dbl_SIG_VALID
///
/// \output
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadVehicleSpeed_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl = SIG_VALID;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVehicleSpeed_RetVal = Dbl_RteAccess_ReadVehicleSpeed();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVehicleSpeed_RetVal.eSigQty, Dbl_SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadVehicleSpeed_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test invalid signal case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl = SIG_INVALID
///
/// \input
///
/// - Expectations: Dbl_RteAccess_ReadVehicleSpeed_RetVal.eSigQty = Dbl_SIG_INVALID
///
/// \output
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadVehicleSpeed_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl = SIG_INVALID;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadVehicleSpeed_RetVal = Dbl_RteAccess_ReadVehicleSpeed();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadVehicleSpeed_RetVal.eSigQty, Dbl_SIG_INVALID, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadVehicleSpeed    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_Dbl_RteAccess_ReadVehicleSpeed(void)
{
  Mt_Dbl_RteAccess_ReadVehicleSpeed_TestCase_1();
  Mt_Dbl_RteAccess_ReadVehicleSpeed_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadSteeringWheelAngle_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test valid signal case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty
///
/// - Expectations:
///
/// \output Dbl_RteAccess_ReadSteeringWheelAngle_RetVal.eSigQty = Dbl_SIG_VALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadSteeringWheelAngle_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty = SIG_VALID;
  //Step 3) Call FUT
  Dbl_RteAccess_ReadSteeringWheelAngle_RetVal = Dbl_RteAccess_ReadSteeringWheelAngle();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSteeringWheelAngle_RetVal.eSigQty, Dbl_SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadSteeringWheelAngle_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test invalid signal case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty = SIG_INVALID
///
/// - Expectations:
///
/// \output Dbl_RteAccess_ReadSteeringWheelAngle_RetVal.eSigQty = Dbl_SIG_INVALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadSteeringWheelAngle_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty = SIG_INVALID;
  //Step 3) Call FUT
  Dbl_RteAccess_ReadSteeringWheelAngle_RetVal = Dbl_RteAccess_ReadSteeringWheelAngle();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadSteeringWheelAngle_RetVal.eSigQty, Dbl_SIG_INVALID, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadSteeringWheelAngle    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_Dbl_RteAccess_ReadSteeringWheelAngle(void)
{
  Mt_Dbl_RteAccess_ReadSteeringWheelAngle_TestCase_1();
  Mt_Dbl_RteAccess_ReadSteeringWheelAngle_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadYawSpeed_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test valid signal ccase
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input
/// \input
///
/// - Expectations:
///
/// \output
/// \output
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadYawSpeed_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty = SIG_VALID;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadYawSpeed_RetVal = Dbl_RteAccess_ReadYawSpeed();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadYawSpeed_RetVal.eSigQty, Dbl_SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadYawSpeed_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test invalid signal case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty
///
/// - Expectations:
///
/// \output Dbl_RteAccess_ReadYawSpeed_RetVal.eSigQty = Dbl_SIG_INVALID
/// \output
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_RteAccess_ReadYawSpeed_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty = SIG_INVALID;

  //Step 3) Call FUT
  Dbl_RteAccess_ReadYawSpeed_RetVal = Dbl_RteAccess_ReadYawSpeed();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_RteAccess_ReadYawSpeed_RetVal.eSigQty, Dbl_SIG_INVALID, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_RteAccess_ReadYawSpeed    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_Dbl_RteAccess_ReadYawSpeed(void)
{
  Mt_Dbl_RteAccess_ReadYawSpeed_TestCase_1();
  Mt_Dbl_RteAccess_ReadYawSpeed_TestCase_2();
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_Timeout_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if number of selected timers protection works
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_Timeout_Param1 = 0u
/// \input Dbl_Timeout_Param2 = 0u
/// \input Dbl_Timeout_Param3 = DBL_NUMBER_OF_TIMERS - 1u
/// \input Dbl_Timeout_RetVal = TRUE
///
/// - Expectations:
///
/// \output Dbl_sTimerCfg[Dbl_Timeout_Param3].ulTimeMs_Input = Dbl_Timeout_Param2
/// \output Dbl_sTimerCfg[Dbl_Timeout_Param3].boReq_Input    = Dbl_Timeout_Param1
/// \output Dbl_Timeout_RetVal                                      = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_Timeout_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_Timeout_Param1 = 0u;
  Dbl_Timeout_Param2 = 0u;
  Dbl_Timeout_Param3 = DBL_NUMBER_OF_TIMERS - 1u;
  Dbl_Timeout_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Timeout_RetVal = Dbl_Timeout(Dbl_Timeout_Param1, Dbl_Timeout_Param2, Dbl_Timeout_Param3);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_sTimerCfg[Dbl_Timeout_Param3].ulTimeMs_Input, Dbl_Timeout_Param2, == );
  AL_UNITTEST_CHECK(Dbl_sTimerCfg[Dbl_Timeout_Param3].boReq_Input, Dbl_Timeout_Param1, == );
  AL_UNITTEST_CHECK(Dbl_Timeout_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_Timeout_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if number of selected timers protection works
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_Timeout_Param1 = 0u
/// \input Dbl_Timeout_Param2 = 0u
/// \input Dbl_Timeout_Param3 = DBL_NUMBER_OF_TIMERS - 1u
/// \input Dbl_Timeout_RetVal = TRUE
///
/// - Expectations:
///
/// \output Dbl_Timeout_RetVal                                      = FALSE
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_Timeout_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_Timeout_Param1 = 0u;
  Dbl_Timeout_Param2 = 0u;
  Dbl_Timeout_Param3 = DBL_NUMBER_OF_TIMERS + 1u;
  Dbl_Timeout_RetVal = TRUE;

  //Step 3) Call FUT
  Dbl_Timeout_RetVal = Dbl_Timeout(Dbl_Timeout_Param1, Dbl_Timeout_Param2, Dbl_Timeout_Param3);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_Timeout_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_Timeout    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_Dbl_Timeout(void)
{
  Mt_Dbl_Timeout_TestCase_1();
  Mt_Dbl_Timeout_TestCase_2();
}



//-----------------------------------------------------------------------------
/// Mt_Dbl_HandleDelayStatus_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test timer input in start case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_HandleDelayStatus_Param2                                                       = 0u;
/// \input Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boReq_Input      = TRUE;
/// \input Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = FALSE;
///
/// - Expectations:
///
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].ulCommandStart == UTILTIME_TIMER_START(UTILTIME_MSEC(Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].ulTimeMs_Input))
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer == TRUE
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_HandleDelayStatus_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_HandleDelayStatus_Param2 = 0u;
  Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boReq_Input = TRUE;
  Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = FALSE;

  //Step 3) Call FUT
  Dbl_HandleDelayStatus_RetVal = Dbl_HandleDelayStatus(Dbl_HandleDelayStatus_Param1, Dbl_HandleDelayStatus_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].ulCommandStart, UTILTIME_TIMER_START(UTILTIME_MSEC(Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].ulTimeMs_Input)), == );
  AL_UNITTEST_CHECK(Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer, TRUE, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_HandleDelayStatus_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test timer input in reset case
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_HandleDelayStatus_Param2                                                       = 0u;
/// \input Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boReq_Input      = FALSE;
/// \input Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = FALSE;
///
/// - Expectations:
///
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boTimeOut        = FALSE
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = FALSE
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].ulCommandStart   = 0u
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_HandleDelayStatus_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_HandleDelayStatus_Param2 = 0u;
  Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boReq_Input = FALSE;
  Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = FALSE;

  //Step 3) Call FUT
  Dbl_HandleDelayStatus_RetVal = Dbl_HandleDelayStatus(Dbl_HandleDelayStatus_Param1, Dbl_HandleDelayStatus_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boTimeOut, FALSE, == );
  AL_UNITTEST_CHECK(Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer, FALSE, == );
  AL_UNITTEST_CHECK(Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].ulCommandStart, 0u, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_HandleDelayStatus_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if timer is still running
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_HandleDelayStatus_Param2                                                       = 0u
/// \input Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = FALSE
///
/// - Expectations:
///
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boTimeOut        = FALSE
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = FALSE
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].ulCommandStart   = 0u
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_HandleDelayStatus_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_HandleDelayStatus_Param2 = 0u;
  Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boReq_Input = TRUE;
  Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = FALSE;

  LPTMR0_GetTimeElapsed_RetVal = 100000000;
  //Step 3) Call FUT
  Dbl_HandleDelayStatus_RetVal = Dbl_HandleDelayStatus(Dbl_HandleDelayStatus_Param1, Dbl_HandleDelayStatus_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boTimeOut, UTILTIME_TIMER_TIMEOUT(Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].ulCommandStart), == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_HandleDelayStatus_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if timer is not running

///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_HandleDelayStatus_Param2                                                       = 0u
/// \input Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = TRUE
/// \input Dbl_HandleDelayStatus_RetVal = FALSE
///
/// - Expectations:
///
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boTimeOut        = FALSE
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = FALSE
/// \output Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].ulCommandStart   = 0u
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_HandleDelayStatus_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_HandleDelayStatus_Param2 = 0u;
  Dbl_HandleDelayStatus_Param1[Dbl_HandleDelayStatus_Param2].boStartStopTimer = TRUE;
  Dbl_HandleDelayStatus_RetVal = FALSE;

  //Step 3) Call FUT
  Dbl_HandleDelayStatus_RetVal = Dbl_HandleDelayStatus(Dbl_HandleDelayStatus_Param1, Dbl_HandleDelayStatus_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_HandleDelayStatus_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// Mt_Dbl_HandleDelayStatus    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if function check short to ground error 
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_Dbl_HandleDelayStatus(void)
{
  Mt_Dbl_HandleDelayStatus_TestCase_1();
  Mt_Dbl_HandleDelayStatus_TestCase_2();
  Mt_Dbl_HandleDelayStatus_TestCase_3();
  Mt_Dbl_HandleDelayStatus_TestCase_4();
}

//-----------------------------------------------------------------------------
/// void Mt_Dbl_FilterIIR_Input(void)
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if filter works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dbl_FilterIIR_Input_Param1 = 100u
/// \input  Dbl_FilterIIR_Input_RetVal = 1u
///
/// - Expectations:
///
/// \output Dbl_FilterIIR_Input_RetVal        = 0u
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_FilterIIR_Input(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_FilterIIR_Input_Param1 = 100;
  Dbl_FilterIIR_Input_RetVal = 1;

  //Step 3) Call FUT
  Dbl_FilterIIR_Input_RetVal = Dbl_FilterIIR_Input(Dbl_FilterIIR_Input_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_FilterIIR_Input_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// void Mt_Dbl_FilterIIR_Input(void)
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if filter works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_Get_Filtered_Calculated_Curvature_Value_Param1 = 100u
/// \input Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal = 1u
/// \input Dbl_sCrCalcFilterData.ucFilterTracking            = 0u
///
/// - Expectations:
///
/// \output Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal        = 0u
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_Get_Filtered_Calculated_Curvature_Value_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_Get_Filtered_Calculated_Curvature_Value_Param1 = 100u;
  Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal = 1u;
  Dbl_sCrCalcFilterData.ucFilterTracking            = 0u;

  //Step 3) Call FUT
  Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal = Dbl_Get_Filtered_Calculated_Curvature_Value(Dbl_Get_Filtered_Calculated_Curvature_Value_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// void Mt_Dbl_Get_Filtered_Calculated_Curvature_Value_TestCase_2(void)
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if filter works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dbl_Get_Filtered_Calculated_Curvature_Value_Param1 = 100;
/// \input  Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal = 1;
/// \input  Dbl_sCrCalcFilterData.ucFilterTracking            = 5;
///
/// - Expectations:
///
/// \output Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal= -10000u
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_Get_Filtered_Calculated_Curvature_Value_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_Get_Filtered_Calculated_Curvature_Value_Param1 = 100;
  Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal = 1;
  Dbl_sCrCalcFilterData.ucFilterTracking            = 5;

  //Step 3) Call FUT
  Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal = Dbl_Get_Filtered_Calculated_Curvature_Value(Dbl_Get_Filtered_Calculated_Curvature_Value_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_Get_Filtered_Calculated_Curvature_Value_RetVal, -10000u, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_Get_Filtered_Calculated_Curvature_Value    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if all contained test cases are passed
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_Dbl_Get_Filtered_Calculated_Curvature_Value(void)
{
  Mt_Dbl_Get_Filtered_Calculated_Curvature_Value_TestCase_1();
  Mt_Dbl_Get_Filtered_Calculated_Curvature_Value_TestCase_2();
}

//-----------------------------------------------------------------------------
/// void Mt_Dbl_Get_Calculated_Curvature_Coding_Parameters(void)
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if function gets correct coding parameters
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_sCrCalcFilterData.ucFilterTimePrio      = 0u
/// \input Dbl_sCrCalcFilterData.ucFilterTracking      = 0u
/// \input Dbl_sCrCalcFilterData.ucFilterTrackingRange = 0u
/// \input  Dbl_sCodingParam.psCodingParameters_Blocks = &Coding_Dummy;
/// \input  Coding_Dummy.Dbl.AfsHld.ucFilterTracking   = 9u;
///
/// - Expectations:
///
/// \output Dbl_sCrCalcFilterData.ucFilterTracking        = 9u
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_Get_Calculated_Curvature_Coding_Parameters(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_sCrCalcFilterData.ucFilterTimePrio      = 0u;
  Dbl_sCrCalcFilterData.ucFilterTracking      = 0u;
  Dbl_sCrCalcFilterData.ucFilterTrackingRange = 0u;
  Dbl_sCodingParam.psCodingParameters_Blocks  = &Coding_Dummy;
  Coding_Dummy.Dbl.AfsHld.ucFilterTracking    = 9u;

  //Step 3) Call FUT
  Dbl_Get_Calculated_Curvature_Coding_Parameters();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_sCrCalcFilterData.ucFilterTracking, 9u, == );

}

//-----------------------------------------------------------------------------
/// void Mt_Dbl_Curvature_SigQty_TestCase_1(void)
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if function gets correct signal quality for VehPathCurvature
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy
/// \input DblCrState_unEgoVehicleMotionConfirmation                                   = 0u
/// \input Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u
/// \input Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode                               = 1u
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                                    = SIG_VALID
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                          = SIG_VALID
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                                  = SIG_VALID
/// \input DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal            = FALSE
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle              = DBL_CURVATURE_INVALID_VALUE + 1
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState                    = eTA_NOMINAL
/// \input Dbl_Curvature_SigQty_RetVal                                                 = SIG_INVALID
///
/// - Expectations:
///
/// \output Dbl_Curvature_SigQty_RetVal                                               =  SIG_VALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_Curvature_SigQty_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
  DblCrState_unEgoVehicleMotionConfirmation                                   = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u;
  Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode                               = 1u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                                    = SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                          = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                                  = SIG_VALID;
  DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal            = FALSE;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle              = DBL_CURVATURE_INVALID_VALUE + 1;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState                    = eTA_NOMINAL;
  Dbl_Curvature_SigQty_RetVal                                                 = SIG_INVALID;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_RetVal = Dbl_Curvature_SigQty();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_Curvature_SigQty_RetVal, SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// void Mt_Dbl_Curvature_SigQty_TestCase_2(void)
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if function gets correct signal quality for VehPathCurvature
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy
/// \input DblCrState_unEgoVehicleMotionConfirmation                                   = 0u
/// \input Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u
/// \input Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode                               = 1u
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID
/// \input Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                                    = SIG_VALID
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                          = SIG_VALID
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_INVALID
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty                                  = SIG_VALID
/// \input DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal            = FALSE
/// \input Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle              = DBL_CURVATURE_INVALID_VALUE + 1
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState                    = eTA_NOMINAL
/// \input Dbl_Curvature_SigQty_RetVal                                                 = SIG_VALID
///
/// - Expectations:
///
/// \output Dbl_Curvature_SigQty_RetVal                                               =  SIG_INVALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_Curvature_SigQty_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
  DblCrState_unEgoVehicleMotionConfirmation                                   = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u;
  Coding_Dummy.Dbl.DisableFuncs.ucCurvatureMode                               = 1u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID;
  Rte_Read_SigPrep_YawSpeed_Param1.eSigQty                                    = SIG_VALID;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.eSigQty                          = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_INVALID;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty                                  = SIG_VALID;
  DblCrState_Transition_CalculationPhase_Invalid_to_Nominal_RetVal            = FALSE;
  Rte_Read_SigPrep_SteeringWheelAngle_Param1.nSteeringWheelAngle              = DBL_CURVATURE_INVALID_VALUE + 1;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState                    = eTA_NOMINAL;
  Dbl_Curvature_SigQty_RetVal                                                 = SIG_VALID;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_RetVal = Dbl_Curvature_SigQty();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_Curvature_SigQty_RetVal, SIG_INVALID, == );
}

//-----------------------------------------------------------------------------
/// void Mt_Dbl_Curvature_SigQty_TestCase_3(void)
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if function gets correct signal quality for VehPathCurvature
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy
/// \input DblCrState_unEgoVehicleMotionConfirmation                                   = 0u
/// \input Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID
/// \input Dbl_Curvature_SigQty_RetVal                                                 = SIG_INVALID
///
/// - Expectations:
///
/// \output Dbl_Curvature_SigQty_RetVal                                               =  SIG_VALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_Curvature_SigQty_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
  DblCrState_unEgoVehicleMotionConfirmation                                   = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID;
  Dbl_Curvature_SigQty_RetVal                                                 = SIG_INVALID;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_RetVal = Dbl_Curvature_SigQty();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_Curvature_SigQty_RetVal, SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// void Mt_Dbl_Curvature_SigQty_TestCase_4(void)
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: - Test subject: Test if function gets correct signal quality for VehPathCurvature
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy
/// \input DblCrState_unEgoVehicleMotionConfirmation                                   = 0u
/// \input Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID
/// \input Dbl_Curvature_SigQty_RetVal                                                 = SIG_INVALID
///
/// - Expectations:
///
/// \output Dbl_Curvature_SigQty_RetVal                                               =  SIG_VALID
///
//----------------------------------------------------------------------------- 
void Mt_Dbl_Curvature_SigQty_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dbl_sCodingParam.psCodingParameters_Blocks                                  = &Coding_Dummy;
  DblCrState_unEgoVehicleMotionConfirmation                                   = 0u;
  Coding_Dummy.Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME        = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQtyDbl                                 = SIG_VALID;
  Dbl_Curvature_SigQty_RetVal                                                 = SIG_INVALID;

  //Step 3) Call FUT
  Dbl_Curvature_SigQty_RetVal = Dbl_Curvature_SigQty();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dbl_Curvature_SigQty_RetVal, SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// Mt_Dbl_Curvature_SigQty    
/// 
/// \FuSa Relevant: NA 
/// 
/// \Test Case Description 
///        - Test subject: Test if all contained test cases are passed
/// 
///         - Test Design Technique:  - ET (Exploratory Testing) 
/// 
/// \Expected test results : All test cases contained are passed 
/// 
//-----------------------------------------------------------------------------                                                                             
void Mt_Dbl_Curvature_SigQty(void)
{
  Mt_Dbl_Curvature_SigQty_TestCase_1();
  Mt_Dbl_Curvature_SigQty_TestCase_2();
  Mt_Dbl_Curvature_SigQty_TestCase_3();
  Mt_Dbl_Curvature_SigQty_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \brief  ALUnitTest_AddTests
///
/// \descr  Every test case shall be added to this list
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void ALUnitTest_AddTests(void)
{
  ALUnitTest_AddFunction("Mt_Dbl__ClPolySolverCalcMaxStartSlope",                                  Mt_Dbl__ClPolySolverCalcMaxStartSlope                             );
  ALUnitTest_AddFunction("Mt_Dbl_UtilLinearInterpolatePClamp32",                                   Mt_Dbl_UtilLinearInterpolatePClamp32                              );
  ALUnitTest_AddFunction("Mt_Dbl__ClPolySolverCalcStartSlope",                                     Mt_Dbl__ClPolySolverCalcStartSlope                                );
  ALUnitTest_AddFunction("Mt_Dbl_UtilMath_LinearInterpolateP32",                                   Mt_Dbl_UtilMath_LinearInterpolateP32                              );
  ALUnitTest_AddFunction("Mt_Dbl__ClPolySolverCalcEndSlope",                                       Mt_Dbl__ClPolySolverCalcEndSlope                                  );
  ALUnitTest_AddFunction("Mt_Dbl__ClPolySolverCalcEndC",                                           Mt_Dbl__ClPolySolverCalcEndC                                      );
  ALUnitTest_AddFunction("Mt_Dbl_ClPolySolver",                                                    Mt_Dbl_ClPolySolver                                               );
  ALUnitTest_AddFunction("Mt_Dbl_ClResetSpeedFilter",                                              Mt_Dbl_ClResetSpeedFilter                                         );
  ALUnitTest_AddFunction("Mt_Dbl_ClHlaIdlePosition",                                               Mt_Dbl_ClHlaIdlePosition                                          );
  ALUnitTest_AddFunction("Mt_Dbl_ClHlaAttenuationFactor",                                          Mt_Dbl_ClHlaAttenuationFactor                                     );
  ALUnitTest_AddFunction("Mt_Dbl_ClPoly3",                                                         Mt_Dbl_ClPoly3                                                    );
  ALUnitTest_AddFunction("Mt_Dbl_LrRelation2",                                                     Mt_Dbl_LrRelation2                                                );
  ALUnitTest_AddFunction("Mt_Dbl_DblcCl",                                                          Mt_Dbl_DblcCl                                                     );
  ALUnitTest_AddFunction("Mt_Dbl_Call_StateNormal",                                                Mt_Dbl_Call_StateNormal                                           );
  ALUnitTest_AddFunction("Mt_Dbl_ClIdleSignal",                                                    Mt_Dbl_ClIdleSignal                                               );
  ALUnitTest_AddFunction("Mt_Dbl_Time2Inc",                                                        Mt_Dbl_Time2Inc                                                   );
  ALUnitTest_AddFunction("Mt_Dbl_Time2Step",                                                       Mt_Dbl_Time2Step                                                  );
  ALUnitTest_AddFunction("Mt_Dbl_ClIdleRange",                                                     Mt_Dbl_ClIdleRange                                                );
  ALUnitTest_AddFunction("Mt_Dbl_CalcIdleRange",                                                   Mt_Dbl_CalcIdleRange                                              );
  ALUnitTest_AddFunction("Mt_DblDblc_Convert_Deg_mRad",                                            Mt_DblDblc_Convert_Deg_mRad                                       );
  ALUnitTest_AddFunction("Mt_Dbl_Dblc_Convert_Deg_mRadHr",                                         Mt_Dbl_Dblc_Convert_Deg_mRadHr                                    );
  ALUnitTest_AddFunction("Mt_Dbl_DblcCalculateSwiveling",                                          Mt_Dbl_DblcCalculateSwiveling                                     );
  ALUnitTest_AddFunction("Mt_Dbl_DblcLimitSwiveling",                                              Mt_Dbl_DblcLimitSwiveling                                         );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadDblCmd",                                            Mt_Dbl_RteAccess_ReadDblCmd                                       );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadSwimRate",                                          Mt_Dbl_RteAccess_ReadSwimRate                                     );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadSpeed",                                             Mt_Dbl_RteAccess_ReadSpeed                                        );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR",                              Mt_Dbl_RteAccess_ReadDynBendingBeamFaultR                         );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL",                              Mt_Dbl_RteAccess_ReadDynBendingBeamFaultL                         );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadSteeringType",                                      Mt_Dbl_RteAccess_ReadSteeringType                                 );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadEnvCondition",                                      Mt_Dbl_RteAccess_ReadEnvCondition                                 );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadCurvature",                                         Mt_Dbl_RteAccess_ReadCurvature                                    );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadReverseGearStatus",                                 Mt_Dbl_RteAccess_ReadReverseGearStatus                            );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadVehicleModeConfig",                                 Mt_Dbl_RteAccess_ReadVehicleModeConfig                            );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadVESMainState",                                      Mt_Dbl_RteAccess_ReadVESMainState                                 );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadVehicleElectricState",                              Mt_Dbl_RteAccess_ReadVehicleElectricState                         );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_WriteDblOutput",                                        Mt_Dbl_RteAccess_WriteDblOutput                                   );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_WriteDblSysMonTx_FullStatus",                           Mt_Dbl_RteAccess_WriteDblSysMonTx_FullStatus                      );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus",                     Mt_Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus                );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadDblOutput",                                         Mt_Dbl_RteAccess_ReadDblOutput                                    );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadDblTrafficSide",                                    Mt_Dbl_RteAccess_ReadDblTrafficSide                               );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_Read_EcuSide",                                          Mt_Dbl_RteAccess_Read_EcuSide                                     );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_WriteDriveSituation",                                   Mt_Dbl_RteAccess_WriteDriveSituation                              );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadGfhbCmd",                                           Mt_Dbl_RteAccess_ReadGfhbCmd                                      );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadHbCmd",                                             Mt_Dbl_RteAccess_ReadHbCmd                                        );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadFlashBeamCmd",                                      Mt_Dbl_RteAccess_ReadFlashBeamCmd                                 );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_WriteSwimRate",                                         Mt_Dbl_RteAccess_WriteSwimRate                                    );
  ALUnitTest_AddFunction("Mt_Dbl_Read_PhaseVie",                                                   Mt_Dbl_Read_PhaseVie                                              );
  ALUnitTest_AddFunction("Mt_Dbl_RetPowerTrainActive",                                             Mt_Dbl_RetPowerTrainActive                                        );
  ALUnitTest_AddFunction("Mt_Dbl_GetHBStatus",                                                     Mt_Dbl_GetHBStatus                                                );
  ALUnitTest_AddFunction("Mt_Dbl_ReadFault",                                                       Mt_Dbl_ReadFault                                                  );
  ALUnitTest_AddFunction("Mt_Dbl_DefOfFailure",                                                    Mt_Dbl_DefOfFailure                                               );
  ALUnitTest_AddFunction("Mt_Dbl_RetDigitalSwivelingFunctionalFault_LR",                           Mt_Dbl_RetDigitalSwivelingFunctionalFault_LR                      );
  ALUnitTest_AddFunction("Mt_Dbl_DetectMode",                                                      Mt_Dbl_DetectMode                                                 );
  ALUnitTest_AddFunction("Mt_Dbl_UseMode",                                                         Mt_Dbl_UseMode                                                    );
  ALUnitTest_AddFunction("Mt_Dbl_UseSubMode",                                                      Mt_Dbl_UseSubMode                                                 );
  ALUnitTest_AddFunction("Mt_Dbl_ModeAssembly",                                                    Mt_Dbl_ModeAssembly                                               );
  ALUnitTest_AddFunction("Mt_Dbl_ModeCustomer",                                                    Mt_Dbl_ModeCustomer                                               );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Assembly_To_Frozen",                                   Mt_Dbl_Transition_Assembly_To_Frozen                              );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Customer_To_Unavailable",                              Mt_Dbl_Transition_Customer_To_Unavailable                         );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Customer_To_Available",                                Mt_Dbl_Transition_Customer_To_Available                           );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Fail_To_Init",                                         Mt_Dbl_Transition_Fail_To_Init                                    );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Init_To_Nominal",                                      Mt_Dbl_Transition_Init_To_Nominal                                 );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Fail_To_Nominal",                                      Mt_Dbl_Transition_Fail_To_Nominal                                 );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Adj_To_Nominal",                                       Mt_Dbl_Transition_Adj_To_Nominal                                  );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Nominal_To_Adj",                                       Mt_Dbl_Transition_Nominal_To_Adj                                  );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Init_To_Adj",                                          Mt_Dbl_Transition_Init_To_Adj                                     );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Fail_To_Adj",                                          Mt_Dbl_Transition_Fail_To_Adj                                     );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Init_To_Fail",                                         Mt_Dbl_Transition_Init_To_Fail                                    );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Nominal_To_Fail",                                      Mt_Dbl_Transition_Nominal_To_Fail                                 );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Adj_To_Fail",                                          Mt_Dbl_Transition_Adj_To_Fail                                     );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Adj_To_Init",                                          Mt_Dbl_Transition_Adj_To_Init                                     );
  ALUnitTest_AddFunction("Mt_Dbl_Transition_Nominal_To_Init",                                      Mt_Dbl_Transition_Nominal_To_Init                                 );
  ALUnitTest_AddFunction("Mt_Dbl_ReadEnvironmentSignals",                                          Mt_Dbl_ReadEnvironmentSignals                                     );
  ALUnitTest_AddFunction("Mt_Dbl_DblcSm_ParaFct0",                                                 Mt_Dbl_DblcSm_ParaFct0                                            );
  ALUnitTest_AddFunction("Mt_Dbl_DetectSide",                                                      Mt_Dbl_DetectSide                                                 );
  ALUnitTest_AddFunction("Mt_Dbl_GetSide",                                                         Mt_Dbl_GetSide                                                    );
  ALUnitTest_AddFunction("Mt_Dbl_GetTrafficSide",                                                  Mt_Dbl_GetTrafficSide                                             );
  ALUnitTest_AddFunction("Mt_Dbl_DblcSm_Init",                                                     Mt_Dbl_DblcSm_Init                                                );
  ALUnitTest_AddFunction("Mt_Dbl_DblcOutputContro",                                                Mt_Dbl_DblcOutputContro                                           );
  ALUnitTest_AddFunction("Mt_Dbl_SetSteerbackDetection",                                           Mt_Dbl_SetSteerbackDetection                                      );
  ALUnitTest_AddFunction("Mt_Dbl_Mrad2MDeg",                                                       Mt_Dbl_Mrad2MDeg                                                  );
  ALUnitTest_AddFunction("Mt_Dbl_Call_StateOff",                                                   Mt_Dbl_Call_StateOff                                              );
  ALUnitTest_AddFunction("Mt_Dbl_Call_StateHold",                                                  Mt_Dbl_Call_StateHold                                             );
  ALUnitTest_AddFunction("Mt_Dbl_StateMachine_StateInit",                                          Mt_Dbl_StateMachine_StateInit                                     );
  ALUnitTest_AddFunction("Mt_Dbl_StateMachine_StateNominal",                                       Mt_Dbl_StateMachine_StateNominal                                  );
  ALUnitTest_AddFunction("Mt_Dbl_StateMachine_StateFail",                                          Mt_Dbl_StateMachine_StateFail                                     );
  ALUnitTest_AddFunction("Mt_Dbl_HbActive",                                                        Mt_Dbl_HbActive                                                   );
  ALUnitTest_AddFunction("Mt_Dbl_Write_OutputValues",                                              Mt_Dbl_Write_OutputValues                                         );
  ALUnitTest_AddFunction("Mt_Dbl_StateMachine_StateAdj",                                           Mt_Dbl_StateMachine_StateAdj                                      );
  ALUnitTest_AddFunction("Mt_Dbl_SubModeFrozen",                                                   Mt_Dbl_SubModeFrozen                                              );
  ALUnitTest_AddFunction("Mt_Dbl_SubModeUnavailable",                                              Mt_Dbl_SubModeUnavailable                                         );
  ALUnitTest_AddFunction("Mt_Dbl_GetTimer",                                                        Mt_Dbl_GetTimer                                                   );
  ALUnitTest_AddFunction("Mt_Dbl_ConstHighSpeed_Detect",                                           Mt_Dbl_ConstHighSpeed_Detect                                      );
  ALUnitTest_AddFunction("Mt_Dbl_ReadInputSignals",                                                Mt_Dbl_ReadInputSignals                                           );
  ALUnitTest_AddFunction("Mt_Dbl_Init",                                                            Mt_Dbl_Init                                                       );
  ALUnitTest_AddFunction("Mt_Dbl_Cycle",                                                           Mt_Dbl_Cycle                                                      );
  ALUnitTest_AddFunction("Mt_Dbl_riDbl_Init",                                                      Mt_Dbl_riDbl_Init                                                 );
  ALUnitTest_AddFunction("Mt_Dbl_rpDbl_Cycle",                                                     Mt_Dbl_rpDbl_Cycle                                                );
  ALUnitTest_AddFunction("Mt_Dbl_StMch",                                                           Mt_Dbl_StMch                                                      );
  ALUnitTest_AddFunction("Mt_Dbl_Call_StateFailure",                                               Mt_Dbl_Call_StateFailure                                          );
  ALUnitTest_AddFunction("Mt_Dbl_SmoothTransition",                                                Mt_Dbl_SmoothTransition                                           );
  ALUnitTest_AddFunction("Mt_Dbl_Reset_Flags",                                                     Mt_Dbl_Reset_Flags                                                );
  ALUnitTest_AddFunction("Mt_DblCrvCalc_Get_CurvatureCodingParameters",                            Mt_DblCrvCalc_Get_CurvatureCodingParameters                       );
  ALUnitTest_AddFunction("Mt_DblCrvCalc_Get_WfCodingParameters",                                   Mt_DblCrvCalc_Get_WfCodingParameters                              );
  ALUnitTest_AddFunction("Mt_DblCrvCalc_ProcessAngle",                                             Mt_DblCrvCalc_ProcessAngle                                        );
  ALUnitTest_AddFunction("Mt_DblCrvCalc_getLinearInterpolatedValue",                               Mt_DblCrvCalc_getLinearInterpolatedValue                          );
  ALUnitTest_AddFunction("Mt_DblCrvCalc_WeightingFactorCalculation",                               Mt_DblCrvCalc_WeightingFactorCalculation                          );
  ALUnitTest_AddFunction("Mt_DblCrvCalc_FindWfZone",                                               Mt_DblCrvCalc_FindWfZone                                          );
  ALUnitTest_AddFunction("Mt_DblCrvCalc_GetSin",                                                   Mt_DblCrvCalc_GetSin                                              );
  ALUnitTest_AddFunction("Mt_DblCrvCalc_getCurvatureValue",                                        Mt_DblCrvCalc_getCurvatureValue                                   );
  ALUnitTest_AddFunction("Mt_DblCrState_Init",                                                     Mt_DblCrState_Init                                                );
  ALUnitTest_AddFunction("Mt_DblCrState_State_Machine",                                            Mt_DblCrState_State_Machine                                       );
  ALUnitTest_AddFunction("Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid",           Mt_DblCrState_Transition_CalculationPhase_Nominal_to_Invalid      );
  ALUnitTest_AddFunction("Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal",           Mt_DblCrState_Transition_CalculationPhase_Invalid_to_Nominal      );
  ALUnitTest_AddFunction("Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable",      Mt_DblCrState_Transition_CalculationMode_Available_to_Unavailable );
  ALUnitTest_AddFunction("Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available",      Mt_DblCrState_Transition_CalculationMode_Unavailable_to_Available );
  ALUnitTest_AddFunction("Mt_DblCrState_PowerTrain_State",                                         Mt_DblCrState_PowerTrain_State                                    );
  ALUnitTest_AddFunction("Mt_DblCrState_HandleDelayStatus",                                        Mt_DblCrState_HandleDelayStatus                                   );
  ALUnitTest_AddFunction("Mt_DblCrState_Timeout",                                                  Mt_DblCrState_Timeout                                             );
  ALUnitTest_AddFunction("Mt_Dbl_Curvature_SigQty_INV",                                            Mt_Dbl_Curvature_SigQty_INV                                       );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadEtatReseauElec",                                    Mt_Dbl_RteAccess_ReadEtatReseauElec                               );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadVehicleSpeed",                                      Mt_Dbl_RteAccess_ReadVehicleSpeed                                 );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadSteeringWheelAngle",                                Mt_Dbl_RteAccess_ReadSteeringWheelAngle                           );
  ALUnitTest_AddFunction("Mt_Dbl_RteAccess_ReadYawSpeed",                                          Mt_Dbl_RteAccess_ReadYawSpeed                                     );
  ALUnitTest_AddFunction("Mt_Dbl_Timeout",                                                         Mt_Dbl_Timeout                                                    );
  ALUnitTest_AddFunction("Mt_Dbl_HandleDelayStatus",                                               Mt_Dbl_HandleDelayStatus                                          );
  ALUnitTest_AddFunction("Mt_Dbl_FilterIIR_Input",                                                 Mt_Dbl_FilterIIR_Input                                            );
  ALUnitTest_AddFunction("Mt_Dbl_Get_Filtered_Calculated_Curvature_Value",                          Mt_Dbl_Get_Filtered_Calculated_Curvature_Value                   );
  ALUnitTest_AddFunction("Mt_Dbl_Get_Calculated_Curvature_Coding_Parameters",                      Mt_Dbl_Get_Calculated_Curvature_Coding_Parameters                 );
  ALUnitTest_AddFunction("Mt_Dbl_Curvature_SigQty",                                                Mt_Dbl_Curvature_SigQty                                           );
}
// EOF
