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
/// \file  ctscEcuM.c
///
/// \brief EcuM Runnable functions
///
/// \Project LDMO
///
/// \Author Stefan Tyirean (f75617c) mailto: stefan.tyirean[a]marelli.com
///
/// \Date September 2021
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------
#include <Bsw/EcuM/EcuM.h>
#include <Bsw/EcuM/ctscEcuM.h>
#include <Bsw/Sys/Load/SysLoad.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif
//-----------------------------------------------------------------------------
// Sysload Tags
//-----------------------------------------------------------------------------
#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(rpEcuM_Cycle0)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  rpEcuM_Cycle0
///
/// \descr  EcuM cycle runable
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void rpEcuM_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpEcuM_Cycle0)
#endif

  EcuM_MainFunction();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpEcuM_Cycle0)
#endif
}

void reEcuM_RequestRUN(void)
{
    uint8 ucReq;
    (void)Rte_Read_ElecInt_RequestRUN(&ucReq);
    EcuM_RequestRUN(ucReq);
}

void reEcuM_ReleaseRUN(void)
{
    uint8 ucReq;
    (void)Rte_Read_ElecInt_ReleaseRUN(&ucReq);
    EcuM_ReleaseRUN(ucReq);
}

void reEcuM_ReleasePOST_RUN(void)
{
    uint8 ucReq;
    (void)Rte_Read_ElecInt_ReleasePOST_RUN(&ucReq);
    EcuM_ReleasePOST_RUN(ucReq);
}


void reEcuM_RequestPOST_RUN(void)
{
    uint8 ucReq;
    (void)Rte_Read_Diag_RequestPOST_RUN(&ucReq);
    EcuM_RequestPOST_RUN(ucReq);
}

void reEcuM_DiagResetRequest(void)
{
    EcuM_DiagResetRequest();
}

// EOF
