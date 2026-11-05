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
/// \file  CddTpsGen2_Cod.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN2_COD_2024_01_30_H_
#define CDD_TPS_GEN2_COD_2024_01_30_H_


// access to module APIs
#include <CddMlc_Cod.h>
#include <CddMlc.h>

#include <CddTpsGen2_Cfg.h>

#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <RteCommonTypes.h>
#include <Test_Ext.h>
#endif

//-----------------------------------------------------------------------------
// External variables
//-----------------------------------------------------------------------------
extern CONST_AL tNvmPara_CodingArea*  CddTpsGen2_pCodingArea;


//-----------------------------------------------------------------------------
// Typedef
//-----------------------------------------------------------------------------

typedef struct
{
  boolean boIsMasterId;
  uint8 ucPhysicalAddr;        // encoded chip address
}tsCddTpsGen2_MasterSlaveId;

typedef struct
{  
  tsCddTpsGen2_MasterSlaveId asMasterSlaveId[CDDTPSGEN2_MAX_CHIPs];        // encoded chip address
  uint8 aucCodDevID[CDDTPSGEN2_MAX_CHIPs];       // chip position in the array of chips
  uint8 ucEepromAddr;
  uint8 ucEepromId;
  uint8 ucConnectedDevices;                           // store the  actual count of GEN2 connected
  uint8 ucBaudRate;
}tsCddTpsGen2_DevData;

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Declaration or definitions of functions
//-----------------------------------------------------------------------------
tsCddTpsGen2_DevData* CddTpsGen2_pfGetDevData(void);

//-----------------------------------------------------------------------------
// inline functions
//-----------------------------------------------------------------------------
      
#define CDDTPSGEN2_Para_COUNT_CONNECTED_DEV       CddTpsGen2_pfGetDevData()->ucConnectedDevices
#define CDDTPSGEN2_Para_CHIP_IDX(ucIdx)           CddTpsGen2_pfGetDevData()->aucCodDevID[ucIdx]    
#define CDDTPSGEN2_Para_CHIP_ADDR(ucIdx)          CddTpsGen2_pfGetDevData()->asMasterSlaveId[ucIdx]
#define CDDTPSGEN2_Para_CHIP_EEPROM_ADDR          CddTpsGen2_pfGetDevData()->ucEepromAddr
#define CDDTPSGEN2_Para_CHIP_MASTER_IDPOS         CddTpsGen2_pfGetDevData()->ucMasterId_Pos
#define CDDTPSGEN2_Para_BAUDRATE                  CddTpsGen2_pfGetDevData()->ucBaudRate


#define CDDTPSGEN2_IS_DEVICE_CONNECTED(ucIdx)   (  ( CDDTPSGEN2_Para_CHIP_IDX(unDevIdx) != CDDTPSGEN2_ADDR_NOT_CONNECTED) ? TRUE : FALSE  )

#ifndef UNIT_TEST
#define CDDTPSGEN2_Para_Get_CHIP_ID(ucIdx)        CDDMLC_Para_CHIP_ID(ucIdx)
#endif
#endif // CDD_TPS_GEN2_COD_2024_01_30_H_
