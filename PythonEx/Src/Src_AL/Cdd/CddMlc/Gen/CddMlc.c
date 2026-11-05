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
/// \file  CddMlc.c
///
/// \brief
///
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
// standard includes
#include <AL_Helper.h>

// module API (include path)
#include <CddMlc.h>
#include <CddMlc_Cod.h>

// module includes (relative to API)
#include <CddMlc_RoutCfg.h>
#include <CddMlc_Types.h>

#include <CddMlc_Cfg.h>

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
STATIC_AL tsCddMlcTarget  CddMlc_sTarget        = { 0u };
STATIC_AL boolean         CddMlc_boMlcPoweredUP = FALSE;

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
STATIC_AL boolean CddMlcTPS92662_GetDeviceStatusFault(boolean* pboComFault);
STATIC_AL boolean CddMlcTPS92664_GetDeviceStatusFault(boolean* pboComFault);
STATIC_AL boolean CddMlcTPS9266x_GetDeviceStatusFault(boolean* pboComFault);

STATIC_AL void    CddMlcTPS92664_GetDeviceCrcFault   (boolean* pboCrcFault);
STATIC_AL void    CddMlcTPS92662_GetDeviceCrcFault   (boolean* pboCrcFault);
STATIC_AL void    CddMlcTPS9266x_GetDeviceCrcFault   (boolean* pboCrcFault);

STATIC_AL void    CddMlcTPS92662_GetSwitchsFault(tsSwitchFault *psSwitchFault);
STATIC_AL void    CddMlcTPS92664_GetSwitchsFault(tsSwitchFault *psSwitchFault);
STATIC_AL void    CddMlcTPS9266x_GetSwitchsFault(tsSwitchFault *psSwitchFault);

STATIC_AL void    CddMlcTPS92662_GetSensorInfo(tsCddMlc_SensorData* psSensorData);
STATIC_AL void    CddMlcTPS92664_GetSensorInfo(tsCddMlc_SensorData* psSensorData);
STATIC_AL void    CddMlcTPS9266x_GetSensorInfo(tsCddMlc_SensorData* psSensorData);

STATIC_AL uint8   CddMlcTps92662x_GetPowerOnReset(void);

STATIC_AL boolean CddMlcTPS9266x_GetDeviceInit(void);
STATIC_AL boolean CddMlc_VccxLine_Fault(void);


//-----------------------------------------------------------------------------
/// \brief  CddMlc_CheckPowerUp
///
/// \descr  Introduce some delay until the HSS2 output became stable
///         before starting the initialization sequence of the MLC driver.
///         This function checks if pwoer is stable and MLC can operate
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddMlc_CheckPowerUp(void)
{
  STATIC_UT(uint8,  CddMlc_ucPowerUpGuard, 0u);
  const boolean boVCCXFault = CddMlc_VccxLine_Fault();
  /* if MLC is powered up, introduce power up delay to become stable */
  if (((CDDMLC_IS_VCCX_POWERED != FALSE) && (boVCCXFault == FALSE )) && (CddMlc_boMlcPoweredUP == FALSE))
  {

    if (CddMlc_ucPowerUpGuard >= CDDMLC_POWERUP_CYCLE_GUARD)
    {
      CddMlc_boMlcPoweredUP = TRUE;
    }

    //increment delay
    CddMlc_ucPowerUpGuard++;
  }


  /*  reset flags if loss of power occurs */
  if ((CDDMLC_IS_VCCX_POWERED == FALSE) || (boVCCXFault != FALSE))
  {
    CddMlc_boMlcPoweredUP = FALSE;
    CddMlc_ucPowerUpGuard = 0u;
  }

  return CddMlc_boMlcPoweredUP;

}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_IsMlcPowered
///
/// \descr  The function returns the MLC power status (TRUE - HSS is stable,
///         FALSE - HSS is not powered or stable)
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddMlc_IsMlcPowered(void)
{
  return  CddMlc_boMlcPoweredUP;
}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_SetTarget
///
/// \descr  This function calls the correct function to set PWMs to the assigned
///         MLC device type
///
/// \param  ucChipConnected
/// \param  psTargetPWM
///
/// \return void
//-----------------------------------------------------------------------------
void CddMlc_SetTarget(uint8 ucChipConnected, tsCddMlcTarget* psTargetPWM)
{
  CddMlc_sTarget = *psTargetPWM;
  
  switch (ucChipConnected)
  {
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A:
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A:
    for (uint8 ucDevNbr = 0u; ucDevNbr < CDDMLC_CFG_MAX_CHIPS; ucDevNbr++)
    {
      CDDMLC_DRV_GEN2_SetDutyCycle(ucDevNbr, &CddMlc_sTarget.aunDutyCycle_1_1024[ucDevNbr][0]);
    }
    break;

  case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664:
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665:
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667:
    for (uint8 ucDevNbr = 0u; ucDevNbr < CDDMLC_CFG_MAX_CHIPS; ucDevNbr++)
    {
      CDDMLC_DRV_GEN3_SetDutyCycle(ucDevNbr, &CddMlc_sTarget.aunDutyCycle_1_1024[ucDevNbr][0]);
    }
    break;

  case CDDMLC_COD_MATRIX_TYPE_TPSGENx_1:
  case CDDMLC_COD_MATRIX_TYPE_TPSGENx_2:
    for (uint8 ucDevNbr = 0u; ucDevNbr < CDDMLC_CFG_MAX_CHIPS; ucDevNbr++)
    {
      CDDMLC_DRV_GEN2_SetDutyCycle(ucDevNbr, &CddMlc_sTarget.aunDutyCycle_1_1024[ucDevNbr][0]);
      CDDMLC_DRV_GEN3_SetDutyCycle(ucDevNbr, &CddMlc_sTarget.aunDutyCycle_1_1024[ucDevNbr][0]);
    }
    break;

  default:
    break;
  }

}

//-----------------------------------------------------------------------------
/// \brief  CddMlc_GetStatus
///
/// \descr  The function collects all types of errors detected by the MLC modules
///         and saves their status
///
/// \param  ucMtxCfgType  : get from coding (TPSGEN2/TPSGEN2_3A/TPSGEN3/TPSGENx)
/// \param  *psStatus     : store the MLCs faults statuses
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
void CddMlc_GetStatus(uint8 ucMtxCfgType, tsCddMlcStatus *psStatus)
{
  //Get Data from underliying module
  psStatus->boVccXFault = (CddMlc_boMlcPoweredUP == FALSE) ? TRUE : FALSE; //only for debug
  switch (ucMtxCfgType)
  {
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A:
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A:
    psStatus->boBusFault = CddMlcTPS92662_GetDeviceStatusFault(psStatus->aboComFault);
    CddMlcTPS92662_GetDeviceCrcFault(psStatus->aboCrcFault);
    CddMlcTPS92662_GetSwitchsFault(psStatus->asSwitchFault);
    CddMlcTPS92662_GetSensorInfo(psStatus->asSensorData);
    psStatus->ucPowerOnReset = CDDMLC_DRV_GEN2_GetPWRStatus();
    psStatus->boInitStatus = CDDMLC_DRV_GEN2_IsDrvInit();
    break;
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664:
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665:
  case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667:
    psStatus->boBusFault = CddMlcTPS92664_GetDeviceStatusFault(psStatus->aboComFault);
    CddMlcTPS92664_GetDeviceCrcFault(psStatus->aboCrcFault);
    CddMlcTPS92664_GetSwitchsFault(psStatus->asSwitchFault);
    CddMlcTPS92664_GetSensorInfo(psStatus->asSensorData);
    psStatus->ucPowerOnReset = CDDMLC_DRV_GEN3_GetPWRStatus();
    psStatus->boInitStatus = CDDMLC_DRV_GEN3_IsDrvInit();
    break;
  case CDDMLC_COD_MATRIX_TYPE_TPSGENx_1:
  case CDDMLC_COD_MATRIX_TYPE_TPSGENx_2:
    CddMlcTPS9266x_GetSwitchsFault(psStatus->asSwitchFault);
    psStatus->boBusFault = CddMlcTPS9266x_GetDeviceStatusFault(psStatus->aboComFault);
    CddMlcTPS9266x_GetDeviceCrcFault(psStatus->aboCrcFault);
    CddMlcTPS9266x_GetSensorInfo(psStatus->asSensorData);
    psStatus->ucPowerOnReset = CddMlcTps92662x_GetPowerOnReset();
    psStatus->boInitStatus = CddMlcTPS9266x_GetDeviceInit();
    break;
  default:
    break;
  }

} //PRQA S 5324 1 // compactness and readability

 //-----------------------------------------------------------------------------
/// \brief CddMlc_CheckReinit
///
/// \descr This function calls the correct function to reset the matrix to the assigned
///         MLC device type
///
/// \param  ucMtxCfgType
/// \param  boCmdStatus
///
/// \return 
//-----------------------------------------------------------------------------
void CddMlc_CheckReinit(uint8 ucMtxCfgType, boolean boCmdStatus)
 {
   switch (ucMtxCfgType)
   {
   case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A:
   case CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A:
     CDDMLC_DRV_GEN2_ReinitMatrix(boCmdStatus);
     break;
   case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664:
   case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665:
   case CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667:
     CDDMLC_DRV_GEN3_ReinitMatrix(boCmdStatus);
     break;
   case CDDMLC_COD_MATRIX_TYPE_TPSGENx_1:
   case CDDMLC_COD_MATRIX_TYPE_TPSGENx_2:
     CDDMLC_DRV_GEN2_ReinitMatrix(boCmdStatus);
     CDDMLC_DRV_GEN3_ReinitMatrix(boCmdStatus);
     break;
   default:
     break;
   }
 }

 //-----------------------------------------------------------------------------
/// \brief  CddMlcTPS92662_GetSwitchsFault
/// 
/// \descr  The function collects the pixel fault for GEN2
///
/// \param  psSwitchFault
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlcTPS92662_GetSwitchsFault(tsSwitchFault *psSwitchFault)
 {
   for (uint8 ucIdx = 0u; ucIdx < CDDMLC_CFG_MAX_CHIPS; ucIdx++)
   {
     psSwitchFault[ucIdx].unSwitchFault_Bit = CDDMLC_DRV_GEN2_IsShortToGnd(ucIdx);
   }
 }

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS92664_GetSwitchsFault
///
/// \descr  The function collects the pixel fault for GEN3
///
/// \param  psSwitchFault
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlcTPS92664_GetSwitchsFault(tsSwitchFault *psSwitchFault)
{
  for (uint8 ucIdx = 0u; ucIdx < CDDMLC_CFG_MAX_CHIPS; ucIdx++)
  {
    psSwitchFault[ucIdx].unSwitchFault_Bit = CDDMLC_DRV_GEN3_IsShortToGnd(ucIdx);
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS9266x_GetSwitchsFault
///
/// \descr  This function collects the pixel fault status of the assigned
///         MLC device type
///
/// \param  psSwitchFault
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlcTPS9266x_GetSwitchsFault(tsSwitchFault* psSwitchFault)
{
  for (uint8 ucDevId = 0u; ucDevId < CDDMLC_CFG_MAX_CHIPS; ucDevId++)
  {
    //clear each error status
    psSwitchFault[ucDevId].unSwitchFault_Bit = 0u;

    if (CDDMLC_DRV_IsGEN2(ucDevId) != FALSE)
    {
      psSwitchFault[ucDevId].unSwitchFault_Bit = CDDMLC_DRV_GEN2_IsShortToGnd(ucDevId);
    }

    if (CDDMLC_DRV_IsGEN3(ucDevId) != FALSE)
    {
      psSwitchFault[ucDevId].unSwitchFault_Bit = CDDMLC_DRV_GEN3_IsShortToGnd(ucDevId);
    }

  }
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS92662_GetSensorInfo
///
/// \descr  The function collects the ADC results for GEN2
///
/// \param  psSensorData
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlcTPS92662_GetSensorInfo(tsCddMlc_SensorData *psSensorData)
{
  for (uint8 ucIdx = 0u; ucIdx < CDDMLC_CFG_MAX_CHIPS; ucIdx++)
  {
    CDDMLC_DRV_GEN2_GetSensorInfo(ucIdx, &psSensorData[ucIdx]);
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS92664_GetSensorInfo
///
/// \descr  The function collects the ADC results for GEN3
///
/// \param  psSensorData
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlcTPS92664_GetSensorInfo(tsCddMlc_SensorData* psSensorData)
{
  for (uint8 ucIdx = 0u; ucIdx < CDDMLC_CFG_MAX_CHIPS; ucIdx++)
  {
    CDDMLC_DRV_GEN3_GetSensorInfo(ucIdx, &psSensorData[ucIdx]);
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS9266x_GetSensorInfo
///
/// \descr  This function collects the ADC result data of the assigned
///         MLC device type
///
/// \param  psSensorData
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlcTPS9266x_GetSensorInfo(tsCddMlc_SensorData* psSensorData)
{
  for (uint8 ucDevId = 0u; ucDevId < CDDMLC_CFG_MAX_CHIPS; ucDevId++)
  {
    if (CDDMLC_DRV_IsGEN2(ucDevId) != FALSE)
    {
      CDDMLC_DRV_GEN2_GetSensorInfo(ucDevId, &psSensorData[ucDevId]);
    }

    if (CDDMLC_DRV_IsGEN3(ucDevId) != FALSE)
    {
      CDDMLC_DRV_GEN3_GetSensorInfo(ucDevId, &psSensorData[ucDevId]);
    }

  }
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTps92662x_GetPowerOnReset
///
/// \descr  This function collects the PWR bit status of the assigned
///         MLC device type
///
/// \param  -
///
/// \return STATIC_AL uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 CddMlcTps92662x_GetPowerOnReset(void)
{
  uint8 ucGEN2_PWR = 0u, ucGEN3_PWR = 0u;

  ucGEN2_PWR = CDDMLC_DRV_GEN2_GetPWRStatus();

  ucGEN3_PWR = CDDMLC_DRV_GEN3_GetPWRStatus();

  return (ucGEN2_PWR | ucGEN3_PWR);
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS92662_GetDeviceStatusFault
///
/// \descr  This function collects the device communication error status of the 
///         assigned GEN2 devices and returns the bus error fault status
///
/// \param  pboComFault : device error comm status
///
/// \return STATIC_AL boolean : bus error status
//-----------------------------------------------------------------------------
STATIC_AL boolean CddMlcTPS92662_GetDeviceStatusFault(boolean* pboComFault)
 {
   uint8 ucCnt = 0u;
   boolean boComBrokenGen2 = FALSE;

   if (CDDMLC_Para_GEN2_CNT_DEVS != 0U)
   {
     for (uint8_fast ucIdx = 0u; ucIdx < CDDMLC_CFG_MAX_CHIPS; ucIdx++)
     {
       pboComFault[ucIdx] = CDDMLC_DRV_GEN2_IsComFault(ucIdx);
       ucCnt = (pboComFault[ucIdx] != FALSE) ? ucCnt + 1u : ucCnt;
     }

     boComBrokenGen2 = (ucCnt != 0u && ucCnt == CDDMLC_Para_GEN2_CNT_DEVS) ? TRUE : FALSE;
   }

   return boComBrokenGen2;
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS92664_GetDeviceStatusFault
///
/// \descr  This function collects the device communication error status of the 
///         assigned GEN3 devices and returns the bus error fault status
///
/// \param  pboComFault : device error comm status
///
/// \return STATIC_AL boolean : bus error status
//-----------------------------------------------------------------------------
STATIC_AL boolean CddMlcTPS92664_GetDeviceStatusFault(boolean* pboComFault)
{
  uint8 ucCnt = 0u;
  boolean boComBrokenGen3 = FALSE;

  if (CDDMLC_Para_GEN3_CNT_DEVS != 0U)
  {
    for (uint8_fast ucIdx = 0u; ucIdx < CDDMLC_CFG_MAX_CHIPS; ucIdx++)
    {
      pboComFault[ucIdx] = CDDMLC_DRV_GEN3_IsComFault(ucIdx);
      ucCnt = (pboComFault[ucIdx] != FALSE) ? ucCnt + 1u : ucCnt;
    }

    boComBrokenGen3 = (ucCnt != 0u && ucCnt == CDDMLC_Para_GEN3_CNT_DEVS) ? TRUE : FALSE;
  }

  return boComBrokenGen3;
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS9266x_GetDeviceStatusFault
///
/// \descr  This function collects the device communication error status of the 
///         assigned MLC device type and returns the bus error fault status
///
/// \param  pboComFault : device error comm status
///
/// \return STATIC_AL boolean : bus error status
//-----------------------------------------------------------------------------
STATIC_AL boolean CddMlcTPS9266x_GetDeviceStatusFault(boolean* pboComFault)
{
  uint8 ucCnt[2] = { 0u, 0u };
  boolean boComBrokenGenX = FALSE;

  for (uint8 ucDevId = 0u; ucDevId < CDDMLC_CFG_MAX_CHIPS; ucDevId++)
  {
    //clear each error status
    pboComFault[ucDevId] = FALSE;

    if (CDDMLC_DRV_IsGEN2(ucDevId) != FALSE)
    {
      pboComFault[ucDevId] = CDDMLC_DRV_GEN2_IsComFault(ucDevId);
      ucCnt[0] = (pboComFault[ucDevId] != FALSE) ? ucCnt[0] + 1u : ucCnt[0];
    }

    if (CDDMLC_DRV_IsGEN3(ucDevId) != FALSE)
    {
      pboComFault[ucDevId] = CDDMLC_DRV_GEN3_IsComFault(ucDevId);
      ucCnt[1] = (pboComFault[ucDevId] != FALSE) ? ucCnt[1] + 1u : ucCnt[1];
    }

  }

  boComBrokenGenX   = (ucCnt[0] != 0u && ucCnt[0] == CDDMLC_Para_GEN2_CNT_DEVS) ? TRUE : FALSE;
  boComBrokenGenX  &= (ucCnt[1] != 0u && ucCnt[1] == CDDMLC_Para_GEN3_CNT_DEVS) ? TRUE : FALSE;

  return boComBrokenGenX;
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS92664_GetDeviceStatusFault
///
/// \descr  This function collects the device crc error status of the 
///         assigned GEN3 devices and returns the crc error fault status
///
/// \param  pboCrcFault : device error crc status
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlcTPS92664_GetDeviceCrcFault(boolean* pboCrcFault)
{
  if (CDDMLC_Para_GEN3_CNT_DEVS != 0U)
  {
    for (uint8_fast ucIdx = 0u; ucIdx < CDDMLC_CFG_MAX_CHIPS; ucIdx++)
    {
      pboCrcFault[ucIdx] = CDDMLC_DRV_GEN3_IsCrcFault(ucIdx);
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS92662_GetDeviceStatusFault
///
/// \descr  This function collects the device crc error status of the 
///         assigned GEN2 devices and returns the crc error fault status
///
/// \param  pboCrcFault : device error crc status
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddMlcTPS92662_GetDeviceCrcFault(boolean* pboCrcFault)
{
  if (CDDMLC_Para_GEN2_CNT_DEVS != 0U)
  {
    for (uint8_fast ucIdx = 0u; ucIdx < CDDMLC_CFG_MAX_CHIPS; ucIdx++)
    {
      pboCrcFault[ucIdx] = CDDMLC_DRV_GEN2_IsCrcFault(ucIdx);
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS9266x_GetDeviceStatusFault
///
/// \descr  This function collects the device communication error status of the 
///         assigned MLC device type and returns the bus error fault status
///
/// \param  pboComFault : device error comm status
///
/// \return STATIC_AL boolean : bus error status
//-----------------------------------------------------------------------------
STATIC_AL void CddMlcTPS9266x_GetDeviceCrcFault(boolean* pboCrcFault)
{
  for (uint8 ucDevId = 0u; ucDevId < CDDMLC_CFG_MAX_CHIPS; ucDevId++)
  {
    //clear each error status
    pboCrcFault[ucDevId] = FALSE;

    if (CDDMLC_DRV_IsGEN2(ucDevId) != FALSE)
    {
      pboCrcFault[ucDevId] = CDDMLC_DRV_GEN2_IsCrcFault(ucDevId);
    }

    if (CDDMLC_DRV_IsGEN3(ucDevId) != FALSE)
    {
      pboCrcFault[ucDevId] = CDDMLC_DRV_GEN3_IsCrcFault(ucDevId);
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddMlcTPS9266x_GetDeviceInit
///
/// \descr  This function returns the initialization completed status of the
///         mixed configuration
///
/// \param  void 
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddMlcTPS9266x_GetDeviceInit(void)
{
    //clear each error status
    const boolean boGen2Init = CDDMLC_DRV_GEN2_IsDrvInit();
    const boolean boGen3Init = CDDMLC_DRV_GEN3_IsDrvInit();
    return ((boGen2Init != FALSE) && (boGen3Init != FALSE)) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  CddMlc_VccxLine_Fault
///
/// \descr  This function returns the status fault for VCCX line
///
/// \param  void 
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddMlc_VccxLine_Fault(void)
{
  teRte_VccxLineState eVccxLineState;
  CDDMLC_GET_VCCX_FAULT(&eVccxLineState);
  //return true only when a short to gnd or short to vbat are met
  return ((eVccxLineState == eVccx_Short2GND) || (eVccxLineState == eVccx_Short2Vbat)) ? TRUE : FALSE;
}
