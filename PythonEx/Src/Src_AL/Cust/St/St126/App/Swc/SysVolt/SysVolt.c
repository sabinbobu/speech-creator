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
/// \file   SysVolt.c
///
/// \brief  Generic part of SysVolt implementation
///
/// \descr  Main Voltage states processing
///
/// \author Henrietta Futo (F31185D)
///         mailTo: henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Swc/SysVolt/SysVolt.h>
#include <Swc/SysVolt/SysVolt_Cfg.h>
#include <Swc/SysVolt/SysVolt_RteAccess.h>
#include <Swc/SysVolt/SysVolt_Types.h>
#include <RteCommonTypes.h>
#include <Dem.h>
#include <Nvm.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif


//=============================================================================
// variables
//=============================================================================

// Indicates if we have loaded coding data for SysVolt
STATIC_AL boolean                                                SysVolt_boCodingValidStatus = TRUE; 
// Array holding the results for all configured modules
STATIC_AL tsSysVolt_InVoltState                                  SysVolt_asInStateResult[eSysV_LastModule_Idx];
//Coding Data
STATIC_AL tsRteCodingParameters                                   SysVolt_sCodingParam;
STATIC_AL boolean                                                 SysVolt_boIsCodingValid = TRUE;
STATIC_AL teSysVolt_VbatState                                     SysVolt_eVbatDiag = eVbatNormal;
//=============================================================================
// function definitions
//=============================================================================

// Dem Report function of UV_D and OV_D
STATIC_AL void    SysVolt_ReportVbatDemError(teSysVolt_VbatState eVbatState);
STATIC_AL void    SysVolt_StMachine(boolean boInit);
STATIC_AL void    SysVolt_Diagnosis(void);
STATIC_AL boolean SysVolt_DetectElecTransition(void);

//-----------------------------------------------------------------------------
/// \brief  SysVolt_Init
///
/// \descr  Initialization, reading first time the ADC and setting the range levels
///         to the value that is matching with the configured Level voltage
///         values.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysVolt_Init(void)
{
  SysVolt_StMachine(TRUE);
}


//-----------------------------------------------------------------------------
/// \brief  SysVolt_Cycle
///
/// \descr  Cyclic function, called as runnable every 1 ms
///         handles all cyclic tasks of SysVolt
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysVolt_Cycle(void)
{
  static boolean boFlag = FALSE;
  if (SysVolt_boCodingValidStatus != FALSE)
  {
    if (boFlag == FALSE)
    {
      SysVolt_ParaFct0();
      boFlag = TRUE;
    }
    SysVolt_StMachine(FALSE);
	  SysVolt_Diagnosis();
  }
  else
  {
    // Coding not available
  }
  // Get the vehicle state
  
}

//-----------------------------------------------------------------------------
/// \brief  SysVolt_StMachine
///
/// \descr  state machine for voltage behavior based on cfg file
///
/// \param  boInit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysVolt_StMachine(boolean boInit)
{
  // Index in the array of configured modules
  uint8 ucConfigIdx = 0u;
  // Index in the array of voltage ranges
  uint8 ucVoltRangeIdx = 0u;
  // Voltage value read from ADC in millivolts
  uint16 unReadVoltage_mv = 0u;
  // TRUE if voltage range is increasing, FALSE if decreasing
  boolean boDirectionStatus = FALSE;
  // The new voltage derived from unReadVoltage_mv
  // Voltage range result
  teSysVolt_VoltRanges eNewVoltageRange = eSysVolt_eUnknown;
  // Number of volt States for the last entry
  uint8 ucNrVoltStateLast = 0u;
  for (ucConfigIdx = 0u; ucConfigIdx < (uint8)eSysV_LastModule_Idx; ucConfigIdx++)
  {
    // Get voltage value via RTE
    SysVolt_Configs[ucConfigIdx].pfReadVoltageCb(&unReadVoltage_mv);
    /*   unReadVoltage_mv = 11000;*/
       // Get number of states of the last entry 
    ucNrVoltStateLast = SysVolt_Configs[ucConfigIdx].ucNumOfRanges - 1u;

    // Initialize with the highest voltage range
    eNewVoltageRange = SysVolt_Configs[ucConfigIdx].pRangeCfg[ucNrVoltStateLast].eVoltageRange;

    // Check if we find a lower voltage range
    for (ucVoltRangeIdx = 0u; ucVoltRangeIdx < SysVolt_Configs[ucConfigIdx].ucNumOfRanges; ucVoltRangeIdx++)
    {
      if (unReadVoltage_mv < SysVolt_Configs[ucConfigIdx].pRangeCfg[ucVoltRangeIdx].unRangeUpperLimit_mV)
      {
        // Matching voltage range found
        eNewVoltageRange = SysVolt_Configs[ucConfigIdx].pRangeCfg[ucVoltRangeIdx].eVoltageRange;
        break;
      }
      else
      {
        // Continue to find range where upper limit is greater than voltage read
      }
    }
    // End of loop over voltage ranges
    if (boInit != FALSE)
    {
      SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult = eNewVoltageRange;
      // Debounce timer time-out Ms set to elapsed
      SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms = 0u;

      // Inform about the initial voltage range
      if (NULL_PTR != SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb)
      {
        // Invoke Rte wrapper for RTE write
        SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb(eNewVoltageRange);
      }
      else
      {
        // Avoid NULL_PTR call
      }
    }
    else
    {
      // Is it in the same voltage range like in last cycle?
      if (SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange != eNewVoltageRange)
      {
        // Check direction
        boDirectionStatus = (boolean)((eNewVoltageRange > SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult) ? TRUE : FALSE);

        // Reload debounce counter depending on direction
        // Is it getting worse?
        if ((((uint8)eNewVoltageRange > (uint8)eSysVolt_eNormal) && (boDirectionStatus == TRUE)) ||
          (((uint8)eNewVoltageRange < (uint8)eSysVolt_eNormal) && (boDirectionStatus == FALSE)))
        {
          SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms = SysVolt_Configs[ucConfigIdx].pRangeCfg->unDebounceCnt_RangeGetsWorse_Ms;
        }
        else
        {
          SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms = SysVolt_Configs[ucConfigIdx].pRangeCfg->unDebounceCnt_RangeGetsBetter_Ms;
        }

        SysVolt_asInStateResult[ucConfigIdx].ulDebounceTmr_Us = TimerGetTick();
      }
      // Voltage range changed
      else
      {
        // Debounce Timer free runs
      }

      // Check for state change
      if (((TIMER_SIGNED)TimerGetTimeSince(SysVolt_asInStateResult[ucConfigIdx].ulDebounceTmr_Us) >= (TIMER_SIGNED)UTILTIME_MSEC(SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms)) &&
        (SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult != eNewVoltageRange))
      {
        // Debounce time elapsed and new state is different to old state
        // Change state
        SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult = eNewVoltageRange;

        // Call range change indication callback
        if (NULL_PTR != SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb)
        {
          // Write to RTE
          SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb(eNewVoltageRange);
        }
        else
        {
          // Avoid NULL_PTR call
        }
      }
      else
      {
        // Debounce timer not elapsed, keep actual state
      }
    }
    // Save voltage range for next run
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = eNewVoltageRange;
  }
  // End of loop over configurations
}

//-----------------------------------------------------------------------------
/// \brief SysVolt_ParaFct0
///
/// \descr System Volt para function
///
/// \param  eCmd - CodM command (coding validity)
/// \param  pData - Coding address
///
/// \return void
//-----------------------------------------------------------------------------
void SysVolt_ParaFct0(void)
{
 tParaFct0_Cmd sCodingStatus = eParaFct0_CodingDataInvalid;
 (void)Rte_Read_CodM_SysVolt_Para(&SysVolt_sCodingParam);

 sCodingStatus = SysVolt_sCodingParam.eCodingState;

 if (sCodingStatus == eParaFct0_CodingDataValid)
 {
   SysVolt_boIsCodingValid = TRUE;
   /*--------------------------------- LED Voltage Coding Data ----------------------------------------*/
// Coding range values are in Volt with 0.1 factor. They need multiplied with 100 for milivolt convertions
   // LED Voltage levels
   SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[0].unRangeUpperLimit_mV = 100u * (uint16)SysVolt_sCodingParam.psCodingParameters_Blocks->Led1.LedSupplyVoltage.LED_SUPPLY_MIN_OFF_V;
   SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[1].unRangeUpperLimit_mV = 100u * (uint16)SysVolt_sCodingParam.psCodingParameters_Blocks->Led1.LedSupplyVoltage.LED_SUPPLY_MIN_ON_V;
  
   // LED Voltage debounce time
   SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsWorse_Ms = SYSVOLT_ZERO_DEBTIME;
   SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsWorse_Ms  = (uint16)SysVolt_sCodingParam.psCodingParameters_Blocks->Led1.LedSupplyVoltage.LED_SUPPLY_MIN_OFF_T;
   SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsBetter_Ms = (uint16)SysVolt_sCodingParam.psCodingParameters_Blocks->Led1.LedSupplyVoltage.LED_SUPPLY_MIN_OFF_T;
   SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsBetter_Ms = (uint16)SysVolt_sCodingParam.psCodingParameters_Blocks->Led1.LedSupplyVoltage.LED_SUPPLY_MIN_ON_T;

   /*--------------------------------- FAN Voltage Coding Data ----------------------------------------*/
    // Coding range values are in Volt with 0.1 factor. They need multiplied with 100 for milivolt convertions
    // FAN Voltage levels
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[0].unRangeUpperLimit_mV = 100u * (uint16)SysVolt_sCodingParam.psCodingParameters_Blocks->Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_V_MIN;
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[1].unRangeUpperLimit_mV = 100u * (uint16)SysVolt_sCodingParam.psCodingParameters_Blocks->Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_V_MIN;
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[2].unRangeUpperLimit_mV = 100u * (uint16)SysVolt_sCodingParam.psCodingParameters_Blocks->Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_V_MAX;
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[3].unRangeUpperLimit_mV = 100u * (uint16)SysVolt_sCodingParam.psCodingParameters_Blocks->Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_V_MAX;
   // FAN Voltage debounce time
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsWorse_Ms = SYSVOLT_FAN1_DEBTIME_MS;
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsWorse_Ms = SYSVOLT_FAN1_DEBTIME_MS;
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[2].unDebounceCnt_RangeGetsWorse_Ms = SYSVOLT_FAN1_DEBTIME_MS;
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[3].unDebounceCnt_RangeGetsWorse_Ms = SYSVOLT_FAN1_DEBTIME_MS;
   
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsBetter_Ms = SYSVOLT_FAN1_DEBTIME_MS;
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsBetter_Ms = SYSVOLT_FAN1_DEBTIME_MS;
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[2].unDebounceCnt_RangeGetsBetter_Ms = SYSVOLT_FAN1_DEBTIME_MS;
   SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[3].unDebounceCnt_RangeGetsBetter_Ms = SYSVOLT_FAN1_DEBTIME_MS;
 }
 else
 {
   SysVolt_boIsCodingValid = FALSE;
 }
 }

//-----------------------------------------------------------------------------
/// \brief  SysVolt_DetectElecTransition
///
/// \descr  detects change of electric veh state for STT state
///
/// \param  boolean
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysVolt_DetectElecTransition(void)
{
 teSysVolt_EtatFee eCurrentValue = SysVolt_RteAccess_ReadElectricalSuppState();
 boolean boRetVal;

  if ((eCurrentValue == SysVolt_eEtatFee_4_1) ||
    ((eCurrentValue == SysVolt_eEtatFee_1_3c) ||
     (eCurrentValue == SysVolt_eEtatFee_1_3r) ||
     (eCurrentValue == SysVolt_eEtatFee_1_3vr)))
  {
	  boRetVal = TRUE;
  }
  else
  {
	  boRetVal = FALSE;
  }

  return boRetVal;
}

//-----------------------------------------------------------------------------
/// \brief SysVolt_Diagnosis
///
/// \descr SysVolt Check if the requested condition are met for realizing the diagnoss
///        
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysVolt_Diagnosis(void)
{
 teSysVolt_EtatPrincipSEV  eVESMainState = eSysVolt_State_InvalidSEV;
 boolean                   boEtatFee;

 // Checks electric veh state for STT state
 boEtatFee = SysVolt_DetectElecTransition();
 // Reads vechicle electric state
(void)SysVolt_RteAccess_ReadVESMainState(&eVESMainState);

	//check if engine started 
	 //REQS: REQ-0543421 B, REQ-0543407 B from STO
	if (((eVESMainState == eSysVolt_State_Contact) && (NvmBlockDeltaPwmPara.eNVM_Function_STT == eOptionSTT_Absent)) ||
		((eVESMainState == eSysVolt_State_Contact) && (NvmBlockDeltaPwmPara.eNVM_Function_STT == eOptionSTT_Present) && (boEtatFee != FALSE)))
	{
		// Set or Clear Dtc based on Vbat state
		SysVolt_ReportVbatDemError(SysVolt_eVbatDiag);
	}
	else
	{
		// do nothing
		
	}
}

//-----------------------------------------------------------------------------
/// \brief SysVolt_LocalDiagVbat
///
/// \descr SysVolt Local Callback Vbat Diag
///        Transition is only step-by-step, jump between states is not possible
///
/// \param  eVbatState - Vbat Voltage Range state
///
/// \return void
//-----------------------------------------------------------------------------
void SysVolt_LocalDiagVbat(teSysVolt_VoltRanges eVbatState)
{
  // Old Vbat state (previous)
  static teSysVolt_VoltRanges eOldVbatState = eSysVolt_eLow2;
  // General Vbat State
   
  // Diagnostic Vbat State machine
  switch (eVbatState)
  {
    // Vbat < 8.0V
  case eSysVolt_eLow2:
	  SysVolt_eVbatDiag = eVbatLow;
    break;
    // > 8.0 V and < 8.2 V
  case eSysVolt_eLow1:
    if (eOldVbatState != eSysVolt_eLow2)
    {
	  SysVolt_eVbatDiag = eVbatNormal;
    }
    else
    {
      // Keep the state
    }
    break;
    // 8.2 V < Vbat < 15.8 V
  case eSysVolt_eNormal:
	  SysVolt_eVbatDiag = eVbatNormal;
    break;
    // 15.8 V < Vbat < 16.0 V
  case eSysVolt_eHigh1:
    if (eOldVbatState != eSysVolt_eHigh2)
    {
		SysVolt_eVbatDiag = eVbatNormal;
    }
    else
    {
      // keep the state
    }
    break;
    // Vbat > 16.0 V
  case eSysVolt_eHigh2:
	  SysVolt_eVbatDiag = eVbatHigh;
    break;
  default:
    break;
  }

  

     // Set old Vbat state
  eOldVbatState = eVbatState;
}


//-----------------------------------------------------------------------------
/// \brief SysVolt_ReportVbatDemError
///
/// \descr Dem Error reporting based on Vbat state transition (Vbat)
///
/// \param  eVbatState: Vbat State [Normal, OverVoltage or UnderVoltage]
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysVolt_ReportVbatDemError(teSysVolt_VbatState eVbatState)
{
  switch (eVbatState)
  {
    // Nominal voltage transition (Clear Dtcs)
  case eVbatNormal:
    // Clear UV_D and OV_D
    Rte_Call_DemPrj_ReportErrorStatus((uint16)OV_D, DEM_EVENT_STATUS_PASSED);
    Rte_Call_DemPrj_ReportErrorStatus((uint16)UV_D, DEM_EVENT_STATUS_PASSED);
  break;
    // Undervoltage transition (Set UV_D)
  case eVbatLow:
    // Set UV_D
      Rte_Call_DemPrj_ReportErrorStatus((uint16)UV_D, DEM_EVENT_STATUS_FAILED);
    // Clear OV_D
      Rte_Call_DemPrj_ReportErrorStatus((uint16)OV_D, DEM_EVENT_STATUS_PASSED);
    break;
    // Overvolatge transition (Set OV_D)
  case eVbatHigh:
    // Set OV_D
      Rte_Call_DemPrj_ReportErrorStatus((uint16)OV_D, DEM_EVENT_STATUS_FAILED);
    // Clear UV_D
      Rte_Call_DemPrj_ReportErrorStatus((uint16)UV_D, DEM_EVENT_STATUS_PASSED);
    break;
  default:
    break;
  }
}
// EOF
