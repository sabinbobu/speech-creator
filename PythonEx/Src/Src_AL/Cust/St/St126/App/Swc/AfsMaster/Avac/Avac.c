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
/// \file  Avac.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Alf Traulsen  (taf2rt)
///         mailTo:alf.traulsen[at]al-lighting.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Swc/AfsMaster/Avac/AvacData.h>
#include "Avac.h"
#include "AvacVdd.h"
#include "AvacAlg.h"
#include <Nvm.h>


//=============================================================================
// Functions
//=============================================================================

STATIC_AL void Avac_CheckZeroLvl(void);

//-----------------------------------------------------------------------------
/// \brief Avac_CheckZeroLvl
///
/// \descr Checks and sets DTC for zero level programming
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Avac_CheckZeroLvl(void)
{
  // Set DTC for Zero Level Programming
  if (NvmBlockDeltaPwmPara.ucZeroLevProg != 0xFFu)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)ZERO_LVL_PROG, DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)ZERO_LVL_PROG, DEM_EVENT_STATUS_PASSED);
  }
}

//-----------------------------------------------------------------------------
/// \func   Avac_ParaChanged()
///
/// \brief  Avac coding parameters changed
///
/// \param  - 
///
/// \return void
//-----------------------------------------------------------------------------
void Avac_ParaChanged(void)
{
  if (AvacData_GetCodingValid() != FALSE)
  {
    AvacData_Init();
    AvacVdd_Init();
    AvacAlg_Init();
  }
}

//-----------------------------------------------------------------------------
/// \brief  Avac_Init
///
/// \descr  initialize avac
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void Avac_Init(void)
{
  tsRteCodingParameters sCodingParameters;
  (void)Rte_Read_CodM_CtrlStp_Para(&sCodingParameters);

  if (AvacData_GetCodingValid() != FALSE)
  {
    AvacData_Init();
    AvacVdd_Init();
    AvacAlg_Init();
    AvacData_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);
  }
}


// ---------------------------------------------------------------------------
///
///  \func     Avac_Cycle0
///
///  \brief    cyclic function called every 20ms
///
///  \param    none
///
///  \return   none
///
// ---------------------------------------------------------------------------
void Avac_Cycle0(void)
{
  if (AvacData_GetCodingValid() != FALSE)
  {
    if (Cod_AvacStpEnable() == 1u)
    {
      Avac_CheckZeroLvl();
    }
    else
    {
      Rte_Call_DemPrj_ReportErrorStatus((uint16)ZERO_LVL_PROG, DEM_EVENT_STATUS_PASSED);
    }
    AvacVdd_DetectStreetQuality();
    AvacAlg_Add_Main();

    AvacVdd_DetectVehicleDynamic();
    AvacAlg_Main();
  }
  
  // Check and report zero lvl prog error
  //Avac_CheckZeroLvl();

}// PRQA S 5324 // HIS metrics violation : STCAL = 8

