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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"

//=============================================================================
// Stub function parameter stubs
//=============================================================================

uint16                                    Dem_SetEventStatus_Output_Param1;
uint8                                     Dem_SetEventStatus_Output_Param2;
CddDma_DynConfig_DmaChannelName_EnumType  CddDma_StartJob_Param1;
CONST_AL tsCddDma_Parameter*              CddDma_StartJob_Param2;
CddDma_tfpCallback                        CddDma_StartJob_Param3;
uint32_t                                  CRC_DRV_GetCrcResult_Param1;
CddDma_DynConfig_DmaChannelName_EnumType  CddDma_IsJobCompleted_Param1;
CRC_Type *                                CRC_SetSeedReg_Param1;
uint32                                    CRC_SetSeedReg_Param2;
uint32                                    CRC_DRV_Init_Param1;
crc_user_config_t*                        CRC_DRV_Init_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

uint32_t   CRC_DRV_GetCrcResult_RetVal;
boolean  CddDma_IsJobCompleted_RetVal;
status_t CRC_DRV_Init_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 SysCrc_RomSegs_CallbackFunction_Callback_HitCount;
uint8 Dem_SetEventStatus_HitCount;
uint8 EcuM_FlashCrcFailure_Indication_HitCount;
uint8 CddDma_StartJob_HitCount;
uint8 CRC_DRV_GetCrcResult_HitCount;
uint8 CddDma_IsJobCompleted_HitCount;
uint8 CRC_SetSeedReg_HitCount;
uint8 CRC_DRV_Init_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief SysCrc_RomSegs_CallbackFunction_Callback
///
/// \descr Stub function created to verify that the SysCrc_RomSegs_CallbackFunction function correctly calls it's callback function
///
/// \param
///
/// \return void
//-----------------------------------------------------------------------------
void SysCrc_RomSegs_CallbackFunction_Callback(void)
{
  SysCrc_RomSegs_CallbackFunction_Callback_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Dem_SetEventStatus
///
/// \descr Stub function created to simulate the behaviour of Dem_SetEventStatus function
///
/// \param unAlecId
/// \param ucTestStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus)
{
  Dem_SetEventStatus_Output_Param1 = unAlecId;
  Dem_SetEventStatus_Output_Param2 = ucTestStatus;

  Dem_SetEventStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_FlashCrcFailure_Indication
///
/// \descr Stub function created to simulate the behaviour of EcuM_FlashCrcFailure_Indication function
///
/// \param
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_FlashCrcFailure_Indication(void)
{
  EcuM_FlashCrcFailure_Indication_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CddDma_StartJob
///
/// \descr Stub function created to simulate the behaviour of CddDma_StartJob function
///
/// \param eDmaChannelName
/// \param psParameter
/// \param fpCallback
///
/// \return void
//-----------------------------------------------------------------------------
void CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback)
{
  CddDma_StartJob_Param1 = eDmaChannelName;
  CddDma_StartJob_Param2 = psParameter;
  CddDma_StartJob_Param3 = fpCallback;

  CddDma_StartJob_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief CRC_DRV_GetCrcResult
///
/// \descr Stub function created to simulate the behaviour of CRC_DRV_GetCrcResult function
///
/// \param instance
///
/// \return uint32_t
//-----------------------------------------------------------------------------
uint32_t CRC_DRV_GetCrcResult(uint32_t instance)
{
  CRC_DRV_GetCrcResult_Param1 = instance;

  CRC_DRV_GetCrcResult_HitCount++;

  return CRC_DRV_GetCrcResult_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddDma_IsJobCompleted
///
/// \descr Stub function created to simulate the behaviour of CddDma_IsJobCompleted function
///
/// \param eDmaChannelName
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddDma_IsJobCompleted(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName)
{
  CddDma_IsJobCompleted_Param1 = eDmaChannelName;

  CddDma_IsJobCompleted_HitCount++;

  return  CddDma_IsJobCompleted_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CRC_SetSeedReg
///
/// \descr Stub function created to simulate the behaviour of CRC_SetSeedReg function
///
/// \param base
/// \param seedValue
///
/// \return void
//-----------------------------------------------------------------------------
void CRC_SetSeedReg(CRC_Type * const base, uint32 seedValue)
{
  CRC_SetSeedReg_Param1 = base;
  CRC_SetSeedReg_Param2 = seedValue;

  CRC_SetSeedReg_HitCount++;

}

//-----------------------------------------------------------------------------
/// \brief CRC_DRV_Init
///
/// \descr Stub function created to simulate the behaviour of CRC_DRV_Init function
///
/// \param instance
/// \param userConfigPtr
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t CRC_DRV_Init(uint32 instance, const crc_user_config_t * userConfigPtr)
{
  CRC_DRV_Init_Param1 = instance;
  CRC_DRV_Init_Param2 = userConfigPtr;

  CRC_DRV_Init_HitCount++;

}
