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
/// \file  CddSpi.c
///
/// \brief Complex Driver  Spi
///        This module provides services for SPI transmission in Motorola Master Mode for a  multislave scenario. 
///        It provides 2 different operation modes: SINGLE OPERATION Mode and CYCLIC OPERATION Mode
///        The SINGLE OPERATION Mode is used to provide asynchronous single transmissions when they are demanded.
///        The CYCLIC OPERATION Mode is used to  provide cyclic transmissions in which a set of
///        Transmission and Reception Callbacks are called to send data from the Upper Software Layer and receive 
///        data from Lower Software Layer with a configurable period.
///
//-----------------------------------------------------------------------------

//=============================================================================
//  includes
//=============================================================================
//#include <Std_Types.h>
#include <CddSpi.h>
#include <CddSpi_Types.h>
#include <AL_Helper.h>
//#include <IntegrationTest.h>
//#include <Os.h>

//Derived implementation headers
#if (defined(CPU_S32K146) || defined(CPU_S32K142) || defined(CPU_S32K144) )
#include <S32K/S32K_14X/CddSpi_S32K_14X.h>
#endif

#if defined(CPU_PCWIN32API)
#include <PC/PC_WIN32API/CddSpi_PC_WIN32API.h>
#endif
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCddSpiInit)
SYS_LOAD_MEAS_VAR_DEC(rpCddSpi_Cycle)
#endif

//=============================================================================
// Preprocessor definitions
//=============================================================================
//Sequence context
#define CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK         0x01U
#define CDDSPI_SEQ_CONTEXT_COMPLETE_MSK            0x02U
#define CDDSPI_SEQ_CONTEXT_INITIALIZED_POS         0U
#define CDDSPI_SEQ_CONTEXT_COMPLETE_POS            1U


//=============================================================================
// Private typedefs 
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
}teCddSpiIfcCyclicMode;
#endif

typedef struct tsCddSpiIfcCfg
{
  CONST_AL uint8                  ucIfcMap;
  #if (CDDSPI_SINGLE_OPERATION == STD_ON)
  CONST_AL teCddSpiIfcSingleMode  eIfcSingleMode;
  #endif
  #if (CDDSPI_CYCLIC_OPERATION == STD_ON)
  CONST_AL teCddSpiIfcCyclicMode  eIfcCyclicMode;
           uint8                  ucSeqMap;
  #endif
}tsCddSpiIfcCfg;

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
//Ifc seq enum
#define CDDSPI_MAC_DECL_IFCSEQ_ENUM
#include <CddSpi_Cfg.h>
#undef CDDSPI_MAC_DECL_IFCSEQ_ENUM

typedef void   (*tfpCddSpiRxCb)(uint16 unId, uint32 ulData);
typedef uint32 (*tfpCddSpiTxCb)(uint16 unId);
typedef uint8  (*tfpCddSpiCrc) (uint8* pucData, uint32 ulLength, uint8 ucStartVal, boolean boFirstCall);

typedef struct tsCddSpiDevCb
{
  tfpCddSpiTxCb fpTx;
  tfpCddSpiRxCb fpRx;
}tsCddSpiDevCb;

typedef struct tsCddSpiCbData
{
           tsCddSpiDevCb  sDevCb;
  CONST_AL uint16         unCbId;
}tsCddSpiCbData;

typedef struct tsCddSpiDevSeqData
{
           tsCddSpiCbData* psCbData;
           uint16*         punTxBuff;
           uint16*         punRxBuff;
  CONST_AL teCddSpiDev     eDev;
}tsCddSpiDevSeqData;

typedef struct tsCddSpiSeqData
{
           tsCddSpiDevSeqData* psDevData;
  CONST_AL uint8               ucDeviceCount;
           uint8               ucFramesCount;
}tsCddSpiSeqData;

typedef struct tsCddSpiSeqHandler
{
  CONST_AL teCddSpiIfc eSpiIfc;
           uint8       ucCycleCnt;
  CONST_AL uint8       ucPrescaler;
  CONST_AL uint8       ucTimeOutMax;
           uint8       ucTimeOutCnt;
           uint8       ucSeqContext;
           uint8       ucIntDevIdx;
}tsCddSpiSeqHandler;

#endif //CDDSPI_CYCLIC_OPERATION

#if (CDDSPI_DEBUG         == STD_ON)
#if (CDDSPI_DEBUG_PROFILE == STD_ON)
typedef enum teCddSpiIfcError
{
  CddSpi_eIfcError_TimeOut_Idle,
  CddSpi_eIfcError_TimeOut_Tx,
  CddSpi_eIfcError_TransferNotCompletedinTime,
  CddSpi_eIfcError_TransferLost,
  CddSpi_eIfcError_DeviceAccess,
  CddSpi_eIfcError_Count,
}teCddSpiIfcError;

typedef enum teCddSpiOperationError
{
  CddSpi_eOpError_SingleOperationAccess,
  CddSpi_eOpError_CyclicOperationAccess,
  CddSpi_eOpError_DynConfData,
  CddSpi_eOpError_Count,
}teCddSpiOperationError;

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
typedef struct tsCddSpiCyclicErrorEntry
{
  uint32           ulCycle;
  teCddSpiIfcError eIfcError;
}tsCddSpiCyclicErrorEntry;

typedef struct tsCddSpiCyclicErrorRecord
{
  tsCddSpiCyclicErrorEntry  asErrorEntry[CDDSPI_DEBUG_CYCLIC_RECORD_SIZE];
  uint8                     ucIdx;
}tsCddSpiCyclicErrorRecord;
#endif
typedef struct tsCddSpiProfile
{
  uint32            aulIfcErrorCnt                 [CddSpi_eIfc_Count][CddSpi_eIfcError_Count];
  uint32            aulOpErrorCnt                  [CddSpi_eOpError_Count];
  #if (CDDSPI_CYCLIC_OPERATION == STD_ON)
  uint16            aunTxBuff                      [CddSpi_eIfc_Count][CDDSPI_DEBUG_SEQ_BUFF_SIZE];
  uint8             aucTxBuffIdx                   [CddSpi_eIfc_Count];
  uint16            aunRxBuff                      [CddSpi_eIfc_Count][CDDSPI_DEBUG_SEQ_BUFF_SIZE];
  uint8             aucRxBuffIdx                   [CddSpi_eIfc_Count];
  uint32            aulCycleCnt                    [CddSpi_eIfc_Count];
  tsCddSpiCyclicErrorRecord asCyclicErrorRecord    [CddSpi_eIfc_Count];
  uint8             ucCyclesInjection;
  #endif
}tsCddSpiProfile;
#endif //CDDSPI_DEBUG_PROFILE

#if ((CDDSPI_DEBUG_ITM_RUNNABLE == STD_ON) || (CDDSPI_DEBUG_ITM_INTERRUPT == STD_ON))
typedef enum teCddSpiItmCheckPoint
{
  CddSpi_eItmCP_Entry,
  CddSpi_eItmCP_Exit,
}teCddSpiItmCheckPoint;

typedef enum teCddSpiItmChannel
{
  CddSpi_eItmChannel_Runnable,
  CddSpi_eItmChannel_Interrupt,
}teCddSpiItmChannel;
#endif //CDDSPI_DEBUG_ITM
#endif //CDDSPI_DEBUG


//=============================================================================
// Private variables
//=============================================================================
//Device handler
#define CDDSPI_MAC_DECL_DEVHANDLE
#include <CddSpi_Cfg.h>
#undef  CDDSPI_MAC_DECL_DEVHANDLE

//Ifc Hw Mode 
#define CDDSPI_MAC_DECL_IFCCFG
#include <CddSpi_Cfg.h>
#undef  CDDSPI_MAC_DECL_IFCCFG

#if (CDDSPI_DYNAMIC_CFG == STD_ON)
  //Dev Dynamic Cfg
  #define CDDSPI_MAC_DECL_DEVDYNCFG
  #include <CddSpi_Cfg.h>
  #undef  CDDSPI_MAC_DECL_DEVDYNCFG
#endif

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
  //CBs prototypes
  #define CDDSPI_MAC_DECL_CBS
  #include <CddSpi_Cfg.h>
  #undef  CDDSPI_MAC_DECL_CBS
  //Device CBs and CbIds
  #define CDDSPI_MAC_DECL_DEVCB
  #include <CddSpi_Cfg.h>
  #undef  CDDSPI_MAC_DECL_DEVCB
  #ifndef UNIT_TEST
    #define CDDSPI_MAC_DECL_DEVCB_ASSERT
    // PRQA S 605 EOF // Justification: Intended assertion statement
    #include <CddSpi_Cfg.h>
    #undef  CDDSPI_MAC_DECL_DEVCB_ASSERT
  #endif
  //Device Tx Buffer 
  #define CDDSPI_MAC_DECL_TXBUFF
  #include <CddSpi_Cfg.h>
  #undef  CDDSPI_MAC_DECL_TXBUFF
  //Device Rx Buffer 
  #define CDDSPI_MAC_DECL_RXBUFF
  #include <CddSpi_Cfg.h>
  #undef  CDDSPI_MAC_DECL_RXBUFF
  //Sequence data per interface
  #define CDDSPI_MAC_DECL_SEQDATAIFC
  #include <CddSpi_Cfg.h>
  #undef  CDDSPI_MAC_DECL_SEQDATAIFC
  //Full sequence data
  #define CDDSPI_MAC_DECL_SEQDATA
  #include <CddSpi_Cfg.h>
  #undef  CDDSPI_MAC_DECL_SEQDATA
  //Sequence handler
  #define CDDSPI_MAC_DECL_SEQHANDLE
  #include <CddSpi_Cfg.h>
  #undef  CDDSPI_MAC_DECL_SEQHANDLE

  #define CDDSPI_MAC_DECL_INTERLEAVE_DATA
  #include <CddSpi_Cfg.h>
  #undef  CDDSPI_MAC_DECL_INTERLEAVE_DATA
#endif

//Spi driver state
STATIC_AL uint8 CddSpi_ucState = CDDSPI_STATE_RESET;

//Spi status fault
#if (CDDSPI_STATUS_FAULT == STD_ON)
STATIC_AL uint8 CddSpi_ucStatusFaultVal;
#endif

//Spi driver profiling
#if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
  STATIC_AL volatile tsCddSpiProfile CddSpi_sProfile;
#endif

//=============================================================================
// Private functions prototypes
//=============================================================================
#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
STATIC_AL void CddSpi_ProcessSequence(uint8 ucIdx);
STATIC_AL void CddSpi_ProcessRxData(uint8 ucIdx);
STATIC_AL void CddSpi_ProcessTxData(uint8 ucIdx);
STATIC_AL void CddSpi_UpdateDevRxData(tsCddSpiDevSeqData* psDevData);
STATIC_AL void CddSpi_UpdateDevTxData(tsCddSpiDevSeqData* psDevData);
STATIC_AL void CddSpi_HandleTransmissionInCyclicIrqMode(uint8 ucIdx);
STATIC_AL void CddSpi_HandleTransmissionInCyclicPollingMode(uint8 ucIdx);
STATIC_AL void CddSpi_HandleTransmissionInCyclicDMAMode(uint8 ucIdx);
STATIC_AL void CddSpi_CalculateIfcSeqMap(uint8 ucIdx);
STATIC_AL void CddSpi_ISRHandle(uint8 ucIdx);
  #if (CDDSPI_DYNAMIC_CFG == STD_ON)
  STATIC_AL boolean  CddSpi_SetDynamicCfg(uint8 ucDev);
  STATIC_AL void     CddSpi_UnSetDevCb(uint8 ucDev, uint8 ucCbIdx);
  #endif
#endif

//=============================================================================
// Public functions  implementation
//=============================================================================

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief riCddSpiInit
///
/// \descr Init Runnable of module CddSpi.It acts as a function wrapper which calls
///        CddSpi_Start for module initialization at Rte context.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void riCddSpiInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCddSpiInit)
#endif

    CddSpi_Start();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCddSpiInit)
#endif
}

//-----------------------------------------------------------------------------
/// \brief  rpCddSpi_Cycle
///
/// \descr  Cyclic runnable  of module CddSpi. It acts as a function wrapper which
///         calls the rpCddSpi_Cycle for cyclic handling at Rte context.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void rpCddSpi_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCddSpi_Cycle)
#endif

  #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_ITM_RUNNABLE == STD_ON))
  CDDSPI_DEBUG_ITM(CddSpi_eItmChannel_Runnable, CddSpi_eItmCP_Entry);
  #endif

  CddSpi_Cycle();

  #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
  for (uint8 ucIdx = 0U; ucIdx < CddSpi_sProfile.ucCyclesInjection ; ucIdx++) {CddSpi_Cycle(); }
  #endif

  #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_ITM_RUNNABLE == STD_ON))
  CDDSPI_DEBUG_ITM(CddSpi_eItmChannel_Runnable, CddSpi_eItmCP_Exit);
  #endif

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCddSpi_Cycle)
#endif
}
#endif

//-----------------------------------------------------------------------------
/// \brief CddSpi_Init
///
/// \descr Initialize all SPI units configured in CddSpi_Cfg.h by calling derived initialization functions 
///        Switch to SINGLE Operation Mode. Driver must be in Reset State
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_Init(void)
{
  //Check if driver has not been initialized yet to proceed the initialization sequence
  if (CddSpi_ucState == CDDSPI_STATE_RESET)
  {
    //Initialize all configured Spi interfaces
    for (uint8 ucIfcIdx = 0U; ucIfcIdx < (uint8)CddSpi_eIfc_Count; ucIfcIdx++)
    {
      CddSpi_InitIfc_Deriv(CddSpi_asIfcCfg[ucIfcIdx].ucIfcMap);
    }
    //Switch mode to SINGLE Operation as default Operation mode after initialization
    CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;
  }
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_DeInit
///
/// \descr DeInitialize all SPI units configured in CddSpi_Cfg.h by calling derived deinitialization functions
///        Switch to Reset State. Driver must be either in Single Operation Mode or Cyclic Operation Mode State.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_DeInit(void)
{
  //Check if driver is already deinitialized to proceed with deinitialization sequence
  if (CddSpi_ucState != CDDSPI_STATE_RESET)
  {
    //Initialize all configured Spi interfaces
    for (uint8 ucIdx = 0U; ucIdx < (uint8)CddSpi_eIfc_Count; ucIdx++)
    {
      CddSpi_DeInitIfc_Deriv(CddSpi_asIfcCfg[ucIdx].ucIfcMap);
    }
    //Switch to Reset state
    CddSpi_ucState = CDDSPI_STATE_RESET;
  }
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_GetState
///
/// \descr Return CddSpi State:
///         -CDDSPI_STATE_RESET
///         -CDDSPI_STATE_SINGLE_OPERATION
///         -CDDSPI_STATE_CYCLIC_OPERATION
///
/// \param  -
///
/// \return teCddSpiState
//-----------------------------------------------------------------------------
uint8 CddSpi_GetState(void)
{
  return CddSpi_ucState;
}

#if (CDDSPI_SINGLE_OPERATION == STD_ON) 
//-----------------------------------------------------------------------------
/// \brief  CddSpi_TransferMsg
///
/// \descr   Send/Receive single SPI messages  (16-bit max.).
///          The amount of SPI elements to sent/received is configured in CddSpi_Cfg.h for 
///          every Device by setting the parameter "Elements" in macro CDDSPI_DEV_CFG.
///
/// \param  ucDevice : target SPI peripheral
///                   - use macro CDDSPI_DEVICE(name) as parameter
///                   - name = name of SPI peripheral specified in CddSpi_Cfg.h
///         punData  :  in/out parameter (pointer)
///                   - data given in this variable will be sent to peripheral
///                   - data received by the peripheral will be stored in this
///                     variable if the function returns "true"
///
/// \return bool    TRUE:  Transfer successful
///                 FALSE: Transfer not performed
///
//-----------------------------------------------------------------------------
boolean CddSpi_TransferMsg(uint8 ucDevice, uint16* punData)
{
  boolean boRetVal = FALSE;

  #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
  uint8 ucIfcIdx ;
  for (uint8 ucIdx = 0U; ucIdx < (uint8)CddSpi_eIfc_Count; ucIdx++)
  {
    if (CddSpi_asIfcCfg[ucIdx].ucIfcMap == CddSpi_asDeviceCfg[ucDevice].ucSpiIfc)
    {
      ucIfcIdx = ucIdx;
      break;
    }
  }
  #endif

  //Check if driver is in SINGLE OPERATION mode
  if (CddSpi_ucState == CDDSPI_STATE_SINGLE_OPERATION)
  {
    //Check if device ID is on the configured device list
    if (ucDevice < (uint8)CddSpi_eDev_Count)
    {
      //Use a Time Out to avoid permanent blocked scenario
      uint32 ulTimer = CDDSPI_TIMEOUT_VAL;
      //Get Device Transmission Parameters
      const tsCddSpiDevCfg * const psDevCfg = &CddSpi_asDeviceCfg[ucDevice];
      //Configure Transmission Paramters
      CddSpi_ConfigureTransfer_Deriv(psDevCfg);

      //Fill Out Hw Fifo  to transmit data
      CddSpi_TxFifoPut_Deriv(psDevCfg->ucSpiIfc,
        punData,
        psDevCfg->ucElements);
      //Wait until transfer is completed or time out is elapsed
      while ((CddSpi_TransferComplete_Deriv(psDevCfg->ucSpiIfc, psDevCfg->ucElements) == FALSE) &&
        (ulTimer > 0U))
      {
        ulTimer--;
      }

      //Get data from Hw Fifo if time Out is not elapsed
      if (ulTimer > 0U)
      {
        boRetVal = TRUE;
        CddSpi_RxFifoGet_Deriv(psDevCfg->ucSpiIfc,
          punData,
          psDevCfg->ucElements);
      }
      else
      {
        #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
        CddSpi_sProfile.aulIfcErrorCnt[ucIfcIdx][CddSpi_eIfcError_TimeOut_Tx]++;
        #endif
      }
    }
    else
    {
      #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
      CddSpi_sProfile.aulIfcErrorCnt[ucIfcIdx][CddSpi_eIfcError_DeviceAccess]++;
      #endif
    }
  }
  else
  {
    #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
    CddSpi_sProfile.aulOpErrorCnt[CddSpi_eOpError_SingleOperationAccess]++;
    #endif
  }

  return boRetVal;
}
#endif

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSpi_Start
///
/// \descr Trigger the CYCLIC OPERATION mode.
///        Execute Dynamic Configuratoin to update number of elements if this option is configured
///        in CddSpi_Cfg.h
///        Calculate Interface mapping for every sequence.
///        Module must be in SINGLE Operation mode.
///
/// \param  - 
///
/// \return - 
//-----------------------------------------------------------------------------
void CddSpi_Start(void)
{
  boolean boRunCycleOperation = TRUE;

  //Check if module is in Single Operation mode
  if (CddSpi_ucState == CDDSPI_STATE_SINGLE_OPERATION)
  {
    //Set Device Dynamic Configuration
    #if (CDDSPI_DYNAMIC_CFG == STD_ON)
    for (uint8 ucDevIdx = 0U; ucDevIdx < (uint8)CddSpi_eDev_Count; ucDevIdx++)
    {
      if (CddSpi_SetDynamicCfg(ucDevIdx) == FALSE)
      {
        boRunCycleOperation = FALSE;

        #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
        CddSpi_sProfile.aulOpErrorCnt[CddSpi_eOpError_DynConfData]++;
        #endif

        #if (CDDSPI_STATUS_FAULT == STD_ON)
        CddSpi_ucStatusFaultVal |= CDDSPI_STATUS_FAULT_DYNAMIC_CONFIG_ERROR_MSK;
        #endif
        break;
      }
      else
      {
        //empty
      }
    }
    #endif
    if (boRunCycleOperation == TRUE)
    {

      for (uint8 ucSeqIdx = 0U; ucSeqIdx < (uint8)CddSpi_eSeq_Count; ucSeqIdx++)
      {
        tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[ucSeqIdx];
        //Temporary software timer, use GPT instead
        uint32 ulTimer = CDDSPI_TIMEOUT_VAL;

        //Wait until SPI Ifc is idle
        while ((CddSpi_IfcIdle_Deriv(CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap) == FALSE) &&
          (ulTimer > 0U))
        {
          ulTimer--;
        }

        //Calculate assigned SeqId for every Ifc
        CddSpi_CalculateIfcSeqMap(ucSeqIdx);

        #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
        if (ulTimer == 0U)
        {
          CddSpi_sProfile.aulIfcErrorCnt[psSeqHandler->eSpiIfc][CddSpi_eIfcError_TimeOut_Idle]++;
        }
        else
        {
          //empty
        }
        #endif
      }
      //Switch mode to CYCLIC operation
      CddSpi_ucState = CDDSPI_STATE_CYCLIC_OPERATION;

    }
    else
    {
      #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
      CddSpi_sProfile.aulOpErrorCnt[CddSpi_eOpError_CyclicOperationAccess]++;
      #endif
    }

    //Swith To Status Fault SA
    #if (CDDSPI_STATUS_FAULT == STD_ON)
    CddSpi_ucStatusFaultVal |= (uint8)CDDSPI_STATUS_FAULT_SA_MSK;
    #endif
  }
  else
  {
    //empty
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_Stop
///
/// \descr  Stop CYCLIC  Operation mode and switch to SINGLE Operation mode.
///         Reset internal flags/variable information
///         Driver must be in CYCLIC Operation mode
///
/// \param  -
///
/// \return -
//-----------------------------------------------------------------------------
void CddSpi_Stop(void)
{
  //Check if module is in Cyclic Operation mode
  if (CddSpi_ucState == CDDSPI_STATE_CYCLIC_OPERATION)
  {
    for (uint8 ucSeqIdx = 0U; ucSeqIdx < (uint8)CddSpi_eSeq_Count; ucSeqIdx++)
    {
      tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[ucSeqIdx];

      //Software TimeOut
      uint32 ulTimer = CDDSPI_TIMEOUT_VAL;
      //Wait until SPI Ifc is idle
      while ((CddSpi_IfcIdle_Deriv(CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap) == FALSE) &&
             (ulTimer  > 0U))
      {
        ulTimer--;
      }

      if (CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].eIfcCyclicMode == CddSpi_eIfcCyclicMode_Interrupt)
      {
        //Disable Interrupt
        CddSpi_RxIntDisable_Deriv(CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap);
      }else if (CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].eIfcCyclicMode == CddSpi_eIfcCyclicMode_DMA)
      {
        //Disable Dma Data Flow
        CddSpi_DmaStop_Deriv(CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap);
      }
      else
      {
        //empty
      }

      #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
      if (ulTimer == 0U)
      {
        CddSpi_sProfile.aulIfcErrorCnt[psSeqHandler->eSpiIfc][CddSpi_eIfcError_TimeOut_Idle]++;
      }
      else
      {
        //empty
      }
      #endif
    }
    //Switch mode to SINGLE Operation
    CddSpi_ucState = CDDSPI_STATE_SINGLE_OPERATION;

    //Swith To Status Fault SNA (Rx Cb not handled in that mode)
    #if (CDDSPI_STATUS_FAULT == STD_ON)
    CddSpi_ucStatusFaultVal &= (uint8)(~CDDSPI_STATUS_FAULT_SA_MSK);
    #endif
  }
  else
  {
    //empty
  }
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_Cycle
///
/// \descr Cyclic module API. Process all sequences configured in CddSpi_Cfg
///        Provide Status Fault information if this option is configured in CddSpi_Cfg.
///        Module must be in CYCLIC Operation Mode.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_Cycle(void)
{
  //Check if module is in Cyclic Operation mode
  if (CddSpi_ucState == CDDSPI_STATE_CYCLIC_OPERATION)
  {
    for (uint8 ucSeqIdx = 0U; ucSeqIdx < (uint8)CddSpi_eSeq_Count; ucSeqIdx++)
    {
      CddSpi_ProcessSequence(ucSeqIdx);
      #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
      CddSpi_sProfile.aulCycleCnt[CddSpi_asSeqHandler[ucSeqIdx].eSpiIfc]++;
      #endif
    }
  }
  else
  {
    #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
    CddSpi_sProfile.aulOpErrorCnt[CddSpi_eOpError_CyclicOperationAccess]++;
    #endif
  }

  #if (CDDSPI_STATUS_FAULT == STD_ON)
  CddSpi_StatusFault(CddSpi_ucStatusFaultVal);
  #endif
}

//=============================================================================
// Private functions  implementation
//=============================================================================

#if (CDDSPI_DYNAMIC_CFG == STD_ON)
//-----------------------------------------------------------------------------
/// \brief CddSpi_SetDynamicCfg
///
/// \descr Calculate number of device elements mounted on the PCB by calling Dynamic Configuration
///        device callout configured in CddSpi_Cfg.h. Mounted devices are considered as active, not mounted
///        elements are considered as inactive. For all inactive elements a NULL_PTR Tx RX Cyclic CallBack is set
///        so that the driver does not service an inactive element in Cyclic context. 
///
///        Dynamic configuration device callbacak provides a footprint value by taking into consideration the
///        maximum number of elements which can be populated on the PCB. 
///        The maximum number of elements are set in CddSpi_Cfg.h
///
///        E.g Footprint of 5 max elements and only 0,2,4 are active:
///
///                     ---------   ---------   ---------   ---------   ---------
///        Elem Id     |    4    | |    3    | |    2    | |    1    | |    0    |
///                     ---------   ---------   ---------   ---------   ---------
///                     ---------   ---------   ---------   ---------   ---------
///        Value       |    1    | |    0    | |    1    | |    0    | |    1    |
///                     ---------   ---------   ---------   ---------   ---------
///        Output:
///                     ---------   ---------   ---------   ---------   ---------
///        Tx,Rx CBs   | USER_DEF| | NULL_PTR| | USER_DEF| | NULL_PTR| | USER_DEF|
///                     ---------   ---------   ---------   ---------   ---------
///        Elements    : 3
///
/// \param  ucDev : Device to apply dynamic configuration.
///
/// \return  boolean
///            TRUE: Dynamic configuratoin set successfully. All active CallOuts return TRUE
///            FALSE: Dynamic configuratoin not set successfully. At least one of the  active CallOuts returns FALSE
//-----------------------------------------------------------------------------
STATIC_AL boolean CddSpi_SetDynamicCfg(uint8 ucDev)
{
  boolean boRetVal = TRUE;
  //Check Dynamic Configuration Callout active
  if (CddSpi_asDevDynCfg[ucDev].fpDevDynCfgCb != NULL_PTR)
  {
    uint16  unElemFootPrint = 0U;
    //Get FootPrint from  Configuration Callout
    if (CddSpi_asDevDynCfg[ucDev].fpDevDynCfgCb(&unElemFootPrint) != FALSE)
    {
      uint8 ucElemtsCnt = 0U;

      for (uint8 ucElemIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[ucDev].ucMaxElements; ucElemIdx++ )
      {
        if ((unElemFootPrint & (uint16)1U) == (uint16)0U)
        {
          #if (CDDSPI_CYCLIC_OPERATION == STD_ON)
          //Disable all TX-RX Callbacks of non- active elements
          CddSpi_UnSetDevCb(ucDev, ucElemIdx);
          #endif
        }
        else
        {
          ucElemtsCnt++;
        }
        unElemFootPrint >>= 1U;
      }
      //Update Number of element of the device
      CddSpi_asDeviceCfg[ucDev].ucElements = ucElemtsCnt;
    }
    else
    {
      boRetVal = FALSE;
    }
  }
  else
  {
    //empty
  }

  return boRetVal;
}
#endif

//-----------------------------------------------------------------------------
/// \brief  CddSpi_ProcessSequence
///
/// \descr  Handle cycles to service TX and RX Data processing, considering pre-scaling and timeouts.
///         Check if previous transsmision has been completed. 
///         If previous transmission has been completed, process RX and TX Data.
///         By first Cycle, only TX -Data is processed , since no RX data is available yet, and
///         initialization flag is set, so that the driver knows that it can process RX Data.
///
/// \param  ucIdx : Sequence Index to be processed.
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddSpi_ProcessSequence(uint8 ucIdx)
{
  tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[ucIdx];
  tsCddSpiSeqData*    const psSeqData = &CddSpi_asSeqData[ucIdx];

  if (psSeqHandler->ucCycleCnt == 0U)
  {
    if ((psSeqHandler->ucSeqContext & CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK) != 0U)
    {
      //Check for last transfer to be complete
      //Polling   Mode: Check that all sequence frames are received
      //DMA       Mode: To be done
      //Interrupt Mode: Transfer complete flag is set in ISR
      switch (CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].eIfcCyclicMode)
      {
        case  CddSpi_eIfcCyclicMode_Polling:
          psSeqHandler->ucSeqContext |= (CddSpi_TransferComplete_Deriv(CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap, psSeqData->ucFramesCount) == TRUE) ? CDDSPI_SEQ_CONTEXT_COMPLETE_MSK : 0x00U;
          break;
        //Set always completed for the momment. TBD
        case  CddSpi_eIfcCyclicMode_DMA:
          psSeqHandler->ucSeqContext |= (CddSpi_TransferCompleteDMA_Deriv(CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap) == TRUE) ? CDDSPI_SEQ_CONTEXT_COMPLETE_MSK : 0x00U;
          break;
        //Do nothing.Transfer completion is evaulated in ISR.
        case  CddSpi_eIfcCyclicMode_Interrupt:
        default:
          break;
      }

      //Transfer complete, handle next sequence
      if ((psSeqHandler->ucSeqContext & CDDSPI_SEQ_CONTEXT_COMPLETE_MSK) != 0U)
      {
        //Reset Transmission complete flag
        psSeqHandler->ucSeqContext &= (uint8)(~CDDSPI_SEQ_CONTEXT_COMPLETE_MSK);
        //Reset Cycles TimeOut
        psSeqHandler->ucTimeOutCnt = psSeqHandler->ucTimeOutMax;
        //Process Sequence Tx and Rx Data
        CddSpi_ProcessRxData(ucIdx);
        CddSpi_ProcessTxData(ucIdx);
      }
      //Transfer not complete in time, wait until maximum wait-cycles are elapsed
      else
      {
        // if maximum cycles(timeout) are elapsed,
        // try to hanlde next sequence
        if (psSeqHandler->ucTimeOutCnt == 0U)
        {
          //Process Sequence Tx and Rx Data
          CddSpi_ProcessRxData(ucIdx);
          CddSpi_ProcessTxData(ucIdx);
          //Reset TimeOut Counter
          psSeqHandler->ucTimeOutCnt = psSeqHandler->ucTimeOutMax;

          #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
          CddSpi_sProfile.aulIfcErrorCnt[psSeqHandler->eSpiIfc][CddSpi_eIfcError_TransferLost]++;
          CddSpi_sProfile.asCyclicErrorRecord[psSeqHandler->eSpiIfc].asErrorEntry[CddSpi_sProfile.asCyclicErrorRecord[psSeqHandler->eSpiIfc].ucIdx] = (tsCddSpiCyclicErrorEntry){ CddSpi_sProfile.aulCycleCnt[psSeqHandler->eSpiIfc],
                                                                                                                                                                                  CddSpi_eIfcError_TransferLost};
          CddSpi_sProfile.asCyclicErrorRecord[psSeqHandler->eSpiIfc].ucIdx = (CddSpi_sProfile.asCyclicErrorRecord[psSeqHandler->eSpiIfc].ucIdx + 1U) % CDDSPI_DEBUG_CYCLIC_RECORD_SIZE;
          #endif
        }
        else
        {
          //if maximum wait-cycles (timeout) are not elapsed
          //ignore Rx and Tx Data processing and
          //decrement TimeOut counter 
          psSeqHandler->ucTimeOutCnt--;

          #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
          CddSpi_sProfile.aulIfcErrorCnt[psSeqHandler->eSpiIfc][CddSpi_eIfcError_TransferNotCompletedinTime]++;
          CddSpi_sProfile.asCyclicErrorRecord[psSeqHandler->eSpiIfc].asErrorEntry[CddSpi_sProfile.asCyclicErrorRecord[psSeqHandler->eSpiIfc].ucIdx] = (tsCddSpiCyclicErrorEntry){ CddSpi_sProfile.aulCycleCnt[psSeqHandler->eSpiIfc],
                                                                                                                                                                                  CddSpi_eIfcError_TransferNotCompletedinTime};
          CddSpi_sProfile.asCyclicErrorRecord[psSeqHandler->eSpiIfc].ucIdx = (CddSpi_sProfile.asCyclicErrorRecord[psSeqHandler->eSpiIfc].ucIdx + 1U) % CDDSPI_DEBUG_CYCLIC_RECORD_SIZE;
          #endif
        }

      }
    }
    else
    {
      //First Cyclce just process Tx Data
      CddSpi_ProcessTxData(ucIdx);
      //Set Initialized Flag in Sequence context variable
      psSeqHandler->ucSeqContext |= (uint8)CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK;
    }
    //Set sequence index to configured prescaler
    psSeqHandler->ucCycleCnt = psSeqHandler->ucPrescaler;
  }
  else
  {
    //Decrement sequence cycle counter, period is not elapsed
    psSeqHandler->ucCycleCnt--;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_ProcessRxData
///
/// \descr  Collect RX data from HW-Buffer if Sequence operates in Polling Mode and 
///         one single device is attached to the Spi Interface used in the sequence
///         If Sequence operates in Polling Mode and there is more than one device attached
///         to the Spi Interface used in the sequence, or the sequence operates in Interrupt Mode,
///         The RX data is already collected in subroutine CddSpi_ProcessTxData (Polling mode) or
///         in CddSpi_ISRHandle (Interrupt mode).
///         Call subroutine to provide RX-data to the upper layer.
///
/// \param  ucIdx : Sequence Index to be processed.
///
/// \return  -
//-----------------------------------------------------------------------------
STATIC_AL void CddSpi_ProcessRxData(uint8 ucIdx)
{
  tsCddSpiSeqData*    const psSeqData = &CddSpi_asSeqData[ucIdx];
  tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[ucIdx];
  volatile uint8 ucDataIdx = 0U;
  uint8 ucInterfaceIdx = CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap;

  for (uint8 ucDevIdx = 0U; ucDevIdx < psSeqData->ucDeviceCount; ucDevIdx++)
  {
    tsCddSpiDevSeqData* psDevData = &(psSeqData->psDevData[ucDevIdx]);

    #ifndef CDDSPI_AUTO_SLAVE_CONFIG
    //In Polling Mode:   If only 1 device is attached to the interface, fill out SW-Buffer with data from Hw Rx Buffer.
    //                   If more than 1 device is attached, SW-Buffer is filled out in CddSpi_HandleTransmissionInCyclicPollingMode
    //In Interrupt Mode: Sw-Buffer is already filled out with data from Hw Rx Buffer
    if ((CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].eIfcCyclicMode == CddSpi_eIfcCyclicMode_Polling) &&
                                     (psSeqData->ucDeviceCount == 1U                           )  )
    {
      //Get data from HW-Fifo
      CddSpi_RxFifoGet_Deriv(CddSpi_asDeviceCfg[psDevData->eDev].ucSpiIfc,
      psDevData->punRxBuff,
      CddSpi_asDeviceCfg[psDevData->eDev].ucElements);

      psSeqData->ucFramesCount -= CddSpi_asDeviceCfg[psDevData->eDev].ucElements;

      #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
      for (uint8 ucDevBuffIdx = 0U; ucDevBuffIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucDevBuffIdx++)
      {
        CddSpi_sProfile.aunRxBuff[CddSpi_asSeqHandler[ucIdx].eSpiIfc][CddSpi_sProfile.aucRxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc]] = psDevData->punRxBuff[ucDevBuffIdx];
        CddSpi_sProfile.aucRxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc]++;
      }
      #endif
    }
    else
    {
      //empty
    }
    #else
    //Place holder to support Auto Slave Configuration
    #endif

    if (CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].eIfcCyclicMode == CddSpi_eIfcCyclicMode_DMA)
    {
      //Fill RxBuff for each device
      for (uint8 ucElemIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucElemIdx++)
      {
        psDevData->punRxBuff[ucElemIdx] = aunCddSpiReceiveData[ucInterfaceIdx][ucDataIdx];
        ucDataIdx++;
      }
    }
    else
    {
      //empty
    }

    //Update Upper Layer Data (Rx-Callbacks)
    CddSpi_UpdateDevRxData(psDevData);
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_ProcessTxData
///
/// \descr  Call common subroutine to collect Tx-Data from Upper Layer of all devices
///         attached to the sequence and call specific subroutine to handle Tx transmission 
///         depending on the mode that the sequence operates with (Polling Interrupt or DMA)
///
/// \param   ucIdx : Sequence Index to be processed.
///
/// \return  -
//-----------------------------------------------------------------------------
STATIC_AL void CddSpi_ProcessTxData(uint8 ucIdx)
{
  tsCddSpiSeqData*    const psSeqData = &CddSpi_asSeqData[ucIdx];
  tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[ucIdx];

  #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
  CddSpi_sProfile.aucTxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc] = 0U;
  CddSpi_sProfile.aucRxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc] = 0U;
  #endif

  //Update Tx Sw-Buffer with new data from upper layer (Tx Callbacks)
  for (uint8 ucDevIdx = 0U; ucDevIdx < psSeqData->ucDeviceCount; ucDevIdx++)
  {
    CddSpi_UpdateDevTxData(&psSeqData->psDevData[ucDevIdx]);
  }

  //Handle Hw buffering depending on Sequence Cyclic Mode
  switch (CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].eIfcCyclicMode )
  {
    case  CddSpi_eIfcCyclicMode_Polling:
      CddSpi_HandleTransmissionInCyclicPollingMode(ucIdx);
      break;
    case  CddSpi_eIfcCyclicMode_Interrupt:
      CddSpi_HandleTransmissionInCyclicIrqMode(ucIdx);
      break;
    case  CddSpi_eIfcCyclicMode_DMA:
      CddSpi_HandleTransmissionInCyclicDMAMode(ucIdx);
      break;
    default:
      break;
  }

}
//-----------------------------------------------------------------------------
/// \brief  CddSpi_UpdateDevRxData
///
/// \descr  Provide Rx-Data to all active device elements of the upper layer
///
/// \param  psDevData: Pointer to device data handled cyclically
///
/// \return  -
//-----------------------------------------------------------------------------
STATIC_AL void CddSpi_UpdateDevRxData(tsCddSpiDevSeqData* psDevData)
{
  for (uint8 ucElemIdx = 0U, ucDevBuffIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucMaxElements; ucElemIdx++ )
  {
    //Adjust CallBack Indexing (from Bottom to Top)
    uint8 ucCbIdx = CddSpi_asDeviceCfg[psDevData->eDev].ucMaxElements - ucElemIdx - 1U;
    if (psDevData->psCbData[ucCbIdx].sDevCb.fpRx != NULL_PTR)
    {
      uint32 ulData = psDevData->punRxBuff[ucDevBuffIdx];
      //Call Device Rx Callback to provide Rx-Data
      psDevData->psCbData[ucCbIdx].sDevCb.fpRx(psDevData->psCbData[ucCbIdx].unCbId, ulData);
      ucDevBuffIdx++;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_UpdateDevTxData
///
/// \descr Collect Tx-Data of all active device elements of the Upper layer.
///
/// \param  psDevData : Pointer to device data handled cyclically
///
/// \return  -
//-----------------------------------------------------------------------------
STATIC_AL void CddSpi_UpdateDevTxData(tsCddSpiDevSeqData* psDevData)
{
  for (uint8 ucElemIdx = 0U, ucDevBuffIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucMaxElements; ucElemIdx++)
  {
    //Adjuat Callback Indexing (from bottom to top)
    uint8 ucCbIdx = CddSpi_asDeviceCfg[psDevData->eDev].ucMaxElements - ucElemIdx - 1U;
    if (psDevData->psCbData[ucCbIdx].sDevCb.fpTx != NULL_PTR)
    {
      //Get Raw data of Tx Callback
      uint32 ulData = psDevData->psCbData[ucCbIdx].sDevCb.fpTx(psDevData->psCbData[ucCbIdx].unCbId);

      //Update Internal Tx Device Buffer with data from Upper Layer
      psDevData->punTxBuff[ucDevBuffIdx] = (uint16)ulData;
      ucDevBuffIdx++;
    }
    else
    {
      //empty
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_HandleTransmissionInCyclicPollingMode
///
/// \descr  Buffer Tx Data in Tx HW buffer of all devices attached to the sequence 
///         to trigger a Spi Transmission.
///         If more than one device is attached to the Spi interface sequence,
///         wait until device transmission is complete and collect Rx Data in internal device buffer,
///         before triggering the transmission of the next device.
///         If one single device is attached to the Spi interface sequence, no polling is needed
///         since after transmission is triggered, data will be collected in the RX data processing
///         of the next cycle.
///
///
/// \param  ucIdx : Sequence index to be processed.
///
/// \return
//-----------------------------------------------------------------------------
STATIC_AL void CddSpi_HandleTransmissionInCyclicPollingMode(uint8 ucIdx) 
{
  tsCddSpiSeqData*    const psSeqData = &CddSpi_asSeqData[ucIdx];

  //Fill out Tx buffer and wait until transmission is complete for every
  //device, but the last (transmission parameters shall not configure again after last device)
  for (uint8 ucDevIdx = 0; ucDevIdx < psSeqData->ucDeviceCount; ucDevIdx++)
  {
    const tsCddSpiDevSeqData* psDevData = &(psSeqData->psDevData[ucDevIdx]);

    //Configure transmission parameters
    CddSpi_ConfigureTransfer_Deriv(&CddSpi_asDeviceCfg[psDevData->eDev]);

    //Transmit Tx Data
    CddSpi_TxFifoPut_Deriv(CddSpi_asDeviceCfg[psDevData->eDev].ucSpiIfc,
                           psDevData->punTxBuff,
                           CddSpi_asDeviceCfg[psDevData->eDev].ucElements);

    psSeqData->ucFramesCount += CddSpi_asDeviceCfg[psDevData->eDev].ucElements;

    #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
    for (uint8 ucDevBuffIdx = 0U; ucDevBuffIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucDevBuffIdx++)
    {
      CddSpi_sProfile.aunTxBuff[CddSpi_asSeqHandler[ucIdx].eSpiIfc][CddSpi_sProfile.aucTxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc]] = psDevData->punTxBuff[ucDevBuffIdx];
      CddSpi_sProfile.aucTxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc]++;
    }
    #endif

    #ifndef CDDSPI_AUTO_SLAVE_CONFIG 
    //If more than one device is attached to the Spi Interface, then wait
    ///until transmission if device is not the last in the sequence.
    //This is needed if MCU does not support auto CS or transmission is not handled by interrupts
    if( psSeqData->ucDeviceCount != 1U)
    {
      uint32 ulTimer = CDDSPI_TIMEOUT_VAL;
      //Wait until entries get recieved
      while ((CddSpi_TransferComplete_Deriv(CddSpi_asDeviceCfg[psDevData->eDev].ucSpiIfc, CddSpi_asDeviceCfg[psDevData->eDev].ucElements) == FALSE) &&
             (ulTimer > 0U))
      {
        ulTimer--;
      }

      #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
      if (ulTimer == 0U)
      {
        CddSpi_sProfile.aulIfcErrorCnt[CddSpi_asSeqHandler[ucIdx].eSpiIfc][CddSpi_eIfcError_TimeOut_Tx]++ ;
      }
      else
      {
        //empty
      }
      #endif

      //Get data from HW-Fifo
      CddSpi_RxFifoGet_Deriv(CddSpi_asDeviceCfg[psDevData->eDev].ucSpiIfc,
                             psDevData->punRxBuff,
                             CddSpi_asDeviceCfg[psDevData->eDev].ucElements);

      psSeqData->ucFramesCount -= CddSpi_asDeviceCfg[psDevData->eDev].ucElements;

      #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
      for (uint8 ucDevBuffIdx = 0U; ucDevBuffIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucDevBuffIdx++)
      {
        CddSpi_sProfile.aunRxBuff[CddSpi_asSeqHandler[ucIdx].eSpiIfc][CddSpi_sProfile.aucRxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc]] = psDevData->punRxBuff[ucDevBuffIdx]  ;
        CddSpi_sProfile.aucRxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc]++;
      }
      #endif

    #else
    //Place holder for implementing auto-slave config
    #endif //CDDSPI_AUTO_SLAVE_CONFIG
    }
    else
    {
      //empty
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_HandleTransmissionInCyclicIrqMode
///
/// \descr  Buffer Tx Data in Tx HW buffer of the first device attached to the sequence 
///         to trigger a Spi Transmission. Trnamission handling of the rest of the devices
///         is handled in ISR.
///
///
/// \param  ucIdx: Sequence Index to be processed
///
/// \return -
//-----------------------------------------------------------------------------
STATIC_AL void CddSpi_HandleTransmissionInCyclicIrqMode(uint8 ucIdx) 
{
  tsCddSpiSeqData*    const psSeqData = &CddSpi_asSeqData[ucIdx];
  tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[ucIdx];

  //Configure Rx trigger level of first device and transmit its data
  //Rest of the transmission/receptions are handled in ISR
  psSeqHandler->ucIntDevIdx = 0U;
  const tsCddSpiDevSeqData* psDevData = &(psSeqData->psDevData[psSeqHandler->ucIntDevIdx]);

  //Configure transmission parameter of first device
  CddSpi_ConfigureTransfer_Deriv(&CddSpi_asDeviceCfg[psDevData->eDev]);

  //Enable Rx Interrupt
  CddSpi_RxIntEnable_Deriv(CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap);

  //Fill out Hw Tx buffer with data of first device
  CddSpi_TxFifoPut_Deriv(CddSpi_asDeviceCfg[psDevData->eDev].ucSpiIfc, 
                         psDevData->punTxBuff,
                         CddSpi_asDeviceCfg[psDevData->eDev].ucElements);

  #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
  for (uint8 ucDevBuffIdx = 0U; ucDevBuffIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucDevBuffIdx++)
  {
    CddSpi_sProfile.aunTxBuff[CddSpi_asSeqHandler[ucIdx].eSpiIfc][CddSpi_sProfile.aucTxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc]] = psDevData->punTxBuff[ucDevBuffIdx];
    CddSpi_sProfile.aucTxBuffIdx[CddSpi_asSeqHandler[ucIdx].eSpiIfc]++;
  }
  #endif
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_HandleTransmissionInCyclicDMAMode
///
/// \descr  Fill the buffer with the command and data words for all transfers
///         cyclic mode.
///
///
/// \param  ucIdx: Sequence Index to be processed
///
/// \return -
//-----------------------------------------------------------------------------
STATIC_AL void CddSpi_HandleTransmissionInCyclicDMAMode(uint8 ucIdx)
{
  tsCddSpiSeqData*    const psSeqData = &CddSpi_asSeqData[ucIdx];
  tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[ucIdx];
  uint8 ucInterfaceIdx = CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap;
  volatile uint8 ucDataIdx = 0U;

  for (uint8 ucDevIdx = 0; ucDevIdx < psSeqData->ucDeviceCount; ucDevIdx++)
  {
    const tsCddSpiDevSeqData* psDevData = &(psSeqData->psDevData[ucDevIdx]);

    //Configure transmission parameters
    //This could be done by specific part
    for (uint8 ucElemIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucElemIdx++)
    {
      CddSpi_msInterleaveData[ucInterfaceIdx][ucDataIdx].ulTCR_data = CddSpi_GetCommandWord_Deriv( &CddSpi_asDeviceCfg[psDevData->eDev], 
                                                                                                   ucElemIdx);
      CddSpi_msInterleaveData[ucInterfaceIdx][ucDataIdx].ulTDR_data = (uint32)psDevData->punTxBuff[ucElemIdx];
      ucDataIdx++;
    }
  }

  /*
    Msg:  310(Casting to different object pointer type.)
    Msg: 3305(Pointer cast to stricter alignment.)
  */
  //start DMA transfer
  CddSpi_StartTransfer_Deriv( ucInterfaceIdx,
                              (uint32*)&(CddSpi_msInterleaveData[ucInterfaceIdx][0]), // PRQA S 310       //the cast is allowed since we need memory address
                              (uint32*)&(aunCddSpiReceiveData[ucInterfaceIdx][0]),    // PRQA S 310, 3305 //the cast is allowed since we need memory address
                              (uint16)ucDataIdx);
}

//-----------------------------------------------------------------------------
/// \brief CddSpi_CalculateIfcSeqMap
///
/// \descr Calculate the Spi Interface Index that the Sequence operates with
///        This depends on the order the Sequence map has been configured in CddSpi_Cfg.h
///
///        E.g IFC5 Ifc -> Index 0, IFC4 ->Ifc Index 1
///        CDDSPI_IFC(CDDSPI_IFC5, CDDSPI_SINGLE_POLLING, CDDSPI_CYCLIC_POLLING)
///        CDDSPI_IFC(CDDSPI_IFC4, CDDSPI_SINGLE_POLLING, CDDSPI_CYCLIC_INTERRUPT)
///
///        IFC4 -> Seq Index 0    , IFC5->Seq Index 1
///        BEGIN_CDDSPI_SEQ(CDDSPI_IFC4, 0, 0, 3)
///         (...)
///        END_CDDSPI_SEQ
///         
///        BEGIN_CDDSPI_SEQ(CDDSPI_IFC5, 0, 0, 3)
///        (...)
///        END_CDDSPI_SEQ
///
/// \param  ucIdx : Sequence Index to be processed
///
/// \return 
//-----------------------------------------------------------------------------
STATIC_AL void CddSpi_CalculateIfcSeqMap(uint8 ucIdx)
{
  uint8 ucIfcIdx = 0U;
  while (((uint8)CddSpi_asSeqHandler[ucIdx].eSpiIfc != ucIfcIdx) && (ucIfcIdx < (uint8)CddSpi_eIfc_Count))
  {
    ucIfcIdx++;
  }
  
  CddSpi_asIfcCfg[ucIfcIdx].ucSeqMap = ucIdx;
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_UnSetDevCb
///
/// \descr  Assign NULL_PTR value to the CallBack Index of the Device which are
///         passed as arguments.
///         Function is called at Dynamic Configuration context to disable all
///         TX-RX Callbacks of inactive devices
///
/// \param  ucDev   : Device Index
/// \param  ucCbIdx : CallBack Index
///
/// \return 
//-----------------------------------------------------------------------------
#if (CDDSPI_DYNAMIC_CFG == STD_ON)
STATIC_AL void CddSpi_UnSetDevCb(uint8 ucDev, uint8 ucCbIdx)
{
  for (uint8 ucSeqIdx = 0U; ucSeqIdx < (uint8)CddSpi_eSeq_Count; ucSeqIdx++)
  {
    //Only check Ifc Seq that the Dev is attached to
    if (CddSpi_asIfcCfg[CddSpi_asSeqHandler[ucSeqIdx].eSpiIfc].ucIfcMap == CddSpi_asDeviceCfg[ucDev].ucSpiIfc )
    {
      for (uint8 ucDevIdx = 0U; ucDevIdx < CddSpi_asSeqData[ucSeqIdx].ucDeviceCount; ucDevIdx++)
      {
        if ((uint8)CddSpi_asSeqData[ucSeqIdx].psDevData[ucDevIdx].eDev == ucDev)
        {
          CddSpi_asSeqData[ucSeqIdx].psDevData[ucDevIdx].psCbData[ucCbIdx].sDevCb.fpTx = NULL_PTR;
          CddSpi_asSeqData[ucSeqIdx].psDevData[ucDevIdx].psCbData[ucCbIdx].sDevCb.fpRx = NULL_PTR;
          break;
        }
        else
        {
          //empty
        }
      }
      break;
    }
    else
    {
      //empty
    }
  }
}
#endif

//-----------------------------------------------------------------------------
/// \brief CddSpi_ISRHandle
///
/// \descr ISR function Handler
///        Collect RX-Data of the device by which the transmission has been triggered
///        and trigger transmission of next device of the sequence.
///        If no more device present on the sequence, set COMPLETE flag in sequence context data.
///        
///
/// \param  ucIdx : Interrface Index in which a Interrupt has been triggered (CddSpi_Ifc_X, X  [0:7])
///
/// \return -
//-----------------------------------------------------------------------------
//STATIC_AL void CddSpi_ISRHandle(uint8 ucIdx)
//{
//  if (CddSpi_RxEventTriggered_Deriv(CddSpi_asIfcCfg[ucIdx].ucIfcMap) == TRUE)
//  {
//          tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[CddSpi_asIfcCfg[ucIdx].ucSeqMap];
//    const tsCddSpiDevSeqData*       psDevData    = &(CddSpi_asSeqData[CddSpi_asIfcCfg[ucIdx].ucSeqMap].psDevData[psSeqHandler->ucIntDevIdx]);
//
//    //Fill out SW-Buffer with data from Hw Rx Buffer 
//    CddSpi_RxFifoGet_Deriv(CddSpi_asDeviceCfg[psDevData->eDev].ucSpiIfc,
//                           psDevData->punRxBuff,
//                           CddSpi_asDeviceCfg[psDevData->eDev].ucElements);
//
//    #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
//    for (uint8 ucDevBuffIdx = 0U; ucDevBuffIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucDevBuffIdx++)
//    {
//      //Get data from HW-Fifo
//      CddSpi_sProfile.aunRxBuff[ucIdx][CddSpi_sProfile.aucRxBuffIdx[ucIdx]] = (uint16) psDevData->punRxBuff[ucDevBuffIdx];
//      CddSpi_sProfile.aucRxBuffIdx[ucIdx]++;
//    }
//    #endif
//
//
//    //Clear Trigger Event(it must be cleared after Hw Buffer is empty)
//    CddSpi_RxTriggerEventClear_Deriv(CddSpi_asIfcCfg[ucIdx].ucIfcMap);
//    
//    //Increment Device Index to handle next transmission
//    psSeqHandler->ucIntDevIdx++;
//
//    //Check if device is not the last in the sequence
//    //If last device, Tx is not performed
//    if (psSeqHandler->ucIntDevIdx < CddSpi_asSeqData[CddSpi_asIfcCfg[ucIdx].ucSeqMap].ucDeviceCount)
//    {
//      psDevData = &(CddSpi_asSeqData[CddSpi_asIfcCfg[ucIdx].ucSeqMap].psDevData[psSeqHandler->ucIntDevIdx]);
//      //Configure transmission parameter of first device
//      //Configure Rx trigger level of next device 
//      CddSpi_ConfigureTransfer_Deriv(&CddSpi_asDeviceCfg[psDevData->eDev]);
//      //Fill out Hw Tx buffer with data of next device
//      CddSpi_TxFifoPut_Deriv(CddSpi_asDeviceCfg[psDevData->eDev].ucSpiIfc,
//                             psDevData->punTxBuff,
//                             CddSpi_asDeviceCfg[psDevData->eDev].ucElements);
//
//      #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_PROFILE == STD_ON))
//      for (uint8 ucDevBuffIdx = 0U; ucDevBuffIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucDevBuffIdx++)
//      {
//
//        CddSpi_sProfile.aunTxBuff[ucIdx][CddSpi_sProfile.aucTxBuffIdx[ucIdx]] = psDevData->punTxBuff[ucDevBuffIdx];
//        CddSpi_sProfile.aucTxBuffIdx[ucIdx]++;
//      }
//      #endif
//
//    }
//    else
//    {
//      CddSpi_RxIntDisable_Deriv(CddSpi_asIfcCfg[ucIdx].ucIfcMap);
//      psSeqHandler->ucSeqContext |= CDDSPI_SEQ_CONTEXT_COMPLETE_MSK;
//    }
//  }
//}

//=============================================================================
//  ISRs
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  ISR(CddSpi_IRQ4)
///
/// \descr  Interrupt Service Routine which calls internal subroutine to 
///         handle Spi transmission in Interrupt Mode.
///
/// \param  -
///
/// \return  -
//-----------------------------------------------------------------------------

//ISR(CddSpi_IRQ4)
//{
//  #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_ITM_INTERRUPT == STD_ON))
//  CDDSPI_DEBUG_ITM(CddSpi_eItmChannel_Interrupt, CddSpi_eItmCP_Entry);
//  #endif
//
//  CddSpi_ISRHandle((uint8)CddSpi_eIfc_4);
//
//  #if ((CDDSPI_DEBUG == STD_ON) && (CDDSPI_DEBUG_ITM_INTERRUPT == STD_ON))
//  CDDSPI_DEBUG_ITM(CddSpi_eItmChannel_Interrupt, CddSpi_eItmCP_Exit);
//  #endif
//}
#endif
