// *****************************************************************************
// Os_MemMap.h
// *****************************************************************************

#ifndef __OS_MEMMAP_H
#define __OS_MEMMAP_H


// -----------------------------------------------------------------------------
// preprocessor definitions
// -----------------------------------------------------------------------------
#define m_ram_start                         0x1FFF8000  // physical RAM area start
#define m_ram_limit                         0x20007000  // physical RAM area limit

#define m_flash_pav_start                   0x0000A000  // PAV EOL calibration data start
#define m_flash_pav_limit                   0x0000C000  // PAV EOL calibration data limit

// MPU-Region1: Application Code-FLASH area
#define m_flash_cal_start                   0x00020000 //Application coding data Calibration area start
#define m_flash_cal_limit                   0x00024000 //Application coding data Calibration area limit

#define m_flash_ecu_status_start            0x00024000 //Ecu Status area start
#define m_flash_ecu_status_limit            0x00025000 //Ecu Status area limit

#define m_flash_app_start                   0x00026000 //Software Application area start
#define m_flash_app_limit                   0x00080000 //Software Application area limit

#define m_flash_start                       0x0001C000
#define m_flash_limit                       0x00080000

// MPU-Region2: Application System-RAM area
#define m_data_system_start                 0x1FFF8000
#define m_data_system_limit                 0x1FFF9500

// MPU-Region3: Application Untrusted-RAM area
#define m_data_untrusted_start                  0x1FFF9500
#define m_data_untrusted_limit                  0x20002E00

// MPU-Region4: Application Trusted-RAM area
#define m_data_trusted_start                0x20003000
#define m_data_trusted_limit                0x20007000

// MPU-Region: Application Selftest area
#define m_data_selftest1_start              0x20002E00
#define m_data_selftest1_limit              0x20002E80
#define m_data_selftest2_start              0x20002E80
#define m_data_selftest2_limit              0x20002F00

// MPU-Region5: Application Shared-RAM area
#define m_data_shared_start                 0x20002F00
#define m_data_shared_limit                 0x20003000

// MPU-Region6: Application Flex-RAM area
#define m_data_flexnvm_start                0x10000000
#define m_data_flexnvm_limit                0x10010000

// MPU-Region7: Application Flex-NVM area
#define m_data_flexram_start                0x14000000
#define m_data_flexram_limit                0x14001000


#endif // __OS_MEMMAP_H

