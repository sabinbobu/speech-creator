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
/// \file  SysCrc_Cfg.h
///
/// \brief
///
/// \author Cruciu Denis-Mihai (F31196D)
///         mailTo: denis-mihai.cruciu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef SYS_CRC_2021_08_03_H_
#define SYS_CRC_2021_08_03_H_

//=============================================================================
//  includes
//=============================================================================
#include <Bsw/Dem/Dem.h>
#include <Bsw/EcuM/EcuM.h>
#include <Os_MemMap.h>

//length in bytes for the CRC stored in ROM (App CRC and FBL CRC)
#define SYS_CRC_LENGTH     6u
//Start Address and offset for the segments
#define SYS_CRC_APP_START            m_flash_app_start
#define SYS_CRC_APP_CRC_OFFSET       (m_flash_app_limit - m_flash_app_start - SYS_CRC_LENGTH)
#define SYS_CRC_CAL_START            m_flash_cal_start
#define SYS_CRC_CAL_CRC_OFFSET       (m_flash_cal_limit - m_flash_cal_start - SYS_CRC_LENGTH)
// number of bytes that are consumed by the CRC calculation per call
// = 32, should be a multiple of '4' = sizeof(uint32)
#define SYS_CRC_CONSUMPTION   32u 
//Initial seed value
#define SYS_CRC_INITIAL_SEED_VALUE   0xFFFFFFFFU
//Address of calculated CRC value for App
#define SYS_CRC_APP_ROM_CALC_CRC (SYS_CRC_APP_START + SYS_CRC_APP_CRC_OFFSET)
//Address of calculated CRC value for Calib
#define SYS_CRC_CAL_ROM_CALC_CRC (SYS_CRC_CAL_START + SYS_CRC_CAL_CRC_OFFSET)

// defined segments
//                               start addr. of segment,  size of segment,                swap CRC,         used DTC of this checked segment    ROM Address calculated CRC         need to add callback functions
#define SYS_CRC_ROM_SEGMENTS { { SYS_CRC_APP_START,       SYS_CRC_APP_CRC_OFFSET,         FALSE,              (uint16)CRC_APP_DEFECT,             SYS_CRC_APP_ROM_CALC_CRC,        EcuM_FlashCrcFailure_Indication}, \
                               { SYS_CRC_CAL_START,       SYS_CRC_CAL_CRC_OFFSET,         FALSE,              (uint16)CRC_CALIB_DEFECT,           SYS_CRC_CAL_ROM_CALC_CRC,        SysCrc_RomSegs_RomSegCalCbStatus}}

//Macro used to assign the bit shifted value for DCRA1CIN register of Rom CRC Segment Position
#define SYS_CRC_LIST(X,Y) (((uint32)(*(&(X)[(Y) + 0])) << 24) \
                         | ((uint32)(*(&(X)[(Y) + 1])) << 16) \
                         | ((uint32)(*(&(X)[(Y) + 2])) << 8)  \
                         | ((uint32)(*(&(X)[(Y) + 3])) << 0))

#endif // SYS_CRC_2021_08_03_H_
