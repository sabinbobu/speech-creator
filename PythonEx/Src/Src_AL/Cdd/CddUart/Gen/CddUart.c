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
/// \file  CddUart.c
///
/// \brief Complex Driver  Uart 
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
///
//-----------------------------------------------------------------------------

//=============================================================================
//  includes
//=============================================================================
//#include <Std_Types.h>
#include <CddUart.h>
#include <CddUart_Types.h>
#include <AL_Helper.h>

//Derived implementation headers
#if (defined(CPU_S32K146) || defined(CPU_S32K142) || defined(CPU_S32K144) )
#include <CddUart_S32K_14X.h>
#endif

#if defined(CPU_PCWIN32API)
#include <PC/PC_WIN32API/CddUart_PC_WIN32API.h>
#endif
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCddUartInit)
SYS_LOAD_MEAS_VAR_DEC(rpCddUart_Cycle)
#endif

//=============================================================================
// Preprocessor definitions
//=============================================================================
//Sequence context
#define CDDUART_SEQ_CONTEXT_INITIALIZED_MSK         0x01U
#define CDDUART_SEQ_CONTEXT_COMPLETE_MSK            0x02U
#define CDDUART_SEQ_CONTEXT_INITIALIZED_POS         0U
#define CDDUART_SEQ_CONTEXT_COMPLETE_POS            1U

#define CDDUART_BAUDRATE_CODING_500Kbps             5U
#define CDDUART_BAUDRATE_CODING_1Mbps               10U

#define CDDUART_UNKNOWN_DEVICE                      0xFFU


//=============================================================================
// Private typedefs 
//=============================================================================
typedef boolean(*tfpCddUartDevDynCfg)(uint8 ucDevUartCfg, uint8* pucBaudRate, uint8 *pucMountedDev);

typedef struct tsCddUartDevDynCfg
{
  tfpCddUartDevDynCfg fpDevDynCfgCb;
}tsCddUartDevDynCfg;

typedef enum teCddUartIfcSingleMode
{
  CddUart_eIfcSingleMode_Polling    = 0,
  CddUart_eIfcSingleMode_Interrupt  = 1,
  CddUart_eIfcSingleMode_DMA        = 2,
}teCddUartIfcSingleMode;

typedef enum teCddUartIfcCyclicMode
{
  CddUart_eIfcCyclicMode_Polling    = 0,
  CddUart_eIfcCyclicMode_Interrupt  = 1,
  CddUart_eIfcCyclicMode_DMA        = 2,
}teCddUartIfcCyclicMode;

typedef struct tsCddUartIfcCfg
{
  CONST_AL uint8                    ucIfcMap;
  CONST_AL teCddUartIfcSingleMode   eIfcSingleMode;
  CONST_AL teCddUartIfcCyclicMode   eIfcCyclicMode;
  uint8                             ucSeqMap;
}tsCddUartIfcCfg;

//Ifc seq enum
#define CDDUART_MAC_DECL_IFCSEQ_ENUM
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef CDDUART_MAC_DECL_IFCSEQ_ENUM

typedef void  (*tfpCddUartRxCb)(const uint8* pucRxData, boolean boRxStatus);
typedef void  (*tfpCddUartTxCb)(tsCddUart_MessageEntryType *psTxCbData);
typedef uint8 (*tfpCddUartCrc) (uint8* pucData, uint32 ulLength, uint8 ucStartVal, boolean boFirstCall);

typedef struct tsCddUartDevCb
{
  tfpCddUartTxCb fpTx;
  tfpCddUartRxCb fpRx;
}tsCddUartDevCb;

typedef struct tsCddUartCbData
{
  tsCddUartDevCb  sDevCb;
  CONST_AL uint16 unCbId;
}tsCddUartCbData;

typedef struct tsCddUartDevSeqData
{
  tsCddUartCbData*          psCbData;
  CONST_AL teCddUartDev     eDev;
  CONST_AL uint8            ucCbCount;
}tsCddUartDevSeqData;

typedef struct tsCddUartDevSeqData_StM
{
  uint8  ucDevAct;
  uint8  ucDevDyn;
  uint8  ucCbAct;
}tsCddUartDevSeqData_StM;

typedef struct tsCddUartSeqData
{
  tsCddUartDevSeqData*    psDevData;
  tsCddUartDevSeqData_StM sStM;
}tsCddUartSeqData;

typedef struct tsCddUartSeqHandler
{
  CONST_AL teCddUartIfc eUartIfc;
  uint8                 ucCycleCnt;
  CONST_AL uint8        ucPrescaler;
  CONST_AL uint8        ucTimeOutMax;
  uint8                 ucTimeOutCnt;
  uint8                 ucSeqContext;
  uint8                 ucIntDevIdx;
}tsCddUartSeqHandler;

typedef struct tsCddUartDynamicCfg
{
  uint8 ucMountedDev;
  uint8 aucIdxMountedDev[(uint8)CddUart_eDev_Count];
}tsCddUartDynamicCfg;


//=============================================================================
// Private variables
//=============================================================================

//Device handler
#define CDDUART_MAC_DECL_DEVHANDLE
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_DEVHANDLE

//Ifc Hw Mode 
#define CDDUART_MAC_DECL_IFCCFG
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_IFCCFG

  //Dev Dynamic Cfg
#define CDDUART_MAC_DECL_DEVDYNCFG
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_DEVDYNCFG

  //CBs prototypes
#define CDDUART_MAC_DECL_CBS
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_CBS
//Device CBs and CbIds
#define CDDUART_MAC_DECL_DEVCB
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_DEVCB
#ifndef UNIT_TEST
#define CDDUART_MAC_DECL_DEVCB_ASSERT
// PRQA S 605 EOF // Justification: Intended assertion statement
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_DEVCB_ASSERT
#endif
//Sequence data per interface
#define CDDUART_MAC_DECL_SEQDATAIFC
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_SEQDATAIFC
//Full sequence data
#define CDDUART_MAC_DECL_SEQDATA
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_SEQDATA
//Sequence handler
#define CDDUART_MAC_DECL_SEQHANDLE
#include <../Cdd/CddUart/Cfg/CddUart_Cfg.h>
#undef  CDDUART_MAC_DECL_SEQHANDLE


//=============================================================================
// Private declarations
//=============================================================================

//Uart driver state
STATIC_AL uint8 CddUart_ucState = CDDUART_STATE_RESET;

//Uart status fault
#if (CDDUART_STATUS_FAULT == STD_ON)
STATIC_AL uint8 CddUart_ucStatusFaultVal;
#endif


//=============================================================================
// Private functions prototypes
//=============================================================================
STATIC_AL void      CddUart_StartMapping(void);
STATIC_AL void      CddUart_ProcessSequence(uint8 ucSeq);
STATIC_AL void      CddUart_CalculateIfcSeqMap(uint8 ucSeq);
STATIC_AL void      CddUart_ISRHandle(uint8 ucIdx);
STATIC_AL boolean   CddUart_ProcessDynamicCfg(void);
STATIC_AL boolean   CddUart_GetCodData(uint8 *pucMountedDevice);
STATIC_AL void      CddUart_UploadData(uint8 ucSeq);
STATIC_AL void      CddUart_ProcessTxCallback(uint8 ucSeq);
STATIC_AL void      CddUart_ProcessRxCallback(uint8 ucSeq);
STATIC_AL void      CddUart_HandleDataOnIrq(const uint8 ucSeq);
STATIC_AL void      CddUart_PrepareForCycle(uint8 ucMountedDevices);
STATIC_AL boolean   CddUart_SequenceStM(const uint8 ucSeq, const boolean boActDevFault);
STATIC_AL void      CddUart_ResetStM(const uint8 ucSeq);
STATIC_AL void      CddUart_GetTxData(const uint8 ucSeq);

//=============================================================================
// Global variables
//=============================================================================
STATIC_AL volatile boolean CddUart_boIsDmaReady[(uint8)CddUart_eSeq_Count] = { TRUE };
STATIC_AL uint8            CddUart_aucRxDataDMA[(uint8)CddUart_eSeq_Count][CDDUART_MAX_RX_DATA];

STATIC_AL tsCddUart_MessageEntryType CddUart_sMessageEntry[(uint8)CddUart_eSeq_Count];
STATIC_AL tsCddUartDynamicCfg        CddUart_DynamicCfg[(uint8)CddUart_eSeq_Count];

//=============================================================================
// Public functions  implementation
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief riCddUartInit
///
/// \descr Init Runnable of module CddUart.It acts as a function wrapper which calls
///        CddUart_Start for module initialization at Rte context.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void riCddUartInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCddUartInit)
#endif

    CddUart_StartMapping();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCddUartInit)
#endif
}

//-----------------------------------------------------------------------------
/// \brief  rpCddUart_Cycle
///
/// \descr  Cyclic runnable  of module CddUart. It acts as a function wrapper which
///         calls the rpCddUart_Cycle for cyclic handling at Rte context.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void rpCddUart_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCddUart_Cycle)
#endif

  CddUart_Cycle();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCddUart_Cycle)
#endif
}

//-----------------------------------------------------------------------------
/// \brief CddUart_Init
///
/// \descr Initialize all UART units configured in CddUart_Cfg.h by calling derived initialization functions 
///        Switch to SINGLE Operation Mode. Driver must be in Reset State
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_Init(void)
{
  //Check if driver has not been initialized yet to proceed the initialization sequence
  if (CddUart_ucState == CDDUART_STATE_RESET)
  {
    //Initialize all configured Uart interfaces
    for (uint8 ucIfcIdx = 0U; ucIfcIdx < (uint8)CddUart_eIfc_Count; ucIfcIdx++)
    {
      CddUart_InitIfc_Deriv(CddUart_asIfcCfg[ucIfcIdx].ucIfcMap);
    }
    //Switch mode to SINGLE Operation as default Operation mode after initialization
    CddUart_ucState = CDDUART_STATE_INITIALIZED;
  }
}

//-----------------------------------------------------------------------------
/// \brief CddUart_DeInit
///
/// \descr DeInitialize all UART units configured in CddUart_Cfg.h by calling derived deinitialization functions
///        Switch to Reset State. Driver must be either in Single Operation Mode or Cyclic Operation Mode State.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_DeInit(void)
{
  //Check if driver is already deinitialized to proceed with deinitialization sequence
  if (CddUart_ucState != CDDUART_STATE_RESET)
  {
    //Initialize all configured Uart interfaces
    for (uint8 ucIdx = 0U; ucIdx < (uint8)CddUart_eIfc_Count; ucIdx++)
    {
      CddUart_DeInitIfc_Deriv(CddUart_asIfcCfg[ucIdx].ucIfcMap);
    }
    //Switch to Reset state
    CddUart_ucState = CDDUART_STATE_RESET;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_StartMapping
///
/// \descr  Trigger the CYCLIC OPERATION mode.
///         Execute Dynamic Configuration to update number of elements if this option is configured
///         in CddUart_Cfg.h
///         Calculate Interface mapping for every sequence.
///         Module must be in SINGLE Operation mode.
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_StartMapping(void)
{
  //check if module has been initialized 
  if (CddUart_ucState == CDDUART_STATE_INITIALIZED)
  {
    //run for each sequence
    for (uint8 ucSeqIdx = 0U; ucSeqIdx < (uint8)CddUart_eSeq_Count; ucSeqIdx++)
    {
      tsCddUartSeqHandler* const psSeqHandler = &CddUart_asSeqHandler[ucSeqIdx];
      //Temporary software timer, use GPT instead
      uint32 ulTimer = 0xFFFFUL;

      //Wait until Uart Ifc is idle
      while ((CddUart_IfcIdle_Deriv(CddUart_asIfcCfg[psSeqHandler->eUartIfc].ucIfcMap) == FALSE) &&
        (ulTimer > 0U))
      {
        ulTimer--;
    }
      //Calculate assigned SeqId for every Ifc
      CddUart_CalculateIfcSeqMap(ucSeqIdx);
      //prepare DMA flag as ready
      CddUart_boIsDmaReady[ucSeqIdx] = TRUE;
    }

    //Switch mode to CYCLIC operation
    CddUart_ucState = CDDUART_STATE_CYCLIC_OPERATION;

  }
}

//-----------------------------------------------------------------------------
/// \brief CddUart_Cycle
///
/// \descr Cyclic module API. Process all sequences configured in CddUart_Cfg
///        Provide Status Fault information if this option is configured in CddUart_Cfg.
///        Module must be in CYCLIC Operation Mode.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_Cycle(void)
{

  //Check if module is in Cyclic Operation mode
  if (CddUart_ucState == CDDUART_STATE_CYCLIC_OPERATION)
  {
    if (CddUart_ProcessDynamicCfg() != FALSE)
    {
      for (uint8 ucSeqIdx = 0U; ucSeqIdx < (uint8)CddUart_eSeq_Count; ucSeqIdx++)
      {
        CddUart_ProcessSequence(ucSeqIdx);
      }
    }
  }
  else
  {
    //cycle mode not ready
  }

#if (CDDUART_STATUS_FAULT == STD_ON)
  CddUart_StatusFault(CddUart_ucStatusFaultVal);
#endif

}

//=============================================================================
// Private functions  implementation
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief CddUart_CalculateIfcSeqMap
///
/// \descr Calculate the Uart Interface Index that the Sequence operates with
///        This depends on the order the Sequence map has been configured in CddUart_Cfg.h
///
///        E.g IFC5 Ifc -> Index 0, IFC4 ->Ifc Index 1
///        CDDUART_IFC(CDDUART_IFC5, CDDUART_SINGLE_POLLING, CDDUART_CYCLIC_POLLING)
///        CDDUART_IFC(CDDUART_IFC4, CDDUART_SINGLE_POLLING, CDDUART_CYCLIC_INTERRUPT)
///
///        IFC4 -> Seq Index 0    , IFC5->Seq Index 1
///        BEGIN_CDDUART_SEQ(CDDUART_IFC4, 0, 0, 3)
///         (...)
///        END_CDDUART_SEQ
///         
///        BEGIN_CDDUART_SEQ(CDDUART_IFC5, 0, 0, 3)
///        (...)
///        END_CDDUART_SEQ
///
/// \param  ucSeq : Sequence Index to be processed
///
/// \return 
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_CalculateIfcSeqMap(uint8 ucSeq)
{
  uint8 ucIfcIdx = 0U;
  while (((uint8)CddUart_asSeqHandler[ucSeq].eUartIfc != ucIfcIdx) && (ucIfcIdx < (uint8)CddUart_eIfc_Count))
  {
    ucIfcIdx++;
  }

  CddUart_asIfcCfg[ucIfcIdx].ucSeqMap = ucSeq;
}


//-----------------------------------------------------------------------------
/// \brief  CddUart_GetCodData
///
/// \descr  This function saves the number of mounted device type on UART and
///         returns data availability status
///
/// \param  pucMountedDevice
///
/// \return STATIC_AL boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddUart_GetCodData(uint8 *pucMountedDevice)
{
  boolean boCodStatus = FALSE;
  uint8 ucCodBaudRate = 0u, ucMountedDev_Bit = 0u;

  for (uint8 ucDevIdx = 0U; ucDevIdx < (uint8)CddUart_eDev_Count; ucDevIdx++)
  {
    if (CddUart_asDevDynCfg[ucDevIdx].fpDevDynCfgCb != NULL_PTR)
    {
      boCodStatus = CddUart_asDevDynCfg[ucDevIdx].fpDevDynCfgCb(ucDevIdx, &ucCodBaudRate, &ucMountedDev_Bit);
      //consistency data - coding is available

      if (boCodStatus != FALSE)
      {
        *pucMountedDevice = ucMountedDev_Bit;
        //config baudrate
        switch (ucCodBaudRate)
        {
        case CDDUART_BAUDRATE_CODING_500Kbps:
          CddUart_asDeviceCfg[ucDevIdx].ulBaudRate = CDDUART_BAUDRATE_500K;
          break;
        case CDDUART_BAUDRATE_CODING_1Mbps:
          CddUart_asDeviceCfg[ucDevIdx].ulBaudRate = CDDUART_BAUDRATE_1M;
          break;
        default:
          //default cfg value
          break;
        }
        //prepare UART configuration
        CddUart_ConfigureTransfer_Param(&CddUart_asDeviceCfg[ucDevIdx]);
      }
    }
  }

  return boCodStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_ProcessDynamicCfg
///
/// \descr  This function creates a dynamic configuration on the pre-configured 
///         UART mapping based on coded data : mounted devices, uart baud rate
///
/// \param  void
///
/// \return STATIC_AL boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddUart_ProcessDynamicCfg(void)
{
  STATIC_UT(boolean, boCodingData, FALSE);
  uint8 ucCodDev_Bit = 0u;

  //while coding not available, try again
  if (boCodingData == FALSE)
  {
    boCodingData = CddUart_GetCodData(&ucCodDev_Bit);
 
    if (boCodingData != FALSE)
    {
      CddUart_PrepareForCycle(ucCodDev_Bit);
    }
  }
  //return consisteny status of coding data
  return boCodingData;
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_PrepareForCycle
///
/// \descr  This function prepares data for cyclic operation. It configures dynamically
///         the mounted devices on UART interfaces.
///
/// \param  ucMountedDevices
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_PrepareForCycle(uint8 ucMountedDevices)
{
  for (uint8_fast ucSeqIdx = 0U; ucSeqIdx < (uint8)CddUart_eSeq_Count; ucSeqIdx++)
  {
    CddUart_DynamicCfg[ucSeqIdx].ucMountedDev = 0u;
    for (uint8 ucDevIdx = 0U; ucDevIdx < (uint8)CddUart_eDev_Count; ucDevIdx++)
    {
      if (((ucMountedDevices & (uint8)(1u << ucDevIdx)) != 0u))
      {
        CddUart_DynamicCfg[ucSeqIdx].aucIdxMountedDev[CddUart_DynamicCfg[ucSeqIdx].ucMountedDev] = ucDevIdx;
        CddUart_DynamicCfg[ucSeqIdx].ucMountedDev++;
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_ProcessTxCallback
///
/// \descr  This function is the entry point in the cyclic sequence processing,
///         and its purpose is to process the TX callback and get the TX data 
///         from upper layer. It processes TX callbacks on each sequence.
///
/// \param  ucSeq
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_ProcessTxCallback(uint8 ucSeq)
{
  //start from the beginning
  CddUart_ResetStM(ucSeq);
  //reset DMA flag for a new trigger
  CddUart_boIsDmaReady[ucSeq] = FALSE;
  //get data
  CddUart_GetTxData(ucSeq);
}


//-----------------------------------------------------------------------------
/// \brief  CddUart_UploadData
///
/// \descr  This function is called after TX callback was processed, TX and
///         RX configuration data were saved and triggers a DMA transfer.
///
/// \param  ucSeq
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_UploadData(uint8 ucSeq)
{
  const uint8 ucDevIdx = CddUart_asSeqData[ucSeq].sStM.ucDevAct;
  /*
    Msg:  310(Casting to different object pointer type.)
    Msg: 3305(Pointer cast to stricter alignment.)
  */
  //start DMA transfer
  CddUart_StartTransfer_Deriv(CddUart_asDeviceCfg[ucDevIdx].ucUartIfc,
                              (uint32*)&CddUart_sMessageEntry[ucSeq].pucTxData[0],  // PRQA S 310, 3305 //the cast is allowed since we need memory address
                              (uint32*)&CddUart_aucRxDataDMA[ucSeq][0],         // PRQA S 310, 3305 //the cast is allowed since we need memory address
                              CddUart_sMessageEntry[ucSeq].ucTxDataLength,
                              CddUart_sMessageEntry[ucSeq].ucRxDataLength);
}


//-----------------------------------------------------------------------------
/// \brief  CddUart_ProcessRxCallback
///
/// \descr This function is called after TX callback was performed, and reception
///        is completed. The aim is to update the received data to the upper layer
///        from the configured byte position.
///
/// \param  ucSeq
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_ProcessRxCallback(uint8 ucSeq)
{
  tsCddUartSeqHandler* const psSeqHandler = &CddUart_asSeqHandler[ucSeq];
  const boolean boRxStatus = CddUart_GetRxCbStatus();

  uint8 ucDevIdx = CddUart_asSeqData[ucSeq].sStM.ucDevAct;
  uint8 ucCbIdx  = CddUart_asSeqData[ucSeq].sStM.ucCbAct;
  
  if (CddUart_asIfcCfg[psSeqHandler->eUartIfc].eIfcCyclicMode == CddUart_eIfcCyclicMode_DMA)
  {
    tfpCddUartRxCb fpRxTemp = CddUart_asSeqData[ucSeq].psDevData[ucDevIdx].psCbData[ucCbIdx].sDevCb.fpRx;
    if (fpRxTemp != NULL_PTR)
    {
      for (uint8_fast ucIdx = 0u; ucIdx < CddUart_sMessageEntry[ucSeq].ucRxDataLength; ucIdx++)
      {
        CddUart_sMessageEntry[ucSeq].pucRxData[ucIdx] = CddUart_aucRxDataDMA[ucSeq][ucIdx + CddUart_sMessageEntry[ucSeq].ucTxDataLength];
      }
      fpRxTemp(&CddUart_sMessageEntry[ucSeq].pucRxData[0], boRxStatus);
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  CddUart_ProcessSequence
///
/// \descr  Handle cycles to service TX and RX Data processing, considering pre-scaling and timeouts.
///         Check if previous transmission has been completed. 
///         If previous transmission has been completed, process RX and TX Data.
///         By first Cycle, only TX -Data is processed , since no RX data is available yet, and
///         initialization flag is set, so that the driver knows that it can process RX Data.
///
/// \param  ucSeq : Sequence Index to be processed.
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_ProcessSequence(uint8 ucSeq)
{
  tsCddUartSeqHandler* const psSeqHandler = &CddUart_asSeqHandler[ucSeq];
  tsCddUartSeqData*    const psSeqData = &CddUart_asSeqData[ucSeq];
  
  if (psSeqHandler->ucCycleCnt == 0U)
  {
    if ((psSeqHandler->ucSeqContext & CDDUART_SEQ_CONTEXT_INITIALIZED_MSK) != 0U)
    {
      //Check for last transfer to be complete
      //Polling   Mode: To be done -> Check that all sequence frames are received
      //DMA       Mode: It's done for LP3 and DPE projects
      //Interrupt Mode: To be done -> Transfer complete flag is set in ISR
      switch (CddUart_asIfcCfg[psSeqHandler->eUartIfc].eIfcCyclicMode)
      {
      case  CddUart_eIfcCyclicMode_Polling:
        //not available
        break;
        //Get DMA done flag status for RX completed.
      case  CddUart_eIfcCyclicMode_DMA:
        psSeqHandler->ucSeqContext |= (CddUart_boIsDmaReady[ucSeq] != FALSE) ? CDDUART_SEQ_CONTEXT_COMPLETE_MSK : 0x00U;
        break;
        //Do nothing.Transfer completion is evaluated in ISR.
      case  CddUart_eIfcCyclicMode_Interrupt:
        //not available 
      default:
        break;
      }

      //Transfer complete, handle next sequence
      if ((psSeqHandler->ucSeqContext & CDDUART_SEQ_CONTEXT_COMPLETE_MSK) != 0U)
      {
        //Reset Transmission complete flag
        psSeqHandler->ucSeqContext &= (uint8)(~CDDUART_SEQ_CONTEXT_COMPLETE_MSK);
        //Reset Cycles TimeOut
        psSeqHandler->ucTimeOutCnt = psSeqHandler->ucTimeOutMax;
        //check if the first callback can be performed
        CddUart_ProcessTxCallback(ucSeq);
      }
      else
      {
        // try to handle next sequence
        if (psSeqHandler->ucTimeOutCnt == 0U)
        {
          // go on at the next command
          CddUart_HandleDataOnIrq(ucSeq);
          //Reset TimeOut Counter
          psSeqHandler->ucTimeOutCnt = psSeqHandler->ucTimeOutMax;
        }
        else
        {
          //if maximum wait-cycles (timeout) are not elapsed
          //ignore Rx and Tx Data processing and
          //decrement TimeOut counter 
          psSeqHandler->ucTimeOutCnt--;
        }
      }
    }
    else
    {
      //check if the first callback can be performed
      CddUart_ProcessTxCallback(ucSeq);
      //Set Initialized Flag in Sequence context variable
      psSeqHandler->ucSeqContext |= (uint8)CDDUART_SEQ_CONTEXT_INITIALIZED_MSK;
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
/// \brief  CddUart_SendReceived_Irq0
///
/// \descr  This function called IRQ 0 it belongs to sequence 0
/// \descr  This is a callback function called from DMA interrupt if the message was 
///         successfully received.
///         The data is updated to the Rx buffers in upper layers, and if there 
///         is a new message waiting to be sent this function proceeds to send it.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddUart_SendReceived_Irq0(void)
{
  CddUart_HandleDataOnIrq(0);
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_HandleDataOnIrq
///
/// \descr  This function is called by the DMA interrupt callback function if 
///         the message was successfully received OR if a timeout error was found.
///         The data is updated to the Rx buffers in upper layers, and if there 
///         is a new message waiting to be sent this function proceeds to send it.
///
/// \param  ucIrq it belong to a selected sequence
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_HandleDataOnIrq(const uint8 ucSeq)
{
  CddUart_ProcessRxCallback(ucSeq);

  CddUart_boIsDmaReady[ucSeq] = CddUart_SequenceStM(ucSeq, FALSE);

  if (CddUart_boIsDmaReady[ucSeq] == FALSE)
  {
    CddUart_GetTxData(ucSeq);
    
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_GetTxData
///
/// \descr  Call common subroutine to collect Tx-Data from Upper Layer of the current device
///         attached to the sequence and call specific subroutine to handle Tx transmission 
///         depending on the mode that the sequence operates with (Polling Interrupt or DMA)
///
/// \param  ucSeq
///
/// \return STATIC_AL boolean
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_GetTxData(const uint8 ucSeq)
{
  const uint8 ucDevAct = CddUart_asSeqData[ucSeq].sStM.ucDevAct;
  const uint8 ucDevDyn = CddUart_asSeqData[ucSeq].sStM.ucDevDyn;
  const uint8 ucCbIdx  = CddUart_asSeqData[ucSeq].sStM.ucCbAct;

  for (uint8_fast ucIdx = ucDevDyn; ucIdx < CddUart_DynamicCfg[ucSeq].ucMountedDev; ucIdx++)
  {
    tfpCddUartTxCb fpTxTemp = CddUart_asSeqData[ucSeq].psDevData[ucDevAct].psCbData[ucCbIdx].sDevCb.fpTx;
    if (fpTxTemp != NULL_PTR)
    {
      fpTxTemp(&CddUart_sMessageEntry[ucSeq]);

      if ((CddUart_sMessageEntry[ucSeq].pucTxData != NULL_PTR) && (CddUart_sMessageEntry[ucSeq].ucTxDataLength != 0u))
      {
        CddUart_UploadData(ucSeq);
        break;
      }
      else
      {
        CddUart_boIsDmaReady[ucSeq] = TRUE;
        if (CddUart_SequenceStM(ucSeq, TRUE) != FALSE) //go to next tx cb untill is triggered the stop condition
        {
          break;
        }
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CddUart_SequenceStM
///
/// \descr  This function implements a state machine for the sequence processing
///         to decide the callback to be called and the device to be addressed
///         based on the dynamic and static configuration
///
/// \param  ucSeq
///
/// \return STATIC_AL boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddUart_SequenceStM(const uint8 ucSeq, const boolean boActDevFault)
{
  boolean boStopCondition = FALSE;

  const uint8 ucDevAct = CddUart_asSeqData[ucSeq].sStM.ucDevAct;
  const uint8 ucCbAct = (boActDevFault == FALSE) ? CddUart_asSeqData[ucSeq].sStM.ucCbAct : (CddUart_asSeqData[ucSeq].psDevData[ucDevAct].ucCbCount - 1u);

  //DevAct will be used to express the static configuration 
  //DevDyn will be used to express the dynamic configuration
  if (ucCbAct < (CddUart_asSeqData[ucSeq].psDevData[ucDevAct].ucCbCount - 1u))
  {
    CddUart_asSeqData[ucSeq].sStM.ucCbAct++;
  }
  else
  {
    CddUart_asSeqData[ucSeq].sStM.ucCbAct = 0u;
    //CddUart_DynamicCfg[ucSeq].ucMountedDev indicate how many types (Gen2/Gen3) are mounted comming from coding data
    if (CddUart_asSeqData[ucSeq].sStM.ucDevDyn < (CddUart_DynamicCfg[ucSeq].ucMountedDev - 1u))
    {
      CddUart_asSeqData[ucSeq].sStM.ucDevDyn++;
      CddUart_asSeqData[ucSeq].sStM.ucDevAct = CddUart_DynamicCfg[ucSeq].aucIdxMountedDev[CddUart_asSeqData[ucSeq].sStM.ucDevDyn];
    }
    else
    {
      //stop condition
      CddUart_asSeqData[ucSeq].sStM.ucDevAct = 0xFFu; //for safety reason
      CddUart_asSeqData[ucSeq].sStM.ucCbAct  = 0xFFu; //for safety reason
      boStopCondition = TRUE;
    }
  }

  return boStopCondition;
}


//-----------------------------------------------------------------------------
/// \brief  CddUart_ResetStM
///
/// \descr  This function resetes the state machine.
///
/// \param  ucSeq
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CddUart_ResetStM(const uint8 ucSeq)
{
  CddUart_asSeqData[ucSeq].sStM.ucCbAct  = 0u;
  CddUart_asSeqData[ucSeq].sStM.ucDevDyn = 0u;
  //start with the first mounted device
  CddUart_asSeqData[ucSeq].sStM.ucDevAct = CddUart_DynamicCfg[ucSeq].aucIdxMountedDev[0];
}
