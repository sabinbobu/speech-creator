// *****************************************************************************
// OsMpu.h
// *****************************************************************************

#ifndef __OSMPU_H
#define __OSMPU_H


// -----------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------
#include "stdint.h"
#include "mpu_driver.h"

// -----------------------------------------------------------------------------
// preprocessor definitions
// -----------------------------------------------------------------------------
#define MPU_CONFIG_1_INST  (0U)
#define MPU_CONFIG_1_NUM_OF_REGION_CFG0  (8U)
#define MPU_CONFIG_1_NUM_OF_USER_CFG  (1U)

// -----------------------------------------------------------------------------
// function prototypes
// -----------------------------------------------------------------------------
void Os_MpuInit(void);
void Os_AipsInit(void);

// -----------------------------------------------------------------------------
// Global variables 
// -----------------------------------------------------------------------------
extern const mpu_user_config_t MPU_Cfg0[MPU_CONFIG_1_NUM_OF_REGION_CFG0];
extern const mpu_master_access_right_t AccessRightConfig0[FEATURE_MPU_MASTER_COUNT];
extern const mpu_master_access_right_t AR_FLASH[FEATURE_MPU_MASTER_COUNT];
extern const mpu_master_access_right_t AR_RAM_Restricted[FEATURE_MPU_MASTER_COUNT];
extern const mpu_master_access_right_t AR_RAM_Unrestricted[FEATURE_MPU_MASTER_COUNT];

#endif // __OSMPU_H

