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
/// \file  CddStp_Simulation.h
///
/// \brief Simulation interface used for HIL test
///
/// \author J. Kling ALRT-EES6 (f84304b)
///
//-----------------------------------------------------------------------------
#ifndef CDD_STP_SIMULATION_H_
#define CDD_STP_SIMULATION_H_


//=============================================================================
// Defines and Typedef
//=============================================================================

#define CDDSTP_SIMULATION_PASSWORD         0xCAFEBABEu
#define CDDSTP_SIMULATION_DEACTIVATED      0xDEADC0DEu

#define CDDSTP_SIMULATION_UNUSED_VALUE     0xFFFFu


typedef enum
{
  eSimuHandling_Inactive = 0xFFu,
  eSimuHandling_Active   = 1u
} tCddStp_SimuHndlng;


typedef struct {
  uint32              ulSimActivated;                     // simulation active (password)

  uint16              unVBatt_EcuSupply_mV;               // 'IoHwAb_User_GetAdc_DIAG_VBAT' / 'Rte_Read_ctacCddStp_ppIoHwAbUserEcuSupply0_ulActual' / 'Rte_Read_ppIoHwAbUserEcuSupply0_ulActual'

  tCddStp_SimuHndlng  ucSim_DriverDefect;                 // G-SWRS.STP2.897: Set sCddStp_Simulation_Data.ulSimActivated to 0xCAFEBABE and sCddStp_Simulation_Data.ucSim_DriverDefect to 1. 

  tCddStp_SimuHndlng  ucSim_SPI_ERROR_SpiProtocolError;   // Indicates SPI protocol errors, such as more SCLK pulses than are required or SCLK is absent even though nSCS is low.Becomes high in fault and the nFAULT pin is driven low.Normal operation resumes when the protocol error is removed and a clear faults command has been issued either through the CLR_FLT bit or an nSLEEP reset pulse.
  tCddStp_SimuHndlng  ucSim_UVLO_UnderVoltageLockout;     // Indicates an undervoltage lockout fault condition.
  tCddStp_SimuHndlng  ucSim_CPUV_ChargePumpUndervoltage;  // Indicates charge pump undervoltage fault condition.
  tCddStp_SimuHndlng  ucSim_OCP_OverCurrentProtection;    // Indicates overcurrent fault condition
  tCddStp_SimuHndlng  ucSim_OL_OpenLoad;                  // Indicates open-load condition
//tCddStp_SimuHndlng  ucSim_TF_ThermalFault;              // Logic OR of the overtemperature warning, undertemperature warning and overtemperature shutdown.
  tCddStp_SimuHndlng  ucSim_OTW_OverThermalWarning;       // Over-Thermal-Warning: reducing of current - NO stop and NO error
  tCddStp_SimuHndlng  ucSim_OTS_OverTemperatureShutdown;  // Indicates overtemperature shutdown
  tCddStp_SimuHndlng  ucSim_UTW_UnderTemperatureWarning;  // Indicates undertemperature warning - currently NOT used

  tCddStp_SimuHndlng  ucSim_LT_IsLowTemperature;          // set Low-Temperature-Mode

  uint8               ucSim_StReg_Basic;                  // 1 1 UVLO CPUV OCP RSVD TF OL
  uint8               ucSim_StReg_Fault;                  // FAULT SPI_ERROR UVLO CPUV OCP RSVD TF OL
  uint8               ucSim_StReg_DiagStatus1;            // OCP_LS2_B OCP_HS2_B OCP_LS1_B OCP_HS1_B OCP_LS2_A OCP_HS2_A OCP_LS1_A OCP_HS1_A
  uint8               ucSim_StReg_DiagStatus2;            // UTW OTW OTS RSVD RSVD RSVD OL_B OL_A
} tCddStp_Simulation_Data; // simulation for validation purposes


boolean CddStp_Simulation_IsSimActive(void);
boolean CddStp_Simulation_HandleVBatt_EcuSupply(uint16 * punVoltage_mV);
void    CddStp_Simulation_HandleSpiRxStatusBits(boolean * pboSim_DriverDefect, boolean * pboSim_SPI_ERROR_SpiProtocolError , boolean * pboSim_UVLO_UnderVoltageLockout
                                                                             , boolean * pboSim_CPUV_ChargePumpUndervoltage, boolean * pboSim_OCP_OverCurrentProtection
                                                                             , boolean * pboSim_OL_OpenLoad
                                                                           /*, boolean * pboSim_TF_ThermalFault*/          , boolean * pboSim_OTW_OverThermalWarning
                                                                             , boolean * pboSim_OTS_OverTemperatureShutdown, boolean * pboSim_UTW_UnderTemperatureWarning);
void    CddStp_Simulation_HandleStatusRegisters(uint8 * pucBasic, uint8 * pucFault, uint8 * pucDiagStatus1, uint8 * pucDiagStatus2);
boolean CddStp_Simulation_HandleDriverDefect_FatalError(void);
boolean CddStp_Simulation_HandleLowTempMode(void);


#endif // CDD_STP_SIMULATION_H_

// EOF
