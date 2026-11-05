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
#include <RteCommonTypes.h>
#include <CddLed.h>

//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================
Std_ReturnType Rte_Read_SysMon_TgtLedSig_sVal(tsRte_TgtLedSig0_ASIL* ppara1);
Std_ReturnType Rte_Read_CodM_CddLed_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CtrlLed_LedSettings_sVal(tsRte_ChLedSettings* ppara1);
Std_ReturnType Rte_Write_CddLed_LedState(const tsRte_LedStates* ppara1);
Std_ReturnType Rte_Write_CddLed_Status(const tCddLedStatus* ppara1);
Std_ReturnType Rte_Write_CddLed_TgtLed_FaultStatus_ASIL(const tsRte_TgtLedSig0_FaultStatus_ASIL* ppara1);

boolean        SysMonCheck_Data_IsTurnIndicatorFuSa(uint8 ucFuSaIdx);
uint8          Crc_CalculateCRC8H2F(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint8  StartValue8);
uint32         LPTMR0_GetTimeElapsed(const uint32 ulStartValue);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern tsRte_TgtLedSig0_ASIL Rte_Read_SysMon_TgtLedSig_sVal_Param1;
extern tsRteCodingParameters Rte_Read_CodM_CddLed_Para_Param1;
extern tsRte_ChLedSettings   Rte_Read_CtrlLed_LedSettings_sVal_Param1;
extern tsRte_LedStates       Rte_Write_CddLed_LedState_Param1;
extern tCddLedStatus         Rte_Write_CddLed_Status_Param1;
extern tsRte_TgtLedSig0_FaultStatus_ASIL Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_Param1;
extern uint8                 SysMonCheck_Data_IsTurnIndicatorFuSa_Param1;

extern uint8*                Crc_CalculateCRC8H2F_Param1;
extern uint32                Crc_CalculateCRC8H2F_Param2;
extern uint8                 Crc_CalculateCRC8H2F_Param3;
extern uint32                LPTMR0_GetTimeElapsed_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern Std_ReturnType  Rte_Read_SysMon_TgtLedSig_sVal_RetVal;
extern Std_ReturnType  Rte_Read_CodM_CddLed_Para_RetVal;
extern Std_ReturnType  Rte_Read_CtrlLed_LedSettings_sVal_RetVal;
extern Std_ReturnType  Rte_Write_CddLed_LedState_RetVal;
extern Std_ReturnType  Rte_Write_CddLed_Status_RetVal;
extern Std_ReturnType  Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_RetVal;
extern boolean         SysMonCheck_Data_IsTurnIndicatorFuSa_RetVal;
extern uint8           Crc_CalculateCRC8H2F_RetVal;
extern uint32          LPTMR0_GetTimeElapsed_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8 Rte_Read_SysMon_TgtLedSig_sVal_HitCount;
extern uint8 Rte_Read_CodM_CddLed_Para_HitCount;
extern uint8 Rte_Read_CtrlLed_LedSettings_sVal_HitCount;
extern uint8 Rte_Write_CddLed_LedState_HitCount;
extern uint8 Rte_Write_CddLed_Status_HitCount;
extern uint8 Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_HitCount;
 
extern uint8   SysMonCheck_Data_IsTurnIndicatorFuSa_HitCount;
extern uint8   Crc_CalculateCRC8H2F_HitCount;
extern uint8   LPTMR0_GetTimeElapsed_HitCount;


#endif // TEST_STUBS_2023_08_25_H_
