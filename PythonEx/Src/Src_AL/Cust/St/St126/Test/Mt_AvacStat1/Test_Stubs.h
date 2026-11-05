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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================

#include <AL_Helper.h>
#include <Rte/RteCommonTypes.h>
#include <Nvm.h>

//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================

void            Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
Std_ReturnType  NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
Std_ReturnType  Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1);
Std_ReturnType  Rte_Read_CtrlDcm_StatusParameters_Port(tsRte_CtrlDcmStatusParams* ppara1);
Std_ReturnType  Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType  Rte_Read_Pitch_Angle(tPitch0*                   ppara1);
Std_ReturnType  Rte_Read_CodM_Pitch_Para(tsRteCodingParameters*     ppara1);
Std_ReturnType  Rte_Write_AvacStat1_SpeedMode(const teRte_DcmSpeedMode*  ppara1);
Std_ReturnType  Rte_Write_ppsAvacStat1Out_Port(const tPositionOut*        ppara1);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern uint16                    Dem_SetEventStatus_Param1;
extern uint8                     Dem_SetEventStatus_Param2;
extern NvM_BlockIdType           NvM_WriteBlock_Param1;
extern void*                     NvM_WriteBlock_Param2;
extern tsRte_SigPrep_DynamicSigs Rte_Read_SigPrep_DynamicSigs_Param1;
extern tsRte_CtrlDcmStatusParams Rte_Read_CtrlDcm_StatusParameters_Port_Param1;
extern tsRte_SysMon_VehicleSpeed Rte_Read_SysMon_VehicleSpeed_Param1;
extern tPitch0                   Rte_Read_Pitch_Angle_Param1;
extern tsRteCodingParameters     Rte_Read_CodM_Pitch_Para_Param1;
extern teRte_DcmSpeedMode        Rte_Write_AvacStat1_SpeedMode_Param1;
extern tPositionOut              Rte_Write_ppsAvacStat1Out_Port_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType  NvM_WriteBlock_RetVal;
extern Std_ReturnType  Rte_Read_SigPrep_DynamicSigs_RetVal;
extern Std_ReturnType  Rte_Read_CtrlDcm_StatusParameters_Port_RetVal;
extern Std_ReturnType  Rte_Read_SysMon_VehicleSpeed_RetVal;
extern Std_ReturnType  Rte_Read_Pitch_Angle_RetVal;
extern Std_ReturnType  Rte_Read_CodM_Pitch_Para_RetVal;
extern Std_ReturnType  Rte_Write_AvacStat1_SpeedMode_RetVal;
extern Std_ReturnType  Rte_Write_ppsAvacStat1Out_Port_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 NvM_WriteBlock_HitCount;
extern uint8 Rte_Read_SigPrep_DynamicSigs_HitCount;
extern uint8 Rte_Read_CtrlDcm_StatusParameters_Port_HitCount;
extern uint8 Rte_Read_SysMon_VehicleSpeed_HitCount;
extern uint8 Rte_Read_Pitch_Angle_HitCount;
extern uint8 Rte_Read_CodM_Pitch_Para_HitCount;
extern uint8 Rte_Write_AvacStat1_SpeedMode_HitCount;
extern uint8 Rte_Write_ppsAvacStat1Out_Port_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
