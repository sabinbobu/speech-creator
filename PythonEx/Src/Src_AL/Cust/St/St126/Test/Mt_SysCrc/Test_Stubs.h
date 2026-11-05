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
#include <CddDma.h>
#include <SysCrc_reg_stubs.h>
#include <RteCommonTypes.h>

//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================

void SysCrc_RomSegs_CallbackFunction_Callback(void);
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
void EcuM_FlashCrcFailure_Indication(void);
void CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback);
uint32_t CRC_DRV_GetCrcResult(uint32_t instance);
boolean CddDma_IsJobCompleted(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName);
void CRC_SetSeedReg(CRC_Type * const base, uint32 seedValue);
status_t CRC_DRV_Init(uint32 instance, const crc_user_config_t * userConfigPtr);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern uint16                                    Dem_SetEventStatus_Output_Param1;
extern uint8                                     Dem_SetEventStatus_Output_Param2;
extern CddDma_DynConfig_DmaChannelName_EnumType  CddDma_StartJob_Param1;
extern CONST_AL tsCddDma_Parameter*              CddDma_StartJob_Param2;
extern CddDma_tfpCallback                        CddDma_StartJob_Param3;
extern uint32_t                                  CRC_DRV_GetCrcResult_Param1;
extern CddDma_DynConfig_DmaChannelName_EnumType  CddDma_IsJobCompleted_Param1;
extern CRC_Type *                                CRC_SetSeedReg_Param1;
extern uint32                                    CRC_SetSeedReg_Param2;
extern uint32                                    CRC_DRV_Init_Param1;
extern crc_user_config_t*                        CRC_DRV_Init_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern uint32_t   CRC_DRV_GetCrcResult_RetVal;
extern boolean  CddDma_IsJobCompleted_RetVal;
extern status_t CRC_DRV_Init_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 SysCrc_RomSegs_CallbackFunction_Callback_HitCount;
extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 EcuM_FlashCrcFailure_Indication_HitCount;
extern uint8 CddDma_StartJob_HitCount;
extern uint8 CRC_DRV_GetCrcResult_HitCount;
extern uint8 CddDma_IsJobCompleted_HitCount;
extern uint8 CRC_SetSeedReg_HitCount;
extern uint8 CRC_DRV_Init_HitCount;


#endif // TEST_STUBS_2023_08_25_H_
