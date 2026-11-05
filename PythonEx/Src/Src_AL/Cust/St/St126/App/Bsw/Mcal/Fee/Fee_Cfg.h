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
/// \file   Fee_Cfg.h
///
/// \brief  Configuration of FEE module
///         
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------


#include <Std_Types.h>

#include <Cfg/Cfg.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif


//#include <Types/Types.h>
//#include <Cfg/Cfg.h>
#include <Nvm_Id.h>

//lint -e451 Header file repeatedly included but does not have a standard include guard
//#include <r_eel_types.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard

//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <_FeeMac.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard


#include <Bsw/NvM/NvM_Para.h>
//#include <Bsw/NvM/NvmPara.h>
//#include <Swc/CodM/CodM_Para.h>
//#include <Swc/StatM/StatM.h>
//#include <Bsw/Dem/Dem.h>
//#include <Swc/SigPrep/SigPrepTx_Callbacks.h>

#define FEE_DEV_ERROR_DETECT STD_OFF
#define FEE_INSTANCE_ID  0u 
//#define Fee_Det_ReportError(ModuleId,InstanceId,ApiId,ErrorId ) Rte_Call_DemPrj_ReportErrorStatus(FEE_Ecu_Error, DEM_EVENT_STATUS_FAILED)

// In production software, this must always set to STD_OFF. Formatting of dataflash by software is not supported
#define FEE_USE_FEE_FORMAT STD_OFF
#define FEE_ENDJOB_NOTIFICATION
#define FEE_ERROR_NOTIFICATION


/// Base address of EERAM
//#define FEE_EERAMBase     FEATURE_FLS_FLEX_RAM_START_ADDRESS        // base address of FlexRAM block
#define FEE_EERAMBase     (0x14000000u)        // base address of FlexRAM block
/// Size of EEPROM
//#define FEE_EEESize       FEATURE_FLS_FLEX_RAM_SIZE                 // 4KB Emulated EEPROM
#define FEE_EEESize       (4096u)                 // 4KB Emulated EEPROM

/*  FlexNVM block count. */
#define FLS_DF_BLOCK_COUNT    (1u)
/* brief FlexNVM block size. */
#define FLS_DF_BLOCK_SIZE (65536u)
/* brief FlexNVM sector size. */
#define FLS_DF_BLOCK_SECTOR_SIZE (2048u)
/* brief FlexNVM write unit size. */
#define FLS_DF_BLOCK_WRITE_UNIT_SIZE (8u)
/* brief FlexNVM start address. (Valid only if FlexNVM is available.) */
#define FLS_DF_START_ADDRESS (0x10000000u)



// Flash Common Commands registers
#define FEE_FTFC_FCCOB3   FTFC->FCCOB[0]
#define FEE_FTFC_FCCOB2   FTFC->FCCOB[1]
#define FEE_FTFC_FCCOB1   FTFC->FCCOB[2]
#define FEE_FTFC_FCCOB0   FTFC->FCCOB[3]
#define FEE_FTFC_FCCOB7   FTFC->FCCOB[4]
#define FEE_FTFC_FCCOB6   FTFC->FCCOB[5]
#define FEE_FTFC_FCCOB5   FTFC->FCCOB[6]
#define FEE_FTFC_FCCOB4   FTFC->FCCOB[7]
#define FEE_FTFC_FCCOBB   FTFC->FCCOB[8]
#define FEE_FTFC_FCCOBA   FTFC->FCCOB[9]
#define FEE_FTFC_FCCOB9   FTFC->FCCOB[10]
#define FEE_FTFC_FCCOB8   FTFC->FCCOB[11]

/// Flash hardware algorithm operation commands
#define FEE_FTFC_PROGRAM_PARTITION        0x80U

/// Clear error bits command
#define FEE_CLEAR_FTFC_FSTAT_ERROR_BITS FTFC->FSTAT = (uint8_t)(FTFC_FSTAT_FPVIOL_MASK | \
                                                       FTFC_FSTAT_ACCERR_MASK          | \
                                                       FTFC_FSTAT_RDCOLERR_MASK)



BEGIN_FEE_MAP()
//          name,                    type,                         block_id,  immediate,  cbfunc
  FEE_BLOCK ( MultiBlockRequest,     uint16                       , 0x00,     TRUE,       dummy )
  FEE_BLOCK ( ConfigBlock,           tNvMConfigBlock              , 0x01,     TRUE,       dummy )
  FEE_BLOCK ( DemData,               tNvmDemData                  , 0x02,     TRUE,       dummy )
  FEE_BLOCK ( ErrCustPs,             tErrCustPs5Struct            , 0x03,     TRUE,       dummy )
  FEE_BLOCK ( FreezeFrameDataPs,     tFreezeFrameDataPs8Struct    , 0x04,     TRUE,       dummy )
  FEE_BLOCK ( DeltaPwmPara,          tisNvmDeltaPwmPara           , 0x05,     TRUE,       dummy )
  FEE_BLOCK ( FactoryData,           uint32                       , 0x06,     TRUE,       dummy )
  FEE_BLOCK ( InstrumentatedFrames,  boolean                      , 0x07,     TRUE,       dummy )
  FEE_BLOCK ( Statistics,            tstNvmStat                   , 0x08,     TRUE,       dummy )
  FEE_BLOCK ( MatrixEEPromContent,   tuNvmPara_EEProm             , 0x09,     TRUE,       dummy )
#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
  FEE_BLOCK ( DcMotorData,           tDcMotorDataStruct           , 0x0A,     TRUE,       dummy )
  FEE_BLOCK ( DcMotorCharacteristic, tDcMotorCharacteristicStruct , 0x0B,     TRUE,       dummy )
  FEE_BLOCK ( StatAvacPrj1Para,      tisStatAvacPrj1Para          , 0x0C,     TRUE,       dummy )
  FEE_BLOCK ( StatAvac1Para,         tisStatAvac1Para             , 0x0D,     TRUE,       dummy )
  FEE_BLOCK ( StatAvacOp1Data,       tisStatAvacOp1Data           , 0x0E,     TRUE,       dummy )
  FEE_BLOCK ( NmBackupCounters,      tisNmBackupCounters          , 0x0F,     TRUE,       dummy )
#elif defined (SAMPLE_FULL)
  FEE_BLOCK ( NmBackupCounters,      tisNmBackupCounters          , 0x0A,     TRUE,       dummy )
#endif
END_FEE_MAP()


