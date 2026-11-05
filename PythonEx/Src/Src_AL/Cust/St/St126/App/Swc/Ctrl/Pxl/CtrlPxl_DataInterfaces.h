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
/// \file   CtrlPxl_DataInterfaces.h
///
/// \brief  Data Interfaces for memory handling
///
/// \author Bodian Bianca-Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_PXL_DATA_INTERFACES_2022_05_31_H_
#define CTRL_PXL_DATA_INTERFACES_2022_05_31_H_

//=============================================================================
// includes
//=============================================================================
#include "CtrlPxl_Types.h"
#include <AL_Helper.h>

//=============================================================================
// variables
//=============================================================================
/*internal handling structure accessed through the module*/
extern tsCtrlPxl_InternalHandling CtrlPxl_sInternalHandling;

//=============================================================================
// defines
//=============================================================================
//CODING DATA
#define CTRLPXL_CODING_DATA                CtrlPxl_sInternalHandling.sCodingData
#define CTRLPXL_SEGMENT_MAP                CTRLPXL_CODING_DATA.aucMapMtxSegments
#define CTRLPXL_SEGMENT_POSITION           CTRLPXL_CODING_DATA.aucMapLuToSeg
#define CTRLPXL_LOGICAL_UNIT_MAP           CTRLPXL_CODING_DATA.aucMapLu

//EEPROM DATA
#define CTRLPXL_EEPROM_MAPPING_BYTES       CtrlPxl_sInternalHandling.sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.Data
#define CTRLPXL_EEPROM_MAPPING_FIELDS      CtrlPxl_sInternalHandling.sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.MatrixParam_Data
#define CTRLPXL_NVM_BRIGHTNESS             CtrlPxl_sInternalHandling.sEepromHandling.sCalibNvmDataUsed.aucBrightnessVal
#define CTRLPXL_NVM_BINNING                CtrlPxl_sInternalHandling.sEepromHandling.sCalibNvmDataUsed.aucBinningClass

#endif // CTRL_PXL_DATA_INTERFACES_2022_05_31_H_
