// *****************************************************************************
// OsMpu.c
//
//
// *****************************************************************************

// -----------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------
#include "stdint.h"
#include "cmsis_os2.h"
#include "rtx_os.h"
#include "Os_Cfg.h"
#include "Os_Mpu.h"
#include "Os_MemMap.h"
#include "Os_Main.h"
#include "Os_EvtRec.h"
#include "Rte_Cfg.h"
#include <UtilUtility.h>
#include "RTX_Config_CPUload.h"


// -----------------------------------------------------------------------------
// preprocessor definitions
// -----------------------------------------------------------------------------
#define OS_MPU_ACTIVE_REGION            OS_MpuCfg
#define OS_MPU_INSTANCE                 0

#define OS_MPU_REGION0_PRIVILEGED       0
#define OS_MPU_REGION1_FLASH            1
#define OS_MPU_REGION2_RAM_SYSTEM       2
#define OS_MPU_REGION3_RAM_UNTRUSTED    3
#define OS_MPU_REGION4_RAM_SHARED       4
#define OS_MPU_REGION5_RAM_TRUSTED      5
#define OS_MPU_REGION7_FLEXRAM          6
#define OS_MPU_REGION8_FLEXNVM          7

// -----------------------------------------------------------------------------
// vars, constants
// -----------------------------------------------------------------------------
static const mpu_master_access_right_t OS_AR_Privileged[] =
{
  { // CORE
    .masterNum = FEATURE_MPU_MASTER_CORE,
    .accessRight = MPU_SUPERVISOR_RWX_USER_NONE,
    .processIdentifierEnable = false
  },
  { // DEBUGGER
    .masterNum = FEATURE_MPU_MASTER_DEBUGGER,
    .accessRight = MPU_SUPERVISOR_USER_RWX,
    .processIdentifierEnable = false
  },
  { // DMA
    .masterNum = FEATURE_MPU_MASTER_DMA,
    .accessRight = MPU_SUPERVISOR_RWX_USER_NONE,
    .processIdentifierEnable = false
  }
#if(FEATURE_MPU_MASTER_COUNT > 3)
  ,{ // ENET
    .masterNum = FEATURE_MPU_MASTER_ENET,
    .accessRight = MPU_NONE,
    .processIdentifierEnable = false
  }
#endif
};

static const mpu_master_access_right_t OS_AR_FLASH[] =
{
  { // CORE
    .masterNum = FEATURE_MPU_MASTER_CORE,
    .accessRight = MPU_SUPERVISOR_RWX_USER_RX,
    .processIdentifierEnable = false
  },
  { // DEBUGGER
    .masterNum = FEATURE_MPU_MASTER_DEBUGGER,
    .accessRight = MPU_SUPERVISOR_RWX_USER_RWX,
    .processIdentifierEnable = false
  },
  { // DMA
    .masterNum = FEATURE_MPU_MASTER_DMA,
    .accessRight = MPU_SUPERVISOR_RWX_USER_R,
    .processIdentifierEnable = false
  }
#if(FEATURE_MPU_MASTER_COUNT > 3)
  ,{ // ENET
    .masterNum = FEATURE_MPU_MASTER_ENET,
    .accessRight = MPU_NONE,
    .processIdentifierEnable = false
  }
#endif
};

static const mpu_master_access_right_t OS_AR_RAM_Restricted[] =
{
  { // CORE
    .masterNum = FEATURE_MPU_MASTER_CORE,
    .accessRight = MPU_SUPERVISOR_RWX_USER_R,
    .processIdentifierEnable = false
  },
  { // DEBUGGER
    .masterNum = FEATURE_MPU_MASTER_DEBUGGER,
    .accessRight = MPU_SUPERVISOR_RWX_USER_RWX,
    .processIdentifierEnable = false
  },
  { // DMA
    .masterNum = FEATURE_MPU_MASTER_DMA,
    .accessRight = MPU_SUPERVISOR_RWX_USER_R,
    .processIdentifierEnable = false
  }
#if(FEATURE_MPU_MASTER_COUNT > 3)
  ,{ // ENET
    .masterNum = FEATURE_MPU_MASTER_ENET,
    .accessRight = MPU_NONE,
    .processIdentifierEnable = false
  }
#endif
};

static const mpu_master_access_right_t OS_AR_RAM_Unrestricted[] =
{
  { // CORE
    .masterNum = FEATURE_MPU_MASTER_CORE,
    .accessRight = MPU_SUPERVISOR_RWX_USER_RW,
    .processIdentifierEnable = false
  },
  { // DEBUGGER
    .masterNum = FEATURE_MPU_MASTER_DEBUGGER,
    .accessRight = MPU_SUPERVISOR_RWX_USER_RWX,
    .processIdentifierEnable = false
  },
  { // DMA
    .masterNum = FEATURE_MPU_MASTER_DMA,
    .accessRight = MPU_SUPERVISOR_RWX_USER_RW,
    .processIdentifierEnable = false
  }
#if(FEATURE_MPU_MASTER_COUNT > 3)
  ,{ // ENET
    .masterNum = FEATURE_MPU_MASTER_ENET,
    .accessRight = MPU_NONE,
    .processIdentifierEnable = false
  }
#endif
};



static const mpu_user_config_t OS_MpuCfg[] = //MPU_Cfg0[] =
{
  { // MpuRegion0: Privileged Access to all
    .startAddr         = 0x00000000U,
    .endAddr           = 0xFFFFFFFFU,
    .masterAccRight    = OS_AR_Privileged,
    .processIdentifier = 0x0U,
    .processIdMask     = 0x0U
  },
  { // MpuRegion1: FLASH-Memory
    .startAddr         = (uint32_t)(m_flash_pav_start),
    .endAddr           = (uint32_t)(m_flash_limit-1),
    .masterAccRight    = OS_AR_FLASH,
    .processIdentifier = 0x0U,
    .processIdMask     = 0x0U
  },
  { // MpuRegion2: RAM System-Memory
    .startAddr         = (uint32_t)(m_data_system_start),
    .endAddr           = (uint32_t)(m_data_system_limit-1),
    .masterAccRight    = OS_AR_RAM_Restricted,
    .processIdentifier = 0x0U,
    .processIdMask     = 0x0U
  },
  { // MpuRegion3: RAM Untrusted-Memory
    .startAddr         = (uint32_t)(m_data_untrusted_start),
    .endAddr           = (uint32_t)(m_data_untrusted_limit-1),
    .masterAccRight    = OS_AR_RAM_Unrestricted,
    .processIdentifier = 0x0U,
    .processIdMask     = 0x0U
  },
  { // MpuRegion4: RAM Shared-Memory
    .startAddr         = (uint32_t)(m_data_shared_start),
    .endAddr           = (uint32_t)(m_data_shared_limit-1),
    .masterAccRight    = OS_AR_RAM_Restricted,
    .processIdentifier = 0x0U,
    .processIdMask     = 0x0U
  },
  { // MpuRegion5: RAM Trusted-Memory
	.startAddr         = (uint32_t)(m_data_trusted_start),
	.endAddr           = (uint32_t)(m_data_trusted_limit-1),
	.masterAccRight    = OS_AR_RAM_Restricted,
	.processIdentifier = 0x0U,
	.processIdMask     = 0x0U
  },
  { // MpuRegion6: FlexRAM-Memory
    .startAddr         = (uint32_t)(m_data_flexram_start),
    .endAddr           = (uint32_t)(m_data_flexram_limit-1),
    .masterAccRight    = OS_AR_RAM_Unrestricted,
    .processIdentifier = 0x0U,
    .processIdMask     = 0x0U
  },
  { // MpuRegion7: FlexNVM-Memory
    .startAddr         = (uint32_t)(m_data_flexnvm_start),
    .endAddr           = (uint32_t)(m_data_flexnvm_limit-1),
    .masterAccRight    = OS_AR_RAM_Restricted,
    .processIdentifier = 0x0U,
    .processIdMask     = 0x0U
  }
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_MpuInit
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Os_MpuInit(void)
{
  #if(OS_MPU_ENABLE == 1)
  status_t  Status;
  
  OS_EVTREC2(OS_EVTREC_MpuInit, 0UL, 0UL);
  
  Status = MPU_DRV_Init(OS_MPU_INSTANCE, UTIL_COUNTOF(OS_MPU_ACTIVE_REGION), OS_MPU_ACTIVE_REGION);

  // initialize MPU
  if(Status != STATUS_SUCCESS)
  {
    OS_EVTREC2(OS_EVTREC_OsMpu_Internal_Error, __LINE__, Status);
    //dtg ERRORHANDLING
  }
  #endif
}  


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_AipsInit
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Os_AipsInit(void)
{
  uint8_t  Index;
  
  OS_EVTREC2(OS_EVTREC_AipsInit, 0UL, 0UL);
  
  #if(OS_AIPS_ENABLE == 1)

  #else
  // PRQA S 306 3 // program architecture and readability - Cast between a pointer to object and an integral type wanted and documented
  AIPS->PACRA = 0U;
  AIPS->PACRB = 0U;
  AIPS->PACRD = 0U;

  for(Index=0; Index < AIPS_OPACR_COUNT; Index++)
  {
    // PRQA S 306 1 // program architecture and readability - Cast between a pointer to object and an integral type wanted and documented
    AIPS->OPACR[Index] = 0U;
  }  
  #endif
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// osZoneSetup_Callback
//
// OS scheduler hook-function
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void osZoneSetup_Callback(uint32_t zone)
{

  RTX_WorkThreadSwitch_Notification();

  #if(OS_RTE_MONITOR == 1)
    if(RteMonitorBuffer[zone] != NULL_PTR)
    {
      RteMonitorActive = RteMonitorBuffer[zone];
    }
  #endif
  
  #if(OS_MPU_ENABLE == 1)
    OS_EVTREC2(OS_EVTREC_osZoneSetup_System, (uint32_t)zone, 0UL);
  
    switch(zone >> OS_THREAD_INDEX_BITS)
  {
      case OS_PID_SYSTEM:
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION2_RAM_SYSTEM,   OS_AR_RAM_Unrestricted);
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION5_RAM_TRUSTED,  OS_AR_RAM_Unrestricted);
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION4_RAM_SHARED,   OS_AR_RAM_Unrestricted);
//      MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION6_FLEXRAM,      OS_AR_RAM_Unrestricted);
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION8_FLEXNVM,      OS_AR_RAM_Unrestricted);
      break;

      case OS_PID_TRUSTED:
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION2_RAM_SYSTEM,   OS_AR_RAM_Restricted);
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION5_RAM_TRUSTED,  OS_AR_RAM_Unrestricted);
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION4_RAM_SHARED,  OS_AR_RAM_Unrestricted);
//      MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION6_FLEXRAM,      OS_AR_RAM_Unrestricted);
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION8_FLEXNVM,      OS_AR_RAM_Unrestricted);
      break;

      case OS_PID_UNTRUSTED:
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION2_RAM_SYSTEM,   OS_AR_RAM_Restricted);
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION4_RAM_SHARED,   OS_AR_RAM_Restricted);
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION5_RAM_TRUSTED,  OS_AR_RAM_Restricted);
//      MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION6_FLEXRAM,      OS_AR_RAM_Unrestricted);
      (void)MPU_DRV_SetMasterAccessRights(OS_MPU_INSTANCE, OS_MPU_REGION8_FLEXNVM,      OS_AR_RAM_Restricted);
      break;

    default:
      //dtg Errorhandling
      break;
  }
  #else
  (void)zone;
  #endif // OS_MPU_ENABLE
}


