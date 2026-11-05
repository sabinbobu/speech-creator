//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddMlc_Adapter.c
///
/// \brief
///
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

// standard includes

// module API (include path)
#include <CddMlc_Adapter.h>

// module includes (relative to API)
#include <CddMlc.h>
#include <CddMlc_Cod.h>
#include <CddMlc_RoutCfg.h>

// RTE includes
#ifndef UNIT_TEST
#include <Rte.h>
#endif

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define CDDMLC_DEVICE_MATRIXGEN2   0u
#define CDDMLC_DEVICE_MATRIXGEN3   1u

//-----------------------------------------------------------------------------
// Private type definitions
//-----------------------------------------------------------------------------
typedef void (*pMlcDevInitFunc)(void);
typedef void (*pMlDevCyclicFunc)(void);

typedef struct
{
  pMlcDevInitFunc init;
  pMlcDevInitFunc cyclic;
}tsCddMlc_DeviceAPIs;

//=============================================================================
// Private variables
//=============================================================================

// Device enum
#define CDDMLC_DECL_DEV_ENUM
#include <CddMlc_Cfg.h>

// Interface Configuration
#define CDDMLC_DECL_IFCCFG
#include <CddMlc_Cfg.h>

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
CONST_AL  tNvmPara_CodingArea*  CddMlc_pCodingArea;
STATIC_AL tsCddMlc_CodingData   CddMlc_sCodingData;
STATIC_AL teCddMlc_DeviceType   CddMlc_eConnectedDevice = eMlcDeviceMax;
STATIC_AL boolean               CddMlc_boExecuteOperation = FALSE;
STATIC_AL boolean               CddMlc_boActionToExecuteAfterNewConfig = FALSE;
STATIC_AL tsCddMlcStatus        CddMlc_sStatus;

// simulation interface (activated by compiler switch only)
#ifdef CDDMLC_Cfg_Simulation

#define MLC_Sim_ElectricalErrors 0x5A5AA5A5u
STATIC_AL volatile uint32 CddMlc_ulTestElErrorHookActivation = 0u;
STATIC_AL volatile tsCddMlc_SimulationData CddMlc_sSimulationData[CDDMLC_CFG_MAX_CHIPS];

#define MLC_Sim_ADCChangeValues 0xA5A5A5A5u
STATIC_AL volatile uint32 CddMlc_ulTestADCHookActivation = 0u;
STATIC_AL volatile uint8  CddMlc_ucADC1Value_NTC[CDDMLC_CFG_MAX_CHIPS];
STATIC_AL volatile uint8  CddMlc_ucADC2Value_Binning[CDDMLC_CFG_MAX_CHIPS];
STATIC_AL volatile uint8  CddMlc_ucSelectChip;

#endif

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define CDDMLC_CODING_DEBUG 0u

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
STATIC_AL teCddMlc_DeviceType CddMlc_DeviceCfg(void);
STATIC_AL void    CddMlc_DevInit(teCddMlc_DeviceType eDeviceId);
STATIC_AL void    CddMlc_DevCyclic(teCddMlc_DeviceType eDeviceId);
STATIC_AL void    reCddMlc_NewTarget(void);
STATIC_AL void    CddMlc_UpdateRTE(tsCddMlcStatus sMlcComStatus);

STATIC_AL void    CddMlc_Read_CodingPara(tsCddMlc_CodingParam* sCodingParam);
STATIC_AL boolean CddMlc_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
STATIC_AL void    CddMlc_EvaluateCoding(void);
STATIC_AL boolean CddMlc_CodingDataValidation(void);
STATIC_AL void    CddMlc_Data_LmmConfig(void);
STATIC_AL void    CddMlc_CheckReinitMatrix(void);

//-----------------------------------------------------------------------------
/// \brief  riCddMlc_Init
///
/// \descr  Init runnable of CDDMLC module to be called at MCU start-up
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void riCddMlc_Init(void)
{
  // evaluate coding and get parameters
   CddMlc_EvaluateCoding();

  if ( (CddMlc_boExecuteOperation != FALSE) && (CddMlc_boActionToExecuteAfterNewConfig != FALSE))
  {
    CddMlc_DevInit(CddMlc_eConnectedDevice);
    CddMlc_boActionToExecuteAfterNewConfig = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  rpCddMlc_Cycle0
///
/// \descr  Cyclic runnable for CDDMLC module ; Cycle time = 10 ms
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void rpCddMlc_Cycle0(void)
{

  // evaluate coding and get parameters if it failed in init phase
    CddMlc_EvaluateCoding();

  /*
    Cycle routine performed depending on if MLC is present or not
    in the ECU configuration (coding data)

    OperationEnabled:  At least 1 MLC is connected
    OperationDisabled: No MLC connected
  */

  /* Devices are connected according to Coding Data -> MLC Operation must be enabled    */

  if (CddMlc_boExecuteOperation != FALSE)
  {

    //Call the appropriate init function 
    if (CddMlc_boActionToExecuteAfterNewConfig != FALSE)
    {
      CddMlc_DevInit(CddMlc_eConnectedDevice);
      CddMlc_boActionToExecuteAfterNewConfig = FALSE;
    }

    /*
       Power Up Delay, before sending any command to MLCs
       Introduce some delay till the HSS2 output became stable
       before starting the initialization sequence of the MLC driver
    */

    if (CddMlc_CheckPowerUp() != FALSE)
    {
      CddMlc_DevCyclic(CddMlc_eConnectedDevice);

      // set target values
      reCddMlc_NewTarget();
      //collect MLCs status
      CddMlc_GetStatus(CDDMLC_Para_CHIP_TYPE, &CddMlc_sStatus);
      //check matrix reinitialization 
      CddMlc_CheckReinitMatrix();
      // send to rte port
      CddMlc_UpdateRTE(CddMlc_sStatus);
      //check eeprom timeout
      CDDMLC_EEPROM_TIMEOUT();
    }
    else
    {
      // do nothing 
    }
  }
}// PRQA S 5324 // HIS metrics violation : STCAL = 9 for architecture and readability

//-----------------------------------------------------------------------------
/// \brief  reCddMlc_NewTarget
///
/// \descr  This function is called on new target values reception
///         This shall be done event triggered by writing RTE target value
///
/// \param  -
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void reCddMlc_NewTarget(void)
{
  tsCddMlcTarget *psTargetPWM;
  tsRte_TgtMtxPixels_sVal sRteTarget;
  // read target values    
  CDDMLC_GET_TARGET_PWM(&sRteTarget);
  //PRQA S 310 1 //cast needed
  psTargetPWM = (tsCddMlcTarget*)&sRteTarget;
  //send target values
  CddMlc_SetTarget(CDDMLC_Para_CHIP_TYPE, psTargetPWM);
}

//-----------------------------------------------------------------------------
/// \brief CddMlc_CheckReinitMatrix
///
/// \descr this function receives the command to reinit MLCs in case the application
///        reacts in case of comm error
///
/// \param  -
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlc_CheckReinitMatrix(void)
{
  boolean boGetMatrixReset = FALSE, boClrPort = FALSE;
  //get matrix command reset via rte
  CDDMLC_GET_REINIT_MLC(&boGetMatrixReset);
  CddMlc_CheckReinit(CDDMLC_Para_CHIP_TYPE, boGetMatrixReset);
  //set rte matrix command reset to false
  CDDMLC_RTE_SEND_CLR_REINIT_MLC(&boClrPort);
}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_UpdateRTE
///
/// \descr  This function performs a cyclical update of the matrix data on RTE
///
/// \param  sMlcComStatus
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlc_UpdateRTE(tsCddMlcStatus sMlcComStatus)
{
  tsRte_CddMlcComStatus   sDevComStatus   = { 0 };
  tsRte_MlcComErrorStatus sDevCrcStatus   = { 0 };
  tasRte_MlcLedStatus     asDevFaultError = { 0 };
  tasRte_MlcAdcResult     asDevSensorData = { 0 };
  teRte_CddMlc_SystemMode eSystemMode = CddMlc_SystemMode_Inactive;

  for (uint8 ucDevId = 0u; ucDevId < CDDMLC_CFG_MAX_CHIPS; ucDevId++)
  {
    //get communication error 
    if (sMlcComStatus.aboComFault[ucDevId] != FALSE)
    {
      sDevComStatus.ucMlcStatus |= (uint8)((uint8)1u << ucDevId);
    }
    else
    {
      sDevComStatus.ucMlcStatus &= (uint8)(~(uint8)(1u << ucDevId));
    }

    //get CRC error 
    sDevCrcStatus.aboMlcCorruptedComm[ucDevId] = sMlcComStatus.aboCrcFault[ucDevId];

    // save electrical status fault
    asDevFaultError[ucDevId].unLedFault = sMlcComStatus.asSwitchFault[ucDevId].unSwitchFault_Bit;


    //save sensor data
    asDevSensorData[ucDevId].ucADC1Value = sMlcComStatus.asSensorData[ucDevId].ucADC1Value;
    asDevSensorData[ucDevId].ucADC2Value = sMlcComStatus.asSensorData[ucDevId].ucADC2Value;
    //remap signal quality of ADC for RTE common types
    switch (sMlcComStatus.asSensorData[ucDevId].eQlty)
    {
    case SENSOR_QLTY_VALID:
      asDevSensorData[ucDevId].eQlty = CDD_MLC_QLTY_VALID;
      break;
    case SENSOR_QLTY_INVALID:
      asDevSensorData[ucDevId].eQlty = CDD_MLC_QLTY_INVALID;
      break;
    case SENSOR_QLTY_SNA:
    default:
      asDevSensorData[ucDevId].eQlty = CDD_MLC_QLTY_SNA;
      break;
    }

#ifdef CDDMLC_Cfg_Simulation
    //compiler switch in case developer hook is active; overwrite the values
    if (CddMlc_ulTestADCHookActivation == MLC_Sim_ADCChangeValues)
    {
      asDevSensorData[ucDevId].ucADC1Value = CddMlc_ucADC1Value_NTC[ucDevId];
      asDevSensorData[ucDevId].ucADC2Value = CddMlc_ucADC2Value_Binning[ucDevId];
    }

    //compiler swicth in case developer hook is active; overwrite the values
    if (CddMlc_ulTestElErrorHookActivation == MLC_Sim_ElectricalErrors)
    {
      asDevFaultError[ucDevId].unLedFault = CddMlc_sSimulationData[ucDevId].unLedFault;
      sDevCrcStatus.aboMlcCorruptedComm[ucDevId] = CddMlc_sSimulationData[ucDevId].boCrcFault;
    }
#endif
  }
  
  // save Power On Reset (PWR) Status represented on bit
  sDevComStatus.ucPowerCycle = sMlcComStatus.ucPowerOnReset;
  eSystemMode = (sMlcComStatus.boInitStatus != FALSE) ? CddMlc_SystemMode_CfgLeds : CddMlc_SystemMode_Powerup;

  //write device com. status fault
    CDDMLC_RTE_SEND_MTX_COMM_STATUS(&sDevComStatus)
  //write device crc status fault
    CDDMLC_RTE_SEND_MTX_CRC_STATUS(&sDevCrcStatus)
  //write electrical fault
    CDDMLC_RTE_SEND_MTX_PXL_FAULT(&asDevFaultError)
  // write sensor data
    CDDMLC_RTE_SEND_MTX_ADC_DATA(&asDevSensorData)
  // write matrix init status
    CDDMLC_RTE_SEND_MTX_INIT_STATUS(&eSystemMode)
}

//-----------------------------------------------------------------------------
/// \brief  CddTpsMixed_Init
///
/// \descr  This function calls the initialization of the modules
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsMixed_Init(void)
{
  CddTpsGen2_Init();
  CddTpsGen3_Init();
}
    
//-----------------------------------------------------------------------------
/// \brief  CddTpsMixed_Cycle
///
/// \descr  This function calls the cycle functions of the modules
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddTpsMixed_Cycle(void)
{
  CddTpsGen2_Cycle();
  CddTpsGen3_Cycle();

}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_DevInit
///
/// \descr  This function calls the correct init function assigned to the
///         MLC device type
///
/// \param  eDeviceId : MLC device type
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlc_DevInit(teCddMlc_DeviceType eDeviceId)
{
  /* call the appropriate MLC type init function */
  if ((eDeviceId < eMlcDeviceMax) && (CddMlc_sDeviceAPIs[eDeviceId].init != NULL_PTR))
  {
    CddMlc_sDeviceAPIs[eDeviceId].init();
  }
}


//-----------------------------------------------------------------------------
/// \brief  CddMlc_DevCyclic
///
/// \descr  This function calls the correct cyclic function assigned to the 
///         MLC device type
///
/// \param  eDeviceId : MLC device type
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlc_DevCyclic(teCddMlc_DeviceType eDeviceId)
{
  /* call the appropriate MLC type cyclic function */
  if ((eDeviceId < eMlcDeviceMax) && (CddMlc_sDeviceAPIs[eDeviceId].cyclic != NULL_PTR))
  {
    CddMlc_sDeviceAPIs[eDeviceId].cyclic();
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_Read_CodingPara
///
/// \descr  Function to read the coding parameters from CodM module
///
/// \param  sCodingParam
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlc_Read_CodingPara(tsCddMlc_CodingParam* sCodingParam)
{
  tsRteCodingParameters* sRteCodingParam;

  //PRQA S 310 1 //cust needed
  sRteCodingParam = (tsRteCodingParameters*)sCodingParam;

  //read coding
  (void)Rte_Read_CodM_CddMlc_Para(sRteCodingParam);
}


//-----------------------------------------------------------------------------
/// \brief  CddMlc_CodingDataValidation
///
/// \descr  This function reads the coding data, checks and return the validity
///
/// \param  -
///
/// \return STATIC_AL boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddMlc_CodingDataValidation(void)
{
  tsCddMlc_CodingParam sCodingParam;

  //get coding data via RTE
  CDDMLC_RTE_RE_GET_CODING_DATA(&sCodingParam);

  CONST_AL boolean boCodingValidity = CddMlc_ParaFct0(sCodingParam.eCodingState, sCodingParam.psCodingParameters_Blocks);

  //return validity of coding
  return boCodingValidity;
}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_ParaFct0
///
/// \descr  This function get coding parameters and check validity of coding
///
/// \param  eCmd  : coding status
/// \param  pData : coding parameters
///
/// \return STATIC_AL boolean : coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean CddMlc_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;

  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
    CddMlc_pCodingArea = pData;
    boCodingValidity = TRUE;
    break;
  case eParaFct0_CodingDataInvalid:
    boCodingValidity = FALSE;
    break;
  default:
    break;
  }

  return boCodingValidity;
 
}


//-----------------------------------------------------------------------------
/// \brief  CddMlc_EvaluateCoding
///
/// \descr  Validate the coding data and extract the relevant coding parameters
///
/// \param  -
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlc_EvaluateCoding(void)
{
  // init state for coding data
  STATIC_UT(boolean, boCodingPrevStatus, FALSE);

  //actual state for coding data
  boolean boCodingStatus;

  //read coding data, check if coding needs to be reloaded 
  boCodingStatus = CddMlc_CodingDataValidation();

  // get the relevant coding data once coding status is valid
  if ((boCodingStatus != FALSE) && (boCodingPrevStatus == FALSE))
  {

    // get parameters
    CddMlc_Data_LmmConfig();

    // return the device name connected from coding data
    CddMlc_eConnectedDevice = CddMlc_DeviceCfg();

    // check if the MLC driver is enabled or not
    if (CddMlc_sCodingData.ucMlcConnectedDevs > 0U)
    {
      CddMlc_boExecuteOperation = TRUE;
    }
    else
    {
      CddMlc_boExecuteOperation = FALSE;
    }

    //Reset flag -> new coding requires new once executed actions
    CddMlc_boActionToExecuteAfterNewConfig = TRUE;
  }
 
  //save coding status in module's struct
  CddMlc_sCodingData.boCodingValid = boCodingStatus;

  // keep the current status of coding data
  boCodingPrevStatus = boCodingStatus;

}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_Data_LmmConfig
///
/// \descr  Load coding data into MLC configuration structure
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlc_Data_LmmConfig(void)
{
  uint8* pucMlcCodAddr = NULL_PTR;

  CddMlc_sCodingData.ucMlcConnectedDevGEN2 = 0u;
  CddMlc_sCodingData.ucMlcConnectedDevGEN3 = 0u;
  CddMlc_sCodingData.ucMlcConnectedDevs    = 0u;

#if(CDDMLC_CODING_DEBUG == 0u)
  // get mlc chip type
  CddMlc_sCodingData.ucMlcMatrixType = CddMlc_Cod_Get_MlcChipType();
#else
  CddMlc_sCodingData.ucMlcMatrixType = CDDMLC_COD_MATRIX_TYPE_TPSGENx_1;
#endif
  // get mlc coding address ID
  pucMlcCodAddr = CddMlc_Cod_Get_ChipID();

  // get mlc bus interface
  CddMlc_sCodingData.ucMlcCanUartInterface = (CddMlc_sCodingData.ucMlcMatrixType != CDDMLC_COD_MATRIX_TYPE_NXP) ? CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN : CDDMLC_COD_MATRIX_INTERFACE_SATELLITE_CAN;

  // get mlc addresses only for the supported range
  if ( (CddMlc_sCodingData.ucMlcMatrixType != CDDMLC_COD_MATRIX_TYPE_DISABLED) && (CddMlc_sCodingData.ucMlcMatrixType <= CDDMLC_COD_MATRIX_TYPE_TPSGENx_2) ) 
  {
    //get the uart communication speed for the matrix device 
#if(CDDMLC_CODING_DEBUG == 0u)
    CddMlc_sCodingData.ucMlcBaudRate = CddMlc_Cod_Get_MlcBaudRate();
#else
    CddMlc_sCodingData.ucMlcBaudRate = 10u;
#endif

    for (uint8 ucDevice = 0u; ucDevice < CDDMLC_CFG_MAX_CHIPS; ucDevice++)
    {
#if(CDDMLC_CODING_DEBUG == 0u)
      CddMlc_sCodingData.aucMlcCanUartDeviceID[ucDevice] = pucMlcCodAddr[ucDevice];
#else

      /*   ---------  START   TEST   CODE  FOR MIXED      UNTIL    CODING IS AVAILABLE   ----------------   */      
      switch (CddMlc_sCodingData.ucMlcMatrixType)
      {
      case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A:
        /* adding 8u  is to know the master device for  GEN 2 */
        CddMlc_sCodingData.aucMlcCanUartDeviceID[0] = 0u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[1] = 255u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[2] = 2u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[3] = 255u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[4] = 4u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[5] = 5u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[6] = 6u + 8u;
        break;
      case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664:
        /* adding 32u is to know it is GEN 3 */
        /* adding 16u is to know the master device for  GEN 3 */
        CddMlc_sCodingData.aucMlcCanUartDeviceID[0] = 32u + 3u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[1] = 255u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[2] = 32u + 4u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[3] = 255u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[4] = 255u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[5] = 255u;
        CddMlc_sCodingData.aucMlcCanUartDeviceID[6] = 255u;
        break;
      case CDDMLC_COD_MATRIX_TYPE_TPSGENx_1:
        /* adding 32u is to know it is GEN 3 */
        /* adding 8u  is to know the master device for  GEN 2 */
        /* adding 16u is to know the master device for  GEN 3 */
        CddMlc_sCodingData.aucMlcCanUartDeviceID[0] = 32u + 11u + 16u;  //LMM1    -> DRV BUCK 05    -  HB
        CddMlc_sCodingData.aucMlcCanUartDeviceID[1] = 255u;         		//LMM2
        CddMlc_sCodingData.aucMlcCanUartDeviceID[2] = 32u + 12u;    		//LMM3    -> DRV BUCK 07    -  HB
        CddMlc_sCodingData.aucMlcCanUartDeviceID[3] = 255u;         		//LMM4
        CddMlc_sCodingData.aucMlcCanUartDeviceID[4] = 4u;           		//LMM5    -> DRV BUCK 06    - LOW BEAM
        CddMlc_sCodingData.aucMlcCanUartDeviceID[5] = 255u;         		//LMM6
        CddMlc_sCodingData.aucMlcCanUartDeviceID[6] = 6u + 8u;        	//LMM7    -> DRV BUCK 12    - HB randul cel mai mare

        //PLACA CU 2 X GEN3 (TPS664)
        //CddMlc_sCodingData.aucMlcCanUartDeviceID[0] = 32u + 3u;       //LMM1    -> DRV BUCK 05    -  HB
        //CddMlc_sCodingData.aucMlcCanUartDeviceID[1] = 255u;           //LMM2
        //CddMlc_sCodingData.aucMlcCanUartDeviceID[2] = 32u + 4u;    	  //LMM3    -> DRV BUCK 07    -  HB
        //CddMlc_sCodingData.aucMlcCanUartDeviceID[3] = 255u;           //LMM4
        //CddMlc_sCodingData.aucMlcCanUartDeviceID[4] = 2u;             //LMM5    -> DRV BUCK 06    - LOW BEAM
        //CddMlc_sCodingData.aucMlcCanUartDeviceID[5] = 255u;           //LMM6
        //CddMlc_sCodingData.aucMlcCanUartDeviceID[6] = 6u + 8u;        //LMM7    -> DRV BUCK 12    - HB randul cel mai mare
        break;
      default:
        break;
      }
      
#endif
      //CddMlc_sCodingData.ucMlcEepromDeviceID = 255u;

      /*   ---------  END   TEST   CODE  FOR MIXED      UNTIL    CODING IS AVAILABLE   ----------------   */

      if (CDDMLC_DRV_IsGEN2(ucDevice) != FALSE)
      {
        CddMlc_sCodingData.ucMlcConnectedDevs++;
        CddMlc_sCodingData.ucMlcConnectedDevGEN2++;
      }
      else if (CDDMLC_DRV_IsGEN3(ucDevice) != FALSE)
      {
        CddMlc_sCodingData.ucMlcConnectedDevs++;
        CddMlc_sCodingData.ucMlcConnectedDevGEN3++;
      }
      else
      {

      }
    }

  }
  else
  {
    CddMlc_sCodingData.ucMlcConnectedDevs = 0;
  }

  //get eeprom address ID
  CddMlc_sCodingData.ucMlcEepromDeviceID = CddMlc_Cod_Get_EepromAddrID();
}


//-----------------------------------------------------------------------------
/// \brief  CddMlc_Cod_UartGetConfig
///
/// \descr  Function called as callback by Uart module to set the correct Baud Rate
///         for the mounted device type
///
/// \param  unDevUartCfg    : mounted device type
/// \param  pucBaudRate     : Baud Rate to be set 
/// \param  pucMountedDev  :  mounted device on bits
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddMlc_Cod_UartGetConfig(uint8 ucDevUartCfg, uint8* pucBaudRate, uint8 *pucMountedDev)
{
  STATIC_UT(uint8, ucDev_Bit, 0u);
  const boolean boCodStatus = CddMlc_sCodingData.boCodingValid;
  *pucBaudRate = 0u;

  if (boCodStatus != FALSE)
  {
    *pucBaudRate = CddMlc_sCodingData.ucMlcBaudRate;
    switch (CddMlc_sCodingData.ucMlcMatrixType)
    {
    case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A:
    case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A:
      if (ucDevUartCfg == CDDMLC_DEVICE_MATRIXGEN2)
      {
        ucDev_Bit |= (uint8)(1u << ucDevUartCfg);
      }
      break;
    case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664:
    case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665:
    case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667:
      if (ucDevUartCfg == CDDMLC_DEVICE_MATRIXGEN3)
      {
        ucDev_Bit |= (uint8)(1u << ucDevUartCfg);
      }
      break;
    case CDDMLC_COD_MATRIX_TYPE_TPSGENx_1:
    case CDDMLC_COD_MATRIX_TYPE_TPSGENx_2:
     if ((ucDevUartCfg == CDDMLC_DEVICE_MATRIXGEN2) || (ucDevUartCfg == CDDMLC_DEVICE_MATRIXGEN3))
      {
       ucDev_Bit |= (uint8)(1u << ucDevUartCfg);
      }
      break;
    default:
      break;
    }
    *pucMountedDev = ucDev_Bit;
  }

  return boCodStatus;
}


//-----------------------------------------------------------------------------
/// \brief  CddMlc_pfGetCodingData
///
/// \descr  Return coding data structure for sub-modules usage
///
/// \param  -
///
/// \return tsCddMlc_CodingData *
//-----------------------------------------------------------------------------
tsCddMlc_CodingData* CddMlc_pfGetCodingData(void)
{
  return &CddMlc_sCodingData;
}


//-----------------------------------------------------------------------------
/// \brief  CddMlc_DeviceCfg
///
/// \descr  This function configures the switch number in a string based on 
///         matrix type and returns the device name
///
/// \param  -
///
/// \return STATIC_AL CddMlc_eDeviceType
//-----------------------------------------------------------------------------
STATIC_AL teCddMlc_DeviceType CddMlc_DeviceCfg(void)
{
  teCddMlc_DeviceType eRetDevType;

  switch (CddMlc_sCodingData.ucMlcMatrixType)
  {

  case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A:
    CddMlc_sCodingData.ucMlcSwitchsSupported = CDDMLC_TPSGEN2_MAX_SWITCHES_PER_DEVICE;
    eRetDevType = MLC_DEVICE(DEV_TI_GEN2);
    break;

  case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A:
    CddMlc_sCodingData.ucMlcSwitchsSupported = CDDMLC_TPSGEN2_3A_MAX_SWITCHES_PER_DEVICE;
    eRetDevType = MLC_DEVICE(DEV_TI_GEN2);
    break;

  case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664:
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665:
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667:
    CddMlc_sCodingData.ucMlcSwitchsSupported = CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE;
    eRetDevType = MLC_DEVICE(DEV_TI_GEN3);
    break;
 
  case CDDMLC_COD_MATRIX_TYPE_TPSGENx_1:
  case CDDMLC_COD_MATRIX_TYPE_TPSGENx_2:
    CddMlc_sCodingData.ucMlcSwitchsSupported = CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE;
    eRetDevType = MLC_DEVICE(DEV_MIXED_TI);
    break;

  default:
    eRetDevType = eMlcDeviceMax;           // undefined
    break;
  }

  return eRetDevType;
}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_IsDevGEN2
/// 
/// \descr  The function checks if the coded device is a generation 2 type
///
/// \param  ucDevId
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddMlc_IsDevGEN2(uint8 ucDevId)
{
  boolean boDevGEN2;

  boDevGEN2 = CddMlc_sCodingData.aucMlcCanUartDeviceID[ucDevId] < CDDMLC_COD_DEV_ADDR_GEN3_START ? TRUE : FALSE;

  return boDevGEN2;
}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_IsDevGEN3
///
/// \descr  The function checks if the coded device is a generation 3 type
///
/// \param  ucDevId
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddMlc_IsDevGEN3(uint8 ucDevId)
{
  boolean boDevGEN3;

  boDevGEN3 =  ( (CddMlc_sCodingData.aucMlcCanUartDeviceID[ucDevId] >= CDDMLC_COD_DEV_ADDR_GEN3_START &&
                 (CddMlc_sCodingData.aucMlcCanUartDeviceID[ucDevId] < CDDMLC_COD_DEV_ADDR_GEN3_MAX_ID) ) )  ? TRUE : FALSE;

  return boDevGEN3;
}

//-----------------------------------------------------------------------------
/// \brief  reCddMlcEE_CbkInit
///
/// \descr  Access the right I2C init callback function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void reCddMlcEE_CbkInit(void)
{
  tsRte_MatrixEE0CbkFn sMlcEE_DataInitCbk;
  (void)Rte_Read_CtrlPxl_MatrixEE_CbkInitData(&sMlcEE_DataInitCbk);
  (void)CDDMLC_DRV_GEN2_InitEEprom(sMlcEE_DataInitCbk.pfnMatrixEECbkSuccess, sMlcEE_DataInitCbk.pfnMatrixEECbkFail);
}

//-----------------------------------------------------------------------------
/// \brief  reCddMlcEE_Read
///
/// \descr  Access EEPROM memory and store the read data
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void reCddMlcEE_Read(void)
{
  tsRte_MatrixEE0peration sMlcEE_DataRead;
  (void)Rte_Read_CtrlPxl_MatrixEE_DataRead(&sMlcEE_DataRead);
  (void)CDDMLC_DRV_GEN2_ReadEEprom(sMlcEE_DataRead.pucMatrixEEbuffer, sMlcEE_DataRead.unMatrixEEStartAdd, sMlcEE_DataRead.unMatrixEELength, sMlcEE_DataRead.sMatrixEE0CbkFn.pfnMatrixEECbkSuccess, sMlcEE_DataRead.sMatrixEE0CbkFn.pfnMatrixEECbkFail);
}

//-----------------------------------------------------------------------------
/// \brief  reCddMlcEE_Write
///
/// \descr  Access EEPROM memory to load data
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void reCddMlcEE_Write(void)
{
  tsRte_MatrixEE0peration sMlcEE_DataWrite;
  (void)Rte_Read_CtrlPxl_MatrixEE_DataWrite(&sMlcEE_DataWrite);
  (void)CDDMLC_DRV_GEN2_WriteEEprom(sMlcEE_DataWrite.pucMatrixEEbuffer, sMlcEE_DataWrite.unMatrixEEStartAdd, sMlcEE_DataWrite.unMatrixEELength, sMlcEE_DataWrite.sMatrixEE0CbkFn.pfnMatrixEECbkSuccess, sMlcEE_DataWrite.sMatrixEE0CbkFn.pfnMatrixEECbkFail);
}


//-----------------------------------------------------------------------------
/// \brief  CddMlc_GetEEPROMAddressId
///
/// \descr  This function returns the device matrix id to which eeprom is attached
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CddMlc_GetEEPROMAddressId(void)
{
  uint8 ucEEConnectedId = CDDMLC_COD_DEV_ADDR_NOT_CONNECTED;
  if (CddMlc_sCodingData.ucMlcMatrixType != CDDMLC_COD_MATRIX_TYPE_DISABLED)
  {
    ucEEConnectedId = CDDMLC_EEPROM_CONNECTED_ID();
  }
  return ucEEConnectedId;
}
