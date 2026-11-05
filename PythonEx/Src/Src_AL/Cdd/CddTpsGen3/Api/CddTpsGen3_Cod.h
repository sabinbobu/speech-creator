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
/// \file  CDDTPSGEN3_Cod.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN3_COD_2024_01_30_H_
#define CDD_TPS_GEN3_COD_2024_01_30_H_


// access to module APIs
#ifndef UNIT_TEST
#include <CddMlc_Cod.h>
#include <CddMlc.h>
#endif

#include <CddTpsGen3_Cfg.h>

#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <RteCommonTypes.h>
#include <Test/Test_Ext.h>
#endif

//-----------------------------------------------------------------------------
// External variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Typedef
//-----------------------------------------------------------------------------

typedef struct
{
  boolean boIsMasterId;
  uint8 ucPhysicalAddr;        // encoded chip address
}tsCddTpsGen3_MasterSlaveId;

typedef struct
{
  tsCddTpsGen3_MasterSlaveId asMasterSlaveId[CDDTPSGEN3_MAX_CHIPs];        // encoded chip address
  uint8 aucCodDevID[CDDTPSGEN3_MAX_CHIPs];       // chip position in the array of chips
  uint8 ucEepromAddr;
  uint8 ucBaudRate;
  uint8 ucConnectedDevices;                           // store the  actual count of GEN2 connected
}tsCddTpsGen3_DevData;

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Declaration or definitions of functions
//-----------------------------------------------------------------------------
tsCddTpsGen3_DevData* CddTpsGen3_pfGetDevData(void);

//-----------------------------------------------------------------------------
// inline functions
//-----------------------------------------------------------------------------

#define CDDTPSGEN3_Para_COUNT_CONNECTED_DEV       CddTpsGen3_pfGetDevData()->ucConnectedDevices
#define CDDTPSGEN3_Para_CHIP_IDX(ucIdx)           CddTpsGen3_pfGetDevData()->aucCodDevID[ucIdx]
#define CDDTPSGEN3_Para_CHIP_ADDR(ucIdx)          CddTpsGen3_pfGetDevData()->asMasterSlaveId[ucIdx]
#define CDDTPSGEN3_Para_CHIP_EEPROM_ADDR          CddTpsGen3_pfGetDevData()->ucEepromAddr
#define CDDTPSGEN3_Para_BAUDRATE                  CddTpsGen3_pfGetDevData()->ucBaudRate


#define CDDTPSGEN3_IS_DEVICE_CONNECTED(ucIdx)   (  ( CDDTPSGEN3_Para_CHIP_IDX(unDevIdx) != CDDTPSGEN3_ADDR_NOT_CONNECTED) ? TRUE : FALSE  )

#define CDDTPSGEN3_CONNECTED_DEVICES              CDDTPSGEN3_pfGetDevData()->ucTpsGen3_ConnectedDevices

#ifndef UNIT_TEST
#define CDDTPSGEN3_Para_Get_CHIP_ID(ucIdx)        CDDMLC_Para_CHIP_ID(ucIdx)
#define CDDTPSGEN3_Para_Get_BAUDRATE              CDDMLC_Para_BAUDRATE
#define CDDTPSGEN3_Para_IS_CODING_VALID           CDDMLC_Para_IS_CODING_VALID
#endif


#endif // CDD_TPS_GEN2_COD_2024_01_30_H_
