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
/// \file  CddStp_Simulation.c
///
/// \brief Simulation interface used for HIL test
///
/// \author J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------

//=============================================================================
//  Standard / system header file includes
//=============================================================================

#include <Std_Types.h>
#include <AL_Helper.h> //-- STATIC_AL


//=============================================================================
//  Project-specific header file includes
//=============================================================================

#ifndef UNIT_TEST // NOT Unit-Tests = 'regular'
#include <CddStpPrj.h>

#else // Unit-Tests!
//  #define CFA_CNT_STP_88XX   (4u)
  #include <CddStpPrj.h>
#endif


#ifdef CDDSTP_CFG_SIMULATION // defined in '.\Asr6\Src\Src_AL\Cust\Bw\Bw16\App\Bsw\Cdd\CddStp\CddStpPrj.h'
#include <CddStp_Simulation.h>


//=============================================================================
// local variables
//=============================================================================

STATIC_AL tCddStp_Simulation_Data CddStp_Simulation_Data = // simulation for validation purposes
{
  .ulSimActivated                    = CDDSTP_SIMULATION_DEACTIVATED,

  .unVBatt_EcuSupply_mV              = CDDSTP_SIMULATION_UNUSED_VALUE, // 'Magic-Number' -> Simu-Voltage NOT valid/used

  .ucSim_DriverDefect                = eSimuHandling_Inactive,

  .ucSim_SPI_ERROR_SpiProtocolError  = eSimuHandling_Inactive,
  .ucSim_UVLO_UnderVoltageLockout    = eSimuHandling_Inactive,
  .ucSim_CPUV_ChargePumpUndervoltage = eSimuHandling_Inactive,
  .ucSim_OCP_OverCurrentProtection   = eSimuHandling_Inactive,
  .ucSim_OL_OpenLoad                 = eSimuHandling_Inactive,
//.ucSim_TF_ThermalFault             = eSimuHandling_Inactive,
  .ucSim_OTW_OverThermalWarning      = eSimuHandling_Inactive,
  .ucSim_OTS_OverTemperatureShutdown = eSimuHandling_Inactive,
  .ucSim_UTW_UnderTemperatureWarning = eSimuHandling_Inactive,

  .ucSim_LT_IsLowTemperature         = eSimuHandling_Inactive,

  .ucSim_StReg_Basic                 = 0u,
  .ucSim_StReg_Fault                 = 0u,
  .ucSim_StReg_DiagStatus1           = 0u,
  .ucSim_StReg_DiagStatus2           = 0u
};


//=============================================================================
// Macros
//=============================================================================

//=============================================================================
// Prototpes
//=============================================================================

//=============================================================================
// Function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Return TRUE if the simulation interface has been actived with password
///
/// \descr
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddStp_Simulation_IsSimActive(void)
{
  return (CddStp_Simulation_Data.ulSimActivated == CDDSTP_SIMULATION_PASSWORD) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  pboSim_DriverDefect
/// \param  pboSim_SPI_ERROR_SpiProtocolError
/// \param  pboSim_UVLO_UnderVoltageLockout
/// \param  pboSim_CPUV_ChargePumpUndervoltage
/// \param  pboSim_OCP_OverCurrentProtection
/// \param  pboSim_OL_OpenLoad
/// \param  pboSim_OTW_OverThermalWarning
/// \param  pboSim_OTS_OverTemperatureShutdown
/// \param  pboSim_UTW_UnderTemperatureWarning
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_Simulation_HandleSpiRxStatusBits(boolean * pboSim_DriverDefect, boolean * pboSim_SPI_ERROR_SpiProtocolError , boolean * pboSim_UVLO_UnderVoltageLockout
                                                                          , boolean * pboSim_CPUV_ChargePumpUndervoltage, boolean * pboSim_OCP_OverCurrentProtection
                                                                          , boolean * pboSim_OL_OpenLoad
                                                                        /*, boolean * pboSim_TF_ThermalFault*/          , boolean * pboSim_OTW_OverThermalWarning
                                                                          , boolean * pboSim_OTS_OverTemperatureShutdown, boolean * pboSim_UTW_UnderTemperatureWarning)
{
  if (CddStp_Simulation_IsSimActive() != FALSE)
  {
    // if (CddStp_Simulation_Data.ucSim_SPI_ERROR_SpiProtocolError != eSimuHandling_Inactive)
    *pboSim_DriverDefect                = (CddStp_Simulation_Data.ucSim_DriverDefect                == eSimuHandling_Active) ? TRUE : FALSE;
    *pboSim_SPI_ERROR_SpiProtocolError  = (CddStp_Simulation_Data.ucSim_SPI_ERROR_SpiProtocolError  == eSimuHandling_Active) ? TRUE : FALSE;
    *pboSim_OL_OpenLoad                 = (CddStp_Simulation_Data.ucSim_OL_OpenLoad                 == eSimuHandling_Active) ? TRUE : FALSE;
    *pboSim_OCP_OverCurrentProtection   = (CddStp_Simulation_Data.ucSim_OCP_OverCurrentProtection   == eSimuHandling_Active) ? TRUE : FALSE;
    *pboSim_UVLO_UnderVoltageLockout    = (CddStp_Simulation_Data.ucSim_UVLO_UnderVoltageLockout    == eSimuHandling_Active) ? TRUE : FALSE;
    *pboSim_CPUV_ChargePumpUndervoltage = (CddStp_Simulation_Data.ucSim_CPUV_ChargePumpUndervoltage == eSimuHandling_Active) ? TRUE : FALSE;
  //*pboSim_TF_ThermalFault             = (CddStp_Simulation_Data.ucSim_TF_ThermalFault             == eSimuHandling_Active) ? TRUE : FALSE;
    *pboSim_OTW_OverThermalWarning      = (CddStp_Simulation_Data.ucSim_OTW_OverThermalWarning      == eSimuHandling_Active) ? TRUE : FALSE;
    *pboSim_OTS_OverTemperatureShutdown = (CddStp_Simulation_Data.ucSim_OTS_OverTemperatureShutdown == eSimuHandling_Active) ? TRUE : FALSE;
    *pboSim_UTW_UnderTemperatureWarning = (CddStp_Simulation_Data.ucSim_UTW_UnderTemperatureWarning == eSimuHandling_Active) ? TRUE : FALSE;
  }

  else // sim is NOT active
  {
    // MISRA
  }
  // PRQA S 5328 1 // program architecture and readability - intentionally no modification of existing code  -  warning - QAC(Prio2) Msg : 5328(HIS metrics violation : 'CddStp8899Com_Simulation_HandleSpiRxStatusBits() : STPAR = 8' exceeds threshold 5 for Number of function parameters(STPAR).)
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_Simulation_HandleVBatt_EcuSupply
///
/// \descr  VBatt in mV
///         Magic-Number: CDDSTP_SIMULATION_UNUSED_VALUE ('0xFFFF')  ->  do NOT use value
///
/// \param  punVoltage_mV
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddStp_Simulation_HandleVBatt_EcuSupply(uint16 * punVoltage_mV)
{
  *punVoltage_mV = CddStp_Simulation_Data.unVBatt_EcuSupply_mV; // Magic-Number: CDDSTP_SIMULATION_UNUSED_VALUE ('0xFFFF') 
  return (*punVoltage_mV == CDDSTP_SIMULATION_UNUSED_VALUE) ? FALSE : TRUE;
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_Simulation_HandleDriverDefect_FatalError
///
/// \descr
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddStp_Simulation_HandleDriverDefect_FatalError(void)
{
  return (CddStp_Simulation_Data.ucSim_DriverDefect == eSimuHandling_Active) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_Simulation_HandleLowTempMode
///
/// \descr
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddStp_Simulation_HandleLowTempMode(void)
{
  return (CddStp_Simulation_Data.ucSim_LT_IsLowTemperature == eSimuHandling_Active) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  CddStp_Simulation_UpdateStatusRegisters
///
/// \descr
///
/// \param  4x Status-Register: ucBasic, ucFault, ucDiagStatus1, ucDiagStatus2
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_Simulation_HandleStatusRegisters(uint8 *pucBasic, uint8 *pucFault, uint8 *pucDiagStatus1, uint8 *pucDiagStatus2)
{
  // 'simulation' is NOT active  ->  update internal vars
  if (CddStp_Simulation_IsSimActive() == FALSE)
  {
    // store 'correct' values for later use
    CddStp_Simulation_Data.ucSim_StReg_Basic       = *pucBasic;
    CddStp_Simulation_Data.ucSim_StReg_Fault       = *pucFault;
    CddStp_Simulation_Data.ucSim_StReg_DiagStatus1 = *pucDiagStatus1;
    CddStp_Simulation_Data.ucSim_StReg_DiagStatus2 = *pucDiagStatus2;
  }
  else // sim is active
  {
    *pucBasic       = CddStp_Simulation_Data.ucSim_StReg_Basic;
    *pucFault       = CddStp_Simulation_Data.ucSim_StReg_Fault;
    *pucDiagStatus1 = CddStp_Simulation_Data.ucSim_StReg_DiagStatus1;
    *pucDiagStatus2 = CddStp_Simulation_Data.ucSim_StReg_DiagStatus2;
  }
}


#endif // CDDSTP_CFG_SIMULATION

// EOF
