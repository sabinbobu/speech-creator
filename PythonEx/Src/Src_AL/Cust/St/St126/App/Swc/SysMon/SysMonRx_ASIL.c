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
/// \file   SysMonRx_ASIL.c
///
/// \brief  SysMon Emergency Operation Mode
///
/// \descr  All cases of the Emergency Operation Mode shall be treated here
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <SysMonRx_Callbacks.h>
#include <SysMonCheck.h>
#include <SysMonCheck_Data.h>
#include <SysMonRx_ASIL.h>
#include <SysMon_Types.h>
#include <SysMonRx.h>


//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

 //-----------------------------------------------------------------------------
 // variables
 //-----------------------------------------------------------------------------
//-- Emergency operation mode for Low Beam
STATIC_AL boolean SysMonRx_ASIL_boEmergencyOperation_FinalLowBeamStatus = FALSE;
STATIC_AL boolean SysMonRx_ASIL_boDiagLowBeamStatus                     = FALSE;

STATIC_AL tSysMonRx_Signal_Low_Beam        SysMonRx_ASIL_sSignalLowBeam       = { 0u, SysMon_LowBeam_SNA_State };
STATIC_AL tSysMonRx_Signal_Life_Phase      SysMonRx_ASIL_sSignalLifePhase     = { SysMon_LifePhase_Invalid_State, SysMon_LifePhase_SNA_State };
STATIC_AL tSysMonRx_Signal_Speed           SysMonRx_ASIL_sSignalSpeed         = { SysMon_Speed_SNA_State };
STATIC_AL tSysMonRx_Signal_VES_Main_State  SysMonRx_ASIL_sSignalVESMainState  = { SysMon_VESMainState_SNA_State };
STATIC_AL tSysMonRx_Signal_Turn_Indicator  SysMonRx_ASIL_sSignalTurnIndicator = { SYSMON_TURNINDICATOR_OFF, SysMon_TurnIndicator_SNA_State };

STATIC_AL tSysMonLbEmergencyOperationData SysMonRx_ASIL_EmergencyOperationData_LowBeam = {
  SysMon_LowBeam_SNA_State, SysMon_LifePhase_SNA_State, SysMon_Speed_SNA_State, //-- states
  SYSMON_LOWBEAM_OFF,            // last valid low beam request
  FALSE, FALSE, FALSE, FALSE,    //-- analysis do's for LowBeam
  FALSE };                       //-- Diagnosis of LowBeam

STATIC_AL boolean  SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation = FALSE;
STATIC_AL boolean  SysMonRx_ASIL_boEmergencyOperationLowBeam            = FALSE;
STATIC_AL boolean  SysMonRx_ASIL_boEmergencyOperationTurnIndicator      = FALSE;


//-- Emergency operation mode for Turn Indicator
STATIC_AL boolean SysMonRx_ASIL_boEmergencyOperation_FinalTurnIndicatorStatus = FALSE;
STATIC_AL boolean SysMonRx_ASIL_boDiagTurnIndicatorStatus                     = FALSE;
STATIC_AL uint32  SysMonRx_ASIL_ulTiScrlTime                                  = 0u;

STATIC_AL tSysMonTiEmergencyOperationData SysMonRx_ASIL_EmergencyOperationData_TurnIndicator = {
  SysMon_TurnIndicator_SNA_State, SysMon_LifePhase_SNA_State, SysMon_VESMainState_SNA_State, //-- states
  SYSMON_TURNINDICATOR_OFF,      // last valid turn indicator request
  FALSE, FALSE,                  //-- analysis do's for TurnIndicator
  FALSE};                        //-- Diagnosis of TurnIndicator

// Timer used to set the Invalid/Valid state for LowBeam
STATIC_AL TIMER SysMonRx_ASIL_ulInvalid_LowBeam_us = 0u;
// Timer used to set the Invalid/Valid state for LifePhase for Low Beam
STATIC_AL TIMER SysMonRx_ASIL_ulInvalid_LB_LifePhase_us = 0u;
// Timer used to set the Invalid/Valid state for LifePhase for Turn Indicator
STATIC_AL TIMER SysMonRx_ASIL_ulInvalid_TI_LifePhase_us = 0u;
// Timer used to set the Invalid/Valid state for Speed
STATIC_AL TIMER SysMonRx_ASIL_ulInvalid_Speed_us = 0u;
// Timer used to set the Invalid/Valid state for VESMainState
STATIC_AL TIMER SysMonRx_ASIL_ulInvalid_VESMainState_us = 0u;
// Timer used to set the Invalid/Valid state for TurnIndicator
STATIC_AL TIMER SysMonRx_ASIL_ulInvalid_TurnIndicator_us = 0u;

//-----------------------------------------------------------------------------
// funtion prototypes
//-----------------------------------------------------------------------------
// Interfaces for Low Beam Emergency Operation Mode
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Cycle                  (void);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Refresh                (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_CheckDataAndCases      (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_HandleLowBeam                  (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_HandleLowBeamDiag              (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Valid                  (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_OFF     (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_ON      (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_OFF           (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_ON            (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_OFF           (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_ON            (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_OFF   (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_ON    (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_OFF           (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_ON            (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_OFF          (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_ON           (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_OFF (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_ON  (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_OFF          (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_ON           (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_OFF          (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_ON           (tSysMonLbEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_ActivateLowBeam                (void);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_DeactivateLowBeam              (void);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_FollowLowBeam                  (void);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_SetDiagLowBeam                 (void);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_ClearDiagLowBeam               (void);

// LowBeam State Interfaces
STATIC_AL void                    SysMonRx_ASIL_Compute_LowBeamState  (void);
STATIC_AL void                    SysMonRx_ASIL_SetLowBeamValue       (uint8 ucLowBeamCmd);
STATIC_AL void                    SysMonRx_ASIL_SetLowBeamState       (SysMon_EnumLowBeamState State);

// Life Phase State Interfaces for Low Beam
STATIC_AL void                      SysMonRx_ASIL_Compute_LB_PhaseVieState(void);
STATIC_AL void                      SysMonRx_ASIL_SetLbLifePhaseState       (SysMon_EnumLifePhaseState State);
STATIC_AL SysMon_EnumLifePhaseState SysMonRx_ASIL_GetLbLifePhaseState       (void);

// VESMainState State Interfaces
STATIC_AL void                    SysMonRx_ASIL_Compute_VESMainState(void);
STATIC_AL void                    SysMonRx_ASIL_SetVESMainState(SysMon_EnumVESMainState State);
STATIC_AL SysMon_EnumVESMainState SysMonRx_ASIL_GetVESMainState(void);

// Speed State Interfaces
STATIC_AL void                    SysMonRx_ASIL_Compute_SpeedState(void);
STATIC_AL void                    SysMonRx_ASIL_SetSpeedState(SysMon_EnumSpeedState State);

// TurnIndicator State Interfaces
STATIC_AL void                          SysMonRx_ASIL_Compute_TurnIndicatorState(void);
STATIC_AL void                          SysMonRx_ASIL_SetTurnIndicatorValue(uint8 ucTurnIndicatorCmd);
STATIC_AL void                          SysMonRx_ASIL_SetTurnIndicatorState(SysMon_EnumTurnIndicatorState State);

// Life Phase State Interfaces for Turn Indicator
STATIC_AL void                      SysMonRx_ASIL_Compute_TI_PhaseVieState(void);
STATIC_AL void                      SysMonRx_ASIL_SetTiLifePhaseState(SysMon_EnumLifePhaseState State);
STATIC_AL SysMon_EnumLifePhaseState SysMonRx_ASIL_GetTiLifePhaseState(void);

// Interfaces for Turn Indicator Emergency Operation Mode
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Cycle                      (void);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Refresh                    (tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_CheckDataAndCases          (tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicator                      (tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicatorDiag                  (tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Valid                      (tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_ON  (tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_OFF (tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_ON (tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_OFF(tSysMonTiEmergencyOperationData* CONST_AL pEOdata);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_DeactivateTurnIndicator                  (void);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_FollowTurnIndicator                      (void);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_SetDiagTurnIndicator                     (void);
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_ClearDiagTurnIndicator                   (void);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
STATIC_AL boolean SysMonRx_ASIL_Check_TI_Scrolling                                       (void);
#endif // CFG_VARIANT_FULL


//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_InitLowBeamAndTurnIndicatorInterfaces
///
/// \descr  Puplic interface to get Initialize the Low Beam and Turn Indicator Interfaces
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_ASIL_InitLowBeamAndTurnIndicatorInterfaces(void)
{
  // Initialize Low Beam Interface
  SysMonRx_ASIL_EmergencyOperationData_LowBeam.eLowBeamState             = SysMon_LowBeam_SNA_State;
  SysMonRx_ASIL_EmergencyOperationData_LowBeam.eLifePhaseState           = SysMon_LifePhase_SNA_State;
  SysMonRx_ASIL_EmergencyOperationData_LowBeam.eSpeedState               = SysMon_Speed_SNA_State;
  SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest = SYSMON_LOWBEAM_OFF;

  // Initialize Turn Indicator Interface
  SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.eTurnIndicatorState = SysMon_TurnIndicator_SNA_State;
  SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.eLifePhaseState = SysMon_LifePhase_SNA_State;
  SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.eVESMainState = SysMon_VESMainState_SNA_State;
  SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.ucLastTurnIndicatorValidRequest = SYSMON_TURNINDICATOR_OFF;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation
///
/// \descr  - Gets current states and relevant signal data for LowBeam and TurnIndicator
///         - Perform analysis of current data of LowBeam and TurnIndicator
///           and handles the reques sent to FctR for Low Beam and Turn Indicator
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_ASIL_EmergencyOperation(void)
{
  // Low Beam processing
  SysMonRx_ASIL_EmergencyOperation_LowBeam_Cycle();

  // Turn Indicator processing
  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Cycle();
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Cycle
///
/// \descr  Cycle function for checking Emergency Operation mode for Low Beam
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Cycle(void)
{
  SysMonRx_ASIL_EmergencyOperation_LowBeam_Refresh(&SysMonRx_ASIL_EmergencyOperationData_LowBeam);
  SysMonRx_ASIL_EmergencyOperation_LowBeam_CheckDataAndCases(&SysMonRx_ASIL_EmergencyOperationData_LowBeam);
  SysMonRx_ASIL_EmergencyOperation_HandleLowBeam(&SysMonRx_ASIL_EmergencyOperationData_LowBeam);
  SysMonRx_ASIL_EmergencyOperation_HandleLowBeamDiag(&SysMonRx_ASIL_EmergencyOperationData_LowBeam);
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Refresh
///
/// \descr  Helper to initialize data before investigation
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Refresh(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  // Compute Low Beam State
  SysMonRx_ASIL_Compute_LowBeamState();
  // Compute Life Phase State for Low Beam
  SysMonRx_ASIL_Compute_LB_PhaseVieState();
  // Compute Speed State
  SysMonRx_ASIL_Compute_SpeedState();

  // Get states
  pEOdata->eLowBeamState             = SysMonRx_ASIL_GetLowBeamState();
  pEOdata->eLifePhaseState           = SysMonRx_ASIL_GetLbLifePhaseState();
  pEOdata->eSpeedState               = SysMonRx_ASIL_GetSpeedState();

  SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest = SysMonRx_ASIL_GetLowBeamValue();

  // Will be reset each call and will be set in SysMonRx_ASIL_EmergencyOperation_LowBeam_CheckDataAndCases when
  // condition becomes true
  pEOdata->boDoActivateLowBeam       = FALSE;
  pEOdata->boDoDeactivateLowBeam     = FALSE;
  pEOdata->boDoNotDeactivateLowBeam  = FALSE;
  pEOdata->boDoNotActivateLowBeam    = FALSE;

  pEOdata->boDiagLowBeam             = FALSE;

  SysMonRx_ASIL_boEmergencyOperation_FinalLowBeamStatus = FALSE;
  SysMonRx_ASIL_boEmergencyOperationLowBeam             = FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_CheckDataAndCases
///
/// \descr  Analyse states and data
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_CheckDataAndCases(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  struct SysMon_ASIL_sEmergencyOperationLowBeamFctArg pfa[] = {
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Valid,                   pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_OFF,      pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_ON,       pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_OFF,            pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_ON,             pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_OFF,            pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_ON,             pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_OFF,    pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_ON,     pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_OFF,            pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_ON,             pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_OFF,           pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_ON,            pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_OFF,  pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_ON,   pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_OFF,           pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_ON,            pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_OFF,           pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_ON,            pEOdata }
  };

  CONST_AL uint32 COUNT = sizeof(pfa) / sizeof(pfa[0]);
  
  for (uint8 i = 0U; i < COUNT; i++)
  {
    (*(pfa[i].func))(pfa[i].arg);
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Valid
///
/// \descr  Case when all states are Valid.
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Valid(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SysMon_LowBeam_Invalid_State != pEOdata->eLowBeamState)
  {
    SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation = FALSE;
    if (SysMon_Speed_Invalid_State != pEOdata->eSpeedState)
    {
      if (SysMon_LifePhase_Invalid_State != pEOdata->eLifePhaseState)
      {
        // Nothing to do
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_OFF
///
/// \descr  Cases 1, 3, 4 and 5 when Low Beam was Off.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_0_State, and
/// -       - the application is in state LifePhase_Not_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_OFF == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_0_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Not_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotActivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam          = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_ON
///
/// \descr  Cases 1, 3, 4 and 5 when Low Beam was On.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_0_State, and
/// -       - the application is in state LifePhase_Not_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case1_3_4_5_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_ON == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_0_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Not_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoDeactivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam         = TRUE;
        }
      }
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_OFF
///
/// \descr  Case 2 when Low Beam was Off.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_0_State, and
/// -       - the application is in state LifePhase_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_OFF == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_0_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotActivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam          = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_ON
///
/// \descr  Case 2 when Low Beam was On.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_0_State, and
/// -       - the application is in state LifePhase_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case2_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_ON == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_0_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotDeactivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam            = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_OFF
///
/// \descr  Case 6 when Low Beam was Off.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_0_State, and
/// -       - the application is in state LifePhase_Invalid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_OFF == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_0_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Invalid_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotActivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam          = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_ON
///
/// \descr  Case 6 when Low Beam was On.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_0_State, and
/// -       - the application is in state LifePhase_Invalid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case6_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_ON == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_0_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Invalid_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoDeactivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam         = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_OFF
///
/// \descr  Cases 7, 9, 10 and 11 when Low Beam was Off.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Drive_State, and
/// -       - the application is in state LifePhase_Not_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_OFF == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Drive_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Not_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoActivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam       = TRUE;
          SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_ON
///
/// \descr  Cases 7, 9, 10 and 11 when Low Beam was On.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Drive_State, and
/// -       - the application is in state LifePhase_Not_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case7_9_10_11_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_ON == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Drive_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Not_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotDeactivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam            = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_OFF
///
/// \descr  Case 8 when Low Beam was Off.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Drive_State, and
/// -       - the application is in state LifePhase_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_OFF == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Drive_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoActivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam       = TRUE;
          SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_ON
///
/// \descr  Case 8 when Low Beam was On.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Drive_State, and
/// -       - the application is in state LifePhase_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case8_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_ON == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Drive_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotDeactivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam            = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_OFF
///
/// \descr  Case 12 when Low Beam was Off.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Drive_State, and
/// -       - the application is in state LifePhase_Invalid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_OFF == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Drive_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Invalid_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoActivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam       = TRUE;
          SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_ON
///
/// \descr  Case 12 when Low Beam was On.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Drive_State, and
/// -       - the application is in state LifePhase_Invalid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case12_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_ON == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Drive_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Invalid_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotDeactivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam            = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_OFF
///
/// \descr  Cases 13, 15, 16 and 17 when Low Beam was Off.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Invalid_State, and
/// -       - the application is in state LifePhase_Not_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_OFF == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Invalid_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Not_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoActivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam       = TRUE;
          SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_ON
///
/// \descr  Cases 13, 15, 16 and 17 when Low Beam was On.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Invalid_State, and
/// -       - the application is in state LifePhase_Not_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case13_15_16_17_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_ON == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Invalid_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Not_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotDeactivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam            = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_OFF
///
/// \descr  Cases 14 when Low Beam was Off.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Invalid_State, and
/// -       - the application is in state LifePhase_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_OFF == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Invalid_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoActivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam       = TRUE;
          SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_ON
///
/// \descr  Cases 14 when Low Beam was On.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Invalid_State, and
/// -       - the application is in state LifePhase_Normal_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case14_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_ON == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Invalid_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Normal_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotDeactivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam            = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_OFF
///
/// \descr  Cases 18 when Low Beam was Off.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Invalid_State, and
/// -       - the application is in state LifePhase_Invalid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_OFF(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_OFF == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Invalid_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Invalid_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoActivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam       = TRUE;
          SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_ON
///
/// \descr  Cases 14 when Low Beam was On.
///         - the application is in state LowBeam_Invalid_State, and
///         - the application is in state Speed_Invalid_State, and
/// -       - the application is in state LifePhase_Invalid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_LowBeam_Case18_LB_ON(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_LOWBEAM_ON == SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest)
  {
    if (SysMon_LowBeam_Invalid_State == pEOdata->eLowBeamState)
    {
      if (SysMon_Speed_Invalid_State == pEOdata->eSpeedState)
      {
        if (SysMon_LifePhase_Invalid_State == pEOdata->eLifePhaseState)
        {
          pEOdata->boDoNotDeactivateLowBeam = TRUE;
          pEOdata->boDiagLowBeam            = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_HandleLowBeam
///
/// \descr  Check the DTC related result of the data analysis of SysMonRx_ASIL_EmergencyOperation_CaseXX_LB_YY,
///         namely isDoActivateLowBeam, isDoDeActivateLowBeam, isDoNotDeActivateLowBeam
///         and isDoNotActivateLowBeam
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_HandleLowBeam(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  boolean boCrc32RomFailure = FALSE;

  // Get status of CRC32 check over ROM Coding Data
  boCrc32RomFailure = SysMonCheck_Data_Get_Crc32RomFailure();

  // Check if Low Beam needs to be activated by Emergency Operation Mode
  if (((FALSE != pEOdata->boDoActivateLowBeam) || (FALSE != SysMonRx_ASIL_boLowBeamActivatedbyEmergencyOperation)) && (FALSE == boCrc32RomFailure))
  {
    if (FALSE == pEOdata->boDoNotActivateLowBeam)
    {
      // Activate Low Beam due to Emergency Operation Mode
      SysMonRx_ASIL_EmergencyOperation_ActivateLowBeam();
    }
    else
    {
      // Nothing to do
    }
  }
  else
  {
    SysMonRx_ASIL_EmergencyOperation_FollowLowBeam();
  }

  // Check if Low Beam needs to be deactivated or kept off by Emergency Operation Mode
  if (((FALSE != pEOdata->boDoDeactivateLowBeam) || ((FALSE != pEOdata->boDoNotActivateLowBeam))) && (FALSE == boCrc32RomFailure))
  {
    if (FALSE == pEOdata->boDoNotDeactivateLowBeam)
    {
      // Deactivate Low Beam due to Emergency Operation Mode
      SysMonRx_ASIL_EmergencyOperation_DeactivateLowBeam();
    }
    else
    {
      // Nothing to do
    }
  }
  else
  {
    // Nothing to do
  }

  // Check if Low Beam needs to be kept ON by Emergency Operation Mode
  if ((FALSE != pEOdata->boDoNotDeactivateLowBeam) && (FALSE == boCrc32RomFailure))
  {
    // Keep Low Beam activated due to Emergency Operation Mode
    SysMonRx_ASIL_EmergencyOperation_ActivateLowBeam();
  }
  else
  {
    // Nothing to do
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_HandleLowBeamDiag
///
/// \descr  Check the Diagnostic state result of the data analysis of SysMonRx_ASIL_EmergencyOperation_CaseXX_LB_YY
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_HandleLowBeamDiag(tSysMonLbEmergencyOperationData* CONST_AL pEOdata)
{
  boolean boCodFail_DiagLb = FALSE;
  boolean boCrc32RomFailure = FALSE;

  // Get status of Coding Failure
  boCodFail_DiagLb = SysMonCheck_Get_CodingFailureDiagLowBeamStatus();

  // Get status of CRC32 check over ROM Coding Data
  boCrc32RomFailure = SysMonCheck_Data_Get_Crc32RomFailure();

  // Check if Low Beam Diagnosis shall be set to NOK based on Emergency Operation Mode or of coding issues
  if (((FALSE != pEOdata->boDiagLowBeam) || (FALSE != boCodFail_DiagLb)) && (FALSE == boCrc32RomFailure))
  {
    SysMonRx_ASIL_EmergencyOperation_SetDiagLowBeam();
  }
  else
  {
    SysMonRx_ASIL_EmergencyOperation_ClearDiagLowBeam();
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_SetDiagLowBeam
///
/// \descr  Set the LowBeam Diagnosis Status in context of Emergency Operation Mode (send request)
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_SetDiagLowBeam(void)
{
  SysMonRx_ASIL_boDiagLowBeamStatus = TRUE;
}




//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_ClearDiagLowBeam
///
/// \descr  Clear the LowBeam Diagnosis Status.
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_ClearDiagLowBeam(void)
{
  SysMonRx_ASIL_boDiagLowBeamStatus = FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Get_boDiagLowBeamStatus
///
/// \descr  Get SysMonRx_ASIL_boDiagLowBeamStatus in context of Emergency Operation Mode
///
/// \param  void
///
/// \return  boolean - Value of Diag Low Beam that will go to SysMonTx
//-----------------------------------------------------------------------------
boolean SysMonRx_ASIL_Get_boDiagLowBeamStatus(void)
{
  return SysMonRx_ASIL_boDiagLowBeamStatus;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_ActivateLowBeam
///
/// \descr  Activate LowBeam in context of Emergency Operation Mode (send request)
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_ActivateLowBeam(void)
{
  SysMonRx_ASIL_boEmergencyOperation_FinalLowBeamStatus = TRUE;
  SysMonRx_ASIL_boEmergencyOperationLowBeam             = TRUE;
  // Trigger CDDLED directly (Removed based on LDMO-3383)
  //SysMonCheck_TriggerCddLed_LowBeam(SYSMON_LOWBEAM_ON);
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_DeactivateLowBeam
///
/// \descr  Deactivate LowBeam in context of Emergency Operation Mode (send request)
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_DeactivateLowBeam(void)
{
  SysMonRx_ASIL_boEmergencyOperation_FinalLowBeamStatus = FALSE;
  SysMonRx_ASIL_boEmergencyOperationLowBeam             = TRUE;
  // Trigger CdLed directly (Removed based on LDMO-3383)
  // SysMonCheck_TriggerCddLed_LowBeam(SYSMON_LOWBEAM_OFF);
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam
///
/// \descr  Return LowBeam in context of Emergency Operation Mode (send request)
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam(void)
{
  return SysMonRx_ASIL_boEmergencyOperationLowBeam;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_FollowLowBeam
///
/// \descr  There is no problem on the Low Beam as a result of the Emergency Operation Mode analysis
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_FollowLowBeam(void)
{
  SysMonRx_ASIL_boEmergencyOperation_FinalLowBeamStatus = (SysMonRx_ASIL_EmergencyOperationData_LowBeam.ucLastLowBeamValidRequest != SYSMON_LOWBEAM_OFF) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Get_boEmergencyOperation_FinalLowBeamStatus
///
/// \descr  Get SysMonRx_ASIL_boEmergencyOperation_FinalLowBeamStatus in context of Emergency Operation Mode
///
/// \param  void
///
/// \return  SysMonRx_ASIL_boEmergencyOperation_FinalLowBeamStatus - Final value of Low Beam that will go to FctR
//-----------------------------------------------------------------------------
boolean SysMonRx_ASIL_Get_boEmergencyOperation_FinalLowBeamStatus(void)
{
  return SysMonRx_ASIL_boEmergencyOperation_FinalLowBeamStatus;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Cycle
///
/// \descr  Cycle function for checking Emergency Operation Mode for Turn Indicator
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Cycle(void)
{
  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Refresh(&SysMonRx_ASIL_EmergencyOperationData_TurnIndicator);
  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_CheckDataAndCases(&SysMonRx_ASIL_EmergencyOperationData_TurnIndicator);
  SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicator(&SysMonRx_ASIL_EmergencyOperationData_TurnIndicator);
  SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicatorDiag(&SysMonRx_ASIL_EmergencyOperationData_TurnIndicator);
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Refresh
///
/// \descr  Helper to initialize data before investigation
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Refresh(tSysMonTiEmergencyOperationData* CONST_AL pEOdata)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  STATIC_UT(boolean, boTiScrlCheck, TRUE);

  // Check if TI Scrolling is present only once at startup
  if (boTiScrlCheck != FALSE)
  {
    boTiScrlCheck = SysMonRx_ASIL_Check_TI_Scrolling();
  }
  else
  {
    // nothing to do, TI Scrolling has already been checked
  }
#endif // CFG_VARIANT_FULL

  // Compute Turn Indicator State
  SysMonRx_ASIL_Compute_TurnIndicatorState();
  // Compute Life Phase State
  SysMonRx_ASIL_Compute_TI_PhaseVieState();
  // Compute VES Main State
  SysMonRx_ASIL_Compute_VESMainState();

  // Get states from SysMonRx_Callbacks
  pEOdata->eTurnIndicatorState  = SysMonRx_ASIL_GetTurnIndicatorState();
  pEOdata->eLifePhaseState      = SysMonRx_ASIL_GetTiLifePhaseState();
  pEOdata->eVESMainState        = SysMonRx_ASIL_GetVESMainState();

  SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.ucLastTurnIndicatorValidRequest = SysMonRx_ASIL_GetTurnIndicatorValue();

  // Will be reset each call and will be set in SysMonRx_ASIL_EmergencyOperation_TurnIndicator_CheckDataAndCases when
  // condition becomes true
  pEOdata->boDoDeactivateTurnIndicator    = FALSE;
  pEOdata->boDoNotDeactivateTurnIndicator = FALSE;

  pEOdata->boDiagTurnIndicator            = FALSE;

  SysMonRx_ASIL_boEmergencyOperation_FinalTurnIndicatorStatus = FALSE;
  SysMonRx_ASIL_boEmergencyOperationTurnIndicator             = FALSE;
} // PRQA S 5324 1 // Software Architecture



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_CheckDataAndCases
///
/// \descr  Analyse states and data
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_CheckDataAndCases(tSysMonTiEmergencyOperationData* CONST_AL pEOdata)
{
  struct SysMon_ASIL_sEmergencyOperationTurnIndicatorFctArg pfa[] = {
  { SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Valid,                         pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_ON,     pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_OFF,    pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_ON,    pEOdata },
  { SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_OFF,   pEOdata }
  };

  CONST_AL uint32 COUNT = sizeof(pfa) / sizeof(pfa[0]);

  for (uint8 i = 0U; i < COUNT; i++)
  {
    (*(pfa[i].func))(pfa[i].arg);
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicator
///
/// \descr  Check the result of the data analysis of SysMonRx_ASIL_EmergencyOperation_CaseXX_LB_YY,
///         namely isDoActivateTurnIndicator, isDoDeActivateTurnIndicator, isDoNotDeActivateTurnIndicator
///         and isDoNotActivateTurnIndicator
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicator(tSysMonTiEmergencyOperationData* CONST_AL pEOdata)
{
  //-- Check wheter TurnIndicator shall be switched off for Notlauf
  if (TRUE == pEOdata->boDoDeactivateTurnIndicator)
  {
    if (FALSE == pEOdata->boDoNotDeactivateTurnIndicator)
    {
      SysMonRx_ASIL_EmergencyOperation_DeactivateTurnIndicator();
    }
    else
    {
      // Nothing to do
    }
  }
  else
  {
    // Follow the Turn Indicator received on CAN because there is not Emergency Operation
    SysMonRx_ASIL_EmergencyOperation_FollowTurnIndicator();
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicatorDiag
///
/// \descr  Check the Diagnostic state result of the data analysis of SysMonRx_ASIL_EmergencyOperation_CaseXX_TI_YY
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_HandleTurnIndicatorDiag(tSysMonTiEmergencyOperationData* CONST_AL pEOdata)
{
  boolean boCodFail_DiagTi = FALSE;

  boCodFail_DiagTi = SysMonCheck_Get_CodingFailureDiagTurnIndicatorStatus();

  // Check if Turn Indicator Diagnosis shall be set to NOK based on Emergency Operation Mode or of coding issues
  if ((FALSE != pEOdata->boDiagTurnIndicator) || (FALSE != boCodFail_DiagTi))
  {
    SysMonRx_ASIL_EmergencyOperation_SetDiagTurnIndicator();
  }
  else
  {
    SysMonRx_ASIL_EmergencyOperation_ClearDiagTurnIndicator();
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_SetDiagTurnIndicator
///
/// \descr  Set the TurnIndicator Diagnosis Status in context of Emergency Operation Mode (send request)
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_SetDiagTurnIndicator(void)
{
  SysMonRx_ASIL_boDiagTurnIndicatorStatus = TRUE;
}




//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_ClearDiagTurnIndicator
///
/// \descr  Clear the TurnIndicator Diagnosis Status.
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_ClearDiagTurnIndicator(void)
{
  SysMonRx_ASIL_boDiagTurnIndicatorStatus = FALSE;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Get_boDiagTurnIndicatorStatus
///
/// \descr  Get SysMonRx_ASIL_boDiagTurnIndicatorStatus in context of Emergency Operation Mode
///
/// \param  void
///
/// \return  boolean - Value of Diag Turn Indicator that will go to SysMonTx
//-----------------------------------------------------------------------------
boolean SysMonRx_ASIL_Get_boDiagTurnIndicatorStatus(void)
{
  return SysMonRx_ASIL_boDiagTurnIndicatorStatus;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_DeactivateTurnIndicator
///
/// \descr  Deactivate TurnIndicator in context of Emergency Operation Mode (send request)
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_DeactivateTurnIndicator(void)
{
  SysMonRx_ASIL_boEmergencyOperation_FinalTurnIndicatorStatus = FALSE;
  SysMonRx_ASIL_boEmergencyOperationTurnIndicator             = TRUE;
  // Trigger CddLed directly
  SysMonCheck_TriggerCddLed_TurnIndicator_Off();
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_FollowTurnIndicator
///
/// \descr  There is no problem on the Turn Indicator as a result of the Emergency Operation Mode analysis
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_FollowTurnIndicator(void)
{
  SysMonRx_ASIL_boEmergencyOperation_FinalTurnIndicatorStatus = (SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.ucLastTurnIndicatorValidRequest == SYSMON_TURNINDICATOR_ON) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Get_boEmergencyOperation_FinalTurnIndicatorStatus
///
/// \descr  Get SysMonRx_ASIL_boEmergencyOperation_FinalTurnIndicatorStatus in context of Emergency Operation Mode
///
/// \param  void
///
/// \return  SysMonRx_ASIL_boEmergencyOperation_FinalTurnIndicatorStatus - Final value of Turn Indicator that will go to FctR
//-----------------------------------------------------------------------------
boolean SysMonRx_ASIL_Get_boEmergencyOperation_FinalTurnIndicatorStatus(void)
{
  return SysMonRx_ASIL_boEmergencyOperation_FinalTurnIndicatorStatus;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Valid
///
/// \descr  Case when all states are Valid.
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Valid(tSysMonTiEmergencyOperationData* CONST_AL pEOdata)
{
  if (SysMon_TurnIndicator_Invalid_State != pEOdata->eTurnIndicatorState)
  {
    if (SysMon_LifePhase_Invalid_State != pEOdata->eLifePhaseState)
    {
      if (SysMon_VESMainState_Invalid_State != pEOdata->eVESMainState)
      {
        // Nothing to do
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_ON
///
/// \descr  Cases 1, 2, 3, 4, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 and 19  when Turn Indicator was On.
///         - the application is in state TurnIndicator_Invalid_State, and
/// -       - the application is in state LifePhase_Not_Normal_State, and
///         - the application is in state SysMon_VESMainState_Invalid_State OR SysMon_VESMainState_Valid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_ON(tSysMonTiEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_TURNINDICATOR_ON == SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.ucLastTurnIndicatorValidRequest)
  {
    if (SysMon_TurnIndicator_Invalid_State == pEOdata->eTurnIndicatorState)
    {
      if (SysMon_LifePhase_Not_Normal_State == pEOdata->eLifePhaseState)
      {
        //if (((SysMon_VESMainState_Invalid_State == pEOdata->eVESMainState) || 
        //    (SysMon_VESMainState_Valid_State == pEOdata->eVESMainState)))
        //{
          pEOdata->boDoDeactivateTurnIndicator = TRUE;
          pEOdata->boDiagTurnIndicator         = TRUE;
        //}
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_OFF
///
/// \descr  Cases 1, 2, 3, 4, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 and 19  when Turn Indicator was Off.
///         - the application is in state TurnIndicator_Invalid_State, and
/// -       - the application is in state LifePhase_Not_Normal_State, and
///         - the application is in state SysMon_VESMainState_Invalid_State OR SysMon_VESMainState_Valid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case1_2_3_4_9_to_20_TI_OFF(tSysMonTiEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_TURNINDICATOR_OFF == SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.ucLastTurnIndicatorValidRequest)
  {
    if (SysMon_TurnIndicator_Invalid_State == pEOdata->eTurnIndicatorState)
    {
      if (SysMon_LifePhase_Not_Normal_State == pEOdata->eLifePhaseState)
      {
        if (((SysMon_VESMainState_Invalid_State == pEOdata->eVESMainState) ||
            (SysMon_VESMainState_Valid_State == pEOdata->eVESMainState)))
        {
          // Nothing to do
          pEOdata->boDiagTurnIndicator = TRUE;
        }
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_ON
///
/// \descr  Cases 5, 6, 7, 8, 21, 22, 23 and 24 when Turn Indicator was On.
///         - the application is in state TurnIndicator_Invalid_State, and
/// -       - the application is in state LifePhase_Normal_State OR LifePhase_Invalid_State, and
///         - the application is in state SysMon_VESMainState_Invalid_State OR SysMon_VESMainState_Valid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_ON(tSysMonTiEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_TURNINDICATOR_ON == SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.ucLastTurnIndicatorValidRequest)
  {
    if (SysMon_TurnIndicator_Invalid_State == pEOdata->eTurnIndicatorState)
    {
      if ((SysMon_LifePhase_Normal_State == pEOdata->eLifePhaseState) ||
          (SysMon_LifePhase_Invalid_State == pEOdata->eLifePhaseState))
      {
        //if (((SysMon_VESMainState_Invalid_State == pEOdata->eVESMainState) ||
        //    (SysMon_VESMainState_Valid_State == pEOdata->eVESMainState)))
        //{
          pEOdata->boDoDeactivateTurnIndicator = TRUE;
          pEOdata->boDiagTurnIndicator         = TRUE;
        //}
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_OFF
///
/// \descr  Cases 5, 6, 7, 8, 21, 22, 23 and 24 when Turn Indicator was Off.
///         - the application is in state TurnIndicator_Invalid_State, and
/// -       - the application is in state LifePhase_Normal_State OR LifePhase_Invalid_State, and
///         - the application is in state SysMon_VESMainState_Invalid_State OR SysMon_VESMainState_Valid_State
///
/// \param  pEOdata - pointer to structure containing the Emergency Operation Mode data
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Case5_6_7_8_21_22_23_24_OFF(tSysMonTiEmergencyOperationData* CONST_AL pEOdata)
{
  if (SYSMON_TURNINDICATOR_OFF == SysMonRx_ASIL_EmergencyOperationData_TurnIndicator.ucLastTurnIndicatorValidRequest)
  {
    if (SysMon_TurnIndicator_Invalid_State == pEOdata->eTurnIndicatorState)
    {
      if ((SysMon_LifePhase_Normal_State == pEOdata->eLifePhaseState) ||
          (SysMon_LifePhase_Invalid_State == pEOdata->eLifePhaseState))
      {
        //if (((SysMon_VESMainState_Invalid_State == pEOdata->eVESMainState) ||
        //    (SysMon_VESMainState_Valid_State == pEOdata->eVESMainState)))
        //{
          pEOdata->boDiagTurnIndicator = TRUE;
        //}
      }
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Compute_LowBeamState
///
/// \descr  Compute the LowBeamState used in the Emergency Operation Mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_Compute_LowBeamState(void)
{
  teRte_SigQty    eSigQty          = SIG_SNA;
  uint8           ucLowBeamCmd     = 0u;

  STATIC_UT(boolean, boCrcFailure,        FALSE);
  STATIC_UT(boolean, boTimeoutFailure,    FALSE);
  STATIC_UT(boolean, boNoFailure,         FALSE);
  STATIC_UT(boolean, boSetLowBeamInvalid, FALSE);

  // Get Low Beam value and Signal Quality from SysMonRx_Callbacks
  SysMonRx_Callbacks_GetLowBeamSignal(&ucLowBeamCmd, &eSigQty);

  // Check for CRC, E2E Alive and Timeout errors
  switch (eSigQty)
  {
    case SIG_INVALID:
    case SIG_E2E_CRCERR:
    case SIG_E2E_ALIVEERR:
    case SIG_E2E_TIMEOUT:
      // Reset Flags for other errors
      boTimeoutFailure  = FALSE;
      boNoFailure   = FALSE;

      // First time appearance of CRC/Alive error
      if (boCrcFailure == FALSE)
      {
        // Get time stamp
        SysMonRx_ASIL_ulInvalid_LowBeam_us = TimerGetTick();
        // Set CRC Failure flag
        boCrcFailure = TRUE;
      }
      else
      {
        if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_LowBeam_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_LOWBEAM_CRC_ALIVE_ERROR_MS))
        {
          // Set the Low Beam Invalid flag
          boSetLowBeamInvalid = TRUE;
        }
        else
        {
          // nothing to do
        }
      }
      break;

    case SIG_TIMEOUT:
      // Reset Flags for other errors
      boCrcFailure = FALSE;
      boNoFailure      = FALSE;

      // First time appearance of Timeout error
      if (boTimeoutFailure == FALSE)
      {
        // Get time stamp
        SysMonRx_ASIL_ulInvalid_LowBeam_us = TimerGetTick();
        // Set Timeout Failure flag
        boTimeoutFailure = TRUE;
      }
      else
      {
        if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_LowBeam_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_LOWBEAM_TIMEOUT_ERROR_MS))
        {
          // Set the Low Beam Invalid flag
          boSetLowBeamInvalid = TRUE;
        }
        else
        {
          // nothing to do
        }
      }
      break;

    case SIG_VALID:
      // Reset Flags for other errors
      boTimeoutFailure = FALSE;
      boCrcFailure     = FALSE;

          // First time appearance of No Failure
      if (boNoFailure == FALSE)
      {
        // Get time stamp
        SysMonRx_ASIL_ulInvalid_LowBeam_us = TimerGetTick();
        // Set No Failure flag
        boNoFailure = TRUE;
      }
      else
      {
        if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_LowBeam_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_LOWBEAM_NO_ERROR_MS))
        {
          // Clear the Low Beam Invalid flag
          boSetLowBeamInvalid = FALSE;
        }
        else
        {
          // nothing to do
        }
      }
      break;

    default:
      break;
  }

  // Check Low Beam Invalid flag
  if (TRUE == boSetLowBeamInvalid)
  {
    // Set the LowBeamState to Invalid State
    SysMonRx_ASIL_SetLowBeamState(SysMon_LowBeam_Invalid_State);
  }
  else
  {
    // Set the Low Beam Value
    SysMonRx_ASIL_SetLowBeamValue(ucLowBeamCmd);
    // Set the LowBeamState to Valid State
    SysMonRx_ASIL_SetLowBeamState(SysMon_LowBeam_Valid_State);
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_SetLowBeamValue
///
/// \descr  Set the Low Beam value
///
/// \param  ucLowBeamCmd - Low Beam command received on CAN frame HS6_DAT_VSM_34E
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_SetLowBeamValue(uint8 ucLowBeamCmd)
{
  // Set the Low Beam value
  SysMonRx_ASIL_sSignalLowBeam.ucValue = ucLowBeamCmd;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_SetLowBeamState
///
/// \descr  Set the Low Beam State value
///
/// \param  State - Low Beam State that will be set
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_SetLowBeamState(SysMon_EnumLowBeamState State)
{
  // Set the Low Beam State
  SysMonRx_ASIL_sSignalLowBeam.eLowBeamState = State;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetLowBeamState
///
/// \descr  Puplic interface to get LowBeam state for Emergency Operation Mode
///
/// \param  void
///
/// \return SysMon_EnumLowBeamState - value of LowBeamState
//-----------------------------------------------------------------------------
SysMon_EnumLowBeamState SysMonRx_ASIL_GetLowBeamState(void)
{
  return SysMonRx_ASIL_sSignalLowBeam.eLowBeamState;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetLowBeamValue
///
/// \descr  Get the Low Beam value
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
uint8 SysMonRx_ASIL_GetLowBeamValue(void)
{
  // Return the Low Beam value
  return (SysMonRx_ASIL_sSignalLowBeam.ucValue != SYSMON_RX_ZERO_VALUE) ? SYSMON_LOWBEAM_ON : SYSMON_LOWBEAM_OFF;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Compute_LB_PhaseVieState
///
/// \descr  Compute the LifePhaseState used by Low Beam in the Emergency Operation Mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_Compute_LB_PhaseVieState(void)
{
  teRte_SigQty    eSigQty       = SIG_SNA;
  teRte_PhaseVie  eLifePhaseCmd = eWake;

  STATIC_UT(boolean, boInvalidFailure, FALSE);
  STATIC_UT(boolean, boTimeoutFailure, FALSE);
  STATIC_UT(boolean, boNoFailure, FALSE);
  STATIC_UT(boolean, boSetLifePhaseInvalid, FALSE);

  // Get Life Phase value and Signal Quality from SysMonRx_Callbacks
  SysMonRx_Callbacks_GetLifePhaseSignal(&eLifePhaseCmd, &eSigQty);

  // Check for Invalid and Timeout errors
  switch (eSigQty)
  {
  case SIG_INVALID:
    // Reset Flags for other errors
    boTimeoutFailure = FALSE;
    boNoFailure      = FALSE;

    // First time appearance of Invalid error
    if (boInvalidFailure == FALSE)
    {
      // Get time stamp
      SysMonRx_ASIL_ulInvalid_LB_LifePhase_us = TimerGetTick();
      // Set Invalid Failure flag
      boInvalidFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_LB_LifePhase_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_LIFEPHASE_LB_INVALID_ERROR_MS))
      {
        // Set the Life Phase Invalid flag
        boSetLifePhaseInvalid = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
    break;

  case SIG_TIMEOUT:
    // Reset Flags for other errors
    boInvalidFailure = FALSE;
    boNoFailure = FALSE;

    // First time appearance of Timeout error
    if (boTimeoutFailure == FALSE)
    {
      // Get time stamp
      SysMonRx_ASIL_ulInvalid_LB_LifePhase_us = TimerGetTick();
      // Set Timeout Failure flag
      boTimeoutFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_LB_LifePhase_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_LIFEPHASE_LB_TIMEOUT_ERROR_MS))
      {
        // Set the Life Phase Invalid flag
        boSetLifePhaseInvalid = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
    break;

  case SIG_VALID:
    // Reset Flags for other errors
    boTimeoutFailure = FALSE;
    boInvalidFailure = FALSE;

    // First time appearance of No Failure
    if (boNoFailure == FALSE)
    {
      // Get time stamp
      SysMonRx_ASIL_ulInvalid_LB_LifePhase_us = TimerGetTick();
      // Set No Failure flag
      boNoFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_LB_LifePhase_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_LIFEPHASE_LB_NO_ERROR_MS))
      {
        // Clear the Life Phase Invalid flag
        boSetLifePhaseInvalid = FALSE;
      }
      else
      {
        // nothing to do
      }
    }
    break;

  default:
    break;
  }

  // Check Life Phase Invalid flag
  if (TRUE == boSetLifePhaseInvalid)
  {
    // Set the LifePhaseState to Invalid State
    SysMonRx_ASIL_SetLbLifePhaseState(SysMon_LifePhase_Invalid_State);
  }
  else
  {
    if (eSigQty == SIG_VALID)
    {
      switch (eLifePhaseCmd)
      {
      case eNormalMode:
        // Set the LifePhaseState to Normal State
        SysMonRx_ASIL_SetLbLifePhaseState(SysMon_LifePhase_Normal_State);
        break;

      case eStandBy:
      case eSwitchToStadby:
      case eWake:
      case eCOM_OFF:
        // Set the LifePhaseState to Not Normal State
        SysMonRx_ASIL_SetLbLifePhaseState(SysMon_LifePhase_Not_Normal_State);
        break;

      default:
        // nothing to do
        break;
      }
    }
    else
    {
      // nothing to do
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_SetLbLifePhaseState
///
/// \descr  Set the Life Phase State value for Low Beam
///
/// \param  State - Life Phase State that will be set
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_SetLbLifePhaseState(SysMon_EnumLifePhaseState State)
{
  // Set the Life Phase State
  SysMonRx_ASIL_sSignalLifePhase.eLbLifePhaseState = State;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetLbLifePhaseState
///
/// \descr  Puplic interface to get LifePhase state for Emergency Operation Mode
///
/// \param  void
///
/// \return SysMon_EnumLifePhaseState - value of LifePhaseState
//-----------------------------------------------------------------------------
STATIC_AL SysMon_EnumLifePhaseState SysMonRx_ASIL_GetLbLifePhaseState(void)
{
  return SysMonRx_ASIL_sSignalLifePhase.eLbLifePhaseState;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Compute_VESMainState
///
/// \descr  Compute the VESMainState state used in the Emergency Operation Mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_Compute_VESMainState(void)
{
  teRte_SigQty    eSigQty = SIG_SNA;

  STATIC_UT(boolean, boInvalidFailure, FALSE);
  STATIC_UT(boolean, boTimeoutFailure, FALSE);
  STATIC_UT(boolean, boNoFailure, FALSE);
  STATIC_UT(boolean, boSetVESMainStateInvalid, FALSE);

  // Get VESMainState Signal Quality from SysMonRx_Callbacks
  SysMonRx_Callbacks_GetVESMainStateSignal(&eSigQty);

  // Check for Invalid and Timeout errors
  switch (eSigQty)
  {
  case SIG_INVALID:
    // Reset Flags for other errors
    boTimeoutFailure = FALSE;
    boNoFailure = FALSE;

    // First time appearance of Invalid error
    if (boInvalidFailure == FALSE)
    {
      // Get time stamp
      SysMonRx_ASIL_ulInvalid_VESMainState_us = TimerGetTick();
      // Set Invalid Failure flag
      boInvalidFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_VESMainState_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_VESMAINSTATE_INVALID_ERROR_MS + SysMonRx_ASIL_ulTiScrlTime))
      {
        // Set the VESMainState Invalid flag
        boSetVESMainStateInvalid = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
    break;

  case SIG_TIMEOUT:
    // Reset Flags for other errors
    boInvalidFailure  = FALSE;
    boNoFailure       = FALSE;

    // First time appearance of Timeout error
    if (boTimeoutFailure == FALSE)
    {
      // Get time stamp
      SysMonRx_ASIL_ulInvalid_VESMainState_us = TimerGetTick();
      // Set Timeout Failure flag
      boTimeoutFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_VESMainState_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_VESMAINSTATE_TIMEOUT_ERROR_MS + SysMonRx_ASIL_ulTiScrlTime))
      {
        // Set the VESMainState Invalid flag
        boSetVESMainStateInvalid = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
    break;

  case SIG_VALID:
    // Reset Flags for other errors
    boTimeoutFailure = FALSE;
    boInvalidFailure = FALSE;

    // First time appearance of No Failure
    if (boNoFailure == FALSE)
    {
      // Get time stamp
      SysMonRx_ASIL_ulInvalid_VESMainState_us = TimerGetTick();
      // Set No Failure flag
      boNoFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_VESMainState_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_VESMAINSTATE_NO_ERROR_MS + SysMonRx_ASIL_ulTiScrlTime))
      {
        // Clear the VESMainState Invalid flag
        boSetVESMainStateInvalid = FALSE;
      }
      else
      {
        // nothing to do
      }
    }
    break;

  default:
    break;
  }

  // Check VESMainState Invalid flag
  if (TRUE == boSetVESMainStateInvalid)
  {
    // Set the VESMainState to Invalid State
    SysMonRx_ASIL_SetVESMainState(SysMon_VESMainState_Invalid_State);
  }
  else
  {
    // Set the VESMainState to Valid State
    SysMonRx_ASIL_SetVESMainState(SysMon_VESMainState_Valid_State);
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_SetVESMainState
///
/// \descr  Set the VES Main State value
///
/// \param  State - VESMainState State that will be set
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_SetVESMainState(SysMon_EnumVESMainState State)
{
  // Set the VES Main State
  SysMonRx_ASIL_sSignalVESMainState.eVESMainState = State;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetVESMainState
///
/// \descr  Puplic interface to get VESMainState state for Emergency Operation Mode
///
/// \param  void
///
/// \return SysMon_EnumVESMainState - value of VESMainState
//-----------------------------------------------------------------------------
STATIC_AL SysMon_EnumVESMainState SysMonRx_ASIL_GetVESMainState(void)
{
  return SysMonRx_ASIL_sSignalVESMainState.eVESMainState;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Compute_SpeedMainState
///
/// \descr  Compute the SpeedState used in the Emergency Operation Mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_Compute_SpeedState(void)
{
  teRte_SigQty  eSigQty = SIG_SNA;
  uint16        unSpeedLastValidValue = 0u;

  STATIC_UT(boolean, boInvalidFailure, FALSE);
  STATIC_UT(boolean, boTimeoutFailure, FALSE);
  STATIC_UT(boolean, boNoFailure, FALSE);
  STATIC_UT(boolean, boSetSpeedInvalid, FALSE);

  // Get Speed Value and Signal Quality from SysMonRx_Callbacks
  SysMonRx_Callbacks_GetSpeedSignal(&unSpeedLastValidValue, &eSigQty);

  // Check for CRC, E2E Alive, Timeout and Invalid errors
  switch (eSigQty)
  {
    case SIG_INVALID:
    case SIG_E2E_CRCERR:
    case SIG_E2E_ALIVEERR:
    case SIG_E2E_TIMEOUT:
      // Reset Flags for other errors
      boTimeoutFailure = FALSE;
      boNoFailure = FALSE;

      // First time appearance of CRC/Alive/Invalid error
      if (boInvalidFailure == FALSE)
      {
        // Get time stamp
        SysMonRx_ASIL_ulInvalid_Speed_us = TimerGetTick();
        // Set CRC Failure flag
        boInvalidFailure = TRUE;
      }
      else
      {
        if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_Speed_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_SPEED_CRC_ALIVE_INVALID_ERROR_MS))
        {
          // Set the Speed Invalid flag
          boSetSpeedInvalid = TRUE;
        }
        else
        {
          // nothing to do
        }
      }
      break;

    case SIG_TIMEOUT:
      // Reset Flags for other errors
      boInvalidFailure = FALSE;
      boNoFailure = FALSE;

      // First time appearance of Timeout error
      if (boTimeoutFailure == FALSE)
      {
        // Get time stamp
        SysMonRx_ASIL_ulInvalid_Speed_us = TimerGetTick();
        // Set Timeout Failure flag
        boTimeoutFailure = TRUE;
      }
      else
      {
        if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_Speed_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_SPEED_TIMEOUT_ERROR_MS))
        {
          // Set the Speed Invalid flag
          boSetSpeedInvalid = TRUE;
        }
        else
        {
          // nothing to do
        }
      }
      break;

    case SIG_VALID:
      // Reset Flags for other errors
      boTimeoutFailure = FALSE;
      boInvalidFailure = FALSE;

      // First time appearance of No Failure
      if (boNoFailure == FALSE)
      {
        // Get time stamp
        SysMonRx_ASIL_ulInvalid_Speed_us = TimerGetTick();
        // Set No Failure flag
        boNoFailure = TRUE;
      }
      else
      {
        if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_Speed_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_SPEED_NO_ERROR_MS))
        {
          // Clear the Speed flag
          boSetSpeedInvalid = FALSE;
        }
        else
        {
          // nothing to do
        }
      }
      break;

    default:
      break;
  }

  // Check Speed Invalid flag
  if (TRUE == boSetSpeedInvalid)
  {
    // Set the SpeedState to Invalid State
    SysMonRx_ASIL_SetSpeedState(SysMon_Speed_Invalid_State);
  }
  else
  {
    if (eSigQty == SIG_VALID)
    {
      if (unSpeedLastValidValue <= SYSMON_RX_5KMH_THRESHOLD)
      {
        // Set the SpeedState to 0 State
        SysMonRx_ASIL_SetSpeedState(SysMon_Speed_0_State);
      }
      else
      {
        // Set the SpeedState to Drive State
        SysMonRx_ASIL_SetSpeedState(SysMon_Speed_Drive_State);
      }
    }
    else
    {
      // nothing to do
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_SetSpeedState
///
/// \descr  Set the Speed State value
///
/// \param  State - Speed State that will be set
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_SetSpeedState(SysMon_EnumSpeedState State)
{
  // Set the Speed State
  SysMonRx_ASIL_sSignalSpeed.eSpeedState = State;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetSpeedState
///
/// \descr  Puplic interface to get Speed state for Emergency Operation Mode
///
/// \param  void
///
/// \return SysMon_EnumSpeedState - value of SpeedState
//-----------------------------------------------------------------------------
SysMon_EnumSpeedState SysMonRx_ASIL_GetSpeedState(void)
{
  return SysMonRx_ASIL_sSignalSpeed.eSpeedState;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Compute_TurnIndicatorState
///
/// \descr  Compute the TurnIndicatorState used in the Emergency Operation Mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_Compute_TurnIndicatorState(void)
{
  teRte_SigQty    eSigQty                = SIG_SNA;
  uint8           ucTurnIndicatorCmd     = SYSMON_TURNINDICATOR_OFF;
  NM_ModeType     eNMMode                = REVEIL;

  STATIC_UT(boolean, boInvalidFailure,          FALSE);
  STATIC_UT(boolean, boTimeoutFailure,          FALSE);
  STATIC_UT(boolean, boNoFailure,               FALSE);
  STATIC_UT(boolean, boSetTurnIndicatorInvalid, FALSE);

  // Get Turn Indicator value and Signal Quality from SysMonRx_Callbacks
  SysMonRx_Callbacks_GetTurnIndicatorSignal(&ucTurnIndicatorCmd, &eSigQty);

  // Get NM Mode from NM Stack
  eNMMode = SysMonRx_getNMMode();

  if (((eNMMode != NM_NORMAL) && (eNMMode != LIMP_HOME_MODE)) &&
      ((eSigQty == SIG_TIMEOUT) || (eSigQty == SIG_INVALID)) &&
      (SysMonRx_ASIL_sSignalTurnIndicator.eTurnIndicatorState == SysMon_TurnIndicator_Valid_State))
  {
    // TI Interface has started failing, but PHASE_VIE has changed // see Ticket ID LDMO-2729
    eSigQty = SIG_SNA;

    // Reset Flags for all errors
    boTimeoutFailure  = FALSE;
    boInvalidFailure  = FALSE;
    boNoFailure       = FALSE;

    // Clear the Turn Indicator Invalid flag
    boSetTurnIndicatorInvalid = FALSE;
  }
  else
  {
    // nothing to do
  }

  // Check for Invalid and Timeout errors
  switch (eSigQty)
  {
    case SIG_INVALID:
      // Reset Flags for other errors
      boTimeoutFailure  = FALSE;
      boNoFailure       = FALSE;

      // First time appearance of Invalid error
      if (boInvalidFailure == FALSE)
      {
        // Get time stamp
        SysMonRx_ASIL_ulInvalid_TurnIndicator_us = TimerGetTick();
        // Set Invalid Failure flag
        boInvalidFailure = TRUE;
      }
      else
      {
        if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_TurnIndicator_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_TURNINDICATOR_INVALID_ERROR_MS + SysMonRx_ASIL_ulTiScrlTime))
        {
          // Set the Turn Indicator Invalid flag
          boSetTurnIndicatorInvalid = TRUE;
        }
        else
        {
          // nothing to do
        }
      }
      break;

    case SIG_TIMEOUT:
      // Reset Flags for other errors
      boInvalidFailure  = FALSE;
      boNoFailure       = FALSE;

      // First time appearance of Timeout error
      if (boTimeoutFailure == FALSE)
      {
        // Get time stamp
        SysMonRx_ASIL_ulInvalid_TurnIndicator_us = TimerGetTick();
        // Set Timeout Failure flag
        boTimeoutFailure = TRUE;
      }
      else
      {
        if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_TurnIndicator_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_TURNINDICATOR_TIMEOUT_ERROR_MS + SysMonRx_ASIL_ulTiScrlTime))
        {
          // Set the Turn Indicator Invalid flag
          boSetTurnIndicatorInvalid = TRUE;
        }
        else
        {
          // nothing to do
        }
      }
      break;

    case SIG_VALID:
      // Reset Flags for other errors
      boTimeoutFailure = FALSE;
      boInvalidFailure = FALSE;

      // First time appearance of No Failure
      if (boNoFailure == FALSE)
      {
        // Get time stamp
        SysMonRx_ASIL_ulInvalid_TurnIndicator_us = TimerGetTick();
        // Set No Failure flag
        boNoFailure = TRUE;
      }
      else
      {
        if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_TurnIndicator_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_TURNINDICATOR_NO_ERROR_MS + SysMonRx_ASIL_ulTiScrlTime))
        {
          // Clear the Turn Indicator Invalid flag
          boSetTurnIndicatorInvalid = FALSE;
        }
        else
        {
          // nothing to do
        }
      }
      break;

    default:
      // Reset Flags for all errors
      boTimeoutFailure  = FALSE;
      boInvalidFailure  = FALSE;
      boNoFailure       = FALSE;

      // Clear the Turn Indicator Invalid flag
      boSetTurnIndicatorInvalid = FALSE;
      break;
  }

  // Check Turn Indicator Invalid flag
  if (TRUE == boSetTurnIndicatorInvalid)
  {
    // Set the TurnIndicatorState to Invalid State
    SysMonRx_ASIL_SetTurnIndicatorState(SysMon_TurnIndicator_Invalid_State);
  }
  else
  {
    if (eSigQty == SIG_VALID)
    {
      // Set the Turn Indicator Value
      SysMonRx_ASIL_SetTurnIndicatorValue(ucTurnIndicatorCmd);
      // Set the TurnIndicatorState to Valid State
      SysMonRx_ASIL_SetTurnIndicatorState(SysMon_TurnIndicator_Valid_State);
    }
    else
    {
      // nothing to do
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_SetTurnIndicatorValue
///
/// \descr  Set the Turn Indicator value
///
/// \param  ucTurnIndicatorCmd - Turn Indicator command received on CAN frame HS6_DAT_VSM_2AE
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_SetTurnIndicatorValue(uint8 ucTurnIndicatorCmd)
{
  // Set the Turn Indicator value
  SysMonRx_ASIL_sSignalTurnIndicator.ucValue = ucTurnIndicatorCmd;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_SetTurnIndicatorState
///
/// \descr  Set the Turn Indicator State value
///
/// \param  State - Turn Indicator State that will be set
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_SetTurnIndicatorState(SysMon_EnumTurnIndicatorState State)
{
  // Set the Turn Indicator State
  SysMonRx_ASIL_sSignalTurnIndicator.eTurnIndicatorState = State;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_GetTurnIndicatorValue
///
/// \descr  Get the Turn Indicator value
///
/// \param  void
///
/// \return uint8 - value of Turn Indicator
//-----------------------------------------------------------------------------
uint8 SysMonRx_ASIL_GetTurnIndicatorValue(void)
{
  // Return the Turn Indicator value
  return SysMonRx_ASIL_sSignalTurnIndicator.ucValue;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetTurnIndicatorState
///
/// \descr  Puplic interface to get TurnIndicator state for Emergency Operation Mode
///
/// \param  void
///
/// \return SysMon_EnumTurnIndicatorState - value of TurnIndicatorState
//-----------------------------------------------------------------------------
SysMon_EnumTurnIndicatorState SysMonRx_ASIL_GetTurnIndicatorState(void)
{
  return SysMonRx_ASIL_sSignalTurnIndicator.eTurnIndicatorState;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Compute_TI_PhaseVieState
///
/// \descr  Compute the LifePhaseState used by Turn Indicator in the Emergency Operation Mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_Compute_TI_PhaseVieState(void)
{
  teRte_SigQty    eSigQty = SIG_SNA;
  teRte_PhaseVie  eLifePhaseCmd = eWake;

  STATIC_UT(boolean, boInvalidFailure, FALSE);
  STATIC_UT(boolean, boTimeoutFailure, FALSE);
  STATIC_UT(boolean, boNoFailure, FALSE);
  STATIC_UT(boolean, boSetLifePhaseInvalid, FALSE);

  // Get Life Phase value and Signal Quality from SysMonRx_Callbacks
  SysMonRx_Callbacks_GetLifePhaseSignal(&eLifePhaseCmd, &eSigQty);

  // Check for Invalid and Timeout errors
  switch (eSigQty)
  {
  case SIG_INVALID:
    // Reset Flags for other errors
    boTimeoutFailure = FALSE;
    boNoFailure = FALSE;

    // First time appearance of Invalid error
    if (boInvalidFailure == FALSE)
    {
      // Get time stamp
      SysMonRx_ASIL_ulInvalid_TI_LifePhase_us = TimerGetTick();
      // Set Invalid Failure flag
      boInvalidFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_TI_LifePhase_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_LIFEPHASE_TI_INVALID_ERROR_MS + SysMonRx_ASIL_ulTiScrlTime))
      {
        // Set the Life Phase Invalid flag
        boSetLifePhaseInvalid = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
    break;

  case SIG_TIMEOUT:
    // Reset Flags for other errors
    boInvalidFailure = FALSE;
    boNoFailure = FALSE;

    // First time appearance of Timeout error
    if (boTimeoutFailure == FALSE)
    {
      // Get time stamp
      SysMonRx_ASIL_ulInvalid_TI_LifePhase_us = TimerGetTick();
      // Set Timeout Failure flag
      boTimeoutFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_TI_LifePhase_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_LIFEPHASE_TI_TIMEOUT_ERROR_MS + SysMonRx_ASIL_ulTiScrlTime))
      {
        // Set the Life Phase Invalid flag
        boSetLifePhaseInvalid = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
    break;

  case SIG_VALID:
    // Reset Flags for other errors
    boTimeoutFailure = FALSE;
    boInvalidFailure = FALSE;

    // First time appearance of No Failure
    if (boNoFailure == FALSE)
    {
      // Get time stamp
      SysMonRx_ASIL_ulInvalid_TI_LifePhase_us = TimerGetTick();
      // Set No Failure flag
      boNoFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(SysMonRx_ASIL_ulInvalid_TI_LifePhase_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_LIFEPHASE_TI_NO_ERROR_MS + SysMonRx_ASIL_ulTiScrlTime))
      {
        // Clear the Life Phase Invalid flag
        boSetLifePhaseInvalid = FALSE;
      }
      else
      {
        // nothing to do
      }
    }
    break;

  default:
    break;
  }

  // Check Life Phase Invalid flag
  if (TRUE == boSetLifePhaseInvalid)
  {
    // Set the LifePhaseState to Invalid State
    SysMonRx_ASIL_SetTiLifePhaseState(SysMon_LifePhase_Invalid_State);
  }
  else
  {
    if (eSigQty == SIG_VALID)
    {
      switch (eLifePhaseCmd)
      {
      case eNormalMode:
        // Set the LifePhaseState to Normal State
        SysMonRx_ASIL_SetTiLifePhaseState(SysMon_LifePhase_Normal_State);
        break;

      case eStandBy:
      case eSwitchToStadby:
      case eWake:
      case eCOM_OFF:
        // Set the LifePhaseState to Not Normal State
        SysMonRx_ASIL_SetTiLifePhaseState(SysMon_LifePhase_Not_Normal_State);
        break;

      default:
        // nothing to do
        break;
      }
    }
    else
    {
      // nothing to do
    }
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_SetTiLifePhaseState
///
/// \descr  Set the Life Phase State value for Turn Indicator
///
/// \param  State - Life Phase State that will be set
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_ASIL_SetTiLifePhaseState(SysMon_EnumLifePhaseState State)
{
  // Set the Life Phase State
  SysMonRx_ASIL_sSignalLifePhase.eTiLifePhaseState = State;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetTiLifePhaseState
///
/// \descr  Puplic interface to get LifePhase state for Emergency Operation Mode
///
/// \param  void
///
/// \return SysMon_EnumLifePhaseState - value of LifePhaseState
//-----------------------------------------------------------------------------
STATIC_AL SysMon_EnumLifePhaseState SysMonRx_ASIL_GetTiLifePhaseState(void)
{
  return SysMonRx_ASIL_sSignalLifePhase.eTiLifePhaseState;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationTurnIndicator
///
/// \descr  Return Turn Indicator in context of Emergency Operation Mode (send request)
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationTurnIndicator(void)
{
  return SysMonRx_ASIL_boEmergencyOperationTurnIndicator;
}


#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Check_TI_Scrolling
///
/// \descr  Check if TI Scrolling is present and add 200 ms to TI interfaces if it is present
///
/// \param  void
///
/// \return boolean 
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonRx_ASIL_Check_TI_Scrolling(void)
{
  STATIC_UT(boolean, boCheckTiScrl,           TRUE);
  STATIC_UT(boolean, boCheckTiScrlTimerStart, TRUE);
  STATIC_UT(TIMER,   ulCheckTiScrlTimer_us,     0u);

  boolean boIsTiScrlPresent = FALSE;

  // First time check, see if timer needs to be started
  if (boCheckTiScrlTimerStart != FALSE)
  {
    // Get time stamp
    ulCheckTiScrlTimer_us = TimerGetTick();
    // Clear first time check flag
    boCheckTiScrlTimerStart = FALSE;
  }
  else
  {
    if (TimerGetTimeSince(ulCheckTiScrlTimer_us) >= UTILTIME_MSEC(SYSMONRX_ASIL_SCROLLING_TI_CHECK_MS))
    {
      // Get information if TI Scrolling is Present
      boIsTiScrlPresent = SysMonCheck_Data_Get_TiScrollingPresent();

      // Add 200 ms time to interfaces if TI Scrolling is present
      SysMonRx_ASIL_ulTiScrlTime = (FALSE != boIsTiScrlPresent) ? SYSMONRX_ASIL_TURNINDICATOR_SCROLLING_MS : SYSMONRX_ASIL_TURNINDICATOR_NO_SCROLLING_MS;

      // Invalidate flag
      boCheckTiScrl = FALSE;
    }
    else
    {
      // nothing to do, timer has not expired yet
    }
  }

  return boCheckTiScrl;
}
#endif // CFG_VARIANT_FULL


// EOF
