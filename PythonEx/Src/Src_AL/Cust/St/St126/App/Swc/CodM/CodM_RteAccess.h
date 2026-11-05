#ifndef __CODM_RTE_ACCESS_H__
#define __CODM_RTE_ACCESS_H__

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
/// \file   CodM_RteAccess.h
///
/// \brief  Header which contains the wrappers for the communication with
///         the RTE.
///
/// \author Cretu Vlad (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <RteCommonTypes.h>
#endif // !UNIT_TEST


#include <AL_Helper.h>
#include <CodM_Types.h>



//=============================================================================
// function prototypes
//=============================================================================
// To be used
//teCodM_HandTraffic CodM_RteAccess_GetTouristMState(void);
void roCodM_RteAccess_GetMinBrightnessParamsValidity(tsRte_CodMinBrightness_Param* const sMinBrParam);
uint32 CodM_RteAccess_CalculateCrc32(CONST_AL uint8* CONST_AL pucData, uint16 unLength, uint32 ulCrc_StartVal);

//=============================================================================
// inline functions
//=============================================================================
// To be used
//read
//LOCAL_INLINE Std_ReturnType CodM_RteAccess_Read_CodM_SteeringWheel_Side_Info(const tsRte_HandTraffic *pdata)
//{
//  return Rte_Read_SigPrep_HandTraffic_Port((void*)pdata);
//}
//
////write
//LOCAL_INLINE Std_ReturnType CodM_RteAccess_Write_CodM_Calibration(const teRte_CodM_eHeadLampType *pdata)
//{
//  return Rte_Write_CodM_Calibration_Type((const void*)pdata);      
//}

//// Get CRC status for calibration data segment
//LOCAL_INLINE boolean CodM_RteAccess_GetCalibCrcStatus(void)
//{
//  return Rte_Call_SysCrc_RomSegs_GetCalibCrcStatus();
//}
//
//// Get CRC status for PAV data segment
//LOCAL_INLINE boolean CodM_RteAccess_GetPavCrcStatus(void)
//{
//  return Rte_Call_SysCrc_RomSegs_GetPavCrcStatus();
//}
//
//// Report error status
//LOCAL_INLINE void CodM_RteAccess_ReportErrorStatus(uint16 unAlecId, uint8 ucTestStatus)
//{
//  Rte_Call_DemPrj_ReportErrorStatus(unAlecId, ucTestStatus);
//}
//
////----------------------------------------- Para Functions -----------------------------------------------------//
//
//LOCAL_INLINE void CodM_RteAccess_roAppM_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAppM_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roSensT_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roSensT_ParaFct0(eCmd, pData);
//}

//LOCAL_INLINE void CodM_RteAccess_roCtrlLed_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  CODM_RTE_SE_CTRLLED_PARA_DATA(eCmd, pData);
//}

//LOCAL_INLINE void CodM_RteAccess_roFctR_ParaFct0(tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  CODM_RTE_SE_FCTR0_PARA_DATA(eCmd, pData)
//}

//LOCAL_INLINE void CodM_RteAccess_roCtrlPxl_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roCtrlPxl_ParaFct0(eCmd, pData);
//}

//LOCAL_INLINE void CodM_RteAccess_roRSens_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roRSens_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roCtrlFan_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roCtrlFan_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roCtrlStp_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roCtrlStp_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roSysVolt_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roSysVolt_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roCddStp_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roCddStp_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roCddLed_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roCddLed_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAfsAw_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAfsAw_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAfsCr_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAfsCr_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAfsHb_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAfsHb_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAfsAiming_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAfsAiming_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAfsLgtFctMgr_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAfsLgtFctMgr_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAfsLmt_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAfsLmt_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAfsMnvr_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAfsMnvr_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAfsSbl_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAfsSbl_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAfsTi_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAfsTi_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roAppDbl_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roAppDbl_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roVddHld_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roVddHld_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roCanErr_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roCanErr_ParaFct0(eCmd, pData);
//}
//
//LOCAL_INLINE void CodM_RteAccess_roEcuM_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  Rte_Call_roEcuM_ParaFct0(eCmd, pData);
//}

#endif // __CODM_RTE_ACCESS_H__

// EOF
