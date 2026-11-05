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
/// \file  CddSpi_CallOuts.c
///
/// \brief Impelementation of CddSpi User Call Outs
///        to handle  SPI Dynamic configuration and status fault
///
//-----------------------------------------------------------------------------
//=============================================================================
//  includes
//=============================================================================
#include <Std_Types.h>
#include <AL_Helper.h>
#include <CddSpi_CallOuts.h>
#include <CddSpi.h>
#include <CddSpi_Cfg.h>

#ifndef UNIT_TEST


#endif
//Eft definitions
#define CDDSPI_CALLOUT_STP_MAX                             3U
#define CDDSPI_CALLOUT_STP_ADDR_DATA_BYTE_INCRM            2U
#define CDDSPI_CALLOUT_STP_MOUNTED                         1U
//-----------------------------------------------------------------------------
/// \brief  CddSpi_GetEFTData
///
/// \descr  Get EFT Data structre and check its consistency
///
/// \param  psEFTDAta : Double Pointer to get EFT Data structure pointer
///
/// \return boolean
///           TRUE : EFT Data Valid
///           FALSE: EFT Data Invalid
//-----------------------------------------------------------------------------
STATIC_AL boolean CddSpi_GetEFTData(tieEftDataPtr* psEFTDAta)
{
  tieDataStatus  eDataStatus = tieDataStatus_Valid;
  tieEftDataPtr psEFTDataAddr;// = NULL_PTR;
  boolean        boRetVal = FALSE;
#ifdef UNIT_TEST
  (void)Rte_Read_ppCodMEftCrcStatus0_sVal(&eDataStatus);
#endif
  if (eDataStatus == tieDataStatus_Valid)
  {
#ifdef UNIT_TEST
    (void)Rte_Call_ppCodMEftData0_GetData(&psEFTDataAddr);
#endif
    if (psEFTDataAddr != NULL_PTR)
    {
      *psEFTDAta = psEFTDataAddr;

      boRetVal = TRUE;
    }
  }

  return boRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_GetStpConfig
///
/// \descr  Provides device population footprint to CddSpi
///         to handle transmissions with steppers (CddStp)
///
/// \param  punData: Data pointer to provide footprint
///
/// \return boolean
///           TRUE : Footprint data valid
///           FALSE: Footprint data iinnvalid
//-----------------------------------------------------------------------------
boolean CddSpi_GetStpConfig(uint16* punData)
{
  boolean        boRetVal = FALSE;
  tieEftDataPtr psEFTData = NULL_PTR;

  if (CddSpi_GetEFTData(&psEFTData) == TRUE)
  {
    uint8  ucStpMountedIdx = 0U;
    uint8* pucEftStpAdd = &(psEFTData->EFT_ECUVARCFG_STEPPER[0]);
    *punData = 0U;

    for (uint8 ucIdx = 0U; ucIdx < CDDSPI_CALLOUT_STP_MAX; ucIdx++)
    {

      if (*pucEftStpAdd != 0U)
      {
        *punData |= (uint16)((uint16)1U << ucStpMountedIdx);
        ucStpMountedIdx++;
      }

      pucEftStpAdd += CDDSPI_CALLOUT_STP_ADDR_DATA_BYTE_INCRM;
    }

    //If daisy chain configuration, additional element is needed (header)
    if (ucStpMountedIdx > 1U)
    {
      *punData |= (uint16)((uint16)1U << ucStpMountedIdx);
    }

    boRetVal = TRUE;
  }
  return boRetVal;
}

// the following "Task" functions not used in LDM
#if 0
STATIC_AL volatile boolean CddSpi_init = FALSE;
void TaskCddSpi_Cyclic_Func(void)
{
  if (CddSpi_init == FALSE)
  {
    CddSpi_Start();
    CddSpi_init = TRUE;
  }
  else
  {
    //empty
  }

  CddSpi_Cycle();
}

void TaskCddSpi_Cyclic_Init(void)
{
  CddSpi_Start();
}
#endif


#if (CDDSPI_STATUS_FAULT == STD_ON)
void CddSpi_StatusFault(uint8 ucData)
{

}
#endif

