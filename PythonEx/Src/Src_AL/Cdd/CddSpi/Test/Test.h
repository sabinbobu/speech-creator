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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>

// Headers of the Module
#include <CddSpi.h>
#include <CddSpi_Types.h>
#include <CddSpi_S32K_14X.h>
#include <CddSpi_S32K_14X_Types.h>

// Headers of other modules
#include <CddDma.h>
#include <RteCommonTypes.h>

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
#define CDDSPI_MAC_DECL_IFCSEQ_ENUM
#include <CddSpi_Cfg.h>
#undef CDDSPI_MAC_DECL_IFCSEQ_ENUM
#endif

//=============================================================================
// Typedefs
//=============================================================================
typedef boolean(*tfpCddSpiDevDynCfg)(uint16* punData);

typedef struct tsCddSpiDevDynCfg
{
  tfpCddSpiDevDynCfg fpDevDynCfgCb;
}tsCddSpiDevDynCfg;

#if (CDDSPI_SINGLE_OPERATION == STD_ON)
typedef enum teCddSpiIfcSingleMode
{
  CddSpi_eIfcSingleMode_Polling = 0,
  CddSpi_eIfcSingleMode_Interrupt = 1,
  CddSpi_eIfcSingleMode_DMA = 2,
}teCddSpiIfcSingleMode;
#endif

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
typedef enum teCddSpiIfcCyclicMode
{
  CddSpi_eIfcCyclicMode_Polling = 0,
  CddSpi_eIfcCyclicMode_Interrupt = 1,
  CddSpi_eIfcCyclicMode_DMA = 2,
  CddSpi_eIfcCyclicMode_DUMMY = 99,
}teCddSpiIfcCyclicMode;
#endif

typedef struct tsCddSpiIfcCfg
{
  CONST_AL uint8                                    ucIfcMap;
#if (CDDSPI_SINGLE_OPERATION == STD_ON)
  CONST_AL teCddSpiIfcSingleMode  eIfcSingleMode;
#endif
#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
  CONST_AL teCddSpiIfcCyclicMode                    eIfcCyclicMode;
  uint8                                             ucSeqMap;
#endif
}tsCddSpiIfcCfg;

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
//Ifc seq enum

typedef void(*tfpCddSpiRxCb)(uint16 unId, uint32 ulData);
typedef uint32(*tfpCddSpiTxCb)(uint16 unId);
typedef uint8(*tfpCddSpiCrc) (uint8* pucData, uint32 ulLength, uint8 ucStartVal, boolean boFirstCall);

typedef struct tsCddSpiDevCb
{
  tfpCddSpiTxCb                                     fpTx;
  tfpCddSpiRxCb                                     fpRx;
}tsCddSpiDevCb;

typedef struct tsCddSpiCbData
{
  tsCddSpiDevCb                                     sDevCb;
  CONST_AL uint16                                   unCbId;
}tsCddSpiCbData;

typedef struct tsCddSpiDevSeqData
{
  tsCddSpiCbData*                                   psCbData;
  uint16*                                           punTxBuff;
  uint16*                                           punRxBuff;
  CONST_AL teCddSpiDev                              eDev;
}tsCddSpiDevSeqData;


typedef struct tsCddSpiSeqData
{
  tsCddSpiDevSeqData*                               psDevData;
  CONST_AL uint8                                    ucDeviceCount;
  uint8                                             ucFramesCount;
}tsCddSpiSeqData;

typedef struct tsCddSpiSeqHandler
{
  CONST_AL teCddSpiIfc                              eSpiIfc;
  uint8                                             ucCycleCnt;
  CONST_AL uint8                                    ucPrescaler;
  CONST_AL uint8                                    ucTimeOutMax;
  uint8                                             ucTimeOutCnt;
  uint8                                             ucSeqContext;
  uint8                                             ucIntDevIdx;
}tsCddSpiSeqHandler;

#endif //CDDSPI_CYCLIC_OPERATION

//=============================================================================
// Defines
//=============================================================================

// External Preprocessor definitions
#define CDDSPI_CYT2_B9_SCB_DIVIDER_TYPE             (0U)         //8Bit divider used
#define CDDSPI_CYT2_B9_SCB_DIVIDER_VALUE            (15U)        //80MHz /(1 +7)  = 10MHz for SCB Block
#define CDDSPI_CYT2_B9_SCB_PERCLK_IDX(n)            (30U + (n) )
#define CDDSPI_S32K_14X_RX_FIFO_STATUS_MSK          (uint32)0x7UL
#define CDDSPI_CYT2_B9_SCB_SPI_STATUS_BUS_BUSY_MSK  (uint32)0x001UL
//Sequence context
#define CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK          0x01U
#define CDDSPI_SEQ_CONTEXT_COMPLETE_MSK             0x02U
#define CDDSPI_SEQ_CONTEXT_INITIALIZED_POS          0U
#define CDDSPI_SEQ_CONTEXT_COMPLETE_POS             1U

// UT Preprocessor definitions
#define CDDSPI_UT_UINT32_PATTERN                    (uint32)0x05050505UL
#define CDDSPI_UT_UINT16_PATTERN                    (uint32)0x0505UL
#define CDDSPI_UT_CRC_PATTERN                       (uint8) 0x05U
#define CDDSPI_UT_CRC_RX_CB_POS                     (uint32)24UL
#define CDDSPI_UT_RX_TX_VALID_MSK                   (uint32)0x00010000UL
#define CDDSPI_UT_SF_EFT_SA_MASK                    (uint8)0xC0
#define CDDSPI_UT_BUFF_MAX_LENGTH                   (uint16)20

//=============================================================================
// Module global variables
//=============================================================================

// Extern data
extern uint8                                        CddSpi_ucState;

#if (CDDSPI_STATUS_FAULT == STD_ON)
extern uint8                                        CddSpi_ucStatusFaultVal;
#endif

extern volatile tsCddSpi_S32K146_PERI               dummyPERI;
extern tsCddSpiIfcCfg                               CddSpi_asIfcCfg[CddSpi_eIfc_Count];
#if (CDDSPI_DYNAMIC_CFG == STD_ON)
extern tsCddSpiDevDynCfg                            CddSpi_asDevDynCfg[];
#endif

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
extern tsCddSpiCbData                               CDDSPI_CONCAT(CddSpi_asSpiDevCb_, SBC)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_, SBC)];
extern tsCddSpiCbData                               CDDSPI_CONCAT(CddSpi_asSpiDevCb_, BOOST)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_, BOOST)];
extern tsCddSpiCbData                               CDDSPI_CONCAT(CddSpi_asSpiDevCb_, STP)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_, STP)];
extern tsCddSpiCbData                               CDDSPI_CONCAT(CddSpi_asSpiDevCb_, BUCK_0_5)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_, BUCK_0_5)];
extern tsCddSpiDevSeqData                           CDDSPI_CONCAT(CddSpi_asSeqDataIfc_, 0)[];
extern tsCddSpiDevSeqData                           CDDSPI_CONCAT(CddSpi_asSeqDataIfc_, 1)[];
extern tsCddSpiSeqData                              CddSpi_asSeqData[];
extern tsCddSpiDevCfg                               CddSpi_asDeviceCfg[];
extern tsCddSpiSeqHandler                           CddSpi_asSeqHandler[CddSpi_eSeq_Count];
extern tsCddSpiTransferData                         CddSpi_msInterleaveData[CddSpi_eIfc_Count][10];
extern volatile uint16                              aunCddSpiReceiveData[CddSpi_eIfc_Count][10];
extern volatile boolean                             _init;
#endif

extern uint8                                        CddSpi_ucState;
extern tsCddSpiIfcCfg                               CddSpi_asIfcCfg[CddSpi_eIfc_Count];

//Spi status fault
#if (CDDSPI_STATUS_FAULT == STD_ON)
extern uint8                                        CddSpi_ucStatusFaultVal;
#endif

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
extern tsCddSpiCbData                               CDDSPI_CONCAT(CddSpi_asSpiDevCb_, SBC)[];
extern tsCddSpiCbData                               CDDSPI_CONCAT(CddSpi_asSpiDevCb_, BOOST)[];
extern tsCddSpiCbData                               CDDSPI_CONCAT(CddSpi_asSpiDevCb_, STP)[];
extern tsCddSpiCbData                               CDDSPI_CONCAT(CddSpi_asSpiDevCb_, BUCK_0_5)[];
extern tsCddSpiDevSeqData                           CDDSPI_CONCAT(CddSpi_asSeqDataIfc_, 0)[];
extern tsCddSpiDevSeqData                           CDDSPI_CONCAT(CddSpi_asSeqDataIfc_, 1)[];
extern tsCddSpiSeqData                              CddSpi_asSeqData[];
extern tsCddSpiDevCfg                               CddSpi_asDeviceCfg[];
extern tsCddSpiSeqHandler                           CddSpi_asSeqHandler[CddSpi_eSeq_Count];
#endif

//=============================================================================
//  Global variables stubs
//=============================================================================

static uint8                                        Mt_CddSpi_ucState;
static tsCddSpiIfcCfg                               Mt_CddSpi_asIfcCfg[CddSpi_eIfc_Count];
#if (CDDSPI_STATUS_FAULT == STD_ON)
static uint8                                        Mt_CddSpi_ucStatusFaultVal;
#endif
static tsCddSpi_S32K146_PERI                        Mt_dummyPERI;
#if (CDDSPI_DYNAMIC_CFG == STD_ON)
static tsCddSpiDevDynCfg                            Mt_CddSpi_asDevDynCfg[CddSpi_eDev_Count];
#endif

//Spi status fault
#if (CDDSPI_STATUS_FAULT == STD_ON)
static uint8                                        Mt_CddSpi_ucStatusFaultVal;
#endif

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
static  tsCddSpiCbData                              CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, SBC)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_, SBC)];
static  tsCddSpiCbData                              CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BOOST)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_, BOOST)];
static  tsCddSpiCbData                              CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, STP)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_, STP)];
static  tsCddSpiCbData                              CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BUCK_0_5)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_, BUCK_0_5)];
static  tsCddSpiDevSeqData                          CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC1)[1]; //Devices attached to Seq Ifc 1
static  tsCddSpiDevSeqData                          CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC0)[3]; //Devices attached to Seq Ifc 0 
static  tsCddSpiSeqData                             Mt_CddSpi_asSeqData[CddSpi_eSeq_Count];
static  tsCddSpiDevCfg                              Mt_CddSpi_asDeviceCfg[CddSpi_eDev_Count];
static  tsCddSpiSeqHandler                          Mt_CddSpi_asSeqHandler[CddSpi_eSeq_Count];
#endif


//=============================================================================
// Module function declarations
//=============================================================================
#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
extern void                                         CddSpi_ProcessSequence(uint8 ucIdx);
extern void                                         CddSpi_ProcessRxData(uint8 ucIdx);
extern void                                         CddSpi_ProcessTxData(uint8 ucIdx);
extern void                                         CddSpi_UpdateDevRxData(tsCddSpiDevSeqData* psDevData);
extern void                                         CddSpi_UpdateDevTxData(tsCddSpiDevSeqData* psDevData);
extern void                                         CddSpi_HandleTransmissionInCyclicIrqMode(uint8 ucIdx);
extern void                                         CddSpi_HandleTransmissionInCyclicPollingMode(uint8 ucIdx);
extern void                                         CddSpi_HandleTransmissionInCyclicDMAMode(uint8 ucIdx);
extern void                                         CddSpi_CalculateIfcSeqMap(uint8 ucIdx);
extern void                                         CddSpi_ISRHandle(uint8 ucIdx);
#if (CDDSPI_DYNAMIC_CFG == STD_ON)
extern boolean                                      CddSpi_SetDynamicCfg(uint8 ucDev);
extern void                                         CddSpi_UnSetDevCb(uint8 ucDev, uint8 ucCbIdx);
#endif
#endif

extern boolean                                      CddSpi_GetEFTData(tieEftDataPtr* psEFTDAta);


//=============================================================================
// Module function parameter stubs
//=============================================================================

//=============================================================================
// Module function return value stubs
//=============================================================================

//=============================================================================
// Module static variables inside functions 
//=============================================================================

#endif // TEST_2023_08_25_H_
