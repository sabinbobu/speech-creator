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
/// \file   SysVolt_RteAccess.c
///
/// \brief  Rte wrappers
///
/// \descr  Rte Wrappers implementation (read/write)
///
/// \author Henrietta Futo (F31185D)
///         mailTo: henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <Bsw/IoHwAb/IoHwAbUser.h>
#include <Swc/SysVolt/SysVolt_RteAccess.h>
#include <Swc/SysVolt/SysVolt.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif
#include <RteCommonTypes.h> 


//=============================================================================
// Wrapper functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief SysVolt_RteAccess_Write_Stp_VoltState
///
/// \descr Stepper voltage Range Rte wrapper
///
/// \param  teSysVolt_VoltRanges - input stepper voltage range
///
/// \return void
//-----------------------------------------------------------------------------
void SysVolt_RteAccess_Write_Stp_VoltState(teSysVolt_VoltRanges eInVoltageRange)
{
  teRte_SysVolt_Results eSetVoltageState;

  // Local module type convertor to Rte type
  switch (eInVoltageRange)
  {
    case eSysVolt_eLow3:    eSetVoltageState = SysVolt_eLow3;   break;
    case eSysVolt_eLow2:    eSetVoltageState = SysVolt_eLow2;   break;
    case eSysVolt_eLow1:    eSetVoltageState = SysVolt_eLow1;   break;
    case eSysVolt_eNormal:  eSetVoltageState = SysVolt_eNormal; break;
    case eSysVolt_eHigh1:   eSetVoltageState = SysVolt_eHigh1;  break;
    case eSysVolt_eHigh2:   eSetVoltageState = SysVolt_eHigh2;  break;
    case eSysVolt_eHigh3:   eSetVoltageState = SysVolt_eHigh3;  break;
    default: eSetVoltageState = SysVolt_eUnknown; break;
  }

  // Write Stp Voltage range on Rte
  //(void)Rte_Write_SysVolt_StepperVoltRng0_sVoltRng(&eSetVoltageState); 
}

//-----------------------------------------------------------------------------
/// \brief SysVolt_RteAccess_Write_Led_VoltState
///
/// \descr Led voltage Range Rte wrapper
///
/// \param  teSysVolt_VoltRanges - input led voltage range
///
/// \return void
//-----------------------------------------------------------------------------
void SysVolt_RteAccess_Write_Led_VoltState(teSysVolt_VoltRanges eInVoltageRange)
{
  teRte_SysVolt_Results eSetVoltageState;
  // Local module type convertor to Rte type
  switch (eInVoltageRange)
  {
  case eSysVolt_eLow3:    eSetVoltageState = SysVolt_eLow3;   break;
  case eSysVolt_eLow2:    eSetVoltageState = SysVolt_eLow2;   break;
  case eSysVolt_eLow1:    eSetVoltageState = SysVolt_eLow1;   break;
  case eSysVolt_eNormal:  eSetVoltageState = SysVolt_eNormal; break;
  case eSysVolt_eHigh1:   eSetVoltageState = SysVolt_eHigh1;  break;
  case eSysVolt_eHigh2:   eSetVoltageState = SysVolt_eHigh2;  break;
  case eSysVolt_eHigh3:   eSetVoltageState = SysVolt_eHigh3;  break;
  default: eSetVoltageState = SysVolt_eUnknown; break;
  }

  // Write Stp Voltage range on Rte
  (void)Rte_Write_SysVolt_LedVoltRng0_sVoltRng(&eSetVoltageState);
}
//-----------------------------------------------------------------------------
/// \brief SysVolt_RteAccess_Write_Fan_VoltState
///
/// \descr Fan voltage Range Rte wrapper
///
/// \param  teSysVolt_VoltRanges - input fan voltage range
///
/// \return void
//-----------------------------------------------------------------------------
void SysVolt_RteAccess_Write_Fan_VoltState(teSysVolt_VoltRanges eInVoltageRange)
{
 teRte_SysVolt_Results eSetVoltageState;

  // Local module type convertor to Rte type
  switch (eInVoltageRange)
  {
    case eSysVolt_eLow3:    eSetVoltageState = SysVolt_eLow3;    break;
    case eSysVolt_eLow2:    eSetVoltageState = SysVolt_eLow2;    break;
    case eSysVolt_eLow1:    eSetVoltageState = SysVolt_eLow1;    break;
    case eSysVolt_eNormal:  eSetVoltageState = SysVolt_eNormal;  break;
    case eSysVolt_eHigh1:   eSetVoltageState = SysVolt_eHigh1;   break;
    case eSysVolt_eHigh2:   eSetVoltageState = SysVolt_eHigh2;   break;
    case eSysVolt_eHigh3:   eSetVoltageState = SysVolt_eHigh3;   break;
    default:                eSetVoltageState = SysVolt_eUnknown; break;
  }

  // Write Fan Voltage range on Rte
  (void)Rte_Write_SysVolt_FanVoltRng0_sVoltRng(&eSetVoltageState); 
}

//-----------------------------------------------------------------------------
/// \brief SysVolt_RteAccess_Read_Vbat
///
/// \descr Read Vbat voltage Rte call wrapper
///
/// \param  unVoltage_mV - batery voltage indirected
///
/// \return void
//-----------------------------------------------------------------------------
void SysVolt_RteAccess_Read_Vbat(uint16* const unVoltage_mV)
{
  tiu32Voltage_mV u32Voltage_mV;
  // Rte call for Vbat voltage
  (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(&u32Voltage_mV);
  *unVoltage_mV = (uint16)u32Voltage_mV;
}

//-----------------------------------------------------------------------------
/// \brief  SysVolt_RteAccess_ReadVESMainState
///
/// \descr  reads vechicle electric state
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
Std_ReturnType SysVolt_RteAccess_ReadVESMainState(teSysVolt_EtatPrincipSEV *psData)
{
	Std_ReturnType                           ucReturnValue;
	tsRte_SysMon_VehNetState                 sVechStateMsg;
	uint8                                    ucSysVoltVESMainState;

	//receive bb messages
	(void)Rte_Read_SysMon_VehNetState(&sVechStateMsg);

	switch (sVechStateMsg.eVESMainState)
	{
	case VESState_Stop:
		*psData = eSysVolt_State_Stop;
		break;
	case VESState_Ignition:
		*psData = eSysVolt_State_Contact;
		break;
	case VESState_Start:
		*psData = eSysVolt_State_Start;
		break;
	default:
		*psData = eSysVolt_State_InvalidSEV;
		break;
	}

	return ucReturnValue;
}


//-----------------------------------------------------------------------------
/// \brief  SysVolt_RteAccess_ReadElectricalSuppState
///
/// \descr  reads TMC pressure
///
/// \param  void
///
/// \return uint16
//-----------------------------------------------------------------------------
teSysVolt_EtatFee SysVolt_RteAccess_ReadElectricalSuppState(void)
{
  tsRte_SigPrep_ElecSupState sElectricalSupplyStateMsg;
  teSysVolt_EtatFee          eCtrlStpEtatFee;

  //receive bb messages
  (void)Rte_Read_SigPrep_ElecSupState(&sElectricalSupplyStateMsg);

  if (sElectricalSupplyStateMsg.eSigQty == SIG_VALID)
  {
    switch (sElectricalSupplyStateMsg.eElectrSupplyState)
    {
    case eEtatFee_1_1: {eCtrlStpEtatFee = SysVolt_eEtatFee_1_1;     } break;
    case eEtatFee_1_2: {eCtrlStpEtatFee = SysVolt_eEtatFee_1_2;     } break;
    case eEtatFee_1_3c: {eCtrlStpEtatFee = SysVolt_eEtatFee_1_3c;    } break;
    case eEtatFee_1_3r: {eCtrlStpEtatFee = SysVolt_eEtatFee_1_3r;    } break;
    case eEtatFee_2_1: {eCtrlStpEtatFee  = SysVolt_eEtatFee_2_1;     } break;
    case eEtatFee_3c_1: {eCtrlStpEtatFee = SysVolt_eEtatFee_3c_1;    } break;
    case eEtatFee_3r_1: {eCtrlStpEtatFee = SysVolt_eEtatFee_3r_1;    } break;
    case eEtatFee_4_1: {eCtrlStpEtatFee  = SysVolt_eEtatFee_4_1;     } break;
    case eEtatFee_5_5: {eCtrlStpEtatFee  = SysVolt_eEtatFee_5_5;     } break;
    case eEtatFee_1_3vr: {eCtrlStpEtatFee = SysVolt_eEtatFee_1_3vr;   } break;
    case eEtatFee_3vr_1: {eCtrlStpEtatFee = SysVolt_eEtatFee_3vr_1;   } break;
    case eEtatFee_Invalid: {eCtrlStpEtatFee = SysVolt_eEtatFee_Invalid; } break;
    default: break;
    }
  }
  else
  {
    eCtrlStpEtatFee = SysVolt_eEtatFee_Invalid;
  }

  return eCtrlStpEtatFee;
}
// EOF
