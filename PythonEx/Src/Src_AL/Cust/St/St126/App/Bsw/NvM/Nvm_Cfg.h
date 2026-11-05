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
/// \file   Nvm_Cfg.h
///
/// \brief  Configuration of NvM module
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------


#include <Std_Types.h>
#include <Cfg/Cfg.h>
//#include <Types/Types.h>
//#include <Cfg/Cfg.h>
// use V2 API
#define NVM_API_V2

#ifdef UNIT_TEST
#include <Nvm_Id.h>     //UT files include PC_WIN32API MCAL and Fee_Cfg is not included, hence the tNvMConfigBlock type will be unknown
#endif


//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <_NvmMac.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#include "Nvm_Para.h"

#ifndef UNIT_TEST
#include <Deh.h>
#endif // UNIT_TEST

#ifdef SAMPLE_ECO
#include "CddDcm.h"
#include "AvacStat1Init.h"
#endif // SAMPLE_ECO

//#include <Bsw/Nvm/NvmPara.h>
//#include <Swc/CodM/CodM.h>
//#include <Swc/StatM/StatM.h>
//#include <Bsw/Dem2/Dem2.h>
//#include <Swc/LaserSens/LaserSens.h>
//#include <Swc/App/App_Main.h>

#define MEMIF_NONE          (0u)
#define MEMIF_FEE           (1u)
#define MEMIF_BLOCK_NONEId  (0u)
#define NVM_MEMIF1 MEMIF_FEE

/* Take care that the MultiBlockRequest definition is not zero (it´s defined as 0 in AUTOSAR). The NvM module doesn´t work as AUTOSAR for the MultiBlockRequest.
/   Problem in NvM_GetErrorStatus function (that considers the NvM_aAdminTable[blockId].ErrorStatus. blockId index)
*/
//#define MultiBlockRequest NvMBlockCount
//#define NVM_API_CONFIG_USE_PRIO_QUEUE          STD_OFF
//#define NvM_QUEUE_SIZE 60

BEGIN_NVM_MAP()
  //TBD: not working with only one block ; the macro must be checked
  // do not change the first two lines
  //          name,                  type                         , block_id, init_rom                                            , init_callback       , prio , flags                  ,  cbfunc  ,  memif_device  , memifblockid
  NVM_BLOCK ( MultiBlockRequest,     uint16                       , 0x00,     NULL_PTR                                            , NULL_PTR            , dummy, 0                      ,  NULL_PTR,  MEMIF_NONE    , MEMIF_BLOCK_NONE)  
  NVM_BLOCK ( ConfigBlock,           tNvMConfigBlock              , 0x01,     NULL_PTR                                            , Nvm_InitConfigBlock , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockConfigBlock)
  NVM_BLOCK ( DemData,               tNvmDemData                  , 0x02,     NULL_PTR                                            , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockDemData)
  NVM_BLOCK ( ErrCustPs,             tErrCustPs5Struct            , 0x03,     NULL_PTR                                            , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockErrCustPs)
  NVM_BLOCK ( FreezeFrameDataPs,     tFreezeFrameDataPs8Struct    , 0x04,     NULL_PTR                                            , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockFreezeFrameDataPs)
  NVM_BLOCK ( DeltaPwmPara,          tisNvmDeltaPwmPara           , 0x05,     NULL_PTR                                            , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockDeltaPwmPara)
  NVM_BLOCK ( FactoryData,           uint32                       , 0x06,     NULL_PTR                                            , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockFactoryData)
  NVM_BLOCK ( InstrumentatedFrames,  boolean                      , 0x07,     NULL_PTR                                            , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockInstrumentatedFrames)
  NVM_BLOCK ( Statistics,            tstNvmStat                   , 0x08,     NULL_PTR                                            , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockStatistics)
  NVM_BLOCK ( MatrixEEPromContent,   tuNvmPara_EEProm             , 0x09,     NULL_PTR                                            , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockMatrixEEPromContent)
#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
  NVM_BLOCK ( DcMotorData,           tDcMotorDataStruct           , 0x0A,     ((uint8*)&NvmInit_ParaDcMotorDataDefault)           , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockDcMotorData)
  NVM_BLOCK ( DcMotorCharacteristic, tDcMotorCharacteristicStruct , 0x0B,     ((uint8*)&NvmInit_ParaDcMotorCharacteristicDefault) , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockDcMotorCharacteristic)
  NVM_BLOCK ( StatAvacPrj1Para,      tisStatAvacPrj1Para          , 0x0C,     ((uint8*)&NvmInit_StatAvacPrj1ParaDefault)          , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockStatAvacPrj1Para      )
  NVM_BLOCK ( StatAvac1Para,         tisStatAvac1Para             , 0x0D,     ((uint8*)&NvmInit_StatAvac1ParaDefault)             , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockStatAvac1Para         )
  NVM_BLOCK ( StatAvacOp1Data,       tisStatAvacOp1Data           , 0x0E,     ((uint8*)&NvmInit_StatAvacOp1DataDefault)           , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockStatAvacOp1Data       )
  NVM_BLOCK(  NmBackupCounters,      tisNmBackupCounters          , 0x0F,     ((uint8*)&NvmInit_NmBackupCountersDefault)          , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockNmBackupCounters      )
#elif defined (SAMPLE_FULL)
  NVM_BLOCK ( NmBackupCounters,      tisNmBackupCounters          , 0x0A,     ((uint8*)&NvmInit_NmBackupCountersDefault)          , NULL_PTR            , dummy, NVM_FLAG_READ_WRITE_ALL,  NULL_PTR,  MEMIF_FEE     , FeeBlockNmBackupCounters)
#endif

END_NVM_MAP()



