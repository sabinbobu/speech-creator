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
/// \file   Dbl_RteAccess.h
///
/// \brief  encapsule RTE access
///
/// \descr  Functions used for the Dbl RTE wrapper, for input/output 
///
///
/// \author Futo Henrietta-Helena F31185D
///         mail to <henrietta-helena.futo[at]magnetimarelli.com>
//-----------------------------------------------------------------------------
#ifndef DBL_RTE_ACCESS_2021_11_02_H_
#define DBL_RTE_ACCESS_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================

#include "Dbl_Types.h"
#include "DblData.h"
#include <RteCommonTypes.h>
#include <Cfg/Cfg.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif

//=============================================================================
// functions prototype
//=============================================================================

uint8                              Dbl_RteAccess_ReadDblCmd(void);
uint8                              Dbl_RteAccess_ReadVehicleModeConfig(void);
teDbl_EtatPrincipSEV               Dbl_RteAccess_ReadVESMainState(void);
tsDbl_VehNetState                  Dbl_RteAccess_ReadVehicleElectricState(void);
teDbl_TypeDir                      Dbl_RteAccess_ReadSteeringType(void);
teDbl_DynBendingBeamFault          Dbl_RteAccess_ReadDynBendingBeamFaultR(void);
teDbl_DynBendingBeamFault          Dbl_RteAccess_ReadDynBendingBeamFaultL(void);
tsDbl_SwivellingOut                Dbl_RteAccess_ReadDblOutput(void);
uint32                             Dbl_RteAccess_ReadSpeed(void);
boolean                            Dbl_RteAccess_ReadEnvCondition(void);
boolean                            Dbl_RteAccess_ReadReverseGearStatus(void);
void                               Dbl_RteAccess_WriteDblOutput(tsDbl_SwivellingOut nAngle, uint8 ucState, teDbl_eSubMode eMode);
void                               Dbl_RteAccess_WriteDriveSituation(uint8 ucDblDriveSit);
void                               Dbl_RteAccess_WriteSwimRate(tsDbl_SwiRateLimMsg sDblLimits);
teRte_SigQty                       Dbl_RteAccess_ReadCurvature(sint32* nCurvature);
void                               Dbl_RteAccess_Read_EcuSide(teDbl_MountingSide* eEcuSide);
void                               Dbl_RteAccess_WriteDblSysMonTx_FullStatus(boolean boFailureStatus);
void                               Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus(teDbl_MountingSide eSide, boolean boStatus);
teTraffic                          Dbl_RteAccess_ReadDblTrafficSide(void);
tsDbl_SwiRateLimMsg                Dbl_RteAccess_ReadSwimRate(void);
uint8                              Dbl_RteAccess_ReadGfhbCmd(void);
uint8                              Dbl_RteAccess_ReadFlashBeamCmd(void);
uint8                              Dbl_RteAccess_ReadHbCmd(void);
boolean                            Dbl_Read_PhaseVie(void);
tsDbl_YawSpeed                     Dbl_RteAccess_ReadYawSpeed(void);
tsDbl_SteeringWheelAngle           Dbl_RteAccess_ReadSteeringWheelAngle(void);
tsDbl_VehicleSpeed                 Dbl_RteAccess_ReadVehicleSpeed(void);
teDbl_SigQty                       Dbl_RteAccess_ReadEtatReseauElec(void);

#endif // DBL_RTE_ACCESS_2021_11_02_H_
