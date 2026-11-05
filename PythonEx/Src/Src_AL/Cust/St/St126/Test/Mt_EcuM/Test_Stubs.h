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

#include <Std_Types.h>
#include <EcuM.h>
#include <CddDma.h>
#include <CddSpi.h>
#include <CddBoost.h>
#include <CddSbc.h>
#include <UtilMath.h>
#include <RteCommonTypes.h>
#include <ErrCust.h>
#include <Pwm.h>
#include <LPTMR.h>
#include <Adc.h>
#include <Pdb.h>
#include <Lpit.h>
#include <TrigMux.h>
#include <Wdg.h>
#include <Nvm.h>
#include <Fee.h>
#include <SysCrc.h>
#include <Util_Time.h>

//=============================================================================
// Typedefs
//=============================================================================

typedef uint8 IRQn_Type;
typedef enum
{
  LGM_TRUE = (uint8)0xAA,
  LGM_FALSE = (uint8)0x55
} LGM_BOOL;

typedef enum
{
  EcuM_DriverInitZero_InitFunction_Id,
  EcuM_DriverInitZero_Id_Count
}
EcuM_DriverInitZero_Id_List;

typedef enum
{
  EcuM_DriverInitOne_InitFunction_Id,
  EcuM_DriverInitOne_Id_Count
}
EcuM_DriverInitOne_Id_List;

typedef enum
{
  EcuM_Startup_Two_Trusted_InitFunction_Id,
  EcuM_Startup_Two_Trusted_Id_Count
}
EcuM_Startup_Two_Trusted_Id_List;

typedef enum
{
  EcuM_Startup_Two_NonTrusted_InitFunction_Id,
  EcuM_Startup_Two_NonTrusted_Id_Count
}
EcuM_Startup_Two_NonTrusted_Id_List;

typedef enum
{
  EcuM_Startup_Interrupt_interrupt_Enable_Id,
  EcuM_Startup_Interrupt_Enable_Id_Count
}
EcuM_Startup_Interrupt_Enable_Id_List;

typedef enum
{
  EcuM_Startup_Interrupt_interrupt_Cfg_Id,
  EcuM_Startup_Interrupt_Cfg_Id_Count
}
EcuM_Startup_Interrupt_Cfg_Id_List;

typedef enum
{
  EcuM_Startup_Interrupt_interrupt_Disable_Id,
  EcuM_Startup_Interrupt_Disable_Id_Count
}
EcuM_Startup_Interrupt_Disable_Id_List;

typedef enum SysMon_EnumSpeedState
{
  SysMon_Speed_0_State = 1U,
  SysMon_Speed_Drive_State = 2U,
  SysMon_Speed_Invalid_State = 3U
} SysMon_EnumSpeedState;

typedef enum SysMon_EnumLowBeamState
{
  SysMon_LowBeam_Valid_State = 1U,
  SysMon_LowBeam_Invalid_State = 2U
} SysMon_EnumLowBeamState;

typedef uint8_t   AppModeType;

/*typedef enum
{
  MCU_RESET_UNDEFINED,
  MCU_WATCHDOG_RESET,
  MCU_POWER_ON_RESET,
  MCU_STOP_ACKNOWLEDGE_ERROR_RESET,
  MCU_MDM_AP_SYSTEM_RESET_REQUEST,
  MCU_SOFTWARE_RESET,
  MCU_CORE_LOCKUP,
  MCU_JTAG_GENERATED_RESET,
  MCU_EXTERNAL_PIN_RESET,
  MCU_CMU_LOSS_OF_CLOCK_RESET,
  MCU_LOSS_OF_LOCK_RESET,
  MCU_LOSS_OF_CLOCK_RESET,
  MCU_LOW_VOLTAGE_DETECT_OR_HIGH_VOLTAGE_DETECT_RESET
}Mcu_ResetType;*/

typedef uint8 Mcu_ClockSpecificType;
typedef Mcu_ClockSpecificType Mcu_ClockType;

//=============================================================================
// Stub function declarations
//=============================================================================

void                    NvM_WriteAll(void);
void                    Mcu_PerformReset(void);
Std_ReturnType          NvM_GetErrorStatus(NvM_BlockIdType BlockId, NvM_RequestResultType *RequestResultPtr);
void                    Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
void                    Dem_Set_Init_Window(boolean boLevel);
void                    EcuM_GetMcuPrivilegeStatus(void);
void                    EcuM_UserSwitch(void);
void                    EcuM_PrivilegeSwitch(void);
void                    Dem_ClearStartUpStatus(void);
void                    WdgM_ResetShaDataResetReason(void);
void                    WdgM_SetLocalCheckPoint(uint8 ucId);
Std_ReturnType          Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1);
void                    SysMonRx_ComM_EnableCallbacks(void);
boolean                 SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam(void);
void                    SysMonTx_ComM_ActivateTxBufer(void);
void                    SysMonRx_ComM_DisableCallbacks(void);
SysMon_EnumSpeedState   SysMonRx_ASIL_GetSpeedState(void);
SysMon_EnumLowBeamState SysMonRx_ASIL_GetLowBeamState(void);
void                    SigPrepRx_ComM_EnableCallbacks(void);
void                    SigPrepTx_ComM_ActivateTxBufer(void);
void                    SigPrepTx_ComM_DeactivateTxBuffer(void);
void                    SysMonTx_ComM_DeactivateTxBuffer(void);
void                    SigPrepRx_ComM_DisableCallbacks(void);
void                    ENABLE_INTERRUPTS(void);
void                    CddSbc_SetWdgTimeoutModeAnd200ms(void);
void                    INT_SYS_SetPriority(IRQn_Type irqNumber, uint8_t priority);
void                    INT_SYS_EnableIRQ(IRQn_Type irqNumber);
void                    StartOS(AppModeType Mode);
boolean                 EcuM_EvaluateExternalWadgResetReason(void);
Std_ReturnType          Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType          Rte_Read_FctR_TiWarningMode(teRte_WarningMode* ppara1);
void                    StatM_Deinit(void);
void                    IoHwAbUser_InitGetMountingSide(void);
uint32                  Os_Get_BusFaultCnt(void);

Std_ReturnType          Rte_Read_SigPrep_SleepBSI(uint8* ppara1);
Std_ReturnType          Rte_Read_ElecInt_RequestRUN(uint8* ppara1);
Std_ReturnType          Rte_Read_ElecInt_ReleaseRUN(uint8* ppara1);
Std_ReturnType          Rte_Read_ElecInt_ReleasePOST_RUN(uint8* ppara1);
Std_ReturnType          Rte_Read_Diag_RequestPOST_RUN(uint8* ppara1);

Std_ReturnType          Rte_Write_MPU_ErrorCounter(uint32* ppara1);
Std_ReturnType          Rte_Write_EcuM_Deinit(boolean ppara1);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tieFeeState                             Fee_State;
extern MemIf_JobResultType                     Fee_JobResult;

extern teRte_WarningMode                       Rte_Read_FctR_TiWarningMode_Param1;
extern teRte_MountingSide                      Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern teRte_ReqLightState                     Rte_Read_SysMon_LowBeamCmd_Req_Param1;
extern uint8                                   WdgM_SetLocalCheckPoint_Param1;
extern Mcu_ClockType*                          Mcu_InitClock_Param1;
extern NvM_BlockIdType                         NvM_GetErrorStatus_Param1;
extern NvM_RequestResultType*                  NvM_GetErrorStatus_Param2;
extern CONST_AL sIcu_ConfigType*               Icu_Init_Param1;
extern CONST_AL tsAdc_CfgData* CONST_AL        Adc_Init_Param1;
extern CONST_AL tsPdb_CfgData* CONST_AL        Pdb_Init_Param1;
extern CONST_AL tsTrigMux_CfgData* CONST_AL    TrigMux_Init_Param1;
extern CONST_AL tsLpit_CfgData * CONST_AL      Lpit_Init_Param1;
extern tsRte_SysMonLgtFctsReq                  Rte_Read_SysMon_StdLgtFcts_Req_Param1;
extern tsRte_SysMonLgtTiReq                    Rte_Read_SysMon_StdLgtTi_Req_Param1;
extern uint32                                  LPTMR0_GetTimeElapsed_Param1;
extern uint16                                  Dem_SetEventStatus_Param1;
extern uint8                                   Dem_SetEventStatus_Param2;
extern boolean                                 Dem_Set_Init_Window_Param1;
extern IRQn_Type                               INT_SYS_SetPriority_Param1;
extern uint8_t                                 INT_SYS_SetPriority_Param2;
extern IRQn_Type                               INT_SYS_EnableIRQ_Param1;
extern AppModeType                             StartOS_Param1;
extern uint8   Rte_Read_SigPrep_SleepBSI_Param1;
extern uint8   Rte_Read_ElecInt_RequestRUN_Param1;
extern uint8   Rte_Read_ElecInt_ReleaseRUN_Param1;
extern uint8   Rte_Read_ElecInt_ReleasePOST_RUN_Param1;
extern uint8   Rte_Read_Diag_RequestPOST_RUN_Param1;
extern boolean Rte_Write_EcuM_Deinit_Param1;
extern uint32*  Rte_Write_MPU_ErrorCounter_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType          Rte_Read_FctR_TiWarningMode_RetVal;
extern Std_ReturnType          Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern SysMon_EnumLowBeamState SysMonRx_ASIL_GetLowBeamState_RetVal;
extern SysMon_EnumSpeedState   SysMonRx_ASIL_GetSpeedState_RetVal;
extern Std_ReturnType          Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
extern Std_ReturnType          Mcu_InitClock_RetVal;
extern Std_ReturnType          NvM_GetErrorStatus_RetVal;
extern uint32                  LPTMR0_GetTimeElapsed_RetVal;
extern Std_ReturnType          Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
extern Std_ReturnType          Rte_Read_SysMon_StdLgtTi_Req_RetVal;
extern bool                    Mcu_InitHasBeenCalled_RetVal;
extern Mcu_ResetType           Mcu_GetResetReason_RetVal;
extern boolean                 SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal;
extern Std_ReturnType          Rte_Read_SigPrep_SleepBSI_RetVal;
extern Std_ReturnType          Rte_Read_ElecInt_RequestRUN_RetVal;
extern Std_ReturnType          Rte_Read_ElecInt_ReleaseRUN_RetVal;
extern Std_ReturnType          Rte_Read_ElecInt_ReleasePOST_RUN_RetVal;
extern Std_ReturnType          Rte_Read_Diag_RequestPOST_RUN_RetVal;
extern uint32                  Os_Get_BusFaultCnt_RetVal;
extern uint32                  Rte_Write_MPU_ErrorCounter_RetVal;
extern Std_ReturnType          Rte_Write_EcuM_Deinit_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 Rte_Read_FctR_TiWarningMode_HitCount;
extern uint8 Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8 CddSbc_SetWdgTimeoutModeAnd200ms_HitCount;
extern uint8 ENABLE_INTERRUPTS_HitCount;
extern uint8 SigPrepRx_ComM_DisableCallbacks_HitCount;
extern uint8 SysMonTx_ComM_DeactivateTxBuffer_HitCount;
extern uint8 SigPrepTx_ComM_ActivateTxBufer_HitCount;
extern uint8 SigPrepTx_ComM_DeactivateTxBuffer_HitCount;
extern uint8 SigPrepRx_ComM_EnableCallbacks_HitCount;
extern uint8 SysMonRx_ASIL_GetLowBeamState_HitCount;
extern uint8 SysMonRx_ASIL_GetSpeedState_HitCount;
extern uint8 SysMonRx_ComM_DisableCallbacks_HitCount;
extern uint8 SysMonTx_ComM_ActivateTxBufer_HitCount;
extern uint8 SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount;
extern uint8 SysMonRx_ComM_EnableCallbacks_HitCount;
extern uint8 Rte_Read_SysMon_LowBeamCmd_Req_HitCount;
extern uint8 WdgM_SetLocalCheckPoint_HitCount;
extern uint8 WdgM_ResetShaDataResetReason_HitCount;
extern uint8 Dem_ClearStartUpStatus_HitCount;
extern uint8 Mcu_InitClock_HitCount;
extern uint8 Icu_Init_HitCount;
extern uint8 INT_SYS_SetPriority_HitCount;
extern uint8 INT_SYS_EnableIRQGlobal_HitCount;
extern uint8 INT_SYS_EnableIRQ_HitCount;
extern uint8 StartOS_HitCount;
extern uint8 NvM_GetErrorStatus_HitCount;
extern uint8 Nvm_WriteAll_HitCount;
extern uint8 Mcu_PerformReset_HitCount;
extern uint8 LPTMR0_GetTimeElapsed_HitCount;
extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 Dem_Set_Init_Window_HitCount;
extern uint8 Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
extern uint8 Rte_Read_SysMon_StdLgtTi_Req_HitCount;
extern uint8 CddBoost_Shutdown_HitCount;
extern uint8 CddSbc_SetSleepMode_HitCount;
extern uint8 riNvM_Init_HitCount;
extern uint8 CddSpi_Stop_HitCount;
extern uint8 NvM_MainFunction_HitCount;
extern uint8 NvM_ReadAll_HitCount;
extern uint8 riDem_Init_HitCount;
extern uint8 riErrCust_Init_HitCount;
extern uint8 CddStp_Tsp_Init_HitCount;
extern uint8 CddSpi_Init_HitCount;
extern uint8 CddSbc_Init_HitCount;
extern uint8 SysVolt_Init_HitCount;
extern uint8 riFee_Init_HitCount;
extern uint8 CddDma_Init_HitCount;
extern uint8 Mcu_InitHasBeenCalled_HitCount;
extern uint8 Mcu_GetResetReason_HitCount;
extern uint8 StatM_Deinit_HitCount;
extern uint8 IoHwAbUser_InitGetMountingSide_HitCount;
extern uint8 Rte_Read_SigPrep_SleepBSI_HitCount;
extern uint8 Rte_Read_ElecInt_RequestRUN_HitCount;
extern uint8 Rte_Read_ElecInt_ReleaseRUN_HitCount;
extern uint8 Rte_Read_ElecInt_ReleasePOST_RUN_HitCount;
extern uint8 Rte_Read_Diag_RequestPOST_RUN_HitCount;
extern uint8 Os_Get_BusFaultCnt_HitCount;
extern uint8 Rte_Write_MPU_ErrorCounter_HitCount;
extern uint8 Rte_Write_EcuM_Deinit_HitCount;

//=============================================================================
// Global variable stubs ( registers, global variables from other modules which are referenced in the module )
//=============================================================================

extern Mcu_ClockType	       Mcu_ClockData;
extern LGM_BOOL             NM_CAN_b_SleepBSIframe;
extern boolean              Mcu_boInitHasBeenCalled;


#endif // TEST_STUBS_2023_08_25_H_
