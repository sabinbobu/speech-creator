/******************************************************************************/
/*!
* \file     ILCU_LevellingAdapter.c
*
* \brief    Single integration point between ILCU and the ASL chain ported
*           from DPE (ECO): AvacStat1 -> CtrlDcm -> CddDcm.
*
* \descr    - Schedules the ported runnables at their DPE rates.
*           - Implements the DPE RTE ports: chain-internal ports are static
*             buffers, absent vehicle signals are constant STUBs.
*           - Maps the LWR output stage onto ILCU IoHwAb.
*           - Replaces NvM/Dem/NM/timer services that ILCU does not have.
*           Every STUB is listed in PORT_CHANGES.md.
*/
/******************************************************************************/

/* ILCU headers first, so ILCU definitions win over the adapter's guarded ones */
#include "IoHwAb.h"
#include "IoHwAb_Internals.h"   /* CTRL_LWR PWM and LWR feedback have no public IoHwAb wrapper */
#include "ILCU_LevellingAdapter.h"
#include "AvacStat1Init.h"      /* DPE NvM defaults of AvacStat1 */
#include "CddDcm.h"             /* DPE NvM default of CddDcm */

/*============================================================================*/
/* Local definitions                                                          */
/*============================================================================*/
#define ILCU_LVLADP_MAIN_PERIOD_US      5000u   /* MainFunction period (ILCU BasicTask) */
#define ILCU_LVLADP_20MS_DIVIDER        4u      /* 4 x 5 ms = DPE 20 ms slot */
#define ILCU_LVLADP_DEM_EVENT_MAX       32u     /* above highest event id used (29) */
#define ILCU_LVLADP_NM_NORMAL_MODE      ((NM_ModeType)0x01u)   /* any value != LIMP_HOME_MODE */

/*============================================================================*/
/* NvM RAM blocks (STUB: never persisted)                                     */
/*============================================================================*/
tisNvmDeltaPwmPara   NvmBlockDeltaPwmPara;
tisStatAvacPrj1Para  NvmBlockStatAvacPrj1Para;
tisStatAvac1Para     NvmBlockStatAvac1Para;
tisStatAvacOp1Data   NvmBlockStatAvacOp1Data;
tDcMotorDataStruct   NvmBlockDcMotorData;

/*============================================================================*/
/* Local data                                                                 */
/*============================================================================*/
/* STUB coding block; standstill thresholds are patched in Init (see there) */
static tNvmPara_CodingArea ILCU_LvlAdp_CodingArea = { NVMPARA_AVACSTPBLOCK_INIT };

/* Chain-internal ports. Initial values = "no data yet". */
static tPositionOut                 ILCU_LvlAdp_AvacStat1Out    = { { { 0, 0, 0u } }, (uint8)SIG_INIT };
static tsRte_CtrlDcmTarget          ILCU_LvlAdp_DcmTarget       = { { 0, TRUE } };
static tsRte_DcmStatusError         ILCU_LvlAdp_DcmError        = { FALSE, FALSE };
static tsRte_CtrlDcmStatusParams    ILCU_LvlAdp_CtrlDcmStatus;  /* debug visible: ASL mode/phase */
static tDcmStateMsg                 ILCU_LvlAdp_DcmState;
static tDcmPosMsg                   ILCU_LvlAdp_DcmPos;

/* DPE CAN/UDS ports without a peer in ILCU (loop-back buffers) */
static tsRte_LevellingTgtPos        ILCU_LvlAdp_MasterCommand   = { eSigneConsigneSiteD_Negativ, eCmdRefSiteD_NoReferencing, { 0u }, SIG_SNA };
static tsRte_Hs6_Diag_Drvled_L_457  ILCU_LvlAdp_DrvLedDiag      = { eDiagLvl_Ok };
static tsRte_Hs6_Diag_Drvled_R_477  ILCU_LvlAdp_DrvLedDiagR     = { eDiagLvl_Ok };
static tsRte_DcMotorRoutineControl  ILCU_LvlAdp_RoutineControl  =
{
  eDcmControl_Unknown, eDcmBothActuators, eDcmStop, FALSE, FALSE, eDcmDID_Invalid, 0u, 0u
};

static uint8   ILCU_LvlAdp_DemStatus[ILCU_LVLADP_DEM_EVENT_MAX];  /* debug visible */
static TIMER   ILCU_LvlAdp_TimeUs;
static uint8   ILCU_LvlAdp_TickCnt;
static sint16  ILCU_LvlAdp_LastPitch;

/*============================================================================*/
/* ILCU-facing API                                                            */
/*============================================================================*/
void ILCU_LevellingAdapter_Init(void)
{
  /* DPE NvM defaults = what DPE NvM loads when no valid NV data exists */
  NvmBlockStatAvacPrj1Para = NvmInit_StatAvacPrj1ParaDefault;
  NvmBlockStatAvac1Para    = NvmInit_StatAvac1ParaDefault;
  NvmBlockStatAvacOp1Data  = NvmInit_StatAvacOp1DataDefault;
  NvmBlockDcMotorData      = NvmInit_ParaDcMotorDataDefault;

  /* STUB: Pitch/Diag-owned block. 0xFF = zero-level programming done, which
   * CtrlDcm requires (TrainingState) to enter Customer mode. eASL_Present is
   * set by AvacStat1_Init from coding. */
  NvmBlockDeltaPwmPara.ucZeroLevProg     = 0xFFu;
  NvmBlockDeltaPwmPara.snVehicleAttitude = 0;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input    = eInput_HLS;
  NvmBlockDeltaPwmPara.eASL_Present      = eASL_Absent;

  /* STUB coding: DPE NVMPARA_AVACSTP_DCMOTORDATA_INIT, except the standstill
   * speed thresholds. They are 0 there, which keeps AvacStat1 in
   * Below_Min_Speed at speed 0 (no levelling). 2/5 km/h are the production
   * values documented in AvacStat1Data.h. */
  ILCU_LvlAdp_CodingArea.AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED      = 2u;
  ILCU_LvlAdp_CodingArea.AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED = 5u;

  ILCU_LvlAdp_TimeUs  = 0u;
  ILCU_LvlAdp_TickCnt = 0u;

  /* DPE init order (Rte_Cfg.c): AvacStat1 sets eASL_Present used by CtrlDcm */
  riAvacStat1_Init();
  riCddDcm_Init();
  riCtrlDcm_Init();
}

void ILCU_LevellingAdapter_MainFunction(void)
{
  ILCU_LvlAdp_TimeUs += ILCU_LVLADP_MAIN_PERIOD_US;

  ILCU_LvlAdp_TickCnt++;
  if (ILCU_LvlAdp_TickCnt >= ILCU_LVLADP_20MS_DIVIDER)
  {
    ILCU_LvlAdp_TickCnt = 0u;
    rpAvacStat1_Cycle0();
    rpCtrlDcm_Cycle();
  }

  rpCddDcm_Cycle0();
}

#ifndef ILCU_LVLADP_EXTERNAL_PITCH_SOURCE
Std_ReturnType ILCU_LevellingAdapter_GetPitchAngle(sint16* Pitch_0p1mrad)
{
  /* STUB: fixed angle until the IMU module provides the pitch */
  *Pitch_0p1mrad = (sint16)ILCU_LVLADP_STUB_PITCH_0P1MRAD;
  return E_OK;
}
#endif

/*============================================================================*/
/* Platform services ILCU does not provide                                    */
/*============================================================================*/
TIMER TimerGetTick(void)
{
  return ILCU_LvlAdp_TimeUs;
}

TIMER TimerGetTimeSince(TIMER Start)
{
  /* unsigned subtraction is wrap-safe */
  return (TIMER)(ILCU_LvlAdp_TimeUs - Start);
}

NM_ErrorCodeType NM_GetMode(NM_ModeType* p_NMMode)
{
  /* STUB: no network management in ILCU, never limp-home */
  *p_NMMode = ILCU_LVLADP_NM_NORMAL_MODE;
  return 0u;
}

void Rte_Call_DemPrj_ReportErrorStatus(uint16 EventId, uint8 EventStatus)
{
  /* STUB: no Dem in ILCU. Like the DPE macro, event id 0 is ignored. */
  if ((EventId > 0u) && (EventId < ILCU_LVLADP_DEM_EVENT_MAX))
  {
    ILCU_LvlAdp_DemStatus[EventId] = EventStatus;
  }
}

Std_ReturnType ILCU_LvlAdp_NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr)
{
  /* STUB: RAM blocks only, nothing is persisted */
  (void)BlockId;
  (void)NvM_SrcPtr;
  return E_OK;
}

/*============================================================================*/
/* LWR output stage -> ILCU IoHwAb                                            */
/*============================================================================*/
void IoHwAb_User_SetDio_EN_DC(uint8 ucSignal)
{
  (void)IoHwAb_DiscreteEN_LWR_Write((ucSignal != 0u) ? IOHWAB_LEVEL_HIGH : IOHWAB_LEVEL_LOW);
}

void IoHwAbUser_GetAdc_VoltDC_OUT1(uint16* pio_signal)
{
  IoHwAb_ConvertedValueType Value_mV = 0u;

  /* LWR_DC feedback, ADC1 ch0 (PA15). 0 on error, as DPE expects. */
  if (IoHwAb_AnalogReadConverted(IOHWAB_CHID_ADIN_3, &Value_mV) != E_OK)
  {
    Value_mV = 0u;
  }
  *pio_signal = (Value_mV > 0xFFFFu) ? 0xFFFFu : (uint16)Value_mV;
}

void ILCU_LvlAdp_LwrPwmSetDuty(uint16 DutyCycle)
{
  /* AUTOSAR 0x8000 = 100 % -> IoHwAb per mille. Rounding makes this the exact
   * inverse of CddDcmHal's (pm * 0x8000) / 1000 for pm = 0..1000. */
  uint32 Duty_pm = (((uint32)DutyCycle * 1000u) + 0x4000u) / 0x8000u;

  (void)IoHwAb_TimingSetDutyCycle(IOHWAB_CHID_CTRL_LWR, (IoHwAb_DutyCycleType)Duty_pm);
}

void ILCU_LvlAdp_LwrPwmStart(void)
{
  /* Nothing to do: with AUTOSAR Pwm the next SetDutyCycle re-activates a
   * channel that was set to idle. */
}

void ILCU_LvlAdp_LwrPwmToIdle(void)
{
  /* DPE clamped the channel low; ILCU idle state of CTRL_LWR is low */
  (void)IoHwAb_TimingStopActuation(IOHWAB_CHID_CTRL_LWR);
}

Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1)
{
  IoHwAb_VoltageType Vbat_mV = 0u;
  Std_ReturnType     RetVal  = IoHwAb_VoltageKL30_Read(&Vbat_mV);

  *ppara1 = (RetVal == E_OK) ? (tiu32Voltage_mV)Vbat_mV : 0u;
  return RetVal;
}

/*============================================================================*/
/* RTE: AvacStat1                                                             */
/*============================================================================*/
Std_ReturnType Rte_Read_CodM_Pitch_Para(tsRteCodingParameters* ppara1)
{
  ppara1->psCodingParameters_Blocks = &ILCU_LvlAdp_CodingArea;
  ppara1->eCodingState              = eParaFct0_CodingDataValid;
  return E_OK;
}

Std_ReturnType Rte_Read_Pitch_Angle(tPitch0* ppara1)
{
  sint16 Angle = 0;

  if (ILCU_LevellingAdapter_GetPitchAngle(&Angle) == E_OK)
  {
    ILCU_LvlAdp_LastPitch = Angle;
    ppara1->eSigQty = SIG_VALID;
  }
  else
  {
    ppara1->eSigQty = SIG_INVALID;
  }
  ppara1->nAngle     = ILCU_LvlAdp_LastPitch;
  ppara1->nHeightErr = 0;
  return E_OK;
}

Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1)
{
  /* STUB: no vehicle speed in ILCU -> standstill */
  ppara1->eVehicleSpeed.unVehicleSpeed = 0u;
  ppara1->eVehicleSpeedDispo           = eVvhIndisp_SpeedInfoAvailable;
  ppara1->eSigQty                      = SIG_VALID;
  return E_OK;
}

Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1)
{
  /* STUB: no vehicle dynamics in ILCU */
  ppara1->ePedalAcceleration.ucPedalAcceleration = 0u;
  ppara1->eSigQty                                = SIG_VALID;
  return E_OK;
}

Std_ReturnType Rte_Write_ppsAvacStat1Out_Port(const tPositionOut* ppara1)
{
  ILCU_LvlAdp_AvacStat1Out = *ppara1;
  return E_OK;
}

/*============================================================================*/
/* RTE: CtrlDcm                                                               */
/*============================================================================*/
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  /* STUB: single ECU = DPE left/master side */
  *ppara1 = eMountedLeft;
  return E_OK;
}

Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1)
{
  /* STUB: ignition on, powertrain active */
  ppara1->eVESMainState         = VESState_Ignition;
  ppara1->eElectricNetworkState = eTA_NOMINAL;
  ppara1->eSigQty               = SIG_VALID;
  return E_OK;
}

Std_ReturnType Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1)
{
  /* STUB: customer vehicle mode -> CtrlDcm Customer/Available */
  ppara1->eEtatMar    = eEtatMar_Forward;
  ppara1->eVehicleCfg = eModeConfigVehicle_Client;
  ppara1->eSigQty     = SIG_VALID;
  return E_OK;
}

Std_ReturnType Rte_Read_ppsAvacStat1Out_Port(tPositionOut* ppara1)
{
  *ppara1 = ILCU_LvlAdp_AvacStat1Out;
  return E_OK;
}

Std_ReturnType Rte_Read_CddDcm_ErrorStatus(tsRte_DcmStatusError* ppara1)
{
  *ppara1 = ILCU_LvlAdp_DcmError;
  return E_OK;
}

Std_ReturnType Rte_Read_Pitch_PlausState(teRte_HlsSensorState* ppara1)
{
  /* STUB: DPE Pitch height-sensor plausibility has no ILCU equivalent yet */
  *ppara1 = eNO_FAILURE;
  return E_OK;
}

Std_ReturnType Rte_Read_SigPrep_LevellingTgtPos(tsRte_LevellingTgtPos* ppara1)
{
  /* STUB: right-side (slave) input; unreachable with the left mounting side */
  ppara1->eRCmdSignLvl              = eSigneConsigneSiteD_Positive;
  ppara1->eRCmdRefLvl               = eCmdRefSiteD_NoReferencing;
  ppara1->eRCmdPosLvl.unRCmdPosLvl  = 0u;
  ppara1->eSigQty                   = SIG_VALID;
  return E_OK;
}

Std_ReturnType Rte_Read_CtrlDcm_MasterCommand(tsRte_LevellingTgtPos* ppara1)
{
  *ppara1 = ILCU_LvlAdp_MasterCommand;
  return E_OK;
}

Std_ReturnType Rte_Write_CtrlDcm_MasterCommand(const tsRte_LevellingTgtPos* ppara1)
{
  ILCU_LvlAdp_MasterCommand = *ppara1;
  return E_OK;
}

Std_ReturnType Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1)
{
  *ppara1 = ILCU_LvlAdp_DrvLedDiag;
  return E_OK;
}

Std_ReturnType Rte_Write_DrvLedDiag(const tsRte_Hs6_Diag_Drvled_L_457* ppara1)
{
  ILCU_LvlAdp_DrvLedDiag = *ppara1;
  return E_OK;
}

Std_ReturnType Rte_Read_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1)
{
  *ppara1 = ILCU_LvlAdp_DrvLedDiagR;
  return E_OK;
}

Std_ReturnType Rte_Write_DrvLedDiagR(const tsRte_Hs6_Diag_Drvled_R_477* ppara1)
{
  ILCU_LvlAdp_DrvLedDiagR = *ppara1;
  return E_OK;
}

Std_ReturnType Rte_Read_SigPrep_DcmDiagStatusR(tsRte_DcmDiagStatusR* ppara1)
{
  /* STUB: no right-side ECU; VALID keeps CtrlDcm out of the functional fault */
  ppara1->eLevellingAdjustFaultR = eDiagLvl_Ok;
  ppara1->eSigQty                = SIG_VALID;
  return E_OK;
}

Std_ReturnType Rte_Write_ppCtrlDcmTarget0_DcmTargetValues(const tsRte_CtrlDcmTarget* ppara1)
{
  ILCU_LvlAdp_DcmTarget = *ppara1;
  return E_OK;
}

Std_ReturnType Rte_Write_CtrlDcm_StatusParameters_Port(const tsRte_CtrlDcmStatusParams* ppara1)
{
  ILCU_LvlAdp_CtrlDcmStatus = *ppara1;
  return E_OK;
}

Std_ReturnType Rte_Read_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1)
{
  *ppara1 = ILCU_LvlAdp_RoutineControl;
  return E_OK;
}

Std_ReturnType Rte_Write_Dcm_RoutineControl(const tsRte_DcMotorRoutineControl* ppara1)
{
  ILCU_LvlAdp_RoutineControl = *ppara1;
  return E_OK;
}

/*============================================================================*/
/* RTE: CddDcm                                                                */
/*============================================================================*/
Std_ReturnType Rte_Read_DcmState0_Port(tDcmStateMsg* ppara1)
{
  *ppara1 = ILCU_LvlAdp_DcmState;
  return E_OK;
}

Std_ReturnType Rte_Write_DcmState0_Port(const tDcmStateMsg* ppara1)
{
  ILCU_LvlAdp_DcmState = *ppara1;
  return E_OK;
}

Std_ReturnType Rte_Read_DcmPos0_Port(tDcmPosMsg* ppara1)
{
  *ppara1 = ILCU_LvlAdp_DcmPos;
  return E_OK;
}

Std_ReturnType Rte_Write_DcmPos0_Port(const tDcmPosMsg* ppara1)
{
  ILCU_LvlAdp_DcmPos = *ppara1;
  return E_OK;
}

Std_ReturnType Rte_Read_ppCtrlDcmTarget0_DcmTargetValues(tsRte_CtrlDcmTarget* ppara1)
{
  *ppara1 = ILCU_LvlAdp_DcmTarget;
  return E_OK;
}

Std_ReturnType Rte_Write_CddDcm_ErrorStatus(const tsRte_DcmStatusError* ppara1)
{
  ILCU_LvlAdp_DcmError = *ppara1;
  return E_OK;
}
