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
/// \file  CtrlPxl_Cfg.h
///
/// \brief config file for pixel module
///
/// \author Caba Ionut (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_PXL_CFG_2021_03_09_H_
#define CTRL_PXL_CFG_2021_03_09_H_

//=============================================================================
// includes
//=============================================================================
#include <Cfg/Cfg.h>

//=============================================================================
// defines
//=============================================================================

#define CTRLPXL_SCALING_65535                              0xFFFFu
#define CTRLPXL_SCALING_32768                              0x8000u
#define CTRLPXL_MS_CONVERTION                              1000u  //[ms]

/* ------------- Module Unit Definitions -----------*/
#define CTRLPXL_CFG_PXL_NUMBERS                            CFG_MATRIX_PXL_CNT                    //max number of pixels for LDM prj
#define CTRLPXL_CFG_NR_OF_LOGICAL_UNITS                    CFG_LOGICAL_UNITS                     //max number of logical units from coding
#define CTRLPXL_CFG_NR_OF_MATRIX_DRV                       CFG_MLC_Chip_Cnt                      //max number of matrix driver for LDM prj
#define CTRLPXL_CFG_NR_OF_MATRIX_DRV_RESERVED              1u                                    //see EEPROM map : LMM8 = reserved
#define CTRLPXL_CFG_NR_OF_PXLs_STRING                      CFG_MATRIX_LEDs_PER_CH_Cnt            //max pixels number from a string controled by a matrix driver(MLC)
#define CTRLPXL_CFG_UNKNOWN_UINT8_VALUE                    0xFFU
#define CTRLPXL_CFG_MAX_PXL_ROW                            3U
#define CTRLPXL_CFG_MAX_NR_OF_PXL                          (CFG_MATRIX_RAW_CNT * CTRLPXL_CFG_MAX_PXL_ROW)//number of pixels controled / MLC


/*---------------Pixel defect timers-----------------*/
#define CTRL_PXL_LED_DEFECT_OFFSET_TIMER_MS                100u     //offset timer for led defect 
#define CTRL_PXL_LED_DEFECT_TIMER_MS                       100u     //debounce timer used for clear lmm fault !!!!! must match with CDD_LMM_CFG_CLR_FLT_CNT from Lmm cfg file


/*-----------  Reset MLC comands  ------------------*/
#define CTRL_PXL_MATRIX_SYSMODE_CTRL_NOACTION              0U
#define CTRL_PXL_MATRIX_SYSMODE_CTRL_RESETCOMM             1U
#define CTRL_PXL_MATRIX_SYSMODE_CTRL_SETINACTIVE           2U


/* ----------- Matrix Intensity Scaling  -----------*/
#define CTRLPXL_PWM_RESOLUTION                             0x3FFu    // max PWM resolution (1023d)
#define CTRLPXL_PERC_PWM(pwm_raw)                          ((((pwm_raw) * 100U) + 512U ) >> 10U)
#define CTRLPXL_ERROR_SUPPRESSION_PXL_DEFECT_MIN_PWM       51u  // meaning : 5% of PWM resolution  = (5*1023)/100 = 51.15
#define CTRL_PXL_NO_ERROR                                  0u  
#define CTRL_PXL_NUMBER_OF_MLC_CHIP                        CFG_MLC_Chip_Cnt     //number of LMM chips taken from CfgPrj.h

//because CPM sends values > 0x800u and does not saturate  them to 0x800, we need to covert them in 10-bit values for matrix and in the correct range
#define CTRLPXL_DO_SCALLING_FOR_MLC(pwm)                   (((pwm) * CTRLPXL_PWM_RESOLUTION)>> 15u)   // >>15 means division by 0x8000 (max. allowed from CPM)
#define CTRLPXL_SCALING_X_TO_Y_VALUE(x, y, val)            ((val) == 0u) ? 0u : (uint16)( ( (uint32)((uint32)(y) * (uint32)(val))   ) / (uint32)(x)) //scaling number (from x->y)
#define CTRL_PXL_MATRIX_RESETMATRIX_NOACTION               0U


/* ----------- EEPROM Data ------------------------*/
#define CTRL_PXL_NUMBER_OF_LMM_CHIP_EEPROM                 (CTRLPXL_CFG_NR_OF_MATRIX_DRV + CTRLPXL_CFG_NR_OF_MATRIX_DRV_RESERVED)

 //number of brightness data stored into EEProm = 8 LMM * 12 PXLs
#define CTRL_PXL_NUMBER_OF_EEPROM_BRIGHTNESS               ((CTRL_PXL_NUMBER_OF_LMM_CHIP_EEPROM) * CTRLPXL_CFG_NR_OF_PXLs_STRING)
#define CTRL_PXL_NUMBER_OF_EEPROM_BINNING_CLASS            12u // no of binning classes stored in eeprom
#define CTRL_PXL_START_EEPROM_ADDRESS                      0x00u
#define CTRL_PXL_CFG_MAX_BINNING_CLASSES                   0x06U
#define CTRL_PXL_CFG_BINNING_CLASS_5                       0x05U   //max binning class
#define CTRL_PXL_CFG_BINNING_CLASS_0                       0x00U   //min binning class
#define CTRL_PXL_BRIGHTNESS_FACTOR                         0xC8u   //max value on 8 bit taken from Eeprom : 0xC8 = 200 (max) res. 0.5%
#define CTRL_PXL_EEPROM_SIZE                               CFG_MATRIX_EEPROM_SIZE  //external matrix EEPROM size
#define CTRL_PXL_EEPROM_CRC_OFFSET                         1u      // CRC is saved on 1st byte, data starts from CRC offset


//start addresses of LMM_x device brightness values in the eeprom memory (see Eeprom Configuration)
#define CTRLPXL_START_EEPROM_ADDRESS_LMM1_BRIGHTVAL        0x10u
#define CTRLPXL_START_EEPROM_ADDRESS_LMM2_BRIGHTVAL        0x20u
#define CTRLPXL_START_EEPROM_ADDRESS_LMM3_BRIGHTVAL        0x30u
#define CTRLPXL_START_EEPROM_ADDRESS_LMM4_BRIGHTVAL        0x40u
#define CTRLPXL_START_EEPROM_ADDRESS_LMM5_BRIGHTVAL        0x50u
#define CTRLPXL_START_EEPROM_ADDRESS_LMM6_BRIGHTVAL        0x60u
#define CTRLPXL_START_EEPROM_ADDRESS_LMM7_BRIGHTVAL        0x70u
#define CTRLPXL_START_EEPROM_ADDRESS_LMM8_BRIGHTVAL        0x80u

#define CTRLPXL_SIZEOF_EEPROM_BRIGHTVAL_PER_LMM            0x0Cu
#define CTRLPXL_SKIP_RESERVED_BYTE_SIZE                    0x04u
#define CTRLPXL_NR_BYTES_BRIGHTVAL_WITH_RESERVED_PER_LMM   (CTRLPXL_SIZEOF_EEPROM_BRIGHTVAL_PER_LMM + CTRLPXL_SKIP_RESERVED_BYTE_SIZE)

#endif // CTRL_PXL_CFG_2021_03_09_H_
