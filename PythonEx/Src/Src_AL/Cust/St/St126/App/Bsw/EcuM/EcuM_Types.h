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
/// \file  EcuM_Types.h
///
/// \brief Ecu Manager types header file
///
/// \Project LDMO
///
/// \Author Alex Mertic mailto: alexandru-laurentiu.mertic@marelli.com
///
/// \Date June 2020
//-----------------------------------------------------------------------------
#ifndef ECU_M_2020_06_26_H_
#define ECU_M_2020_06_26_H_

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Mcu_TargetTypes.h>
#include <Std_Types.h>
#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif


//-----------------------------------------------------------------------------
// typedefs
//-----------------------------------------------------------------------------

typedef union
{
  struct
  {
    uint32 biMpuTest1_Res : 2;
    uint32 biMpuTest2_Res : 2;
    uint32 biMpuTest3_Res : 2;
    uint32 biMpuTest4_Res : 2;
    uint32 biMpuTest5_Res : 2;
    uint32 biMpuTest6_Res : 2;
    uint32 biMpuTest7_Res : 2;
    uint32 biMpuTest8_Res : 2;
    uint32 biMpuAllTests_Res : 2;
    uint32 biReserved : 14;
  }Bit;
  uint32 ulMpuTest_Result_Stat;
}tuEcuM_MpuSelf_Test_Res;

// Init callback type
typedef void(*tpInitFunction)(void);

// EcuM state type
typedef enum
{
  eEcuM_Undefined,
  eEcuM_Startup_One,
  eEcuM_Startup_Two,
  eEcuM_Startup,
  eEcuM_WakeUp,
  eEcuM_Up,
  eEcuM_App_Run,
  eEcuM_ShutDownPrep,
  eEcuM_ShutDown
}teEcuM_EcuState;

// Charge Pump state type
typedef enum
{
  eEcuM_ChargePump_NotEnabled,
  eEcuM_ChargePump_Enabled,
  eEcuM_ChargePump_Error
}teEcuM_ChargePumpState;

typedef struct
{
  uint8 ucInterrupt;
  uint8 ucPriority;
}tsEcuM_InterruptCfg;

typedef struct
{
  boolean boMPUErrorStatus;
  uint8 ucMPUErrorFlags;
  uint32 ulMPUAddressError[4];
  uint32 ulMPUDetailedError[4];
}tsEcuM_MPUSelfTestDetails;

typedef struct
{
  uint16 unEcc_DED_Reset;             //offset 0
  uint16 unReserved1;
  uint16 unMpu_Self_Test_Reset;       //offset 4
  uint16 unSBC_Wdg_Reset;             //offset 6
  uint16 unCRC_App_Reset;             //offset 8
  uint16 unClock_Cfg_Reset;           //offset A
  uint16 unEcc_Self_Test_Reset;       //offset C
  uint16 unMPU_Bus_Fault_Cnt;         //offset E
  uint16 unHardFaultSwLock;           //offset 10
}tsEcuM_EcuInternalErrors;

typedef union
{
  struct
  {
    uint32 biECC_DED_ResetReason : 1;
    uint32 biMPU_Self_Test_ResetReason : 1;
    uint32 biSBC_WDG_ResetReason : 1;
    uint32 biCRC_App_ResetReason : 1;
    uint32 biECC_Self_Test_ResetReason : 1;
    uint32 biClock_Cfg_ResetReason : 1;
    uint32 biHard_Fault_ResetReason : 1;
    uint32 biReserved : 25;
  }Bit;
  uint32 Word;
}tuEcuM_EcuInternalResetReason;

typedef struct
{
  Mcu_ResetType eMcuResetReason;
  tuEcuM_EcuInternalResetReason uEcuInternalResetReason;
}tsEcuM_ResetReason;


#endif // ECU_M_2020_06_26_H_

// EOF
